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
#include "magic.hpp"
#include "map.hpp"
#include "mef.hpp"
#include "message.hpp"
#include "shop.hpp"
#include "status_ailment.hpp"
#include "talk.hpp"
#include "text.hpp"
#include "ui.hpp"
#include "variables.hpp"



namespace elona
{

namespace
{

TalkResult _talk_hv_visitor(Character& speaker)
{
    listmax = 0;
    buff = i18n::s.get("core.talk.visitor.wanted_to_say_hi", speaker);
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.more");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker);
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }
    return TalkResult::talk_end;
}



void _adventurer_give_new_year_gift(Character& speaker)
{
    flt();
    if (const auto item = itemcreate_extra_inv(752, cdata.player().position, 0))
    {
        item->param3 = speaker.impression + rnd(50);
        txt(i18n::s.get(
            "core.talk.visitor.adventurer.new_year.throws", speaker, *item));
    }
}



TalkResult _talk_hv_adventurer_new_year(Character& speaker)
{
    listmax = 0;
    buff = i18n::s.get(
        "core.talk.visitor.adventurer.new_year.happy_new_year", speaker);
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.more");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker);
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }
    listmax = 0;
    buff = i18n::s.get("core.talk.visitor.adventurer.new_year.gift", speaker);
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.more");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker);
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }

    _adventurer_give_new_year_gift(speaker);

    return TalkResult::talk_end;
}



void _adventurer_hate_action(Character& speaker)
{
    txt(i18n::s.get("core.talk.visitor.adventurer.hate.text", speaker));
    if (rnd(2) == 0)
    {
        for (int cnt = 0; cnt < 28; ++cnt)
        {
            tlocx = speaker.position.x + rnd(3) - rnd(3);
            tlocy = speaker.position.y - rnd(3) + rnd(3);
            if (tlocx < 0 || tlocy < 0 || tlocx >= map_data.width ||
                tlocy >= map_data.height)
            {
                continue;
            }
            if (tlocx == speaker.position.x)
            {
                if (tlocy == speaker.position.y)
                {
                    continue;
                }
            }
            txt(i18n::s.get(
                "core.talk.visitor.adventurer.hate.throws", speaker));
            snd("core.throw2");
            ThrowingObjectAnimation({tlocx, tlocy}, speaker.position, 223, 0)
                .play();
            mef_add(tlocx, tlocy, 5, 24, rnd(15) + 20, 50, speaker.index);
            mapitem_fire(speaker, tlocx, tlocy);
        }
    }
    else
    {
        for (int cnt = 0, cnt_end = (8 + rnd(6)); cnt < cnt_end; ++cnt)
        {
            flt();
            itemcreate_extra_inv(704, -1, -1, 0);
            txt(i18n::s.get("core.food.vomits", speaker));
            snd("core.vomit");
            await(g_config.animation_wait() / 2);
            update_screen();
        }
    }
}



TalkResult _talk_hv_adventurer_hate(Character& speaker)
{
    listmax = 0;
    buff = i18n::s.get("core.talk.visitor.adventurer.hate.dialog", speaker);
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.more");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker);
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }

    _adventurer_hate_action(speaker);

    return TalkResult::talk_end;
}



void _adventurer_become_best_friend(Character& speaker)
{
    speaker.is_best_friend() = true;
    flt();
    if (const auto item = itemcreate_extra_inv(730, cdata.player().position, 0))
    {
        txt(i18n::s.get("core.talk.visitor.receive", *item, speaker));
        txt(i18n::s.get("core.talk.visitor.adventurer.like.wonder_if"));
    }
}



void _talk_hv_adventurer_best_friend(Character& speaker)
{
    listmax = 0;
    buff = i18n::s.get("core.talk.visitor.adventurer.like.dialog", speaker);
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.more");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker);

    _adventurer_become_best_friend(speaker);

    // NOTE: this dialog falls through.
    listmax = 0;
}



int _adventurer_get_trained_skill(Character& speaker)
{
    int stat = advfavoriteskill(speaker.index);
    int val = rtval(rnd(stat));
    if (speaker.impression >= 300)
    {
        if (rnd(3) == 0)
        {
            stat = advfavoritestat(speaker.index);
            val = stat;
        }
    }
    return val;
}



void _adventurer_learn_skill(int skill_id)
{
    cdata.player().platinum_coin -= calclearncost(skill_id, 0, true);
    chara_gain_skill(cdata.player(), skill_id);
    ++game_data.number_of_learned_skills_by_trainer;
}



