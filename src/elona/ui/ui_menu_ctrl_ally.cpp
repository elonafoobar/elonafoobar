#include "ui_menu_ctrl_ally.hpp"

#include "../ability.hpp"
#include "../area.hpp"
#include "../audio.hpp"
#include "../calc.hpp"
#include "../character.hpp"
#include "../data/types/type_ability.hpp"
#include "../draw.hpp"
#include "../game.hpp"
#include "../i18n.hpp"
#include "../menu.hpp"
#include "../message.hpp"



namespace elona
{
namespace ui
{

bool UIMenuCtrlAlly::_should_display_ally(const Character& chara)
{
    if (chara.state() == Character::State::empty)
    {
        return false;
    }
    if (_operation == ControlAllyOperation::sell)
    {
        if (chara.state() == Character::State::pet_dead)
        {
            return false;
        }
    }
    if (_operation == ControlAllyOperation::staying ||
        _operation == ControlAllyOperation::gene_engineer)
    {
        if (chara.state() != Character::State::alive)
        {
            return false;
        }
    }
    if (_operation == ControlAllyOperation::gene_engineer)
    {
        if (_gene_engineering_original_character)
        {
            if (chara.index == _gene_engineering_original_character->index)
            {
                return false;
            }
        }
    }
    if (chara.current_map != 0)
    {
        if (_operation == ControlAllyOperation::sell ||
            _operation == ControlAllyOperation::pet_arena)
        {
            return false;
        }
    }
    if (_operation != ControlAllyOperation::sell)
    {
        if (chara.is_escorted() || chara.is_escorted_in_sub_quest())
        {
            return false;
        }
    }
    if (chara.is_ridden())
    {
        return false;
    }

    return true;
}

void UIMenuCtrlAlly::_insert_proceed_entry()
{
    list(0, listmax) = 99;
    list(1, listmax) = -9999;
    ++listmax;
}

static void _init_pet_arena_selection()
{
    int _p = 0;
    DIM2(followerin, 16);
    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
    {
        if (cnt == 0)
        {
            continue;
        }
        i = list(0, cnt);
        if (cdata[i].state() != Character::State::pet_dead)
        {
            followerin(i) = 1;
            ++_p;
            if (_p == arenaop(1))
            {
                break;
            }
        }
    }
}

bool UIMenuCtrlAlly::init()
{
    snd("core.pop2");
    listmax = 0;
    page = 0;
    pagesize = 16;
    cs = 0;
    cs_bk = -1;
    if (_operation == ControlAllyOperation::pet_arena)
    {
        _insert_proceed_entry();
    }
    for (auto&& ally : cdata.allies())
    {
        if (_should_display_ally(ally))
        {
            list(0, listmax) = ally.index;
            list(1, listmax) = -ally.level;
            ++listmax;
        }
    }
    sort_list_by_column1();
    if (_operation == ControlAllyOperation::pet_arena)
    {
        _init_pet_arena_selection();
    }
    windowshadow = 1;

    return true;
}

static void _update_call_back()
{
    txt(i18n::s.get("core.ui.ally_list.call.prompt"));
    s(10) = i18n::s.get("core.ui.ally_list.call.title");
    s(11) = strhint2 + strhint3;
    s(12) = i18n::s.get("core.ui.ally_list.name");
    s(13) = i18n::s.get("core.ui.ally_list.status");
    x = 0;
}

static void _update_sell()
{
    txt(i18n::s.get("core.ui.ally_list.sell.prompt"));
    s(10) = i18n::s.get("core.ui.ally_list.sell.title");
    s(11) = strhint2 + strhint3;
    s(12) = i18n::s.get("core.ui.ally_list.name");
    s(13) = i18n::s.get("core.ui.ally_list.sell.value");
    x = 20;
}

static void _update_pet_arena()
{
    i = 0;
    for (const auto& ally : cdata.player_and_allies())
    {
        i += followerin(ally.index) == 1;
    }
    if (i < arenaop(1))
    {
        Message::instance().txtef(ColorIndex::red);
    }
    else
    {
        Message::instance().txtef(ColorIndex::blue);
    }
    txt(i18n::s.get("core.ui.ally_list.pet_arena.prompt") + ": " + i +
        u8" / "s + arenaop(1));
    s(10) = i18n::s.get("core.ui.ally_list.pet_arena.title");
    s(11) = strhint2 + strhint3;
    s(12) = i18n::s.get("core.ui.ally_list.name");
    s(13) = i18n::s.get("core.ui.ally_list.status");
    x = 20;
}

static void _update_staying()
{
    if (area_data[game()->current_map].id == mdata_t::MapId::shop)
    {
        txt(i18n::s.get("core.ui.ally_list.shop.prompt"));
        s(10) = i18n::s.get("core.ui.ally_list.shop.title");
        s(11) = strhint2 + strhint3;
        s(12) = i18n::s.get("core.ui.ally_list.name");
        s(13) = i18n::s.get("core.ui.ally_list.shop.chr_negotiation");
    }
    if (area_data[game()->current_map].id == mdata_t::MapId::ranch)
    {
        txt(i18n::s.get("core.ui.ally_list.ranch.prompt"));
        s(10) = i18n::s.get("core.ui.ally_list.ranch.title");
        s(11) = strhint2 + strhint3;
        s(12) = i18n::s.get("core.ui.ally_list.name");
        s(13) = i18n::s.get("core.ui.ally_list.ranch.breed_power");
    }
    if (game()->current_map == mdata_t::MapId::your_home)
    {
        txt(i18n::s.get("core.ui.ally_list.stayer.prompt"));
        s(10) = i18n::s.get("core.ui.ally_list.stayer.title");
        s(11) = strhint2 + strhint3;
        s(12) = i18n::s.get("core.ui.ally_list.name");
        s(13) = i18n::s.get("core.ui.ally_list.status");
    }
    x = 20;
}

void UIMenuCtrlAlly::_update_investigate_and_gene_engineer(
    bool is_gene_engineer)
{
    txt(i18n::s.get("core.ui.ally_list.gene_engineer.prompt"));
    s(10) = i18n::s.get("core.ui.ally_list.gene_engineer.title");
    s(11) = strhint2 + strhint3;
    s(12) = i18n::s.get("core.ui.ally_list.name");
    s(13) = i18n::s.get("core.ui.ally_list.status");
    if (is_gene_engineer)
    {
        if (_gene_engineering_original_character)
        {
            s(13) = i18n::s.get("core.ui.ally_list.gene_engineer.body_skill");
        }
    }
    x = 0;
}

void UIMenuCtrlAlly::update()
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
        Message::instance().linebreak();
    }

