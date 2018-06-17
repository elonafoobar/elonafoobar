#include "ability.hpp"
#include "variables.hpp"

namespace elona
{

int proc_random_event()
{
    int id0 = 0;
    int id1 = 0;
    if (gspd < 10)
    {
        return 0;
    }
    if (dbg_skipevent)
    {
        return 0;
    }
    if (mode == 12)
    {
        return 0;
    }
    if (mode == 9)
    {
        if (!cdata[0].god_id.empty())
        {
            if (rnd(12) == 0)
            {
                id0 = 18;
            }
        }
        if (rnd(80) == 0)
        {
            id0 = 4;
            id1 = 120;
        }
        if (rnd(20) == 0)
        {
            id0 = 3;
        }
        if (rnd(25) == 0)
        {
            id0 = 2;
        }
        if (rnd(100) == 0)
        {
            id0 = 5;
            id1 = 65;
        }
        if (rnd(20) == 0)
        {
            id0 = 6;
        }
        if (rnd(20) == 0)
        {
            id0 = 7;
        }
        if (rnd(250) == 0)
        {
            if (inv_getfreeid(0) != -1)
            {
                id0 = 19;
            }
        }
        if (rnd(10000) == 0)
        {
            if (inv_getfreeid(0) != -1)
            {
                id0 = 21;
            }
        }
        if (rnd(70) == 0)
        {
            id0 = 8;
            id1 = 40;
        }
        if (rnd(200) == 0)
        {
            id0 = 20;
        }
        if (rnd(50) == 0)
        {
            id0 = 23;
        }
        if (rnd(300) == 0)
        {
            id0 = 24;
        }
        if (rnd(90) == 0)
        {
            id0 = 22;
            id1 = 70;
        }
        goto label_1894_internal;
    }
    if (mdata(6) != 1)
    {
        if (cdata[0].continuous_action_id != 0)
        {
            return 0;
        }
    }
    if (mdata(6) == 5)
    {
        return 0;
    }
    if (rnd(30) == 0)
    {
        id0 = 17;
    }
    if (rnd(25) == 0)
    {
        id0 = 16;
    }
    if (rnd(25) == 0)
    {
        id0 = 12;
    }
    if (rnd(50) == 0)
    {
        id0 = 9;
    }
    if (rnd(80) == 0)
    {
        id0 = 14;
    }
    if (rnd(50) == 0)
    {
        id0 = 8;
        id1 = 40;
    }
    if (rnd(80) == 0)
    {
        id0 = 13;
        id1 = 45;
    }
    if (mdata(6) == 3)
    {
        if (rnd(25) == 0)
        {
            id0 = 15;
            id1 = 80;
        }
        goto label_1894_internal;
    }
    if (mdata(6) == 1)
    {
        if (rnd(40))
        {
            return 0;
        }
        goto label_1894_internal;
    }
    if (rnd(25) == 0)
    {
        id0 = 10;
    }
    if (rnd(25) == 0)
    {
        id0 = 11;
    }
label_1894_internal:
    if (id0 == 0)
    {
        return 0;
    }
    cc = 0;
    tc = 0;
    listmax = 0;
    if (id1 != 0)
    {
        if (rnd(sdata(19, 0) + 1) > id1)
        {
            id0 = 1;
        }
    }
    switch (id0)
    {
    case 15:
        for (int cnt = 0; cnt < 20; ++cnt)
        {
            p = rnd(gdata_crowd_density + 1) + 57;
            if (p >= ELONA_MAX_CHARACTERS)
            {
                --cnt;
                continue;
            }
            if (cdata[p].state == 1)
            {
                txt(lang(
                    name(p) + u8"「ぎゃぁーー！」"s,
                    name(p) + u8" screams, "s + u8"\"Ahhhhhhh!\""s));
                dmghp(p, 99999, -11);
                break;
            }
        }
        s = lang(u8"殺人鬼"s, u8"Murderer"s);
        buff = lang(
            u8"街のどこかで悲鳴があがった。あなたはガードが慌しく走っていくのを目撃した。「人殺し、人殺しだ！！」"s,
            u8"Suddenly, a painful shriek rises from somewhere in the town. You see several guards hastily run by."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"なむ…"s, u8"Sorry for you."s);
        ++listmax;
        show_random_event_window(u8"bg_re9");
        break;
    case 14:
        s = lang(u8"謎のご馳走"s, u8"Strange Feast"s);
        buff = lang(
            u8"あなたは目の前にご馳走をみつけた。"s,
            u8"You come across a strange feast."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"食べる"s, u8"(Eat)"s);
        ++listmax;
        list(0, listmax) = 2;
        listn(0, listmax) = lang(u8"立ち去る"s, u8"(Leave)"s);
        ++listmax;
        show_random_event_window(u8"bg_re10");
        if (rtval == 1)
        {
            cdata[0].nutrition = 15000;
            txt(lang(u8"なかなか美味しかった。"s, u8"It was tasty."s),
                lang(u8"悪くない。"s, u8"Not bad at all."s),
                lang(u8"あなたは舌鼓をうった。"s, u8"You smack your lips."s));
            show_eating_message();
            chara_anorexia(0);
        }
        break;
    case 13:
        s = lang(u8"ご馳走の匂い"s, u8"Smell of Food"s);
        buff = lang(
            u8"どこからともなく漂うご馳走の匂いで、あなたの胃は不満を叫び始めた。"s,
            u8"A sweet smell of food floats from nowhere. Your stomach growls but you can't find out where it comes from."s);
        cdata[0].nutrition -= 5000;
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"腹減った…"s, u8"I'm hungry now!"s);
        ++listmax;
        show_random_event_window(u8"bg_re10");
        break;
    case 1:
        s = lang(u8"不運の回避"s, u8"Avoiding Misfortune"s);
        buff = lang(
            u8"あなたは一瞬嫌な予感がしたが、それはやがて消えた。"s,
            u8"You sense a bad feeling for a moment but it fades away quickly."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"よし"s, u8"Good."s);
        ++listmax;
        show_random_event_window(u8"bg_re8");
        break;
    case 24:
        efid = 1113;
        tc = 0;
        magic();
        s = lang(u8"才能の開花"s, u8"Your Potential"s);
        buff = lang(
            u8"突然あなたの才能は開花した！"s,
            u8"Suddenly you develop your gift!"s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"ワァオー"s, u8"Woohoo!"s);
        ++listmax;
        show_random_event_window(u8"bg_re4");
        break;
    case 18:
        skillexp(181, 0, 1000, 6, 1000);
        s = lang(u8"信仰の深まり"s, u8"Gaining Faith"s);
        buff = lang(
            u8"夢の中で、あなたは偉大なる者の穏やかな威光に触れた。"s,
            u8"In your dream, a saint comes out and blesses you."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"神よ"s, u8"Great."s);
        ++listmax;
        show_random_event_window(u8"bg_re12");
        break;
    case 12:
        s = lang(u8"マテリアルの発見"s, u8"Small Luck"s);
        buff = lang(
            u8"石ころにつまずいて転んだ拍子に、あなたは幾つかのマテリアルを見つけた。"s,
            u8"You stumble over a stone and find some materials on the ground. "s);
        efid = 1117;
        efp = 100;
        tc = 0;
        magic();
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"よし"s, u8"Nice."s);
        ++listmax;
        show_random_event_window(u8"bg_re3");
        break;
    case 23:
        efid = 1117;
        efp = 200;
        tc = 0;
        magic();
        s = lang(u8"夢の中の収穫"s, u8"Dream Harvest"s);
        buff = lang(
            u8"夢の中で、あなたはのんきにマテリアルを採取していた"s,
            u8"In your dream, you harvest materials peacefully."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"るん♪"s, u8"Sweet."s);
        ++listmax;
        show_random_event_window(u8"bg_re3");
        break;
    case 10:
        s = lang(u8"野営跡の発見"s, u8"Camping Site"s);
        buff = lang(
            u8"あなたは何者かが野営した跡を見つけた。辺りには食べ残しやがらくたが散らばっている。もしかしたら、何か役に立つものがあるかもしれない。"s,
            u8"You discover a camping site someone left behind. Chunks of leftovers and junks remain here. You may possibly find some useful items."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"調べる"s, u8"(Search)"s);
        ++listmax;
        list(0, listmax) = 2;
        listn(0, listmax) = lang(u8"立ち去る"s, u8"(Leave)"s);
        ++listmax;
        show_random_event_window(u8"bg_re3");
        if (rtval == 1)
        {
            for (int cnt = 0, cnt_end = (1 + rnd(4)); cnt < cnt_end; ++cnt)
            {
                flt();
                flttypemajor = fsetremain(rnd(length(fsetremain)));
                itemcreate(-1, 0, cdata[0].position.x, cdata[0].position.y, 0);
            }
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
        }
        break;
    case 4:
        snd(116);
        efid = 1118;
        efp = 100;
        tc = 0;
        magic();
        s = lang(u8"不気味な夢"s, u8"Creepy Dream"s);
        buff = lang(
            u8"あなたは不気味な夢をみた。陰気な幾つもの瞳があなたを凝視し、どこからともなく笑い声がこだました。「ケラケラケラ…ミツケタヨ…ケラケラ」あなたが二度寝返りをうった後、その夢は終わった。"s,
            u8"In your dreams, several pairs of gloomy eyes stare at you and laughter seemingly from nowhere echoes around you.  \"Keh-la keh-la keh-la I found you...I found you.. keh-la keh-la keh-la\" After tossing around a couple times, the dream is gone."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"おかしな夢だ"s, u8"Strange..."s);
        ++listmax;
        show_random_event_window(u8"bg_re5");
        break;
    case 22:
        snd(116);
        efid = 454;
        efp = 100;
        tc = 0;
        magic();
        s = lang(u8"怪物の夢"s, u8"Monster Dream"s);
        buff = lang(
            u8"あなたは怪物と戦っていた。醜い化け物に斬りかかろうとした時、怪物は悲鳴をあげた。「オレハオマエダ！オマエハオレダ！」あなたは自分の呻き声に起こされた。"s,
            u8"You are fighting an ugly monster. You are about to thrust a dagger into the neck of the monster. And the monster screams. \"You are me! I am you!\" You are awakened by your own low moan."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"ううぅん…"s, u8"Urrgh..hh.."s);
        ++listmax;
        show_random_event_window(u8"bg_re2");
        break;
    case 19:
        flt();
        itemcreate(0, 621, -1, -1, 0);
        txt(lang(
            itemname(ci, 1) + u8"をバックパックに入れた。"s,
            u8"You put "s + itemname(ci, 1) + u8" in your backpack."s));
        s = lang(u8"宝を埋める夢"s, u8"Treasure of Dream"s);
        buff = lang(
            u8"あなたは夢の中で宝を埋めた。あなたはすぐに飛び起き、その場所を紙に書き留めた"s,
            u8"You buried treasure in your dream. You quickly get up and write down the location."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"ワァオー"s, u8"Woohoo!"s);
        ++listmax;
        show_random_event_window(u8"bg_re15");
        break;
    case 20:
        buff_add(tc, 19, 777, 1500);
        s = lang(u8"幸運の日"s, u8"Lucky Day"s);
        buff = lang(u8"うみみゃぁ！"s, u8"Mewmewmew!"s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"ワァオー"s, u8"Woohoo!"s);
        ++listmax;
        show_random_event_window(u8"bg_re12");
        break;
    case 21:
        flt();
        itemcreate(0, 721, -1, -1, 0);
        txt(lang(
            itemname(ci, 1) + u8"をバックパックに入れた。"s,
            u8"You put "s + itemname(ci, 1) + u8" in your backpack."s));
        s = lang(u8"運命の気まぐれ"s, u8"Quirk of Fate"s);
        buff =
            lang(u8"うみみゃっ、見つけたね！"s, u8"Mewmew? You've found me!"s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"ワァオー"s, u8"Woohoo!"s);
        ++listmax;
        show_random_event_window(u8"bg_re15");
        break;
    case 5:
        if (trait(42))
        {
            txt(lang(
                u8"あなたは祈祷を捧げ呪いのつぶやきを無効にした。"s,
                u8"Your prayer nullifies the curse."s));
        }
        else
        {
            f = 0;
            tc = 0;
            for (int i = 0; i < 30; ++i)
            {
                if (cdata_body_part(tc, i) % 10000 == 0)
                {
                    continue;
                }
                else
                {
                    f = 1;
                }
            }
            if (f)
            {
                efid = 1114;
                efp = 200;
                magic();
            }
            else if (event_id() == -1)
            {
                event_add(26);
            }
        }
        s = lang(u8"呪いのつぶやき"s, u8"Cursed Whispering"s);
        buff = lang(
            u8"どこからともなく聞こえる呪いのつぶやきが、あなたの眠りを妨げた。"s,
            u8"Your sleep is disturbed by a harshly whispering that comes from nowhere."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"眠れない…"s, u8"Can't...sleep..."s);
        ++listmax;
        show_random_event_window(u8"bg_re5");
        break;
    case 8:
        p = rnd(cdata[0].gold / 8 + 1);
        if (cdata[0].is_protected_from_thieves())
        {
            p = 0;
        }
        if (p > 0)
        {
            txt(lang(
                u8"金貨"s + p + u8"枚を失った。"s,
                u8"You lose "s + p + u8" gold pieces."s));
            cdata[0].gold -= p;
        }
        else
        {
            txt(lang(
                u8"損害はなかった。"s,
                u8"The thief fails to steal money from you."s));
        }
        s = lang(u8"悪意ある手"s, u8"Malicious Hand"s);
        buff = lang(
            u8"悪意のある手が忍び寄り、あなたが気付かない間に金貨を奪って逃げた。"s,
            u8"A malicious hand slips and steals your money."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"盗人め…"s, u8"Bloody thieves..."s);
        ++listmax;
        show_random_event_window(u8"bg_re9");
        break;
    case 11:
        s = lang(u8"冒険者の遺骸"s, u8"Corpse"s);
        buff = lang(
            u8"この場所で力尽きた冒険者の遺骸を見つけた。既に朽ちかけている骨と、身に着けていたと思われる幾つかの装備が散らばっている。"s,
            u8"You find a corpse of an adventurer. There're bones and equipment scatters on the ground waiting to decay."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"あさる"s, u8"(Loot)"s);
        ++listmax;
        list(0, listmax) = 2;
        listn(0, listmax) = lang(u8"埋葬する"s, u8"(Bury)"s);
        ++listmax;
        show_random_event_window(u8"bg_re7");
        if (rtval == 1)
        {
            txt(lang(
                u8"あなたは遺留品をあさった。"s, u8"You loot the remains."s));
            modify_karma(0, -2);
            for (int cnt = 0, cnt_end = (1 + rnd(3)); cnt < cnt_end; ++cnt)
            {
                flt(0, calcfixlv(3));
                if (rnd(3) == 0)
                {
                    flttypemajor = fsetwear(rnd(length(fsetwear)));
                }
                else
                {
                    flttypemajor = fsetremain(rnd(length(fsetremain)));
                }
                itemcreate(-1, 0, cdata[0].position.x, cdata[0].position.y, 0);
            }
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
        }
        else
        {
            txt(lang(
                u8"あなたは骨と遺留品を埋葬した。"s,
                u8"You bury the corpse with respect."s));
            modify_karma(0, 5);
        }
        break;
    case 2:
        efid = 1104;
        efp = 100;
        tc = 0;
        magic();
        s = lang(u8"魔法使いの夢"s, u8"Wizard's Dream"s);
        buff = lang(
            u8"夢の中であなたは赤い髪の魔術師に出会った。「誰じゃ、お主は？ふむ、間違った者の夢に現れてしまったようじゃ。すまぬな。お詫びといってはなんじゃが…」魔法使いは指をくるりと回した。あなたは軽い頭痛を覚えた。"s,
            u8"In your dream, you meet a wizard with a red mustache. \"Who are you? Hmm, I guess I picked up the wrong man's dream. My apology for disturbing your sleep. To make up for this...\" The wizard draws a circle in the air and vanishs. You feel the effects of a faint headache."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"おかしな夢だ"s, u8"A weird dream."s);
        ++listmax;
        show_random_event_window(u8"bg_re6");
        break;
    case 3:
        efid = 1119;
        efp = 100;
        tc = 0;
        magic();
        s = lang(u8"成長のきざし"s, u8"Development"s);
        buff = lang(
            u8"長年の鍛錬の成果が実ったようだ。なかなか眠りにつけず考えごとをしていたあなたは、ふと、自らの技術に関する新しいアイデアを思いついた。"s,
            u8"You lie awake, sunk deep into thought. As memories of your journey flow from one into another, you chance upon a new theory to improve one of your skills."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"よし！"s, u8"Good!"s);
        ++listmax;
        show_random_event_window(u8"bg_re4");
        break;
    case 6:
        skillexp(154, 0, 1000);
        s = lang(u8"自然治癒力の向上"s, u8"Regeneration"s);
        buff = lang(
            u8"身体が妙に火照ってあなたは目を覚ました。気がつくと、腕にあった傷跡が完全に消えていた。"s,
            u8"Your entire body flushes. When you wake up, a scar in your arm is gone."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"よし"s, u8"Good."s);
        ++listmax;
        show_random_event_window(u8"bg_re4");
        break;
    case 7:
        skillexp(155, 0, 1000);
        s = lang(u8"瞑想力の向上"s, u8"Meditation"s);
        buff = lang(
            u8"あなたは、夢の中でも驚くほど理性を保っていた。まるで瞑想を行っている時のように、あなたは心の平和を感じた。"s,
            u8"In your dream, you meditate and feel inner peace."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"よし"s, u8"Good."s);
        ++listmax;
        show_random_event_window(u8"bg_re4");
        break;
    case 9:
        ++cdata[0].platinum_coin;
        s = lang(u8"路上に転がる幸運"s, u8"Great Luck"s);
        buff = lang(
            u8"下を向いて歩いていると、幸運にもプラチナ硬貨を見つけた。"s,
            u8"You stumble over a stone and find a platinum coin."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"ラッキー！"s, u8"What a luck!"s);
        ++listmax;
        show_random_event_window(u8"bg_re1");
        break;
    case 16:
        p = rnd(cdata[0].gold / 10 + 1000) + 1;
        cdata[0].gold += p;
        txt(lang(
            u8"金貨"s + p + u8"枚を手に入れた。"s,
            u8"You pick up "s + p + u8" gold pieces."s));
        s = lang(u8"発狂した金持ち"s, u8"Mad Millionaire"s);
        buff = lang(
            u8"発狂した金持ちが、何か叫びながら金貨をばらまいている…"s,
            u8"A rich mad man is scattering his money all over the ground."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"ラッキー！"s, u8"What a luck!"s);
        ++listmax;
        show_random_event_window(u8"bg_re1");
        break;
    case 17:
        efid = 451;
        efp = 800;
        tc = 0;
        magic();
        s = lang(u8"辻プリースト"s, u8"Wandering Priest"s);
        buff = lang(
            u8"突然、向かいからやって来た一人の神官が、すれ違いざまにあなたに魔法をかけた。「ノープロブレム」"s,
            u8"A priest comes up to you and casts a spell on you. \"No problem.\""s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"ありがとう"s, u8"Thanks."s);
        ++listmax;
        show_random_event_window(u8"bg_re11");
        break;
    }

    cc = 0;
    load_continuous_action_animation();
    return 1;
}



