#include "talk.hpp"

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
#include "inventory.hpp"
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
            "core.talk.visitor.adventurer.new_year.throws",
            speaker,
            item.unwrap()));
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
            ThrowingObjectAnimation(speaker.position, {tlocx, tlocy}, 223, 0)
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
        txt(i18n::s.get("core.talk.visitor.receive", item.unwrap(), speaker));
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
    inv_make_free_slot_force(-1);

    if (rnd(4))
    {
        p = 55;
    }
    else
    {
        p = 622;
    }
    flt();
    if (const auto item = itemcreate_extra_inv(p, cdata.player().position, 0))
    {
        txt(i18n::s.get("core.talk.visitor.receive", item.unwrap(), speaker));
        snd("core.get1");
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
    if (!inv_has_free_slot(0))
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
                "core.talk.visitor.adventurer.souvenir.receive",
                item.unwrap()));
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
    if (speaker.impression >= 100 && !speaker.is_best_friend())
    {
        inv_make_free_slot_force(-1);
        _talk_hv_adventurer_best_friend(speaker);
        // NOTE: this dialog falls through.
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

#include "audio.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "config.hpp"
#include "deferred_event.hpp"
#include "draw.hpp"
#include "enums.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "macro.hpp"
#include "map.hpp"
#include "menu.hpp"
#include "message.hpp"
#include "quest.hpp"
#include "random.hpp"
#include "shop.hpp"
#include "text.hpp"
#include "ui.hpp"
#include "variables.hpp"


namespace elona
{

namespace
{

bool chatval_show_impress;

}



void talk_start()
{
    asset_load("ie_chat");
    gsel(0);
}



bool talk_setup_variables(Character& chara)
{
    input_halt_input(HaltInput::force);
    if (chara.role == Role::innkeeper)
    {
        if (g_config.extra_help())
        {
            maybe_show_ex_help(7, true);
        }
    }
    if (chara.role == Role::trainer)
    {
        maybe_show_ex_help(8, true);
    }
    set_npc_religion(chara);
    if (scenemode == 0)
    {
        snd("core.chat");
        map_proc_regen_and_update();
    }
    cs = 0;
    chatesc = 1;
    if (chara.relationship <= -1)
    {
        if (!event_has_pending_events())
        {
            txt(i18n::s.get("core.talk.will_not_listen", chara));
            quest_teleport = false;
            update_screen();
            return false;
        }
    }
    if (game_data.date.hours() >= chara.time_interest_revive)
    {
        chara.interest = 100;
    }
    if (is_shopkeeper(chara.role))
    {
        invfile = chara.shop_store_id;
        shop_refresh_on_talk(chara);
    }

    return true;
}



void talk_to_npc(Character& chara)
{
    if (!talk_setup_variables(chara))
    {
        return;
    }

    talk_start();
    if (scenemode == 1)
    {
        talk_wrapper(chara, TalkResult::talk_more);
        return;
    }
    chatval_unique_chara_id = none;
    chatval_show_impress = true;
    if (chara.quality == Quality::special && chara.index >= 16)
    {
        chatval_unique_chara_id = charaid2int(chara.id);
        chatval_show_impress = false;
    }
    if (event_processing_event() == 2)
    {
        talk_wrapper(chara, TalkResult::talk_game_begin);
        return;
    }
    if (event_processing_event() == 16)
    {
        talk_wrapper(chara, TalkResult::talk_finish_escort);
        return;
    }
    if (chara.sleep != 0)
    {
        talk_wrapper(chara, TalkResult::talk_sleeping);
        return;
    }
    if (chara.activity)
    {
        talk_wrapper(chara, TalkResult::talk_busy);
        return;
    }
    if (chara.index == 0)
    {
        talk_wrapper(chara, TalkResult::talk_end);
        return;
    }
    if (chara.visited_just_now())
    {
        chara.visited_just_now() = false;
        talk_wrapper(chara, TalkResult::talk_house_visitor);
    }

    if (chatval_unique_chara_id &&
        game_data.current_map != mdata_t::MapId::show_house &&
        chara.index >= 16)
    {
        talk_wrapper(chara, TalkResult::talk_unique);
        return;
    }

    if (quest_teleport)
    {
        quest_teleport = false;
        talk_wrapper(chara, TalkResult::talk_quest_giver);
        return;
    }
    buff = "";

    talk_wrapper(chara, TalkResult::talk_npc);
}



TalkResult talk_more(Character& speaker)
{
    listmax = 0;
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



TalkResult talk_sleeping(Character& speaker)
{
    listmax = 0;
    buff = u8"("s + i18n::s.get("core.talk.is_sleeping", speaker) + u8")"s;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.bye");
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



TalkResult talk_busy(Character& speaker)
{
    listmax = 0;
    buff = u8"("s + i18n::s.get("core.talk.is_busy", speaker) + u8")"s;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.bye");
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



TalkResult talk_ignored(Character& speaker)
{
    listmax = 0;
    buff = i18n::s.get("core.talk.ignores_you", speaker);
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.ui.bye"));
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



TalkResult talk_game_begin(Character& initial_speaker)
{
    auto speaker = std::ref(initial_speaker);
    if (lomiaseaster)
    {
        cdata.player().blind = 100;
        listmax = 0;
        buff = i18n::s.get_enum("core.talk.unique.lomias.begin.easter_egg", 0);
        if (const auto larnneire = chara_find("core.larnneire"))
        {
            speaker = std::ref(*larnneire);
        }
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.ui.more");
        ++listmax;
        chatesc = 1;
        talk_window_query(speaker.get());
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return TalkResult::talk_end;
            }
        }
        listmax = 0;
        buff = i18n::s.get_enum("core.talk.unique.lomias.begin.easter_egg", 1);
        if (const auto lomias = chara_find("core.lomias"))
        {
            speaker = std::ref(*lomias);
        }
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.ui.more");
        ++listmax;
        chatesc = 1;
        talk_window_query(speaker.get());
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return TalkResult::talk_end;
            }
        }
        update_screen();
        await(3000);
        Message::instance().linebreak();
        txt(i18n::s.get(
                "core.talk.unique.lomias.begin.easter_egg.something_is_killed"),
            Message::color{ColorIndex::red});
        txt(i18n::s.get("core.talk.unique.lomias.begin.easter_egg.ugh"));
        snd("core.kill1");
        spillblood(28, 6, 10);
        flt();
        itemcreate_extra_inv(705, 28, 6, 0);
        update_screen();
        await(500);
        await(500);
        listmax = 0;
        buff = i18n::s.get_enum("core.talk.unique.lomias.begin.easter_egg", 2);
        if (const auto larnneire = chara_find("core.larnneire"))
        {
            speaker = std::ref(*larnneire);
        }
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.ui.more");
        ++listmax;
        chatesc = 1;
        talk_window_query(speaker.get());
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return TalkResult::talk_end;
            }
        }
        listmax = 0;
        buff = i18n::s.get_enum("core.talk.unique.lomias.begin.easter_egg", 3);
        if (const auto lomias = chara_find("core.lomias"))
        {
            speaker = std::ref(*lomias);
        }
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.ui.more");
        ++listmax;
        chatesc = 1;
        talk_window_query(speaker.get());
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return TalkResult::talk_end;
            }
        }
        listmax = 0;
        buff = i18n::s.get_enum("core.talk.unique.lomias.begin.easter_egg", 4);
        if (const auto larnneire = chara_find("core.larnneire"))
        {
            speaker = std::ref(*larnneire);
        }
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.ui.more");
        ++listmax;
        chatesc = 1;
        talk_window_query(speaker.get());
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return TalkResult::talk_end;
            }
        }
        listmax = 0;
        buff = i18n::s.get_enum("core.talk.unique.lomias.begin.easter_egg", 5);
        if (const auto lomias = chara_find("core.lomias"))
        {
            speaker = std::ref(*lomias);
        }
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.ui.more");
        ++listmax;
        chatesc = 1;
        talk_window_query(speaker.get());
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return TalkResult::talk_end;
            }
        }
        listmax = 0;
        buff = i18n::s.get_enum("core.talk.unique.lomias.begin.easter_egg", 6);
        if (const auto larnneire = chara_find("core.larnneire"))
        {
            speaker = std::ref(*larnneire);
        }
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.ui.more");
        ++listmax;
        chatesc = 1;
        talk_window_query(speaker.get());
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return TalkResult::talk_end;
            }
        }
        await(1500);
        update_screen();
        fade_out();
        gsel(0);
        cdata.player().blind = 0;
        txt(i18n::s.get("core.talk.unique.lomias.begin.easter_egg.was_dream"));
    }
    else
    {
        Message::instance().linebreak();
    }
    txt(i18n::s.get("core.talk.unique.lomias.begin.regain_consciousness"));
    listmax = 0;
    buff = i18n::s.get_enum("core.talk.unique.lomias.begin", 0);
    if (const auto lomias = chara_find("core.lomias"))
    {
        speaker = std::ref(*lomias);
    }
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.more");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker.get());
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }
    listmax = 0;
    buff = i18n::s.get_enum("core.talk.unique.lomias.begin", 1);
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.more");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker.get());
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }
    listmax = 0;
    buff = i18n::s.get_enum("core.talk.unique.lomias.begin", 2);
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.more");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker.get());
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }
    listmax = 0;
    buff = i18n::s.get_enum("core.talk.unique.lomias.begin", 3);
    if (const auto larnneire = chara_find("core.larnneire"))
    {
        speaker = std::ref(*larnneire);
    }
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.more");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker.get());
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }
    listmax = 0;
    buff = i18n::s.get_enum(
        "core.talk.unique.lomias.begin", 4, cdata.player().name);
    if (const auto lomias = chara_find("core.lomias"))
    {
        speaker = std::ref(*lomias);
    }
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.more");
    ++listmax;
    chatesc = 1;
    talk_window_query(speaker.get());
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }
    map_data.bgm = 67;
    play_music();
    return TalkResult::talk_unique;
}



