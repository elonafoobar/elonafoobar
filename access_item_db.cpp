#include <unordered_map>
#include "character.hpp"
#include "elona.hpp"
#include "item.hpp"
#include "item_db.hpp"
#include "filesystem.hpp"
#include "variables.hpp"



namespace elona
{


int access_item_db(int dbmode)
{
    const auto info = the_item_db[dbid];
    if (info)
    {
        if (dbmode == 10 || dbmode == 3)
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
            if (dbmode == 10)
                return 0;
        }
        else if (dbmode == 2)
        {
            ichargelevel = info->chargelevel;
            reftype = info->category;
            return 0;
        }
        else if (dbmode == 17)
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
            return 0;
        }
    }
    else
    {
        return -999;
    }

    if (dbmode == 3)
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
        if (dbmode == 3)
        {
            inv[ci].param2 = 8;
        }
        break;
    case 791:
        if (dbmode == 3)
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
        if (dbmode == 3)
        {
            inv[ci].function = 15;
        }
        break;
    case 789:
        if (dbmode == 3)
        {
            inv[ci].function = 15;
        }
        break;
    case 788:
        if (dbmode == 3)
        {
            inv[ci].skill = 108;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::lulwy;
        }
        break;
    case 787:
        if (dbmode == 3)
        {
            inv[ci].param2 = 5;
            inv[ci].param3 = 720;
        }
        break;
    case 786:
        if (dbmode == 3)
        {
            inv[ci].param2 = 4;
        }
        break;
    case 785:
        if (dbmode == 3)
        {
            inv[ci].param2 = 1;
        }
        break;
    case 783:
        if (dbmode == 13)
        {
            decode_book();
            return -1;
        }
        break;
    case 781:
        if (dbmode == 3)
        {
            inv[ci].skill = 101;
        }
        break;
    case 778:
        if (dbmode == 3)
        {
            inv[ci].function = 44;
        }
        break;
    case 777:
        if (dbmode == 3)
        {
            inv[ci].function = 26;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv[ci].param3 = 240;
            fixlv = 6;
        }
        break;
    case 776:
        if (dbmode == 3)
        {
            inv[ci].function = 26;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv[ci].param3 = 240;
            fixlv = 6;
        }
        break;
    case 775:
        if (dbmode == 3)
        {
            ibitmod(5, ci, 1);
            inv[ci].param2 = 8;
        }
        break;
    case 772:
        if (dbmode == 3)
        {
            inv[ci].param1 = 2000;
            inv[ci].param3 = 32;
        }
        break;
    case 771:
        if (dbmode == 3)
        {
            fixlv = 6;
        }
        if (dbmode == 15)
        {
            efid = 1147;
            efp = 100;
            drink_potion();
            return -1;
        }
        break;
    case 770:
        if (dbmode == 15)
        {
            efid = 1146;
            efp = 100;
            drink_potion();
            return -1;
        }
        break;
    case 767:
        if (dbmode == 3)
        {
            inv[ci].param1 = 0;
        }
        break;
    case 761:
        if (dbmode == 3)
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
        if (dbmode == 3)
        {
            inv[ci].function = 49;
            ibitmod(5, ci, 1);
            inv[ci].param1 = rnd(20000) + 1;
            fixlv = 6;
        }
        break;
    case 759:
        if (dbmode == 3)
        {
            inv[ci].skill = 100;
        }
        break;
    case 758:
        if (dbmode == 3)
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
        if (dbmode == 3)
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
        if (dbmode == 3)
        {
            inv[ci].param2 = 7;
        }
        break;
    case 755:
        if (dbmode == 3)
        {
            inv[ci].param2 = 6;
        }
        break;
    case 749:
        if (dbmode == 3)
        {
            inv[ci].function = 48;
            ibitmod(5, ci, 1);
        }
        break;
    case 748:
        if (dbmode == 3)
        {
            inv[ci].function = 47;
            ibitmod(5, ci, 1);
            ibitmod(16, ci, 1);
        }
        break;
    case 747:
        if (dbmode == 3)
        {
            inv[ci].param1 = 1;
            inv[ci].param2 = rnd(4) + 1;
        }
        if (dbmode == 13)
        {
            read_normal_book();
            return -1;
        }
        break;
    case 746:
        if (dbmode == 3)
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
        if (dbmode == 3)
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
        if (dbmode == 3)
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
        if (dbmode == 3)
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
        if (dbmode == 3)
        {
            ibitmod(5, ci, 1);
            fixlv = 6;
        }
        if (dbmode == 13)
        {
            read_normal_book();
            return -1;
        }
        break;
    case 741:
        if (dbmode == 3)
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
        if (dbmode == 3)
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
        if (dbmode == 3)
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
        if (dbmode == 3)
        {
            inv[ci].param2 = 6;
        }
        break;
    case 737:
        if (dbmode == 13)
        {
            efid = 1145;
            efp = 100;
            read_scroll();
            return -1;
        }
        break;
    case 736:
        if (dbmode == 15)
        {
            efid = 1116;
            efp = 250;
            drink_potion();
            return -1;
        }
        break;
    case 735:
        if (dbmode == 3)
        {
            inv[ci].skill = 107;
            fixeditemenc(0) = 80025;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
        }
        break;
    case 733:
        if (dbmode == 3)
        {
            inv[ci].function = 45;
        }
        break;
    case 732:
        if (dbmode == 3)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 464;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 731:
        if (dbmode == 3)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 463;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 730:
        if (dbmode == 3)
        {
            ibitmod(5, ci, 1);
        }
        break;
    case 728:
        if (dbmode == 3)
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
        if (dbmode == 3)
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
        if (dbmode == 3)
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
        if (dbmode == 3)
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
        if (dbmode == 3)
        {
            ibitmod(5, ci, 1);
        }
        break;
    case 723:
        if (dbmode == 3)
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
        if (dbmode == 3)
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
        if (dbmode == 3)
        {
            inv[ci].function = 43;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv[ci].param3 = 480;
            fixlv = 6;
        }
        break;
    case 720:
        if (dbmode == 3)
        {
            inv[ci].param1 = 200;
        }
        break;
    case 719:
        if (dbmode == 3)
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
        if (dbmode == 3)
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
        if (dbmode == 3)
        {
            inv[ci].function = 42;
        }
        break;
    case 716:
        if (dbmode == 3)
        {
            inv[ci].skill = 111;
            ibitmod(5, ci, 1);
            inv[ci].difficulty_of_identification = 500;
            fixlv = 6;
        }
        break;
    case 715:
        if (dbmode == 3)
        {
            inv[ci].function = 41;
        }
        break;
    case 714:
        if (dbmode == 3)
        {
            inv[ci].skill = 111;
            fixeditemenc(0) = 80024;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
        }
        break;
    case 713:
        if (dbmode == 3)
        {
            inv[ci].skill = 111;
            fixeditemenc(0) = 70061;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
        }
        break;
    case 712:
        if (dbmode == 13)
        {
            efid = 1115;
            return -1;
        }
        break;
    case 711:
        if (dbmode == 15)
        {
            efid = 1144;
            efp = 100;
            drink_potion();
            return -1;
        }
        break;
    case 710:
        if (dbmode == 3)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 462;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 709:
        if (dbmode == 13)
        {
            efid = 462;
            efp = 1500;
            read_scroll();
            return -1;
        }
        break;
    case 708:
        if (dbmode == 13)
        {
            efid = 461;
            efp = 2500;
            read_scroll();
            return -1;
        }
        break;
    case 707:
        if (dbmode == 3)
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
        if (dbmode == 15)
        {
            efid = 1143;
            efp = 100;
            drink_potion();
            return -1;
        }
        break;
    case 705:
        if (dbmode == 3)
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
        if (dbmode == 15)
        {
            efid = 1130;
            efp = 100;
            drink_potion();
            return -1;
        }
        break;
    case 703:
        if (dbmode == 3)
        {
            inv[ci].function = 39;
        }
        break;
    case 702:
        if (dbmode == 3)
        {
            ibitmod(5, ci, 1);
            inv[ci].param2 = 4;
            fixlv = 6;
        }
        break;
    case 701:
        if (dbmode == 3)
        {
            inv[ci].function = 37;
        }
        break;
    case 700:
        if (dbmode == 13)
        {
            menucycle = 1;
            show_city_chart();
            return -1;
        }
        break;
    case 699:
        if (dbmode == 3)
        {
            ibitmod(5, ci, 1);
        }
        break;
    case 698:
        if (dbmode == 15)
        {
            efid = 1142;
            efp = 100;
            drink_potion();
            return -1;
        }
        break;
    case 697:
        if (dbmode == 3)
        {
            inv[ci].count = 2 + rnd(2) - rnd(2);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 459;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 696:
        if (dbmode == 3)
        {
            inv[ci].count = 2 + rnd(2) - rnd(2);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 460;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 695:
        if (dbmode == 3)
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
        if (dbmode == 3)
        {
            inv[ci].skill = 183;
            inv[ci].function = 17;
            inv[ci].param1 = 175;
        }
        break;
    case 692:
        if (dbmode == 3)
        {
            inv[ci].skill = 183;
            inv[ci].function = 17;
            inv[ci].param1 = 70;
        }
        break;
    case 691:
        if (dbmode == 3)
        {
            inv[ci].skill = 183;
            inv[ci].function = 17;
            inv[ci].param1 = 130;
        }
        break;
    case 690:
        if (dbmode == 3)
        {
            inv[ci].skill = 183;
            inv[ci].function = 17;
            inv[ci].param1 = 150;
        }
        break;
    case 689:
        if (dbmode == 3)
        {
            inv[ci].function = 36;
        }
        break;
    case 688:
        if (dbmode == 3)
        {
            inv[ci].function = 35;
        }
        break;
    case 687:
        if (dbmode == 3)
        {
            inv[ci].count = 2 + rnd(2) - rnd(2);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            decode_book();
            return -1;
        }
        break;
    case 686:
        if (dbmode == 3)
        {
            inv[ci].function = 34;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv[ci].param3 = 720;
            fixlv = 6;
        }
        break;
    case 685:
        if (dbmode == 3)
        {
            inv[ci].function = 33;
        }
        break;
    case 684:
        if (dbmode == 3)
        {
            inv[ci].function = 32;
            ibitmod(5, ci, 1);
        }
        break;
    case 683:
        if (dbmode == 3)
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
        if (dbmode == 3)
        {
            inv[ci].function = 31;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv[ci].param3 = 72;
            fixlv = 6;
        }
        break;
    case 681:
        if (dbmode == 3)
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
        if (dbmode == 3)
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
        if (dbmode == 3)
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
        if (dbmode == 3)
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
        if (dbmode == 3)
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
        if (dbmode == 3)
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
        if (dbmode == 3)
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
        if (dbmode == 3)
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
        if (dbmode == 3)
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
        if (dbmode == 3)
        {
            inv[ci].function = 29;
            ibitmod(5, ci, 1);
            fixlv = 6;
        }
        break;
    case 671:
        if (dbmode == 3)
        {
            inv[ci].function = 28;
            ibitmod(5, ci, 1);
            fixlv = 6;
        }
        break;
    case 670:
        if (dbmode == 3)
        {
            inv[ci].param1 = 7;
        }
        break;
    case 669:
        if (dbmode == 3)
        {
            inv[ci].param1 = 7;
        }
        break;
    case 668:
        if (dbmode == 3)
        {
            inv[ci].param1 = 1;
            inv[ci].param2 = rnd(4) + 1;
        }
        if (dbmode == 13)
        {
            read_normal_book();
            return -1;
        }
        break;
    case 667:
        if (dbmode == 3)
        {
            inv[ci].param2 = 7;
        }
        break;
    case 666:
        if (dbmode == 3)
        {
            inv[ci].function = 27;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv[ci].param3 = 120;
            fixlv = 6;
        }
        break;
    case 665:
        if (dbmode == 3)
        {
            inv[ci].function = 26;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv[ci].param3 = 240;
            fixlv = 6;
        }
        break;
    case 664:
        if (dbmode == 3)
        {
            fixeditemenc(0) = 10018;
            fixeditemenc(1) = 400 + rnd((rnd(1000) + 1));
            fixeditemenc(2) = 0;
        }
        break;
    case 663:
        if (dbmode == 3)
        {
            ibitmod(5, ci, 1);
            fixlv = 6;
        }
        break;
    case 662:
        if (dbmode == 3)
        {
            ibitmod(5, ci, 1);
            inv[ci].param2 = 7;
            fixlv = 6;
        }
        break;
    case 661:
        if (dbmode == 3)
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
        if (dbmode == 3)
        {
            inv[ci].count = 5 + rnd(5) - rnd(5);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 418;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 655:
        if (dbmode == 3)
        {
            ibitmod(5, ci, 1);
            inv[ci].param2 = 7;
            fixlv = 6;
        }
        break;
    case 654:
        if (dbmode == 3)
        {
            inv[ci].param1 = 160;
        }
        break;
    case 650:
        if (dbmode == 15)
        {
            drink_well();
            return -1;
        }
        break;
    case 648:
        if (dbmode == 3)
        {
            inv[ci].function = 44;
        }
        break;
    case 643:
        if (dbmode == 3)
        {
            inv[ci].param1 = 130;
        }
        break;
    case 641:
        if (dbmode == 3)
        {
            ibitmod(5, ci, 1);
            fixlv = 6;
        }
        break;
    case 640:
        if (dbmode == 3)
        {
            inv[ci].function = 25;
        }
        break;
    case 639:
        if (dbmode == 3)
        {
            ibitmod(5, ci, 1);
            inv[ci].param2 = 7;
            fixlv = 6;
        }
        break;
    case 638:
        if (dbmode == 13)
        {
            efid = 1141;
            efp = 100;
            read_scroll();
            return -1;
        }
        break;
    case 637:
        if (dbmode == 3)
        {
            ibitmod(5, ci, 1);
            fixlv = 6;
        }
        break;
    case 635:
        if (dbmode == 3)
        {
            inv[ci].function = 24;
        }
        break;
    case 634:
        if (dbmode == 3)
        {
            inv[ci].function = 23;
        }
        break;
    case 633:
        if (dbmode == 3)
        {
            inv[ci].skill = 111;
            fixeditemenc(0) = 70054;
            fixeditemenc(1) = 800;
            fixeditemenc(2) = 0;
        }
        break;
    case 632:
        if (dbmode == 13)
        {
            efid = 1140;
            efp = 150;
            read_scroll();
            return -1;
        }
        break;
    case 630:
        if (dbmode == 3)
        {
            inv[ci].function = 21;
        }
        break;
    case 629:
        if (dbmode == 3)
        {
            inv[ci].function = 20;
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        break;
    case 628:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 458;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 627:
        if (dbmode == 3)
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
        if (dbmode == 3)
        {
            ibitmod(5, ci, 1);
        }
        if (dbmode == 15)
        {
            efid = 1139;
            efp = 500;
            drink_potion();
            return -1;
        }
        break;
    case 625:
        if (dbmode == 3)
        {
            ibitmod(5, ci, 1);
        }
        break;
    case 624:
        if (dbmode == 3)
        {
            ibitmod(5, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 1137;
            efp = 100;
            read_scroll();
            return -1;
        }
        break;
    case 623:
        if (dbmode == 3)
        {
            ibitmod(5, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 1138;
            efp = 100;
            read_scroll();
            return -1;
        }
        break;
    case 622:
        if (dbmode == 3)
        {
            ibitmod(5, ci, 1);
        }
        break;
    case 621:
        if (dbmode == 13)
        {
            efid = 1136;
            efp = 100;
            read_scroll();
            return -1;
        }
        break;
    case 620:
        if (dbmode == 15)
        {
            efid = 1135;
            efp = 100;
            drink_potion();
            return -1;
        }
        break;
    case 618:
        if (dbmode == 3)
        {
            inv[ci].param1 = 6000;
            inv[ci].param3 = 4;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::ehekatl;
        }
        break;
    case 616:
        if (dbmode == 3)
        {
            ibitmod(5, ci, 1);
        }
        break;
    case 615:
        if (dbmode == 3)
        {
            ibitmod(5, ci, 1);
        }
        break;
    case 613:
        if (dbmode == 3)
        {
            inv[ci].param1 = 180;
        }
        break;
    case 611:
        if (dbmode == 3)
        {
            inv[ci].function = 8;
        }
        break;
    case 606:
        if (dbmode == 3)
        {
            inv[ci].function = 15;
            inv[ci].param1 = 225;
        }
        break;
    case 603:
        if (dbmode == 3)
        {
            inv[ci].function = 44;
            ibitmod(5, ci, 1);
        }
        break;
    case 602:
        if (dbmode == 3)
        {
            inv[ci].param2 = 100;
        }
        if (dbmode == 15)
        {
            drink_well();
            return -1;
        }
        break;
    case 600:
        if (dbmode == 3)
        {
            ibitmod(5, ci, 1);
        }
        break;
    case 598:
        if (dbmode == 3)
        {
            inv[ci].param1 = 6;
        }
        break;
    case 597:
        if (dbmode == 3)
        {
            inv[ci].param1 = 6;
        }
        break;
    case 587:
        if (dbmode == 3)
        {
            inv[ci].function = 14;
        }
        if (dbmode == 15)
        {
            efid = 1103;
            efp = 100;
            drink_potion();
            return -1;
        }
        break;
    case 583:
        if (dbmode == 3)
        {
            inv[ci].function = 13;
            inv[ci].param1 = 100;
        }
        break;
    case 582:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 457;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 581:
        if (dbmode == 3)
        {
            inv[ci].count = 6 + rnd(6) - rnd(6);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 14)
        {
            efid = 457;
            efp = 100;
            return -1;
        }
        break;
    case 578:
        if (dbmode == 3)
        {
            inv[ci].function = 11;
        }
        break;
    case 577:
        if (dbmode == 15)
        {
            efid = 1133;
            efp = 100;
            drink_potion();
            return -1;
        }
        break;
    case 576:
        if (dbmode == 3)
        {
            inv[ci].function = 10;
        }
        break;
    case 574:
        if (dbmode == 15)
        {
            efid = 1101;
            efp = 100;
            drink_potion();
            return -1;
        }
        break;
    case 573:
        if (dbmode == 3)
        {
            inv[ci].param1 = 8000;
            inv[ci].param3 = 240;
        }
        break;
    case 572:
        if (dbmode == 13)
        {
            efid = 1115;
            return -1;
        }
        break;
    case 571:
        if (dbmode == 3)
        {
            inv[ci].param2 = 5;
        }
        break;
    case 570:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 14)
        {
            efid = 456;
            efp = 100;
            return -1;
        }
        break;
    case 569:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 456;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 568:
        if (dbmode == 3)
        {
            inv[ci].count = 12 + rnd(12) - rnd(12);
            ibitmod(4, ci, 1);
        }
        break;
    case 567:
        if (dbmode == 3)
        {
            inv[ci].count = 12 + rnd(12) - rnd(12);
            ibitmod(4, ci, 1);
        }
        break;
    case 566:
        if (dbmode == 15)
        {
            efid = 1116;
            efp = 250;
            drink_potion();
            return -1;
        }
        break;
    case 565:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 14)
        {
            efid = 455;
            efp = 100;
            return -1;
        }
        break;
    case 564:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 455;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 563:
        if (dbmode == 3)
        {
            inv[ci].param1 = 0;
        }
        if (dbmode == 13)
        {
            read_normal_book();
            return -1;
        }
        break;
    case 562:
        if (dbmode == 3)
        {
            inv[ci].function = 8;
        }
        break;
    case 560:
        if (dbmode == 3)
        {
            ibitmod(5, ci, 1);
        }
        break;
    case 559:
        if (dbmode == 15)
        {
            efid = 1131;
            efp = 200;
            drink_potion();
            return -1;
        }
        break;
    case 558:
        if (dbmode == 3)
        {
            fixeditemenc(0) = 31;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 20057;
            fixeditemenc(3) = 100;
            fixeditemenc(4) = 0;
        }
        break;
    case 557:
        if (dbmode == 3)
        {
            fixeditemenc(0) = 30;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
        }
        break;
    case 556:
        if (dbmode == 3)
        {
            fixeditemenc(0) = 29;
            fixeditemenc(1) = 500;
            fixeditemenc(2) = 0;
        }
        break;
    case 555:
        if (dbmode == 3)
        {
            inv[ci].function = 7;
        }
        break;
    case 554:
        if (dbmode == 3)
        {
            inv[ci].param2 = 1;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::kumiromi;
        }
        break;
    case 553:
        if (dbmode == 3)
        {
            inv[ci].param2 = 1;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::kumiromi;
        }
        break;
    case 552:
        if (dbmode == 3)
        {
            fixeditemenc(0) = 32;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
        }
        break;
    case 551:
        if (dbmode == 3)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 14)
        {
            efid = 405;
            efp = 100;
            return -1;
        }
        break;
    case 550:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 405;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 549:
        if (dbmode == 13)
        {
            efid = 404;
            efp = 400;
            read_scroll();
            return -1;
        }
        break;
    case 548:
        if (dbmode == 3)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 404;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 546:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 438;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 545:
        if (dbmode == 3)
        {
            inv[ci].count = 7 + rnd(7) - rnd(7);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 14)
        {
            efid = 438;
            efp = 100;
            return -1;
        }
        break;
    case 544:
        if (dbmode == 3)
        {
            inv[ci].function = 6;
            inv[ci].param1 = discsetmc();
        }
        break;
    case 543:
        if (dbmode == 13)
        {
            efid = 1115;
            return -1;
        }
        break;
    case 542:
        if (dbmode == 13)
        {
            efid = 1115;
            return -1;
        }
        break;
    case 526:
        if (dbmode == 3)
        {
            inv[ci].param1 = rnd(5) + 2;
            inv[ci].param2 = isetfruit(rnd(length(isetfruit)));
        }
        break;
    case 522:
        if (dbmode == 3)
        {
            inv[ci].param1 = 1;
        }
        if (dbmode == 13)
        {
            efid = 1115;
            return -1;
        }
        break;
    case 521:
        if (dbmode == 3)
        {
            inv[ci].param1 = 1;
        }
        if (dbmode == 13)
        {
            efid = 1115;
            return -1;
        }
        break;
    case 520:
        if (dbmode == 3)
        {
            fixeditemenc(0) = 32;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
        }
        break;
    case 519:
        if (dbmode == 15)
        {
            efid = 1108;
            efp = 150;
            drink_potion();
            return -1;
        }
        break;
    case 518:
        if (dbmode == 3)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 14)
        {
            efid = 1132;
            efp = 100;
            return -1;
        }
        break;
    case 517:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 14)
        {
            efid = 628;
            efp = 100;
            return -1;
        }
        break;
    case 516:
        if (dbmode == 15)
        {
            efid = 1103;
            efp = 100;
            drink_potion();
            return -1;
        }
        break;
    case 515:
        if (dbmode == 13)
        {
            efid = 1129;
            efp = 300;
            read_scroll();
            return -1;
        }
        break;
    case 514:
        if (dbmode == 3)
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
        if (dbmode == 3)
        {
            inv[ci].skill = 110;
        }
        break;
    case 512:
        if (dbmode == 3)
        {
            inv[ci].skill = 110;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::mani;
        }
        break;
    case 511:
        if (dbmode == 3)
        {
            inv[ci].param1 = 100 + rnd(200);
        }
        if (dbmode == 13)
        {
            efid = 1128;
            efp = inv[ci].param1;
            read_scroll();
            return -1;
        }
        break;
    case 509:
        if (dbmode == 13)
        {
            efid = 1125;
            efp = 400;
            read_scroll();
            return -1;
        }
        break;
    case 508:
        if (dbmode == 13)
        {
            efid = 1125;
            efp = 200;
            read_scroll();
            return -1;
        }
        break;
    case 507:
        if (dbmode == 13)
        {
            efid = 1124;
            efp = 400;
            read_scroll();
            return -1;
        }
        break;
    case 506:
        if (dbmode == 13)
        {
            efid = 1124;
            efp = 200;
            read_scroll();
            return -1;
        }
        break;
    case 505:
        if (dbmode == 3)
        {
            ibitmod(5, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 1123;
            efp = 100;
            read_scroll();
            return -1;
        }
        break;
    case 504:
        if (dbmode == 3)
        {
            inv[ci].function = 38;
        }
        break;
    case 502:
        if (dbmode == 13)
        {
            efid = 1127;
            efp = 350;
            read_scroll();
            return -1;
        }
        break;
    case 501:
        if (dbmode == 13)
        {
            efid = 1127;
            efp = 180;
            read_scroll();
            return -1;
        }
        break;
    case 500:
        if (dbmode == 13)
        {
            efid = 1127;
            efp = 10;
            read_scroll();
            return -1;
        }
        break;
    case 499:
        if (dbmode == 3)
        {
            inv[ci].param2 = 7;
        }
        break;
    case 498:
        if (dbmode == 3)
        {
            inv[ci].param2 = 6;
        }
        break;
    case 497:
        if (dbmode == 3)
        {
            inv[ci].param2 = 5;
        }
        break;
    case 496:
        if (dbmode == 3)
        {
            inv[ci].skill = 110;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::mani;
        }
        break;
    case 495:
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::mani;
        }
        break;
    case 494:
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::mani;
        }
        break;
    case 492:
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::mani;
        }
        break;
    case 491:
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::mani;
        }
        break;
    case 490:
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::mani;
        }
        break;
    case 489:
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::mani;
        }
        break;
    case 488:
        if (dbmode == 3)
        {
            inv[ci].function = 9;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::mani;
        }
        break;
    case 487:
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::mani;
        }
        break;
    case 486:
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::mani;
        }
        break;
    case 485:
        if (dbmode == 3)
        {
            inv[ci].count = 8 + rnd(8) - rnd(8);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 14)
        {
            efid = 436;
            efp = 100;
            return -1;
        }
        break;
    case 484:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 436;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 483:
        if (dbmode == 3)
        {
            inv[ci].skill = 109;
        }
        break;
    case 482:
        if (dbmode == 3)
        {
            inv[ci].skill = 109;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::lulwy;
        }
        break;
    case 481:
        if (dbmode == 3)
        {
            inv[ci].count = 2 + rnd(2) - rnd(2);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 435;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 480:
        if (dbmode == 3)
        {
            inv[ci].count = 2 + rnd(2) - rnd(2);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 14)
        {
            efid = 435;
            efp = 100;
            return -1;
        }
        break;
    case 479:
        if (dbmode == 13)
        {
            efid = 1122;
            efp = 100;
            read_scroll();
            return -1;
        }
        break;
    case 478:
        if (dbmode == 3)
        {
            inv[ci].function = 5;
        }
        break;
    case 454:
        if (dbmode == 3)
        {
            inv[ci].skill = 168;
        }
        break;
    case 453:
        if (dbmode == 3)
        {
            inv[ci].skill = 168;
        }
        break;
    case 452:
        if (dbmode == 3)
        {
            inv[ci].skill = 168;
        }
        break;
    case 451:
        if (dbmode == 3)
        {
            inv[ci].skill = 168;
        }
        break;
    case 450:
        if (dbmode == 3)
        {
            inv[ci].skill = 168;
        }
        break;
    case 449:
        if (dbmode == 3)
        {
            inv[ci].skill = 168;
        }
        break;
    case 434:
        if (dbmode == 3)
        {
            inv[ci].count = 2 + rnd(2) - rnd(2);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 454;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 433:
        if (dbmode == 15)
        {
            efid = 1121;
            efp = 200;
            drink_potion();
            return -1;
        }
        break;
    case 432:
        if (dbmode == 15)
        {
            efid = 454;
            efp = 100;
            drink_potion();
            return -1;
        }
        break;
    case 431:
        if (dbmode == 13)
        {
            efid = 1107;
            efp = 300;
            read_scroll();
            return -1;
        }
        break;
    case 430:
        if (dbmode == 13)
        {
            efid = 1119;
            efp = 500;
            read_scroll();
            return -1;
        }
        break;
    case 429:
        if (dbmode == 15)
        {
            efid = 1118;
            efp = 100;
            drink_potion();
            return -1;
        }
        break;
    case 428:
        if (dbmode == 3)
        {
            inv[ci].param1 = 0;
        }
        break;
    case 427:
        if (dbmode == 3)
        {
            inv[ci].param2 = 7;
        }
        break;
    case 426:
        if (dbmode == 3)
        {
            inv[ci].param2 = 3;
        }
        break;
    case 425:
        if (dbmode == 3)
        {
            inv[ci].param2 = 6;
        }
        break;
    case 424:
        if (dbmode == 3)
        {
            inv[ci].param2 = 3;
        }
        break;
    case 423:
        if (dbmode == 3)
        {
            inv[ci].param2 = 4;
        }
        break;
    case 422:
        if (dbmode == 3)
        {
            inv[ci].param2 = 1;
        }
        break;
    case 421:
        if (dbmode == 3)
        {
            inv[ci].param2 = 1;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::kumiromi;
        }
        break;
    case 420:
        if (dbmode == 3)
        {
            inv[ci].param2 = 1;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::kumiromi;
        }
        break;
    case 419:
        if (dbmode == 3)
        {
            inv[ci].param2 = 1;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::kumiromi;
        }
        break;
    case 418:
        if (dbmode == 3)
        {
            inv[ci].param2 = 1;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::kumiromi;
        }
        break;
    case 417:
        if (dbmode == 3)
        {
            inv[ci].param2 = 1;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::kumiromi;
        }
        break;
    case 412:
        if (dbmode == 3)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 14)
        {
            efid = 412;
            efp = 100;
            return -1;
        }
        break;
    case 411:
        if (dbmode == 13)
        {
            efid = 430;
            efp = 500;
            read_scroll();
            return -1;
        }
        break;
    case 410:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 430;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 409:
        if (dbmode == 3)
        {
            inv[ci].param1 = 5;
        }
        break;
    case 408:
        if (dbmode == 3)
        {
            inv[ci].param1 = 1;
        }
        break;
    case 407:
        if (dbmode == 3)
        {
            inv[ci].param1 = 2;
        }
        break;
    case 406:
        if (dbmode == 3)
        {
            inv[ci].param1 = 0;
        }
        break;
    case 405:
        if (dbmode == 3)
        {
            inv[ci].param1 = 3;
        }
        break;
    case 404:
        if (dbmode == 3)
        {
            inv[ci].param1 = 0;
        }
        break;
    case 403:
        if (dbmode == 3)
        {
            inv[ci].param1 = 3;
        }
        break;
    case 402:
        if (dbmode == 3)
        {
            inv[ci].param1 = 5;
        }
        break;
    case 401:
        if (dbmode == 3)
        {
            inv[ci].param1 = 4;
        }
        break;
    case 400:
        if (dbmode == 3)
        {
            inv[ci].param1 = 2;
        }
        break;
    case 399:
        if (dbmode == 3)
        {
            inv[ci].param1 = 1;
        }
        break;
    case 398:
        if (dbmode == 13)
        {
            efid = 453;
            efp = 250;
            read_scroll();
            return -1;
        }
        break;
    case 397:
        if (dbmode == 3)
        {
            inv[ci].count = 5 + rnd(5) - rnd(5);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 453;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 396:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 452;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 395:
        if (dbmode == 13)
        {
            efid = 1117;
            efp = 250;
            read_scroll();
            return -1;
        }
        break;
    case 393:
        if (dbmode == 3)
        {
            inv[ci].function = 3;
        }
        break;
    case 392:
        if (dbmode == 15)
        {
            efid = 1116;
            efp = 100;
            drink_potion();
            return -1;
        }
        break;
    case 391:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 14)
        {
            efid = 621;
            efp = 100;
            return -1;
        }
        break;
    case 390:
        if (dbmode == 13)
        {
            efid = 621;
            efp = 250;
            read_scroll();
            return -1;
        }
        break;
    case 389:
        if (dbmode == 13)
        {
            efid = 407;
            efp = 300;
            read_scroll();
            return -1;
        }
        break;
    case 388:
        if (dbmode == 13)
        {
            efid = 406;
            efp = 300;
            read_scroll();
            return -1;
        }
        break;
    case 387:
        if (dbmode == 3)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 407;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 386:
        if (dbmode == 3)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 406;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 385:
        if (dbmode == 3)
        {
            inv[ci].count = 6 + rnd(6) - rnd(6);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 14)
        {
            efid = 407;
            efp = 100;
            return -1;
        }
        break;
    case 384:
        if (dbmode == 13)
        {
            efid = 451;
            efp = 250;
            read_scroll();
            return -1;
        }
        break;
    case 383:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 451;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 382:
        if (dbmode == 15)
        {
            efid = 449;
            efp = 250;
            drink_potion();
            return -1;
        }
        break;
    case 381:
        if (dbmode == 3)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 450;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 380:
        if (dbmode == 3)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 449;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 379:
        if (dbmode == 15)
        {
            efid = 448;
            efp = 250;
            drink_potion();
            return -1;
        }
        break;
    case 378:
        if (dbmode == 3)
        {
            inv[ci].count = 5 + rnd(5) - rnd(5);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 448;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 377:
        if (dbmode == 3)
        {
            inv[ci].count = 8 + rnd(8) - rnd(8);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 14)
        {
            efid = 446;
            efp = 100;
            return -1;
        }
        break;
    case 376:
        if (dbmode == 15)
        {
            efid = 447;
            efp = 400;
            drink_potion();
            return -1;
        }
        break;
    case 375:
        if (dbmode == 15)
        {
            efid = 446;
            efp = 250;
            drink_potion();
            return -1;
        }
        break;
    case 374:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 447;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 373:
        if (dbmode == 3)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 446;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 372:
        if (dbmode == 15)
        {
            efid = 445;
            efp = 250;
            drink_potion();
            return -1;
        }
        break;
    case 371:
        if (dbmode == 3)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 445;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 370:
        if (dbmode == 15)
        {
            efid = 444;
            efp = 300;
            drink_potion();
            return -1;
        }
        break;
    case 369:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 444;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 368:
        if (dbmode == 15)
        {
            efid = 443;
            efp = 400;
            drink_potion();
            return -1;
        }
        break;
    case 367:
        if (dbmode == 3)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 443;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 366:
        if (dbmode == 3)
        {
            inv[ci].count = 7 + rnd(7) - rnd(7);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 14)
        {
            efid = 443;
            efp = 100;
            return -1;
        }
        break;
    case 365:
        if (dbmode == 3)
        {
            inv[ci].count = 5 + rnd(5) - rnd(5);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 442;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 364:
        if (dbmode == 15)
        {
            efid = 442;
            efp = 200;
            drink_potion();
            return -1;
        }
        break;
    case 363:
        if (dbmode == 13)
        {
            efid = 412;
            efp = 2500;
            read_scroll();
            return -1;
        }
        break;
    case 362:
        if (dbmode == 13)
        {
            efid = 411;
            efp = 2000;
            read_scroll();
            return -1;
        }
        break;
    case 360:
        if (dbmode == 3)
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
        if (dbmode == 3)
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
        if (dbmode == 3)
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
        if (dbmode == 3)
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
        if (dbmode == 3)
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
        if (dbmode == 3)
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
        if (dbmode == 3)
        {
            inv[ci].param1 = 6000;
            inv[ci].param3 = 4;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::ehekatl;
        }
        break;
    case 353:
        if (dbmode == 3)
        {
            inv[ci].param1 = 6000;
            inv[ci].param3 = 4;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::ehekatl;
        }
        break;
    case 352:
        if (dbmode == 3)
        {
            inv[ci].param1 = 6000;
            inv[ci].param3 = 4;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::ehekatl;
        }
        break;
    case 351:
        if (dbmode == 3)
        {
            inv[ci].param1 = 6000;
            inv[ci].param3 = 4;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::ehekatl;
        }
        break;
    case 350:
        if (dbmode == 3)
        {
            inv[ci].param1 = 6000;
            inv[ci].param3 = 4;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::ehekatl;
        }
        break;
    case 349:
        if (dbmode == 3)
        {
            inv[ci].param1 = 6000;
            inv[ci].param3 = 4;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::ehekatl;
        }
        break;
    case 348:
        if (dbmode == 3)
        {
            inv[ci].param1 = 6000;
            inv[ci].param3 = 4;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::ehekatl;
        }
        break;
    case 347:
        if (dbmode == 3)
        {
            inv[ci].param1 = 6000;
            inv[ci].param3 = 4;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::ehekatl;
        }
        break;
    case 346:
        if (dbmode == 3)
        {
            inv[ci].param1 = 6000;
            inv[ci].param3 = 4;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::ehekatl;
        }
        break;
    case 345:
        if (dbmode == 3)
        {
            inv[ci].param1 = 6000;
            inv[ci].param3 = 4;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::ehekatl;
        }
        break;
    case 344:
        if (dbmode == 3)
        {
            inv[ci].param1 = 1;
        }
        if (dbmode == 13)
        {
            efid = 1115;
            return -1;
        }
        break;
    case 343:
        if (dbmode == 3)
        {
            inv[ci].function = 22;
        }
        break;
    case 342:
        if (dbmode == 3)
        {
            inv[ci].function = 16;
            inv[ci].param1 = 60;
        }
        break;
    case 334:
        if (dbmode == 3)
        {
            inv[ci].function = 44;
        }
        break;
    case 333:
        if (dbmode == 3)
        {
            inv[ci].param2 = 3;
        }
        break;
    case 330:
        if (dbmode == 3)
        {
            inv[ci].function = 44;
        }
        break;
    case 328:
        if (dbmode == 3)
        {
            inv[ci].function = 17;
            inv[ci].param1 = 150;
        }
        break;
    case 327:
        if (dbmode == 3)
        {
            inv[ci].function = 44;
        }
        break;
    case 325:
        if (dbmode == 3)
        {
            inv[ci].param1 = 130;
        }
        break;
    case 322:
        if (dbmode == 3)
        {
            inv[ci].function = 19;
        }
        break;
    case 319:
        if (dbmode == 3)
        {
            inv[ci].param1 = 0;
        }
        break;
    case 310:
        if (dbmode == 3)
        {
            inv[ci].param1 = 130;
        }
        break;
    case 309:
        if (dbmode == 3)
        {
            inv[ci].function = 19;
        }
        break;
    case 307:
        if (dbmode == 3)
        {
            inv[ci].param1 = 130;
        }
        break;
    case 306:
        if (dbmode == 3)
        {
            inv[ci].function = 15;
            inv[ci].param1 = 200;
        }
        break;
    case 305:
        if (dbmode == 3)
        {
            inv[ci].param1 = 130;
        }
        break;
    case 304:
        if (dbmode == 3)
        {
            inv[ci].param1 = 100;
        }
        break;
    case 303:
        if (dbmode == 3)
        {
            inv[ci].param1 = 120;
        }
        break;
    case 299:
        if (dbmode == 3)
        {
            inv[ci].function = 19;
        }
        break;
    case 297:
        if (dbmode == 3)
        {
            inv[ci].param1 = 150;
        }
        break;
    case 290:
        if (dbmode == 3)
        {
            inv[ci].count = 1 + rnd(1) - rnd(1);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 14)
        {
            efid = 441;
            efp = 100;
            return -1;
        }
        break;
    case 289:
        if (dbmode == 3)
        {
            inv[ci].count = 1 + rnd(1) - rnd(1);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 441;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 288:
        if (dbmode == 13)
        {
            efid = 1114;
            efp = 100;
            read_scroll();
            return -1;
        }
        break;
    case 287:
        if (dbmode == 15)
        {
            efid = 1113;
            efp = 100;
            drink_potion();
            return -1;
        }
        break;
    case 286:
        if (dbmode == 15)
        {
            efid = 440;
            efp = 100;
            drink_potion();
            return -1;
        }
        break;
    case 285:
        if (dbmode == 15)
        {
            efid = 439;
            efp = 100;
            drink_potion();
            return -1;
        }
        break;
    case 272:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 433;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 271:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 434;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 270:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 432;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 269:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 431;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 268:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 423;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 267:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 422;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 266:
        if (dbmode == 3)
        {
            inv[ci].skill = 101;
        }
        break;
    case 265:
        if (dbmode == 3)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 416;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 264:
        if (dbmode == 3)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 417;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 263:
        if (dbmode == 3)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 415;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 262:
        if (dbmode == 15)
        {
            efid = 1108;
            efp = 200;
            drink_potion();
            return -1;
        }
        break;
    case 261:
        if (dbmode == 3)
        {
            inv[ci].param1 = 6000;
            inv[ci].param3 = 6;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::ehekatl;
        }
        break;
    case 260:
        if (dbmode == 3)
        {
            inv[ci].param1 = 7000;
            inv[ci].param3 = 240;
        }
        break;
    case 259:
        if (dbmode == 3)
        {
            inv[ci].param1 = 5000;
            inv[ci].param3 = 24;
        }
        break;
    case 258:
        if (dbmode == 3)
        {
            inv[ci].param2 = 3;
        }
        break;
    case 257:
        if (dbmode == 3)
        {
            inv[ci].count = 5 + rnd(5) - rnd(5);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 414;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 256:
        if (dbmode == 3)
        {
            inv[ci].function = 15;
            inv[ci].param1 = 80;
        }
        break;
    case 255:
        if (dbmode == 3)
        {
            inv[ci].function = 15;
            inv[ci].param1 = 40;
        }
        break;
    case 254:
        if (dbmode == 3)
        {
            inv[ci].skill = 183;
            inv[ci].function = 17;
            inv[ci].param1 = 110;
        }
        break;
    case 253:
        if (dbmode == 15)
        {
            efid = 1102;
            efp = 200;
            drink_potion();
            return -1;
        }
        break;
    case 252:
        if (dbmode == 3)
        {
            inv[ci].count = 2 + rnd(2) - rnd(2);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 403;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 251:
        if (dbmode == 3)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 402;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 250:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 401;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 249:
        if (dbmode == 3)
        {
            inv[ci].count = 5 + rnd(5) - rnd(5);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 400;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 248:
        if (dbmode == 3)
        {
            inv[ci].count = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 428;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 247:
        if (dbmode == 3)
        {
            inv[ci].count = 2 + rnd(2) - rnd(2);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 413;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 246:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 429;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 245:
        if (dbmode == 13)
        {
            efid = 408;
            efp = 100;
            read_scroll();
            return -1;
        }
        break;
    case 244:
        if (dbmode == 13)
        {
            efid = 1104;
            efp = 100;
            read_scroll();
            return -1;
        }
        break;
    case 243:
        if (dbmode == 13)
        {
            efid = 1105;
            efp = 100;
            read_scroll();
            return -1;
        }
        break;
    case 242:
        if (dbmode == 13)
        {
            efid = 429;
            efp = 500;
            read_scroll();
            return -1;
        }
        break;
    case 236:
        if (dbmode == 13)
        {
            efid = 428;
            efp = 100;
            read_scroll();
            return -1;
        }
        break;
    case 235:
        if (dbmode == 3)
        {
            inv[ci].skill = 104;
        }
        break;
    case 234:
        if (dbmode == 3)
        {
            inv[ci].skill = 102;
        }
        break;
    case 233:
        if (dbmode == 3)
        {
            inv[ci].param2 = 3;
        }
        break;
    case 232:
        if (dbmode == 3)
        {
            inv[ci].skill = 100;
        }
        break;
    case 231:
        if (dbmode == 3)
        {
            inv[ci].skill = 110;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::mani;
        }
        break;
    case 230:
        if (dbmode == 3)
        {
            inv[ci].skill = 108;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::lulwy;
        }
        break;
    case 229:
        if (dbmode == 3)
        {
            inv[ci].skill = 105;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::itzpalt;
        }
        break;
    case 228:
        if (dbmode == 3)
        {
            inv[ci].skill = 104;
        }
        break;
    case 227:
        if (dbmode == 3)
        {
            inv[ci].skill = 103;
        }
        break;
    case 226:
        if (dbmode == 3)
        {
            inv[ci].skill = 102;
        }
        break;
    case 225:
        if (dbmode == 3)
        {
            inv[ci].skill = 101;
        }
        break;
    case 224:
        if (dbmode == 3)
        {
            inv[ci].skill = 100;
        }
        break;
    case 223:
        if (dbmode == 3)
        {
            inv[ci].function = 15;
            inv[ci].param1 = 60;
        }
        break;
    case 219:
        if (dbmode == 3)
        {
            inv[ci].function = 46;
        }
        break;
    case 213:
        if (dbmode == 3)
        {
            inv[ci].skill = 104;
        }
        break;
    case 212:
        if (dbmode == 3)
        {
            inv[ci].skill = 105;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::itzpalt;
        }
        break;
    case 211:
        if (dbmode == 3)
        {
            inv[ci].skill = 107;
            fixeditemenc(0) = 80025;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
        }
        break;
    case 210:
        if (dbmode == 3)
        {
            inv[ci].skill = 111;
        }
        break;
    case 209:
        if (dbmode == 13)
        {
            efid = 412;
            efp = 100;
            read_scroll();
            return -1;
        }
        break;
    case 207:
        if (dbmode == 3)
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
        if (dbmode == 3)
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
        if (dbmode == 15)
        {
            efid = 1102;
            efp = 500;
            drink_potion();
            return -1;
        }
        break;
    case 204:
        if (dbmode == 3)
        {
            inv[ci].param1 = 1000;
            inv[ci].param3 = 4;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return 1;
        }
        break;
    case 203:
        if (dbmode == 3)
        {
            inv[ci].count = 8 + rnd(8) - rnd(8);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 14)
        {
            efid = 401;
            efp = 100;
            return -1;
        }
        break;
    case 202:
        if (dbmode == 3)
        {
            inv[ci].count = 9 + rnd(9) - rnd(9);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 14)
        {
            efid = 429;
            efp = 100;
            return -1;
        }
        break;
    case 201:
        if (dbmode == 3)
        {
            inv[ci].param1 = 2000;
            inv[ci].param3 = 2;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::kumiromi;
        }
        break;
    case 200:
        if (dbmode == 3)
        {
            inv[ci].param1 = 2000;
            inv[ci].param3 = 72;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::kumiromi;
        }
        break;
    case 199:
        if (dbmode == 3)
        {
            inv[ci].param1 = 2000;
            inv[ci].param3 = 72;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::kumiromi;
        }
        break;
    case 198:
        if (dbmode == 3)
        {
            inv[ci].param1 = 2000;
            inv[ci].param3 = 72;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::kumiromi;
        }
        break;
    case 197:
        if (dbmode == 3)
        {
            inv[ci].param1 = 3000;
            inv[ci].param3 = 12;
        }
        break;
    case 196:
        if (dbmode == 3)
        {
            inv[ci].param1 = 3000;
            inv[ci].param3 = 8;
        }
        break;
    case 195:
        if (dbmode == 3)
        {
            inv[ci].param1 = 3000;
            inv[ci].param3 = 12;
        }
        break;
    case 194:
        if (dbmode == 3)
        {
            inv[ci].param1 = 3000;
            inv[ci].param3 = 8;
        }
        break;
    case 193:
        if (dbmode == 3)
        {
            inv[ci].param1 = 2000;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::kumiromi;
        }
        break;
    case 192:
        if (dbmode == 3)
        {
            inv[ci].param1 = 3000;
            inv[ci].param3 = 16;
        }
        break;
    case 191:
        if (dbmode == 3)
        {
            inv[ci].param1 = 4000;
        }
        break;
    case 190:
        if (dbmode == 3)
        {
            inv[ci].param1 = 2000;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::kumiromi;
        }
        break;
    case 188:
        if (dbmode == 3)
        {
            inv[ci].param1 = 2000;
            inv[ci].param3 = 72;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::kumiromi;
        }
        break;
    case 187:
        if (dbmode == 3)
        {
            inv[ci].param1 = 2000;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::kumiromi;
        }
        break;
    case 186:
        if (dbmode == 3)
        {
            inv[ci].param1 = 2000;
            inv[ci].param3 = 72;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::kumiromi;
        }
        break;
    case 185:
        if (dbmode == 3)
        {
            inv[ci].param1 = 2000;
            inv[ci].param3 = 72;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::kumiromi;
        }
        break;
    case 184:
        if (dbmode == 3)
        {
            inv[ci].param1 = 3000;
            inv[ci].param3 = 8;
        }
        break;
    case 183:
        if (dbmode == 3)
        {
            inv[ci].param1 = 3000;
            inv[ci].param3 = 16;
        }
        break;
    case 182:
        if (dbmode == 3)
        {
            inv[ci].param1 = 3000;
            inv[ci].param3 = 12;
        }
        break;
    case 181:
        if (dbmode == 3)
        {
            inv[ci].param1 = 3000;
            inv[ci].param3 = 16;
        }
        break;
    case 180:
        if (dbmode == 3)
        {
            inv[ci].param1 = 3000;
            inv[ci].param3 = 16;
        }
        break;
    case 179:
        if (dbmode == 3)
        {
            inv[ci].param1 = 2000;
            inv[ci].param3 = 48;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::kumiromi;
        }
        break;
    case 178:
        if (dbmode == 3)
        {
            inv[ci].param1 = 3000;
            inv[ci].param3 = 72;
        }
        break;
    case 177:
        if (dbmode == 3)
        {
            inv[ci].param1 = 3000;
            inv[ci].param3 = 72;
        }
        break;
    case 176:
        if (dbmode == 3)
        {
            inv[ci].count = 8 + rnd(8) - rnd(8);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 14)
        {
            efid = 447;
            efp = 100;
            return -1;
        }
        break;
    case 175:
        if (dbmode == 3)
        {
            inv[ci].count = 10 + rnd(10) - rnd(10);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 14)
        {
            efid = 421;
            efp = 100;
            return -1;
        }
        break;
    case 174:
        if (dbmode == 3)
        {
            inv[ci].param1 = 110;
        }
        break;
    case 173:
        if (dbmode == 3)
        {
            inv[ci].param2 = 100;
        }
        if (dbmode == 15)
        {
            drink_well();
            return -1;
        }
        break;
    case 161:
        if (dbmode == 3)
        {
            inv[ci].function = 1;
        }
        break;
    case 160:
        if (dbmode == 3)
        {
            inv[ci].function = 4;
        }
        break;
    case 155:
        if (dbmode == 3)
        {
            inv[ci].function = 15;
            inv[ci].param1 = 100;
        }
        break;
    case 154:
        if (dbmode == 3)
        {
            inv[ci].function = 15;
            inv[ci].param1 = 100;
        }
        break;
    case 153:
        if (dbmode == 3)
        {
            inv[ci].function = 15;
            inv[ci].param1 = 100;
        }
        break;
    case 142:
        if (dbmode == 3)
        {
            inv[ci].function = 15;
            inv[ci].param1 = 200;
        }
        break;
    case 127:
        if (dbmode == 3)
        {
            inv[ci].function = 2;
        }
        break;
    case 125:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 14)
        {
            efid = 402;
            efp = 100;
            return -1;
        }
        break;
    case 123:
        if (dbmode == 3)
        {
            inv[ci].count = 10 + rnd(10) - rnd(10);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 14)
        {
            efid = 420;
            efp = 100;
            return -1;
        }
        break;
    case 122:
        if (dbmode == 3)
        {
            inv[ci].count = 8 + rnd(8) - rnd(8);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 14)
        {
            efid = 419;
            efp = 100;
            return -1;
        }
        break;
    case 121:
        if (dbmode == 3)
        {
            inv[ci].count = 8 + rnd(8) - rnd(8);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 14)
        {
            efid = 424;
            efp = 100;
            return -1;
        }
        break;
    case 120:
        if (dbmode == 3)
        {
            inv[ci].count = 10 + rnd(10) - rnd(10);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 14)
        {
            efid = 414;
            efp = 100;
            return -1;
        }
        break;
    case 119:
        if (dbmode == 3)
        {
            inv[ci].count = 8 + rnd(8) - rnd(8);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 14)
        {
            efid = 400;
            efp = 100;
            return -1;
        }
        break;
    case 118:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 424;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 116:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 410;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 112:
        if (dbmode == 3)
        {
            inv[ci].function = 15;
            inv[ci].param1 = 150;
        }
        break;
    case 109:
        if (dbmode == 3)
        {
            inv[ci].param2 = 100;
        }
        if (dbmode == 15)
        {
            drink_well();
            return -1;
        }
        break;
    case 102:
        if (dbmode == 3)
        {
            inv[ci].function = 44;
        }
        break;
    case 101:
        if (dbmode == 3)
        {
            inv[ci].function = 44;
        }
        break;
    case 92:
        if (dbmode == 3)
        {
            inv[ci].function = 44;
        }
        break;
    case 88:
        if (dbmode == 3)
        {
            inv[ci].skill = 183;
            inv[ci].function = 17;
            inv[ci].param1 = 200;
        }
        break;
    case 81:
        if (dbmode == 3)
        {
            inv[ci].function = 44;
        }
        break;
    case 80:
        if (dbmode == 3)
        {
            inv[ci].param1 = 100;
        }
        break;
    case 77:
        if (dbmode == 3)
        {
            inv[ci].function = 44;
        }
        break;
    case 76:
        if (dbmode == 15)
        {
            efid = 403;
            efp = 100;
            drink_potion();
            return -1;
        }
        break;
    case 75:
        if (dbmode == 15)
        {
            efid = 402;
            efp = 300;
            drink_potion();
            return -1;
        }
        break;
    case 74:
        if (dbmode == 15)
        {
            efid = 402;
            efp = 100;
            drink_potion();
            return -1;
        }
        break;
    case 73:
        if (dbmode == 3)
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
        if (dbmode == 15)
        {
            efid = 401;
            efp = 400;
            drink_potion();
            return -1;
        }
        break;
    case 71:
        if (dbmode == 15)
        {
            efid = 401;
            efp = 300;
            drink_potion();
            return -1;
        }
        break;
    case 70:
        if (dbmode == 15)
        {
            efid = 401;
            efp = 100;
            drink_potion();
            return -1;
        }
        break;
    case 69:
        if (dbmode == 15)
        {
            efid = 400;
            efp = 300;
            drink_potion();
            return -1;
        }
        break;
    case 68:
        if (dbmode == 15)
        {
            efid = 400;
            efp = 100;
            drink_potion();
            return -1;
        }
        break;
    case 64:
        if (dbmode == 3)
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
        if (dbmode == 3)
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
        if (dbmode == 3)
        {
            inv[ci].skill = 110;
        }
        break;
    case 61:
        if (dbmode == 3)
        {
            inv[ci].skill = 108;
        }
        break;
    case 60:
        if (dbmode == 3)
        {
            inv[ci].skill = 110;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::mani;
        }
        break;
    case 59:
        if (dbmode == 3)
        {
            inv[ci].skill = 168;
        }
        break;
    case 58:
        if (dbmode == 3)
        {
            inv[ci].skill = 108;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::lulwy;
        }
        break;
    case 57:
        if (dbmode == 3)
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
        if (dbmode == 3)
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
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::jure
                || cdata[0].god_id == core_god::opatos;
        }
        break;
    case 42:
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::jure
                || cdata[0].god_id == core_god::opatos;
        }
        break;
    case 41:
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::jure
                || cdata[0].god_id == core_god::opatos;
        }
        break;
    case 40:
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::jure
                || cdata[0].god_id == core_god::opatos;
        }
        break;
    case 39:
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::jure
                || cdata[0].god_id == core_god::opatos;
        }
        break;
    case 38:
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::jure
                || cdata[0].god_id == core_god::opatos;
        }
        break;
    case 37:
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::jure
                || cdata[0].god_id == core_god::opatos;
        }
        break;
    case 36:
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::jure
                || cdata[0].god_id == core_god::opatos;
        }
        break;
    case 35:
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata[0].god_id == core_god::jure
                || cdata[0].god_id == core_god::opatos;
        }
        break;
    case 34:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 421;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 33:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 420;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 32:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 419;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 31:
        if (dbmode == 15)
        {
            efid = 1102;
            efp = 300;
            drink_potion();
            return -1;
        }
        break;
    case 30:
        if (dbmode == 15)
        {
            efid = 1112;
            efp = 200;
            drink_potion();
            return -1;
        }
        break;
    case 29:
        if (dbmode == 15)
        {
            efid = 1110;
            efp = 200;
            drink_potion();
            return -1;
        }
        break;
    case 28:
        if (dbmode == 15)
        {
            efid = 1109;
            efp = 150;
            drink_potion();
            return -1;
        }
        break;
    case 27:
        if (dbmode == 15)
        {
            efid = 1111;
            efp = 200;
            drink_potion();
            return -1;
        }
        break;
    case 26:
        if (dbmode == 15)
        {
            efid = 1130;
            drink_potion();
            return -1;
        }
        break;
    case 25:
        if (dbmode == 3)
        {
            inv[ci].param1 = 2;
        }
        if (dbmode == 13)
        {
            inv[ci].param1 = 2;
            read_normal_book();
            return -1;
        }
        break;
    case 24:
        if (dbmode == 3)
        {
            inv[ci].param1 = 0;
        }
        if (dbmode == 13)
        {
            read_normal_book();
            return -1;
        }
        break;
    case 23:
        if (dbmode == 3)
        {
            inv[ci].param1 = 1;
        }
        if (dbmode == 13)
        {
            inv[ci].param1 = 1;
            read_normal_book();
            return -1;
        }
        break;
    case 22:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 412;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 21:
        if (dbmode == 3)
        {
            inv[ci].count = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 411;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 20:
        if (dbmode == 3)
        {
            inv[ci].count = 5 + rnd(5) - rnd(5);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 408;
            efp = 100;
            decode_book();
            return -1;
        }
        break;
    case 19:
        if (dbmode == 3)
        {
            inv[ci].count = 12 + rnd(12) - rnd(12);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 14)
        {
            efid = 409;
            efp = 100;
            return -1;
        }
        break;
    case 18:
        if (dbmode == 3)
        {
            inv[ci].count = 8 + rnd(8) - rnd(8);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 14)
        {
            efid = 411;
            efp = 100;
            return -1;
        }
        break;
    case 17:
        if (dbmode == 13)
        {
            efid = 458;
            efp = 300;
            read_scroll();
            return -1;
        }
        break;
    case 16:
        if (dbmode == 13)
        {
            efid = 408;
            efp = 100;
            read_scroll();
            return -1;
        }
        break;
    case 15:
        if (dbmode == 13)
        {
            efid = 413;
            efp = 100;
            read_scroll();
            return -1;
        }
        break;
    case 14:
        if (dbmode == 13)
        {
            efid = 411;
            efp = 100;
            read_scroll();
            return -1;
        }
        break;
    case 6:
        if (dbmode == 3)
        {
            fixeditemenc(0) = 33;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
        }
        break;
    case 4:
        if (dbmode == 3)
        {
            inv[ci].skill = 103;
        }
        break;
    case 3:
        if (dbmode == 3)
        {
            inv[ci].skill = 102;
        }
        break;
    case 2:
        if (dbmode == 3)
        {
            inv[ci].skill = 101;
        }
        break;
    case 1:
        if (dbmode == 3)
        {
            inv[ci].skill = 100;
        }
        break;
    default: break;
    }

    return 0;
}



} // namespace elona
