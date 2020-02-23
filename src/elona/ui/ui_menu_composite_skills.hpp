#pragma once

#include <variant>
#include "ui_menu_composite.hpp"



namespace elona
{
namespace ui
{

struct UIMenuSkillsResult
{
    int effect_id;
};



struct UIMenuSpellsResult
{
    int effect_id;
};



using UIMenuCompositeSkillsResult =
    std::variant<UIMenuSkillsResult, UIMenuSpellsResult>;



class UIMenuCompositeSkills
    : public UIMenuComposite<UIMenuCompositeSkillsResult>
{
public:
    enum class Index : size_t
    {
        spells = 0,
        skills = 1
    };

    UIMenuCompositeSkills(size_t selected)
        : UIMenuComposite(selected)
    {
    }

protected:
    virtual void add_menus();
};

} // namespace ui
} // namespace elona
