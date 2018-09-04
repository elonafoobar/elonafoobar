#pragma once
#include "ui_menu.hpp"

namespace elona
{
struct Character;
enum class ControlAllyOperation;

namespace ui
{

class UIMenuCtrlAlly : public UIMenu<int>
{
public:
    UIMenuCtrlAlly(ControlAllyOperation operation)
        : _operation(operation)
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuCtrlAlly::ResultType> on_key(
        const std::string& key);

private:
    bool _should_display_ally(const Character& chara);
    void _insert_proceed_entry();
    void _on_init_finish();

    std::string _get_ally_name(const Character& chara);
    std::string _get_ally_info(const Character& chara);
    std::string _get_general_ally_info(const Character& chara);
    std::string _get_specific_ally_info(const Character& chara);
    int _draw_get_color_mode(const Character& chara);

    void _draw_ally_list_entry(int cnt, const Character& chara);
    void _draw_ally_name(int cnt, const Character& chara);
    void _draw_ally_info(int cnt, const Character& chara);

    void _draw_ally_list_entry_sell(int cnt, const Character& chara);
    std::string _modify_ally_info_gene_engineer(
        const Character& chara,
        const std::string& ally_info_);

    optional<UIMenuCtrlAlly::Result> _select_gene_engineer(int _p);
    optional<UIMenuCtrlAlly::Result> _select_pet_arena(int _p);

    ControlAllyOperation _operation;
};

} // namespace ui
} // namespace elona
