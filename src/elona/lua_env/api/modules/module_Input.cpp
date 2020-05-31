#include "../../../attack.hpp"
#include "../../../dialog.hpp"
#include "../../../i18n.hpp"
#include "../../../input.hpp"
#include "../../../input_prompt.hpp"
#include "../../../keybind/macro_action_queue.hpp"
#include "../../../macro.hpp"
#include "../../../menu.hpp"
#include "../../../message.hpp"
#include "../../../talk.hpp"
#include "../common.hpp"



/**
 * @luadoc
 *
 * Functions for prompting the player for input.
 */
namespace elona::lua::api::modules::module_Input
{

namespace
{

void _append_choices(sol::table& choices)
{
    int index = 0;
    std::string response_id;
    std::string text;

    listmax = 0;

    for (size_t i = 1; i <= choices.size(); i++)
    {
        sol::object value = choices[i];

        if (value.is<std::string>())
        {
            text = value.as<std::string>();
        }
        else
        {
            throw sol::error{"Dialog choices must be a table of strings."};
        }

        ELONA_APPEND_RESPONSE(index, text);
        index++;
    }

    if (listmax == 0)
    {
        throw sol::error{"No choices were provided."};
    }
}

} // namespace



/**
 * @luadoc yes_no
 *
 * Prompts the player to select "yes" or "no".
 *
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
sol::optional<bool> Input_yes_no(const std::string& message)
{
    input_halt_input(HaltInput::force);
    txt(message + i18n::space_if_needed());
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



/**
 * @luadoc prompt_number
 *
 * Prompts the player to choose a number. Raises an error if
 * <code>max</code> is less than 0.
 *
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
sol::optional<int> Input_prompt_number_with_initial(
    const std::string& message,
    int max,
    int initial)
{
    if (max < 1)
    {
        throw sol::error("Input.prompt_number(): called with max < 1");
    }

    txt(message + i18n::space_if_needed());
    input_number_dialog(
        (windoww - 200) / 2 + inf_screenx, winposy(60), max, initial);

    if (rtval == -1)
    {
        return sol::nullopt;
    }

    return elona::stoi(elona::inputlog(0));
}



sol::optional<int> Input_prompt_number(const std::string& message, int max)
{
    return Input_prompt_number_with_initial(message, max, 0);
}



/**
 * @luadoc prompt_text
 *
 * Prompts the player to enter text.
 *
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
sol::optional<std::string> Input_prompt_text(
    const std::string& message,
    bool is_cancelable)
{
    txt(message + i18n::space_if_needed());
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
 * @luadoc prompt_choice
 *
 * Prompts the player to select from a list of choices. Raises an
 * error if no arguments are provided.
 *
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
sol::optional<int> Input_prompt_choice(sol::table choices)
{
    Prompt prompt;
    size_t width = 160;

    // Lua tables are 1-indexed, but the prompt is 0-indexed.
    for (size_t i = 1; i <= choices.size(); i++)
    {
        sol::optional<std::string> choice = choices[i];
        if (choice)
        {
            width = std::max(width, strlen_u(*choice) * (13 - en * 2));
            prompt.append(std::move(*choice), i);
        }
    }

    int rtval = prompt.query(promptx, prompty, (int)width);
    if (rtval == -1)
    {
        return sol::nullopt;
    }

    return rtval;
}



int Input_prompt_dialog(
    const std::string& text,
    const std::string& portrait_id,
    const std::string& speaker_name,
    sol::table choices,
    sol::optional<int> default_index)
{
    // Copy text, as it is used mutably.
    auto text_ = text;

    _append_choices(choices);

    if (default_index)
    {
        chatesc = 1;
    }
    else
    {
        chatesc = -1;
    }

    talk_start();
    auto result =
        talk_window_query(portrait_id, none, speaker_name, text_, none);

    if (result == -1)
    {
        auto default_choice = clamp(*default_index, 0, (int)choices.size() - 1);
        return default_choice;
    }

    return result;
}



/**
 * @luadoc prompt_dialog
 *
 * Creates a dialog window like the one normally shown when talking to a
 * character.
 *
 * @tparam string message Message to display.
 * @tparam string portrait_id Portrait ID of the speaker.
 * @tparam string speaker_name Name of the speaker to display.
 * @tparam[opt] num default_index Default choice to use if canceled.
 * @tparam {string,...} choices An array of string choices for the dialog.
 * @tparam[opt] num impression Impression to display.
 * @tparam[opt] num interest Interest to display.
 * @return num index of the selected item, or the default if canceled
 */
int Input_prompt_dialog_impress(
    const std::string& text,
    const std::string& portrait_id,
    const std::string& speaker_name,
    sol::table choices,
    sol::optional<int> default_index,
    int impression,
    int interest)
{
    // Copy text, as it is used mutably.
    auto text_ = text;

    auto impress_interest = std::make_pair(impression, interest);

    _append_choices(choices);

    if (default_index)
    {
        chatesc = 1;
    }
    else
    {
        chatesc = -1;
    }

    talk_start();
    auto result = talk_window_query(
        portrait_id, none, speaker_name, text_, impress_interest);

    if (result == -1)
    {
        auto default_choice = clamp(*default_index, 0, (int)choices.size() - 1);
        return default_choice;
    }

    return result;
}



int Input_prompt_dialog_with_chip(
    const std::string& text,
    int chara_image,
    const std::string& speaker_name,
    sol::table choices,
    sol::optional<int> default_index)
{
    // Copy text, as it is used mutably.
    auto text_ = text;

    _append_choices(choices);

    if (default_index)
    {
        chatesc = 1;
    }
    else
    {
        chatesc = -1;
    }

    talk_start();
    auto result =
        talk_window_query(none, chara_image, speaker_name, text_, none);

    if (result == -1)
    {
        auto default_choice = clamp(*default_index, 0, (int)choices.size() - 1);
        return default_choice;
    }

    return result;
}



/**
 * @luadoc prompt_dialog
 *
 * Creates a dialog window like the one normally shown when talking to a
 * character.
 *
 * @tparam string message Message to display.
 * @tparam num chara_image Character chip of the speaker.
 * @tparam string speaker_name Name of the speaker to display.
 * @tparam[opt] num default_index Default choice to use if canceled.
 * @tparam {string,...} choices An array of string choices for the dialog.
 * @tparam[opt] num impression Impression to display.
 * @tparam[opt] num interest Interest to display.
 * @return num index of the selected item, or the default if canceled
 */
int Input_prompt_dialog_with_chip_impress(
    const std::string& text,
    int chara_image,
    const std::string& speaker_name,
    sol::table choices,
    sol::optional<int> default_index,
    int impression,
    int interest)
{
    // Copy text, as it is used mutably.
    auto text_ = text;

    auto impress_interest = std::make_pair(impression, interest);

    if (default_index)
    {
        chatesc = 1;
    }
    else
    {
        chatesc = -1;
    }

    talk_start();
    _append_choices(choices);

    auto result = talk_window_query(
        none, chara_image, speaker_name, text_, impress_interest);

    if (result == -1)
    {
        auto default_choice = clamp(*default_index, 0, (int)choices.size() - 1);
        return default_choice;
    }

    return result;
}



void Input_start_dialog(LuaCharacterHandle speaker)
{
    auto& speaker_ref = lua::ref<Character>(speaker);

    auto data = the_character_db.ensure(charaid2int(speaker_ref.id));
    if (!data.dialog_id)
    {
        throw sol::error(
            "Character has no dialog: "s + speaker_ref.new_id().get());
    }

    if (!talk_setup_variables(speaker_ref))
    {
        return;
    }
    talk_start();

    dialog_start(speaker_ref, *data.dialog_id);

    talk_end();
}



/**
 * @luadoc start_dialog
 *
 * Starts a dialog with a character.
 *
 * @tparam LuaCharacter speaker Character who will speak.
 * @tparam[opt] string dialog Dialog ID to use. Defaults to the one in the
 * character's definition.
 */
void Input_start_dialog_with_data(
    LuaCharacterHandle speaker,
    const std::string& dialog)
{
    auto& speaker_ref = lua::ref<Character>(speaker);

    if (!talk_setup_variables(speaker_ref))
    {
        return;
    }
    talk_start();

    dialog_start(speaker_ref, dialog);

    talk_end();
}



/**
 * @luadoc choose_ally
 *
 * Prompts the player to choose an ally.
 *
 * @tparam ChooseAllyOperation operation the operation to apply
 * @treturn[1] LuaCharacter
 * @treturn[2] nil
 */
sol::optional<LuaCharacterHandle> Input_choose_ally(const EnumString& operation)
{
    auto operation_value =
        LuaEnums::ControlAllyOperationTable.ensure_from_string(operation);

    auto stat = ctrl_ally(operation_value);
    if (stat == -1)
    {
        return sol::nullopt;
    }

    return lua::handle(cdata[stat]);
}



/**
 * @luadoc enqueue_macro
 *
 * Enqueues an action or a list of actions into the macro action queue. It will
 * be run in order of insertion the next time input is queried.
 *
 * @tparam[1] string action the action to run.
 * @tparam[2] table actions an array of actions to run.
 * @usage Macro.enqueue("north")
 * Macro.enqueue({"east", "wait", "northwest"})
 */
void Input_enqueue_macro(const std::string& action_id)
{
    keybind::macro_action_queue.push(action_id);
}



void Input_enqueue_macro_table(sol::table array)
{
    for (size_t i = 1; i <= array.size(); i++)
    {
        sol::optional<std::string> action = array[i];
        if (action)
        {
            Input_enqueue_macro(*action);
        }
    }
}



/**
 * @luadoc clear_macro_queue
 *
 * Clears any actions that haven't been run yet in the macro action queue.
 */
void Input_clear_macro_queue()
{
    keybind::macro_action_queue.clear();
}



/**
 * @luadoc ignore_keywait
 *
 * Disables input/macro keywait for this frame.
 */
void Input_ignore_keywait()
{
    keybd_wait = 100000;
}



sol::optional<Position>
Input_prompt_position_with_initial_xy(const std::string& message, int x, int y)
{
    elona::tlocinitx = x;
    elona::tlocinity = y;

    txt(message + i18n::space_if_needed());

    int result = elona::target_position(false);

    update_screen();

    if (result == -1)
    {
        return sol::nullopt;
    }

    return Position{tlocx, tlocy};
}



sol::optional<Position> Input_prompt_position(const std::string& message)
{
    return Input_prompt_position_with_initial_xy(message, 0, 0);
}



sol::optional<Position> Input_prompt_position_with_initial(
    const std::string& message,
    const Position& pos)
{
    return Input_prompt_position_with_initial_xy(message, pos.x, pos.y);
}



/**
 * @luadoc any_key_pressed
 *
 * Returns true if any key is pressed.
 *
 * @treturn bool
 */
bool Input_any_key_pressed()
{
    return snail::Input::instance().pressed_keys().size() > 0;
}



void bind(sol::table api_table)
{
    /* clang-format off */

    ELONA_LUA_API_BIND_FUNCTION("yes_no", Input_yes_no);
    ELONA_LUA_API_BIND_FUNCTION("prompt_choice", Input_prompt_choice);
    ELONA_LUA_API_BIND_FUNCTION("prompt_number", Input_prompt_number, Input_prompt_number_with_initial);
    ELONA_LUA_API_BIND_FUNCTION("prompt_text", Input_prompt_text);
    ELONA_LUA_API_BIND_FUNCTION("prompt_dialog", Input_prompt_dialog, Input_prompt_dialog_impress, Input_prompt_dialog_with_chip, Input_prompt_dialog_with_chip_impress);
    ELONA_LUA_API_BIND_FUNCTION("start_dialog", Input_start_dialog, Input_start_dialog_with_data);
    ELONA_LUA_API_BIND_FUNCTION("choose_ally", Input_choose_ally);
    ELONA_LUA_API_BIND_FUNCTION("enqueue_macro", Input_enqueue_macro, Input_enqueue_macro_table);
    ELONA_LUA_API_BIND_FUNCTION("clear_macro_queue", Input_clear_macro_queue);
    ELONA_LUA_API_BIND_FUNCTION("ignore_keywait", Input_ignore_keywait);
    ELONA_LUA_API_BIND_FUNCTION("prompt_position", Input_prompt_position, Input_prompt_position_with_initial, Input_prompt_position_with_initial_xy);
    ELONA_LUA_API_BIND_FUNCTION("any_key_pressed", Input_any_key_pressed);

    /* clang-format on */
}

} // namespace elona::lua::api::modules::module_Input
