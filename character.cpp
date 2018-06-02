#include "character.hpp"
#include <cassert>
#include <type_traits>
#include "ability.hpp"
#include "calc.hpp"
#include "cat.hpp"
#include "character_status.hpp"
#include "class.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "equipment.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "item_db.hpp"
#include "map_cell.hpp"
#include "quest.hpp"
#include "random.hpp"
#include "range.hpp"
#include "trait.hpp"
#include "variables.hpp"

using namespace elona;



namespace elona
{


character_db the_character_db;
cdata_t cdata;


int p_at_m117 = 0;
int f_at_m125 = 0;
int chara_createhack = 0;
elona_vector1<std::string> usertxt;

void character_db::define(lua_State* L)
{
    const char* id = luaL_checkstring(L, -2);
    if (!id)
        throw std::runtime_error(u8"Error: fail to load character data");

    ELONA_CAT_DB_FIELD_INTEGER(ai_act_sub_freq, 0);
    ELONA_CAT_DB_FIELD_INTEGER(ai_calm, 0);
    ELONA_CAT_DB_FIELD_INTEGER(ai_dist, 0);
    ELONA_CAT_DB_FIELD_INTEGER(ai_heal, 0);
    ELONA_CAT_DB_FIELD_INTEGER(ai_move, 0);
    ELONA_CAT_DB_FIELD_INTEGER(can_talk, 0);
    ELONA_CAT_DB_FIELD_STRING(class_, "");
    ELONA_CAT_DB_FIELD_INTEGER(color, 0);
    ELONA_CAT_DB_FIELD_INTEGER(creaturepack, 0);
    ELONA_CAT_DB_FIELD_INTEGER(cspecialeq, 0);
    ELONA_CAT_DB_FIELD_INTEGER(damage_reaction_info, 0);
    ELONA_CAT_DB_FIELD_INTEGER(item_type, 0);
    ELONA_CAT_DB_FIELD_INTEGER(element_of_unarmed_attack, 0);
    ELONA_CAT_DB_FIELD_INTEGER(eqammo_0, 0);
    ELONA_CAT_DB_FIELD_INTEGER(eqammo_1, 0);
    ELONA_CAT_DB_FIELD_INTEGER(eqmultiweapon, 0);
    ELONA_CAT_DB_FIELD_INTEGER(eqrange_0, 0);
    ELONA_CAT_DB_FIELD_INTEGER(eqrange_1, 0);
    ELONA_CAT_DB_FIELD_INTEGER(eqring1, 0);
    ELONA_CAT_DB_FIELD_INTEGER(eqtwohand, 0);
    ELONA_CAT_DB_FIELD_INTEGER(eqweapon1, 0);
    ELONA_CAT_DB_FIELD_INTEGER(female_image, 0);
    ELONA_CAT_DB_FIELD_STRING(filter, "");
    ELONA_CAT_DB_FIELD_INTEGER(fixlv, 0);
    ELONA_CAT_DB_FIELD_BOOLEAN(has_random_name, false);
    ELONA_CAT_DB_FIELD_INTEGER(image, 0);
    ELONA_CAT_DB_FIELD_INTEGER(level, 0);
    ELONA_CAT_DB_FIELD_INTEGER(male_image, 0);
    ELONA_CAT_DB_FIELD_INTEGER(original_relationship, 0);
    ELONA_CAT_DB_FIELD_INTEGER(portrait, 0);
    ELONA_CAT_DB_FIELD_STRING(race, "");
    ELONA_CAT_DB_FIELD_INTEGER(sex, -1);

    std::unordered_map<int, int> resistances;
    lua_getfield(L, -1, u8"resistances");
    if (!lua_isnil(L, -1))
    {
        lua_pushnil(L);
        while (lua_next(L, -2))
        {
            int k = std::stoi(luaL_checkstring(L, -2) + 1);
            int v = luaL_checkinteger(L, -1);
            resistances.emplace(k, v);
            lua_pop(L, 1);
        }
    }
    lua_pop(L, 1);

    ELONA_CAT_DB_FIELD_INTEGER(fltselect, 0);
    ELONA_CAT_DB_FIELD_INTEGER(category, 0);
    ELONA_CAT_DB_FIELD_INTEGER(rarity, 10000);
    ELONA_CAT_DB_FIELD_INTEGER(coefficient, 400);

    // TODO DRY
    std::vector<int> normal_actions;
    lua_getfield(L, -1, u8"normal_actions");
    if (!lua_isnil(L, -1))
    {
        lua_pushnil(L);
        while (lua_next(L, -2))
        {
            int v = luaL_checkinteger(L, -1);
            normal_actions.push_back(v);
            lua_pop(L, 1);
        }
    }
    lua_pop(L, 1);

    std::vector<int> special_actions;
    lua_getfield(L, -1, u8"special_actions");
    if (!lua_isnil(L, -1))
    {
        lua_pushnil(L);
        while (lua_next(L, -2))
        {
            int v = luaL_checkinteger(L, -1);
            special_actions.push_back(v);
            lua_pop(L, 1);
        }
    }
    lua_pop(L, 1);

    std::vector<int> flag_types;
    lua_getfield(L, -1, u8"flags");
    if (!lua_isnil(L, -1))
    {
        lua_pushnil(L);
        while (lua_next(L, -2))
        {
            int v = luaL_checkinteger(L, -1);
            flag_types.push_back(v);
            lua_pop(L, 1);
        }
    }
    lua_pop(L, 1);

    // TODO: cannot set bit flags off.
    decltype(character_data::_flags) flags;
    for (const auto& type : flag_types)
    {
        flags[type] = true;
    }

    storage.emplace(
        std::stoi(id), // TODO
        character_data{
            std::stoi(id),
            normal_actions,
            special_actions,
            ai_act_sub_freq,
            ai_calm,
            ai_dist,
            ai_heal,
            ai_move,
            can_talk,
            class_,
            color,
            creaturepack,
            cspecialeq,
            damage_reaction_info,
            item_type,
            element_of_unarmed_attack,
            eqammo_0,
            eqammo_1,
            eqmultiweapon,
            eqrange_0,
            eqrange_1,
            eqring1,
            eqtwohand,
            eqweapon1,
            female_image,
            filter,
            fixlv,
            has_random_name,
            image,
            level,
            male_image,
            original_relationship,
            portrait,
            race,
            sex,
            resistances,
            fltselect,
            category,
            rarity,
            coefficient,
            flags,
        });
}


character::character()
    : growth_buffs(10)
    , body_parts(30)
    , buffs(16)
    , attr_adjs(10)
{
}


void character::clear()
{
    character tmp{};
    using std::swap;
    swap(*this, tmp);
}


void character::clear_flags()
{
    for (size_t i = 0; i < 32 * 30; ++i)
    {
        _flags[i] = false;
    }
}


cdata_t::cdata_t()
    : storage(ELONA_MAX_CHARACTERS)
{
}



void initialize_character_filters()
{
    filter_creature(0) = u8"";
    filter_creature(1) = u8"/man/";
    filter_creature(2) = u8"/man/";
    filter_creature(3) = u8"/slime/";
    filter_creature(4) = u8"/fire/slime/";
    filter_creature(5) = u8"/wild/";
    filter_creature(6) = u8"/wild/";
    filter_creature(7) = u8"/man/";
    filter_creature(8) = u8"/man/";
    filter_creature(9) = u8"/man/";
    filter_creature(10) = u8"/wild/";
    filter_creature(11) = u8"/wild/";
    filter_creature(12) = u8"/man/";
    filter_creature(13) = u8"";
    filter_creature(14) = u8"";
    filter_creature(15) = u8"";
    filter_creature(16) = u8"/man/";
    filter_creature(17) = u8"";
    filter_creature(18) = u8"/man/";
    filter_creature(19) = u8"";
    filter_creature(20) = u8"";
    filter_creature(21) = u8"/undead/";
    filter_creature(22) = u8"";
    filter_creature(23) = u8"/man/god/";
    filter_creature(24) = u8"/man/";
    filter_creature(25) = u8"";
    filter_creature(26) = u8"/man/";
    filter_creature(27) = u8"/man/god/";
    filter_creature(28) = u8"/man/";
    filter_creature(29) = u8"/man/";
    filter_creature(30) = u8"/man/";
    filter_creature(31) = u8"/man/";
    filter_creature(32) = u8"";
    filter_creature(33) = u8"/man/";
    filter_creature(34) = u8"/man/";
    filter_creature(35) = u8"/man/";
    filter_creature(36) = u8"/man/";
    filter_creature(37) = u8"/man/";
    filter_creature(38) = u8"/man/";
    filter_creature(39) = u8"/man/";
    filter_creature(40) = u8"/man/";
    filter_creature(41) = u8"/man/";
    filter_creature(42) = u8"/wild/";
    filter_creature(43) = u8"/wild/";
    filter_creature(44) = u8"/wild/fire/dragon/";
    filter_creature(45) = u8"/fire/";
    filter_creature(46) = u8"";
    filter_creature(47) = u8"/undead/";
    filter_creature(48) = u8"/undead/";
    filter_creature(49) = u8"/undead/";
    filter_creature(50) = u8"/wild/";
    filter_creature(51) = u8"/wild/fire/";
    filter_creature(52) = u8"/wild/";
    filter_creature(53) = u8"/wild/";
    filter_creature(54) = u8"/wild/";
    filter_creature(55) = u8"/wild/";
    filter_creature(56) = u8"/wild/";
    filter_creature(57) = u8"/wild/";
    filter_creature(58) = u8"/wild/";
    filter_creature(59) = u8"/wild/";
    filter_creature(60) = u8"/wild/";
    filter_creature(61) = u8"/wild/";
    filter_creature(62) = u8"/wild/";
    filter_creature(63) = u8"/undead/";
    filter_creature(64) = u8"/undead/";
    filter_creature(65) = u8"";
    filter_creature(66) = u8"";
    filter_creature(67) = u8"";
    filter_creature(68) = u8"/dragon/";
    filter_creature(69) = u8"/man/";
    filter_creature(70) = u8"/man/";
    filter_creature(71) = u8"/man/";
    filter_creature(72) = u8"/man/";
    filter_creature(73) = u8"/man/";
    filter_creature(74) = u8"/man/";
    filter_creature(75) = u8"/man/";
    filter_creature(76) = u8"/man/";
    filter_creature(77) = u8"/man/";
    filter_creature(78) = u8"";
    filter_creature(79) = u8"/man/";
    filter_creature(80) = u8"/man/";
    filter_creature(81) = u8"";
    filter_creature(82) = u8"/fire/";
    filter_creature(83) = u8"";
    filter_creature(84) = u8"";
    filter_creature(85) = u8"/fire/";
    filter_creature(86) = u8"/god/";
    filter_creature(87) = u8"";
    filter_creature(88) = u8"/undead/";
    filter_creature(89) = u8"/undead/";
    filter_creature(90) = u8"/undead/";
    filter_creature(91) = u8"/undead/";
    filter_creature(92) = u8"/undead/";
    filter_creature(93) = u8"";
    filter_creature(94) = u8"";
    filter_creature(95) = u8"/wild/";
    filter_creature(96) = u8"/wild/";
    filter_creature(97) = u8"/fire/dragon/";
    filter_creature(98) = u8"/dragon/";
    filter_creature(99) = u8"/undead/";
    filter_creature(100) = u8"/undead/";
    filter_creature(101) = u8"/undead/";
    filter_creature(102) = u8"";
    filter_creature(103) = u8"";
    filter_creature(104) = u8"";
    filter_creature(105) = u8"";
    filter_creature(106) = u8"/undead/fire/";
    filter_creature(107) = u8"/undead/";
    filter_creature(108) = u8"/wild/";
    filter_creature(109) = u8"/wild/";
    filter_creature(110) = u8"/undead/";
    filter_creature(111) = u8"/undead/";
    filter_creature(112) = u8"/undead/";
    filter_creature(113) = u8"";
    filter_creature(114) = u8"/god/";
    filter_creature(115) = u8"/god/";
    filter_creature(116) = u8"/god/";
    filter_creature(117) = u8"/god/";
    filter_creature(118) = u8"/undead/";
    filter_creature(119) = u8"";
    filter_creature(120) = u8"/dragon/";
    filter_creature(121) = u8"/fire/dragon/";
    filter_creature(122) = u8"/dragon/";
    filter_creature(123) = u8"/dragon/";
    filter_creature(124) = u8"/undead/dragon/";
    filter_creature(125) = u8"/dragon/";
    filter_creature(126) = u8"/fire/";
    filter_creature(127) = u8"/wild/";
    filter_creature(128) = u8"/wild/";
    filter_creature(129) = u8"/wild/";
    filter_creature(130) = u8"/wild/";
    filter_creature(131) = u8"/undead/";
    filter_creature(132) = u8"";
    filter_creature(133) = u8"/fire/";
    filter_creature(134) = u8"/fire/";
    filter_creature(135) = u8"";
    filter_creature(136) = u8"";
    filter_creature(137) = u8"";
    filter_creature(138) = u8"";
    filter_creature(139) = u8"/man/";
    filter_creature(140) = u8"/dragon/";
    filter_creature(141) = u8"/undead/god/";
    filter_creature(142) = u8"/man/";
    filter_creature(143) = u8"";
    filter_creature(144) = u8"";
    filter_creature(145) = u8"";
    filter_creature(146) = u8"/man/";
    filter_creature(147) = u8"/fire/";
    filter_creature(148) = u8"/fire/";
    filter_creature(149) = u8"/fire/";
    filter_creature(150) = u8"/undead/";
    filter_creature(151) = u8"/undead/";
    filter_creature(152) = u8"/man/";
    filter_creature(153) = u8"/pawn/";
    filter_creature(154) = u8"/pawn/";
    filter_creature(155) = u8"/pawn/";
    filter_creature(156) = u8"/pawn/";
    filter_creature(157) = u8"";
    filter_creature(158) = u8"";
    filter_creature(159) = u8"/man/shopguard/";
    filter_creature(160) = u8"/man/shopguard/";
    filter_creature(161) = u8"/man/shopguard/";
    filter_creature(162) = u8"/man/";
    filter_creature(163) = u8"/man/";
    filter_creature(164) = u8"/wild/cat/";
    filter_creature(165) = u8"/wild/";
    filter_creature(166) = u8"/man/";
    filter_creature(167) = u8"/wild/";
    filter_creature(168) = u8"/wild/";
    filter_creature(169) = u8"/slime/";
    filter_creature(170) = u8"/man/";
    filter_creature(171) = u8"/man/";
    filter_creature(172) = u8"/man/";
    filter_creature(173) = u8"/man/";
    filter_creature(174) = u8"/man/sf/";
    filter_creature(175) = u8"/god/";
    filter_creature(176) = u8"/man/";
    filter_creature(177) = u8"/god/";
    filter_creature(178) = u8"/undead/god/";
    filter_creature(179) = u8"/man/";
    filter_creature(180) = u8"";
    filter_creature(181) = u8"/god/";
    filter_creature(182) = u8"/man/";
    filter_creature(183) = u8"/man/";
    filter_creature(184) = u8"/man/";
    filter_creature(185) = u8"/man/";
    filter_creature(186) = u8"";
    filter_creature(187) = u8"";
    filter_creature(188) = u8"";
    filter_creature(189) = u8"/undead/";
    filter_creature(190) = u8"/undead/";
    filter_creature(191) = u8"/undead/ether/";
    filter_creature(192) = u8"/wild/";
    filter_creature(193) = u8"/wild/ether/";
    filter_creature(194) = u8"/slime/";
    filter_creature(195) = u8"/wild/";
    filter_creature(196) = u8"/undead/";
    filter_creature(197) = u8"/undead/";
    filter_creature(198) = u8"/undead/";
    filter_creature(199) = u8"/undead/";
    filter_creature(200) = u8"/undead/";
    filter_creature(201) = u8"/undead/";
    filter_creature(202) = u8"";
    filter_creature(203) = u8"/man/";
    filter_creature(204) = u8"/man/";
    filter_creature(205) = u8"/man/";
    filter_creature(206) = u8"/man/";
    filter_creature(207) = u8"/god/";
    filter_creature(208) = u8"/man/";
    filter_creature(209) = u8"/man/";
    filter_creature(210) = u8"/man/";
    filter_creature(211) = u8"/man/";
    filter_creature(212) = u8"";
    filter_creature(213) = u8"/man/";
    filter_creature(214) = u8"/man/";
    filter_creature(215) = u8"/man/";
    filter_creature(216) = u8"";
    filter_creature(217) = u8"/man/";
    filter_creature(218) = u8"";
    filter_creature(219) = u8"";
    filter_creature(220) = u8"/god/";
    filter_creature(221) = u8"/man/";
    filter_creature(222) = u8"/man/";
    filter_creature(223) = u8"/man/";
    filter_creature(224) = u8"/man/";
    filter_creature(225) = u8"/wild/";
    filter_creature(226) = u8"/man/";
    filter_creature(227) = u8"/man/";
    filter_creature(228) = u8"/wild/cat/";
    filter_creature(229) = u8"/wild/cat/";
    filter_creature(230) = u8"/wild/cat/";
    filter_creature(231) = u8"/man/";
    filter_creature(232) = u8"";
    filter_creature(233) = u8"/man/";
    filter_creature(234) = u8"/man/";
    filter_creature(235) = u8"/man/";
    filter_creature(236) = u8"/yeek/";
    filter_creature(237) = u8"/yeek/";
    filter_creature(238) = u8"/yeek/";
    filter_creature(239) = u8"/man/";
    filter_creature(240) = u8"/yeek/";
    filter_creature(241) = u8"/yeek/";
    filter_creature(242) = u8"/yeek/";
    filter_creature(243) = u8"/man/";
    filter_creature(244) = u8"";
    filter_creature(245) = u8"";
    filter_creature(246) = u8"/wild/cat/";
    filter_creature(247) = u8"/man/";
    filter_creature(248) = u8"/dragon/";
    filter_creature(249) = u8"/man/";
    filter_creature(250) = u8"";
    filter_creature(251) = u8"";
    filter_creature(252) = u8"/man/";
    filter_creature(253) = u8"/man/";
    filter_creature(254) = u8"/undead/";
    filter_creature(255) = u8"/wild/";
    filter_creature(256) = u8"/wild/";
    filter_creature(257) = u8"/undead/";
    filter_creature(258) = u8"";
    filter_creature(259) = u8"/man/";
    filter_creature(260) = u8"/god/";
    filter_creature(261) = u8"/god/";
    filter_creature(262) = u8"/god/";
    filter_creature(263) = u8"/god/";
    filter_creature(264) = u8"/god/";
    filter_creature(265) = u8"/god/";
    filter_creature(266) = u8"/god/";
    filter_creature(267) = u8"/wild/horse/";
    filter_creature(268) = u8"/wild/horse/";
    filter_creature(269) = u8"/man/";
    filter_creature(270) = u8"/man/";
    filter_creature(271) = u8"/man/";
    filter_creature(272) = u8"/man/";
    filter_creature(273) = u8"/man/";
    filter_creature(274) = u8"/man/";
    filter_creature(275) = u8"/wild/horse/";
    filter_creature(276) = u8"/wild/horse/";
    filter_creature(277) = u8"/wild/horse/";
    filter_creature(278) = u8"";
    filter_creature(279) = u8"/man/";
    filter_creature(280) = u8"/man/";
    filter_creature(281) = u8"/dragon/";
    filter_creature(282) = u8"/mino/";
    filter_creature(283) = u8"";
    filter_creature(284) = u8"";
    filter_creature(285) = u8"/slime/";
    filter_creature(286) = u8"/slime/";
    filter_creature(287) = u8"";
    filter_creature(288) = u8"/man/";
    filter_creature(289) = u8"/man/";
    filter_creature(290) = u8"/man/";
    filter_creature(291) = u8"/man/";
    filter_creature(292) = u8"/man/";
    filter_creature(293) = u8"/man/";
    filter_creature(294) = u8"/man/";
    filter_creature(295) = u8"/man/";
    filter_creature(296) = u8"/mino/";
    filter_creature(297) = u8"/man/";
    filter_creature(298) = u8"/mino/";
    filter_creature(299) = u8"/mino/";
    filter_creature(300) = u8"/mino/";
    filter_creature(301) = u8"/man/";
    filter_creature(302) = u8"/man/rogue/";
    filter_creature(303) = u8"/man/rogue/";
    filter_creature(304) = u8"/man/rogue/";
    filter_creature(305) = u8"/man/rogue/";
    filter_creature(306) = u8"/god/";
    filter_creature(307) = u8"/undead/";
    filter_creature(308) = u8"/undead/";
    filter_creature(309) = u8"/god/";
    filter_creature(310) = u8"/god/";
    filter_creature(311) = u8"/god/";
    filter_creature(312) = u8"";
    filter_creature(313) = u8"";
    filter_creature(314) = u8"";
    filter_creature(315) = u8"";
    filter_creature(316) = u8"";
    filter_creature(317) = u8"";
    filter_creature(318) = u8"";
    filter_creature(319) = u8"";
    filter_creature(320) = u8"/man/";
    filter_creature(321) = u8"";
    filter_creature(322) = u8"/man/";
    filter_creature(323) = u8"/undead/";
    filter_creature(324) = u8"";
    filter_creature(325) = u8"";
    filter_creature(326) = u8"/man/";
    filter_creature(327) = u8"";
    filter_creature(328) = u8"";
    filter_creature(329) = u8"";
    filter_creature(330) = u8"/dragon/";
    filter_creature(331) = u8"/god/";
    filter_creature(332) = u8"/wild/cat/";
    filter_creature(333) = u8"/man/";
    filter_creature(334) = u8"/man/";
    filter_creature(335) = u8"/man/";
    filter_creature(336) = u8"/god/";
    filter_creature(337) = u8"/man/";
    filter_creature(338) = u8"/god/";
    filter_creature(339) = u8"/god/";
    filter_creature(340) = u8"";
    filter_creature(341) = u8"";
    filter_creature(342) = u8"/god/";
    filter_creature(343) = u8"";
    filter_creature(344) = u8"/wild/";
    filter_creature(345) = u8"";
    filter_creature(346) = u8"";
    filter_creature(347) = u8"/man/";
    filter_creature(348) = u8"/man/";
    filter_creature(349) = u8"/man/god/";
    filter_creature(350) = u8"/man/";
    filter_creature(351) = u8"/man/";
    filter_creature(352) = u8"/man/";
    filter_creature(353) = u8"/man/";
}

void chara_set_generation_filter()
{
    dbid = 0;
    if (gdata_current_map == 21)
    {
        flt(calcobjlv(10), calcfixlv(2));
        fltn(u8"sf"s);
        return;
    }
    if (mdata(6) == 3 || mdata(6) == 2)
    {
        flt(calcobjlv(10), calcfixlv(2));
        fltselect = 5;
        if (gdata_current_dungeon_level == 1)
        {
            if (gdata_current_map == 12)
            {
                if (rnd(2))
                {
                    dbid = 269;
                    return;
                }
            }
            if (gdata_current_map == 33)
            {
                if (rnd(3) == 0)
                {
                    dbid = 270;
                    return;
                }
            }
            if (gdata_current_map == 14)
            {
                if (rnd(3) == 0)
                {
                    dbid = 271;
                    return;
                }
                else if (rnd(2) == 0)
                {
                    dbid = 335;
                    return;
                }
            }
            if (gdata_current_map == 36)
            {
                if (rnd(3) == 0)
                {
                    dbid = 272;
                    return;
                }
            }
            if (gdata_current_map == 5)
            {
                if (rnd(2))
                {
                    dbid = 273;
                    return;
                }
            }
            if (gdata_current_map == 15)
            {
                if (rnd(3) == 0)
                {
                    dbid = 274;
                    return;
                }
            }
        }
        if (gdata_current_map == 36)
        {
            if (gdata_current_dungeon_level == 3)
            {
                dbid = 289;
            }
        }
        if (gdata_current_map == 14)
        {
            if (gdata_current_dungeon_level == 3)
            {
                dbid = 293;
            }
        }
        if (gdata_current_map == 11)
        {
            if (gdata_current_dungeon_level == 3)
            {
                dbid = 295;
            }
        }
        return;
    }
    if (gdata_current_map == 3)
    {
        flt(calcobjlv(gdata_current_dungeon_level), calcfixlv(2));
        if (gdata_current_dungeon_level < 4)
        {
            if (objlv > 5)
            {
                objlv = 5;
            }
        }
        return;
    }
    if (gdata_current_map == 42)
    {
        flt(calcobjlv(gdata_current_dungeon_level % 50 + 5), calcfixlv(2));
        return;
    }
    if (gdata_current_map == 19)
    {
        flt(calcobjlv(gdata_current_dungeon_level), calcfixlv(2));
        return;
    }
    if (gdata_current_map == 17)
    {
        flt(calcobjlv(gdata_current_dungeon_level), calcfixlv(2));
        fltn(u8"undead"s);
        return;
    }
    if (gdata_current_map == 16)
    {
        flt(calcobjlv(gdata_current_dungeon_level), calcfixlv(2));
        fltn(u8"fire"s);
        return;
    }
    if (gdata_current_map == 18)
    {
        flt(calcobjlv(gdata_current_dungeon_level), calcfixlv(2));
        if (rnd(2) == 0)
        {
            fltn(u8"man"s);
        }
        return;
    }
    if (gdata_current_map == 37)
    {
        flt(calcobjlv(gdata_current_dungeon_level), calcfixlv(2));
        flttypemajor = 13;
        return;
    }
    if (gdata_current_map == 10 || gdata_current_map == 20)
    {
        flt(calcobjlv(20), calcfixlv(2));
        fltselect = 4;
        return;
    }
    if (gdata_current_map == 13)
    {
        if (gdata_executing_immediate_quest_type >= 1000)
        {
            flt(calcobjlv(qdata(5, gdata_executing_immediate_quest) + 1),
                calcfixlv(2));
        }
        if (gdata_executing_immediate_quest_type == 1006)
        {
            fltn(u8"wild"s);
            objlv = clamp(objlv / 4, 1, 8);
        }
        return;
    }
    if (adata(16, gdata_current_map) == 28)
    {
        flt(calcobjlv(gdata_current_dungeon_level), calcfixlv(2));
        if (rnd(2))
        {
            fltn(u8"yeek"s);
        }
        return;
    }
    if (adata(16, gdata_current_map) == 38)
    {
        flt(calcobjlv(gdata_current_dungeon_level), calcfixlv(2));
        if (rnd(2))
        {
            fltn(u8"mino"s);
        }
        return;
    }
    if (mdata(6) >= 20)
    {
        flt(calcobjlv(gdata_current_dungeon_level), calcfixlv(2));
        return;
    }
    if (adata(16, gdata_current_map) == 101
        || adata(16, gdata_current_map) == 102)
    {
        flt(calcobjlv(100), calcfixlv(2));
        if (rnd(1))
        {
            fltselect = 5;
        }
        else
        {
            fltselect = 7;
        }
        return;
    }
    flt(calcobjlv(cdata[0].level), calcfixlv(2));
    return;
}

int chara_get_free_slot()
{
    int rc = -1;
    for (int cnt = ELONA_MAX_PARTY_CHARACTERS; cnt < ELONA_MAX_CHARACTERS;
         ++cnt)
    {
        if (cdata[cnt].state == 0)
        {
            rc = cnt;
            break;
        }
    }
    return rc;
}

int chara_get_free_slot_ally()
{
    f_at_m125 = 0;
    for (int cnt = 1, cnt_end = cnt + (clamp(sdata(17, 0) / 5 + 1, 2, 15));
         cnt < cnt_end;
         ++cnt)
    {
        if (cdata[cnt].state != 0)
        {
            continue;
        }
        f_at_m125 = cnt;
        break;
    }
    return f_at_m125;
}



void chara_place()
{
    int placefail = 0;
    if (rc == -1)
    {
        return;
    }
    if (rc == 56)
    {
        cdata[rc].state = 0;
        return;
    }
    placefail = 0;
    if (gdata_mount == rc)
    {
        if (rc != 0)
        {
            cdata[rc].position.x = cdata[0].position.x;
            cdata[rc].position.y = cdata[0].position.y;
            return;
        }
    }
    for (int cnt = 0;; ++cnt)
    {
        if (cnt == 99)
        {
            if (rc >= 57)
            {
                placefail = 1;
                break;
            }
        }
        if (cnt > 99)
        {
            if (mdata(0) == 0)
            {
                placefail = 1;
                break;
            }
            y = (cnt - 100) / mdata(0);
            x = (cnt - 100) % mdata(0);
            if (y >= mdata(1))
            {
                if (rc != 0)
                {
                    placefail = 1;
                    break;
                }
                else
                {
                    x = rnd(mdata(0));
                    y = rnd(mdata(1));
                    if (map(x, y, 1) != 0)
                    {
                        map(x, y, 1) = 0;
                    }
                }
            }
        }
        else
        {
            x = rnd(mdata(0) - 4) + 2;
            y = rnd(mdata(1) - 4) + 2;
            if (cxinit >= 0)
            {
                if (cnt == 0)
                {
                    x = cxinit;
                    y = cyinit;
                }
                else
                {
                    x = cxinit + rnd((cnt + 1)) - rnd((cnt + 1));
                    y = cyinit + rnd((cnt + 1)) - rnd((cnt + 1));
                }
            }
            if (cnt < 20)
            {
                if (cxinit == -2)
                {
                    p = cdata[0].vision_distance / 2;
                    if (x >= cdata[0].position.x - p
                        && x <= cdata[0].position.x + p)
                    {
                        if (y >= cdata[0].position.y - p
                            && y <= cdata[0].position.y + p)
                        {
                            continue;
                        }
                    }
                }
            }
        }
        if (x < 0 || y < 0 || x >= mdata(0) || y >= mdata(1))
        {
            continue;
        }
        if (chipm(7, map(x, y, 0)) & 4)
        {
            continue;
        }
        if (map(x, y, 1) != 0)
        {
            continue;
        }
        if (map(x, y, 6) != 0)
        {
            if (chipm(7, map(x, y, 6) % 1000) & 4)
            {
                continue;
            }
            cell_featread(x, y);
            if (feat(1) == 11)
            {
                if (rc != 0)
                {
                    if (cxinit < 0)
                    {
                        continue;
                    }
                }
            }
            if (feat(1) == 10)
            {
                if (rc != 0)
                {
                    if (cxinit < 0)
                    {
                        continue;
                    }
                }
            }
        }
        cdata[rc].initial_position.x = x;
        cdata[rc].initial_position.y = y;
        map(x, y, 1) = rc + 1;
        cdata[rc].position.x = x;
        cdata[rc].position.y = y;
        p = 1;
        break;
    }
    if (placefail == 1)
    {
        if (rc < 16)
        {
            cdata[rc].state = 8;
            txt(lang(
                name(rc) + u8"とはぐれた。"s,
                name(rc) + u8" loses "s + his(rc) + u8" way."s));
        }
        else
        {
            txt(lang(
                name(rc) + u8"は何かに潰されて息絶えた。"s,
                name(rc) + u8" is killed."s));
            cdata[rc].state = 0;
            // Exclude town residents because they occupy character slots even
            // if they are dead.
            modify_crowd_density(rc, -1);
        }
        if (cdata[rc].character_role != 0)
        {
            cdata[rc].state = 2;
        }
        if (cdata[rc].character_role == 13)
        {
            cdata[rc].state = 4;
            cdata[rc].time_to_revive = gdata_hour + gdata_day * 24
                + gdata_month * 24 * 30 + gdata_year * 24 * 30 * 12 + 24
                + rnd(12);
        }
    }
    return;
}


int chara_create_internal()
{
    if (rc == -1)
    {
        rc = chara_get_free_slot();
        if (rc == -1)
        {
            rc = 56;
            return 0;
        }
    }
    chara_delete(rc);
    cequipment = 0;
    if (rc == 0)
    {
        p = 10;
    }
    else
    {
        p = 4;
    }
    if (dbid == -1)
    {
        if (fltselect == 0 && filtermax == 0 && fltnrace(0).empty())
        {
            if (fixlv == 3)
            {
                if (rnd(20) == 0)
                {
                    fltselect = 2;
                }
            }
            if (fixlv == 4)
            {
                if (rnd(10) == 0)
                {
                    fltselect = 2;
                }
            }
        }
        dbmode = 1;
        get_random_npc_id();
        if (dbid == 0)
        {
            if (fltselect == 2 || fixlv == 6)
            {
                fixlv = 4;
            }
            flt(objlv + 10, fixlv);
            dbmode = 1;
            get_random_npc_id();
        }
    }
    else if (dbid == 343)
    {
        if (usernpcmax > 0)
        {
            cdata[rc].cnpc_id = rnd(usernpcmax);
        }
    }
    chara_createhack = dbid + 1;
    cm = 1;
    cmshade = 0;
    ++npcmemory(1, dbid);
    if (dbid == 323)
    {
        if (rnd(5))
        {
            objlv *= 2;
            if (fixlv >= 4)
            {
                fixlv = 3;
            }
            cmshade = 1;
            flt(objlv, fixlv);
            dbmode = 1;
            get_random_npc_id();
        }
    }
    if (gdata_current_map == 42)
    {
        if (!novoidlv)
        {
            voidlv = gdata_current_dungeon_level / 50 * 50;
        }
    }
    novoidlv = 0;
    if (dbid == 343)
    {
        create_cnpc();
    }
    else
    {
        dbmode = 3;
        access_character_info();
    }
    if (cmshade)
    {
        cdatan(0, rc) = lang(u8"シェイド"s, u8"shade"s);
        cdata[rc].image = 280;
    }
    cdata[rc].quality = fixlv;
    cdata[rc].index = rc;
    initialize_character();
    rtval = rc;
    return 1;
}


int chara_create(int prm_756, int prm_757, int prm_758, int prm_759)
{
    chara_createhack = -1;
    if (prm_758 == -3)
    {
        cxinit = -1;
        cyinit = -1;
    }
    else
    {
        cxinit = prm_758;
        cyinit = prm_759;
    }
    if (prm_757 == 0)
    {
        dbid = -1;
    }
    else
    {
        dbid = prm_757;
    }
    rc = prm_756;
    int stat = chara_create_internal();
    initlv = 0;
    voidlv = 0;
    chara_createhack = 0;
    if (stat == 1)
    {
        if (rc == 56)
        {
            cdata[rc].state = 0;
            --npcmemory(1, cdata[rc].id);
            return 1;
        }
        if (rc != 0)
        {
            if (prm_758 != -1)
            {
                chara_place();
            }
        }
    }
    else
    {
        rc = 56;
        return 0;
    }
    return 1;
}

void chara_refresh(int cc)
{
    int rp = 0;
    int rp2 = 0;
    int rp3 = 0;
    if (cc == 0)
    {
        gdata_seven_league_boot_effect = 0;
        gdata_ether_disease_speed = 0;
        gdata_protects_from_etherwind = 0;
        gdata_protects_from_bad_weather = 0;
        gdata(89) = 70;
        gdata_catches_god_signal = 0;
        gdata_reveals_religion = 0;
    }
    for (int cnt = 0; cnt < 600; ++cnt)
    {
        sdata(cnt, cc) = sdata.get(cnt, cc).original_level;
    }
    if (cc == 0)
    {
        cdata(cc).clear_flags();
        if (trait(161) != 0)
        {
            for (int i = 0; i < 30; ++i)
            {
                if (cdata_body_part(cc, i) % 10000 == 0)
                {
                    continue;
                }
                rp = cdata_body_part(cc, i) % 10000 - 1;
                if (inv[rp].weight >= 1000)
                {
                    cdata_body_part(cc, i) =
                        cdata_body_part(cc, i) / 10000 * 10000;
                    inv[rp].body_part = 0;
                }
            }
        }
    }
    else if (cdata[cc].id == 343)
    {
        for (size_t i = 0; i < 32 * 30; ++i)
        {
            cdata[cc]._flags[i] =
                userdata(40 + i / (8 * sizeof(int)), cdata[cc].cnpc_id)
                & (1 << (i % (8 * sizeof(int))));
        }
    }
    else
    {
        for (size_t i = 0; i < 32 * 30; ++i)
        {
            cdata[cc]._flags[i] = the_character_db[cdata[cc].id]->_flags[i];
        }
    }
    for (int cnt = 10; cnt < 20; ++cnt)
    {
        cdata[cc].growth_buffs[cnt - 10] = 0;
    }
    cdata[cc].dv = 0;
    cdata[cc].pv = 0;
    cdata[cc].hit_bonus = 0;
    cdata[cc].damage_bonus = 0;
    cdata[cc].equipment_type = 0;
    attacknum = 0;
    cdata[cc].rate_to_pierce = 0;
    cdata[cc].rate_of_critical_hit = 0;
    cdata[cc].curse_power = 0;
    cdata[cc].extra_attack = 0;
    cdata[cc].extra_shot = 0;
    cdata[cc].sum_of_equipment_weight = 0;
    cdata[cc].decrease_physical_damage = 0;
    cdata[cc].nullify_damage = 0;
    cdata[cc].cut_counterattack = 0;
    for (int i = 0; i < 30; ++i)
    {
        if (cdata_body_part(cc, i) % 10000 == 0)
        {
            continue;
        }
        rp = cdata_body_part(cc, i) % 10000 - 1;
        cdata[cc].sum_of_equipment_weight += inv[rp].weight;
        if (inv[rp].skill == 168)
        {
            if (!(cdata[cc].equipment_type & 1))
            {
                cdata[cc].equipment_type += 1;
            }
        }
        cdata[cc].dv += inv[rp].dv;
        cdata[cc].pv += inv[rp].pv;
        if (inv[rp].dice_x == 0)
        {
            cdata[cc].hit_bonus += inv[rp].hit_bonus;
            cdata[cc].damage_bonus += inv[rp].damage_bonus;
            cdata[cc].pv += inv[rp].enhancement * 2
                + (inv[rp].curse_state == curse_state_t::blessed) * 2;
        }
        else if (cdata_body_part(cc, i) / 10000 == 5)
        {
            ++attacknum;
        }
        if (inv[rp].curse_state == curse_state_t::cursed)
        {
            cdata[cc].curse_power += 20;
        }
        if (inv[rp].curse_state == curse_state_t::doomed)
        {
            cdata[cc].curse_power += 100;
        }
        if (inv[rp].material == 8)
        {
            if (cc == 0)
            {
                gdata_ether_disease_speed += 5;
            }
        }
        for (int cnt = 0; cnt < 15; ++cnt)
        {
            if (inv[rp].enchantments[cnt].id == 0)
            {
                break;
            }
            rp2 = inv[rp].enchantments[cnt].id;
            if (rp2 >= 10000)
            {
                rp3 = rp2 % 10000;
                rp2 = rp2 / 10000;
                if (rp2 == 1)
                {
                    sdata(rp3, cc) += inv[rp].enchantments[cnt].power / 50 + 1;
                    continue;
                }
                if (rp2 == 2)
                {
                    sdata(rp3, cc) += inv[rp].enchantments[cnt].power / 2;
                    if (sdata(rp3, cc) < 0)
                    {
                        sdata(rp3, cc) = 1;
                    }
                    continue;
                }
                if (rp2 == 3)
                {
                    if (sdata.get(rp3, cc).original_level != 0)
                    {
                        sdata(rp3, cc) +=
                            inv[rp].enchantments[cnt].power / 50 + 1;
                        if (sdata(rp3, cc) < 1)
                        {
                            sdata(rp3, cc) = 1;
                        }
                    }
                    continue;
                }
            }
            else
            {
                if (rp2 == 56)
                {
                    if (cc == 0)
                    {
                        gdata_catches_god_signal = 1;
                        continue;
                    }
                }
                if (rp2 == 59)
                {
                    if (cc == 0)
                    {
                        gdata_reveals_religion = 1;
                        continue;
                    }
                }
                if (rp2 == 29)
                {
                    sdata(18, cc) += inv[rp].enchantments[cnt].power / 50 + 1;
                    if (cc == 0)
                    {
                        gdata_seven_league_boot_effect +=
                            inv[rp].enchantments[cnt].power / 8;
                        continue;
                    }
                }
                if (rp2 == 32)
                {
                    cdata[cc].is_floating() = true;
                    continue;
                }
                if (rp2 == 35)
                {
                    cdata[cc].can_see_invisible() = true;
                    continue;
                }
                if (rp2 == 23)
                {
                    cdata[cc].is_immune_to_blindness() = true;
                    continue;
                }
                if (rp2 == 24)
                {
                    cdata[cc].is_immune_to_paralyzation() = true;
                    continue;
                }
                if (rp2 == 25)
                {
                    cdata[cc].is_immune_to_confusion() = true;
                    continue;
                }
                if (rp2 == 26)
                {
                    cdata[cc].is_immune_to_fear() = true;
                    continue;
                }
                if (rp2 == 27)
                {
                    cdata[cc].is_immune_to_sleep() = true;
                    continue;
                }
                if (rp2 == 28)
                {
                    cdata[cc].is_immune_to_poison() = true;
                    continue;
                }
                if (rp2 == 42)
                {
                    cdata[cc].can_digest_rotten_food() = true;
                    continue;
                }
                if (rp2 == 41)
                {
                    cdata[cc].is_protected_from_thieves() = true;
                    continue;
                }
                if (rp2 == 55)
                {
                    cdata[cc].cures_bleeding_quickly() = true;
                    continue;
                }
                if (rp2 == 52)
                {
                    cdata[cc].decrease_physical_damage +=
                        inv[rp].enchantments[cnt].power / 40 + 5;
                    continue;
                }
                if (rp2 == 53)
                {
                    cdata[cc].nullify_damage +=
                        inv[rp].enchantments[cnt].power / 60 + 3;
                    continue;
                }
                if (rp2 == 54)
                {
                    cdata[cc].cut_counterattack +=
                        inv[rp].enchantments[cnt].power / 5;
                    continue;
                }
                if (rp2 == 44)
                {
                    cdata[cc].rate_of_critical_hit +=
                        inv[rp].enchantments[cnt].power / 50;
                    continue;
                }
                if (rp2 == 39)
                {
                    cdata[cc].rate_to_pierce +=
                        inv[rp].enchantments[cnt].power / 50;
                    continue;
                }
                if (rp2 == 50)
                {
                    cdata[cc].extra_attack +=
                        inv[rp].enchantments[cnt].power / 15;
                    continue;
                }
                if (rp2 == 51)
                {
                    cdata[cc].extra_shot +=
                        inv[rp].enchantments[cnt].power / 15;
                    cdata[cc].extra_shot = 100;
                    continue;
                }
                if (rp2 == 21 || rp2 == 45 || rp2 == 46 || rp2 == 47)
                {
                    cdata[cc].has_cursed_equipments() = true;
                    continue;
                }
                if (cc == 0)
                {
                    if (rp2 == 30)
                    {
                        gdata_protects_from_etherwind = 1;
                        continue;
                    }
                    if (rp2 == 31)
                    {
                        gdata_protects_from_bad_weather = 1;
                        continue;
                    }
                }
            }
        }
    }
    if (refreshmode == 1)
    {
        buff += u8"\n"s;
        buff += u8"<title1>◆ 装備による能力の修正<def>\n"s;
        for (int cnt = 0; cnt < 600; ++cnt)
        {
            sdata(cnt, 56) = sdata.get(cnt, cc).original_level;
            if (sdata(cnt, 56) != sdata(cnt, cc))
            {
                rp = sdata(cnt, cc) - sdata(cnt, 56);
                cnvbonus(cnt, rp);
            }
        }
    }
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        if (cdata[cc].attr_adjs[cnt] != 0)
        {
            if (cdata[cc].quality >= 4)
            {
                if (cdata[cc].attr_adjs[cnt]
                    < sdata.get(10 + cnt, cc).original_level / 5)
                {
                    cdata[cc].attr_adjs[cnt] =
                        sdata.get(10 + cnt, cc).original_level / 5;
                }
            }
            sdata(10 + cnt, cc) += cdata[cc].attr_adjs[cnt];
        }
        if (sdata(10 + cnt, cc) < 1)
        {
            sdata(10 + cnt, cc) = 1;
        }
    }
    if (cc == 0)
    {
        apply_god_blessing(cc);
        for (int cnt = 0; cnt < 217; ++cnt)
        {
            if (trait(cnt) != 0)
            {
                get_trait_info(1, cnt);
            }
        }
    }
    if (cdata[cc].equipment_type & 1)
    {
        if (cdata[cc].pv > 0)
        {
            cdata[cc].pv =
                cdata[cc].pv * (120 + int(std::sqrt(sdata(168, cc))) * 2) / 100;
        }
    }
    else if (attacknum == 1)
    {
        cdata[cc].equipment_type += 2;
    }
    else if (attacknum != 0)
    {
        cdata[cc].equipment_type += 4;
    }
    cdata[cc].max_mp =
        clamp(
            ((sdata(16, cc) * 2 + sdata(15, cc) + sdata(14, cc) / 3)
                 * cdata[cc].level / 25
             + sdata(16, cc)),
            1,
            1000000)
        * sdata(3, cc) / 100;
    cdata[cc].max_hp =
        clamp(
            ((sdata(11, cc) * 2 + sdata(10, cc) + sdata(15, cc) / 3)
                 * cdata[cc].level / 25
             + sdata(11, cc)),
            1,
            1000000)
            * sdata(2, cc) / 100
        + 5;
    cdata[cc].max_sp =
        100 + (sdata(15, cc) + sdata(11, cc)) / 5 + trait(24) * 8;
    if (cdata[cc].max_mp < 1)
    {
        cdata[cc].max_mp = 1;
    }
    if (cdata[cc].max_hp < 1)
    {
        cdata[cc].max_hp = 1;
    }
    if (cc >= ELONA_MAX_PARTY_CHARACTERS || false)
    {
        cdata[cc].dv = cdata[cc].level / 2
            + cdata[cc].dv * cdata[cc].dv_correction_value / 100
            + cdata[cc].dv_correction_value - 100;
        cdata[cc].pv = cdata[cc].level
            + (cdata[cc].pv + cdata[cc].level / 2
               + cdata[cc].pv_correction_value / 25)
                * cdata[cc].pv_correction_value / 100;
        if (cdata[cc].quality == 3)
        {
            cdata[cc].max_hp = cdata[cc].max_hp * 3 / 2;
        }
        if (cdata[cc].quality >= 4)
        {
            cdata[cc].max_hp = cdata[cc].max_hp * 5;
        }
    }
    else
    {
        cdata[cc].max_hp += 10;
    }
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        rp = cdata[cc].buffs[cnt].id;
        if (rp == 0)
        {
            break;
        }
        apply_buff(cc, rp, cdata[cc].buffs[cnt].power);
    }
    if (cdata[cc].equipment_type & 4)
    {
        cdata[cc].extra_attack += int(std::sqrt(sdata(166, cc))) * 3 / 2 + 4;
    }
    if (sdata(186, cc))
    {
        cdata[cc].rate_of_critical_hit += int(std::sqrt(sdata(186, cc))) + 2;
    }
    if (cdata[cc].rate_of_critical_hit > 30)
    {
        cdata[cc].hit_bonus += (cdata[cc].rate_of_critical_hit - 30) * 2;
        cdata[cc].rate_of_critical_hit = 30;
    }
    refresh_burden_state();
    refreshspeed(cc);
    cdata[cc].needs_refreshing_status() = false;
}