void _adventurer_train_skill(int skill_id)
{
    cdata.player().platinum_coin -= calctraincost(skill_id, 0, true);
    modify_potential(
        cdata.player(),
        skill_id,
        clamp(
            15 - sdata.get(skill_id, cdata.player().index).potential / 15,
            2,
            15 - (skill_id < 18) * 10));
}



TalkResult _talk_hv_adventurer_train(Character& speaker)
{
    int skill_id = _adventurer_get_trained_skill(speaker);

    list(0, listmax) = 0;
    listn(0, listmax) =
        i18n::s.get("core.talk.visitor.adventurer.train.choices.pass");
    ++listmax;
    if (sdata.get(skill_id, 0).original_level == 0)
    {
        buff = i18n::s.get(
            "core.talk.visitor.adventurer.train.learn.dialog",
            the_ability_db.get_text(skill_id, "name"),
            std::to_string(
                calclearncost(skill_id, cdata.player().index, true)) +
                i18n::s.get("core.ui.platinum"),
            speaker);
        if (cdata.player().platinum_coin >=
            calclearncost(skill_id, cdata.player().index, true))
        {
            list(0, listmax) = 1;
            listn(0, listmax) =
                i18n::s.get("core.talk.visitor.adventurer.train.choices.learn");
            ++listmax;
        }
    }
    else
    {
        buff = i18n::s.get(
            "core.talk.visitor.adventurer.train.train.dialog",
            the_ability_db.get_text(skill_id, "name"),
            std::to_string(
                calclearncost(skill_id, cdata.player().index, true)) +
                i18n::s.get("core.ui.platinum"),
            speaker);
        if (cdata.player().platinum_coin >=
            calctraincost(skill_id, cdata.player().index, true))
        {
            list(0, listmax) = 2;
            listn(0, listmax) =
                i18n::s.get("core.talk.visitor.adventurer.train.choices.train");
            ++listmax;
        }
    }
    chatesc = 1;
    int chatval_ = talk_window_query(speaker);
    if (chatval_ == 0 || chatval_ == -1)
    {
        listmax = 0;
        buff = i18n::s.get("core.talk.visitor.adventurer.train.pass", speaker);
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.ui.more");
        ++listmax;
        chatesc = 1;
        talk_window_query(speaker);
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return TalkResult::talk_end;
            }
        }
        return TalkResult::talk_end;
    }
    snd("core.paygold1");
    if (chatval_ == 1)
    {
        _adventurer_learn_skill(skill_id);

        listmax = 0;
        buff = i18n::s.get(
            "core.talk.visitor.adventurer.train.learn.after", speaker);
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.ui.more");
        ++listmax;
        chatesc = 1;
        talk_window_query(speaker);
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return TalkResult::talk_end;
            }
        }
    }
    if (chatval_ == 2)
    {
        _adventurer_train_skill(skill_id);

        listmax = 0;
        buff = i18n::s.get(
            "core.talk.visitor.adventurer.train.train.after", speaker);
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.ui.more");
        ++listmax;
        chatesc = 1;
        talk_window_query(speaker);
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return TalkResult::talk_end;
            }
        }
    }
    return TalkResult::talk_end;
}



void _adventurer_receive_coin(Character& speaker)
{
    if (!inv_get_free_slot(-1))
    {
        txt(i18n::s.get(
            "core.talk.visitor.adventurer.friendship.no_empty_spot"));
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
        if (const auto item =
                itemcreate_extra_inv(p, cdata.player().position, 0))
        {
            txt(i18n::s.get("core.talk.visitor.receive", *item, speaker));
            snd("core.get1");
        }
    }
}



TalkResult _talk_hv_adventurer_friendship(Character& speaker)
{
    listmax = 0;
    buff =
        i18n::s.get("core.talk.visitor.adventurer.friendship.dialog", speaker);
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.more");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker);
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }

    _adventurer_receive_coin(speaker);

    return TalkResult::talk_end;
}



void _adventurer_receive_souvenir()
{
    if (!inv_get_free_slot(0))
    {
        txt(i18n::s.get(
            "core.talk.visitor.adventurer.souvenir.inventory_is_full"));
    }
    else
    {
        flt();
        if (const auto item = itemcreate_player_inv(729, 0))
        {
            txt(i18n::s.get(
                "core.talk.visitor.adventurer.souvenir.receive", *item));
            snd("core.get1");
        }
    }
}



