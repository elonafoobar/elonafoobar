#pragma once
#include "ui_menu_composite.hpp"

namespace elona
{
namespace ui
{

struct character_sheet_result
{
    character_sheet_result(bool returned_from_portrait)
        : returned_from_portrait(returned_from_portrait)
        , trainer_skill_id(-1)
    {
    }
    character_sheet_result(int trainer_skill_id)
        : returned_from_portrait(false)
        , trainer_skill_id(trainer_skill_id)
    {
    }

    bool returned_from_portrait;
    int trainer_skill_id;
};

enum class feats_result
{
    confirmed,
    pressed_f1,
};

typedef boost::variant<character_sheet_result, feats_result>
    ui_menu_composite_character_result;

class ui_menu_composite_character
    : public ui_menu_composite<ui_menu_composite_character_result>
{
public:
    enum index : size_t
    {
        character_sheet = 0,
        materials = 1,
        feats = 2,
        equipment = 3
    };

    ui_menu_composite_character(size_t selected)
        : ui_menu_composite(selected)
    {
    }

protected:
    virtual void add_menus();
};

} // namespace ui
} // namespace elona
