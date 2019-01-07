#include "character_id.hpp"



namespace
{

std::string _get_new_id_by_legacy_id(int legacy_id)
{
    switch (legacy_id)
    {
    case 0: return "core.bug";
    case 1: return "core.shopkeeper";
    case 2: return "core.zeome";
    case 3: return "core.putit";
    case 4: return "core.red_putit";
    case 5: return "core.rabbit";
    case 6: return "core.snail";
    case 7: return "core.fallen_soldier";
    case 8: return "core.mercenary";
    case 9: return "core.beggar";
    case 10: return "core.wild_sheep";
    case 11: return "core.flying_frog";
    case 12: return "core.gangster";
    case 13: return "core.kobold";
    case 14: return "core.centipede";
    case 15: return "core.mushroom";
    case 16: return "core.citizen";
    case 17: return "core.orc";
    case 18: return "core.warrior_of_elea";
    case 19: return "core.mandrake";
    case 20: return "core.orc_warrior";
    case 21: return "core.zombie";
    case 22: return "core.beetle";
    case 23: return "core.orphe";
    case 24: return "core.wizard_of_elea";
    case 25: return "core.goda";
    case 26: return "core.mad_scientist";
    case 27: return "core.isca";
    case 28: return "core.whom_dwell_in_the_vanity";
    case 29: return "core.loyter";
    case 30: return "core.miches";
    case 31: return "core.shena";
    case 32: return "core.dungeon_cleaner";
    case 33: return "core.larnneire";
    case 34: return "core.lomias";
    case 35: return "core.town_child";
    case 36: return "core.old_person";
    case 37: return "core.at";
    case 38: return "core.elder";
    case 39: return "core.citizen2";
    case 40: return "core.trainer";
    case 41: return "core.wizard";
    case 42: return "core.bat";
    case 43: return "core.vampire_bat";
    case 44: return "core.dragon_bat";
    case 45: return "core.fire_ent";
    case 46: return "core.ice_ent";
    case 47: return "core.lich";
    case 48: return "core.master_lich";
    case 49: return "core.demi_lich";
    case 50: return "core.hound";
    case 51: return "core.fire_hound";
    case 52: return "core.ice_hound";
    case 53: return "core.lightning_hound";
    case 54: return "core.dark_hound";
    case 55: return "core.illusion_hound";
    case 56: return "core.nerve_hound";
    case 57: return "core.poison_hound";
    case 58: return "core.sound_hound";
    case 59: return "core.nether_hound";
    case 60: return "core.chaos_hound";
    case 61: return "core.giant_squirrel";
    case 62: return "core.killer_squirrel";
    case 63: return "core.grudge";
    case 64: return "core.hungry_demon";
    case 65: return "core.electric_cloud";
    case 66: return "core.chaos_cloud";
    case 67: return "core.floating_eye";
    case 68: return "core.wyvern";
    case 69: return "core.informer";
    case 70: return "core.bartender";
    case 71: return "core.sailor";
    case 72: return "core.captain";
    case 73: return "core.arena_master";
    case 74: return "core.healer";
    case 75: return "core.warrior";
    case 76: return "core.guard_port_kapul";
    case 77: return "core.guard";
    case 78: return "core.puppet";
    case 79: return "core.stersha";
    case 80: return "core.xabi";
    case 81: return "core.wasp";
    case 82: return "core.red_wasp";
    case 83: return "core.cyclops";
    case 84: return "core.titan";
    case 85: return "core.imp";
    case 86: return "core.nether_imp";
    case 87: return "core.chaos_imp";
    case 88: return "core.hand_of_the_dead";
    case 89: return "core.hand_of_the_chaos";
    case 90: return "core.hand_of_the_murderer";
    case 91: return "core.ghost";
    case 92: return "core.nymph";
    case 93: return "core.man_eater_flower";
    case 94: return "core.chaos_flower";
    case 95: return "core.cobra";
    case 96: return "core.king_cobra";
    case 97: return "core.fire_drake";
    case 98: return "core.ice_drake";
    case 99: return "core.lesser_mummy";
    case 100: return "core.mummy";
    case 101: return "core.greater_mummy";
    case 102: return "core.goblin";
    case 103: return "core.goblin_warrior";
    case 104: return "core.goblin_shaman";
    case 105: return "core.goblin_wizard";
    case 106: return "core.red_baptist";
    case 107: return "core.blue_baptist";
    case 108: return "core.brown_bear";
    case 109: return "core.grizzly";
    case 110: return "core.living_armor";
    case 111: return "core.steel_mass";
    case 112: return "core.golden_armor";
    case 113: return "core.death_armor";
    case 114: return "core.medusa";
    case 115: return "core.euryale";
    case 116: return "core.stheno";
    case 117: return "core.cupid_of_love";
    case 118: return "core.lesser_phantom";
    case 119: return "core.harpy";
    case 120: return "core.green_dragon";
    case 121: return "core.red_dragon";
    case 122: return "core.white_dragon";
    case 123: return "core.elec_dragon";
    case 124: return "core.nether_dragon";
    case 125: return "core.chaos_dragon";
    case 126: return "core.cerberus";
    case 127: return "core.spider";
    case 128: return "core.black_widow";
    case 129: return "core.paralyzer";
    case 130: return "core.tarantula";
    case 131: return "core.blood_spider";
    case 132: return "core.wooden_golem";
    case 133: return "core.stone_golem";
    case 134: return "core.steel_golem";
    case 135: return "core.golden_golem";
    case 136: return "core.mithril_golem";
    case 137: return "core.sky_golem";
    case 138: return "core.adamantium_golem";
    case 139: return "core.slan";
    case 140: return "core.vesda";
    case 141: return "core.issizzle";
    case 142: return "core.erystia";
    case 143: return "core.wynan";
    case 144: return "core.quruiza";
    case 145: return "core.corgon";
    case 146: return "core.karam";
    case 147: return "core.fire_crab";
    case 148: return "core.fire_centipede";
    case 149: return "core.cultist_of_fire";
    case 150: return "core.skeleton_warrior";
    case 151: return "core.skeleton_berserker";
    case 152: return "core.missionary_of_darkness";
    case 153: return "core.pawn";
    case 154: return "core.rook";
    case 155: return "core.bishop";
    case 156: return "core.knight";
    case 157: return "core.queen";
    case 158: return "core.king";
    case 159: return "core.mercenary_warrior";
    case 160: return "core.mercenary_archer";
    case 161: return "core.mercenary_wizard";
    case 162: return "core.yerles_machine_infantry";
    case 163: return "core.rock_thrower";
    case 164: return "core.cat";
    case 165: return "core.dog";
    case 166: return "core.little_girl";
    case 167: return "core.rat";
    case 168: return "core.hermit_crab";
    case 169: return "core.slime";
    case 170: return "core.public_performer";
    case 171: return "core.citizen_of_cyber_dome";
    case 172: return "core.citizen_of_cyber_dome2";
    case 173: return "core.sales_person";
    case 174: return "core.punk";
    case 175: return "core.frisia";
    case 176: return "core.younger_sister";
    case 177: return "core.utima";
    case 178: return "core.azzrssil";
    case 179: return "core.master_of_pet_arena";
    case 180: return "core.twintail";
    case 181: return "core.silver_wolf";
    case 182: return "core.nurse";
    case 183: return "core.rich_person";
    case 184: return "core.noble_child";
    case 185: return "core.tourist";
    case 186: return "core.blade";
    case 187: return "core.blade_alpha";
    case 188: return "core.blade_omega";
    case 189: return "core.deformed_eye";
    case 190: return "core.impure_eye";
    case 191: return "core.wisp";
    case 192: return "core.hedgehog";
    case 193: return "core.shining_hedgehog";
    case 194: return "core.acid_slime";
    case 195: return "core.chicken";
    case 196: return "core.pumpkin";
    case 197: return "core.greater_pumpkin";
    case 198: return "core.halloween_nightmare";
    case 199: return "core.stalker";
    case 200: return "core.shadow_stalker";
    case 201: return "core.puppy";
    case 202: return "core.ebon";
    case 203: return "core.moyer_the_crooked";
    case 204: return "core.palmian_elite_soldier";
    case 205: return "core.maid";
    case 206: return "core.nun";
    case 207: return "core.ebon2";
    case 208: return "core.garokk";
    case 209: return "core.miral";
    case 210: return "core.younger_cat_sister";
    case 211: return "core.young_lady";
    case 212: return "core.test_subject";
    case 213: return "core.gwen";
    case 214: return "core.thief";
    case 215: return "core.robber";
    case 216: return "core.great_race_of_yith";
    case 217: return "core.master_thief";
    case 218: return "core.shub_niggurath";
    case 219: return "core.gagu";
    case 220: return "core.spiral_king";
    case 221: return "core.pael";
    case 222: return "core.lily";
    case 223: return "core.raphael";
    case 224: return "core.ainc";
    case 225: return "core.poppy";
    case 226: return "core.rilian";
    case 227: return "core.tam";
    case 228: return "core.carbuncle";
    case 229: return "core.lion";
    case 230: return "core.cacy";
    case 231: return "core.gilbert_the_colonel";
    case 232: return "core.yerles_self_propelled_gun";
    case 233: return "core.juere_infantry";
    case 234: return "core.yerles_elite_machine_infantry";
    case 235: return "core.juere_swordman";
    case 236: return "core.yeek";
    case 237: return "core.kamikaze_yeek";
    case 238: return "core.yeek_warrior";
    case 239: return "core.hot_spring_maniac";
    case 240: return "core.master_yeek";
    case 241: return "core.yeek_archer";
    case 242: return "core.rodlob";
    case 243: return "core.arnord";
    case 244: return "core.kamikaze_samurai";
    case 245: return "core.bomb_rock";
    case 246: return "core.silver_cat";
    case 247: return "core.mia";
    case 248: return "core.tyrannosaurus";
    case 249: return "core.younger_sister_of_mansion";
    case 250: return "core.fairy";
    case 251: return "core.troll";
    case 252: return "core.renton";
    case 253: return "core.marks";
    case 254: return "core.ancient_coffin";
    case 255: return "core.scorpion";
    case 256: return "core.king_scorpion";
    case 257: return "core.tuwen";
    case 258: return "core.iron_maiden";
    case 259: return "core.noel";
    case 260: return "core.black_cat";
    case 261: return "core.cute_fairy";
    case 262: return "core.android";
    case 263: return "core.black_angel";
    case 264: return "core.exile";
    case 265: return "core.golden_knight";
    case 266: return "core.defender";
    case 267: return "core.lame_horse";
    case 268: return "core.yowyn_horse";
    case 269: return "core.farmer";
    case 270: return "core.sister";
    case 271: return "core.rogue";
    case 272: return "core.artist";
    case 273: return "core.miner";
    case 274: return "core.noble";
    case 275: return "core.noyel_horse";
    case 276: return "core.wild_horse";
    case 277: return "core.wild_horse2";
    case 278: return "core.mutant";
    case 279: return "core.icolle";
    case 280: return "core.balzak";
    case 281: return "core.lizard_man";
    case 282: return "core.minotaur";
    case 283: return "core.spore_mushroom";
    case 284: return "core.chaos_mushroom";
    case 285: return "core.blue_bubble";
    case 286: return "core.bubble";
    case 287: return "core.mass_monster";
    case 288: return "core.revlus";
    case 289: return "core.mage_guild_member";
    case 290: return "core.lexus";
    case 291: return "core.fray";
    case 292: return "core.sin";
    case 293: return "core.thief_guild_member";
    case 294: return "core.abyss";
    case 295: return "core.fighter_guild_member";
    case 296: return "core.minotaur_magician";
    case 297: return "core.doria";
    case 298: return "core.minotaur_boxer";
    case 299: return "core.minotaur_king";
    case 300: return "core.ungaga";
    case 301: return "core.conery";
    case 302: return "core.rogue_boss";
    case 303: return "core.rogue_warrior";
    case 304: return "core.rogue_archer";
    case 305: return "core.rogue_wizard";
    case 306: return "core.lulwy";
    case 307: return "core.executioner";
    case 308: return "core.messenger_of_death";
    case 309: return "core.asura";
    case 310: return "core.mitra";
    case 311: return "core.varuna";
    case 312: return "core.hungry_sea_lion";
    case 313: return "core.super_hungry_sea_lion";
    case 314: return "core.death_gaze";
    case 315: return "core.chaos_eye";
    case 316: return "core.mad_gaze";
    case 317: return "core.silver_eyed_witch";
    case 318: return "core.big_daddy";
    case 319: return "core.little_sister";
    case 320: return "core.cleaner";
    case 321: return "core.hard_gay";
    case 322: return "core.strange_scientist";
    case 323: return "core.shade";
    case 324: return "core.quickling";
    case 325: return "core.quickling_archer";
    case 326: return "core.bard";
    case 327: return "core.cube";
    case 328: return "core.silver_bell";
    case 329: return "core.gold_bell";
    case 330: return "core.alien";
    case 331: return "core.ehekatl";
    case 332: return "core.stray_cat";
    case 333: return "core.guild_trainer";
    case 334: return "core.mysterious_producer";
    case 335: return "core.prostitute";
    case 336: return "core.god_inside_ehekatl";
    case 337: return "core.prisoner";
    case 338: return "core.opatos";
    case 339: return "core.kumiromi";
    case 340: return "core._test";
    case 341: return "core.mine_dog";
    case 342: return "core.mani";
    case 343: return "core.user";
    case 344: return "core.mammoth";
    case 345: return "core.kaneda_bike";
    case 346: return "core.cub";
    case 347: return "core.fanatic";
    case 348: return "core.part_time_worker";
    case 349: return "core.holy_beast";
    case 350: return "core.festival_tourist";
    case 351: return "core.the_leopard_warrior";
    case 352: return "core.silvia";
    case 353: return "core.caravan_master";
    default: assert(0); return "";
    }
}



int _get_old_id_by_new_id(const std::string& id)
{
    if (id == "core.bug")
        return 0;
    else if (id == "core.shopkeeper")
        return 1;
    else if (id == "core.zeome")
        return 2;
    else if (id == "core.putit")
        return 3;
    else if (id == "core.red_putit")
        return 4;
    else if (id == "core.rabbit")
        return 5;
    else if (id == "core.snail")
        return 6;
    else if (id == "core.fallen_soldier")
        return 7;
    else if (id == "core.mercenary")
        return 8;
    else if (id == "core.beggar")
        return 9;
    else if (id == "core.wild_sheep")
        return 10;
    else if (id == "core.flying_frog")
        return 11;
    else if (id == "core.gangster")
        return 12;
    else if (id == "core.kobold")
        return 13;
    else if (id == "core.centipede")
        return 14;
    else if (id == "core.mushroom")
        return 15;
    else if (id == "core.citizen")
        return 16;
    else if (id == "core.orc")
        return 17;
    else if (id == "core.warrior_of_elea")
        return 18;
    else if (id == "core.mandrake")
        return 19;
    else if (id == "core.orc_warrior")
        return 20;
    else if (id == "core.zombie")
        return 21;
    else if (id == "core.beetle")
        return 22;
    else if (id == "core.orphe")
        return 23;
    else if (id == "core.wizard_of_elea")
        return 24;
    else if (id == "core.goda")
        return 25;
    else if (id == "core.mad_scientist")
        return 26;
    else if (id == "core.isca")
        return 27;
    else if (id == "core.whom_dwell_in_the_vanity")
        return 28;
    else if (id == "core.loyter")
        return 29;
    else if (id == "core.miches")
        return 30;
    else if (id == "core.shena")
        return 31;
    else if (id == "core.dungeon_cleaner")
        return 32;
    else if (id == "core.larnneire")
        return 33;
    else if (id == "core.lomias")
        return 34;
    else if (id == "core.town_child")
        return 35;
    else if (id == "core.old_person")
        return 36;
    else if (id == "core.at")
        return 37;
    else if (id == "core.elder")
        return 38;
    else if (id == "core.citizen2")
        return 39;
    else if (id == "core.trainer")
        return 40;
    else if (id == "core.wizard")
        return 41;
    else if (id == "core.bat")
        return 42;
    else if (id == "core.vampire_bat")
        return 43;
    else if (id == "core.dragon_bat")
        return 44;
    else if (id == "core.fire_ent")
        return 45;
    else if (id == "core.ice_ent")
        return 46;
    else if (id == "core.lich")
        return 47;
    else if (id == "core.master_lich")
        return 48;
    else if (id == "core.demi_lich")
        return 49;
    else if (id == "core.hound")
        return 50;
    else if (id == "core.fire_hound")
        return 51;
    else if (id == "core.ice_hound")
        return 52;
    else if (id == "core.lightning_hound")
        return 53;
    else if (id == "core.dark_hound")
        return 54;
    else if (id == "core.illusion_hound")
        return 55;
    else if (id == "core.nerve_hound")
        return 56;
    else if (id == "core.poison_hound")
        return 57;
    else if (id == "core.sound_hound")
        return 58;
    else if (id == "core.nether_hound")
        return 59;
    else if (id == "core.chaos_hound")
        return 60;
    else if (id == "core.giant_squirrel")
        return 61;
    else if (id == "core.killer_squirrel")
        return 62;
    else if (id == "core.grudge")
        return 63;
    else if (id == "core.hungry_demon")
        return 64;
    else if (id == "core.electric_cloud")
        return 65;
    else if (id == "core.chaos_cloud")
        return 66;
    else if (id == "core.floating_eye")
        return 67;
    else if (id == "core.wyvern")
        return 68;
    else if (id == "core.informer")
        return 69;
    else if (id == "core.bartender")
        return 70;
    else if (id == "core.sailor")
        return 71;
    else if (id == "core.captain")
        return 72;
    else if (id == "core.arena_master")
        return 73;
    else if (id == "core.healer")
        return 74;
    else if (id == "core.warrior")
        return 75;
    else if (id == "core.guard_port_kapul")
        return 76;
    else if (id == "core.guard")
        return 77;
    else if (id == "core.puppet")
        return 78;
    else if (id == "core.stersha")
        return 79;
    else if (id == "core.xabi")
        return 80;
    else if (id == "core.wasp")
        return 81;
    else if (id == "core.red_wasp")
        return 82;
    else if (id == "core.cyclops")
        return 83;
    else if (id == "core.titan")
        return 84;
    else if (id == "core.imp")
        return 85;
    else if (id == "core.nether_imp")
        return 86;
    else if (id == "core.chaos_imp")
        return 87;
    else if (id == "core.hand_of_the_dead")
        return 88;
    else if (id == "core.hand_of_the_chaos")
        return 89;
    else if (id == "core.hand_of_the_murderer")
        return 90;
    else if (id == "core.ghost")
        return 91;
    else if (id == "core.nymph")
        return 92;
    else if (id == "core.man_eater_flower")
        return 93;
    else if (id == "core.chaos_flower")
        return 94;
    else if (id == "core.cobra")
        return 95;
    else if (id == "core.king_cobra")
        return 96;
    else if (id == "core.fire_drake")
        return 97;
    else if (id == "core.ice_drake")
        return 98;
    else if (id == "core.lesser_mummy")
        return 99;
    else if (id == "core.mummy")
        return 100;
    else if (id == "core.greater_mummy")
        return 101;
    else if (id == "core.goblin")
        return 102;
    else if (id == "core.goblin_warrior")
        return 103;
    else if (id == "core.goblin_shaman")
        return 104;
    else if (id == "core.goblin_wizard")
        return 105;
    else if (id == "core.red_baptist")
        return 106;
    else if (id == "core.blue_baptist")
        return 107;
    else if (id == "core.brown_bear")
        return 108;
    else if (id == "core.grizzly")
        return 109;
    else if (id == "core.living_armor")
        return 110;
    else if (id == "core.steel_mass")
        return 111;
    else if (id == "core.golden_armor")
        return 112;
    else if (id == "core.death_armor")
        return 113;
    else if (id == "core.medusa")
        return 114;
    else if (id == "core.euryale")
        return 115;
    else if (id == "core.stheno")
        return 116;
    else if (id == "core.cupid_of_love")
        return 117;
    else if (id == "core.lesser_phantom")
        return 118;
    else if (id == "core.harpy")
        return 119;
    else if (id == "core.green_dragon")
        return 120;
    else if (id == "core.red_dragon")
        return 121;
    else if (id == "core.white_dragon")
        return 122;
    else if (id == "core.elec_dragon")
        return 123;
    else if (id == "core.nether_dragon")
        return 124;
    else if (id == "core.chaos_dragon")
        return 125;
    else if (id == "core.cerberus")
        return 126;
    else if (id == "core.spider")
        return 127;
    else if (id == "core.black_widow")
        return 128;
    else if (id == "core.paralyzer")
        return 129;
    else if (id == "core.tarantula")
        return 130;
    else if (id == "core.blood_spider")
        return 131;
    else if (id == "core.wooden_golem")
        return 132;
    else if (id == "core.stone_golem")
        return 133;
    else if (id == "core.steel_golem")
        return 134;
    else if (id == "core.golden_golem")
        return 135;
    else if (id == "core.mithril_golem")
        return 136;
    else if (id == "core.sky_golem")
        return 137;
    else if (id == "core.adamantium_golem")
        return 138;
    else if (id == "core.slan")
        return 139;
    else if (id == "core.vesda")
        return 140;
    else if (id == "core.issizzle")
        return 141;
    else if (id == "core.erystia")
        return 142;
    else if (id == "core.wynan")
        return 143;
    else if (id == "core.quruiza")
        return 144;
    else if (id == "core.corgon")
        return 145;
    else if (id == "core.karam")
        return 146;
    else if (id == "core.fire_crab")
        return 147;
    else if (id == "core.fire_centipede")
        return 148;
    else if (id == "core.cultist_of_fire")
        return 149;
    else if (id == "core.skeleton_warrior")
        return 150;
    else if (id == "core.skeleton_berserker")
        return 151;
    else if (id == "core.missionary_of_darkness")
        return 152;
    else if (id == "core.pawn")
        return 153;
    else if (id == "core.rook")
        return 154;
    else if (id == "core.bishop")
        return 155;
    else if (id == "core.knight")
        return 156;
    else if (id == "core.queen")
        return 157;
    else if (id == "core.king")
        return 158;
    else if (id == "core.mercenary_warrior")
        return 159;
    else if (id == "core.mercenary_archer")
        return 160;
    else if (id == "core.mercenary_wizard")
        return 161;
    else if (id == "core.yerles_machine_infantry")
        return 162;
    else if (id == "core.rock_thrower")
        return 163;
    else if (id == "core.cat")
        return 164;
    else if (id == "core.dog")
        return 165;
    else if (id == "core.little_girl")
        return 166;
    else if (id == "core.rat")
        return 167;
    else if (id == "core.hermit_crab")
        return 168;
    else if (id == "core.slime")
        return 169;
    else if (id == "core.public_performer")
        return 170;
    else if (id == "core.citizen_of_cyber_dome")
        return 171;
    else if (id == "core.citizen_of_cyber_dome2")
        return 172;
    else if (id == "core.sales_person")
        return 173;
    else if (id == "core.punk")
        return 174;
    else if (id == "core.frisia")
        return 175;
    else if (id == "core.younger_sister")
        return 176;
    else if (id == "core.utima")
        return 177;
    else if (id == "core.azzrssil")
        return 178;
    else if (id == "core.master_of_pet_arena")
        return 179;
    else if (id == "core.twintail")
        return 180;
    else if (id == "core.silver_wolf")
        return 181;
    else if (id == "core.nurse")
        return 182;
    else if (id == "core.rich_person")
        return 183;
    else if (id == "core.noble_child")
        return 184;
    else if (id == "core.tourist")
        return 185;
    else if (id == "core.blade")
        return 186;
    else if (id == "core.blade_alpha")
        return 187;
    else if (id == "core.blade_omega")
        return 188;
    else if (id == "core.deformed_eye")
        return 189;
    else if (id == "core.impure_eye")
        return 190;
    else if (id == "core.wisp")
        return 191;
    else if (id == "core.hedgehog")
        return 192;
    else if (id == "core.shining_hedgehog")
        return 193;
    else if (id == "core.acid_slime")
        return 194;
    else if (id == "core.chicken")
        return 195;
    else if (id == "core.pumpkin")
        return 196;
    else if (id == "core.greater_pumpkin")
        return 197;
    else if (id == "core.halloween_nightmare")
        return 198;
    else if (id == "core.stalker")
        return 199;
    else if (id == "core.shadow_stalker")
        return 200;
    else if (id == "core.puppy")
        return 201;
    else if (id == "core.ebon")
        return 202;
    else if (id == "core.moyer_the_crooked")
        return 203;
    else if (id == "core.palmian_elite_soldier")
        return 204;
    else if (id == "core.maid")
        return 205;
    else if (id == "core.nun")
        return 206;
    else if (id == "core.ebon2")
        return 207;
    else if (id == "core.garokk")
        return 208;
    else if (id == "core.miral")
        return 209;
    else if (id == "core.younger_cat_sister")
        return 210;
    else if (id == "core.young_lady")
        return 211;
    else if (id == "core.test_subject")
        return 212;
    else if (id == "core.gwen")
        return 213;
    else if (id == "core.thief")
        return 214;
    else if (id == "core.robber")
        return 215;
    else if (id == "core.great_race_of_yith")
        return 216;
    else if (id == "core.master_thief")
        return 217;
    else if (id == "core.shub_niggurath")
        return 218;
    else if (id == "core.gagu")
        return 219;
    else if (id == "core.spiral_king")
        return 220;
    else if (id == "core.pael")
        return 221;
    else if (id == "core.lily")
        return 222;
    else if (id == "core.raphael")
        return 223;
    else if (id == "core.ainc")
        return 224;
    else if (id == "core.poppy")
        return 225;
    else if (id == "core.rilian")
        return 226;
    else if (id == "core.tam")
        return 227;
    else if (id == "core.carbuncle")
        return 228;
    else if (id == "core.lion")
        return 229;
    else if (id == "core.cacy")
        return 230;
    else if (id == "core.gilbert_the_colonel")
        return 231;
    else if (id == "core.yerles_self_propelled_gun")
        return 232;
    else if (id == "core.juere_infantry")
        return 233;
    else if (id == "core.yerles_elite_machine_infantry")
        return 234;
    else if (id == "core.juere_swordman")
        return 235;
    else if (id == "core.yeek")
        return 236;
    else if (id == "core.kamikaze_yeek")
        return 237;
    else if (id == "core.yeek_warrior")
        return 238;
    else if (id == "core.hot_spring_maniac")
        return 239;
    else if (id == "core.master_yeek")
        return 240;
    else if (id == "core.yeek_archer")
        return 241;
    else if (id == "core.rodlob")
        return 242;
    else if (id == "core.arnord")
        return 243;
    else if (id == "core.kamikaze_samurai")
        return 244;
    else if (id == "core.bomb_rock")
        return 245;
    else if (id == "core.silver_cat")
        return 246;
    else if (id == "core.mia")
        return 247;
    else if (id == "core.tyrannosaurus")
        return 248;
    else if (id == "core.younger_sister_of_mansion")
        return 249;
    else if (id == "core.fairy")
        return 250;
    else if (id == "core.troll")
        return 251;
    else if (id == "core.renton")
        return 252;
    else if (id == "core.marks")
        return 253;
    else if (id == "core.ancient_coffin")
        return 254;
    else if (id == "core.scorpion")
        return 255;
    else if (id == "core.king_scorpion")
        return 256;
    else if (id == "core.tuwen")
        return 257;
    else if (id == "core.iron_maiden")
        return 258;
    else if (id == "core.noel")
        return 259;
    else if (id == "core.black_cat")
        return 260;
    else if (id == "core.cute_fairy")
        return 261;
    else if (id == "core.android")
        return 262;
    else if (id == "core.black_angel")
        return 263;
    else if (id == "core.exile")
        return 264;
    else if (id == "core.golden_knight")
        return 265;
    else if (id == "core.defender")
        return 266;
    else if (id == "core.lame_horse")
        return 267;
    else if (id == "core.yowyn_horse")
        return 268;
    else if (id == "core.farmer")
        return 269;
    else if (id == "core.sister")
        return 270;
    else if (id == "core.rogue")
        return 271;
    else if (id == "core.artist")
        return 272;
    else if (id == "core.miner")
        return 273;
    else if (id == "core.noble")
        return 274;
    else if (id == "core.noyel_horse")
        return 275;
    else if (id == "core.wild_horse")
        return 276;
    else if (id == "core.wild_horse2")
        return 277;
    else if (id == "core.mutant")
        return 278;
    else if (id == "core.icolle")
        return 279;
    else if (id == "core.balzak")
        return 280;
    else if (id == "core.lizard_man")
        return 281;
    else if (id == "core.minotaur")
        return 282;
    else if (id == "core.spore_mushroom")
        return 283;
    else if (id == "core.chaos_mushroom")
        return 284;
    else if (id == "core.blue_bubble")
        return 285;
    else if (id == "core.bubble")
        return 286;
    else if (id == "core.mass_monster")
        return 287;
    else if (id == "core.revlus")
        return 288;
    else if (id == "core.mage_guild_member")
        return 289;
    else if (id == "core.lexus")
        return 290;
    else if (id == "core.fray")
        return 291;
    else if (id == "core.sin")
        return 292;
    else if (id == "core.thief_guild_member")
        return 293;
    else if (id == "core.abyss")
        return 294;
    else if (id == "core.fighter_guild_member")
        return 295;
    else if (id == "core.minotaur_magician")
        return 296;
    else if (id == "core.doria")
        return 297;
    else if (id == "core.minotaur_boxer")
        return 298;
    else if (id == "core.minotaur_king")
        return 299;
    else if (id == "core.ungaga")
        return 300;
    else if (id == "core.conery")
        return 301;
    else if (id == "core.rogue_boss")
        return 302;
    else if (id == "core.rogue_warrior")
        return 303;
    else if (id == "core.rogue_archer")
        return 304;
    else if (id == "core.rogue_wizard")
        return 305;
    else if (id == "core.lulwy")
        return 306;
    else if (id == "core.executioner")
        return 307;
    else if (id == "core.messenger_of_death")
        return 308;
    else if (id == "core.asura")
        return 309;
    else if (id == "core.mitra")
        return 310;
    else if (id == "core.varuna")
        return 311;
    else if (id == "core.hungry_sea_lion")
        return 312;
    else if (id == "core.super_hungry_sea_lion")
        return 313;
    else if (id == "core.death_gaze")
        return 314;
    else if (id == "core.chaos_eye")
        return 315;
    else if (id == "core.mad_gaze")
        return 316;
    else if (id == "core.silver_eyed_witch")
        return 317;
    else if (id == "core.big_daddy")
        return 318;
    else if (id == "core.little_sister")
        return 319;
    else if (id == "core.cleaner")
        return 320;
    else if (id == "core.hard_gay")
        return 321;
    else if (id == "core.strange_scientist")
        return 322;
    else if (id == "core.shade")
        return 323;
    else if (id == "core.quickling")
        return 324;
    else if (id == "core.quickling_archer")
        return 325;
    else if (id == "core.bard")
        return 326;
    else if (id == "core.cube")
        return 327;
    else if (id == "core.silver_bell")
        return 328;
    else if (id == "core.gold_bell")
        return 329;
    else if (id == "core.alien")
        return 330;
    else if (id == "core.ehekatl")
        return 331;
    else if (id == "core.stray_cat")
        return 332;
    else if (id == "core.guild_trainer")
        return 333;
    else if (id == "core.mysterious_producer")
        return 334;
    else if (id == "core.prostitute")
        return 335;
    else if (id == "core.god_inside_ehekatl")
        return 336;
    else if (id == "core.prisoner")
        return 337;
    else if (id == "core.opatos")
        return 338;
    else if (id == "core.kumiromi")
        return 339;
    else if (id == "core._test")
        return 340;
    else if (id == "core.mine_dog")
        return 341;
    else if (id == "core.mani")
        return 342;
    else if (id == "core.user")
        return 343;
    else if (id == "core.mammoth")
        return 344;
    else if (id == "core.kaneda_bike")
        return 345;
    else if (id == "core.cub")
        return 346;
    else if (id == "core.fanatic")
        return 347;
    else if (id == "core.part_time_worker")
        return 348;
    else if (id == "core.holy_beast")
        return 349;
    else if (id == "core.festival_tourist")
        return 350;
    else if (id == "core.the_leopard_warrior")
        return 351;
    else if (id == "core.silvia")
        return 352;
    else if (id == "core.caravan_master")
        return 353;
    else
    {
        assert(0);
        return 0;
    }
}

} // namespace



namespace elona
{

bool CharacterId::operator==(int legacy_id) const
{
    const auto new_id = _get_new_id_by_legacy_id(legacy_id);
    return _value == new_id;
}



CharacterId::CharacterId(int legacy_id)
    : _value(_get_new_id_by_legacy_id(legacy_id))
{
}



int CharacterId::to_integer() const
{
    return _get_old_id_by_new_id(_value);
}

} // namespace elona