int relationbetween(int c1, int c2)
{
    if (cdata[c1].relationship >= -2)
    {
        if (cdata[c2].relationship <= -3)
        {
            return -3;
        }
    }
    else if (cdata[c2].relationship >= -2)
    {
        return -3;
    }
    return 0;
}
void rowactend(int cc)
{
    cdata[cc].continuous_action_id = 0;
    cdata[cc].continuous_action_turn = 0;
    cdata[cc].continuous_action_item = 0;
}



int chara_custom_talk(int cc, int talk_type)
{
    std::vector<std::string> talk_file_buffer;

    bool use_external_file = false;

    if (cdata[cc].has_custom_talk())
    {
        const auto filepath =
            filesystem::dir::user() / u8"talk" / cdatan(4, cc);
        if (!fs::exists(filepath))
            return 0;
        range::copy(
            fileutil::read_by_line{filepath},
            std::back_inserter(talk_file_buffer));
        use_external_file = true;
    }
    else if (cdata[cc].id == 343)
    {
        talk_file_buffer = strutil::split_lines(usertxt(cdata[cc].cnpc_id));
        use_external_file = true;
    }

    if (use_external_file)
    {
        std::string tag;
        switch (talk_type)
        {
        case 101: tag = u8"%txtAggro"s; break;
        case 103: tag = u8"%txtKilled"s; break;
        case 102: tag = u8"%txtDead"s; break;
        case 104: tag = u8"%txtWelcome"s; break;
        case 100: tag = u8"%txtCalm"s; break;
        case 106: tag = u8"%txtDialog"s; break;
        default: assert(0);
        }

        tag += u8"," + lang(u8"JP"s, u8"EN"s);
        const auto start_text = range::find_if(
            talk_file_buffer,
            [&](const auto& line) { return strutil::contains(line, tag); });
        if (start_text == std::end(talk_file_buffer))
        {
            throw std::runtime_error(u8"Error: fail to load custom talk");
        }
        const auto end_text = std::find_if(
            std::next(start_text),
            std::cend(talk_file_buffer),
            [](const auto& line) { return strutil::contains(line, u8"%"); });
        if (end_text == std::end(talk_file_buffer))
        {
            throw std::runtime_error(u8"Error: fail to load custom talk");
        }

        // Example:
        // %txtDialog,EN                              <- start_text
        // Elona Foobar is one of the Elona variants.
        // Elona is one of the rogue-like games.
        // %END                                       <- end_text
        const auto number_of_lines_plus_1 = std::distance(start_text, end_text);
        if (number_of_lines_plus_1 == 1)
        {
            throw std::runtime_error(u8"Error: fail to load custom talk");
        }
        else
        {
            std::vector<std::string> lines;
            std::copy(
                std::next(start_text), end_text, std::back_inserter(lines));
            const auto line = lines[rnd(int(lines.size()))];
            if (!line.empty())
            {
                if (talk_type == 106)
                {
                    buff = line;
                }
                else
                {
                    txtef(9);
                    txt(line);
                }
            }
        }
        return 1;
    }

    if (talk_type == 106)
        return 0;

    if (cdata[cc].can_talk != 0)
    {
        dbid = cdata[cc].id;
        dbmode = talk_type;
        access_character_info();
        return 1;
    }
    return 0;
}



