#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class UIMenuScene : public UIMenu<DummyResult>
{
public:
    UIMenuScene()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuScene::ResultType> on_key(const std::string& key);

private:
    void _draw_window();
    void _draw_key(int);
    void _draw_keys();
    void _draw_title();
    void _draw_list_entry(int, int);
    void _draw_list_entries();
    void _draw_more();
};

} // namespace ui
} // namespace elona