void talk_end()
{
    quest_teleport = false;
    if (scenemode == 0)
    {
        screenupdate = -1;
        update_screen();
    }
}



std::string talk_get_speaker_name(const Character& chara)
{
    std::string speaker_name;

    if (scenemode)
    {
        return actor(0, current_actor_index);
    }
    if (chara.alias == ""s)
    {
        speaker_name = chara.name + u8" "s;
    }
    else
    {
        speaker_name =
            i18n::s.get("core.talk.window.of", chara.name, chara.alias) + " ";
    }
    if (chara.sex == 0)
    {
        speaker_name += cnven(i18n::s.get("core.ui.sex3.male"));
    }
    else
    {
        speaker_name += cnven(i18n::s.get("core.ui.sex3.female"));
    }
    if (chara.alias != ""s)
    {
        speaker_name += " " + i18n::s.get("core.talk.window.fame", chara.fame);
    }
    if (is_shopkeeper(chara.role))
    {
        speaker_name +=
            " " + i18n::s.get("core.talk.window.shop_rank", chara.shop_rank);
    }
    if (game_data.reveals_religion)
    {
        speaker_name += u8" ("s + god_name(chara.god_id) + u8")"s;
    }

    return speaker_name;
}



int talk_window_query(const Character& chara)
{
    const auto speaker_name = talk_get_speaker_name(chara);
    optional<std::pair<int, int>> impress_interest = none;

    if (chatval_show_impress)
    {
        impress_interest = std::make_pair(chara.impression, chara.interest);
    }

    if (chara.portrait != "" || scenemode)
    {
        const auto portrait_id =
            scenemode ? actor(1, current_actor_index) : chara.portrait;
        return talk_window_query(
            portrait_id, none, speaker_name, buff, impress_interest);
    }
    else
    {
        return talk_window_query(
            none, chara.image, speaker_name, buff, impress_interest);
    }
}



