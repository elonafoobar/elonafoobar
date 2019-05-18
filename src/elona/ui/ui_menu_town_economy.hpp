#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class UIMenuTownEconomy : public UIMenu<DummyResult>
{
public:
    UIMenuTownEconomy()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuTownEconomy::ResultType> on_key(
        const std::string& key);

private:
    void _draw_window();
    void _draw_economy_info(int);
    void _draw_economy_details();

    int _city;
};

} // namespace ui
} // namespace elona
