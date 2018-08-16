#include "ability.hpp"
#include "activity.hpp"
#include "adventurer.hpp"
#include "animation.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "config.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "mef.hpp"
#include "shop.hpp"
#include "status_ailment.hpp"
#include "talk.hpp"
#include "ui.hpp"
#include "variables.hpp"

namespace elona
{

namespace
{

talk_result_t _talk_hv_visitor()
{
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.visitor.wanted_to_say_hi", cdata[tc]);
    tc = tc * 1 + 0;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::_(u8"ui", u8"more");
    ++listmax;
    chatesc = 1;
    talk_window_query();
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return talk_result_t::talk_end;
        }
    }
    return talk_result_t::talk_end;
}


void _adventurer_give_new_year_gift()
{
    flt();
    int stat = itemcreate(
        -1, 752, cdata.player().position.x, cdata.player().position.y, 0);
    if (stat != 0)
    {
        inv[ci].param3 = cdata[tc].impression + rnd(50);
    }
    txt(i18n::s.get(
        "core.locale.talk.visitor.adventurer.new_year.throws",
        cdata[tc],
        inv[ci]));
}

talk_result_t _talk_hv_adventurer_new_year()
{
    listmax = 0;
    buff = i18n::s.get(
        "core.locale.talk.visitor.adventurer.new_year.happy_new_year",
        cdata[tc]);
    tc = tc * 1 + 0;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::_(u8"ui", u8"more");
    ++listmax;
    chatesc = 1;
    talk_window_query();
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return talk_result_t::talk_end;
        }
    }
    listmax = 0;
    buff = i18n::s.get(
        "core.locale.talk.visitor.adventurer.new_year.gift", cdata[tc]);
    tc = tc * 1 + 0;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::_(u8"ui", u8"more");
    ++listmax;
    chatesc = 1;
    talk_window_query();
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return talk_result_t::talk_end;
        }
    }

    _adventurer_give_new_year_gift();

    return talk_result_t::talk_end;
}

void _adventurer_hate_action()
{
    txt(i18n::s.get(
        "core.locale.talk.visitor.adventurer.hate.text", cdata[tc]));
    if (rnd(2) == 0)
    {
        for (int cnt = 0; cnt < 28; ++cnt)
        {
            tlocx = cdata[tc].position.x + rnd(3) - rnd(3);
            tlocy = cdata[tc].position.y - rnd(3) + rnd(3);
            if (tlocx < 0 || tlocy < 0 || tlocx >= mdata_map_width
                || tlocy >= mdata_map_height)
            {
                continue;
            }
            if (tlocx == cdata[tc].position.x)
            {
                if (tlocy == cdata[tc].position.y)
                {
                    continue;
                }
            }
            txt(i18n::s.get(
                "core.locale.talk.visitor.adventurer.hate.throws", cdata[tc]));
            snd(91);
            ccbk = cc;
            cc = tc;
            throwing_object_animation(
                {tlocx, tlocy}, cdata[cc].position, 223, 0)
                .play();
            cc = ccbk;
            mef_add(tlocx, tlocy, 5, 24, rnd(15) + 20, 50, tc);
            mapitem_fire(tlocx, tlocy);
        }
    }
    else
    {
        for (int cnt = 0, cnt_end = (8 + rnd(6)); cnt < cnt_end; ++cnt)
        {
            flt();
            itemcreate(-1, 704, -1, -1, 0);
            txt(i18n::s.get("core.locale.food.vomits", cdata[tc]));
            snd(104);
            await(config::instance().animewait / 2);
            update_screen();
        }
    }
}

talk_result_t _talk_hv_adventurer_hate()
{
    listmax = 0;
    buff = i18n::s.get(
        "core.locale.talk.visitor.adventurer.hate.dialog", cdata[tc]);
    tc = tc * 1 + 0;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::_(u8"ui", u8"more");
    ++listmax;
    chatesc = 1;
    talk_window_query();
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return talk_result_t::talk_end;
        }
    }

    _adventurer_hate_action();

    return talk_result_t::talk_end;
}

void _adventurer_become_best_friend()
{
    cdata[tc].is_best_friend() = true;
    flt();
    itemcreate(
        -1, 730, cdata.player().position.x, cdata.player().position.y, 0);
    txt(i18n::s.get("core.locale.talk.visitor.receive", inv[ci], cdata[tc]));
    txt(i18n::s.get("core.locale.talk.visitor.adventurer.like.wonder_if"));
}