int talk_window_query(
    optional_ref<const std::string> portrait_id,
    optional<int> chara_image,
    const std::string& speaker_name,
    std::string& text,
    optional<std::pair<int, int>> impress_interest)
{
    cs_bk = -1;
    key_list = key_enter;
    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
    {
        key_list(cnt) = key_select(cnt);
        ++keyrange;
    }
    keyrange = listmax;
    talk_window_init(text);

    while (true)
    {
        talk_window_show(
            portrait_id, chara_image, speaker_name, text, impress_interest);
        font(14 - en * 2);
        cs_listbk();
        for (int cnt = 0, cnt_end = (keyrange); cnt < cnt_end; ++cnt)
        {
            noteget(s, cnt);
            x = wx + 136;
            y = wy + wh - 56 - keyrange * 19 + cnt * 19 + 2;
            display_key(x, y, cnt);
            cs_list(cs == cnt, listn(0, cnt), x + 30, y, 4);
        }
        cs_bk = cs;
        redraw();
        int cursor{};
        auto action = cursor_check_ex(cursor);
        const auto input = stick(StickKey::escape);
        if (input == StickKey::escape)
        {
            if (scenemode)
            {
                scene_cut = 1;
                talk_reset_variables();
                return -1;
            }
        }
        p = -1;
        for (int cnt = 0, cnt_end = (keyrange); cnt < cnt_end; ++cnt)
        {
            if (cnt == cursor)
            {
                p = list(0, cnt);
                break;
            }
        }
        if (p != -1)
        {
            talk_reset_variables();
            return p(0);
        }
        if (action == "cancel" && chatesc != -1)
        {
            talk_reset_variables();
            return -1;
        }
    }
}



