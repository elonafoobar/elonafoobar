#include <sstream>

#include "ability.hpp"
#include "building.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "class.hpp"
#include "data/types/type_race.hpp"
#include "game.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "menu.hpp"
#include "text.hpp"
#include "trait.hpp"
#include "variables.hpp"



namespace elona
{

namespace
{

std::string game_date_time()
{
    const auto Y = std::to_string(game_data.date.year);
    const auto m = std::to_string(game_data.date.month);
    const auto d = std::to_string(game_data.date.day);
    const auto H = std::to_string(game_data.date.hour);
    const auto M = std::to_string(game_data.date.minute);

    return Y + u8"年" + m + u8"月" + d + u8"日 " + H + u8"時" + M + u8"分";
}

} // namespace



void save_dump_player_info()
{
    // TODO: i18n

    std::stringstream ss;

    ss << u8"Elona 1.22" << std::endl;
    ss << u8"Elona foobar " << latest_version.long_string() << std::endl;

    ss << u8"キャラクター情報 " << game_date_time() << "  " << mdatan(0)
       << std::endl;

    ss << std::endl;

    ss << "  " << fixtxt(cdata.player().alias + cdata.player().name, 34)
       << i18n::s.get_enum("core.ui.sex", cdata.player().sex) << " "
       << calc_age(cdata.player()) << u8"歳  " << cdata.player().height
       << u8"cm " << cdata.player().weight << u8"kg" << std::endl;

    ss << std::endl;

    ss << fixtxt(
              u8"種族       : " +
                  the_race_db.get_text(cdata.player().race, "name"),
              30)
       << fixtxt(u8"信仰      : " + god_name(cdata.player().god_id), 32)
       << std::endl;
    ss << fixtxt(u8"職業       : " + class_get_name(cdata.player().class_), 30)
       << fixtxt(u8"所属      : " + guildname(), 32) << std::endl;
    ss << fixtxt(u8"レベル     : " + std::to_string(cdata.player().level), 30)
       << fixtxt(u8"経過日数  : " + std::to_string(game_data.play_days), 32)
       << std::endl;
    ss << fixtxt(
              u8"残りBP     : " + std::to_string(cdata.player().skill_bonus),
              30)
       << fixtxt(u8"経過ターン: " + std::to_string(game_data.play_turns), 32)
       << std::endl;
    ss << fixtxt(u8"金貨       : " + std::to_string(cdata.player().gold), 30)
       << fixtxt(u8"殺害数    : " + std::to_string(game_data.kill_count), 32)
       << std::endl;
    ss << fixtxt(
              u8"プラチナ   : " + std::to_string(cdata.player().platinum_coin),
              30)
       << fixtxt(
              u8"最深到達  : " +
                  std::to_string(game_data.deepest_dungeon_level) + u8"階相当",
              32)
       << std::endl;
    ss << fixtxt(
              u8"プレイ時間 : "s +
                  cnvplaytime((
                      game_data.play_time + timeGetTime() / 1000 - time_begin)),
              30)
       << std::endl;

    ss << std::endl;

    s(1) = u8"生命力    : " +
        std::to_string(cdata.player().get_skill(2).level) + u8"(" +
        std::to_string(cdata.player().get_skill(2).base_level) + u8")";
    s(2) = u8"マナ      : " +
        std::to_string(cdata.player().get_skill(3).level) + u8"(" +
        std::to_string(cdata.player().get_skill(3).base_level) + u8")";
    s(3) = u8"狂気度    : " + std::to_string(cdata.player().insanity);
    s(4) = u8"速度      : " + std::to_string(cdata.player().current_speed);
    s(5) = u8"名声度    : " + std::to_string(cdata.player().fame);
    s(6) = u8"カルマ    : " + std::to_string(cdata.player().karma);
    s(7) = u8"DV        : " + std::to_string(cdata.player().dv);
    s(8) = u8"PV        : " + std::to_string(cdata.player().pv);
    s(9) = "";

    for (int cnt = 0; cnt < 8; ++cnt)
    {
        s = "";
        p = cdata.player().get_skill(10 + cnt).potential;
        if (p >= 200)
        {
            s += u8"superb"s;
        }
        else if (p >= 150)
        {
            s += u8"great"s;
        }
        else if (p >= 100)
        {
            s += u8"good"s;
        }
        else if (p >= 50)
        {
            s += u8"bad"s;
        }
        else
        {
            s += u8"hopeless"s;
        }
        s = fixtxt(s, 15);
        s = fixtxt(
                i18n::s.get_enum("core.ui.attribute", cnt) + u8"    : "s +
                    cdata.player().get_skill(10 + cnt).level + u8"("s +
                    cdata.player().get_skill(10 + cnt).base_level + u8")"s,
                24) +
            s;

        ss << (s + s(1 + cnt)) << std::endl;
    }

    ss << std::endl;

    append_accuracy_info(cdata.player(), 1);

    attackskill = 106;
    {
        const auto evade = calc_evasion(cdata.player());
        const auto prot = calc_attack_protection(cdata.player());

        ss << u8"回避    : " << evade << u8"%" << std::endl;
        ss << u8"軽減    : " << (100 - 10000 / (prot.rate + 100)) << u8"% + "
           << prot.dice_x << u8"d" << prot.dice_y << std::endl;
    }

    ss << std::endl;

    ss << u8"------------------------------ 装備品 合計重量"
       << cnvweight(cdata.player().sum_of_equipment_weight) << u8" "
       << get_armor_class_name(cdata.player()) << std::endl;
    ss << std::endl;

    for (const auto& equipment_slot : cdata.player().equipment_slots)
    {
        if (!equipment_slot)
        {
            continue;
        }

        if ((trait(206) != 0 && equipment_slot.type == 2) ||
            (trait(203) != 0 && equipment_slot.type == 9) ||
            (trait(205) != 0 && equipment_slot.type == 3))
        {
            continue;
        }

        std::string item_name = u8"装備なし";
        std::string item_desc;
        p(0) = 0;
        listmax = 0;
        if (equipment_slot.equipment)
        {
            item_name = itemname(equipment_slot.equipment.unwrap());
            item_desc = cnvweight(equipment_slot.equipment->weight);
            item_dump_desc(equipment_slot.equipment.unwrap());
        }
        else
        {
            listmax = 0;
        }

        ss << i18n::s.get_enum("core.ui.body_part", equipment_slot.type)
           << u8":" << std::endl;
        ss << item_name << u8" " << item_desc << std::endl;
        for (int i = 0; i < listmax; ++i)
        {
            ss << listn(0, i) << std::endl;
        }
        ss << std::endl;
    }

    ss << u8"------------------------------ 特徴" << std::endl;
    ss << std::endl;

    trait_load_desc(cdata.player());
    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
    {
        if (list(0, cnt) < 0)
        {
            continue;
        }
        if (list(1, cnt) < 10000)
        {
            continue;
        }
        ss << listn(0, cnt) << std::endl;
    }

    ss << std::endl;

    ss << u8"------------------------------ 仲間" << std::endl;
    ss << std::endl;

    for (const auto& ally : cdata.allies())
    {
        if (ally.state() == Character::State::empty)
        {
            continue;
        }

        ss << ally.name << u8" " << the_race_db.get_text(ally.race, "name")
           << u8"の" << class_get_name(ally.class_) << u8" "
           << i18n::s.get_enum("core.ui.sex", ally.sex) << u8" "
           << calc_age(ally) << u8"歳" << u8"  " << ally.height << u8"cm"
           << u8" " << ally.weight << u8"kg" << std::endl;
        ss << u8"レベル " << ally.level;
        if (ally.is_married())
        {
            ss << u8" 婚約済み";
        }
        ss << std::endl << std::endl;
    }

    ss << u8"------------------------------ 称号" << std::endl;
    ss << std::endl;

    for (int i = 0; i < 9; ++i)
    {
        if (game_data.ranks.at(i) < 10000)
        {
            ss << ranktitle(i) << u8" Rank." << game_data.ranks.at(i) / 100
               << std::endl;
            ss << u8"給料: 約 " << calcincome(i) << u8" gold  ノルマ: ";
            if (i == 3 || i == 4 || i == 5 || i == 8)
            {
                ss << u8"なし";
            }
            else
            {
                ss << game_data.rank_deadlines.at(i) << u8"日以内";
            }
            ss << std::endl;
        }
    }

    std::ofstream out{
        (filesystem::dirs::save() / fs::u8path(playerid + u8".txt")).native()};
    out << ss.str() << std::endl;

    std::cout << ss.str();
}

} // namespace elona
