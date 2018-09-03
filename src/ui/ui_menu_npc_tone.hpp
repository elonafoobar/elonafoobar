#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class UIMenuNPCTone : public UIMenu<std::string>
{
public:
    UIMenuNPCTone()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuNPCTone::result_type> on_key(
        const std::string& key);
};

} // namespace ui
} // namespace elona
