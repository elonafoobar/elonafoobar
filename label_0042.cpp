#include "elona.hpp"
#include "variables.hpp"


namespace elona
{


int label_0042()
{
    if (tid == 24)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 3;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2(0) = lang(u8"短距離走者"s, u8"Short Distance Runner"s);
            traitrefn2(1) = lang(u8"中距離走者"s, u8"Middle Distance Runner"s);
            traitrefn2(2) = lang(u8"長距離走者"s, u8"Long Distance Runner"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"長年の特訓の成果がスタミナを高める"s,
                    u8"Years of training strengthens your stamina."s);
                traitrefn(3) = lang(
                    u8"あなたは持久力がある[スタミナ+]"s,
                    u8"You have good stamina. [Stamina+]"s);
                traitrefn(4) = lang(
                    u8"あなたはかなり持久力がある[スタミナ++]"s,
                    u8"You have very good stamina. [Stamina++]"s);
                traitrefn(5) = lang(
                    u8"あなたの持久力は恐ろしい[スタミナ上昇]"s,
                    u8"You have outstanding stamina. [Stamina+++]"s);
            }
            return 1;
        }
        return 1;
    }
    if (tid == 3)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2 = lang(u8"吸血鬼"s, u8"Vampiric Ability"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"吸血鬼の友人から血の吸い方を学ぶ"s,
                    u8"Your vampire friend teaches you how to suck blood."s);
                traitrefn(3) = lang(
                    u8"あなたは血を吸うことができる"s,
                    u8"You can suck blood now."s);
            }
            return 1;
        }
        spact(1) = 1;
        return 1;
    }
    if (tid == 40)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2 = lang(u8"指導者"s, u8"Natural Leader"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"指導を続けるうちに、仲間を一時的に強くする方法を見つける"s,
                    u8"You find how to strengthen your allies for a short time."s);
                traitrefn(3) = lang(
                    u8"あなたは仲間を一時的に強くできる"s,
                    u8"You can temporally strengthen your allies."s);
            }
            return 1;
        }
        spact(56) = 1;
        return 1;
    }
    if (tid == 13)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2 = lang(u8"空間歪曲"s, u8"Dimensional Move"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"夢の中で近くへの瞬間移動を思いつく"s,
                    u8"You hit upon an idea of insta-teleport from a dream."s);
                traitrefn(3) = lang(
                    u8"あなたは空間を曲げられる"s,
                    u8"You can insta-teleport to nearby tiles."s);
            }
            return 1;
        }
        spact(27) = 1;
        return 1;
    }
    if (tid == 14)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2 = lang(u8"火炎芸"s, u8"Fire Breath"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"酒を飲んでいるうちに火を噴けるようになる"s,
                    u8"Too much drinking makes you want to breath fire."s);
                traitrefn(3) = lang(
                    u8"あなたは口から火を噴ける"s, u8"You can breath fire."s);
            }
            return 1;
        }
        spact(2) = 1;
        return 1;
    }
    if (tid == 22)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2 = lang(u8"催眠術師"s, u8"Hypnotism"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"突如として眠りの手を覚える"s,
                    u8"Suddenly, you know how to make everyone sleep."s);
                traitrefn(3) = lang(
                    u8"あなたは催眠をかけることができる"s,
                    u8"You can hypnotize single target."s);
            }
            return 1;
        }
        spact(18) = 1;
        return 1;
    }
    if (tid == 23)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2 = lang(u8"毒の知恵"s, u8"Poison Nail"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"毒の研究の結果、毒の手を覚える"s,
                    u8"Researching poisons leads you to a method to poison others."s);
                traitrefn(3) = lang(
                    u8"あなたは毒を盛ることができる"s,
                    u8"You can poison a creature."s);
            }
            return 1;
        }
        spact(15) = 1;
        return 1;
    }
    if (tid == 21)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 2;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2(0) = lang(u8"セクシー"s, u8"Sexy"s);
            traitrefn2(1) = lang(u8"色魔"s, u8"Lady Killer"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"セクシーなポーズを学ぶ"s, u8"You learn sexy poses."s);
                traitrefn(3) = lang(
                    u8"あなたはセクシーだ[魅力+4]"s,
                    u8"You are sexy. [CHR+4]"s);
                traitrefn(4) = lang(
                    u8"あなたはとんでもない色魔だ[魅力+8] "s,
                    u8"You are a lady killer. [CHR+8]"s);
            }
            return 1;
        }
        sdata(17, 0) = std::clamp(
            sdata(17, 0) + trait(tid) * 4, int{sdata(17, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 5)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 3;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2(0) = lang(u8"腕相撲"s, u8"Arm Wrestler"s);
            traitrefn2(1) = lang(u8"腕相撲の達人"s, u8"Adept Arm Wrestler"s);
            traitrefn2(2) =
                lang(u8"腕相撲のチャンピオン"s, u8"Master Arm Wrestler"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"腕相撲の特訓で筋力を高める"s,
                    u8"Training arm wrestling increases your strength."s);
                traitrefn(3) = lang(
                    u8"あなたは腕相撲が強い[筋力+3]"s,
                    u8"You are an arm wrestler. [STR+3]"s);
                traitrefn(4) = lang(
                    u8"あなたは腕相撲の達人だ[筋力+6]"s,
                    u8"You are a good arm wrestler. [STR+6]"s);
                traitrefn(5) = lang(
                    u8"あなたは腕相撲のチャンピオンだ[筋力+9]"s,
                    u8"You are a master of arm wrestling. [STR+9]"s);
            }
            return 1;
        }
        sdata(10, 0) = std::clamp(
            sdata(10, 0) + trait(tid) * 3, int{sdata(10, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 38)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 2;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2(0) = lang(u8"見習い会計士"s, u8"Apprentice Accountant"s);
            traitrefn2(1) = lang(u8"熟練会計士"s, u8"Expert Accountant"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"会計の技能を磨き税金を減らす"s,
                    u8"Working as an accountant reduces your tax payment."s);
                traitrefn(3) = lang(
                    u8"あなたは税金の計算に強い[税金7%減]"s,
                    u8"You can set expenses off against tax. [TAX-7%]"s);
                traitrefn(4) = lang(
                    u8"あなたは税金の計算にとても強い[税金15%減]"s,
                    u8"You are good at setting expenses off against tax. [TAX-15%]"s);
            }
            return 1;
        }
        return 1;
    }
    if (tid == 39)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 2;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2(0) =
                lang(u8"見習い補給係"s, u8"Apprentice Quartermaster"s);
            traitrefn2(1) = lang(u8"熟練補給係"s, u8"Expert Quartermaster"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"補給係としての経験が、給料物資の品質を上げる"s,
                    u8"Working as a quartermaster gives you better payoff."s);
                traitrefn(3) = lang(
                    u8"あなたはたまに質の高い補給品を受け取る"s,
                    u8"You sometimes receive quality supplies."s);
                traitrefn(4) = lang(
                    u8"あなたは頻繁に質の高い補給品を受け取る"s,
                    u8"You frequently receive quality supplies."s);
            }
            return 1;
        }
        return 1;
    }
    if (tid == 42)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2 = lang(u8"祈祷師"s, u8"Exorcist"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"祈祷を捧げることで、呪いの言葉の効力を弱める"s,
                    u8"Your prayer weakens the power of cursed whisperings."s);
                traitrefn(3) = lang(
                    u8"あなたの祈りは呪いの言葉を掻き消す"s,
                    u8"Your prayer nullifies cursed whisperings."s);
            }
            return 1;
        }
        return 1;
    }
    if (tid == 9)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 3;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2(0) = lang(u8"我慢強い"s, u8"Tough"s);
            traitrefn2(1) = lang(u8"とても我慢強い"s, u8"Pretty Tough"s);
            traitrefn2(2) = lang(u8"恐ろしく我慢強い"s, u8"Awfully Tough"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"頭を壁にぶつけて耐久力を高める"s,
                    u8"Pushing your head against a wall makes you tougher."s);
                traitrefn(3) = lang(
                    u8"あなたは我慢強い[耐久+3]"s, u8"You are tough. [CON+3]"s);
                traitrefn(4) = lang(
                    u8"あなたはとても我慢強い[耐久+6]"s,
                    u8"You are pretty tough. [CON+6]"s);
                traitrefn(5) = lang(
                    u8"あなたは恐ろしく我慢強い[耐久+9]"s,
                    u8"You are awfully tough. [CON+9]"s);
            }
            return 1;
        }
        sdata(11, 0) = std::clamp(
            sdata(11, 0) + trait(tid) * 3, int{sdata(11, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 20)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 2;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2(0) = lang(u8"格闘家"s, u8"Martial Artist"s);
            traitrefn2(1) = lang(u8"拳聖"s, u8"Ken-Sei"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"ストリートファイトに興じ格闘技の技を得る"s,
                    u8"You learn tricks of martial arts from fighting in streets."s);
                traitrefn(3) = lang(
                    u8"あなたは格闘技を会得している[格闘+3]"s,
                    u8"You know martial arts. [Martial Arts+3]"s);
                traitrefn(4) = lang(
                    u8"あなたは拳聖だ[格闘+6]"s,
                    u8"You mastered martial arts. [Martial Arts+6]"s);
            }
            return 1;
        }
        sdata(106, 0) = std::clamp(
            sdata(106, 0) + trait(tid) * 3, int{sdata(106, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 12)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 2;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2(0) = lang(u8"集中"s, u8"Concentration"s);
            traitrefn2(1) = lang(u8"高い集中"s, u8"More Concentration"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"日々瞑想し詠唱技術を高める"s,
                    u8"Daily meditation increases your casting skill."s);
                traitrefn(3) = lang(
                    u8"あなたの集中力は高い[詠唱+4]"s,
                    u8"You concentrate while casting. [Casting+4]"s);
                traitrefn(4) = lang(
                    u8"あなたは極度に集中できる[詠唱+8]"s,
                    u8"You concentrate more while casting. [Casting+8]"s);
            }
            if (sorg(172, 0) == 0)
            {
                return -1;
            }
            return 1;
        }
        sdata(172, 0) = std::clamp(
            sdata(172, 0) + trait(tid) * 4, int{sdata(172, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 43)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2 = lang(u8"盾殴り"s, u8"Shield Bash"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"盾の扱いを身につけ、盾での攻撃機会を増やす"s,
                    u8"Mastering shield increases your chance of shield bash."s);
                traitrefn(3) = lang(
                    u8"あなたは盾で攻撃する機会を多く得る"s,
                    u8"You can bash with your shield more frequently."s);
            }
            if (sorg(168, 0) == 0)
            {
                return -1;
            }
            return 1;
        }
        cbitmod(30, 0, 1);
        return 1;
    }
    if (tid == 44)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2 = lang(u8"優しい笑顔"s, u8"Gentle Face"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"優しい笑顔を習得し、敵が逃げ出すのを防ぐ"s,
                    u8"Your gentle face prevents your enemies from escaping."s);
                traitrefn(3) = lang(
                    u8"あなたの攻撃は敵を恐怖させない"s,
                    u8"Your attacks don't cause enemies to run."s);
            }
            return 1;
        }
        return 1;
    }
    if (tid == 19)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 2;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2(0) = lang(u8"二刀流の習熟"s, u8"Ambidextrous"s);
            traitrefn2(1) = lang(u8"二刀流の達人"s, u8"Improved Ambidextrous"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"長年の修行により二刀流の技術を磨く"s,
                    u8"Years of training increases your two weapon fighting skill."s);
                traitrefn(3) = lang(
                    u8"あなたは複数の武器を巧みに操る[二刀流+4]"s,
                    u8"You can handle multiple weapons. [Dual Wield+4]"s);
                traitrefn(4) = lang(
                    u8"あなたは二刀流を極めている[二刀流+8]"s,
                    u8"You mastered multiple weapon style. [Two Wield+8]"s);
            }
            if (sorg(166, 0) == 0)
            {
                return -1;
            }
            return 1;
        }
        sdata(166, 0) = std::clamp(
            sdata(166, 0) + trait(tid) * 4, int{sdata(166, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 15)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 2;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2(0) = lang(u8"暗闇への適正"s, u8"Conquer Darkness"s);
            traitrefn2(1) =
                lang(u8"暗闇への強い適正"s, u8"Conquer Deep Darkness"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"地底での生活が暗黒への耐性を高める"s,
                    u8"Living in darkness makes you resistant to darkness."s);
                traitrefn(3) = lang(
                    u8"あなたは暗闇に慣れている[暗黒耐性強化]"s,
                    u8"You don't fear darkness. [RES Darkness+]"s);
                traitrefn(4) = lang(
                    u8"あなたは闇の中で生活できる[暗黒耐性強化]"s,
                    u8"You can dance in darkness. [RES Darkness++]"s);
            }
            return 1;
        }
        sdata(53, 0) = std::clamp(
            sdata(53, 0) + trait(tid) * 50 / 2, int{sdata(53, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 18)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 2;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2(0) = lang(u8"免疫"s, u8"Poison Tolerance"s);
            traitrefn2(1) = lang(u8"強い免疫"s, u8"More Poison Tolerance"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"貴族の毒見係のおかげで毒への耐性を得る"s,
                    u8"Being a taster for a noble grants you resistance to poison."s);
                traitrefn(3) = lang(
                    u8"あなたは毒に免疫がある[毒耐性強化]"s,
                    u8"You have a torerance to poison. [RES Poison+]"s);
                traitrefn(4) = lang(
                    u8"あなたには毒に強い免疫がある[毒耐性強化]"s,
                    u8"You have a strong tolerance to poison. [RES Poison++]"s);
            }
            return 1;
        }
        sdata(55, 0) = std::clamp(
            sdata(55, 0) + trait(tid) * 50 / 2, int{sdata(55, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 16)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 2;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2(0) = lang(u8"交渉上手"s, u8"Negotiator"s);
            traitrefn2(1) = lang(u8"交渉の神"s, u8"Great Negotiator"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"行商人の元で働き交渉の技術を学ぶ"s,
                    u8"Working under a trader improves your negotiation skill."s);
                traitrefn(3) = lang(
                    u8"あなたは交渉が上手い[交渉+4]"s,
                    u8"You are a negotiator. [Negotiation+4]"s);
                traitrefn(4) = lang(
                    u8"あなたの交渉は神ががっている[交渉+8]"s,
                    u8"You are a great negotiator. [Negotiation+8]"s);
            }
            if (sorg(156, 0) == 0)
            {
                return -1;
            }
            return 1;
        }
        sdata(156, 0) = std::clamp(
            sdata(156, 0) + trait(tid) * 4, int{sdata(156, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 17)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 2;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2(0) = lang(u8"信者"s, u8"Believer"s);
            traitrefn2(1) = lang(u8"狂信者"s, u8"Zealot"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"神官の下で修行し信仰を深める"s,
                    u8"Training under a priest deepens your faith."s);
                traitrefn(3) = lang(
                    u8"あなたは信仰に篤い[信仰+4]"s,
                    u8"You really believe in god. [Faith+4]"s);
                traitrefn(4) = lang(
                    u8"あなたは猛烈な信者だ[信仰+8]"s,
                    u8"You are a zealot. [Faith+8]"s);
            }
            return 1;
        }
        sdata(181, 0) = std::clamp(
            sdata(181, 0) + trait(tid) * 4, int{sdata(181, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 1)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 3;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2(0) = lang(u8"幸運の持ち主"s, u8"Lucky"s);
            traitrefn2(1) = lang(u8"類稀な幸運"s, u8"Incredibly Lucky"s);
            traitrefn2(2) = lang(u8"幸運の女神の寵愛"s, u8"Goddess of Luck"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"流れ星を見て幸運を手にする"s,
                    u8"Sighting a falling star brings you luck."s);
                traitrefn(3) =
                    lang(u8"あなたは幸運の持ち主だ"s, u8"You are lucky"s);
                traitrefn(4) = lang(
                    u8"あなたは類稀な幸運の持ち主だ"s,
                    u8"You can rely on a good dose of luck."s);
                traitrefn(5) = lang(
                    u8"あなたは幸運の女神の寵愛を受けている"s,
                    u8"The goddess of luck smiles on you."s);
            }
            return 1;
        }
        sdata(19, 0) = std::clamp(
            sdata(19, 0) + trait(tid) * 5, int{sdata(19, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 2)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 5;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2(0) = lang(u8"苦行者見習い"s, u8"Apprentice Ascetic"s);
            traitrefn2(1) = lang(u8"苦行者"s, u8"Journeyman Ascetic"s);
            traitrefn2(2) = lang(u8"熟練の苦行者"s, u8"Expert Ascetic"s);
            traitrefn2(3) = lang(u8"苦行の達人"s, u8"Master Ascetic"s);
            traitrefn2(4) = lang(u8"伝説的苦行者"s, u8"Legendary Ascetic"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"苦行を通じてHPを増やす"s,
                    u8"Being an ascetic increases your HP."s);
                traitrefn(3) = lang(
                    u8"あなたは苦行者の見習いだ[HP+5%]"s,
                    u8"You are an apprentice of an ascetic. [HP+5%]"s);
                traitrefn(4) = lang(
                    u8"あなたは立派な苦行者だ[HP+10%]"s,
                    u8"You are a journeyman of an ascetic. [HP+10%]"s);
                traitrefn(5) = lang(
                    u8"あなたは熟練した苦行者だ[HP+15%]"s,
                    u8"You are an expert of an ascetic. [HP+15%]"s);
                traitrefn(6) = lang(
                    u8"あなたは苦行の達人だ[HP+20%]"s,
                    u8"You are a master of an ascetic. [HP+20%]"s);
                traitrefn(7) = lang(
                    u8"あなたは伝説的名苦行者だ[HP+25%]"s,
                    u8"You are an legendary ascetic. [HP+25%]"s);
            }
            return 1;
        }
        sdata(2, 0) = std::clamp(
            sdata(2, 0) + trait(tid) * 5, int{sdata(2, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 11)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 5;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2(0) = lang(u8"魔力の遺伝子"s, u8"Magical Gene"s);
            traitrefn2(1) = lang(u8"魔力の細胞"s, u8"Magical Cell"s);
            traitrefn2(2) = lang(u8"魔力の血液"s, u8"Magical Blood"s);
            traitrefn2(3) = lang(u8"魔力の肉体"s, u8"Magic Body"s);
            traitrefn2(4) = lang(u8"魔力の支配"s, u8"Magic Being"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"遺伝子組み換えを行いMPを増やす"s,
                    u8"You gain MP by using gene manipulation."s);
                traitrefn(3) = lang(
                    u8"あなたは魔力の遺伝子を持っている[MP+5%]"s,
                    u8"Your genes contain magic. [MP+5%]"s);
                traitrefn(4) = lang(
                    u8"あなたは魔力の細胞を持っている[MP+10%]"s,
                    u8"Your cells contain magica [MP+10%]"s);
                traitrefn(5) = lang(
                    u8"あなたには魔力の血液が流れている[MP+15%]"s,
                    u8"Your blood contain magic [MP+15%]"s);
                traitrefn(6) = lang(
                    u8"あなたの肉体は魔力を帯びている[MP+20%]"s,
                    u8"Your body is made of magic. [MP+20%]"s);
                traitrefn(7) = lang(
                    u8"あなたは魔力を支配している[MP+25%]"s,
                    u8"Magic dominats your entire body. [MP+25%"s);
            }
            return 1;
        }
        sdata(3, 0) = std::clamp(
            sdata(3, 0) + trait(tid) * 5, int{sdata(3, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 6)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 2;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2(0) = lang(u8"罠への注意"s, u8"Careful"s);
            traitrefn2(1) = lang(u8"罠への警戒"s, u8"Very Careful"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"周りを注意深く観察し、罠の発見を容易にする"s,
                    u8"You search around carefully to spot traps."s);
                traitrefn(3) = lang(
                    u8"あなたは罠に注意している[探知+3]"s,
                    u8"You are cautious about traps. [Detection+3]"s);
                traitrefn(4) = lang(
                    u8"あなたは罠に警戒している[探知+6]"s,
                    u8"You are very cautious about traps. [Detection+6]"s);
            }
            if (sdata(159, 0) == 0)
            {
                return -1;
            }
            return 1;
        }
        sdata(159, 0) = std::clamp(
            sdata(159, 0) + trait(tid) * 3, int{sdata(159, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 4)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 2;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2(0) = lang(u8"俊足"s, u8"Agile"s);
            traitrefn2(1) = lang(u8"韋駄天"s, u8"Very Agile"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"猫を追いかけて速くなる"s,
                    u8"Chasing cats increases your speed."s);
                traitrefn(3) = lang(
                    u8"あなたは速く走ることができる[速度+5]"s,
                    u8"You can run fast. [SPD+5]"s);
                traitrefn(4) = lang(
                    u8"あなたは猫よりも速い[速度+10]"s,
                    u8"You can run faster than a cat. [SPD+10]"s);
            }
            if (trait(tid) == 1)
            {
                if (cdata_level(0) < 5)
                {
                    return -1;
                }
            }
            return 1;
        }
        sdata(18, 0) = std::clamp(
            sdata(18, 0) + trait(tid) * 5, int{sdata(18, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 7)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 3;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2(0) = lang(u8"石の守備"s, u8"Stone Defense"s);
            traitrefn2(1) = lang(u8"鉄の守備"s, u8"Iron Defense"s);
            traitrefn2(2) = lang(u8"鋼の守備"s, u8"Steel Defense"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"受身を会得しPVを上昇させる"s,
                    u8"You establish your own defensive style."s);
                traitrefn(3) = lang(
                    u8"あなたの防御は石のように硬い[PV+5]"s,
                    u8"Your defense is as hard as stone. [PV+5]"s);
                traitrefn(4) = lang(
                    u8"あなたの守備は鉄壁だ[PV+10]"s,
                    u8"Your defense is as hard as iron. [PV+10]"s);
                traitrefn(5) = lang(
                    u8"あなたの防御は鋼のように固い[PV+15]"s,
                    u8"Your defense is as hard as steel. [PV+15]"s);
            }
            if (trait(tid) == 1)
            {
                if (cdata_level(0) < 5)
                {
                    return -1;
                }
            }
            return 1;
        }
        cdata_pv(0) = std::clamp(
            cdata_pv(0) + trait(tid) * 5, int{cdata_pv(0) > 0}, 9999);
        return 1;
    }
    if (tid == 8)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 3;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2(0) = lang(u8"見極め"s, u8"Dodge"s);
            traitrefn2(1) = lang(u8"見極めの熟練者"s, u8"Improved Dodge"s);
            traitrefn2(2) = lang(u8"見極めの達人"s, u8"Greater Dodge"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"敵の動きを見極めDVを上昇させる"s,
                    u8"You learn how to dodge attacks."s);
                traitrefn(3) = lang(
                    u8"あなたは見切れる[DV+4]"s,
                    u8"You can somewhat dodge enemy attacks. [DV+4]"s);
                traitrefn(4) = lang(
                    u8"あなたはかなり見切れる[DV+8]"s,
                    u8"You can dodge enemy attacks. [DV+8]"s);
                traitrefn(5) = lang(
                    u8"あなたの見切りは伝説的だ[DV+12]"s,
                    u8"You can really dodge enemy attacks. [DV+12]"s);
            }
            return 1;
        }
        cdata_dv(0) = std::clamp(
            cdata_dv(0) + trait(tid) * 4, int{cdata_dv(0) > 0}, 9999);
        return 1;
    }
    if (tid == 10)
    {
        if (traitmode == 0)
        {
            traitref(0) = 0;
            traitref(1) = 0;
            traitref(2) = 3;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            traitrefn2(0) = lang(u8"回避の修練者"s, u8"Evade"s);
            traitrefn2(1) = lang(u8"回避の熟練者"s, u8"Improved Evade"s);
            traitrefn2(2) = lang(u8"回避の達人"s, u8"Greater Evade"s);
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(
                    u8"回避の技術に磨きをかける"s,
                    u8"You improve your evasion skill."s);
                traitrefn(3) = lang(
                    u8"あなたは回避に長けている[回避+2]"s,
                    u8"You can somewhat evade enemy attacks. [Evasion+2]"s);
                traitrefn(4) = lang(
                    u8"あなたは華麗に回避する[回避+4]"s,
                    u8"You can evade enemy attacks. [Evasion+4]"s);
                traitrefn(5) = lang(
                    u8"あなたは回避の達人だ[回避+6]"s,
                    u8"You can really evade enemy attacks. [Evasion+6]"s);
            }
            if (sorg(173, 0) == 0)
            {
                return -1;
            }
            return 1;
        }
        sdata(173, 0) = std::clamp(
            sdata(173, 0) + trait(tid) * 2, int{sdata(173, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 41)
    {
        if (traitmode == 0)
        {
            traitref(0) = 1;
            traitref(1) = 0;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(u8"カンニバリズム"s, u8"Cannibalism"s);
                traitrefn(3) = lang(
                    u8"あなたは人肉を食べることに抵抗がない"s,
                    u8"You have no trouble eating human flesh."s);
            }
            traitrefn(0) = lang(
                u8"あなたは人肉の味の虜になった。"s,
                u8"You are charmed by the flavor of human flesh."s);
            traitrefn(1) = lang(
                u8"あなたは人肉の味に飽きた。"s,
                u8"You can no longer accept human flesh."s);
            return 1;
        }
        return 1;
    }
    if (tid == 25)
    {
        if (traitmode == 0)
        {
            traitref(0) = 1;
            traitref(1) = -3;
            traitref(2) = 3;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(u8"鉄の皮膚"s, u8"Iron Skin"s);
                traitrefn(3) = lang(
                    u8"あなたの皮膚は硬い[PV+3]"s,
                    u8"Your skin is hard. [PV+3]"s);
                traitrefn(4) = lang(
                    u8"あなたの皮膚はとても硬い[PV+6]"s,
                    u8"Your skin is very hard. [PV+6]"s);
                traitrefn(5) = lang(
                    u8"あなたは鉄のような皮膚を持っている[PV+9]"s,
                    u8"Your skin is as hard as iron. [PV+9]"s);
            }
            if (trait(tid) < 0)
            {
                traitrefn(2) = lang(u8"アルビノ"s, u8"Albino"s);
                traitrefn(3) = lang(
                    u8"あなたの皮膚は白い[PV-3]"s,
                    u8"Your skin is white. [PV-3]"s);
                traitrefn(4) = lang(
                    u8"あなたの皮膚は脆い[PV-6]"s,
                    u8"Your skin is fragile. [PV-6]"s);
                traitrefn(5) = lang(
                    u8"あなたの皮膚は崩れている[PV-9]"s,
                    u8"Your skin is collapsing. [PV-9]"s);
            }
            traitrefn(0) = lang(
                u8"あなたの皮膚は硬くなった。"s,
                u8"Your skin becomes harder."s);
            traitrefn(1) = lang(
                u8"あなたの皮膚は薄くなった。"s, u8"Your skin becomes pale."s);
            return 1;
        }
        cdata_pv(0) += trait(tid) * 3;
        return 1;
    }
    if (tid == 26)
    {
        if (traitmode == 0)
        {
            traitref(0) = 1;
            traitref(1) = -3;
            traitref(2) = 3;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(u8"しなやかな関節"s, u8"Flexible Joint"s);
                traitrefn(3) = lang(
                    u8"あなたの関節はしなやかだ[器用+3]"s,
                    u8"Your joints are flexible. [DEX+3]"s);
                traitrefn(4) = lang(
                    u8"あなたの関節はとてもしなやかだ[器用+6]"s,
                    u8"Your joints are very flexible. [DEX+6]"s);
                traitrefn(5) = lang(
                    u8"あなたの関節は驚くほどしなやかだ[器用+9]"s,
                    u8"Your joints are incredibly flexible. [DEX+9]"s);
            }
            if (trait(tid) < 0)
            {
                traitrefn(2) = lang(u8"きしむ関節"s, u8"Creaking Joint"s);
                traitrefn(3) = lang(
                    u8"あなたの関節はきしむ[器用-3]"s,
                    u8"Your joints creak. [DEX-3]"s);
                traitrefn(4) = lang(
                    u8"あなたは関節痛に悩んでいる[器用-6]"s,
                    u8"You are worrying about your joint creakings. [DEX-6]"s);
                traitrefn(5) = lang(
                    u8"あなたはひどい関節痛を抱えている[器用-9]"s,
                    u8"You have terrible joint creakings. [DEX-9]"s);
            }
            traitrefn(0) = lang(
                u8"あなたの関節はしなやかになった。"s,
                u8"Your joints become flexible."s);
            traitrefn(1) =
                lang(u8"あなたの関節は痛み出した。"s, u8"Your joints creak."s);
            return 1;
        }
        sdata(12, 0) = std::clamp(
            sdata(12, 0) + trait(tid) * 3, int{sdata(12, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 27)
    {
        if (traitmode == 0)
        {
            traitref(0) = 1;
            traitref(1) = -2;
            traitref(2) = 2;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(u8"トロールの血"s, u8"Troll Blood"s);
                traitrefn(3) = lang(
                    u8"あなたの傷跡は再生する[自然治癒強化]"s,
                    u8"Your wounds regenerate rapidly. [Regeneration+]"s);
                traitrefn(4) = lang(
                    u8"あなたの傷は瞬く間にふさがる[自然治癒強化]"s,
                    u8"Your wounds regenerate instantly. [Regeneration++]"s);
            }
            if (trait(tid) < 0)
            {
                traitrefn(2) = lang(u8"貧血"s, u8"Anemia"s);
                traitrefn(3) = lang(
                    u8"あなたは血の気が少ない[自然治癒弱化]"s,
                    u8"You suffer from anemia. [Regeneration-]"s);
                traitrefn(4) = lang(
                    u8"あなたの顔には血の気が全くない[自然治癒弱化]"s,
                    u8"You constantly have an attack of anemia. [Regeneration--]"s);
            }
            traitrefn(0) = lang(
                u8"あなたの血液は緑っぽくなった。"s,
                u8"Suddenly your blood become greenish!"s);
            traitrefn(1) = lang(
                u8"あなたの血液は薄れた。"s, u8"Your metabolism slows down."s);
            return 1;
        }
        sdata(154, 0) = std::clamp(
            sdata(154, 0) + trait(tid) * 4, int{sdata(154, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 28)
    {
        if (traitmode == 0)
        {
            traitref(0) = 1;
            traitref(1) = -3;
            traitref(2) = 3;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(u8"しなやかな脚"s, u8"Lithe Leg"s);
                traitrefn(3) = lang(
                    u8"あなたの脚はしなやかだ[速度上昇]"s,
                    u8"You have lithe legs. [SPD+5]"s);
                traitrefn(4) = lang(
                    u8"あなたの脚はとてもしなやかだ[速度上昇]"s,
                    u8"You have very lithe legs. [SPD+10]"s);
                traitrefn(5) = lang(
                    u8"あなたの脚は理想的な形をしている[速度上昇]"s,
                    u8"You have ideal legs. [SPD+15]"s);
            }
            if (trait(tid) < 0)
            {
                traitrefn(2) = lang(u8"ねじれた脚"s, u8"Twisted Leg"s);
                traitrefn(3) = lang(
                    u8"あなたの脚はねじれている[速度下降]"s,
                    u8"Your legs are twisted. [SPD-5]"s);
                traitrefn(4) = lang(
                    u8"あなたの脚はとてもねじれている[速度下降]"s,
                    u8"Your legs are very twisted. [SPD-10]"s);
                traitrefn(5) = lang(
                    u8"あなたの脚は折れている[速度下降]"s,
                    u8"Your legs are broken. [SPD-15]"s);
            }
            traitrefn(0) = lang(
                u8"あなたの脚はしなやかになった。"s,
                u8"Your legs become lithe."s);
            traitrefn(1) =
                lang(u8"あなたの脚はねじれた。"s, u8"Your legs are twisted!"s);
            return 1;
        }
        sdata(18, 0) = std::clamp(
            sdata(18, 0) + trait(tid) * 5, int{sdata(18, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 29)
    {
        if (traitmode == 0)
        {
            traitref(0) = 1;
            traitref(1) = -3;
            traitref(2) = 3;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(u8"強い腕"s, u8"Strong Arm"s);
                traitrefn(3) = lang(
                    u8"あなたの腕はひきしまっている[筋力+3]"s,
                    u8"You have well-knit arms. [STR+3]"s);
                traitrefn(4) = lang(
                    u8"あなたの腕は強力だ[筋力+6]"s,
                    u8"You have well-muscled arms. [STR+6]"s);
                traitrefn(5) = lang(
                    u8"あなたの腕は筋肉の塊だ[筋力+9]"s,
                    u8"You have ideal arms. [STR+9]"s);
            }
            if (trait(tid) < 0)
            {
                traitrefn(2) = lang(u8"弱い腕"s, u8"Weak Arm"s);
                traitrefn(3) = lang(
                    u8"あなたの腕はたるんでいる[筋力-3]"s,
                    u8"Your arms are thin. [STR-3]"s);
                traitrefn(4) = lang(
                    u8"あなたの腕はとてもたるんでいる[筋力-6]"s,
                    u8"Your arms are very thin. [STR-6]"s);
                traitrefn(5) = lang(
                    u8"あなたの腕には筋肉がない[腕力-9]"s,
                    u8"Your arms are just decorative. [STR-9]"s);
            }
            traitrefn(0) = lang(
                u8"あなたの腕の筋肉が増えた。"s, u8"Your arms grow stronger."s);
            traitrefn(1) = lang(
                u8"あなたの腕の贅肉が増えた。"s, u8"Your arms become thin."s);
            return 1;
        }
        sdata(10, 0) = std::clamp(
            sdata(10, 0) + trait(tid) * 3, int{sdata(10, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 30)
    {
        if (traitmode == 0)
        {
            traitref(0) = 1;
            traitref(1) = -2;
            traitref(2) = 2;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(u8"美声"s, u8"Sweet Voice"s);
                traitrefn(3) = lang(
                    u8"あなたは美声を持っている[魅力+5]"s,
                    u8"Your voice is sweet.[CHR+5]"s);
                traitrefn(4) = lang(
                    u8"あなたの声は全てを魅了する[魅力+10]"s,
                    u8"Your voice charms everyone.[CHR+10]"s);
            }
            if (trait(tid) < 0)
            {
                traitrefn(2) = lang(u8"かれた声"s, u8"Husky Voice"s);
                traitrefn(3) = lang(
                    u8"あなたの声はかれている[魅力-5]"s,
                    u8"Your voice is hasky.[CHR-5]"s);
                traitrefn(4) = lang(
                    u8"あなたが喋ると皆逃げる[魅力-10]"s,
                    u8"Everyone is frightened when you talk.[CHR-10]"s);
            }
            traitrefn(0) = lang(
                u8"あなたの声はよく通る。"s, u8"Your voice becomes lovely."s);
            traitrefn(1) =
                lang(u8"あなたの声はかれた。"s, u8"Your voice becomes scary."s);
            return 1;
        }
        sdata(17, 0) = std::clamp(
            sdata(17, 0) + trait(tid) * 5, int{sdata(17, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 31)
    {
        if (traitmode == 0)
        {
            traitref(0) = 1;
            traitref(1) = -2;
            traitref(2) = 2;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(u8"脳内コンピュータ"s, u8"Brain Computer"s);
                traitrefn(3) = lang(
                    u8"あなたの脳は機械化している[暗記+4]"s,
                    u8"Your brain is mechanized.[Memorization+4]"s);
                traitrefn(4) = lang(
                    u8"あなたの脳は完璧な機械だ[暗記+8]"s,
                    u8"Your brain is fully mechanized.[Memorization+8]"s);
            }
            if (trait(tid) < 0)
            {
                traitrefn(2) = lang(u8"痴呆"s, u8"Stupid"s);
                traitrefn(3) = lang(
                    u8"あなたは少しぼけている[暗記-4]"s,
                    u8"You are stupid.[Memorization-4]"s);
                traitrefn(4) = lang(
                    u8"あなたは痴呆だ[暗記-8]"s,
                    u8"You are really stupid.[Memorization-8]"s);
            }
            traitrefn(0) = lang(
                u8"あなたの脳は機械化した。"s, u8"Your brain is mechanized!"s);
            traitrefn(1) = lang(
                u8"あなたの脳は原始化した。"s, u8"Your brain degenerates."s);
            return 1;
        }
        sdata(165, 0) = std::clamp(
            sdata(165, 0) + trait(tid) * 4, int{sdata(165, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 32)
    {
        if (traitmode == 0)
        {
            traitref(0) = 1;
            traitref(1) = -1;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(u8"魔法への耐性"s, u8"Magic Res+"s);
                traitrefn(3) = lang(
                    u8"あなたは魔法に耐性がある[魔法耐性強化]"s,
                    u8"You have resistance to magic.[RES Magic+]"s);
            }
            if (trait(tid) < 0)
            {
                traitrefn(2) = lang(u8"魔法の弱点"s, u8"Magic Res-"s);
                traitrefn(3) = lang(
                    u8"あなたは魔法に弱い[魔法耐性弱化]"s,
                    u8"You have weakness to magic.[RES Magic-]"s);
            }
            traitrefn(0) = lang(
                u8"あなたは魔法の耐性を得た。"s,
                u8"You gain resistance to magic."s);
            traitrefn(1) = lang(
                u8"あなたは魔法の耐性を失った。"s,
                u8"You lose resistance to magic."s);
            return 1;
        }
        sdata(60, 0) = std::clamp(
            sdata(60, 0) + trait(tid) * 50, int{sdata(60, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 33)
    {
        if (traitmode == 0)
        {
            traitref(0) = 1;
            traitref(1) = -1;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(u8"強い鼓膜"s, u8"Sound Res+"s);
                traitrefn(3) = lang(
                    u8"あなたの鼓膜は厚い[音耐性強化]"s,
                    u8"Your eardrums are thick.[RES Sound+]"s);
            }
            if (trait(tid) < 0)
            {
                traitrefn(2) = lang(u8"弱い鼓膜"s, u8"Sound Res-"s);
                traitrefn(3) = lang(
                    u8"あなたの鼓膜は薄い[音耐性弱化]"s,
                    u8"Your eardrums are thin.[RES Sound-]"s);
            }
            traitrefn(0) = lang(
                u8"あなたの鼓膜は厚くなった。"s,
                u8"Your eardrums become thick."s);
            traitrefn(1) = lang(
                u8"あなたの鼓膜は薄くなった。"s,
                u8"Your eardrums become thin."s);
            return 1;
        }
        sdata(57, 0) = std::clamp(
            sdata(57, 0) + trait(tid) * 50, int{sdata(57, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 34)
    {
        if (traitmode == 0)
        {
            traitref(0) = 1;
            traitref(1) = -1;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(u8"火炎耐性"s, u8"Fire Res+"s);
                traitrefn(3) = lang(
                    u8"あなたの血は滾っている[火炎耐性強化]"s,
                    u8"Your blood is boiling. [RES Fire+]"s);
            }
            if (trait(tid) < 0)
            {
                traitrefn(2) = lang(u8"火炎弱点"s, u8"Fire Res-"s);
                traitrefn(3) = lang(
                    u8"あなたの腕には鳥肌がたっている[火炎耐性弱化]"s,
                    u8"Your skin gets gooseflesh.[RES Fire-]"s);
            }
            traitrefn(0) = lang(
                u8"あなたの血は滾りだした。"s, u8"Your blood starts to boil."s);
            traitrefn(1) = lang(
                u8"あなたの腕に鳥肌がたった。"s,
                u8"Your skin gets gooseflesh."s);
            return 1;
        }
        sdata(50, 0) = std::clamp(
            sdata(50, 0) + trait(tid) * 50, int{sdata(50, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 35)
    {
        if (traitmode == 0)
        {
            traitref(0) = 1;
            traitref(1) = -1;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(u8"冷気耐性"s, u8"Cold Res+"s);
                traitrefn(3) = lang(
                    u8"あなたの皮膚には霜が付いている[冷気耐性強化]"s,
                    u8"Your skin is covered by frost.[RES Cold+]"s);
            }
            if (trait(tid) < 0)
            {
                traitrefn(2) = lang(u8"冷気弱点"s, u8"Cold Res-"s);
                traitrefn(3) = lang(
                    u8"あなたの皮膚は寒さに弱い[冷気耐性弱化]"s,
                    u8"Your skin is sheer.[RES Cold-]"s);
            }
            traitrefn(0) = lang(
                u8"あなたの皮膚は冷たくなった。"s, u8"You feel hot-headed."s);
            traitrefn(1) =
                lang(u8"あなたは汗をかきはじめた。"s, u8"You shiver."s);
            return 1;
        }
        sdata(51, 0) = std::clamp(
            sdata(51, 0) + trait(tid) * 50, int{sdata(51, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 36)
    {
        if (traitmode == 0)
        {
            traitref(0) = 1;
            traitref(1) = -1;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(u8"電撃耐性"s, u8"Lightning Res+"s);
                traitrefn(3) = lang(
                    u8"あなたは非電導体だ[電撃耐性強化]"s,
                    u8"You have resistance to lightning.[RES Lightning+]"s);
            }
            if (trait(tid) < 0)
            {
                traitrefn(2) = lang(u8"電撃弱点"s, u8"Lightning Res-"s);
                traitrefn(3) = lang(
                    u8"あなたの身体は電気を良く通す[電撃耐性弱化]"s,
                    u8"You have weakness to lightning.[RES Lightning-]"s);
            }
            traitrefn(0) = lang(
                u8"あなたは非電導体になった。"s,
                u8"You gain resistance to lightning."s);
            traitrefn(1) = lang(
                u8"あなたの身体は電気を良く通す。"s,
                u8"You lose resistance to lightning."s);
            return 1;
        }
        sdata(52, 0) = std::clamp(
            sdata(52, 0) + trait(tid) * 50, int{sdata(52, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 37)
    {
        if (traitmode == 0)
        {
            traitref(0) = 1;
            traitref(1) = -2;
            traitref(2) = 2;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = lang(u8"鷹の目"s, u8"Hawk Eye"s);
                traitrefn(3) = lang(
                    u8"あなたは猫の目をしている[感覚+5]"s,
                    u8"You have the eyes of a cat. [PER+5]"s);
                traitrefn(4) = lang(
                    u8"あなたは鷹の目をしている[感覚+10]"s,
                    u8"You have the eyes of a hawk. [PER+10]"s);
            }
            if (trait(tid) < 0)
            {
                traitrefn(2) = lang(u8"色弱"s, u8"Color Blind"s);
                traitrefn(3) = lang(
                    u8"あなたは色弱だ[感覚-5]"s,
                    u8"You are partially color-blind. [PER-5]"s);
                traitrefn(4) = lang(
                    u8"あなたは片目がない[感覚-10]"s,
                    u8"You are blind in one eye. [PER-10]"s);
            }
            traitrefn(0) =
                lang(u8"あなたの目は細くなった。"s, u8"Your eyes glow."s);
            traitrefn(1) = lang(
                u8"あなたの視力は低下した。"s, u8"Your sight is weakened."s);
            return 1;
        }
        sdata(13, 0) = std::clamp(
            sdata(13, 0) + trait(tid) * 5, int{sdata(13, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 150)
    {
        if (traitmode == 0)
        {
            traitref(0) = 2;
            traitref(1) = -2;
            traitref(2) = 2;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたは火炎に耐性がある"s,
                    u8"You have resistance to fire."s);
                traitrefn(4) = lang(
                    u8"あなたは火炎にかなりの耐性がある"s,
                    u8"You have strong resistance to fire."s);
            }
            if (trait(tid) < 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたは火炎に弱い"s, u8"You have weakness to fire."s);
                traitrefn(4) = lang(
                    u8"あなたはかなり火炎に弱い"s,
                    u8"You have strong weakness to fire."s);
            }
            return 1;
        }
        sdata(50, 0) = std::clamp(
            sdata(50, 0) + trait(tid) * 50, int{sdata(50, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 151)
    {
        if (traitmode == 0)
        {
            traitref(0) = 2;
            traitref(1) = -2;
            traitref(2) = 2;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたは冷気に耐性がある"s,
                    u8"You have resistance to cold."s);
                traitrefn(4) = lang(
                    u8"あなたは冷気にかなりの耐性がある"s,
                    u8"You have strong resistance to cold."s);
            }
            if (trait(tid) < 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたは冷気に弱い"s, u8"You have weakness to cold."s);
                traitrefn(4) = lang(
                    u8"あなたはかなり冷気に弱い"s,
                    u8"You have strong weakness to cold."s);
            }
            return 1;
        }
        sdata(51, 0) = std::clamp(
            sdata(51, 0) + trait(tid) * 50, int{sdata(51, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 152)
    {
        if (traitmode == 0)
        {
            traitref(0) = 2;
            traitref(1) = -2;
            traitref(2) = 2;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたは毒に耐性がある"s,
                    u8"You have resistance to poison."s);
                traitrefn(4) = lang(
                    u8"あなたは毒にかなりの耐性がある"s,
                    u8"You have strong resistance to poison."s);
            }
            if (trait(tid) < 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたは毒に弱い"s, u8"You have weakness to poison."s);
                traitrefn(4) = lang(
                    u8"あなたはかなり毒に弱い"s,
                    u8"You have strong weakness to poison."s);
            }
            return 1;
        }
        sdata(55, 0) = std::clamp(
            sdata(55, 0) + trait(tid) * 50, int{sdata(55, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 155)
    {
        if (traitmode == 0)
        {
            traitref(0) = 2;
            traitref(1) = -2;
            traitref(2) = 2;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたは暗黒に耐性がある"s,
                    u8"You have resistance to darkness."s);
                traitrefn(4) = lang(
                    u8"あなたは暗黒にかなりの耐性がある"s,
                    u8"You have strong resistance to darkness."s);
            }
            if (trait(tid) < 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたは暗黒に弱い"s,
                    u8"You have weakness to darkness."s);
                traitrefn(4) = lang(
                    u8"あなたはかなり暗黒に弱い"s,
                    u8"You have strong weakness to darkness."s);
            }
            return 1;
        }
        sdata(53, 0) = std::clamp(
            sdata(53, 0) + trait(tid) * 50, int{sdata(53, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 156)
    {
        if (traitmode == 0)
        {
            traitref(0) = 2;
            traitref(1) = 0;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたはマナの反動を軽減できる"s,
                    u8"You take less damages from the mana reaction."s);
            }
            return 1;
        }
        return 1;
    }
    if (tid == 160)
    {
        if (traitmode == 0)
        {
            traitref(0) = 2;
            traitref(1) = 0;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたは高い耐性をもっている"s,
                    u8"You have outstanding resistances."s);
            }
            return 1;
        }
        sdata(60, 0) =
            std::clamp(sdata(60, 0) + 150, int{sdata(60, 0) > 0}, 9999);
        sdata(52, 0) =
            std::clamp(sdata(52, 0) + 100, int{sdata(52, 0) > 0}, 9999);
        sdata(53, 0) =
            std::clamp(sdata(53, 0) + 200, int{sdata(53, 0) > 0}, 9999);
        sdata(57, 0) =
            std::clamp(sdata(57, 0) + 50, int{sdata(57, 0) > 0}, 9999);
        sdata(59, 0) =
            std::clamp(sdata(59, 0) + 100, int{sdata(59, 0) > 0}, 9999);
        sdata(54, 0) =
            std::clamp(sdata(54, 0) + 200, int{sdata(54, 0) > 0}, 9999);
        sdata(58, 0) =
            std::clamp(sdata(58, 0) + 100, int{sdata(58, 0) > 0}, 9999);
        sdata(51, 0) =
            std::clamp(sdata(51, 0) + 100, int{sdata(51, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 161)
    {
        if (traitmode == 0)
        {
            traitref(0) = 2;
            traitref(1) = 0;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたは1s以上の物を装備できない[DV上昇]"s,
                    u8"You can't wear equipment weight more than 1s. [DV++]"s);
            }
            return 1;
        }
        if (cdata_dv(0) > 0)
        {
            cdata_dv(0) = cdata_dv(0) * 125 / 100 + 50;
        }
        return 1;
    }
    if (tid == 162)
    {
        if (traitmode == 0)
        {
            traitref(0) = 2;
            traitref(1) = 0;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたは罪悪感を感じない[カルマ上限-20]"s,
                    u8"You don't feel guilty. [Karma limit -20]"s);
            }
            return 1;
        }
        return 1;
    }
    if (tid == 169)
    {
        if (traitmode == 0)
        {
            traitref(0) = 2;
            traitref(1) = 0;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたは良い心を持っている[カルマ上限+20]"s,
                    u8"You are a good man. [Karma limit +20]"s);
            }
            return 1;
        }
        return 1;
    }
    if (tid == 163)
    {
        if (traitmode == 0)
        {
            traitref(0) = 2;
            traitref(1) = 0;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたの周りでは質の高いエンチャントが生成される"s,
                    u8"Quality stuff are generated around you."s);
            }
            return 1;
        }
        return 1;
    }
    if (tid == 164)
    {
        if (traitmode == 0)
        {
            traitref(0) = 2;
            traitref(1) = 0;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたが受ける物理ダメージは軽減される"s,
                    u8"You are given physical damage reduction."s);
            }
            return 1;
        }
        return 1;
    }
    if (tid == 165)
    {
        if (traitmode == 0)
        {
            traitref(0) = 2;
            traitref(1) = 0;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたの元素魔法は強化されている"s,
                    u8"Elemental spells you cast are empowered."s);
            }
            return 1;
        }
        return 1;
    }
    if (tid == 166)
    {
        if (traitmode == 0)
        {
            traitref(0) = 2;
            traitref(1) = 0;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたは周囲の狂気を緩和する"s,
                    u8"You are surrounded by an aura that cures sanity."s);
            }
            return 1;
        }
        return 1;
    }
    if (tid == 167)
    {
        if (traitmode == 0)
        {
            traitref(0) = 2;
            traitref(1) = 0;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(u8"あなたは萌える"s, u8"You moe."s);
            }
            return 1;
        }
        return 1;
    }
    if (tid == 157)
    {
        if (traitmode == 0)
        {
            traitref(0) = 2;
            traitref(1) = 0;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたは朦朧状態にならない"s, u8"You won't be dim."s);
            }
            return 1;
        }
        return 1;
    }
    if (tid == 158)
    {
        if (traitmode == 0)
        {
            traitref(0) = 2;
            traitref(1) = 0;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたの食料の消化は遅い"s,
                    u8"Your digestion is slow."s);
            }
            return 1;
        }
        return 1;
    }
    if (tid == 159)
    {
        if (traitmode == 0)
        {
            traitref(0) = 2;
            traitref(1) = 0;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたはより多く採取できる"s,
                    u8"You can gather more materials."s);
            }
            return 1;
        }
        return 1;
    }
    if (tid == 154)
    {
        if (traitmode == 0)
        {
            traitref(0) = 2;
            traitref(1) = 0;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたには追加の成長ボーナスが与えられる"s,
                    u8"You receive extra bonus points."s);
            }
            return 1;
        }
        return 1;
    }
    if (tid == 153)
    {
        if (traitmode == 0)
        {
            traitref(0) = 2;
            traitref(1) = -2;
            traitref(2) = 2;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたは魔法に耐性がある"s,
                    u8"You have resistance to magic."s);
                traitrefn(4) = lang(
                    u8"あなたは魔法にかなりの耐性がある"s,
                    u8"You have strong resistance to magic."s);
            }
            if (trait(tid) < 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたは魔法に弱い"s, u8"You have weakness to magic."s);
                traitrefn(4) = lang(
                    u8"あなたはかなり魔法に弱い"s,
                    u8"You have strong weakness to magic."s);
            }
            return 1;
        }
        sdata(60, 0) = std::clamp(
            sdata(60, 0) + trait(tid) * 50, int{sdata(60, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 0)
    {
        if (traitmode == 0)
        {
            traitref(0) = 2;
            traitref(1) = 0;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたの肉体は刻々と変化する"s,
                    u8"Your body is changing every moment."s);
            }
            return 1;
        }
        return 1;
    }
    if (tid == 168)
    {
        if (traitmode == 0)
        {
            traitref(0) = 2;
            traitref(1) = 0;
            traitref(2) = 1;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) >= 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたのエーテル病の進行は遅い"s,
                    u8"Your body slows the Ether Disease progress."s);
            }
            return 1;
        }
        return 1;
    }
    if (tid == 201)
    {
        if (traitmode == 0)
        {
            traitref(0) = 3;
            traitref(1) = -3;
            traitref(2) = 0;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) < 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたは重力を生み出している[重量+10%]"s,
                    u8"You generate gravity. [Weight+10%]"s);
                traitrefn(4) = lang(
                    u8"あなたは大きな重力を生み出している[重量+20%]"s,
                    u8"You generate heavy gravity. [Weight+20%]"s);
                traitrefn(5) = lang(
                    u8"あなたはとてつもない重力を生み出している[重量+30%]"s,
                    u8"You generate massive gravity. [Weight+30%]"s);
            }
            traitrefn(0) = lang(
                u8"あなたの周りの重力は軽減した。"s, u8"You wieght less."s);
            traitrefn(1) = lang(
                u8"あなたは重力を発するようになった。"s,
                u8"You start to generate gravity."s);
            return 1;
        }
        return 1;
    }
    if (tid == 202)
    {
        if (traitmode == 0)
        {
            traitref(0) = 3;
            traitref(1) = -3;
            traitref(2) = 0;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) < 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたの顔はただれている[魅力"s
                        + -1 * (4 + cdata_level(0) / 5) + u8"]"s,
                    u8"You have sores on your face. [CHR"s
                        + -1 * (4 + cdata_level(0) / 5) + u8"]"s);
                traitrefn(4) = lang(
                    u8"あなたの顔中に蕁麻疹が出ている[魅力"s
                        + -2 * (4 + cdata_level(0) / 5) + u8"]"s,
                    u8"Your face is ulcerate. [CHR"s
                        + -2 * (4 + cdata_level(0) / 5) + u8"]"s);
                traitrefn(5) = lang(
                    u8"あなたの顔は崩れかけている[魅力"s
                        + -3 * (4 + cdata_level(0) / 5) + u8"]"s,
                    u8"Your face is crumbling. [CHR"s
                        + -3 * (4 + cdata_level(0) / 5) + u8"]"s);
            }
            traitrefn(0) = lang(
                u8"あなたの顔のただれは軽くなった。"s,
                u8"The swelling in your face decreases."s);
            traitrefn(1) =
                lang(u8"あなたの顔はただれた。"s, u8"Your face is festered."s);
            return 1;
        }
        sdata(17, 0) = std::clamp(
            sdata(17, 0) + trait(tid) * (4 + cdata_level(0) / 5),
            int{sdata(17, 0) > 0},
            9999);
        return 1;
    }
    if (tid == 203)
    {
        if (traitmode == 0)
        {
            traitref(0) = 3;
            traitref(1) = -1;
            traitref(2) = 0;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) < 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたの足の裏は蹄になっている[足装備不可 速度+"s
                        + (20 + cdata_level(0) / 2) + u8"]"s,
                    u8"Your feet transformed into hooves. [SPD+"s
                        + (20 + cdata_level(0) / 2) + u8" Can't wear boots]"s);
            }
            traitrefn(0) = lang(
                u8"あなたの足は元に戻った。"s, u8"Your feet become normal."s);
            traitrefn(1) = lang(
                u8"あなたの足の裏は蹄に変形した。"s,
                u8"Your feet change into hooves."s);
            return 1;
        }
        sdata(18, 0) = std::clamp(
            sdata(18, 0) + (20 + cdata_level(0) / 2),
            int{sdata(18, 0) > 0},
            9999);
        return 1;
    }
    if (tid == 204)
    {
        if (traitmode == 0)
        {
            traitref(0) = 3;
            traitref(1) = -1;
            traitref(2) = 0;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) < 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたの目は4つある[感覚+"s + (5 + cdata_level(0) / 3)
                        + u8" 魅力"s + (5 + cdata_level(0) / 3) * -1 + u8"]"s,
                    u8"You have 4 eyes. [PER+"s + (5 + cdata_level(0) / 3)
                        + u8" CHR"s + (5 + cdata_level(0) / 3) * -1 + u8"]"s);
            }
            traitrefn(0) =
                lang(u8"あなたの目は減った。"s, u8"Your eyes become normal."s);
            traitrefn(1) = lang(
                u8"あなたの目は増殖した。"s, u8"Your eyes are multipling."s);
            return 1;
        }
        sdata(17, 0) = std::clamp(
            sdata(17, 0) + (5 + cdata_level(0) / 3) * -1,
            int{sdata(17, 0) > 0},
            9999);
        sdata(13, 0) = std::clamp(
            sdata(13, 0) + (5 + cdata_level(0) / 3),
            int{sdata(13, 0) > 0},
            9999);
        return 1;
    }
    if (tid == 205)
    {
        if (traitmode == 0)
        {
            traitref(0) = 3;
            traitref(1) = -1;
            traitref(2) = 0;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) < 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたの背中には羽がある[背中装備不可 重量-20% 速度+"s
                        + (12 + cdata_level(0) / 4) + u8"]"s,
                    u8"You have grown feather. [SPD+"s
                        + (12 + cdata_level(0) / 4)
                        + u8" Weight-20% Can't wear cloaks]"s);
            }
            traitrefn(0) = lang(
                u8"あなたの背中から羽が消えた。"s, u8"Your feathers wilt."s);
            traitrefn(1) = lang(
                u8"あなたの背中に羽が生えた。"s,
                u8"Feathers come out from your back."s);
            return 1;
        }
        cbitmod(5, 0, 1);
        sdata(18, 0) = std::clamp(
            sdata(18, 0) + (12 + cdata_level(0) / 4),
            int{sdata(18, 0) > 0},
            9999);
        return 1;
    }
    if (tid == 206)
    {
        if (traitmode == 0)
        {
            traitref(0) = 3;
            traitref(1) = -1;
            traitref(2) = 0;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) < 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたの首はもの凄く太い[首装備不可 魅力"s
                        + (5 + cdata_level(0) / 5) * -1 + u8" PV+"s
                        + (12 + cdata_level(0)) + u8"]"s,
                    u8"Your neck is extremely thick. [CHR"s
                        + (5 + cdata_level(0) / 5) * -1 + u8" PV+"s
                        + (12 + cdata_level(0)) + u8" Can't wear amulets]"s);
            }
            traitrefn(0) = lang(
                u8"あなたの首は細くなった。"s, u8"Your neck becomes thin."s);
            traitrefn(1) = lang(
                u8"あなたの首は太くなった。"s,
                u8"Your neck becomes extremely thick."s);
            return 1;
        }
        sdata(17, 0) = std::clamp(
            sdata(17, 0) + (5 + cdata_level(0) / 5) * -1,
            int{sdata(17, 0) > 0},
            9999);
        cdata_pv(0) += 12 + cdata_level(0);
        return 1;
    }
    if (tid == 207)
    {
        if (traitmode == 0)
        {
            traitref(0) = 3;
            traitref(1) = -1;
            traitref(2) = 0;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) < 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたは殺戮に飢えている[DV"s
                        + (15 + cdata_level(0) * 3 / 2) * -1
                        + u8" ダメージ修正+"s + (5 + cdata_level(0) * 2 / 3)
                        + u8"]"s,
                    u8"Desire for violence arises withn in you. [DV"s
                        + (15 + cdata_level(0) * 3 / 2) * -1 + u8" Dmg bonus+"s
                        + (5 + cdata_level(0) * 2 / 3) + u8"]"s);
            }
            traitrefn(0) = lang(
                u8"あなたの心は落ち着いた。"s,
                u8" A deep sense of peace fills your heart."s);
            traitrefn(1) = lang(
                u8"あなたは憎しみに支配された。"s,
                u8"Hatred dominates your soul."s);
            return 1;
        }
        cdata_dv(0) += (15 + cdata_level(0) * 3 / 2) * -1;
        return 1;
    }
    if (tid == 208)
    {
        if (traitmode == 0)
        {
            traitref(0) = 3;
            traitref(1) = -1;
            traitref(2) = 0;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) < 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたの頭は巨大化している[耐久"s
                        + (5 + cdata_level(0) / 3) * -1 + u8" 器用"s
                        + (4 + cdata_level(0) / 4) * -1 + u8" 習得+"s
                        + (6 + cdata_level(0) / 2) + u8" 意思+"s
                        + (2 + cdata_level(0) / 6) + u8"]"s,
                    u8"Your head has grown huge. [END"s
                        + (5 + cdata_level(0) / 3) * -1 + u8" DEX"s
                        + (4 + cdata_level(0) / 4) * -1 + u8" LER+"s
                        + (6 + cdata_level(0) / 2) + u8" WIL+"s
                        + (2 + cdata_level(0) / 6) + u8"]"s);
            }
            traitrefn(0) = lang(
                u8"あなたの頭は元に戻った。"s,
                u8"Your head is normal size now."s);
            traitrefn(1) = lang(
                u8"あなたの頭は巨大化した。"s,
                u8"Suddenly your head become giant size."s);
            return 1;
        }
        sdata(11, 0) = std::clamp(
            sdata(11, 0) + (5 + cdata_level(0) / 3) * -1,
            int{sdata(11, 0) > 0},
            9999);
        sdata(12, 0) = std::clamp(
            sdata(12, 0) + (4 + cdata_level(0) / 4) * -1,
            int{sdata(12, 0) > 0},
            9999);
        sdata(14, 0) = std::clamp(
            sdata(14, 0) + (6 + cdata_level(0) / 2),
            int{sdata(14, 0) > 0},
            9999);
        sdata(15, 0) = std::clamp(
            sdata(15, 0) + (2 + cdata_level(0) / 6),
            int{sdata(15, 0) > 0},
            9999);
        return 1;
    }
    if (tid == 209)
    {
        if (traitmode == 0)
        {
            traitref(0) = 3;
            traitref(1) = -1;
            traitref(2) = 0;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) < 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたは雨を呼ぶ[雨天確率上昇]"s,
                    u8"Clouds of rain follow you. [Chance of rain+]"s);
            }
            traitrefn(0) = lang(
                u8"あなたの頭上から雨雲が消えた。"s,
                u8"Clouds of rain stop following you."s);
            traitrefn(1) = lang(
                u8"あなたの頭上に雨雲が現れた。"s,
                u8"Clouds of rain start to follow you."s);
            return 1;
        }
        return 1;
    }
    if (tid == 210)
    {
        if (traitmode == 0)
        {
            traitref(0) = 3;
            traitref(1) = -1;
            traitref(2) = 0;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) < 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたはポーション中毒だ[定期的ポーション消費]"s,
                    u8"You are addicted to potion. [Consume potions]"s);
            }
            traitrefn(0) = lang(
                u8"あなたのポーション中毒は消えた。"s,
                u8"You are no longer addicted to potion."s);
            traitrefn(1) = lang(
                u8"あなたはポーション中毒になった。"s,
                u8"Potions! More potions!! Suddenly, You become addicted to potion."s);
            return 1;
        }
        return 1;
    }
    if (tid == 211)
    {
        if (traitmode == 0)
        {
            traitref(0) = 3;
            traitref(1) = -1;
            traitref(2) = 0;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) < 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたは衰弱している[HP-15% 筋力"s
                        + (4 + cdata_level(0) / 2) * -1 + u8"]"s,
                    u8"You suffer debilitation. [HP-15% STR"s
                        + (4 + cdata_level(0) / 2) * -1 + u8"]"s);
            }
            traitrefn(0) = lang(
                u8"あなたは健康になった。"s, u8"You become healthy again."s);
            traitrefn(1) =
                lang(u8"あなたは衰弱した。"s, u8"You become weak, very weak."s);
            return 1;
        }
        sdata(10, 0) = std::clamp(
            sdata(10, 0) + (4 + cdata_level(0) / 2) * -1,
            int{sdata(10, 0) > 0},
            9999);
        sdata(2, 0) = std::clamp(sdata(2, 0) + -15, int{sdata(2, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 212)
    {
        if (traitmode == 0)
        {
            traitref(0) = 3;
            traitref(1) = -1;
            traitref(2) = 0;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) < 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたは痴呆になっている[MP-15% 魔力"s
                        + (4 + cdata_level(0) / 2) * -1 + u8"]"s,
                    u8"You have dementia. [MP-15% MAG"s
                        + (4 + cdata_level(0) / 2) * -1 + u8"]"s);
            }
            traitrefn(0) = lang(
                u8"あなたは明晰になった。"s, u8"You become confident again."s);
            traitrefn(1) =
                lang(u8"あなたはぼけた。"s, u8"You become feebleminded."s);
            return 1;
        }
        sdata(16, 0) = std::clamp(
            sdata(16, 0) + (4 + cdata_level(0) / 2) * -1,
            int{sdata(16, 0) > 0},
            9999);
        sdata(3, 0) = std::clamp(sdata(3, 0) + -15, int{sdata(3, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 213)
    {
        if (traitmode == 0)
        {
            traitref(0) = 3;
            traitref(1) = -1;
            traitref(2) = 0;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) < 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたは重い甲殻で覆われている[PV+"s
                        + (15 + cdata_level(0) / 2) + u8" 速度"s
                        + (20 + cdata_level(0) / 2) * -1 + u8"]"s,
                    u8"You are covered by heavy carapace. [PV+"s
                        + (15 + cdata_level(0) / 2) + u8" SPD"s
                        + (20 + cdata_level(0) / 2) * -1 + u8"]"s);
            }
            traitrefn(0) = lang(
                u8"あなたの皮膚から甲殻が消えた。"s,
                u8"Your carapace starts to break."s);
            traitrefn(1) = lang(
                u8"あなたの皮膚は甲殻で覆われた。"s,
                u8"Heavy carapace starts to cover up your skin."s);
            return 1;
        }
        sdata(18, 0) = std::clamp(
            sdata(18, 0) + (20 + cdata_level(0) / 2) * -1,
            int{sdata(18, 0) > 0},
            9999);
        cdata_pv(0) += 15 + cdata_level(0) / 2;
        return 1;
    }
    if (tid == 214)
    {
        if (traitmode == 0)
        {
            traitref(0) = 3;
            traitref(1) = -1;
            traitref(2) = 0;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) < 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたの周囲の空間は捩れている[ランダムテレポート]"s,
                    u8"You are unstablizing space around you. [Random teleporation]"s);
            }
            traitrefn(0) = lang(
                u8"あなたの周囲の空間は元通りになった。"s,
                u8"You feel steady."s);
            traitrefn(1) = lang(
                u8"あなたの周囲の空間は捩れた。"s, u8"You feel unstable."s);
            return 1;
        }
        return 1;
    }
    if (tid == 215)
    {
        if (traitmode == 0)
        {
            traitref(0) = 3;
            traitref(1) = -1;
            traitref(2) = 0;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) < 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたは生きたマナバッテリーだ[杖から魔力抽出]"s,
                    u8"You are a living mana battery. [Absorb mana from rods]"s);
            }
            traitrefn(0) = lang(
                u8"あなたのマナは元通りになった。"s,
                u8"You are no longer a living mana battery."s);
            traitrefn(1) = lang(
                u8"あなたのマナは杖から魔力を抽出する。"s,
                u8"You are a living mana battery."s);
            return 1;
        }
        return 1;
    }
    if (tid == 216)
    {
        if (traitmode == 0)
        {
            traitref(0) = 3;
            traitref(1) = -1;
            traitref(2) = 0;
            traitref(3) = 1;
            traitref(4) = 0;
            traitref(5) = 100;
            traitref(6) = -1;
            if (trait(tid) < 0)
            {
                traitrefn(2) = "";
                traitrefn(3) = lang(
                    u8"あなたの手から毒が滴っている[ポーション毒化 毒耐性強化]"s,
                    u8"Poison drips from your hands. [Poison potions RES Poison+]"s);
            }
            traitrefn(0) = lang(
                u8"あなたの手は元通りになった。"s,
                u8"Your hands are clean now."s);
            traitrefn(1) = lang(
                u8"あなたの手から毒が滴り出した。"s,
                u8"Poison starts to drip from your hands."s);
            return 1;
        }
        sdata(55, 0) =
            std::clamp(sdata(55, 0) + 100, int{sdata(55, 0) > 0}, 9999);
        return 1;
    }
    return 0;
}



} // namespace elona
