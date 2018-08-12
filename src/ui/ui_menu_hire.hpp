#pragma once
#include "../menu.hpp"
#include "ui_menu.hpp"

namespace elona
{
class character;

namespace ui
{

class ui_menu_hire : public ui_menu<int>
{
public:
    ui_menu_hire(hire_operation operation)
        : _operation(operation)
    {
    }

protected:
    virtual void init();
    virtual void update();
    virtual void draw();
    virtual optional<ui_menu_hire::result_type> on_key(const std::string& key);

private:
    void _populate_list();

    hire_operation _operation;
};

} // namespace ui
} // namespace elona