int chara_find(int prm_766)
{
    p_at_m117 = 0;
    for (int cnt = ELONA_MAX_PARTY_CHARACTERS; cnt < ELONA_MAX_CHARACTERS;
         ++cnt)
    {
        if (cdata[cnt].state != 2)
        {
            if (cdata[cnt].state != 1)
            {
                continue;
            }
        }
        if (cdata[cnt].id == prm_766)
        {
            p_at_m117 = cnt;
            break;
        }
    }
    return p_at_m117;
}



int chara_find_ally(int prm_767)
{
    p_at_m117 = -1;
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        if (cdata[cnt].state != 1)
        {
            continue;
        }
        if (cdata[cnt].id == prm_767)
        {
            p_at_m117 = cnt;
            break;
        }
    }
    return p_at_m117;
}



int chara_impression_level(int impression)
{
    if (impression < 10)
        return 0;
    if (impression < 25)
        return 1;
    if (impression < 40)
        return 2;
    if (impression < 75)
        return 3;
    if (impression < 100)
        return 4;
    if (impression < 150)
        return 5;
    if (impression < 200)
        return 6;
    if (impression < 300)
        return 7;
    else
        return 8;
}



void chara_mod_impression(int cc, int delta)
{
    int level1 = chara_impression_level(cdata[cc].impression);
    if (delta >= 0)
    {
        delta = delta * 100 / (50 + level1 * level1 * level1);
        if (delta == 0)
        {
            if (level1 < rnd(10))
            {
                delta = 1;
            }
        }
    }
    cdata[cc].impression += delta;
    int level2 = chara_impression_level(cdata[cc].impression);
    if (level1 > level2)
    {
        txtef(8);
        txt(lang(
            cdatan(0, cc) + u8"との関係が<"s
                + i18n::_(u8"ui", u8"impression", u8"_"s + level2)
                + u8">になった…"s,
            u8"Your relation with "s + cdatan(0, cc) + u8" becomes <"s
                + i18n::_(u8"ui", u8"impression", u8"_"s + level2)
                + u8">..."s));
    }
    else if (level2 > level1)
    {
        if (cdata[cc].relationship != -3)
        {
            txtef(2);
            txt(lang(
                cdatan(0, cc) + u8"との関係が<"s
                    + i18n::_(u8"ui", u8"impression", u8"_"s + level2)
                    + u8">になった！"s,
                u8"Your relation with "s + cdatan(0, cc) + u8" becomes <"s
                    + i18n::_(u8"ui", u8"impression", u8"_"s + level2)
                    + u8">!"s));
        }
    }
}



