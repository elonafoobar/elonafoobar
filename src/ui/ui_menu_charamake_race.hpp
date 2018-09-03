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

class UIMenuCharamakeRace : public UIMenu<ui_menu_charamake_race_result>
{
public:
    UIMenuCharamakeRace()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuCharamakeRace::result_type> on_key(
        const std::string& key);
};

} // namespace ui
} // namespace elona
