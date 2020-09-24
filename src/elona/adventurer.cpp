#include "adventurer.hpp"

#include <string>

#include "ability.hpp"
#include "area.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "data/types/type_ability.hpp"
#include "data/types/type_item.hpp"
#include "equipment.hpp"
#include "game.hpp"
#include "i18n.hpp"
#include "inventory.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "map.hpp"
#include "message.hpp"
#include "random.hpp"
#include "text.hpp"
#include "variables.hpp"



namespace elona
{

namespace
{

void add_news_entry(std::string news_content, bool show_message)
{
    if (show_message)
    {
        txt(u8"[News] "s + news_content,
            Message::color{ColorIndex::light_brown});
    }
    talk_conv(news_content, 38 - en * 5);
    newsbuff += news_content + u8"\n"s;
}



void add_news_topic(const std::string& mark, const std::string& news_content)
{
    const auto dt = game_date_time();
    const auto date = std::to_string(dt.year()) + "/" +
        std::to_string(dt.month()) + "/" + std::to_string(dt.day()) + " h" +
        std::to_string(dt.hour());
    add_news_entry(mark + " " + date + " " + news_content, false);
}

} // namespace



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



int adventurer_favorite_skill(const Character& adv)
{
    const auto seed = adv.index;
    randomize(seed);
    std::vector<int> skills;
    while (skills.size() < 2)
    {
        const auto skill_id = rnd(300) + 100;
        if (the_ability_db[skill_id])
        {
            skills.push_back(skill_id);
        }
    }
    randomize();
    return choice(skills);
}



int adventurer_favorite_stat(const Character& adv)
{
    const auto seed = adv.index;
    randomize(seed);
    const auto ret = rnd(8) + 10;
    randomize();
    return ret;
}



void adventurer_add_news(
    NewsType news_type,
    const Character& adventurer,
    const std::string& extra_info)
{
    switch (news_type)
    {
    case NewsType::discovery:
        add_news_topic(u8"@01"s, i18n::s.get("core.news.discovery.title"));
        add_news_entry(
            i18n::s.get(
                "core.news.discovery.text",
                adventurer.alias,
                adventurer.name,
                extra_info /* discovered artifact */,
                mapname(adventurer.current_map)),
            true);
        break;
    case NewsType::growth:
        add_news_topic(u8"@02"s, i18n::s.get("core.news.growth.title"));
        add_news_entry(
            i18n::s.get(
                "core.news.growth.text",
                adventurer.alias,
                adventurer.name,
                adventurer.level),
            true);
        break;
    case NewsType::recovery:
        add_news_topic(u8"@02"s, i18n::s.get("core.news.recovery.title"));
        add_news_entry(
            i18n::s.get(
                "core.news.recovery.text", adventurer.alias, adventurer.name),
            true);
        break;
    case NewsType::accomplishment:
        add_news_topic(u8"@03"s, i18n::s.get("core.news.accomplishment.title"));
        add_news_entry(
            i18n::s.get(
                "core.news.accomplishment.text",
                adventurer.alias,
                adventurer.name,
                extra_info /* gained fame */),
            true);
        break;
    case NewsType::retirement:
        add_news_topic(u8"@04"s, i18n::s.get("core.news.retirement.title"));
        add_news_entry(
            i18n::s.get(
                "core.news.retirement.text", adventurer.alias, adventurer.name),
            true);
        break;
    default: assert(0); break;
    }

    newsbuff += u8"\n"s;
}



void adventurer_update()
{
    for (auto&& adv : cdata.adventurers())
    {
        if (adv.hire_limit_time != time::Instant::epoch())
        {
            if (adv.hire_limit_time <= game_now())
            {
                adv.hire_limit_time = time::Instant::epoch();
                adv.is_contracting() = false;
                adv.relationship = 0;
                txt(i18n::s.get("core.chara.contract_expired", adv));
            }
        }
        if (adv.current_map != game()->current_map)
        {
            if (adv.state() == Character::State::adventurer_empty)
            {
                create_adventurer(adv);
                continue;
            }
            if (adv.state() == Character::State::adventurer_dead)
            {
                if (game_now() >= adv.revival_time)
                {
                    if (rnd(3) == 0)
                    {
                        adventurer_add_news(NewsType::retirement, adv);
                        adv.set_state(Character::State::empty);
                        create_adventurer(adv);
                    }
                    else
                    {
                        adventurer_add_news(NewsType::recovery, adv);
                        adv.set_state(
                            Character::State::adventurer_in_other_map);
                    }
                    continue;
                }
            }
        }
        if ((adv.current_map != game()->current_map ||
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
        if (adv.current_map == game()->current_map)
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
            adventurer_add_news(
                NewsType::accomplishment, adv, std::to_string(fame));
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
        const auto inv = adv.inventory();
        const auto item = inv->at(inv_get_random_slot(inv));
        if (!item)
        {
            f = 1;
            break;
        }
        if (item->is_equipped())
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
    if (const auto item = itemcreate_chara_inv(adv, 0, 0))
    {
        item->identify_state = IdentifyState::completely;
        if (item->quality >= Quality::miracle)
        {
            if (is_equipment(the_item_db[item->id]->category))
            {
                adventurer_add_news(
                    NewsType::discovery, adv, itemname(item.unwrap()));
            }
        }
        wear_most_valuable_equipment(adv, item.unwrap());
    }
}

} // namespace elona
