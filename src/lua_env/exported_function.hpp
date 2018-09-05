#pragma once
#include "../enums.hpp"
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
    void call(Args&&... args) const
    {
        auto result = func.call(std::forward<Args>(args)...);
        if (!result.valid())
        {
            sol::error err = result;
            txtef(ColorIndex::red);
            txt(id + ": Script callback error: " + err.what());
        }
    }

    template <typename Retval, typename... Args>
    Retval call_with_result(Retval default_value, Args&&... args) const
    {
        auto result = func.call(std::forward<Args>(args)...);
        if (!result.valid())
        {
            sol::error err = result;
            txtef(ColorIndex::red);
            txt(id + ": Script callback error: " + err.what());
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
                txtef(ColorIndex::red);
                txt(id + ": Script callback error: incorrect type returned");
                return default_value;
            }
        }
        catch (const std::exception& e)
        {
            txtef(ColorIndex::red);
            txt(id + ": Script callback error: " + e.what());
            return default_value;
        }
    }
};

} // namespace lua
} // namespace elona