void talk_reset_variables()
{
    snd("core.more1");
    cs = 0;
    listmax = 0;
}



void talk_window_init(std::string& text)
{
    if (scenemode == 0)
    {
        screenupdate = -1;
        update_screen();
        cs = 0;
    }
    talk_conv(text, 56 - en * 3);
    wx = (windoww - 600) / 2 + inf_screenx;
    wy = winposy(380);
    ww = 600;
    wh = 380;
    gmode(2, 80);
    draw("ie_chat", wx + 4, wy - 16);
}



void talk_window_show(
    optional_ref<const std::string> portrait_id,
    optional<int> chara_image,
    const std::string& speaker_name,
    std::string& text,
    optional<std::pair<int, int>> impress_interest)
{
    gmode(2);
    draw("ie_chat", wx, wy - 20);
    if (portrait_id)
    {
        if (const auto rect = draw_get_rect_portrait(*portrait_id))
        {
            gcopy(
                rect->buffer,
                rect->x,
                rect->y,
                rect->width,
                rect->height,
                wx + 42,
                wy + 42);
        }
    }
    else if (chara_image)
    {
        const auto chara_chip_id = *chara_image % 1000;
        draw_chara(
            *chara_image,
            wx + 82,
            wy + 125 - chara_chips[chara_chip_id].offset_y,
            2);
    }
    else
    {
        assert(false);
    }

    font(10 - en * 2);
    display_topic(i18n::s.get("core.talk.window.impress"), wx + 28, wy + 170);
    display_topic(i18n::s.get("core.talk.window.attract"), wx + 28, wy + 215);

    font(12 + sizefix - en * 2, snail::Font::Style::bold);
    mes(wx + 120, wy + 16, speaker_name, {20, 10, 5});

    font(13 - en * 2);
    if (impress_interest)
    {
        int impress, interest;
        std::tie(impress, interest) = *impress_interest;

        std::string impress_enum = i18n::s.get_enum(
            u8"core.ui.impression", chara_impression_level(impress));
        std::string impress_text;

        if (impress < 150)
        {
            impress_text = ""s + impress;
        }
        else
        {
            impress_text = u8"???"s;
        }
        mes(wx + 32,
            wy + 198,
            u8"("s + impress_text + u8")"s + impress_enum,
            {20, 10, 5});
        if (interest >= 0)
        {
            for (int cnt = 0, cnt_end = (interest / 5 + 1); cnt < cnt_end;
                 ++cnt)
            {
                draw("interest_icon", wx + 26 + cnt * 4, wy + 245);
            }
        }
    }
    else
    {
        mes(wx + 60, wy + 198, u8"-"s);
        mes(wx + 60, wy + 245, u8"-"s);
    }
    font(14 - en * 2);
    notesel(text);
    for (int cnt = 0, cnt_end = (noteinfo()); cnt < cnt_end; ++cnt)
    {
        p = cnt;
        x = wx + 150;
        y = wy + 43 + cnt * 19;
        noteget(s, p);
        mes(x, y, s, {20, 10, 5});
    }
}



int talk_guide_quest_client()
{
    constexpr int max_quest = 5;

    int ret{};

    for (int i = 0; i < max_quest; ++i)
    {
        const auto quest_id = game_data.taken_quests.at(i);
        if (quest_data[quest_id].progress != 1)
            continue;
        if (game_data.current_dungeon_level != 1)
            continue;

        auto client = -1;
        if (quest_data[quest_id].id == 1011)
        {
            if (quest_data[quest_id].originating_map_id ==
                game_data.current_map)
            {
                client = quest_data[quest_id].target_chara_index;
            }
        }
        if (quest_data[quest_id].id == 1002)
        {
            if (quest_data[quest_data[quest_id].target_chara_index]
                    .originating_map_id == game_data.current_map)
            {
                client = quest_data[quest_data[quest_id].target_chara_index]
                             .client_chara_index;
            }
        }
        if (client != -1)
        {
            // Check duplicate
            bool duplicated{};
            for (int j = 0; j < i; ++j)
            {
                if (game_data.taken_quests.at(j) == quest_id)
                {
                    duplicated = true;
                    break;
                }
            }
            if (!duplicated)
            {
                rtval(ret) = client;
                ++ret;
            }
        }
    }

    return ret;
}

} // namespace elona
