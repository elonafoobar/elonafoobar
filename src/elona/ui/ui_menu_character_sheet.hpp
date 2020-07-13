#pragma once
#include "../menu.hpp"
#include "ui_menu.hpp"
#include "ui_menu_composite_character.hpp"

namespace elona
{
namespace ui
{

class UIMenuCharacterSheet : public UIMenu<UIMenuCompositeCharacterResult>
{
public:
    UIMenuCharacterSheet(Character& chara, CharacterSheetOperation operation)
        : _chara(chara)
        , _operation(operation)
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuCharacterSheet::ResultType> on_key(
        const std::string& key);

private:
    void _draw_title(CharacterSheetOperation);
    void _draw_window(bool);
    void _draw_first_page_topics();
    void _draw_portrait_face();
    void _draw_portrait_sprite();
    void _draw_first_page_portrait();
    void _draw_first_page_text_exp();
    void _draw_first_page_text_personal();
    void _draw_first_page_text_attribute();
    void _draw_first_page_text_time();
    void _draw_first_page_text_weight();
    void _draw_first_page_text_level();
    void _draw_first_page_text_name();
    void _draw_attribute_level(int);
    void _draw_attribute_potential(int);
    void _draw_attribute(int);
    void _draw_first_page_attributes();
    void _draw_first_page_weapon_info();
    void _draw_first_page_text_fame();
    void _draw_first_page_stats_fame();
    void _draw_first_page_stats_time();
    void _draw_first_page_stats_weight();
    void _draw_first_page_buffs(int&, int&);
    void _draw_first_page(int&, int&);
    void _draw_other_pages_topics();
    void _draw_other_pages_keys();
    void _draw_other_pages();
    void _draw_skill_icon(int, int);
    void _draw_skill_name(int, int);
    void _draw_skill_power(int, int);
    void _draw_skill_desc(int, int);
    void _draw_skill_train_cost(int, int, bool);
    void _draw_skill_enchantment_power(int, int);
    void _draw_skill_entry(int, int, CharacterSheetOperation);
    void _draw_text_entry(int, const std::string&);
    void _draw_other_page_single_list_entry(
        int,
        int,
        const std::string&,
        CharacterSheetOperation);
    void _draw_other_page_list_entries(CharacterSheetOperation);

    Character& _chara;
    CharacterSheetOperation _operation;

    bool _returned_from_portrait = false;
    int _cs_buff = 0;
    int _cs_buffmax = 0;
};

} // namespace ui
} // namespace elona
