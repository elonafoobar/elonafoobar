#pragma once

#include <memory>
#include <unordered_map>
#include <lua.hpp>
#include "filesystem.hpp"
#include "lib/noncopyable.hpp"
#include "optional.hpp"


namespace elona::cat
{


using ref = int;



class engine : lib::noncopyable
{
public:
    engine() = default;

    void initialize();
    void load(const fs::path& filepath);
    void register_function(const char* name, lua_CFunction);

    lua_State* ptr()
    {
        return L.get();
    }


    template <typename T, typename... Args>
    T call(ref func, Args&&... args)
    {
        lua_rawgeti(ptr(), LUA_REGISTRYINDEX, func);
        using swallow = std::initializer_list<int>;
        (void)swallow{(void(push(args)), 0)...};

        lua_pcall(ptr(), sizeof...(Args), 1 /* TODO */, 0);
        return to_cpp_type<T>(-1);
    }


    // FIXME: DRY
    // -2 is the called function.
    // -1 is the first argument, i.e., self.
    template <typename T, typename... Args>
    T call_method(Args&&... args)
    {
        using swallow = std::initializer_list<int>;
        (void)swallow{(void(push(args)), 0)...};

        lua_pcall(ptr(), sizeof...(Args) + 1 /* for self */, 1 /* TODO */, 0);
        return to_cpp_type<T>(-1);
    }


    // FIXME: rename
    template <typename T, typename... Args>
    T call_with_self(ref self, ref func, Args&&... args)
    {
        lua_rawgeti(ptr(), LUA_REGISTRYINDEX, func);
        lua_rawgeti(ptr(), LUA_REGISTRYINDEX, self);
        using swallow = std::initializer_list<int>;
        (void)swallow{(void(push(args)), 0)...};

        lua_pcall(ptr(), sizeof...(Args) + 1 /* for self */, 1 /* TODO */, 0);
        return to_cpp_type<T>(-1);
    }


private:
    std::unique_ptr<lua_State, decltype(&lua_close)> L{nullptr, lua_close};



    void push(int n)
    {
        lua_pushinteger(ptr(), n);
    }


    void push(const char* s)
    {
        lua_pushstring(ptr(), s);
    }


    void push(const std::string s)
    {
        lua_pushstring(ptr(), s.c_str());
    }


    void push(double d)
    {
        lua_pushnumber(ptr(), d);
    }


    void push(nullptr_t)
    {
        lua_pushnil(ptr());
    }



    template <typename T>
    T to_cpp_type(int index)
    {
        if constexpr (std::is_same_v<T, std::string>)
        {
            return luaL_checkstring(ptr(), index);
        }
        else if constexpr (std::is_same_v<T, int>)
        {
            return luaL_checkinteger(ptr(), index);
        }
        else if constexpr (std::is_same_v<T, double>)
        {
            return luaL_checknumber(ptr(), index);
        }
        else if constexpr (std::is_same_v<T, nullptr_t>)
        {
            (void)index;
            return nullptr;
        }
    }
};


inline engine global;



template <typename T>
struct userdata
{
    static void push_new(lua_State* L, T* ptr)
    {
        auto self = lua_newuserdata(L, sizeof(userdata<T>));
        (static_cast<userdata<T>*>(self))->_ptr = ptr;
    }

    T* ptr() noexcept
    {
        return _ptr;
    }

private:
    T* _ptr;
};



template <typename>
struct cat_db_traits;


template <class T>
class cat_db : public lib::noncopyable
{
    using traits_type = cat_db_traits<T>;

public:
    using id_type = typename traits_type::id_type;
    using data_type = typename traits_type::data_type;
    using map_type = std::unordered_map<id_type, data_type>;


    struct iterator
    {
    private:
        using base_iterator_type = typename map_type::const_iterator;

    public:
        using value_type = const data_type;
        using difference_type = typename base_iterator_type::difference_type;
        using pointer = value_type*;
        using reference = value_type&;
        using iterator_category =
            typename base_iterator_type::iterator_category;


        iterator(const typename map_type::const_iterator& itr)
            : itr(itr)
        {
        }

        reference operator*() const
        {
            return itr->second;
        }

        pointer operator->() const
        {
            return itr.operator->();
        }

        void operator++()
        {
            ++itr;
        }

        bool operator!=(const iterator& other) const
        {
            return itr != other.itr;
        }

    private:
        typename map_type::const_iterator itr;
    };



    iterator begin() const
    {
        return iterator{std::begin(storage)};
    }

    iterator end() const
    {
        return iterator{std::end(storage)};
    }


    void initialize()
    {
        cat::global.load(
            fs::path(u8"../data") / fs::path(traits_type::filename));

        auto L = cat::global.ptr();

        lua_getglobal(L, traits_type::table_name);
        lua_getfield(L, -1, u8"__storage__");
        lua_pushnil(L);
        while (lua_next(L, -2))
        {
            static_cast<T&>(*this).define(L);
            lua_pop(L, 1);
        }
        lua_pop(L, 2);
    }


    optional_ref<data_type> operator[](const id_type& id) const
    {
        const auto itr = storage.find(id);
        if (itr == std::end(storage))
            return none;
        else
            return itr->second;
    }


protected:
    map_type storage;
};



#define ELONA_CAT_DB_FIELD_INTEGER(name, default_value) \
    lua_getfield(L, -1, #name); \
    int name = lua_isnil(L, -1) ? (default_value) : luaL_checkinteger(L, -1); \
    lua_pop(L, 1);
#define ELONA_CAT_DB_FIELD_STRING(name, default_value) \
    lua_getfield(L, -1, #name); \
    const char* name = \
        lua_isnil(L, -1) ? (default_value) : luaL_checkstring(L, -1); \
    lua_pop(L, 1);
#define ELONA_CAT_DB_FIELD_BOOLEAN(name, default_value) \
    lua_getfield(L, -1, #name); \
    bool name = lua_isnil(L, -1) ? (default_value) : lua_toboolean(L, -1); \
    lua_pop(L, 1);
#define ELONA_CAT_DB_FIELD_REF(name) \
    lua_getfield(L, -1, #name); \
    cat::ref name = luaL_ref(L, LUA_REGISTRYINDEX);



} // namespace elona::cat