void _talk_hv_adventurer_best_friend()
{
    listmax = 0;
    buff = i18n::s.get(
        "core.locale.talk.visitor.adventurer.like.dialog", cdata[tc]);
    tc = tc * 1 + 0;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::_(u8"ui", u8"more");
    ++listmax;
    chatesc = 1;
    talk_window_query();

    _adventurer_become_best_friend();

    // NOTE: this dialog falls through.
    listmax = 0;
}

int _adventurer_get_trained_skill()
{
    int stat = advfavoriteskill(tc);
    int val = rtval(rnd(stat));
    if (cdata[tc].impression >= 300)
    {
        if (rnd(3) == 0)
        {
            stat = advfavoritestat(tc);
            val = stat;
        }
    }
    return val;
}

void _adventurer_learn_skill()
{
    cdata.player().platinum_coin -= calclearncost(csskill, 0, true);
    chara_gain_skill(cdata[cc], csskill);
    ++gdata_number_of_learned_skills_by_trainer;
}

void _adventurer_train_skill()
{
    cdata.player().platinum_coin -= calctraincost(csskill, 0, true);
    modify_potential(
        cdata[cc],
        csskill,
        clamp(
            15 - sdata.get(csskill, cc).potential / 15,
            2,
            15 - (csskill < 18) * 10));
}

talk_result_t _talk_hv_adventurer_train()
{
    int stat = _adventurer_get_trained_skill();
    csskill = stat;

    list(0, listmax) = 0;
    listn(0, listmax) =
        i18n::s.get("core.locale.talk.visitor.adventurer.train.choices.pass");
    ++listmax;
    if (sdata.get(csskill, 0).original_level == 0)
    {
        buff = i18n::s.get(
            "core.locale.talk.visitor.adventurer.train.learn."
            "dialog",
            i18n::_(u8"ability", std::to_string(csskill), u8"name"),
            std::to_string(calclearncost(csskill, cc, true))
                + i18n::_(u8"ui", u8"platinum"),
            cdata[tc]);
        if (cdata.player().platinum_coin >= calclearncost(csskill, cc, true))
        {
            list(0, listmax) = 1;
            listn(0, listmax) = i18n::s.get(
                "core.locale.talk.visitor.adventurer.train.choices."
                "learn");
            ++listmax;
        }
    }
    else
    {
        buff = i18n::s.get(
            "core.locale.talk.visitor.adventurer.train.train."
            "dialog",
            i18n::_(u8"ability", std::to_string(csskill), u8"name"),
            std::to_string(calclearncost(csskill, cc, true))
                + i18n::_(u8"ui", u8"platinum"),
            cdata[tc]);
        if (cdata.player().platinum_coin >= calctraincost(csskill, cc, true))
        {
            list(0, listmax) = 2;
            listn(0, listmax) = i18n::s.get(
                "core.locale.talk.visitor.adventurer.train.choices."
                "train");
            ++listmax;
        }
    }
    chatesc = 1;
    int chatval_ = talk_window_query();
    if (chatval_ == 0 || chatval_ == -1)
    {
        listmax = 0;
        buff = i18n::s.get(
            "core.locale.talk.visitor.adventurer.train.pass", cdata[tc]);
        tc = tc * 1 + 0;
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::_(u8"ui", u8"more");
        ++listmax;
        chatesc = 1;
        talk_window_query();
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return talk_result_t::talk_end;
            }
        }
        return talk_result_t::talk_end;
    }
    snd(12);
    if (chatval_ == 1)
    {
        _adventurer_learn_skill();

        listmax = 0;
        buff = i18n::s.get(
            "core.locale.talk.visitor.adventurer.train.learn.after", cdata[tc]);
        tc = tc * 1 + 0;
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::_(u8"ui", u8"more");
        ++listmax;
        chatesc = 1;
        talk_window_query();
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return talk_result_t::talk_end;
            }
        }
    }
    if (chatval_ == 2)
    {
        _adventurer_train_skill();

        listmax = 0;
        buff = i18n::s.get(
            "core.locale.talk.visitor.adventurer.train.train.after", cdata[tc]);
        tc = tc * 1 + 0;
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::_(u8"ui", u8"more");
        ++listmax;
        chatesc = 1;
        talk_window_query();
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return talk_result_t::talk_end;
            }
        }
    }
    return talk_result_t::talk_end;
}

