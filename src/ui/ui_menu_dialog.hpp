#pragma once
#include "../dialog/dialog.hpp"
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class ui_menu_dialog : public ui_menu<size_t>
{
public:
    ui_menu_dialog(dialog_data& the_dialog, bool is_cancelable)
        : _dialog(the_dialog)
        , _is_cancelable(is_cancelable)
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<ui_menu_dialog::result_type> on_key(
        const std::string& key);

private:
    dialog_data& _dialog;
    bool _is_cancelable;

    std::vector<std::string> _choice_text;
};

} // namespace ui
} // namespace elona
