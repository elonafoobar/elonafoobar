#pragma once

#include "../../util/noncopyable.hpp"
#include "../filesystem.hpp"
#include "lua_env.hpp"



namespace elona
{
namespace lua
{

class LuaSubmodule : public lib::noncopyable
{
protected:
    explicit LuaSubmodule(LuaEnv& lua)
        : _lua(lua)
        , _env(*_lua.get_state(), sol::create, _lua.get_state()->globals())
    {
    }


    LuaEnv& lua()
    {
        return _lua;
    }


    std::shared_ptr<sol::state> lua_state()
    {
        return _lua.get_state();
    }


    sol::environment& env()
    {
        return _env;
    }


    const sol::environment& env() const
    {
        return _env;
    }


    auto safe_script_in_global_env(const std::string& source)
    {
        return lua_state()->safe_script(source);
    }


    auto safe_script_file_in_global_env(const fs::path& filepath)
    {
        return lua_state()->safe_script_file(
            filepathutil::to_utf8_path(filepath));
    }


    auto safe_script(const std::string& source, sol::environment& env)
    {
        return lua_state()->safe_script(source, env);
    }


    auto safe_script_file(const fs::path& filepath, sol::environment& env)
    {
        return lua_state()->safe_script_file(
            filepathutil::to_utf8_path(filepath), env);
    }


    auto safe_script(const std::string& source)
    {
        return safe_script(source, env());
    }


    auto safe_script_file(const fs::path& filepath)
    {
        return safe_script_file(filepath, env());
    }


    template <typename ErrorHandler>
    auto safe_script(
        const std::string& source,
        sol::environment& env,
        ErrorHandler&& error_handler)
    {
        return lua_state()->safe_script(
            source, env, std::forward<ErrorHandler>(error_handler));
    }


    template <typename ErrorHandler>
    auto safe_script_file(
        const fs::path& filepath,
        sol::environment& env,
        ErrorHandler&& error_handler)
    {
        return lua_state()->safe_script_file(
            filepathutil::to_utf8_path(filepath),
            env,
            std::forward<ErrorHandler>(error_handler));
    }


    template <typename ErrorHandler>
    auto safe_script(const std::string& source, ErrorHandler&& error_handler)
    {
        return safe_script(
            source, env(), std::forward<ErrorHandler>(error_handler));
    }


    template <typename ErrorHandler>
    auto safe_script_file(
        const fs::path& filepath,
        ErrorHandler&& error_handler)
    {
        return safe_script_file(
            filepath, env(), std::forward<ErrorHandler>(error_handler));
    }



private:
    LuaEnv& _lua;
    sol::environment _env;
};

} // namespace lua
} // namespace elona
