#include "wish.hpp"
#include "ability.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "debug.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "item_db.hpp"
#include "optional.hpp"
#include "variables.hpp"


namespace
{


std::string fix_wish(const std::string& text)
{
    using strutil::remove_str;
    using strutil::to_lower;

    auto ret{text};

    if (debug::voldemort)
    {
        const auto pos = ret.find_first_not_of(u8"0123456789");
        if (pos != std::string::npos)
        {
            ret = ret.substr(pos);
        }
        ret = remove_str(ret, u8"呪われた");
        ret = remove_str(ret, u8"堕落した");
        ret = remove_str(ret, u8"祝福された");
        ret = remove_str(ret, u8"呪われていない");
        ret = remove_str(ret, u8"cursed ");
        ret = remove_str(ret, u8"doomed ");
        ret = remove_str(ret, u8"blessed ");
        ret = remove_str(ret, u8"uncursed ");
    }
    if (jp)
    {
        ret = remove_str(ret, u8",");
        ret = remove_str(ret, u8" ");
        ret = remove_str(ret, u8"　");
    }
    else
    {
        ret = to_lower(ret);
    }
    ret = remove_str(ret, lang(u8"アイテム", u8"item"));
    ret = remove_str(ret, lang(u8"スキル", u8"skill "));
    ret = remove_str(ret, lang(u8"スキル", u8"skill"));

    return ret;
}


std::string remove_extra_str(const std::string& text)
{
    using strutil::remove_str;

    auto ret{text};

    ret = remove_str(ret, u8"の剥製");
    ret = remove_str(ret, u8"剥製");
    ret = remove_str(ret, u8"のはく製");
    ret = remove_str(ret, u8"はく製");
    ret = remove_str(ret, u8"のカード");
    ret = remove_str(ret, u8"カード");
    ret = remove_str(ret, u8"card ");
    ret = remove_str(ret, u8"figure ");
    ret = remove_str(ret, u8"card");
    ret = remove_str(ret, u8"figure");

    return ret;
}


void wish_end()
{
    s = lang(
        cdatan(1, 0) + cdatan(0, 0) + u8"は狂喜して叫んだ。「"s + inputlog
            + u8"！！」"s + txtcopy,
        cdatan(1, 0) + u8" "s + cdatan(0, 0) + u8" goes wild with joy, \""s
            + inputlog + u8"!!\" "s + cnven(txtcopy));
    if (gdata_wizard == 0)
    {
        if (wishfilter == 0 || 0)
        {
            net_send(u8"wish"s + s);
            wishfilter = 1;
        }
    }
    return;
}


void select_wished_character()
{
    i = 0;
    s2 = remove_extra_str(inputlog);
    for (int cnt = 0; cnt < 800; ++cnt)
    {
        p = 0;
        s = refchara_str(cnt, 2);
        if (en)
        {
            s = strutil::to_lower(s(0));
        }
        if (strutil::contains(s(0), s2))
        {
            p = 1000 - (s(0).size() - s2.size()) * 10;
        }
        if (p != 0)
        {
            dblist(0, i) = cnt;
            dblist(1, i) = p;
            ++i;
        }
    }
    p(0) = 0;
    p(1) = 0;
    for (int cnt = 0, cnt_end = (i); cnt < cnt_end; ++cnt)
    {
        if (dblist(1, cnt) > p(1))
        {
            p(0) = dblist(0, cnt);
            p(1) = dblist(1, cnt);
        }
    }
    dbid = p;
    if (dbid == 0)
    {
        dbid = 37;
    }
    return;
}


void wish_for_character()
{
    inputlog = strutil::remove_str(inputlog(0), u8"summon");
    select_wished_character();
    flt();
    characreate(-1, dbid, cdata[0].position.x, cdata[0].position.y);
    cell_refresh(cdata[rc].position.x, cdata[rc].position.y);
    txt(cdatan(0, rc) + " is summoned.");
    wish_end();
    return;
}


void wish_for_card()
{
    select_wished_character();
    flt();
    characreate(56, dbid, -3, 0);
    flt();
    itemcreate(-1, 504, cdata[0].position.x, cdata[0].position.y, 0);
    inv[ci].subname = cdata[56].id;
    inv[ci].param1 = cdata[56].image;
    chara_vanquish(56);
    cell_refresh(cdata[0].position.x, cdata[0].position.y);
    txt(lang(
        u8"足元に"s + itemname(ci) + u8"が転がってきた。"s,
        ""s + itemname(ci) + u8" appear"s + _s2(inv[ci].number)
            + u8" from nowhere."s));
    wish_end();
    return;
}


void wish_for_figure()
{
    select_wished_character();
    flt();
    characreate(56, dbid, -3, 0);
    flt();
    itemcreate(-1, 503, cdata[0].position.x, cdata[0].position.y, 0);
    inv[ci].subname = cdata[56].id;
    inv[ci].param1 = cdata[56].image;
    chara_vanquish(56);
    cell_refresh(cdata[0].position.x, cdata[0].position.y);
    txt(lang(
        u8"足元に"s + itemname(ci) + u8"が転がってきた。"s,
        ""s + itemname(ci) + u8" appear"s + _s2(inv[ci].number)
            + u8" from nowhere."s));
    wish_end();
    return;
}


} // namespace


