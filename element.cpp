#include "element.hpp"
#include "ability.hpp"
#include "audio.hpp"
#include "character.hpp"
#include "elona.hpp"
#include "fov.hpp"
#include "random.hpp"
#include "variables.hpp"



namespace elona
{



int randomele()
{
    int p_at_m45 = 0;
    int i_at_m45 = 0;
    p_at_m45 = rnd(11) + 50;
    if (p_at_m45 != 1)
    {
        for (int cnt = 0, cnt_end = (the_ability_db[p_at_m45]->sdataref4);
             cnt < cnt_end;
             ++cnt)
        {
            i_at_m45 = rnd(11) + 50;
            if (the_ability_db[i_at_m45]->sdataref4
                < the_ability_db[p_at_m45]->sdataref4)
            {
                if (rnd(2) == 0)
                {
                    p_at_m45 = i_at_m45;
                }
            }
        }
    }
    return p_at_m45;
}



std::string elename(int prm_348)
{
    if (efid == 614)
    {
        return lang(u8"飢えた"s, u8"starving"s);
    }
    if (efid == 613)
    {
        return lang(u8"腐った"s, u8"rotten"s);
    }
    if (efid == 617)
    {
        return lang(u8"恐ろしい"s, u8"fearful"s);
    }
    if (efid == 618)
    {
        return lang(u8"柔らかい"s, u8"silky"s);
    }
    if (prm_348 == 50)
    {
        return lang(u8"燃える"s, u8"burning"s);
    }
    if (prm_348 == 51)
    {
        return lang(u8"冷たい"s, u8"icy"s);
    }
    if (prm_348 == 52)
    {
        return lang(u8"放電する"s, u8"electric"s);
    }
    if (prm_348 == 54)
    {
        return lang(u8"霊的な"s, u8"psychic"s);
    }
    if (prm_348 == 58)
    {
        return lang(u8"痺れる"s, u8"numb"s);
    }
    if (prm_348 == 57)
    {
        return lang(u8"震える"s, u8"shivering"s);
    }
    if (prm_348 == 55)
    {
        return lang(u8"毒の"s, u8"poisonous"s);
    }
    if (prm_348 == 56)
    {
        return lang(u8"地獄の"s, u8"infernal"s);
    }
    if (prm_348 == 59)
    {
        return lang(u8"混沌の"s, u8"chaotic"s);
    }
    if (prm_348 == 53)
    {
        return lang(u8"暗黒の"s, u8"gloomy"s);
    }
    if (prm_348 == 61)
    {
        return lang(u8"出血の"s, u8"cut"s);
    }
    if (prm_348 == 62)
    {
        return lang(u8"エーテルの"s, u8"ether"s);
    }
    return u8"?"s;
}



int eleinfo(int prm_754, int prm_755)
{
    if (prm_754 == 50)
    {
        if (prm_755 == 0)
        {
            return 3;
        }
        else
        {
            return 108;
        }
    }
    if (prm_754 == 51)
    {
        if (prm_755 == 0)
        {
            return 12;
        }
        else
        {
            return 106;
        }
    }
    if (prm_754 == 52)
    {
        if (prm_755 == 0)
        {
            return 5;
        }
        else
        {
            return 107;
        }
    }
    if (prm_754 == 59)
    {
        if (prm_755 == 0)
        {
            return 8;
        }
        else
        {
            return 114;
        }
    }
    if (prm_754 == 53)
    {
        if (prm_755 == 0)
        {
            return 4;
        }
        else
        {
            return 115;
        }
    }
    if (prm_754 == 58)
    {
        if (prm_755 == 0)
        {
            return 9;
        }
        else
        {
            return 111;
        }
    }
    if (prm_754 == 57)
    {
        if (prm_755 == 0)
        {
            return 11;
        }
        else
        {
            return 112;
        }
    }
    if (prm_754 == 54)
    {
        if (prm_755 == 0)
        {
            return 10;
        }
        else
        {
            return 113;
        }
    }
    if (prm_754 == 55)
    {
        if (prm_755 == 0)
        {
            return 2;
        }
        else
        {
            return 110;
        }
    }
    if (prm_754 == 56)
    {
        if (prm_755 == 0)
        {
            return 7;
        }
        else
        {
            return 109;
        }
    }
    if (prm_754 == 63)
    {
        if (prm_755 == 0)
        {
            return 2;
        }
        else
        {
            return 110;
        }
    }
    return 0;
}



void resistmod(int cc, int element, int delta)
{
    if (delta >= 50)
    {
        txtef(2);
        switch (element)
        {
        case 50:
            txt(lang(
                name(cc) + u8"の身体は急に火照りだした。"s,
                u8"Suddenly, "s + name(cc) + u8" feel"s + _s(cc)
                    + u8" very hot."s));
            break;
        case 51:
            txt(lang(
                name(cc) + u8"の身体は急に冷たくなった。"s,
                u8"Suddenly, "s + name(cc) + u8" feel"s + _s(cc)
                    + u8" cool."s));
            break;
        case 52:
            txt(lang(
                name(cc) + u8"の身体に電気が走った。"s,
                name(cc) + u8" "s + is(cc)
                    + u8" struck by an electric shock."s));
            break;
        case 54:
            txt(lang(
                name(cc) + u8"は急に明晰になった。"s,
                u8"Suddenly, "s + name(cc) + your(cc)
                    + u8" mind becomes very clear."s));
            break;
        case 58:
            txt(lang(
                name(cc) + u8"は急に神経が図太くなった。"s,
                name(cc) + your(cc) + u8" nerve is sharpened."s));
            break;
        case 53:
            txt(lang(
                name(cc) + u8"は急に暗闇が怖くなくなった。"s,
                name(cc) + u8" no longer fear"s + _s(cc) + u8" darkness."s));
            break;
        case 57:
            txt(lang(
                name(cc) + u8"は騒音を気にしなくなった。"s,
                name(cc) + your(cc) + u8" eardrums get thick."s));
            break;
        case 59:
            txt(lang(
                name(cc) + u8"は急にカオスを理解した。"s,
                u8"Suddenly, "s + name(cc) + u8" understand"s + _s(cc)
                    + u8" chaos."s));
            break;
        case 55:
            txt(lang(
                name(cc) + u8"の毒への耐性は強くなった。"s,
                name(cc) + u8" now "s + have(cc)
                    + u8" antibodies to poisons."s));
            break;
        case 56:
            txt(lang(
                name(cc) + u8"の魂は地獄に近づいた。"s,
                name(cc) + u8" "s + is(cc) + u8" no longer afraid"s + _s(cc)
                    + u8" of hell."s));
            break;
        case 60:
            txt(lang(
                name(cc) + u8"の皮膚は魔力のオーラに包まれた。"s,
                name(cc) + your(cc)
                    + u8" body is covered by a magical aura."s));
            break;
        default: assert(0);
        }
    }
    else if (delta <= 50 * -1)
    {
        txtef(8);
        switch (element)
        {
        case 50:
            txt(lang(
                name(cc) + u8"は急に汗をかきだした。"s,
                name(cc) + u8" sweat"s + _s(cc) + u8"."s));
            break;
        case 51:
            txt(lang(
                name(cc) + u8"は急に寒気を感じた。"s,
                name(cc) + u8" shivers"s + _s(cc) + u8"."s));
            break;
        case 52:
            txt(lang(
                name(cc) + u8"は急に電気に敏感になった。"s,
                name(cc) + u8" "s + is(cc) + u8" shocked."s));
            break;
        case 54:
            txt(lang(
                name(cc) + u8"は以前ほど明晰ではなくなった。"s,
                name(cc) + your(cc) + u8" mind becomes slippery."s));
            break;
        case 58:
            txt(lang(
                name(cc) + u8"の神経は急に萎縮した。"s,
                name(cc) + u8" become"s + _s(cc) + u8" dull."s));
            break;
        case 53:
            txt(lang(
                name(cc) + u8"は急に暗闇が怖くなった。"s,
                u8"Suddenly, "s + name(cc) + u8" fear"s + _s(cc)
                    + u8" darkness."s));
            break;
        case 57:
            txt(lang(
                name(cc) + u8"は急に辺りをうるさく感じた。"s,
                name(cc) + u8" become"s + _s(cc)
                    + u8" very sensitive to noises."s));
            break;
        case 59:
            txt(lang(
                name(cc) + u8"はカオスへの理解を失った。"s,
                name(cc) + u8" no longer understand"s + _s(cc) + u8" chaos."s));
            break;
        case 55:
            txt(lang(
                name(cc) + u8"の毒への耐性は薄れた。"s,
                name(cc) + u8" lose"s + _s(cc, true)
                    + u8" antibodies to poisons."s));
            break;
        case 56:
            txt(lang(
                name(cc) + u8"の魂は地獄から遠ざかった。"s,
                name(cc) + u8" "s + is(cc) + u8" afraid of hell."s));
            break;
        case 60:
            txt(lang(
                name(cc) + u8"の皮膚から魔力のオーラが消えた。"s,
                u8"The magical aura disappears from "s + name(cc) + your(cc)
                    + u8" body."s));
            break;
        }
    }

    sdata.get(element, cc).original_level =
        clamp(sdata.get(element, cc).original_level + delta, 50, 200);
    snd(107);
    animeload(15, cc);

    chara_refresh(cc);
}



void txteledmg(int type, int attacker, int target, int element)
{
    switch (element)
    {
    case 50:
        if (type == 0)
        {
            if (is_in_fov(target))
            {
                txt(lang(
                    name(target) + u8"は燃え上がった。"s,
                    name(target) + u8" "s + is(target) + u8" burnt."s));
            }
        }
        else if (type == 1)
        {
            txt(lang(
                u8"燃やし尽くした。"s,
                u8"burn"s + _s(attacker) + u8" "s + him(target)
                    + u8" to death."s));
        }
        else if (type == 2)
        {
            txt(lang(
                name(target) + u8"は燃え尽きて灰になった。"s,
                name(target) + u8" "s + is(target) + u8" burnt to ashes."s));
        }
        break;
    case 51:
        if (type == 0)
        {
            if (is_in_fov(target))
            {
                txt(lang(
                    name(target) + u8"は凍えた。"s,
                    name(target) + u8" "s + is(target) + u8" frozen."s));
            }
        }
        else if (type == 1)
        {
            txt(lang(
                u8"氷の塊に変えた。"s,
                u8"transform"s + _s(attacker) + u8" "s + him(target)
                    + u8" to an ice sculpture."s));
        }
        else if (type == 2)
        {
            txt(lang(
                name(target) + u8"は氷の彫像になった。"s,
                name(target) + u8" "s + is(target) + u8" frozen and turn"s
                    + _s(target) + u8" into an ice sculpture."s));
        }
        break;
    case 52:
        if (type == 0)
        {
            if (is_in_fov(target))
            {
                txt(lang(
                    name(target) + u8"に電流が走った。"s,
                    name(target) + u8" "s + is(target) + u8" shocked."s));
            }
        }
        else if (type == 1)
        {
            txt(lang(
                u8"焦げカスにした。"s,
                u8"electrocute"s + _s(attacker) + u8" "s + him(target)
                    + u8" to death."s));
        }
        else if (type == 2)
        {
            txt(lang(
                name(target) + u8"は雷に打たれ死んだ。"s,
                name(target) + u8" "s + is(target)
                    + u8" struck by lightning and die"s + _s(target) + u8"."s));
        }
        break;
    case 53:
        if (type == 0)
        {
            if (is_in_fov(target))
            {
                txt(lang(
                    name(target) + u8"は闇の力で傷ついた。"s,
                    name(target) + u8" "s + is(target)
                        + u8" struck by dark force."s));
            }
        }
        else if (type == 1)
        {
            txt(lang(
                u8"闇に飲み込んだ。"s,
                u8"let"s + _s(attacker) + u8" the depths swallow "s
                    + him(target) + u8"."s));
        }
        else if (type == 2)
        {
            txt(lang(
                name(target) + u8"は闇に蝕まれて死んだ。"s,
                name(target) + u8" "s + is(target)
                    + u8" consumed by darkness."s));
        }
        break;
    case 58:
        if (type == 0)
        {
            if (is_in_fov(target))
            {
                txt(lang(
                    name(target) + u8"の神経は傷ついた。"s,
                    name(target) + your(target) + u8" nerves are hurt."s));
            }
        }
        else if (type == 1)
        {
            txt(lang(
                u8"神経を破壊した。"s,
                u8"destroy"s + _s(attacker) + u8" "s + his(target)
                    + u8" nerves."s));
        }
        else if (type == 2)
        {
            txt(lang(
                name(target) + u8"は神経を蝕まれて死んだ。"s,
                name(target) + u8" die"s + _s(target)
                    + u8" from neurofibroma."s));
        }
        break;
    case 54:
        if (type == 0)
        {
            if (is_in_fov(target))
            {
                txt(lang(
                    name(target) + u8"は狂気に襲われた。"s,
                    name(target) + u8" suffer"s + _s(target)
                        + u8" a splitting headache."s));
            }
        }
        else if (type == 1)
        {
            txt(lang(
                u8"再起不能にした。"s,
                u8"completely disable"s + _s(attacker) + u8" "s + him(target)
                    + u8"."s));
        }
        else if (type == 2)
        {
            txt(lang(
                name(target) + u8"は発狂して死んだ。"s,
                name(target) + u8" lose"s + _s(target) + u8" "s + his(target)
                    + u8" mind and commit"s + _s(target) + u8" a suicide."s));
        }
        break;
    case 59:
        if (type == 0)
        {
            if (is_in_fov(target))
            {
                txt(lang(
                    name(target) + u8"は混沌の渦で傷ついた。"s,
                    name(target) + u8" "s + is(target)
                        + u8" hurt by chaotic force."s));
            }
        }
        else if (type == 1)
        {
            txt(lang(
                u8"混沌の渦に吸い込んだ。"s,
                u8"let"s + _s(attacker) + u8" the chaos consume "s + him(target)
                    + u8"."s));
        }
        else if (type == 2)
        {
            txt(lang(
                name(target) + u8"は混沌の渦に吸収された。"s,
                name(target) + u8" "s + is(target)
                    + u8" drawn into a chaotic vortex."s));
        }
        break;
    case 56:
        if (type == 0)
        {
            if (is_in_fov(target))
            {
                txt(lang(
                    name(target) + u8"は冥界の冷気で傷ついた。"s,
                    name(target) + u8" "s + is(target)
                        + u8" chilled by infernal squall."s));
            }
        }
        else if (type == 1)
        {
            txt(lang(
                u8"冥界に墜とした。"s,
                u8"entrap"s + _s(attacker) + u8" "s + him(target)
                    + u8" into the inferno."s));
        }
        else if (type == 2)
        {
            txt(lang(
                name(target) + u8"は冥界に墜ちた。"s,
                name(target) + u8" go"s + _s(target, true) + u8" to hell."s));
        }
        break;
    case 55:
        if (type == 0)
        {
            if (is_in_fov(target))
            {
                txt(lang(
                    name(target) + u8"は吐き気を催した。"s,
                    name(target) + u8" suffer"s + _s(target)
                        + u8" from venom."s));
            }
        }
        else if (type == 1)
        {
            txt(lang(
                u8"毒殺した。"s,
                u8"kill"s + _s(attacker) + u8" "s + him(target)
                    + u8" with poison."s));
        }
        else if (type == 2)
        {
            txt(lang(
                name(target) + u8"は毒に蝕まれて死んだ。"s,
                name(target) + u8" "s + is(target) + u8" poisoned to death."s));
        }
        break;
    case 57:
        if (type == 0)
        {
            if (is_in_fov(target))
            {
                txt(lang(
                    name(target) + u8"は轟音の衝撃を受けた。"s,
                    name(target) + u8" "s + is(target)
                        + u8" shocked by a shrill sound"s));
            }
        }
        else if (type == 1)
        {
            txt(lang(
                u8"聴覚を破壊し殺した。"s,
                u8"shatter"s + _s(attacker) + u8" "s + him(target)
                    + u8" to atoms."s));
        }
        else if (type == 2)
        {
            txt(lang(
                name(target) + u8"は朦朧となって死んだ。"s,
                name(target) + u8" resonate"s + _s(target)
                    + u8" and break up."s));
        }
        break;
    case 63:
        if (type == 0)
        {
            if (is_in_fov(target))
            {
                txt(lang(
                    name(target) + u8"は酸に焼かれた。"s,
                    name(target) + u8" "s + is(target) + u8" burnt by acid."s));
            }
        }
        else if (type == 1)
        {
            txt(lang(
                u8"ドロドロに溶かした。"s,
                u8"melt"s + _s(attacker) + u8" "s + him(target) + u8" away."s));
        }
        else if (type == 2)
        {
            txt(lang(
                name(target) + u8"は酸に焼かれ溶けた。"s,
                name(target) + u8" melt"s + _s(target) + u8"."s));
        }
        break;
    case 61:
        if (type == 0)
        {
            if (is_in_fov(target))
            {
                txt(lang(
                    name(target) + u8"は切り傷を負った。"s,
                    name(target) + u8" get"s + _s(target) + u8" a cut."s));
            }
        }
        else if (type == 1)
        {
            txt(lang(
                u8"千切りにした。"s,
                u8"cut"s + _s(attacker) + u8" "s + him(target)
                    + u8" into thin strips."s));
        }
        else if (type == 2)
        {
            txt(lang(
                name(target) + u8"は千切りになった。"s,
                name(target) + u8" "s + is(target)
                    + u8" cut into thin strips."s));
        }
        break;
    default:
        if (type == 0)
        {
            if (is_in_fov(target))
            {
                txt(lang(
                    name(target) + u8"は傷ついた。"s,
                    name(target) + u8" "s + is(target) + u8" wounded."s));
            }
        }
        else if (type == 1)
        {
            txt(lang(
                u8"殺した。"s,
                u8"kill"s + _s(attacker) + u8" "s + him(target) + u8"."s));
        }
        else if (type == 2)
        {
            txt(lang(
                name(target) + u8"は死んだ。"s,
                name(target) + u8" "s + is(target) + u8" killed."s));
        }
        break;
    }
}



} // namespace elona
