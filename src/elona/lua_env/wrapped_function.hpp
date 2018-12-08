#pragma once
#include "../../thirdparty/sol2/sol.hpp"
#include "../enums.hpp"
#include "../message.hpp"
#include "../variables.hpp"

namespace elona
{
namespace lua
{

/**
 * Wrapper around sol::protected function for better ergonomics of handling
 * failure and default values.
 */
struct WrappedFunction
{
    WrappedFunction()
        : id("")
        , func(sol::lua_nil)
    {
    }

    WrappedFunction(std::string id, sol::protected_function func)
        : id(id)
        , func(func)
    {
    }

    std::string id;
    sol::protected_function func;

    template <typename... Args>
    void call_unsafely(Args&&... args) const
    {
        auto result = func.call(std::forward<Args>(args)...);
        if (!result.valid())
        {
            sol::error err = result;
            throw err;
        }
    }

    template <typename... Args>
    void call(Args&&... args) const
    {
        try
        {
            call_unsafely(std::forward<Args>(args)...);
        }
        catch (const sol::error& err)
        {
            std::string message = id + ": Script callback error: " + err.what();

            txt(message, Message::color{ColorIndex::red});
            std::cerr << message << std::endl;
        }
    }

    template <typename Retval, typename... Args>
    Retval call_with_result(Retval default_value, Args&&... args) const
    {
        auto result = func.call(std::forward<Args>(args)...);
        if (!result.valid())
        {
            sol::error err = result;
            std::string message = id + ": Script callback error: " + err.what();

            txt(message, Message::color{ColorIndex::red});
            std::cerr << message << std::endl;
            return default_value;
        }

        try
        {
            sol::optional<Retval> ret =
                result.template get<sol::optional<Retval>>();
            if (ret)
            {
                return *ret;
            }
            else
            {
                std::string message =
                    id + ": Script callback error: incorrect type returned";

                txt(message, Message::color{ColorIndex::red});
                std::cerr << message << std::endl;
                return default_value;
            }
        }
        catch (const std::exception& e)
        {
            std::string message = id + ": Script callback error: " + e.what();

            txt(message, Message::color{ColorIndex::red});
            std::cerr << message << std::endl;
            return default_value;
        }
    }
}; // namespace lua

} // namespace lua
} // namespace elona
