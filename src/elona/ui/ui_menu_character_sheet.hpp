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
    UIMenuCharacterSheet(CharacterSheetOperation operation)
        : _operation(operation)
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuCharacterSheet::ResultType> on_key(
        const std::string& key);

private:
    CharacterSheetOperation _operation;

    bool _returned_from_portrait = false;
    int _cs_buff = 0;
    int _cs_buffmax = 0;
};

} // namespace ui
} // namespace elona
