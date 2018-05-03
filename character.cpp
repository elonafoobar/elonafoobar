#include "character.hpp"
#include <cassert>
#include <type_traits>
#include "cat.hpp"
#include "elona.hpp"
#include "range.hpp"
#include "variables.hpp"

using namespace elona;



namespace elona
{


character_db the_character_db;
cdata_t cdata;



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
    : storage(245)
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


} // namespace elona
