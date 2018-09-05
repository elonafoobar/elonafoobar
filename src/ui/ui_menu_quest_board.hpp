#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class UIMenuQuestBoard : public UIMenu<int>
{
public:
    UIMenuQuestBoard()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuQuestBoard::ResultType> on_key(
        const std::string& key);

private:
};

} // namespace ui
} // namespace elona
