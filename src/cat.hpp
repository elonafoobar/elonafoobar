#pragma once

#include <chrono>
#include <memory>
#include <unordered_map>
#include <lua.hpp>
#include "filesystem.hpp"
#include "lib/noncopyable.hpp"
#include "log.hpp"
#include "macro.hpp"
#include "optional.hpp"

using namespace std::literals::string_literals;

namespace elona
{
namespace cat
{


using Ref = int;



class Engine : lib::noncopyable
{
public:
    Engine() = default;

    void initialize();
    void load(const fs::path& filepath);
    void register_function(const char* name, lua_CFunction);

    lua_State* ptr()
    {
        return L.get();
    }


    template <typename T, typename... Args>
    T call(Ref func, Args&&... args)
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
    T call_with_self(Ref self, Ref func, Args&&... args)
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


    void push(std::nullptr_t)
    {
        lua_pushnil(ptr());
    }



    template <
        typename T,
        std::enable_if_t<
            std::is_same<T, std::nullptr_t>::value,
            std::nullptr_t> = nullptr>
    T to_cpp_type(int index)
    {
        UNUSED(index);
        return nullptr;
    }

#define ELONA_DEFINE_TO_CPP_TYPE(type, function) \
    template < \
        typename T, \
        std::enable_if_t<std::is_same<T, type>::value, std::nullptr_t> = \
            nullptr> \
    T to_cpp_type(int index) \
    { \
        return function(ptr(), index); \
    }

    ELONA_DEFINE_TO_CPP_TYPE(std::string, luaL_checkstring)
    ELONA_DEFINE_TO_CPP_TYPE(int, luaL_checkinteger)
    ELONA_DEFINE_TO_CPP_TYPE(double, luaL_checknumber)
#undef ELONA_DEFINE_TO_CPP_TYPE
};


extern Engine global;



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
struct CatDBTraits;


template <class T>
class CatDB : public lib::noncopyable
{
    using TraitsType = CatDBTraits<T>;

public:
    using IdType = typename TraitsType::IdType;
    using DataType = typename TraitsType::DataType;
    using MapType = std::unordered_map<IdType, DataType>;


    struct iterator
    {
    private:
        using base_iterator_type = typename MapType::const_iterator;

    public:
        using value_type = const DataType;
        using difference_type = typename base_iterator_type::difference_type;
        using pointer = value_type*;
        using reference = value_type&;
        using iterator_category =
            typename base_iterator_type::iterator_category;


        iterator(const typename MapType::const_iterator& itr)
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
        typename MapType::const_iterator itr;
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
        using namespace std::chrono;
        steady_clock::time_point begin = steady_clock::now();

        cat::global.load(filesystem::path(u8"data") / TraitsType::filename);

        auto L = cat::global.ptr();

        lua_getglobal(L, TraitsType::table_name);
        lua_getfield(L, -1, u8"__storage__");
        lua_pushnil(L);
        while (lua_next(L, -2))
        {
            static_cast<T&>(*this).define(L);
            lua_pop(L, 1);
        }
        lua_pop(L, 2);

        steady_clock::time_point end = steady_clock::now();
        auto time =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - begin)
                .count();
        ELONA_LOG(
            "[CAT ("s << TraitsType::filename << ")] Elements: "s
                      << storage.size() << ", time: []"s << time << "ms"s);
    }


    optional_ref<DataType> operator[](const IdType& id) const
    {
        const auto itr = storage.find(id);
        if (itr == std::end(storage))
            return none;
        else
            return itr->second;
    }


protected:
    MapType storage;
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
    cat::Ref name = luaL_ref(L, LUA_REGISTRYINDEX);



} // namespace cat
} // namespace elona
