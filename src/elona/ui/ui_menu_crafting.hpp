#pragma once
#include "ui_menu.hpp"

namespace elona
{
struct CraftingRecipe;
struct RequiredMaterial;

namespace ui
{

class UIMenuCrafting : public UIMenu<int>
{
public:
    UIMenuCrafting(int prodtype, int invctrl)
        : _prodtype(prodtype)
        , _invctrl(invctrl)
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuCrafting::ResultType> on_key(const std::string& key);

private:
    void _draw_window();
    void _draw_key(int);
    void _draw_keys();
    void _draw_recipe_desc(const CraftingRecipe&);
    void _draw_single_recipe_required_material(int, const RequiredMaterial&);
    void _draw_recipe_required_materials(const CraftingRecipe&);
    void _draw_recipe(int, bool);
    void _draw_single_list_entry(int, int, bool);
    bool _draw_list_entries(bool);

    int _prodtype;
    int _invctrl;
};

} // namespace ui
} // namespace elona
