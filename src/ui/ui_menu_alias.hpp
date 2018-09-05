#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

struct UIMenuAliasResult
{
    std::string alias = "";
    int seed = -1;
};

class UIMenuAlias : public UIMenu<UIMenuAliasResult>
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
    virtual optional<UIMenuAlias::ResultType> on_key(const std::string& key);

private:
    void _set_reroll_aliases();

    int _alias_type;
    int _seed;
};

} // namespace ui
} // namespace elona
