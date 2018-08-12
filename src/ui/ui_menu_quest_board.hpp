#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class ui_menu_quest_board : public ui_menu<int>
{
public:
    ui_menu_quest_board()
    {
    }

protected:
    virtual void init();
    virtual void update();
    virtual void draw();
    virtual optional<ui_menu_quest_board::result_type> on_key(
        const std::string& key);

private:
};

} // namespace ui
} // namespace elona