void _adventurer_receive_coin()
{
    if (inv_getfreeid(-1) == -1)
    {
        txt(
            i18n::s.get("core.locale.talk.visitor.adventurer."
                        "friendship.no_empty_spot"));
    }
    else
    {
        if (rnd(4))
        {
            p = 55;
        }
        else
        {
            p = 622;
        }
        flt();
        itemcreate(
            -1, p, cdata.player().position.x, cdata.player().position.y, 0);
        txt(i18n::s.get(
            "core.locale.talk.visitor.receive", inv[ci], cdata[tc]));
        snd(14);
    }
}

talk_result_t _talk_hv_adventurer_friendship()
{
    listmax = 0;
    buff = i18n::s.get(
        "core.locale.talk.visitor.adventurer.friendship.dialog", cdata[tc]);
    tc = tc * 1 + 0;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::_(u8"ui", u8"more");
    ++listmax;
    chatesc = 1;
    talk_window_query();
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return talk_result_t::talk_end;
        }
    }

    _adventurer_receive_coin();

    return talk_result_t::talk_end;
}

void _adventurer_receive_souvenir()
{
    if (inv_getfreeid(0) == -1)
    {
        txt(
            i18n::s.get("core.locale.talk.visitor.adventurer."
                        "souvenir.inventory_is_full"));
    }
    else
    {
        flt();
        itemcreate(0, 729, -1, -1, 0);
        txt(i18n::s.get(
            "core.locale.talk.visitor.adventurer.souvenir.receive", inv[ci]));
        snd(14);
    }
}

talk_result_t _talk_hv_adventurer_souvenir()
{
    listmax = 0;
    buff = i18n::s.get(
        "core.locale.talk.visitor.adventurer.souvenir.dialog", cdata[tc]);
    tc = tc * 1 + 0;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::_(u8"ui", u8"more");
    ++listmax;
    chatesc = 1;
    talk_window_query();
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return talk_result_t::talk_end;
        }
    }

    _adventurer_receive_souvenir();

    return talk_result_t::talk_end;
}

void _adventurer_receive_materials()
{
    txt(i18n::s.get(
        "core.locale.talk.visitor.adventurer.materials.receive", cdata[tc]));
    efid = 1117;
    efp = 100;
    tc = 0;
    magic();
}

talk_result_t _talk_hv_adventurer_materials()
{
    listmax = 0;
    buff = i18n::s.get(
        "core.locale.talk.visitor.adventurer.materials.dialog", cdata[tc]);
    tc = tc * 1 + 0;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::_(u8"ui", u8"more");
    ++listmax;
    chatesc = 1;
    talk_window_query();
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return talk_result_t::talk_end;
        }
    }

    _adventurer_receive_materials();

    return talk_result_t::talk_end;
}

talk_result_t _talk_hv_adventurer_favorite_skill()
{
    int stat = advfavoriteskill(tc);
    csskill = rtval(rnd(stat));
    listmax = 0;
    buff = i18n::s.get(
        "core.locale.talk.visitor.adventurer.favorite_skill.dialog",
        i18n::_(u8"ability", std::to_string(csskill), u8"name"),
        cdata[tc]);
    tc = tc * 1 + 0;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::_(u8"ui", u8"more");
    ++listmax;
    chatesc = 1;
    talk_window_query();
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return talk_result_t::talk_end;
        }
    }
    return talk_result_t::talk_end;
}

talk_result_t _talk_hv_adventurer_favorite_stat()
{
    int stat = advfavoritestat(tc);
    csskill = stat;
    listmax = 0;
    buff = i18n::s.get(
        "core.locale.talk.visitor.adventurer.favorite_stat.dialog",
        i18n::_(u8"ability", std::to_string(csskill), u8"name"),
        cdata[tc]);
    tc = tc * 1 + 0;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::_(u8"ui", u8"more");
    ++listmax;
    chatesc = 1;
    talk_window_query();
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return talk_result_t::talk_end;
        }
    }
    return talk_result_t::talk_end;
}

void _adventurer_hold_conversation()
{
    txt(i18n::s.get(
        "core.locale.talk.visitor.adventurer.conversation.hold", cdata[tc]));
    chara_modify_impression(cdata[tc], 10);
}

