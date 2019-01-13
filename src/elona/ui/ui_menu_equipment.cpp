#include "ui_menu_equipment.hpp"
#include "../character.hpp"
#include "../equipment.hpp"
#include "../item.hpp"
#include "../menu.hpp"
#include "../message.hpp"

namespace elona
{
namespace ui
{

static bool _should_show_entry(int body_part)
{
    if (body_part == 0)
    {
        return false;
    }
    if (trait(206) != 0) // Your neck is extremely thick.
    {
        if (body_part / 10000 == 2)
        {
            return false;
        }
    }
    if (trait(203) != 0) // Your feet transformed into hooves.
    {
        if (body_part / 10000 == 9)
        {
            return false;
        }
    }
    if (trait(205) != 0) // You have grown feather.
    {
        if (body_part / 10000 == 3)
        {
            return false;
        }
    }

    return true;
}

static int _load_equipment_list(const Character& chara)
{
    int mainhand = 0;

    for (int i = 0; i < 30; ++i)
    {
        if (_should_show_entry(chara.body_parts[i]))
        {
            if (mainhand == 0)
            {
                if (chara.body_parts[i] / 10000 == 5)
                {
                    mainhand = i + 100;
                }
            }
            list(0, listmax) = i + 100;
            list(1, listmax) = chara.body_parts[i] / 10000;
            ++listmax;
        }
    }
    sort_list_by_column1();

    return mainhand;
}

bool UIMenuEquipment::init()
{
    cc = 0;
    page = 0;
    pagesize = 14;
    listmax = 0;
    cs = 0;
    cs_bk = -1;
    if (_cs_prev != 0)
    {
        cs = _cs_prev;
        _cs_prev = 0;
    }

    ww = 690;
    wh = 380;
    wx = (windoww - 690) / 2 + inf_screenx;
    wy = winposy(380);

    // TODO refactor
    if (nowindowanime == 0)
    {
        snd("core.wear");
    }

    window_animation(wx, wy, ww, wh, 9, 4);
    gsel(3);
    pos(960, 96);
    picload(filesystem::dir::graphic() / u8"deco_wear.bmp", 1);
    gsel(0);
    windowshadow = 1;

    _mainhand = _load_equipment_list(cdata[cc]);

    return true;
}

void UIMenuEquipment::update()
{
    cs_bk = -1;
    pagemax = (listmax - 1) / pagesize;
    if (page < 0)
    {
        page = pagemax;
    }
    else if (page > pagemax)
    {
        page = 0;
    }
}

void UIMenuEquipment::_draw_window_background()
{
    ui_display_window(
        i18n::s.get("core.locale.ui.equip.title"),
        strhint5 + strhint5b + strhint3,
        (windoww - 690) / 2 + inf_screenx,
        winposy(428),
        690,
        428,
        64);
    display_topic(
        i18n::s.get("core.locale.ui.equip.category") + "/" +
            i18n::s.get("core.locale.ui.equip.name"),
        wx + 28,
        wy + 30);
}

void UIMenuEquipment::_draw_window_deco(bool show_resistances)
{
    if (!show_resistances)
    {
        display_topic(
            i18n::s.get("core.locale.ui.equip.weight"), wx + 524, wy + 30);
    }
    pos(wx + 46, wy - 16);
    gcopy(3, 768, 48, 48, 48);
    pos(wx + ww - 106, wy);
    gcopy(3, 960, 96, 96, 120);
    pos(wx, wy + wh - 164);
    gcopy(3, 960, 216, 72, 144);
    if (show_resistances)
    {
        pos(wx + 320, wy + 40);
        mes(i18n::s.get("core.locale.ui.equip.resist"));
    }
}

void UIMenuEquipment::_draw_window_headers()
{
    display_note(
        i18n::s.get("core.locale.ui.equip.equip_weight") + ": " +
        cnvweight(cdata[cc].sum_of_equipment_weight) + cnveqweight(cc) + " " +
        i18n::s.get("core.locale.ui.equip.hit_bonus") + ":" +
        cdata[cc].hit_bonus + " " +
        i18n::s.get("core.locale.ui.equip.damage_bonus") + ":" +
        cdata[cc].damage_bonus + u8"  DV/PV:"s + cdata[cc].dv + u8"/"s +
        cdata[cc].pv);
}

void UIMenuEquipment::_draw_window(bool show_resistances)
{
    _draw_window_background();
    _draw_window_deco(show_resistances);
    _draw_window_headers();
}

void UIMenuEquipment::_draw_key(int cnt, int p_, bool is_main_hand)
{
    if (cnt % 2 == 0)
    {
        boxf(wx + 100, wy + 60 + cnt * 19, 558, 18, {12, 14, 16, 16});
    }

    std::string body_part_name;
    if (is_main_hand)
    {
        body_part_name = i18n::s.get("core.locale.ui.equip.main_hand");
    }
    else
    {
        body_part_name =
            i18n::s.get_enum("core.locale.ui.body_part", list(1, p_));
    }

    pos(wx + 22, wy + 60 + cnt * 19 - 4);
    gcopy(3, 600 + (list(1, p_) - 1) * 24, 336, 24, 24);
    pos(wx + 46, wy + 60 + cnt * 19 + 3);
    mes(body_part_name);
}

void UIMenuEquipment::_draw_keys(int main_hand)
{
    font(12 + sizefix - en * 2, snail::Font::Style::bold);
    gmode(2);
    keyrange = 0;
    f = 0;
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        int index = pagesize * page + cnt;
        if (index >= listmax)
        {
            break;
        }
        key_list(cnt) = key_select(cnt);
        ++keyrange;
        bool is_main_hand = list(0, index) == main_hand;
        _draw_key(cnt, index, is_main_hand);
    }
}

static void
_draw_single_list_entry(int cnt, int list_item, bool show_resistances)
{
    display_key(wx + 88, wy + 60 + cnt * 19 - 2, cnt);

    int equipped_item = cdata[cc].body_parts[list_item - 100];
    std::string item_name = u8"-    "s;
    std::string item_weight = u8"-"s;

    if (equipped_item % 10000 != 0)
    {
        equipped_item = equipped_item % 10000 - 1;
        item_name = itemname(equipped_item);
        item_weight = cnvweight(inv[equipped_item].weight);

        draw_item_with_portrait(
            inv[equipped_item], wx + 126, wy + 70 + cnt * 19);

        if (show_resistances)
        {
            equipinfo(equipped_item, wx + 320, wy + 60 + cnt * 19 + 2);
            item_name = strmid(item_name, 0, 22);
        }
    }
    else
    {
        equipped_item = -1;
    }

    const auto text_color = equipped_item == -1
        ? snail::Color{10, 10, 10}
        : cs_list_get_item_color(inv[equipped_item]);
    cs_list(
        cs == cnt,
        item_name,
        wx + 140 - 26,
        wy + 60 + cnt * 19 - 1,
        30,
        text_color);

    pos(wx + 640 - strlen_u(item_weight) * 7, wy + 60 + cnt * 19 + 2);
    mes(item_weight, text_color);
}

void UIMenuEquipment::_draw_list_entries(bool show_resistances)
{
    font(14 - en * 2);
    cs_listbk();
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        int index = pagesize * page + cnt;
        if (index >= listmax)
        {
            break;
        }

        int list_item = list(0, index);
        _draw_single_list_entry(cnt, list_item, show_resistances);
    }
    cs_bk = cs;
}