namespace elona
{


void what_do_you_wish_for()
{
    int number_of_items{};
    optional<curse_state_t> curse_state;
    int wishid = 0;
    txtcopy = "";
    txtef(5);
    txt(lang(u8"何を望む？"s, u8"What do you wish for? "s));
    inputlog = "";
    input_text_dialog(
        (windoww - 290) / 2 + inf_screenx, winposy(90), 16, false);
    txt(lang(u8"「"s + inputlog + u8"！！」"s, u8"\""s + inputlog + u8"!!\""s));
    msgtemp = "";
    autosave = 1 * (gdata_current_map != 35);
    tcopy = 1;
    if (inputlog == ""s || inputlog == u8" "s)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        return;
    }
    if (en)
    {
        inputlog = strutil::to_lower(inputlog(0));
    }
    snd(24);
    if (strutil::contains(inputlog(0), u8"中の神")
        || strutil::contains(inputlog(0), u8"god inside"s))
    {
        txt(lang(
            u8"中の神も大変…あ…中の神なんているわけないじゃない！…ねえ、聞かなかったことにしてね。"s,
            u8"There's no God inside."s));
        wish_end();
        return;
    }
    if (strutil::contains(inputlog(0), u8"中の人")
        || strutil::contains(inputlog(0), u8"man inside"s))
    {
        txt(lang(u8"中の人も大変ね。"s, u8"There's no man inside."s));
        wish_end();
        return;
    }
    if (inputlog == u8"エヘカトル"s || inputlog == u8"ehekatl"s)
    {
        txt(lang(u8"「うみみゅみゅぁ！」"s, u8"\"Meeewmew!\""s));
        flt();
        characreate(-1, 331, cdata[0].position.x, cdata[0].position.y);
        wish_end();
        return;
    }
    if (inputlog == u8"ルルウィ"s || inputlog == u8"lulwy"s)
    {
        txt(lang(
            u8"「アタシを呼びつけるとは生意気ね。」"s,
            u8"\"You dare to call my name?\""s));
        flt();
        characreate(-1, 306, cdata[0].position.x, cdata[0].position.y);
        wish_end();
        return;
    }
    if (inputlog == u8"オパートス"s || inputlog == u8"opatos"s)
    {
        txt(lang(u8"工事中。"s, u8"\"Under construction.\""s));
        flt();
        characreate(-1, 338, cdata[0].position.x, cdata[0].position.y);
        wish_end();
        return;
    }
    if (inputlog == u8"クミロミ"s || inputlog == u8"kumiromi"s)
    {
        txt(lang(u8"工事中。"s, u8"\"Under construction.\""s));
        flt();
        characreate(-1, 339, cdata[0].position.x, cdata[0].position.y);
        wish_end();
        return;
    }
    if (inputlog == u8"マニ"s || inputlog == u8"mani"s)
    {
        txt(lang(u8"工事中。"s, u8"\"Under construction.\""s));
        flt();
        characreate(-1, 342, cdata[0].position.x, cdata[0].position.y);
        wish_end();
        return;
    }
    if (inputlog == u8"若さ"s || inputlog == u8"若返り"s || inputlog == u8"年"s
        || inputlog == u8"美貌"s || inputlog == u8"youth"s
        || inputlog == u8"age"s || inputlog == u8"beauty"s)
    {
        txt(lang(u8"ふぅん…そんな願いでいいんだ。"s, u8"A typical wish."s));
        cdata[0].birth_year += 20;
        if (cdata[0].birth_year + 12 > gdata_year)
        {
            cdata[0].birth_year = gdata_year - 12;
        }
        wish_end();
        return;
    }
    if (inputlog == u8"通り名"s || inputlog == u8"異名"s || inputlog == u8"aka"s
        || inputlog == u8"title"s || inputlog == u8"name"s
        || inputlog == u8"alias"s)
    {
        if (gdata_wizard)
        {
            txt(lang(u8"だめよ。"s, u8"*laugh*"s));
            wish_end();
            return;
        }
        txt(lang(u8"新しい異名は？"s, u8"What's your new alias?"s));
        int stat = select_alias(0);
        if (stat == 1)
        {
            txt(lang(
                u8"あなたの新しい異名は「"s + cmaka + u8"」。満足したかしら？"s,
                u8"You will be known as <"s + cmaka + u8">."s));
            msgtemp = cdatan(1, 0) + cdatan(0, 0) + u8"は今後"s + cmaka
                + u8"と名乗ることにした。"s;
            cdatan(1, 0) = cmaka;
        }
        else
        {
            txt(lang(
                u8"あら、そのままでいいの？"s, u8"What a waste of a wish!"s));
            msgtemp = u8"あら、そのままでいいの？"s;
        }
        wish_end();
        return;
    }
    if (inputlog == u8"性転換"s || inputlog == u8"性"s || inputlog == u8"異性"s
        || inputlog == u8"sex"s)
    {
        if (cdata[0].sex == 0)
        {
            cdata[0].sex = 1;
        }
        else
        {
            cdata[0].sex = 0;
        }
        txt(lang(
            name(0) + u8"は"s + i18n::_(u8"ui", u8"sex", u8"_"s + cdata[0].sex)
                + u8"になった！ …もう後戻りはできないわよ。"s,
            name(0) + u8" become "s
                + i18n::_(u8"ui", u8"sex", u8"_"s + cdata[0].sex) + u8"!"s));
        wish_end();
        return;
    }
    if (inputlog == u8"贖罪"s || inputlog == u8"redemption"s
        || inputlog == u8"atonement"s)
    {
        if (cdata[0].karma >= 0)
        {
            txt(lang(
                u8"…罪なんて犯してないじゃない。"s, u8"You aren't a sinner."s));
            wish_end();
            return;
        }
        modify_karma(0, cdata[0].karma / 2 * -1);
        txt(lang(
            u8"あら…都合のいいことを言うのね。"s,
            u8"What a convenient wish!"s));
        wish_end();
        return;
    }
    if (inputlog == u8"死"s || inputlog == u8"death"s)
    {
        txt(lang(u8"それがお望みなら…"s, u8"If you wish so..."s));
        dmghp(0, 99999, -11);
        wish_end();
        return;
    }
    if (inputlog == u8"仲間"s || inputlog == u8"friend"s
        || inputlog == u8"company"s || inputlog == u8"ally"s)
    {
        evadd(12);
        wish_end();
        return;
    }
    if (inputlog == u8"金"s || inputlog == u8"金貨"s || inputlog == u8"富"s
        || inputlog == u8"財産"s || inputlog == u8"money"s
        || inputlog == u8"gold"s || inputlog == u8"wealth"s
        || inputlog == u8"fortune"s)
    {
        txtef(5);
        txt(lang(u8"金貨が降ってきた！"s, u8"Lots of gold pieces appear."s));
        flt();
        itemcreate(
            -1,
            54,
            cdata[0].position.x,
            cdata[0].position.y,
            (cdata[0].level / 3 + 1) * 10000);
        wish_end();
        return;
    }
    if (inputlog == u8"メダル"s || inputlog == u8"小さなメダル"s
        || inputlog == u8"ちいさなメダル"s || inputlog == u8"coin"s
        || inputlog == u8"medal"s || inputlog == u8"small coin"s
        || inputlog == u8"small medal"s)
    {
        txtef(5);
        txt(lang(u8"小さなメダルが降ってきた！"s, u8"A small coin appears."s));
        flt();
        itemcreate(
            -1, 622, cdata[0].position.x, cdata[0].position.y, 3 + rnd(3));
        wish_end();
        return;
    }
    if (inputlog == u8"プラチナ"s || inputlog == u8"プラチナ硬貨"s
        || inputlog == u8"platina"s || inputlog == u8"platinum"s)
    {
        txtef(5);
        txt(lang(
            u8"プラチナ硬貨が降ってきた！"s, u8"Platinum pieces appear."s));
        flt();
        itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 5);
        wish_end();
        return;
    }
    if (inputlog == u8"名声"s || inputlog == u8"fame"s)
    {
        txtef(5);
        txt(u8"fame +1,000,000");
        cdata[0].fame += 1'000'000;
        wish_end();
        return;
    }
    if (strutil::contains(inputlog(0), lang(u8"スキル"s, u8"skill"s)))
    {
        goto label_1999_internal;
    }
    if (strutil::contains(inputlog(0), lang(u8"アイテム"s, u8"item"s)))
    {
        goto label_1998_internal;
    }
    if (strutil::contains(inputlog(0), lang(u8"カード"s, u8"card"s)))
    {
        wish_for_card();
        return;
    }
    if (debug::voldemort)
    {
        if (strutil::contains(inputlog(0), u8"summon"))
        {
            wish_for_character();
            return;
        }
    }
    if (strutil::contains(inputlog(0), lang(u8"剥製"s, u8"figure"s))
        || strutil::contains(inputlog(0), u8"はく製"s))
    {
        wish_for_figure();
        return;
    }
