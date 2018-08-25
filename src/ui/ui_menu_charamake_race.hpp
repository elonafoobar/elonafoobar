#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

struct ui_menu_charamake_race_result
{
    ui_menu_charamake_race_result(std::string race_id, std::string race_name)
        : race_id(race_id)
        , race_name(race_name)
    {
    }

    std::string race_id;
    std::string race_name;
};

class ui_menu_charamake_race : public ui_menu<ui_menu_charamake_race_result>
{
public:
    ui_menu_charamake_race()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<ui_menu_charamake_race::result_type> on_key(
        const std::string& key);
};

} // namespace ui
} // namespace elona
