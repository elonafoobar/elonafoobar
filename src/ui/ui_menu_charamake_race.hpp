#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

struct UIMenuCharamakeRaceResult
{
    UIMenuCharamakeRaceResult(std::string race_id, std::string race_name)
        : race_id(race_id)
        , race_name(race_name)
    {
    }

    std::string race_id;
    std::string race_name;
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
};

} // namespace ui
} // namespace elona