talk_result_t _talk_hv_adventurer_conversation()
{
    listmax = 0;
    buff = i18n::s.get(
        "core.locale.talk.visitor.adventurer.conversation.dialog",
        cdata.player(),
        cdata[tc]);
    tc = tc * 1 + 0;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::_(u8"ui", u8"more");
    ++listmax;
    chatesc = 1;
    talk_window_query();
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return talk_result_t::talk_end;
        }
    }

    _adventurer_hold_conversation();

    return talk_result_t::talk_end;
}

void _adventurer_drink()
{
    snd(17);
    txt(i18n::s.get(
        "core.locale.talk.visitor.adventurer.drink.cheers", cdata[tc]));
    txtef(9);
    txt(i18n::s.get_enum("core.locale.magic.alcohol.normal", rnd(7)));
    dmgcon(tc, status_ailment_t::drunk, 1000);
    dmgcon(cc, status_ailment_t::drunk, 1000);
    chara_modify_impression(cdata[tc], 15);
}

talk_result_t _talk_hv_adventurer_drink()
{
    listmax = 0;
    buff = i18n::s.get(
        "core.locale.talk.visitor.adventurer.drink.dialog", cdata[tc]);
    tc = tc * 1 + 0;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::_(u8"ui", u8"more");
    ++listmax;
    chatesc = 1;
    talk_window_query();
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return talk_result_t::talk_end;
        }
    }

    _adventurer_drink();

    return talk_result_t::talk_end;
}

talk_result_t _talk_hv_adventurer()
{
    if (gdata_month == 1 && rnd(4))
    {
        return _talk_hv_adventurer_new_year();
    }
    if (cdata[tc].impression < 25)
    {
        return _talk_hv_adventurer_hate();
    }
    if (cdata[tc].impression >= 100 && !cdata[tc].is_best_friend()
        && inv_getfreeid(-1) != -1)
    {
        // NOTE: this dialog falls through.
        _talk_hv_adventurer_best_friend();
    }
    if (rnd(4) == 0 && cdata[tc].impression >= 150)
    {
        return _talk_hv_adventurer_train();
    }
    if (rnd(5) == 0 && cdata[tc].impression >= 150)
    {
        return _talk_hv_adventurer_friendship();
    }
    if (rnd(4) == 0 && cdata[tc].impression >= 100)
    {
        return _talk_hv_adventurer_souvenir();
    }
    if (rnd(5) == 0 && cdata[tc].impression >= 100)
    {
        return _talk_hv_adventurer_materials();
    }
    if (rnd(8) == 0)
    {
        return _talk_hv_adventurer_favorite_skill();
    }
    if (rnd(10) == 0)
    {
        return _talk_hv_adventurer_favorite_stat();
    }
    if (rnd(3) == 0 && cdata[tc].impression >= 75)
    {
        return _talk_hv_adventurer_conversation();
    }
    if (rnd(3) == 0)
    {
        return _talk_hv_adventurer_drink();
    }
    return _talk_hv_visitor();
}

int _trainer_calc_skills()
{
    int plat = 3;

    gdata_last_month_when_trainer_visited = gdata_month;
    buff = i18n::s.get(
        "core.locale.talk.visitor.trainer.dialog.member",
        guildname(),
        plat,
        cdata[tc]);
    if (gdata_belongs_to_mages_guild != 0)
    {
        p(0) = 16;
        p(1) = 15;
        p(2) = 14;
        p(3) = -1;
    }
    else if (gdata_belongs_to_fighters_guild != 0)
    {
        p(0) = 10;
        p(1) = 11;
        p(2) = 12;
        p(3) = -1;
    }
    else if (gdata_belongs_to_thieves_guild != 0)
    {
        p(0) = 12;
        p(1) = 13;
        p(2) = 11;
        p(3) = 14;
        p(4) = -1;
    }
    else
    {
        plat = 4;
        p(3) = -1;
        i = rnd(6);
        for (int cnt = 0; cnt < 3; ++cnt)
        {
            p(cnt) = 10 + cnt + i;
        }
        buff = i18n::s.get(
            "core.locale.talk.visitor.trainer.dialog.nonmember",
            plat,
            cdata[tc]);
    }

    return plat;
}