void chara_vanquish(int cc)
{
    if (cc == gdata_mount)
    {
        ride_end();
    }
    else if (cdata[cc].state == 1 || cdata[cc].state == 10)
    {
        map(cdata[cc].position.x, cdata[cc].position.y, 1) = 0;
    }
    cdata[cc].state = 0;
    cdata[cc].character_role = 0;
    quest_check();
    modify_crowd_density(cc, 1);
}

int chara_copy(int prm_848)
{
    int c_at_m139 = 0;
    int f_at_m139 = 0;
    int y_at_m139 = 0;
    int x_at_m139 = 0;
    c_at_m139 = 0;
    for (int cnt = ELONA_MAX_PARTY_CHARACTERS; cnt < ELONA_MAX_CHARACTERS;
         ++cnt)
    {
        if (cdata[cnt].state == 0)
        {
            c_at_m139 = cnt;
            break;
        }
    }
    if (c_at_m139 == 0)
    {
        return 0;
    }
    f_at_m139 = 0;
    for (int cnt = 0; cnt < 8; ++cnt)
    {
        y_at_m139 =
            cdata[prm_848].position.y - rnd((cnt / 4 + 1)) + rnd((cnt / 4 + 1));
        if (y_at_m139 < 0 || y_at_m139 >= mdata(1))
        {
            continue;
        }
        x_at_m139 =
            cdata[prm_848].position.x - rnd((cnt / 4 + 1)) + rnd((cnt / 4 + 1));
        if (x_at_m139 < 0 || x_at_m139 >= mdata(0))
        {
            continue;
        }
        if (map(x_at_m139, y_at_m139, 1) == 0)
        {
            if ((chipm(7, map(x_at_m139, y_at_m139, 0)) & 4) == 0)
            {
                f_at_m139 = 1;
                break;
            }
        }
    }
    if (f_at_m139 == 0)
    {
        return 0;
    }
    chara_delete(c_at_m139);
    sdata.copy(c_at_m139, prm_848);
    cdata(c_at_m139) = cdata(prm_848);
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        cdatan(cnt, c_at_m139) = cdatan(cnt, prm_848);
    }
    map(x_at_m139, y_at_m139, 1) = c_at_m139 + 1;
    cdata[c_at_m139].position.x = x_at_m139;
    cdata[c_at_m139].position.y = y_at_m139;
    cdata[c_at_m139].impression = 0;
    cdata[c_at_m139].gold = 0;
    for (int i = 0; i < 30; ++i)
    {
        cdata_body_part(c_at_m139, i) =
            cdata_body_part(c_at_m139, i) / 10000 * 10000;
    }
    cdata[c_at_m139].original_relationship = -3;
    cdata[c_at_m139].has_own_sprite() = false;
    cdata[c_at_m139].is_livestock() = false;
    cdata[c_at_m139].is_married() = false;
    cdata[c_at_m139].is_ridden() = false;
    cdata[c_at_m139].needs_refreshing_status() = true;
    cdata[c_at_m139].is_hung_on_sand_bag() = false;

    modify_crowd_density(c_at_m139, 1);
    ++npcmemory(1, cdata[c_at_m139].id);
    return 1;
}


