#include "ui_menu_mod_info.hpp"

#include "../../util/fileutil.hpp"
#include "../../util/strutil.hpp"
#include "../audio.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"
#include "../lua_env/mod_manager.hpp"



namespace elona
{
namespace ui
{

static int _wrap_text(std::string& text, int max_line_length)
{
    std::string rest{text};
    text.clear();
    int n{};

    while (1)
    {
        const auto len = rest.size();
        if (int(len) < max_line_length)
        {
            text += rest;
            return n;
        }
        size_t byte_length = 0;
        size_t width_length = 0;
        while (width_length <= len)
        {
            const auto bytes = strutil::byte_count(rest[byte_length]);
            const auto char_width = bytes == 1 ? 1 : 2;

            byte_length += bytes;
            width_length += char_width;

            if (int(width_length) > max_line_length)
            {
                text += rest.substr(0, byte_length) + '\n';
                ++n;
                if (rest.size() > byte_length)
                {
                    rest = rest.substr(byte_length);
                }
                else
                {
                    rest = "";
                }
                break;
            }
        }
    }
}

bool UIMenuModInfo::init()
{
    key_list(0) = key_enter;
    keyrange = 0;
    pagesize = 1;
    listmax = 0;

    _build_description();

    return true;
}

void UIMenuModInfo::_build_description()
{
    _readme_pages.clear();
    _desc_page = 0;

    auto readme_path =
        filesystem::dir::for_mod(_desc.manifest.id) / "README.txt";
    if (!fs::exists(readme_path))
    {
        // TODO
        _readme_pages.push_back(
            i18n::s.get("core.locale.main_menu.mods.no_readme"));
        return;
    }

    std::vector<std::string> description_lines;
    range::copy(
        fileutil::read_by_line(readme_path),
        std::back_inserter(description_lines));

    if (description_lines.empty())
    {
        // TODO
        _readme_pages.push_back(
            i18n::s.get("core.locale.main_menu.mods.no_readme"));
        return;
    }

    const size_t text_width = 90 - 2;
    constexpr size_t lines_per_page = 15;

    for (auto&& line : description_lines)
    {
        _wrap_text(line, text_width);
    }
    size_t line_count = 0;
    for (const auto& lines : description_lines)
    {
        if (lines == "")
        {
            _readme_pages.back() += '\n';
        }
        for (const auto& line : strutil::split_lines(lines))
        {
            if (line_count == 0)
            {
                _readme_pages.push_back(line + '\n');
            }
            else
            {
                _readme_pages.back() += line + '\n';
            }
            ++line_count;
            if (line_count == lines_per_page)
            {
                line_count = 0;
            }
        }
    }

    listmax = _readme_pages.size();
}



void UIMenuModInfo::update()
{
    pagemax = (listmax - 1) / pagesize;
    if (page < 0)
        page = pagemax;
    else if (page > pagemax)
        page = 0;
}



void UIMenuModInfo::_draw_mod_page()
{
    display_topic(
        i18n::s.get("core.locale.main_menu.mods.info.title"), wx + 30, wy + 36);

    int y = wy + 60;

    gmes(
        "<b>" + i18n::s.get("core.locale.main_menu.mods.info.id") + ":<def> " +
            _desc.manifest.id,
        wx + 30,
        y,
        488,
        {30, 30, 30},
        false);
    gmes(
        "<b>" + i18n::s.get("core.locale.main_menu.mods.info.author") +
            ":<def> " + _desc.manifest.author,
        wx + 30,
        y + 16,
        488,
        {30, 30, 30},
        false);
    gmes(
        "<b>" + i18n::s.get("core.locale.main_menu.mods.info.version") +
            ":<def> " + _desc.manifest.version.to_string(),
        wx + 30,
        y + 32,
        488,
        {30, 30, 30},
        false);
    gmes(
        "<b>" + i18n::s.get("core.locale.main_menu.mods.info.description") +
            ":<def> " + _desc.manifest.description,
        wx + 30,
        y + 48,
        488,
        {30, 30, 30},
        false);

    window2(wx + 30 + 498 - 4, y - 36 - 4, 128 + 8, 128 + 8, 1, 1);
    boxf(wx + 30 + 498, y - 36, 128, 128, {0, 0, 0});
    mes(wx + 30 + 498 + 32 + 6, y - 36 + 64 - 7, "(image)", {255, 255, 255});

    display_topic("README", wx + 30, wy + 160);

    font(14 - en * 2);
    mes(wx + 30, wy + 184, _readme_pages.at(page));
}



void UIMenuModInfo::_draw_window()
{
    ui_display_window(
        _desc.manifest.name,
        strhint2 + strhint3b,
        (windoww - 700) / 2 + inf_screenx,
        winposy(500) - 10,
        700,
        500);
}



void UIMenuModInfo::draw()
{
    _draw_window();
    _draw_mod_page();
}



optional<UIMenuModInfo::ResultType> UIMenuModInfo::on_key(
    const std::string& action)
{
    // Page changes
    if (action == "next_page")
    {
        if (pagemax != 0)
        {
            snd("core.pop1");
            page++;
            set_reupdate();
        }
    }
    if (action == "previous_page")
    {
        if (pagemax != 0)
        {
            snd("core.pop1");
            page--;
            set_reupdate();
        }
    }

    // Closing menu
    if (action == "cancel")
    {
        return UIMenuModInfo::ResultType::finish();
    }
    return none;
}

} // namespace ui
} // namespace elona
