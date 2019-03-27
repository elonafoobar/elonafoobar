#include "lua_api_gui.hpp"
#include "../../audio.hpp"
#include "../../message.hpp"
#include "../../quest.hpp"
#include "../../ui.hpp"
#include "../enums/enums.hpp"
#include "../handle_manager.hpp"

namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Prints some text in the HUD message window.
 * @tparam string message the message to print
 */
void LuaApiGUI::txt(const std::string& message)
{
    elona::txt(message);
}

/**
 * @luadoc txt
 *
 * Prints some text in the HUD message window.
 * @tparam string message the message to print
 * @tparam Color color of the message
 */
void LuaApiGUI::txt_txtef(const std::string& message, const EnumString& color)
{
    auto color_value = LuaEnums::ColorIndexTable.ensure_from_string(color);
    elona::Message::instance().txtef(color_value);
    elona::txt(message);
}

/**
 * @luadoc
 *
 * Starts a new message line in the HUD message window.
 */
void LuaApiGUI::txtnew()
{
    elona::Message::instance().linebreak();
}

/**
 * @luadoc
 *
 * Plays a sound.
 * @tparam string sound_id The sound, of type core.sound
 */
void LuaApiGUI::play_sound(const std::string& sound_id)
{
    elona::snd(SharedId(sound_id));
}

/**
 * @luadoc
 *
 * Displays the journal update message.
 */
void LuaApiGUI::show_journal_update_message()
{
    quest_update_journal_msg();
}

/**
 * @luadoc
 *
 * Fades out the screen, then fades it in.
 */
void LuaApiGUI::fade_out()
{
    elona::update_screen();
    elona::fade_out();
    gsel(0);
}

void LuaApiGUI::update_screen(sol::optional<bool> redraw)
{
    bool redraw_value = redraw.value_or(true);
    int screenupdatebk = elona::screenupdate;
    elona::screenupdate = redraw_value ? 0 : -1;

    elona::update_screen();

    elona::screenupdate = screenupdatebk;
}

void LuaApiGUI::bind(sol::table& api_table)
{
    api_table.set_function(
        "txt", sol::overload(LuaApiGUI::txt, LuaApiGUI::txt_txtef));
    LUA_API_BIND_FUNCTION(api_table, LuaApiGUI, txtnew);
    LUA_API_BIND_FUNCTION(api_table, LuaApiGUI, play_sound);
    LUA_API_BIND_FUNCTION(api_table, LuaApiGUI, show_journal_update_message);
    LUA_API_BIND_FUNCTION(api_table, LuaApiGUI, fade_out);
    LUA_API_BIND_FUNCTION(api_table, LuaApiGUI, update_screen);
}

} // namespace lua
} // namespace elona
