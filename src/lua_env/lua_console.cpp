#include "lua_console.hpp"
#include "../config.hpp"
#include "../filesystem.hpp"
#include "../input.hpp"
#include "../macro.hpp"
#include "../snail/application.hpp"
#include "../snail/blend_mode.hpp"
#include "../ui.hpp"
#include "../util.hpp"
#include "../variables.hpp"
#include "lua_env.hpp"
#include <boost/algorithm/string/predicate.hpp>

namespace elona
{
namespace lua
{

lua_console::lua_console(lua_env* lua)
{
    lua_ = lua;
    console_env_ = sol::environment(*(lua_->get_state()),
                                    sol::create,
                                    lua_->get_state()->globals());

    buf_ = buffer(max_lines);
    input_history_ = buffer(max_lines);

    console_env_.set("_API_TABLES", lua->get_api_manager().get_api_table());
    console_env_.set("_MOD_NAME", "console");
    lua_->get_state()->safe_script_file(filesystem::make_preferred_path_in_utf8(
                                            filesystem::dir::mods() / "core"s / "console.lua"),
                                        console_env_);

    sol::table Debug = console_env_["Debug"];
    Debug.set_function("run_script", [this](const std::string& script_file) {
                                         lua_->run_startup_script(script_file);
                                     });
}

void lua_console::print_single_line(const std::string& line)
{
    if (line.size() == 0)
    {
        return;
    }

    int max_chars = max_chars_;
    size_t last_index = 0;
    size_t cut_index = utf8_cut_index(line, max_chars);

    while (cut_index != line.size())
    {
        buf_.push_back(line.substr(last_index, cut_index));
        last_index = cut_index;
        max_chars += max_chars_;
        cut_index = utf8_cut_index(line, max_chars);
    }

    buf_.push_back(line.substr(last_index, cut_index));
}

void lua_console::print(const std::string& message)
{
    if (message.size() == 0)
    {
        return;
    }

    for (std::string line : strutil::split_lines(message))
    {
        print_single_line(line);
    }
}

void lua_console::draw()
{
    if (!enabled_)
    {
        return;
    }

    snail::application::instance().get_renderer().set_blend_mode(
        snail::blend_mode_t::blend);
    snail::application::instance().get_renderer().set_draw_color(
        {17, 17, 65, 192});
    snail::application::instance().get_renderer().fill_rect(
        0,
        0,
        width_,
        height_);

    elona::color(255, 255, 255);

    size_t n = std::min(static_cast<size_t>(max_lines_ - 1), buf_.size());
    int i = 0;
    for(auto it = buf_.end() - n; it < buf_.end(); it++)
    {
        elona::pos(4, char_height_ * i);
        font(inf_mesfont - en * 2);
        mes(*it);

        i++;
    }

    if (focused_)
    {
        elona::pos(4, char_height_ * (max_lines_ - 1));
        font(inf_mesfont - en * 2);
        mes((is_multiline_ ? PROMPT_SECONDARY : PROMPT_PRIMARY) +
            u8" "s + input_ +
            (cursor_visible_ ? u8"|" : ""));
    }

    elona::color(0, 0, 0);
}

inline bool lua_console::is_incomplete_lua_line(const sol::error& error)
{
    return boost::algorithm::ends_with(error.what(), EOF_MARK);
}

bool lua_console::lua_error_handler(const std::string& input, const sol::protected_function_result pfr)
{
    UNUSED(input);

    bool multiline_ended = true;

    if (pfr.status() == sol::call_status::syntax)
    {
        sol::error error = pfr;
        if (is_incomplete_lua_line(error))
        {
            is_multiline_ = true;
            multiline_ended = false;
        }
        else
        {
            std::string mes = lang(u8"エラー: ", u8"Error: ") + error.what();
            print(mes);
        }
    }
    else
    {
        sol::error error = pfr;
        std::string mes = lang(u8"エラー: ", u8"Error: ") + error.what();
        print(mes);
    }

    return multiline_ended;
}

// Returns true if the Lua input is incomplete, and should be
// preserved
bool lua_console::interpret_lua(const std::string& input)
{
    if (input == ""s)
    {
        return is_multiline_;
    }

    bool multiline_ended = true;

    auto ignore_handler = [](lua_State*, sol::protected_function_result pfr) {
                              return pfr;
                          };

    auto handler = [this, &multiline_ended, &input](lua_State*, sol::protected_function_result pfr) {
                       multiline_ended = lua_error_handler(input, pfr);
                       return pfr;
                   };

    // First try prepending "return" to the statement, ignoring errors.
    auto result = lua::lua.get_state()->safe_script(u8"return " + input, console_env_, ignore_handler);

    // If that fails, execute the original statement.
    if (!result.valid())
    {
        result = lua::lua.get_state()->safe_script(input, console_env_, handler);
    }

    if (result.valid())
    {
        console_env_.set("_LAST_RESULT", result.get<sol::object>());
        auto as_string = lua_->get_state()->safe_script("return inspect(_LAST_RESULT)", console_env_);

        if (as_string.valid())
        {
            print(result.get<std::string>());
        }
        else
        {
            print("<Unknown result>");
        }
    }
    else if (multiline_ended)
    {
        print("<Unknown result>");
    }

    update_slight();

    return multiline_ended;
}

void lua_console::grab_input()
{
    bool reenable = false;
    int frame = 0;
    int history_index = -1;

    if (!enabled_)
    {
        enabled_ = true;
        reenable = true;
    }

    focused_ = true;
    cursor_visible_ = true;
    inputlog = "";
    input_ = "";
    notesel(inputlog);
    mesbox(inputlog, true);

    while (focused_)
    {
        ++frame;
        if (frame % config::instance().scrsync == 1)
        {
            ++scrturn;
            label_1420();
        }
        if (frame % 30 == 0)
        {
            cursor_visible_ = !cursor_visible_;
        }

        noteget(input_, 0);

        await(config::instance().wait1);
        key_check(0);

        if (getkey(snail::key::escape))
        {
            focused_ = false;
        }
        else if (getkey(snail::key::up))
        {
            if (input_history_.size() > 0)
            {
                if (history_index == -1
                    || static_cast<size_t>(history_index) < input_history_.size() - 1)
                {
                    ++history_index;
                    input_ = input_history_.at(history_index);
                    inputlog = input_;
                }
            }
        }
        else if (getkey(snail::key::down))
        {
            if (input_history_.size() > 0)
            {
                if (history_index > 0)
                {
                    --history_index;
                    input_ = input_history_.at(history_index);
                    inputlog = input_;
                }
            }
        }
        else if (getkey(snail::key::enter))
        {
            rm_crlf(input_);
            multiline_input_ += input_;
            if (input_ != "")
            {
                print((is_multiline_ ? PROMPT_SECONDARY : PROMPT_PRIMARY) + u8" "s + input_);
                if (interpret_lua(multiline_input_))
                {
                    multiline_input_ = "";
                    is_multiline_ = false;
                }
                else
                {
                    multiline_input_ += "\n";
                }
                input_history_.push_back(input_);
                history_index = -1;
            }
            inputlog = "";
            input_ = "";
        }
    }

    onkey_0();
    just_exited_ = true;

    if (reenable)
    {
        enabled_ = false;
    }
}

} // namespace lua
} // namespace elona