TalkResult _talk_hv_adventurer_souvenir(Character& speaker)
{
    listmax = 0;
    buff = i18n::s.get("core.talk.visitor.adventurer.souvenir.dialog", speaker);
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.more");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker);
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }

    _adventurer_receive_souvenir();

    return TalkResult::talk_end;
}



void _adventurer_receive_materials(Character& speaker)
{
    txt(i18n::s.get("core.talk.visitor.adventurer.materials.receive", speaker));
    efid = 1117;
    efp = 100;
    speaker.index = 0;
    magic(cdata.player(), cdata.player());
}



TalkResult _talk_hv_adventurer_materials(Character& speaker)
{
    listmax = 0;
    buff =
        i18n::s.get("core.talk.visitor.adventurer.materials.dialog", speaker);
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.more");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker);
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }

    _adventurer_receive_materials(speaker);

    return TalkResult::talk_end;
}



TalkResult _talk_hv_adventurer_favorite_skill(Character& speaker)
{
    int stat = advfavoriteskill(speaker.index);
    int skill_id = rtval(rnd(stat));
    listmax = 0;
    buff = i18n::s.get(
        "core.talk.visitor.adventurer.favorite_skill.dialog",
        the_ability_db.get_text(skill_id, "name"),
        speaker);
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.more");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker);
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }
    return TalkResult::talk_end;
}



TalkResult _talk_hv_adventurer_favorite_stat(Character& speaker)
{
    int skill_id = advfavoritestat(speaker.index);
    listmax = 0;
    buff = i18n::s.get(
        "core.talk.visitor.adventurer.favorite_stat.dialog",
        the_ability_db.get_text(skill_id, "name"),
        speaker);
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.more");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker);
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }
    return TalkResult::talk_end;
}



void _adventurer_hold_conversation(Character& speaker)
{
    txt(i18n::s.get("core.talk.visitor.adventurer.conversation.hold", speaker));
    chara_modify_impression(speaker, 10);
}



TalkResult _talk_hv_adventurer_conversation(Character& speaker)
{
    listmax = 0;
    buff = i18n::s.get(
        "core.talk.visitor.adventurer.conversation.dialog",
        cdata.player(),
        speaker);
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.more");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker);
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }

    _adventurer_hold_conversation(speaker);

    return TalkResult::talk_end;
}



void _adventurer_drink(Character& speaker)
{
    snd("core.drink1");
    txt(i18n::s.get("core.talk.visitor.adventurer.drink.cheers", speaker));
    txt(i18n::s.get("core.magic.alcohol.normal"),
        Message::color{ColorIndex::cyan});
    status_ailment_damage(speaker, StatusAilment::drunk, 1000);
    status_ailment_damage(cdata.player(), StatusAilment::drunk, 1000);
    chara_modify_impression(speaker, 15);
}



TalkResult _talk_hv_adventurer_drink(Character& speaker)
{
    listmax = 0;
    buff = i18n::s.get("core.talk.visitor.adventurer.drink.dialog", speaker);
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.more");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker);
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }

    _adventurer_drink(speaker);

    return TalkResult::talk_end;
}



TalkResult _talk_hv_adventurer(Character& speaker)
{
    if (game_data.date.month == 1 && rnd(4))
    {
        return _talk_hv_adventurer_new_year(speaker);
    }
    if (speaker.impression < 25)
    {
        return _talk_hv_adventurer_hate(speaker);
    }
    if (speaker.impression >= 100 && !speaker.is_best_friend() &&
        inv_get_free_slot(-1))
    {
        // NOTE: this dialog falls through.
        _talk_hv_adventurer_best_friend(speaker);
    }
    if (rnd(4) == 0 && speaker.impression >= 150)
    {
        return _talk_hv_adventurer_train(speaker);
    }
    if (rnd(5) == 0 && speaker.impression >= 150)
    {
        return _talk_hv_adventurer_friendship(speaker);
    }
    if (rnd(4) == 0 && speaker.impression >= 100)
    {
        return _talk_hv_adventurer_souvenir(speaker);
    }
    if (rnd(5) == 0 && speaker.impression >= 100)
    {
        return _talk_hv_adventurer_materials(speaker);
    }
    if (rnd(8) == 0)
    {
        return _talk_hv_adventurer_favorite_skill(speaker);
    }
    if (rnd(10) == 0)
    {
        return _talk_hv_adventurer_favorite_stat(speaker);
    }
    if (rnd(3) == 0 && speaker.impression >= 75)
    {
        return _talk_hv_adventurer_conversation(speaker);
    }
    if (rnd(3) == 0)
    {
        return _talk_hv_adventurer_drink(speaker);
    }
    return _talk_hv_visitor(speaker);
}



