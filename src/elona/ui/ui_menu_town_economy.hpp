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
    int _city;
};

} // namespace ui
} // namespace elona
