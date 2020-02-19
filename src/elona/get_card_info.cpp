#include "data/types/type_character.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "tcg.hpp"


namespace elona
{

int get_card_info(int card_id, CardInfo& card_info)
{
    std::string card_name;
    if (const auto card_name_opt =
            i18n::s.get_enum_optional("core.card_info", card_id))
    {
        card_name = *card_name_opt;
    }
    else if (const auto chara_id = the_character_db.get_id_from_legacy(card_id))
    {
        card_name = i18n::s.get_m("chara", chara_id->get(), "name");
    }
    else
    {
        return 0; // undefined card
    }

    card_info.cardrefn = card_name;

    if (card_id == 0)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 168;
        card_info.cardrefrace = u8"slime"s;
        return 1;
    }
    if (card_id == 343)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 1;
        card_info.cardrefrace = u8"god"s;
        return 1;
    }
    if (card_id == 1)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 140;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 353)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 443;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (card_id == 70)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 144;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 69)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 15;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 73)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 41;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 74)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 69;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 206)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 163;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 38)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 142;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 40)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 7;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 333)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 415;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 76)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 363;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 77)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 25;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (card_id == 204)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 74;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 2)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 297;
        card_info.cardrefrace = u8"elea"s;
        return 1;
    }
    if (card_id == 37)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 347;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 23)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 1;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 331;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (card_id == 26)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 1;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 332;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 27)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 1;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 333;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 28)
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
    if (card_id == 29)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 1;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 337;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (card_id == 140)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 1;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 338;
        card_info.cardrefrace = u8"dragon"s;
        return 1;
    }
    if (card_id == 30)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 8;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 31)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 109;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (card_id == 351)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 478;
        card_info.cardrefrace = u8"cat"s;
        return 1;
    }
    if (card_id == 352)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 479;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 32)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 344;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 33)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 345;
        card_info.cardrefrace = u8"elea"s;
        return 1;
    }
    if (card_id == 34)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 346;
        card_info.cardrefrace = u8"elea"s;
        return 1;
    }
    if (card_id == 139)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 99;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 146)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 99;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 142)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 340;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 141)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 339;
        card_info.cardrefrace = u8"lich"s;
        return 1;
    }
    if (card_id == 143)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 341;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 144)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 343;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 145)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 342;
        card_info.cardrefrace = u8"dragon"s;
        return 1;
    }
    if (card_id == 306)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 393;
        card_info.cardrefrace = u8"god"s;
        return 1;
    }
    if (card_id == 331)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 413;
        card_info.cardrefrace = u8"god"s;
        return 1;
    }
    if (card_id == 336)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 413;
        card_info.cardrefrace = u8"god"s;
        return 1;
    }
    if (card_id == 338)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 432;
        card_info.cardrefrace = u8"god"s;
        return 1;
    }
    if (card_id == 339)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 433;
        card_info.cardrefrace = u8"god"s;
        return 1;
    }
    if (card_id == 342)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 447;
        card_info.cardrefrace = u8"god"s;
        return 1;
    }
    if (card_id == 340)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 435;
        card_info.cardrefrace = u8"god"s;
        return 1;
    }
    if (card_id == 3)
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
    if (card_id == 4)
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
    if (card_id == 169)
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
    if (card_id == 194)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 70;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 2257;
        card_info.cardrefrace = u8"slime"s;
        return 1;
    }
    if (card_id == 286)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 25;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 400;
        card_info.cardrefrace = u8"slime"s;
        return 1;
    }
    if (card_id == 285)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 25;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 17400;
        card_info.cardrefrace = u8"slime"s;
        return 1;
    }
    if (card_id == 287)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 25;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 401;
        card_info.cardrefrace = u8"drake"s;
        return 1;
    }
    if (card_id == 327)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 15;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 282;
        card_info.cardrefrace = u8"machine"s;
        return 1;
    }
    if (card_id == 5)
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
    if (card_id == 6)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 174;
        card_info.cardrefrace = u8"snail"s;
        return 1;
    }
    if (card_id == 7)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 37;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 8)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 139;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 9)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 102;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 269)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 179;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 320)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 10;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 410;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 273)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 187;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 326)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 148;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (card_id == 270)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 181;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 349)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 442;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 348)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 473;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 347)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 285;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 271)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 183;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 335)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 418;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 337)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 419;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 272)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 185;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 274)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 189;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 289)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 195;
        card_info.cardrefrace = u8"eulderna"s;
        return 1;
    }
    if (card_id == 293)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 76;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (card_id == 295)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 78;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 35)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 104;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 36)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 106;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 174)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 60;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 112;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 10)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 30;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 170;
        card_info.cardrefrace = u8"sheep"s;
        return 1;
    }
    if (card_id == 11)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 172;
        card_info.cardrefrace = u8"frog"s;
        return 1;
    }
    if (card_id == 12)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 31;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (card_id == 13)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 171;
        card_info.cardrefrace = u8"kobold"s;
        return 1;
    }
    if (card_id == 236)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 378;
        card_info.cardrefrace = u8"yeek"s;
        return 1;
    }
    if (card_id == 238)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 6378;
        card_info.cardrefrace = u8"yeek"s;
        return 1;
    }
    if (card_id == 241)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 2378;
        card_info.cardrefrace = u8"yeek"s;
        return 1;
    }
    if (card_id == 240)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 8378;
        card_info.cardrefrace = u8"yeek"s;
        return 1;
    }
    if (card_id == 237)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 150;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3378;
        card_info.cardrefrace = u8"yeek"s;
        return 1;
    }
    if (card_id == 244)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 25;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 385;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 245)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 20;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 386;
        card_info.cardrefrace = u8"rock"s;
        return 1;
    }
    if (card_id == 321)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 15;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 411;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 242)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 381;
        card_info.cardrefrace = u8"yeek"s;
        return 1;
    }
    if (card_id == 239)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 379;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 14)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 173;
        card_info.cardrefrace = u8"centipede"s;
        return 1;
    }
    if (card_id == 15)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 177;
        card_info.cardrefrace = u8"mushroom"s;
        return 1;
    }
    if (card_id == 283)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 399;
        card_info.cardrefrace = u8"mushroom"s;
        return 1;
    }
    if (card_id == 284)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 8399;
        card_info.cardrefrace = u8"mushroom"s;
        return 1;
    }
    if (card_id == 16)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 136;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (card_id == 39)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 134;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (card_id == 171)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 128;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (card_id == 172)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 127;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (card_id == 173)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 146;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (card_id == 71)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 120;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 72)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 119;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 79)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 117;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 80)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 116;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 17)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 17165;
        card_info.cardrefrace = u8"orc"s;
        return 1;
    }
    if (card_id == 281)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 397;
        card_info.cardrefrace = u8"lizardman"s;
        return 1;
    }
    if (card_id == 282)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 70;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 398;
        card_info.cardrefrace = u8"minotaur"s;
        return 1;
    }
    if (card_id == 296)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 70;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 4398;
        card_info.cardrefrace = u8"minotaur"s;
        return 1;
    }
    if (card_id == 298)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 70;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3398;
        card_info.cardrefrace = u8"minotaur"s;
        return 1;
    }
    if (card_id == 299)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 8398;
        card_info.cardrefrace = u8"minotaur"s;
        return 1;
    }
    if (card_id == 300)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 10398;
        card_info.cardrefrace = u8"minotaur"s;
        return 1;
    }
    if (card_id == 251)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 391;
        card_info.cardrefrace = u8"troll"s;
        return 1;
    }
    if (card_id == 18)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3;
        card_info.cardrefrace = u8"elea"s;
        return 1;
    }
    if (card_id == 24)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 47;
        card_info.cardrefrace = u8"elea"s;
        return 1;
    }
    if (card_id == 309)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 405;
        card_info.cardrefrace = u8"asura"s;
        return 1;
    }
    if (card_id == 310)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 2405;
        card_info.cardrefrace = u8"asura"s;
        return 1;
    }
    if (card_id == 311)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3405;
        card_info.cardrefrace = u8"asura"s;
        return 1;
    }
    if (card_id == 41)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 13;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 75)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 21;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 19)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 175;
        card_info.cardrefrace = u8"mandrake"s;
        return 1;
    }
    if (card_id == 22)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 176;
        card_info.cardrefrace = u8"beetle"s;
        return 1;
    }
    if (card_id == 20)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 165;
        card_info.cardrefrace = u8"orc"s;
        return 1;
    }
    if (card_id == 25)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3165;
        card_info.cardrefrace = u8"orc"s;
        return 1;
    }
    if (card_id == 21)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 167;
        card_info.cardrefrace = u8"zombie"s;
        return 1;
    }
    if (card_id == 42)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 200;
        card_info.cardrefrace = u8"bat"s;
        return 1;
    }
    if (card_id == 43)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 70;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3200;
        card_info.cardrefrace = u8"bat"s;
        return 1;
    }
    if (card_id == 44)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 60;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 4200;
        card_info.cardrefrace = u8"bat"s;
        return 1;
    }
    if (card_id == 45)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 16201;
        card_info.cardrefrace = u8"ent"s;
        return 1;
    }
    if (card_id == 46)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 17201;
        card_info.cardrefrace = u8"ent"s;
        return 1;
    }
    if (card_id == 47)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 60;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 202;
        card_info.cardrefrace = u8"lich"s;
        return 1;
    }
    if (card_id == 48)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 16202;
        card_info.cardrefrace = u8"lich"s;
        return 1;
    }
    if (card_id == 49)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 17202;
        card_info.cardrefrace = u8"lich"s;
        return 1;
    }
    if (card_id == 307)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 10;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 404;
        card_info.cardrefrace = u8"lich"s;
        return 1;
    }
    if (card_id == 308)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 10;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 4404;
        card_info.cardrefrace = u8"lich"s;
        return 1;
    }
    if (card_id == 50)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 80;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 6203;
        card_info.cardrefrace = u8"hound"s;
        return 1;
    }
    if (card_id == 51)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 70;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3203;
        card_info.cardrefrace = u8"hound"s;
        return 1;
    }
    if (card_id == 52)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 70;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 12203;
        card_info.cardrefrace = u8"hound"s;
        return 1;
    }
    if (card_id == 53)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 70;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 5203;
        card_info.cardrefrace = u8"hound"s;
        return 1;
    }
    if (card_id == 54)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 70;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 4203;
        card_info.cardrefrace = u8"hound"s;
        return 1;
    }
    if (card_id == 55)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 10203;
        card_info.cardrefrace = u8"hound"s;
        return 1;
    }
    if (card_id == 56)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 9203;
        card_info.cardrefrace = u8"hound"s;
        return 1;
    }
    if (card_id == 57)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 2203;
        card_info.cardrefrace = u8"hound"s;
        return 1;
    }
    if (card_id == 58)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 11203;
        card_info.cardrefrace = u8"hound"s;
        return 1;
    }
    if (card_id == 59)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 15203;
        card_info.cardrefrace = u8"hound"s;
        return 1;
    }
    if (card_id == 60)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 18203;
        card_info.cardrefrace = u8"hound"s;
        return 1;
    }
    if (card_id == 61)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 6204;
        card_info.cardrefrace = u8"rabbit"s;
        return 1;
    }
    if (card_id == 62)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3204;
        card_info.cardrefrace = u8"rabbit"s;
        return 1;
    }
    if (card_id == 63)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 205;
        card_info.cardrefrace = u8"ghost"s;
        return 1;
    }
    if (card_id == 64)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 70;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 2205;
        card_info.cardrefrace = u8"ghost"s;
        return 1;
    }
    if (card_id == 312)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 406;
        card_info.cardrefrace = u8"ent"s;
        return 1;
    }
    if (card_id == 313)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 16406;
        card_info.cardrefrace = u8"ent"s;
        return 1;
    }
    if (card_id == 65)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 5206;
        card_info.cardrefrace = u8"spirit"s;
        return 1;
    }
    if (card_id == 66)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 18206;
        card_info.cardrefrace = u8"spirit"s;
        return 1;
    }
    if (card_id == 67)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 80;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 207;
        card_info.cardrefrace = u8"eye"s;
        return 1;
    }
    if (card_id == 315)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 60;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 8207;
        card_info.cardrefrace = u8"eye"s;
        return 1;
    }
    if (card_id == 316)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 60;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 4407;
        card_info.cardrefrace = u8"eye"s;
        return 1;
    }
    if (card_id == 314)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 60;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3407;
        card_info.cardrefrace = u8"eye"s;
        return 1;
    }
    if (card_id == 68)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 235;
        card_info.cardrefrace = u8"wyvern"s;
        return 1;
    }
    if (card_id == 78)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 209;
        card_info.cardrefrace = u8"eulderna"s;
        return 1;
    }
    if (card_id == 81)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 210;
        card_info.cardrefrace = u8"wasp"s;
        return 1;
    }
    if (card_id == 82)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3210;
        card_info.cardrefrace = u8"wasp"s;
        return 1;
    }
    if (card_id == 83)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 60;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 232;
        card_info.cardrefrace = u8"giant"s;
        return 1;
    }
    if (card_id == 84)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 16232;
        card_info.cardrefrace = u8"giant"s;
        return 1;
    }
    if (card_id == 85)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 16212;
        card_info.cardrefrace = u8"imp"s;
        return 1;
    }
    if (card_id == 86)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 4212;
        card_info.cardrefrace = u8"imp"s;
        return 1;
    }
    if (card_id == 87)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 18212;
        card_info.cardrefrace = u8"imp"s;
        return 1;
    }
    if (card_id == 88)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 213;
        card_info.cardrefrace = u8"hand"s;
        return 1;
    }
    if (card_id == 89)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 18213;
        card_info.cardrefrace = u8"hand"s;
        return 1;
    }
    if (card_id == 90)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 16213;
        card_info.cardrefrace = u8"hand"s;
        return 1;
    }
    if (card_id == 91)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 214;
        card_info.cardrefrace = u8"ghost"s;
        return 1;
    }
    if (card_id == 92)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 5214;
        card_info.cardrefrace = u8"ghost"s;
        return 1;
    }
    if (card_id == 93)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 215;
        card_info.cardrefrace = u8"mandrake"s;
        return 1;
    }
    if (card_id == 94)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 10215;
        card_info.cardrefrace = u8"mandrake"s;
        return 1;
    }
    if (card_id == 95)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 17216;
        card_info.cardrefrace = u8"snake"s;
        return 1;
    }
    if (card_id == 96)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 16216;
        card_info.cardrefrace = u8"snake"s;
        return 1;
    }
    if (card_id == 97)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3233;
        card_info.cardrefrace = u8"drake"s;
        return 1;
    }
    if (card_id == 98)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 233;
        card_info.cardrefrace = u8"drake"s;
        return 1;
    }
    if (card_id == 99)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 219;
        card_info.cardrefrace = u8"zombie"s;
        return 1;
    }
    if (card_id == 100)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 10219;
        card_info.cardrefrace = u8"zombie"s;
        return 1;
    }
    if (card_id == 101)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 5219;
        card_info.cardrefrace = u8"zombie"s;
        return 1;
    }
    if (card_id == 257)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 8219;
        card_info.cardrefrace = u8"zombie"s;
        return 1;
    }
    if (card_id == 254)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 395;
        card_info.cardrefrace = u8"zombie"s;
        return 1;
    }
    if (card_id == 102)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 16220;
        card_info.cardrefrace = u8"goblin"s;
        return 1;
    }
    if (card_id == 103)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 5220;
        card_info.cardrefrace = u8"goblin"s;
        return 1;
    }
    if (card_id == 104)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 18220;
        card_info.cardrefrace = u8"goblin"s;
        return 1;
    }
    if (card_id == 105)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 4220;
        card_info.cardrefrace = u8"goblin"s;
        return 1;
    }
    if (card_id == 106)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3221;
        card_info.cardrefrace = u8"ghost"s;
        return 1;
    }
    if (card_id == 107)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 4221;
        card_info.cardrefrace = u8"ghost"s;
        return 1;
    }
    if (card_id == 108)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 222;
        card_info.cardrefrace = u8"bear"s;
        return 1;
    }
    if (card_id == 109)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3222;
        card_info.cardrefrace = u8"bear"s;
        return 1;
    }
    if (card_id == 344)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 439;
        card_info.cardrefrace = u8"bear"s;
        return 1;
    }
    if (card_id == 110)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 223;
        card_info.cardrefrace = u8"armor"s;
        return 1;
    }
    if (card_id == 111)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 30;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 17223;
        card_info.cardrefrace = u8"armor"s;
        return 1;
    }
    if (card_id == 112)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 30;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 5223;
        card_info.cardrefrace = u8"armor"s;
        return 1;
    }
    if (card_id == 113)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 30;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 16223;
        card_info.cardrefrace = u8"armor"s;
        return 1;
    }
    if (card_id == 114)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 224;
        card_info.cardrefrace = u8"medusa"s;
        return 1;
    }
    if (card_id == 115)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 5224;
        card_info.cardrefrace = u8"medusa"s;
        return 1;
    }
    if (card_id == 116)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 16224;
        card_info.cardrefrace = u8"medusa"s;
        return 1;
    }
    if (card_id == 117)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 225;
        card_info.cardrefrace = u8"cupid"s;
        return 1;
    }
    if (card_id == 118)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 226;
        card_info.cardrefrace = u8"phantom"s;
        return 1;
    }
    if (card_id == 248)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 389;
        card_info.cardrefrace = u8"dinosaur"s;
        return 1;
    }
    if (card_id == 119)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 227;
        card_info.cardrefrace = u8"harpy"s;
        return 1;
    }
    if (card_id == 120)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 30;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 19228;
        card_info.cardrefrace = u8"dragon"s;
        return 1;
    }
    if (card_id == 121)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 20;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3228;
        card_info.cardrefrace = u8"dragon"s;
        return 1;
    }
    if (card_id == 122)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 20;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 228;
        card_info.cardrefrace = u8"dragon"s;
        return 1;
    }
    if (card_id == 123)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 20;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 5228;
        card_info.cardrefrace = u8"dragon"s;
        return 1;
    }
    if (card_id == 124)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 10;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 4228;
        card_info.cardrefrace = u8"dragon"s;
        return 1;
    }
    if (card_id == 125)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 10;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 18228;
        card_info.cardrefrace = u8"dragon"s;
        return 1;
    }
    if (card_id == 126)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 229;
        card_info.cardrefrace = u8"cerberus"s;
        return 1;
    }
    if (card_id == 255)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 396;
        card_info.cardrefrace = u8"centipede"s;
        return 1;
    }
    if (card_id == 256)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3396;
        card_info.cardrefrace = u8"centipede"s;
        return 1;
    }
    if (card_id == 127)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 230;
        card_info.cardrefrace = u8"spider"s;
        return 1;
    }
    if (card_id == 128)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 19230;
        card_info.cardrefrace = u8"spider"s;
        return 1;
    }
    if (card_id == 129)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 17230;
        card_info.cardrefrace = u8"spider"s;
        return 1;
    }
    if (card_id == 130)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 5230;
        card_info.cardrefrace = u8"spider"s;
        return 1;
    }
    if (card_id == 131)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 16230;
        card_info.cardrefrace = u8"spider"s;
        return 1;
    }
    if (card_id == 132)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 6231;
        card_info.cardrefrace = u8"golem"s;
        return 1;
    }
    if (card_id == 133)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 231;
        card_info.cardrefrace = u8"golem"s;
        return 1;
    }
    if (card_id == 134)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 15231;
        card_info.cardrefrace = u8"golem"s;
        return 1;
    }
    if (card_id == 135)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 30;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 5231;
        card_info.cardrefrace = u8"golem"s;
        return 1;
    }
    if (card_id == 136)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 20;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 17231;
        card_info.cardrefrace = u8"golem"s;
        return 1;
    }
    if (card_id == 137)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 15;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 9231;
        card_info.cardrefrace = u8"golem"s;
        return 1;
    }
    if (card_id == 138)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 15;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 2231;
        card_info.cardrefrace = u8"golem"s;
        return 1;
    }
    if (card_id == 147)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 237;
        card_info.cardrefrace = u8"crab"s;
        return 1;
    }
    if (card_id == 148)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 239;
        card_info.cardrefrace = u8"centipede"s;
        return 1;
    }
    if (card_id == 149)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 240;
        card_info.cardrefrace = u8"goblin"s;
        return 1;
    }
    if (card_id == 150)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 241;
        card_info.cardrefrace = u8"skeleton"s;
        return 1;
    }
    if (card_id == 151)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3241;
        card_info.cardrefrace = u8"skeleton"s;
        return 1;
    }
    if (card_id == 152)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 243;
        card_info.cardrefrace = u8"eulderna"s;
        return 1;
    }
    if (card_id == 153)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 244;
        card_info.cardrefrace = u8"piece"s;
        return 1;
    }
    if (card_id == 154)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 245;
        card_info.cardrefrace = u8"piece"s;
        return 1;
    }
    if (card_id == 155)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 246;
        card_info.cardrefrace = u8"piece"s;
        return 1;
    }
    if (card_id == 156)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 247;
        card_info.cardrefrace = u8"piece"s;
        return 1;
    }
    if (card_id == 157)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 248;
        card_info.cardrefrace = u8"piece"s;
        return 1;
    }
    if (card_id == 158)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 249;
        card_info.cardrefrace = u8"piece"s;
        return 1;
    }
    if (card_id == 159)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 25;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 159;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 160)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 25;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 57;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 161)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 25;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 100;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 302)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 25;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 150;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (card_id == 303)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 25;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 31;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (card_id == 304)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 25;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 158;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (card_id == 305)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 25;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 157;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (card_id == 162)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 250;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (card_id == 234)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3250;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (card_id == 231)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 370;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (card_id == 232)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 373;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (card_id == 233)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 377;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (card_id == 235)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 4377;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (card_id == 163)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 251;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (card_id == 164)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 253;
        card_info.cardrefrace = u8"cat"s;
        return 1;
    }
    if (card_id == 246)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 1;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 387;
        card_info.cardrefrace = u8"cat"s;
        return 1;
    }
    if (card_id == 332)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 10;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 6387;
        card_info.cardrefrace = u8"cat"s;
        return 1;
    }
    if (card_id == 229)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 368;
        card_info.cardrefrace = u8"cat"s;
        return 1;
    }
    if (card_id == 230)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 369;
        card_info.cardrefrace = u8"catgod"s;
        return 1;
    }
    if (card_id == 228)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 367;
        card_info.cardrefrace = u8"cat"s;
        return 1;
    }
    if (card_id == 165)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 254;
        card_info.cardrefrace = u8"dog"s;
        return 1;
    }
    if (card_id == 225)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 364;
        card_info.cardrefrace = u8"dog"s;
        return 1;
    }
    if (card_id == 226)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 365;
        card_info.cardrefrace = u8"roran"s;
        return 1;
    }
    if (card_id == 227)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 366;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 166)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 4;
        card_info.cardrefrace = u8"roran"s;
        return 1;
    }
    if (card_id == 167)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 6255;
        card_info.cardrefrace = u8"rat"s;
        return 1;
    }
    if (card_id == 168)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 256;
        card_info.cardrefrace = u8"shell"s;
        return 1;
    }
    if (card_id == 170)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 258;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (card_id == 175)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 348;
        card_info.cardrefrace = u8"catgod"s;
        return 1;
    }
    if (card_id == 176)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 105;
        card_info.cardrefrace = u8"roran"s;
        return 1;
    }
    if (card_id == 249)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 105;
        card_info.cardrefrace = u8"roran"s;
        return 1;
    }
    if (card_id == 210)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 354;
        card_info.cardrefrace = u8"catsister"s;
        return 1;
    }
    if (card_id == 211)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 355;
        card_info.cardrefrace = u8"roran"s;
        return 1;
    }
    if (card_id == 177)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 349;
        card_info.cardrefrace = u8"machinegod"s;
        return 1;
    }
    if (card_id == 178)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3339;
        card_info.cardrefrace = u8"undeadgod"s;
        return 1;
    }
    if (card_id == 179)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 350;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 208)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 352;
        card_info.cardrefrace = u8"dwarf"s;
        return 1;
    }
    if (card_id == 209)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 353;
        card_info.cardrefrace = u8"dwarf"s;
        return 1;
    }
    if (card_id == 180)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 259;
        card_info.cardrefrace = u8"cat"s;
        return 1;
    }
    if (card_id == 181)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 260;
        card_info.cardrefrace = u8"hound"s;
        return 1;
    }
    if (card_id == 182)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 208;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 183)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 20;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 71;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 184)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 73;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 185)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 122;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (card_id == 350)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 1477;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (card_id == 186)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 270;
        card_info.cardrefrace = u8"machine"s;
        return 1;
    }
    if (card_id == 187)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 17270;
        card_info.cardrefrace = u8"machine"s;
        return 1;
    }
    if (card_id == 188)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3270;
        card_info.cardrefrace = u8"machine"s;
        return 1;
    }
    if (card_id == 345)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 470;
        card_info.cardrefrace = u8"bike"s;
        return 1;
    }
    if (card_id == 346)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 5;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 471;
        card_info.cardrefrace = u8"bike"s;
        return 1;
    }
    if (card_id == 341)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 25;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 434;
        card_info.cardrefrace = u8"machine"s;
        return 1;
    }
    if (card_id == 258)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 198;
        card_info.cardrefrace = u8"machine"s;
        return 1;
    }
    if (card_id == 189)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 60;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 271;
        card_info.cardrefrace = u8"eye"s;
        return 1;
    }
    if (card_id == 190)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 60;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3271;
        card_info.cardrefrace = u8"eye"s;
        return 1;
    }
    if (card_id == 191)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 272;
        card_info.cardrefrace = u8"wisp"s;
        return 1;
    }
    if (card_id == 192)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 273;
        card_info.cardrefrace = u8"crab"s;
        return 1;
    }
    if (card_id == 193)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 70;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 17273;
        card_info.cardrefrace = u8"crab"s;
        return 1;
    }
    if (card_id == 195)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 30;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 274;
        card_info.cardrefrace = u8"chicken"s;
        return 1;
    }
    if (card_id == 196)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 60;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 275;
        card_info.cardrefrace = u8"mandrake"s;
        return 1;
    }
    if (card_id == 201)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 20;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 5275;
        card_info.cardrefrace = u8"mandrake"s;
        return 1;
    }
    if (card_id == 197)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 60;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 4275;
        card_info.cardrefrace = u8"mandrake"s;
        return 1;
    }
    if (card_id == 198)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 60;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3275;
        card_info.cardrefrace = u8"mandrake"s;
        return 1;
    }
    if (card_id == 199)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 30;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 276;
        card_info.cardrefrace = u8"stalker"s;
        return 1;
    }
    if (card_id == 200)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 30;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3276;
        card_info.cardrefrace = u8"stalker"s;
        return 1;
    }
    if (card_id == 202)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 351;
        card_info.cardrefrace = u8"giant"s;
        return 1;
    }
    if (card_id == 203)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 23;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 205)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 104;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (card_id == 207)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 351;
        card_info.cardrefrace = u8"giant"s;
        return 1;
    }
    if (card_id == 212)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 117;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (card_id == 213)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 356;
        card_info.cardrefrace = u8"roran"s;
        return 1;
    }
    if (card_id == 221)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 358;
        card_info.cardrefrace = u8"roran"s;
        return 1;
    }
    if (card_id == 222)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 359;
        card_info.cardrefrace = u8"roran"s;
        return 1;
    }
    if (card_id == 223)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 361;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 224)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 362;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 243)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 383;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 247)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 388;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 252)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 392;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 253)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 394;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (card_id == 259)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 199;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (card_id == 301)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 403;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 214)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 30;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 166;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (card_id == 215)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 30;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 3166;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (card_id == 217)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 30;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 4166;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (card_id == 216)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 20;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 429;
        card_info.cardrefrace = u8"yith"s;
        return 1;
    }
    if (card_id == 218)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 277;
        card_info.cardrefrace = u8"yith"s;
        return 1;
    }
    if (card_id == 219)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 80;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 278;
        card_info.cardrefrace = u8"orc"s;
        return 1;
    }
    if (card_id == 220)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 30;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 430;
        card_info.cardrefrace = u8"yith"s;
        return 1;
    }
    if (card_id == 250)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 390;
        card_info.cardrefrace = u8"fairy"s;
        return 1;
    }
    if (card_id == 260)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 211;
        card_info.cardrefrace = u8"servant"s;
        return 1;
    }
    if (card_id == 261)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 217;
        card_info.cardrefrace = u8"servant"s;
        return 1;
    }
    if (card_id == 262)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 218;
        card_info.cardrefrace = u8"servant"s;
        return 1;
    }
    if (card_id == 263)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 236;
        card_info.cardrefrace = u8"servant"s;
        return 1;
    }
    if (card_id == 264)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 269;
        card_info.cardrefrace = u8"servant"s;
        return 1;
    }
    if (card_id == 265)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 267;
        card_info.cardrefrace = u8"servant"s;
        return 1;
    }
    if (card_id == 266)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 242;
        card_info.cardrefrace = u8"servant"s;
        return 1;
    }
    if (card_id == 267)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 10;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 17262;
        card_info.cardrefrace = u8"horse"s;
        return 1;
    }
    if (card_id == 276)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 10;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 6262;
        card_info.cardrefrace = u8"horse"s;
        return 1;
    }
    if (card_id == 275)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 10;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 15262;
        card_info.cardrefrace = u8"horse"s;
        return 1;
    }
    if (card_id == 268)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 10;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 16262;
        card_info.cardrefrace = u8"horse"s;
        return 1;
    }
    if (card_id == 277)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 10;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 10262;
        card_info.cardrefrace = u8"horse"s;
        return 1;
    }
    if (card_id == 278)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 70;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 191;
        card_info.cardrefrace = u8"mutant"s;
        return 1;
    }
    if (card_id == 279)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 263;
        card_info.cardrefrace = u8"yerles"s;
        return 1;
    }
    if (card_id == 280)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 192;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 288)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 193;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 290)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 196;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 292)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 197;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (card_id == 294)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 196;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (card_id == 291)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 80;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 297)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 196;
        card_info.cardrefrace = u8"norland"s;
        return 1;
    }
    if (card_id == 317)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 279;
        card_info.cardrefrace = u8"roran"s;
        return 1;
    }
    if (card_id == 318)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 408;
        card_info.cardrefrace = u8"machinegod"s;
        return 1;
    }
    if (card_id == 319)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 409;
        card_info.cardrefrace = u8"mutant"s;
        return 1;
    }
    if (card_id == 322)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 412;
        card_info.cardrefrace = u8"roran"s;
        return 1;
    }
    if (card_id == 334)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 50;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 416;
        card_info.cardrefrace = u8"juere"s;
        return 1;
    }
    if (card_id == 323)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 10;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 280;
        card_info.cardrefrace = u8"ghost"s;
        return 1;
    }
    if (card_id == 324)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 15;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 19281;
        card_info.cardrefrace = u8"quickling"s;
        return 1;
    }
    if (card_id == 325)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 15;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 5281;
        card_info.cardrefrace = u8"quickling"s;
        return 1;
    }
    if (card_id == 328)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 2;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 252;
        card_info.cardrefrace = u8"metal"s;
        return 1;
    }
    if (card_id == 329)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 5;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 5252;
        card_info.cardrefrace = u8"metal"s;
        return 1;
    }
    if (card_id == 330)
    {
        card_info.cardreftype = 0;
        card_info.cardrefrare = 40;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = 17283;
        card_info.cardrefrace = u8"dinosaur"s;
        return 1;
    }
    if (card_id == 502)
    {
        card_info.cardreftype = 30;
        card_info.cardrefdomain = 1;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = -1;
        card_info.cardrefrace = "";
        return 1;
    }
    if (card_id == 503)
    {
        card_info.cardreftype = 30;
        card_info.cardrefdomain = 1;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = -2;
        card_info.cardrefrace = "";
        return 1;
    }
    if (card_id == 500)
    {
        card_info.cardreftype = 30;
        card_info.cardrefdomain = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = -3;
        card_info.cardrefrace = "";
        return 1;
    }
    if (card_id == 501)
    {
        card_info.cardreftype = 30;
        card_info.cardrefdomain = 0;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = -4;
        card_info.cardrefrace = "";
        return 1;
    }
    if (card_id == 504)
    {
        card_info.cardreftype = 30;
        card_info.cardrefdomain = 2;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = -5;
        card_info.cardrefrace = "";
        return 1;
    }
    if (card_id == 505)
    {
        card_info.cardreftype = 30;
        card_info.cardrefdomain = 2;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = -6;
        card_info.cardrefrace = "";
        return 1;
    }
    if (card_id == 506)
    {
        card_info.cardreftype = 30;
        card_info.cardrefdomain = 3;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = -7;
        card_info.cardrefrace = "";
        return 1;
    }
    if (card_id == 507)
    {
        card_info.cardreftype = 30;
        card_info.cardrefdomain = 3;
        card_info.cardrefrare = 100;
        card_info.cardrefcost = 0;
        card_info.cardrefpic = -8;
        card_info.cardrefrace = "";
        return 1;
    }
    if (card_id == 508)
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
    if (card_id == 509)
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