    switch (_operation)
    {
    case ControlAllyOperation::call_back: _update_call_back(); break;
    case ControlAllyOperation::sell: _update_sell(); break;
    case ControlAllyOperation::pet_arena: _update_pet_arena(); break;
    case ControlAllyOperation::staying: _update_staying(); break;
    case ControlAllyOperation::investigate:
    case ControlAllyOperation::gene_engineer:
        _update_investigate_and_gene_engineer(
            _operation == ControlAllyOperation::gene_engineer);
        break;
    }
}

void UIMenuCtrlAlly::_draw_info_pet_arena(
    const Character& chara,
    std::string& _s)
{
    if (followerin(chara.index) == 1)
    {
        _s += i18n::s.get("core.ui.ally_list.pet_arena.in");
    }
}



snail::Color UIMenuCtrlAlly::_draw_get_color(const Character& chara)
{
    if (_operation == ControlAllyOperation::gene_engineer)
    {
        if (chara.level > cdata.player().get_skill(151).level + 5)
        {
            return {160, 10, 10};
        }
    }

    return {10, 10, 10};
}



std::string UIMenuCtrlAlly::_get_ally_name(const Character& chara)
{
    std::string ally_name = chara.alias + u8" "s + chara.name;

    if (chara.current_map != 0)
    {
        ally_name = ally_name + u8"("s + mapname(chara.current_map) + u8")"s;
    }
    if (_operation == ControlAllyOperation::pet_arena)
    {
        _draw_info_pet_arena(chara, ally_name);
    }

    return ally_name;
}

