#include "module_GUI.hpp"

#include "../../../audio.hpp"
#include "../../../message.hpp"
#include "../../../quest.hpp"
#include "../../../ui.hpp"
#include "../../enums/enums.hpp"



namespace elona::lua::api::modules::module_GUI
{

/**
 * @luadoc txt
 *
 * Prints some text in the HUD message window.
 *
 * @tparam string message the message to print
 */
void GUI_txt(const std::string& message)
{
    elona::txt(message);
}



/**
 * @luadoc txt
 *
 * Prints some text in the HUD message window.
 *
 * @tparam string message the message to print
 * @tparam Color color of the message
 */
void GUI_txt_txtef(const std::string& message, const EnumString& color)
{
    auto color_value = LuaEnums::ColorIndexTable.ensure_from_string(color);
    elona::Message::instance().txtef(color_value);
    elona::txt(message);
}



/**
 * @luadoc txtnew
 *
 * Starts a new message line in the HUD message window.
 */
void GUI_txtnew()
{
    elona::Message::instance().linebreak();
}



/**
 * @luadoc play_sound
 *
 * Plays a sound.
 *
 * @tparam string sound_id The sound, of type core.sound
 */
void GUI_play_sound(const std::string& sound_id)
{
    elona::snd(data::InstanceId{sound_id});
}



/**
 * @luadoc show_journal_update_message
 *
 * Displays the journal update message.
 */
void GUI_show_journal_update_message()
{
    quest_update_journal_msg();
}



/**
 * @luadoc fade_out
 *
 * Fades out the screen, then fades it in.
 */
void GUI_fade_out()
{
    update_screen();
    elona::fade_out();
    gsel(0);
}



void bind(sol::table api_table)
{
    /* clang-format off */

    ELONA_LUA_API_BIND_FUNCTION("txt", GUI_txt, GUI_txt_txtef);
    ELONA_LUA_API_BIND_FUNCTION("txtnew", GUI_txtnew);
    ELONA_LUA_API_BIND_FUNCTION("play_sound", GUI_play_sound);
    ELONA_LUA_API_BIND_FUNCTION("show_journal_update_message", GUI_show_journal_update_message);
    ELONA_LUA_API_BIND_FUNCTION("fade_out", GUI_fade_out);

    /* clang-format on */
}

} // namespace elona::lua::api::modules::module_GUI
