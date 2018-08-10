#include "wish.hpp"
#include "ability.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "db_item.hpp"
#include "debug.hpp"
#include "dmgheal.hpp"
#include "event.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "map_cell.hpp"
#include "menu.hpp"
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

    // TODO
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
    ret = remove_str(ret, u8"item");
    ret = remove_str(ret, u8"アイテム");
    ret = remove_str(ret, u8"skill");
    ret = remove_str(ret, u8"skill ");
    ret = remove_str(ret, u8"スキル");

    return ret;
}


std::string remove_extra_str(const std::string& text)
{
    using namespace strutil;

    auto ret{text};

    // TODO
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
        "wish"
        + i18n::s.get(
              "core.locale.wish.sent_message",
              cdatan(1, 0),
              cdatan(0, 0),
              i18n::s.get("core.locale.wish.your_wish", inputlog(0)),
              cnven(txtcopy)));

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
    chara_create(
        -1, dbid, cdata.player().position.x, cdata.player().position.y);
    cell_refresh(cdata[rc].position.x, cdata[rc].position.y);
    txt(cdatan(0, rc) + " is summoned.");
}



void wish_for_card()
{
    dbid = select_wished_character(inputlog);
    flt();
    chara_create(56, dbid, -3, 0);
    flt();
    itemcreate(
        -1, 504, cdata.player().position.x, cdata.player().position.y, 0);
    inv[ci].subname = cdata.tmp().id;
    inv[ci].param1 = cdata.tmp().image;
    chara_vanquish(56);
    cell_refresh(cdata.player().position.x, cdata.player().position.y);
    txt(i18n::s.get(
        "core.locale.wish.something_appears_from_nowhere", inv[ci]));
}



void wish_for_figure()
{
    dbid = select_wished_character(inputlog);
    flt();
    chara_create(56, dbid, -3, 0);
    flt();
    itemcreate(
        -1, 503, cdata.player().position.x, cdata.player().position.y, 0);
    inv[ci].subname = cdata.tmp().id;
    inv[ci].param1 = cdata.tmp().image;
    chara_vanquish(56);
    cell_refresh(cdata.player().position.x, cdata.player().position.y);
    txt(i18n::s.get(
        "core.locale.wish.something_appears_from_nowhere", inv[ci]));
}



template <typename F>
bool _match_wish(
    const std::string& key,
    const std::vector<std::string>& english_words,
    F match)
{
    auto words = i18n::s.get_list(key);
    words.insert(
        std::end(words), std::begin(english_words), std::end(english_words));
    return std::any_of(std::begin(words), std::end(words), match);
}



/// Returns true if `wish` equals one of the special words. English words are
/// available in all languages.
/// @params key The I18N key associated with the special words. Note that it
/// does not contain the prefix, "core.locale.wish.special_wish.".
bool match_special_wish(
    const std::string& wish,
    const std::string& key,
    const std::vector<std::string>& english_words)
{
    return _match_wish(
        "core.locale.wish.special_wish." + key,
        english_words,
        [&](const auto& word) { return wish == word; });
}



/// Returns true if `wish` equals one of the special words. English words are
/// available in all languages.
/// @params key The I18N key associated with the special words. Note that it
/// does not contain the prefix, "core.locale.wish.general_wish.".
bool match_general_wish(
    const std::string& wish,
    const std::string& key,
    const std::vector<std::string>& english_words)
{
    return _match_wish(
        "core.locale.wish.general_wish." + key,
        english_words,
        [&](const auto& word) { return strutil::contains(wish, word); });
}



