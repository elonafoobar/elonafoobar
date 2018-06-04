#include "wish.hpp"
#include "ability.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "debug.hpp"
#include "dmgheal.hpp"
#include "event.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "item_db.hpp"
#include "itemgen.hpp"
#include "map_cell.hpp"
#include "network.hpp"
#include "optional.hpp"
#include "random.hpp"
#include "variables.hpp"


namespace
{


template <typename T, typename Similarity = int>
class by_similarity_selector
{
public:
    void add(const T& value, const Similarity& similarity)
    {
        candidates.emplace_back(value, similarity);
    }

    void remove(const T& value)
    {
        const auto itr = std::find_if(
            std::begin(candidates),
            std::end(candidates),
            [&](const auto& candidate) { return candidate.value == value; });
        if (itr != std::end(candidates))
        {
            candidates.erase(itr);
        }
    }

    bool empty() const
    {
        return candidates.empty();
    }

    optional<T> get() const
    {
        const auto itr = std::max_element(
            std::begin(candidates),
            std::end(candidates),
            [](const auto& a, const auto& b) {
                return a.similarity < b.similarity;
            });
        return itr == std::end(candidates) ? none
                                           : boost::make_optional(itr->value);
    }

    T get_force() const
    {
        return *get();
    }

    T get_or(const T& default_value) const
    {
        return get().value_or(default_value);
    }

private:
    struct candidate_t
    {
        T value;
        Similarity similarity;

        candidate_t(const T& value, const Similarity& similarity)
            : value(value)
            , similarity(similarity)
        {
        }
    };