std::string UIMenuCtrlAlly::_get_general_ally_info(const Character& chara)
{
    std::string ally_info = u8"Lv."s + chara.level + u8" "s;

    if (chara.state() == Character::State::pet_dead)
    {
        ally_info += i18n::s.get("core.ui.ally_list.dead");
    }
    if (chara.state() == Character::State::pet_waiting)
    {
        if (_operation == ControlAllyOperation::call_back)
        {
            ally_info += i18n::s.get("core.ui.ally_list.call.waiting");
        }
        else
        {
            ally_info += u8"(Hp: "s + chara.hp * 100 / chara.max_hp + u8"%) "s +
                i18n::s.get("core.ui.ally_list.waiting");
        }
    }
    if (chara.state() == Character::State::alive)
    {
        if (_operation == ControlAllyOperation::call_back)
        {
            ally_info += i18n::s.get("core.ui.ally_list.alive");
        }
        else
        {
            ally_info += u8"(Hp: "s + chara.hp * 100 / chara.max_hp + u8"%)"s;
        }
    }

    return ally_info;
}

std::string UIMenuCtrlAlly::_get_specific_ally_info(const Character& chara)
{
    std::string _s = "";

    if (area_data[game()->current_map].id == mdata_t::MapId::shop)
    {
        _s = u8"   "s + chara.get_skill(17).level + u8" / " +
            chara.get_skill(156).level;
    }
    else if (area_data[game()->current_map].id == mdata_t::MapId::ranch)
    {
        _s = u8"   "s + chara_breed_power(chara);
    }

    return _s;
}

static bool _has_general_info(ControlAllyOperation operation)
{
    return operation != ControlAllyOperation::staying ||
        (operation == ControlAllyOperation::staying &&
         game()->current_map == mdata_t::MapId::your_home);
}

std::string UIMenuCtrlAlly::_get_ally_info(const Character& chara)
{
    std::string _s = "";

    if (_has_general_info(_operation))
    {
        _s = _get_general_ally_info(chara);
    }
    else
    {
        _s = _get_specific_ally_info(chara);
    }

    return _s;
}

std::string UIMenuCtrlAlly::_modify_ally_info_gene_engineer(
    const Character& chara,
    const std::string& ally_info_)
{
    std::string ally_info = ally_info_;

    if (_gene_engineering_original_character)
    {
        if (const auto body_part_id =
                gene_engineering_get_transplanted_body_part(
                    *_gene_engineering_original_character, chara))
        {
            ally_info =
                i18n::s.get_data_text("core.body_part", *body_part_id, "name");
        }
        else
        {
            ally_info = i18n::s.get("core.ui.ally_list.gene_engineer.none");
        }
        ally_info += u8"/"s;
        {
            int stat = gain_skills_by_geen_engineering(
                *_gene_engineering_original_character, chara);
            if (stat == 0)
            {
                ally_info +=
                    i18n::s.get("core.ui.ally_list.gene_engineer.none");
            }
            else
            {
                ally_info += ""s + the_ability_db.get_text(rtval, "name");
                if (rtval(1) != -1)
                {
                    ally_info +=
                        u8", "s + the_ability_db.get_text(rtval(1), "name");
                }
            }
        }
    }

    return ally_info;
}

void UIMenuCtrlAlly::_draw_ally_list_entry_sell(int cnt, const Character& chara)
{
    std::string ally_name = chara.alias + u8" "s + chara.name;
    ally_name += u8" Lv."s + chara.level;

    cs_list(cs == cnt, ally_name, wx + 84, wy + 66 + cnt * 19 - 1);

    std::string ally_info =
        ""s + calc_slave_value(chara) * 2 / 3 + i18n::s.get("core.ui.gold");

    mes(wx + 390, wy + 66 + cnt * 19 + 2, ally_info);
}

void UIMenuCtrlAlly::_draw_ally_name(int cnt, const Character& chara)
{
    std::string ally_name = _get_ally_name(chara);
    cs_list(
        cs == cnt,
        ally_name,
        wx + 84,
        wy + 66 + cnt * 19 - 1,
        0,
        _draw_get_color(chara));
}

void UIMenuCtrlAlly::_draw_ally_info(int cnt, const Character& chara)
{
    std::string ally_info = _get_ally_info(chara);

    if (_operation == ControlAllyOperation::gene_engineer)
    {
        ally_info = _modify_ally_info_gene_engineer(chara, ally_info);
    }

    const auto text_color = _draw_get_color(chara);
    mes(wx + 370, wy + 66 + cnt * 19 + 2, ally_info, text_color);
}