int _trainer_calc_skills(Character& speaker)
{
    int plat = 3;

    game_data.last_month_when_trainer_visited = game_data.date.month;
    buff = i18n::s.get(
        "core.talk.visitor.trainer.dialog.member", guildname(), plat, speaker);
    if (game_data.guild.belongs_to_mages_guild != 0)
    {
        p(0) = 16;
        p(1) = 15;
        p(2) = 14;
        p(3) = -1;
    }
    else if (game_data.guild.belongs_to_fighters_guild != 0)
    {
        p(0) = 10;
        p(1) = 11;
        p(2) = 12;
        p(3) = -1;
    }
    else if (game_data.guild.belongs_to_thieves_guild != 0)
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
            "core.talk.visitor.trainer.dialog.nonmember", plat, speaker);
    }

    return plat;
}



void _trainer_do_training(int plat, int chatval_)
{
    cdata.player().platinum_coin -= plat;
    snd("core.ding3");
    txt(i18n::s.get(
            "core.talk.visitor.trainer.potential_expands",
            cdata.player(),
            the_ability_db.get_text(chatval_, "name")),
        Message::color{ColorIndex::green});
    modify_potential(cdata.player(), chatval_, 10);
}



TalkResult _talk_hv_trainer(Character& speaker)
{
    int plat = 0;

    if (game_data.last_month_when_trainer_visited == game_data.date.month)
    {
        listmax = 0;
        buff = i18n::s.get(
            "core.talk.visitor.trainer.no_more_this_month", speaker);
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.ui.more");
        ++listmax;
        chatesc = 1;
        talk_window_query(speaker);
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return TalkResult::talk_end;
            }
        }
        return TalkResult::talk_end;
    }

    // modifies buff/p
    plat = _trainer_calc_skills(speaker);

    list(0, listmax) = 0;
    listn(0, listmax) =
        i18n::s.get("core.talk.visitor.trainer.choices.not_today");
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
                "core.talk.visitor.trainer.choices.improve",
                the_ability_db.get_text(p(cnt), "name"));
            ++listmax;
        }
    }
    int chatval_ = talk_window_query(speaker);
    if (chatval_ == 0 || chatval_ == -1)
    {
        listmax = 0;
        buff = i18n::s.get("core.talk.visitor.trainer.regret", speaker);
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.ui.more");
        ++listmax;
        chatesc = 1;
        talk_window_query(speaker);
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return TalkResult::talk_end;
            }
        }
        return TalkResult::talk_end;
    }

    _trainer_do_training(plat, chatval_);

    listmax = 0;
    buff = i18n::s.get("core.talk.visitor.trainer.after", speaker);
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.more");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker);
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }
    return TalkResult::talk_end;
}



void _beggar_give(Character& speaker)
{
    p = cdata.player().gold / 20 + 1;
    txt(i18n::s.get("core.talk.visitor.beggar.spare", p(0), speaker));
    cdata.player().gold -= p;
    snd("core.paygold1");
    earn_gold(speaker, p);
    modify_karma(cdata.player(), 2);
}



TalkResult _talk_hv_beggar(Character& speaker)
{
    if (cdata.player().gold > 0)
    {
        list(0, listmax) = 1;
        listn(0, listmax) = i18n::s.get("core.talk.visitor.choices.yes");
        ++listmax;
    }
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.talk.visitor.choices.no");
    ++listmax;
    buff = i18n::s.get("core.talk.visitor.beggar.dialog", speaker);
    int chatval_ = talk_window_query(speaker);
    if (chatval_ == 1)
    {
        _beggar_give(speaker);

        listmax = 0;
        buff = i18n::s.get("core.talk.visitor.beggar.after", speaker);
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.ui.more");
        ++listmax;
        chatesc = 1;
        talk_window_query(speaker);
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return TalkResult::talk_end;
            }
        }
        return TalkResult::talk_end;
    }
    listmax = 0;
    buff = i18n::s.get("core.talk.visitor.beggar.cheap");
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.more");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker);
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }
    return TalkResult::talk_end;
}



