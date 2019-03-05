#include "lua_api_input.hpp"
#include "../../i18n.hpp"
#include "../../input.hpp"
#include "../../input_prompt.hpp"
#include "../../message.hpp"

namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Prompts the player to select "yes" or "no".
 * @tparam string message a message to display
 * @treturn[1] bool true if "yes" was selected.
 * @treturn[2] nil if canceled.
 * @usage local result = Input.yes_no("Yes or no?")
 *
 * if result == nil then
 *    GUI.txt("You canceled. ")
 * elseif result then
 *    GUI.txt("You chose yes. ")
 * else
 *    GUI.txt("You chose no. ")
 * end
 */
sol::optional<bool> LuaApiInput::yes_no(const std::string& message)
{
    txt(message + " ");
    const auto result = elona::yes_no();
    if (result == YesNo::canceled)
    {
        return sol::nullopt;
    }
    else
    {
        return result == YesNo::yes;
    }
}



sol::optional<int> LuaApiInput::prompt_number(
    const std::string& message,
    int max)
{
    return LuaApiInput::prompt_number_with_initial(message, max, 0);
}

/**
 * @luadoc prompt_number
 *
 * Prompts the player to choose a number. Raises an error if
 * <code>max</code> is less than 0.
 * @tparam string message a message to display
 * @tparam num max the maximum number choosable
 * @tparam[opt] num initial the initial value
 * @treturn[1] num the number chosen
 * @treturn[2] nil if canceled, or max < 0
 * @usage local result = Input.prompt_number("Which character to spawn? ", 353)
 * if result then
 *    local chara = Chara.create(25, 25, result)
 *    if chara then
 *       GUI.txt("Spawned " .. chara.name .. ". ")
 *    end
 * else
 *    GUI.txt("Never mind.")
 * end
 */
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

/**
 * @luadoc
 *
 * Prompts the player to enter text.
 * @tparam string message a message to display
 * @tparam bool is_cancelable whether or not the dialog can be canceled
 * @treturn[1] string the text that was input
 * @treturn[1] nil if canceled
 * @usage local result = Input.prompt_text("What text?", true)
 *
 * if result then
 *    GUI.txt("You typed \"" .. result .. "\". ")
 * else
 *    GUI.txt("Never mind. ")
 * end
 */
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

/**
 * @luadoc
 *
 * Prompts the player to select from a list of choices. Raises an
 * error if no arguments are provided.
 * @tparam table choices a list of string choices
 * @treturn[1] num the index of the item chosen, starting from 1
 * @treturn[2] nil if canceled
 * @usage GUI.txt("Which? ")
 * local choices = {"First", "Second", "Third"}
 * local result = Input.prompt_choice(choices)
 *
 * if result then
 *    GUI.txt("You chose \"" .. choices[result] .. "\". ")
 * else
 *    GUI.txt("Never mind. ")
 * end
 */
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
