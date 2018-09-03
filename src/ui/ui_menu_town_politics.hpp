#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class UIMenuTownPolitics : public UIMenu<dummy_result>
{
public:
    UIMenuTownPolitics()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuTownPolitics::result_type> on_key(
        const std::string& key);
};

} // namespace ui
} // namespace elona
