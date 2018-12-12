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
    virtual optional<UIMenuMessageLog::ResultType> on_key(
        const std::string& key);


private:
    int message_offset{};
};

} // namespace ui
} // namespace elona
