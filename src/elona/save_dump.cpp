#include <sstream>

#include "building.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "class.hpp"
#include "data/types/type_race.hpp"
#include "data/types/type_skill.hpp"
#include "game.hpp"
#include "god.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "menu.hpp"
#include "skill.hpp"
#include "text.hpp"
#include "trait.hpp"
#include "variables.hpp"



namespace elona
{

namespace
{

std::string game_date_time_string()
{
    const auto dt = game_date_time();

    const auto Y = std::to_string(dt.year());
    const auto m = std::to_string(dt.month());
    const auto d = std::to_string(dt.day());
    const auto H = std::to_string(dt.hour());
    const auto M = std::to_string(dt.minute());

    return Y + "年" + m + "月" + d + "日 " + H + "時" + M + "分";
}

} // namespace



void save_dump_player_info()
{
    // TODO: i18n

    std::stringstream ss;

    ss << "Elona 1.22" << std::endl;
    ss << "Elona foobar " << latest_version.long_string() << std::endl;

    ss << "キャラクター情報 " << game_date_time_string() << "  " << mdatan(0)
       << std::endl;

    ss << std::endl;

    ss << "  " << fixtxt(cdata.player().alias + cdata.player().name, 34)
       << i18n::s.get_enum("core.ui.sex", cdata.player().sex) << " "
       << calc_age(cdata.player()) << "歳  " << cdata.player().height << "cm "
       << cdata.player().weight << "kg" << std::endl;

    ss << std::endl;

    ss << fixtxt(
              "種族       : " +
                  the_race_db.get_text(cdata.player().race, "name"),
              30)
       << fixtxt("信仰      : " + god_get_name(cdata.player().religion), 32)
       << std::endl;
    ss << fixtxt("職業       : " + class_get_name(cdata.player().class_), 30)
       << fixtxt("所属      : " + guildname(), 32) << std::endl;
    ss << fixtxt("レベル     : " + std::to_string(cdata.player().level), 30)
       << fixtxt("経過日数  : " + std::to_string(game()->play_days), 32)
       << std::endl;
    ss << fixtxt(
              "残りBP     : " + std::to_string(cdata.player().skill_bonus), 30)
       << fixtxt("経過ターン: " + std::to_string(game()->play_turns), 32)
       << std::endl;
    ss << fixtxt("金貨       : " + std::to_string(cdata.player().gold), 30)
       << fixtxt("殺害数    : " + std::to_string(game()->total_kill_count), 32)
       << std::endl;
    ss << fixtxt("プラチナ   : " + std::to_string(cdata.player().platinum), 30)
       << fixtxt(
              "最深到達  : " +
                  std::to_string(game()->deepest_dungeon_danger_level) +
                  "階相当",
              32)
       << std::endl;
    ss << fixtxt(
              "プレイ時間 : "s +
                  cnvplaytime(
                      (game()->play_seconds_in_real_world +
                       timeGetTime() / 1000 - time_begin)),
              30)
       << std::endl;

    ss << std::endl;

    s(1) = "生命力    : " +
        std::to_string(cdata.player().skills().level("core.stat_life")) + "(" +
        std::to_string(cdata.player().skills().base_level("core.stat_life")) +
        ")";
    s(2) = "マナ      : " +
        std::to_string(cdata.player().skills().level("core.stat_mana")) + "(" +
        std::to_string(cdata.player().skills().base_level("core.stat_mana")) +
        ")";
    s(3) = "狂気度    : " + std::to_string(cdata.player().insanity);
    s(4) = "速度      : " + std::to_string(cdata.player().current_speed);
    s(5) = "名声度    : " + std::to_string(cdata.player().fame);
    s(6) = "カルマ    : " + std::to_string(cdata.player().karma);
    s(7) = "DV        : " + std::to_string(cdata.player().dv);
    s(8) = "PV        : " + std::to_string(cdata.player().pv);
    s(9) = "";

    for (int cnt = 0; cnt < 8; ++cnt)
    {
        s = "";
        p = cdata.player().skills().potential(
            *the_skill_db.get_id_from_integer(10 + cnt));
        if (p >= 200)
        {
            s += "superb"s;
        }
        else if (p >= 150)
        {
            s += "great"s;
        }
        else if (p >= 100)
        {
            s += "good"s;
        }
        else if (p >= 50)
        {
            s += "bad"s;
        }
        else
        {
            s += "hopeless"s;
        }
        s = fixtxt(s, 15);
        s = fixtxt(
                i18n::s.get_enum("core.ui.attribute", cnt) + "    : "s +
                    cdata.player().skills().level(
                        *the_skill_db.get_id_from_integer(10 + cnt)) +
                    "("s +
                    cdata.player().skills().base_level(
                        *the_skill_db.get_id_from_integer(10 + cnt)) +
                    ")"s,
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

        ss << "回避    : " << evade << "%" << std::endl;
        ss << "軽減    : " << (100 - 10000 / (prot.rate + 100)) << "% + "
           << prot.dice_x << "d" << prot.dice_y << std::endl;
    }

    ss << std::endl;

    ss << "------------------------------ 装備品 合計重量"
       << cnvweight(cdata.player().equipment_weight) << " "
       << get_armor_class_name(cdata.player()) << std::endl;
    ss << std::endl;

    for (const auto& body_part : cdata.player().body_parts)
    {
        if (body_part.is_unequippable())
        {
            continue;
        }

        std::string item_name = "装備なし";
        std::string item_desc;
        p(0) = 0;
        listmax = 0;
        if (const auto equipment = body_part.equipment())
        {
            item_name = itemname(equipment.unwrap());
            item_desc = cnvweight(equipment->weight);
            item_dump_desc(equipment.unwrap());
        }
        else
        {
            listmax = 0;
        }

        ss << i18n::s.get_data_text("core.body_part", body_part.id, "name")
           << ":" << std::endl;
        ss << item_name << " " << item_desc << std::endl;
        for (int i = 0; i < listmax; ++i)
        {
            ss << listn(0, i) << std::endl;
        }
        ss << std::endl;
    }

    ss << "------------------------------ 特徴" << std::endl;
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

    ss << "------------------------------ 仲間" << std::endl;
    ss << std::endl;

    for (const auto& ally : cdata.allies())
    {
        if (ally.state() == Character::State::empty)
        {
            continue;
        }

        ss << ally.name << " " << the_race_db.get_text(ally.race, "name")
           << "の" << class_get_name(ally.class_) << " "
           << i18n::s.get_enum("core.ui.sex", ally.sex) << " " << calc_age(ally)
           << "歳"
           << "  " << ally.height << "cm"
           << " " << ally.weight << "kg" << std::endl;
        ss << "レベル " << ally.level;
        if (ally.is_married())
        {
            ss << " 婚約済み";
        }
        ss << std::endl << std::endl;
    }

    ss << "------------------------------ 称号" << std::endl;
    ss << std::endl;

    for (int i = 0; i < 9; ++i)
    {
        if (game()->ranks.at(i) < 10000)
        {
            ss << ranktitle(i) << " Rank." << game()->ranks.at(i) / 100
               << std::endl;
            ss << "給料: 約 " << calcincome(i) << " gold  ノルマ: ";
            if (i == 3 || i == 4 || i == 5 || i == 8)
            {
                ss << "なし";
            }
            else
            {
                ss << game()->rank_deadlines.at(i) << "日以内";
            }
            ss << std::endl;
        }
    }

    std::ofstream out{
        (filesystem::dirs::save() / fs::u8path(playerid + ".txt")).native()};
    out << ss.str() << std::endl;

    std::cout << ss.str();
}

} // namespace elona
