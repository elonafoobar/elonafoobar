#pragma once
#include "../menu.hpp"
#include "ui_menu.hpp"
#include "ui_menu_composite_character.hpp"

namespace elona
{
namespace ui
{

class ui_menu_character_sheet
    : public ui_menu<ui_menu_composite_character_result>
{
public:
    ui_menu_character_sheet(character_sheet_operation operation)
        : _operation(operation)
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<ui_menu_character_sheet::result_type> on_key(
        const std::string& key);

private:
    character_sheet_operation _operation;

    bool _returned_from_portrait = false;
    int _cs_buff = 0;
    int _cs_buffmax = 0;
};

} // namespace ui
} // namespace elona