void _trainer_do_training(int plat, int chatval_)
{
    cdata.player().platinum_coin -= plat;
    snd(61);
    txtef(2);
    txt(i18n::s.get(
        "core.locale.talk.visitor.trainer.potential_expands",
        cdata.player(),
        i18n::_(u8"ability", std::to_string(chatval_), u8"name")));
    modify_potential(cdata.player(), chatval_, 10);
}

talk_result_t _talk_hv_trainer()
{
    int plat = 0;

    if (gdata_last_month_when_trainer_visited == gdata_month)
    {
        listmax = 0;
        buff = i18n::s.get(
            "core.locale.talk.visitor.trainer.no_more_this_month", cdata[tc]);
        tc = tc * 1 + 0;
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::_(u8"ui", u8"more");
        ++listmax;
        chatesc = 1;
        talk_window_query();
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return talk_result_t::talk_end;
            }
        }
        return talk_result_t::talk_end;
    }

    // modifies buff/p
    plat = _trainer_calc_skills();

    list(0, listmax) = 0;
    listn(0, listmax) =
        i18n::s.get("core.locale.talk.visitor.trainer.choices.not_today");
    ++listmax;
    if (cdata.player().platinum_coin >= plat)
    {
        for (int cnt = 0; cnt < 8; ++cnt)
        {
            if (p(cnt) == -1)
            {
                break;
            }
            list(0, listmax) = p(cnt);
            listn(0, listmax) = i18n::s.get(
                "core.locale.talk.visitor.trainer.choices.improve",
                i18n::_(u8"ability", std::to_string(p(cnt)), u8"name"));
            ++listmax;
        }
    }
    int chatval_ = talk_window_query();
    if (chatval_ == 0 || chatval_ == -1)
    {
        listmax = 0;
        buff =
            i18n::s.get("core.locale.talk.visitor.trainer.regret", cdata[tc]);
        tc = tc * 1 + 0;
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::_(u8"ui", u8"more");
        ++listmax;
        chatesc = 1;
        talk_window_query();
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return talk_result_t::talk_end;
            }
        }
        return talk_result_t::talk_end;
    }

    _trainer_do_training(plat, chatval_);

    listmax = 0;
    buff = i18n::s.get("core.locale.talk.visitor.trainer.after", cdata[tc]);
    tc = tc * 1 + 0;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::_(u8"ui", u8"more");
    ++listmax;
    chatesc = 1;
    talk_window_query();
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return talk_result_t::talk_end;
        }
    }
    return talk_result_t::talk_end;
}

void _beggar_give()
{
    p = cdata.player().gold / 20 + 1;
    txt(i18n::s.get("core.locale.talk.visitor.beggar.spare", p(0), cdata[tc]));
    cdata.player().gold -= p;
    snd(12);
    earn_gold(cdata[tc], p);
    modify_karma(cdata.player(), 2);
}

talk_result_t _talk_hv_beggar()
{
    if (cdata.player().gold > 0)
    {
        list(0, listmax) = 1;
        listn(0, listmax) = i18n::s.get("core.locale.talk.visitor.choices.yes");
        ++listmax;
    }
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.locale.talk.visitor.choices.no");
    ++listmax;
    buff = i18n::s.get("core.locale.talk.visitor.beggar.dialog", cdata[tc]);
    int chatval_ = talk_window_query();
    if (chatval_ == 1)
    {
        _beggar_give();

        listmax = 0;
        buff = i18n::s.get("core.locale.talk.visitor.beggar.after", cdata[tc]);
        tc = tc * 1 + 0;
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::_(u8"ui", u8"more");
        ++listmax;
        chatesc = 1;
        talk_window_query();
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return talk_result_t::talk_end;
            }
        }
        return talk_result_t::talk_end;
    }
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.visitor.beggar.cheap");
    tc = tc * 1 + 0;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::_(u8"ui", u8"more");
    ++listmax;
    chatesc = 1;
    talk_window_query();
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return talk_result_t::talk_end;
        }
    }
    return talk_result_t::talk_end;
}

