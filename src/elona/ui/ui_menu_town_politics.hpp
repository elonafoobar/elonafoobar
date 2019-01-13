#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class UIMenuTownPolitics : public UIMenu<DummyResult>
{
public:
    UIMenuTownPolitics()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuTownPolitics::ResultType> on_key(
        const std::string& key);

private:
    void _draw_window();
    void _draw_key(int);
    void _draw_keys();
    void _draw_list_entries();
};

} // namespace ui
} // namespace elona
