#include "enchantment.hpp"
#include "db_item.hpp"
#include "element.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "random.hpp"
#include "variables.hpp"

using namespace elona;



namespace
{

elona_vector2<int> encref;



bool check_enchantment_filters(int category, int type)
{
    constexpr auto max_enchantment_filters = 2;

    for (int i = 0; i < max_enchantment_filters; ++i)
    {
        const auto filter = encref(3 + i, type);
        if (filter == 0 || enchantment_filter(category, filter))
        {
            return true;
        }
    }

    return false;
}



} // namespace



namespace elona
{

elona_vector2<int> enclist;
elona_vector2<int> egoenc;
elona_vector2<int> egoref;
elona_vector1<int> egolist;
elona_vector1<int> p_at_m47;
int maxegominorn = 0;
int enc_at_m48 = 0;
int encp_at_m48 = 0;
int p_at_m48 = 0;

void initialize_enchantment_data()
{
    DIM3(encref, 8, 62);
    DIM3(enclist, 2, 62);
    DIM3(encammoref, 3, 6);
    SDIM2(ammoname, 6);
    encammoref(0, 0) = 30;
    encammoref(1, 0) = 70;
    encammoref(2, 0) = 1;
    encammoref(0, 1) = 5;
    encammoref(1, 1) = 15;
    encammoref(2, 1) = 10;
    encammoref(0, 3) = 20;
    encammoref(1, 3) = 35;
    encammoref(2, 3) = 2;
    encammoref(0, 2) = 15;
    encammoref(1, 2) = 30;
    encammoref(2, 2) = 2;
    encammoref(0, 4) = 2;
    encammoref(1, 4) = 5;
    encammoref(2, 4) = 25;
    encammoref(0, 5) = 2;
    encammoref(1, 5) = 5;
    encammoref(2, 5) = 15;

    for (int cnt = 0; cnt < 6; cnt++)
    {
        ammoname(cnt) = i18n::s.get_enum(
            "core.locale.enchantment.with_parameters.ammo.kinds", cnt);
    }

    encref(0, 21) = -1;
    encref(1, 21) = 50;
    encref(2, 21) = 75;
    encref(3, 21) = 0;
    encref(0, 45) = -1;
    encref(1, 45) = 50;
    encref(2, 45) = 100;
    encref(3, 45) = 0;
    encref(0, 46) = -1;
    encref(1, 46) = 50;
    encref(2, 46) = 100;
    encref(3, 46) = 0;
    encref(0, 47) = -1;
    encref(1, 47) = 50;
    encref(2, 47) = 50;
    encref(3, 47) = 0;
    encref(0, 56) = 0;
    encref(1, 56) = 200;
    encref(2, 56) = 30;
    encref(3, 56) = 0;
    encref(0, 59) = 0;
    encref(1, 59) = 200;
    encref(2, 59) = 30;
    encref(3, 59) = 0;
    encref(0, 3) = 0;
    encref(1, 3) = 120;
    encref(2, 3) = 4500;
    encref(3, 3) = 0;
    encref(0, 6) = 0;
    encref(1, 6) = 120;
    encref(2, 6) = 4500;
    encref(3, 6) = 0;
    encref(0, 7) = 1;
    encref(1, 7) = 120;
    encref(2, 7) = 300;
    encref(3, 7) = 10000;
    encref(4, 7) = 24000;
    encref(0, 9) = 1;
    encref(1, 9) = 120;
    encref(2, 9) = 50000;
    encref(3, 9) = 25000;
    encref(0, 23) = 1;
    encref(1, 23) = 120;
    encref(2, 23) = 400;
    encref(3, 23) = 0;
    encref(0, 1) = 1;
    encref(1, 1) = 120;
    encref(2, 1) = 3000;
    encref(3, 1) = 0;
    encref(0, 22) = 1;
    encref(1, 22) = 150;
    encref(2, 22) = 150;
    encref(3, 22) = 0;
    encref(0, 25) = 1;
    encref(1, 25) = 120;
    encref(2, 25) = 400;
    encref(3, 25) = 0;
    encref(0, 2) = 2;
    encref(1, 2) = 150;
    encref(2, 2) = 2500;
    encref(3, 2) = 0;
    encref(0, 24) = 2;
    encref(1, 24) = 120;
    encref(2, 24) = 300;
    encref(3, 24) = 0;
    encref(0, 26) = 1;
    encref(1, 26) = 120;
    encref(2, 26) = 600;
    encref(3, 26) = 0;
    encref(0, 27) = 1;
    encref(1, 27) = 120;
    encref(2, 27) = 600;
    encref(3, 27) = 0;
    encref(0, 28) = 2;
    encref(1, 28) = 120;
    encref(2, 28) = 500;
    encref(3, 28) = 0;
    encref(0, 29) = 3;
    encref(1, 29) = 200;
    encref(2, 29) = 25;
    encref(3, 29) = 18000;
    encref(0, 30) = 3;
    encref(1, 30) = 200;
    encref(2, 30) = 25;
    encref(3, 30) = 20000;
    encref(0, 31) = 2;
    encref(1, 31) = 200;
    encref(2, 31) = 40;
    encref(3, 31) = 32000;
    encref(0, 48) = 1;
    encref(1, 48) = 120;
    encref(2, 48) = 300;
    encref(3, 48) = 0;
    encref(0, 50) = 3;
    encref(1, 50) = 180;
    encref(2, 50) = 150;
    encref(3, 50) = 32000;
    encref(4, 50) = 34000;
    encref(0, 51) = 3;
    encref(1, 51) = 180;
    encref(2, 51) = 150;
    encref(3, 51) = 32000;
    encref(4, 51) = 34000;
    encref(0, 32) = 1;
    encref(1, 32) = 130;
    encref(2, 32) = 250;
    encref(3, 32) = 0;
    encref(0, 55) = 3;
    encref(1, 55) = 130;
    encref(2, 55) = 40;
    encref(3, 55) = 19000;
    encref(4, 55) = 34000;
    encref(0, 33) = 3;
    encref(1, 33) = 160;
    encref(2, 33) = 200;
    encref(3, 33) = 0;
    encref(0, 34) = 3;
    encref(1, 34) = 170;
    encref(2, 34) = 250;
    encref(3, 34) = 10000;
    encref(0, 57) = 2;
    encref(1, 57) = 170;
    encref(2, 57) = 200;
    encref(3, 57) = 10000;
    encref(4, 57) = 24000;
    encref(0, 58) = 2;
    encref(1, 58) = 170;
    encref(2, 58) = 200;
    encref(3, 58) = 10000;
    encref(4, 58) = 24000;
    encref(0, 52) = 1;
    encref(1, 52) = 140;
    encref(2, 52) = 750;
    encref(3, 52) = 14000;
    encref(0, 53) = 2;
    encref(1, 53) = 160;
    encref(2, 53) = 500;
    encref(3, 53) = 14000;
    encref(0, 54) = 3;
    encref(1, 54) = 180;
    encref(2, 54) = 250;
    encref(3, 54) = 14000;
    encref(4, 54) = 16000;
    encref(0, 35) = 2;
    encref(1, 35) = 170;
    encref(2, 35) = 100;
    encref(3, 35) = 12000;
    encref(4, 35) = 32000;
    encref(0, 44) = 99;
    encref(1, 44) = 300;
    encref(2, 44) = 10000;
    encref(3, 44) = 10000;
    encref(4, 44) = 34000;
    encref(0, 42) = 99;
    encref(1, 42) = 300;
    encref(2, 42) = 2000;
    encref(3, 42) = 0;
    encref(0, 36) = 99;
    encref(1, 36) = 450;
    encref(2, 36) = 1000;
    encref(3, 36) = 10000;
    encref(4, 36) = 24000;
    encref(0, 38) = 99;
    encref(1, 38) = 450;
    encref(2, 38) = 1000;
    encref(3, 38) = 10000;
    encref(4, 38) = 24000;
    encref(0, 37) = 99;
    encref(1, 37) = 100;
    encref(2, 37) = 1000;
    encref(3, 37) = 10000;
    encref(4, 37) = 24000;
    encref(0, 39) = 99;
    encref(1, 39) = 500;
    encref(2, 39) = 500;
    encref(3, 39) = 10000;
    encref(4, 39) = 22000;
    encref(0, 40) = 99;
    encref(1, 40) = 550;
    encref(2, 40) = 500;
    encref(3, 40) = 10000;
    encref(4, 40) = 24000;
    encref(0, 41) = 99;
    encref(1, 41) = 300;
    encref(2, 41) = 1500;
    encref(3, 41) = 0;
    encref(0, 43) = 99;
    encref(1, 43) = 150;
    encref(2, 43) = 2000;
    encref(3, 43) = 0;
    encref(0, 8) = 99;
    encref(1, 8) = 300;
    encref(2, 8) = 15000;
    encref(3, 8) = 0;
    encref(0, 49) = 100;
    encref(1, 49) = 120;
    encref(2, 49) = 300;
    encref(3, 49) = 60000;
    encref(0, 60) = 100;
    encref(1, 60) = 120;
    encref(2, 60) = 300;
    encref(3, 60) = 60000;
    encref(0, 61) = 2;
    encref(1, 61) = 170;
    encref(2, 61) = 150;
    encref(3, 61) = 10000;
    encref(4, 61) = 24000;
    DIM3(encprocref, 6, 26);
    encprocref(0, 0) = 450;
    encprocref(1, 0) = 2000;
    encprocref(2, 0) = 1000;
    encprocref(3, 0) = 10000;
    encprocref(4, 0) = 24000;
    encprocref(5, 0) = 10;
    encprocref(0, 1) = 620;
    encprocref(1, 1) = 2000;
    encprocref(2, 1) = 6000;
    encprocref(3, 1) = 24000;
    encprocref(4, 1) = 0;
    encprocref(5, 1) = 50;
    encprocref(0, 2) = 452;
    encprocref(1, 2) = 2000;
    encprocref(2, 2) = 1000;
    encprocref(3, 2) = 10000;
    encprocref(4, 2) = 24000;
    encprocref(5, 2) = 10;
    encprocref(0, 3) = 434;
    encprocref(1, 3) = 2000;
    encprocref(2, 3) = 800;
    encprocref(3, 3) = 10000;
    encprocref(4, 3) = 24000;
    encprocref(5, 3) = 12;
    encprocref(0, 4) = 433;
    encprocref(1, 4) = 2000;
    encprocref(2, 4) = 600;
    encprocref(3, 4) = 10000;
    encprocref(4, 4) = 24000;
    encprocref(5, 4) = 12;
    encprocref(0, 5) = 625;
    encprocref(1, 5) = 3000;
    encprocref(2, 5) = 400;
    encprocref(3, 5) = 10000;
    encprocref(4, 5) = 24000;
    encprocref(5, 5) = 2;
    encprocref(0, 6) = 627;
    encprocref(1, 6) = 3000;
    encprocref(2, 6) = 1000;
    encprocref(3, 6) = 10000;
    encprocref(4, 6) = 24000;
    encprocref(5, 6) = 50;
    encprocref(0, 7) = 619;
    encprocref(1, 7) = 2000;
    encprocref(2, 7) = 4000;
    encprocref(3, 7) = 24000;
    encprocref(4, 7) = 0;
    encprocref(5, 7) = 50;
    encprocref(0, 8) = 604;
    encprocref(1, 8) = 2000;
    encprocref(2, 8) = 1000;
    encprocref(3, 8) = 10000;
    encprocref(4, 8) = 24000;
    encprocref(5, 8) = 15;
    encprocref(0, 9) = 609;
    encprocref(1, 9) = 2000;
    encprocref(2, 9) = 1000;
    encprocref(3, 9) = 10000;
    encprocref(4, 9) = 24000;
    encprocref(5, 9) = 15;
    encprocref(0, 10) = 608;
    encprocref(1, 10) = 2000;
    encprocref(2, 10) = 1000;
    encprocref(3, 10) = 10000;
    encprocref(4, 10) = 24000;
    encprocref(5, 10) = 15;
    encprocref(0, 11) = 453;
    encprocref(1, 11) = 3000;
    encprocref(2, 11) = 1000;
    encprocref(3, 11) = 10000;
    encprocref(4, 11) = 24000;
    encprocref(5, 11) = 4;
    encprocref(0, 12) = 451;
    encprocref(1, 12) = 3000;
    encprocref(2, 12) = 1000;
    encprocref(3, 12) = 10000;
    encprocref(4, 12) = 24000;
    encprocref(5, 12) = 4;
    encprocref(0, 13) = 448;
    encprocref(1, 13) = 3000;
    encprocref(2, 13) = 1000;
    encprocref(3, 13) = 10000;
    encprocref(4, 13) = 24000;
    encprocref(5, 13) = 4;
    encprocref(0, 14) = 446;
    encprocref(1, 14) = 3000;
    encprocref(2, 14) = 400;
    encprocref(3, 14) = 10000;
    encprocref(4, 14) = 24000;
    encprocref(5, 14) = 1;
    encprocref(0, 15) = 444;
    encprocref(1, 15) = 3000;
    encprocref(2, 15) = 1000;
    encprocref(3, 15) = 10000;
    encprocref(4, 15) = 24000;
    encprocref(5, 15) = 3;
    encprocref(0, 16) = 442;
    encprocref(1, 16) = 3000;
    encprocref(2, 16) = 1000;
    encprocref(3, 16) = 10000;
    encprocref(4, 16) = 24000;
    encprocref(5, 16) = 2;
    encprocref(0, 17) = 443;
    encprocref(1, 17) = 2000;
    encprocref(2, 17) = 800;
    encprocref(3, 17) = 10000;
    encprocref(4, 17) = 24000;
    encprocref(5, 17) = 10;
    encprocref(0, 18) = 436;
    encprocref(1, 18) = 2000;
    encprocref(2, 18) = 1000;
    encprocref(3, 18) = 10000;
    encprocref(4, 18) = 24000;
    encprocref(5, 18) = 10;
    encprocref(0, 19) = 421;
    encprocref(1, 19) = 2000;
    encprocref(2, 19) = 1000;
    encprocref(3, 19) = 10000;
    encprocref(4, 19) = 24000;
    encprocref(5, 19) = 15;
    encprocref(0, 20) = 422;
    encprocref(1, 20) = 2000;
    encprocref(2, 20) = 1000;
    encprocref(3, 20) = 10000;
    encprocref(4, 20) = 24000;
    encprocref(5, 20) = 15;
    encprocref(0, 21) = 423;
    encprocref(1, 21) = 2000;
    encprocref(2, 21) = 1000;
    encprocref(3, 21) = 10000;
    encprocref(4, 21) = 24000;
    encprocref(5, 21) = 15;
    encprocref(0, 22) = 419;
    encprocref(1, 22) = 2000;
    encprocref(2, 22) = 1000;
    encprocref(3, 22) = 10000;
    encprocref(4, 22) = 24000;
    encprocref(5, 22) = 15;
    encprocref(0, 23) = 404;
    encprocref(1, 23) = 3000;
    encprocref(2, 23) = 800;
    encprocref(3, 23) = 10000;
    encprocref(4, 23) = 24000;
    encprocref(5, 23) = 2;
    encprocref(0, 24) = 655;
    encprocref(1, 24) = 2000;
    encprocref(2, 24) = 200;
    encprocref(3, 24) = 10000;
    encprocref(4, 24) = 24000;
    encprocref(5, 24) = 90;
    encprocref(0, 25) = 658;
    encprocref(1, 25) = 2000;
    encprocref(2, 25) = 1000;
    encprocref(3, 25) = 10000;
    encprocref(4, 25) = 0;
    encprocref(5, 25) = 100;
    return;
}

std::string enchantment_print_level(int prm_448)
{
    std::string s = "";
    for (int cnt = 0, cnt_end = (std::abs(prm_448) + 1); cnt < cnt_end; ++cnt)
    {
        if (cnt > 4)
        {
            s += u8"+"s;
            break;
        }
        s += i18n::s.get("core.locale.enchantment.level");
    }
    return s;
}

std::string enchantment_level_string(int prm_448)
{
    return " [" + enchantment_print_level(prm_448) + "]";
}

void get_enchantment_description(int val0, int power, int category, bool trait)
{
    rtval(0) = desc_entry_t::enchantment;
    rtval(1) = 0;

    s = "";

    if (val0 / 10000 != 0)
    {
        if (trait)
            return;

        int sid = val0 % 10000;
        switch (val0 / 10000)
        {
        case 1:
            rtval = desc_entry_t::raises_stat;
            if (power / 50 + 1 < 0)
            {
                rtval = desc_entry_t::negative_effect;
                const auto skill_name =
                    i18n::_(u8"ability", std::to_string(sid), u8"name");
                if (category == 57000)
                {
                    s = i18n::s.get(
                        "core.locale.enchantment.with_parameters.attribute.in_"
                        "food.decreases",
                        skill_name);
                    s += enchantment_level_string(power / 50);
                }
                else
                {
                    s = i18n::s.get(
                        "core.locale.enchantment.with_parameters.attribute."
                        "other.decreases",
                        skill_name,
                        std::abs(power / 50 + 1));
                }
            }
            else
            {
                const auto skill_name =
                    i18n::_(u8"ability", std::to_string(sid), u8"name");
                if (category == 57000)
                {
                    s = i18n::s.get(
                        "core.locale.enchantment.with_parameters.attribute.in_"
                        "food.increases",
                        skill_name);
                    s += enchantment_level_string(power / 50);
                }
                else
                {
                    s = i18n::s.get(
                        "core.locale.enchantment.with_parameters.attribute."
                        "other.increases",
                        skill_name,
                        std::abs(power / 50 + 1));
                }
            }
            break;
        case 2:
            rtval = desc_entry_t::raises_resist;
            if (power / 2 < 0)
            {
                rtval = desc_entry_t::negative_effect;
                s = i18n::s.get(
                    "core.locale.enchantment.with_parameters.resistance."
                    "decreases",
                    i18n::_(u8"ability", std::to_string(sid), u8"name"));
            }
            else
            {
                s = i18n::_(
                    u8"ability",
                    std::to_string(sid),
                    u8"enchantment_description");
                if (s == ""s)
                {
                    s = i18n::s.get(
                        "core.locale.enchantment.with_parameters.resistance."
                        "increases",
                        i18n::_(u8"ability", std::to_string(sid), u8"name"));
                }
            }
            s += enchantment_level_string(power / 100);
            break;
        case 3:
            rtval = desc_entry_t::raises_skill;
            if (power / 50 + 1 < 0)
            {
                rtval = desc_entry_t::negative_effect;
                s = i18n::s.get(
                    "core.locale.enchantment.with_parameters.skill.decreases",
                    i18n::_(u8"ability", std::to_string(sid), u8"name"));
            }
            else
            {
                s = i18n::_(
                    u8"ability",
                    std::to_string(sid),
                    u8"enchantment_description");
                if (s == ""s)
                {
                    s = i18n::s.get(
                        "core.locale.enchantment.with_parameters.skill."
                        "increases",
                        i18n::_(u8"ability", std::to_string(sid), u8"name"));
                }
            }
            s += enchantment_level_string((power / 50 + 1) / 5);
            break;
        case 6:
            rtval = desc_entry_t::maintains_skill;
            if (category == 57000)
            {
                s = i18n::s.get(
                    "core.locale.enchantment.with_parameters.skill_maintenance."
                    "in_food",
                    i18n::_(u8"ability", std::to_string(sid), u8"name"));
                s += enchantment_level_string(power / 50);
            }
            else
            {
                s = i18n::s.get(
                    "core.locale.enchantment.with_parameters.skill_maintenance."
                    "other",
                    i18n::_(u8"ability", std::to_string(sid), u8"name"));
            }
            break;
        case 7:
            rtval = desc_entry_t::enchantment;
            s = i18n::_(
                u8"ability", std::to_string(sid), u8"enchantment_description");
            if (s == ""s)
            {
                s = i18n::s.get(
                    "core.locale.enchantment.with_parameters.extra_damage",
                    i18n::_(u8"ability", std::to_string(sid), u8"name"));
            }
            s += enchantment_level_string(power / 100);
            break;
        case 8:
            rtval = desc_entry_t::enchantment;
            sid = encprocref(0, sid);
            s = i18n::s.get(
                "core.locale.enchantment.with_parameters.invokes",
                i18n::_(u8"ability", std::to_string(sid), u8"name"));
            s += enchantment_level_string(power / 50);
            break;
        case 9:
            rtval = desc_entry_t::enchantment;
            s = i18n::s.get(
                "core.locale.enchantment.with_parameters.ammo.text",
                ammoname(sid));
            s += " ["
                + i18n::s.get(
                      "core.locale.enchantment.with_parameters.ammo.max",
                      power / 1000)
                + "]";
            break;
        }
        return;
    }

    s = i18n::s.get_enum("core.locale.enchantment.no_parameters", val0);

    switch (val0)
    {
    case 0: s = u8"?????"s; break;
    case 21:
        rtval = desc_entry_t::negative_effect;
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += enchantment_level_string(power / 50);
        }
        break;
    case 45:
        rtval = desc_entry_t::negative_effect;
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += enchantment_level_string(power / 50);
        }
        break;
    case 46:
        rtval = desc_entry_t::negative_effect;
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += enchantment_level_string(power / 50);
        }
        break;
    case 47:
        rtval = desc_entry_t::negative_effect;
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += enchantment_level_string(power / 50);
        }
        break;
    case 22: rtval = desc_entry_t::enchantment; break;
    case 23: rtval = desc_entry_t::enchantment; break;
    case 24: rtval = desc_entry_t::enchantment; break;
    case 25: rtval = desc_entry_t::enchantment; break;
    case 26: rtval = desc_entry_t::enchantment; break;
    case 27: rtval = desc_entry_t::enchantment; break;
    case 28: rtval = desc_entry_t::enchantment; break;
    case 41: rtval = desc_entry_t::enchantment; break;
    case 42: rtval = desc_entry_t::enchantment; break;
    case 29:
        rtval = desc_entry_t::enchantment;
        if (trait)
        {
            rtval(1) = power / 100;
        }
        else
        {
            s += enchantment_level_string(power / 100);
        }
        break;
    case 30: rtval = desc_entry_t::enchantment; break;
    case 31: rtval = desc_entry_t::enchantment; break;
    case 48: rtval = desc_entry_t::enchantment; break;
    case 32: rtval = desc_entry_t::enchantment; break;
    case 33: rtval = desc_entry_t::enchantment; break;
    case 34:
        rtval = desc_entry_t::enchantment;
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += enchantment_level_string(power / 50);
        }
        break;
    case 35: rtval = desc_entry_t::enchantment; break;
    case 36:
        rtval = desc_entry_t::enchantment;
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += enchantment_level_string(power / 50);
        }
        break;
    case 37: rtval = desc_entry_t::enchantment; break;
    case 38:
        rtval = desc_entry_t::enchantment;
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += enchantment_level_string(power / 50);
        }
        break;
    case 39:
        rtval = desc_entry_t::enchantment;
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += enchantment_level_string(power / 50);
        }
        break;
    case 44:
        rtval = desc_entry_t::enchantment;
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += enchantment_level_string(power / 50);
        }
        break;
    case 50:
        rtval = desc_entry_t::enchantment;
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += enchantment_level_string(power / 50);
        }
        break;
    case 51:
        rtval = desc_entry_t::enchantment;
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += enchantment_level_string(power / 50);
        }
        break;
    case 40:
        rtval = desc_entry_t::enchantment;
        if (trait)
        {
            rtval(1) = power / 100;
        }
        else
        {
            s += enchantment_level_string(power / 100);
        }
        break;
    case 43:
        rtval = desc_entry_t::enchantment;
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += enchantment_level_string(power / 50);
        }
        break;
    case 49: rtval = desc_entry_t::enchantment; break;
    case 52:
        rtval = desc_entry_t::enchantment;
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += enchantment_level_string(power / 50);
        }
        break;
    case 53:
        rtval = desc_entry_t::enchantment;
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += enchantment_level_string(power / 50);
        }
        break;
    case 54:
        rtval = desc_entry_t::enchantment;
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += enchantment_level_string(power / 50);
        }
        break;
    case 55: rtval = desc_entry_t::enchantment; break;
    case 56: rtval = desc_entry_t::enchantment; break;
    case 57:
        rtval = desc_entry_t::enchantment;
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += enchantment_level_string(power / 50);
        }
        break;
    case 58:
        rtval = desc_entry_t::enchantment;
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += enchantment_level_string(power / 50);
        }
        break;
    case 59: rtval = desc_entry_t::enchantment; break;
    case 60: rtval = desc_entry_t::enchantment; break;
    case 61:
        rtval = desc_entry_t::enchantment;
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += enchantment_level_string(power / 50);
        }
        break;
    }
}