void chara_delete(int prm_783)
{
    for (const auto& cnt : items(prm_783))
    {
        inv[cnt].number = 0;
    }
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        cdatan(cnt, prm_783) = "";
    }
    sdata.clear(prm_783);
    cdata(prm_783).clear();
    return;
}


int chara_relocate(int prm_784, int prm_785, int prm_786)
{
    int tc_at_m125 = 0;
    int p_at_m125 = 0;
    int invrangecc_at_m125 = 0;
    int cnt2_at_m125 = 0;
    tc_at_m125 = prm_785;
    if (prm_784 == gdata_mount)
    {
        ride_end();
        cdata[prm_784].position.x = cdata[0].position.x;
        cdata[prm_784].position.y = cdata[0].position.y;
    }
    if (tc_at_m125 == -1)
    {
        f_at_m125 = 0;
        for (int cnt = ELONA_MAX_PARTY_CHARACTERS; cnt < ELONA_MAX_CHARACTERS;
             ++cnt)
        {
            if (cdata[cnt].state == 0)
            {
                f_at_m125 = 1;
                tc_at_m125 = cnt;
                break;
            }
        }
        if (f_at_m125 == 0)
        {
            for (int cnt = 0;; ++cnt)
            {
                tc_at_m125 = ELONA_MAX_PARTY_CHARACTERS
                    + rnd(ELONA_MAX_OTHER_CHARACTERS);
                if (cdata[cnt].state == 1)
                {
                    if (cdata[cnt].character_role == 0)
                    {
                        break;
                    }
                }
            }
            chara_vanquish(tc_at_m125);
        }
    }

    // Backups for changing
    position_t position;
    position_t initial_position;
    int relationship;
    int original_relationship;
    int hate;
    int enemy_id;
    int hp;
    if (prm_786 == 1)
    {
        // Change
        position = cdata[tc_at_m125].position;
        initial_position = cdata[tc_at_m125].initial_position;
        relationship = cdata[tc_at_m125].relationship;
        original_relationship = cdata[tc_at_m125].original_relationship;
        hate = cdata[tc_at_m125].hate;
        enemy_id = cdata[tc_at_m125].enemy_id;
        hp = cdata[tc_at_m125].hp;
    }
    cdata[prm_784].item_which_will_be_used = 0;
    cdata[prm_784].is_livestock() = false;
    const auto tmp = inv_getheader(prm_784);
    const auto invhead = tmp.first;
    const auto invrange = tmp.second;
    p_at_m125 = invhead;
    invrangecc_at_m125 = invrange;
    for (const auto& cnt : items(tc_at_m125))
    {
        cnt2_at_m125 = cnt;
        if (cnt == invrangecc_at_m125)
        {
            break;
        }
        if (cc == prm_784)
        {
            if (ci == p_at_m125)
            {
                ci = cnt2_at_m125;
            }
        }
        inv(cnt2_at_m125) = inv(p_at_m125);
        inv(p_at_m125).clear();
        inv[cnt].body_part = 0;
        ++p_at_m125;
    }
    sdata.copy(tc_at_m125, prm_784);
    sdata.clear(prm_784);
    cdata(tc_at_m125) = cdata(prm_784);
    cdata(prm_784).clear();
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        cdatan(cnt, tc_at_m125) = cdatan(cnt, prm_784);
        cdatan(cnt, prm_784) = "";
    }
    {
        for (int i = 0; i < 30; ++i)
        {
            cdata_body_part(tc_at_m125, i) =
                cdata_body_part(tc_at_m125, i) / 10000 * 10000;
        }
    }
    if (prm_786 == 1)
    {
        // Change
        cdata[tc_at_m125].state = 1;
        cdata[tc_at_m125].position = position;
        cdata[tc_at_m125].initial_position = initial_position;
        cdata[tc_at_m125].relationship = relationship;
        cdata[tc_at_m125].original_relationship = original_relationship;
        cdata[tc_at_m125].hate = hate;
        cdata[tc_at_m125].hp = hp;
        map(cdata[tc_at_m125].position.x, cdata[tc_at_m125].position.y, 1) =
            tc_at_m125 + 1;
    }
    else
    {
        if (prm_784 != 56)
        {
            map(cdata[tc_at_m125].position.x, cdata[tc_at_m125].position.y, 1) =
                tc_at_m125 + 1;
        }
        else
        {
            rc = tc_at_m125;
            cdata[tc_at_m125].state = 1;
            cxinit = cdata[0].position.x;
            cyinit = cdata[0].position.y;
            chara_place();
        }
        cdata[tc_at_m125].enemy_id = 0;
        cdata[tc_at_m125].hate = 0;
    }
    if (tc_at_m125 < 16)
    {
        for (int cnt = 50; cnt < 61; ++cnt)
        {
            p_at_m125 = 100;
            if (sdata.get(cnt, tc_at_m125).original_level >= 500
                || sdata.get(cnt, tc_at_m125).original_level <= 100)
            {
                p_at_m125 = sdata.get(cnt, tc_at_m125).original_level;
            }
            if (p_at_m125 > 500)
            {
                p_at_m125 = 500;
            }
            sdata.get(cnt, tc_at_m125).original_level = p_at_m125;
            sdata.get(cnt, tc_at_m125).experience = 0;
            sdata.get(cnt, tc_at_m125).potential = 0;
        }
    }
    rc = tc_at_m125;
    wear_most_valuable_equipment_for_all_body_parts();
    chara_refresh(tc_at_m125);
    if (tc_at_m125 < 57)
    {
        modify_crowd_density(prm_784, -1);
    }
    if (prm_784 < 57)
    {
        modify_crowd_density(tc_at_m125, 1);
    }
    return prm_784;
}



void chara_set_item_which_will_be_used()
{
    int category = the_item_db[inv[ci].id]->category;
    if (category == 57000 || category == 52000 || category == 53000)
    {
        cdata[rc].item_which_will_be_used = ci;
    }
    return;
}



int chara_armor_class(int cc)
{
    if (cdata[cc].sum_of_equipment_weight >= 35000)
    {
        return 169;
    }
    else if (cdata[cc].sum_of_equipment_weight >= 15000)
    {
        return 170;
    }
    else
    {
        return 171;
    }
}



bool belong_to_same_team(const character& c1, const character& c2)
{
    return (c1.relationship >= 0 && c2.relationship >= 0)
        || (c1.relationship == -1 && c2.relationship == -1)
        || (c1.relationship <= -2 && c2.relationship <= -2);
}



std::string chara_refstr(int prm_0258, int prm_0259)
{
    dbmode = 16;
    dbid = prm_0258;
    dbspec = prm_0259;
    access_character_info();
    return refstr;
}

} // namespace elona