    std::vector<candidate_t> candidates;
};


std::string fix_wish(const std::string& text)
{
    using namespace strutil;

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
    using namespace strutil;

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
    if (gdata_wizard || wishfilter)
        return;

    net_send(
        u8"wish"
        + lang(
              cdatan(1, 0) + cdatan(0, 0) + u8"は狂喜して叫んだ。「" + inputlog
                  + u8"！！」" + txtcopy,
              cdatan(1, 0) + u8" " + cdatan(0, 0) + u8" goes wild with joy, \""
                  + inputlog + u8"!!\" " + cnven(txtcopy)));

    wishfilter = 1;
}


int select_wished_character(const std::string& input)
{
    constexpr int default_result = 37;
    using namespace strutil;

    by_similarity_selector<int> selector;
    const auto wish = remove_extra_str(input);
    for (int i = 0; i < 800; ++i)
    {
        int similarity{};
        auto name = chara_refstr(i, 2);
        if (en)
        {
            name = to_lower(name);
        }
        if (contains(name, wish))
        {
            similarity = 1000 - (strlen_u(name) - strlen_u(wish)) * 10;
        }
        if (similarity)
        {
            selector.add(i, similarity);
        }
    }

    return selector.get_or(default_result);
}


void wish_for_character()
{
    inputlog = strutil::remove_str(inputlog, u8"summon");
    dbid = select_wished_character(inputlog);
    flt();
    chara_create(-1, dbid, cdata[0].position.x, cdata[0].position.y);
    cell_refresh(cdata[rc].position.x, cdata[rc].position.y);
    txt(cdatan(0, rc) + " is summoned.");
}


void wish_for_card()
{
    dbid = select_wished_character(inputlog);
    flt();
    chara_create(56, dbid, -3, 0);
    flt();
    itemcreate(-1, 504, cdata[0].position.x, cdata[0].position.y, 0);
    inv[ci].subname = cdata[56].id;
    inv[ci].param1 = cdata[56].image;
    chara_vanquish(56);
    cell_refresh(cdata[0].position.x, cdata[0].position.y);
    txt(lang(
        u8"足元に" + itemname(ci) + u8"が転がってきた。",
        "" + itemname(ci) + u8" appear" + _s2(inv[ci].number)
            + u8" from nowhere."));
}


void wish_for_figure()
{
    dbid = select_wished_character(inputlog);
    flt();
    chara_create(56, dbid, -3, 0);
    flt();
    itemcreate(-1, 503, cdata[0].position.x, cdata[0].position.y, 0);
    inv[ci].subname = cdata[56].id;
    inv[ci].param1 = cdata[56].image;
    chara_vanquish(56);
    cell_refresh(cdata[0].position.x, cdata[0].position.y);
    txt(lang(
        u8"足元に" + itemname(ci) + u8"が転がってきた。",
        "" + itemname(ci) + u8" appear" + _s2(inv[ci].number)
            + u8" from nowhere."));
}


bool grant_special_wishing(const std::string& wish)
{
    using namespace strutil;

    if (contains(wish, u8"中の神") || contains(wish, u8"god inside"))
    {
        txt(lang(
            u8"中の神も大変…あ…中の神なんているわけないじゃない！…ねえ、聞かな"
            u8"かったことにしてね。",
            u8"There's no God inside."));
    }
    else if (contains(wish, u8"中の人") || contains(wish, u8"man inside"))
    {
        txt(lang(u8"中の人も大変ね。", u8"There's no man inside."));
    }
    else if (wish == u8"エヘカトル" || wish == u8"ehekatl")
    {
        txt(lang(u8"「うみみゅみゅぁ！」", u8"\"Meeewmew!\""));
        flt();
        chara_create(-1, 331, cdata[0].position.x, cdata[0].position.y);
    }
    else if (wish == u8"ルルウィ" || wish == u8"lulwy")
    {
        txt(lang(
            u8"「アタシを呼びつけるとは生意気ね。」",
            u8"\"You dare to call my name?\""));
        flt();
        chara_create(-1, 306, cdata[0].position.x, cdata[0].position.y);
    }
    else if (wish == u8"オパートス" || wish == u8"opatos")
    {
        txt(lang(u8"工事中。", u8"\"Under construction.\""));
        flt();
        chara_create(-1, 338, cdata[0].position.x, cdata[0].position.y);
    }
    else if (wish == u8"クミロミ" || wish == u8"kumiromi")
    {
        txt(lang(u8"工事中。", u8"\"Under construction.\""));
        flt();
        chara_create(-1, 339, cdata[0].position.x, cdata[0].position.y);
    }
    else if (wish == u8"マニ" || wish == u8"mani")
    {
        txt(lang(u8"工事中。", u8"\"Under construction.\""));
        flt();
        chara_create(-1, 342, cdata[0].position.x, cdata[0].position.y);
    }
    else if (
        wish == u8"若さ" || wish == u8"若返り" || wish == u8"年"
        || wish == u8"美貌" || wish == u8"youth" || wish == u8"age"
        || wish == u8"beauty")
    {
        txt(lang(u8"ふぅん…そんな願いでいいんだ。", u8"A typical wish."));
        cdata[0].birth_year += 20;
        if (cdata[0].birth_year + 12 > gdata_year)
        {
            cdata[0].birth_year = gdata_year - 12;
        }
    }
    else if (
        wish == u8"通り名" || wish == u8"異名" || wish == u8"aka"
        || wish == u8"title" || wish == u8"name" || wish == u8"alias")
    {
        if (gdata_wizard)
        {
            txt(lang(u8"だめよ。", u8"*laugh*"));
        }
        txt(lang(u8"新しい異名は？", u8"What's your new alias?"));
        int stat = select_alias(0);
        if (stat == 1)
        {
            txt(lang(
                u8"あなたの新しい異名は「" + cmaka + u8"」。満足したかしら？",
                u8"You will be known as <" + cmaka + u8">."));
            cdatan(1, 0) = cmaka;
        }
        else
        {
            txt(lang(
                u8"あら、そのままでいいの？", u8"What a waste of a wish!"));
        }
    }
    else if (
        wish == u8"性転換" || wish == u8"性" || wish == u8"異性"
        || wish == u8"sex")
    {
        cdata[0].sex = !cdata[0].sex;

        txt(lang(
            name(0) + u8"は" + i18n::_(u8"ui", u8"sex", u8"_"s + cdata[0].sex)
                + u8"になった！ …もう後戻りはできないわよ。",
            name(0) + u8" become "
                + i18n::_(u8"ui", u8"sex", u8"_"s + cdata[0].sex) + u8"!"));
    }
    else if (
        wish == u8"贖罪" || wish == u8"redemption" || wish == u8"atonement")
    {
        if (cdata[0].karma >= 0)
        {
            txt(lang(
                u8"…罪なんて犯してないじゃない。", u8"You aren't a sinner."));
        }
        modify_karma(0, -cdata[0].karma / 2);
        txt(lang(
            u8"あら…都合のいいことを言うのね。", u8"What a convenient wish!"));
    }
    else if (wish == u8"死" || wish == u8"death")
    {
        txt(lang(u8"それがお望みなら…", u8"If you wish so..."));
        dmghp(0, 99999, -11);
    }
    else if (
        wish == u8"仲間" || wish == u8"friend" || wish == u8"company"
        || wish == u8"ally")
    {
        event_add(12);
    }
    else if (
        wish == u8"金" || wish == u8"金貨" || wish == u8"富" || wish == u8"財産"
        || wish == u8"money" || wish == u8"gold" || wish == u8"wealth"
        || wish == u8"fortune")
    {
        txtef(5);
        txt(lang(u8"金貨が降ってきた！", u8"Lots of gold pieces appear."));
        flt();
        itemcreate(
            -1,
            54,
            cdata[0].position.x,
            cdata[0].position.y,
            (cdata[0].level / 3 + 1) * 10000);
    }
    else if (
        wish == u8"メダル" || wish == u8"小さなメダル"
        || wish == u8"ちいさなメダル" || wish == u8"coin" || wish == u8"medal"
        || wish == u8"small coin" || wish == u8"small medal")
    {
        txtef(5);
        txt(lang(u8"小さなメダルが降ってきた！", u8"A small coin appears."));
        flt();
        itemcreate(
            -1, 622, cdata[0].position.x, cdata[0].position.y, 3 + rnd(3));
    }
    else if (
        wish == u8"プラチナ" || wish == u8"プラチナ硬貨" || wish == u8"platina"
        || wish == u8"platinum")
    {
        txtef(5);
        txt(lang(u8"プラチナ硬貨が降ってきた！", u8"Platinum pieces appear."));
        flt();
        itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 5);
    }
    else if (gdata_wizard)
    {
        if (wish == u8"名声" || wish == u8"fame")
        {
            txtef(5);
            txt(u8"fame +1,000,000");
            cdata[0].fame += 1'000'000;
        }
    }
    else
    {
        return false; // No match
    }

