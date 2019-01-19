#include "lua_api_input.hpp"
#include "../../i18n.hpp"
#include "../../input.hpp"
#include "../../input_prompt.hpp"
#include "../../message.hpp"

namespace elona
{
namespace lua
{

bool LuaApiInput::yes_no(const std::string& message)
{
    txt(message + " ");
    return static_cast<bool>(yes_no());
}

sol::optional<int> LuaApiInput::prompt_number(
    const std::string& message,
    int max)
{
    return LuaApiInput::prompt_number_with_initial(message, max, 0);
}

sol::optional<int> LuaApiInput::prompt_number_with_initial(
    const std::string& message,
    int max,
    int initial)
{
    if (max < 1)
    {
        throw sol::error("LuaApiInput.prompt_number called with max < 1");
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

sol::optional<std::string> LuaApiInput::prompt_text(
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

sol::optional<int> LuaApiInput::prompt_choice(sol::table choices)
{
    Prompt prompt;

    // Lua tables are 1-indexed, but the prompt is 0-indexed.
    for (size_t i = 1; i <= choices.size(); i++)
    {
        std::string choice = choices[i];
        prompt.append(choice, i - 1);
    }

    int rtval = prompt.query(promptx, prompty, 240);
    if (rtval == -1)
    {
        return sol::nullopt;
    }

    // Lua tables are 1-indexed, so add 1 to the result.
    return rtval + 1;
}

void LuaApiInput::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiInput, yes_no);
    LUA_API_BIND_FUNCTION(api_table, LuaApiInput, prompt_choice);
    api_table.set_function(
        "prompt_number",
        sol::overload(
            LuaApiInput::prompt_number,
            LuaApiInput::prompt_number_with_initial));
    LUA_API_BIND_FUNCTION(api_table, LuaApiInput, prompt_text);
}

} // namespace lua
} // namespace elona
