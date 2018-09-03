#pragma once
#include "ui_menu.hpp"

namespace elona
{
struct character;
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
    virtual optional<UIMenuCtrlAlly::result_type> on_key(
        const std::string& key);

private:
    bool _should_display_ally(const character& chara);
    void _insert_proceed_entry();
    void _on_init_finish();

    std::string _get_ally_name(const character& chara);
    std::string _get_ally_info(const character& chara);
    std::string _get_general_ally_info(const character& chara);
    std::string _get_specific_ally_info(const character& chara);
    int _draw_get_color_mode(const character& chara);

    void _draw_ally_list_entry(int cnt, const character& chara);
    void _draw_ally_name(int cnt, const character& chara);
    void _draw_ally_info(int cnt, const character& chara);

    void _draw_ally_list_entry_sell(int cnt, const character& chara);
    std::string _modify_ally_info_gene_engineer(
        const character& chara,
        const std::string& ally_info_);

    optional<UIMenuCtrlAlly::result> _select_gene_engineer(int _p);
    optional<UIMenuCtrlAlly::result> _select_pet_arena(int _p);

    ControlAllyOperation _operation;
};

} // namespace ui
} // namespace elona
