#pragma once
#include "ui_menu.hpp"
namespace elona
{
namespace ui
{
class ui_menu_game_help : public ui_menu<dummy_result>
{
public:
    ui_menu_game_help()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<ui_menu_game_help::result_type> on_key(
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