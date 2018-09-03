#pragma once
#include "../menu.hpp"
#include "ui_menu.hpp"

namespace elona
{
struct Character;

namespace ui
{

class UIMenuHire : public UIMenu<int>
{
public:
    UIMenuHire(HireOperation operation)
        : _operation(operation)
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuHire::result_type> on_key(const std::string& key);

private:
    bool _should_display_chara(const Character& chara);
    void _populate_list();

    void _draw_topic();
    void _draw_window();
    void _draw_list_entries();
    void _draw_list_entry(int cnt, const Character& chara);
    void _draw_list_entry_cost(int cnt, const Character& chara);

    HireOperation _operation;
};

} // namespace ui
} // namespace elona
