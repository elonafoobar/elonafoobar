#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class UIMenuAdventurers : public UIMenu<dummy_result>
{
public:
    UIMenuAdventurers()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuAdventurers::result_type> on_key(
        const std::string& key);
};

} // namespace ui
} // namespace elona
