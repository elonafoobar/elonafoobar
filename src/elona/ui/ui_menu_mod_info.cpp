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

bool UIMenuModInfo::init()
{
    key_list(0) = keybind_get_bound_key_name("enter");
    keyrange = 0;
    pagesize = 1;
    listmax = 0;

    _build_description();

    return true;
}



optional<fs::path> UIMenuModInfo::_find_readme(const fs::path& mod_dir)
{
    for (const auto& filename :
         {"README.md", "README.markdown", "README.txt", "README"})
    {
        const auto path = mod_dir / fs::u8path(filename);
        if (fs::exists(path))
        {
            return path;
        }
    }
    return none;
}



void UIMenuModInfo::_build_description()
{
    _readme_pages.clear();
    _desc_page = 0;

    auto readme_path = _find_readme(
        filesystem::dirs::for_mod(_desc.manifest.id, _desc.manifest.version));

    if (!readme_path)
    {
        _readme_pages.push_back(
            i18n::s.get("core.main_menu.mod_list.no_readme"));
    }
    else
    {
        std::vector<std::string> description_lines;
        range::copy(
            fileutil::read_by_line(*readme_path),
            std::back_inserter(description_lines));

        const size_t text_width = 90 - 2;
        constexpr size_t lines_per_page = 15;

        for (auto&& line : description_lines)
        {
            strutil::wrap_text(line, text_width);
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

        if (description_lines.empty())
        {
            _readme_pages.push_back(
                i18n::s.get("core.main_menu.mod_list.no_readme"));
        }
    }

    listmax = _readme_pages.size();

    auto image_path =
        filesystem::dirs::for_mod(_desc.manifest.id, _desc.manifest.version) /
        "image.png";
    if (fs::exists(image_path))
    {
        _mod_image = snail::Image{image_path};
    }
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
        i18n::s.get("core.main_menu.mod_list.info.title"), wx + 30, wy + 36);

    int y = wy + 60;

    gmes(
        "<b>" + i18n::s.get("core.main_menu.mod_list.info.id") + ":<def> " +
            _desc.manifest.id,
        wx + 30,
        y,
        570,
        {30, 30, 30},
        false);
    gmes(
        "<b>" + i18n::s.get("core.main_menu.mod_list.info.author") + ":<def> " +
            _desc.manifest.authors,
        wx + 30,
        y + 16,
        570,
        {30, 30, 30},
        false);
    gmes(
        "<b>" + i18n::s.get("core.main_menu.mod_list.info.version") +
            ":<def> " + _desc.manifest.version.to_string(),
        wx + 30,
        y + 32,
        570,
        {30, 30, 30},
        false);
    gmes(
        "<b>" + i18n::s.get("core.main_menu.mod_list.info.description") +
            ":<def> " +
            _desc.manifest.description.localize(g_config.language()),
        wx + 30,
        y + 48,
        570,
        {30, 30, 30},
        false);

    auto image_x = wx + 30 + 578;
    auto image_y = wy + 30;
    window2(image_x - 4, image_y - 4, 48 + 8, 48 + 8, 1, 1);

    if (_mod_image)
    {
        auto& renderer = snail::Application::instance().get_renderer();
        renderer.render_image(*_mod_image, image_x, image_y, 48, 48);
    }

    display_topic("README", wx + 30, wy + 160);

    font(14 - en * 2);
    mes(wx + 30, wy + 184, _readme_pages.at(page));
}



void UIMenuModInfo::_draw_window()
{
    ui_display_window(
        _desc.manifest.name.localize(g_config.language()),
        strhint2 + strhint3b,
        (windoww - 700) / 2 + inf_screenx,
        winposy(480, 1),
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
