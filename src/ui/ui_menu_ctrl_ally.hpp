#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class ui_menu_ctrl_ally : public ui_menu<int>
{
public:
    ui_menu_ctrl_ally()
    {
    }

protected:
    virtual void init();
    virtual void update();
    virtual void draw();
    virtual optional<ui_menu_ctrl_ally::result_type> on_key(
        const std::string& key);

private:
    optional<ui_menu_ctrl_ally::result> _select_gene_engineer(int _p);
    optional<ui_menu_ctrl_ally::result> _select_pet_arena(int _p);
};

} // namespace ui
} // namespace elona
