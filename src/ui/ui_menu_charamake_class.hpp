#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class ui_menu_charamake_class : public ui_menu<std::string>
{
public:
    ui_menu_charamake_class(const std::string& race)
        : _race(race)
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<ui_menu_charamake_class::result_type> on_key(
        const std::string& key);

private:
    std::string _race;
};

} // namespace ui
} // namespace elona
