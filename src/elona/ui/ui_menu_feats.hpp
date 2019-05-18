#pragma once
#include "ui_menu.hpp"
#include "ui_menu_composite_character.hpp"

namespace elona
{
namespace ui
{

class UIMenuFeats : public UIMenu<UIMenuCompositeCharacterResult>
{
public:
    enum class Operation
    {
        normal,
        character_making
    };

public:
    UIMenuFeats(Operation operation)
        : _operation(operation)
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuFeats::ResultType> on_key(const std::string& key);

private:
    void _draw_window_background(bool);
    void _draw_window_deco();
    void _draw_window(bool);
    void _draw_key(int, int);
    void _draw_keys();
    void _draw_acquirable_trait_number(int);
    void _draw_single_list_entry_name(int, const snail::Color&);
    void _draw_single_list_entry_text(
        int,
        bool,
        const snail::Color&,
        const std::string&);
    void _draw_single_list_entry(int, int, int, const std::string&);
    void _draw_list_entries();

    Operation _operation;
};

} // namespace ui
} // namespace elona
