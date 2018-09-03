#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class UIMenuTownChart : public UIMenu<dummy_result>
{
public:
    UIMenuTownChart()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuTownChart::result_type> on_key(
        const std::string& key);

private:
    int _city;
};

} // namespace ui
} // namespace elona
