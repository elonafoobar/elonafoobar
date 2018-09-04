#pragma once
#include "ui_menu.hpp"
namespace elona
{
namespace ui
{
class UIMenuGameHelp : public UIMenu<DummyResult>
{
public:
    UIMenuGameHelp()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuGameHelp::ResultType> on_key(
        const std::string& key);

    void _remove_parenthesis_around_keys();
    void _update_key_list();
    void _update_regular_pages();
    void _draw_navigation_menu();
    void _draw_background_vignette(int id);

private:
    int _book_id;
};
} // namespace ui
} // namespace elona