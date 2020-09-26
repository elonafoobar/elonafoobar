#include "activity.hpp"

#include "ability.hpp"
#include "animation.hpp"
#include "area.hpp"
#include "audio.hpp"
#include "building.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "command.hpp"
#include "config.hpp"
#include "crafting.hpp"
#include "crafting_material.hpp"
#include "data/types/type_ability.hpp"
#include "dmgheal.hpp"
#include "draw.hpp"
#include "enchantment.hpp"
#include "fish.hpp"
#include "food.hpp"
#include "fov.hpp"
#include "game.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "inventory.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "message.hpp"
#include "optional.hpp"
#include "random_event.hpp"
#include "save.hpp"
#include "status_ailment.hpp"
#include "text.hpp"
#include "ui.hpp"
#include "variables.hpp"
#include "world.hpp"



namespace elona
{

namespace
{

int digx = 0;
int digy = 0;
int performance_tips;



// Returns true if stop.
bool prompt_stop_activity(const Character& doer)
{
    txt(i18n::s.get_data_text(
        "core.activity", doer.activity.id, "cancel_prompt"));
    return static_cast<bool>(yes_no());
}



void search_material_spot()
{
    if (cell_data.at(cdata.player().position.x, cdata.player().position.y)
            .feats == 0)
    {
        return;
    }
    cell_featread(cdata.player().position.x, cdata.player().position.y);
    if (feat(1) < 24 || 28 < feat(1))
    {
        return;
    }
    int atxspot = 11;
    int atxlv = game()->current_dungeon_level;
    if (map_data.type == mdata_t::MapType::dungeon)
    {
        atxspot = 9;
    }
    if (map_data.type == mdata_t::MapType::dungeon_tower)
    {
        atxspot = 12;
    }
    if (map_data.type == mdata_t::MapType::dungeon_forest)
    {
        atxspot = 10;
    }
    if (map_data.type == mdata_t::MapType::dungeon_castle)
    {
        atxspot = 12;
    }
    if (map_data.type == mdata_t::MapType::world_map)
    {
        atxlv = cdata.player().level / 2 + rnd(10);
        if (atxlv > 30)
        {
            atxlv = 30 + rnd(rnd_capped(atxlv - 30) + 1);
        }
        if (4 <= game()->stood_world_map_tile &&
            game()->stood_world_map_tile < 9)
        {
            atxspot = 10;
        }
        if (264 <= game()->stood_world_map_tile &&
            game()->stood_world_map_tile < 363)
        {
            atxspot = 11;
        }
        if (9 <= game()->stood_world_map_tile &&
            game()->stood_world_map_tile < 13)
        {
            atxspot = 10;
        }
        if (13 <= game()->stood_world_map_tile &&
            game()->stood_world_map_tile < 17)
        {
            atxspot = 11;
        }
    }
    cell_featread(cdata.player().position.x, cdata.player().position.y);
    if (feat(1) == 27)
    {
        atxlv += cdata.player().get_skill(161).level / 3;
        atxspot = 16;
    }
    if (feat(1) == 26)
    {
        atxspot = 13;
    }
    if (feat(1) == 25)
    {
        atxspot = 14;
    }
    if (feat(1) == 28)
    {
        atxspot = 15;
    }
    if (rnd(7) == 0)
    {
        for (int cnt = 0; cnt < 1; ++cnt)
        {
            i = 5;
            if (atxspot == 14)
            {
                if (cdata.player().get_skill(163).level <
                        rnd_capped(atxlv * 2 + 1) ||
                    rnd(10) == 0)
                {
                    txt(i18n::s.get("core.activity.material.digging.fails"));
                    break;
                }
                i = 1;
                chara_gain_skill_exp(cdata.player(), 163, 40);
            }
            if (atxspot == 13)
            {
                if (cdata.player().get_skill(185).level <
                        rnd_capped(atxlv * 2 + 1) ||
                    rnd(10) == 0)
                {
                    txt(i18n::s.get("core.activity.material.fishing.fails"));
                    break;
                }
                i = 2;
                chara_gain_skill_exp(cdata.player(), 185, 40);
            }
            if (atxspot == 15)
            {
                if (cdata.player().get_skill(180).level <
                        rnd_capped(atxlv * 2 + 1) ||
                    rnd(10) == 0)
                {
                    txt(i18n::s.get("core.activity.material.searching.fails"));
                    break;
                }
                i = 3;
                chara_gain_skill_exp(cdata.player(), 180, 30);
            }
            crafting_material_gain(
                crafting_material_select_random_id(atxlv, 0, atxspot), 1, i);
        }
    }
    if (rnd(50 + cdata.player().traits().level("core.more_materials") * 20) ==
        0)
    {
        s = i18n::s.get("core.activity.material.searching.no_more");
        if (feat(1) == 26)
        {
            s = i18n::s.get("core.activity.material.fishing.no_more");
        }
        if (feat(1) == 25)
        {
            s = i18n::s.get("core.activity.material.digging.no_more");
        }
        if (feat(1) == 28)
        {
            s = i18n::s.get("core.activity.material.harvesting.no_more");
        }
        txt(s);
        cdata.player().activity.finish();
        cell_data.at(cdata.player().position.x, cdata.player().position.y)
            .feats = 0;
    }
}



int calc_performance_tips(const Character& performer, const Character& audience)
{
    // Quality factor
    const auto Q = performer.quality_of_performance;
    // Instrument factor
    const auto I = performer.activity.item->param1;

    const auto max = performer.get_skill(183).level * 100;

    const auto m = Q * Q * (100 + I / 5) / 100 / 1000 + rnd(10);
    auto ret = clamp(audience.gold * clamp(m, 1, 100) / 125, 0, max);

    if (audience.is_player_or_ally())
    {
        ret = rnd(clamp(ret, 1, 100)) + 1;
    }
    if (is_shopkeeper(audience.role))
    {
        ret /= 5;
    }
    return clamp(ret, 0, audience.gold);
}



void activity_perform_generate_item(
    const Character& performer,
    const Character& audience,
    const ItemRef& instrument)
{
    const std::vector<int> fsetperform{
        18000,
        20000,
        32000,
        34000,
        52000,
        57000,
        57000,
        57000,
        60000,
        64000,
        64000,
        77000,
    };

    const auto x =
        clamp(performer.position.x - 1 + rnd(3), 0, map_data.width - 1);
    const auto y =
        clamp(performer.position.y - 1 + rnd(3), 0, map_data.height - 1);

    cell_check(x, y);
    if (cellaccess == 0)
        return;
    if (!fov_los(audience.position, {x, y}))
        return;

    if (enchantment_find(instrument, 49))
    {
        flt(calcobjlv(performer.quality_of_performance / 8),
            calcfixlv((rnd(4) == 0) ? Quality::miracle : Quality::great));
    }
    else
    {
        flt(calcobjlv(performer.quality_of_performance / 10),
            calcfixlv(Quality::good));
    }

    flttypemajor = choice(fsetperform);
    int item_id = 0;
    if (game()->executing_immediate_quest_type == 1009)
    {
        if (rnd(150) == 0)
        {
            item_id = 241;
        }
        if (rnd(150) == 0)
        {
            item_id = 622;
        }
        if (audience.level > 15)
        {
            if (rnd(1000) == 0)
            {
                item_id = 725;
            }
        }
        if (audience.level > 10)
        {
            if (rnd(800) == 0)
            {
                item_id = 726;
            }
        }
    }
    else
    {
        if (rnd(10) == 0)
        {
            item_id = 724;
        }
        if (rnd(250) == 0)
        {
            item_id = 55;
        }
    }

    /*
     * Generate an item and play throwing animation.
     * The generated item should be hidden during the animation is playing, and
     * then appear when the animation finishes. In vanilla, it is done by
     * removing the item once and restore it after the animation. For vanilla's
     * implementation, see diff of Pull Request #1687.
     * https://github.com/elonafoobar/elonafoobar/pull/1687/files#diff-df8c633c69661a36d5d606d01e0bf6ca
     * It does not work in foobar because these oprations trigger event
     * `core.item_created` and `core.item_removed`, calling registered event
     * handlers. To avoid firing events, only the drawing information is removed
     * temporarily and then restored, instead of modifying the item itself.
     */

    // Save drawing information of the cell *before* tip generation.
    const auto item_info_actual_before_tip_generation =
        cell_data.at(x, y).item_info_actual;
    const auto item_info_memory_before_tip_generation =
        cell_data.at(x, y).item_info_memory;
    if (const auto item = itemcreate_map_inv(item_id, x, y, 1))
    {
        // Save drawing information of the cell *after* tip generation.
        const auto item_info_actual_after_tip_generation =
            cell_data.at(x, y).item_info_actual;
        const auto item_info_memory_after_tip_generation =
            cell_data.at(x, y).item_info_memory;
        // Restore drawing information of the cell *before* tip generation.
        // It actually does hiding the generated item during the throwing
        // animation is playing.
        cell_data.at(x, y).item_info_actual =
            item_info_actual_before_tip_generation;
        cell_data.at(x, y).item_info_memory =
            item_info_memory_before_tip_generation;
        // Play animation.
        ThrowingObjectAnimation(
            audience.position, item->position(), item->image, item->tint)
            .play();
        // Restore drawing information of the cell *after* tip generation.
        // It fixes the inconsistency that the drawing information is different
        // from the actual item. Now, all invariant constraints are properly
        // restored.
        cell_data.at(x, y).item_info_actual =
            item_info_actual_after_tip_generation;
        cell_data.at(x, y).item_info_memory =
            item_info_memory_after_tip_generation;
        ++performance_tips;
    }
}



std::pair<bool, int> activity_perform_proc_audience(
    Character& performer,
    Character& audience)
{
    const auto performer_skill = performer.get_skill(183).level;
    const auto& instrument = performer.activity.item.unwrap();

    if (audience.state() != Character::State::alive)
    {
        return std::make_pair(false, 0);
    }
    if (game()->date.hours() >= audience.time_interest_revive)
    {
        audience.interest = 100;
    }
    if (is_in_fov(performer))
    {
        if (audience.vision_flag != msync)
        {
            return std::make_pair(false, 0);
        }
    }
    else if (dist(performer.position, audience.position) > 3)
    {
        return std::make_pair(false, 0);
    }
    if (audience.interest <= 0)
    {
        return std::make_pair(false, 0);
    }
    if (audience.sleep > 0)
    {
        return std::make_pair(false, 0);
    }

    const auto x = audience.position.x;
    const auto y = audience.position.y;
    if (cell_data.at(x, y).chara_index_plus_one == 0)
    {
        return std::make_pair(false, 0); // TODO: unreachable?
    }
    if (audience == performer)
    {
        return std::make_pair(false, 0);
    }
    if (audience.relationship == -3)
    {
        if (audience.hate == 0)
        {
            if (is_in_fov(audience))
            {
                txt(i18n::s.get("core.activity.perform.gets_angry", audience));
            }
        }
        audience.hate = 30;
        return std::make_pair(false, 0);
    }
    if (performer.is_player())
    {
        audience.interest -= rnd(15);
        audience.time_interest_revive = game()->date.hours() + 12;
    }
    if (audience.interest <= 0)
    {
        if (is_in_fov(performer))
        {
            txt(i18n::s.get("core.activity.perform.dialog.disinterest"),
                Message::color{ColorIndex::cyan});
        }
        audience.interest = 0;
        return std::make_pair(false, 0);
    }
    if (performer_skill < audience.level)
    {
        if (rnd(3) == 0)
        {
            performer.quality_of_performance -= audience.level / 2;
            if (is_in_fov(performer))
            {
                txt(i18n::s.get("core.activity.perform.dialog.angry"),
                    Message::color{ColorIndex::cyan});
                txt(i18n::s.get("core.activity.perform.throws_rock", audience));
            }
            dmg = rnd_capped(audience.level + 1) + 1;
            if (audience.id == CharaId::loyter)
            {
                dmg = audience.level * 2 + rnd(100);
            }
            damage_hp(performer, dmg, -8);
            if (performer.state() == Character::State::empty)
            {
                return std::make_pair(true, 0);
            }
            return std::make_pair(false, 0);
        }
    }

    int gold = 0;
    if (rnd(3) == 0)
    {
        const auto tips = calc_performance_tips(performer, audience);
        audience.gold -= tips;
        earn_gold(performer, tips);
        gold = tips;
    }
    if (audience.level > performer_skill)
    {
        return std::make_pair(false, gold);
    }
    if (rnd_capped(performer_skill + 1) > rnd_capped(audience.level * 2 + 1))
    {
        if (game()->executing_immediate_quest_type == 1009)
        {
            if (audience.is_map_local())
            {
                audience.impression += rnd(3);
                calcpartyscore();
            }
        }
        const auto p = rnd_capped(audience.level + 1) + 1;
        if (rnd(2) == 0)
        {
            performer.quality_of_performance += p;
        }
        else if (rnd(2) == 0)
        {
            performer.quality_of_performance -= p;
        }
    }
    if (enchantment_find(instrument, 60))
    {
        if (rnd(15) == 0)
        {
            status_ailment_damage(audience, StatusAilment::drunk, 500);
        }
    }
    if (rnd_capped(performer_skill + 1) > rnd_capped(audience.level * 5 + 1))
    {
        if (rnd(3) == 0)
        {
            if (is_in_fov(performer))
            {
                txt(i18n::s.get(
                        "core.activity.perform.dialog.interest",
                        audience,
                        performer),
                    Message::color{ColorIndex::cyan});
            }
            performer.quality_of_performance += audience.level + 5;
            if (performer.is_player() && !audience.is_player_or_ally())
            {
                if (rnd_capped(performance_tips * 2 + 2) == 0)
                {
                    activity_perform_generate_item(
                        performer, audience, instrument);
                }
            }
        }
    }
    return std::make_pair(false, gold);
}



void activity_perform_start(Character& performer, ItemRef instrument)
{
    if (is_in_fov(performer))
    {
        txt(i18n::s.get("core.activity.perform.start", performer, instrument));
    }
    performer.activity.id = "core.perform";
    performer.activity.turns = 61;
    performer.activity.item = instrument;
    performer.quality_of_performance = 40;
    performer.tip_gold = 0;
    if (performer.is_player())
    {
        performance_tips = 0;
    }
}



void activity_perform_doing(Character& performer)
{
    if (performer.activity.turns % 10 == 0)
    {
        if (is_in_fov(performer))
        {
            if (rnd(10) == 0)
            {
                txt(i18n::s.get("core.activity.perform.sound.random"),
                    Message::color{ColorIndex::blue});
            }
            txt(i18n::s.get("core.activity.perform.sound.cha"),
                Message::color{ColorIndex::blue});
        }
    }
    if (performer.activity.turns % 20 == 0)
    {
        int gold = 0;
        make_sound(performer, 5, 1, true);
        for (auto&& audience : cdata.all())
        {
            const auto result =
                activity_perform_proc_audience(performer, audience);
            if (result.first)
                break;
            gold += result.second;
        }
        if (gold != 0)
        {
            performer.tip_gold += gold;
            if (is_in_fov(performer))
            {
                snd("core.getgold1");
            }
        }
    }
}



int calc_performance_quality_level(int quality)
{
    if (quality < 0)
        return 0;
    else if (quality < 20)
        return 1;
    else if (quality < 40)
        return 2;
    else if (quality == 40)
        return 3;
    else if (quality < 60)
        return 4;
    else if (quality < 80)
        return 5;
    else if (quality < 100)
        return 6;
    else if (quality < 120)
        return 7;
    else if (quality < 150)
        return 8;
    else
        return 9;
}



void activity_perform_end(Character& performer)
{
    if (performer.is_player())
    {
        const auto quality_level =
            calc_performance_quality_level(performer.quality_of_performance);
        txt(i18n::s.get_enum("core.activity.perform.quality", quality_level));
    }

    if (performer.quality_of_performance > 40)
    {
        performer.quality_of_performance = performer.quality_of_performance *
            (100 + performer.activity.item->param1 / 5) / 100;
    }
    if (performer.tip_gold != 0)
    {
        if (is_in_fov(performer))
        {
            txt(i18n::s.get(
                "core.activity.perform.tip", performer, performer.tip_gold));
        }
    }

    performer.activity.finish();

    const auto experience =
        performer.quality_of_performance - performer.get_skill(183).level + 50;
    if (experience > 0)
    {
        chara_gain_skill_exp(performer, 183, experience, 0, 0);
    }
}



void activity_eating_start(Character& eater, const ItemRef& food)
{
    eater.activity.id = "core.eat";
    eater.activity.turns = 8;
    eater.activity.item = food;
    if (is_in_fov(eater))
    {
        snd("core.eat1");
        if (food->own_state == OwnState::town && eater.is_player_or_ally())
        {
            txt(i18n::s.get("core.activity.eat.start.in_secret", eater, food));
        }
        else
        {
            txt(i18n::s.get("core.activity.eat.start.normal", eater, food));
        }
        if (food->id == "core.corpse" && food->subname == 344)
        {
            txt(i18n::s.get("core.activity.eat.start.mammoth"));
        }
    }
}



void activity_sleep_start(Character& doer, const OptionalItemRef& bed)
{
    doer.activity.id = "core.sleep";
    doer.activity.item = bed;

    if (map_data.type == mdata_t::MapType::player_owned ||
        map_is_town_or_guild())
    {
        txt(i18n::s.get("core.activity.sleep.start.other"));
        doer.activity.turns = 5;
    }
    else
    {
        txt(i18n::s.get("core.activity.sleep.start.global"));
        doer.activity.turns = 20;
    }

    update_screen();
}



void activity_sleep_doing(Character&, const OptionalItemRef&)
{
}



void activity_sleep_end(Character& doer, const OptionalItemRef& bed)
{
    txt(i18n::s.get("core.activity.sleep.finish"));
    sleep_start(bed);
    doer.activity.finish();
}



void activity_build_shelter_start(Character& doer, const ItemRef& shelter)
{
    doer.activity.id = "core.build_shelter";
    doer.activity.item = shelter;

    txt(i18n::s.get("core.activity.construct.start", shelter));
    doer.activity.turns = 25;

    update_screen();
}



void activity_build_shelter_doing(Character&, const ItemRef&)
{
}



void activity_build_shelter_end(Character& doer, const ItemRef& shelter)
{
    snd("core.build1");
    txt(i18n::s.get("core.activity.construct.finish", shelter));
    item_build_shelter(shelter);
    doer.activity.finish();
}



void activity_enter_shelter_start(Character& doer, const ItemRef& shelter)
{
    doer.activity.id = "core.enter_shelter";
    doer.activity.item = shelter;

    txt(i18n::s.get("core.activity.pull_hatch.start", shelter));
    doer.activity.turns = 10;

    update_screen();
}



void activity_enter_shelter_doing(Character&, const ItemRef&)
{
}



void activity_enter_shelter_end(Character& doer, const ItemRef& shelter)
{
    txt(i18n::s.get("core.activity.pull_hatch.finish", shelter));
    chatteleport = 1;
    game()->previous_map2 = game()->current_map;
    game()->previous_dungeon_level = game()->current_dungeon_level;
    game()->previous_x = cdata.player().position.x;
    game()->previous_y = cdata.player().position.y;
    game()->destination_map = static_cast<int>(mdata_t::MapId::shelter_);
    game()->destination_dungeon_level = shelter->charges;
    levelexitby = 2;
    snd("core.exitmap1");
    doer.activity.finish();
}



void activity_harvest_start(Character& doer, const ItemRef& crop)
{
    doer.activity.id = "core.harvest";
    doer.activity.item = crop;

    txt(i18n::s.get("core.activity.dig", crop));
    doer.activity.turns = 10 +
        clamp(crop->weight /
                  (1 + cdata.player().get_skill(10).level * 10 +
                   cdata.player().get_skill(180).level * 40),
              1,
              100);

    update_screen();
}



void activity_harvest_doing(Character& doer, const ItemRef&)
{
    if (rnd(5) == 0)
    {
        chara_gain_skill_exp(cdata.player(), 180, 20, 4);
    }
    if (rnd(6) == 0)
    {
        if (rnd(55) > doer.get_skill(10).base_level + 25)
        {
            chara_gain_skill_exp(doer, 10, 50);
        }
    }
    if (rnd(8) == 0)
    {
        if (rnd(55) > doer.get_skill(11).base_level + 28)
        {
            chara_gain_skill_exp(doer, 11, 50);
        }
    }
    if (rnd(10) == 0)
    {
        if (rnd(55) > doer.get_skill(15).base_level + 30)
        {
            chara_gain_skill_exp(doer, 15, 50);
        }
    }
    if (rnd(4) == 0)
    {
        txt(i18n::s.get("core.activity.harvest.sound"),
            Message::color{ColorIndex::cyan});
    }
}



void activity_harvest_end(Character& doer, const ItemRef& crop)
{
    txt(i18n::s.get(
        "core.activity.harvest.finish", crop, cnvweight(crop->weight)));
    in = crop->number();
    pick_up_item(inv_player(), crop, none);
    doer.activity.finish();
}



void activity_study_start(Character& doer, const ItemRef& textbook)
{
    doer.activity.id = "core.study";
    doer.activity.item = textbook;

    if (game()->weather == "core.sunny" || game()->weather == "core.rain")
    {
        if (game()->time_when_textbook_becomes_available > game()->date.hours())
        {
            txt(i18n::s.get("core.activity.study.start.bored"));
            doer.activity.finish();
            return;
        }
    }
    game()->time_when_textbook_becomes_available = game()->date.hours() + 48;
    if (textbook->id == "core.textbook")
    {
        txt(i18n::s.get(
            "core.activity.study.start.studying",
            the_ability_db.get_text(textbook->param1, "name")));
    }
    else
    {
        txt(i18n::s.get("core.activity.study.start.training"));
    }
    if (game()->weather != "core.sunny" && game()->weather != "core.rain")
    {
        if (game()->current_map == mdata_t::MapId::shelter_ ||
            map_can_use_bad_weather_in_study())
        {
            txt(i18n::s.get("core.activity.study.start.weather_is_bad"));
        }
    }
    doer.activity.turns = 50;

    update_screen();
}



void activity_study_doing(Character& doer, const ItemRef& textbook)
{
    int p = 25;
    if (game()->weather != "core.sunny" && game()->weather != "core.rain")
    {
        if (game()->current_map == mdata_t::MapId::shelter_)
        {
            p = 5;
        }
        if (map_can_use_bad_weather_in_study())
        {
            p = 5;
            game()->date.minute += 30;
        }
    }
    if (textbook->id == "core.textbook")
    {
        if (rnd(p) == 0)
        {
            chara_gain_skill_exp(doer, textbook->param1, 25);
        }
    }
    else if (rnd(p) == 0)
    {
        chara_gain_skill_exp(doer, randattb(), 25);
    }
}



void activity_study_end(Character& doer, const ItemRef& textbook)
{
    if (textbook->id == "core.textbook")
    {
        txt(i18n::s.get(
            "core.activity.study.finish.studying",
            the_ability_db.get_text(textbook->param1, "name")));
    }
    else
    {
        txt(i18n::s.get("core.activity.study.finish.training"));
    }
    doer.activity.finish();
}



void activity_steal_start(Character& doer, const ItemRef& steal_target)
{
    doer.activity.id = "core.steal";
    doer.activity.item = steal_target;

    txt(i18n::s.get("core.activity.steal.start", steal_target));
    doer.activity.turns = 2 + clamp(steal_target->weight / 500, 0, 50);

    update_screen();
}



void activity_steal_doing(Character& doer, const ItemRef& steal_target)
{
    if (steal_target->id == "core.iron_maiden")
    {
        if (rnd(15) == 0)
        {
            doer.activity.finish();
            txt(i18n::s.get("core.activity.iron_maiden"));
            damage_hp(doer, 9999, -18);
            return;
        }
    }
    if (steal_target->id == "core.guillotine")
    {
        if (rnd(15) == 0)
        {
            doer.activity.finish();
            txt(i18n::s.get("core.activity.guillotine"));
            damage_hp(doer, 9999, -19);
            return;
        }
    }

    f = 0;
    f2 = 0;
    auto steal_target_owner = item_get_owner(steal_target);
    if (const auto owner = steal_target_owner.as_character())
    {
        if (owner->original_relationship == -3)
        {
            f2 = 1;
        }
    }
    i = cdata.player().get_skill(300).level * 5 +
        cdata.player().get_skill(12).level + 25;
    if (game()->date.hour >= 19 || game()->date.hour < 7)
    {
        i = i * 15 / 10;
    }
    if (steal_target->quality == Quality::great)
    {
        i = i * 8 / 10;
    }
    if (steal_target->quality >= Quality::miracle)
    {
        i = i * 5 / 10;
    }
    make_sound(cdata.player(), 5, 8, false);
    for (int cnt = 16; cnt < ELONA_MAX_CHARACTERS; ++cnt)
    {
        if (cdata[cnt].state() != Character::State::alive)
        {
            continue;
        }
        if (cdata[cnt].sleep != 0)
        {
            continue;
        }
        if (dist(cdata[cnt].position, cdata.player().position) > 5)
        {
            continue;
        }
        if (f2 == 1)
        {
            if (cnt != steal_target_owner.as_character()->index)
            {
                continue;
            }
        }
        p = rnd_capped(i + 1) *
            (80 + (is_in_fov(cdata[cnt]) == 0) * 50 +
             dist(cdata[cnt].position, cdata.player().position) * 20) /
            100;
        if (cnt < 57)
        {
            p = p * 2 / 3;
        }
        if (rnd_capped(cdata[cnt].get_skill(13).level + 1) > p)
        {
            if (is_in_fov(cdata[cnt]))
            {
                txt(i18n::s.get(
                    "core.activity.steal.notice.in_fov", cdata[cnt]));
            }
            else
            {
                txt(i18n::s.get(
                    "core.activity.steal.notice.out_of_fov", cdata[cnt]));
            }
            if (cdata[cnt].role == Role::guard)
            {
                txt(i18n::s.get("core.activity.steal.notice.dialog.guard"));
                chara_modify_impression(cdata[cnt], -5);
            }
            else
            {
                txt(i18n::s.get("core.activity.steal.notice.dialog.other"));
                chara_modify_impression(cdata[cnt], -5);
            }
            cdata[cnt].emotion_icon = 520;
            f = 1;
        }
    }
    if (f)
    {
        txt(i18n::s.get("core.activity.steal.notice.you_are_found"));
        modify_karma(cdata.player(), -5);
        if (const auto owner = steal_target_owner.as_character())
        {
            if (owner->id != CharaId::ebon)
            {
                if (owner->sleep == 0)
                {
                    owner->relationship = -2;
                    chara_act_hostile_action(cdata.player(), *owner);
                    chara_modify_impression(*owner, -20);
                }
            }
        }
        go_hostile();
    }
    if (const auto owner = steal_target_owner.as_character())
    {
        if (owner->state() != Character::State::alive)
        {
            if (f != 1)
            {
                txt(i18n::s.get("core.activity.steal.target_is_dead"));
                f = 1;
            }
        }
        if (owner->role == Role::user)
        {
            if (f != 1)
            {
                txt(i18n::s.get("core.activity.steal.cannot_be_stolen"));
                f = 1;
            }
        }
        if (dist(doer.position, owner->position) >= 3)
        {
            if (f != 1)
            {
                txt(i18n::s.get("core.activity.steal.you_lose_the_target"));
                f = 0;
            }
        }
    }
    if (steal_target->number() <= 0)
    {
        f = 1;
    }
    if (steal_target->is_precious)
    {
        if (f != 1)
        {
            txt(i18n::s.get("core.activity.steal.cannot_be_stolen"));
            f = 1;
        }
    }
    if (steal_target->weight >= cdata.player().get_skill(10).level * 500)
    {
        if (f != 1)
        {
            txt(i18n::s.get("core.activity.steal.it_is_too_heavy"));
            f = 1;
        }
    }
    if (itemusingfind(steal_target, true) != -1)
    {
        if (f != 1)
        {
            txt(i18n::s.get("core.action.someone_else_is_using"));
            f = 1;
        }
    }
    if (f)
    {
        txt(i18n::s.get("core.activity.steal.abort"));
        doer.activity.finish();
    }
}



void activity_steal_end(Character& doer, const ItemRef& steal_target)
{
    const auto owner = item_get_owner(steal_target).as_character();
    if ((owner && owner->state() != Character::State::alive) ||
        steal_target->number() == 0)
    {
        txt(i18n::s.get("core.activity.steal.abort"));
        doer.activity.finish();
        return;
    }

    in = 1;
    if (steal_target->id == "core.gold_piece")
    {
        in = steal_target->number();
    }

    const auto slot_opt = inv_get_free_slot(inv_player());
    if (!slot_opt)
    {
        txt(i18n::s.get("core.action.pick_up.your_inventory_is_full"));
        doer.activity.finish();
        return;
    }
    const auto slot = *slot_opt;
    steal_target->is_quest_target = false;
    if (steal_target->body_part != 0)
    {
        auto& item_owner = *item_get_owner(steal_target).as_character();
        p = steal_target->body_part;
        item_owner.equipment_slots[p - 100].unequip();
        steal_target->body_part = 0;
        chara_refresh(item_owner);
    }

    const auto stolen_item =
        item_separate(steal_target, inv_player(), slot, in);
    stolen_item->is_stolen = true;
    stolen_item->own_state = OwnState::none;
    txt(i18n::s.get("core.activity.steal.succeed", stolen_item));
    const auto item_weight = stolen_item->weight;
    if (stolen_item->id == "core.gold_piece")
    {
        snd("core.getgold1");
        earn_gold(cdata.player(), in);
        stolen_item->remove();
    }
    else
    {
        inv_stack(inv_player(), stolen_item, true);
        sound_pick_up();
    }
    refresh_burden_state();
    chara_gain_skill_exp(
        cdata.player(), 300, clamp(item_weight / 25, 0, 450) + 50);
    if (cdata.player().karma >= -30)
    {
        if (rnd(3) == 0)
        {
            txt(i18n::s.get("core.activity.steal.guilt"));
            modify_karma(cdata.player(), -1);
        }
    }
    doer.activity.finish();
}

} // namespace



void rowact_check(Character& chara)
{
    if (chara.activity)
    {
        if (chara.activity.id != "core.travel")
        {
            chara.activity.is_interrupted = true;
        }
    }
}



void rowact_item(const ItemRef& item)
{
    for (auto&& chara : cdata.all())
    {
        if (chara.state() != Character::State::alive)
            continue;
        if (chara.activity.turns <= 0)
            continue;

        if (chara.activity.id == "core.eat" || chara.activity.id == "core.read")
        {
            if (chara.activity.item == item)
            {
                chara.activity.finish();
                txt(i18n::s.get("core.activity.cancel.item", chara));
            }
        }
    }
}



void activity_handle_damage(Character& chara)
{
    bool stop = false;
    if (chara.is_player())
    {
        if (chara.activity.id != "core.eat" &&
            chara.activity.id != "core.read" &&
            chara.activity.id != "core.travel")
        {
            stop = true;
        }
        else
        {
            screenupdate = -1;
            update_screen();
            stop = prompt_stop_activity(chara);
        }
    }
    if (stop)
    {
        if (is_in_fov(chara))
        {
            txt(i18n::s.get_data_text(
                "core.activity", chara.activity.id, "canceled", chara));
        }
        chara.activity.finish();
    }
    screenupdate = -1;
    update_screen();
    chara.activity.is_interrupted = false;
}



optional<TurnResult> activity_proc(Character& chara)
{
    --chara.activity.turns;

    const auto auto_turn = [&](int delay) {
        if (chara.is_player())
        {
            elona::auto_turn(delay);
        }
    };

    if (chara.activity.id == "core.fish")
    {
        auto_turn(g_config.animation_wait() * 2);
        spot_fishing(chara, chara.activity.item);
    }
    else if (chara.activity.id == "core.dig_wall")
    {
        auto_turn(g_config.animation_wait() * 0.75);
        spot_mining_or_wall(chara);
    }
    else if (chara.activity.id == "core.search_material")
    {
        auto_turn(g_config.animation_wait() * 0.75);
        spot_material(chara);
    }
    else if (chara.activity.id == "core.dig_ground")
    {
        auto_turn(g_config.animation_wait() * 0.75);
        spot_digging(chara);
    }
    else if (chara.activity.id == "core.sleep")
    {
        auto_turn(g_config.animation_wait() / 4);
        do_rest(chara);
    }
    else if (chara.activity.id == "core.eat")
    {
        assert(chara.activity.item);
        auto_turn(g_config.animation_wait() * 5);
        return do_eat_command(chara, chara.activity.item.unwrap());
    }
    else if (chara.activity.id == "core.read")
    {
        assert(chara.activity.item);
        auto_turn(g_config.animation_wait() * 1.25);
        return do_read_command(chara, chara.activity.item.unwrap());
    }
    else if (chara.activity.id == "core.sex")
    {
        auto_turn(g_config.animation_wait() * 2.5);
        activity_sex(chara, none);
    }
    else if (chara.activity.id == "core.sleep")
    {
        auto_turn(g_config.animation_wait());
        activity_sleep(chara, chara.activity.item);
    }
    else if (chara.activity.id == "core.build_shelter")
    {
        assert(chara.activity.item);
        auto_turn(g_config.animation_wait());
        activity_build_shelter(chara, chara.activity.item.unwrap());
    }
    else if (chara.activity.id == "core.enter_shelter")
    {
        assert(chara.activity.item);
        auto_turn(g_config.animation_wait());
        activity_enter_shelter(chara, chara.activity.item.unwrap());
    }
    else if (chara.activity.id == "core.harvest")
    {
        assert(chara.activity.item);
        auto_turn(g_config.animation_wait() * 2);
        activity_harvest(chara, chara.activity.item.unwrap());
    }
    else if (chara.activity.id == "core.study")
    {
        assert(chara.activity.item);
        auto_turn(g_config.animation_wait() * 2);
        activity_study(chara, chara.activity.item.unwrap());
    }
    else if (chara.activity.id == "core.steal")
    {
        assert(chara.activity.item);
        auto_turn(g_config.animation_wait() * 2.5);
        activity_steal(chara, chara.activity.item.unwrap());
    }
    else if (chara.activity.id == "core.blend")
    {
        auto_turn(g_config.animation_wait());
        activity_blending();
    }
    else if (chara.activity.id == "core.perform")
    {
        assert(chara.activity.item);
        auto_turn(g_config.animation_wait() * 2);
        activity_perform(chara, chara.activity.item.unwrap());
    }
    else if (chara.activity.id == "core.travel")
    {
        map_global_proc_travel_events(chara);
        return proc_movement_event(chara);
    }
    else
    {
        // do nothing
    }

    if (chara.activity.turns > 0)
    {
        return TurnResult::turn_end;
    }
    chara.activity.finish();
    if (chara.is_player())
    {
        if (chatteleport == 1)
        {
            chatteleport = 0;
            return TurnResult::exit_map;
        }
    }

    return none;
}



void activity_perform(Character& performer, ItemRef instrument)
{
    if (!performer.activity)
    {
        activity_perform_start(performer, instrument);
    }
    else if (performer.activity.turns > 0)
    {
        activity_perform_doing(performer);
    }
    else
    {
        activity_perform_end(performer);
    }
}



void activity_sex(Character& chara_a, optional_ref<Character> chara_b)
{
    int sexhost = 0;
    if (!chara_a.activity)
    {
        assert(chara_b);
        chara_a.activity.id = "core.sex";
        chara_a.activity.turns = 25 + rnd(10);
        chara_a.activity_target = chara_b->index;
        chara_b->activity.id = "core.sex";
        chara_b->activity.turns = chara_a.activity.turns * 2;
        chara_b->activity_target = chara_a.index + 10000;
        if (is_in_fov(chara_a))
        {
            txt(i18n::s.get("core.activity.sex.take_clothes_off", chara_a));
        }
        return;
    }

    sexhost = 1;
    auto target_index = chara_a.activity_target;
    if (target_index >= 10000)
    {
        target_index -= 10000;
        sexhost = 0;
    }
    if (cdata[target_index].state() != Character::State::alive ||
        cdata[target_index].activity.id != "core.sex")
    {
        if (is_in_fov(chara_a))
        {
            txt(i18n::s.get(
                "core.activity.sex.spare_life",
                i18n::s.get_enum("core.ui.sex2", cdata[target_index].sex),
                cdata[target_index]));
        }
        chara_a.activity.finish();
        cdata[target_index].activity.finish();
        return;
    }
    if (chara_a.is_player())
    {
        if (!action_sp(cdata.player(), 1 + rnd(2)))
        {
            txt(i18n::s.get("core.magic.common.too_exhausted"));
            chara_a.activity.finish();
            cdata[target_index].activity.finish();
            return;
        }
    }
    chara_a.emotion_icon = 317;
    if (chara_a.activity.turns > 0)
    {
        if (sexhost == 0)
        {
            if (chara_a.activity.turns % 5 == 0)
            {
                if (is_in_fov(chara_a))
                {
                    txt(i18n::s.get("core.activity.sex.dialog"),
                        Message::color{ColorIndex::cyan});
                }
            }
        }
        return;
    }
    if (sexhost == 0)
    {
        chara_a.activity.finish();
        return;
    }

    {
        chara_a.drunk = 0;
        if (rnd(15) == 0)
        {
            status_ailment_damage(chara_a, StatusAilment::sick, 200);
        }
        chara_gain_skill_exp(
            chara_a, 17, 250 + (chara_a.is_map_local()) * 1000);
    }

    {
        if (rnd(3) == 0)
        {
            status_ailment_damage(
                cdata[target_index], StatusAilment::insane, 500);
        }
        if (rnd(5) == 0)
        {
            status_ailment_damage(
                cdata[target_index], StatusAilment::paralyzed, 500);
        }
        status_ailment_damage(cdata[target_index], StatusAilment::insane, 300);
        heal_insanity(cdata[target_index], 10);
        chara_gain_skill_exp(
            cdata[target_index],
            11,
            250 + (cdata[target_index].is_map_local()) * 1000);
        chara_gain_skill_exp(
            cdata[target_index],
            15,
            250 + (cdata[target_index].is_map_local()) * 1000);
        if (rnd(15) == 0)
        {
            status_ailment_damage(
                cdata[target_index], StatusAilment::sick, 200);
        }
        chara_gain_skill_exp(
            cdata[target_index],
            17,
            250 + (cdata[target_index].is_map_local()) * 1000);
    }

    int sexvalue = chara_a.get_skill(17).level * (50 + rnd(50)) + 100;

    std::string dialog_head;
    std::string dialog_tail;
    std::string dialog_after;

    if (is_in_fov(chara_a))
    {
        dialog_head =
            i18n::s.get("core.activity.sex.after_dialog", cdata[target_index]);
        Message::instance().txtef(ColorIndex::yellow_green);
    }
    if (target_index != 0)
    {
        if (cdata[target_index].gold >= sexvalue)
        {
            if (is_in_fov(chara_a))
            {
                dialog_tail =
                    i18n::s.get("core.activity.sex.take", cdata[target_index]);
            }
        }
        else
        {
            if (is_in_fov(chara_a))
            {
                dialog_tail = i18n::s.get(
                    "core.activity.sex.take_all_i_have", cdata[target_index]);
                if (rnd(3) == 0)
                {
                    if (!chara_a.is_player())
                    {
                        dialog_after = i18n::s.get(
                            "core.activity.sex.gets_furious", chara_a);
                        chara_a.enemy_id = target_index;
                        chara_a.hate = 20;
                    }
                }
            }
            if (cdata[target_index].gold <= 0)
            {
                cdata[target_index].gold = 1;
            }
            sexvalue = cdata[target_index].gold;
        }
        cdata[target_index].gold -= sexvalue;
        if (chara_a.is_player())
        {
            chara_modify_impression(cdata[target_index], 5);
            flt();
            itemcreate_map_inv(54, chara_a.position, sexvalue);
            dialog_after +=
                i18n::s.get("core.common.something_is_put_on_the_ground");
            modify_karma(cdata.player(), -1);
        }
        else
        {
            earn_gold(chara_a, sexvalue);
        }
    }
    if (!dialog_head.empty() || !dialog_tail.empty() || !dialog_after.empty())
    {
        txt(i18n::s.get("core.activity.sex.format", dialog_head, dialog_tail) +
            dialog_after);
    }
    chara_a.activity.finish();
    cdata[target_index].activity.finish();
}



void activity_eating(Character& eater, const ItemRef& food)
{
    if (!eater.activity)
    {
        activity_eating_start(eater, food);
    }
    else if (eater.activity.turns > 0)
    {
        // Do nothing.
    }
    else
    {
        if (is_in_fov(eater))
        {
            txt(i18n::s.get("core.activity.eat.finish", eater, food));
        }
        activity_eating_finish(eater, food);
        eater.activity.finish();
    }
}



void activity_eating_finish(Character& eater, const ItemRef& food)
{
    apply_general_eating_effect(eater, food);

    if (eater.is_player())
    {
        item_identify(food, IdentifyState::partly);
    }
    if (chara_unequip(food))
    {
        chara_refresh(eater);
    }

    food->modify_number(-1);

    if (eater.is_player())
    {
        show_eating_message(eater);
    }
    else
    {
        if (food == eater.ai_item)
        {
            eater.ai_item = nullptr;
        }
        if (eater.was_passed_item_by_you_just_now())
        {
            if (food->material == "core.raw" && food->param3 < 0)
            {
                txt(i18n::s.get("core.food.passed_rotten"),
                    Message::color{ColorIndex::cyan});
                damage_hp(eater, 999, -12);
                if (eater.state() != Character::State::alive)
                {
                    if (eater.relationship > 0)
                    {
                        modify_karma(cdata.player(), -5);
                    }
                    else
                    {
                        modify_karma(cdata.player(), -1);
                    }
                }
                chara_modify_impression(eater, -25);
                return;
            }
        }
    }

    chara_anorexia(eater);

    if ((food->id == "core.kagami_mochi" && rnd(3)) ||
        (food->id == "core.mochi" && rnd(10) == 0))
    {
        if (is_in_fov(eater))
        {
            txt(i18n::s.get("core.food.mochi.chokes", eater),
                Message::color{ColorIndex::purple});
            txt(i18n::s.get("core.food.mochi.dialog"));
        }
        ++eater.choked;
    }
}



void activity_sleep(Character& doer, const OptionalItemRef& bed)
{
    if (!doer.is_player())
    {
        doer.activity.finish();
        return;
    }

    if (!doer.activity)
    {
        activity_sleep_start(doer, bed);
        return;
    }
    else
    {
        if (doer.activity.turns > 0)
        {
            activity_sleep_doing(doer, bed);
        }
        else
        {
            activity_sleep_end(doer, bed);
        }
    }
}



void activity_build_shelter(Character& doer, const ItemRef& shelter)
{
    if (!doer.is_player())
    {
        doer.activity.finish();
        return;
    }

    if (!doer.activity)
    {
        activity_build_shelter_start(doer, shelter);
        return;
    }
    else
    {
        if (doer.activity.turns > 0)
        {
            activity_build_shelter_doing(doer, shelter);
        }
        else
        {
            activity_build_shelter_end(doer, shelter);
        }
    }
}



void activity_enter_shelter(Character& doer, const ItemRef& shelter)
{
    if (!doer.is_player())
    {
        doer.activity.finish();
        return;
    }

    if (!doer.activity)
    {
        activity_enter_shelter_start(doer, shelter);
        return;
    }
    else
    {
        if (doer.activity.turns > 0)
        {
            activity_enter_shelter_doing(doer, shelter);
        }
        else
        {
            activity_enter_shelter_end(doer, shelter);
        }
    }
}



void activity_harvest(Character& doer, const ItemRef& crop)
{
    if (!doer.is_player())
    {
        doer.activity.finish();
        return;
    }

    if (!doer.activity)
    {
        activity_harvest_start(doer, crop);
        return;
    }
    else
    {
        if (doer.activity.turns > 0)
        {
            activity_harvest_doing(doer, crop);
        }
        else
        {
            activity_harvest_end(doer, crop);
        }
    }
}



void activity_study(Character& doer, const ItemRef& textbook)
{
    if (!doer.is_player())
    {
        doer.activity.finish();
        return;
    }

    if (!doer.activity)
    {
        activity_study_start(doer, textbook);
        return;
    }
    else
    {
        if (doer.activity.turns > 0)
        {
            activity_study_doing(doer, textbook);
        }
        else
        {
            activity_study_end(doer, textbook);
        }
    }
}



void activity_steal(Character& doer, const ItemRef& steal_target)
{
    if (!doer.is_player())
    {
        doer.activity.finish();
        return;
    }

    if (!doer.activity)
    {
        activity_steal_start(doer, steal_target);
        return;
    }
    else
    {
        if (doer.activity.turns > 0)
        {
            activity_steal_doing(doer, steal_target);
        }
        else
        {
            activity_steal_end(doer, steal_target);
        }
    }
}



void spot_fishing(Character& fisher, OptionalItemRef rod)
{
    static int fishstat;

    if (!fisher.activity)
    {
        txt(i18n::s.get("core.activity.fishing.start"));
        snd("core.fish_cast");
        if (rowactre == 0)
        {
            fisher.activity.item = rod;
        }
        fisher.activity.id = "core.fish";
        fisher.activity.turns = 100;
        racount = 0;
        fishstat = 0;
        gsel(9);
        picload(filesystem::dirs::graphic() / u8"fishing.bmp", 0, 0, true);
        gsel(0);
        return;
    }
    if (rowactre != 0)
    {
        search_material_spot();
        return;
    }
    if (fisher.activity.turns > 0)
    {
        if (rnd(5) == 0)
        {
            fishstat = 1;
            fish = fish_select_at_random(fisher.activity.item->param4);
        }
        if (fishstat == 1)
        {
            if (rnd(5) == 0)
            {
                if (g_config.animation_wait() != 0)
                {
                    for (int cnt = 0, cnt_end = (4 + rnd(4)); cnt < cnt_end;
                         ++cnt)
                    {
                        fishanime(0) = 1;
                        fishanime(1) = 3 + rnd(3);
                        addefmap(fishx, fishy, 4, 2);
                        ++scrturn;
                        update_screen();
                        redraw();
                        await(g_config.animation_wait() * 2);
                    }
                }
                if (rnd(3) == 0)
                {
                    fishstat = 2;
                }
                if (rnd(6) == 0)
                {
                    fishstat = 0;
                }
                fishanime = 0;
            }
        }
        if (fishstat == 2)
        {
            fishanime = 2;
            snd("core.water2");
            cdata.player().emotion_icon = 220;
            if (g_config.animation_wait() != 0)
            {
                for (int cnt = 0, cnt_end = (8 + rnd(10)); cnt < cnt_end; ++cnt)
                {
                    ++scrturn;
                    update_screen();
                    redraw();
                    await(g_config.animation_wait() * 2);
                }
            }
            if (rnd(10))
            {
                fishstat = 3;
            }
            else
            {
                fishstat = 0;
            }
            fishanime = 0;
        }
        if (fishstat == 3)
        {
            fishanime = 3;
            if (g_config.animation_wait() != 0)
            {
                for (int cnt = 0, cnt_end = (28 + rnd(15)); cnt < cnt_end;
                     ++cnt)
                {
                    if (cnt % 7 == 0)
                    {
                        snd("core.fish_fight");
                    }
                    fishanime(1) = cnt;
                    ++scrturn;
                    update_screen();
                    addefmap(fishx, fishy, 5, 2);
                    redraw();
                    await(g_config.animation_wait() * 2);
                }
            }
            if (the_fish_db[fish]->difficulty >=
                rnd_capped(cdata.player().get_skill(185).level + 1))
            {
                fishstat = 0;
            }
            else
            {
                fishstat = 4;
            }
            fishanime = 0;
        }
        if (fishstat == 4)
        {
            fishanime = 4;
            snd("core.fish_get");
            if (g_config.animation_wait() != 0)
            {
                for (int cnt = 0; cnt < 21; ++cnt)
                {
                    fishanime(1) = cnt;
                    if (cnt == 1)
                    {
                        addefmap(fishx, fishy, 1, 3);
                    }
                    ++scrturn;
                    update_screen();
                    redraw();
                    await(g_config.animation_wait() * 2);
                }
            }
            sound_pick_up();
            fishanime = 0;
            fisher.activity.finish();
            fish_get(fish);
            chara_gain_exp_fishing(cdata.player());
            cdata.player().emotion_icon = 306;
        }
        if (rnd(10) == 0)
        {
            damage_sp(fisher, 1);
        }
        return;
    }
    txt(i18n::s.get("core.activity.fishing.fail"));
    fisher.activity.finish();
}



void spot_material(Character& chara)
{
    if (!chara.activity)
    {
        chara.activity.id = "core.search_material";
        chara.activity.turns = 40;
        txt(i18n::s.get("core.activity.material.start"));
        racount = 0;
        return;
    }
    if (rowactre != 0)
    {
        search_material_spot();
        return;
    }
    chara.activity.finish();
}



void spot_digging(Character& chara)
{
    if (!chara.activity)
    {
        chara.activity.id = "core.dig_ground";
        chara.activity.turns = 20;
        if (rowactre == 0)
        {
            txt(i18n::s.get("core.activity.dig_spot.start.global"));
        }
        else
        {
            txt(i18n::s.get("core.activity.dig_spot.start.other"));
        }
        racount = 0;
        return;
    }
    if (rowactre != 0)
    {
        search_material_spot();
        return;
    }
    if (chara.activity.turns > 0)
    {
        if (chara.turn % 5 == 0)
        {
            txt(i18n::s.get("core.activity.dig_spot.sound"),
                Message::color{ColorIndex::blue});
        }
        return;
    }
    txt(i18n::s.get("core.activity.dig_spot.finish"));
    if (map_data.type == mdata_t::MapType::world_map)
    {
        for (const auto& item : *inv_player())
        {
            if (item->id == "core.treasure_map" && item->param1 != 0 &&
                item->param1 == cdata.player().position.x &&
                item->param2 == cdata.player().position.y)
            {
                snd("core.chest1");
                txt(i18n::s.get("core.activity.dig_spot.something_is_there"),
                    Message::color{ColorIndex::orange});
                msg_halt();
                snd("core.ding2");
                flt();
                itemcreate_map_inv(622, cdata.player().position, 2 + rnd(3));
                flt();
                itemcreate_map_inv(55, cdata.player().position, 1 + rnd(3));
                flt();
                itemcreate_map_inv(
                    54, cdata.player().position, rnd(10000) + 2000);
                for (int i = 0; i < 4; ++i)
                {
                    flt(calcobjlv(cdata.player().level + 10),
                        calcfixlv(Quality::good));
                    if (i == 0)
                    {
                        fixlv = Quality::godly;
                    }
                    flttypemajor = choice(fsetchest);
                    itemcreate_map_inv(0, cdata.player().position, 0);
                }
                txt(i18n::s.get("core.common.something_is_put_on_the_ground"));
                save_trigger_autosaving();
                item->modify_number(-1);
                break;
            }
        }
    }
    spillfrag(refx, refy, 1);
    chara.activity.finish();
}



void spot_mining_or_wall(Character& chara)
{
    static int countdig{};

    if (!chara.activity)
    {
        chara.activity.id = "core.dig_wall";
        chara.activity.turns = 40;
        if (rowactre == 0)
        {
            txt(i18n::s.get("core.activity.dig_mining.start.wall"));
        }
        else
        {
            txt(i18n::s.get("core.activity.dig_mining.start.spot"));
        }
        if (chip_data.for_cell(refx, refy).kind == 6)
        {
            txt(i18n::s.get("core.activity.dig_mining.start.hard"));
        }
        countdig = 0;
        racount = 0;
        return;
    }
    if (rowactre != 0)
    {
        search_material_spot();
        return;
    }
    if (chara.activity.turns > 0)
    {
        if (rnd(5) == 0)
        {
            damage_sp(chara, 1);
        }
        ++countdig;
        f = 0;
        if (chip_data.for_cell(refx, refy).kind == 6)
        {
            if (rnd(12000) <
                chara.get_skill(10).level + chara.get_skill(163).level * 10)
            {
                f = 1;
            }
            p = 30 - chara.get_skill(163).level / 2;
            if (p > 0)
            {
                if (countdig <= p)
                {
                    f = 0;
                }
            }
        }
        else
        {
            if (rnd(1500) <
                chara.get_skill(10).level + chara.get_skill(163).level * 10)
            {
                f = 1;
            }
            p = 20 - chara.get_skill(163).level / 2;
            if (p > 0)
            {
                if (countdig <= p)
                {
                    f = 0;
                }
            }
        }
        if (f == 1 ||
            (story_quest_progress("core.tutorial") == 2 &&
             game()->current_map == mdata_t::MapId::your_home))
        {
            rtval = 0;
            if (rnd(5) == 0)
            {
                rtval = 54;
            }
            if (rnd(8) == 0)
            {
                rtval = -1;
            }
            if (cell_data.at(refx, refy).feats != 0)
            {
                cell_featread(refx, refy);
                if (feat(1) == 22)
                {
                    discover_hidden_path();
                }
            }
            cell_data.at(refx, refy).chip_id_actual = tile_tunnel;
            spillfrag(refx, refy, 2);
            snd("core.crush1");
            BreakingAnimation({refx, refy}).play();
            txt(i18n::s.get("core.activity.dig_mining.finish.wall"));
            if (story_quest_progress("core.tutorial") == 2 &&
                game()->current_map == mdata_t::MapId::your_home)
            {
                flt();
                if (const auto item = itemcreate_map_inv(208, digx, digy, 0))
                {
                    item->curse_state = CurseState::cursed;
                }
                txt(i18n::s.get("core.activity.dig_mining.finish.find"));
                story_quest_set_progress("core.tutorial", 3);
            }
            else if (
                rtval != 0 && game()->current_map != mdata_t::MapId::shelter_)
            {
                if (rtval > 0)
                {
                    flt();
                    itemcreate_map_inv(rtval, digx, digy, 0);
                }
                else if (rtval == -1)
                {
                    flt(calcobjlv(game()->current_dungeon_level),
                        calcfixlv(Quality::good));
                    flttypemajor = 77000;
                    itemcreate_map_inv(0, digx, digy, 0);
                }
                txt(i18n::s.get("core.activity.dig_mining.finish.find"));
            }
            chara_gain_exp_digging(cdata.player());
            chara.activity.finish();
        }
        else if (chara.turn % 5 == 0)
        {
            txt(i18n::s.get("core.activity.dig_spot.sound"),
                Message::color{ColorIndex::blue});
        }
        return;
    }
    txt(i18n::s.get("core.activity.dig_mining.fail"));
    chara.activity.finish();
}



TurnResult do_dig_after_sp_check(Character& chara)
{
    if (chara.sp < 0)
    {
        txt(i18n::s.get("core.action.dig.too_exhausted"));
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    rowactre = 0;
    digx = tlocx;
    digy = tlocy;
    spot_mining_or_wall(chara);
    return TurnResult::turn_end;
}



void sleep_start(const OptionalItemRef& bed)
{
    int timeslept = 0;
    if (game()->current_map == mdata_t::MapId::quest)
    {
        txt(i18n::s.get("core.activity.sleep.but_you_cannot"));
        game()->character_and_status_for_gene = 0;
        return;
    }
    if (game()->catches_god_signal)
    {
        txtgod(cdata.player().god_id, 10);
    }
    load_sleep_background();
    play_music("core.mcCoda", false);
    msg_halt();
    for (int cnt = 0; cnt < 20; ++cnt)
    {
        gmode(2, cnt * 10);
        draw_sleep_background_frame();
        await(g_config.animation_wait() * 10);
    }
    gmode(2);
    for (int cnt = 0; cnt < ELONA_MAX_PARTY_CHARACTERS; ++cnt)
    {
        cdata[cnt].wet = 0;
        cdata[cnt].poisoned = 0;
        cdata[cnt].sleep = 0;
        cdata[cnt].confused = 0;
        cdata[cnt].blind = 0;
        cdata[cnt].paralyzed = 0;
        cdata[cnt].dimmed = 0;
        cdata[cnt].drunk = 0;
        cdata[cnt].bleeding = 0;
        game()->continuous_active_hours = 0;
        cdata[cnt].hp = cdata[cnt].max_hp;
        cdata[cnt].mp = cdata[cnt].max_mp;
        cdata[cnt].sp = cdata[cnt].max_sp;
        status_ailment_heal(cdata[cnt], StatusAilment::sick, 7 + rnd(7));
        if (cdata[cnt].has_anorexia())
        {
            cdata[cnt].anorexia_count -= rnd(6);
        }
        else
        {
            cdata[cnt].anorexia_count -= rnd(3);
        }
        if (cdata[cnt].anorexia_count < 0)
        {
            cure_anorexia(cdata[cnt]);
            cdata[cnt].anorexia_count = 0;
        }
        heal_insanity(cdata[cnt], 10);
        if (cdata[cnt].has_lay_hand())
        {
            cdata[cnt].is_lay_hand_available() = true;
        }
    }
    mode = 9;
    timeslept = 7 + rnd(5);
    for (int cnt = 0, cnt_end = (timeslept); cnt < cnt_end; ++cnt)
    {
        ++game()->date.hour;
        weather_changes();
        if (mode != 9)
        {
            load_sleep_background();
            mode = 9;
        }
        game()->continuous_active_hours = 0;
        game()->date.minute = 0;
        draw_sleep_background_frame();
        await(g_config.animation_wait() * 25);
    }
    if (game()->character_and_status_for_gene != 0)
    {
        optional_ref<Character> gene_chara;
        for (auto& ally : cdata.allies())
        {
            if (ally.state() == Character::State::alive)
            {
                if (ally.has_made_gene())
                {
                    gene_chara = ally;
                    break;
                }
            }
        }
        if (gene_chara)
        {
            gene_chara->has_made_gene() = false;
            show_random_event_window(
                i18n::s.get("core.activity.sleep.new_gene.title"),
                i18n::s.get("core.activity.sleep.new_gene.text", *gene_chara),
                {i18n::s.get_enum("core.activity.sleep.new_gene.choices", 0)},
                u8"core.bg_re14");
            save_save_gene();
        }
    }
    draw_sleep_background_frame();
    game()->character_and_status_for_gene = 0;
    mode = 0;
    wake_up();
    cdata.player().nutrition -=
        1500 / (cdata.player().traits().level("core.slow_digestion") + 1);
    txt(i18n::s.get("core.activity.sleep.slept_for", timeslept),
        Message::color{ColorIndex::green});

    optional<int> bed_quality;
    if (bed && bed->param1 != 0 && bed->number() != 0 &&
        the_item_db[bed->id]->subcategory == 60004)
    {
        bed_quality = bed->param1;
    }

    if (!bed_quality)
    {
        txt(i18n::s.get("core.activity.sleep.wake_up.so_so"));
    }
    else
    {
        i = 0;
        for (int cnt = 10; cnt < 18; ++cnt)
        {
            i += cdata.player().get_skill(cnt).base_level;
        }
        i = clamp(i / 6, 10, 1000);
        exp = i * i * i / 10;
        game()->sleep_experience =
            game()->sleep_experience * (*bed_quality) / 100;
        grown = 0;
        for (int cnt = 0;; ++cnt)
        {
            if (game()->sleep_experience >= exp)
            {
                game()->sleep_experience -= exp;
            }
            else if (cnt != 0)
            {
                break;
            }
            modify_potential(cdata.player(), 10 + rnd(8), 1);
            ++grown;
            if (cnt > 6)
            {
                if (rnd(5) == 0)
                {
                    game()->sleep_experience = 0;
                    break;
                }
            }
        }
        txt(i18n::s.get("core.activity.sleep.wake_up.good", grown),
            Message::color{ColorIndex::green});
    }

    msg_halt();
    play_music();
    save_trigger_autosaving();
    if (area_data[game()->current_map].id == mdata_t::MapId::shop)
    {
        update_shop();
    }
}

} // namespace elona
