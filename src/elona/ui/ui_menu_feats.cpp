#include "ui_menu_feats.hpp"

#include "../../snail/color.hpp"
#include "../../util/range.hpp"
#include "../../util/strutil.hpp"
#include "../enchantment.hpp"
#include "../menu.hpp"
#include "../message.hpp"
#include "../trait.hpp"



namespace elona
{
namespace ui
{

const constexpr int trait_desc_value = 99999;



bool UIMenuFeats::init()
{
    _chara_index = 0;

    listmax = 0;
    page = 0;
    pagesize = 15;
    cs = 0;
    cs_bk = -1;

    snd("core.feat");
    ww = 700;
    wh = 400;
    wx = (windoww - ww) / 2 + inf_screenx;
    wy = winposy(wh);
    window_animation(wx, wy, ww, wh, 9, 4);
    asset_load("deco_feat");
    gsel(0);
    windowshadow = 1;

    return true;
}



void UIMenuFeats::_change_tense_of_trait_desc(int cnt)
{
    if (jp)
    {
        listn(0, cnt) = strutil::replace(
            listn(0, cnt),
            u8"あなた",
            cdata[_chara_index].sex == 0 ? u8"彼" : u8"彼女");
    }
    else
    {
        listn(0, cnt) = strutil::replace(
            listn(0, cnt),
            u8" your",
            cdata[_chara_index].sex == 0 ? u8" his" : u8" her");
        listn(0, cnt) = strutil::replace(
            listn(0, cnt),
            u8" you",
            cdata[_chara_index].sex == 0 ? u8" him" : u8" her");
    }
}



void UIMenuFeats::_add_trait_desc(const std::string& trait_desc)
{
    list(0, listmax) = 1;
    list(1, listmax) = trait_desc_value;
    listn(0, listmax) = i18n::s.get(
        "core.trait.window.his_equipment",
        cnven(
            (jp)
                ? ((_chara_index == 0)
                       ? u8"あなたの"
                       : (cdata[_chara_index].sex == 0 ? u8"彼の" : u8"彼女の"))
                : ((_chara_index == 0)
                       ? "your"
                       : (cdata[_chara_index].sex == 0 ? u8"his" : u8"her"))),
        trait_desc);
    ++listmax;
}



void UIMenuFeats::_load_traits_by_enchantments()
{
    std::vector<std::string> traits_by_enchantments;
    for (int i = 0; i < 30; ++i)
    {
        if (cdata[_chara_index].body_parts[i] % 10000 != 0)
        {
            const auto item_index =
                cdata[_chara_index].body_parts[i] % 10000 - 1;
            for (const auto& enc : inv[item_index].enchantments)
            {
                if (enc.id == 0)
                    break;
                get_enchantment_description(
                    enc.id, enc.power, ItemCategory::unidentified, true);
                if (!s(0).empty())
                {
                    traits_by_enchantments.push_back(s);
                }
            }
        }
    }
    range::sort(traits_by_enchantments);
    traits_by_enchantments.erase(
        std::unique(
            std::begin(traits_by_enchantments),
            std::end(traits_by_enchantments)),
        std::end(traits_by_enchantments));
    for (const auto& trait : traits_by_enchantments)
    {
        _add_trait_desc(trait);
    }

    if (_chara_index != 0)
    {
        for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
        {
            _change_tense_of_trait_desc(cnt);
        }
    }
}



void UIMenuFeats::update()
{
    trait_load_desc(cdata[_chara_index]);
    _load_traits_by_enchantments();

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
    if (cs < 0)
    {
        for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
        {
            if (list(1, cnt) >= 10000)
            {
                if (list(0, cnt) - 10000 == cs)
                {
                    page = cnt / pagesize;
                    cs = cnt % pagesize;
                    break;
                }
            }
        }
        if (cs < 0)
        {
            cs = 0;
        }
    }
}



void UIMenuFeats::_draw_window_background(bool is_chara_making)
{
    int y_adjust;
    if (is_chara_making)
    {
        // Adjust downwards for character making caption.
        y_adjust = 1;
    }
    else
    {
        y_adjust = 0;
    }

    ui_display_window(
        i18n::s.get("core.trait.window.title"),
        i18n::s.get("core.trait.window.enter") + "  " + strhint2 + strhint3 +
            key_mode + u8"," + key_identify + u8" [" +
            i18n::s.get("core.trait.window.ally") + u8"]",
        (windoww - 730) / 2 + inf_screenx,
        winposy(430, y_adjust) + y_adjust * 15,
        730,
        430,
        55,
        40);
}



void UIMenuFeats::_draw_window_deco()
{
    s(0) = i18n::s.get("core.trait.window.name");
    s(1) = i18n::s.get("core.trait.window.level");
    s(2) = i18n::s.get("core.trait.window.detail");
    display_topic(s, wx + 46, wy + 36);
    display_topic(s(2), wx + 255, wy + 36);
    draw_indexed("inventory_icon", wx + 46, wy - 16, 11);
    elona::draw("deco_feat_a", wx + ww - 56, wy + wh - 198);
    elona::draw("deco_feat_b", wx, wy);
    elona::draw("deco_feat_c", wx + ww - 108, wy);
    elona::draw("deco_feat_d", wx, wy + wh - 70);
}



void UIMenuFeats::_draw_window(bool is_chara_making)
{
    _draw_window_background(is_chara_making);
    _draw_window_deco();
}



void UIMenuFeats::_draw_key(int cnt, int p_)
{
    int list_item = list(0, p_);
    int list_value = list(1, p_);

    if (list_item < 0)
    {
        return;
    }
    if (cnt % 2 == 0)
    {
        boxf(wx + 57, wy + 66 + cnt * 19, 640, 18, {12, 14, 16, 16});
    }
    if (list_value >= 10000 || list_item < 0)
    {
        return;
    }

    display_key(wx + 58, wy + 66 + cnt * 19 - 2, cnt);
}



void UIMenuFeats::_draw_keys()
{
    keyrange = 0;
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        int index = pagesize * page + cnt;
        if (index >= listmax)
        {
            break;
        }
        key_list(cnt) = key_select(cnt);
        ++keyrange;
        _draw_key(cnt, index);
    }
}



void UIMenuFeats::_draw_acquirable_trait_number(int tc_)
{
    std::string note;
    if (tc_ == 0)
    {
        note = i18n::s.get(
            "core.trait.window.you_can_acquire",
            game_data.acquirable_feat_count);
    }
    else
    {
        note = i18n::s.get(
            "core.trait.window.your_trait", cnven(cdatan(0, _chara_index)));
    }
    display_note(note, 50);
}



void UIMenuFeats::_draw_single_list_entry_name(
    int cnt,
    const snail::Color& text_color)
{
    mes(wx + 270, wy + 66 + cnt * 19 + 2, traitrefn(2), text_color);
}



void UIMenuFeats::_draw_single_list_entry_text(
    int cnt,
    bool draw_name,
    const snail::Color& text_color,
    const std::string& text)
{
    if (draw_name)
    {
        x = 84;
    }
    else
    {
        x = 70;
    }
    draw_indexed(
        "trait_icon", wx + (draw_name ? 30 : 45), wy + 61 + cnt * 19, traitref);

    cs_list(cs == cnt, text, wx + x, wy + 66 + cnt * 19 - 1, 0, text_color);

    if (draw_name)
    {
        _draw_single_list_entry_name(cnt, text_color);
    }
}



static snail::Color _get_trait_color(int trait_value)
{
    if (trait_value == 0)
    {
        return {10, 10, 10};
    }
    else if (trait_value > 0)
    {
        return {0, 0, 200};
    }
    else
    {
        return {200, 0, 0};
    }
}



void UIMenuFeats::_draw_single_list_entry(
    int cnt,
    int list_item,
    int list_value,
    const std::string& text)
{
    if (list_item < 0)
    {
        cs_list(cs == cnt, text, wx + 114, wy + 66 + cnt * 19 - 1);
        return;
    }

    snail::Color text_color = {10, 10, 10};

    if (list_value != trait_desc_value)
    {
        trait_get_info(0, list_item);
        text_color = _get_trait_color(trait(list_item));
    }
    else
    {
        traitref = 5;
    }

    bool draw_name = list_value < 10000;
    _draw_single_list_entry_text(cnt, draw_name, text_color, text);
}



void UIMenuFeats::_draw_list_entries()
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