    return true; // Grant some wishing.
}


bool wish_for_item(const std::string& input)
{
    using namespace strutil;

    const auto number_of_items = elona::stoi(input);
    optional<curse_state_t> curse_state;

    if (debug::voldemort)
    {
        if (contains(input, u8"呪われた") || contains(input, u8"cursed "))
        {
            curse_state = curse_state_t::cursed;
        }
        else if (contains(input, u8"堕落した") || contains(input, u8"doomed "))
        {
            curse_state = curse_state_t::doomed;
        }
        else if (
            contains(input, u8"祝福された") || contains(input, u8"blessed "))
        {
            curse_state = curse_state_t::blessed;
        }
        else if (
            contains(input, u8"呪われていない")
            || contains(input, u8"uncursed "))
        {
            curse_state = curse_state_t::none;
        }
    }

    by_similarity_selector<int> selector;
    const auto wish = fix_wish(input);
    for (const auto& item_data : the_item_db)
    {
        const auto id = item_data.id;

        if (id == 0 || id == 23 || id == 290 || id == 289 || id == 361)
            continue;

        int similarity{};
        if (ioriginalnameref(id) == wish)
        {
            similarity = 10'000;
        }
        auto name = cnvitemname(id);
        if (en)
        {
            name = to_lower(name);
        }
        // Calculate similarity.
        for (size_t i = 0; i < wish.size();)
        {
            const auto byte = byte_count(wish[i]);
            if (contains(name, wish.substr(0, i + byte)))
            {
                similarity += 50 + (i * 1) + rnd(15);
            }
            i += byte;
        }

        if (similarity)
        {
            selector.add(id, similarity);
        }
    }

    if (selector.empty())
        return false;

    while (1)
    {
        const auto opt_id = selector.get();
        if (!opt_id)
            break;

        const auto id = *opt_id;

        flt(cdata[0].level + 10, 4);
        if (id == 558 || id == 556 || id == 557 || id == 664)
        {
            fixlv = calcfixlv(3);
        }
        if (id == 630)
        {
            objfix = 2;
        }

        nostack = 1;
        nooracle = 1;
        itemcreate(-1, id, cdata[cc].position.x, cdata[cc].position.y, 0);
        nooracle = 0;

        // Unwishable item
        if (ibit(5, ci) || inv[ci].quality == 6)
        {
            if (!gdata_wizard)
            {
                // Remove this item and retry.
                selector.remove(id);
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
        else if (inv[ci].id == 55)
        {
            inv[ci].number = 8 + rnd(5);
        }
        else if (inv[ci].id == 602)
        {
            inv[ci].number = 0;
            flt();
            itemcreate(-1, 516, cdata[cc].position.x, cdata[cc].position.y, 3);
            inv[ci].curse_state = curse_state_t::blessed;
            txt(lang(u8"あ、それ在庫切れ。", u8"It's sold out."));
        }
        if (the_item_db[inv[ci].id]->category == 52000
            || the_item_db[inv[ci].id]->category == 53000)
        {
            inv[ci].number = 3 + rnd(2);
            if (inv[ci].value >= 20000)
            {
                inv[ci].number = 1;
            }
            else if (inv[ci].value >= 10000)
            {
                inv[ci].number = 2;
            }
            else if (inv[ci].value >= 5000)
            {
                inv[ci].number = 3;
            }
            switch (inv[ci].id)
            {
            case 559: inv[ci].number = 2 + rnd(2); break;
            case 502: inv[ci].number = 2; break;
            case 243: inv[ci].number = 1; break;
            case 621: inv[ci].number = 1; break;
            case 706: inv[ci].number = 1; break;
            }
        }
        if (debug::voldemort && number_of_items != 0)
        {
            inv[ci].number = number_of_items;
        }
        if (debug::voldemort && curse_state)
        {
            inv[ci].curse_state = curse_state.get();
        }

        item_identify(inv[ci], identification_state_t::completely_identified);
        txt(lang(
            u8"足元に" + itemname(ci) + u8"が転がってきた。",
            "" + itemname(ci) + u8" appear" + _s2(inv[ci].number) + u8"."));
        return true;
    }

    return false;
}


bool wish_for_skill(const std::string& input)
{
    using namespace strutil;

    by_similarity_selector<int> selector;
    const auto wish = fix_wish(input);

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

        auto name = i18n::_(u8"ability", std::to_string(id), u8"name");
        int similarity = 0;
        if (name == wish)
        {
            similarity = 10'000;
        }
        if (en)
        {
            name = to_lower(name);
        }
        // Calculate similarity.
        for (size_t i = 0; i < wish.size();)
        {
            const auto byte = byte_count(wish[i]);
            if (contains(name, wish.substr(i, byte)))
            {
                similarity += 50 + rnd(15);
            }
            i += byte;
        }

        if (similarity != 0)
        {
            selector.add(id, similarity);
        }
    }
    if (!selector.empty())
    {
        const auto id = selector.get_force();
        const auto name = i18n::_(u8"ability", std::to_string(id), u8"name");
        if (!name.empty())
        {
            txtef(5);
            if (sdata.get(id, 0).original_level == 0)
            {
                txt(lang(
                    name + u8"の技術を会得した！",
                    u8"You learn " + name + u8"!"));
                skillgain(0, id, 1);
            }
            else
            {
                txt(lang(
                    name + u8"が上昇した！",
                    u8"Your " + name + u8" skill improves!"));
                skillmod(id, 0, 1000);
                modify_potential(0, id, 25);
            }
        }
        else
        {
            txt(lang(u8"何もおきない… ", u8"Nothing happens..."));
            return false;
        }
    }
    else
    {
        txt(lang(u8"何もおきない… ", u8"Nothing happens..."));
        return false;
    }
    return true;
}


bool process_wish()
{
    using namespace strutil;

    txtcopy = "";
    txtef(5);
    txt(lang(u8"何を望む？", u8"What do you wish for? "));

    input_text_dialog(
        (windoww - 290) / 2 + inf_screenx, winposy(90), 16, false);

    txt(lang(u8"「" + inputlog + u8"！！」", u8"\"" + inputlog + u8"!!\""));

    msgtemp = "";
    autosave = 1 * (gdata_current_map != 35);
    tcopy = 1;

    if (inputlog(0) == "" || inputlog(0) == u8" ")
    {
        txt(lang(u8"何もおきない… ", u8"Nothing happens..."));
        return false;
    }
    if (en)
    {
        inputlog = to_lower(inputlog);
    }

    snd(24);

    if (grant_special_wishing(inputlog))
    {
        return true;
    }

    bool skip_character{};
    bool skip_item{};

    if (contains(inputlog, lang(u8"スキル", u8"skill")))
    {
        skip_character = true;
        skip_item = true;
    }
    if (contains(inputlog, lang(u8"アイテム", u8"item")))
    {
        skip_character = true;
    }

    if (!skip_character)
    {
        if (contains(inputlog, lang(u8"カード", u8"card")))
        {
            wish_for_card();
            return true;
        }
        if (debug::voldemort)
        {
            if (contains(inputlog, u8"summon"))
            {
                wish_for_character();
                return true;
            }
        }
        if (contains(inputlog, lang(u8"剥製", u8"figure"))
            || contains(inputlog, u8"はく製"))
        {
            wish_for_figure();
            return true;
        }
    }

    if (!skip_item)
    {
        bool granted = wish_for_item(inputlog);
        if (granted)
            return true;
    }

    wish_for_skill(inputlog);

    return true;
}


} // namespace


namespace elona
{


void what_do_you_wish_for()
{
    const auto did_wish_something = process_wish();
    if (did_wish_something)
        wish_end();
}


} // namespace elona
