#pragma once
#include "../enums.hpp"
#include "../message.hpp"
#include "../thirdparty/sol2/sol.hpp"
#include "../variables.hpp"

namespace elona
{
namespace lua
{

// Holds identifier and function pointer from an exported Lua
// function.
struct ExportedFunction
{
    ExportedFunction(std::string id, sol::protected_function func)
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

            Message::instance().txtef(ColorIndex::red);
            txt(message);
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

            Message::instance().txtef(ColorIndex::red);
            txt(message);
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

                Message::instance().txtef(ColorIndex::red);
                txt(message);
                std::cerr << message << std::endl;
                return default_value;
            }
        }
        catch (const std::exception& e)
        {
            std::string message = id + ": Script callback error: " + e.what();

            Message::instance().txtef(ColorIndex::red);
            txt(message);
            std::cerr << message << std::endl;
            return default_value;
        }
    }
}; // namespace lua

} // namespace lua
} // namespace elona