void UIMenuEquipment::draw()
{
    _draw_window(_show_resistances);
    _draw_keys(_mainhand);
    _draw_list_entries(_show_resistances);
}

static void _unequip_item()
{
    game_data.player_is_changing_equipment = 1;
    ci = cdata[cc].body_parts[body - 100] % 10000 - 1;
    if (is_cursed(inv[ci].curse_state))
    {
        txt(i18n::s.get("core.locale.ui.equip.cannot_be_taken_off", inv[ci]));
        return;
    }
    unequip_item(cc);
    chara_refresh(cc);
    snd("core.equip1");
    Message::instance().linebreak();
    txt(i18n::s.get("core.locale.ui.equip.you_unequip", inv[ci]));
    if (cdata[cc].body_parts[body - 100] / 10000 == 5)
    {
        equip_melee_weapon();
    }
}

static void _equip_item()
{
    // Push equipment selection screen onto call stack and pop it off
    // after.
    nowindowanime = 1;
    menucycle = 0;
    invctrl = 6;
    snd("core.inv");
    ctrl_inventory();
}

static bool _on_list_entry_select(int index)
{
    body = index;

    if (cdata[cc].body_parts[body - 100] % 10000 != 0)
    {
        _unequip_item();
        render_hud();
        return false;
    }

    _equip_item();
    return true;
}

static void _show_item_desc(int body_)
{
    ci = cdata[cc].body_parts[body_ - 100] % 10000 - 1;
    item_show_description();
    nowindowanime = 1;
    returnfromidentify = 0;
    screenupdate = -1;
    update_screen();
}

optional<UIMenuEquipment::ResultType> UIMenuEquipment::on_key(
    const std::string& action)
{
    if (auto id = get_selected_item())
    {
        _cs_prev = cs;

        bool equipped = _on_list_entry_select(*id);

        if (equipped)
        {
            // Reinitialize "list" after returning from ctrl_inventory().
            set_reinit();
        }
        else
        {
            set_reupdate();
        }
        return none;
    }
    else if (action == "identify")
    {
        int body_ = list(0, pagesize * page + cs);
        if (cdata[cc].body_parts[body_ - 100] % 10000 != 0)
        {
            _cs_prev = cs;
            _show_item_desc(body_);

            // Modifies "list", so run init() again in-place.
            set_reinit();
            return none;
        }
    }
    else if (action == "switch_mode")
    {
        _show_resistances = !_show_resistances;
        snd("core.pop1");
        set_reupdate();
    }
    else if (action == "next_page")
    {
        if (pagemax != 0)
        {
            snd("core.pop1");
            ++page;
            set_reupdate();
        }
    }
    else if (action == "previous_page")
    {
        if (pagemax != 0)
        {
            snd("core.pop1");
            --page;
            set_reupdate();
        }
    }
    else if (action == "cancel")
    {
        menucycle = 0;
        create_pcpic(cc);
        update_screen();
        // result.turn_result = TurnResult::pc_turn_user_error
        return UIMenuEquipment::Result::cancel();
    }

    return none;
} // namespace ui

} // namespace ui
} // namespace elona
