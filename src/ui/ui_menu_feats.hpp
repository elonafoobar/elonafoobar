#pragma once
#include "ui_menu.hpp"
#include "ui_menu_composite_character.hpp"

namespace elona
{
namespace ui
{

class ui_menu_feats : public ui_menu<ui_menu_composite_character_result>
{
public:
    enum class operation
    {
        normal,
        character_making
    };

public:
    ui_menu_feats(bool decorate, operation operation)
        : _decorate(decorate)
        , _operation(operation)
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<ui_menu_feats::result_type> on_key(const std::string& key);

private:
    bool _decorate;
    operation _operation;

    int _featrq = 0;
};

} // namespace ui
} // namespace elona
