#pragma once
#include "../enums.hpp"
#include "../variables.hpp"
#include "../thirdparty/sol2/sol.hpp"

namespace elona
{
namespace lua
{

// Holds identifier and function pointer from an exported Lua
// function.
struct exported_function
{
    exported_function(std::string id,
                      sol::protected_function func)
        : id(id)
        , func(func) {}

    std::string id;
    sol::protected_function func;

    template <typename... Args>
    void call(Args&&... args) const
    {
        auto result = func.call(std::forward<Args>(args)...);
        if (!result.valid())
        {
            sol::error err = result;
            txtef(color_index_t::red);
            txt(id + ": Script callback error: " + err.what());
        }
    }

    template <typename Retval, typename... Args>
    sol::optional<Retval> call_with_result(Args&&... args) const
    {
        auto result = func.call(std::forward<Args>(args)...);
        if (!result.valid())
        {
            sol::error err = result;
            txtef(color_index_t::red);
            txt(id + ": Script callback error: " + err.what());
            return sol::nullopt;
        }

        return result.get();
    }
};

} // namespace lua
} // namespace elona