talk_result_t _talk_hv_punk()
{
    list(0, listmax) = 1;
    listn(0, listmax) = i18n::s.get("core.locale.talk.visitor.choices.yes");
    ++listmax;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.locale.talk.visitor.choices.no");
    ++listmax;
    buff = i18n::s.get("core.locale.talk.visitor.punk.dialog", cdata[tc]);
    int chatval_ = talk_window_query();
    if (chatval_ == 1)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.npc.common.sex.start", cdata[tc]);
        tc = tc * 1 + 0;
        list(0, listmax) = 0;
        listn(0, listmax) =
            i18n::s.get("core.locale.talk.npc.common.sex.response");
        ++listmax;
        chatesc = 1;
        talk_window_query();
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return talk_result_t::talk_end;
            }
        }

        continuous_action_sex();

        return talk_result_t::talk_end;
    }
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.visitor.punk.hump");
    tc = tc * 1 + 0;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::_(u8"ui", u8"more");
    ++listmax;
    chatesc = 1;
    talk_window_query();
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return talk_result_t::talk_end;
        }
    }
    return talk_result_t::talk_end;
}

talk_result_t _talk_hv_mysterious_producer()
{

    list(0, listmax) = 1;
    listn(0, listmax) = i18n::s.get("core.locale.talk.visitor.choices.yes");
    ++listmax;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.locale.talk.visitor.choices.no");
    ++listmax;
    buff = i18n::s.get(
        "core.locale.talk.visitor.mysterious_producer.want_to_be_star",
        cdata[tc]);
    int chatval_ = talk_window_query();
    if (chatval_ == 1)
    {
        listmax = 0;
        buff = i18n::s.get(
            "core.locale.talk.visitor.mysterious_producer.no_turning_back",
            cdata[tc]);
        tc = tc * 1 + 0;
        list(0, listmax) = 0;
        listn(0, listmax) =
            i18n::s.get("core.locale.talk.npc.common.sex.response");
        ++listmax;
        chatesc = 1;
        talk_window_query();
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return talk_result_t::talk_end;
            }
        }

        continuous_action_sex();

        return talk_result_t::talk_end;
    }
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.visitor.punk.hump");
    tc = tc * 1 + 0;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::_(u8"ui", u8"more");
    ++listmax;
    chatesc = 1;
    talk_window_query();
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return talk_result_t::talk_end;
        }
    }
    return talk_result_t::talk_end;
}

void _merchant_buy()
{
    invctrl = 11;
    invfile = cdata[tc].shop_store_id;
    shop_sell_item();
    screenupdate = -1;
    update_screen();
    cs = 0;
    buff = "";
}

void _merchant_sell()
{
    invctrl = 12;
    invfile = cdata[tc].shop_store_id;
    shop_sell_item();
    cc = 0;
    screenupdate = -1;
    update_screen();
    cs = 0;
    buff = "";
}

talk_result_t _talk_hv_merchant()
{
    list(0, listmax) = 0;
    listn(0, listmax) =
        i18n::s.get("core.locale.talk.visitor.merchant.choices.buy");
    ++listmax;
    list(0, listmax) = 1;
    listn(0, listmax) =
        i18n::s.get("core.locale.talk.visitor.merchant.choices.sell");
    ++listmax;
    list(0, listmax) = 2;
    listn(0, listmax) =
        i18n::s.get("core.locale.talk.visitor.merchant.choices.not_now");
    ++listmax;
    buff = i18n::s.get("core.locale.talk.visitor.merchant.dialog", cdata[tc]);
    int chatval_ = talk_window_query();
    if (chatval_ == 0)
    {
        _merchant_buy();
        return talk_result_t::talk_house_visitor;
    }
    if (chatval_ == 1)
    {
        _merchant_sell();
        return talk_result_t::talk_house_visitor;
    }
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.visitor.merchant.regret", cdata[tc]);
    tc = tc * 1 + 0;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::_(u8"ui", u8"more");
    ++listmax;
    chatesc = 1;
    talk_window_query();
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return talk_result_t::talk_end;
        }
    }
    cdata[tc].character_role = 2002;
    return talk_result_t::talk_end;
}

} // namespace

talk_result_t talk_house_visitor()
{
    listmax = 0;
    cc = 0;
    switch (cdata[tc].character_role)
    {
    case 13: return _talk_hv_adventurer();
    case 2005: return _talk_hv_trainer();
    case 2002: return _talk_hv_visitor();
    case 2000: return _talk_hv_beggar();
    case 2001: return _talk_hv_punk();
    case 2006: return _talk_hv_mysterious_producer();
    case 2003: return _talk_hv_merchant();
    }
    return talk_result_t::talk_end;
}

} // namespace elona