void UIMenuCtrlAlly::_draw_ally_list_entry(int cnt, const Character& chara)
{
    if (_operation != ControlAllyOperation::sell)
    {
        _draw_ally_name(cnt, chara);
        _draw_ally_info(cnt, chara);
    }
    else if (_operation == ControlAllyOperation::sell)
    {
        _draw_ally_list_entry_sell(cnt, chara);
    }
}

void UIMenuCtrlAlly::draw()
{
    ui_display_window(
        s(10),
        s(11),
        (windoww - 620) / 2 + inf_screenx,
        winposy(400),
        620,
        400);
    display_topic(s(12), wx + 28, wy + 36);
    display_topic(s(13), wx + 350 + x, wy + 36);
    keyrange = 0;
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        key_list(cnt) = key_select(cnt);
        ++keyrange;
        if (cnt % 2 == 0)
        {
            boxf(wx + 70, wy + 66 + cnt * 19, 500, 18, {12, 14, 16, 16});
        }
        display_key(wx + 58, wy + 66 + cnt * 19 - 2, cnt);
    }
    font(14 - en * 2);
    cs_listbk();
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        if (list(0, p) != 99)
        {
            draw_chara_scale_height(
                cdata[list(0, p)], wx + 40, wy + 74 + cnt * 19 - 8);
        }
        i = list(0, p);
        if (i == 99)
        {
            cs_list(
                cs == cnt,
                i18n::s.get("core.ui.ally_list.proceed"),
                wx + 84,
                wy + 66 + cnt * 19 - 1);
            continue;
        }

        _draw_ally_list_entry(cnt, cdata[i]);
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
}

optional<UIMenuCtrlAlly::Result> UIMenuCtrlAlly::_select_gene_engineer(int _p)
{
    if (cdata[_p].level > cdata.player().get_skill(151).level + 5)
    {
        snd("core.fail1");
        txt(i18n::s.get("core.ui.ally_list.gene_engineer.skill_too_low"));
        set_reupdate();
        return none;
    }

    return UIMenuCtrlAlly::Result::finish(_p);
}

optional<UIMenuCtrlAlly::Result> UIMenuCtrlAlly::_select_pet_arena(int _p)
{
    i = 0;
    for (const auto& ally : cdata.player_and_allies())
    {
        if (followerin(ally.index) == 1)
        {
            ++i;
        }
    }

    if (_p == 99)
    {
        if (i == 0)
        {
            txt(i18n::s.get("core.ui.ally_list.pet_arena.need_at_least_one"));
            snd("core.fail1");
            set_reupdate();
        }
        else
        {
            snd("core.ok1");
            return UIMenuCtrlAlly::Result::finish(1);
        }
    }
    else if (cdata[_p].state() == Character::State::pet_dead)
    {
        txt(i18n::s.get("core.ui.ally_list.pet_arena.is_dead", cdata[_p]));
        snd("core.fail1");
        set_reupdate();
    }
    else if (followerin(_p) == 0)
    {
        if (i >= arenaop(1))
        {
            snd("core.fail1");
            txt(i18n::s.get("core.ui.ally_list.pet_arena.too_many"));
            set_reupdate();
        }
        else
        {
            followerin(_p) = 1;
            snd("core.ok1");
        }
    }
    else
    {
        followerin(_p) = 0;
        snd("core.ok1");
    }
    return none;
}

optional<UIMenuCtrlAlly::Result> UIMenuCtrlAlly::on_key(
    const std::string& action)
{
    if (auto id = get_selected_item())
    {
        if (_operation == ControlAllyOperation::gene_engineer)
        {
            return _select_gene_engineer(*id);
        }
        else if (_operation == ControlAllyOperation::pet_arena)
        {
            return _select_pet_arena(*id);
        }
        else
        {
            return UIMenuCtrlAlly::Result::finish(list(0, _index));
        }
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
        return UIMenuCtrlAlly::Result::cancel();
    }

    return none;
}

} // namespace ui
} // namespace elona