        int list_index = list(0, index);
        int list_value = list(1, index);
        const std::string& text = listn(0, index);
        _draw_single_list_entry(cnt, list_index, list_value, text);
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
}



void UIMenuFeats::draw()
{
    _draw_window(_operation == Operation::character_making);
    _draw_keys();
    _draw_acquirable_trait_number(_chara_index);
    _draw_list_entries();
}



bool UIMenuFeats::_gain_trait(int p_, bool show_text)
{
    int tid = list(0, p_);
    trait_get_info(0, tid);

    if (traitref(2) <= trait(tid))
    {
        if (show_text)
        {
            txt(i18n::s.get("core.trait.window.already_maxed"));
        }
        return false;
    }

    --game_data.acquirable_feat_count;
    cs = -10000 + tid;
    snd("core.ding3");
    ++trait(tid);
    chara_refresh(_chara_index);

    return true;
}



bool UIMenuFeats::_can_select_trait(int p_)
{
    return game_data.acquirable_feat_count > 0 && list(1, p_) < 10000 &&
        _chara_index == 0;
}



void UIMenuFeats::_switch_target(bool is_forwards)
{
    int new_index = _chara_index;
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        if (is_forwards)
        {
            ++new_index;
            if (new_index == 16)
            {
                new_index = 0;
            }
        }
        else
        {
            --new_index;
            if (new_index < 0)
            {
                new_index = 15;
            }
        }
        if (cdata[new_index].state() == Character::State::alive)
        {
            break;
        }
    }
    _chara_index = new_index;
    snd("core.pop1");
    page = 0;
    cs = 0;
}



optional<UIMenuFeats::ResultType> UIMenuFeats::on_key(const std::string& action)
{
    auto index = get_selected_index();
    if (index && *index > 0 && _can_select_trait(*index))
    {
        bool show_text = _operation == Operation::normal;
        if (_gain_trait(*index, show_text))
        {
            if (_operation == Operation::character_making)
            {
                if (game_data.acquirable_feat_count == 0)
                {
                    return UIMenuFeats::Result::finish(
                        UIMenuCompositeCharacterResult{FeatsResult::confirmed});
                }
            }
            else
            {
                render_hud();
            }
        }

        set_reupdate();
        return none;
    }
    if (action == "next_page")
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
    else if (action == "switch_mode" || action == "identify")
    {
        bool is_forwards = action == "identify";
        _switch_target(is_forwards);
        set_reupdate();
    }
    else if (action == "cancel")
    {
        if (_operation == Operation::normal)
        {
            update_screen();
        }
        return UIMenuFeats::Result::cancel();
    }
    else if (
        getkey(snail::Key::f1) && _operation == Operation::character_making)
    {
        show_game_help();
        return UIMenuFeats::Result::finish(
            UIMenuCompositeCharacterResult{FeatsResult::pressed_f1});
    }

    return none;
}

} // namespace ui
} // namespace elona
