#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class UIMenuAdventurers : public UIMenu<DummyResult>
{
public:
    UIMenuAdventurers()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuAdventurers::ResultType> on_key(
        const std::string& key);
};

} // namespace ui
} // namespace elona
