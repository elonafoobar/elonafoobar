#pragma once
#include "ui_menu.hpp"

namespace elona
{
struct Character;

namespace ui
{

class UIMenuAdventurers : public UIMenu<DummyResult>
{
public:
    UIMenuAdventurers()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuAdventurers::ResultType> on_key(
        const std::string& key);

private:
    void _draw_window();
    void _draw_key(int);
    void _draw_keys();
    void _draw_list_entry_name(int, const Character&);
    void _draw_list_entry_level(int, const Character&);
    void _draw_list_entry_map_name(int, const Character&);
    void _draw_list_entry(int, const Character&, int);
    void _draw_list_entries();
};

} // namespace ui
} // namespace elona
