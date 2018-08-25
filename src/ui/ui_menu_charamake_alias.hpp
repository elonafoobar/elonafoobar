#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class ui_menu_charamake_alias : public ui_menu<std::string>
{
public:
    ui_menu_charamake_alias(
        optional<std::string> previous_alias,
        elona_vector1<int>& locked_aliases)
        : _previous_alias(previous_alias)
        , _locked_aliases(locked_aliases)
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<ui_menu_charamake_alias::result_type> on_key(
        const std::string& key);

private:
    void _reroll_aliases();

    optional<std::string> _previous_alias;
    elona_vector1<int>& _locked_aliases;

    bool _redraw_aliases = false;
};

} // namespace ui
} // namespace elona
