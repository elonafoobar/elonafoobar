#pragma once
#include "ui_menu.hpp"

namespace elona
{
class ConfigMenu;

namespace ui
{

class UIMenuConfig : public UIMenu<int>
{
public:
    UIMenuConfig(ConfigMenu& menu, int submenu_index)
        : _menu(menu)
        , _submenu_index(submenu_index)
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuConfig::ResultType> on_key(const std::string& key);

private:
    void _draw_background();
    void _draw_window(const std::string&, int, int);
    void _draw_deco();
    void _draw_keys(bool);
    void _draw_arrows(int);
    void _draw_items(ConfigMenu&, bool);

    ConfigMenu& _menu;
    int _submenu_index;
};

} // namespace ui
} // namespace elona
