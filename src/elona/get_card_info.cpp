#include "data/types/type_character.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "tcg.hpp"


namespace elona
{

int get_card_info(int dbid, CardInfo& card_info)
{
    std::string card_name;
    if (const auto card_name_opt =
            i18n::s.get_enum_optional("core.card_info", dbid))
    {
        card_name = *card_name_opt;
    }
    else if (const auto chara_id = the_character_db.get_id_from_legacy(dbid))
    {
        card_name = i18n::s.get_m("chara", *chara_id, "name");
    }
    else
    {
        return 0; // undefined card
    }

    card_info.cardrefn = card_name;

    if (dbid == 0)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 168;
        card_info.cardrefrace = u8"slime"s;
        return 1;
    }
    if (dbid == 343)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 1;
        card_info.cardrefrace = u8"god"s;
        return 1;
    }
    if (dbid == 1)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 140;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 353)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 443;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 70)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 144;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 69)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 15;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 73)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 41;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 74)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 69;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 206)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 163;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 38)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 142;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 40)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 7;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 333)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 415;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 76)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 363;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 77)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 25;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 204)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 74;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 2)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 297;
        card_info.cardrefrace = u8"elea"s;
        return 1;
    }
    if (dbid == 37)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 347;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 23)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 1;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 331;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 26)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 1;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 332;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 27)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 1;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 333;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 28)
    {
        card_info.cardreftype = 10;
        card_info.cardrefdomain = 3;
        card_info.cardrefrare = 1;
        card_info.cardrefcost = 6;
        card_info.cardrefattack = 5;
        card_info.cardrefhp = 6;
        card_info.cardrefpic = 334;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 29)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 1;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 337;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 140)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 1;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 338;
        card_info.cardrefrace = u8"dragon"s;
        return 1;
    }
    if (dbid == 30)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 8;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 31)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 109;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 351)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 478;
        card_info.cardrefrace = u8"cat"s;
        return 1;
    }
    if (dbid == 352)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 479;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 32)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 344;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 33)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 345;
        card_info.cardrefrace = u8"elea"s;
        return 1;
    }
    if (dbid == 34)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 346;
        card_info.cardrefrace = u8"elea"s;
        return 1;
    }
    if (dbid == 139)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 99;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 146)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 99;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 142)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 340;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 141)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 339;
        card_info.cardrefrace = u8"lich"s;
        return 1;
    }
    if (dbid == 143)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 341;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 144)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 343;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 145)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 342;
        card_info.cardrefrace = u8"dragon"s;
        return 1;
    }
    if (dbid == 306)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 393;
        card_info.cardrefrace = u8"god"s;
        return 1;
    }
    if (dbid == 331)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 413;
        card_info.cardrefrace = u8"god"s;
        return 1;
    }
    if (dbid == 336)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 413;
        card_info.cardrefrace = u8"god"s;
        return 1;
    }
    if (dbid == 338)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 432;
        card_info.cardrefrace = u8"god"s;
        return 1;
    }
    if (dbid == 339)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 433;
        card_info.cardrefrace = u8"god"s;
        return 1;
    }
    if (dbid == 342)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 447;
        card_info.cardrefrace = u8"god"s;
        return 1;
    }
    if (dbid == 340)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 435;
        card_info.cardrefrace = u8"god"s;
        return 1;
    }
    if (dbid == 3)
    {
        card_info.cardreftype = 10;
        card_info.cardrefdomain = 0;
        card_info.cardrefrare = 80;
        card_info.cardrefcost = 2;
        card_info.cardrefattack = 2;
        card_info.cardrefhp = 2;
        card_info.cardrefpic = 168;
        card_info.cardrefrace = u8"slime"s;
        return 1;
    }
    if (dbid == 4)
    {
        card_info.cardreftype = 10;
        card_info.cardrefdomain = 0;
        card_info.cardrefrare = 70;
        card_info.cardrefcost = 3;
        card_info.cardrefattack = 3;
        card_info.cardrefhp = 3;
        card_info.cardrefpic = 3168;
        card_info.cardrefrace = u8"slime"s;
        return 1;
    }
    if (dbid == 169)
    {
        card_info.cardreftype = 10;
        card_info.cardrefskill = 1;
        card_info.cardrefdomain = 1;
        card_info.cardrefrare = 70;
        card_info.cardrefcost = 4;
        card_info.cardrefattack = 4;
        card_info.cardrefhp = 3;
        card_info.cardrefskillcost = 3;
        card_info.cardrefpic = 4257;
        card_info.cardrefrace = u8"slime"s;
        return 1;
    }
    if (dbid == 194)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 70;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 2257;
        card_info.cardrefrace = u8"slime"s;
        return 1;
    }
    if (dbid == 286)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 25;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 400;
        card_info.cardrefrace = u8"slime"s;
        return 1;
    }
    if (dbid == 285)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 25;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 17400;
        card_info.cardrefrace = u8"slime"s;
        return 1;
    }
    if (dbid == 287)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 25;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 401;
        card_info.cardrefrace = u8"drake"s;
        return 1;
    }
    if (dbid == 327)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 15;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 282;
        card_info.cardrefrace = u8"machine"s;
        return 1;
    }
    if (dbid == 5)
    {
        card_info.cardreftype = 10;
        card_info.cardrefdomain = 2;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 1;
        card_info.cardrefattack = 1;
        card_info.cardrefhp = 1;
        card_info.cardrefpic = 169;
        card_info.cardrefrace = u8"rabbit"s;
        return 1;
    }
    if (dbid == 6)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 174;
        card_info.cardrefrace = u8"snail"s;
        return 1;
    }
    if (dbid == 7)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 37;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 8)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 139;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 9)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 102;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 269)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 179;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 320)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 10;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 410;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 273)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 187;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 326)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 148;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 270)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 181;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 349)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 442;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 348)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 473;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 347)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 285;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 271)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 183;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 335)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 418;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 337)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 419;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 272)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 185;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 274)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 189;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 289)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 195;
        card_info.cardrefrace = u8"eulderna"s;
        return 1;
    }
    if (dbid == 293)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 76;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 295)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 78;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 35)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 104;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 36)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 106;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 174)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 60;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 112;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 10)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 30;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 170;
        card_info.cardrefrace = u8"sheep"s;
        return 1;
    }
    if (dbid == 11)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 172;
        card_info.cardrefrace = u8"frog"s;
        return 1;
    }
    if (dbid == 12)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 31;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 13)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 171;
        card_info.cardrefrace = u8"kobold"s;
        return 1;
    }
    if (dbid == 236)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 378;
        card_info.cardrefrace = u8"yeek"s;
        return 1;
    }
    if (dbid == 238)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 6378;
        card_info.cardrefrace = u8"yeek"s;
        return 1;
    }
    if (dbid == 241)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 2378;
        card_info.cardrefrace = u8"yeek"s;
        return 1;
    }
    if (dbid == 240)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 8378;
        card_info.cardrefrace = u8"yeek"s;
        return 1;
    }
    if (dbid == 237)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 150;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3378;
        card_info.cardrefrace = u8"yeek"s;
        return 1;
    }
    if (dbid == 244)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 25;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 385;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 245)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 20;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 386;
        card_info.cardrefrace = u8"rock"s;
        return 1;
    }
    if (dbid == 321)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 15;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 411;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 242)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 381;
        card_info.cardrefrace = u8"yeek"s;
        return 1;
    }
    if (dbid == 239)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 379;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 14)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 173;
        card_info.cardrefrace = u8"centipede"s;
        return 1;
    }
    if (dbid == 15)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 177;
        card_info.cardrefrace = u8"mushroom"s;
        return 1;
    }
    if (dbid == 283)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 399;
        card_info.cardrefrace = u8"mushroom"s;
        return 1;
    }
    if (dbid == 284)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 8399;
        card_info.cardrefrace = u8"mushroom"s;
        return 1;
    }
    if (dbid == 16)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 136;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 39)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 134;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 171)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 128;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 172)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 127;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 173)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 146;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 71)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 120;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 72)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 119;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 79)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 117;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 80)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 116;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 17)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 17165;
        card_info.cardrefrace = u8"orc"s;
        return 1;
    }
    if (dbid == 281)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 397;
        card_info.cardrefrace = u8"lizardman"s;
        return 1;
    }
    if (dbid == 282)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 70;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 398;
        card_info.cardrefrace = u8"minotaur"s;
        return 1;
    }
    if (dbid == 296)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 70;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 4398;
        card_info.cardrefrace = u8"minotaur"s;
        return 1;
    }
    if (dbid == 298)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 70;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3398;
        card_info.cardrefrace = u8"minotaur"s;
        return 1;
    }
    if (dbid == 299)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 8398;
        card_info.cardrefrace = u8"minotaur"s;
        return 1;
    }
    if (dbid == 300)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 10398;
        card_info.cardrefrace = u8"minotaur"s;
        return 1;
    }
    if (dbid == 251)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 391;
        card_info.cardrefrace = u8"troll"s;
        return 1;
    }
    if (dbid == 18)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3;
        card_info.cardrefrace = u8"elea"s;
        return 1;
    }
    if (dbid == 24)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 47;
        card_info.cardrefrace = u8"elea"s;
        return 1;
    }
    if (dbid == 309)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 405;
        card_info.cardrefrace = u8"asura"s;
        return 1;
    }
    if (dbid == 310)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 2405;
        card_info.cardrefrace = u8"asura"s;
        return 1;
    }
    if (dbid == 311)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3405;
        card_info.cardrefrace = u8"asura"s;
        return 1;
    }
    if (dbid == 41)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 13;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 75)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 21;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 19)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 175;
        card_info.cardrefrace = u8"mandrake"s;
        return 1;
    }
    if (dbid == 22)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 176;
        card_info.cardrefrace = u8"beetle"s;
        return 1;
    }
    if (dbid == 20)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 165;
        card_info.cardrefrace = u8"orc"s;
        return 1;
    }
    if (dbid == 25)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3165;
        card_info.cardrefrace = u8"orc"s;
        return 1;
    }
    if (dbid == 21)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 167;
        card_info.cardrefrace = u8"zombie"s;
        return 1;
    }
    if (dbid == 42)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 200;
        card_info.cardrefrace = u8"bat"s;
        return 1;
    }
    if (dbid == 43)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 70;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3200;
        card_info.cardrefrace = u8"bat"s;
        return 1;
    }
    if (dbid == 44)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 60;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 4200;
        card_info.cardrefrace = u8"bat"s;
        return 1;
    }
    if (dbid == 45)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 16201;
        card_info.cardrefrace = u8"ent"s;
        return 1;
    }
    if (dbid == 46)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 17201;
        card_info.cardrefrace = u8"ent"s;
        return 1;
    }
    if (dbid == 47)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 60;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 202;
        card_info.cardrefrace = u8"lich"s;
        return 1;
    }
    if (dbid == 48)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 16202;
        card_info.cardrefrace = u8"lich"s;
        return 1;
    }
    if (dbid == 49)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 17202;
        card_info.cardrefrace = u8"lich"s;
        return 1;
    }
    if (dbid == 307)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 10;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 404;
        card_info.cardrefrace = u8"lich"s;
        return 1;
    }
    if (dbid == 308)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 10;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 4404;
        card_info.cardrefrace = u8"lich"s;
        return 1;
    }
    if (dbid == 50)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 80;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 6203;
        card_info.cardrefrace = u8"hound"s;
        return 1;
    }
    if (dbid == 51)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 70;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3203;
        card_info.cardrefrace = u8"hound"s;
        return 1;
    }
    if (dbid == 52)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 70;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 12203;
        card_info.cardrefrace = u8"hound"s;
        return 1;
    }
    if (dbid == 53)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 70;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 5203;
        card_info.cardrefrace = u8"hound"s;
        return 1;
    }
    if (dbid == 54)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 70;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 4203;
        card_info.cardrefrace = u8"hound"s;
        return 1;
    }
    if (dbid == 55)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 10203;
        card_info.cardrefrace = u8"hound"s;
        return 1;
    }
    if (dbid == 56)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 9203;
        card_info.cardrefrace = u8"hound"s;
        return 1;
    }
    if (dbid == 57)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 2203;
        card_info.cardrefrace = u8"hound"s;
        return 1;
    }
    if (dbid == 58)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 11203;
        card_info.cardrefrace = u8"hound"s;
        return 1;
    }
    if (dbid == 59)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 15203;
        card_info.cardrefrace = u8"hound"s;
        return 1;
    }
    if (dbid == 60)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 18203;
        card_info.cardrefrace = u8"hound"s;
        return 1;
    }
    if (dbid == 61)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 6204;
        card_info.cardrefrace = u8"rabbit"s;
        return 1;
    }
    if (dbid == 62)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3204;
        card_info.cardrefrace = u8"rabbit"s;
        return 1;
    }
    if (dbid == 63)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 205;
        card_info.cardrefrace = u8"ghost"s;
        return 1;
    }
    if (dbid == 64)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 70;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 2205;
        card_info.cardrefrace = u8"ghost"s;
        return 1;
    }
    if (dbid == 312)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 406;
        card_info.cardrefrace = u8"ent"s;
        return 1;
    }
    if (dbid == 313)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 16406;
        card_info.cardrefrace = u8"ent"s;
        return 1;
    }
    if (dbid == 65)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 5206;
        card_info.cardrefrace = u8"spirit"s;
        return 1;
    }
    if (dbid == 66)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 18206;
        card_info.cardrefrace = u8"spirit"s;
        return 1;
    }
    if (dbid == 67)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 80;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 207;
        card_info.cardrefrace = u8"eye"s;
        return 1;
    }
    if (dbid == 315)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 60;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 8207;
        card_info.cardrefrace = u8"eye"s;
        return 1;
    }
    if (dbid == 316)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 60;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 4407;
        card_info.cardrefrace = u8"eye"s;
        return 1;
    }
    if (dbid == 314)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 60;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3407;
        card_info.cardrefrace = u8"eye"s;
        return 1;
    }
    if (dbid == 68)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 235;
        card_info.cardrefrace = u8"wyvern"s;
        return 1;
    }
    if (dbid == 78)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 209;
        card_info.cardrefrace = u8"eulderna"s;
        return 1;
    }
    if (dbid == 81)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 210;
        card_info.cardrefrace = u8"wasp"s;
        return 1;
    }
    if (dbid == 82)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3210;
        card_info.cardrefrace = u8"wasp"s;
        return 1;
    }
    if (dbid == 83)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 60;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 232;
        card_info.cardrefrace = u8"giant"s;
        return 1;
    }
    if (dbid == 84)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 16232;
        card_info.cardrefrace = u8"giant"s;
        return 1;
    }
    if (dbid == 85)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 16212;
        card_info.cardrefrace = u8"imp"s;
        return 1;
    }
    if (dbid == 86)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 4212;
        card_info.cardrefrace = u8"imp"s;
        return 1;
    }
    if (dbid == 87)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 18212;
        card_info.cardrefrace = u8"imp"s;
        return 1;
    }
    if (dbid == 88)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 213;
        card_info.cardrefrace = u8"hand"s;
        return 1;
    }
    if (dbid == 89)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 18213;
        card_info.cardrefrace = u8"hand"s;
        return 1;
    }
    if (dbid == 90)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 16213;
        card_info.cardrefrace = u8"hand"s;
        return 1;
    }
    if (dbid == 91)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 214;
        card_info.cardrefrace = u8"ghost"s;
        return 1;
    }
    if (dbid == 92)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 5214;
        card_info.cardrefrace = u8"ghost"s;
        return 1;
    }
    if (dbid == 93)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 215;
        card_info.cardrefrace = u8"mandrake"s;
        return 1;
    }
    if (dbid == 94)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 10215;
        card_info.cardrefrace = u8"mandrake"s;
        return 1;
    }
    if (dbid == 95)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 17216;
        card_info.cardrefrace = u8"snake"s;
        return 1;
    }
    if (dbid == 96)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 16216;
        card_info.cardrefrace = u8"snake"s;
        return 1;
    }
    if (dbid == 97)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3233;
        card_info.cardrefrace = u8"drake"s;
        return 1;
    }
    if (dbid == 98)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 233;
        card_info.cardrefrace = u8"drake"s;
        return 1;
    }
    if (dbid == 99)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 219;
        card_info.cardrefrace = u8"zombie"s;
        return 1;
    }
    if (dbid == 100)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 10219;
        card_info.cardrefrace = u8"zombie"s;
        return 1;
    }
    if (dbid == 101)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 5219;
        card_info.cardrefrace = u8"zombie"s;
        return 1;
    }
    if (dbid == 257)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 8219;
        card_info.cardrefrace = u8"zombie"s;
        return 1;
    }
    if (dbid == 254)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 395;
        card_info.cardrefrace = u8"zombie"s;
        return 1;
    }
    if (dbid == 102)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 16220;
        card_info.cardrefrace = u8"goblin"s;
        return 1;
    }
    if (dbid == 103)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 5220;
        card_info.cardrefrace = u8"goblin"s;
        return 1;
    }
    if (dbid == 104)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 18220;
        card_info.cardrefrace = u8"goblin"s;
        return 1;
    }
    if (dbid == 105)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 4220;
        card_info.cardrefrace = u8"goblin"s;
        return 1;
    }
    if (dbid == 106)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3221;
        card_info.cardrefrace = u8"ghost"s;
        return 1;
    }
    if (dbid == 107)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 4221;
        card_info.cardrefrace = u8"ghost"s;
        return 1;
    }
    if (dbid == 108)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 222;
        card_info.cardrefrace = u8"bear"s;
        return 1;
    }
    if (dbid == 109)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3222;
        card_info.cardrefrace = u8"bear"s;
        return 1;
    }
    if (dbid == 344)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 439;
        card_info.cardrefrace = u8"bear"s;
        return 1;
    }
    if (dbid == 110)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 223;
        card_info.cardrefrace = u8"armor"s;
        return 1;
    }
    if (dbid == 111)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 30;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 17223;
        card_info.cardrefrace = u8"armor"s;
        return 1;
    }
    if (dbid == 112)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 30;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 5223;
        card_info.cardrefrace = u8"armor"s;
        return 1;
    }
    if (dbid == 113)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 30;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 16223;
        card_info.cardrefrace = u8"armor"s;
        return 1;
    }
    if (dbid == 114)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 224;
        card_info.cardrefrace = u8"medusa"s;
        return 1;
    }
    if (dbid == 115)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 5224;
        card_info.cardrefrace = u8"medusa"s;
        return 1;
    }
    if (dbid == 116)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 16224;
        card_info.cardrefrace = u8"medusa"s;
        return 1;
    }
    if (dbid == 117)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 225;
        card_info.cardrefrace = u8"cupid"s;
        return 1;
    }
    if (dbid == 118)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 226;
        card_info.cardrefrace = u8"phantom"s;
        return 1;
    }
    if (dbid == 248)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 389;
        card_info.cardrefrace = u8"dinosaur"s;
        return 1;
    }
    if (dbid == 119)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 227;
        card_info.cardrefrace = u8"harpy"s;
        return 1;
    }
    if (dbid == 120)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 30;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 19228;
        card_info.cardrefrace = u8"dragon"s;
        return 1;
    }
    if (dbid == 121)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 20;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3228;
        card_info.cardrefrace = u8"dragon"s;
        return 1;
    }
    if (dbid == 122)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 20;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 228;
        card_info.cardrefrace = u8"dragon"s;
        return 1;
    }
    if (dbid == 123)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 20;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 5228;
        card_info.cardrefrace = u8"dragon"s;
        return 1;
    }
    if (dbid == 124)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 10;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 4228;
        card_info.cardrefrace = u8"dragon"s;
        return 1;
    }
    if (dbid == 125)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 10;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 18228;
        card_info.cardrefrace = u8"dragon"s;
        return 1;
    }
    if (dbid == 126)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 229;
        card_info.cardrefrace = u8"cerberus"s;
        return 1;
    }
    if (dbid == 255)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 396;
        card_info.cardrefrace = u8"centipede"s;
        return 1;
    }
    if (dbid == 256)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3396;
        card_info.cardrefrace = u8"centipede"s;
        return 1;
    }
    if (dbid == 127)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 230;
        card_info.cardrefrace = u8"spider"s;
        return 1;
    }
    if (dbid == 128)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 19230;
        card_info.cardrefrace = u8"spider"s;
        return 1;
    }
    if (dbid == 129)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 17230;
        card_info.cardrefrace = u8"spider"s;
        return 1;
    }
    if (dbid == 130)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 5230;
        card_info.cardrefrace = u8"spider"s;
        return 1;
    }
    if (dbid == 131)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 16230;
        card_info.cardrefrace = u8"spider"s;
        return 1;
    }
    if (dbid == 132)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 6231;
        card_info.cardrefrace = u8"golem"s;
        return 1;
    }
    if (dbid == 133)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 231;
        card_info.cardrefrace = u8"golem"s;
        return 1;
    }
    if (dbid == 134)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 15231;
        card_info.cardrefrace = u8"golem"s;
        return 1;
    }
    if (dbid == 135)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 30;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 5231;
        card_info.cardrefrace = u8"golem"s;
        return 1;
    }
    if (dbid == 136)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 20;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 17231;
        card_info.cardrefrace = u8"golem"s;
        return 1;
    }
    if (dbid == 137)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 15;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 9231;
        card_info.cardrefrace = u8"golem"s;
        return 1;
    }
    if (dbid == 138)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 15;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 2231;
        card_info.cardrefrace = u8"golem"s;
        return 1;
    }
    if (dbid == 147)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 237;
        card_info.cardrefrace = u8"crab"s;
        return 1;
    }
    if (dbid == 148)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 239;
        card_info.cardrefrace = u8"centipede"s;
        return 1;
    }
    if (dbid == 149)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 240;
        card_info.cardrefrace = u8"goblin"s;
        return 1;
    }
    if (dbid == 150)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 241;
        card_info.cardrefrace = u8"skeleton"s;
        return 1;
    }
    if (dbid == 151)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3241;
        card_info.cardrefrace = u8"skeleton"s;
        return 1;
    }
    if (dbid == 152)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 243;
        card_info.cardrefrace = u8"eulderna"s;
        return 1;
    }
    if (dbid == 153)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 244;
        card_info.cardrefrace = u8"piece"s;
        return 1;
    }
    if (dbid == 154)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 245;
        card_info.cardrefrace = u8"piece"s;
        return 1;
    }
    if (dbid == 155)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 246;
        card_info.cardrefrace = u8"piece"s;
        return 1;
    }
    if (dbid == 156)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 247;
        card_info.cardrefrace = u8"piece"s;
        return 1;
    }
    if (dbid == 157)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 248;
        card_info.cardrefrace = u8"piece"s;
        return 1;
    }
    if (dbid == 158)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 249;
        card_info.cardrefrace = u8"piece"s;
        return 1;
    }
    if (dbid == 159)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 25;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 159;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 160)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 25;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 57;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 161)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 25;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 100;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 302)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 25;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 150;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 303)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 25;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 31;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 304)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 25;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 158;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 305)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 25;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 157;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 162)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 250;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 234)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3250;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 231)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 370;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 232)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 373;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 233)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 377;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 235)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 4377;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 163)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 251;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 164)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 253;
        card_info.cardrefrace = u8"cat"s;
        return 1;
    }
    if (dbid == 246)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 1;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 387;
        card_info.cardrefrace = u8"cat"s;
        return 1;
    }
    if (dbid == 332)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 10;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 6387;
        card_info.cardrefrace = u8"cat"s;
        return 1;
    }
    if (dbid == 229)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 368;
        card_info.cardrefrace = u8"cat"s;
        return 1;
    }
    if (dbid == 230)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 369;
        card_info.cardrefrace = u8"catgod"s;
        return 1;
    }
    if (dbid == 228)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 367;
        card_info.cardrefrace = u8"cat"s;
        return 1;
    }
    if (dbid == 165)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 254;
        card_info.cardrefrace = u8"dog"s;
        return 1;
    }
    if (dbid == 225)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 364;
        card_info.cardrefrace = u8"dog"s;
        return 1;
    }
    if (dbid == 226)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 365;
        card_info.cardrefrace = u8"roran"s;
        return 1;
    }
    if (dbid == 227)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 366;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 166)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 4;
        card_info.cardrefrace = u8"roran"s;
        return 1;
    }
    if (dbid == 167)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 6255;
        card_info.cardrefrace = u8"rat"s;
        return 1;
    }
    if (dbid == 168)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 256;
        card_info.cardrefrace = u8"shell"s;
        return 1;
    }
    if (dbid == 170)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 258;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 175)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 348;
        card_info.cardrefrace = u8"catgod"s;
        return 1;
    }
    if (dbid == 176)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 105;
        card_info.cardrefrace = u8"roran"s;
        return 1;
    }
    if (dbid == 249)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 105;
        card_info.cardrefrace = u8"roran"s;
        return 1;
    }
    if (dbid == 210)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 354;
        card_info.cardrefrace = u8"catsister"s;
        return 1;
    }
    if (dbid == 211)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 355;
        card_info.cardrefrace = u8"roran"s;
        return 1;
    }
    if (dbid == 177)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 349;
        card_info.cardrefrace = u8"machinegod"s;
        return 1;
    }
    if (dbid == 178)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3339;
        card_info.cardrefrace = u8"undeadgod"s;
        return 1;
    }
    if (dbid == 179)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 350;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 208)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 352;
        card_info.cardrefrace = u8"dwarf"s;
        return 1;
    }
    if (dbid == 209)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 353;
        card_info.cardrefrace = u8"dwarf"s;
        return 1;
    }
    if (dbid == 180)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 259;
        card_info.cardrefrace = u8"cat"s;
        return 1;
    }
    if (dbid == 181)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 260;
        card_info.cardrefrace = u8"hound"s;
        return 1;
    }
    if (dbid == 182)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 208;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 183)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 20;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 71;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 184)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 73;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 185)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 122;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 350)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 1477;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 186)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 270;
        card_info.cardrefrace = u8"machine"s;
        return 1;
    }
    if (dbid == 187)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 17270;
        card_info.cardrefrace = u8"machine"s;
        return 1;
    }
    if (dbid == 188)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3270;
        card_info.cardrefrace = u8"machine"s;
        return 1;
    }
    if (dbid == 345)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 470;
        card_info.cardrefrace = u8"bike"s;
        return 1;
    }
    if (dbid == 346)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 5;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 471;
        card_info.cardrefrace = u8"bike"s;
        return 1;
    }
    if (dbid == 341)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 25;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 434;
        card_info.cardrefrace = u8"machine"s;
        return 1;
    }
    if (dbid == 258)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 198;
        card_info.cardrefrace = u8"machine"s;
        return 1;
    }
    if (dbid == 189)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 60;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 271;
        card_info.cardrefrace = u8"eye"s;
        return 1;
    }
    if (dbid == 190)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 60;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3271;
        card_info.cardrefrace = u8"eye"s;
        return 1;
    }
    if (dbid == 191)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 272;
        card_info.cardrefrace = u8"wisp"s;
        return 1;
    }
    if (dbid == 192)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 273;
        card_info.cardrefrace = u8"crab"s;
        return 1;
    }
    if (dbid == 193)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 70;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 17273;
        card_info.cardrefrace = u8"crab"s;
        return 1;
    }
    if (dbid == 195)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 30;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 274;
        card_info.cardrefrace = u8"chicken"s;
        return 1;
    }
    if (dbid == 196)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 60;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 275;
        card_info.cardrefrace = u8"mandrake"s;
        return 1;
    }
    if (dbid == 201)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 20;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 5275;
        card_info.cardrefrace = u8"mandrake"s;
        return 1;
    }
    if (dbid == 197)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 60;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 4275;
        card_info.cardrefrace = u8"mandrake"s;
        return 1;
    }
    if (dbid == 198)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 60;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3275;
        card_info.cardrefrace = u8"mandrake"s;
        return 1;
    }
    if (dbid == 199)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 30;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 276;
        card_info.cardrefrace = u8"stalker"s;
        return 1;
    }
    if (dbid == 200)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 30;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3276;
        card_info.cardrefrace = u8"stalker"s;
        return 1;
    }
    if (dbid == 202)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 351;
        card_info.cardrefrace = u8"giant"s;
        return 1;
    }
    if (dbid == 203)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 23;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 205)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 104;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 207)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 351;
        card_info.cardrefrace = u8"giant"s;
        return 1;
    }
    if (dbid == 212)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 117;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 213)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 356;
        card_info.cardrefrace = u8"roran"s;
        return 1;
    }
    if (dbid == 221)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 358;
        card_info.cardrefrace = u8"roran"s;
        return 1;
    }
    if (dbid == 222)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 359;
        card_info.cardrefrace = u8"roran"s;
        return 1;
    }
    if (dbid == 223)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 361;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 224)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 362;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 243)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 383;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 247)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 388;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 252)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 392;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 253)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 394;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 259)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 199;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 301)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 403;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 214)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 30;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 166;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 215)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 30;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3166;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 217)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 30;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 4166;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 216)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 20;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 429;
        card_info.cardrefrace = u8"yith"s;
        return 1;
    }
    if (dbid == 218)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 277;
        card_info.cardrefrace = u8"yith"s;
        return 1;
    }
    if (dbid == 219)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 80;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 278;
        card_info.cardrefrace = u8"orc"s;
        return 1;
    }
    if (dbid == 220)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 30;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 430;
        card_info.cardrefrace = u8"yith"s;
        return 1;
    }
    if (dbid == 250)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 390;
        card_info.cardrefrace = u8"fairy"s;
        return 1;
    }
    if (dbid == 260)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 211;
        card_info.cardrefrace = u8"servant"s;
        return 1;
    }
    if (dbid == 261)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 217;
        card_info.cardrefrace = u8"servant"s;
        return 1;
    }
    if (dbid == 262)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 218;
        card_info.cardrefrace = u8"servant"s;
        return 1;
    }
    if (dbid == 263)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 236;
        card_info.cardrefrace = u8"servant"s;
        return 1;
    }
    if (dbid == 264)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 269;
        card_info.cardrefrace = u8"servant"s;
        return 1;
    }
    if (dbid == 265)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 267;
        card_info.cardrefrace = u8"servant"s;
        return 1;
    }
    if (dbid == 266)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 242;
        card_info.cardrefrace = u8"servant"s;
        return 1;
    }
    if (dbid == 267)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 10;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 17262;
        card_info.cardrefrace = u8"horse"s;
        return 1;
    }
    if (dbid == 276)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 10;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 6262;
        card_info.cardrefrace = u8"horse"s;
        return 1;
    }
    if (dbid == 275)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 10;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 15262;
        card_info.cardrefrace = u8"horse"s;
        return 1;
    }
    if (dbid == 268)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 10;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 16262;
        card_info.cardrefrace = u8"horse"s;
        return 1;
    }
    if (dbid == 277)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 10;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 10262;
        card_info.cardrefrace = u8"horse"s;
        return 1;
    }
    if (dbid == 278)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 70;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 191;
        card_info.cardrefrace = u8"mutant"s;
        return 1;
    }
    if (dbid == 279)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 263;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 280)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 192;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 288)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 193;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 290)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 196;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 292)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 197;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 294)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 196;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 291)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 80;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 297)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 196;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 317)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 279;
        card_info.cardrefrace = u8"roran"s;
        return 1;
    }
    if (dbid == 318)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 408;
        card_info.cardrefrace = u8"machinegod"s;
        return 1;
    }
    if (dbid == 319)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 409;
        card_info.cardrefrace = u8"mutant"s;
        return 1;
    }
    if (dbid == 322)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 412;
        card_info.cardrefrace = u8"roran"s;
        return 1;
    }
    if (dbid == 334)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 416;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 323)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 10;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 280;
        card_info.cardrefrace = u8"ghost"s;
        return 1;
    }
    if (dbid == 324)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 15;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 19281;
        card_info.cardrefrace = u8"quickling"s;
        return 1;
    }
    if (dbid == 325)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 15;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 5281;
        card_info.cardrefrace = u8"quickling"s;
        return 1;
    }
    if (dbid == 328)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 252;
        card_info.cardrefrace = u8"metal"s;
        return 1;
    }
    if (dbid == 329)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 5;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 5252;
        card_info.cardrefrace = u8"metal"s;
        return 1;
    }
    if (dbid == 330)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 17283;
        card_info.cardrefrace = u8"dinosaur"s;
        return 1;
    }
    if (dbid == 502)
    {
        card_info.cardreftype = 30;
        card_info.cardrefdomain = 1;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = -1;
        card_info.cardrefrace = "";
        return 1;
    }
    if (dbid == 503)
    {
        card_info.cardreftype = 30;
        card_info.cardrefdomain = 1;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = -2;
        card_info.cardrefrace = "";
        return 1;
    }
    if (dbid == 500)
    {
        card_info.cardreftype = 30;
        card_info.cardrefdomain = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = -3;
        card_info.cardrefrace = "";
        return 1;
    }
    if (dbid == 501)
    {
        card_info.cardreftype = 30;
        card_info.cardrefdomain = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = -4;
        card_info.cardrefrace = "";
        return 1;
    }
    if (dbid == 504)
    {
        card_info.cardreftype = 30;
        card_info.cardrefdomain = 2;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = -5;
        card_info.cardrefrace = "";
        return 1;
    }
    if (dbid == 505)
    {
        card_info.cardreftype = 30;
        card_info.cardrefdomain = 2;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = -6;
        card_info.cardrefrace = "";
        return 1;
    }
    if (dbid == 506)
    {
        card_info.cardreftype = 30;
        card_info.cardrefdomain = 3;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = -7;
        card_info.cardrefrace = "";
        return 1;
    }
    if (dbid == 507)
    {
        card_info.cardreftype = 30;
        card_info.cardrefdomain = 3;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = -8;
        card_info.cardrefrace = "";
        return 1;
    }
    if (dbid == 508)
    {
        card_info.cardreftype = 20;
        card_info.cardrefskill = 2;
        card_info.cardrefdomain = 0;
        card_info.cardrefrare = 80;
        card_info.cardrefcost = 3;
        card_info.cardrefpic = -22;
        card_info.cardrefrace = "";
        return 1;
    }
    if (dbid == 509)
    {
        card_info.cardreftype = 20;
        card_info.cardrefskill = 3;
        card_info.cardrefdomain = 0;
        card_info.cardrefrare = 70;
        card_info.cardrefcost = 2;
        card_info.cardrefpic = -23;
        card_info.cardrefrace = "";
        return 1;
    }
    return 0;
}

} // namespace elona
