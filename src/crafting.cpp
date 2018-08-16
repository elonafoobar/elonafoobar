#include "crafting.hpp"
#include "ability.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "config.hpp"
#include "draw.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "macro.hpp"
#include "random.hpp"
#include "ui.hpp"
#include "variables.hpp"

#include "ui/ui_menu_crafting.hpp"

namespace elona
{

int matid = 0;
elona_vector1<int> matval;

void initialize_craft_material_data()
{
    DIM2(matval, 4);
    DIM3(matref, 5, 400);
    DIM3(matspot, 5, 400);
    SDIM3(matname, 40, 400);
    SDIM3(matdesc, 80, 400);

    for (int cnt = 0; cnt < 55; cnt++)
    {
        matname(cnt) =
            i18n::s.get_enum_property("core.locale.material", "name", cnt);
        matdesc(cnt) =
            i18n::s.get_enum_property("core.locale.material", "desc", cnt);
    }

    matref(0, 0) = 0;
    matref(1, 0) = 1;
    matref(2, 0) = 240;
    matspot(0, 0) = 18;

    matref(0, 1) = 1;
    matref(1, 1) = 80;
    matref(2, 1) = 434;
    matspot(0, 1) = 18;

    matref(0, 40) = 1;
    matref(1, 40) = 200;
    matref(2, 40) = 437;
    matspot(0, 40) = 18;

    matref(0, 41) = 1;
    matref(1, 41) = 1000;
    matref(2, 41) = 437;
    matspot(0, 41) = 18;

    matref(0, 43) = 1;
    matref(1, 43) = 20;
    matref(2, 43) = 470;
    matspot(0, 43) = 18;

    matref(0, 2) = 1;
    matref(1, 2) = 10;
    matref(2, 2) = 239;
    matspot(0, 2) = 18;

    matref(0, 3) = 1;
    matref(1, 3) = 10;
    matref(2, 3) = 239;
    matspot(0, 3) = 18;

    matref(0, 48) = 1;
    matref(1, 48) = 10;
    matref(2, 48) = 209;
    matspot(0, 48) = 18;

    matref(0, 6) = 1;
    matref(1, 6) = 70;
    matref(2, 6) = 239;
    matspot(0, 6) = 18;

    matref(0, 45) = 3;
    matref(1, 45) = 20;
    matref(2, 45) = 155;
    matspot(0, 45) = 18;

    matref(0, 38) = 4;
    matref(1, 38) = 30;
    matref(2, 38) = 8;
    matspot(0, 38) = 18;

    matref(0, 30) = 10;
    matref(1, 30) = 150;
    matref(2, 30) = 7;
    matspot(0, 30) = 18;

    matref(0, 23) = 12;
    matref(1, 23) = 20;
    matref(2, 23) = 7;
    matspot(0, 23) = 18;

    matref(0, 44) = 25;
    matref(1, 44) = 150;
    matref(2, 44) = 7;
    matspot(0, 44) = 18;

    matref(0, 50) = 1;
    matref(1, 50) = 30;
    matref(2, 50) = 209;
    matspot(0, 50) = 9;

    matref(0, 46) = 2;
    matref(1, 46) = 20;
    matref(2, 46) = 239;
    matspot(0, 46) = 10;

    matref(0, 33) = 4;
    matref(1, 33) = 20;
    matref(2, 33) = 155;
    matspot(0, 33) = 10;

    matref(0, 53) = 6;
    matref(1, 53) = 20;
    matref(2, 53) = 202;
    matspot(0, 53) = 10;

    matref(0, 47) = 10;
    matref(1, 47) = 20;
    matref(2, 47) = 239;
    matspot(0, 47) = 10;

    matref(0, 37) = 12;
    matref(1, 37) = 60;
    matref(2, 37) = 471;
    matspot(0, 37) = 10;

    matref(0, 54) = 1;
    matref(1, 54) = 50;
    matref(2, 54) = 354;
    matspot(0, 54) = 12;

    matref(0, 49) = 5;
    matref(1, 49) = 50;
    matref(2, 49) = 150;
    matspot(0, 49) = 12;

    matref(0, 35) = 8;
    matref(1, 35) = 40;
    matref(2, 35) = 470;
    matspot(0, 35) = 12;

    matref(0, 36) = 8;
    matref(1, 36) = 40;
    matref(2, 36) = 354;
    matspot(0, 36) = 12;

    matref(0, 12) = 1;
    matref(1, 12) = 10;
    matref(2, 12) = 354;
    matspot(0, 12) = 13;

    matref(0, 5) = 1;
    matref(1, 5) = 10;
    matref(2, 5) = 354;
    matspot(0, 5) = 13;

    matref(0, 10) = 4;
    matref(1, 10) = 50;
    matref(2, 10) = 354;
    matspot(0, 10) = 13;

    matref(0, 25) = 4;
    matref(1, 25) = 20;
    matref(2, 25) = 354;
    matspot(0, 25) = 13;

    matref(0, 11) = 8;
    matref(1, 11) = 30;
    matref(2, 11) = 354;
    matspot(0, 11) = 13;

    matref(0, 20) = 12;
    matref(1, 20) = 15;
    matref(2, 20) = 7;
    matspot(0, 20) = 13;

    matref(0, 7) = 1;
    matref(1, 7) = 40;
    matref(2, 7) = 209;
    matspot(0, 7) = 14;

    matref(0, 9) = 1;
    matref(1, 9) = 10;
    matref(2, 9) = 209;
    matspot(0, 9) = 14;

    matref(0, 26) = 5;
    matref(1, 26) = 10;
    matref(2, 26) = 209;
    matspot(0, 26) = 14;

    matref(0, 27) = 5;
    matref(1, 27) = 10;
    matref(2, 27) = 209;
    matspot(0, 27) = 14;

    matref(0, 28) = 5;
    matref(1, 28) = 10;
    matref(2, 28) = 209;
    matspot(0, 28) = 14;

    matref(0, 52) = 8;
    matref(1, 52) = 50;
    matref(2, 52) = 209;
    matspot(0, 52) = 14;

    matref(0, 8) = 10;
    matref(1, 8) = 40;
    matref(2, 8) = 209;
    matspot(0, 8) = 14;

    matref(0, 22) = 20;
    matref(1, 22) = 100;
    matref(2, 22) = 209;
    matspot(0, 22) = 14;

    matref(0, 51) = 40;
    matref(1, 51) = 200;
    matref(2, 51) = 209;
    matspot(0, 51) = 14;

    matref(0, 13) = 1;
    matref(1, 13) = 10;
    matref(2, 13) = 170;
    matspot(0, 13) = 15;

    matref(0, 14) = 1;
    matref(1, 14) = 20;
    matref(2, 14) = 170;
    matspot(0, 14) = 15;

    matref(0, 15) = 1;
    matref(1, 15) = 20;
    matref(2, 15) = 170;
    matspot(0, 15) = 15;

    matref(0, 16) = 1;
    matref(1, 16) = 10;
    matref(2, 16) = 170;
    matspot(0, 16) = 15;

    matref(0, 42) = 3;
    matref(1, 42) = 20;
    matref(2, 42) = 170;
    matspot(0, 42) = 15;

    matref(0, 29) = 7;
    matref(1, 29) = 50;
    matref(2, 29) = 170;
    matspot(0, 29) = 15;

    matref(0, 17) = 12;
    matref(1, 17) = 20;
    matref(2, 17) = 170;
    matspot(0, 17) = 15;

    matref(0, 24) = 15;
    matref(1, 24) = 40;
    matref(2, 24) = 8;
    matspot(0, 24) = 15;

    matref(0, 34) = 25;
    matref(1, 34) = 200;
    matref(2, 34) = 354;
    matspot(0, 34) = 15;

    matspot(1, 34) = 10;
    matref(0, 4) = 1;
    matref(1, 4) = 10;
    matref(2, 4) = 436;
    matspot(0, 4) = 16;

    matref(0, 18) = 1;
    matref(1, 18) = 80;
    matref(2, 18) = 301;
    matspot(0, 18) = 16;

    matref(0, 31) = 1;
    matref(1, 31) = 20;
    matref(2, 31) = 304;
    matspot(0, 31) = 16;

    matref(0, 39) = 3;
    matref(1, 39) = 20;
    matref(2, 39) = 301;
    matspot(0, 39) = 16;

    matref(0, 19) = 5;
    matref(1, 19) = 15;
    matref(2, 19) = 304;
    matspot(0, 19) = 16;

    matref(0, 32) = 8;
    matref(1, 32) = 40;
    matref(2, 32) = 304;
    matspot(0, 32) = 16;

    matref(0, 21) = 15;
    matref(1, 21) = 45;
    matref(2, 21) = 209;
    matspot(0, 21) = 16;
}



int get_required_craft_materials()
{
    matneed(0) = -1;
    matneed(1) = -1;
    matneed(2) = -1;
    matneed(3) = -1;
    matneed(4) = -1;
    matneed(5) = -1;
    matneed(6) = -1;
    matneed(7) = -1;
    matneed(8) = -1;
    matneed(9) = -1;
    if (matid == 502)
    {
        matval(0) = 179;
        matval(1) = 40;
        matval(2) = 100;
        matneed(0) = 35;
        matneed(1) = 2;
        matneed(2) = 44;
        matneed(3) = 2;
        matneed(4) = 51;
        matneed(5) = 2;
        return 1;
    }
    if (matid == 501)
    {
        matval(0) = 179;
        matval(1) = 13;
        matval(2) = 100;
        matneed(0) = 43;
        matneed(1) = 2;
        matneed(2) = 44;
        matneed(3) = 1;
        return 1;
    }
    if (matid == 500)
    {
        matval(0) = 179;
        matval(1) = 1;
        matval(2) = 100;
        matneed(0) = 43;
        matneed(1) = 2;
        matneed(2) = 38;
        matneed(3) = 1;
        return 1;
    }
    if (matid == 455)
    {
        matval(0) = 177;
        matval(1) = 1;
        matval(2) = 100;
        matneed(0) = 45;
        matneed(1) = 4;
        matneed(2) = 53;
        matneed(3) = 2;
        matneed(4) = 7;
        matneed(5) = 3;
        return 1;
    }
    if (matid == 411)
    {
        matval(0) = 179;
        matval(1) = 5;
        matval(2) = 100;
        matneed(0) = 43;
        matneed(1) = 4;
        matneed(2) = 36;
        matneed(3) = 1;
        matneed(4) = 23;
        matneed(5) = 2;
        return 1;
    }
    if (matid == 408)
    {
        matval(0) = 176;
        matval(1) = 11;
        matval(2) = 100;
        matneed(0) = 47;
        matneed(1) = 3;
        matneed(2) = 52;
        matneed(3) = 2;
        matneed(4) = 21;
        matneed(5) = 1;
        return 1;
    }
    if (matid == 407)
    {
        matval(0) = 178;
        matval(1) = 14;
        matval(2) = 100;
        matneed(0) = 25;
        matneed(1) = 4;
        matneed(2) = 20;
        matneed(3) = 3;
        matneed(4) = 42;
        matneed(5) = 1;
        return 1;
    }
    if (matid == 405)
    {
        matval(0) = 176;
        matval(1) = 15;
        matval(2) = 100;
        matneed(0) = 48;
        matneed(1) = 8;
        matneed(2) = 9;
        matneed(3) = 5;
        matneed(4) = 52;
        matneed(5) = 2;
        return 1;
    }
    if (matid == 403)
    {
        matval(0) = 176;
        matval(1) = 12;
        matval(2) = 100;
        matneed(0) = 47;
        matneed(1) = 5;
        matneed(2) = 16;
        matneed(3) = 2;
        matneed(4) = 10;
        matneed(5) = 1;
        return 1;
    }
    if (matid == 402)
    {
        matval(0) = 177;
        matval(1) = 5;
        matval(2) = 100;
        matneed(0) = 53;
        matneed(1) = 7;
        matneed(2) = 45;
        matneed(3) = 4;
        return 1;
    }
    if (matid == 401)
    {
        matval(0) = 179;
        matval(1) = 14;
        matval(2) = 100;
        matneed(0) = 3;
        matneed(1) = 8;
        matneed(2) = 53;
        matneed(3) = 4;
        matneed(4) = 21;
        matneed(5) = 1;
        return 1;
    }
    if (matid == 400)
    {
        matval(0) = 176;
        matval(1) = 8;
        matval(2) = 100;
        matneed(0) = 3;
        matneed(1) = 6;
        matneed(2) = 46;
        matneed(3) = 4;
        matneed(4) = 2;
        matneed(5) = 4;
        return 1;
    }
    if (matid == 399)
    {
        matval(0) = 177;
        matval(1) = 8;
        matval(2) = 100;
        matneed(0) = 45;
        matneed(1) = 5;
        matneed(2) = 33;
        matneed(3) = 2;
        matneed(4) = 20;
        matneed(5) = 2;
        return 1;
    }
    if (matid == 395)
    {
        matval(0) = 179;
        matval(1) = 30;
        matval(2) = 100;
        matneed(0) = 43;
        matneed(1) = 5;
        matneed(2) = 30;
        matneed(3) = 1;
        matneed(4) = 44;
        matneed(5) = 1;
        return 1;
    }
    if (matid == 390)
    {
        matval(0) = 179;
        matval(1) = 25;
        matval(2) = 100;
        matneed(0) = 35;
        matneed(1) = 1;
        matneed(2) = 36;
        matneed(3) = 2;
        matneed(4) = 30;
        matneed(5) = 2;
        return 1;
    }
    if (matid == 389)
    {
        matval(0) = 179;
        matval(1) = 25;
        matval(2) = 100;
        matneed(0) = 35;
        matneed(1) = 2;
        matneed(2) = 36;
        matneed(3) = 2;
        matneed(4) = 17;
        matneed(5) = 4;
        return 1;
    }
    if (matid == 388)
    {
        matval(0) = 179;
        matval(1) = 15;
        matval(2) = 100;
        matneed(0) = 35;
        matneed(1) = 1;
        matneed(2) = 17;
        matneed(3) = 2;
        matneed(4) = 23;
        matneed(5) = 3;
        return 1;
    }
    if (matid == 384)
    {
        matval(0) = 179;
        matval(1) = 15;
        matval(2) = 100;
        matneed(0) = 35;
        matneed(1) = 2;
        matneed(2) = 17;
        matneed(3) = 4;
        matneed(4) = 16;
        matneed(5) = 4;
        return 1;
    }
    if (matid == 362)
    {
        matval(0) = 179;
        matval(1) = 18;
        matval(2) = 100;
        matneed(0) = 35;
        matneed(1) = 1;
        matneed(2) = 49;
        matneed(3) = 2;
        matneed(4) = 30;
        matneed(5) = 1;
        return 1;
    }
    if (matid == 287)
    {
        matval(0) = 178;
        matval(1) = 45;
        matval(2) = 100;
        matneed(0) = 34;
        matneed(1) = 2;
        matneed(2) = 10;
        matneed(3) = 5;
        matneed(4) = 25;
        matneed(5) = 4;
        return 1;
    }
    if (matid == 286)
    {
        matval(0) = 178;
        matval(1) = 8;
        matval(2) = 100;
        matneed(0) = 25;
        matneed(1) = 4;
        matneed(2) = 14;
        matneed(3) = 4;
        return 1;
    }
    if (matid == 285)
    {
        matval(0) = 178;
        matval(1) = 8;
        matval(2) = 100;
        matneed(0) = 25;
        matneed(1) = 4;
        matneed(2) = 15;
        matneed(3) = 4;
        return 1;
    }
    if (matid == 253)
    {
        matval(0) = 178;
        matval(1) = 1;
        matval(2) = 100;
        matneed(0) = 5;
        matneed(1) = 4;
        return 1;
    }
    if (matid == 245)
    {
        matval(0) = 179;
        matval(1) = 1;
        matval(2) = 100;
        matneed(0) = 43;
        matneed(1) = 2;
        matneed(2) = 2;
        matneed(3) = 2;
        matneed(4) = 4;
        matneed(5) = 2;
        return 1;
    }
    if (matid == 242)
    {
        matval(0) = 179;
        matval(1) = 10;
        matval(2) = 100;
        matneed(0) = 35;
        matneed(1) = 1;
        matneed(2) = 36;
        matneed(3) = 1;
        matneed(4) = 23;
        matneed(5) = 3;
        return 1;
    }
    if (matid == 236)
    {
        matval(0) = 179;
        matval(1) = 4;
        matval(2) = 100;
        matneed(0) = 43;
        matneed(1) = 3;
        matneed(2) = 13;
        matneed(3) = 2;
        matneed(4) = 2;
        matneed(5) = 2;
        return 1;
    }
    if (matid == 209)
    {
        matval(0) = 179;
        matval(1) = 8;
        matval(2) = 100;
        matneed(0) = 43;
        matneed(1) = 4;
        matneed(2) = 17;
        matneed(3) = 2;
        matneed(4) = 16;
        matneed(5) = 2;
        return 1;
    }
    if (matid == 175)
    {
        matval(0) = 176;
        matval(1) = 17;
        matval(2) = 100;
        matneed(0) = 37;
        matneed(1) = 1;
        matneed(2) = 28;
        matneed(3) = 5;
        matneed(4) = 54;
        matneed(5) = 1;
        return 1;
    }
    if (matid == 123)
    {
        matval(0) = 176;
        matval(1) = 14;
        matval(2) = 100;
        matneed(0) = 37;
        matneed(1) = 1;
        matneed(2) = 26;
        matneed(3) = 5;
        matneed(4) = 50;
        matneed(5) = 2;
        return 1;
    }
    if (matid == 122)
    {
        matval(0) = 176;
        matval(1) = 14;
        matval(2) = 100;
        matneed(0) = 37;
        matneed(1) = 1;
        matneed(2) = 27;
        matneed(3) = 5;
        matneed(4) = 20;
        matneed(5) = 5;
        return 1;
    }
    if (matid == 120)
    {
        matval(0) = 176;
        matval(1) = 1;
        matval(2) = 100;
        matneed(0) = 6;
        matneed(1) = 1;
        matneed(2) = 9;
        matneed(3) = 4;
        matneed(4) = 50;
        matneed(5) = 2;
        return 1;
    }
    if (matid == 119)
    {
        matval(0) = 176;
        matval(1) = 1;
        matval(2) = 100;
        matneed(0) = 6;
        matneed(1) = 1;
        matneed(2) = 14;
        matneed(3) = 4;
        matneed(4) = 54;
        matneed(5) = 1;
        return 1;
    }
    if (matid == 76)
    {
        matval(0) = 178;
        matval(1) = 40;
        matval(2) = 100;
        matneed(0) = 34;
        matneed(1) = 2;
        matneed(2) = 5;
        matneed(3) = 5;
        matneed(4) = 42;
        matneed(5) = 4;
        return 1;
    }
    if (matid == 75)
    {
        matval(0) = 178;
        matval(1) = 30;
        matval(2) = 100;
        matneed(0) = 34;
        matneed(1) = 1;
        matneed(2) = 25;
        matneed(3) = 4;
        matneed(4) = 14;
        matneed(5) = 5;
        return 1;
    }
    if (matid == 74)
    {
        matval(0) = 178;
        matval(1) = 25;
        matval(2) = 100;
        matneed(0) = 15;
        matneed(1) = 3;
        matneed(2) = 25;
        matneed(3) = 4;
        matneed(4) = 42;
        matneed(5) = 3;
        return 1;
    }
    if (matid == 72)
    {
        matval(0) = 178;
        matval(1) = 20;
        matval(2) = 100;
        matneed(0) = 10;
        matneed(1) = 1;
        matneed(2) = 5;
        matneed(3) = 4;
        matneed(4) = 42;
        matneed(5) = 2;
        return 1;
    }
    if (matid == 71)
    {
        matval(0) = 178;
        matval(1) = 15;
        matval(2) = 100;
        matneed(0) = 25;
        matneed(1) = 3;
        matneed(2) = 42;
        matneed(3) = 2;
        return 1;
    }
    if (matid == 70)
    {
        matval(0) = 178;
        matval(1) = 10;
        matval(2) = 100;
        matneed(0) = 25;
        matneed(1) = 3;
        matneed(2) = 14;
        matneed(3) = 1;
        matneed(4) = 15;
        matneed(5) = 1;
        return 1;
    }
    if (matid == 69)
    {
        matval(0) = 178;
        matval(1) = 5;
        matval(2) = 100;
        matneed(0) = 5;
        matneed(1) = 3;
        matneed(2) = 15;
        matneed(3) = 2;
        return 1;
    }
    if (matid == 68)
    {
        matval(0) = 178;
        matval(1) = 1;
        matval(2) = 100;
        matneed(0) = 5;
        matneed(1) = 3;
        matneed(2) = 14;
        matneed(3) = 1;
        return 1;
    }
    if (matid == 66)
    {
        matval(0) = 177;
        matval(1) = 8;
        matval(2) = 100;
        matneed(0) = 33;
        matneed(1) = 4;
        matneed(2) = 39;
        matneed(3) = 5;
        matneed(4) = 18;
        matneed(5) = 2;
        return 1;
    }
    if (matid == 65)
    {
        matval(0) = 177;
        matval(1) = 10;
        matval(2) = 100;
        matneed(0) = 33;
        matneed(1) = 5;
        matneed(2) = 54;
        matneed(3) = 3;
        matneed(4) = 31;
        matneed(5) = 6;
        return 1;
    }
    if (matid == 19)
    {
        matval(0) = 176;
        matval(1) = 5;
        matval(2) = 100;
        matneed(0) = 6;
        matneed(1) = 1;
        matneed(2) = 4;
        matneed(3) = 4;
        matneed(4) = 29;
        matneed(5) = 2;
        return 1;
    }
    if (matid == 18)
    {
        matval(0) = 176;
        matval(1) = 8;
        matval(2) = 100;
        matneed(0) = 6;
        matneed(1) = 1;
        matneed(2) = 32;
        matneed(3) = 2;
        matneed(4) = 49;
        matneed(5) = 2;
        return 1;
    }
    if (matid == 16)
    {
        matval(0) = 179;
        matval(1) = 7;
        matval(2) = 100;
        matneed(0) = 43;
        matneed(1) = 3;
        matneed(2) = 2;
        matneed(3) = 2;
        matneed(4) = 4;
        matneed(5) = 3;
        return 1;
    }
    if (matid == 14)
    {
        matval(0) = 179;
        matval(1) = 1;
        matval(2) = 100;
        matneed(0) = 43;
        matneed(1) = 2;
        matneed(2) = 49;
        matneed(3) = 1;
        return 1;
    }
    if (matid == 8)
    {
        matval(0) = 177;
        matval(1) = 4;
        matval(2) = 100;
        matneed(0) = 45;
        matneed(1) = 6;
        matneed(2) = 53;
        matneed(3) = 3;
        matneed(4) = 50;
        matneed(5) = 2;
        return 1;
    }
    return -1;
}



void crafting_menu()
{
    int matuse = 0;

    while (true)
    {
        auto result = ui::ui_menu_crafting(prodtype, invctrl).show();

        if (!result.canceled && result.value)
        {
            matid = *result.value;
            get_required_craft_materials();

            matuse = 0;
            for (int cnt = 0; cnt < 6; ++cnt)
            {
                int j0 = matneed(cnt * 2);
                int j1 = matneed(cnt * 2 + 1);
                if (j0 == -1)
                {
                    break;
                }
                mat(j0) -= j1;
                matuse += j1;
            }
            snd(58);
            fixlv = 2;
            if (rnd(200 + matval(1) * 2) < sdata(matval, 0) + 20)
            {
                fixlv = 4;
            }
            if (rnd(100 + matval(1) * 2) < sdata(matval, 0) + 20)
            {
                fixlv = 3;
            }
            flt(calcobjlv(sdata(matval, 0)), calcfixlv(fixlv));
            nostack = 1;
            itemcreate(0, matid, -1, -1, 0);
            txt(i18n::s.get("core.locale.crafting.you_crafted", inv[ci]));
            item_stack(0, ci, 0);
            r2 = matuse;
            gain_crafting_experience(matval);
            chara_refresh(0);
            render_hud();
            page_save();
        }
        else if (result.canceled)
        {
            break;
        }
    }
}


int prodcheck()
{
    int f_at_m110 = 0;
    elona_vector1<int> j_at_m110;
    f_at_m110 = 1;
    if (matval(1) > sdata(matval, 0))
    {
        f_at_m110 = -1;
    }
    for (int cnt = 0; cnt < 6; ++cnt)
    {
        j_at_m110(0) = matneed(cnt * 2);
        j_at_m110(1) = matneed(cnt * 2 + 1);
        if (j_at_m110 == -1)
        {
            break;
        }
        if (mat(j_at_m110) < j_at_m110(1))
        {
            f_at_m110 = -1;
        }
    }
    return f_at_m110;
}


} // namespace elona
