#include <unordered_map>
#include "character.hpp"
#include "data/types/type_item.hpp"
#include "elona.hpp"
#include "filesystem.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "menu.hpp"
#include "random.hpp"
#include "variables.hpp"



namespace elona
{

void item_db_set_basic_stats(Item& item, int legacy_id)
{
    const auto& info = the_item_db.ensure(legacy_id);
    item.value = info.value;
    item.weight = info.weight;
    item.dice_x = info.dice_x;
    item.dice_y = info.dice_y;
    item.hit_bonus = info.hit_bonus;
    item.damage_bonus = info.damage_bonus;
    item.pv = info.pv;
    item.dv = info.dv;
    item.material = info.material;
}



bool item_db_is_offerable(Item& item, int legacy_id)
{
    (void)item;

    const auto& G = cdata.player().god_id;

    switch (legacy_id)
    {
    case 788: return G == core_god::lulwy;
    case 618: return G == core_god::ehekatl;
    case 554: return G == core_god::kumiromi;
    case 553: return G == core_god::kumiromi;
    case 512: return G == core_god::mani;
    case 496: return G == core_god::mani;
    case 495: return G == core_god::mani;
    case 494: return G == core_god::mani;
    case 492: return G == core_god::mani;
    case 491: return G == core_god::mani;
    case 490: return G == core_god::mani;
    case 489: return G == core_god::mani;
    case 488: return G == core_god::mani;
    case 487: return G == core_god::mani;
    case 486: return G == core_god::mani;
    case 482: return G == core_god::lulwy;
    case 421: return G == core_god::kumiromi;
    case 420: return G == core_god::kumiromi;
    case 419: return G == core_god::kumiromi;
    case 418: return G == core_god::kumiromi;
    case 417: return G == core_god::kumiromi;
    case 354: return G == core_god::ehekatl;
    case 353: return G == core_god::ehekatl;
    case 352: return G == core_god::ehekatl;
    case 351: return G == core_god::ehekatl;
    case 350: return G == core_god::ehekatl;
    case 349: return G == core_god::ehekatl;
    case 348: return G == core_god::ehekatl;
    case 347: return G == core_god::ehekatl;
    case 346: return G == core_god::ehekatl;
    case 345: return G == core_god::ehekatl;
    case 261: return G == core_god::ehekatl;
    case 231: return G == core_god::mani;
    case 230: return G == core_god::lulwy;
    case 229: return G == core_god::itzpalt;
    case 212: return G == core_god::itzpalt;
    case 204: return true;
    case 201: return G == core_god::kumiromi;
    case 200: return G == core_god::kumiromi;
    case 199: return G == core_god::kumiromi;
    case 198: return G == core_god::kumiromi;
    case 193: return G == core_god::kumiromi;
    case 190: return G == core_god::kumiromi;
    case 188: return G == core_god::kumiromi;
    case 187: return G == core_god::kumiromi;
    case 186: return G == core_god::kumiromi;
    case 185: return G == core_god::kumiromi;
    case 179: return G == core_god::kumiromi;
    case 60: return G == core_god::mani;
    case 58: return G == core_god::lulwy;
    case 44: return G == core_god::jure || G == core_god::opatos;
    case 42: return G == core_god::jure || G == core_god::opatos;
    case 41: return G == core_god::jure || G == core_god::opatos;
    case 40: return G == core_god::jure || G == core_god::opatos;
    case 39: return G == core_god::jure || G == core_god::opatos;
    case 38: return G == core_god::jure || G == core_god::opatos;
    case 37: return G == core_god::jure || G == core_god::opatos;
    case 36: return G == core_god::jure || G == core_god::opatos;
    case 35: return G == core_god::jure || G == core_god::opatos;
    default: return false;
    }
}



void item_db_get_description(Item& item, int legacy_id)
{
    (void)item;

    const auto& info = the_item_db.ensure(legacy_id);
    const auto& locale_key_prefix = info.locale_key_prefix;
    if (auto text = i18n::s.get_optional(locale_key_prefix + ".description_0"))
    {
        description(0) = *text;
    }
    if (auto text = i18n::s.get_optional(locale_key_prefix + ".description_1"))
    {
        description(1) = *text;
    }
    if (auto text = i18n::s.get_optional(locale_key_prefix + ".description_2"))
    {
        description(2) = *text;
    }
    if (auto text = i18n::s.get_optional(locale_key_prefix + ".description_3"))
    {
        description(3) = *text;
    }
}



void item_db_get_charge_level(const Item& item, int legacy_id)
{
    (void)item;

    const auto& info = the_item_db.ensure(legacy_id);
    ichargelevel = info.chargelevel;
    reftype = info.category;
}



void item_db_set_full_stats(Item& item, int legacy_id)
{
    const auto& info = the_item_db.ensure(legacy_id);

    // Common initialization
    item_db_set_basic_stats(item, legacy_id);

    item.id = int2itemid(legacy_id);
    item.set_number(1);
    item.difficulty_of_identification = 0; // Default value
    item.image = info.image;
    fixeditemenc(0) = 0; // Default value
    reftype = info.category;
    reftypeminor = info.subcategory;

    switch (legacy_id)
    {
    case 792: item.param2 = 8; break;
    case 791:
        item.skill = 100;
        fixeditemenc(0) = 57;
        fixeditemenc(1) = 300;
        fixeditemenc(2) = 61;
        fixeditemenc(3) = 200;
        fixeditemenc(4) = 0;
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 790: item.function = 15; break;
    case 789: item.function = 15; break;
    case 788: item.skill = 108; break;
    case 787:
        item.param2 = 5;
        item.param3 = 720;
        break;
    case 786: item.param2 = 4; break;
    case 785: item.param2 = 1; break;
    case 781: item.skill = 101; break;
    case 778: item.function = 44; break;
    case 777:
        item.function = 26;
        item.is_precious() = true;
        item.has_cooldown_time() = true;
        item.param3 = 240;
        fixlv = Quality::special;
        break;
    case 776:
        item.function = 26;
        item.is_precious() = true;
        item.has_cooldown_time() = true;
        item.param3 = 240;
        fixlv = Quality::special;
        break;
    case 775:
        item.is_precious() = true;
        item.param2 = 8;
        break;
    case 772:
        item.param1 = 2000;
        item.param3 = 32;
        break;
    case 771: fixlv = Quality::special; break;
    case 767: item.param1 = 0; break;
    case 761:
        item.skill = 183;
        fixeditemenc(0) = 60;
        fixeditemenc(1) = 100;
        fixeditemenc(2) = 0;
        item.function = 17;
        item.is_precious() = true;
        item.param1 = 200;
        fixlv = Quality::special;
        break;
    case 760:
        item.function = 49;
        item.is_precious() = true;
        item.param1 = rnd(20000) + 1;
        fixlv = Quality::special;
        break;
    case 759: item.skill = 100; break;
    case 758:
        item.skill = 110;
        fixeditemenc(0) = 35;
        fixeditemenc(1) = 100;
        fixeditemenc(2) = 0;
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 757:
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
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 756: item.param2 = 7; break;
    case 755: item.param2 = 6; break;
    case 749:
        item.function = 48;
        item.is_precious() = true;
        break;
    case 748:
        item.function = 47;
        item.is_precious() = true;
        item.is_showroom_only() = true;
        break;
    case 747:
        item.param1 = 1;
        item.param2 = rnd(4) + 1;
        break;
    case 746:
        item.function = 30;
        item.is_precious() = true;
        item.has_cooldown_time() = true;
        item.param1 = 1132;
        item.param2 = 100;
        item.param3 = 24;
        break;
    case 745:
        item.function = 30;
        item.is_precious() = true;
        item.has_cooldown_time() = true;
        item.param1 = 1132;
        item.param2 = 100;
        item.param3 = 24;
        break;
    case 744:
        item.function = 30;
        item.is_precious() = true;
        item.has_cooldown_time() = true;
        item.param1 = 1132;
        item.param2 = 100;
        item.param3 = 24;
        break;
    case 743:
        item.function = 30;
        item.is_precious() = true;
        item.has_cooldown_time() = true;
        item.param1 = 1132;
        item.param2 = 100;
        item.param3 = 24;
        break;
    case 742:
        item.is_precious() = true;
        fixlv = Quality::special;
        break;
    case 741:
        item.skill = 100;
        fixeditemenc(0) = 20050;
        fixeditemenc(1) = 550;
        fixeditemenc(2) = 70052;
        fixeditemenc(3) = 400;
        fixeditemenc(4) = 57;
        fixeditemenc(5) = 1150;
        fixeditemenc(6) = 10011;
        fixeditemenc(7) = 720;
        fixeditemenc(8) = 0;
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 740:
        fixeditemenc(0) = 56;
        fixeditemenc(1) = 100;
        fixeditemenc(2) = 30181;
        fixeditemenc(3) = 550;
        fixeditemenc(4) = 20057;
        fixeditemenc(5) = 400;
        fixeditemenc(6) = 0;
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 739:
        item.skill = 107;
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
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 738: item.param2 = 6; break;
    case 735:
        item.skill = 107;
        fixeditemenc(0) = 80025;
        fixeditemenc(1) = 100;
        fixeditemenc(2) = 0;
        break;
    case 733: item.function = 45; break;
    case 732:
        item.count = 3 + rnd(3) - rnd(3);
        item.has_charge() = true;
        break;
    case 731:
        item.count = 3 + rnd(3) - rnd(3);
        item.has_charge() = true;
        break;
    case 730: item.is_precious() = true; break;
    case 728:
        fixeditemenc(0) = 55;
        fixeditemenc(1) = 100;
        fixeditemenc(2) = 20056;
        fixeditemenc(3) = 450;
        fixeditemenc(4) = 20050;
        fixeditemenc(5) = 350;
        fixeditemenc(6) = 0;
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 727:
        item.skill = 168;
        fixeditemenc(0) = 54;
        fixeditemenc(1) = 1000;
        fixeditemenc(2) = 20058;
        fixeditemenc(3) = 450;
        fixeditemenc(4) = 0;
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 726:
        item.skill = 168;
        fixeditemenc(0) = 30183;
        fixeditemenc(1) = -450;
        fixeditemenc(2) = 52;
        fixeditemenc(3) = 400;
        fixeditemenc(4) = 53;
        fixeditemenc(5) = 400;
        fixeditemenc(6) = 0;
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 725:
        item.skill = 111;
        fixeditemenc(0) = 70059;
        fixeditemenc(1) = 400;
        fixeditemenc(2) = 30183;
        fixeditemenc(3) = -700;
        fixeditemenc(4) = 44;
        fixeditemenc(5) = 450;
        fixeditemenc(6) = 0;
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 724: item.is_precious() = true; break;
    case 723:
        fixeditemenc(0) = 50;
        fixeditemenc(1) = 600;
        fixeditemenc(2) = 30166;
        fixeditemenc(3) = 650;
        fixeditemenc(4) = 0;
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 722:
        fixeditemenc(0) = 51;
        fixeditemenc(1) = 600;
        fixeditemenc(2) = 30109;
        fixeditemenc(3) = 700;
        fixeditemenc(4) = 0;
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 721:
        item.function = 43;
        item.is_precious() = true;
        item.has_cooldown_time() = true;
        item.param3 = 480;
        fixlv = Quality::special;
        break;
    case 720: item.param1 = 200; break;
    case 719:
        item.skill = 100;
        fixeditemenc(0) = 44;
        fixeditemenc(1) = 250;
        fixeditemenc(2) = 39;
        fixeditemenc(3) = 200;
        fixeditemenc(4) = 33;
        fixeditemenc(5) = 100;
        fixeditemenc(6) = 0;
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 718:
        item.skill = 111;
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
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 717: item.function = 42; break;
    case 716:
        item.skill = 111;
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 715: item.function = 41; break;
    case 714:
        item.skill = 111;
        fixeditemenc(0) = 80024;
        fixeditemenc(1) = 100;
        fixeditemenc(2) = 0;
        break;
    case 713:
        item.skill = 111;
        fixeditemenc(0) = 70061;
        fixeditemenc(1) = 100;
        fixeditemenc(2) = 0;
        break;
    case 710:
        item.count = 3 + rnd(3) - rnd(3);
        item.has_charge() = true;
        break;
    case 707:
        item.skill = 183;
        fixeditemenc(0) = 49;
        fixeditemenc(1) = 100;
        fixeditemenc(2) = 0;
        item.function = 17;
        item.is_precious() = true;
        item.param1 = 180;
        fixlv = Quality::special;
        break;
    case 705:
        fixeditemenc(0) = 48;
        fixeditemenc(1) = 100;
        fixeditemenc(2) = 10017;
        fixeditemenc(3) = 450;
        fixeditemenc(4) = 41;
        fixeditemenc(5) = 100;
        fixeditemenc(6) = 0;
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 703: item.function = 39; break;
    case 702:
        item.is_precious() = true;
        item.param2 = 4;
        fixlv = Quality::special;
        break;
    case 701: item.function = 37; break;
    case 699: item.is_precious() = true; break;
    case 697:
        item.count = 2 + rnd(2) - rnd(2);
        item.has_charge() = true;
        break;
    case 696:
        item.count = 2 + rnd(2) - rnd(2);
        item.has_charge() = true;
        break;
    case 695:
        item.skill = 102;
        fixeditemenc(0) = 44;
        fixeditemenc(1) = 750;
        fixeditemenc(2) = 0;
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 693:
        item.skill = 183;
        item.function = 17;
        item.param1 = 175;
        break;
    case 692:
        item.skill = 183;
        item.function = 17;
        item.param1 = 70;
        break;
    case 691:
        item.skill = 183;
        item.function = 17;
        item.param1 = 130;
        break;
    case 690:
        item.skill = 183;
        item.function = 17;
        item.param1 = 150;
        break;
    case 689: item.function = 36; break;
    case 688: item.function = 35; break;
    case 687:
        item.count = 2 + rnd(2) - rnd(2);
        item.has_charge() = true;
        break;
    case 686:
        item.function = 34;
        item.is_precious() = true;
        item.has_cooldown_time() = true;
        item.param3 = 720;
        fixlv = Quality::special;
        break;
    case 685: item.function = 33; break;
    case 684:
        item.function = 32;
        item.is_precious() = true;
        break;
    case 683:
        item.function = 30;
        item.is_precious() = true;
        item.has_cooldown_time() = true;
        item.param1 = 1132;
        item.param2 = 100;
        item.param3 = 24;
        fixlv = Quality::special;
        break;
    case 682:
        item.function = 31;
        item.is_precious() = true;
        item.has_cooldown_time() = true;
        item.param3 = 72;
        fixlv = Quality::special;
        break;
    case 681:
        item.function = 30;
        item.is_precious() = true;
        item.has_cooldown_time() = true;
        item.param1 = 404;
        item.param2 = 400;
        item.param3 = 8;
        fixlv = Quality::special;
        break;
    case 680:
        item.function = 30;
        item.is_precious() = true;
        item.has_cooldown_time() = true;
        item.param1 = 446;
        item.param2 = 300;
        item.param3 = 12;
        fixlv = Quality::special;
        break;
    case 679:
        item.skill = 103;
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
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 678:
        item.skill = 101;
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
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 677:
        item.skill = 104;
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
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 676:
        item.skill = 105;
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
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 675:
        item.skill = 107;
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
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 674:
        item.skill = 110;
        fixeditemenc(0) = 80017;
        fixeditemenc(1) = 350;
        fixeditemenc(2) = 43;
        fixeditemenc(3) = 200;
        fixeditemenc(4) = 30110;
        fixeditemenc(5) = 450;
        fixeditemenc(6) = 20057;
        fixeditemenc(7) = 350;
        fixeditemenc(8) = 0;
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 673:
        item.skill = 108;
        fixeditemenc(0) = 80014;
        fixeditemenc(1) = 200;
        fixeditemenc(2) = 80005;
        fixeditemenc(3) = 200;
        fixeditemenc(4) = 10018;
        fixeditemenc(5) = 250;
        fixeditemenc(6) = 20052;
        fixeditemenc(7) = 300;
        fixeditemenc(8) = 0;
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 672:
        item.function = 29;
        item.is_precious() = true;
        fixlv = Quality::special;
        break;
    case 671:
        item.function = 28;
        item.is_precious() = true;
        fixlv = Quality::special;
        break;
    case 670: item.param1 = 7; break;
    case 669: item.param1 = 7; break;
    case 668:
        item.param1 = 1;
        item.param2 = rnd(4) + 1;
        break;
    case 667: item.param2 = 7; break;
    case 666:
        item.function = 27;
        item.is_precious() = true;
        item.has_cooldown_time() = true;
        item.param3 = 120;
        fixlv = Quality::special;
        break;
    case 665:
        item.function = 26;
        item.is_precious() = true;
        item.has_cooldown_time() = true;
        item.param3 = 240;
        fixlv = Quality::special;
        break;
    case 664:
        fixeditemenc(0) = 10018;
        fixeditemenc(1) = 400 + rnd((rnd(1000) + 1));
        fixeditemenc(2) = 0;
        break;
    case 663:
        item.is_precious() = true;
        fixlv = Quality::special;
        break;
    case 662:
        item.is_precious() = true;
        item.param2 = 7;
        fixlv = Quality::special;
        break;
    case 661:
        fixeditemenc(0) = 43;
        fixeditemenc(1) = 100;
        fixeditemenc(2) = 29;
        fixeditemenc(3) = 100;
        fixeditemenc(4) = 10012;
        fixeditemenc(5) = 250;
        fixeditemenc(6) = 30182;
        fixeditemenc(7) = 200;
        fixeditemenc(8) = 0;
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 660:
        item.count = 5 + rnd(5) - rnd(5);
        item.has_charge() = true;
        break;
    case 655:
        item.is_precious() = true;
        item.param2 = 7;
        fixlv = Quality::special;
        break;
    case 654: item.param1 = 160; break;
    case 648: item.function = 44; break;
    case 643: item.param1 = 130; break;
    case 641:
        item.is_precious() = true;
        fixlv = Quality::special;
        break;
    case 640: item.function = 25; break;
    case 639:
        item.is_precious() = true;
        item.param2 = 7;
        fixlv = Quality::special;
        break;
    case 637:
        item.is_precious() = true;
        fixlv = Quality::special;
        break;
    case 635: item.function = 24; break;
    case 634: item.function = 23; break;
    case 633:
        item.skill = 111;
        fixeditemenc(0) = 70054;
        fixeditemenc(1) = 800;
        fixeditemenc(2) = 0;
        break;
    case 630: item.function = 21; break;
    case 629:
        item.function = 20;
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 628:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 627:
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
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 626: item.is_precious() = true; break;
    case 625: item.is_precious() = true; break;
    case 624: item.is_precious() = true; break;
    case 623: item.is_precious() = true; break;
    case 622: item.is_precious() = true; break;
    case 618:
        item.param1 = 6000;
        item.param3 = 4;
        break;
    case 616: item.is_precious() = true; break;
    case 615: item.is_precious() = true; break;
    case 613: item.param1 = 180; break;
    case 611: item.function = 8; break;
    case 606:
        item.function = 15;
        item.param1 = 225;
        break;
    case 603:
        item.function = 44;
        item.is_precious() = true;
        break;
    case 602: item.param2 = 100; break;
    case 600: item.is_precious() = true; break;
    case 598: item.param1 = 6; break;
    case 597: item.param1 = 6; break;
    case 587: item.function = 14; break;
    case 583:
        item.function = 13;
        item.param1 = 100;
        break;
    case 582:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 581:
        item.count = 6 + rnd(6) - rnd(6);
        item.has_charge() = true;
        break;
    case 578: item.function = 11; break;
    case 576: item.function = 10; break;
    case 573:
        item.param1 = 8000;
        item.param3 = 240;
        break;
    case 571: item.param2 = 5; break;
    case 570:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 569:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 568:
        item.count = 12 + rnd(12) - rnd(12);
        item.has_charge() = true;
        break;
    case 567:
        item.count = 12 + rnd(12) - rnd(12);
        item.has_charge() = true;
        break;
    case 565:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 564:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 563: item.param1 = 0; break;
    case 562: item.function = 8; break;
    case 560: item.is_precious() = true; break;
    case 558:
        fixeditemenc(0) = 31;
        fixeditemenc(1) = 100;
        fixeditemenc(2) = 20057;
        fixeditemenc(3) = 100;
        fixeditemenc(4) = 0;
        break;
    case 557:
        fixeditemenc(0) = 30;
        fixeditemenc(1) = 100;
        fixeditemenc(2) = 0;
        break;
    case 556:
        fixeditemenc(0) = 29;
        fixeditemenc(1) = 500;
        fixeditemenc(2) = 0;
        break;
    case 555: item.function = 7; break;
    case 554: item.param2 = 1; break;
    case 553: item.param2 = 1; break;
    case 552:
        fixeditemenc(0) = 32;
        fixeditemenc(1) = 100;
        fixeditemenc(2) = 0;
        break;
    case 551:
        item.count = 3 + rnd(3) - rnd(3);
        item.has_charge() = true;
        break;
    case 550:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 548:
        item.count = 3 + rnd(3) - rnd(3);
        item.has_charge() = true;
        break;
    case 546:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 545:
        item.count = 7 + rnd(7) - rnd(7);
        item.has_charge() = true;
        break;
    case 544:
        item.function = 6;
        item.param1 = discsetmc();
        break;
    case 526:
        item.param1 = rnd(5) + 2;
        item.param2 = choice(isetfruit);
        break;
    case 522: item.param1 = 1; break;
    case 521: item.param1 = 1; break;
    case 520:
        fixeditemenc(0) = 32;
        fixeditemenc(1) = 100;
        fixeditemenc(2) = 0;
        break;
    case 518:
        item.count = 3 + rnd(3) - rnd(3);
        item.has_charge() = true;
        break;
    case 517:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 514:
        item.skill = 110;
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
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 513: item.skill = 110; break;
    case 512: item.skill = 110; break;
    case 511: item.param1 = 100 + rnd(200); break;
    case 505: item.is_precious() = true; break;
    case 504: item.function = 38; break;
    case 499: item.param2 = 7; break;
    case 498: item.param2 = 6; break;
    case 497: item.param2 = 5; break;
    case 496: item.skill = 110; break;
    case 488: item.function = 9; break;
    case 485:
        item.count = 8 + rnd(8) - rnd(8);
        item.has_charge() = true;
        break;
    case 484:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 483: item.skill = 109; break;
    case 482: item.skill = 109; break;
    case 481:
        item.count = 2 + rnd(2) - rnd(2);
        item.has_charge() = true;
        break;
    case 480:
        item.count = 2 + rnd(2) - rnd(2);
        item.has_charge() = true;
        break;
    case 478: item.function = 5; break;
    case 454: item.skill = 168; break;
    case 453: item.skill = 168; break;
    case 452: item.skill = 168; break;
    case 451: item.skill = 168; break;
    case 450: item.skill = 168; break;
    case 449: item.skill = 168; break;
    case 434:
        item.count = 2 + rnd(2) - rnd(2);
        item.has_charge() = true;
        break;
    case 428: item.param1 = 0; break;
    case 427: item.param2 = 7; break;
    case 426: item.param2 = 3; break;
    case 425: item.param2 = 6; break;
    case 424: item.param2 = 3; break;
    case 423: item.param2 = 4; break;
    case 422: item.param2 = 1; break;
    case 421: item.param2 = 1; break;
    case 420: item.param2 = 1; break;
    case 419: item.param2 = 1; break;
    case 418: item.param2 = 1; break;
    case 417: item.param2 = 1; break;
    case 412:
        item.count = 3 + rnd(3) - rnd(3);
        item.has_charge() = true;
        break;
    case 410:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 409: item.param1 = 5; break;
    case 408: item.param1 = 1; break;
    case 407: item.param1 = 2; break;
    case 406: item.param1 = 0; break;
    case 405: item.param1 = 3; break;
    case 404: item.param1 = 0; break;
    case 403: item.param1 = 3; break;
    case 402: item.param1 = 5; break;
    case 401: item.param1 = 4; break;
    case 400: item.param1 = 2; break;
    case 399: item.param1 = 1; break;
    case 397:
        item.count = 5 + rnd(5) - rnd(5);
        item.has_charge() = true;
        break;
    case 396:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 393: item.function = 3; break;
    case 391:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 387:
        item.count = 3 + rnd(3) - rnd(3);
        item.has_charge() = true;
        break;
    case 386:
        item.count = 3 + rnd(3) - rnd(3);
        item.has_charge() = true;
        break;
    case 385:
        item.count = 6 + rnd(6) - rnd(6);
        item.has_charge() = true;
        break;
    case 383:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 381:
        item.count = 3 + rnd(3) - rnd(3);
        item.has_charge() = true;
        break;
    case 380:
        item.count = 3 + rnd(3) - rnd(3);
        item.has_charge() = true;
        break;
    case 378:
        item.count = 5 + rnd(5) - rnd(5);
        item.has_charge() = true;
        break;
    case 377:
        item.count = 8 + rnd(8) - rnd(8);
        item.has_charge() = true;
        break;
    case 374:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 373:
        item.count = 3 + rnd(3) - rnd(3);
        item.has_charge() = true;
        break;
    case 371:
        item.count = 3 + rnd(3) - rnd(3);
        item.has_charge() = true;
        break;
    case 369:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 367:
        item.count = 3 + rnd(3) - rnd(3);
        item.has_charge() = true;
        break;
    case 366:
        item.count = 7 + rnd(7) - rnd(7);
        item.has_charge() = true;
        break;
    case 365:
        item.count = 5 + rnd(5) - rnd(5);
        item.has_charge() = true;
        break;
    case 360:
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
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 359:
        item.skill = 104;
        fixeditemenc(0) = 40;
        fixeditemenc(1) = 400;
        fixeditemenc(2) = 70056;
        fixeditemenc(3) = 400;
        fixeditemenc(4) = 20056;
        fixeditemenc(5) = 300;
        fixeditemenc(6) = 26;
        fixeditemenc(7) = 100;
        fixeditemenc(8) = 0;
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 358:
        item.skill = 105;
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
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 357:
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
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 356:
        item.skill = 103;
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
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 355:
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
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 354:
        item.param1 = 6000;
        item.param3 = 4;
        break;
    case 353:
        item.param1 = 6000;
        item.param3 = 4;
        break;
    case 352:
        item.param1 = 6000;
        item.param3 = 4;
        break;
    case 351:
        item.param1 = 6000;
        item.param3 = 4;
        break;
    case 350:
        item.param1 = 6000;
        item.param3 = 4;
        break;
    case 349:
        item.param1 = 6000;
        item.param3 = 4;
        break;
    case 348:
        item.param1 = 6000;
        item.param3 = 4;
        break;
    case 347:
        item.param1 = 6000;
        item.param3 = 4;
        break;
    case 346:
        item.param1 = 6000;
        item.param3 = 4;
        break;
    case 345:
        item.param1 = 6000;
        item.param3 = 4;
        break;
    case 344: item.param1 = 1; break;
    case 343: item.function = 22; break;
    case 342:
        item.function = 16;
        item.param1 = 60;
        break;
    case 334: item.function = 44; break;
    case 333: item.param2 = 3; break;
    case 330: item.function = 44; break;
    case 328:
        item.function = 17;
        item.param1 = 150;
        break;
    case 327: item.function = 44; break;
    case 325: item.param1 = 130; break;
    case 322: item.function = 19; break;
    case 319: item.param1 = 0; break;
    case 310: item.param1 = 130; break;
    case 309: item.function = 19; break;
    case 307: item.param1 = 130; break;
    case 306:
        item.function = 15;
        item.param1 = 200;
        break;
    case 305: item.param1 = 130; break;
    case 304: item.param1 = 100; break;
    case 303: item.param1 = 120; break;
    case 299: item.function = 19; break;
    case 297: item.param1 = 150; break;
    case 290:
        item.count = 1 + rnd(1) - rnd(1);
        item.has_charge() = true;
        break;
    case 289:
        item.count = 1 + rnd(1) - rnd(1);
        item.has_charge() = true;
        break;
    case 272:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 271:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 270:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 269:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 268:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 267:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 266: item.skill = 101; break;
    case 265:
        item.count = 3 + rnd(3) - rnd(3);
        item.has_charge() = true;
        break;
    case 264:
        item.count = 3 + rnd(3) - rnd(3);
        item.has_charge() = true;
        break;
    case 263:
        item.count = 3 + rnd(3) - rnd(3);
        item.has_charge() = true;
        break;
    case 261:
        item.param1 = 6000;
        item.param3 = 6;
        break;
    case 260:
        item.param1 = 7000;
        item.param3 = 240;
        break;
    case 259:
        item.param1 = 5000;
        item.param3 = 24;
        break;
    case 258: item.param2 = 3; break;
    case 257:
        item.count = 5 + rnd(5) - rnd(5);
        item.has_charge() = true;
        break;
    case 256:
        item.function = 15;
        item.param1 = 80;
        break;
    case 255:
        item.function = 15;
        item.param1 = 40;
        break;
    case 254:
        item.skill = 183;
        item.function = 17;
        item.param1 = 110;
        break;
    case 252:
        item.count = 2 + rnd(2) - rnd(2);
        item.has_charge() = true;
        break;
    case 251:
        item.count = 3 + rnd(3) - rnd(3);
        item.has_charge() = true;
        break;
    case 250:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 249:
        item.count = 5 + rnd(5) - rnd(5);
        item.has_charge() = true;
        break;
    case 248:
        item.count = 3 + rnd(3) - rnd(3);
        item.has_charge() = true;
        break;
    case 247:
        item.count = 2 + rnd(2) - rnd(2);
        item.has_charge() = true;
        break;
    case 246:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 235: item.skill = 104; break;
    case 234: item.skill = 102; break;
    case 233: item.param2 = 3; break;
    case 232: item.skill = 100; break;
    case 231: item.skill = 110; break;
    case 230: item.skill = 108; break;
    case 229: item.skill = 105; break;
    case 228: item.skill = 104; break;
    case 227: item.skill = 103; break;
    case 226: item.skill = 102; break;
    case 225: item.skill = 101; break;
    case 224: item.skill = 100; break;
    case 223:
        item.function = 15;
        item.param1 = 60;
        break;
    case 219: item.function = 46; break;
    case 213: item.skill = 104; break;
    case 212: item.skill = 105; break;
    case 211:
        item.skill = 107;
        fixeditemenc(0) = 80025;
        fixeditemenc(1) = 100;
        fixeditemenc(2) = 0;
        break;
    case 210: item.skill = 111; break;
    case 207:
        item.skill = 108;
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
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 206:
        item.skill = 101;
        fixeditemenc(0) = 80000;
        fixeditemenc(1) = 200;
        fixeditemenc(2) = 70052;
        fixeditemenc(3) = 300;
        fixeditemenc(4) = 20052;
        fixeditemenc(5) = 250;
        fixeditemenc(6) = 30172;
        fixeditemenc(7) = 350;
        fixeditemenc(8) = 0;
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 204:
        item.param1 = 1000;
        item.param3 = 4;
        break;
    case 203:
        item.count = 8 + rnd(8) - rnd(8);
        item.has_charge() = true;
        break;
    case 202:
        item.count = 9 + rnd(9) - rnd(9);
        item.has_charge() = true;
        break;
    case 201:
        item.param1 = 2000;
        item.param3 = 2;
        break;
    case 200:
        item.param1 = 2000;
        item.param3 = 72;
        break;
    case 199:
        item.param1 = 2000;
        item.param3 = 72;
        break;
    case 198:
        item.param1 = 2000;
        item.param3 = 72;
        break;
    case 197:
        item.param1 = 3000;
        item.param3 = 12;
        break;
    case 196:
        item.param1 = 3000;
        item.param3 = 8;
        break;
    case 195:
        item.param1 = 3000;
        item.param3 = 12;
        break;
    case 194:
        item.param1 = 3000;
        item.param3 = 8;
        break;
    case 193: item.param1 = 2000; break;
    case 192:
        item.param1 = 3000;
        item.param3 = 16;
        break;
    case 191: item.param1 = 4000; break;
    case 190: item.param1 = 2000; break;
    case 188:
        item.param1 = 2000;
        item.param3 = 72;
        break;
    case 187: item.param1 = 2000; break;
    case 186:
        item.param1 = 2000;
        item.param3 = 72;
        break;
    case 185:
        item.param1 = 2000;
        item.param3 = 72;
        break;
    case 184:
        item.param1 = 3000;
        item.param3 = 8;
        break;
    case 183:
        item.param1 = 3000;
        item.param3 = 16;
        break;
    case 182:
        item.param1 = 3000;
        item.param3 = 12;
        break;
    case 181:
        item.param1 = 3000;
        item.param3 = 16;
        break;
    case 180:
        item.param1 = 3000;
        item.param3 = 16;
        break;
    case 179:
        item.param1 = 2000;
        item.param3 = 48;
        break;
    case 178:
        item.param1 = 3000;
        item.param3 = 72;
        break;
    case 177:
        item.param1 = 3000;
        item.param3 = 72;
        break;
    case 176:
        item.count = 8 + rnd(8) - rnd(8);
        item.has_charge() = true;
        break;
    case 175:
        item.count = 10 + rnd(10) - rnd(10);
        item.has_charge() = true;
        break;
    case 174: item.param1 = 110; break;
    case 173: item.param2 = 100; break;
    case 161: item.function = 1; break;
    case 160: item.function = 4; break;
    case 155:
        item.function = 15;
        item.param1 = 100;
        break;
    case 154:
        item.function = 15;
        item.param1 = 100;
        break;
    case 153:
        item.function = 15;
        item.param1 = 100;
        break;
    case 142:
        item.function = 15;
        item.param1 = 200;
        break;
    case 127: item.function = 2; break;
    case 125:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 123:
        item.count = 10 + rnd(10) - rnd(10);
        item.has_charge() = true;
        break;
    case 122:
        item.count = 8 + rnd(8) - rnd(8);
        item.has_charge() = true;
        break;
    case 121:
        item.count = 8 + rnd(8) - rnd(8);
        item.has_charge() = true;
        break;
    case 120:
        item.count = 10 + rnd(10) - rnd(10);
        item.has_charge() = true;
        break;
    case 119:
        item.count = 8 + rnd(8) - rnd(8);
        item.has_charge() = true;
        break;
    case 118:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 116:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 112:
        item.function = 15;
        item.param1 = 150;
        break;
    case 109: item.param2 = 100; break;
    case 102: item.function = 44; break;
    case 101: item.function = 44; break;
    case 92: item.function = 44; break;
    case 88:
        item.skill = 183;
        item.function = 17;
        item.param1 = 200;
        break;
    case 81: item.function = 44; break;
    case 80: item.param1 = 100; break;
    case 77: item.function = 44; break;
    case 73:
        item.skill = 100;
        fixeditemenc(0) = 37;
        fixeditemenc(1) = 100;
        fixeditemenc(2) = 0;
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 64:
        item.skill = 100;
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
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 63:
        item.skill = 107;
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
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 62: item.skill = 110; break;
    case 61: item.skill = 108; break;
    case 60: item.skill = 110; break;
    case 59: item.skill = 168; break;
    case 58: item.skill = 108; break;
    case 57:
        item.skill = 100;
        fixeditemenc(0) = 39;
        fixeditemenc(1) = 400;
        fixeditemenc(2) = 25;
        fixeditemenc(3) = 100;
        fixeditemenc(4) = 10010;
        fixeditemenc(5) = 300;
        fixeditemenc(6) = 20058;
        fixeditemenc(7) = 200;
        fixeditemenc(8) = 0;
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 56:
        item.skill = 100;
        fixeditemenc(0) = 40;
        fixeditemenc(1) = 300;
        fixeditemenc(2) = 70058;
        fixeditemenc(3) = 400;
        fixeditemenc(4) = 10018;
        fixeditemenc(5) = 300;
        fixeditemenc(6) = 24;
        fixeditemenc(7) = 100;
        fixeditemenc(8) = 0;
        item.is_precious() = true;
        item.difficulty_of_identification = 500;
        fixlv = Quality::special;
        break;
    case 34:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 33:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 32:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 25: item.param1 = 2; break;
    case 24: item.param1 = 0; break;
    case 23: item.param1 = 1; break;
    case 22:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 21:
        item.count = 4 + rnd(4) - rnd(4);
        item.has_charge() = true;
        break;
    case 20:
        item.count = 5 + rnd(5) - rnd(5);
        item.has_charge() = true;
        break;
    case 19:
        item.count = 12 + rnd(12) - rnd(12);
        item.has_charge() = true;
        break;
    case 18:
        item.count = 8 + rnd(8) - rnd(8);
        item.has_charge() = true;
        break;
    case 6:
        fixeditemenc(0) = 33;
        fixeditemenc(1) = 100;
        fixeditemenc(2) = 0;
        break;
    case 4: item.skill = 103; break;
    case 3: item.skill = 102; break;
    case 2: item.skill = 101; break;
    case 1: item.skill = 100; break;
    default: break;
    }
}



void item_db_on_read(Item& item, int legacy_id)
{
    switch (legacy_id)
    {
    case 783: decode_book(); break;
    case 747: read_normal_book(); break;
    case 742: read_normal_book(); break;
    case 737:
        efid = 1145;
        efp = 100;
        read_scroll();
        break;
    case 732:
        efid = 464;
        efp = 100;
        decode_book();
        break;
    case 731:
        efid = 463;
        efp = 100;
        decode_book();
        break;
    case 712: efid = 1115; break;
    case 710:
        efid = 462;
        efp = 100;
        decode_book();
        break;
    case 709:
        efid = 462;
        efp = 1500;
        read_scroll();
        break;
    case 708:
        efid = 461;
        efp = 2500;
        read_scroll();
        break;
    case 700:
        menucycle = 1;
        show_city_chart();
        break;
    case 697:
        efid = 459;
        efp = 100;
        decode_book();
        break;
    case 696:
        efid = 460;
        efp = 100;
        decode_book();
        break;
    case 687: decode_book(); break;
    case 668: read_normal_book(); break;
    case 660:
        efid = 418;
        efp = 100;
        decode_book();
        break;
    case 638:
        efid = 1141;
        efp = 100;
        read_scroll();
        break;
    case 632:
        efid = 1140;
        efp = 150;
        read_scroll();
        break;
    case 628:
        efid = 458;
        efp = 100;
        decode_book();
        break;
    case 624:
        efid = 1137;
        efp = 100;
        read_scroll();
        break;
    case 623:
        efid = 1138;
        efp = 100;
        read_scroll();
        break;
    case 621:
        efid = 1136;
        efp = 100;
        read_scroll();
        break;
    case 582:
        efid = 457;
        efp = 100;
        decode_book();
        break;
    case 572: efid = 1115; break;
    case 569:
        efid = 456;
        efp = 100;
        decode_book();
        break;
    case 564:
        efid = 455;
        efp = 100;
        decode_book();
        break;
    case 563: read_normal_book(); break;
    case 550:
        efid = 405;
        efp = 100;
        decode_book();
        break;
    case 549:
        efid = 404;
        efp = 400;
        read_scroll();
        break;
    case 548:
        efid = 404;
        efp = 100;
        decode_book();
        break;
    case 546:
        efid = 438;
        efp = 100;
        decode_book();
        break;
    case 543: efid = 1115; break;
    case 542: efid = 1115; break;
    case 522: efid = 1115; break;
    case 521: efid = 1115; break;
    case 515:
        efid = 1129;
        efp = 300;
        read_scroll();
        break;
    case 511:
        efid = 1128;
        efp = item.param1;
        read_scroll();
        break;
    case 509:
        efid = 1125;
        efp = 400;
        read_scroll();
        break;
    case 508:
        efid = 1125;
        efp = 200;
        read_scroll();
        break;
    case 507:
        efid = 1124;
        efp = 400;
        read_scroll();
        break;
    case 506:
        efid = 1124;
        efp = 200;
        read_scroll();
        break;
    case 505:
        efid = 1123;
        efp = 100;
        read_scroll();
        break;
    case 502:
        efid = 1127;
        efp = 350;
        read_scroll();
        break;
    case 501:
        efid = 1127;
        efp = 180;
        read_scroll();
        break;
    case 500:
        efid = 1127;
        efp = 10;
        read_scroll();
        break;
    case 484:
        efid = 436;
        efp = 100;
        decode_book();
        break;
    case 481:
        efid = 435;
        efp = 100;
        decode_book();
        break;
    case 479:
        efid = 1122;
        efp = 100;
        read_scroll();
        break;
    case 434:
        efid = 454;
        efp = 100;
        decode_book();
        break;
    case 431:
        efid = 1107;
        efp = 300;
        read_scroll();
        break;
    case 430:
        efid = 1119;
        efp = 500;
        read_scroll();
        break;
    case 411:
        efid = 430;
        efp = 500;
        read_scroll();
        break;
    case 410:
        efid = 430;
        efp = 100;
        decode_book();
        break;
    case 398:
        efid = 453;
        efp = 250;
        read_scroll();
        break;
    case 397:
        efid = 453;
        efp = 100;
        decode_book();
        break;
    case 396:
        efid = 452;
        efp = 100;
        decode_book();
        break;
    case 395:
        efid = 1117;
        efp = 250;
        read_scroll();
        break;
    case 390:
        efid = 621;
        efp = 250;
        read_scroll();
        break;
    case 389:
        efid = 407;
        efp = 300;
        read_scroll();
        break;
    case 388:
        efid = 406;
        efp = 300;
        read_scroll();
        break;
    case 387:
        efid = 407;
        efp = 100;
        decode_book();
        break;
    case 386:
        efid = 406;
        efp = 100;
        decode_book();
        break;
    case 384:
        efid = 451;
        efp = 250;
        read_scroll();
        break;
    case 383:
        efid = 451;
        efp = 100;
        decode_book();
        break;
    case 381:
        efid = 450;
        efp = 100;
        decode_book();
        break;
    case 380:
        efid = 449;
        efp = 100;
        decode_book();
        break;
    case 378:
        efid = 448;
        efp = 100;
        decode_book();
        break;
    case 374:
        efid = 447;
        efp = 100;
        decode_book();
        break;
    case 373:
        efid = 446;
        efp = 100;
        decode_book();
        break;
    case 371:
        efid = 445;
        efp = 100;
        decode_book();
        break;
    case 369:
        efid = 444;
        efp = 100;
        decode_book();
        break;
    case 367:
        efid = 443;
        efp = 100;
        decode_book();
        break;
    case 365:
        efid = 442;
        efp = 100;
        decode_book();
        break;
    case 363:
        efid = 412;
        efp = 2500;
        read_scroll();
        break;
    case 362:
        efid = 411;
        efp = 2000;
        read_scroll();
        break;
    case 344: efid = 1115; break;
    case 289:
        efid = 441;
        efp = 100;
        decode_book();
        break;
    case 288:
        efid = 1114;
        efp = 100;
        read_scroll();
        break;
    case 272:
        efid = 433;
        efp = 100;
        decode_book();
        break;
    case 271:
        efid = 434;
        efp = 100;
        decode_book();
        break;
    case 270:
        efid = 432;
        efp = 100;
        decode_book();
        break;
    case 269:
        efid = 431;
        efp = 100;
        decode_book();
        break;
    case 268:
        efid = 423;
        efp = 100;
        decode_book();
        break;
    case 267:
        efid = 422;
        efp = 100;
        decode_book();
        break;
    case 265:
        efid = 416;
        efp = 100;
        decode_book();
        break;
    case 264:
        efid = 417;
        efp = 100;
        decode_book();
        break;
    case 263:
        efid = 415;
        efp = 100;
        decode_book();
        break;
    case 257:
        efid = 414;
        efp = 100;
        decode_book();
        break;
    case 252:
        efid = 403;
        efp = 100;
        decode_book();
        break;
    case 251:
        efid = 402;
        efp = 100;
        decode_book();
        break;
    case 250:
        efid = 401;
        efp = 100;
        decode_book();
        break;
    case 249:
        efid = 400;
        efp = 100;
        decode_book();
        break;
    case 248:
        efid = 428;
        efp = 100;
        decode_book();
        break;
    case 247:
        efid = 413;
        efp = 100;
        decode_book();
        break;
    case 246:
        efid = 429;
        efp = 100;
        decode_book();
        break;
    case 245:
        efid = 408;
        efp = 100;
        read_scroll();
        break;
    case 244:
        efid = 1104;
        efp = 100;
        read_scroll();
        break;
    case 243:
        efid = 1105;
        efp = 100;
        read_scroll();
        break;
    case 242:
        efid = 429;
        efp = 500;
        read_scroll();
        break;
    case 236:
        efid = 428;
        efp = 100;
        read_scroll();
        break;
    case 209:
        efid = 412;
        efp = 100;
        read_scroll();
        break;
    case 118:
        efid = 424;
        efp = 100;
        decode_book();
        break;
    case 116:
        efid = 410;
        efp = 100;
        decode_book();
        break;
    case 34:
        efid = 421;
        efp = 100;
        decode_book();
        break;
    case 33:
        efid = 420;
        efp = 100;
        decode_book();
        break;
    case 32:
        efid = 419;
        efp = 100;
        decode_book();
        break;
    case 25:
        item.param1 = 2;
        read_normal_book();
        break;
    case 24: read_normal_book(); break;
    case 23:
        item.param1 = 1;
        read_normal_book();
        break;
    case 22:
        efid = 412;
        efp = 100;
        decode_book();
        break;
    case 21:
        efid = 411;
        efp = 100;
        decode_book();
        break;
    case 20:
        efid = 408;
        efp = 100;
        decode_book();
        break;
    case 17:
        efid = 458;
        efp = 300;
        read_scroll();
        break;
    case 16:
        efid = 408;
        efp = 100;
        read_scroll();
        break;
    case 15:
        efid = 413;
        efp = 100;
        read_scroll();
        break;
    case 14:
        efid = 411;
        efp = 100;
        read_scroll();
        break;
    default: break;
    }
}



void item_db_on_zap(Item& item, int legacy_id)
{
    (void)item;

    switch (legacy_id)
    {
    case 581:
        efid = 457;
        efp = 100;
        break;
    case 570:
        efid = 456;
        efp = 100;
        break;
    case 565:
        efid = 455;
        efp = 100;
        break;
    case 551:
        efid = 405;
        efp = 100;
        break;
    case 545:
        efid = 438;
        efp = 100;
        break;
    case 518:
        efid = 1132;
        efp = 100;
        break;
    case 517:
        efid = 628;
        efp = 100;
        break;
    case 485:
        efid = 436;
        efp = 100;
        break;
    case 480:
        efid = 435;
        efp = 100;
        break;
    case 412:
        efid = 412;
        efp = 100;
        break;
    case 391:
        efid = 621;
        efp = 100;
        break;
    case 385:
        efid = 407;
        efp = 100;
        break;
    case 377:
        efid = 446;
        efp = 100;
        break;
    case 366:
        efid = 443;
        efp = 100;
        break;
    case 290:
        efid = 441;
        efp = 100;
        break;
    case 203:
        efid = 401;
        efp = 100;
        break;
    case 202:
        efid = 429;
        efp = 100;
        break;
    case 176:
        efid = 447;
        efp = 100;
        break;
    case 175:
        efid = 421;
        efp = 100;
        break;
    case 125:
        efid = 402;
        efp = 100;
        break;
    case 123:
        efid = 420;
        efp = 100;
        break;
    case 122:
        efid = 419;
        efp = 100;
        break;
    case 121:
        efid = 424;
        efp = 100;
        break;
    case 120:
        efid = 414;
        efp = 100;
        break;
    case 119:
        efid = 400;
        efp = 100;
        break;
    case 19:
        efid = 409;
        efp = 100;
        break;
    case 18:
        efid = 411;
        efp = 100;
        break;
    default: break;
    }
}



void item_db_on_drink(Item& item, int legacy_id)
{
    (void)item;

    switch (legacy_id)
    {
    case 771:
        efid = 1147;
        efp = 100;
        drink_potion();
        break;
    case 770:
        efid = 1146;
        efp = 100;
        drink_potion();
        break;
    case 736:
        efid = 1116;
        efp = 250;
        drink_potion();
        break;
    case 711:
        efid = 1144;
        efp = 100;
        drink_potion();
        break;
    case 706:
        efid = 1143;
        efp = 100;
        drink_potion();
        break;
    case 704:
        efid = 1130;
        efp = 100;
        drink_potion();
        break;
    case 698:
        efid = 1142;
        efp = 100;
        drink_potion();
        break;
    case 650: drink_well(); break;
    case 626:
        efid = 1139;
        efp = 500;
        drink_potion();
        break;
    case 620:
        efid = 1135;
        efp = 100;
        drink_potion();
        break;
    case 602: drink_well(); break;
    case 587:
        efid = 1103;
        efp = 100;
        drink_potion();
        break;
    case 577:
        efid = 1133;
        efp = 100;
        drink_potion();
        break;
    case 574:
        efid = 1101;
        efp = 100;
        drink_potion();
        break;
    case 566:
        efid = 1116;
        efp = 250;
        drink_potion();
        break;
    case 559:
        efid = 1131;
        efp = 200;
        drink_potion();
        break;
    case 519:
        efid = 1108;
        efp = 150;
        drink_potion();
        break;
    case 516:
        efid = 1103;
        efp = 100;
        drink_potion();
        break;
    case 433:
        efid = 1121;
        efp = 200;
        drink_potion();
        break;
    case 432:
        efid = 454;
        efp = 100;
        drink_potion();
        break;
    case 429:
        efid = 1118;
        efp = 100;
        drink_potion();
        break;
    case 392:
        efid = 1116;
        efp = 100;
        drink_potion();
        break;
    case 382:
        efid = 449;
        efp = 250;
        drink_potion();
        break;
    case 379:
        efid = 448;
        efp = 250;
        drink_potion();
        break;
    case 376:
        efid = 447;
        efp = 400;
        drink_potion();
        break;
    case 375:
        efid = 446;
        efp = 250;
        drink_potion();
        break;
    case 372:
        efid = 445;
        efp = 250;
        drink_potion();
        break;
    case 370:
        efid = 444;
        efp = 300;
        drink_potion();
        break;
    case 368:
        efid = 443;
        efp = 400;
        drink_potion();
        break;
    case 364:
        efid = 442;
        efp = 200;
        drink_potion();
        break;
    case 287:
        efid = 1113;
        efp = 100;
        drink_potion();
        break;
    case 286:
        efid = 440;
        efp = 100;
        drink_potion();
        break;
    case 285:
        efid = 439;
        efp = 100;
        drink_potion();
        break;
    case 262:
        efid = 1108;
        efp = 200;
        drink_potion();
        break;
    case 253:
        efid = 1102;
        efp = 200;
        drink_potion();
        break;
    case 205:
        efid = 1102;
        efp = 500;
        drink_potion();
        break;
    case 173: drink_well(); break;
    case 109: drink_well(); break;
    case 76:
        efid = 403;
        efp = 100;
        drink_potion();
        break;
    case 75:
        efid = 402;
        efp = 300;
        drink_potion();
        break;
    case 74:
        efid = 402;
        efp = 100;
        drink_potion();
        break;
    case 72:
        efid = 401;
        efp = 400;
        drink_potion();
        break;
    case 71:
        efid = 401;
        efp = 300;
        drink_potion();
        break;
    case 70:
        efid = 401;
        efp = 100;
        drink_potion();
        break;
    case 69:
        efid = 400;
        efp = 300;
        drink_potion();
        break;
    case 68:
        efid = 400;
        efp = 100;
        drink_potion();
        break;
    case 31:
        efid = 1102;
        efp = 300;
        drink_potion();
        break;
    case 30:
        efid = 1112;
        efp = 200;
        drink_potion();
        break;
    case 29:
        efid = 1110;
        efp = 200;
        drink_potion();
        break;
    case 28:
        efid = 1109;
        efp = 150;
        drink_potion();
        break;
    case 27:
        efid = 1111;
        efp = 200;
        drink_potion();
        break;
    case 26:
        efid = 1130;
        drink_potion();
        break;
    default: break;
    }
}

} // namespace elona
