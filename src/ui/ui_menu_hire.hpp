#pragma once
#include "../menu.hpp"
#include "ui_menu.hpp"

namespace elona
{
class character;

namespace ui
{

class ui_menu_hire : public ui_menu<int>
{
public:
    ui_menu_hire(hire_operation operation)
        : _operation(operation)
    {
    }

protected:
    virtual void init();
    virtual void update();
    virtual void draw();
    virtual optional<ui_menu_hire::result_type> on_key(const std::string& key);

private:
    bool _should_display_chara(const character& chara);
    void _populate_list();

    void _draw_topic();
    void _draw_window();
    void _draw_list_entries();
    void _draw_list_entry(int cnt, const character& chara);
    void _draw_list_entry_cost(int cnt, const character& chara);

    hire_operation _operation;
};

} // namespace ui
} // namespace elona