label_1998_internal:
    number_of_items = elona::stoi(inputlog(0));
    if (debug::voldemort)
    {
        if (strutil::contains(inputlog(0), u8"呪われた")
            || strutil::contains(inputlog(0), u8"cursed "))
        {
            curse_state = curse_state_t::cursed;
        }
        else if (
            strutil::contains(inputlog(0), u8"堕落した")
            || strutil::contains(inputlog(0), u8"doomed "))
        {
            curse_state = curse_state_t::doomed;
        }
        else if (
            strutil::contains(inputlog(0), u8"祝福された")
            || strutil::contains(inputlog(0), u8"blessed "))
        {
            curse_state = curse_state_t::blessed;
        }
        else if (
            strutil::contains(inputlog(0), u8"呪われていない")
            || strutil::contains(inputlog(0), u8"uncursed "))
        {
            curse_state = curse_state_t::none;
        }
    }
    inputlog = fix_wish(inputlog);
    i = 0;
    for (int cnt = 0, cnt_end = (length(ioriginalnameref)); cnt < cnt_end;
         ++cnt)
    {
        if (cnt == 0)
        {
            continue;
        }
        if (cnt == 23)
        {
            continue;
        }
        if (cnt == 290)
        {
            continue;
        }
        if (cnt == 289)
        {
            continue;
        }
        if (cnt == 361)
        {
            continue;
        }
        p = 0;
        int cnt2 = cnt;
        if (ioriginalnameref(cnt) == inputlog)
        {
            p = 10000;
        }
        s = cnvitemname(cnt2);
        if (en)
        {
            s = strutil::to_lower(s(0));
        }
        for (int cnt = 0, cnt_end = (inputlog(0).size()); cnt < cnt_end; ++cnt)
        {
            if (strutil::contains(s(0), strmid(inputlog, 0, cnt * (1 + jp))))
            {
                p = p + 50 * (cnt + 1) + rnd(15);
            }
        }
        if (p != 0)
        {
            dblist(0, i) = cnt;
            dblist(1, i) = p;
            ++i;
        }
    }
    if (i != 0)
    {
        while (1)
        {
            p(0) = 0;
            p(1) = 0;
            for (int cnt = 0, cnt_end = (i); cnt < cnt_end; ++cnt)
            {
                if (dblist(1, cnt) > p(1))
                {
                    p(0) = dblist(0, cnt);
                    p(1) = dblist(1, cnt);
                    wishid = cnt;
                }
            }
            if (p == 0)
            {
                f = 0;
                break;
            }
            flt(cdata[0].level + 10, 4);
            if (p == 558 || p == 556 || p == 557 || p == 664)
            {
                fixlv = calcfixlv(3);
            }
            if (p == 630)
            {
                objfix = 2;
            }
            nostack = 1;
            nooracle = 1;
            itemcreate(-1, p, cdata[cc].position.x, cdata[cc].position.y, 0);
            nooracle = 0;
            if (ibit(5, ci) == 1 || inv[ci].quality == 6)
            {
                if (gdata_wizard == 0)
                {
                    dblist(1, wishid) = 0;
                    inv[ci].number = 0;
                    --itemmemory(1, inv[ci].id);
                    cell_refresh(inv[ci].position.x, inv[ci].position.y);
                    continue;
                }
            }
            if (inv[ci].id == 54)
            {
                inv[ci].number = cdata[0].level * cdata[0].level * 50 + 20000;
            }
            if (inv[ci].id == 55)
            {
                inv[ci].number = 8 + rnd(5);
            }
            if (inv[ci].id == 602)
            {
                inv[ci].number = 0;
                flt();
                itemcreate(
                    -1, 516, cdata[cc].position.x, cdata[cc].position.y, 3);
                inv[ci].curse_state = curse_state_t::blessed;
                txt(lang(u8"あ、それ在庫切れ。"s, u8"It's sold out."s));
            }
            if (the_item_db[inv[ci].id]->category == 52000
                || the_item_db[inv[ci].id]->category == 53000)
            {
                inv[ci].number = 3 + rnd(2);
                if (inv[ci].id == 559)
                {
                    inv[ci].number = 2 + rnd(2);
                }
                if (inv[ci].id == 502)
                {
                    inv[ci].number = 2;
                }
                if (inv[ci].id == 243)
                {
                    inv[ci].number = 1;
                }
                if (inv[ci].id == 621)
                {
                    inv[ci].number = 1;
                }
                if (inv[ci].id == 706)
                {
                    inv[ci].number = 1;
                }
                if (inv[ci].value >= 5000)
                {
                    inv[ci].number = 3;
                }
                if (inv[ci].value >= 10000)
                {
                    inv[ci].number = 2;
                }
                if (inv[ci].value >= 20000)
                {
                    inv[ci].number = 1;
                }
            }
            if (debug::voldemort && number_of_items != 0)
            {
                inv[ci].number = number_of_items;
            }
            if (curse_state)
            {
                inv[ci].curse_state = curse_state.get();
            }
            item_identify(
                inv[ci], identification_state_t::completely_identified);
            txt(lang(
                u8"足元に"s + itemname(ci) + u8"が転がってきた。"s,
                ""s + itemname(ci) + u8" appear"s + _s2(inv[ci].number)
                    + u8"."s));
            f = 1;
            break;
        }
        if (f)
        {
            wish_end();
            return;
        }
    }
