#pragma once
#include "ui_menu.hpp"
#include "ui_menu_composite_character.hpp"

namespace elona
{
namespace ui
{

class UIMenuFeats : public UIMenu<ui_menu_composite_character_result>
{
public:
    enum class Operation
    {
        normal,
        character_making
    };

public:
    UIMenuFeats(Operation operation)
        : _operation(operation)
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuFeats::result_type> on_key(const std::string& key);

private:
    Operation _operation;
};

} // namespace ui
} // namespace elona