int show_random_event_window(const std::string& file)
{
    if (config::instance().skiprandevents)
    {
        if (listmax <= 1)
        {
            snd(62);
            txt(""s + buff);
            txt(lang(u8"「"s, u8"\""s) + listn(0, 0) + lang(u8"」"s, u8"\""s));
            rtval = -1;
            return rtval;
        }
    }
    keyhalt = 1;
    cs = 0;
    page = 0;
    pagemax = 0;
    pagesize = 16;
    cs_bk = -1;
    key = "";
    objprm(0, ""s);
    keylog = "";
    if (listmax <= 1)
    {
        chatesc = 0;
    }
    else
    {
        chatesc = -1;
    }
    gsel(7);
    gmode(0);
    pos(0, 0);
    picload(filesystem::dir::graphic() / (u8""s + file + u8".bmp"), 0);
    tx = ginfo(12);
    ty = ginfo(13);
    gsel(0);
    snd(62);
    dx = tx + 36;
    talk_conv(buff, (dx - 80) / (7 - en) - en * 4);
    notesel(buff);
    dy = ty + noteinfo() * 15 + 80 + listmax * 20;
label_1897_internal:
    gmode(2);
    window(
        (windoww - dx) / 2 + inf_screenx + 4, winposy(dy) - 12, dx, dy, 0, -1);
    window((windoww - dx) / 2 + inf_screenx, winposy(dy) - 16, dx, dy);
    wx = (windoww - dx) / 2 + inf_screenx;
    wy = winposy(dy);
    gmode(0);
    pos(wx + 12, wy + 6);
    gcopy(7, 0, 0, tx, ty);
    gmode(2);
    color(240, 230, 220);
    boxl(wx + 12, wy + 6, wx + tx + 12, wy + ty + 6);
    color(0, 0, 0);
    font(14 - en * 2);
    q = lang(u8"《 "s + s + u8" 》"s, u8" < "s + s + u8" > "s);
    pos(wx + 40, wy + 16);
    color(30, 20, 10);
    bmes(q, 245, 235, 225);
    color(0, 0, 0);
    font(14 - en * 2);
    color(30, 30, 30);
    pos(wx + 24, wy + ty + 20);
    mes(buff);
    color(0, 0, 0);
    keyrange = 0;
    cs_listbk();
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        key_list(cnt) = key_select(cnt);
        ++keyrange;
    }
    font(14 - en * 2);
    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
    {
        p = cnt;
        i = list(0, p);
        display_key(wx + 30, wy + dy + cnt * 20 - listmax * 20 - 52, cnt);
        q = listn(0, p);
        cs_list(cs == cnt, q, wx + 60, wy + dy + cnt * 20 - listmax * 20 - 52);
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
    redraw();
    await(config::instance().wait1);
    key_check();
    cursor_check();
    ELONA_GET_SELECTED_ITEM(rtval, snd(40));
    if (chatesc != -1)
    {
        if (key == key_cancel)
        {
            snd(40);
            rtval = chatesc;
        }
    }
    if (rtval != -1)
    {
        label_1898();
        return 0;
    }
    goto label_1897_internal;
}



int label_1898()
{
    key = "";
    return rtval;
}

}
