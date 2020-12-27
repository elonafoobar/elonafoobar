#include "ui_menu_hire.hpp"

#include "../audio.hpp"
#include "../calc.hpp"
#include "../draw.hpp"
#include "../game.hpp"
#include "../i18n.hpp"



namespace elona
{
namespace ui
{

bool UIMenuHire::_should_display_chara(const Character& chara)
{
    if (_operation == HireOperation::revive)
    {
        if (chara.state() != Character::State::pet_dead &&
            chara.state() != Character::State::villager_dead)
        {
            return false;
        }
    }
    else
    {
        if (_operation == HireOperation::hire)
        {
            if (chara.state() != Character::State::servant_being_selected)
            {
                return false;
            }
        }
        else if (chara.state() != Character::State::alive)
        {
            return false;
        }
        if (chara.is_player_or_ally())
        {
            if (chara.current_map != game()->current_map)
            {
                return false;
            }
        }
    }
    if (chara.is_player())
    {
        return false;
    }
    if (chara.is_escorted_in_sub_quest() == 1)
    {
        return false;
    }

    return true;
}

void UIMenuHire::_populate_list()
{
    for (auto&& cnt : cdata.all())
    {
        if (_should_display_chara(cnt))
        {
            list(0, listmax) = cnt.index;
            list(1, listmax) = -cnt.level;
            ++listmax;
        }
    }
    sort_list_by_column1();
}

bool UIMenuHire::init()
{
    snd("core.pop2");
    listmax = 0;
    page = 0;
    pagesize = 16;
    cs = 0;
    cs_bk = -1;
    windowshadow = 1;

    _populate_list();

    return true;
}

void UIMenuHire::update()
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

void UIMenuHire::_draw_topic()
{
    if (_operation == HireOperation::move)
    {
        s = i18n::s.get("core.ui.npc_list.wage");
    }
    else
    {
        s = i18n::s.get("core.ui.npc_list.init_cost");
    }
    if (_operation != HireOperation::revive)
    {
        display_topic(s, wx + 490, wy + 36);
    }
}

void UIMenuHire::_draw_window()
{
    ui_display_window(
        i18n::s.get("core.ui.npc_list.title"),
        strhint2 + strhint3,
        (windoww - 700) / 2 + inf_screenx,
        winposy(448),
        700,
        448);
    display_topic(i18n::s.get("core.ui.npc_list.name"), wx + 28, wy + 36);
    display_topic(i18n::s.get("core.ui.npc_list.info"), wx + 350, wy + 36);

    _draw_topic();
}

void UIMenuHire::_draw_key(int cnt)
{
    if (cnt % 2 == 0)
    {
        boxf(wx + 70, wy + 66 + cnt * 19, 600, 18, {12, 14, 16, 16});
    }
    display_key(wx + 58, wy + 66 + cnt * 19 - 2, cnt);
}

void UIMenuHire::_draw_keys()
{
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
        _draw_key(cnt);
    }
}

void UIMenuHire::_draw_list_entry_pic(int cnt, const Character& chara)
{
    draw_chara_scale_height(chara, wx + 40, wy + 74 + cnt * 19 - 8);
}

void UIMenuHire::_draw_list_entry_name(int cnt, const Character& chara)
{
    const auto chara_name = strutil::take_by_width(chara.name, 36);
    cs_list(cs == cnt, chara_name, wx + 84, wy + 66 + cnt * 19 - 1);
}

void UIMenuHire::_draw_list_entry_info(int cnt, const Character& chara)
{
    std::string level = "Lv."s + chara.level + " "s;

    if (chara.sex == 0)
    {
        level += cnven(i18n::s.get("core.ui.sex3.male"));
    }
    else
    {
        level += cnven(i18n::s.get("core.ui.sex3.female"));
    }

    level += i18n::s.get("core.ui.npc_list.age_counter", calc_age(chara));

    mes(wx + 372, wy + 66 + cnt * 19 + 2, level);
}

void UIMenuHire::_draw_list_entry_cost(int cnt, const Character& chara)
{
    if (_operation != HireOperation::revive)
    {
        std::string text;
        int cost = calc_servant_hire_cost(chara);

        if (_operation == HireOperation::hire)
        {
            text = ""s + (cost * 20) + "("s + cost + ")"s;
        }
        else
        {
            text = ""s + cost;
        }

        mes(wx + 512,
            wy + 66 + cnt * 19 + 2,
            i18n::s.get("core.ui.npc_list.gold_counter", text));
    }
}


void UIMenuHire::_draw_list_entry(int cnt, const Character& chara)
{
    _draw_list_entry_pic(cnt, chara);
    _draw_list_entry_name(cnt, chara);
    _draw_list_entry_info(cnt, chara);
    _draw_list_entry_cost(cnt, chara);
}

void UIMenuHire::_draw_list_entries()
{
    font(14 - en * 2);
    cs_listbk();
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }

        int chara_index = list(0, p);
        const Character& chara = cdata[chara_index];

        _draw_list_entry(cnt, chara);
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
}

void UIMenuHire::draw()
{
    _draw_window();
    _draw_keys();
    _draw_list_entries();
}

optional<UIMenuHire::ResultType> UIMenuHire::on_key(const std::string& action)
{
    if (auto selected = get_selected_item())
    {
        return UIMenuHire::Result::finish(*selected);
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
        return UIMenuHire::Result::cancel();
    }

    return none;
}

} // namespace ui
} // namespace elona
