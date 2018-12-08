#pragma once
#include "ui_menu.hpp"

namespace elona
{
class DialogData;

namespace ui
{

class UIMenuDialog : public UIMenu<size_t>
{
public:
    UIMenuDialog(DialogData& the_dialog, bool is_cancelable)
        : _dialog(the_dialog)
        , _is_cancelable(is_cancelable)
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuDialog::ResultType> on_key(const std::string& key);

private:
    DialogData& _dialog;
    bool _is_cancelable;

    std::vector<std::string> _choice_text;
};

} // namespace ui
} // namespace elona
