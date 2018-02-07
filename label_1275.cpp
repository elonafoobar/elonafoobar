#include <unordered_map>
#include "character.hpp"
#include "elona.hpp"
#include "item.hpp"
#include "item_db.hpp"
#include "variables.hpp"



namespace elona
{


int label_1275()
{
    std::string infilterref;
    const auto info = the_item_db[dbid];
    if (info)
    {
        if (dbmode == 10 || dbmode == 3)
        {
            inv_value(ci) = info->value;
            inv_weight(ci) = info->weight;
            inv_dice_x(ci) = info->dice_x;
            inv_dice_y(ci) = info->dice_y;
            inv_hit_bonus(ci) = info->hit_bonus;
            inv_damage_bonus(ci) = info->damage_bonus;
            inv_pv(ci) = info->pv;
            inv_dv(ci) = info->dv;
            inv_material(ci) = info->material;
            if (dbmode == 10)
                return 0;
        }
        else if (dbmode == 2)
        {
            ichargelevel = info->chargelevel;
            infilterref = info->infilterref;
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
        else if (dbmode == 16)
        {
            switch (dbspec)
            {
            case 2: return info->dbspec2;
            case 3: return info->dbspec3;
            case 4: return info->dbspec4;
            case 5: return info->category;
            case 7: return info->dbspec7;
            case 8: return info->dbspec8;
            case 9: return info->dbspec9;
            case 10: return info->dbspec10;
            case 11: return info->dbspec11;
            case 18: return info->dbspec18;
            case 19: return info->dbspec19;
            case 20: return info->dbspec20;
            default: break;
            }
        }
    }
    else
    {
        return -999;
    }

    if (dbmode == 3)
    {
        // Common initialization
        inv_id(ci) = dbid;
        inv_number(ci) = 1;
        inv_difficulty_of_identification(ci) = 0; // Default value
        fixeditemenc(0) = 0; // Default value
        reftype = info->category;
        reftypeminor = info->subcategory;
    }

    switch (dbid)
    {
    case 792:
        if (dbmode == 3)
        {
            inv_image(ci) = 695;
            inv_param2(ci) = 8;
        }
        break;
    case 791:
        if (dbmode == 3)
        {
            inv_skill(ci) = 100;
            inv_image(ci) = 697;
            fixeditemenc(0) = 57;
            fixeditemenc(1) = 300;
            fixeditemenc(2) = 61;
            fixeditemenc(3) = 200;
            fixeditemenc(4) = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 790:
        if (dbmode == 3)
        {
            inv_image(ci) = 555;
            inv_function(ci) = 15;
        }
        break;
    case 789:
        if (dbmode == 3)
        {
            inv_image(ci) = 554;
            inv_function(ci) = 15;
        }
        break;
    case 788:
        if (dbmode == 3)
        {
            inv_skill(ci) = 108;
            inv_image(ci) = 402;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 2;
        }
        break;
    case 787:
        if (dbmode == 3)
        {
            inv_image(ci) = 552;
            inv_param2(ci) = 5;
            inv_param3(ci) = 720;
        }
        break;
    case 786:
        if (dbmode == 3)
        {
            inv_image(ci) = 551;
            inv_param2(ci) = 4;
        }
        break;
    case 785:
        if (dbmode == 3)
        {
            inv_image(ci) = 553;
            inv_param2(ci) = 1;
        }
        break;
    case 784:
        if (dbmode == 3)
        {
            inv_image(ci) = 549;
        }
        break;
    case 783:
        if (dbmode == 3)
        {
            inv_image(ci) = 550;
        }
        if (dbmode == 13)
        {
            label_2163();
            return -1;
        }
        break;
    case 782:
        if (dbmode == 3)
        {
            inv_image(ci) = 360;
        }
        break;
    case 781:
        if (dbmode == 3)
        {
            inv_skill(ci) = 101;
            inv_image(ci) = 546;
        }
        break;
    case 780:
        if (dbmode == 3)
        {
            inv_image(ci) = 545;
        }
        break;
    case 779:
        if (dbmode == 3)
        {
            inv_image(ci) = 544;
        }
        break;
    case 778:
        if (dbmode == 3)
        {
            inv_image(ci) = 543;
            inv_function(ci) = 44;
        }
        break;
    case 777:
        if (dbmode == 3)
        {
            inv_image(ci) = 682;
            inv_function(ci) = 26;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv_param3(ci) = 240;
            fixlv = 6;
        }
        break;
    case 776:
        if (dbmode == 3)
        {
            inv_image(ci) = 681;
            inv_function(ci) = 26;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv_param3(ci) = 240;
            fixlv = 6;
        }
        break;
    case 775:
        if (dbmode == 3)
        {
            inv_image(ci) = 542;
            ibitmod(5, ci, 1);
            inv_param2(ci) = 8;
        }
        break;
    case 774:
        if (dbmode == 3)
        {
            inv_image(ci) = 683;
        }
        break;
    case 773:
        if (dbmode == 3)
        {
            inv_image(ci) = 541;
        }
        break;
    case 772:
        if (dbmode == 3)
        {
            inv_image(ci) = 540;
            inv_param1(ci) = 2000;
            inv_param3(ci) = 32;
        }
        break;
    case 771:
        if (dbmode == 3)
        {
            inv_image(ci) = 679;
            fixlv = 6;
        }
        if (dbmode == 15)
        {
            efid = 1147;
            efp = 100;
            label_2169();
            return -1;
        }
        break;
    case 770:
        if (dbmode == 3)
        {
            inv_image(ci) = 678;
        }
        if (dbmode == 15)
        {
            efid = 1146;
            efp = 100;
            label_2169();
            return -1;
        }
        break;
    case 769:
        if (dbmode == 3)
        {
            inv_image(ci) = 677;
        }
        break;
    case 768:
        if (dbmode == 3)
        {
            inv_image(ci) = 676;
        }
        break;
    case 767:
        if (dbmode == 3)
        {
            inv_image(ci) = 675;
            inv_param1(ci) = 0;
        }
        break;
    case 766:
        if (dbmode == 3)
        {
            inv_image(ci) = 684;
        }
        break;
    case 765:
        if (dbmode == 3)
        {
            inv_image(ci) = 685;
        }
        break;
    case 764:
        if (dbmode == 3)
        {
            inv_image(ci) = 674;
        }
        break;
    case 763:
        if (dbmode == 3)
        {
            inv_image(ci) = 673;
        }
        break;
    case 762:
        if (dbmode == 3)
        {
            inv_image(ci) = 672;
        }
        break;
    case 761:
        if (dbmode == 3)
        {
            inv_skill(ci) = 183;
            inv_image(ci) = 76;
            fixeditemenc(0) = 60;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
            inv_function(ci) = 17;
            ibitmod(5, ci, 1);
            inv_param1(ci) = 200;
            fixlv = 6;
        }
        break;
    case 760:
        if (dbmode == 3)
        {
            inv_image(ci) = 629;
            inv_function(ci) = 49;
            ibitmod(5, ci, 1);
            inv_param1(ci) = rnd(20000) + 1;
            fixlv = 6;
        }
        break;
    case 759:
        if (dbmode == 3)
        {
            inv_skill(ci) = 100;
            inv_image(ci) = 671;
        }
        break;
    case 758:
        if (dbmode == 3)
        {
            inv_skill(ci) = 110;
            inv_image(ci) = 419;
            fixeditemenc(0) = 35;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 757:
        if (dbmode == 3)
        {
            inv_image(ci) = 480;
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
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 756:
        if (dbmode == 3)
        {
            inv_image(ci) = 670;
            inv_param2(ci) = 7;
        }
        break;
    case 755:
        if (dbmode == 3)
        {
            inv_image(ci) = 669;
            inv_param2(ci) = 6;
        }
        break;
    case 754:
        if (dbmode == 3)
        {
            inv_image(ci) = 668;
        }
        break;
    case 753:
        if (dbmode == 3)
        {
            inv_image(ci) = 667;
        }
        break;
    case 752:
        if (dbmode == 3)
        {
            inv_image(ci) = 666;
        }
        break;
    case 751:
        if (dbmode == 3)
        {
            inv_image(ci) = 664;
        }
        break;
    case 750:
        if (dbmode == 3)
        {
            inv_image(ci) = 665;
        }
        break;
    case 749:
        if (dbmode == 3)
        {
            inv_image(ci) = 686;
            inv_function(ci) = 48;
            ibitmod(5, ci, 1);
        }
        break;
    case 748:
        if (dbmode == 3)
        {
            inv_image(ci) = 662;
            inv_function(ci) = 47;
            ibitmod(5, ci, 1);
            ibitmod(16, ci, 1);
        }
        break;
    case 747:
        if (dbmode == 3)
        {
            inv_image(ci) = 333;
            inv_param1(ci) = 1;
            inv_param2(ci) = rnd(4) + 1;
        }
        if (dbmode == 13)
        {
            label_2164();
            return -1;
        }
        break;
    case 746:
        if (dbmode == 3)
        {
            inv_image(ci) = 657;
            inv_function(ci) = 30;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv_param1(ci) = 1132;
            inv_param2(ci) = 100;
            inv_param3(ci) = 24;
        }
        break;
    case 745:
        if (dbmode == 3)
        {
            inv_image(ci) = 657;
            inv_function(ci) = 30;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv_param1(ci) = 1132;
            inv_param2(ci) = 100;
            inv_param3(ci) = 24;
        }
        break;
    case 744:
        if (dbmode == 3)
        {
            inv_image(ci) = 657;
            inv_function(ci) = 30;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv_param1(ci) = 1132;
            inv_param2(ci) = 100;
            inv_param3(ci) = 24;
        }
        break;
    case 743:
        if (dbmode == 3)
        {
            inv_image(ci) = 657;
            inv_function(ci) = 30;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv_param1(ci) = 1132;
            inv_param2(ci) = 100;
            inv_param3(ci) = 24;
        }
        break;
    case 742:
        if (dbmode == 3)
        {
            inv_image(ci) = 308;
            ibitmod(5, ci, 1);
            fixlv = 6;
        }
        if (dbmode == 13)
        {
            label_2164();
            return -1;
        }
        break;
    case 741:
        if (dbmode == 3)
        {
            inv_skill(ci) = 100;
            inv_image(ci) = 501;
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
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 740:
        if (dbmode == 3)
        {
            inv_image(ci) = 488;
            fixeditemenc(0) = 56;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 30181;
            fixeditemenc(3) = 550;
            fixeditemenc(4) = 20057;
            fixeditemenc(5) = 400;
            fixeditemenc(6) = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 739:
        if (dbmode == 3)
        {
            inv_skill(ci) = 107;
            inv_image(ci) = 425;
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
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 738:
        if (dbmode == 3)
        {
            inv_image(ci) = 539;
            inv_param2(ci) = 6;
        }
        break;
    case 737:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 1145;
            efp = 100;
            label_2171();
            return -1;
        }
        break;
    case 736:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 1116;
            efp = 250;
            label_2169();
            return -1;
        }
        break;
    case 735:
        if (dbmode == 3)
        {
            inv_skill(ci) = 107;
            inv_image(ci) = 421;
            fixeditemenc(0) = 80025;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
        }
        break;
    case 734:
        if (dbmode == 3)
        {
            inv_image(ci) = 220;
        }
        break;
    case 733:
        if (dbmode == 3)
        {
            inv_image(ci) = 563;
            inv_function(ci) = 45;
        }
        break;
    case 732:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 464;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 731:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 463;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 730:
        if (dbmode == 3)
        {
            inv_image(ci) = 538;
            ibitmod(5, ci, 1);
        }
        break;
    case 729:
        if (dbmode == 3)
        {
            inv_image(ci) = 391;
        }
        break;
    case 728:
        if (dbmode == 3)
        {
            inv_image(ci) = 474;
            fixeditemenc(0) = 55;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 20056;
            fixeditemenc(3) = 450;
            fixeditemenc(4) = 20050;
            fixeditemenc(5) = 350;
            fixeditemenc(6) = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 727:
        if (dbmode == 3)
        {
            inv_skill(ci) = 168;
            inv_image(ci) = 453;
            fixeditemenc(0) = 54;
            fixeditemenc(1) = 1000;
            fixeditemenc(2) = 20058;
            fixeditemenc(3) = 450;
            fixeditemenc(4) = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 726:
        if (dbmode == 3)
        {
            inv_skill(ci) = 168;
            inv_image(ci) = 393;
            fixeditemenc(0) = 30183;
            fixeditemenc(1) = -450;
            fixeditemenc(2) = 52;
            fixeditemenc(3) = 400;
            fixeditemenc(4) = 53;
            fixeditemenc(5) = 400;
            fixeditemenc(6) = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 725:
        if (dbmode == 3)
        {
            inv_skill(ci) = 111;
            inv_image(ci) = 76;
            fixeditemenc(0) = 70059;
            fixeditemenc(1) = 400;
            fixeditemenc(2) = 30183;
            fixeditemenc(3) = -700;
            fixeditemenc(4) = 44;
            fixeditemenc(5) = 450;
            fixeditemenc(6) = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 724:
        if (dbmode == 3)
        {
            inv_image(ci) = 538;
            ibitmod(5, ci, 1);
        }
        break;
    case 723:
        if (dbmode == 3)
        {
            inv_image(ci) = 486;
            fixeditemenc(0) = 50;
            fixeditemenc(1) = 600;
            fixeditemenc(2) = 30166;
            fixeditemenc(3) = 650;
            fixeditemenc(4) = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 722:
        if (dbmode == 3)
        {
            inv_image(ci) = 486;
            fixeditemenc(0) = 51;
            fixeditemenc(1) = 600;
            fixeditemenc(2) = 30109;
            fixeditemenc(3) = 700;
            fixeditemenc(4) = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 721:
        if (dbmode == 3)
        {
            inv_image(ci) = 687;
            inv_function(ci) = 43;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv_param3(ci) = 480;
            fixlv = 6;
        }
        break;
    case 720:
        if (dbmode == 3)
        {
            inv_image(ci) = 649;
            inv_param1(ci) = 200;
        }
        break;
    case 719:
        if (dbmode == 3)
        {
            inv_skill(ci) = 100;
            inv_image(ci) = 698;
            fixeditemenc(0) = 44;
            fixeditemenc(1) = 250;
            fixeditemenc(2) = 39;
            fixeditemenc(3) = 200;
            fixeditemenc(4) = 33;
            fixeditemenc(5) = 100;
            fixeditemenc(6) = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 718:
        if (dbmode == 3)
        {
            inv_skill(ci) = 111;
            inv_image(ci) = 630;
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
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 717:
        if (dbmode == 3)
        {
            inv_image(ci) = 657;
            inv_function(ci) = 42;
        }
        break;
    case 716:
        if (dbmode == 3)
        {
            inv_skill(ci) = 111;
            inv_image(ci) = 424;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 715:
        if (dbmode == 3)
        {
            inv_image(ci) = 657;
            inv_function(ci) = 41;
        }
        break;
    case 714:
        if (dbmode == 3)
        {
            inv_skill(ci) = 111;
            inv_image(ci) = 537;
            fixeditemenc(0) = 80024;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
        }
        break;
    case 713:
        if (dbmode == 3)
        {
            inv_skill(ci) = 111;
            inv_image(ci) = 536;
            fixeditemenc(0) = 70061;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
        }
        break;
    case 712:
        if (dbmode == 3)
        {
            inv_image(ci) = 308;
        }
        if (dbmode == 13)
        {
            efid = 1115;
            return -1;
        }
        break;
    case 711:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 1144;
            efp = 100;
            label_2169();
            return -1;
        }
        break;
    case 710:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 462;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 709:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 462;
            efp = 1500;
            label_2171();
            return -1;
        }
        break;
    case 708:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
        }
        if (dbmode == 13)
        {
            efid = 461;
            efp = 2500;
            label_2171();
            return -1;
        }
        break;
    case 707:
        if (dbmode == 3)
        {
            inv_skill(ci) = 183;
            inv_image(ci) = 699;
            fixeditemenc(0) = 49;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
            inv_function(ci) = 17;
            ibitmod(5, ci, 1);
            inv_param1(ci) = 180;
            fixlv = 6;
        }
        break;
    case 706:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 1143;
            efp = 100;
            label_2169();
            return -1;
        }
        break;
    case 705:
        if (dbmode == 3)
        {
            inv_image(ci) = 486;
            fixeditemenc(0) = 48;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 10017;
            fixeditemenc(3) = 450;
            fixeditemenc(4) = 41;
            fixeditemenc(5) = 100;
            fixeditemenc(6) = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 704:
        if (dbmode == 3)
        {
            inv_image(ci) = 535;
        }
        if (dbmode == 15)
        {
            efid = 1130;
            efp = 100;
            label_2169();
            return -1;
        }
        break;
    case 703:
        if (dbmode == 3)
        {
            inv_image(ci) = 534;
            inv_function(ci) = 39;
        }
        break;
    case 702:
        if (dbmode == 3)
        {
            inv_image(ci) = 301;
            ibitmod(5, ci, 1);
            inv_param2(ci) = 4;
            fixlv = 6;
        }
        break;
    case 701:
        if (dbmode == 3)
        {
            inv_image(ci) = 533;
            inv_function(ci) = 37;
        }
        break;
    case 700:
        if (dbmode == 3)
        {
            inv_image(ci) = 532;
        }
        if (dbmode == 13)
        {
            menucycle = 1;
            label_22712();
            return -1;
        }
        break;
    case 699:
        if (dbmode == 3)
        {
            inv_image(ci) = 658;
            ibitmod(5, ci, 1);
        }
        break;
    case 698:
        if (dbmode == 3)
        {
            inv_image(ci) = 365;
        }
        if (dbmode == 15)
        {
            efid = 1142;
            efp = 100;
            label_2169();
            return -1;
        }
        break;
    case 697:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 2 + rnd(2) - rnd(2);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 459;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 696:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 2 + rnd(2) - rnd(2);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 460;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 695:
        if (dbmode == 3)
        {
            inv_skill(ci) = 102;
            inv_image(ci) = 399;
            fixeditemenc(0) = 44;
            fixeditemenc(1) = 750;
            fixeditemenc(2) = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 694:
        if (dbmode == 3)
        {
            inv_image(ci) = 659;
        }
        break;
    case 693:
        if (dbmode == 3)
        {
            inv_skill(ci) = 183;
            inv_image(ci) = 395;
            inv_function(ci) = 17;
            inv_param1(ci) = 175;
        }
        break;
    case 692:
        if (dbmode == 3)
        {
            inv_skill(ci) = 183;
            inv_image(ci) = 394;
            inv_function(ci) = 17;
            inv_param1(ci) = 70;
        }
        break;
    case 691:
        if (dbmode == 3)
        {
            inv_skill(ci) = 183;
            inv_image(ci) = 393;
            inv_function(ci) = 17;
            inv_param1(ci) = 130;
        }
        break;
    case 690:
        if (dbmode == 3)
        {
            inv_skill(ci) = 183;
            inv_image(ci) = 392;
            inv_function(ci) = 17;
            inv_param1(ci) = 150;
        }
        break;
    case 689:
        if (dbmode == 3)
        {
            inv_image(ci) = 688;
            inv_function(ci) = 36;
        }
        break;
    case 688:
        if (dbmode == 3)
        {
            inv_image(ci) = 689;
            inv_function(ci) = 35;
        }
        break;
    case 687:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 2 + rnd(2) - rnd(2);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            label_2163();
            return -1;
        }
        break;
    case 686:
        if (dbmode == 3)
        {
            inv_image(ci) = 690;
            inv_function(ci) = 34;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv_param3(ci) = 720;
            fixlv = 6;
        }
        break;
    case 685:
        if (dbmode == 3)
        {
            inv_image(ci) = 658;
            inv_function(ci) = 33;
        }
        break;
    case 684:
        if (dbmode == 3)
        {
            inv_image(ci) = 691;
            inv_function(ci) = 32;
            ibitmod(5, ci, 1);
        }
        break;
    case 683:
        if (dbmode == 3)
        {
            inv_image(ci) = 657;
            inv_function(ci) = 30;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv_param1(ci) = 1132;
            inv_param2(ci) = 100;
            inv_param3(ci) = 24;
            fixlv = 6;
        }
        break;
    case 682:
        if (dbmode == 3)
        {
            inv_image(ci) = 657;
            inv_function(ci) = 31;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv_param3(ci) = 72;
            fixlv = 6;
        }
        break;
    case 681:
        if (dbmode == 3)
        {
            inv_image(ci) = 657;
            inv_function(ci) = 30;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv_param1(ci) = 404;
            inv_param2(ci) = 400;
            inv_param3(ci) = 8;
            fixlv = 6;
        }
        break;
    case 680:
        if (dbmode == 3)
        {
            inv_image(ci) = 657;
            inv_function(ci) = 30;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv_param1(ci) = 446;
            inv_param2(ci) = 300;
            inv_param3(ci) = 12;
            fixlv = 6;
        }
        break;
    case 679:
        if (dbmode == 3)
        {
            inv_skill(ci) = 103;
            inv_image(ci) = 504;
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
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 678:
        if (dbmode == 3)
        {
            inv_skill(ci) = 101;
            inv_image(ci) = 400;
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
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 677:
        if (dbmode == 3)
        {
            inv_skill(ci) = 104;
            inv_image(ci) = 415;
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
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 676:
        if (dbmode == 3)
        {
            inv_skill(ci) = 105;
            inv_image(ci) = 425;
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
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 675:
        if (dbmode == 3)
        {
            inv_skill(ci) = 107;
            inv_image(ci) = 421;
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
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 674:
        if (dbmode == 3)
        {
            inv_skill(ci) = 110;
            inv_image(ci) = 514;
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
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 673:
        if (dbmode == 3)
        {
            inv_skill(ci) = 108;
            inv_image(ci) = 404;
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
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 672:
        if (dbmode == 3)
        {
            inv_image(ci) = 656;
            inv_function(ci) = 29;
            ibitmod(5, ci, 1);
            fixlv = 6;
        }
        break;
    case 671:
        if (dbmode == 3)
        {
            inv_image(ci) = 632;
            inv_function(ci) = 28;
            ibitmod(5, ci, 1);
            fixlv = 6;
        }
        break;
    case 670:
        if (dbmode == 3)
        {
            inv_image(ci) = 132;
            inv_param1(ci) = 7;
        }
        break;
    case 669:
        if (dbmode == 3)
        {
            inv_image(ci) = 92;
            inv_param1(ci) = 7;
        }
        break;
    case 668:
        if (dbmode == 3)
        {
            inv_image(ci) = 333;
            inv_param1(ci) = 1;
            inv_param2(ci) = rnd(4) + 1;
        }
        if (dbmode == 13)
        {
            label_2164();
            return -1;
        }
        break;
    case 667:
        if (dbmode == 3)
        {
            inv_image(ci) = 391;
            inv_param2(ci) = 7;
        }
        break;
    case 666:
        if (dbmode == 3)
        {
            inv_image(ci) = 692;
            inv_function(ci) = 27;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv_param3(ci) = 120;
            fixlv = 6;
        }
        break;
    case 665:
        if (dbmode == 3)
        {
            inv_image(ci) = 680;
            inv_function(ci) = 26;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv_param3(ci) = 240;
            fixlv = 6;
        }
        break;
    case 664:
        if (dbmode == 3)
        {
            inv_image(ci) = 489;
            fixeditemenc(0) = 10018;
            fixeditemenc(1) = 400 + rnd((rnd(1000) + 1));
            fixeditemenc(2) = 0;
        }
        break;
    case 663:
        if (dbmode == 3)
        {
            inv_image(ci) = 654;
            ibitmod(5, ci, 1);
            fixlv = 6;
        }
        break;
    case 662:
        if (dbmode == 3)
        {
            inv_image(ci) = 189;
            ibitmod(5, ci, 1);
            inv_param2(ci) = 7;
            fixlv = 6;
        }
        break;
    case 661:
        if (dbmode == 3)
        {
            inv_image(ci) = 459;
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
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 660:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 5 + rnd(5) - rnd(5);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 418;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 659:
        if (dbmode == 3)
        {
            inv_image(ci) = 653;
        }
        break;
    case 658:
        if (dbmode == 3)
        {
            inv_image(ci) = 652;
        }
        break;
    case 657:
        if (dbmode == 3)
        {
            inv_image(ci) = 651;
        }
        break;
    case 656:
        if (dbmode == 3)
        {
            inv_image(ci) = 650;
        }
        break;
    case 655:
        if (dbmode == 3)
        {
            inv_image(ci) = 168;
            ibitmod(5, ci, 1);
            inv_param2(ci) = 7;
            fixlv = 6;
        }
        break;
    case 654:
        if (dbmode == 3)
        {
            inv_image(ci) = 649;
            inv_param1(ci) = 160;
        }
        break;
    case 653:
        if (dbmode == 3)
        {
            inv_image(ci) = 648;
        }
        break;
    case 652:
        if (dbmode == 3)
        {
            inv_image(ci) = 647;
        }
        break;
    case 651:
        if (dbmode == 3)
        {
            inv_image(ci) = 646;
        }
        break;
    case 650:
        if (dbmode == 3)
        {
            inv_image(ci) = 645;
        }
        if (dbmode == 15)
        {
            label_2170();
            return -1;
        }
        break;
    case 649:
        if (dbmode == 3)
        {
            inv_image(ci) = 644;
        }
        break;
    case 648:
        if (dbmode == 3)
        {
            inv_image(ci) = 643;
            inv_function(ci) = 44;
        }
        break;
    case 647:
        if (dbmode == 3)
        {
            inv_image(ci) = 642;
        }
        break;
    case 646:
        if (dbmode == 3)
        {
            inv_image(ci) = 641;
        }
        break;
    case 645:
        if (dbmode == 3)
        {
            inv_image(ci) = 640;
        }
        break;
    case 644:
        if (dbmode == 3)
        {
            inv_image(ci) = 639;
        }
        break;
    case 643:
        if (dbmode == 3)
        {
            inv_image(ci) = 638;
            inv_param1(ci) = 130;
        }
        break;
    case 642:
        if (dbmode == 3)
        {
            inv_image(ci) = 637;
        }
        break;
    case 641:
        if (dbmode == 3)
        {
            inv_image(ci) = 636;
            ibitmod(5, ci, 1);
            fixlv = 6;
        }
        break;
    case 640:
        if (dbmode == 3)
        {
            inv_image(ci) = 635;
            inv_function(ci) = 25;
        }
        break;
    case 639:
        if (dbmode == 3)
        {
            inv_image(ci) = 172;
            ibitmod(5, ci, 1);
            inv_param2(ci) = 7;
            fixlv = 6;
        }
        break;
    case 638:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 1141;
            efp = 100;
            label_2171();
            return -1;
        }
        break;
    case 637:
        if (dbmode == 3)
        {
            inv_image(ci) = 633;
            ibitmod(5, ci, 1);
            fixlv = 6;
        }
        break;
    case 636:
        if (dbmode == 3)
        {
            inv_image(ci) = 634;
        }
        break;
    case 635:
        if (dbmode == 3)
        {
            inv_image(ci) = 632;
            inv_function(ci) = 24;
        }
        break;
    case 634:
        if (dbmode == 3)
        {
            inv_image(ci) = 631;
            inv_function(ci) = 23;
        }
        break;
    case 633:
        if (dbmode == 3)
        {
            inv_skill(ci) = 111;
            inv_image(ci) = 630;
            fixeditemenc(0) = 70054;
            fixeditemenc(1) = 800;
            fixeditemenc(2) = 0;
        }
        break;
    case 632:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 1140;
            efp = 150;
            label_2171();
            return -1;
        }
        break;
    case 631:
        if (dbmode == 3)
        {
            inv_image(ci) = 566;
        }
        break;
    case 630:
        if (dbmode == 3)
        {
            inv_image(ci) = 629;
            inv_function(ci) = 21;
        }
        break;
    case 629:
        if (dbmode == 3)
        {
            inv_image(ci) = 628;
            inv_function(ci) = 20;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        break;
    case 628:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 458;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 627:
        if (dbmode == 3)
        {
            inv_image(ci) = 480;
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
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 626:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
            ibitmod(5, ci, 1);
        }
        if (dbmode == 15)
        {
            efid = 1139;
            efp = 500;
            label_2169();
            return -1;
        }
        break;
    case 625:
        if (dbmode == 3)
        {
            inv_image(ci) = 627;
            ibitmod(5, ci, 1);
        }
        break;
    case 624:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            ibitmod(5, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 1137;
            efp = 100;
            label_2171();
            return -1;
        }
        break;
    case 623:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            ibitmod(5, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 1138;
            efp = 100;
            label_2171();
            return -1;
        }
        break;
    case 622:
        if (dbmode == 3)
        {
            inv_image(ci) = 165;
            ibitmod(5, ci, 1);
        }
        break;
    case 621:
        if (dbmode == 3)
        {
            inv_image(ci) = 252;
        }
        if (dbmode == 13)
        {
            efid = 1136;
            efp = 100;
            label_2171();
            return -1;
        }
        break;
    case 620:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 1135;
            efp = 100;
            label_2169();
            return -1;
        }
        break;
    case 619:
        if (dbmode == 3)
        {
            inv_image(ci) = 310;
        }
        break;
    case 618:
        if (dbmode == 3)
        {
            inv_image(ci) = 310;
            inv_param1(ci) = 6000;
            inv_param3(ci) = 4;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 4;
        }
        break;
    case 617:
        if (dbmode == 3)
        {
            inv_image(ci) = 569;
        }
        break;
    case 616:
        if (dbmode == 3)
        {
            inv_image(ci) = 384;
            ibitmod(5, ci, 1);
        }
        break;
    case 615:
        if (dbmode == 3)
        {
            inv_image(ci) = 383;
            ibitmod(5, ci, 1);
        }
        break;
    case 614:
        if (dbmode == 3)
        {
            inv_image(ci) = 568;
        }
        break;
    case 613:
        if (dbmode == 3)
        {
            inv_image(ci) = 569;
            inv_param1(ci) = 180;
        }
        break;
    case 612:
        if (dbmode == 3)
        {
            inv_image(ci) = 382;
        }
        break;
    case 611:
        if (dbmode == 3)
        {
            inv_image(ci) = 107;
            inv_function(ci) = 8;
        }
        break;
    case 610:
        if (dbmode == 3)
        {
            inv_image(ci) = 380;
        }
        break;
    case 609:
        if (dbmode == 3)
        {
            inv_image(ci) = 379;
        }
        break;
    case 608:
        if (dbmode == 3)
        {
            inv_image(ci) = 378;
        }
        break;
    case 607:
        if (dbmode == 3)
        {
            inv_image(ci) = 377;
        }
        break;
    case 606:
        if (dbmode == 3)
        {
            inv_image(ci) = 376;
            inv_function(ci) = 15;
            inv_param1(ci) = 225;
        }
        break;
    case 605:
        if (dbmode == 3)
        {
            inv_image(ci) = 375;
        }
        break;
    case 604:
        if (dbmode == 3)
        {
            inv_image(ci) = 374;
        }
        break;
    case 603:
        if (dbmode == 3)
        {
            inv_image(ci) = 373;
            inv_function(ci) = 44;
            ibitmod(5, ci, 1);
        }
        break;
    case 602:
        if (dbmode == 3)
        {
            inv_image(ci) = 372;
            inv_param2(ci) = 100;
        }
        if (dbmode == 15)
        {
            label_2170();
            return -1;
        }
        break;
    case 601:
        if (dbmode == 3)
        {
            inv_image(ci) = 371;
        }
        break;
    case 600:
        if (dbmode == 3)
        {
            inv_image(ci) = 370;
            ibitmod(5, ci, 1);
        }
        break;
    case 599:
        if (dbmode == 3)
        {
            inv_image(ci) = 570;
        }
        break;
    case 598:
        if (dbmode == 3)
        {
            inv_image(ci) = 134;
            inv_param1(ci) = 6;
        }
        break;
    case 597:
        if (dbmode == 3)
        {
            inv_image(ci) = 570;
            inv_param1(ci) = 6;
        }
        break;
    case 596:
        if (dbmode == 3)
        {
            inv_image(ci) = 369;
        }
        break;
    case 595:
        if (dbmode == 3)
        {
            inv_image(ci) = 571;
        }
        break;
    case 594:
        if (dbmode == 3)
        {
            inv_image(ci) = 572;
        }
        break;
    case 593:
        if (dbmode == 3)
        {
            inv_image(ci) = 573;
        }
        break;
    case 592:
        if (dbmode == 3)
        {
            inv_image(ci) = 368;
        }
        break;
    case 591:
        if (dbmode == 3)
        {
            inv_image(ci) = 366;
        }
        break;
    case 590:
        if (dbmode == 3)
        {
            inv_image(ci) = 367;
        }
        break;
    case 589:
        if (dbmode == 3)
        {
            inv_image(ci) = 574;
        }
        break;
    case 588:
        if (dbmode == 3)
        {
            inv_image(ci) = 575;
        }
        break;
    case 587:
        if (dbmode == 3)
        {
            inv_image(ci) = 365;
            inv_function(ci) = 14;
        }
        if (dbmode == 15)
        {
            efid = 1103;
            efp = 100;
            label_2169();
            return -1;
        }
        break;
    case 586:
        if (dbmode == 3)
        {
            inv_image(ci) = 576;
        }
        break;
    case 585:
        if (dbmode == 3)
        {
            inv_image(ci) = 364;
        }
        break;
    case 584:
        if (dbmode == 3)
        {
            inv_image(ci) = 353;
        }
        break;
    case 583:
        if (dbmode == 3)
        {
            inv_image(ci) = 352;
            inv_function(ci) = 13;
            inv_param1(ci) = 100;
        }
        break;
    case 582:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 457;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 581:
        if (dbmode == 3)
        {
            inv_image(ci) = 471;
            inv_count(ci) = 6 + rnd(6) - rnd(6);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 14)
        {
            efid = 457;
            efp = 100;
            return -1;
        }
        break;
    case 580:
        if (dbmode == 3)
        {
            inv_image(ci) = 236;
        }
        break;
    case 579:
        if (dbmode == 3)
        {
            inv_image(ci) = 577;
        }
        break;
    case 578:
        if (dbmode == 3)
        {
            inv_image(ci) = 348;
            inv_function(ci) = 11;
        }
        break;
    case 577:
        if (dbmode == 3)
        {
            inv_image(ci) = 223;
        }
        if (dbmode == 15)
        {
            efid = 1133;
            efp = 100;
            label_2169();
            return -1;
        }
        break;
    case 576:
        if (dbmode == 3)
        {
            inv_image(ci) = 516;
            inv_function(ci) = 10;
        }
        break;
    case 575:
        if (dbmode == 3)
        {
            inv_image(ci) = 340;
        }
        break;
    case 574:
        if (dbmode == 3)
        {
            inv_image(ci) = 339;
        }
        if (dbmode == 15)
        {
            efid = 1101;
            efp = 100;
            label_2169();
            return -1;
        }
        break;
    case 573:
        if (dbmode == 3)
        {
            inv_image(ci) = 338;
            inv_param1(ci) = 8000;
            inv_param3(ci) = 240;
        }
        break;
    case 572:
        if (dbmode == 3)
        {
            inv_image(ci) = 308;
        }
        if (dbmode == 13)
        {
            efid = 1115;
            return -1;
        }
        break;
    case 571:
        if (dbmode == 3)
        {
            inv_image(ci) = 337;
            inv_param2(ci) = 5;
        }
        break;
    case 570:
        if (dbmode == 3)
        {
            inv_image(ci) = 471;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
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
            inv_image(ci) = 429;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 456;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 568:
        if (dbmode == 3)
        {
            inv_image(ci) = 335;
            inv_count(ci) = 12 + rnd(12) - rnd(12);
            ibitmod(4, ci, 1);
        }
        break;
    case 567:
        if (dbmode == 3)
        {
            inv_image(ci) = 335;
            inv_count(ci) = 12 + rnd(12) - rnd(12);
            ibitmod(4, ci, 1);
        }
        break;
    case 566:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 1116;
            efp = 250;
            label_2169();
            return -1;
        }
        break;
    case 565:
        if (dbmode == 3)
        {
            inv_image(ci) = 471;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
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
            inv_image(ci) = 429;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 455;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 563:
        if (dbmode == 3)
        {
            inv_image(ci) = 334;
            inv_param1(ci) = 0;
        }
        if (dbmode == 13)
        {
            label_2164();
            return -1;
        }
        break;
    case 562:
        if (dbmode == 3)
        {
            inv_image(ci) = 332;
            inv_function(ci) = 8;
        }
        break;
    case 561:
        if (dbmode == 3)
        {
            inv_image(ci) = 197;
        }
        break;
    case 560:
        if (dbmode == 3)
        {
            inv_image(ci) = 331;
            ibitmod(5, ci, 1);
        }
        break;
    case 559:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 1131;
            efp = 200;
            label_2169();
            return -1;
        }
        break;
    case 558:
        if (dbmode == 3)
        {
            inv_image(ci) = 489;
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
            inv_image(ci) = 422;
            fixeditemenc(0) = 30;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
        }
        break;
    case 556:
        if (dbmode == 3)
        {
            inv_image(ci) = 460;
            fixeditemenc(0) = 29;
            fixeditemenc(1) = 500;
            fixeditemenc(2) = 0;
        }
        break;
    case 555:
        if (dbmode == 3)
        {
            inv_image(ci) = 330;
            inv_function(ci) = 7;
        }
        break;
    case 554:
        if (dbmode == 3)
        {
            inv_image(ci) = 323;
            inv_param2(ci) = 1;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 553:
        if (dbmode == 3)
        {
            inv_image(ci) = 323;
            inv_param2(ci) = 1;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 552:
        if (dbmode == 3)
        {
            inv_image(ci) = 326;
            fixeditemenc(0) = 32;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
        }
        break;
    case 551:
        if (dbmode == 3)
        {
            inv_image(ci) = 471;
            inv_count(ci) = 3 + rnd(3) - rnd(3);
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
            inv_image(ci) = 429;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 405;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 549:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 404;
            efp = 400;
            label_2171();
            return -1;
        }
        break;
    case 548:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 404;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 547:
        if (dbmode == 3)
        {
            inv_image(ci) = 325;
        }
        break;
    case 546:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 438;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 545:
        if (dbmode == 3)
        {
            inv_image(ci) = 471;
            inv_count(ci) = 7 + rnd(7) - rnd(7);
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
            inv_image(ci) = 516;
            inv_function(ci) = 6;
            inv_param1(ci) = discsetmc();
        }
        break;
    case 543:
        if (dbmode == 3)
        {
            inv_image(ci) = 308;
        }
        if (dbmode == 13)
        {
            efid = 1115;
            return -1;
        }
        break;
    case 542:
        if (dbmode == 3)
        {
            inv_image(ci) = 308;
        }
        if (dbmode == 13)
        {
            efid = 1115;
            return -1;
        }
        break;
    case 541:
        if (dbmode == 3)
        {
            inv_image(ci) = 134;
        }
        break;
    case 540:
        if (dbmode == 3)
        {
            inv_image(ci) = 130;
        }
        break;
    case 539:
        if (dbmode == 3)
        {
            inv_image(ci) = 578;
        }
        break;
    case 538:
        if (dbmode == 3)
        {
            inv_image(ci) = 131;
        }
        break;
    case 537:
        if (dbmode == 3)
        {
            inv_image(ci) = 92;
        }
        break;
    case 536:
        if (dbmode == 3)
        {
            inv_image(ci) = 81;
        }
        break;
    case 535:
        if (dbmode == 3)
        {
            inv_image(ci) = 83;
        }
        break;
    case 534:
        if (dbmode == 3)
        {
            inv_image(ci) = 582;
        }
        break;
    case 533:
        if (dbmode == 3)
        {
            inv_image(ci) = 581;
        }
        break;
    case 532:
        if (dbmode == 3)
        {
            inv_image(ci) = 584;
        }
        break;
    case 531:
        if (dbmode == 3)
        {
            inv_image(ci) = 583;
        }
        break;
    case 530:
        if (dbmode == 3)
        {
            inv_image(ci) = 587;
        }
        break;
    case 529:
        if (dbmode == 3)
        {
            inv_image(ci) = 588;
        }
        break;
    case 528:
        if (dbmode == 3)
        {
            inv_image(ci) = 589;
        }
        break;
    case 527:
        if (dbmode == 3)
        {
            inv_image(ci) = 590;
        }
        break;
    case 526:
        if (dbmode == 3)
        {
            inv_image(ci) = 591;
            inv_param1(ci) = rnd(5) + 2;
            inv_param2(ci) = isetfruit(rnd(length(isetfruit)));
        }
        break;
    case 525:
        if (dbmode == 3)
        {
            inv_image(ci) = 592;
        }
        break;
    case 524:
        if (dbmode == 3)
        {
            inv_image(ci) = 593;
        }
        break;
    case 523:
        if (dbmode == 3)
        {
            inv_image(ci) = 527;
        }
        break;
    case 522:
        if (dbmode == 3)
        {
            inv_image(ci) = 308;
            inv_param1(ci) = 1;
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
            inv_image(ci) = 308;
            inv_param1(ci) = 1;
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
            inv_image(ci) = 522;
            fixeditemenc(0) = 32;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
        }
        break;
    case 519:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 1108;
            efp = 150;
            label_2169();
            return -1;
        }
        break;
    case 518:
        if (dbmode == 3)
        {
            inv_image(ci) = 471;
            inv_count(ci) = 3 + rnd(3) - rnd(3);
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
            inv_image(ci) = 471;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
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
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 1103;
            efp = 100;
            label_2169();
            return -1;
        }
        break;
    case 515:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 1129;
            efp = 300;
            label_2171();
            return -1;
        }
        break;
    case 514:
        if (dbmode == 3)
        {
            inv_skill(ci) = 110;
            inv_image(ci) = 520;
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
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 513:
        if (dbmode == 3)
        {
            inv_skill(ci) = 110;
            inv_image(ci) = 521;
        }
        break;
    case 512:
        if (dbmode == 3)
        {
            inv_skill(ci) = 110;
            inv_image(ci) = 520;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 1;
        }
        break;
    case 511:
        if (dbmode == 3)
        {
            inv_image(ci) = 308;
            inv_param1(ci) = 100 + rnd(200);
        }
        if (dbmode == 13)
        {
            efid = 1128;
            efp = inv_param1(ci);
            label_2171();
            return -1;
        }
        break;
    case 510:
        if (dbmode == 3)
        {
            inv_image(ci) = 253;
        }
        break;
    case 509:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 1125;
            efp = 400;
            label_2171();
            return -1;
        }
        break;
    case 508:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 1125;
            efp = 200;
            label_2171();
            return -1;
        }
        break;
    case 507:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 1124;
            efp = 400;
            label_2171();
            return -1;
        }
        break;
    case 506:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 1124;
            efp = 200;
            label_2171();
            return -1;
        }
        break;
    case 505:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            ibitmod(5, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 1123;
            efp = 100;
            label_2171();
            return -1;
        }
        break;
    case 504:
        if (dbmode == 3)
        {
            inv_image(ci) = 528;
            inv_function(ci) = 38;
        }
        break;
    case 503:
        if (dbmode == 3)
        {
            inv_image(ci) = 531;
        }
        break;
    case 502:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 1127;
            efp = 350;
            label_2171();
            return -1;
        }
        break;
    case 501:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 1127;
            efp = 180;
            label_2171();
            return -1;
        }
        break;
    case 500:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 1127;
            efp = 10;
            label_2171();
            return -1;
        }
        break;
    case 499:
        if (dbmode == 3)
        {
            inv_image(ci) = 519;
            inv_param2(ci) = 7;
        }
        break;
    case 498:
        if (dbmode == 3)
        {
            inv_image(ci) = 518;
            inv_param2(ci) = 6;
        }
        break;
    case 497:
        if (dbmode == 3)
        {
            inv_image(ci) = 517;
            inv_param2(ci) = 5;
        }
        break;
    case 496:
        if (dbmode == 3)
        {
            inv_skill(ci) = 110;
            inv_image(ci) = 514;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 1;
        }
        break;
    case 495:
        if (dbmode == 3)
        {
            inv_image(ci) = 516;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 1;
        }
        break;
    case 494:
        if (dbmode == 3)
        {
            inv_image(ci) = 515;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 1;
        }
        break;
    case 493:
        if (dbmode == 3)
        {
            inv_image(ci) = 513;
        }
        break;
    case 492:
        if (dbmode == 3)
        {
            inv_image(ci) = 512;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 1;
        }
        break;
    case 491:
        if (dbmode == 3)
        {
            inv_image(ci) = 511;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 1;
        }
        break;
    case 490:
        if (dbmode == 3)
        {
            inv_image(ci) = 510;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 1;
        }
        break;
    case 489:
        if (dbmode == 3)
        {
            inv_image(ci) = 509;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 1;
        }
        break;
    case 488:
        if (dbmode == 3)
        {
            inv_image(ci) = 506;
            inv_function(ci) = 9;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 1;
        }
        break;
    case 487:
        if (dbmode == 3)
        {
            inv_image(ci) = 508;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 1;
        }
        break;
    case 486:
        if (dbmode == 3)
        {
            inv_image(ci) = 507;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 1;
        }
        break;
    case 485:
        if (dbmode == 3)
        {
            inv_image(ci) = 471;
            inv_count(ci) = 8 + rnd(8) - rnd(8);
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
            inv_image(ci) = 429;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 436;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 483:
        if (dbmode == 3)
        {
            inv_skill(ci) = 109;
            inv_image(ci) = 412;
        }
        break;
    case 482:
        if (dbmode == 3)
        {
            inv_skill(ci) = 109;
            inv_image(ci) = 498;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 2;
        }
        break;
    case 481:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 2 + rnd(2) - rnd(2);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 435;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 480:
        if (dbmode == 3)
        {
            inv_image(ci) = 471;
            inv_count(ci) = 2 + rnd(2) - rnd(2);
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
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 1122;
            efp = 100;
            label_2171();
            return -1;
        }
        break;
    case 478:
        if (dbmode == 3)
        {
            inv_image(ci) = 493;
            inv_function(ci) = 5;
        }
        break;
    case 477:
        if (dbmode == 3)
        {
            inv_image(ci) = 489;
        }
        break;
    case 476:
        if (dbmode == 3)
        {
            inv_image(ci) = 490;
        }
        break;
    case 475:
        if (dbmode == 3)
        {
            inv_image(ci) = 491;
        }
        break;
    case 474:
        if (dbmode == 3)
        {
            inv_image(ci) = 492;
        }
        break;
    case 473:
        if (dbmode == 3)
        {
            inv_image(ci) = 483;
        }
        break;
    case 472:
        if (dbmode == 3)
        {
            inv_image(ci) = 484;
        }
        break;
    case 471:
        if (dbmode == 3)
        {
            inv_image(ci) = 485;
        }
        break;
    case 470:
        if (dbmode == 3)
        {
            inv_image(ci) = 486;
        }
        break;
    case 469:
        if (dbmode == 3)
        {
            inv_image(ci) = 487;
        }
        break;
    case 468:
        if (dbmode == 3)
        {
            inv_image(ci) = 488;
        }
        break;
    case 467:
        if (dbmode == 3)
        {
            inv_image(ci) = 482;
        }
        break;
    case 466:
        if (dbmode == 3)
        {
            inv_image(ci) = 479;
        }
        break;
    case 465:
        if (dbmode == 3)
        {
            inv_image(ci) = 480;
        }
        break;
    case 464:
        if (dbmode == 3)
        {
            inv_image(ci) = 481;
        }
        break;
    case 463:
        if (dbmode == 3)
        {
            inv_image(ci) = 413;
        }
        break;
    case 462:
        if (dbmode == 3)
        {
            inv_image(ci) = 476;
        }
        break;
    case 461:
        if (dbmode == 3)
        {
            inv_image(ci) = 475;
        }
        break;
    case 460:
        if (dbmode == 3)
        {
            inv_image(ci) = 474;
        }
        break;
    case 459:
        if (dbmode == 3)
        {
            inv_image(ci) = 474;
        }
        break;
    case 458:
        if (dbmode == 3)
        {
            inv_image(ci) = 461;
        }
        break;
    case 457:
        if (dbmode == 3)
        {
            inv_image(ci) = 459;
        }
        break;
    case 456:
        if (dbmode == 3)
        {
            inv_image(ci) = 473;
        }
        break;
    case 455:
        if (dbmode == 3)
        {
            inv_image(ci) = 473;
        }
        break;
    case 454:
        if (dbmode == 3)
        {
            inv_skill(ci) = 168;
            inv_image(ci) = 458;
        }
        break;
    case 453:
        if (dbmode == 3)
        {
            inv_skill(ci) = 168;
            inv_image(ci) = 457;
        }
        break;
    case 452:
        if (dbmode == 3)
        {
            inv_skill(ci) = 168;
            inv_image(ci) = 456;
        }
        break;
    case 451:
        if (dbmode == 3)
        {
            inv_skill(ci) = 168;
            inv_image(ci) = 455;
        }
        break;
    case 450:
        if (dbmode == 3)
        {
            inv_skill(ci) = 168;
            inv_image(ci) = 454;
        }
        break;
    case 449:
        if (dbmode == 3)
        {
            inv_skill(ci) = 168;
            inv_image(ci) = 453;
        }
        break;
    case 448:
        if (dbmode == 3)
        {
            inv_image(ci) = 452;
        }
        break;
    case 447:
        if (dbmode == 3)
        {
            inv_image(ci) = 451;
        }
        break;
    case 446:
        if (dbmode == 3)
        {
            inv_image(ci) = 414;
        }
        break;
    case 445:
        if (dbmode == 3)
        {
            inv_image(ci) = 448;
        }
        break;
    case 444:
        if (dbmode == 3)
        {
            inv_image(ci) = 447;
        }
        break;
    case 443:
        if (dbmode == 3)
        {
            inv_image(ci) = 446;
        }
        break;
    case 442:
        if (dbmode == 3)
        {
            inv_image(ci) = 445;
        }
        break;
    case 441:
        if (dbmode == 3)
        {
            inv_image(ci) = 444;
        }
        break;
    case 440:
        if (dbmode == 3)
        {
            inv_image(ci) = 443;
        }
        break;
    case 439:
        if (dbmode == 3)
        {
            inv_image(ci) = 442;
        }
        break;
    case 438:
        if (dbmode == 3)
        {
            inv_image(ci) = 441;
        }
        break;
    case 437:
        if (dbmode == 3)
        {
            inv_image(ci) = 440;
        }
        break;
    case 436:
        if (dbmode == 3)
        {
            inv_image(ci) = 410;
        }
        break;
    case 435:
        if (dbmode == 3)
        {
            inv_image(ci) = 409;
        }
        break;
    case 434:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 2 + rnd(2) - rnd(2);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 454;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 433:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 1121;
            efp = 200;
            label_2169();
            return -1;
        }
        break;
    case 432:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 454;
            efp = 100;
            label_2169();
            return -1;
        }
        break;
    case 431:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 1107;
            efp = 300;
            label_2171();
            return -1;
        }
        break;
    case 430:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 1119;
            efp = 500;
            label_2171();
            return -1;
        }
        break;
    case 429:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 1118;
            efp = 100;
            label_2169();
            return -1;
        }
        break;
    case 428:
        if (dbmode == 3)
        {
            inv_image(ci) = 324;
            inv_param1(ci) = 0;
        }
        break;
    case 427:
        if (dbmode == 3)
        {
            inv_image(ci) = 170;
            inv_param2(ci) = 7;
        }
        break;
    case 426:
        if (dbmode == 3)
        {
            inv_image(ci) = 170;
            inv_param2(ci) = 3;
        }
        break;
    case 425:
        if (dbmode == 3)
        {
            inv_image(ci) = 170;
            inv_param2(ci) = 6;
        }
        break;
    case 424:
        if (dbmode == 3)
        {
            inv_image(ci) = 170;
            inv_param2(ci) = 3;
        }
        break;
    case 423:
        if (dbmode == 3)
        {
            inv_image(ci) = 170;
            inv_param2(ci) = 4;
        }
        break;
    case 422:
        if (dbmode == 3)
        {
            inv_image(ci) = 170;
            inv_param2(ci) = 1;
        }
        break;
    case 421:
        if (dbmode == 3)
        {
            inv_image(ci) = 323;
            inv_param2(ci) = 1;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 420:
        if (dbmode == 3)
        {
            inv_image(ci) = 323;
            inv_param2(ci) = 1;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 419:
        if (dbmode == 3)
        {
            inv_image(ci) = 323;
            inv_param2(ci) = 1;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 418:
        if (dbmode == 3)
        {
            inv_image(ci) = 323;
            inv_param2(ci) = 1;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 417:
        if (dbmode == 3)
        {
            inv_image(ci) = 323;
            inv_param2(ci) = 1;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 416:
        if (dbmode == 3)
        {
            inv_image(ci) = 322;
        }
        break;
    case 415:
        if (dbmode == 3)
        {
            inv_image(ci) = 322;
        }
        break;
    case 414:
        if (dbmode == 3)
        {
            inv_image(ci) = 321;
        }
        break;
    case 413:
        if (dbmode == 3)
        {
            inv_image(ci) = 320;
        }
        break;
    case 412:
        if (dbmode == 3)
        {
            inv_image(ci) = 471;
            inv_count(ci) = 3 + rnd(3) - rnd(3);
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
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 430;
            efp = 500;
            label_2171();
            return -1;
        }
        break;
    case 410:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 430;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 409:
        if (dbmode == 3)
        {
            inv_image(ci) = 251;
            inv_param1(ci) = 5;
        }
        break;
    case 408:
        if (dbmode == 3)
        {
            inv_image(ci) = 68;
            inv_param1(ci) = 1;
        }
        break;
    case 407:
        if (dbmode == 3)
        {
            inv_image(ci) = 208;
            inv_param1(ci) = 2;
        }
        break;
    case 406:
        if (dbmode == 3)
        {
            inv_image(ci) = 316;
            inv_param1(ci) = 0;
        }
        break;
    case 405:
        if (dbmode == 3)
        {
            inv_image(ci) = 161;
            inv_param1(ci) = 3;
        }
        break;
    case 404:
        if (dbmode == 3)
        {
            inv_image(ci) = 312;
            inv_param1(ci) = 0;
        }
        break;
    case 403:
        if (dbmode == 3)
        {
            inv_image(ci) = 269;
            inv_param1(ci) = 3;
        }
        break;
    case 402:
        if (dbmode == 3)
        {
            inv_image(ci) = 202;
            inv_param1(ci) = 5;
        }
        break;
    case 401:
        if (dbmode == 3)
        {
            inv_image(ci) = 292;
            inv_param1(ci) = 4;
        }
        break;
    case 400:
        if (dbmode == 3)
        {
            inv_image(ci) = 72;
            inv_param1(ci) = 2;
        }
        break;
    case 399:
        if (dbmode == 3)
        {
            inv_image(ci) = 67;
            inv_param1(ci) = 1;
        }
        break;
    case 398:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 453;
            efp = 250;
            label_2171();
            return -1;
        }
        break;
    case 397:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 5 + rnd(5) - rnd(5);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 453;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 396:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 452;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 395:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 1117;
            efp = 250;
            label_2171();
            return -1;
        }
        break;
    case 394:
        if (dbmode == 3)
        {
            inv_image(ci) = 438;
        }
        break;
    case 393:
        if (dbmode == 3)
        {
            inv_image(ci) = 319;
            inv_function(ci) = 3;
        }
        break;
    case 392:
        if (dbmode == 3)
        {
            inv_image(ci) = 223;
        }
        if (dbmode == 15)
        {
            efid = 1116;
            efp = 100;
            label_2169();
            return -1;
        }
        break;
    case 391:
        if (dbmode == 3)
        {
            inv_image(ci) = 471;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
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
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 621;
            efp = 250;
            label_2171();
            return -1;
        }
        break;
    case 389:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 407;
            efp = 300;
            label_2171();
            return -1;
        }
        break;
    case 388:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 406;
            efp = 300;
            label_2171();
            return -1;
        }
        break;
    case 387:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 407;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 386:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 406;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 385:
        if (dbmode == 3)
        {
            inv_image(ci) = 471;
            inv_count(ci) = 6 + rnd(6) - rnd(6);
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
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 451;
            efp = 250;
            label_2171();
            return -1;
        }
        break;
    case 383:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 451;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 382:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 449;
            efp = 250;
            label_2169();
            return -1;
        }
        break;
    case 381:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 450;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 380:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 449;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 379:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 448;
            efp = 250;
            label_2169();
            return -1;
        }
        break;
    case 378:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 5 + rnd(5) - rnd(5);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 448;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 377:
        if (dbmode == 3)
        {
            inv_image(ci) = 471;
            inv_count(ci) = 8 + rnd(8) - rnd(8);
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
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 447;
            efp = 400;
            label_2169();
            return -1;
        }
        break;
    case 375:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 446;
            efp = 250;
            label_2169();
            return -1;
        }
        break;
    case 374:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 447;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 373:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 446;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 372:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 445;
            efp = 250;
            label_2169();
            return -1;
        }
        break;
    case 371:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 445;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 370:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 444;
            efp = 300;
            label_2169();
            return -1;
        }
        break;
    case 369:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 444;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 368:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 443;
            efp = 400;
            label_2169();
            return -1;
        }
        break;
    case 367:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 443;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 366:
        if (dbmode == 3)
        {
            inv_image(ci) = 471;
            inv_count(ci) = 7 + rnd(7) - rnd(7);
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
            inv_image(ci) = 429;
            inv_count(ci) = 5 + rnd(5) - rnd(5);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 442;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 364:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 442;
            efp = 200;
            label_2169();
            return -1;
        }
        break;
    case 363:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 412;
            efp = 2500;
            label_2171();
            return -1;
        }
        break;
    case 362:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 411;
            efp = 2000;
            label_2171();
            return -1;
        }
        break;
    case 361:
        if (dbmode == 3)
        {
            inv_image(ci) = 253;
        }
        break;
    case 360:
        if (dbmode == 3)
        {
            inv_image(ci) = 407;
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
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 359:
        if (dbmode == 3)
        {
            inv_skill(ci) = 104;
            inv_image(ci) = 426;
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
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 358:
        if (dbmode == 3)
        {
            inv_skill(ci) = 105;
            inv_image(ci) = 425;
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
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 357:
        if (dbmode == 3)
        {
            inv_image(ci) = 407;
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
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 356:
        if (dbmode == 3)
        {
            inv_skill(ci) = 103;
            inv_image(ci) = 427;
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
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 355:
        if (dbmode == 3)
        {
            inv_image(ci) = 414;
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
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 354:
        if (dbmode == 3)
        {
            inv_image(ci) = 318;
            inv_param1(ci) = 6000;
            inv_param3(ci) = 4;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 4;
        }
        break;
    case 353:
        if (dbmode == 3)
        {
            inv_image(ci) = 317;
            inv_param1(ci) = 6000;
            inv_param3(ci) = 4;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 4;
        }
        break;
    case 352:
        if (dbmode == 3)
        {
            inv_image(ci) = 316;
            inv_param1(ci) = 6000;
            inv_param3(ci) = 4;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 4;
        }
        break;
    case 351:
        if (dbmode == 3)
        {
            inv_image(ci) = 315;
            inv_param1(ci) = 6000;
            inv_param3(ci) = 4;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 4;
        }
        break;
    case 350:
        if (dbmode == 3)
        {
            inv_image(ci) = 314;
            inv_param1(ci) = 6000;
            inv_param3(ci) = 4;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 4;
        }
        break;
    case 349:
        if (dbmode == 3)
        {
            inv_image(ci) = 313;
            inv_param1(ci) = 6000;
            inv_param3(ci) = 4;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 4;
        }
        break;
    case 348:
        if (dbmode == 3)
        {
            inv_image(ci) = 312;
            inv_param1(ci) = 6000;
            inv_param3(ci) = 4;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 4;
        }
        break;
    case 347:
        if (dbmode == 3)
        {
            inv_image(ci) = 311;
            inv_param1(ci) = 6000;
            inv_param3(ci) = 4;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 4;
        }
        break;
    case 346:
        if (dbmode == 3)
        {
            inv_image(ci) = 310;
            inv_param1(ci) = 6000;
            inv_param3(ci) = 4;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 4;
        }
        break;
    case 345:
        if (dbmode == 3)
        {
            inv_image(ci) = 309;
            inv_param1(ci) = 6000;
            inv_param3(ci) = 4;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 4;
        }
        break;
    case 344:
        if (dbmode == 3)
        {
            inv_image(ci) = 308;
            inv_param1(ci) = 1;
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
            inv_image(ci) = 307;
            inv_function(ci) = 22;
        }
        break;
    case 342:
        if (dbmode == 3)
        {
            inv_image(ci) = 306;
            inv_function(ci) = 16;
            inv_param1(ci) = 60;
        }
        break;
    case 341:
        if (dbmode == 3)
        {
            inv_image(ci) = 305;
        }
        break;
    case 340:
        if (dbmode == 3)
        {
            inv_image(ci) = 304;
        }
        break;
    case 339:
        if (dbmode == 3)
        {
            inv_image(ci) = 303;
        }
        break;
    case 338:
        if (dbmode == 3)
        {
            inv_image(ci) = 302;
        }
        break;
    case 337:
        if (dbmode == 3)
        {
            inv_image(ci) = 301;
        }
        break;
    case 336:
        if (dbmode == 3)
        {
            inv_image(ci) = 300;
        }
        break;
    case 335:
        if (dbmode == 3)
        {
            inv_image(ci) = 299;
        }
        break;
    case 334:
        if (dbmode == 3)
        {
            inv_image(ci) = 579;
            inv_function(ci) = 44;
        }
        break;
    case 333:
        if (dbmode == 3)
        {
            inv_image(ci) = 297;
            inv_param2(ci) = 3;
        }
        break;
    case 332:
        if (dbmode == 3)
        {
            inv_image(ci) = 296;
        }
        break;
    case 331:
        if (dbmode == 3)
        {
            inv_image(ci) = 295;
        }
        break;
    case 330:
        if (dbmode == 3)
        {
            inv_image(ci) = 294;
            inv_function(ci) = 44;
        }
        break;
    case 329:
        if (dbmode == 3)
        {
            inv_image(ci) = 293;
        }
        break;
    case 328:
        if (dbmode == 3)
        {
            inv_image(ci) = 292;
            inv_function(ci) = 17;
            inv_param1(ci) = 150;
        }
        break;
    case 327:
        if (dbmode == 3)
        {
            inv_image(ci) = 291;
            inv_function(ci) = 44;
        }
        break;
    case 326:
        if (dbmode == 3)
        {
            inv_image(ci) = 290;
        }
        break;
    case 325:
        if (dbmode == 3)
        {
            inv_image(ci) = 289;
            inv_param1(ci) = 130;
        }
        break;
    case 324:
        if (dbmode == 3)
        {
            inv_image(ci) = 288;
        }
        break;
    case 323:
        if (dbmode == 3)
        {
            inv_image(ci) = 586;
        }
        break;
    case 322:
        if (dbmode == 3)
        {
            inv_image(ci) = 286;
            inv_function(ci) = 19;
        }
        break;
    case 321:
        if (dbmode == 3)
        {
            inv_image(ci) = 285;
        }
        break;
    case 320:
        if (dbmode == 3)
        {
            inv_image(ci) = 284;
        }
        break;
    case 319:
        if (dbmode == 3)
        {
            inv_image(ci) = 283;
            inv_param1(ci) = 0;
        }
        break;
    case 318:
        if (dbmode == 3)
        {
            inv_image(ci) = 282;
        }
        break;
    case 317:
        if (dbmode == 3)
        {
            inv_image(ci) = 281;
        }
        break;
    case 316:
        if (dbmode == 3)
        {
            inv_image(ci) = 280;
        }
        break;
    case 315:
        if (dbmode == 3)
        {
            inv_image(ci) = 279;
        }
        break;
    case 314:
        if (dbmode == 3)
        {
            inv_image(ci) = 278;
        }
        break;
    case 313:
        if (dbmode == 3)
        {
            inv_image(ci) = 277;
        }
        break;
    case 312:
        if (dbmode == 3)
        {
            inv_image(ci) = 276;
        }
        break;
    case 311:
        if (dbmode == 3)
        {
            inv_image(ci) = 275;
        }
        break;
    case 310:
        if (dbmode == 3)
        {
            inv_image(ci) = 274;
            inv_param1(ci) = 130;
        }
        break;
    case 309:
        if (dbmode == 3)
        {
            inv_image(ci) = 273;
            inv_function(ci) = 19;
        }
        break;
    case 308:
        if (dbmode == 3)
        {
            inv_image(ci) = 272;
        }
        break;
    case 307:
        if (dbmode == 3)
        {
            inv_image(ci) = 271;
            inv_param1(ci) = 130;
        }
        break;
    case 306:
        if (dbmode == 3)
        {
            inv_image(ci) = 270;
            inv_function(ci) = 15;
            inv_param1(ci) = 200;
        }
        break;
    case 305:
        if (dbmode == 3)
        {
            inv_image(ci) = 269;
            inv_param1(ci) = 130;
        }
        break;
    case 304:
        if (dbmode == 3)
        {
            inv_image(ci) = 268;
            inv_param1(ci) = 100;
        }
        break;
    case 303:
        if (dbmode == 3)
        {
            inv_image(ci) = 267;
            inv_param1(ci) = 120;
        }
        break;
    case 302:
        if (dbmode == 3)
        {
            inv_image(ci) = 266;
        }
        break;
    case 301:
        if (dbmode == 3)
        {
            inv_image(ci) = 265;
        }
        break;
    case 300:
        if (dbmode == 3)
        {
            inv_image(ci) = 264;
        }
        break;
    case 299:
        if (dbmode == 3)
        {
            inv_image(ci) = 263;
            inv_function(ci) = 19;
        }
        break;
    case 298:
        if (dbmode == 3)
        {
            inv_image(ci) = 262;
        }
        break;
    case 297:
        if (dbmode == 3)
        {
            inv_image(ci) = 261;
            inv_param1(ci) = 150;
        }
        break;
    case 296:
        if (dbmode == 3)
        {
            inv_image(ci) = 260;
        }
        break;
    case 295:
        if (dbmode == 3)
        {
            inv_image(ci) = 259;
        }
        break;
    case 294:
        if (dbmode == 3)
        {
            inv_image(ci) = 258;
        }
        break;
    case 293:
        if (dbmode == 3)
        {
            inv_image(ci) = 257;
        }
        break;
    case 292:
        if (dbmode == 3)
        {
            inv_image(ci) = 256;
        }
        break;
    case 291:
        if (dbmode == 3)
        {
            inv_image(ci) = 255;
        }
        break;
    case 290:
        if (dbmode == 3)
        {
            inv_image(ci) = 471;
            inv_count(ci) = 1 + rnd(1) - rnd(1);
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
            inv_image(ci) = 429;
            inv_count(ci) = 1 + rnd(1) - rnd(1);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 441;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 288:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 1114;
            efp = 100;
            label_2171();
            return -1;
        }
        break;
    case 287:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 1113;
            efp = 100;
            label_2169();
            return -1;
        }
        break;
    case 286:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 440;
            efp = 100;
            label_2169();
            return -1;
        }
        break;
    case 285:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 439;
            efp = 100;
            label_2169();
            return -1;
        }
        break;
    case 284:
        if (dbmode == 3)
        {
            inv_image(ci) = 254;
        }
        break;
    case 283:
        if (dbmode == 3)
        {
            inv_image(ci) = 253;
        }
        break;
    case 282:
        if (dbmode == 3)
        {
            inv_image(ci) = 252;
        }
        break;
    case 281:
        if (dbmode == 3)
        {
            inv_image(ci) = 251;
        }
        break;
    case 280:
        if (dbmode == 3)
        {
            inv_image(ci) = 250;
        }
        break;
    case 279:
        if (dbmode == 3)
        {
            inv_image(ci) = 249;
        }
        break;
    case 278:
        if (dbmode == 3)
        {
            inv_image(ci) = 585;
        }
        break;
    case 277:
        if (dbmode == 3)
        {
            inv_image(ci) = 82;
        }
        break;
    case 276:
        if (dbmode == 3)
        {
            inv_image(ci) = 524;
        }
        break;
    case 275:
        if (dbmode == 3)
        {
            inv_image(ci) = 248;
        }
        break;
    case 274:
        if (dbmode == 3)
        {
            inv_image(ci) = 232;
        }
        break;
    case 273:
        if (dbmode == 3)
        {
            inv_image(ci) = 231;
        }
        break;
    case 272:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 433;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 271:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 434;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 270:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 432;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 269:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 431;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 268:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 423;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 267:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 422;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 266:
        if (dbmode == 3)
        {
            inv_skill(ci) = 101;
            inv_image(ci) = 432;
        }
        break;
    case 265:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 416;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 264:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 417;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 263:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 415;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 262:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 1108;
            efp = 200;
            label_2169();
            return -1;
        }
        break;
    case 261:
        if (dbmode == 3)
        {
            inv_image(ci) = 201;
            inv_param1(ci) = 6000;
            inv_param3(ci) = 6;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 4;
        }
        break;
    case 260:
        if (dbmode == 3)
        {
            inv_image(ci) = 233;
            inv_param1(ci) = 7000;
            inv_param3(ci) = 240;
        }
        break;
    case 259:
        if (dbmode == 3)
        {
            inv_image(ci) = 233;
            inv_param1(ci) = 5000;
            inv_param3(ci) = 24;
        }
        break;
    case 258:
        if (dbmode == 3)
        {
            inv_image(ci) = 117;
            inv_param2(ci) = 3;
        }
        break;
    case 257:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 5 + rnd(5) - rnd(5);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 414;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 256:
        if (dbmode == 3)
        {
            inv_image(ci) = 226;
            inv_function(ci) = 15;
            inv_param1(ci) = 80;
        }
        break;
    case 255:
        if (dbmode == 3)
        {
            inv_image(ci) = 349;
            inv_function(ci) = 15;
            inv_param1(ci) = 40;
        }
        break;
    case 254:
        if (dbmode == 3)
        {
            inv_skill(ci) = 183;
            inv_image(ci) = 224;
            inv_function(ci) = 17;
            inv_param1(ci) = 110;
        }
        break;
    case 253:
        if (dbmode == 3)
        {
            inv_image(ci) = 223;
        }
        if (dbmode == 15)
        {
            efid = 1102;
            efp = 200;
            label_2169();
            return -1;
        }
        break;
    case 252:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 2 + rnd(2) - rnd(2);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 403;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 251:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 402;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 250:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 401;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 249:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 5 + rnd(5) - rnd(5);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 400;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 248:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 3 + rnd(3) - rnd(3);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 428;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 247:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 2 + rnd(2) - rnd(2);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 413;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 246:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 429;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 245:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 408;
            efp = 100;
            label_2171();
            return -1;
        }
        break;
    case 244:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 1104;
            efp = 100;
            label_2171();
            return -1;
        }
        break;
    case 243:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 1105;
            efp = 100;
            label_2171();
            return -1;
        }
        break;
    case 242:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 429;
            efp = 500;
            label_2171();
            return -1;
        }
        break;
    case 241:
        if (dbmode == 3)
        {
            inv_image(ci) = 197;
        }
        break;
    case 240:
        if (dbmode == 3)
        {
            inv_image(ci) = 220;
        }
        break;
    case 239:
        if (dbmode == 3)
        {
            inv_image(ci) = 220;
        }
        break;
    case 238:
        if (dbmode == 3)
        {
            inv_image(ci) = 221;
        }
        break;
    case 237:
        if (dbmode == 3)
        {
            inv_image(ci) = 222;
        }
        break;
    case 236:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 428;
            efp = 100;
            label_2171();
            return -1;
        }
        break;
    case 235:
        if (dbmode == 3)
        {
            inv_skill(ci) = 104;
            inv_image(ci) = 426;
        }
        break;
    case 234:
        if (dbmode == 3)
        {
            inv_skill(ci) = 102;
            inv_image(ci) = 399;
        }
        break;
    case 233:
        if (dbmode == 3)
        {
            inv_image(ci) = 233;
            inv_param2(ci) = 3;
        }
        break;
    case 232:
        if (dbmode == 3)
        {
            inv_skill(ci) = 100;
            inv_image(ci) = 503;
        }
        break;
    case 231:
        if (dbmode == 3)
        {
            inv_skill(ci) = 110;
            inv_image(ci) = 547;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 1;
        }
        break;
    case 230:
        if (dbmode == 3)
        {
            inv_skill(ci) = 108;
            inv_image(ci) = 404;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 2;
        }
        break;
    case 229:
        if (dbmode == 3)
        {
            inv_skill(ci) = 105;
            inv_image(ci) = 505;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 3;
        }
        break;
    case 228:
        if (dbmode == 3)
        {
            inv_skill(ci) = 104;
            inv_image(ci) = 494;
        }
        break;
    case 227:
        if (dbmode == 3)
        {
            inv_skill(ci) = 103;
            inv_image(ci) = 504;
        }
        break;
    case 226:
        if (dbmode == 3)
        {
            inv_skill(ci) = 102;
            inv_image(ci) = 500;
        }
        break;
    case 225:
        if (dbmode == 3)
        {
            inv_skill(ci) = 101;
            inv_image(ci) = 502;
        }
        break;
    case 224:
        if (dbmode == 3)
        {
            inv_skill(ci) = 100;
            inv_image(ci) = 431;
        }
        break;
    case 223:
        if (dbmode == 3)
        {
            inv_image(ci) = 198;
            inv_function(ci) = 15;
            inv_param1(ci) = 60;
        }
        break;
    case 222:
        if (dbmode == 3)
        {
            inv_image(ci) = 199;
        }
        break;
    case 221:
        if (dbmode == 3)
        {
            inv_image(ci) = 200;
        }
        break;
    case 220:
        if (dbmode == 3)
        {
            inv_image(ci) = 201;
        }
        break;
    case 219:
        if (dbmode == 3)
        {
            inv_image(ci) = 202;
            inv_function(ci) = 46;
        }
        break;
    case 218:
        if (dbmode == 3)
        {
            inv_image(ci) = 203;
        }
        break;
    case 217:
        if (dbmode == 3)
        {
            inv_image(ci) = 206;
        }
        break;
    case 216:
        if (dbmode == 3)
        {
            inv_image(ci) = 207;
        }
        break;
    case 215:
        if (dbmode == 3)
        {
            inv_image(ci) = 208;
        }
        break;
    case 214:
        if (dbmode == 3)
        {
            inv_image(ci) = 209;
        }
        break;
    case 213:
        if (dbmode == 3)
        {
            inv_skill(ci) = 104;
            inv_image(ci) = 401;
        }
        break;
    case 212:
        if (dbmode == 3)
        {
            inv_skill(ci) = 105;
            inv_image(ci) = 425;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 3;
        }
        break;
    case 211:
        if (dbmode == 3)
        {
            inv_skill(ci) = 107;
            inv_image(ci) = 421;
            fixeditemenc(0) = 80025;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
        }
        break;
    case 210:
        if (dbmode == 3)
        {
            inv_skill(ci) = 111;
            inv_image(ci) = 424;
        }
        break;
    case 209:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 412;
            efp = 100;
            label_2171();
            return -1;
        }
        break;
    case 208:
        if (dbmode == 3)
        {
            inv_image(ci) = 33;
        }
        break;
    case 207:
        if (dbmode == 3)
        {
            inv_skill(ci) = 108;
            inv_image(ci) = 404;
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
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 206:
        if (dbmode == 3)
        {
            inv_skill(ci) = 101;
            inv_image(ci) = 400;
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
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 205:
        if (dbmode == 3)
        {
            inv_image(ci) = 210;
        }
        if (dbmode == 15)
        {
            efid = 1102;
            efp = 500;
            label_2169();
            return -1;
        }
        break;
    case 204:
        if (dbmode == 3)
        {
            inv_image(ci) = 196;
            inv_param1(ci) = 1000;
            inv_param3(ci) = 4;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return 1;
        }
        break;
    case 203:
        if (dbmode == 3)
        {
            inv_image(ci) = 471;
            inv_count(ci) = 8 + rnd(8) - rnd(8);
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
            inv_image(ci) = 471;
            inv_count(ci) = 9 + rnd(9) - rnd(9);
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
            inv_image(ci) = 193;
            inv_param1(ci) = 2000;
            inv_param3(ci) = 2;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 200:
        if (dbmode == 3)
        {
            inv_image(ci) = 192;
            inv_param1(ci) = 2000;
            inv_param3(ci) = 72;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 199:
        if (dbmode == 3)
        {
            inv_image(ci) = 191;
            inv_param1(ci) = 2000;
            inv_param3(ci) = 72;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 198:
        if (dbmode == 3)
        {
            inv_image(ci) = 164;
            inv_param1(ci) = 2000;
            inv_param3(ci) = 72;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 197:
        if (dbmode == 3)
        {
            inv_image(ci) = 189;
            inv_param1(ci) = 3000;
            inv_param3(ci) = 12;
        }
        break;
    case 196:
        if (dbmode == 3)
        {
            inv_image(ci) = 188;
            inv_param1(ci) = 3000;
            inv_param3(ci) = 8;
        }
        break;
    case 195:
        if (dbmode == 3)
        {
            inv_image(ci) = 187;
            inv_param1(ci) = 3000;
            inv_param3(ci) = 12;
        }
        break;
    case 194:
        if (dbmode == 3)
        {
            inv_image(ci) = 186;
            inv_param1(ci) = 3000;
            inv_param3(ci) = 8;
        }
        break;
    case 193:
        if (dbmode == 3)
        {
            inv_image(ci) = 185;
            inv_param1(ci) = 2000;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 192:
        if (dbmode == 3)
        {
            inv_image(ci) = 184;
            inv_param1(ci) = 3000;
            inv_param3(ci) = 16;
        }
        break;
    case 191:
        if (dbmode == 3)
        {
            inv_image(ci) = 183;
            inv_param1(ci) = 4000;
        }
        break;
    case 190:
        if (dbmode == 3)
        {
            inv_image(ci) = 182;
            inv_param1(ci) = 2000;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 189:
        if (dbmode == 3)
        {
            inv_image(ci) = 181;
        }
        break;
    case 188:
        if (dbmode == 3)
        {
            inv_image(ci) = 180;
            inv_param1(ci) = 2000;
            inv_param3(ci) = 72;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 187:
        if (dbmode == 3)
        {
            inv_image(ci) = 179;
            inv_param1(ci) = 2000;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 186:
        if (dbmode == 3)
        {
            inv_image(ci) = 178;
            inv_param1(ci) = 2000;
            inv_param3(ci) = 72;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 185:
        if (dbmode == 3)
        {
            inv_image(ci) = 177;
            inv_param1(ci) = 2000;
            inv_param3(ci) = 72;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 184:
        if (dbmode == 3)
        {
            inv_image(ci) = 176;
            inv_param1(ci) = 3000;
            inv_param3(ci) = 8;
        }
        break;
    case 183:
        if (dbmode == 3)
        {
            inv_image(ci) = 175;
            inv_param1(ci) = 3000;
            inv_param3(ci) = 16;
        }
        break;
    case 182:
        if (dbmode == 3)
        {
            inv_image(ci) = 174;
            inv_param1(ci) = 3000;
            inv_param3(ci) = 12;
        }
        break;
    case 181:
        if (dbmode == 3)
        {
            inv_image(ci) = 173;
            inv_param1(ci) = 3000;
            inv_param3(ci) = 16;
        }
        break;
    case 180:
        if (dbmode == 3)
        {
            inv_image(ci) = 172;
            inv_param1(ci) = 3000;
            inv_param3(ci) = 16;
        }
        break;
    case 179:
        if (dbmode == 3)
        {
            inv_image(ci) = 171;
            inv_param1(ci) = 2000;
            inv_param3(ci) = 48;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 178:
        if (dbmode == 3)
        {
            inv_image(ci) = 170;
            inv_param1(ci) = 3000;
            inv_param3(ci) = 72;
        }
        break;
    case 177:
        if (dbmode == 3)
        {
            inv_image(ci) = 169;
            inv_param1(ci) = 3000;
            inv_param3(ci) = 72;
        }
        break;
    case 176:
        if (dbmode == 3)
        {
            inv_image(ci) = 471;
            inv_count(ci) = 8 + rnd(8) - rnd(8);
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
            inv_image(ci) = 471;
            inv_count(ci) = 10 + rnd(10) - rnd(10);
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
            inv_image(ci) = 166;
            inv_param1(ci) = 110;
        }
        break;
    case 173:
        if (dbmode == 3)
        {
            inv_image(ci) = 355;
            inv_param2(ci) = 100;
        }
        if (dbmode == 15)
        {
            label_2170();
            return -1;
        }
        break;
    case 172:
        if (dbmode == 3)
        {
            inv_image(ci) = 163;
        }
        break;
    case 171:
        if (dbmode == 3)
        {
            inv_image(ci) = 163;
        }
        break;
    case 170:
        if (dbmode == 3)
        {
            inv_image(ci) = 162;
        }
        break;
    case 169:
        if (dbmode == 3)
        {
            inv_image(ci) = 161;
        }
        break;
    case 168:
        if (dbmode == 3)
        {
            inv_image(ci) = 160;
        }
        break;
    case 167:
        if (dbmode == 3)
        {
            inv_image(ci) = 159;
        }
        break;
    case 166:
        if (dbmode == 3)
        {
            inv_image(ci) = 158;
        }
        break;
    case 165:
        if (dbmode == 3)
        {
            inv_image(ci) = 157;
        }
        break;
    case 164:
        if (dbmode == 3)
        {
            inv_image(ci) = 156;
        }
        break;
    case 163:
        if (dbmode == 3)
        {
            inv_image(ci) = 155;
        }
        break;
    case 162:
        if (dbmode == 3)
        {
            inv_image(ci) = 154;
        }
        break;
    case 161:
        if (dbmode == 3)
        {
            inv_image(ci) = 153;
            inv_function(ci) = 1;
        }
        break;
    case 160:
        if (dbmode == 3)
        {
            inv_image(ci) = 152;
            inv_function(ci) = 4;
        }
        break;
    case 159:
        if (dbmode == 3)
        {
            inv_image(ci) = 151;
        }
        break;
    case 158:
        if (dbmode == 3)
        {
            inv_image(ci) = 150;
        }
        break;
    case 157:
        if (dbmode == 3)
        {
            inv_image(ci) = 149;
        }
        break;
    case 156:
        if (dbmode == 3)
        {
            inv_image(ci) = 148;
        }
        break;
    case 155:
        if (dbmode == 3)
        {
            inv_image(ci) = 147;
            inv_function(ci) = 15;
            inv_param1(ci) = 100;
        }
        break;
    case 154:
        if (dbmode == 3)
        {
            inv_image(ci) = 146;
            inv_function(ci) = 15;
            inv_param1(ci) = 100;
        }
        break;
    case 153:
        if (dbmode == 3)
        {
            inv_image(ci) = 145;
            inv_function(ci) = 15;
            inv_param1(ci) = 100;
        }
        break;
    case 152:
        if (dbmode == 3)
        {
            inv_image(ci) = 144;
        }
        break;
    case 151:
        if (dbmode == 3)
        {
            inv_image(ci) = 143;
        }
        break;
    case 150:
        if (dbmode == 3)
        {
            inv_image(ci) = 142;
        }
        break;
    case 149:
        if (dbmode == 3)
        {
            inv_image(ci) = 141;
        }
        break;
    case 148:
        if (dbmode == 3)
        {
            inv_image(ci) = 140;
        }
        break;
    case 147:
        if (dbmode == 3)
        {
            inv_image(ci) = 139;
        }
        break;
    case 146:
        if (dbmode == 3)
        {
            inv_image(ci) = 138;
        }
        break;
    case 145:
        if (dbmode == 3)
        {
            inv_image(ci) = 137;
        }
        break;
    case 144:
        if (dbmode == 3)
        {
            inv_image(ci) = 136;
        }
        break;
    case 143:
        if (dbmode == 3)
        {
            inv_image(ci) = 135;
        }
        break;
    case 142:
        if (dbmode == 3)
        {
            inv_image(ci) = 523;
            inv_function(ci) = 15;
            inv_param1(ci) = 200;
        }
        break;
    case 141:
        if (dbmode == 3)
        {
            inv_image(ci) = 133;
        }
        break;
    case 140:
        if (dbmode == 3)
        {
            inv_image(ci) = 132;
        }
        break;
    case 139:
        if (dbmode == 3)
        {
            inv_image(ci) = 526;
        }
        break;
    case 138:
        if (dbmode == 3)
        {
            inv_image(ci) = 525;
        }
        break;
    case 137:
        if (dbmode == 3)
        {
            inv_image(ci) = 129;
        }
        break;
    case 136:
        if (dbmode == 3)
        {
            inv_image(ci) = 128;
        }
        break;
    case 135:
        if (dbmode == 3)
        {
            inv_image(ci) = 127;
        }
        break;
    case 134:
        if (dbmode == 3)
        {
            inv_image(ci) = 126;
        }
        break;
    case 133:
        if (dbmode == 3)
        {
            inv_image(ci) = 125;
        }
        break;
    case 132:
        if (dbmode == 3)
        {
            inv_image(ci) = 124;
        }
        break;
    case 131:
        if (dbmode == 3)
        {
            inv_image(ci) = 123;
        }
        break;
    case 130:
        if (dbmode == 3)
        {
            inv_image(ci) = 122;
        }
        break;
    case 129:
        if (dbmode == 3)
        {
            inv_image(ci) = 121;
        }
        break;
    case 128:
        if (dbmode == 3)
        {
            inv_image(ci) = 120;
        }
        break;
    case 127:
        if (dbmode == 3)
        {
            inv_image(ci) = 119;
            inv_function(ci) = 2;
        }
        break;
    case 126:
        if (dbmode == 3)
        {
            inv_image(ci) = 118;
        }
        break;
    case 125:
        if (dbmode == 3)
        {
            inv_image(ci) = 471;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 14)
        {
            efid = 402;
            efp = 100;
            return -1;
        }
        break;
    case 124:
        if (dbmode == 3)
        {
            inv_image(ci) = 116;
        }
        break;
    case 123:
        if (dbmode == 3)
        {
            inv_image(ci) = 471;
            inv_count(ci) = 10 + rnd(10) - rnd(10);
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
            inv_image(ci) = 471;
            inv_count(ci) = 8 + rnd(8) - rnd(8);
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
            inv_image(ci) = 471;
            inv_count(ci) = 8 + rnd(8) - rnd(8);
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
            inv_image(ci) = 471;
            inv_count(ci) = 10 + rnd(10) - rnd(10);
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
            inv_image(ci) = 471;
            inv_count(ci) = 8 + rnd(8) - rnd(8);
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
            inv_image(ci) = 429;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 424;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 117:
        if (dbmode == 3)
        {
            inv_image(ci) = 109;
        }
        break;
    case 116:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 410;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 115:
        if (dbmode == 3)
        {
            inv_image(ci) = 381;
        }
        break;
    case 114:
        if (dbmode == 3)
        {
            inv_image(ci) = 106;
        }
        break;
    case 113:
        if (dbmode == 3)
        {
            inv_image(ci) = 105;
        }
        break;
    case 112:
        if (dbmode == 3)
        {
            inv_image(ci) = 104;
            inv_function(ci) = 15;
            inv_param1(ci) = 150;
        }
        break;
    case 111:
        if (dbmode == 3)
        {
            inv_image(ci) = 103;
        }
        break;
    case 110:
        if (dbmode == 3)
        {
            inv_image(ci) = 102;
        }
        break;
    case 109:
        if (dbmode == 3)
        {
            inv_image(ci) = 101;
            inv_param2(ci) = 100;
        }
        if (dbmode == 15)
        {
            label_2170();
            return -1;
        }
        break;
    case 108:
        if (dbmode == 3)
        {
            inv_image(ci) = 100;
        }
        break;
    case 107:
        if (dbmode == 3)
        {
            inv_image(ci) = 99;
        }
        break;
    case 106:
        if (dbmode == 3)
        {
            inv_image(ci) = 98;
        }
        break;
    case 105:
        if (dbmode == 3)
        {
            inv_image(ci) = 97;
        }
        break;
    case 104:
        if (dbmode == 3)
        {
            inv_image(ci) = 96;
        }
        break;
    case 103:
        if (dbmode == 3)
        {
            inv_image(ci) = 95;
        }
        break;
    case 102:
        if (dbmode == 3)
        {
            inv_image(ci) = 94;
            inv_function(ci) = 44;
        }
        break;
    case 101:
        if (dbmode == 3)
        {
            inv_image(ci) = 93;
            inv_function(ci) = 44;
        }
        break;
    case 100:
        if (dbmode == 3)
        {
            inv_image(ci) = 580;
        }
        break;
    case 99:
        if (dbmode == 3)
        {
            inv_image(ci) = 91;
        }
        break;
    case 98:
        if (dbmode == 3)
        {
            inv_image(ci) = 90;
        }
        break;
    case 97:
        if (dbmode == 3)
        {
            inv_image(ci) = 89;
        }
        break;
    case 96:
        if (dbmode == 3)
        {
            inv_image(ci) = 88;
        }
        break;
    case 95:
        if (dbmode == 3)
        {
            inv_image(ci) = 87;
        }
        break;
    case 94:
        if (dbmode == 3)
        {
            inv_image(ci) = 86;
        }
        break;
    case 93:
        if (dbmode == 3)
        {
            inv_image(ci) = 85;
        }
        break;
    case 92:
        if (dbmode == 3)
        {
            inv_image(ci) = 84;
            inv_function(ci) = 44;
        }
        break;
    case 91:
        if (dbmode == 3)
        {
            inv_image(ci) = 72;
        }
        break;
    case 90:
        if (dbmode == 3)
        {
            inv_image(ci) = 80;
        }
        break;
    case 89:
        if (dbmode == 3)
        {
            inv_image(ci) = 78;
        }
        break;
    case 88:
        if (dbmode == 3)
        {
            inv_skill(ci) = 183;
            inv_image(ci) = 76;
            inv_function(ci) = 17;
            inv_param1(ci) = 200;
        }
        break;
    case 87:
        if (dbmode == 3)
        {
            inv_image(ci) = 75;
        }
        break;
    case 86:
        if (dbmode == 3)
        {
            inv_image(ci) = 74;
        }
        break;
    case 85:
        if (dbmode == 3)
        {
            inv_image(ci) = 73;
        }
        break;
    case 84:
        if (dbmode == 3)
        {
            inv_image(ci) = 70;
        }
        break;
    case 83:
        if (dbmode == 3)
        {
            inv_image(ci) = 69;
        }
        break;
    case 82:
        if (dbmode == 3)
        {
            inv_image(ci) = 68;
        }
        break;
    case 81:
        if (dbmode == 3)
        {
            inv_image(ci) = 67;
            inv_function(ci) = 44;
        }
        break;
    case 80:
        if (dbmode == 3)
        {
            inv_image(ci) = 66;
            inv_param1(ci) = 100;
        }
        break;
    case 79:
        if (dbmode == 3)
        {
            inv_image(ci) = 234;
        }
        break;
    case 78:
        if (dbmode == 3)
        {
            inv_image(ci) = 235;
        }
        break;
    case 77:
        if (dbmode == 3)
        {
            inv_image(ci) = 237;
            inv_function(ci) = 44;
        }
        break;
    case 76:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 403;
            efp = 100;
            label_2169();
            return -1;
        }
        break;
    case 75:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 402;
            efp = 300;
            label_2169();
            return -1;
        }
        break;
    case 74:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 402;
            efp = 100;
            label_2169();
            return -1;
        }
        break;
    case 73:
        if (dbmode == 3)
        {
            inv_skill(ci) = 100;
            inv_image(ci) = 405;
            fixeditemenc(0) = 37;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 72:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 401;
            efp = 400;
            label_2169();
            return -1;
        }
        break;
    case 71:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 401;
            efp = 300;
            label_2169();
            return -1;
        }
        break;
    case 70:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 401;
            efp = 100;
            label_2169();
            return -1;
        }
        break;
    case 69:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 400;
            efp = 300;
            label_2169();
            return -1;
        }
        break;
    case 68:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 400;
            efp = 100;
            label_2169();
            return -1;
        }
        break;
    case 67:
        if (dbmode == 3)
        {
            inv_image(ci) = 398;
        }
        break;
    case 66:
        if (dbmode == 3)
        {
            inv_image(ci) = 423;
        }
        break;
    case 65:
        if (dbmode == 3)
        {
            inv_image(ci) = 422;
        }
        break;
    case 64:
        if (dbmode == 3)
        {
            inv_skill(ci) = 100;
            inv_image(ci) = 405;
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
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 63:
        if (dbmode == 3)
        {
            inv_skill(ci) = 107;
            inv_image(ci) = 421;
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
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 62:
        if (dbmode == 3)
        {
            inv_skill(ci) = 110;
            inv_image(ci) = 420;
        }
        break;
    case 61:
        if (dbmode == 3)
        {
            inv_skill(ci) = 108;
            inv_image(ci) = 412;
        }
        break;
    case 60:
        if (dbmode == 3)
        {
            inv_skill(ci) = 110;
            inv_image(ci) = 419;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 1;
        }
        break;
    case 59:
        if (dbmode == 3)
        {
            inv_skill(ci) = 168;
            inv_image(ci) = 411;
        }
        break;
    case 58:
        if (dbmode == 3)
        {
            inv_skill(ci) = 108;
            inv_image(ci) = 404;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 2;
        }
        break;
    case 57:
        if (dbmode == 3)
        {
            inv_skill(ci) = 100;
            inv_image(ci) = 501;
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
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 56:
        if (dbmode == 3)
        {
            inv_skill(ci) = 100;
            inv_image(ci) = 405;
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
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 55:
        if (dbmode == 3)
        {
            inv_image(ci) = 437;
        }
        break;
    case 54:
        if (dbmode == 3)
        {
            inv_image(ci) = 433;
        }
        break;
    case 53:
        if (dbmode == 3)
        {
            inv_image(ci) = 247;
        }
        break;
    case 52:
        if (dbmode == 3)
        {
            inv_image(ci) = 246;
        }
        break;
    case 51:
        if (dbmode == 3)
        {
            inv_image(ci) = 245;
        }
        break;
    case 50:
        if (dbmode == 3)
        {
            inv_image(ci) = 244;
        }
        break;
    case 49:
        if (dbmode == 3)
        {
            inv_image(ci) = 243;
        }
        break;
    case 48:
        if (dbmode == 3)
        {
            inv_image(ci) = 242;
        }
        break;
    case 47:
        if (dbmode == 3)
        {
            inv_image(ci) = 204;
        }
        break;
    case 46:
        if (dbmode == 3)
        {
            inv_image(ci) = 241;
        }
        break;
    case 45:
        if (dbmode == 3)
        {
            inv_image(ci) = 240;
        }
        break;
    case 44:
        if (dbmode == 3)
        {
            inv_image(ci) = 238;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 6 || cdata_god(0) == 5;
        }
        break;
    case 43:
        if (dbmode == 3)
        {
            inv_image(ci) = 239;
        }
        break;
    case 42:
        if (dbmode == 3)
        {
            inv_image(ci) = 213;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 6 || cdata_god(0) == 5;
        }
        break;
    case 41:
        if (dbmode == 3)
        {
            inv_image(ci) = 213;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 6 || cdata_god(0) == 5;
        }
        break;
    case 40:
        if (dbmode == 3)
        {
            inv_image(ci) = 212;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 6 || cdata_god(0) == 5;
        }
        break;
    case 39:
        if (dbmode == 3)
        {
            inv_image(ci) = 212;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 6 || cdata_god(0) == 5;
        }
        break;
    case 38:
        if (dbmode == 3)
        {
            inv_image(ci) = 33;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 6 || cdata_god(0) == 5;
        }
        break;
    case 37:
        if (dbmode == 3)
        {
            inv_image(ci) = 211;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 6 || cdata_god(0) == 5;
        }
        break;
    case 36:
        if (dbmode == 3)
        {
            inv_image(ci) = 211;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 6 || cdata_god(0) == 5;
        }
        break;
    case 35:
        if (dbmode == 3)
        {
            inv_image(ci) = 211;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 6 || cdata_god(0) == 5;
        }
        break;
    case 34:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 421;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 33:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 420;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 32:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 419;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 31:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 1102;
            efp = 300;
            label_2169();
            return -1;
        }
        break;
    case 30:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 1112;
            efp = 200;
            label_2169();
            return -1;
        }
        break;
    case 29:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 1110;
            efp = 200;
            label_2169();
            return -1;
        }
        break;
    case 28:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 1109;
            efp = 150;
            label_2169();
            return -1;
        }
        break;
    case 27:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 1111;
            efp = 200;
            label_2169();
            return -1;
        }
        break;
    case 26:
        if (dbmode == 3)
        {
            inv_image(ci) = 354;
        }
        if (dbmode == 15)
        {
            efid = 1130;
            label_2169();
            return -1;
        }
        break;
    case 25:
        if (dbmode == 3)
        {
            inv_image(ci) = 333;
            inv_param1(ci) = 2;
        }
        if (dbmode == 13)
        {
            inv_param1(ci) = 2;
            label_2164();
            return -1;
        }
        break;
    case 24:
        if (dbmode == 3)
        {
            inv_image(ci) = 333;
            inv_param1(ci) = 0;
        }
        if (dbmode == 13)
        {
            label_2164();
            return -1;
        }
        break;
    case 23:
        if (dbmode == 3)
        {
            inv_image(ci) = 333;
            inv_param1(ci) = 1;
        }
        if (dbmode == 13)
        {
            inv_param1(ci) = 1;
            label_2164();
            return -1;
        }
        break;
    case 22:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 412;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 21:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 411;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 20:
        if (dbmode == 3)
        {
            inv_image(ci) = 429;
            inv_count(ci) = 5 + rnd(5) - rnd(5);
            ibitmod(4, ci, 1);
        }
        if (dbmode == 13)
        {
            efid = 408;
            efp = 100;
            label_2163();
            return -1;
        }
        break;
    case 19:
        if (dbmode == 3)
        {
            inv_image(ci) = 471;
            inv_count(ci) = 12 + rnd(12) - rnd(12);
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
            inv_image(ci) = 471;
            inv_count(ci) = 8 + rnd(8) - rnd(8);
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
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 458;
            efp = 300;
            label_2171();
            return -1;
        }
        break;
    case 16:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 408;
            efp = 100;
            label_2171();
            return -1;
        }
        break;
    case 15:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 413;
            efp = 100;
            label_2171();
            return -1;
        }
        break;
    case 14:
        if (dbmode == 3)
        {
            inv_image(ci) = 470;
        }
        if (dbmode == 13)
        {
            efid = 411;
            efp = 100;
            label_2171();
            return -1;
        }
        break;
    case 13:
        if (dbmode == 3)
        {
            inv_image(ci) = 407;
        }
        break;
    case 12:
        if (dbmode == 3)
        {
            inv_image(ci) = 460;
        }
        break;
    case 11:
        if (dbmode == 3)
        {
            inv_image(ci) = 418;
        }
        break;
    case 10:
        if (dbmode == 3)
        {
            inv_image(ci) = 450;
        }
        break;
    case 9:
        if (dbmode == 3)
        {
            inv_image(ci) = 449;
        }
        break;
    case 8:
        if (dbmode == 3)
        {
            inv_image(ci) = 408;
        }
        break;
    case 7:
        if (dbmode == 3)
        {
            inv_image(ci) = 396;
        }
        break;
    case 6:
        if (dbmode == 3)
        {
            inv_image(ci) = 478;
            fixeditemenc(0) = 33;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
        }
        break;
    case 5:
        if (dbmode == 3)
        {
            inv_image(ci) = 477;
        }
        break;
    case 4:
        if (dbmode == 3)
        {
            inv_skill(ci) = 103;
            inv_image(ci) = 427;
        }
        break;
    case 3:
        if (dbmode == 3)
        {
            inv_skill(ci) = 102;
            inv_image(ci) = 499;
        }
        break;
    case 2:
        if (dbmode == 3)
        {
            inv_skill(ci) = 101;
            inv_image(ci) = 400;
        }
        break;
    case 1:
        if (dbmode == 3)
        {
            inv_skill(ci) = 100;
            inv_image(ci) = 405;
        }
        break;
    case 0:
        if (dbmode == 3)
        {
            inv_image(ci) = 33;
        }
        break;
    default: assert(0);
    }

    return 0;
}



} // namespace elona