TalkResult _talk_hv_punk(Character& speaker)
{
    list(0, listmax) = 1;
    listn(0, listmax) = i18n::s.get("core.talk.visitor.choices.yes");
    ++listmax;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.talk.visitor.choices.no");
    ++listmax;
    buff = i18n::s.get("core.talk.visitor.punk.dialog", speaker);
    int chatval_ = talk_window_query(speaker);
    if (chatval_ == 1)
    {
        listmax = 0;
        buff = i18n::s.get("core.talk.npc.common.sex.start", speaker);
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.talk.npc.common.sex.response");
        ++listmax;
        chatesc = 1;
        talk_window_query(speaker);
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return TalkResult::talk_end;
            }
        }

        activity_sex(cdata.player(), speaker);

        return TalkResult::talk_end;
    }
    listmax = 0;
    buff = i18n::s.get("core.talk.visitor.punk.hump");
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.more");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker);
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }
    return TalkResult::talk_end;
}



TalkResult _talk_hv_mysterious_producer(Character& speaker)
{

    list(0, listmax) = 1;
    listn(0, listmax) = i18n::s.get("core.talk.visitor.choices.yes");
    ++listmax;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.talk.visitor.choices.no");
    ++listmax;
    buff = i18n::s.get(
        "core.talk.visitor.mysterious_producer.want_to_be_star", speaker);
    int chatval_ = talk_window_query(speaker);
    if (chatval_ == 1)
    {
        listmax = 0;
        buff = i18n::s.get(
            "core.talk.visitor.mysterious_producer.no_turning_back", speaker);
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.talk.npc.common.sex.response");
        ++listmax;
        chatesc = 1;
        talk_window_query(speaker);
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return TalkResult::talk_end;
            }
        }

        activity_sex(cdata.player(), speaker);

        return TalkResult::talk_end;
    }
    listmax = 0;
    buff = i18n::s.get("core.talk.visitor.punk.hump");
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.more");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker);
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }
    return TalkResult::talk_end;
}



void _merchant_buy(Character& speaker)
{
    invctrl = 11;
    invfile = speaker.shop_store_id;
    shop_sell_item(speaker);
    screenupdate = -1;
    update_screen();
    cs = 0;
    buff = "";
}



void _merchant_sell(Character& speaker)
{
    invctrl = 12;
    invfile = speaker.shop_store_id;
    shop_sell_item(speaker);
    screenupdate = -1;
    update_screen();
    cs = 0;
    buff = "";
}



TalkResult _talk_hv_merchant(Character& speaker)
{
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.talk.visitor.merchant.choices.buy");
    ++listmax;
    list(0, listmax) = 1;
    listn(0, listmax) = i18n::s.get("core.talk.visitor.merchant.choices.sell");
    ++listmax;
    list(0, listmax) = 2;
    listn(0, listmax) =
        i18n::s.get("core.talk.visitor.merchant.choices.not_now");
    ++listmax;
    buff = i18n::s.get("core.talk.visitor.merchant.dialog", speaker);
    int chatval_ = talk_window_query(speaker);
    if (chatval_ == 0)
    {
        _merchant_buy(speaker);
        return TalkResult::talk_house_visitor;
    }
    if (chatval_ == 1)
    {
        _merchant_sell(speaker);
        return TalkResult::talk_house_visitor;
    }
    listmax = 0;
    buff = i18n::s.get("core.talk.visitor.merchant.regret", speaker);
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.more");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker);
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }
    speaker.role = Role::guest_citizen;
    return TalkResult::talk_end;
}

} // namespace



TalkResult talk_house_visitor(Character& speaker)
{
    listmax = 0;
    switch (speaker.role)
    {
    case Role::adventurer: return _talk_hv_adventurer(speaker);
    case Role::guest_trainer: return _talk_hv_trainer(speaker);
    case Role::guest_citizen: return _talk_hv_visitor(speaker);
    case Role::guest_beggar: return _talk_hv_beggar(speaker);
    case Role::guest_punk: return _talk_hv_punk(speaker);
    case Role::guest_producer: return _talk_hv_mysterious_producer(speaker);
    case Role::guest_wandering_vendor: return _talk_hv_merchant(speaker);
    default: return TalkResult::talk_end;
    }
}

} // namespace elona
