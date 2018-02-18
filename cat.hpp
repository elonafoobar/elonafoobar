#pragma once

#include <memory>
#include <lua.hpp>
#include "filesystem.hpp"
#include "lib/noncopyable.hpp"


namespace elona::cat
{



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

private:
    std::unique_ptr<lua_State, decltype(&lua_close)> L{nullptr, lua_close};
};



inline engine global;



} // namespace elona::cat