int enchantment_filter(int prm_449, int prm_450)
{
    if (prm_450 == 2)
    {
        if ((prm_449 >= 12000 && prm_449 < 24000) == 0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    if (prm_450 == 1)
    {
        if ((prm_449 >= 30000 && prm_449 < 50000) == 0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    if (prm_450 == 3)
    {
        if ((prm_449 >= 12000 && prm_449 < 24000) == 1 || prm_449 == 10000)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    if (prm_449 == prm_450)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}



int enchantment_generate(int prm_451)
{
    int sum_at_m47 = 0;
    int max_at_m47 = 0;
    int i_at_m47 = 0;
    sum_at_m47 = 0;
    max_at_m47 = 0;
    for (int cnt = 0; cnt < 62; ++cnt)
    {
        if (encref(0, cnt) > prm_451)
        {
            continue;
        }
        if (prm_451 >= 0)
        {
            if (encref(0, cnt) < 0)
            {
                continue;
            }
        }
        if (encref(3, cnt) != 0)
        {
            if (enchantment_filter(reftype, encref(3, cnt)) == 0)
            {
                if (encref(4, cnt) == 0)
                {
                    continue;
                }
                else if (enchantment_filter(reftype, encref(4, cnt)) == 0)
                {
                    continue;
                }
            }
        }
        sum_at_m47 += encref(2, cnt);
        enclist(0, max_at_m47) = cnt;
        enclist(1, max_at_m47) = sum_at_m47;
        ++max_at_m47;
    }
    if (max_at_m47 == 0)
    {
        return 0;
    }
    i_at_m47 = 0;
    p_at_m47 = rnd(sum_at_m47);
    for (int cnt = 0, cnt_end = (max_at_m47); cnt < cnt_end; ++cnt)
    {
        if (p_at_m47 < enclist(1, cnt))
        {
            i_at_m47 = enclist(0, cnt);
            break;
        }
    }
    return i_at_m47;
}



int enchantment_gen_level(int prm_452)
{
    int enclv_at_m47 = 0;
    enclv_at_m47 = clamp(prm_452, 0, 4);
    enclv_at_m47 = rnd(enclv_at_m47 + 1);
    return enclv_at_m47;
}



int enchantment_gen_p(int prm_453)
{
    int encp_at_m47 = 0;
    encp_at_m47 = rnd(rnd(500 + (trait(163) != 0) * 50) + 1) + 1;
    if (prm_453 != 0)
    {
        encp_at_m47 = encp_at_m47 * prm_453 / 100;
    }
    return encp_at_m47;
}



void enchantment_sort(int prm_454)
{
    int f_at_m47 = 0;
    int cnt2_at_m47 = 0;
    while (1)
    {
        f_at_m47 = 0;
        for (int cnt = 0; cnt < 14; ++cnt)
        {
            cnt2_at_m47 = cnt + 1;
            if (inv[prm_454].enchantments[cnt].id
                < inv[prm_454].enchantments[cnt2_at_m47].id)
            {
                p_at_m47(0) = inv[prm_454].enchantments[cnt].id;
                p_at_m47(1) = inv[prm_454].enchantments[cnt].power;
                inv[prm_454].enchantments[cnt].id =
                    inv[prm_454].enchantments[cnt2_at_m47].id;
                inv[prm_454].enchantments[cnt2_at_m47].id = p_at_m47;
                inv[prm_454].enchantments[cnt].power =
                    inv[prm_454].enchantments[cnt2_at_m47].power;
                inv[prm_454].enchantments[cnt2_at_m47].power = p_at_m47(1);
                f_at_m47 = 1;
            }
        }
        if (f_at_m47 == 0)
        {
            break;
        }
    }
    return;
}



void enchantment_remove(int prm_455, int prm_456, int prm_457)
{
    if (prm_456 == 0)
    {
        return;
    }
    if (prm_456 >= 10000)
    {
        enc_at_m48 = prm_456 / 10000;
    }
    else
    {
        enc_at_m48 = prm_456;
    }
    enc_at_m48 = prm_456;
    encp_at_m48 = prm_457;
    for (int cnt = 0; cnt < 15; ++cnt)
    {
        if (inv[prm_455].enchantments[cnt].id == enc_at_m48)
        {
            inv[prm_455].enchantments[cnt].power -= encp_at_m48;
            if (inv[prm_455].enchantments[cnt].power == 0)
            {
                inv[prm_455].enchantments[cnt].id = 0;
            }
            break;
        }
    }
    if (prm_456 < 10000)
    {
        p_at_m48 = prm_456;
    }
    else
    {
        p_at_m48 = prm_456 / 10000;
    }
    inv[prm_455].value = inv[prm_455].value * 100 / encref(1, p_at_m48);
    enchantment_sort(prm_455);
    return;
}



bool enchantment_add(
    int ci,
    int type,
    int power,
    int flip_percentage,
    bool not_halve,
    bool only_check,
    bool force)
{
    const auto category = the_item_db[inv[ci].id]->category;

    if (type == 0)
    {
        return false;
    }

    if (!force)
    {
        if (!check_enchantment_filters(
                category, type >= 10000 ? type / 10000 : type))
        {
            return false;
        }
        else if (category == 25000 && !not_halve)
        {
            return false;
        }
    }

    int enc = type;
    int encp = power;

    int sum_at_m48 = 0;
    int max_at_m48 = 0;
    int i_at_m48 = 0;

    switch (enc)
    {
    case 1:
        enc = rnd(10) + 10;
        enc += 10000;
        if (rnd(100) < flip_percentage)
        {
            encp = power * -2;
        }
        break;
    case 2:
        enc = 20000 + randomele();
        if (rnd(100) < flip_percentage)
        {
            encp = power * -2;
        }
        break;
    case 3:
        enc = rnd(40) + 150;
        enc += 30000;
        if (rnd(100) < flip_percentage)
        {
            encp = power * -2;
        }
        break;
    case 6:
        enc = rnd(10) + 10;
        enc += 60000;
        break;
    case 7:
        enc = randomele();
        enc += 70000;
        break;
    case 8:
        sum_at_m48 = 0;
        max_at_m48 = 0;
        for (int cnt = 0; cnt < 26; ++cnt)
        {
            if (encprocref(3, cnt) != 0)
            {
                if (enchantment_filter(category, encprocref(3, cnt)) == 0)
                {
                    if (encprocref(4, cnt) == 0)
                    {
                        continue;
                    }
                    else if (
                        enchantment_filter(category, encprocref(4, cnt)) == 0)
                    {
                        continue;
                    }
                }
            }
            sum_at_m48 += encprocref(2, cnt);
            enclist(0, max_at_m48) = cnt;
            enclist(1, max_at_m48) = sum_at_m48;
            ++max_at_m48;
        }
        if (max_at_m48 == 0)
        {
            return false;
        }
        i_at_m48 = 0;
        p_at_m48 = rnd(sum_at_m48);
        for (int cnt = 0, cnt_end = (max_at_m48); cnt < cnt_end; ++cnt)
        {
            if (p_at_m48 < enclist(1, cnt))
            {
                i_at_m48 = enclist(0, cnt);
                break;
            }
        }
        enc = 80000 + i_at_m48;
        break;
    case 9:
        enc = rnd(rnd(6) + 1);
        encp =
            clamp(encp, 0, 500) * encammoref(1, enc) / 500 + encammoref(0, enc);
        enc += 90000;
        encp += encp * 1000;
        break;
    default: break;
    }

    i_at_m48 = -1;
    for (int cnt = 0; cnt < 15; ++cnt)
    {
        if (inv[ci].enchantments[cnt].id == enc)
        {
            i_at_m48 = cnt;
            continue;
        }
        if (i_at_m48 == -1)
        {
            if (inv[ci].enchantments[cnt].id == 0)
            {
                i_at_m48 = cnt;
            }
        }
    }
    if (i_at_m48 == -1)
    {
        return false;
    }

    if (inv[ci].enchantments[i_at_m48].id == enc)
    {
        if (category == 25000)
        {
            return false;
        }
        if (!not_halve)
        {
            encp /= 2;
        }
    }

    if (only_check)
    {
        rtval(0) = enc;
        rtval(1) = encp;
        return true;
    }

    if (inv[ci].enchantments[i_at_m48].id == enc)
    {
        encp += inv[ci].enchantments[i_at_m48].power;
    }
    inv[ci].enchantments[i_at_m48].id = enc;
    inv[ci].enchantments[i_at_m48].power = encp;

    if (type < 10000)
    {
        p_at_m48 = type;
    }
    else
    {
        p_at_m48 = type / 10000;
    }
    if (inv[ci].value * encref(1, p_at_m48) / 100 > 0)
    {
        inv[ci].value = inv[ci].value * encref(1, p_at_m48) / 100;
    }
    enchantment_sort(ci);

    return true;
}



void add_enchantments_depending_on_ego()
{
    for (int cnt = 0, cnt_end = (rnd(rnd(5) + 1) + 1); cnt < cnt_end; ++cnt)
    {
        enchantment_add(
            ci,
            enchantment_generate(enchantment_gen_level(egolv)),
            enchantment_gen_p(),
            8);
    }
    inv[ci].subname = 20000 + rnd(maxegominorn);
    return;
}



void add_enchantment_by_fixed_ego()
{
    p = 0;
    for (int cnt = 0; cnt < 11; ++cnt)
    {
        if (egoref(0, cnt) != egolv)
        {
            continue;
        }
        if (egoref(1, cnt) != 0)
        {
            if (enchantment_filter(reftype, egoref(1, cnt)) == 0)
            {
                continue;
            }
        }
        egolist(p) = cnt;
        ++p;
    }
    if (p == 0)
    {
        return;
    }
    p = egolist(rnd(p));
    inv[ci].subname = 10000 + p;
    ego_add(ci, p);
    if (rnd(2) == 0)
    {
        enchantment_add(
            ci,
            enchantment_generate(enchantment_gen_level(egolv)),
            enchantment_gen_p(),
            20);
    }
    if (rnd(4) == 0)
    {
        enchantment_add(
            ci,
            enchantment_generate(enchantment_gen_level(egolv)),
            enchantment_gen_p(),
            25);
    }
    return;
}



void add_enchantments()
{
    if (reftype == 25000)
    {
        inv[ci].count = -1;
    }
    if (fixlv <= 2)
    {
        return;
    }
    if (fixlv == 6)
    {
        egolv = 4;
    }
    else
    {
        egolv = rnd(clamp(rnd(objlv / 10 + 3), 0, 4) + 1);
        inv[ci].value = inv[ci].value * 3;
        inv[ci].difficulty_of_identification =
            50 + rnd((std::abs((fixlv - 2)) * 100 + 100));
    }
    if (reftypeminor == 10006)
    {
        for (int cnt = 0; cnt < 1; ++cnt)
        {
            if (rnd(10) == 0)
            {
                enchantment_add(ci, 34, enchantment_gen_p());
            }
            if (rnd(10) == 0)
            {
                enchantment_add(ci, 10016, enchantment_gen_p());
            }
            if (rnd(10) == 0)
            {
                enchantment_add(ci, 30172, enchantment_gen_p());
                break;
            }
            if (rnd(10) == 0)
            {
                enchantment_add(ci, 10003, enchantment_gen_p());
                break;
            }
            if (rnd(10) == 0)
            {
                enchantment_add(ci, 30164, enchantment_gen_p());
                break;
            }
        }
    }
    if (fixlv < 4)
    {
        if (rnd(2))
        {
            add_enchantments_depending_on_ego();
        }
        else
        {
            add_enchantment_by_fixed_ego();
        }
    }
    if (fixlv == 4 || fixlv == 5)
    {
        inv[ci].subname = 40000 + rnd(30000);
        if (fixlv == 5 || (fixlv == 4 && rnd(10) == 0))
        {
            enchantment_add(ci, enchantment_generate(99), enchantment_gen_p());
        }
        if (rnd(100) == 0 || 0)
        {
            if (reftype == 24000 || reftype == 10000)
            {
                ibitmod(10, ci, 1);
                inv[ci].param1 = 1;
                return;
            }
        }
        if (fixlv == 4)
        {
            p = rnd(rnd(rnd(10) + 1) + 3) + 3;
        }
        if (fixlv == 5)
        {
            p = rnd(rnd(rnd(10) + 1) + 3) + 6;
        }
        if (p > 11)
        {
            if (reftype == 10000 || reftype == 24000)
            {
                if (rnd(10) == 0)
                {
                    ibitmod(15, ci, 1);
                    enchantment_add(
                        ci, enchantment_generate(99), enchantment_gen_p());
                    inv[ci].curse_state = curse_state_t::blessed;
                }
            }
        }
        for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
        {
            enchantment_add(
                ci,
                enchantment_generate(enchantment_gen_level(egolv)),
                enchantment_gen_p() + (fixlv == 5) * 100
                    + (ibit(15, ci) == 1) * 100,
                20 - (fixlv == 5) * 10 - (ibit(15, ci) == 1) * 20);
        }
    }
    if (fixlv == 6)
    {
        for (int cnt = 0, cnt_end = (rnd(3)); cnt < cnt_end; ++cnt)
        {
            enchantment_add(
                ci,
                enchantment_generate(enchantment_gen_level(egolv)),
                enchantment_gen_p(),
                10);
        }
    }
    if (is_cursed(inv[ci].curse_state))
    {
        enchantment_add(
            ci,
            enchantment_generate(enchantment_gen_level(egolv)),
            clamp(enchantment_gen_p(), 250, 10000)
                * (125 + (inv[ci].curse_state == curse_state_t::doomed) * 25)
                / 100);
        for (int cnt = 0,
                 cnt_end = cnt
                 + (1 + (inv[ci].curse_state == curse_state_t::doomed)
                    + rnd(2));
             cnt < cnt_end;
             ++cnt)
        {
            if (rnd(3) == 0)
            {
                enchantment_add(ci, 2, enchantment_gen_p() * 3 / 2, 100);
                continue;
            }
            if (rnd(3) == 0)
            {
                enchantment_add(ci, 1, enchantment_gen_p() * 5 / 2, 100);
                continue;
            }
            enchantment_add(ci, enchantment_generate(-1), enchantment_gen_p());
        }
    }
    return;
}



void initialize_ego_data()
{
    SDIM1(egoname);
    DIM3(egoenc, 20, 11);
    DIM3(egoref, 2, 11);
    DIM2(egolist, 11);

    for (int cnt = 0; cnt < 11; cnt++)
    {
        egoname(cnt) =
            i18n::s.get_enum("core.locale.enchantment.item_ego.major", cnt);
    }

    egoref(0, 1) = 0;
    egoref(1, 1) = 1;
    p = 1;
    egoenc(0, p) = 30157;
    egoenc(1, p) = 100;
    egoenc(2, p) = 22;
    egoenc(3, p) = 100;
    egoref(0, 6) = 1;
    egoref(1, 6) = 1;
    p = 6;
    egoenc(0, p) = 23;
    egoenc(1, p) = 100;
    egoref(0, 8) = 1;
    egoref(1, 8) = 1;
    p = 8;
    egoenc(0, p) = 25;
    egoenc(1, p) = 100;
    egoref(0, 0) = 1;
    egoref(1, 0) = 3;
    p = 0;
    egoenc(0, p) = 20050;
    egoenc(1, p) = 150;
    egoenc(2, p) = 70050;
    egoenc(3, p) = 150;
    egoref(0, 2) = 1;
    egoref(1, 2) = 3;
    p = 2;
    egoenc(0, p) = 20051;
    egoenc(1, p) = 150;
    egoenc(2, p) = 70051;
    egoenc(3, p) = 150;
    egoref(0, 3) = 1;
    egoref(1, 3) = 3;
    p = 3;
    egoenc(0, p) = 20052;
    egoenc(1, p) = 150;
    egoenc(2, p) = 70052;
    egoenc(3, p) = 150;
    egoref(0, 5) = 1;
    egoref(1, 5) = 1;
    p = 5;
    egoenc(0, p) = 30154;
    egoenc(1, p) = 100;
    egoref(0, 7) = 2;
    egoref(1, 7) = 1;
    p = 7;
    egoenc(0, p) = 24;
    egoenc(1, p) = 100;
    egoref(0, 9) = 0;
    egoref(1, 9) = 1;
    p = 9;
    egoenc(0, p) = 26;
    egoenc(1, p) = 100;
    egoref(0, 10) = 0;
    egoref(1, 10) = 1;
    p = 10;
    egoenc(0, p) = 27;
    egoenc(1, p) = 100;
    egoref(0, 4) = 3;
    egoref(1, 4) = 10000;
    p = 4;
    egoenc(0, p) = 20050;
    egoenc(1, p) = 100;
    egoenc(2, p) = 20051;
    egoenc(3, p) = 100;
    egoenc(4, p) = 20052;
    egoenc(5, p) = 100;

    for (int cnt = 0; cnt < 10; cnt++)
    {
        egominorn(cnt) =
            i18n::s.get_enum("core.locale.enchantment.item_ego.minor", cnt);
    }

    maxegominorn = egominorn.size();
}

void ego_add(int prm_465, int prm_466)
{
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        if (egoenc(cnt * 2, prm_466) == 0)
        {
            break;
        }
        enchantment_add(
            prm_465,
            egoenc(cnt * 2, prm_466),
            enchantment_gen_p(egoenc(cnt * 2 + 1, prm_466)));
    }
    return;
}
} // namespace elona
