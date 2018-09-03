#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

struct ui_menu_alias_result
{
    std::string alias = "";
    int seed = -1;
};

class UIMenuAlias : public UIMenu<ui_menu_alias_result>
{
public:
    UIMenuAlias(int alias_type)
        : _alias_type(alias_type)
    {
        _seed = 10500;
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuAlias::result_type> on_key(const std::string& key);

private:
    void _set_reroll_aliases();

    int _alias_type;
    int _seed;
};

} // namespace ui
} // namespace elona