bool grant_special_wishing(const std::string& wish)
{
    if (match_special_wish(wish, "god_inside", {"god inside"}))
    {
        txt(i18n::s.get("core.locale.wish.wish_god_inside"));
    }
    else if (match_special_wish(wish, "man_inside", {"man inside"}))
    {
        txt(i18n::s.get("core.locale.wish.wish_man_inside"));
    }
    else if (match_special_wish(wish, "ehekatl", {"ehekatl"}))
    {
        txt(i18n::s.get("core.locale.wish.wish_ehekatl"));
        flt();
        chara_create(
            -1, 331, cdata.player().position.x, cdata.player().position.y);
    }
    else if (match_special_wish(wish, "lulwy", {"lulwy"}))
    {
        txt(i18n::s.get("core.locale.wish.wish_lulwy"));
        flt();
        chara_create(
            -1, 306, cdata.player().position.x, cdata.player().position.y);
    }
    else if (match_special_wish(wish, "opatos", {"opatos"}))
    {
        txt(i18n::s.get("core.locale.wish.wish_opatos"));
        flt();
        chara_create(
            -1, 338, cdata.player().position.x, cdata.player().position.y);
    }
    else if (match_special_wish(wish, "kumiromi", {"kumiromi"}))
    {
        txt(i18n::s.get("core.locale.wish.wish_kumiromi"));
        flt();
        chara_create(
            -1, 339, cdata.player().position.x, cdata.player().position.y);
    }
    else if (match_special_wish(wish, "mani", {"mani"}))
    {
        txt(i18n::s.get("core.locale.wish.wish_mani"));
        flt();
        chara_create(
            -1, 342, cdata.player().position.x, cdata.player().position.y);
    }
    else if (match_special_wish(wish, "youth", {"youth", "age", "beauty"}))
    {
        txt(i18n::s.get("core.locale.wish.wish_youth"));
        cdata.player().birth_year += 20;
        if (cdata.player().birth_year + 12 > gdata_year)
        {
            cdata.player().birth_year = gdata_year - 12;
        }
    }
    else if (match_special_wish(
                 wish, "alias", {"aka", "title", "name", "alias"}))
    {
        if (gdata_wizard)
        {
            txt(i18n::s.get("core.locale.wish.wish_alias.impossible"));
        }
        else
        {
            txt(i18n::s.get(
                "core.locale.wish.wish_alias.what_is_your_new_alias"));
            int stat = select_alias(0);
            if (stat == 1)
            {
                txt(i18n::s.get(
                    "core.locale.wish.wish_alias.new_alias", cmaka));
                cdatan(1, 0) = cmaka;
            }
            else
            {
                txt(i18n::s.get("core.locale.wish.wish_alias.no_change"));
            }
        }
    }
    else if (match_special_wish(wish, "sex", {"sex"}))
    {
        cdata.player().sex = !cdata.player().sex;

        txt(i18n::s.get(
            "core.locale.wish.wish_sex",
            cdata.player(),
            i18n::_(u8"ui", u8"sex", u8"_"s + cdata.player().sex)));
    }
    else if (match_special_wish(
                 wish, "redemption", {"redemption", "atonement"}))
    {
        if (cdata.player().karma >= 0)
        {
            txt(i18n::s.get(
                "core.locale.wish.wish_redemption.you_are_not_a_sinner"));
        }
        else
        {
            modify_karma(cdata.player(), -cdata.player().karma / 2);
            txt(i18n::s.get(
                "core.locale.wish.wish_redemption.what_a_convenient_wish"));
        }
    }
    else if (match_special_wish(wish, "death", {"death"}))
    {
        txt(i18n::s.get("core.locale.wish.wish_death"));
        damage_hp(cdata.player(), 99999, -11);
    }
    else if (match_special_wish(wish, "ally", {"friend", "company", "ally"}))
    {
        event_add(12);
    }
    else if (match_special_wish(
                 wish, "gold", {"money", "gold", "wealth", "fortune"}))
    {
        txtef(5);
        txt(i18n::s.get("core.locale.wish.wish_gold"));
        flt();
        itemcreate(
            -1,
            54,
            cdata.player().position.x,
            cdata.player().position.y,
            (cdata.player().level / 3 + 1) * 10000);
    }
    else if (match_special_wish(
                 wish,
                 "small_medal",
                 {"small medal", "small coin", "medal", "coin"}))
    {
        txtef(5);
        txt(i18n::s.get("core.locale.wish.wish_small_medal"));
        flt();
        itemcreate(
            -1,
            622,
            cdata.player().position.x,
            cdata.player().position.y,
            3 + rnd(3));
    }
    else if (match_special_wish(wish, "platinum", {"platinum", "platina"}))
    {
        txtef(5);
        txt(i18n::s.get("core.locale.wish.wish_platinum"));
        flt();
        itemcreate(
            -1, 55, cdata.player().position.x, cdata.player().position.y, 5);
    }
    else if (gdata_wizard)
    {
        if (match_special_wish(wish, "fame", {"fame"}))
        {
            txtef(5);
            txt(u8"fame +1,000,000");
            cdata.player().fame += 1'000'000;
        }
        else
        {
            return false; // No match
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

    // TODO
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

        flt(cdata.player().level + 10, 4);
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
                inv[ci].remove();
                --itemmemory(1, inv[ci].id);
                cell_refresh(inv[ci].position.x, inv[ci].position.y);
                continue;
            }
        }

        if (inv[ci].id == 54)
        {
            inv[ci].set_number(
                cdata.player().level * cdata.player().level * 50 + 20000);
        }
        else if (inv[ci].id == 55)
        {
            inv[ci].set_number(8 + rnd(5));
        }
        else if (inv[ci].id == 602)
        {
            inv[ci].remove();
            flt();
            itemcreate(-1, 516, cdata[cc].position.x, cdata[cc].position.y, 3);
            inv[ci].curse_state = curse_state_t::blessed;
            txt(i18n::s.get("core.locale.wish.it_is_sold_out"));
        }
        if (the_item_db[inv[ci].id]->category == 52000
            || the_item_db[inv[ci].id]->category == 53000)
        {
            inv[ci].set_number(3 + rnd(2));
            if (inv[ci].value >= 20000)
            {
                inv[ci].set_number(1);
            }
            else if (inv[ci].value >= 10000)
            {
                inv[ci].set_number(2);
            }
            else if (inv[ci].value >= 5000)
            {
                inv[ci].set_number(3);
            }
            switch (inv[ci].id)
            {
            case 559: inv[ci].set_number(2 + rnd(2)); break;
            case 502: inv[ci].set_number(2); break;
            case 243: inv[ci].set_number(1); break;
            case 621: inv[ci].set_number(1); break;
            case 706: inv[ci].set_number(1); break;
            }
        }
        if (debug::voldemort && number_of_items != 0)
        {
            inv[ci].set_number(number_of_items);
        }
        if (debug::voldemort && curse_state)
        {
            inv[ci].curse_state = curse_state.get();
        }

        item_identify(inv[ci], identification_state_t::completely_identified);
        txt(i18n::s.get("core.locale.wish.something_appears", inv[ci]));
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
                txt(i18n::s.get("core.locale.wish.you_learn_skill", name));
                chara_gain_skill(cdata.player(), id, 1);
            }
            else
            {
                txt(i18n::s.get("core.locale.wish.your_skill_improves", name));
                chara_gain_fixed_skill_exp(cdata.player(), id, 1000);
                modify_potential(cdata.player(), id, 25);
            }
        }
        else
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            return false;
        }
    }
    else
    {
        txt(i18n::s.get("core.locale.common.nothing_happens"));
        return false;
    }
    return true;
}



bool process_wish()
{
    using namespace strutil;

    txtcopy = "";
    txtef(5);
    txt(i18n::s.get("core.locale.wish.what_do_you_wish_for"));

    input_text_dialog(
        (windoww - 290) / 2 + inf_screenx, winposy(90), 16, false);

    txt(i18n::s.get("core.locale.wish.your_wish", inputlog(0)));

    msgtemp = "";
    autosave = 1 * (gdata_current_map != mdata_t::map_id_t::show_house);
    tcopy = 1;

    if (inputlog(0) == "" || inputlog(0) == u8" ")
    {
        txt(i18n::s.get("core.locale.common.nothing_happens"));
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

    if (match_general_wish(inputlog, "skill", {"skill"}))
    {
        skip_character = true;
        skip_item = true;
    }
    if (match_general_wish(inputlog, "item", {"item"}))
    {
        skip_character = true;
    }

    if (!skip_character)
    {
        if (match_general_wish(inputlog, "card", {"card"}))
        {
            wish_for_card();
            return true;
        }
        if (debug::voldemort)
        {
            if (match_general_wish(inputlog, "summon", {"summon"}))
            {
                wish_for_character();
                return true;
            }
        }
        if (match_general_wish(inputlog, "figure", {"figure"}))
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
