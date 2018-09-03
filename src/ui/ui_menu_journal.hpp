#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class UIMenuJournal : public UIMenu<dummy_result>
{
public:
    UIMenuJournal()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuJournal::result_type> on_key(
        const std::string& key);
};

} // namespace ui
} // namespace elona
