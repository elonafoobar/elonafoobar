#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class UIMenuSpellWriter : public UIMenu<DummyResult>
{
public:
    UIMenuSpellWriter()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuSpellWriter::result_type> on_key(
        const std::string& key);
};

} // namespace ui
} // namespace elona
