#include "lua_api_input.hpp"
#include "../../i18n.hpp"
#include "../../input.hpp"
#include "../../input_prompt.hpp"
#include "../../message.hpp"

namespace elona
{
namespace lua
{

bool Input::yes_no(const std::string& message)
{
    txt(message + " ");
    rtval = yes_or_no(promptx, prompty, 160);
    return rtval == 0;
}

sol::optional<int> Input::prompt_number(const std::string& message, int max)
{
    return Input::prompt_number_with_initial(message, max, 0);
}

sol::optional<int> Input::prompt_number_with_initial(
    const std::string& message,
    int max,
    int initial)
{
    if (max < 1)
    {
        throw sol::error("Input.prompt_number called with max < 1");
    }

    txt(message + " ");
    input_number_dialog(
        (windoww - 200) / 2 + inf_screenx, winposy(60), max, initial);

    if (rtval == -1)
    {
        return sol::nullopt;
    }

    return elona::stoi(elona::inputlog(0));
}

sol::optional<std::string> Input::prompt_text(
    const std::string& message,
    bool is_cancelable)
{
    txt(message + " ");
    bool canceled = input_text_dialog(
        (windoww - 360) / 2 + inf_screenx,
        winposy(90),
        20,
        is_cancelable,
        true);
    if (canceled)
    {
        return sol::nullopt;
    }

    return elona::inputlog(0);
}

sol::optional<int> Input::prompt_choice(sol::variadic_args args)
{
    if (args.size() == 0)
    {
        throw sol::error("Input.prompt_choice called with no arguments");
    }

    Prompt prompt;
    for (size_t i = 0; i < args.size(); i++)
    {
        prompt.append(args[i].as<std::string>(), i);
    }

    int rtval = prompt.query(promptx, prompty, 160);
    if (rtval == -1)
    {
        return sol::nullopt;
    }

    // Lua tables are 1-indexed, so add 1 to the result.
    return rtval + 1;
}

void Input::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, Input, yes_no);
    LUA_API_BIND_FUNCTION(api_table, Input, prompt_choice);
    api_table.set_function(
        "prompt_number",
        sol::overload(Input::prompt_number, Input::prompt_number_with_initial));
    LUA_API_BIND_FUNCTION(api_table, Input, prompt_text);
}

} // namespace lua
} // namespace elona
