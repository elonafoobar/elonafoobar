#include <unordered_map>
#include "access_item_db.hpp"
#include "character.hpp"
#include "elona.hpp"
#include "filesystem.hpp"
#include "item.hpp"
#include "item_db.hpp"
#include "variables.hpp"

namespace elona
{


item_db_result access_item_db(item_db_query_t dbmode)
{
    item_db_result result = { false, false, read_item_t::none, -1, 0 }; // default to returning invalid effect_id
    const auto info = the_item_db[dbid];
    if (info)
    {
        if (dbmode == item_db_query_t::fixmaterial || dbmode == item_db_query_t::initialize)
        {
            inv[ci].value = info->value;
            inv[ci].weight = info->weight;
            inv[ci].dice_x = info->dice_x;
            inv[ci].dice_y = info->dice_y;
            inv[ci].hit_bonus = info->hit_bonus;
            inv[ci].damage_bonus = info->damage_bonus;
            inv[ci].pv = info->pv;
            inv[ci].dv = info->dv;
            inv[ci].material = info->material;
            if (dbmode == item_db_query_t::fixmaterial)
                return result;
        }
        else if (dbmode == item_db_query_t::charge_level)
        {
            ichargelevel = info->chargelevel;
            reftype = info->category;
            return result;
        }
        else if (dbmode == item_db_query_t::identified)
        {
            if (jp)
            {
                description(0) = info->description_jp[0];
                description(1) = info->description_jp[1];
                description(2) = info->description_jp[2];
                description(3) = info->description_jp[3];
            }
            else
            {
                description(3) = info->description_en;
            }
            return result;
        }
    }
    else
    {
        //return -999;
        return result;
    }

    if (dbmode == item_db_query_t::initialize)
    {
        // Common initialization
        inv[ci].id = dbid;
        inv[ci].number = 1;
        inv[ci].difficulty_of_identification = 0; // Default value
        inv[ci].image = info->image;
        fixeditemenc(0) = 0; // Default value
        reftype = info->category;
        reftypeminor = info->subcategory;
    }

    switch (dbid)
    {
    case 792:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 8;
        }
        break;
    case 791:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 100;
            fixeditemenc(0) = 57;
            fixeditemenc(1) = 300;
            fixeditemenc(2) = 61;
            fixeditemenc(3) = 200;
            fixeditemenc(4) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 790:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 15;
        }
        break;
    case 789:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 15;
        }
        break;
    case 788:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 108;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::lulwy;
            return result;
        }
        break;
    case 787:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 5;
            inv[ci].param3 = 720;
        }
        break;
    case 786:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 4;
        }
        break;
    case 785:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 1;
        }
        break;
    case 783:
        if (dbmode == item_db_query_t::read)
        {
            // recipes don't have effect_id/effect_power
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 781:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 101;
        }
        break;
    case 778:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 44;
        }
        break;
    case 777:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 26;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv[ci].param3 = 240;
            fixlv = 6;
        }
        break;
    case 776:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 26;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv[ci].param3 = 240;
            fixlv = 6;
        }
        break;
    case 775:
        if (dbmode == item_db_query_t::initialize)
        {
            ibitmod(5, ci, 1);
            inv[ci].param2 = 8;
        }
        break;
    case 772:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 2000;
            inv[ci].param3 = 32;
        }
        break;
    case 771:
        if (dbmode == item_db_query_t::initialize)
        {
            fixlv = 6;
        }
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 1147;
            result.effect_power = 100;
            return result;
        }
        break;
    case 770:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 1146;
            result.effect_power = 100;
            return result;
        }
        break;
    case 767:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 0;
        }
        break;
    case 761:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 183;
            fixeditemenc(0) = 60;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
            inv[ci].function = 17;
            ibitmod(5, ci, 1);
            inv[ci].param1 = 200;
            fixlv = 6;
        }
        break;
    case 760:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 49;
            ibitmod(5, ci, 1);
            inv[ci].param1 = rnd(20000) + 1;
            fixlv = 6;
        }
        break;
    case 759:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 100;
        }
        break;
    case 758:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 110;
            fixeditemenc(0) = 35;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 757:
        if (dbmode == item_db_query_t::initialize)
        {
            fixeditemenc(0) = 59;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 50;
            fixeditemenc(3) = 200;
            fixeditemenc(4) = 51;
            fixeditemenc(5) = 150;
            fixeditemenc(6) = 54;
            fixeditemenc(7) = 180;
            fixeditemenc(8) = 33;
            fixeditemenc(9) = 100;
            fixeditemenc(10) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 756:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 7;
        }
        break;
    case 755:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 6;
        }
        break;
    case 749:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 48;
            ibitmod(5, ci, 1);
        }
        break;
    case 748:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 47;
            ibitmod(5, ci, 1);
            ibitmod(16, ci, 1);
        }
        break;
    case 747:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 1;
            inv[ci].param2 = rnd(4) + 1;
        }
        if (dbmode == item_db_query_t::read)
        {
            result.read_item = read_item_t::normal_book;
            return result;
        }
        break;
    case 746:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 30;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv[ci].param1 = 1132;
            inv[ci].param2 = 100;
            inv[ci].param3 = 24;
        }
        break;
    case 745:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 30;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv[ci].param1 = 1132;
            inv[ci].param2 = 100;
            inv[ci].param3 = 24;
        }
        break;
    case 744:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 30;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv[ci].param1 = 1132;
            inv[ci].param2 = 100;
            inv[ci].param3 = 24;
        }
        break;
    case 743:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 30;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv[ci].param1 = 1132;
            inv[ci].param2 = 100;
            inv[ci].param3 = 24;
        }
        break;
    case 742:
        if (dbmode == item_db_query_t::initialize)
        {
            ibitmod(5, ci, 1);
            fixlv = 6;
        }
        if (dbmode == item_db_query_t::read)
        {
            result.read_item = read_item_t::normal_book;
            return result;
        }
        break;
    case 741:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 100;
            fixeditemenc(0) = 20050;
            fixeditemenc(1) = 550;
            fixeditemenc(2) = 70052;
            fixeditemenc(3) = 400;
            fixeditemenc(4) = 57;
            fixeditemenc(5) = 1150;
            fixeditemenc(6) = 10011;
            fixeditemenc(7) = 720;
            fixeditemenc(8) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 740:
        if (dbmode == item_db_query_t::initialize)
        {
            fixeditemenc(0) = 56;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 30181;
            fixeditemenc(3) = 550;
            fixeditemenc(4) = 20057;
            fixeditemenc(5) = 400;
            fixeditemenc(6) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 739:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 107;
            fixeditemenc(0) = 80002;
            fixeditemenc(1) = 400;
            fixeditemenc(2) = 70054;
            fixeditemenc(3) = 850;
            fixeditemenc(4) = 10016;
            fixeditemenc(5) = 34500;
            fixeditemenc(6) = 80025;
            fixeditemenc(7) = 100;
            fixeditemenc(8) = 37;
            fixeditemenc(9) = 100;
            fixeditemenc(10) = 80003;
            fixeditemenc(11) = 350;
            fixeditemenc(12) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 738:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 6;
        }
        break;
    case 737:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1145;
            result.effect_power = 100;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 736:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 1116;
            result.effect_power = 250;
            return result;
        }
        break;
    case 735:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 107;
            fixeditemenc(0) = 80025;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
        }
        break;
    case 733:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 45;
        }
        break;
    case 732:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 464;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 731:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 463;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 730:
        if (dbmode == item_db_query_t::initialize)
        {
            ibitmod(5, ci, 1);
        }
        break;
    case 728:
        if (dbmode == item_db_query_t::initialize)
        {
            fixeditemenc(0) = 55;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 20056;
            fixeditemenc(3) = 450;
            fixeditemenc(4) = 20050;
            fixeditemenc(5) = 350;
            fixeditemenc(6) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 727:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 168;
            fixeditemenc(0) = 54;
            fixeditemenc(1) = 1000;
            fixeditemenc(2) = 20058;
            fixeditemenc(3) = 450;
            fixeditemenc(4) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 726:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 168;
            fixeditemenc(0) = 30183;
            fixeditemenc(1) = -450;
            fixeditemenc(2) = 52;
            fixeditemenc(3) = 400;
            fixeditemenc(4) = 53;
            fixeditemenc(5) = 400;
            fixeditemenc(6) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 725:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 111;
            fixeditemenc(0) = 70059;
            fixeditemenc(1) = 400;
            fixeditemenc(2) = 30183;
            fixeditemenc(3) = -700;
            fixeditemenc(4) = 44;
            fixeditemenc(5) = 450;
            fixeditemenc(6) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 724:
        if (dbmode == item_db_query_t::initialize)
        {
            ibitmod(5, ci, 1);
        }
        break;
    case 723:
        if (dbmode == item_db_query_t::initialize)
        {
            fixeditemenc(0) = 50;
            fixeditemenc(1) = 600;
            fixeditemenc(2) = 30166;
            fixeditemenc(3) = 650;
            fixeditemenc(4) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 722:
        if (dbmode == item_db_query_t::initialize)
        {
            fixeditemenc(0) = 51;
            fixeditemenc(1) = 600;
            fixeditemenc(2) = 30109;
            fixeditemenc(3) = 700;
            fixeditemenc(4) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 721:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 43;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv[ci].param3 = 480;
            fixlv = 6;
        }
        break;
    case 720:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 200;
        }
        break;
    case 719:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 100;
            fixeditemenc(0) = 44;
            fixeditemenc(1) = 250;
            fixeditemenc(2) = 39;
            fixeditemenc(3) = 200;
            fixeditemenc(4) = 33;
            fixeditemenc(5) = 100;
            fixeditemenc(6) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 718:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 111;
            fixeditemenc(0) = 40;
            fixeditemenc(1) = 350;
            fixeditemenc(2) = 70054;
            fixeditemenc(3) = 1200;
            fixeditemenc(4) = 10017;
            fixeditemenc(5) = 450;
            fixeditemenc(6) = 48;
            fixeditemenc(7) = 100;
            fixeditemenc(8) = 30;
            fixeditemenc(9) = 500;
            fixeditemenc(10) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 717:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 42;
        }
        break;
    case 716:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 111;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 715:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 41;
        }
        break;
    case 714:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 111;
            fixeditemenc(0) = 80024;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
        }
        break;
    case 713:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 111;
            fixeditemenc(0) = 70061;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
        }
        break;
    case 712:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1115;
            result.read_item = read_item_t::deed;
            return result;
        }
        break;
    case 711:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 1144;
            result.effect_power = 100;
            return result;
        }
        break;
    case 710:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 462;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 709:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 462;
            result.effect_power = 1500;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 708:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 461;
            result.effect_power = 2500;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 707:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 183;
            fixeditemenc(0) = 49;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
            inv[ci].function = 17;
            ibitmod(5, ci, 1);
            inv[ci].param1 = 180;
            fixlv = 6;
        }
        break;
    case 706:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 1143;
            result.effect_power = 100;
            return result;
        }
        break;
    case 705:
        if (dbmode == item_db_query_t::initialize)
        {
            fixeditemenc(0) = 48;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 10017;
            fixeditemenc(3) = 450;
            fixeditemenc(4) = 41;
            fixeditemenc(5) = 100;
            fixeditemenc(6) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 704:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 1130;
            result.effect_power = 100;
            return result;
        }
        break;
    case 703:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 39;
        }
        break;
    case 702:
        if (dbmode == item_db_query_t::initialize)
        {
            ibitmod(5, ci, 1);
            inv[ci].param2 = 4;
            fixlv = 6;
        }
        break;
    case 701:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 37;
        }
        break;
    case 700:
        if (dbmode == item_db_query_t::read)
        {
            menucycle = 1;
            show_city_chart();
            return result;
        }
        break;
    case 699:
        if (dbmode == item_db_query_t::initialize)
        {
            ibitmod(5, ci, 1);
        }
        break;
    case 698:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 1142;
            result.effect_power = 100;
            return result;
        }
        break;
    case 697:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 2 + rnd(2) - rnd(2);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 459;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 696:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 2 + rnd(2) - rnd(2);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 460;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 695:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 102;
            fixeditemenc(0) = 44;
            fixeditemenc(1) = 750;
            fixeditemenc(2) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 693:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 183;
            inv[ci].function = 17;
            inv[ci].param1 = 175;
        }
        break;
    case 692:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 183;
            inv[ci].function = 17;
            inv[ci].param1 = 70;
        }
        break;
    case 691:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 183;
            inv[ci].function = 17;
            inv[ci].param1 = 130;
        }
        break;
    case 690:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 183;
            inv[ci].function = 17;
            inv[ci].param1 = 150;
        }
        break;
    case 689:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 36;
        }
        break;
    case 688:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 35;
        }
        break;
    case 687:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 2 + rnd(2) - rnd(2);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            // ancient books don't have effect_id/effect_power
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 686:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 34;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv[ci].param3 = 720;
            fixlv = 6;
        }
        break;
    case 685:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 33;
        }
        break;
    case 684:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 32;
            ibitmod(5, ci, 1);
        }
        break;
    case 683:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 30;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv[ci].param1 = 1132;
            inv[ci].param2 = 100;
            inv[ci].param3 = 24;
            fixlv = 6;
        }
        break;
    case 682:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 31;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv[ci].param3 = 72;
            fixlv = 6;
        }
        break;
    case 681:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 30;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv[ci].param1 = 404;
            inv[ci].param2 = 400;
            inv[ci].param3 = 8;
            fixlv = 6;
        }
        break;
    case 680:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 30;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv[ci].param1 = 446;
            inv[ci].param2 = 300;
            inv[ci].param3 = 12;
            fixlv = 6;
        }
        break;
    case 679:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 103;
            fixeditemenc(0) = 39;
            fixeditemenc(1) = 350;
            fixeditemenc(2) = 80013;
            fixeditemenc(3) = 500;
            fixeditemenc(4) = 10010;
            fixeditemenc(5) = 600;
            fixeditemenc(6) = 30167;
            fixeditemenc(7) = 450;
            fixeditemenc(8) = 20054;
            fixeditemenc(9) = 400;
            fixeditemenc(10) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 678:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 101;
            fixeditemenc(0) = 41;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 35;
            fixeditemenc(3) = 100;
            fixeditemenc(4) = 10019;
            fixeditemenc(5) = 1500;
            fixeditemenc(6) = 36;
            fixeditemenc(7) = 400;
            fixeditemenc(8) = 30185;
            fixeditemenc(9) = 600;
            fixeditemenc(10) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 677:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 104;
            fixeditemenc(0) = 80023;
            fixeditemenc(1) = 350;
            fixeditemenc(2) = 80012;
            fixeditemenc(3) = 450;
            fixeditemenc(4) = 10015;
            fixeditemenc(5) = 650;
            fixeditemenc(6) = 20053;
            fixeditemenc(7) = 200;
            fixeditemenc(8) = 20056;
            fixeditemenc(9) = 150;
            fixeditemenc(10) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 676:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 105;
            fixeditemenc(0) = 80000;
            fixeditemenc(1) = 400;
            fixeditemenc(2) = 70050;
            fixeditemenc(3) = 350;
            fixeditemenc(4) = 70051;
            fixeditemenc(5) = 350;
            fixeditemenc(6) = 70052;
            fixeditemenc(7) = 350;
            fixeditemenc(8) = 20050;
            fixeditemenc(9) = 250;
            fixeditemenc(10) = 20051;
            fixeditemenc(11) = 250;
            fixeditemenc(12) = 20052;
            fixeditemenc(13) = 250;
            fixeditemenc(14) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 675:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 107;
            fixeditemenc(0) = 30184;
            fixeditemenc(1) = 600;
            fixeditemenc(2) = 42;
            fixeditemenc(3) = 100;
            fixeditemenc(4) = 30180;
            fixeditemenc(5) = 1100;
            fixeditemenc(6) = 30163;
            fixeditemenc(7) = 800;
            fixeditemenc(8) = 10010;
            fixeditemenc(9) = 550;
            fixeditemenc(10) = 20059;
            fixeditemenc(11) = 400;
            fixeditemenc(12) = 80025;
            fixeditemenc(13) = 100;
            fixeditemenc(14) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 674:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 110;
            fixeditemenc(0) = 80017;
            fixeditemenc(1) = 350;
            fixeditemenc(2) = 43;
            fixeditemenc(3) = 200;
            fixeditemenc(4) = 30110;
            fixeditemenc(5) = 450;
            fixeditemenc(6) = 20057;
            fixeditemenc(7) = 350;
            fixeditemenc(8) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 673:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 108;
            fixeditemenc(0) = 80014;
            fixeditemenc(1) = 200;
            fixeditemenc(2) = 80005;
            fixeditemenc(3) = 200;
            fixeditemenc(4) = 10018;
            fixeditemenc(5) = 250;
            fixeditemenc(6) = 20052;
            fixeditemenc(7) = 300;
            fixeditemenc(8) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 672:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 29;
            ibitmod(5, ci, 1);
            fixlv = 6;
        }
        break;
    case 671:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 28;
            ibitmod(5, ci, 1);
            fixlv = 6;
        }
        break;
    case 670:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 7;
        }
        break;
    case 669:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 7;
        }
        break;
    case 668:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 1;
            inv[ci].param2 = rnd(4) + 1;
        }
        if (dbmode == item_db_query_t::read)
        {
            result.read_item = read_item_t::normal_book;
            return result;
        }
        break;
    case 667:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 7;
        }
        break;
    case 666:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 27;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv[ci].param3 = 120;
            fixlv = 6;
        }
        break;
    case 665:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 26;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv[ci].param3 = 240;
            fixlv = 6;
        }
        break;
    case 664:
        if (dbmode == item_db_query_t::initialize)
        {
            fixeditemenc(0) = 10018;
            fixeditemenc(1) = 400 + rnd((rnd(1000) + 1));
            fixeditemenc(2) = 0;
        }
        break;
    case 663:
        if (dbmode == item_db_query_t::initialize)
        {
            ibitmod(5, ci, 1);
            fixlv = 6;
        }
        break;
    case 662:
        if (dbmode == item_db_query_t::initialize)
        {
            ibitmod(5, ci, 1);
            inv[ci].param2 = 7;
            fixlv = 6;
        }
        break;
    case 661:
        if (dbmode == item_db_query_t::initialize)
        {
            fixeditemenc(0) = 43;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 29;
            fixeditemenc(3) = 100;
            fixeditemenc(4) = 10012;
            fixeditemenc(5) = 250;
            fixeditemenc(6) = 30182;
            fixeditemenc(7) = 200;
            fixeditemenc(8) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 660:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 5 + rnd(5) - rnd(5);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 418;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 655:
        if (dbmode == item_db_query_t::initialize)
        {
            ibitmod(5, ci, 1);
            inv[ci].param2 = 7;
            fixlv = 6;
        }
        break;
    case 654:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 160;
        }
        break;
    case 650:
        if (dbmode == item_db_query_t::drink)
        {
            //drink_well();
            return result;
        }
        break;
    case 648:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 44;
        }
        break;
    case 643:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 130;
        }
        break;
    case 641:
        if (dbmode == item_db_query_t::initialize)
        {
            ibitmod(5, ci, 1);
            fixlv = 6;
        }
        break;
    case 640:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 25;
        }
        break;
    case 639:
        if (dbmode == item_db_query_t::initialize)
        {
            ibitmod(5, ci, 1);
            inv[ci].param2 = 7;
            fixlv = 6;
        }
        break;
    case 638:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1141;
            result.effect_power = 100;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 637:
        if (dbmode == item_db_query_t::initialize)
        {
            ibitmod(5, ci, 1);
            fixlv = 6;
        }
        break;
    case 635:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 24;
        }
        break;
    case 634:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 23;
        }
        break;
    case 633:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 111;
            fixeditemenc(0) = 70054;
            fixeditemenc(1) = 800;
            fixeditemenc(2) = 0;
        }
        break;
    case 632:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1140;
            result.effect_power = 150;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 630:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 21;
        }
        break;
    case 629:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 20;
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        break;
    case 628:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 458;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 627:
        if (dbmode == item_db_query_t::initialize)
        {
            fixeditemenc(0) = 25;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 35;
            fixeditemenc(3) = 100;
            fixeditemenc(4) = 10016;
            fixeditemenc(5) = 200;
            fixeditemenc(6) = 20054;
            fixeditemenc(7) = 250;
            fixeditemenc(8) = 20060;
            fixeditemenc(9) = 150;
            fixeditemenc(10) = 30161;
            fixeditemenc(11) = 300;
            fixeditemenc(12) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 626:
        if (dbmode == item_db_query_t::initialize)
        {
            ibitmod(5, ci, 1);
        }
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 1139;
            result.effect_power = 500;
            return result;
        }
        break;
    case 625:
        if (dbmode == item_db_query_t::initialize)
        {
            ibitmod(5, ci, 1);
        }
        break;
    case 624:
        if (dbmode == item_db_query_t::initialize)
        {
            ibitmod(5, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1137;
            result.effect_power = 100;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 623:
        if (dbmode == item_db_query_t::initialize)
        {
            ibitmod(5, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1138;
            result.effect_power = 100;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 622:
        if (dbmode == item_db_query_t::initialize)
        {
            ibitmod(5, ci, 1);
        }
        break;
    case 621:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1136;
            result.effect_power = 100;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 620:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 1135;
            result.effect_power = 100;
            return result;
        }
        break;
    case 618:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 6000;
            inv[ci].param3 = 4;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::ehekatl;
            return result;
        }
        break;
    case 616:
        if (dbmode == item_db_query_t::initialize)
        {
            ibitmod(5, ci, 1);
        }
        break;
    case 615:
        if (dbmode == item_db_query_t::initialize)
        {
            ibitmod(5, ci, 1);
        }
        break;
    case 613:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 180;
        }
        break;
    case 611:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 8;
        }
        break;
    case 606:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 15;
            inv[ci].param1 = 225;
        }
        break;
    case 603:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 44;
            ibitmod(5, ci, 1);
        }
        break;
    case 602:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 100;
        }
        if (dbmode == item_db_query_t::drink)
        {
            //drink_well();
            return result;
        }
        break;
    case 600:
        if (dbmode == item_db_query_t::initialize)
        {
            ibitmod(5, ci, 1);
        }
        break;
    case 598:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 6;
        }
        break;
    case 597:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 6;
        }
        break;
    case 587:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 14;
        }
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 1103;
            result.effect_power = 100;
            return result;
        }
        break;
    case 583:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 13;
            inv[ci].param1 = 100;
        }
        break;
    case 582:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 457;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 581:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 6 + rnd(6) - rnd(6);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::zap)
        {
            result.effect_id = 457;
            result.effect_power = 100;
            return result;
        }
        break;
    case 578:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 11;
        }
        break;
    case 577:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 1133;
            result.effect_power = 100;
            return result;
        }
        break;
    case 576:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 10;
        }
        break;
    case 574:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 1101;
            result.effect_power = 100;
            return result;
        }
        break;
    case 573:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 8000;
            inv[ci].param3 = 240;
        }
        break;
    case 572:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1115;
            result.read_item = read_item_t::deed;
            return result;
        }
        break;
    case 571:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 5;
        }
        break;
    case 570:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::zap)
        {
            result.effect_id = 456;
            result.effect_power = 100;
            return result;
        }
        break;
    case 569:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 456;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 568:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 12 + rnd(12) - rnd(12);
            ibitmod(4, ci, 1);
        }
        break;
    case 567:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 12 + rnd(12) - rnd(12);
            ibitmod(4, ci, 1);
        }
        break;
    case 566:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 1116;
            result.effect_power = 250;
            return result;
        }
        break;
    case 565:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::zap)
        {
            result.effect_id = 455;
            result.effect_power = 100;
            return result;
        }
        break;
    case 564:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 455;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 563:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 0;
        }
        if (dbmode == item_db_query_t::read)
        {
            result.read_item = read_item_t::normal_book;
            return result;
        }
        break;
    case 562:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 8;
        }
        break;
    case 560:
        if (dbmode == item_db_query_t::initialize)
        {
            ibitmod(5, ci, 1);
        }
        break;
    case 559:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 1131;
            result.effect_power = 200;
            return result;
        }
        break;
    case 558:
        if (dbmode == item_db_query_t::initialize)
        {
            fixeditemenc(0) = 31;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 20057;
            fixeditemenc(3) = 100;
            fixeditemenc(4) = 0;
        }
        break;
    case 557:
        if (dbmode == item_db_query_t::initialize)
        {
            fixeditemenc(0) = 30;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
        }
        break;
    case 556:
        if (dbmode == item_db_query_t::initialize)
        {
            fixeditemenc(0) = 29;
            fixeditemenc(1) = 500;
            fixeditemenc(2) = 0;
        }
        break;
    case 555:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 7;
        }
        break;
    case 554:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 1;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::kumiromi;
            return result;
        }
        break;
    case 553:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 1;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::kumiromi;
            return result;
        }
        break;
    case 552:
        if (dbmode == item_db_query_t::initialize)
        {
            fixeditemenc(0) = 32;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
        }
        break;
    case 551:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::zap)
        {
            result.effect_id = 405;
            result.effect_power = 100;
            return result;
        }
        break;
    case 550:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 405;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 549:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 404;
            result.effect_power = 400;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 548:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 404;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 546:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 438;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 545:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 7 + rnd(7) - rnd(7);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::zap)
        {
            result.effect_id = 438;
            result.effect_power = 100;
            return result;
        }
        break;
    case 544:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 6;
            inv[ci].param1 = discsetmc();
        }
        break;
    case 543:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1115;
            result.read_item = read_item_t::deed;
            return result;
        }
        break;
    case 542:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1115;
            result.read_item = read_item_t::deed;
            return result;
        }
        break;
    case 526:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = rnd(5) + 2;
            inv[ci].param2 = isetfruit(rnd(length(isetfruit)));
        }
        break;
    case 522:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 1;
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1115;
            result.read_item = read_item_t::deed;
            return result;
        }
        break;
    case 521:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 1;
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1115;
            result.read_item = read_item_t::deed;
            return result;
        }
        break;
    case 520:
        if (dbmode == item_db_query_t::initialize)
        {
            fixeditemenc(0) = 32;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
        }
        break;
    case 519:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 1108;
            result.effect_power = 150;
            return result;
        }
        break;
    case 518:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::zap)
        {
            result.effect_id = 1132;
            result.effect_power = 100;
            return result;
        }
        break;
    case 517:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::zap)
        {
            result.effect_id = 628;
            result.effect_power = 100;
            return result;
        }
        break;
    case 516:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 1103;
            result.effect_power = 100;
            return result;
        }
        break;
    case 515:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1129;
            result.effect_power = 300;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 514:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 110;
            fixeditemenc(0) = 80003;
            fixeditemenc(1) = 350;
            fixeditemenc(2) = 80004;
            fixeditemenc(3) = 300;
            fixeditemenc(4) = 70058;
            fixeditemenc(5) = 300;
            fixeditemenc(6) = 20057;
            fixeditemenc(7) = 300;
            fixeditemenc(8) = 20059;
            fixeditemenc(9) = 300;
            fixeditemenc(10) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 513:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 110;
        }
        break;
    case 512:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 110;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::mani;
            return result;
        }
        break;
    case 511:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 100 + rnd(200);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1128;
            result.effect_power = inv[ci].param1;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 509:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1125;
            result.effect_power = 400;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 508:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1125;
            result.effect_power = 200;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 507:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1124;
            result.effect_power = 400;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 506:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1124;
            result.effect_power = 200;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 505:
        if (dbmode == item_db_query_t::initialize)
        {
            ibitmod(5, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1123;
            result.effect_power = 100;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 502:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1127;
            result.effect_power = 350;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 501:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1127;
            result.effect_power = 180;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 500:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1127;
            result.effect_power = 10;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 499:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 7;
        }
        break;
    case 498:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 6;
        }
        break;
    case 497:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 5;
        }
        break;
    case 496:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 110;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::mani;
            return result;
        }
        break;
    case 495:
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::mani;
            return result;
        }
        break;
    case 494:
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::mani;
            return result;
        }
        break;
    case 492:
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::mani;
            return result;
        }
        break;
    case 491:
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::mani;
            return result;
        }
        break;
    case 490:
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::mani;
            return result;
        }
        break;
    case 489:
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::mani;
            return result;
        }
        break;
    case 488:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 9;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::mani;
            return result;
        }
        break;
    case 487:
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::mani;
            return result;
        }
        break;
    case 486:
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::mani;
            return result;
        }
        break;
    case 485:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 8 + rnd(8) - rnd(8);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::zap)
        {
            result.effect_id = 436;
            result.effect_power = 100;
            return result;
        }
        break;
    case 484:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 436;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 483:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 109;
        }
        break;
    case 482:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 109;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::lulwy;
            return result;
        }
        break;
    case 481:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 2 + rnd(2) - rnd(2);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 435;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 480:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 2 + rnd(2) - rnd(2);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::zap)
        {
            result.effect_id = 435;
            result.effect_power = 100;
            return result;
        }
        break;
    case 479:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1122;
            result.effect_power = 100;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 478:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 5;
        }
        break;
    case 454:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 168;
        }
        break;
    case 453:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 168;
        }
        break;
    case 452:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 168;
        }
        break;
    case 451:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 168;
        }
        break;
    case 450:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 168;
        }
        break;
    case 449:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 168;
        }
        break;
    case 434:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 2 + rnd(2) - rnd(2);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 454;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 433:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 1121;
            result.effect_power = 200;
            return result;
        }
        break;
    case 432:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 454;
            result.effect_power = 100;
            return result;
        }
        break;
    case 431:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1107;
            result.effect_power = 300;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 430:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1119;
            result.effect_power = 500;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 429:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 1118;
            result.effect_power = 100;
            return result;
        }
        break;
    case 428:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 0;
        }
        break;
    case 427:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 7;
        }
        break;
    case 426:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 3;
        }
        break;
    case 425:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 6;
        }
        break;
    case 424:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 3;
        }
        break;
    case 423:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 4;
        }
        break;
    case 422:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 1;
        }
        break;
    case 421:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 1;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::kumiromi;
            return result;
        }
        break;
    case 420:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 1;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::kumiromi;
            return result;
        }
        break;
    case 419:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 1;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::kumiromi;
            return result;
        }
        break;
    case 418:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 1;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::kumiromi;
            return result;
        }
        break;
    case 417:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 1;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::kumiromi;
            return result;
        }
        break;
    case 412:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::zap)
        {
            result.effect_id = 412;
            result.effect_power = 100;
            return result;
        }
        break;
    case 411:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 430;
            result.effect_power = 500;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 410:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 430;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 409:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 5;
        }
        break;
    case 408:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 1;
        }
        break;
    case 407:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 2;
        }
        break;
    case 406:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 0;
        }
        break;
    case 405:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 3;
        }
        break;
    case 404:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 0;
        }
        break;
    case 403:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 3;
        }
        break;
    case 402:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 5;
        }
        break;
    case 401:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 4;
        }
        break;
    case 400:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 2;
        }
        break;
    case 399:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 1;
        }
        break;
    case 398:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 453;
            result.effect_power = 250;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 397:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 5 + rnd(5) - rnd(5);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 453;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 396:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 452;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 395:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1117;
            result.effect_power = 250;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 393:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 3;
        }
        break;
    case 392:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 1116;
            result.effect_power = 100;
            return result;
        }
        break;
    case 391:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::zap)
        {
            result.effect_id = 621;
            result.effect_power = 100;
            return result;
        }
        break;
    case 390:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 621;
            result.effect_power = 250;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 389:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 407;
            result.effect_power = 300;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 388:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 406;
            result.effect_power = 300;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 387:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 407;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 386:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 406;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 385:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 6 + rnd(6) - rnd(6);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::zap)
        {
            result.effect_id = 407;
            result.effect_power = 100;
            return result;
        }
        break;
    case 384:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 451;
            result.effect_power = 250;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 383:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 451;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 382:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 449;
            result.effect_power = 250;
            return result;
        }
        break;
    case 381:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 450;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 380:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 449;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 379:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 448;
            result.effect_power = 250;
            return result;
        }
        break;
    case 378:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 5 + rnd(5) - rnd(5);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 448;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 377:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 8 + rnd(8) - rnd(8);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::zap)
        {
            result.effect_id = 446;
            result.effect_power = 100;
            return result;
        }
        break;
    case 376:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 447;
            result.effect_power = 400;
            return result;
        }
        break;
    case 375:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 446;
            result.effect_power = 250;
            return result;
        }
        break;
    case 374:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 447;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 373:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 446;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 372:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 445;
            result.effect_power = 250;
            return result;
        }
        break;
    case 371:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 445;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 370:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 444;
            result.effect_power = 300;
            return result;
        }
        break;
    case 369:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 444;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 368:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 443;
            result.effect_power = 400;
            return result;
        }
        break;
    case 367:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 443;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 366:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 7 + rnd(7) - rnd(7);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::zap)
        {
            result.effect_id = 443;
            result.effect_power = 100;
            return result;
        }
        break;
    case 365:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 5 + rnd(5) - rnd(5);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 442;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 364:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 442;
            result.effect_power = 200;
            return result;
        }
        break;
    case 363:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 412;
            result.effect_power = 2500;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 362:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 411;
            result.effect_power = 2000;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 360:
        if (dbmode == item_db_query_t::initialize)
        {
            fixeditemenc(0) = 41;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 10019;
            fixeditemenc(3) = 700;
            fixeditemenc(4) = 10018;
            fixeditemenc(5) = 350;
            fixeditemenc(6) = 10017;
            fixeditemenc(7) = 550;
            fixeditemenc(8) = 20053;
            fixeditemenc(9) = 200;
            fixeditemenc(10) = 20059;
            fixeditemenc(11) = 200;
            fixeditemenc(12) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 359:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 104;
            fixeditemenc(0) = 40;
            fixeditemenc(1) = 400;
            fixeditemenc(2) = 70056;
            fixeditemenc(3) = 400;
            fixeditemenc(4) = 20056;
            fixeditemenc(5) = 300;
            fixeditemenc(6) = 26;
            fixeditemenc(7) = 100;
            fixeditemenc(8) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 358:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 105;
            fixeditemenc(0) = 80002;
            fixeditemenc(1) = 400;
            fixeditemenc(2) = 70054;
            fixeditemenc(3) = 350;
            fixeditemenc(4) = 70058;
            fixeditemenc(5) = 350;
            fixeditemenc(6) = 10016;
            fixeditemenc(7) = 450;
            fixeditemenc(8) = 34;
            fixeditemenc(9) = 350;
            fixeditemenc(10) = 30172;
            fixeditemenc(11) = 420;
            fixeditemenc(12) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 357:
        if (dbmode == item_db_query_t::initialize)
        {
            fixeditemenc(0) = 42;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 20060;
            fixeditemenc(3) = 250;
            fixeditemenc(4) = 20052;
            fixeditemenc(5) = 450;
            fixeditemenc(6) = 10010;
            fixeditemenc(7) = 450;
            fixeditemenc(8) = 30153;
            fixeditemenc(9) = 550;
            fixeditemenc(10) = 10018;
            fixeditemenc(11) = -1400;
            fixeditemenc(12) = 26;
            fixeditemenc(13) = 100;
            fixeditemenc(14) = 24;
            fixeditemenc(15) = 100;
            fixeditemenc(16) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 356:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 103;
            fixeditemenc(0) = 38;
            fixeditemenc(1) = 300;
            fixeditemenc(2) = 20050;
            fixeditemenc(3) = 200;
            fixeditemenc(4) = 20056;
            fixeditemenc(5) = 250;
            fixeditemenc(6) = 70050;
            fixeditemenc(7) = 350;
            fixeditemenc(8) = 25;
            fixeditemenc(9) = 100;
            fixeditemenc(10) = 26;
            fixeditemenc(11) = 100;
            fixeditemenc(12) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 355:
        if (dbmode == item_db_query_t::initialize)
        {
            fixeditemenc(0) = 39;
            fixeditemenc(1) = 150;
            fixeditemenc(2) = 20050;
            fixeditemenc(3) = 550;
            fixeditemenc(4) = 10010;
            fixeditemenc(5) = 400;
            fixeditemenc(6) = 20057;
            fixeditemenc(7) = 200;
            fixeditemenc(8) = 30166;
            fixeditemenc(9) = 450;
            fixeditemenc(10) = 10019;
            fixeditemenc(11) = 500;
            fixeditemenc(12) = 25;
            fixeditemenc(13) = 100;
            fixeditemenc(14) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 354:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 6000;
            inv[ci].param3 = 4;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::ehekatl;
            return result;
        }
        break;
    case 353:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 6000;
            inv[ci].param3 = 4;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::ehekatl;
            return result;
        }
        break;
    case 352:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 6000;
            inv[ci].param3 = 4;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::ehekatl;
            return result;
        }
        break;
    case 351:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 6000;
            inv[ci].param3 = 4;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::ehekatl;
            return result;
        }
        break;
    case 350:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 6000;
            inv[ci].param3 = 4;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::ehekatl;
            return result;
        }
        break;
    case 349:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 6000;
            inv[ci].param3 = 4;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::ehekatl;
            return result;
        }
        break;
    case 348:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 6000;
            inv[ci].param3 = 4;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::ehekatl;
            return result;
        }
        break;
    case 347:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 6000;
            inv[ci].param3 = 4;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::ehekatl;
            return result;
        }
        break;
    case 346:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 6000;
            inv[ci].param3 = 4;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::ehekatl;
            return result;
        }
        break;
    case 345:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 6000;
            inv[ci].param3 = 4;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::ehekatl;
            return result;
        }
        break;
    case 344:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 1;
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1115;
            result.read_item = read_item_t::deed;
            return result;
        }
        break;
    case 343:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 22;
        }
        break;
    case 342:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 16;
            inv[ci].param1 = 60;
        }
        break;
    case 334:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 44;
        }
        break;
    case 333:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 3;
        }
        break;
    case 330:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 44;
        }
        break;
    case 328:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 17;
            inv[ci].param1 = 150;
        }
        break;
    case 327:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 44;
        }
        break;
    case 325:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 130;
        }
        break;
    case 322:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 19;
        }
        break;
    case 319:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 0;
        }
        break;
    case 310:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 130;
        }
        break;
    case 309:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 19;
        }
        break;
    case 307:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 130;
        }
        break;
    case 306:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 15;
            inv[ci].param1 = 200;
        }
        break;
    case 305:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 130;
        }
        break;
    case 304:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 100;
        }
        break;
    case 303:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 120;
        }
        break;
    case 299:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 19;
        }
        break;
    case 297:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 150;
        }
        break;
    case 290:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 1 + rnd(1) - rnd(1);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::zap)
        {
            result.effect_id = 441;
            result.effect_power = 100;
            return result;
        }
        break;
    case 289:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 1 + rnd(1) - rnd(1);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 441;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 288:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1114;
            result.effect_power = 100;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 287:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 1113;
            result.effect_power = 100;
            return result;
        }
        break;
    case 286:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 440;
            result.effect_power = 100;
            return result;
        }
        break;
    case 285:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 439;
            result.effect_power = 100;
            return result;
        }
        break;
    case 272:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 433;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 271:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 434;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 270:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 432;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 269:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 431;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 268:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 423;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 267:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 422;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 266:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 101;
        }
        break;
    case 265:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 416;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 264:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 417;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 263:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 415;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 262:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 1108;
            result.effect_power = 200;
            return result;
        }
        break;
    case 261:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 6000;
            inv[ci].param3 = 6;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::ehekatl;
            return result;
        }
        break;
    case 260:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 7000;
            inv[ci].param3 = 240;
        }
        break;
    case 259:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 5000;
            inv[ci].param3 = 24;
        }
        break;
    case 258:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 3;
        }
        break;
    case 257:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 5 + rnd(5) - rnd(5);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 414;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 256:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 15;
            inv[ci].param1 = 80;
        }
        break;
    case 255:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 15;
            inv[ci].param1 = 40;
        }
        break;
    case 254:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 183;
            inv[ci].function = 17;
            inv[ci].param1 = 110;
        }
        break;
    case 253:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 1102;
            result.effect_power = 200;
            return result;
        }
        break;
    case 252:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 2 + rnd(2) - rnd(2);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 403;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 251:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 402;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 250:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 401;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 249:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 5 + rnd(5) - rnd(5);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 400;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 248:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 428;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 247:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 2 + rnd(2) - rnd(2);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 413;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 246:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 429;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 245:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 408;
            result.effect_power = 100;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 244:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1104;
            result.effect_power = 100;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 243:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 1105;
            result.effect_power = 100;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 242:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 429;
            result.effect_power = 500;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 236:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 428;
            result.effect_power = 100;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 235:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 104;
        }
        break;
    case 234:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 102;
        }
        break;
    case 233:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 3;
        }
        break;
    case 232:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 100;
        }
        break;
    case 231:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 110;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::mani;
            return result;
        }
        break;
    case 230:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 108;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::lulwy;
            return result;
        }
        break;
    case 229:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 105;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::itzpalt;
            return result;
        }
        break;
    case 228:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 104;
        }
        break;
    case 227:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 103;
        }
        break;
    case 226:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 102;
        }
        break;
    case 225:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 101;
        }
        break;
    case 224:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 100;
        }
        break;
    case 223:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 15;
            inv[ci].param1 = 60;
        }
        break;
    case 219:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 46;
        }
        break;
    case 213:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 104;
        }
        break;
    case 212:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 105;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::itzpalt;
            return result;
        }
        break;
    case 211:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 107;
            fixeditemenc(0) = 80025;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
        }
        break;
    case 210:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 111;
        }
        break;
    case 209:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 412;
            result.effect_power = 100;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 207:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 108;
            fixeditemenc(0) = 80001;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 60012;
            fixeditemenc(3) = 100;
            fixeditemenc(4) = 60013;
            fixeditemenc(5) = 100;
            fixeditemenc(6) = 10012;
            fixeditemenc(7) = 450;
            fixeditemenc(8) = 20055;
            fixeditemenc(9) = 300;
            fixeditemenc(10) = 70055;
            fixeditemenc(11) = 300;
            fixeditemenc(12) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 206:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 101;
            fixeditemenc(0) = 80000;
            fixeditemenc(1) = 200;
            fixeditemenc(2) = 70052;
            fixeditemenc(3) = 300;
            fixeditemenc(4) = 20052;
            fixeditemenc(5) = 250;
            fixeditemenc(6) = 30172;
            fixeditemenc(7) = 350;
            fixeditemenc(8) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 205:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 1102;
            result.effect_power = 500;
            return result;
        }
        break;
    case 204:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 1000;
            inv[ci].param3 = 4;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = true;
            return result;
        }
        break;
    case 203:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 8 + rnd(8) - rnd(8);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::zap)
        {
            result.effect_id = 401;
            result.effect_power = 100;
            return result;
        }
        break;
    case 202:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 9 + rnd(9) - rnd(9);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::zap)
        {
            result.effect_id = 429;
            result.effect_power = 100;
            return result;
        }
        break;
    case 201:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 2000;
            inv[ci].param3 = 2;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::kumiromi;
            return result;
        }
        break;
    case 200:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 2000;
            inv[ci].param3 = 72;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::kumiromi;
            return result;
        }
        break;
    case 199:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 2000;
            inv[ci].param3 = 72;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::kumiromi;
            return result;
        }
        break;
    case 198:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 2000;
            inv[ci].param3 = 72;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::kumiromi;
            return result;
        }
        break;
    case 197:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 3000;
            inv[ci].param3 = 12;
        }
        break;
    case 196:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 3000;
            inv[ci].param3 = 8;
        }
        break;
    case 195:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 3000;
            inv[ci].param3 = 12;
        }
        break;
    case 194:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 3000;
            inv[ci].param3 = 8;
        }
        break;
    case 193:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 2000;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::kumiromi;
            return result;
        }
        break;
    case 192:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 3000;
            inv[ci].param3 = 16;
        }
        break;
    case 191:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 4000;
        }
        break;
    case 190:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 2000;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::kumiromi;
            return result;
        }
        break;
    case 188:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 2000;
            inv[ci].param3 = 72;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::kumiromi;
            return result;
        }
        break;
    case 187:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 2000;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::kumiromi;
            return result;
        }
        break;
    case 186:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 2000;
            inv[ci].param3 = 72;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::kumiromi;
            return result;
        }
        break;
    case 185:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 2000;
            inv[ci].param3 = 72;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::kumiromi;
            return result;
        }
        break;
    case 184:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 3000;
            inv[ci].param3 = 8;
        }
        break;
    case 183:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 3000;
            inv[ci].param3 = 16;
        }
        break;
    case 182:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 3000;
            inv[ci].param3 = 12;
        }
        break;
    case 181:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 3000;
            inv[ci].param3 = 16;
        }
        break;
    case 180:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 3000;
            inv[ci].param3 = 16;
        }
        break;
    case 179:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 2000;
            inv[ci].param3 = 48;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::kumiromi;
            return result;
        }
        break;
    case 178:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 3000;
            inv[ci].param3 = 72;
        }
        break;
    case 177:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 3000;
            inv[ci].param3 = 72;
        }
        break;
    case 176:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 8 + rnd(8) - rnd(8);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::zap)
        {
            result.effect_id = 447;
            result.effect_power = 100;
            return result;
        }
        break;
    case 175:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 10 + rnd(10) - rnd(10);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::zap)
        {
            result.effect_id = 421;
            result.effect_power = 100;
            return result;
        }
        break;
    case 174:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 110;
        }
        break;
    case 173:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 100;
        }
        if (dbmode == item_db_query_t::drink)
        {
            //drink_well();
            return result;
        }
        break;
    case 161:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 1;
        }
        break;
    case 160:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 4;
        }
        break;
    case 155:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 15;
            inv[ci].param1 = 100;
        }
        break;
    case 154:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 15;
            inv[ci].param1 = 100;
        }
        break;
    case 153:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 15;
            inv[ci].param1 = 100;
        }
        break;
    case 142:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 15;
            inv[ci].param1 = 200;
        }
        break;
    case 127:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 2;
        }
        break;
    case 125:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::zap)
        {
            result.effect_id = 402;
            result.effect_power = 100;
            return result;
        }
        break;
    case 123:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 10 + rnd(10) - rnd(10);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::zap)
        {
            result.effect_id = 420;
            result.effect_power = 100;
            return result;
        }
        break;
    case 122:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 8 + rnd(8) - rnd(8);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::zap)
        {
            result.effect_id = 419;
            result.effect_power = 100;
            return result;
        }
        break;
    case 121:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 8 + rnd(8) - rnd(8);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::zap)
        {
            result.effect_id = 424;
            result.effect_power = 100;
            return result;
        }
        break;
    case 120:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 10 + rnd(10) - rnd(10);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::zap)
        {
            result.effect_id = 414;
            result.effect_power = 100;
            return result;
        }
        break;
    case 119:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 8 + rnd(8) - rnd(8);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::zap)
        {
            result.effect_id = 400;
            result.effect_power = 100;
            return result;
        }
        break;
    case 118:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 424;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 116:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 410;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 112:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 15;
            inv[ci].param1 = 150;
        }
        break;
    case 109:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param2 = 100;
        }
        if (dbmode == item_db_query_t::drink)
        {
            //drink_well();
            return result;
        }
        break;
    case 102:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 44;
        }
        break;
    case 101:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 44;
        }
        break;
    case 92:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 44;
        }
        break;
    case 88:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 183;
            inv[ci].function = 17;
            inv[ci].param1 = 200;
        }
        break;
    case 81:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 44;
        }
        break;
    case 80:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 100;
        }
        break;
    case 77:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].function = 44;
        }
        break;
    case 76:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 403;
            result.effect_power = 100;
            return result;
        }
        break;
    case 75:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 402;
            result.effect_power = 300;
            return result;
        }
        break;
    case 74:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 402;
            result.effect_power = 100;
            return result;
        }
        break;
    case 73:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 100;
            fixeditemenc(0) = 37;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 72:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 401;
            result.effect_power = 400;
            return result;
        }
        break;
    case 71:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 401;
            result.effect_power = 300;
            return result;
        }
        break;
    case 70:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 401;
            result.effect_power = 100;
            return result;
        }
        break;
    case 69:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 400;
            result.effect_power = 300;
            return result;
        }
        break;
    case 68:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 400;
            result.effect_power = 100;
            return result;
        }
        break;
    case 64:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 100;
            fixeditemenc(0) = 36;
            fixeditemenc(1) = 300;
            fixeditemenc(2) = 70059;
            fixeditemenc(3) = 300;
            fixeditemenc(4) = 70056;
            fixeditemenc(5) = 250;
            fixeditemenc(6) = 30166;
            fixeditemenc(7) = 300;
            fixeditemenc(8) = 20059;
            fixeditemenc(9) = 250;
            fixeditemenc(10) = 20056;
            fixeditemenc(11) = 200;
            fixeditemenc(12) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 63:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 107;
            fixeditemenc(0) = 32;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 38;
            fixeditemenc(3) = 500;
            fixeditemenc(4) = 34;
            fixeditemenc(5) = 450;
            fixeditemenc(6) = 20060;
            fixeditemenc(7) = 250;
            fixeditemenc(8) = 80025;
            fixeditemenc(9) = 100;
            fixeditemenc(10) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 62:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 110;
        }
        break;
    case 61:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 108;
        }
        break;
    case 60:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 110;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::mani;
            return result;
        }
        break;
    case 59:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 168;
        }
        break;
    case 58:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 108;
        }
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable = cdata[0].god_id == core_god::lulwy;
            return result;
        }
        break;
    case 57:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 100;
            fixeditemenc(0) = 39;
            fixeditemenc(1) = 400;
            fixeditemenc(2) = 25;
            fixeditemenc(3) = 100;
            fixeditemenc(4) = 10010;
            fixeditemenc(5) = 300;
            fixeditemenc(6) = 20058;
            fixeditemenc(7) = 200;
            fixeditemenc(8) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 56:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 100;
            fixeditemenc(0) = 40;
            fixeditemenc(1) = 300;
            fixeditemenc(2) = 70058;
            fixeditemenc(3) = 400;
            fixeditemenc(4) = 10018;
            fixeditemenc(5) = 300;
            fixeditemenc(6) = 24;
            fixeditemenc(7) = 100;
            fixeditemenc(8) = 0;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 44:
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable =
                cdata[0].god_id == core_god::jure
                || cdata[0].god_id == core_god::opatos;
            return result;
        }
        break;
    case 42:
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable =
                cdata[0].god_id == core_god::jure
                || cdata[0].god_id == core_god::opatos;
            return result;
        }
        break;
    case 41:
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable =
                cdata[0].god_id == core_god::jure
                || cdata[0].god_id == core_god::opatos;
            return result;
        }
        break;
    case 40:
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable =
                cdata[0].god_id == core_god::jure
                || cdata[0].god_id == core_god::opatos;
            return result;
        }
        break;
    case 39:
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable =
                cdata[0].god_id == core_god::jure
                || cdata[0].god_id == core_god::opatos;
            return result;
        }
        break;
    case 38:
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable =
                cdata[0].god_id == core_god::jure
                || cdata[0].god_id == core_god::opatos;
            return result;
        }
        break;
    case 37:
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable =
                cdata[0].god_id == core_god::jure
                || cdata[0].god_id == core_god::opatos;
            return result;
        }
        break;
    case 36:
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable =
                cdata[0].god_id == core_god::jure
                || cdata[0].god_id == core_god::opatos;
            return result;
        }
        break;
    case 35:
        if (dbmode == item_db_query_t::is_offerable && dbspec == 12)
        {
            result.is_offerable =
                cdata[0].god_id == core_god::jure
                || cdata[0].god_id == core_god::opatos;
            return result;
        }
        break;
    case 34:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 421;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 33:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 420;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 32:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 419;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 31:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 1102;
            result.effect_power = 300;
            return result;
        }
        break;
    case 30:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 1112;
            result.effect_power = 200;
            return result;
        }
        break;
    case 29:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 1110;
            result.effect_power = 200;
            return result;
        }
        break;
    case 28:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 1109;
            result.effect_power = 150;
            return result;
        }
        break;
    case 27:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 1111;
            result.effect_power = 200;
            return result;
        }
        break;
    case 26:
        if (dbmode == item_db_query_t::drink)
        {
            result.effect_id = 1130;
            return result;
        }
        break;
    case 25:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 2;
        }
        if (dbmode == item_db_query_t::read)
        {
            inv[ci].param1 = 2;
            result.read_item = read_item_t::normal_book;
            return result;
        }
        break;
    case 24:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 0;
        }
        if (dbmode == item_db_query_t::read)
        {
            result.read_item = read_item_t::normal_book;
            return result;
        }
        break;
    case 23:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].param1 = 1;
        }
        if (dbmode == item_db_query_t::read)
        {
            inv[ci].param1 = 1;
            result.read_item = read_item_t::normal_book;
            return result;
        }
        break;
    case 22:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 412;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 21:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 411;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 20:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 5 + rnd(5) - rnd(5);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 408;
            result.effect_power = 100;
            result.read_item = read_item_t::decodable_book;
            return result;
        }
        break;
    case 19:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 12 + rnd(12) - rnd(12);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::zap)
        {
            result.effect_id = 409;
            result.effect_power = 100;
            return result;
        }
        break;
    case 18:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].count = 8 + rnd(8) - rnd(8);
            ibitmod(4, ci, 1);
        }
        if (dbmode == item_db_query_t::zap)
        {
            result.effect_id = 411;
            result.effect_power = 100;
            return result;
        }
        break;
    case 17:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 458;
            result.effect_power = 300;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 16:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 408;
            result.effect_power = 100;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 15:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 413;
            result.effect_power = 100;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 14:
        if (dbmode == item_db_query_t::read)
        {
            result.effect_id = 411;
            result.effect_power = 100;
            result.read_item = read_item_t::scroll;
            return result;
        }
        break;
    case 6:
        if (dbmode == item_db_query_t::initialize)
        {
            fixeditemenc(0) = 33;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
        }
        break;
    case 4:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 103;
        }
        break;
    case 3:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 102;
        }
        break;
    case 2:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 101;
        }
        break;
    case 1:
        if (dbmode == item_db_query_t::initialize)
        {
            inv[ci].skill = 100;
        }
        break;
    default: break;
    }

    return result;
}



} // namespace elona
