#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

struct UIMenuCharamakeRaceResult
{
    data::InstanceId race_id;
};



class UIMenuCharamakeRace : public UIMenu<UIMenuCharamakeRaceResult>
{
public:
    UIMenuCharamakeRace()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuCharamakeRace::ResultType> on_key(
        const std::string& key);

private:
    void _draw_race_info(data::InstanceId race_id);
    void _draw_window();
    void _draw_choice(int, const std::string&);
    void _draw_choices();
};

} // namespace ui
} // namespace elona
