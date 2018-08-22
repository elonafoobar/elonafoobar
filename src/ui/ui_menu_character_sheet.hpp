#pragma once
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
    ui_menu_character_sheet(
        int csctrl,
        bool returned_from_portrait,
        bool is_character_making)
        : _csctrl(csctrl)
        , _returned_from_portrait(returned_from_portrait)
        , _is_character_making(is_character_making)
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<ui_menu_character_sheet::result_type> on_key(
        const std::string& key);

private:
    int _csctrl;
    bool _returned_from_portrait;
    bool _is_character_making;


    int _cs_buff = 0;
    int _cs_buffmax = 0;
};

} // namespace ui
} // namespace elona
