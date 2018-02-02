#include <unordered_map>
#include "elona.hpp"
#include "item_db.hpp"
#include "variables.hpp"



namespace elona
{


int label_1275()
{
    std::string infilterref;
    if (const auto info = the_item_db[dbid])
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

    switch (dbid)
    {
    case 792:
        if (dbmode == 3)
        {
            inv_id(ci) = 792;
            inv_image(ci) = 695;
            reftype = 57000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 8;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 791:
        if (dbmode == 3)
        {
            inv_skill(ci) = 100;
            inv_id(ci) = 791;
            inv_image(ci) = 697;
            reftype = 10000;
            reftypeminor = 10001;
            inv_number(ci) = 1;
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
            inv_id(ci) = 790;
            inv_image(ci) = 555;
            reftype = 59000;
            reftypeminor = 59500;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 15;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 789:
        if (dbmode == 3)
        {
            inv_id(ci) = 789;
            inv_image(ci) = 554;
            reftype = 59000;
            reftypeminor = 59500;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 15;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 788:
        if (dbmode == 3)
        {
            inv_skill(ci) = 108;
            inv_id(ci) = 788;
            inv_image(ci) = 402;
            reftype = 24000;
            reftypeminor = 24001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 2;
        }
        break;
    case 787:
        if (dbmode == 3)
        {
            inv_id(ci) = 787;
            inv_image(ci) = 552;
            reftype = 57000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 5;
            inv_param3(ci) = 720;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 786:
        if (dbmode == 3)
        {
            inv_id(ci) = 786;
            inv_image(ci) = 551;
            reftype = 57000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 4;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 785:
        if (dbmode == 3)
        {
            inv_id(ci) = 785;
            inv_image(ci) = 553;
            reftype = 57000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 1;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 784:
        if (dbmode == 3)
        {
            inv_id(ci) = 784;
            inv_image(ci) = 549;
            reftype = 72000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 783:
        if (dbmode == 3)
        {
            inv_id(ci) = 783;
            inv_image(ci) = 550;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 782;
            inv_image(ci) = 360;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 781:
        if (dbmode == 3)
        {
            inv_skill(ci) = 101;
            inv_id(ci) = 781;
            inv_image(ci) = 546;
            reftype = 10000;
            reftypeminor = 10003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 780:
        if (dbmode == 3)
        {
            inv_id(ci) = 780;
            inv_image(ci) = 545;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 779:
        if (dbmode == 3)
        {
            inv_id(ci) = 779;
            inv_image(ci) = 544;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 778:
        if (dbmode == 3)
        {
            inv_id(ci) = 778;
            inv_image(ci) = 543;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 44;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 777:
        if (dbmode == 3)
        {
            inv_id(ci) = 777;
            inv_image(ci) = 682;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 26;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv_param3(ci) = 240;
            inv_difficulty_of_identification(ci) = 0;
            fixlv = 6;
        }
        break;
    case 776:
        if (dbmode == 3)
        {
            inv_id(ci) = 776;
            inv_image(ci) = 681;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 26;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv_param3(ci) = 240;
            inv_difficulty_of_identification(ci) = 0;
            fixlv = 6;
        }
        break;
    case 775:
        if (dbmode == 3)
        {
            inv_id(ci) = 775;
            inv_image(ci) = 542;
            reftype = 57000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            ibitmod(5, ci, 1);
            inv_param2(ci) = 8;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 774:
        if (dbmode == 3)
        {
            inv_id(ci) = 774;
            inv_image(ci) = 683;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 773:
        if (dbmode == 3)
        {
            inv_id(ci) = 773;
            inv_image(ci) = 541;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 772:
        if (dbmode == 3)
        {
            inv_id(ci) = 772;
            inv_image(ci) = 540;
            reftype = 57000;
            reftypeminor = 57004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 2000;
            inv_param3(ci) = 32;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 771:
        if (dbmode == 3)
        {
            inv_id(ci) = 771;
            inv_image(ci) = 679;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 770;
            inv_image(ci) = 678;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 769;
            inv_image(ci) = 677;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 768:
        if (dbmode == 3)
        {
            inv_id(ci) = 768;
            inv_image(ci) = 676;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 767:
        if (dbmode == 3)
        {
            inv_id(ci) = 767;
            inv_image(ci) = 675;
            reftype = 60000;
            reftypeminor = 60004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 766:
        if (dbmode == 3)
        {
            inv_id(ci) = 766;
            inv_image(ci) = 684;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 765:
        if (dbmode == 3)
        {
            inv_id(ci) = 765;
            inv_image(ci) = 685;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 764:
        if (dbmode == 3)
        {
            inv_id(ci) = 764;
            inv_image(ci) = 674;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 763:
        if (dbmode == 3)
        {
            inv_id(ci) = 763;
            inv_image(ci) = 673;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 762:
        if (dbmode == 3)
        {
            inv_id(ci) = 762;
            inv_image(ci) = 672;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 761:
        if (dbmode == 3)
        {
            inv_skill(ci) = 183;
            inv_id(ci) = 761;
            inv_image(ci) = 76;
            reftype = 60000;
            reftypeminor = 60005;
            inv_number(ci) = 1;
            fixeditemenc(0) = 60;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
            inv_function(ci) = 17;
            ibitmod(5, ci, 1);
            inv_param1(ci) = 200;
            inv_difficulty_of_identification(ci) = 0;
            fixlv = 6;
        }
        break;
    case 760:
        if (dbmode == 3)
        {
            inv_id(ci) = 760;
            inv_image(ci) = 629;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 49;
            ibitmod(5, ci, 1);
            inv_param1(ci) = rnd(20000) + 1;
            inv_difficulty_of_identification(ci) = 0;
            fixlv = 6;
        }
        break;
    case 759:
        if (dbmode == 3)
        {
            inv_skill(ci) = 100;
            inv_id(ci) = 759;
            inv_image(ci) = 671;
            reftype = 10000;
            reftypeminor = 10002;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 758:
        if (dbmode == 3)
        {
            inv_skill(ci) = 110;
            inv_id(ci) = 758;
            inv_image(ci) = 419;
            reftype = 24000;
            reftypeminor = 24020;
            inv_number(ci) = 1;
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
            inv_id(ci) = 757;
            inv_image(ci) = 480;
            reftype = 12000;
            reftypeminor = 12001;
            inv_number(ci) = 1;
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
            inv_id(ci) = 756;
            inv_image(ci) = 670;
            reftype = 57000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 7;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 755:
        if (dbmode == 3)
        {
            inv_id(ci) = 755;
            inv_image(ci) = 669;
            reftype = 57000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 6;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 754:
        if (dbmode == 3)
        {
            inv_id(ci) = 754;
            inv_image(ci) = 668;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 753:
        if (dbmode == 3)
        {
            inv_id(ci) = 753;
            inv_image(ci) = 667;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 752:
        if (dbmode == 3)
        {
            inv_id(ci) = 752;
            inv_image(ci) = 666;
            reftype = 72000;
            reftypeminor = 99999;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 751:
        if (dbmode == 3)
        {
            inv_id(ci) = 751;
            inv_image(ci) = 664;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 750:
        if (dbmode == 3)
        {
            inv_id(ci) = 750;
            inv_image(ci) = 665;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 749:
        if (dbmode == 3)
        {
            inv_id(ci) = 749;
            inv_image(ci) = 686;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 48;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 748:
        if (dbmode == 3)
        {
            inv_id(ci) = 748;
            inv_image(ci) = 662;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 47;
            ibitmod(5, ci, 1);
            ibitmod(16, ci, 1);
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 747:
        if (dbmode == 3)
        {
            inv_id(ci) = 747;
            inv_image(ci) = 333;
            reftype = 55000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 1;
            inv_param2(ci) = rnd(4) + 1;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 746;
            inv_image(ci) = 657;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 30;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv_param1(ci) = 1132;
            inv_param2(ci) = 100;
            inv_param3(ci) = 24;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 745:
        if (dbmode == 3)
        {
            inv_id(ci) = 745;
            inv_image(ci) = 657;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 30;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv_param1(ci) = 1132;
            inv_param2(ci) = 100;
            inv_param3(ci) = 24;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 744:
        if (dbmode == 3)
        {
            inv_id(ci) = 744;
            inv_image(ci) = 657;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 30;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv_param1(ci) = 1132;
            inv_param2(ci) = 100;
            inv_param3(ci) = 24;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 743:
        if (dbmode == 3)
        {
            inv_id(ci) = 743;
            inv_image(ci) = 657;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 30;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv_param1(ci) = 1132;
            inv_param2(ci) = 100;
            inv_param3(ci) = 24;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 742:
        if (dbmode == 3)
        {
            inv_id(ci) = 742;
            inv_image(ci) = 308;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 741;
            inv_image(ci) = 501;
            reftype = 10000;
            reftypeminor = 10002;
            inv_number(ci) = 1;
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
            inv_id(ci) = 740;
            inv_image(ci) = 488;
            reftype = 34000;
            reftypeminor = 34001;
            inv_number(ci) = 1;
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
            inv_id(ci) = 739;
            inv_image(ci) = 425;
            reftype = 10000;
            reftypeminor = 10011;
            inv_number(ci) = 1;
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
            inv_id(ci) = 738;
            inv_image(ci) = 539;
            reftype = 57000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 6;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 737:
        if (dbmode == 3)
        {
            inv_id(ci) = 737;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 736;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 735;
            inv_image(ci) = 421;
            reftype = 10000;
            reftypeminor = 10011;
            inv_number(ci) = 1;
            fixeditemenc(0) = 80025;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 734:
        if (dbmode == 3)
        {
            inv_id(ci) = 734;
            inv_image(ci) = 220;
            reftype = 72000;
            reftypeminor = 99999;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 733:
        if (dbmode == 3)
        {
            inv_id(ci) = 733;
            inv_image(ci) = 563;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 45;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 732:
        if (dbmode == 3)
        {
            inv_id(ci) = 732;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 731;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 730;
            inv_image(ci) = 538;
            reftype = 77000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 729:
        if (dbmode == 3)
        {
            inv_id(ci) = 729;
            inv_image(ci) = 391;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 728:
        if (dbmode == 3)
        {
            inv_id(ci) = 728;
            inv_image(ci) = 474;
            reftype = 19000;
            reftypeminor = 19001;
            inv_number(ci) = 1;
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
            inv_id(ci) = 727;
            inv_image(ci) = 453;
            reftype = 14000;
            reftypeminor = 14003;
            inv_number(ci) = 1;
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
            inv_id(ci) = 726;
            inv_image(ci) = 393;
            reftype = 14000;
            reftypeminor = 14003;
            inv_number(ci) = 1;
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
            inv_id(ci) = 725;
            inv_image(ci) = 76;
            reftype = 24000;
            reftypeminor = 24030;
            inv_number(ci) = 1;
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
            inv_id(ci) = 724;
            inv_image(ci) = 538;
            reftype = 77000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 723:
        if (dbmode == 3)
        {
            inv_id(ci) = 723;
            inv_image(ci) = 486;
            reftype = 34000;
            reftypeminor = 34001;
            inv_number(ci) = 1;
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
            inv_id(ci) = 722;
            inv_image(ci) = 486;
            reftype = 34000;
            reftypeminor = 34001;
            inv_number(ci) = 1;
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
            inv_id(ci) = 721;
            inv_image(ci) = 687;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 43;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv_param3(ci) = 480;
            inv_difficulty_of_identification(ci) = 0;
            fixlv = 6;
        }
        break;
    case 720:
        if (dbmode == 3)
        {
            inv_id(ci) = 720;
            inv_image(ci) = 649;
            reftype = 60000;
            reftypeminor = 60004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 200;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 719:
        if (dbmode == 3)
        {
            inv_skill(ci) = 100;
            inv_id(ci) = 719;
            inv_image(ci) = 698;
            reftype = 10000;
            reftypeminor = 10001;
            inv_number(ci) = 1;
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
            inv_id(ci) = 718;
            inv_image(ci) = 630;
            reftype = 24000;
            reftypeminor = 24030;
            inv_number(ci) = 1;
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
            inv_id(ci) = 717;
            inv_image(ci) = 657;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 42;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 716:
        if (dbmode == 3)
        {
            inv_skill(ci) = 111;
            inv_id(ci) = 716;
            inv_image(ci) = 424;
            reftype = 24000;
            reftypeminor = 24030;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 500;
            fixlv = 6;
        }
        break;
    case 715:
        if (dbmode == 3)
        {
            inv_id(ci) = 715;
            inv_image(ci) = 657;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 41;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 714:
        if (dbmode == 3)
        {
            inv_skill(ci) = 111;
            inv_id(ci) = 714;
            inv_image(ci) = 537;
            reftype = 24000;
            reftypeminor = 24030;
            inv_number(ci) = 1;
            fixeditemenc(0) = 80024;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 713:
        if (dbmode == 3)
        {
            inv_skill(ci) = 111;
            inv_id(ci) = 713;
            inv_image(ci) = 536;
            reftype = 24000;
            reftypeminor = 24030;
            inv_number(ci) = 1;
            fixeditemenc(0) = 70061;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 712:
        if (dbmode == 3)
        {
            inv_id(ci) = 712;
            inv_image(ci) = 308;
            reftype = 53000;
            reftypeminor = 53100;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 711;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 710;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 709;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 708;
            inv_image(ci) = 429;
            reftype = 55000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 707;
            inv_image(ci) = 699;
            reftype = 60000;
            reftypeminor = 60005;
            inv_number(ci) = 1;
            fixeditemenc(0) = 49;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
            inv_function(ci) = 17;
            ibitmod(5, ci, 1);
            inv_param1(ci) = 180;
            inv_difficulty_of_identification(ci) = 0;
            fixlv = 6;
        }
        break;
    case 706:
        if (dbmode == 3)
        {
            inv_id(ci) = 706;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 705;
            inv_image(ci) = 486;
            reftype = 34000;
            reftypeminor = 34001;
            inv_number(ci) = 1;
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
            inv_id(ci) = 704;
            inv_image(ci) = 535;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 703;
            inv_image(ci) = 534;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 39;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 702:
        if (dbmode == 3)
        {
            inv_id(ci) = 702;
            inv_image(ci) = 301;
            reftype = 57000;
            reftypeminor = 57004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            ibitmod(5, ci, 1);
            inv_param2(ci) = 4;
            inv_difficulty_of_identification(ci) = 0;
            fixlv = 6;
        }
        break;
    case 701:
        if (dbmode == 3)
        {
            inv_id(ci) = 701;
            inv_image(ci) = 533;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 37;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 700:
        if (dbmode == 3)
        {
            inv_id(ci) = 700;
            inv_image(ci) = 532;
            reftype = 55000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 699;
            inv_image(ci) = 658;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 698:
        if (dbmode == 3)
        {
            inv_id(ci) = 698;
            inv_image(ci) = 365;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 697;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 696;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 695;
            inv_image(ci) = 399;
            reftype = 10000;
            reftypeminor = 10010;
            inv_number(ci) = 1;
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
            inv_id(ci) = 694;
            inv_image(ci) = 659;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 693:
        if (dbmode == 3)
        {
            inv_skill(ci) = 183;
            inv_id(ci) = 693;
            inv_image(ci) = 395;
            reftype = 60000;
            reftypeminor = 60005;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 17;
            inv_param1(ci) = 175;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 692:
        if (dbmode == 3)
        {
            inv_skill(ci) = 183;
            inv_id(ci) = 692;
            inv_image(ci) = 394;
            reftype = 60000;
            reftypeminor = 60005;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 17;
            inv_param1(ci) = 70;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 691:
        if (dbmode == 3)
        {
            inv_skill(ci) = 183;
            inv_id(ci) = 691;
            inv_image(ci) = 393;
            reftype = 60000;
            reftypeminor = 60005;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 17;
            inv_param1(ci) = 130;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 690:
        if (dbmode == 3)
        {
            inv_skill(ci) = 183;
            inv_id(ci) = 690;
            inv_image(ci) = 392;
            reftype = 60000;
            reftypeminor = 60005;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 17;
            inv_param1(ci) = 150;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 689:
        if (dbmode == 3)
        {
            inv_id(ci) = 689;
            inv_image(ci) = 688;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 36;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 688:
        if (dbmode == 3)
        {
            inv_id(ci) = 688;
            inv_image(ci) = 689;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 35;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 687:
        if (dbmode == 3)
        {
            inv_id(ci) = 687;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 686;
            inv_image(ci) = 690;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 34;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv_param3(ci) = 720;
            inv_difficulty_of_identification(ci) = 0;
            fixlv = 6;
        }
        break;
    case 685:
        if (dbmode == 3)
        {
            inv_id(ci) = 685;
            inv_image(ci) = 658;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 33;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 684:
        if (dbmode == 3)
        {
            inv_id(ci) = 684;
            inv_image(ci) = 691;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 32;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 683:
        if (dbmode == 3)
        {
            inv_id(ci) = 683;
            inv_image(ci) = 657;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 30;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv_param1(ci) = 1132;
            inv_param2(ci) = 100;
            inv_param3(ci) = 24;
            inv_difficulty_of_identification(ci) = 0;
            fixlv = 6;
        }
        break;
    case 682:
        if (dbmode == 3)
        {
            inv_id(ci) = 682;
            inv_image(ci) = 657;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 31;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv_param3(ci) = 72;
            inv_difficulty_of_identification(ci) = 0;
            fixlv = 6;
        }
        break;
    case 681:
        if (dbmode == 3)
        {
            inv_id(ci) = 681;
            inv_image(ci) = 657;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 30;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv_param1(ci) = 404;
            inv_param2(ci) = 400;
            inv_param3(ci) = 8;
            inv_difficulty_of_identification(ci) = 0;
            fixlv = 6;
        }
        break;
    case 680:
        if (dbmode == 3)
        {
            inv_id(ci) = 680;
            inv_image(ci) = 657;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 30;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv_param1(ci) = 446;
            inv_param2(ci) = 300;
            inv_param3(ci) = 12;
            inv_difficulty_of_identification(ci) = 0;
            fixlv = 6;
        }
        break;
    case 679:
        if (dbmode == 3)
        {
            inv_skill(ci) = 103;
            inv_id(ci) = 679;
            inv_image(ci) = 504;
            reftype = 10000;
            reftypeminor = 10005;
            inv_number(ci) = 1;
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
            inv_id(ci) = 678;
            inv_image(ci) = 400;
            reftype = 10000;
            reftypeminor = 10003;
            inv_number(ci) = 1;
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
            inv_id(ci) = 677;
            inv_image(ci) = 415;
            reftype = 10000;
            reftypeminor = 10007;
            inv_number(ci) = 1;
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
            inv_id(ci) = 676;
            inv_image(ci) = 425;
            reftype = 10000;
            reftypeminor = 10006;
            inv_number(ci) = 1;
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
            inv_id(ci) = 675;
            inv_image(ci) = 421;
            reftype = 10000;
            reftypeminor = 10011;
            inv_number(ci) = 1;
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
            inv_id(ci) = 674;
            inv_image(ci) = 514;
            reftype = 24000;
            reftypeminor = 24020;
            inv_number(ci) = 1;
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
            inv_id(ci) = 673;
            inv_image(ci) = 404;
            reftype = 24000;
            reftypeminor = 24001;
            inv_number(ci) = 1;
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
            inv_id(ci) = 672;
            inv_image(ci) = 656;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 29;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 0;
            fixlv = 6;
        }
        break;
    case 671:
        if (dbmode == 3)
        {
            inv_id(ci) = 671;
            inv_image(ci) = 632;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 28;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 0;
            fixlv = 6;
        }
        break;
    case 670:
        if (dbmode == 3)
        {
            inv_id(ci) = 670;
            inv_image(ci) = 132;
            reftype = 92000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 7;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 669:
        if (dbmode == 3)
        {
            inv_id(ci) = 669;
            inv_image(ci) = 92;
            reftype = 92000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 7;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 668:
        if (dbmode == 3)
        {
            inv_id(ci) = 668;
            inv_image(ci) = 333;
            reftype = 55000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 1;
            inv_param2(ci) = rnd(4) + 1;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 667;
            inv_image(ci) = 391;
            reftype = 57000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 7;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 666:
        if (dbmode == 3)
        {
            inv_id(ci) = 666;
            inv_image(ci) = 692;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 27;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv_param3(ci) = 120;
            inv_difficulty_of_identification(ci) = 0;
            fixlv = 6;
        }
        break;
    case 665:
        if (dbmode == 3)
        {
            inv_id(ci) = 665;
            inv_image(ci) = 680;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 26;
            ibitmod(5, ci, 1);
            ibitmod(7, ci, 1);
            inv_param3(ci) = 240;
            inv_difficulty_of_identification(ci) = 0;
            fixlv = 6;
        }
        break;
    case 664:
        if (dbmode == 3)
        {
            inv_id(ci) = 664;
            inv_image(ci) = 489;
            reftype = 32000;
            reftypeminor = 32001;
            inv_number(ci) = 1;
            fixeditemenc(0) = 10018;
            fixeditemenc(1) = 400 + rnd((rnd(1000) + 1));
            fixeditemenc(2) = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 663:
        if (dbmode == 3)
        {
            inv_id(ci) = 663;
            inv_image(ci) = 654;
            reftype = 64000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 0;
            fixlv = 6;
        }
        break;
    case 662:
        if (dbmode == 3)
        {
            inv_id(ci) = 662;
            inv_image(ci) = 189;
            reftype = 57000;
            reftypeminor = 57004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            ibitmod(5, ci, 1);
            inv_param2(ci) = 7;
            inv_difficulty_of_identification(ci) = 0;
            fixlv = 6;
        }
        break;
    case 661:
        if (dbmode == 3)
        {
            inv_id(ci) = 661;
            inv_image(ci) = 459;
            reftype = 18000;
            reftypeminor = 18002;
            inv_number(ci) = 1;
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
            inv_id(ci) = 660;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 659;
            inv_image(ci) = 653;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 658:
        if (dbmode == 3)
        {
            inv_id(ci) = 658;
            inv_image(ci) = 652;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 657:
        if (dbmode == 3)
        {
            inv_id(ci) = 657;
            inv_image(ci) = 651;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 656:
        if (dbmode == 3)
        {
            inv_id(ci) = 656;
            inv_image(ci) = 650;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 655:
        if (dbmode == 3)
        {
            inv_id(ci) = 655;
            inv_image(ci) = 168;
            reftype = 57000;
            reftypeminor = 57004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            ibitmod(5, ci, 1);
            inv_param2(ci) = 7;
            inv_difficulty_of_identification(ci) = 0;
            fixlv = 6;
        }
        break;
    case 654:
        if (dbmode == 3)
        {
            inv_id(ci) = 654;
            inv_image(ci) = 649;
            reftype = 60000;
            reftypeminor = 60004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 160;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 653:
        if (dbmode == 3)
        {
            inv_id(ci) = 653;
            inv_image(ci) = 648;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 652:
        if (dbmode == 3)
        {
            inv_id(ci) = 652;
            inv_image(ci) = 647;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 651:
        if (dbmode == 3)
        {
            inv_id(ci) = 651;
            inv_image(ci) = 646;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 650:
        if (dbmode == 3)
        {
            inv_id(ci) = 650;
            inv_image(ci) = 645;
            reftype = 60001;
            reftypeminor = 60001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 649;
            inv_image(ci) = 644;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 648:
        if (dbmode == 3)
        {
            inv_id(ci) = 648;
            inv_image(ci) = 643;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 44;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 647:
        if (dbmode == 3)
        {
            inv_id(ci) = 647;
            inv_image(ci) = 642;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 646:
        if (dbmode == 3)
        {
            inv_id(ci) = 646;
            inv_image(ci) = 641;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 645:
        if (dbmode == 3)
        {
            inv_id(ci) = 645;
            inv_image(ci) = 640;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 644:
        if (dbmode == 3)
        {
            inv_id(ci) = 644;
            inv_image(ci) = 639;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 643:
        if (dbmode == 3)
        {
            inv_id(ci) = 643;
            inv_image(ci) = 638;
            reftype = 59000;
            reftypeminor = 60004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 130;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 642:
        if (dbmode == 3)
        {
            inv_id(ci) = 642;
            inv_image(ci) = 637;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 641:
        if (dbmode == 3)
        {
            inv_id(ci) = 641;
            inv_image(ci) = 636;
            reftype = 72000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 0;
            fixlv = 6;
        }
        break;
    case 640:
        if (dbmode == 3)
        {
            inv_id(ci) = 640;
            inv_image(ci) = 635;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 25;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 639:
        if (dbmode == 3)
        {
            inv_id(ci) = 639;
            inv_image(ci) = 172;
            reftype = 57000;
            reftypeminor = 57004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            ibitmod(5, ci, 1);
            inv_param2(ci) = 7;
            inv_difficulty_of_identification(ci) = 0;
            fixlv = 6;
        }
        break;
    case 638:
        if (dbmode == 3)
        {
            inv_id(ci) = 638;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 637;
            inv_image(ci) = 633;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 0;
            fixlv = 6;
        }
        break;
    case 636:
        if (dbmode == 3)
        {
            inv_id(ci) = 636;
            inv_image(ci) = 634;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 635:
        if (dbmode == 3)
        {
            inv_id(ci) = 635;
            inv_image(ci) = 632;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 24;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 634:
        if (dbmode == 3)
        {
            inv_id(ci) = 634;
            inv_image(ci) = 631;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 23;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 633:
        if (dbmode == 3)
        {
            inv_skill(ci) = 111;
            inv_id(ci) = 633;
            inv_image(ci) = 630;
            reftype = 24000;
            reftypeminor = 24030;
            inv_number(ci) = 1;
            fixeditemenc(0) = 70054;
            fixeditemenc(1) = 800;
            fixeditemenc(2) = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 632:
        if (dbmode == 3)
        {
            inv_id(ci) = 632;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 631;
            inv_image(ci) = 566;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 630:
        if (dbmode == 3)
        {
            inv_id(ci) = 630;
            inv_image(ci) = 629;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 21;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 629:
        if (dbmode == 3)
        {
            inv_id(ci) = 629;
            inv_image(ci) = 628;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 20;
            inv_difficulty_of_identification(ci) = 0;
            inv_count(ci) = 4 + rnd(4) - rnd(4);
            ibitmod(4, ci, 1);
        }
        break;
    case 628:
        if (dbmode == 3)
        {
            inv_id(ci) = 628;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 627;
            inv_image(ci) = 480;
            reftype = 12000;
            reftypeminor = 12001;
            inv_number(ci) = 1;
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
            inv_id(ci) = 626;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 625;
            inv_image(ci) = 627;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 624:
        if (dbmode == 3)
        {
            inv_id(ci) = 624;
            inv_image(ci) = 429;
            reftype = 55000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 623;
            inv_image(ci) = 429;
            reftype = 55000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 622;
            inv_image(ci) = 165;
            reftype = 77000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 621:
        if (dbmode == 3)
        {
            inv_id(ci) = 621;
            inv_image(ci) = 252;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 620;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 619;
            inv_image(ci) = 310;
            reftype = 64000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 618:
        if (dbmode == 3)
        {
            inv_id(ci) = 618;
            inv_image(ci) = 310;
            reftype = 57000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 6000;
            inv_param3(ci) = 4;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 4;
        }
        break;
    case 617:
        if (dbmode == 3)
        {
            inv_id(ci) = 617;
            inv_image(ci) = 569;
            reftype = 64000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 616:
        if (dbmode == 3)
        {
            inv_id(ci) = 616;
            inv_image(ci) = 384;
            reftype = 72000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 615:
        if (dbmode == 3)
        {
            inv_id(ci) = 615;
            inv_image(ci) = 383;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 614:
        if (dbmode == 3)
        {
            inv_id(ci) = 614;
            inv_image(ci) = 568;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 613:
        if (dbmode == 3)
        {
            inv_id(ci) = 613;
            inv_image(ci) = 569;
            reftype = 60000;
            reftypeminor = 60004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 180;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 612:
        if (dbmode == 3)
        {
            inv_id(ci) = 612;
            inv_image(ci) = 382;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 611:
        if (dbmode == 3)
        {
            inv_id(ci) = 611;
            inv_image(ci) = 107;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 8;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 610:
        if (dbmode == 3)
        {
            inv_id(ci) = 610;
            inv_image(ci) = 380;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 609:
        if (dbmode == 3)
        {
            inv_id(ci) = 609;
            inv_image(ci) = 379;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 608:
        if (dbmode == 3)
        {
            inv_id(ci) = 608;
            inv_image(ci) = 378;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 607:
        if (dbmode == 3)
        {
            inv_id(ci) = 607;
            inv_image(ci) = 377;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 606:
        if (dbmode == 3)
        {
            inv_id(ci) = 606;
            inv_image(ci) = 376;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 15;
            inv_param1(ci) = 225;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 605:
        if (dbmode == 3)
        {
            inv_id(ci) = 605;
            inv_image(ci) = 375;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 604:
        if (dbmode == 3)
        {
            inv_id(ci) = 604;
            inv_image(ci) = 374;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 603:
        if (dbmode == 3)
        {
            inv_id(ci) = 603;
            inv_image(ci) = 373;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 44;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 602:
        if (dbmode == 3)
        {
            inv_id(ci) = 602;
            inv_image(ci) = 372;
            reftype = 60001;
            reftypeminor = 60001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 100;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 601;
            inv_image(ci) = 371;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 600:
        if (dbmode == 3)
        {
            inv_id(ci) = 600;
            inv_image(ci) = 370;
            reftype = 72000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 599:
        if (dbmode == 3)
        {
            inv_id(ci) = 599;
            inv_image(ci) = 570;
            reftype = 80000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 598:
        if (dbmode == 3)
        {
            inv_id(ci) = 598;
            inv_image(ci) = 134;
            reftype = 92000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 6;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 597:
        if (dbmode == 3)
        {
            inv_id(ci) = 597;
            inv_image(ci) = 570;
            reftype = 92000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 6;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 596:
        if (dbmode == 3)
        {
            inv_id(ci) = 596;
            inv_image(ci) = 369;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 595:
        if (dbmode == 3)
        {
            inv_id(ci) = 595;
            inv_image(ci) = 571;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 594:
        if (dbmode == 3)
        {
            inv_id(ci) = 594;
            inv_image(ci) = 572;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 593:
        if (dbmode == 3)
        {
            inv_id(ci) = 593;
            inv_image(ci) = 573;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 592:
        if (dbmode == 3)
        {
            inv_id(ci) = 592;
            inv_image(ci) = 368;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 591:
        if (dbmode == 3)
        {
            inv_id(ci) = 591;
            inv_image(ci) = 366;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 590:
        if (dbmode == 3)
        {
            inv_id(ci) = 590;
            inv_image(ci) = 367;
            reftype = 64000;
            reftypeminor = 99999;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 589:
        if (dbmode == 3)
        {
            inv_id(ci) = 589;
            inv_image(ci) = 574;
            reftype = 80000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 588:
        if (dbmode == 3)
        {
            inv_id(ci) = 588;
            inv_image(ci) = 575;
            reftype = 80000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 587:
        if (dbmode == 3)
        {
            inv_id(ci) = 587;
            inv_image(ci) = 365;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 14;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 586;
            inv_image(ci) = 576;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 585:
        if (dbmode == 3)
        {
            inv_id(ci) = 585;
            inv_image(ci) = 364;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 584:
        if (dbmode == 3)
        {
            inv_id(ci) = 584;
            inv_image(ci) = 353;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 583:
        if (dbmode == 3)
        {
            inv_id(ci) = 583;
            inv_image(ci) = 352;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 13;
            inv_param1(ci) = 100;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 582:
        if (dbmode == 3)
        {
            inv_id(ci) = 582;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 581;
            inv_image(ci) = 471;
            reftype = 56000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 580;
            inv_image(ci) = 236;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 579:
        if (dbmode == 3)
        {
            inv_id(ci) = 579;
            inv_image(ci) = 577;
            reftype = 72000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 578:
        if (dbmode == 3)
        {
            inv_id(ci) = 578;
            inv_image(ci) = 348;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 11;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 577:
        if (dbmode == 3)
        {
            inv_id(ci) = 577;
            inv_image(ci) = 223;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 576;
            inv_image(ci) = 516;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 10;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 575:
        if (dbmode == 3)
        {
            inv_id(ci) = 575;
            inv_image(ci) = 340;
            reftype = 64000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 574:
        if (dbmode == 3)
        {
            inv_id(ci) = 574;
            inv_image(ci) = 339;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 573;
            inv_image(ci) = 338;
            reftype = 57000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 8000;
            inv_param3(ci) = 240;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 572:
        if (dbmode == 3)
        {
            inv_id(ci) = 572;
            inv_image(ci) = 308;
            reftype = 53000;
            reftypeminor = 53100;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 571;
            inv_image(ci) = 337;
            reftype = 57000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 5;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 570:
        if (dbmode == 3)
        {
            inv_id(ci) = 570;
            inv_image(ci) = 471;
            reftype = 56000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 569;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 568;
            inv_image(ci) = 335;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
            inv_count(ci) = 12 + rnd(12) - rnd(12);
            ibitmod(4, ci, 1);
        }
        break;
    case 567:
        if (dbmode == 3)
        {
            inv_id(ci) = 567;
            inv_image(ci) = 335;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
            inv_count(ci) = 12 + rnd(12) - rnd(12);
            ibitmod(4, ci, 1);
        }
        break;
    case 566:
        if (dbmode == 3)
        {
            inv_id(ci) = 566;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 565;
            inv_image(ci) = 471;
            reftype = 56000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 564;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 563;
            inv_image(ci) = 334;
            reftype = 55000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 562;
            inv_image(ci) = 332;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 8;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 561:
        if (dbmode == 3)
        {
            inv_id(ci) = 561;
            inv_image(ci) = 197;
            reftype = 72000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 560:
        if (dbmode == 3)
        {
            inv_id(ci) = 560;
            inv_image(ci) = 331;
            reftype = 72000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 559:
        if (dbmode == 3)
        {
            inv_id(ci) = 559;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 558;
            inv_image(ci) = 489;
            reftype = 32000;
            reftypeminor = 32001;
            inv_number(ci) = 1;
            fixeditemenc(0) = 31;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 20057;
            fixeditemenc(3) = 100;
            fixeditemenc(4) = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 557:
        if (dbmode == 3)
        {
            inv_id(ci) = 557;
            inv_image(ci) = 422;
            reftype = 20000;
            reftypeminor = 20001;
            inv_number(ci) = 1;
            fixeditemenc(0) = 30;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 556:
        if (dbmode == 3)
        {
            inv_id(ci) = 556;
            inv_image(ci) = 460;
            reftype = 18000;
            reftypeminor = 18002;
            inv_number(ci) = 1;
            fixeditemenc(0) = 29;
            fixeditemenc(1) = 500;
            fixeditemenc(2) = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 555:
        if (dbmode == 3)
        {
            inv_id(ci) = 555;
            inv_image(ci) = 330;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 7;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 554:
        if (dbmode == 3)
        {
            inv_id(ci) = 554;
            inv_image(ci) = 323;
            reftype = 57000;
            reftypeminor = 58500;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 1;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 553:
        if (dbmode == 3)
        {
            inv_id(ci) = 553;
            inv_image(ci) = 323;
            reftype = 57000;
            reftypeminor = 58500;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 1;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 552:
        if (dbmode == 3)
        {
            inv_id(ci) = 552;
            inv_image(ci) = 326;
            reftype = 20000;
            reftypeminor = 20001;
            inv_number(ci) = 1;
            fixeditemenc(0) = 32;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 551:
        if (dbmode == 3)
        {
            inv_id(ci) = 551;
            inv_image(ci) = 471;
            reftype = 56000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 550;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 549;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 548;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 547;
            inv_image(ci) = 325;
            reftype = 72000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 546:
        if (dbmode == 3)
        {
            inv_id(ci) = 546;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 545;
            inv_image(ci) = 471;
            reftype = 56000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 544;
            inv_image(ci) = 516;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 6;
            inv_param1(ci) = discsetmc();
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 543:
        if (dbmode == 3)
        {
            inv_id(ci) = 543;
            inv_image(ci) = 308;
            reftype = 53000;
            reftypeminor = 53100;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 542;
            inv_image(ci) = 308;
            reftype = 53000;
            reftypeminor = 53100;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 541;
            inv_image(ci) = 134;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 540:
        if (dbmode == 3)
        {
            inv_id(ci) = 540;
            inv_image(ci) = 130;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 539:
        if (dbmode == 3)
        {
            inv_id(ci) = 539;
            inv_image(ci) = 578;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 538:
        if (dbmode == 3)
        {
            inv_id(ci) = 538;
            inv_image(ci) = 131;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 537:
        if (dbmode == 3)
        {
            inv_id(ci) = 537;
            inv_image(ci) = 92;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 536:
        if (dbmode == 3)
        {
            inv_id(ci) = 536;
            inv_image(ci) = 81;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 535:
        if (dbmode == 3)
        {
            inv_id(ci) = 535;
            inv_image(ci) = 83;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 534:
        if (dbmode == 3)
        {
            inv_id(ci) = 534;
            inv_image(ci) = 582;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 533:
        if (dbmode == 3)
        {
            inv_id(ci) = 533;
            inv_image(ci) = 581;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 532:
        if (dbmode == 3)
        {
            inv_id(ci) = 532;
            inv_image(ci) = 584;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 531:
        if (dbmode == 3)
        {
            inv_id(ci) = 531;
            inv_image(ci) = 583;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 530:
        if (dbmode == 3)
        {
            inv_id(ci) = 530;
            inv_image(ci) = 587;
            reftype = 80000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 529:
        if (dbmode == 3)
        {
            inv_id(ci) = 529;
            inv_image(ci) = 588;
            reftype = 80000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 528:
        if (dbmode == 3)
        {
            inv_id(ci) = 528;
            inv_image(ci) = 589;
            reftype = 80000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 527:
        if (dbmode == 3)
        {
            inv_id(ci) = 527;
            inv_image(ci) = 590;
            reftype = 80000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 526:
        if (dbmode == 3)
        {
            inv_id(ci) = 526;
            inv_image(ci) = 591;
            reftype = 80000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = rnd(5) + 2;
            inv_param2(ci) = isetfruit(rnd(length(isetfruit)));
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 525:
        if (dbmode == 3)
        {
            inv_id(ci) = 525;
            inv_image(ci) = 592;
            reftype = 80000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 524:
        if (dbmode == 3)
        {
            inv_id(ci) = 524;
            inv_image(ci) = 593;
            reftype = 80000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 523:
        if (dbmode == 3)
        {
            inv_id(ci) = 523;
            inv_image(ci) = 527;
            reftype = 80000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 522:
        if (dbmode == 3)
        {
            inv_id(ci) = 522;
            inv_image(ci) = 308;
            reftype = 53000;
            reftypeminor = 53100;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 1;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 521;
            inv_image(ci) = 308;
            reftype = 53000;
            reftypeminor = 53100;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 1;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 520;
            inv_image(ci) = 522;
            reftype = 20000;
            reftypeminor = 20001;
            inv_number(ci) = 1;
            fixeditemenc(0) = 32;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 519:
        if (dbmode == 3)
        {
            inv_id(ci) = 519;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 518;
            inv_image(ci) = 471;
            reftype = 56000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 517;
            inv_image(ci) = 471;
            reftype = 56000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 516;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 515;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 514;
            inv_image(ci) = 520;
            reftype = 24000;
            reftypeminor = 24021;
            inv_number(ci) = 1;
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
            inv_id(ci) = 513;
            inv_image(ci) = 521;
            reftype = 25000;
            reftypeminor = 25030;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 512:
        if (dbmode == 3)
        {
            inv_skill(ci) = 110;
            inv_id(ci) = 512;
            inv_image(ci) = 520;
            reftype = 24000;
            reftypeminor = 24021;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 1;
        }
        break;
    case 511:
        if (dbmode == 3)
        {
            inv_id(ci) = 511;
            inv_image(ci) = 308;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 100 + rnd(200);
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 510;
            inv_image(ci) = 253;
            reftype = 72000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 509:
        if (dbmode == 3)
        {
            inv_id(ci) = 509;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 508;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 507;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 506;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 505;
            inv_image(ci) = 429;
            reftype = 55000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            ibitmod(5, ci, 1);
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 504;
            inv_image(ci) = 528;
            reftype = 62000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 38;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 503:
        if (dbmode == 3)
        {
            inv_id(ci) = 503;
            inv_image(ci) = 531;
            reftype = 62000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 502:
        if (dbmode == 3)
        {
            inv_id(ci) = 502;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 501;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 500;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 499;
            inv_image(ci) = 519;
            reftype = 57000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 7;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 498:
        if (dbmode == 3)
        {
            inv_id(ci) = 498;
            inv_image(ci) = 518;
            reftype = 57000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 6;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 497:
        if (dbmode == 3)
        {
            inv_id(ci) = 497;
            inv_image(ci) = 517;
            reftype = 57000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 5;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 496:
        if (dbmode == 3)
        {
            inv_skill(ci) = 110;
            inv_id(ci) = 496;
            inv_image(ci) = 514;
            reftype = 24000;
            reftypeminor = 24020;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 1;
        }
        break;
    case 495:
        if (dbmode == 3)
        {
            inv_id(ci) = 495;
            inv_image(ci) = 516;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 1;
        }
        break;
    case 494:
        if (dbmode == 3)
        {
            inv_id(ci) = 494;
            inv_image(ci) = 515;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 1;
        }
        break;
    case 493:
        if (dbmode == 3)
        {
            inv_id(ci) = 493;
            inv_image(ci) = 513;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 492:
        if (dbmode == 3)
        {
            inv_id(ci) = 492;
            inv_image(ci) = 512;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 1;
        }
        break;
    case 491:
        if (dbmode == 3)
        {
            inv_id(ci) = 491;
            inv_image(ci) = 511;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 1;
        }
        break;
    case 490:
        if (dbmode == 3)
        {
            inv_id(ci) = 490;
            inv_image(ci) = 510;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 1;
        }
        break;
    case 489:
        if (dbmode == 3)
        {
            inv_id(ci) = 489;
            inv_image(ci) = 509;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 1;
        }
        break;
    case 488:
        if (dbmode == 3)
        {
            inv_id(ci) = 488;
            inv_image(ci) = 506;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 9;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 1;
        }
        break;
    case 487:
        if (dbmode == 3)
        {
            inv_id(ci) = 487;
            inv_image(ci) = 508;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 1;
        }
        break;
    case 486:
        if (dbmode == 3)
        {
            inv_id(ci) = 486;
            inv_image(ci) = 507;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 1;
        }
        break;
    case 485:
        if (dbmode == 3)
        {
            inv_id(ci) = 485;
            inv_image(ci) = 471;
            reftype = 56000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 484;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 483;
            inv_image(ci) = 412;
            reftype = 25000;
            reftypeminor = 25002;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 482:
        if (dbmode == 3)
        {
            inv_skill(ci) = 109;
            inv_id(ci) = 482;
            inv_image(ci) = 498;
            reftype = 24000;
            reftypeminor = 24003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 2;
        }
        break;
    case 481:
        if (dbmode == 3)
        {
            inv_id(ci) = 481;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 480;
            inv_image(ci) = 471;
            reftype = 56000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 479;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 478;
            inv_image(ci) = 493;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 5;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 477:
        if (dbmode == 3)
        {
            inv_id(ci) = 477;
            inv_image(ci) = 489;
            reftype = 32000;
            reftypeminor = 32001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 476:
        if (dbmode == 3)
        {
            inv_id(ci) = 476;
            inv_image(ci) = 490;
            reftype = 32000;
            reftypeminor = 32001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 475:
        if (dbmode == 3)
        {
            inv_id(ci) = 475;
            inv_image(ci) = 491;
            reftype = 32000;
            reftypeminor = 32001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 474:
        if (dbmode == 3)
        {
            inv_id(ci) = 474;
            inv_image(ci) = 492;
            reftype = 32000;
            reftypeminor = 32001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 473:
        if (dbmode == 3)
        {
            inv_id(ci) = 473;
            inv_image(ci) = 483;
            reftype = 34000;
            reftypeminor = 34001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 472:
        if (dbmode == 3)
        {
            inv_id(ci) = 472;
            inv_image(ci) = 484;
            reftype = 34000;
            reftypeminor = 34001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 471:
        if (dbmode == 3)
        {
            inv_id(ci) = 471;
            inv_image(ci) = 485;
            reftype = 34000;
            reftypeminor = 34001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 470:
        if (dbmode == 3)
        {
            inv_id(ci) = 470;
            inv_image(ci) = 486;
            reftype = 34000;
            reftypeminor = 34001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 469:
        if (dbmode == 3)
        {
            inv_id(ci) = 469;
            inv_image(ci) = 487;
            reftype = 34000;
            reftypeminor = 34001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 468:
        if (dbmode == 3)
        {
            inv_id(ci) = 468;
            inv_image(ci) = 488;
            reftype = 34000;
            reftypeminor = 34001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 467:
        if (dbmode == 3)
        {
            inv_id(ci) = 467;
            inv_image(ci) = 482;
            reftype = 12000;
            reftypeminor = 12001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 466:
        if (dbmode == 3)
        {
            inv_id(ci) = 466;
            inv_image(ci) = 479;
            reftype = 12000;
            reftypeminor = 12001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 465:
        if (dbmode == 3)
        {
            inv_id(ci) = 465;
            inv_image(ci) = 480;
            reftype = 12000;
            reftypeminor = 12001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 464:
        if (dbmode == 3)
        {
            inv_id(ci) = 464;
            inv_image(ci) = 481;
            reftype = 12000;
            reftypeminor = 12001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 463:
        if (dbmode == 3)
        {
            inv_id(ci) = 463;
            inv_image(ci) = 413;
            reftype = 12000;
            reftypeminor = 12002;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 462:
        if (dbmode == 3)
        {
            inv_id(ci) = 462;
            inv_image(ci) = 476;
            reftype = 20000;
            reftypeminor = 20001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 461:
        if (dbmode == 3)
        {
            inv_id(ci) = 461;
            inv_image(ci) = 475;
            reftype = 20000;
            reftypeminor = 20001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 460:
        if (dbmode == 3)
        {
            inv_id(ci) = 460;
            inv_image(ci) = 474;
            reftype = 19000;
            reftypeminor = 19001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 459:
        if (dbmode == 3)
        {
            inv_id(ci) = 459;
            inv_image(ci) = 474;
            reftype = 19000;
            reftypeminor = 19001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 458:
        if (dbmode == 3)
        {
            inv_id(ci) = 458;
            inv_image(ci) = 461;
            reftype = 18000;
            reftypeminor = 18001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 457:
        if (dbmode == 3)
        {
            inv_id(ci) = 457;
            inv_image(ci) = 459;
            reftype = 18000;
            reftypeminor = 18002;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 456:
        if (dbmode == 3)
        {
            inv_id(ci) = 456;
            inv_image(ci) = 473;
            reftype = 18000;
            reftypeminor = 18002;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 455:
        if (dbmode == 3)
        {
            inv_id(ci) = 455;
            inv_image(ci) = 473;
            reftype = 18000;
            reftypeminor = 18002;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 454:
        if (dbmode == 3)
        {
            inv_skill(ci) = 168;
            inv_id(ci) = 454;
            inv_image(ci) = 458;
            reftype = 14000;
            reftypeminor = 14003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 453:
        if (dbmode == 3)
        {
            inv_skill(ci) = 168;
            inv_id(ci) = 453;
            inv_image(ci) = 457;
            reftype = 14000;
            reftypeminor = 14003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 452:
        if (dbmode == 3)
        {
            inv_skill(ci) = 168;
            inv_id(ci) = 452;
            inv_image(ci) = 456;
            reftype = 14000;
            reftypeminor = 14003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 451:
        if (dbmode == 3)
        {
            inv_skill(ci) = 168;
            inv_id(ci) = 451;
            inv_image(ci) = 455;
            reftype = 14000;
            reftypeminor = 14003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 450:
        if (dbmode == 3)
        {
            inv_skill(ci) = 168;
            inv_id(ci) = 450;
            inv_image(ci) = 454;
            reftype = 14000;
            reftypeminor = 14003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 449:
        if (dbmode == 3)
        {
            inv_skill(ci) = 168;
            inv_id(ci) = 449;
            inv_image(ci) = 453;
            reftype = 14000;
            reftypeminor = 14003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 448:
        if (dbmode == 3)
        {
            inv_id(ci) = 448;
            inv_image(ci) = 452;
            reftype = 22000;
            reftypeminor = 22001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 447:
        if (dbmode == 3)
        {
            inv_id(ci) = 447;
            inv_image(ci) = 451;
            reftype = 22000;
            reftypeminor = 22003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 446:
        if (dbmode == 3)
        {
            inv_id(ci) = 446;
            inv_image(ci) = 414;
            reftype = 22000;
            reftypeminor = 22001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 445:
        if (dbmode == 3)
        {
            inv_id(ci) = 445;
            inv_image(ci) = 448;
            reftype = 22000;
            reftypeminor = 22003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 444:
        if (dbmode == 3)
        {
            inv_id(ci) = 444;
            inv_image(ci) = 447;
            reftype = 16000;
            reftypeminor = 16003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 443:
        if (dbmode == 3)
        {
            inv_id(ci) = 443;
            inv_image(ci) = 446;
            reftype = 16000;
            reftypeminor = 16003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 442:
        if (dbmode == 3)
        {
            inv_id(ci) = 442;
            inv_image(ci) = 445;
            reftype = 16000;
            reftypeminor = 16003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 441:
        if (dbmode == 3)
        {
            inv_id(ci) = 441;
            inv_image(ci) = 444;
            reftype = 16000;
            reftypeminor = 16003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 440:
        if (dbmode == 3)
        {
            inv_id(ci) = 440;
            inv_image(ci) = 443;
            reftype = 16000;
            reftypeminor = 16003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 439:
        if (dbmode == 3)
        {
            inv_id(ci) = 439;
            inv_image(ci) = 442;
            reftype = 16000;
            reftypeminor = 16001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 438:
        if (dbmode == 3)
        {
            inv_id(ci) = 438;
            inv_image(ci) = 441;
            reftype = 16000;
            reftypeminor = 16001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 437:
        if (dbmode == 3)
        {
            inv_id(ci) = 437;
            inv_image(ci) = 440;
            reftype = 16000;
            reftypeminor = 16001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 436:
        if (dbmode == 3)
        {
            inv_id(ci) = 436;
            inv_image(ci) = 410;
            reftype = 16000;
            reftypeminor = 16001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 435:
        if (dbmode == 3)
        {
            inv_id(ci) = 435;
            inv_image(ci) = 409;
            reftype = 16000;
            reftypeminor = 16001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 434:
        if (dbmode == 3)
        {
            inv_id(ci) = 434;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 433;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 432;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 431;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 430;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 429;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 428;
            inv_image(ci) = 324;
            reftype = 59000;
            reftypeminor = 60004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 427:
        if (dbmode == 3)
        {
            inv_id(ci) = 427;
            inv_image(ci) = 170;
            reftype = 57000;
            reftypeminor = 58005;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 7;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 426:
        if (dbmode == 3)
        {
            inv_id(ci) = 426;
            inv_image(ci) = 170;
            reftype = 57000;
            reftypeminor = 58005;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 3;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 425:
        if (dbmode == 3)
        {
            inv_id(ci) = 425;
            inv_image(ci) = 170;
            reftype = 57000;
            reftypeminor = 58005;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 6;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 424:
        if (dbmode == 3)
        {
            inv_id(ci) = 424;
            inv_image(ci) = 170;
            reftype = 57000;
            reftypeminor = 58005;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 3;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 423:
        if (dbmode == 3)
        {
            inv_id(ci) = 423;
            inv_image(ci) = 170;
            reftype = 57000;
            reftypeminor = 58005;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 4;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 422:
        if (dbmode == 3)
        {
            inv_id(ci) = 422;
            inv_image(ci) = 170;
            reftype = 57000;
            reftypeminor = 58005;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 1;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 421:
        if (dbmode == 3)
        {
            inv_id(ci) = 421;
            inv_image(ci) = 323;
            reftype = 57000;
            reftypeminor = 58500;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 1;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 420:
        if (dbmode == 3)
        {
            inv_id(ci) = 420;
            inv_image(ci) = 323;
            reftype = 57000;
            reftypeminor = 58500;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 1;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 419:
        if (dbmode == 3)
        {
            inv_id(ci) = 419;
            inv_image(ci) = 323;
            reftype = 57000;
            reftypeminor = 58500;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 1;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 418:
        if (dbmode == 3)
        {
            inv_id(ci) = 418;
            inv_image(ci) = 323;
            reftype = 57000;
            reftypeminor = 58500;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 1;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 417:
        if (dbmode == 3)
        {
            inv_id(ci) = 417;
            inv_image(ci) = 323;
            reftype = 57000;
            reftypeminor = 58500;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 1;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 416:
        if (dbmode == 3)
        {
            inv_id(ci) = 416;
            inv_image(ci) = 322;
            reftype = 72000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 415:
        if (dbmode == 3)
        {
            inv_id(ci) = 415;
            inv_image(ci) = 322;
            reftype = 72000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 414:
        if (dbmode == 3)
        {
            inv_id(ci) = 414;
            inv_image(ci) = 321;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 413:
        if (dbmode == 3)
        {
            inv_id(ci) = 413;
            inv_image(ci) = 320;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 412:
        if (dbmode == 3)
        {
            inv_id(ci) = 412;
            inv_image(ci) = 471;
            reftype = 56000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 411;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 410;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 409;
            inv_image(ci) = 251;
            reftype = 92000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 5;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 408:
        if (dbmode == 3)
        {
            inv_id(ci) = 408;
            inv_image(ci) = 68;
            reftype = 92000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 1;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 407:
        if (dbmode == 3)
        {
            inv_id(ci) = 407;
            inv_image(ci) = 208;
            reftype = 92000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 2;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 406:
        if (dbmode == 3)
        {
            inv_id(ci) = 406;
            inv_image(ci) = 316;
            reftype = 92000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 405:
        if (dbmode == 3)
        {
            inv_id(ci) = 405;
            inv_image(ci) = 161;
            reftype = 92000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 3;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 404:
        if (dbmode == 3)
        {
            inv_id(ci) = 404;
            inv_image(ci) = 312;
            reftype = 92000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 403:
        if (dbmode == 3)
        {
            inv_id(ci) = 403;
            inv_image(ci) = 269;
            reftype = 92000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 3;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 402:
        if (dbmode == 3)
        {
            inv_id(ci) = 402;
            inv_image(ci) = 202;
            reftype = 92000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 5;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 401:
        if (dbmode == 3)
        {
            inv_id(ci) = 401;
            inv_image(ci) = 292;
            reftype = 92000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 4;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 400:
        if (dbmode == 3)
        {
            inv_id(ci) = 400;
            inv_image(ci) = 72;
            reftype = 92000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 2;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 399:
        if (dbmode == 3)
        {
            inv_id(ci) = 399;
            inv_image(ci) = 67;
            reftype = 92000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 1;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 398:
        if (dbmode == 3)
        {
            inv_id(ci) = 398;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 397;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 396;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 395;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 394;
            inv_image(ci) = 438;
            reftype = 72000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 393:
        if (dbmode == 3)
        {
            inv_id(ci) = 393;
            inv_image(ci) = 319;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 3;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 392:
        if (dbmode == 3)
        {
            inv_id(ci) = 392;
            inv_image(ci) = 223;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 391;
            inv_image(ci) = 471;
            reftype = 56000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 390;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 389;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 388;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 387;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 386;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 385;
            inv_image(ci) = 471;
            reftype = 56000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 384;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 383;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 382;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 381;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 380;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 379;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 378;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 377;
            inv_image(ci) = 471;
            reftype = 56000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 376;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 375;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 374;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 373;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 372;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 371;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 370;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 369;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 368;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 367;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 366;
            inv_image(ci) = 471;
            reftype = 56000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 365;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 364;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 363;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 362;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 361;
            inv_image(ci) = 253;
            reftype = 72000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 360:
        if (dbmode == 3)
        {
            inv_id(ci) = 360;
            inv_image(ci) = 407;
            reftype = 32000;
            reftypeminor = 32001;
            inv_number(ci) = 1;
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
            inv_id(ci) = 359;
            inv_image(ci) = 426;
            reftype = 10000;
            reftypeminor = 10007;
            inv_number(ci) = 1;
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
            inv_id(ci) = 358;
            inv_image(ci) = 425;
            reftype = 10000;
            reftypeminor = 10006;
            inv_number(ci) = 1;
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
            inv_id(ci) = 357;
            inv_image(ci) = 407;
            reftype = 32000;
            reftypeminor = 32001;
            inv_number(ci) = 1;
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
            inv_id(ci) = 356;
            inv_image(ci) = 427;
            reftype = 10000;
            reftypeminor = 10004;
            inv_number(ci) = 1;
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
            inv_id(ci) = 355;
            inv_image(ci) = 414;
            reftype = 22000;
            reftypeminor = 22003;
            inv_number(ci) = 1;
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
            inv_id(ci) = 354;
            inv_image(ci) = 318;
            reftype = 57000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 6000;
            inv_param3(ci) = 4;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 4;
        }
        break;
    case 353:
        if (dbmode == 3)
        {
            inv_id(ci) = 353;
            inv_image(ci) = 317;
            reftype = 57000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 6000;
            inv_param3(ci) = 4;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 4;
        }
        break;
    case 352:
        if (dbmode == 3)
        {
            inv_id(ci) = 352;
            inv_image(ci) = 316;
            reftype = 57000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 6000;
            inv_param3(ci) = 4;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 4;
        }
        break;
    case 351:
        if (dbmode == 3)
        {
            inv_id(ci) = 351;
            inv_image(ci) = 315;
            reftype = 57000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 6000;
            inv_param3(ci) = 4;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 4;
        }
        break;
    case 350:
        if (dbmode == 3)
        {
            inv_id(ci) = 350;
            inv_image(ci) = 314;
            reftype = 57000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 6000;
            inv_param3(ci) = 4;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 4;
        }
        break;
    case 349:
        if (dbmode == 3)
        {
            inv_id(ci) = 349;
            inv_image(ci) = 313;
            reftype = 57000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 6000;
            inv_param3(ci) = 4;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 4;
        }
        break;
    case 348:
        if (dbmode == 3)
        {
            inv_id(ci) = 348;
            inv_image(ci) = 312;
            reftype = 57000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 6000;
            inv_param3(ci) = 4;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 4;
        }
        break;
    case 347:
        if (dbmode == 3)
        {
            inv_id(ci) = 347;
            inv_image(ci) = 311;
            reftype = 57000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 6000;
            inv_param3(ci) = 4;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 4;
        }
        break;
    case 346:
        if (dbmode == 3)
        {
            inv_id(ci) = 346;
            inv_image(ci) = 310;
            reftype = 57000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 6000;
            inv_param3(ci) = 4;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 4;
        }
        break;
    case 345:
        if (dbmode == 3)
        {
            inv_id(ci) = 345;
            inv_image(ci) = 309;
            reftype = 57000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 6000;
            inv_param3(ci) = 4;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 4;
        }
        break;
    case 344:
        if (dbmode == 3)
        {
            inv_id(ci) = 344;
            inv_image(ci) = 308;
            reftype = 53000;
            reftypeminor = 53100;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 1;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 343;
            inv_image(ci) = 307;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 22;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 342:
        if (dbmode == 3)
        {
            inv_id(ci) = 342;
            inv_image(ci) = 306;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 16;
            inv_param1(ci) = 60;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 341:
        if (dbmode == 3)
        {
            inv_id(ci) = 341;
            inv_image(ci) = 305;
            reftype = 62000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 340:
        if (dbmode == 3)
        {
            inv_id(ci) = 340;
            inv_image(ci) = 304;
            reftype = 62000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 339:
        if (dbmode == 3)
        {
            inv_id(ci) = 339;
            inv_image(ci) = 303;
            reftype = 62000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 338:
        if (dbmode == 3)
        {
            inv_id(ci) = 338;
            inv_image(ci) = 302;
            reftype = 62000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 337:
        if (dbmode == 3)
        {
            inv_id(ci) = 337;
            inv_image(ci) = 301;
            reftype = 62000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 336:
        if (dbmode == 3)
        {
            inv_id(ci) = 336;
            inv_image(ci) = 300;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 335:
        if (dbmode == 3)
        {
            inv_id(ci) = 335;
            inv_image(ci) = 299;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 334:
        if (dbmode == 3)
        {
            inv_id(ci) = 334;
            inv_image(ci) = 579;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 44;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 333:
        if (dbmode == 3)
        {
            inv_id(ci) = 333;
            inv_image(ci) = 297;
            reftype = 91000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 3;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 332:
        if (dbmode == 3)
        {
            inv_id(ci) = 332;
            inv_image(ci) = 296;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 331:
        if (dbmode == 3)
        {
            inv_id(ci) = 331;
            inv_image(ci) = 295;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 330:
        if (dbmode == 3)
        {
            inv_id(ci) = 330;
            inv_image(ci) = 294;
            reftype = 64000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 44;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 329:
        if (dbmode == 3)
        {
            inv_id(ci) = 329;
            inv_image(ci) = 293;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 328:
        if (dbmode == 3)
        {
            inv_id(ci) = 328;
            inv_image(ci) = 292;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 17;
            inv_param1(ci) = 150;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 327:
        if (dbmode == 3)
        {
            inv_id(ci) = 327;
            inv_image(ci) = 291;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 44;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 326:
        if (dbmode == 3)
        {
            inv_id(ci) = 326;
            inv_image(ci) = 290;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 325:
        if (dbmode == 3)
        {
            inv_id(ci) = 325;
            inv_image(ci) = 289;
            reftype = 60000;
            reftypeminor = 60004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 130;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 324:
        if (dbmode == 3)
        {
            inv_id(ci) = 324;
            inv_image(ci) = 288;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 323:
        if (dbmode == 3)
        {
            inv_id(ci) = 323;
            inv_image(ci) = 586;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 322:
        if (dbmode == 3)
        {
            inv_id(ci) = 322;
            inv_image(ci) = 286;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 19;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 321:
        if (dbmode == 3)
        {
            inv_id(ci) = 321;
            inv_image(ci) = 285;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 320:
        if (dbmode == 3)
        {
            inv_id(ci) = 320;
            inv_image(ci) = 284;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 319:
        if (dbmode == 3)
        {
            inv_id(ci) = 319;
            inv_image(ci) = 283;
            reftype = 60000;
            reftypeminor = 60004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 318:
        if (dbmode == 3)
        {
            inv_id(ci) = 318;
            inv_image(ci) = 282;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 317:
        if (dbmode == 3)
        {
            inv_id(ci) = 317;
            inv_image(ci) = 281;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 316:
        if (dbmode == 3)
        {
            inv_id(ci) = 316;
            inv_image(ci) = 280;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 315:
        if (dbmode == 3)
        {
            inv_id(ci) = 315;
            inv_image(ci) = 279;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 314:
        if (dbmode == 3)
        {
            inv_id(ci) = 314;
            inv_image(ci) = 278;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 313:
        if (dbmode == 3)
        {
            inv_id(ci) = 313;
            inv_image(ci) = 277;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 312:
        if (dbmode == 3)
        {
            inv_id(ci) = 312;
            inv_image(ci) = 276;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 311:
        if (dbmode == 3)
        {
            inv_id(ci) = 311;
            inv_image(ci) = 275;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 310:
        if (dbmode == 3)
        {
            inv_id(ci) = 310;
            inv_image(ci) = 274;
            reftype = 60000;
            reftypeminor = 60004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 130;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 309:
        if (dbmode == 3)
        {
            inv_id(ci) = 309;
            inv_image(ci) = 273;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 19;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 308:
        if (dbmode == 3)
        {
            inv_id(ci) = 308;
            inv_image(ci) = 272;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 307:
        if (dbmode == 3)
        {
            inv_id(ci) = 307;
            inv_image(ci) = 271;
            reftype = 60000;
            reftypeminor = 60004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 130;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 306:
        if (dbmode == 3)
        {
            inv_id(ci) = 306;
            inv_image(ci) = 270;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 15;
            inv_param1(ci) = 200;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 305:
        if (dbmode == 3)
        {
            inv_id(ci) = 305;
            inv_image(ci) = 269;
            reftype = 60000;
            reftypeminor = 60004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 130;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 304:
        if (dbmode == 3)
        {
            inv_id(ci) = 304;
            inv_image(ci) = 268;
            reftype = 60000;
            reftypeminor = 60004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 100;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 303:
        if (dbmode == 3)
        {
            inv_id(ci) = 303;
            inv_image(ci) = 267;
            reftype = 60000;
            reftypeminor = 60004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 120;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 302:
        if (dbmode == 3)
        {
            inv_id(ci) = 302;
            inv_image(ci) = 266;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 301:
        if (dbmode == 3)
        {
            inv_id(ci) = 301;
            inv_image(ci) = 265;
            reftype = 64000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 300:
        if (dbmode == 3)
        {
            inv_id(ci) = 300;
            inv_image(ci) = 264;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 299:
        if (dbmode == 3)
        {
            inv_id(ci) = 299;
            inv_image(ci) = 263;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 19;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 298:
        if (dbmode == 3)
        {
            inv_id(ci) = 298;
            inv_image(ci) = 262;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 297:
        if (dbmode == 3)
        {
            inv_id(ci) = 297;
            inv_image(ci) = 261;
            reftype = 60000;
            reftypeminor = 60004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 150;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 296:
        if (dbmode == 3)
        {
            inv_id(ci) = 296;
            inv_image(ci) = 260;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 295:
        if (dbmode == 3)
        {
            inv_id(ci) = 295;
            inv_image(ci) = 259;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 294:
        if (dbmode == 3)
        {
            inv_id(ci) = 294;
            inv_image(ci) = 258;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 293:
        if (dbmode == 3)
        {
            inv_id(ci) = 293;
            inv_image(ci) = 257;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 292:
        if (dbmode == 3)
        {
            inv_id(ci) = 292;
            inv_image(ci) = 256;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 291:
        if (dbmode == 3)
        {
            inv_id(ci) = 291;
            inv_image(ci) = 255;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 290:
        if (dbmode == 3)
        {
            inv_id(ci) = 290;
            inv_image(ci) = 471;
            reftype = 56000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 289;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 288;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 287;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 286;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 52001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 285;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 52001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 284;
            inv_image(ci) = 254;
            reftype = 72000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 283:
        if (dbmode == 3)
        {
            inv_id(ci) = 283;
            inv_image(ci) = 253;
            reftype = 72000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 282:
        if (dbmode == 3)
        {
            inv_id(ci) = 282;
            inv_image(ci) = 252;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 281:
        if (dbmode == 3)
        {
            inv_id(ci) = 281;
            inv_image(ci) = 251;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 280:
        if (dbmode == 3)
        {
            inv_id(ci) = 280;
            inv_image(ci) = 250;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 279:
        if (dbmode == 3)
        {
            inv_id(ci) = 279;
            inv_image(ci) = 249;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 278:
        if (dbmode == 3)
        {
            inv_id(ci) = 278;
            inv_image(ci) = 585;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 277:
        if (dbmode == 3)
        {
            inv_id(ci) = 277;
            inv_image(ci) = 82;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 276:
        if (dbmode == 3)
        {
            inv_id(ci) = 276;
            inv_image(ci) = 524;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 275:
        if (dbmode == 3)
        {
            inv_id(ci) = 275;
            inv_image(ci) = 248;
            reftype = 64000;
            reftypeminor = 99999;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 274:
        if (dbmode == 3)
        {
            inv_id(ci) = 274;
            inv_image(ci) = 232;
            reftype = 64000;
            reftypeminor = 99999;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 273:
        if (dbmode == 3)
        {
            inv_id(ci) = 273;
            inv_image(ci) = 231;
            reftype = 64000;
            reftypeminor = 99999;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 272:
        if (dbmode == 3)
        {
            inv_id(ci) = 272;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 271;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 270;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 269;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 268;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 267;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 266;
            inv_image(ci) = 432;
            reftype = 10000;
            reftypeminor = 10003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 265:
        if (dbmode == 3)
        {
            inv_id(ci) = 265;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 264;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 263;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 262;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 261;
            inv_image(ci) = 201;
            reftype = 57000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 6000;
            inv_param3(ci) = 6;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 4;
        }
        break;
    case 260:
        if (dbmode == 3)
        {
            inv_id(ci) = 260;
            inv_image(ci) = 233;
            reftype = 57000;
            reftypeminor = 57001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 7000;
            inv_param3(ci) = 240;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 259:
        if (dbmode == 3)
        {
            inv_id(ci) = 259;
            inv_image(ci) = 233;
            reftype = 57000;
            reftypeminor = 57002;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 5000;
            inv_param3(ci) = 24;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 258:
        if (dbmode == 3)
        {
            inv_id(ci) = 258;
            inv_image(ci) = 117;
            reftype = 57000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 3;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 257:
        if (dbmode == 3)
        {
            inv_id(ci) = 257;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 256;
            inv_image(ci) = 226;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 15;
            inv_param1(ci) = 80;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 255:
        if (dbmode == 3)
        {
            inv_id(ci) = 255;
            inv_image(ci) = 349;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 15;
            inv_param1(ci) = 40;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 254:
        if (dbmode == 3)
        {
            inv_skill(ci) = 183;
            inv_id(ci) = 254;
            inv_image(ci) = 224;
            reftype = 60000;
            reftypeminor = 60005;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 17;
            inv_param1(ci) = 110;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 253:
        if (dbmode == 3)
        {
            inv_id(ci) = 253;
            inv_image(ci) = 223;
            reftype = 52000;
            reftypeminor = 52002;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 252;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 251;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 250;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 249;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 248;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 247;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 246;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 245;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 244;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 243;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 242;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 241;
            inv_image(ci) = 197;
            reftype = 72000;
            reftypeminor = 99999;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 240:
        if (dbmode == 3)
        {
            inv_id(ci) = 240;
            inv_image(ci) = 220;
            reftype = 72000;
            reftypeminor = 99999;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 239:
        if (dbmode == 3)
        {
            inv_id(ci) = 239;
            inv_image(ci) = 220;
            reftype = 72000;
            reftypeminor = 99999;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 238:
        if (dbmode == 3)
        {
            inv_id(ci) = 238;
            inv_image(ci) = 221;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 237:
        if (dbmode == 3)
        {
            inv_id(ci) = 237;
            inv_image(ci) = 222;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 236:
        if (dbmode == 3)
        {
            inv_id(ci) = 236;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 235;
            inv_image(ci) = 426;
            reftype = 10000;
            reftypeminor = 10008;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 234:
        if (dbmode == 3)
        {
            inv_skill(ci) = 102;
            inv_id(ci) = 234;
            inv_image(ci) = 399;
            reftype = 10000;
            reftypeminor = 10010;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 233:
        if (dbmode == 3)
        {
            inv_id(ci) = 233;
            inv_image(ci) = 233;
            reftype = 57000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 3;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 232:
        if (dbmode == 3)
        {
            inv_skill(ci) = 100;
            inv_id(ci) = 232;
            inv_image(ci) = 503;
            reftype = 10000;
            reftypeminor = 10001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 231:
        if (dbmode == 3)
        {
            inv_skill(ci) = 110;
            inv_id(ci) = 231;
            inv_image(ci) = 547;
            reftype = 24000;
            reftypeminor = 24020;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 230;
            inv_image(ci) = 404;
            reftype = 24000;
            reftypeminor = 24001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 229;
            inv_image(ci) = 505;
            reftype = 10000;
            reftypeminor = 10006;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 228;
            inv_image(ci) = 494;
            reftype = 10000;
            reftypeminor = 10007;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 227:
        if (dbmode == 3)
        {
            inv_skill(ci) = 103;
            inv_id(ci) = 227;
            inv_image(ci) = 504;
            reftype = 10000;
            reftypeminor = 10005;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 226:
        if (dbmode == 3)
        {
            inv_skill(ci) = 102;
            inv_id(ci) = 226;
            inv_image(ci) = 500;
            reftype = 10000;
            reftypeminor = 10010;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 225:
        if (dbmode == 3)
        {
            inv_skill(ci) = 101;
            inv_id(ci) = 225;
            inv_image(ci) = 502;
            reftype = 10000;
            reftypeminor = 10003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 224:
        if (dbmode == 3)
        {
            inv_skill(ci) = 100;
            inv_id(ci) = 224;
            inv_image(ci) = 431;
            reftype = 10000;
            reftypeminor = 10002;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 223:
        if (dbmode == 3)
        {
            inv_id(ci) = 223;
            inv_image(ci) = 198;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 15;
            inv_param1(ci) = 60;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 222:
        if (dbmode == 3)
        {
            inv_id(ci) = 222;
            inv_image(ci) = 199;
            reftype = 64000;
            reftypeminor = 64000;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 221:
        if (dbmode == 3)
        {
            inv_id(ci) = 221;
            inv_image(ci) = 200;
            reftype = 64000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 220:
        if (dbmode == 3)
        {
            inv_id(ci) = 220;
            inv_image(ci) = 201;
            reftype = 64000;
            reftypeminor = 64000;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 219:
        if (dbmode == 3)
        {
            inv_id(ci) = 219;
            inv_image(ci) = 202;
            reftype = 59000;
            reftypeminor = 64000;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 46;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 218:
        if (dbmode == 3)
        {
            inv_id(ci) = 218;
            inv_image(ci) = 203;
            reftype = 64000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 217:
        if (dbmode == 3)
        {
            inv_id(ci) = 217;
            inv_image(ci) = 206;
            reftype = 64000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 216:
        if (dbmode == 3)
        {
            inv_id(ci) = 216;
            inv_image(ci) = 207;
            reftype = 64000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 215:
        if (dbmode == 3)
        {
            inv_id(ci) = 215;
            inv_image(ci) = 208;
            reftype = 64000;
            reftypeminor = 64100;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 214:
        if (dbmode == 3)
        {
            inv_id(ci) = 214;
            inv_image(ci) = 209;
            reftype = 64000;
            reftypeminor = 64000;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 213:
        if (dbmode == 3)
        {
            inv_skill(ci) = 104;
            inv_id(ci) = 213;
            inv_image(ci) = 401;
            reftype = 10000;
            reftypeminor = 10007;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 212:
        if (dbmode == 3)
        {
            inv_skill(ci) = 105;
            inv_id(ci) = 212;
            inv_image(ci) = 425;
            reftype = 10000;
            reftypeminor = 10006;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 211;
            inv_image(ci) = 421;
            reftype = 10000;
            reftypeminor = 10011;
            inv_number(ci) = 1;
            fixeditemenc(0) = 80025;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 210:
        if (dbmode == 3)
        {
            inv_skill(ci) = 111;
            inv_id(ci) = 210;
            inv_image(ci) = 424;
            reftype = 24000;
            reftypeminor = 24030;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 209:
        if (dbmode == 3)
        {
            inv_id(ci) = 209;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 208;
            inv_image(ci) = 33;
            reftype = 77000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 207:
        if (dbmode == 3)
        {
            inv_skill(ci) = 108;
            inv_id(ci) = 207;
            inv_image(ci) = 404;
            reftype = 24000;
            reftypeminor = 24001;
            inv_number(ci) = 1;
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
            inv_id(ci) = 206;
            inv_image(ci) = 400;
            reftype = 10000;
            reftypeminor = 10003;
            inv_number(ci) = 1;
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
            inv_id(ci) = 205;
            inv_image(ci) = 210;
            reftype = 52000;
            reftypeminor = 52002;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 204;
            inv_image(ci) = 196;
            reftype = 57000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 1000;
            inv_param3(ci) = 4;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return 1;
        }
        break;
    case 203:
        if (dbmode == 3)
        {
            inv_id(ci) = 203;
            inv_image(ci) = 471;
            reftype = 56000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 202;
            inv_image(ci) = 471;
            reftype = 56000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 201;
            inv_image(ci) = 193;
            reftype = 57000;
            reftypeminor = 57003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 2000;
            inv_param3(ci) = 2;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 200:
        if (dbmode == 3)
        {
            inv_id(ci) = 200;
            inv_image(ci) = 192;
            reftype = 57000;
            reftypeminor = 57003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 2000;
            inv_param3(ci) = 72;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 199:
        if (dbmode == 3)
        {
            inv_id(ci) = 199;
            inv_image(ci) = 191;
            reftype = 57000;
            reftypeminor = 57003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 2000;
            inv_param3(ci) = 72;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 198:
        if (dbmode == 3)
        {
            inv_id(ci) = 198;
            inv_image(ci) = 164;
            reftype = 57000;
            reftypeminor = 57003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 2000;
            inv_param3(ci) = 72;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 197:
        if (dbmode == 3)
        {
            inv_id(ci) = 197;
            inv_image(ci) = 189;
            reftype = 57000;
            reftypeminor = 57004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 3000;
            inv_param3(ci) = 12;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 196:
        if (dbmode == 3)
        {
            inv_id(ci) = 196;
            inv_image(ci) = 188;
            reftype = 57000;
            reftypeminor = 57004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 3000;
            inv_param3(ci) = 8;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 195:
        if (dbmode == 3)
        {
            inv_id(ci) = 195;
            inv_image(ci) = 187;
            reftype = 57000;
            reftypeminor = 57004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 3000;
            inv_param3(ci) = 12;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 194:
        if (dbmode == 3)
        {
            inv_id(ci) = 194;
            inv_image(ci) = 186;
            reftype = 57000;
            reftypeminor = 57004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 3000;
            inv_param3(ci) = 8;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 193:
        if (dbmode == 3)
        {
            inv_id(ci) = 193;
            inv_image(ci) = 185;
            reftype = 57000;
            reftypeminor = 64000;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 2000;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 192:
        if (dbmode == 3)
        {
            inv_id(ci) = 192;
            inv_image(ci) = 184;
            reftype = 57000;
            reftypeminor = 99999;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 3000;
            inv_param3(ci) = 16;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 191:
        if (dbmode == 3)
        {
            inv_id(ci) = 191;
            inv_image(ci) = 183;
            reftype = 57000;
            reftypeminor = 64000;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 4000;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 190:
        if (dbmode == 3)
        {
            inv_id(ci) = 190;
            inv_image(ci) = 182;
            reftype = 57000;
            reftypeminor = 57003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 2000;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 189:
        if (dbmode == 3)
        {
            inv_id(ci) = 189;
            inv_image(ci) = 181;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 188:
        if (dbmode == 3)
        {
            inv_id(ci) = 188;
            inv_image(ci) = 180;
            reftype = 57000;
            reftypeminor = 57003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 2000;
            inv_param3(ci) = 72;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 187:
        if (dbmode == 3)
        {
            inv_id(ci) = 187;
            inv_image(ci) = 179;
            reftype = 57000;
            reftypeminor = 57003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 2000;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 186:
        if (dbmode == 3)
        {
            inv_id(ci) = 186;
            inv_image(ci) = 178;
            reftype = 57000;
            reftypeminor = 57003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 2000;
            inv_param3(ci) = 72;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 185:
        if (dbmode == 3)
        {
            inv_id(ci) = 185;
            inv_image(ci) = 177;
            reftype = 57000;
            reftypeminor = 57003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 2000;
            inv_param3(ci) = 72;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 184:
        if (dbmode == 3)
        {
            inv_id(ci) = 184;
            inv_image(ci) = 176;
            reftype = 57000;
            reftypeminor = 57003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 3000;
            inv_param3(ci) = 8;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 183:
        if (dbmode == 3)
        {
            inv_id(ci) = 183;
            inv_image(ci) = 175;
            reftype = 57000;
            reftypeminor = 57004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 3000;
            inv_param3(ci) = 16;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 182:
        if (dbmode == 3)
        {
            inv_id(ci) = 182;
            inv_image(ci) = 174;
            reftype = 57000;
            reftypeminor = 57004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 3000;
            inv_param3(ci) = 12;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 181:
        if (dbmode == 3)
        {
            inv_id(ci) = 181;
            inv_image(ci) = 173;
            reftype = 57000;
            reftypeminor = 57004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 3000;
            inv_param3(ci) = 16;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 180:
        if (dbmode == 3)
        {
            inv_id(ci) = 180;
            inv_image(ci) = 172;
            reftype = 57000;
            reftypeminor = 57004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 3000;
            inv_param3(ci) = 16;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 179:
        if (dbmode == 3)
        {
            inv_id(ci) = 179;
            inv_image(ci) = 171;
            reftype = 57000;
            reftypeminor = 64000;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 2000;
            inv_param3(ci) = 48;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 7;
        }
        break;
    case 178:
        if (dbmode == 3)
        {
            inv_id(ci) = 178;
            inv_image(ci) = 170;
            reftype = 57000;
            reftypeminor = 57003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 3000;
            inv_param3(ci) = 72;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 177:
        if (dbmode == 3)
        {
            inv_id(ci) = 177;
            inv_image(ci) = 169;
            reftype = 57000;
            reftypeminor = 57003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 3000;
            inv_param3(ci) = 72;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 176:
        if (dbmode == 3)
        {
            inv_id(ci) = 176;
            inv_image(ci) = 471;
            reftype = 56000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 175;
            inv_image(ci) = 471;
            reftype = 56000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 174;
            inv_image(ci) = 166;
            reftype = 60000;
            reftypeminor = 60004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 110;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 173:
        if (dbmode == 3)
        {
            inv_id(ci) = 173;
            inv_image(ci) = 355;
            reftype = 60001;
            reftypeminor = 60001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 100;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 172;
            inv_image(ci) = 163;
            reftype = 60002;
            reftypeminor = 60002;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 171:
        if (dbmode == 3)
        {
            inv_id(ci) = 171;
            inv_image(ci) = 163;
            reftype = 60002;
            reftypeminor = 60002;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 170:
        if (dbmode == 3)
        {
            inv_id(ci) = 170;
            inv_image(ci) = 162;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 169:
        if (dbmode == 3)
        {
            inv_id(ci) = 169;
            inv_image(ci) = 161;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 168:
        if (dbmode == 3)
        {
            inv_id(ci) = 168;
            inv_image(ci) = 160;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 167:
        if (dbmode == 3)
        {
            inv_id(ci) = 167;
            inv_image(ci) = 159;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 166:
        if (dbmode == 3)
        {
            inv_id(ci) = 166;
            inv_image(ci) = 158;
            reftype = 60000;
            reftypeminor = 64000;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 165:
        if (dbmode == 3)
        {
            inv_id(ci) = 165;
            inv_image(ci) = 157;
            reftype = 60000;
            reftypeminor = 64000;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 164:
        if (dbmode == 3)
        {
            inv_id(ci) = 164;
            inv_image(ci) = 156;
            reftype = 60000;
            reftypeminor = 64000;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 163:
        if (dbmode == 3)
        {
            inv_id(ci) = 163;
            inv_image(ci) = 155;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 162:
        if (dbmode == 3)
        {
            inv_id(ci) = 162;
            inv_image(ci) = 154;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 161:
        if (dbmode == 3)
        {
            inv_id(ci) = 161;
            inv_image(ci) = 153;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 1;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 160:
        if (dbmode == 3)
        {
            inv_id(ci) = 160;
            inv_image(ci) = 152;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 4;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 159:
        if (dbmode == 3)
        {
            inv_id(ci) = 159;
            inv_image(ci) = 151;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 158:
        if (dbmode == 3)
        {
            inv_id(ci) = 158;
            inv_image(ci) = 150;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 157:
        if (dbmode == 3)
        {
            inv_id(ci) = 157;
            inv_image(ci) = 149;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 156:
        if (dbmode == 3)
        {
            inv_id(ci) = 156;
            inv_image(ci) = 148;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 155:
        if (dbmode == 3)
        {
            inv_id(ci) = 155;
            inv_image(ci) = 147;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 15;
            inv_param1(ci) = 100;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 154:
        if (dbmode == 3)
        {
            inv_id(ci) = 154;
            inv_image(ci) = 146;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 15;
            inv_param1(ci) = 100;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 153:
        if (dbmode == 3)
        {
            inv_id(ci) = 153;
            inv_image(ci) = 145;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 15;
            inv_param1(ci) = 100;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 152:
        if (dbmode == 3)
        {
            inv_id(ci) = 152;
            inv_image(ci) = 144;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 151:
        if (dbmode == 3)
        {
            inv_id(ci) = 151;
            inv_image(ci) = 143;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 150:
        if (dbmode == 3)
        {
            inv_id(ci) = 150;
            inv_image(ci) = 142;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 149:
        if (dbmode == 3)
        {
            inv_id(ci) = 149;
            inv_image(ci) = 141;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 148:
        if (dbmode == 3)
        {
            inv_id(ci) = 148;
            inv_image(ci) = 140;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 147:
        if (dbmode == 3)
        {
            inv_id(ci) = 147;
            inv_image(ci) = 139;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 146:
        if (dbmode == 3)
        {
            inv_id(ci) = 146;
            inv_image(ci) = 138;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 145:
        if (dbmode == 3)
        {
            inv_id(ci) = 145;
            inv_image(ci) = 137;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 144:
        if (dbmode == 3)
        {
            inv_id(ci) = 144;
            inv_image(ci) = 136;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 143:
        if (dbmode == 3)
        {
            inv_id(ci) = 143;
            inv_image(ci) = 135;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 142:
        if (dbmode == 3)
        {
            inv_id(ci) = 142;
            inv_image(ci) = 523;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 15;
            inv_param1(ci) = 200;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 141:
        if (dbmode == 3)
        {
            inv_id(ci) = 141;
            inv_image(ci) = 133;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 140:
        if (dbmode == 3)
        {
            inv_id(ci) = 140;
            inv_image(ci) = 132;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 139:
        if (dbmode == 3)
        {
            inv_id(ci) = 139;
            inv_image(ci) = 526;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 138:
        if (dbmode == 3)
        {
            inv_id(ci) = 138;
            inv_image(ci) = 525;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 137:
        if (dbmode == 3)
        {
            inv_id(ci) = 137;
            inv_image(ci) = 129;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 136:
        if (dbmode == 3)
        {
            inv_id(ci) = 136;
            inv_image(ci) = 128;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 135:
        if (dbmode == 3)
        {
            inv_id(ci) = 135;
            inv_image(ci) = 127;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 134:
        if (dbmode == 3)
        {
            inv_id(ci) = 134;
            inv_image(ci) = 126;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 133:
        if (dbmode == 3)
        {
            inv_id(ci) = 133;
            inv_image(ci) = 125;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 132:
        if (dbmode == 3)
        {
            inv_id(ci) = 132;
            inv_image(ci) = 124;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 131:
        if (dbmode == 3)
        {
            inv_id(ci) = 131;
            inv_image(ci) = 123;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 130:
        if (dbmode == 3)
        {
            inv_id(ci) = 130;
            inv_image(ci) = 122;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 129:
        if (dbmode == 3)
        {
            inv_id(ci) = 129;
            inv_image(ci) = 121;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 128:
        if (dbmode == 3)
        {
            inv_id(ci) = 128;
            inv_image(ci) = 120;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 127:
        if (dbmode == 3)
        {
            inv_id(ci) = 127;
            inv_image(ci) = 119;
            reftype = 59000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 2;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 126:
        if (dbmode == 3)
        {
            inv_id(ci) = 126;
            inv_image(ci) = 118;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 125:
        if (dbmode == 3)
        {
            inv_id(ci) = 125;
            inv_image(ci) = 471;
            reftype = 56000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 124;
            inv_image(ci) = 116;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 123:
        if (dbmode == 3)
        {
            inv_id(ci) = 123;
            inv_image(ci) = 471;
            reftype = 56000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 122;
            inv_image(ci) = 471;
            reftype = 56000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 121;
            inv_image(ci) = 471;
            reftype = 56000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 120;
            inv_image(ci) = 471;
            reftype = 56000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 119;
            inv_image(ci) = 471;
            reftype = 56000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 118;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 117;
            inv_image(ci) = 109;
            reftype = 64000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 116:
        if (dbmode == 3)
        {
            inv_id(ci) = 116;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 115;
            inv_image(ci) = 381;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 114:
        if (dbmode == 3)
        {
            inv_id(ci) = 114;
            inv_image(ci) = 106;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 113:
        if (dbmode == 3)
        {
            inv_id(ci) = 113;
            inv_image(ci) = 105;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 112:
        if (dbmode == 3)
        {
            inv_id(ci) = 112;
            inv_image(ci) = 104;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 15;
            inv_param1(ci) = 150;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 111:
        if (dbmode == 3)
        {
            inv_id(ci) = 111;
            inv_image(ci) = 103;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 110:
        if (dbmode == 3)
        {
            inv_id(ci) = 110;
            inv_image(ci) = 102;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 109:
        if (dbmode == 3)
        {
            inv_id(ci) = 109;
            inv_image(ci) = 101;
            reftype = 60001;
            reftypeminor = 60001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param2(ci) = 100;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 108;
            inv_image(ci) = 100;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 107:
        if (dbmode == 3)
        {
            inv_id(ci) = 107;
            inv_image(ci) = 99;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 106:
        if (dbmode == 3)
        {
            inv_id(ci) = 106;
            inv_image(ci) = 98;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 105:
        if (dbmode == 3)
        {
            inv_id(ci) = 105;
            inv_image(ci) = 97;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 104:
        if (dbmode == 3)
        {
            inv_id(ci) = 104;
            inv_image(ci) = 96;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 103:
        if (dbmode == 3)
        {
            inv_id(ci) = 103;
            inv_image(ci) = 95;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 102:
        if (dbmode == 3)
        {
            inv_id(ci) = 102;
            inv_image(ci) = 94;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 44;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 101:
        if (dbmode == 3)
        {
            inv_id(ci) = 101;
            inv_image(ci) = 93;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 44;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 100:
        if (dbmode == 3)
        {
            inv_id(ci) = 100;
            inv_image(ci) = 580;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 99:
        if (dbmode == 3)
        {
            inv_id(ci) = 99;
            inv_image(ci) = 91;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 98:
        if (dbmode == 3)
        {
            inv_id(ci) = 98;
            inv_image(ci) = 90;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 97:
        if (dbmode == 3)
        {
            inv_id(ci) = 97;
            inv_image(ci) = 89;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 96:
        if (dbmode == 3)
        {
            inv_id(ci) = 96;
            inv_image(ci) = 88;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 95:
        if (dbmode == 3)
        {
            inv_id(ci) = 95;
            inv_image(ci) = 87;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 94:
        if (dbmode == 3)
        {
            inv_id(ci) = 94;
            inv_image(ci) = 86;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 93:
        if (dbmode == 3)
        {
            inv_id(ci) = 93;
            inv_image(ci) = 85;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 92:
        if (dbmode == 3)
        {
            inv_id(ci) = 92;
            inv_image(ci) = 84;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 44;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 91:
        if (dbmode == 3)
        {
            inv_id(ci) = 91;
            inv_image(ci) = 72;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 90:
        if (dbmode == 3)
        {
            inv_id(ci) = 90;
            inv_image(ci) = 80;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 89:
        if (dbmode == 3)
        {
            inv_id(ci) = 89;
            inv_image(ci) = 78;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 88:
        if (dbmode == 3)
        {
            inv_skill(ci) = 183;
            inv_id(ci) = 88;
            inv_image(ci) = 76;
            reftype = 60000;
            reftypeminor = 60005;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 17;
            inv_param1(ci) = 200;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 87:
        if (dbmode == 3)
        {
            inv_id(ci) = 87;
            inv_image(ci) = 75;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 86:
        if (dbmode == 3)
        {
            inv_id(ci) = 86;
            inv_image(ci) = 74;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 85:
        if (dbmode == 3)
        {
            inv_id(ci) = 85;
            inv_image(ci) = 73;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 84:
        if (dbmode == 3)
        {
            inv_id(ci) = 84;
            inv_image(ci) = 70;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 83:
        if (dbmode == 3)
        {
            inv_id(ci) = 83;
            inv_image(ci) = 69;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 82:
        if (dbmode == 3)
        {
            inv_id(ci) = 82;
            inv_image(ci) = 68;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 81:
        if (dbmode == 3)
        {
            inv_id(ci) = 81;
            inv_image(ci) = 67;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 44;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 80:
        if (dbmode == 3)
        {
            inv_id(ci) = 80;
            inv_image(ci) = 66;
            reftype = 60000;
            reftypeminor = 60004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 100;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 79:
        if (dbmode == 3)
        {
            inv_id(ci) = 79;
            inv_image(ci) = 234;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 78:
        if (dbmode == 3)
        {
            inv_id(ci) = 78;
            inv_image(ci) = 235;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 77:
        if (dbmode == 3)
        {
            inv_id(ci) = 77;
            inv_image(ci) = 237;
            reftype = 60000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_function(ci) = 44;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 76:
        if (dbmode == 3)
        {
            inv_id(ci) = 76;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 52001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 75;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 52001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 74;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 52001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 73;
            inv_image(ci) = 405;
            reftype = 10000;
            reftypeminor = 10002;
            inv_number(ci) = 1;
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
            inv_id(ci) = 72;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 52001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 71;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 52001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 70;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 52001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 69;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 52001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 68;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 52001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 67;
            inv_image(ci) = 398;
            reftype = 34000;
            reftypeminor = 34001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 66:
        if (dbmode == 3)
        {
            inv_id(ci) = 66;
            inv_image(ci) = 423;
            reftype = 19000;
            reftypeminor = 19001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 65:
        if (dbmode == 3)
        {
            inv_id(ci) = 65;
            inv_image(ci) = 422;
            reftype = 20000;
            reftypeminor = 20001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 64:
        if (dbmode == 3)
        {
            inv_skill(ci) = 100;
            inv_id(ci) = 64;
            inv_image(ci) = 405;
            reftype = 10000;
            reftypeminor = 10002;
            inv_number(ci) = 1;
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
            inv_id(ci) = 63;
            inv_image(ci) = 421;
            reftype = 10000;
            reftypeminor = 10011;
            inv_number(ci) = 1;
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
            inv_id(ci) = 62;
            inv_image(ci) = 420;
            reftype = 25000;
            reftypeminor = 25020;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 61:
        if (dbmode == 3)
        {
            inv_skill(ci) = 108;
            inv_id(ci) = 61;
            inv_image(ci) = 412;
            reftype = 25000;
            reftypeminor = 25001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 60:
        if (dbmode == 3)
        {
            inv_skill(ci) = 110;
            inv_id(ci) = 60;
            inv_image(ci) = 419;
            reftype = 24000;
            reftypeminor = 24020;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 59;
            inv_image(ci) = 411;
            reftype = 14000;
            reftypeminor = 14003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 58:
        if (dbmode == 3)
        {
            inv_skill(ci) = 108;
            inv_id(ci) = 58;
            inv_image(ci) = 404;
            reftype = 24000;
            reftypeminor = 24001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 57;
            inv_image(ci) = 501;
            reftype = 10000;
            reftypeminor = 10002;
            inv_number(ci) = 1;
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
            inv_id(ci) = 56;
            inv_image(ci) = 405;
            reftype = 10000;
            reftypeminor = 10002;
            inv_number(ci) = 1;
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
            inv_id(ci) = 55;
            inv_image(ci) = 437;
            reftype = 69000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 54:
        if (dbmode == 3)
        {
            inv_id(ci) = 54;
            inv_image(ci) = 433;
            reftype = 68000;
            reftypeminor = 99999;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 53:
        if (dbmode == 3)
        {
            inv_id(ci) = 53;
            inv_image(ci) = 247;
            reftype = 64000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 52:
        if (dbmode == 3)
        {
            inv_id(ci) = 52;
            inv_image(ci) = 246;
            reftype = 64000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 51:
        if (dbmode == 3)
        {
            inv_id(ci) = 51;
            inv_image(ci) = 245;
            reftype = 64000;
            reftypeminor = 64000;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 50:
        if (dbmode == 3)
        {
            inv_id(ci) = 50;
            inv_image(ci) = 244;
            reftype = 64000;
            reftypeminor = 64000;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 49:
        if (dbmode == 3)
        {
            inv_id(ci) = 49;
            inv_image(ci) = 243;
            reftype = 64000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 48:
        if (dbmode == 3)
        {
            inv_id(ci) = 48;
            inv_image(ci) = 242;
            reftype = 64000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 47:
        if (dbmode == 3)
        {
            inv_id(ci) = 47;
            inv_image(ci) = 204;
            reftype = 64000;
            reftypeminor = 64100;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 46:
        if (dbmode == 3)
        {
            inv_id(ci) = 46;
            inv_image(ci) = 241;
            reftype = 64000;
            reftypeminor = 64000;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 45:
        if (dbmode == 3)
        {
            inv_id(ci) = 45;
            inv_image(ci) = 240;
            reftype = 64000;
            reftypeminor = 64000;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 44:
        if (dbmode == 3)
        {
            inv_id(ci) = 44;
            inv_image(ci) = 238;
            reftype = 77000;
            reftypeminor = 64000;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 6 || cdata_god(0) == 5;
        }
        break;
    case 43:
        if (dbmode == 3)
        {
            inv_id(ci) = 43;
            inv_image(ci) = 239;
            reftype = 64000;
            reftypeminor = 64000;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 42:
        if (dbmode == 3)
        {
            inv_id(ci) = 42;
            inv_image(ci) = 213;
            reftype = 77000;
            reftypeminor = 77001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 6 || cdata_god(0) == 5;
        }
        break;
    case 41:
        if (dbmode == 3)
        {
            inv_id(ci) = 41;
            inv_image(ci) = 213;
            reftype = 77000;
            reftypeminor = 77001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 6 || cdata_god(0) == 5;
        }
        break;
    case 40:
        if (dbmode == 3)
        {
            inv_id(ci) = 40;
            inv_image(ci) = 212;
            reftype = 77000;
            reftypeminor = 77001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 6 || cdata_god(0) == 5;
        }
        break;
    case 39:
        if (dbmode == 3)
        {
            inv_id(ci) = 39;
            inv_image(ci) = 212;
            reftype = 77000;
            reftypeminor = 77001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 6 || cdata_god(0) == 5;
        }
        break;
    case 38:
        if (dbmode == 3)
        {
            inv_id(ci) = 38;
            inv_image(ci) = 33;
            reftype = 77000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 6 || cdata_god(0) == 5;
        }
        break;
    case 37:
        if (dbmode == 3)
        {
            inv_id(ci) = 37;
            inv_image(ci) = 211;
            reftype = 77000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 6 || cdata_god(0) == 5;
        }
        break;
    case 36:
        if (dbmode == 3)
        {
            inv_id(ci) = 36;
            inv_image(ci) = 211;
            reftype = 77000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 6 || cdata_god(0) == 5;
        }
        break;
    case 35:
        if (dbmode == 3)
        {
            inv_id(ci) = 35;
            inv_image(ci) = 211;
            reftype = 77000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        if (dbmode == 16 && dbspec == 12)
        {
            return cdata_god(0) == 6 || cdata_god(0) == 5;
        }
        break;
    case 34:
        if (dbmode == 3)
        {
            inv_id(ci) = 34;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 33;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 32;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 31;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 52002;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 30;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 29;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 28;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 27;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 26;
            inv_image(ci) = 354;
            reftype = 52000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 25;
            inv_image(ci) = 333;
            reftype = 55000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 2;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 24;
            inv_image(ci) = 333;
            reftype = 55000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 23;
            inv_image(ci) = 333;
            reftype = 55000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_param1(ci) = 1;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 22;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 21;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 20;
            inv_image(ci) = 429;
            reftype = 54000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 19;
            inv_image(ci) = 471;
            reftype = 56000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 18;
            inv_image(ci) = 471;
            reftype = 56000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 17;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 16;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 15;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 14;
            inv_image(ci) = 470;
            reftype = 53000;
            reftypeminor = 0;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
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
            inv_id(ci) = 13;
            inv_image(ci) = 407;
            reftype = 32000;
            reftypeminor = 32001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 12:
        if (dbmode == 3)
        {
            inv_id(ci) = 12;
            inv_image(ci) = 460;
            reftype = 18000;
            reftypeminor = 18001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 11:
        if (dbmode == 3)
        {
            inv_id(ci) = 11;
            inv_image(ci) = 418;
            reftype = 18000;
            reftypeminor = 18001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 10:
        if (dbmode == 3)
        {
            inv_id(ci) = 10;
            inv_image(ci) = 450;
            reftype = 22000;
            reftypeminor = 22001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 9:
        if (dbmode == 3)
        {
            inv_id(ci) = 9;
            inv_image(ci) = 449;
            reftype = 22000;
            reftypeminor = 22003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 8:
        if (dbmode == 3)
        {
            inv_id(ci) = 8;
            inv_image(ci) = 408;
            reftype = 16000;
            reftypeminor = 16003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 7:
        if (dbmode == 3)
        {
            inv_id(ci) = 7;
            inv_image(ci) = 396;
            reftype = 16000;
            reftypeminor = 16001;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 6:
        if (dbmode == 3)
        {
            inv_id(ci) = 6;
            inv_image(ci) = 478;
            reftype = 12000;
            reftypeminor = 12002;
            inv_number(ci) = 1;
            fixeditemenc(0) = 33;
            fixeditemenc(1) = 100;
            fixeditemenc(2) = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 5:
        if (dbmode == 3)
        {
            inv_id(ci) = 5;
            inv_image(ci) = 477;
            reftype = 12000;
            reftypeminor = 12002;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 4:
        if (dbmode == 3)
        {
            inv_skill(ci) = 103;
            inv_id(ci) = 4;
            inv_image(ci) = 427;
            reftype = 10000;
            reftypeminor = 10004;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 3:
        if (dbmode == 3)
        {
            inv_skill(ci) = 102;
            inv_id(ci) = 3;
            inv_image(ci) = 499;
            reftype = 10000;
            reftypeminor = 10009;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 2:
        if (dbmode == 3)
        {
            inv_skill(ci) = 101;
            inv_id(ci) = 2;
            inv_image(ci) = 400;
            reftype = 10000;
            reftypeminor = 10003;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 1:
        if (dbmode == 3)
        {
            inv_skill(ci) = 100;
            inv_id(ci) = 1;
            inv_image(ci) = 405;
            reftype = 10000;
            reftypeminor = 10002;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    case 0:
        if (dbmode == 3)
        {
            inv_id(ci) = 0;
            inv_image(ci) = 33;
            reftype = 99999999;
            reftypeminor = 99999999;
            inv_number(ci) = 1;
            fixeditemenc = 0;
            inv_difficulty_of_identification(ci) = 0;
        }
        break;
    default: assert(0);
    }

    return 0;
}



} // namespace elona
