#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class UIMenuMessageLog : public UIMenu<DummyResult>
{
public:
    UIMenuMessageLog()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuMessageLog::result_type> on_key(
        const std::string& key);
};

} // namespace ui
} // namespace elona
