#include <boost/process/spawn.hpp>

#include "elona/filesystem.hpp"
#include "elona/log.hpp"
#include "elona/profile/profile_manager.hpp"
#include "snail/application.hpp"
#include "snail/input.hpp"
#include "util/natural_order_comparator.hpp"
#include "util/range.hpp"
#include "util/tinyargparser.hpp"
#include "version.hpp"

using namespace elona;



constexpr snail::Color bg_color{160, 145, 128};
constexpr snail::Color fg_color{71, 64, 55};
constexpr int screen_width = 400;
constexpr int screen_height = 560;
constexpr int frame_width = screen_width - 100;
constexpr int frame_height = frame_width * screen_height / screen_width;



int cursor = 0;
std::vector<std::string> profiles;



std::vector<std::string> list_profiles()
{
    std::vector<std::string> result;
    for (const auto& entry :
         filesystem::glob_dirs(filesystem::dirs::profile_root()))
    {
        const auto id = filepathutil::to_utf8_path(entry.path().filename());
        if (profile::is_valid_id(id))
        {
            result.push_back(id);
        }
    }
    range::sort(result, lib::natural_order_comparator{});
    result.push_back(u8"+ NEW");
    return result;
}



void draw(snail::Renderer& r)
{
    r.clear();

    r.set_draw_color(bg_color);
    r.fill_rect(0, 0, screen_width, screen_height);

    r.set_draw_color(fg_color);

    const auto x1 = (screen_width - frame_width) / 2;
    const auto y1 = x1;
    const auto x2 = screen_width - x1 - 1;
    const auto y2 = y1;
    const auto x3 = x2;
    const auto y3 = y1 + frame_height - 1;
    const auto x4 = x1;
    const auto y4 = y3;

    r.render_line(x1, y1, x2, y2);
    r.render_line(x2, y2, x3, y3);
    r.render_line(x3, y3, x4, y4);
    r.render_line(x4, y4, x1, y1);

    r.render_line(x1 - 1, y1 - 1, x2 + 1, y2 - 1);
    r.render_line(x2 + 1, y2 - 1, x3 + 1, y3 + 1);
    r.render_line(x3 + 1, y3 + 1, x4 - 1, y4 + 1);
    r.render_line(x4 - 1, y4 + 1, x1 - 1, y1 - 1);

    for (size_t i = 0; i < profiles.size(); ++i)
    {
        auto x = x1 + 25 + 15;
        auto y = y1 + 25 + i * 20;
        if (static_cast<int>(i) == cursor)
        {
            r.render_text(u8">", x - 20, y, fg_color);
        }
        r.render_text(profiles[i], x, y, fg_color);
    }

    r.render_text(u8"UP/DOWN: Select", x1 + 10, y3 + 20, fg_color);
    r.render_text(u8"ENTER/SPACE: Launch Game", x1 + 10, y3 + 40, fg_color);

    r.present();
}



bool handle_event()
{
    auto& i = snail::Input::instance();

    if (i.was_pressed_just_now(snail::Key::up))
    {
        cursor -= 1;
        if (cursor < 0)
        {
            cursor = static_cast<int>(profiles.size()) - 1;
        }
    }
    else if (i.was_pressed_just_now(snail::Key::down))
    {
        cursor += 1;
        if (cursor >= static_cast<int>(profiles.size()))
        {
            cursor = 0;
        }
    }
    else if (
        i.was_pressed_just_now(snail::Key::enter) ||
        i.was_pressed_just_now(snail::Key::space))
    {
        if (cursor == static_cast<int>(profiles.size()) - 1)
        {
            profile::ProfileManager::instance().create(
                profile::ProfileManager::instance().generate_new_id());
            profiles = list_profiles();
            cursor = static_cast<int>(profiles.size()) - 1;
        }
        else
        {
            const std::vector<fs::path> filenames{
                "Elona foobar.exe",
                "Elona foobar",
                "Elona_foobar.exe",
                "Elona_foobar",
            };
            for (const auto& filename : filenames)
            {
                const auto path = filesystem::dirs::exe() / filename;
                if (fs::exists(path))
                {
                    boost::process::spawn(
                        path,
                        u8"--profile=" + profiles[static_cast<size_t>(cursor)]);
                }
            }
            return false;
        }
    }

    return true;
}



int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    log::Logger::instance().init();

    profiles = list_profiles();

    auto& app = snail::Application::instance();
    app.initialize(u8"Elona foobar Launcher v" + latest_version.short_string());
    app.set_window_size(screen_width, screen_height);
    app.set_call_redraw(false);

    app.get_renderer().enable_blended_text_rendering();
    snail::Font font{
        filesystem::path("font") / "Bitstream Sans Vera Mono" /
            "Bitstream Sans Vera Mono.ttf",
        16};
    app.get_renderer().set_font(font);

    while (true)
    {
        app.proc_event();
        draw(app.get_renderer());
        if (!handle_event())
        {
            break;
        }
        app.wait(30);
    }

    return 0;
}
