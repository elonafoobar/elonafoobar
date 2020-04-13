#pragma once

#include "../optional.hpp"
#include "ui_menu.hpp"



namespace elona
{

struct Character;
enum class ControlAllyOperation;



namespace snail
{

struct Color;

}



namespace ui
{

class UIMenuCtrlAlly : public UIMenu<int>
{
public:
    UIMenuCtrlAlly(
        ControlAllyOperation operation,
        optional_ref<Character> gene_engineering_original_character)
        : _operation(operation)
        , _gene_engineering_original_character(
              gene_engineering_original_character)
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuCtrlAlly::ResultType> on_key(const std::string& key);

private:
    bool _should_display_ally(const Character&);
    void _insert_proceed_entry();
    void _on_init_finish();

    std::string _get_ally_name(const Character&);
    std::string _get_ally_info(const Character&);
    std::string _get_general_ally_info(const Character&);
    std::string _get_specific_ally_info(const Character&);
    snail::Color _draw_get_color(const Character&);

    void _draw_ally_list_entry(int, const Character&);
    void _draw_ally_name(int, const Character&);
    void _draw_ally_info(int, const Character&);

    void _draw_ally_list_entry_sell(int, const Character&);
    std::string _modify_ally_info_gene_engineer(
        const Character&,
        const std::string&);
    void _draw_info_pet_arena(const Character&, std::string&);

    optional<UIMenuCtrlAlly::Result> _select_gene_engineer(int);
    optional<UIMenuCtrlAlly::Result> _select_pet_arena(int);
    void _update_investigate_and_gene_engineer(bool);

    ControlAllyOperation _operation;
    optional_ref<Character> _gene_engineering_original_character;
};

} // namespace ui

} // namespace elona
