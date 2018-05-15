#include "god.hpp"
#include <iostream>
#include "ability.hpp"
#include "animation.hpp"
#include "audio.hpp"
#include "character.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "macro.hpp"
#include "ui.hpp"
#include "variables.hpp"


namespace elona
{


god_db the_god_db;


void txtgod(const god_id_t& id, int type)
{
    if (id.empty())
        return;

    std::string message;
    switch (type)
    {
    case 12: message = i18n::_(u8"god", id, u8"random"); break;
    case 9: message = i18n::_(u8"god", id, u8"kill"); break;
    case 10: message = i18n::_(u8"god", id, u8"night"); break;
    case 11: message = i18n::_(u8"god", id, u8"welcome"); break;
    case 5: message = i18n::_(u8"god", id, u8"believe"); break;
    case 1: message = i18n::_(u8"god", id, u8"betray"); break;
    case 2: message = i18n::_(u8"god", id, u8"take_over"); break;
    case 3: message = i18n::_(u8"god", id, u8"fail_to_take_over"); break;
    case 4: message = i18n::_(u8"god", id, u8"offer"); break;
    case 6: message = i18n::_(u8"god", id, u8"receive_gift"); break;
    case 7: message = i18n::_(u8"god", id, u8"ready_to_receive_gift"); break;
    case 8: message = i18n::_(u8"god", id, u8"ready_to_receive_gift2"); break;
    default: assert(0);
    }

    txtef(5);
    if (type == 6)
    {
    }
    txt(message);
}



int modpiety(int prm_1035)
{
    if (gdata_god_rank == 4)
    {
        if (cdata[0].piety_point >= 4000)
        {
            ++gdata_god_rank;
            txtgod(cdata[0].god_id, 8);
        }
    }
    if (gdata_god_rank == 2)
    {
        if (cdata[0].piety_point >= 2500)
        {
            ++gdata_god_rank;
            txtgod(cdata[0].god_id, 7);
        }
    }
    if (gdata_god_rank == 0)
    {
        if (cdata[0].piety_point >= 1500)
        {
            ++gdata_god_rank;
            txtgod(cdata[0].god_id, 7);
        }
    }
    if (sdata(181, 0) * 100 < cdata[0].piety_point)
    {
        txt(lang(
            u8"あなたの信仰は既に限界まで高まっている。"s,
            u8" Your God becomes indifferent to your gift."s));
        return 0;
    }
    cdata[0].piety_point += prm_1035 / (1 + (gdata_current_map == 35) * 9);
    return 1;
}



void set_npc_religion()
{
    if (!cdata[tc].god_id.empty() || cdata[tc].has_learned_words() || tc == 0)
    {
        return;
    }
    randomize(gdata_random_seed + gdata_current_map);
    cdata[tc].god_id = core_god::int2godid(rnd(8));
    randomize();
    if (cdata[tc].god_id.empty() || rnd(4) == 0)
    {
        cdata[tc].has_learned_words() = true;
    }
    return;
}



void apply_god_blessing(int cc)
{
    if (cdata[cc].god_id == core_god::mani)
    {
        if (sdata(12, cc) > 0)
        {
            sdata(12, cc) +=
                clamp(cdata[cc].piety_point / 400, 1, 8 + sdata(181, 0) / 10);
        }
        if (sdata(13, cc) > 0)
        {
            sdata(13, cc) +=
                clamp(cdata[cc].piety_point / 300, 1, 14 + sdata(181, 0) / 10);
        }
        if (sdata(154, cc) > 0)
        {
            sdata(154, cc) +=
                clamp(cdata[cc].piety_point / 500, 1, 8 + sdata(181, 0) / 10);
        }
        if (sdata(110, cc) > 0)
        {
            sdata(110, cc) +=
                clamp(cdata[cc].piety_point / 250, 1, 18 + sdata(181, 0) / 10);
        }
        if (sdata(159, cc) > 0)
        {
            sdata(159, cc) +=
                clamp(cdata[cc].piety_point / 350, 1, 8 + sdata(181, 0) / 10);
        }
        if (sdata(158, cc) > 0)
        {
            sdata(158, cc) +=
                clamp(cdata[cc].piety_point / 250, 1, 16 + sdata(181, 0) / 10);
        }
        if (sdata(176, cc) > 0)
        {
            sdata(176, cc) +=
                clamp(cdata[cc].piety_point / 300, 1, 10 + sdata(181, 0) / 10);
        }
        if (sdata(179, cc) > 0)
        {
            sdata(179, cc) +=
                clamp(cdata[cc].piety_point / 350, 1, 12 + sdata(181, 0) / 10);
        }
    }
    if (cdata[cc].god_id == core_god::lulwy)
    {
        if (sdata(13, cc) > 0)
        {
            sdata(13, cc) +=
                clamp(cdata[cc].piety_point / 450, 1, 10 + sdata(181, 0) / 10);
        }
        if (sdata(18, cc) > 0)
        {
            sdata(18, cc) +=
                clamp(cdata[cc].piety_point / 350, 1, 30 + sdata(181, 0) / 10);
        }
        if (sdata(108, cc) > 0)
        {
            sdata(108, cc) +=
                clamp(cdata[cc].piety_point / 350, 1, 16 + sdata(181, 0) / 10);
        }
        if (sdata(109, cc) > 0)
        {
            sdata(109, cc) +=
                clamp(cdata[cc].piety_point / 450, 1, 12 + sdata(181, 0) / 10);
        }
        if (sdata(157, cc) > 0)
        {
            sdata(157, cc) +=
                clamp(cdata[cc].piety_point / 450, 1, 12 + sdata(181, 0) / 10);
        }
        if (sdata(174, cc) > 0)
        {
            sdata(174, cc) +=
                clamp(cdata[cc].piety_point / 550, 1, 8 + sdata(181, 0) / 10);
        }
    }
    if (cdata[cc].god_id == core_god::itzpalt)
    {
        if (sdata(16, cc) > 0)
        {
            sdata(16, cc) +=
                clamp(cdata[cc].piety_point / 300, 1, 18 + sdata(181, 0) / 10);
        }
        if (sdata(155, cc) > 0)
        {
            sdata(155, cc) +=
                clamp(cdata[cc].piety_point / 350, 1, 15 + sdata(181, 0) / 10);
        }
        if (sdata(50, cc) > 0)
        {
            sdata(50, cc) +=
                clamp(cdata[cc].piety_point / 50, 1, 200 + sdata(181, 0) / 10);
        }
        if (sdata(51, cc) > 0)
        {
            sdata(51, cc) +=
                clamp(cdata[cc].piety_point / 50, 1, 200 + sdata(181, 0) / 10);
        }
        if (sdata(52, cc) > 0)
        {
            sdata(52, cc) +=
                clamp(cdata[cc].piety_point / 50, 1, 200 + sdata(181, 0) / 10);
        }
    }
    if (cdata[cc].god_id == core_god::ehekatl)
    {
        if (sdata(17, cc) > 0)
        {
            sdata(17, cc) +=
                clamp(cdata[cc].piety_point / 250, 1, 20 + sdata(181, 0) / 10);
        }
        if (sdata(19, cc) > 0)
        {
            sdata(19, cc) +=
                clamp(cdata[cc].piety_point / 100, 1, 50 + sdata(181, 0) / 10);
        }
        if (sdata(173, cc) > 0)
        {
            sdata(173, cc) +=
                clamp(cdata[cc].piety_point / 300, 1, 15 + sdata(181, 0) / 10);
        }
        if (sdata(164, cc) > 0)
        {
            sdata(164, cc) +=
                clamp(cdata[cc].piety_point / 350, 1, 17 + sdata(181, 0) / 10);
        }
        if (sdata(185, cc) > 0)
        {
            sdata(185, cc) +=
                clamp(cdata[cc].piety_point / 300, 1, 12 + sdata(181, 0) / 10);
        }
        if (sdata(158, cc) > 0)
        {
            sdata(158, cc) +=
                clamp(cdata[cc].piety_point / 450, 1, 8 + sdata(181, 0) / 10);
        }
    }
    if (cdata[cc].god_id == core_god::opatos)
    {
        if (sdata(10, cc) > 0)
        {
            sdata(10, cc) +=
                clamp(cdata[cc].piety_point / 450, 1, 11 + sdata(181, 0) / 10);
        }
        if (sdata(11, cc) > 0)
        {
            sdata(11, cc) +=
                clamp(cdata[cc].piety_point / 350, 1, 16 + sdata(181, 0) / 10);
        }
        if (sdata(168, cc) > 0)
        {
            sdata(168, cc) +=
                clamp(cdata[cc].piety_point / 350, 1, 15 + sdata(181, 0) / 10);
        }
        if (sdata(153, cc) > 0)
        {
            sdata(153, cc) +=
                clamp(cdata[cc].piety_point / 300, 1, 16 + sdata(181, 0) / 10);
        }
        if (sdata(163, cc) > 0)
        {
            sdata(163, cc) +=
                clamp(cdata[cc].piety_point / 350, 1, 12 + sdata(181, 0) / 10);
        }
        if (sdata(174, cc) > 0)
        {
            sdata(174, cc) +=
                clamp(cdata[cc].piety_point / 450, 1, 8 + sdata(181, 0) / 10);
        }
    }
    if (cdata[cc].god_id == core_god::jure)
    {
        if (sdata(15, cc) > 0)
        {
            sdata(15, cc) +=
                clamp(cdata[cc].piety_point / 300, 1, 16 + sdata(181, 0) / 10);
        }
        if (sdata(154, cc) > 0)
        {
            sdata(154, cc) +=
                clamp(cdata[cc].piety_point / 250, 1, 18 + sdata(181, 0) / 10);
        }
        if (sdata(155, cc) > 0)
        {
            sdata(155, cc) +=
                clamp(cdata[cc].piety_point / 400, 1, 10 + sdata(181, 0) / 10);
        }
        if (sdata(161, cc) > 0)
        {
            sdata(161, cc) +=
                clamp(cdata[cc].piety_point / 400, 1, 9 + sdata(181, 0) / 10);
        }
        if (sdata(184, cc) > 0)
        {
            sdata(184, cc) +=
                clamp(cdata[cc].piety_point / 450, 1, 8 + sdata(181, 0) / 10);
        }
        if (sdata(174, cc) > 0)
        {
            sdata(174, cc) +=
                clamp(cdata[cc].piety_point / 400, 1, 10 + sdata(181, 0) / 10);
        }
        if (sdata(164, cc) > 0)
        {
            sdata(164, cc) +=
                clamp(cdata[cc].piety_point / 400, 1, 12 + sdata(181, 0) / 10);
        }
    }
    if (cdata[cc].god_id == core_god::kumiromi)
    {
        if (sdata(13, cc) > 0)
        {
            sdata(13, cc) +=
                clamp(cdata[cc].piety_point / 400, 1, 8 + sdata(181, 0) / 10);
        }
        if (sdata(12, cc) > 0)
        {
            sdata(12, cc) +=
                clamp(cdata[cc].piety_point / 350, 1, 12 + sdata(181, 0) / 10);
        }
        if (sdata(14, cc) > 0)
        {
            sdata(14, cc) +=
                clamp(cdata[cc].piety_point / 250, 1, 16 + sdata(181, 0) / 10);
        }
        if (sdata(180, cc) > 0)
        {
            sdata(180, cc) +=
                clamp(cdata[cc].piety_point / 300, 1, 12 + sdata(181, 0) / 10);
        }
        if (sdata(178, cc) > 0)
        {
            sdata(178, cc) +=
                clamp(cdata[cc].piety_point / 350, 1, 10 + sdata(181, 0) / 10);
        }
        if (sdata(177, cc) > 0)
        {
            sdata(177, cc) +=
                clamp(cdata[cc].piety_point / 350, 1, 9 + sdata(181, 0) / 10);
        }
        if (sdata(150, cc) > 0)
        {
            sdata(150, cc) +=
                clamp(cdata[cc].piety_point / 350, 1, 8 + sdata(181, 0) / 10);
        }
    }
}



void get_god_description()
{
    buff = u8" "s;
    if (inv[ci].param1 == 1)
    {
        buff = lang(
            u8"マニは機械仕掛けの神です。マニを信仰した者は、機械や罠に対する膨大な知識を得、またそれらを効果的に利用する術を知ります。<p><p>"s,
            u8"Mani is a clockwork god of machinery. Those faithful to Mani<br>receive immense knowledge of machines and learn a way to use them<br>effectively.<p>"s);
        buff += lang(
            u8"　捧げ物: 死体 / 銃器 / 機械<p>"s,
            u8"Offering: Corpses/Guns/Machinery<p>"s);
        buff += lang(
            u8"ボーナス: 器用 / 感覚 / 銃 / 治癒 / 探知 / 宝石細工 / 鍵開け / 大工<p>"s,
            u8"   Bonus: DEX/PER/Gun/Jeweller/Lockpick/Carpentry<p>"s);
        buff += lang(
            u8"特殊能力: マニの分解術(自動:罠からマテリアルを取り出す)<p>"s,
            u8" Ability: Mani's decomposition (Passive: Extract materials<br>from traps.)<p>"s);
    }
    if (inv[ci].param1 == 2)
    {
        buff = lang(
            u8"ルルウィは風を司る女神です。ルルウィを信仰した者は、風の恩恵を受け素早く動くことが可能になります。<p><p>"s,
            u8"Lulwy is a goddess of wind. Those faithful to Lulwy receive<br>the blessing of wind and can move swiftly.<p>"s);
        buff +=
            lang(u8"　捧げ物: 死体 / 弓<p>"s, u8"Offering: Corpses/Bows<p>"s);
        buff += lang(
            u8"ボーナス: 感覚 / 速度 / 弓 / クロスボウ / 隠密 / 魔道具<p>"s,
            u8"   Bonus: PER/SPD/Bow/Crossbow/Stealth/Magic Device<p>"s);
        buff += lang(
            u8"特殊能力: ルルウィの憑依(スキル:瞬間的に高速になる)<p>"s,
            u8" Ability: Lulwy's trick (Boost your speed for a short time.)<p>"s);
    }
    if (inv[ci].param1 == 3)
    {
        buff = lang(
            u8"イツパロトルは元素を司る神です。イツパロトルを信仰した者は、魔力を大気から吸収し、元素に対する保護を受けることができます。<p><p>"s,
            u8"Itzpalt is a god of elements. Those faithful to Itzpalt are<br>protected from elemental damages and learn to absorb mana from<br>their surroundings.<p>"s);
        buff +=
            lang(u8"　捧げ物: 死体 / 杖<p>"s, u8"Offering: Corpses/Staves<p>"s);
        buff += lang(
            u8"ボーナス: 魔力 / 瞑想 / 火炎耐性 / 冷気耐性 / 電撃耐性<p>"s,
            u8"   Bonus: MAG/Meditation/RES Fire/RES Cold/RES Lightning<p>"s);
        buff += lang(
            u8"特殊能力: マナの抽出(スキル:周囲の空気からマナを吸い出す)<p>"s,
            u8" Ability: Absorb mana (Absorb mana from the air.)<p>"s);
    }
    if (inv[ci].param1 == 4)
    {
        buff = lang(
            u8"エヘカトルは幸運の女神です。エヘカトルを信仰した者は、運を味方につけます。<p><p>"s,
            u8"Ehekatl is a goddess of luck. Those faithful to Ehekatl are<br>really lucky.<p><p>"s);
        buff +=
            lang(u8"　捧げ物: 死体 / 魚<p>"s, u8"Offering: Corpses/Fish<p>"s);
        buff += lang(
            u8"ボーナス: 魅力 / 運 / 回避 / 魔力の限界 / 釣り/ 鍵開け<p>"s,
            u8"   Bonus: CHR/LUCK/Evasion/Magic Capacity/Fishing/Lockpick<p>"s);
        buff += lang(
            u8"特殊能力: エヘカトル流魔術(自動:マナの消費がランダムになる)<p>"s,
            u8" Ability: Ehekatl school of magic (Passive: Randomize casting mana<br>cost.)<p>"s);
    }
    if (inv[ci].param1 == 5)
    {
        buff = lang(
            u8"オパートスは大地の神です。オパートスを信仰した者は、高い防御力と破壊力を身につけます。<p><p>"s,
            u8"Opatos is a god of earth. Those faithful to Opatos have massive<br>strength and defense.<p><p>"s);
        buff +=
            lang(u8"　捧げ物: 死体 / 鉱石<p>"s, u8"Offering: Corpses/Ores<p>"s);
        buff += lang(
            u8"ボーナス: 腕力 / 耐久 / 盾 / 重量挙げ / 採掘 / 魔道具<p>"s,
            u8"   Bonus: STR/CON/Shield/Weight Lifting/Mining/Magic Device<p>"s);
        buff += lang(
            u8"特殊能力: オパートスの甲殻(自動:受ける物理ダメージを減らす)<p>"s,
            u8" Ability: Opatos' shell (Passive: Reduce any physical damage you<br>receive.)<p>"s);
    }
    if (inv[ci].param1 == 6)
    {
        buff = lang(
            u8"ジュアは癒しの女神です。ジュアを信仰した者は、傷ついた身体を癒すことができます。<p><p>"s,
            u8"Jure is a god of healing. Those faithful to Jure can heal wounds.<p><p>"s);
        buff +=
            lang(u8"　捧げ物: 死体 / 鉱石<p>"s, u8"Offering: Corpses/Ores<p>"s);
        buff += lang(
            u8"ボーナス: 意思 / 治癒 / 瞑想 / 解剖学 / 料理 / 魔道具 / 魔力の限界<p>"s,
            u8"   Bonus: WIL/Healing/Anatomy/Cooking/Magic Device/Magic Capacity<p>"s);
        buff += lang(
            u8"特殊能力: ジュアの祈り(スキル:失った体力を回復)<p>"s,
            u8" Ability: Prayer of Jure (Heal yourself.)<p>"s);
    }
    if (inv[ci].param1 == 7)
    {
        buff = lang(
            u8"クミロミは収穫の神です。クミロミを信仰した者は、大地の恵みを収穫し、それを加工する術を知ります。<p><p>"s,
            u8"Kumiromi is a god of harvest. Those faithful to Kumiromi receive<br>the blessings of nature.<p><p>"s);
        buff += lang(
            u8"　捧げ物: 死体 / 野菜<p>"s,
            u8"Offering: Corpses/Vegetables<p>"s);
        buff += lang(
            u8"ボーナス: 感覚 / 器用 / 習得 / 栽培 / 錬金術 / 裁縫 / 読書<p>"s,
            u8"   Bonus: PER/DEX/LER/Gardening/Alchemy/Tailoring/Literacy<p>"s);
        buff += lang(
            u8"特殊能力: 生命の輪廻(自動：腐った作物から種を取り出す)<p>"s,
            u8" Ability: Kumiromi's recycle (Passive: Extract seeds from rotten foods.)<p>"s);
    }
    return;
}



void label_1888()
{
    if (rtval == 0)
    {
        gmode(0);
        pos(0, 0);
        gcopy(4, 0, 0, windoww, windowh - inf_verh);
        gmode(2);
        render_hud();
        redraw();
        if (!cdata[0].god_id.empty())
        {
            mode = 9;
            txtef(8);
            txt(lang(
                i18n::_(u8"god", cdata[0].god_id, u8"name") + u8"は激怒した。"s,
                i18n::_(u8"god", cdata[0].god_id, u8"name")
                    + u8" is enraged."s));
            txtgod(cdata[0].god_id, 1);
            redraw();
            efid = 622;
            efp = 10000;
            tc = 0;
            magic();
            snd(63);
            mode = 0;
            await(500);
        }
        cdata[0].god_id = core_god::int2godid(inv[ci].param1);
        switch_religion();
        msg_halt();
    }
    chara_refresh(0);
    return;
}



void switch_religion()
{
    cdata[0].piety_point = 0;
    cdata[0].praying_point = 500;
    gdata_god_rank = 0;
    spact(23) = 0;
    spact(24) = 0;
    spact(25) = 0;
    if (cdata[0].god_id.empty())
    {
        txtef(5);
        txt(lang(
            u8"あなたは今や無信仰者だ。"s, u8"You are an unbeliever now."s));
    }
    else
    {
        animode = 100;
        play_animation(19);
        snd(51);
        txtef(5);
        txt(lang(
            u8"あなたは今や"s + i18n::_(u8"god", cdata[0].god_id, u8"name")
                + u8"の信者だ！"s,
            u8"You become a follower of "s
                + i18n::_(u8"god", cdata[0].god_id, u8"name") + u8"!"s));
        if (cdata[0].god_id == core_god::itzpalt)
        {
            spact(24) = 1;
        }
        if (cdata[0].god_id == core_god::jure)
        {
            spact(23) = 1;
        }
        if (cdata[0].god_id == core_god::lulwy)
        {
            spact(25) = 1;
        }
        txtgod(cdata[0].god_id, 5);
    }
    return;
}



turn_result_t do_pray()
{
    if (cdata[0].god_id.empty())
    {
        txt(lang(
            name(0) + u8"は神を信仰していないが、試しに祈ってみた。"s,
            u8"You don't believe in God."s));
        return turn_result_t::turn_end;
    }
    txtnew();
    txt(lang(u8"あなたの神に祈りを乞う？"s, u8"Really pray to your God?"s));
    ELONA_YES_NO_PROMPT();
    rtval = show_prompt(promptx, prompty, 160);
    if (rtval != 0)
    {
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    txt(lang(
        i18n::_(u8"god", cdata[0].god_id, u8"name") + u8"に祈った。"s,
        u8"You pray to "s + i18n::_(u8"god", cdata[0].god_id, u8"name")
            + u8"."s));
    if (cdata[0].piety_point < 200 || cdata[0].praying_point < 1000)
    {
        txt(lang(
            i18n::_(u8"god", cdata[0].god_id, u8"name")
                + u8"はあなたに無関心だ。"s,
            i18n::_(u8"god", cdata[0].god_id, u8"name")
                + u8" is indifferent to you."s));
        return turn_result_t::turn_end;
    }
    animode = 100;
    play_animation(19);
    snd(120);
    efid = 1120;
    efp = 100;
    tc = 0;
    magic();
    efid = 451;
    efp = 200;
    tc = 0;
    magic();
    cdata[0].praying_point = 0;
    cdata[0].piety_point = cdata[0].piety_point * 85 / 100;
    if (gdata_god_rank % 2 == 1)
    {
        txtgod(cdata[0].god_id, 6);
        if (gdata_god_rank == 1)
        {
            f = 0;
            p = 0;
            for (int cnt = 1; cnt < 16; ++cnt)
            {
                if (cdata[cnt].state != 0)
                {
                    if (cdatan(2, cnt) == u8"servant"s)
                    {
                        ++p;
                        if (p >= 2)
                        {
                            f = 1;
                            txt(lang(
                                u8"神の使徒は2匹までしか仲間にできない。"s,
                                u8"No more than 2 God's servants are allowed in your party."s));
                            break;
                        }
                    }
                }
            }
            if (f == 0)
            {
                if (chara_get_free_slot_ally() == 0)
                {
                    f = 1;
                    txt(lang(
                        u8"仲間が一杯で、神からの贈り物を受け取ることができなかった。"s,
                        u8"Your party is full. The gift is reserved."s));
                }
            }
            if (f)
            {
                txt(lang(
                    u8"この贈り物を諦める？"s,
                    u8"Do you want to decline this gift?"s));
                ELONA_YES_NO_PROMPT();
                rtval = show_prompt(promptx, prompty, 160);
                if (rtval == 0)
                {
                    ++gdata_god_rank;
                }
                return turn_result_t::turn_end;
            }
            flt();
            dbid = 0;
            txtef(4);
            if (cdata[0].god_id == core_god::mani)
            {
                dbid = 262;
                txt(lang(
                    u8"このアンドロイドはブーストした時に恐るべき力を発揮するようだ。"s,
                    u8"This android shows enormous strength when boosting."s));
            }
            if (cdata[0].god_id == core_god::lulwy)
            {
                dbid = 263;
                txt(lang(
                    u8"この黒天使はブーストした時に恐るべき力を発揮するようだ。"s,
                    u8"This black angel shows enormous strength when boosting."s));
            }
            if (cdata[0].god_id == core_god::itzpalt)
            {
                dbid = 264;
                txt(lang(
                    u8"この追放者は連続魔法を使えるようだ。"s,
                    u8"This exile can cast several spells in a row."s));
            }
            if (cdata[0].god_id == core_god::ehekatl)
            {
                dbid = 260;
                txt(lang(
                    u8"この猫に舐められた武具は、エヘカトルの祝福を授かるようだ。祝福を受けた武具にはエンチャントが一つ付与される。"s,
                    u8"Weapons and armor licked by this cat receive a blessing of Ehekatl which adds an extra enchantment."s));
            }
            if (cdata[0].god_id == core_god::opatos)
            {
                dbid = 265;
                txt(lang(
                    u8"この騎士はある程度重いものをもたせても文句をいわないようだ。"s,
                    u8"This knight can hold really heavy stuff for you."s));
            }
            if (cdata[0].god_id == core_god::jure)
            {
                dbid = 266;
                txt(lang(
                    u8"この防衛者は致死ダメージを受けた仲間をレイハンドで回復できるようだ。レイハンドは眠るたびに再使用可能になる。"s,
                    u8"This defender can use Lay on hand to heal a mortally wounded ally. The ability becomes re-useable after sleeping."s));
            }
            if (cdata[0].god_id == core_god::kumiromi)
            {
                dbid = 261;
                txt(lang(
                    u8"この妖精は食後に種を吐き出すようだ。"s,
                    u8"This fairy generates a seed after eating."s));
            }
            novoidlv = 1;
            chara_create(56, dbid, -3, 0);
            rc = 56;
            new_ally_joins();
        }
        if (gdata_god_rank == 3)
        {
            flt();
            dbid = 0;
            if (cdata[0].god_id == core_god::lulwy)
            {
                dbid = 680;
            }
            if (cdata[0].god_id == core_god::jure)
            {
                dbid = 681;
            }
            if (cdata[0].god_id == core_god::kumiromi)
            {
                dbid = 682;
            }
            if (cdata[0].god_id == core_god::mani)
            {
                dbid = 683;
            }
            if (dbid != 0)
            {
                if (itemmemory(1, dbid))
                {
                    dbid = 559;
                }
                itemcreate(
                    -1, dbid, cdata[0].position.x, cdata[0].position.y, 0);
            }
            else
            {
                nostack = 1;
                itemcreate(
                    -1, 672, cdata[0].position.x, cdata[0].position.y, 0);
                if (cdata[0].god_id == core_god::itzpalt)
                {
                    inv[ci].param1 = 165;
                }
                if (cdata[0].god_id == core_god::ehekatl)
                {
                    inv[ci].param1 = 163;
                }
                if (cdata[0].god_id == core_god::opatos)
                {
                    inv[ci].param1 = 164;
                }
            }
            if (cdata[0].god_id == core_god::jure)
            {
                flt();
                nostack = 1;
                itemcreate(
                    -1, 672, cdata[0].position.x, cdata[0].position.y, 0);
                inv[ci].param1 = 166;
            }
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
        }
        if (gdata_god_rank == 5)
        {
            flt();
            dbid = 0;
            if (cdata[0].god_id == core_god::mani)
            {
                dbid = 674;
            }
            if (cdata[0].god_id == core_god::lulwy)
            {
                dbid = 673;
            }
            if (cdata[0].god_id == core_god::itzpalt)
            {
                dbid = 676;
            }
            if (cdata[0].god_id == core_god::ehekatl)
            {
                dbid = 678;
            }
            if (cdata[0].god_id == core_god::opatos)
            {
                dbid = 679;
            }
            if (cdata[0].god_id == core_god::jure)
            {
                dbid = 677;
            }
            if (cdata[0].god_id == core_god::kumiromi)
            {
                dbid = 675;
            }
            if (itemmemory(1, dbid))
            {
                dbid = 621;
            }
            itemcreate(-1, dbid, cdata[0].position.x, cdata[0].position.y, 0);
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
        }
        ++gdata_god_rank;
    }
    return turn_result_t::turn_end;
}



turn_result_t do_offer()
{
    if (cdata[0].god_id.empty())
    {
        txt(lang(
            u8"あなたは神を信仰していないが、試しに捧げてみた。"s,
            u8"You don't believe in God."s));
        return turn_result_t::turn_end;
    }
    rowact_item(ci);
    item_separate(ci);
    txt(lang(
        u8"あなたは"s + itemname(ci) + u8"を"s
            + i18n::_(u8"god", cdata[0].god_id, u8"name")
            + u8"に捧げ、その名を唱えた。"s,
        u8"You put "s + itemname(ci)
            + u8" on the altar and mutter the name of "s
            + i18n::_(u8"god", cdata[0].god_id, u8"name") + u8"."s));
    snd(121);
    play_animation(7);
    int stat = item_find(60002);
    if (stat != -1)
    {
        ti = stat;
    }
    else
    {
        return turn_result_t::turn_end;
    }
    if (inv[ci].id == 204)
    {
        i = clamp(inv[ci].weight / 200, 1, 50);
        if (inv[ci].param3 < 0)
        {
            i = 1;
        }
    }
    else
    {
        i = 25;
    }
    if (core_god::int2godid(inv[ti].param1) != cdata[0].god_id)
    {
        f = 0;
        if (inv[ti].param1 == 0)
        {
            f = 1;
            txt(lang(
                u8"異世界で、"s + i18n::_(u8"god", cdata[0].god_id, u8"name")
                    + u8"が空白の祭壇の権利を主張した。"s,
                i18n::_(u8"god", cdata[0].god_id, u8"name")
                    + u8" claims the empty altar."s));
        }
        else
        {
            txt(lang(
                u8"異様な霧が現れ、"s
                    + i18n::_(u8"god", cdata[0].god_id, u8"name") + u8"と"s
                    + i18n::_(
                          u8"god",
                          core_god::int2godid(inv[ti].param1),
                          u8"name")
                    + u8"の幻影がせめぎあった。"s,
                u8"Strange fogs surround all over the place. You see shadows of "s
                    + i18n::_(u8"god", cdata[0].god_id, u8"name") + u8" and "s
                    + i18n::_(
                          u8"god",
                          core_god::int2godid(inv[ti].param1),
                          u8"name")
                    + u8" make a fierce dance."s));
            if (rnd(17) <= i)
            {
                f = 1;
            }
            else
            {
                f = 0;
            }
        }
        if (f == 1)
        {
            modpiety(i * 5);
            cdata[0].praying_point += i * 30;
            animode = 100;
            play_animation(19);
            snd(120);
            if (inv[ti].param1 != 0)
            {
                txt(lang(
                    u8"あなたの神の幻影は、次第に色濃くなった。"s,
                    u8"The shadow of your god slowly gets bolder."s));
            }
            txtef(5);
            txt(lang(
                i18n::_(u8"god", cdata[0].god_id, u8"name") + u8"は"s
                    + itemname(ti) + u8"を支配した。"s,
                i18n::_(u8"god", cdata[0].god_id, u8"name")
                    + u8" takes over the altar."s));
            txtgod(cdata[0].god_id, 2);
            inv[ti].param1 = core_god::godid2int(cdata[0].god_id);
        }
        else
        {
            txt(lang(
                i18n::_(u8"god", core_god::int2godid(inv[ti].param1), u8"name")
                    + u8"は祭壇を守りきった。"s,
                i18n::_(u8"god", core_god::int2godid(inv[ti].param1), u8"name")
                    + u8" keeps the altar."s));
            txtgod(core_god::int2godid(inv[ti].param1), 3);
            label_1892();
        }
    }
    else
    {
        txtef(2);
        for (int cnt = 0; cnt < 1; ++cnt)
        {
            if (i >= 15)
            {
                txt(lang(
                    itemname(ci) + u8"はまばゆく輝いて消えた。"s,
                    itemname(ci) + u8" shine"s + _s2(inv[ci].number)
                        + u8" all around and disappear"s + _s2(inv[ci].number)
                        + u8"."s));
                txtgod(cdata[0].god_id, 4);
                break;
            }
            if (i >= 10)
            {
                txt(lang(
                    itemname(ci)
                        + u8"は輝いて消え、三つ葉のクローバーがふってきた。"s,
                    itemname(ci) + u8" shine"s + _s2(inv[ci].number)
                        + u8" for a moment and disappear"s + _s2(inv[ci].number)
                        + u8". A three-leaved falls from the altar."s));
                break;
            }
            if (i >= 5)
            {
                txt(lang(
                    itemname(ci) + u8"は一瞬輝いて消えた。"s,
                    itemname(ci) + u8" shine"s + _s2(inv[ci].number)
                        + u8" for a moment and disappear"s + _s2(inv[ci].number)
                        + u8"."s));
                break;
            }
            if (i >= 1)
            {
                txt(lang(
                    itemname(ci) + u8"は消えた。"s,
                    itemname(ci) + u8" disappear"s + _s2(inv[ci].number)
                        + u8"."s));
                break;
            }
        }
        modpiety(i);
        cdata[0].praying_point += i * 7;
    }
    removeitem(ci, inv[ci].number);
    return turn_result_t::turn_end;
}



} // namespace elona
