#pragma once
#include "ui_menu_composite.hpp"

namespace elona
{
namespace ui
{

struct CharacterSheetResult
{
    CharacterSheetResult(bool returned_from_portrait)
        : returned_from_portrait(returned_from_portrait)
        , trainer_skill_id(none)
    {
    }
    CharacterSheetResult(int trainer_skill_id)
        : returned_from_portrait(false)
        , trainer_skill_id(trainer_skill_id)
    {
    }

    bool returned_from_portrait;
    optional<int> trainer_skill_id;
};

enum class FeatsResult
{
    confirmed,
    pressed_f1,
};

typedef boost::variant<CharacterSheetResult, FeatsResult>
    UIMenuCompositeCharacterResult;

class UIMenuCompositeCharacter
    : public UIMenuComposite<UIMenuCompositeCharacterResult>
{
public:
    enum Index : size_t
    {
        character_sheet = 0,
        equipment = 1,
        feats = 2,
        materials = 3,
    };

    UIMenuCompositeCharacter(size_t selected)
        : UIMenuComposite(selected)
    {
    }

protected:
    virtual void add_menus();
};

} // namespace ui
} // namespace elona
