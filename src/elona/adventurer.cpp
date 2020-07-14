#include "adventurer.hpp"

#include <string>

#include "ability.hpp"
#include "area.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "data/types/type_item.hpp"
#include "equipment.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "map.hpp"
#include "message.hpp"
#include "random.hpp"
#include "text.hpp"
#include "variables.hpp"



namespace elona
{

int i_at_m145 = 0;



void create_all_adventurers()
{
    for (auto&& adv : cdata.adventurers())
    {
        create_adventurer(adv);
    }
}



void create_adventurer(Character& adv)
{
    flt(0, Quality::miracle);
    initlv = rnd_capped(60 + cdata.player().level) + 1;
    p(0) = 75;
    p(1) = 41;
    p(2) = 160;
    novoidlv = 1;
    chara_create(adv.index, p(rnd(3)), -1, -1);
    adv.relationship = 0;
    adv.original_relationship = 0;
    adv._156 = 100;
    adv.set_state(Character::State::adventurer_in_other_map);
    adv.image = rnd(33) * 2 + 1 + adv.sex;
    adv.name = random_name();
    adv.alias = random_title(RandomTitleType::character);
    adv.role = Role::adventurer;
    p = rnd(450);
    if (area_data[p].id == mdata_t::MapId::none ||
        area_data[p].id == mdata_t::MapId::your_home ||
        area_data[p].type == mdata_t::MapType::temporary)
    {
        p = 4;
    }
    if (rnd(4) == 0)
    {
        p = 5;
    }
    if (rnd(4) == 0)
    {
        p = 11;
    }
    if (rnd(6) == 0)
    {
        p = 12;
    }
    adv.current_map = p;
    adv.current_dungeon_level = 1;
    adv.fame = adv.level * adv.level * 30 + rnd_capped(adv.level * 200 + 100) +
        rnd(500);
}



int advfavoriteskill(int seed)
{
    randomize(seed);
    rtval = 0;
    i_at_m145 = 0;
    while (1)
    {
        rtval(i_at_m145) = rnd(300) + 100;
        if (!the_ability_db[rtval(i_at_m145)])
        {
            continue;
        }
        ++i_at_m145;
        if (i_at_m145 >= 2)
        {
            break;
        }
    }
    randomize();
    return i_at_m145;
}



int advfavoritestat(int seed)
{
    randomize(seed);
    i_at_m145 = rnd(8) + 10;
    randomize();
    return i_at_m145;
}



void addnews2(const std::string& news_content, int show_message)
{
    std::string n_at_m36 = news_content;
    if (show_message)
    {
        txt(u8"[News] "s + n_at_m36, Message::color{ColorIndex::light_brown});
    }
    talk_conv(n_at_m36, 38 - en * 5);
    newsbuff += n_at_m36 + u8"\n"s;
}



void addnewstopic(const std::string& mark, const std::string& news_content)
{
    addnews2(
        mark + u8" "s + game_data.date.year + u8"/"s + game_data.date.month +
        u8"/"s + game_data.date.day + u8" h"s + game_data.date.hour + ""s +
        u8" "s + news_content);
}



void addnews(int news_type, int adventurer, int fame, const std::string& valn)
{
    switch (news_type)
    {
    case 0: addnews2(valn); break;
    case 1:
        addnewstopic(u8"@01"s, i18n::s.get("core.news.discovery.title"));
        addnews2(
            i18n::s.get(
                "core.news.discovery.text",
                cdata[adventurer].alias,
                cdata[adventurer].name,
                valn,
                mapname(cdata[adventurer].current_map)),
            1);
        break;
    case 2:
        addnewstopic(u8"@02"s, i18n::s.get("core.news.growth.title"));
        addnews2(
            i18n::s.get(
                "core.news.growth.text",
                cdata[adventurer].alias,
                cdata[adventurer].name,
                cdata[adventurer].level),
            1);
        break;
    case 3:
        addnewstopic(u8"@02"s, i18n::s.get("core.news.recovery.title"));
        addnews2(
            i18n::s.get(
                "core.news.recovery.text",
                cdata[adventurer].alias,
                cdata[adventurer].name),
            1);
        break;
    case 4:
        addnewstopic(u8"@03"s, i18n::s.get("core.news.accomplishment.title"));
        addnews2(
            i18n::s.get(
                "core.news.accomplishment.text",
                cdata[adventurer].alias,
                cdata[adventurer].name,
                fame),
            1);
        break;
    case 5:
        addnewstopic(u8"@04"s, i18n::s.get("core.news.retirement.title"));
        addnews2(
            i18n::s.get(
                "core.news.retirement.text",
                cdata[adventurer].alias,
                cdata[adventurer].name),
            1);
        break;
    }
    newsbuff += u8"\n"s;
}



void adventurer_update()
{
    for (auto&& adv : cdata.adventurers())
    {
        if (adv.period_of_contract != 0)
        {
            if (adv.period_of_contract < game_data.date.hours())
            {
                adv.period_of_contract = 0;
                adv.is_contracting() = false;
                adv.relationship = 0;
                txt(i18n::s.get("core.chara.contract_expired", adv));
            }
        }
        if (adv.current_map != game_data.current_map)
        {
            if (adv.state() == Character::State::adventurer_empty)
            {
                create_adventurer(adv);
                continue;
            }
            if (adv.state() == Character::State::adventurer_dead)
            {
                if (game_data.date.hours() >= adv.time_to_revive)
                {
                    if (rnd(3) == 0)
                    {
                        addnews(5, adv.index);
                        adv.set_state(Character::State::empty);
                        create_adventurer(adv);
                    }
                    else
                    {
                        addnews(3, adv.index);
                        adv.set_state(
                            Character::State::adventurer_in_other_map);
                    }
                    continue;
                }
            }
        }
        if ((adv.current_map != game_data.current_map ||
             map_data.type == mdata_t::MapType::world_map) &&
            rnd(60) == 0)
        {
            for (int cnt = 0; cnt < 10; ++cnt)
            {
                if (rnd(4) == 0)
                {
                    p = rnd(50) + 450;
                }
                else
                {
                    p = rnd(300);
                }
                if (area_data[p].id == mdata_t::MapId::none || p == 7 ||
                    area_data[p].type == mdata_t::MapType::temporary || p == 9)
                {
                    p = 4;
                }
                if (cnt < 5)
                {
                    if (area_data[p].type != mdata_t::MapType::town)
                    {
                        continue;
                    }
                }
                break;
            }
            adv.current_map = p;
            adv.current_dungeon_level = 1;
        }
        if (adv.current_map == game_data.current_map)
        {
            continue;
        }
        if (rnd(200) == 0)
        {
            if (area_data[adv.current_map].type != mdata_t::MapType::town)
            {
                adventurer_discover_equipment(adv);
            }
        }
        if (rnd(10) == 0)
        {
            adv.experience += adv.level * adv.level * 2;
        }
        if (rnd(20) == 0)
        {
            adv.fame += rnd_capped(adv.level * adv.level / 40 + 5) -
                rnd_capped(adv.level * adv.level / 50 + 5);
        }
        if (rnd(2000) == 0)
        {
            adv.experience +=
                clamp(adv.level, 1, 1000) * clamp(adv.level, 1, 1000) * 100;
            int fame = rnd_capped(adv.level * adv.level / 20 + 10) + 10;
            adv.fame += fame;
            addnews(4, adv.index, fame);
            adventurer_discover_equipment(adv);
        }
        if (adv.experience >= adv.required_experience)
        {
            r2 = 0;
            gain_level(adv);
        }
    }
    notesel(newsbuff);
    if (noteinfo() > 195)
    {
        for (int cnt = 0, cnt_end = (noteinfo() - 195); cnt < cnt_end; ++cnt)
        {
            notedel(0);
        }
    }
}



void adventurer_discover_equipment(Character& adv)
{
    f = 0;
    for (int _i = 0; _i < 10; ++_i)
    {
        const auto item = Inventory::at(inv_get_random_slot(adv.index));
        if (!item)
        {
            f = 1;
            break;
        }
        if (item->body_part != 0)
        {
            continue;
        }
        if (item->number() != 0)
        {
            if (adv.ai_item == item)
            {
                adv.ai_item = nullptr;
            }
            item->remove();
            f = 1;
            break;
        }
    }
    if (f == 0)
    {
        return;
    }
    flt(adv.level, Quality::miracle);
    if (rnd(3) == 0)
    {
        flttypemajor = choice(fsetwear);
    }
    else
    {
        flttypemajor = choice(fsetitem);
    }
    if (const auto item = itemcreate_chara_inv(adv.index, 0, 0))
    {
        item->identify_state = IdentifyState::completely;
        if (item->quality >= Quality::miracle)
        {
            if (is_equipment(the_item_db[itemid2int(item->id)]->category))
            {
                addnews(1, adv.index, 0, itemname(item.unwrap()));
            }
        }
        wear_most_valuable_equipment(adv, item.unwrap());
    }
}

} // namespace elona
