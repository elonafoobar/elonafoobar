#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class UIMenuScene : public UIMenu<DummyResult>
{
public:
    UIMenuScene()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuScene::result_type> on_key(const std::string& key);
};

} // namespace ui
} // namespace elona