label_1999_internal:
    inputlog = fix_wish(inputlog);
    i = 0;
    for (const auto& ability_data : the_ability_db)
    {
        const int id = ability_data.id;
        const bool is_basic_attribute_excluding_life_and_mana =
            10 <= id && id <= 19;
        const bool is_skill = 100 <= id && id <= 399;

        if (!is_basic_attribute_excluding_life_and_mana && !is_skill)
        {
            continue;
        }

        auto ability_name = i18n::_(u8"ability", std::to_string(id), u8"name");
        int priority = 0;
        if (ability_name == inputlog)
        {
            priority = 10'000;
        }
        if (en)
        {
            ability_name = strutil::to_lower(ability_name);
        }
        // Calculate similarity.
        for (int i = 0; i < inputlog(0).size() / (1 + jp); ++i)
        {
            if (instr(ability_name, 0, strmid(inputlog, i * (1 + jp), 1 + jp))
                != -1)
            {
                priority += 50 + rnd(15);
            }
        }

        if (priority != 0)
        {
            dblist(0, i) = id;
            dblist(1, i) = priority;
            ++i;
        }
    }
    if (i != 0)
    {
        p(0) = 0;
        p(1) = 0;
        for (int cnt = 0, cnt_end = (i); cnt < cnt_end; ++cnt)
        {
            if (dblist(1, cnt) > p(1))
            {
                p(0) = dblist(0, cnt);
                p(1) = dblist(1, cnt);
            }
        }
        if (i18n::_(u8"ability", std::to_string(p), u8"name") != ""s)
        {
            txtef(5);
            if (sdata.get(p, 0).original_level == 0)
            {
                txt(lang(
                    i18n::_(u8"ability", std::to_string(p), u8"name")
                        + u8"の技術を会得した！"s,
                    u8"You learn "s
                        + i18n::_(u8"ability", std::to_string(p), u8"name")
                        + u8"!"s));
                skillgain(0, p, 1);
            }
            else
            {
                txt(lang(
                    i18n::_(u8"ability", std::to_string(p), u8"name")
                        + u8"が上昇した！"s,
                    u8"Your "s
                        + i18n::_(u8"ability", std::to_string(p), u8"name")
                        + u8" skill improves!"s));
                skillmod(p, 0, 1000);
                modify_potential(0, p, 25);
            }
        }
        else
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        }
        wish_end();
        return;
    }
    txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
    wish_end();
    return;
}


} // namespace elona
