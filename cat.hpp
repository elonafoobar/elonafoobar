#pragma once

#include <memory>
#include <lua.hpp>
#include "filesystem.hpp"
#include "lib/noncopyable.hpp"


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


inline engine global;



} // namespace elona::cat
