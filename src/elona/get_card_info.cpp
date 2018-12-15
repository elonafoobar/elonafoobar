#include "elona.hpp"
#include "i18n.hpp"
#include "variables.hpp"


namespace elona
{


int get_card_info()
{
    cardrefn = i18n::s.get_enum("core.locale.card_info", dbid);

    if (dbid == 0)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 168;
        cardrefrace = u8"slime"s;
        return 1;
    }
    if (dbid == 343)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 1;
        cardrefrace = u8"god"s;
        return 1;
    }
    if (dbid == 1)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 140;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 353)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 443;
        cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 70)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 144;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 69)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 15;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 73)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 41;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 74)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 69;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 206)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 163;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 38)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 142;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 40)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 7;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 333)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 415;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 76)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 363;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 77)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 25;
        cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 204)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 74;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 2)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 297;
        cardrefrace = u8"elea"s;
        return 1;
    }
    if (dbid == 37)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 347;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 23)
    {
        cardreftype = 0;
        cardrefrare = 1;
        cardrefcost = 0;
        cardrefpic = 331;
        cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 26)
    {
        cardreftype = 0;
        cardrefrare = 1;
        cardrefcost = 0;
        cardrefpic = 332;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 27)
    {
        cardreftype = 0;
        cardrefrare = 1;
        cardrefcost = 0;
        cardrefpic = 333;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 28)
    {
        cardreftype = 10;
        cardrefdomain = 3;
        cardrefrare = 1;
        cardrefcost = 6;
        cardrefattack = 5;
        cardrefhp = 6;
        cardrefpic = 334;
        cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 29)
    {
        cardreftype = 0;
        cardrefrare = 1;
        cardrefcost = 0;
        cardrefpic = 337;
        cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 140)
    {
        cardreftype = 0;
        cardrefrare = 1;
        cardrefcost = 0;
        cardrefpic = 338;
        cardrefrace = u8"dragon"s;
        return 1;
    }
    if (dbid == 30)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 8;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 31)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 109;
        cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 351)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 478;
        cardrefrace = u8"cat"s;
        return 1;
    }
    if (dbid == 352)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 479;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 32)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 344;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 33)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 345;
        cardrefrace = u8"elea"s;
        return 1;
    }
    if (dbid == 34)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 346;
        cardrefrace = u8"elea"s;
        return 1;
    }
    if (dbid == 139)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 99;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 146)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 99;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 142)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 340;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 141)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 339;
        cardrefrace = u8"lich"s;
        return 1;
    }
    if (dbid == 143)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 341;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 144)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 343;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 145)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 342;
        cardrefrace = u8"dragon"s;
        return 1;
    }
    if (dbid == 306)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 393;
        cardrefrace = u8"god"s;
        return 1;
    }
    if (dbid == 331)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 413;
        cardrefrace = u8"god"s;
        return 1;
    }
    if (dbid == 336)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 413;
        cardrefrace = u8"god"s;
        return 1;
    }
    if (dbid == 338)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 432;
        cardrefrace = u8"god"s;
        return 1;
    }
    if (dbid == 339)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 433;
        cardrefrace = u8"god"s;
        return 1;
    }
    if (dbid == 342)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 447;
        cardrefrace = u8"god"s;
        return 1;
    }
    if (dbid == 340)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 435;
        cardrefrace = u8"god"s;
        return 1;
    }
    if (dbid == 3)
    {
        cardreftype = 10;
        cardrefdomain = 0;
        cardrefrare = 80;
        cardrefcost = 2;
        cardrefattack = 2;
        cardrefhp = 2;
        cardrefpic = 168;
        cardrefrace = u8"slime"s;
        return 1;
    }
    if (dbid == 4)
    {
        cardreftype = 10;
        cardrefdomain = 0;
        cardrefrare = 70;
        cardrefcost = 3;
        cardrefattack = 3;
        cardrefhp = 3;
        cardrefpic = 3168;
        cardrefrace = u8"slime"s;
        return 1;
    }
    if (dbid == 169)
    {
        cardreftype = 10;
        cardrefskill = 1;
        cardrefdomain = 1;
        cardrefrare = 70;
        cardrefcost = 4;
        cardrefattack = 4;
        cardrefhp = 3;
        cardrefskillcost = 3;
        cardrefpic = 4257;
        cardrefrace = u8"slime"s;
        return 1;
    }
    if (dbid == 194)
    {
        cardreftype = 0;
        cardrefrare = 70;
        cardrefcost = 0;
        cardrefpic = 2257;
        cardrefrace = u8"slime"s;
        return 1;
    }
    if (dbid == 286)
    {
        cardreftype = 0;
        cardrefrare = 25;
        cardrefcost = 0;
        cardrefpic = 400;
        cardrefrace = u8"slime"s;
        return 1;
    }
    if (dbid == 285)
    {
        cardreftype = 0;
        cardrefrare = 25;
        cardrefcost = 0;
        cardrefpic = 17400;
        cardrefrace = u8"slime"s;
        return 1;
    }
    if (dbid == 287)
    {
        cardreftype = 0;
        cardrefrare = 25;
        cardrefcost = 0;
        cardrefpic = 401;
        cardrefrace = u8"drake"s;
        return 1;
    }
    if (dbid == 327)
    {
        cardreftype = 0;
        cardrefrare = 15;
        cardrefcost = 0;
        cardrefpic = 282;
        cardrefrace = u8"machine"s;
        return 1;
    }
    if (dbid == 5)
    {
        cardreftype = 10;
        cardrefdomain = 2;
        cardrefrare = 100;
        cardrefcost = 1;
        cardrefattack = 1;
        cardrefhp = 1;
        cardrefpic = 169;
        cardrefrace = u8"rabbit"s;
        return 1;
    }
    if (dbid == 6)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 174;
        cardrefrace = u8"snail"s;
        return 1;
    }
    if (dbid == 7)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 37;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 8)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 139;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 9)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 102;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 269)
    {
        cardreftype = 0;
        cardrefrare = 2;
        cardrefcost = 0;
        cardrefpic = 179;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 320)
    {
        cardreftype = 0;
        cardrefrare = 10;
        cardrefcost = 0;
        cardrefpic = 410;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 273)
    {
        cardreftype = 0;
        cardrefrare = 2;
        cardrefcost = 0;
        cardrefpic = 187;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 326)
    {
        cardreftype = 0;
        cardrefrare = 2;
        cardrefcost = 0;
        cardrefpic = 148;
        cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 270)
    {
        cardreftype = 0;
        cardrefrare = 2;
        cardrefcost = 0;
        cardrefpic = 181;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 349)
    {
        cardreftype = 0;
        cardrefrare = 2;
        cardrefcost = 0;
        cardrefpic = 442;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 348)
    {
        cardreftype = 0;
        cardrefrare = 2;
        cardrefcost = 0;
        cardrefpic = 473;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 347)
    {
        cardreftype = 0;
        cardrefrare = 2;
        cardrefcost = 0;
        cardrefpic = 285;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 271)
    {
        cardreftype = 0;
        cardrefrare = 2;
        cardrefcost = 0;
        cardrefpic = 183;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 335)
    {
        cardreftype = 0;
        cardrefrare = 2;
        cardrefcost = 0;
        cardrefpic = 418;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 337)
    {
        cardreftype = 0;
        cardrefrare = 2;
        cardrefcost = 0;
        cardrefpic = 419;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 272)
    {
        cardreftype = 0;
        cardrefrare = 2;
        cardrefcost = 0;
        cardrefpic = 185;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 274)
    {
        cardreftype = 0;
        cardrefrare = 2;
        cardrefcost = 0;
        cardrefpic = 189;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 289)
    {
        cardreftype = 0;
        cardrefrare = 2;
        cardrefcost = 0;
        cardrefpic = 195;
        cardrefrace = u8"eulderna"s;
        return 1;
    }
    if (dbid == 293)
    {
        cardreftype = 0;
        cardrefrare = 2;
        cardrefcost = 0;
        cardrefpic = 76;
        cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 295)
    {
        cardreftype = 0;
        cardrefrare = 2;
        cardrefcost = 0;
        cardrefpic = 78;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 35)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 104;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 36)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 106;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 174)
    {
        cardreftype = 0;
        cardrefrare = 60;
        cardrefcost = 0;
        cardrefpic = 112;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 10)
    {
        cardreftype = 0;
        cardrefrare = 30;
        cardrefcost = 0;
        cardrefpic = 170;
        cardrefrace = u8"sheep"s;
        return 1;
    }
    if (dbid == 11)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 172;
        cardrefrace = u8"frog"s;
        return 1;
    }
    if (dbid == 12)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 31;
        cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 13)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 171;
        cardrefrace = u8"kobold"s;
        return 1;
    }
    if (dbid == 236)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 378;
        cardrefrace = u8"yeek"s;
        return 1;
    }
    if (dbid == 238)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 6378;
        cardrefrace = u8"yeek"s;
        return 1;
    }
    if (dbid == 241)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 2378;
        cardrefrace = u8"yeek"s;
        return 1;
    }
    if (dbid == 240)
    {
        cardreftype = 0;
        cardrefrare = 50;
        cardrefcost = 0;
        cardrefpic = 8378;
        cardrefrace = u8"yeek"s;
        return 1;
    }
    if (dbid == 237)
    {
        cardreftype = 0;
        cardrefrare = 150;
        cardrefcost = 0;
        cardrefpic = 3378;
        cardrefrace = u8"yeek"s;
        return 1;
    }
    if (dbid == 244)
    {
        cardreftype = 0;
        cardrefrare = 25;
        cardrefcost = 0;
        cardrefpic = 385;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 245)
    {
        cardreftype = 0;
        cardrefrare = 20;
        cardrefcost = 0;
        cardrefpic = 386;
        cardrefrace = u8"rock"s;
        return 1;
    }
    if (dbid == 321)
    {
        cardreftype = 0;
        cardrefrare = 15;
        cardrefcost = 0;
        cardrefpic = 411;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 242)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 381;
        cardrefrace = u8"yeek"s;
        return 1;
    }
    if (dbid == 239)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 379;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 14)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 173;
        cardrefrace = u8"centipede"s;
        return 1;
    }
    if (dbid == 15)
    {
        cardreftype = 0;
        cardrefrare = 50;
        cardrefcost = 0;
        cardrefpic = 177;
        cardrefrace = u8"mushroom"s;
        return 1;
    }
    if (dbid == 283)
    {
        cardreftype = 0;
        cardrefrare = 50;
        cardrefcost = 0;
        cardrefpic = 399;
        cardrefrace = u8"mushroom"s;
        return 1;
    }
    if (dbid == 284)
    {
        cardreftype = 0;
        cardrefrare = 50;
        cardrefcost = 0;
        cardrefpic = 8399;
        cardrefrace = u8"mushroom"s;
        return 1;
    }
    if (dbid == 16)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 136;
        cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 39)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 134;
        cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 171)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 128;
        cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 172)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 127;
        cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 173)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 146;
        cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 71)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 120;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 72)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 119;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 79)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 117;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 80)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 116;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 17)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 17165;
        cardrefrace = u8"orc"s;
        return 1;
    }
    if (dbid == 281)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 397;
        cardrefrace = u8"lizardman"s;
        return 1;
    }
    if (dbid == 282)
    {
        cardreftype = 0;
        cardrefrare = 70;
        cardrefcost = 0;
        cardrefpic = 398;
        cardrefrace = u8"minotaur"s;
        return 1;
    }
    if (dbid == 296)
    {
        cardreftype = 0;
        cardrefrare = 70;
        cardrefcost = 0;
        cardrefpic = 4398;
        cardrefrace = u8"minotaur"s;
        return 1;
    }
    if (dbid == 298)
    {
        cardreftype = 0;
        cardrefrare = 70;
        cardrefcost = 0;
        cardrefpic = 3398;
        cardrefrace = u8"minotaur"s;
        return 1;
    }
    if (dbid == 299)
    {
        cardreftype = 0;
        cardrefrare = 40;
        cardrefcost = 0;
        cardrefpic = 8398;
        cardrefrace = u8"minotaur"s;
        return 1;
    }
    if (dbid == 300)
    {
        cardreftype = 0;
        cardrefrare = 40;
        cardrefcost = 0;
        cardrefpic = 10398;
        cardrefrace = u8"minotaur"s;
        return 1;
    }
    if (dbid == 251)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 391;
        cardrefrace = u8"troll"s;
        return 1;
    }
    if (dbid == 18)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 3;
        cardrefrace = u8"elea"s;
        return 1;
    }
    if (dbid == 24)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 47;
        cardrefrace = u8"elea"s;
        return 1;
    }
    if (dbid == 309)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 405;
        cardrefrace = u8"asura"s;
        return 1;
    }
    if (dbid == 310)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 2405;
        cardrefrace = u8"asura"s;
        return 1;
    }
    if (dbid == 311)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 3405;
        cardrefrace = u8"asura"s;
        return 1;
    }
    if (dbid == 41)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 13;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 75)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 21;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 19)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 175;
        cardrefrace = u8"mandrake"s;
        return 1;
    }
    if (dbid == 22)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 176;
        cardrefrace = u8"beetle"s;
        return 1;
    }
    if (dbid == 20)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 165;
        cardrefrace = u8"orc"s;
        return 1;
    }
    if (dbid == 25)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 3165;
        cardrefrace = u8"orc"s;
        return 1;
    }
    if (dbid == 21)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 167;
        cardrefrace = u8"zombie"s;
        return 1;
    }
    if (dbid == 42)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 200;
        cardrefrace = u8"bat"s;
        return 1;
    }
    if (dbid == 43)
    {
        cardreftype = 0;
        cardrefrare = 70;
        cardrefcost = 0;
        cardrefpic = 3200;
        cardrefrace = u8"bat"s;
        return 1;
    }
    if (dbid == 44)
    {
        cardreftype = 0;
        cardrefrare = 60;
        cardrefcost = 0;
        cardrefpic = 4200;
        cardrefrace = u8"bat"s;
        return 1;
    }
    if (dbid == 45)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 16201;
        cardrefrace = u8"ent"s;
        return 1;
    }
    if (dbid == 46)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 17201;
        cardrefrace = u8"ent"s;
        return 1;
    }
    if (dbid == 47)
    {
        cardreftype = 0;
        cardrefrare = 60;
        cardrefcost = 0;
        cardrefpic = 202;
        cardrefrace = u8"lich"s;
        return 1;
    }
    if (dbid == 48)
    {
        cardreftype = 0;
        cardrefrare = 50;
        cardrefcost = 0;
        cardrefpic = 16202;
        cardrefrace = u8"lich"s;
        return 1;
    }
    if (dbid == 49)
    {
        cardreftype = 0;
        cardrefrare = 40;
        cardrefcost = 0;
        cardrefpic = 17202;
        cardrefrace = u8"lich"s;
        return 1;
    }
    if (dbid == 307)
    {
        cardreftype = 0;
        cardrefrare = 10;
        cardrefcost = 0;
        cardrefpic = 404;
        cardrefrace = u8"lich"s;
        return 1;
    }
    if (dbid == 308)
    {
        cardreftype = 0;
        cardrefrare = 10;
        cardrefcost = 0;
        cardrefpic = 4404;
        cardrefrace = u8"lich"s;
        return 1;
    }
    if (dbid == 50)
    {
        cardreftype = 0;
        cardrefrare = 80;
        cardrefcost = 0;
        cardrefpic = 6203;
        cardrefrace = u8"hound"s;
        return 1;
    }
    if (dbid == 51)
    {
        cardreftype = 0;
        cardrefrare = 70;
        cardrefcost = 0;
        cardrefpic = 3203;
        cardrefrace = u8"hound"s;
        return 1;
    }
    if (dbid == 52)
    {
        cardreftype = 0;
        cardrefrare = 70;
        cardrefcost = 0;
        cardrefpic = 12203;
        cardrefrace = u8"hound"s;
        return 1;
    }
    if (dbid == 53)
    {
        cardreftype = 0;
        cardrefrare = 70;
        cardrefcost = 0;
        cardrefpic = 5203;
        cardrefrace = u8"hound"s;
        return 1;
    }
    if (dbid == 54)
    {
        cardreftype = 0;
        cardrefrare = 70;
        cardrefcost = 0;
        cardrefpic = 4203;
        cardrefrace = u8"hound"s;
        return 1;
    }
    if (dbid == 55)
    {
        cardreftype = 0;
        cardrefrare = 50;
        cardrefcost = 0;
        cardrefpic = 10203;
        cardrefrace = u8"hound"s;
        return 1;
    }
    if (dbid == 56)
    {
        cardreftype = 0;
        cardrefrare = 50;
        cardrefcost = 0;
        cardrefpic = 9203;
        cardrefrace = u8"hound"s;
        return 1;
    }
    if (dbid == 57)
    {
        cardreftype = 0;
        cardrefrare = 50;
        cardrefcost = 0;
        cardrefpic = 2203;
        cardrefrace = u8"hound"s;
        return 1;
    }
    if (dbid == 58)
    {
        cardreftype = 0;
        cardrefrare = 40;
        cardrefcost = 0;
        cardrefpic = 11203;
        cardrefrace = u8"hound"s;
        return 1;
    }
    if (dbid == 59)
    {
        cardreftype = 0;
        cardrefrare = 40;
        cardrefcost = 0;
        cardrefpic = 15203;
        cardrefrace = u8"hound"s;
        return 1;
    }
    if (dbid == 60)
    {
        cardreftype = 0;
        cardrefrare = 40;
        cardrefcost = 0;
        cardrefpic = 18203;
        cardrefrace = u8"hound"s;
        return 1;
    }
    if (dbid == 61)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 6204;
        cardrefrace = u8"rabbit"s;
        return 1;
    }
    if (dbid == 62)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 3204;
        cardrefrace = u8"rabbit"s;
        return 1;
    }
    if (dbid == 63)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 205;
        cardrefrace = u8"ghost"s;
        return 1;
    }
    if (dbid == 64)
    {
        cardreftype = 0;
        cardrefrare = 70;
        cardrefcost = 0;
        cardrefpic = 2205;
        cardrefrace = u8"ghost"s;
        return 1;
    }
    if (dbid == 312)
    {
        cardreftype = 0;
        cardrefrare = 40;
        cardrefcost = 0;
        cardrefpic = 406;
        cardrefrace = u8"ent"s;
        return 1;
    }
    if (dbid == 313)
    {
        cardreftype = 0;
        cardrefrare = 40;
        cardrefcost = 0;
        cardrefpic = 16406;
        cardrefrace = u8"ent"s;
        return 1;
    }
    if (dbid == 65)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 5206;
        cardrefrace = u8"spirit"s;
        return 1;
    }
    if (dbid == 66)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 18206;
        cardrefrace = u8"spirit"s;
        return 1;
    }
    if (dbid == 67)
    {
        cardreftype = 0;
        cardrefrare = 80;
        cardrefcost = 0;
        cardrefpic = 207;
        cardrefrace = u8"eye"s;
        return 1;
    }
    if (dbid == 315)
    {
        cardreftype = 0;
        cardrefrare = 60;
        cardrefcost = 0;
        cardrefpic = 8207;
        cardrefrace = u8"eye"s;
        return 1;
    }
    if (dbid == 316)
    {
        cardreftype = 0;
        cardrefrare = 60;
        cardrefcost = 0;
        cardrefpic = 4407;
        cardrefrace = u8"eye"s;
        return 1;
    }
    if (dbid == 314)
    {
        cardreftype = 0;
        cardrefrare = 60;
        cardrefcost = 0;
        cardrefpic = 3407;
        cardrefrace = u8"eye"s;
        return 1;
    }
    if (dbid == 68)
    {
        cardreftype = 0;
        cardrefrare = 50;
        cardrefcost = 0;
        cardrefpic = 235;
        cardrefrace = u8"wyvern"s;
        return 1;
    }
    if (dbid == 78)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 209;
        cardrefrace = u8"eulderna"s;
        return 1;
    }
    if (dbid == 81)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 210;
        cardrefrace = u8"wasp"s;
        return 1;
    }
    if (dbid == 82)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 3210;
        cardrefrace = u8"wasp"s;
        return 1;
    }
    if (dbid == 83)
    {
        cardreftype = 0;
        cardrefrare = 60;
        cardrefcost = 0;
        cardrefpic = 232;
        cardrefrace = u8"giant"s;
        return 1;
    }
    if (dbid == 84)
    {
        cardreftype = 0;
        cardrefrare = 50;
        cardrefcost = 0;
        cardrefpic = 16232;
        cardrefrace = u8"giant"s;
        return 1;
    }
    if (dbid == 85)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 16212;
        cardrefrace = u8"imp"s;
        return 1;
    }
    if (dbid == 86)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 4212;
        cardrefrace = u8"imp"s;
        return 1;
    }
    if (dbid == 87)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 18212;
        cardrefrace = u8"imp"s;
        return 1;
    }
    if (dbid == 88)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 213;
        cardrefrace = u8"hand"s;
        return 1;
    }
    if (dbid == 89)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 18213;
        cardrefrace = u8"hand"s;
        return 1;
    }
    if (dbid == 90)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 16213;
        cardrefrace = u8"hand"s;
        return 1;
    }
    if (dbid == 91)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 214;
        cardrefrace = u8"ghost"s;
        return 1;
    }
    if (dbid == 92)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 5214;
        cardrefrace = u8"ghost"s;
        return 1;
    }
    if (dbid == 93)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 215;
        cardrefrace = u8"mandrake"s;
        return 1;
    }
    if (dbid == 94)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 10215;
        cardrefrace = u8"mandrake"s;
        return 1;
    }
    if (dbid == 95)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 17216;
        cardrefrace = u8"snake"s;
        return 1;
    }
    if (dbid == 96)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 16216;
        cardrefrace = u8"snake"s;
        return 1;
    }
    if (dbid == 97)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 3233;
        cardrefrace = u8"drake"s;
        return 1;
    }
    if (dbid == 98)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 233;
        cardrefrace = u8"drake"s;
        return 1;
    }
    if (dbid == 99)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 219;
        cardrefrace = u8"zombie"s;
        return 1;
    }
    if (dbid == 100)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 10219;
        cardrefrace = u8"zombie"s;
        return 1;
    }
    if (dbid == 101)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 5219;
        cardrefrace = u8"zombie"s;
        return 1;
    }
    if (dbid == 257)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 8219;
        cardrefrace = u8"zombie"s;
        return 1;
    }
    if (dbid == 254)
    {
        cardreftype = 0;
        cardrefrare = 50;
        cardrefcost = 0;
        cardrefpic = 395;
        cardrefrace = u8"zombie"s;
        return 1;
    }
    if (dbid == 102)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 16220;
        cardrefrace = u8"goblin"s;
        return 1;
    }
    if (dbid == 103)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 5220;
        cardrefrace = u8"goblin"s;
        return 1;
    }
    if (dbid == 104)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 18220;
        cardrefrace = u8"goblin"s;
        return 1;
    }
    if (dbid == 105)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 4220;
        cardrefrace = u8"goblin"s;
        return 1;
    }
    if (dbid == 106)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 3221;
        cardrefrace = u8"ghost"s;
        return 1;
    }
    if (dbid == 107)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 4221;
        cardrefrace = u8"ghost"s;
        return 1;
    }
    if (dbid == 108)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 222;
        cardrefrace = u8"bear"s;
        return 1;
    }
    if (dbid == 109)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 3222;
        cardrefrace = u8"bear"s;
        return 1;
    }
    if (dbid == 344)
    {
        cardreftype = 0;
        cardrefrare = 50;
        cardrefcost = 0;
        cardrefpic = 439;
        cardrefrace = u8"bear"s;
        return 1;
    }
    if (dbid == 110)
    {
        cardreftype = 0;
        cardrefrare = 40;
        cardrefcost = 0;
        cardrefpic = 223;
        cardrefrace = u8"armor"s;
        return 1;
    }
    if (dbid == 111)
    {
        cardreftype = 0;
        cardrefrare = 30;
        cardrefcost = 0;
        cardrefpic = 17223;
        cardrefrace = u8"armor"s;
        return 1;
    }
    if (dbid == 112)
    {
        cardreftype = 0;
        cardrefrare = 30;
        cardrefcost = 0;
        cardrefpic = 5223;
        cardrefrace = u8"armor"s;
        return 1;
    }
    if (dbid == 113)
    {
        cardreftype = 0;
        cardrefrare = 30;
        cardrefcost = 0;
        cardrefpic = 16223;
        cardrefrace = u8"armor"s;
        return 1;
    }
    if (dbid == 114)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 224;
        cardrefrace = u8"medusa"s;
        return 1;
    }
    if (dbid == 115)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 5224;
        cardrefrace = u8"medusa"s;
        return 1;
    }
    if (dbid == 116)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 16224;
        cardrefrace = u8"medusa"s;
        return 1;
    }
    if (dbid == 117)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 225;
        cardrefrace = u8"cupid"s;
        return 1;
    }
    if (dbid == 118)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 226;
        cardrefrace = u8"phantom"s;
        return 1;
    }
    if (dbid == 248)
    {
        cardreftype = 0;
        cardrefrare = 50;
        cardrefcost = 0;
        cardrefpic = 389;
        cardrefrace = u8"dinosaur"s;
        return 1;
    }
    if (dbid == 119)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 227;
        cardrefrace = u8"harpy"s;
        return 1;
    }
    if (dbid == 120)
    {
        cardreftype = 0;
        cardrefrare = 30;
        cardrefcost = 0;
        cardrefpic = 19228;
        cardrefrace = u8"dragon"s;
        return 1;
    }
    if (dbid == 121)
    {
        cardreftype = 0;
        cardrefrare = 20;
        cardrefcost = 0;
        cardrefpic = 3228;
        cardrefrace = u8"dragon"s;
        return 1;
    }
    if (dbid == 122)
    {
        cardreftype = 0;
        cardrefrare = 20;
        cardrefcost = 0;
        cardrefpic = 228;
        cardrefrace = u8"dragon"s;
        return 1;
    }
    if (dbid == 123)
    {
        cardreftype = 0;
        cardrefrare = 20;
        cardrefcost = 0;
        cardrefpic = 5228;
        cardrefrace = u8"dragon"s;
        return 1;
    }
    if (dbid == 124)
    {
        cardreftype = 0;
        cardrefrare = 10;
        cardrefcost = 0;
        cardrefpic = 4228;
        cardrefrace = u8"dragon"s;
        return 1;
    }
    if (dbid == 125)
    {
        cardreftype = 0;
        cardrefrare = 10;
        cardrefcost = 0;
        cardrefpic = 18228;
        cardrefrace = u8"dragon"s;
        return 1;
    }
    if (dbid == 126)
    {
        cardreftype = 0;
        cardrefrare = 40;
        cardrefcost = 0;
        cardrefpic = 229;
        cardrefrace = u8"cerberus"s;
        return 1;
    }
    if (dbid == 255)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 396;
        cardrefrace = u8"centipede"s;
        return 1;
    }
    if (dbid == 256)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 3396;
        cardrefrace = u8"centipede"s;
        return 1;
    }
    if (dbid == 127)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 230;
        cardrefrace = u8"spider"s;
        return 1;
    }
    if (dbid == 128)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 19230;
        cardrefrace = u8"spider"s;
        return 1;
    }
    if (dbid == 129)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 17230;
        cardrefrace = u8"spider"s;
        return 1;
    }
    if (dbid == 130)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 5230;
        cardrefrace = u8"spider"s;
        return 1;
    }
    if (dbid == 131)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 16230;
        cardrefrace = u8"spider"s;
        return 1;
    }
    if (dbid == 132)
    {
        cardreftype = 0;
        cardrefrare = 40;
        cardrefcost = 0;
        cardrefpic = 6231;
        cardrefrace = u8"golem"s;
        return 1;
    }
    if (dbid == 133)
    {
        cardreftype = 0;
        cardrefrare = 40;
        cardrefcost = 0;
        cardrefpic = 231;
        cardrefrace = u8"golem"s;
        return 1;
    }
    if (dbid == 134)
    {
        cardreftype = 0;
        cardrefrare = 40;
        cardrefcost = 0;
        cardrefpic = 15231;
        cardrefrace = u8"golem"s;
        return 1;
    }
    if (dbid == 135)
    {
        cardreftype = 0;
        cardrefrare = 30;
        cardrefcost = 0;
        cardrefpic = 5231;
        cardrefrace = u8"golem"s;
        return 1;
    }
    if (dbid == 136)
    {
        cardreftype = 0;
        cardrefrare = 20;
        cardrefcost = 0;
        cardrefpic = 17231;
        cardrefrace = u8"golem"s;
        return 1;
    }
    if (dbid == 137)
    {
        cardreftype = 0;
        cardrefrare = 15;
        cardrefcost = 0;
        cardrefpic = 9231;
        cardrefrace = u8"golem"s;
        return 1;
    }
    if (dbid == 138)
    {
        cardreftype = 0;
        cardrefrare = 15;
        cardrefcost = 0;
        cardrefpic = 2231;
        cardrefrace = u8"golem"s;
        return 1;
    }
    if (dbid == 147)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 237;
        cardrefrace = u8"crab"s;
        return 1;
    }
    if (dbid == 148)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 239;
        cardrefrace = u8"centipede"s;
        return 1;
    }
    if (dbid == 149)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 240;
        cardrefrace = u8"goblin"s;
        return 1;
    }
    if (dbid == 150)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 241;
        cardrefrace = u8"skeleton"s;
        return 1;
    }
    if (dbid == 151)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 3241;
        cardrefrace = u8"skeleton"s;
        return 1;
    }
    if (dbid == 152)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 243;
        cardrefrace = u8"eulderna"s;
        return 1;
    }
    if (dbid == 153)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 244;
        cardrefrace = u8"piece"s;
        return 1;
    }
    if (dbid == 154)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 245;
        cardrefrace = u8"piece"s;
        return 1;
    }
    if (dbid == 155)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 246;
        cardrefrace = u8"piece"s;
        return 1;
    }
    if (dbid == 156)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 247;
        cardrefrace = u8"piece"s;
        return 1;
    }
    if (dbid == 157)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 248;
        cardrefrace = u8"piece"s;
        return 1;
    }
    if (dbid == 158)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 249;
        cardrefrace = u8"piece"s;
        return 1;
    }
    if (dbid == 159)
    {
        cardreftype = 0;
        cardrefrare = 25;
        cardrefcost = 0;
        cardrefpic = 159;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 160)
    {
        cardreftype = 0;
        cardrefrare = 25;
        cardrefcost = 0;
        cardrefpic = 57;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 161)
    {
        cardreftype = 0;
        cardrefrare = 25;
        cardrefcost = 0;
        cardrefpic = 100;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 302)
    {
        cardreftype = 0;
        cardrefrare = 25;
        cardrefcost = 0;
        cardrefpic = 150;
        cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 303)
    {
        cardreftype = 0;
        cardrefrare = 25;
        cardrefcost = 0;
        cardrefpic = 31;
        cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 304)
    {
        cardreftype = 0;
        cardrefrare = 25;
        cardrefcost = 0;
        cardrefpic = 158;
        cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 305)
    {
        cardreftype = 0;
        cardrefrare = 25;
        cardrefcost = 0;
        cardrefpic = 157;
        cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 162)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 250;
        cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 234)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 3250;
        cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 231)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 370;
        cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 232)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 373;
        cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 233)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 377;
        cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 235)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 4377;
        cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 163)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 251;
        cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 164)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 253;
        cardrefrace = u8"cat"s;
        return 1;
    }
    if (dbid == 246)
    {
        cardreftype = 0;
        cardrefrare = 1;
        cardrefcost = 0;
        cardrefpic = 387;
        cardrefrace = u8"cat"s;
        return 1;
    }
    if (dbid == 332)
    {
        cardreftype = 0;
        cardrefrare = 10;
        cardrefcost = 0;
        cardrefpic = 6387;
        cardrefrace = u8"cat"s;
        return 1;
    }
    if (dbid == 229)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 368;
        cardrefrace = u8"cat"s;
        return 1;
    }
    if (dbid == 230)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 369;
        cardrefrace = u8"catgod"s;
        return 1;
    }
    if (dbid == 228)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 367;
        cardrefrace = u8"cat"s;
        return 1;
    }
    if (dbid == 165)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 254;
        cardrefrace = u8"dog"s;
        return 1;
    }
    if (dbid == 225)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 364;
        cardrefrace = u8"dog"s;
        return 1;
    }
    if (dbid == 226)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 365;
        cardrefrace = u8"roran"s;
        return 1;
    }
    if (dbid == 227)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 366;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 166)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 4;
        cardrefrace = u8"roran"s;
        return 1;
    }
    if (dbid == 167)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 6255;
        cardrefrace = u8"rat"s;
        return 1;
    }
    if (dbid == 168)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 256;
        cardrefrace = u8"shell"s;
        return 1;
    }
    if (dbid == 170)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 258;
        cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 175)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 348;
        cardrefrace = u8"catgod"s;
        return 1;
    }
    if (dbid == 176)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 105;
        cardrefrace = u8"roran"s;
        return 1;
    }
    if (dbid == 249)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 105;
        cardrefrace = u8"roran"s;
        return 1;
    }
    if (dbid == 210)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 354;
        cardrefrace = u8"catsister"s;
        return 1;
    }
    if (dbid == 211)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 355;
        cardrefrace = u8"roran"s;
        return 1;
    }
    if (dbid == 177)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 349;
        cardrefrace = u8"machinegod"s;
        return 1;
    }
    if (dbid == 178)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 3339;
        cardrefrace = u8"undeadgod"s;
        return 1;
    }
    if (dbid == 179)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 350;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 208)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 352;
        cardrefrace = u8"dwarf"s;
        return 1;
    }
    if (dbid == 209)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 353;
        cardrefrace = u8"dwarf"s;
        return 1;
    }
    if (dbid == 180)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 259;
        cardrefrace = u8"cat"s;
        return 1;
    }
    if (dbid == 181)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 260;
        cardrefrace = u8"hound"s;
        return 1;
    }
    if (dbid == 182)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 208;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 183)
    {
        cardreftype = 0;
        cardrefrare = 20;
        cardrefcost = 0;
        cardrefpic = 71;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 184)
    {
        cardreftype = 0;
        cardrefrare = 40;
        cardrefcost = 0;
        cardrefpic = 73;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 185)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 122;
        cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 350)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 1477;
        cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 186)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 270;
        cardrefrace = u8"machine"s;
        return 1;
    }
    if (dbid == 187)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 17270;
        cardrefrace = u8"machine"s;
        return 1;
    }
    if (dbid == 188)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 3270;
        cardrefrace = u8"machine"s;
        return 1;
    }
    if (dbid == 345)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 470;
        cardrefrace = u8"bike"s;
        return 1;
    }
    if (dbid == 346)
    {
        cardreftype = 0;
        cardrefrare = 5;
        cardrefcost = 0;
        cardrefpic = 471;
        cardrefrace = u8"bike"s;
        return 1;
    }
    if (dbid == 341)
    {
        cardreftype = 0;
        cardrefrare = 25;
        cardrefcost = 0;
        cardrefpic = 434;
        cardrefrace = u8"machine"s;
        return 1;
    }
    if (dbid == 258)
    {
        cardreftype = 0;
        cardrefrare = 50;
        cardrefcost = 0;
        cardrefpic = 198;
        cardrefrace = u8"machine"s;
        return 1;
    }
    if (dbid == 189)
    {
        cardreftype = 0;
        cardrefrare = 60;
        cardrefcost = 0;
        cardrefpic = 271;
        cardrefrace = u8"eye"s;
        return 1;
    }
    if (dbid == 190)
    {
        cardreftype = 0;
        cardrefrare = 60;
        cardrefcost = 0;
        cardrefpic = 3271;
        cardrefrace = u8"eye"s;
        return 1;
    }
    if (dbid == 191)
    {
        cardreftype = 0;
        cardrefrare = 50;
        cardrefcost = 0;
        cardrefpic = 272;
        cardrefrace = u8"wisp"s;
        return 1;
    }
    if (dbid == 192)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 273;
        cardrefrace = u8"crab"s;
        return 1;
    }
    if (dbid == 193)
    {
        cardreftype = 0;
        cardrefrare = 70;
        cardrefcost = 0;
        cardrefpic = 17273;
        cardrefrace = u8"crab"s;
        return 1;
    }
    if (dbid == 195)
    {
        cardreftype = 0;
        cardrefrare = 30;
        cardrefcost = 0;
        cardrefpic = 274;
        cardrefrace = u8"chicken"s;
        return 1;
    }
    if (dbid == 196)
    {
        cardreftype = 0;
        cardrefrare = 60;
        cardrefcost = 0;
        cardrefpic = 275;
        cardrefrace = u8"mandrake"s;
        return 1;
    }
    if (dbid == 201)
    {
        cardreftype = 0;
        cardrefrare = 20;
        cardrefcost = 0;
        cardrefpic = 5275;
        cardrefrace = u8"mandrake"s;
        return 1;
    }
    if (dbid == 197)
    {
        cardreftype = 0;
        cardrefrare = 60;
        cardrefcost = 0;
        cardrefpic = 4275;
        cardrefrace = u8"mandrake"s;
        return 1;
    }
    if (dbid == 198)
    {
        cardreftype = 0;
        cardrefrare = 60;
        cardrefcost = 0;
        cardrefpic = 3275;
        cardrefrace = u8"mandrake"s;
        return 1;
    }
    if (dbid == 199)
    {
        cardreftype = 0;
        cardrefrare = 30;
        cardrefcost = 0;
        cardrefpic = 276;
        cardrefrace = u8"stalker"s;
        return 1;
    }
    if (dbid == 200)
    {
        cardreftype = 0;
        cardrefrare = 30;
        cardrefcost = 0;
        cardrefpic = 3276;
        cardrefrace = u8"stalker"s;
        return 1;
    }
    if (dbid == 202)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 351;
        cardrefrace = u8"giant"s;
        return 1;
    }
    if (dbid == 203)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 23;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 205)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 104;
        cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 207)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 351;
        cardrefrace = u8"giant"s;
        return 1;
    }
    if (dbid == 212)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 117;
        cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 213)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 356;
        cardrefrace = u8"roran"s;
        return 1;
    }
    if (dbid == 221)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 358;
        cardrefrace = u8"roran"s;
        return 1;
    }
    if (dbid == 222)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 359;
        cardrefrace = u8"roran"s;
        return 1;
    }
    if (dbid == 223)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 361;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 224)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 362;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 243)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 383;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 247)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 388;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 252)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 392;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 253)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 394;
        cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 259)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 199;
        cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 301)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 403;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 214)
    {
        cardreftype = 0;
        cardrefrare = 30;
        cardrefcost = 0;
        cardrefpic = 166;
        cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 215)
    {
        cardreftype = 0;
        cardrefrare = 30;
        cardrefcost = 0;
        cardrefpic = 3166;
        cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 217)
    {
        cardreftype = 0;
        cardrefrare = 30;
        cardrefcost = 0;
        cardrefpic = 4166;
        cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 216)
    {
        cardreftype = 0;
        cardrefrare = 20;
        cardrefcost = 0;
        cardrefpic = 429;
        cardrefrace = u8"yith"s;
        return 1;
    }
    if (dbid == 218)
    {
        cardreftype = 0;
        cardrefrare = 40;
        cardrefcost = 0;
        cardrefpic = 277;
        cardrefrace = u8"yith"s;
        return 1;
    }
    if (dbid == 219)
    {
        cardreftype = 0;
        cardrefrare = 80;
        cardrefcost = 0;
        cardrefpic = 278;
        cardrefrace = u8"orc"s;
        return 1;
    }
    if (dbid == 220)
    {
        cardreftype = 0;
        cardrefrare = 30;
        cardrefcost = 0;
        cardrefpic = 430;
        cardrefrace = u8"yith"s;
        return 1;
    }
    if (dbid == 250)
    {
        cardreftype = 0;
        cardrefrare = 50;
        cardrefcost = 0;
        cardrefpic = 390;
        cardrefrace = u8"fairy"s;
        return 1;
    }
    if (dbid == 260)
    {
        cardreftype = 0;
        cardrefrare = 50;
        cardrefcost = 0;
        cardrefpic = 211;
        cardrefrace = u8"servant"s;
        return 1;
    }
    if (dbid == 261)
    {
        cardreftype = 0;
        cardrefrare = 50;
        cardrefcost = 0;
        cardrefpic = 217;
        cardrefrace = u8"servant"s;
        return 1;
    }
    if (dbid == 262)
    {
        cardreftype = 0;
        cardrefrare = 50;
        cardrefcost = 0;
        cardrefpic = 218;
        cardrefrace = u8"servant"s;
        return 1;
    }
    if (dbid == 263)
    {
        cardreftype = 0;
        cardrefrare = 50;
        cardrefcost = 0;
        cardrefpic = 236;
        cardrefrace = u8"servant"s;
        return 1;
    }
    if (dbid == 264)
    {
        cardreftype = 0;
        cardrefrare = 50;
        cardrefcost = 0;
        cardrefpic = 269;
        cardrefrace = u8"servant"s;
        return 1;
    }
    if (dbid == 265)
    {
        cardreftype = 0;
        cardrefrare = 50;
        cardrefcost = 0;
        cardrefpic = 267;
        cardrefrace = u8"servant"s;
        return 1;
    }
    if (dbid == 266)
    {
        cardreftype = 0;
        cardrefrare = 50;
        cardrefcost = 0;
        cardrefpic = 242;
        cardrefrace = u8"servant"s;
        return 1;
    }
    if (dbid == 267)
    {
        cardreftype = 0;
        cardrefrare = 10;
        cardrefcost = 0;
        cardrefpic = 17262;
        cardrefrace = u8"horse"s;
        return 1;
    }
    if (dbid == 276)
    {
        cardreftype = 0;
        cardrefrare = 10;
        cardrefcost = 0;
        cardrefpic = 6262;
        cardrefrace = u8"horse"s;
        return 1;
    }
    if (dbid == 275)
    {
        cardreftype = 0;
        cardrefrare = 10;
        cardrefcost = 0;
        cardrefpic = 15262;
        cardrefrace = u8"horse"s;
        return 1;
    }
    if (dbid == 268)
    {
        cardreftype = 0;
        cardrefrare = 10;
        cardrefcost = 0;
        cardrefpic = 16262;
        cardrefrace = u8"horse"s;
        return 1;
    }
    if (dbid == 277)
    {
        cardreftype = 0;
        cardrefrare = 10;
        cardrefcost = 0;
        cardrefpic = 10262;
        cardrefrace = u8"horse"s;
        return 1;
    }
    if (dbid == 278)
    {
        cardreftype = 0;
        cardrefrare = 70;
        cardrefcost = 0;
        cardrefpic = 191;
        cardrefrace = u8"mutant"s;
        return 1;
    }
    if (dbid == 279)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 263;
        cardrefrace = u8"yerles"s;
        return 1;
    }
    if (dbid == 280)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 192;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 288)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 193;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 290)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 196;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 292)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 197;
        cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 294)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 196;
        cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 291)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 80;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 297)
    {
        cardreftype = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = 196;
        cardrefrace = u8"norland"s;
        return 1;
    }
    if (dbid == 317)
    {
        cardreftype = 0;
        cardrefrare = 50;
        cardrefcost = 0;
        cardrefpic = 279;
        cardrefrace = u8"roran"s;
        return 1;
    }
    if (dbid == 318)
    {
        cardreftype = 0;
        cardrefrare = 50;
        cardrefcost = 0;
        cardrefpic = 408;
        cardrefrace = u8"machinegod"s;
        return 1;
    }
    if (dbid == 319)
    {
        cardreftype = 0;
        cardrefrare = 50;
        cardrefcost = 0;
        cardrefpic = 409;
        cardrefrace = u8"mutant"s;
        return 1;
    }
    if (dbid == 322)
    {
        cardreftype = 0;
        cardrefrare = 50;
        cardrefcost = 0;
        cardrefpic = 412;
        cardrefrace = u8"roran"s;
        return 1;
    }
    if (dbid == 334)
    {
        cardreftype = 0;
        cardrefrare = 50;
        cardrefcost = 0;
        cardrefpic = 416;
        cardrefrace = u8"juere"s;
        return 1;
    }
    if (dbid == 323)
    {
        cardreftype = 0;
        cardrefrare = 10;
        cardrefcost = 0;
        cardrefpic = 280;
        cardrefrace = u8"ghost"s;
        return 1;
    }
    if (dbid == 324)
    {
        cardreftype = 0;
        cardrefrare = 15;
        cardrefcost = 0;
        cardrefpic = 19281;
        cardrefrace = u8"quickling"s;
        return 1;
    }
    if (dbid == 325)
    {
        cardreftype = 0;
        cardrefrare = 15;
        cardrefcost = 0;
        cardrefpic = 5281;
        cardrefrace = u8"quickling"s;
        return 1;
    }
    if (dbid == 328)
    {
        cardreftype = 0;
        cardrefrare = 2;
        cardrefcost = 0;
        cardrefpic = 252;
        cardrefrace = u8"metal"s;
        return 1;
    }
    if (dbid == 329)
    {
        cardreftype = 0;
        cardrefrare = 5;
        cardrefcost = 0;
        cardrefpic = 5252;
        cardrefrace = u8"metal"s;
        return 1;
    }
    if (dbid == 330)
    {
        cardreftype = 0;
        cardrefrare = 40;
        cardrefcost = 0;
        cardrefpic = 17283;
        cardrefrace = u8"dinosaur"s;
        return 1;
    }
    if (dbid == 502)
    {
        cardreftype = 30;
        cardrefdomain = 1;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = -1;
        cardrefrace = "";
        return 1;
    }
    if (dbid == 503)
    {
        cardreftype = 30;
        cardrefdomain = 1;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = -2;
        cardrefrace = "";
        return 1;
    }
    if (dbid == 500)
    {
        cardreftype = 30;
        cardrefdomain = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = -3;
        cardrefrace = "";
        return 1;
    }
    if (dbid == 501)
    {
        cardreftype = 30;
        cardrefdomain = 0;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = -4;
        cardrefrace = "";
        return 1;
    }
    if (dbid == 504)
    {
        cardreftype = 30;
        cardrefdomain = 2;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = -5;
        cardrefrace = "";
        return 1;
    }
    if (dbid == 505)
    {
        cardreftype = 30;
        cardrefdomain = 2;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = -6;
        cardrefrace = "";
        return 1;
    }
    if (dbid == 506)
    {
        cardreftype = 30;
        cardrefdomain = 3;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = -7;
        cardrefrace = "";
        return 1;
    }
    if (dbid == 507)
    {
        cardreftype = 30;
        cardrefdomain = 3;
        cardrefrare = 100;
        cardrefcost = 0;
        cardrefpic = -8;
        cardrefrace = "";
        return 1;
    }
    if (dbid == 508)
    {
        cardreftype = 20;
        cardrefskill = 2;
        cardrefdomain = 0;
        cardrefrare = 80;
        cardrefcost = 3;
        cardrefpic = -22;
        cardrefrace = "";
        return 1;
    }
    if (dbid == 509)
    {
        cardreftype = 20;
        cardrefskill = 3;
        cardrefdomain = 0;
        cardrefrare = 70;
        cardrefcost = 2;
        cardrefpic = -23;
        cardrefrace = "";
        return 1;
    }
    return 0;
}



} // namespace elona
