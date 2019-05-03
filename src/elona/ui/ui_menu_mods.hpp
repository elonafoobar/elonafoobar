#pragma once
#include "../lua_env/mod_manifest.hpp"
#include "ui_menu.hpp"
namespace elona
{
namespace ui
{
class UIMenuMods : public UIMenu<DummyResult>
{
public:
    struct ModDescription
    {
        std::string display_name;
        lua::ModManifest manifest;
        bool enabled;
    };

    UIMenuMods()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuMods::ResultType> on_key(const std::string& key);

    optional<ModDescription> _find_enabled_mod(const std::string& name);
    void _draw_mod_page();
    void _draw_window();
    void _draw_navigation_menu();
    void _draw_background_vignette(int id, int type);

private:
    std::vector<ModDescription> mod_descriptions;

    bool _redraw;
};
} // namespace ui
} // namespace elona
