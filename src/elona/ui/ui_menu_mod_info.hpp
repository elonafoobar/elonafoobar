#pragma once
#include "../lua_env/mod_manifest.hpp"
#include "ui_menu.hpp"
#include "ui_menu_mods.hpp"

namespace snail
{
class Image;
}

namespace elona
{
namespace ui
{
class UIMenuModInfo : public UIMenu<DummyResult>
{
public:
    UIMenuModInfo(const ModDescription& desc)
        : _desc(desc)
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuModInfo::ResultType> on_key(const std::string& key);

    void _build_description();
    void _draw_mod_page();
    void _draw_window();

private:
    const ModDescription& _desc;
    std::vector<std::string> _readme_pages;
    optional<snail::Image> _mod_image;

    size_t _desc_page;
};
} // namespace ui
} // namespace elona
