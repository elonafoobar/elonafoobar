#include "ui_menu_feats.hpp"
#include "../enchantment.hpp"
#include "../menu.hpp"
#include "../snail/color.hpp"
#include "../trait.hpp"

namespace elona
{
namespace ui
{

const constexpr int trait_desc_value = 99999;

bool ui_menu_feats::init()
{
    listmax = 0;
    page = 0;
    pagesize = 15;
    cs = 0;
    tc = 0;
    cs_bk = -1;
    curmenu = 2;
    snd(96);
    ww = 700;
    wh = 400;
    wx = (windoww - ww) / 2 + inf_screenx;
    wy = winposy(wh);
    window_animation(wx, wy, ww, wh, 9, 4);
    gsel(3);
    pos(960, 96);
    picload(filesystem::dir::graphic() / u8"deco_feat.bmp", 1);
    gsel(0);
    windowshadow = 1;

    return true;
}

static void _change_tense_of_trait_desc(int cnt, int tc_)
{
    if (jp)
    {
        listn(0, cnt) = strutil::replace(listn(0, cnt), u8"あなた", he(tc_, 1));
    }
    if (en)
    {
        listn(0, cnt) = strutil::replace(listn(0, cnt), u8" your", his(tc_, 1));
        listn(0, cnt) = strutil::replace(listn(0, cnt), u8" you", him(tc_, 1));
    }
}

static void _add_trait_desc(int tc_, const std::string& trait_desc)
{
    list(0, listmax) = 1;
    list(1, listmax) = trait_desc_value;
    listn(0, listmax) = i18n::s.get(
        "core.locale.trait.window.his_equipment",
        cnven(his(tc_, 1)),
        trait_desc);
    ++listmax;
}

static void _load_traits_by_enchantments()
{
    std::vector<std::string> traits_by_enchantments;
    for (int i = 0; i < 30; ++i)
    {
        if (cdata[tc].body_parts[i] % 10000 != 0)
        {
            ci = cdata[tc].body_parts[i] % 10000 - 1;
            for (const auto& enc : inv[ci].enchantments)
            {
                if (enc.id == 0)
                    break;
                get_enchantment_description(enc.id, enc.power, 0, true);
                if (!s(0).empty())
                {
                    traits_by_enchantments.push_back(s);
                }
            }
        }
    }
    std::sort(
        std::begin(traits_by_enchantments), std::end(traits_by_enchantments));
    traits_by_enchantments.erase(
        std::unique(
            std::begin(traits_by_enchantments),
            std::end(traits_by_enchantments)),
        std::end(traits_by_enchantments));
    for (const auto& trait : traits_by_enchantments)
    {
        _add_trait_desc(tc, trait);
    }

    if (tc != 0)
    {
        for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
        {
            _change_tense_of_trait_desc(cnt, tc);
        }
    }
}

void ui_menu_feats::update()
{
    trait_load_desc();
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

static void _draw_window_background(bool is_chara_making)
{
    s(0) = i18n::s.get("core.locale.trait.window.title");
    s(1) = i18n::s.get("core.locale.trait.window.enter") + "  " + strhint2
        + strhint3 + u8"z,x ["s + i18n::s.get("core.locale.trait.window.ally")
        + u8"]"s;

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

    display_window(
        (windoww - 730) / 2 + inf_screenx,
        winposy(430, y_adjust) + y_adjust * 15,
        730,
        430,
        55,
        40);
}

static void _draw_window_deco()
{
    s(0) = i18n::s.get("core.locale.trait.window.name");
    s(1) = i18n::s.get("core.locale.trait.window.level");
    s(2) = i18n::s.get("core.locale.trait.window.detail");
    display_topic(s, wx + 46, wy + 36);
    display_topic(s(2), wx + 255, wy + 36);
    pos(wx + 46, wy - 16);
    gcopy(3, 816, 48, 48, 48);
    pos(wx + ww - 56, wy + wh - 198);
    gcopy(3, 960, 96, 48, 192);
    pos(wx, wy);
    gcopy(3, 1008, 96, 48, 144);
    pos(wx + ww - 108, wy);
    gcopy(3, 960, 288, 96, 72);
    pos(wx, wy + wh - 70);
    gcopy(3, 1008, 240, 96, 48);
}

static void _draw_window(bool is_chara_making)
{
    _draw_window_background(is_chara_making);
    _draw_window_deco();
}

static void _draw_key(int cnt, int p_)
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

static void _draw_keys()
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

static void _draw_acquirable_trait_number(int tc_)
{
    std::string note;
    if (tc_ == 0)
    {
        note = i18n::s.get(
            "core.locale.trait.window.you_can_acquire",
            gdata_acquirable_feat_count);
    }
    else
    {
        note = i18n::s.get(
            "core.locale.trait.window.your_trait", cnven(cdatan(0, tc)));
    }
    display_note(note, 50);
}

static void _draw_single_list_entry_name(
    int cnt,
    const snail::color& text_color)
{
    pos(wx + 270, wy + 66 + cnt * 19 + 2);

    color(text_color.r, text_color.g, text_color.b);
    mes(traitrefn(2));
    color(0, 0, 0);
}

static void _draw_single_list_entry_text(
    int cnt,
    bool draw_name,
    const snail::color& text_color,
    const std::string& text)
{
    if (draw_name)
    {
        pos(wx + 30, wy + 61 + cnt * 19);
        x = 84;
    }
    else
    {
        pos(wx + 45, wy + 61 + cnt * 19);
        x = 70;
    }
    gcopy(3, 384 + traitref * 24, 336, 24, 24);

    color(text_color.r, text_color.g, text_color.b);
    cs_list(cs == cnt, text, wx + x, wy + 66 + cnt * 19 - 1, 0, -1);
    color(0, 0, 0);

    if (draw_name)
    {
        _draw_single_list_entry_name(cnt, text_color);
    }
}

static snail::color _get_trait_color(int trait_value)
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

static void _draw_single_list_entry(
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

    snail::color text_color = {10, 10, 10};

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

static void _draw_list_entries()
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

void ui_menu_feats::draw()
{
    _draw_window(_operation == Operation::character_making);
    _draw_keys();
    _draw_acquirable_trait_number(tc);
    _draw_list_entries();
}

static bool _gain_trait(int p_, bool show_text)
{
    int tid = list(0, p_);
    trait_get_info(0, tid);

    if (traitref(2) <= trait(tid))
    {
        if (show_text)
        {
            txt(i18n::s.get("core.locale.trait.window.already_maxed"));
        }
        return false;
    }

    --gdata_acquirable_feat_count;
    cs = -10000 + tid;
    snd(61);
    ++trait(tid);
    chara_refresh(tc);

    return true;
}

static bool _can_select_trait(int p_, int tc_)
{
    return gdata_acquirable_feat_count > 0 && list(1, p_) < 10000 && tc_ == 0;
}

static void _switch_target(bool is_forwards)
{
    int new_index = tc;
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
        if (cdata[new_index].state() == character::State::alive)
        {
            break;
        }
    }
    tc = new_index;
    snd(1);
    page = 0;
    cs = 0;
}

optional<ui_menu_feats::result_type> ui_menu_feats::on_key(
    const std::string& key)
{
    int p_;

    ELONA_GET_SELECTED_INDEX(p_);

    if (p_ > 0 && _can_select_trait(p_, tc))
    {
        bool show_text = _operation == Operation::normal;
        if (_gain_trait(p_, show_text))
        {
            if (_operation == Operation::character_making)
            {
                if (gdata_acquirable_feat_count == 0)
                {
                    return ui_menu_feats::result::finish(
                        ui_menu_composite_character_result{
                            FeatsResult::confirmed});
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
    if (key == key_pageup)
    {
        if (pagemax != 0)
        {
            snd(1);
            ++page;
            set_reupdate();
        }
    }
    else if (key == key_pagedown)
    {
        if (pagemax != 0)
        {
            snd(1);
            --page;
            set_reupdate();
        }
    }
    else if (key == u8"z"s || key == u8"x"s)
    {
        bool is_forwards = key == u8"x";
        _switch_target(is_forwards);
        set_reupdate();
    }
    else if (key == key_cancel)
    {
        if (_operation == Operation::normal)
        {
            update_screen();
        }
        return ui_menu_feats::result::cancel();
    }
    else if (
        getkey(snail::Key::f1) && _operation == Operation::character_making)
    {
        show_game_help();
        return ui_menu_feats::result::finish(
            ui_menu_composite_character_result{FeatsResult::pressed_f1});
    }

    return none;
}

} // namespace ui
} // namespace elona
