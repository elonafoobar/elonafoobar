#include "wish.hpp"

#include <array>

#include "../util/range.hpp"
#include "../util/strutil.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "chara_db.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "config.hpp"
#include "data/types/type_item.hpp"
#include "data/types/type_skill.hpp"
#include "debug.hpp"
#include "deferred_event.hpp"
#include "dmgheal.hpp"
#include "game.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "map_cell.hpp"
#include "menu.hpp"
#include "message.hpp"
#include "net.hpp"
#include "optional.hpp"
#include "random.hpp"
#include "save.hpp"
#include "skill.hpp"
#include "text.hpp"
#include "ui.hpp"
#include "variables.hpp"



namespace
{

template <typename T, typename Similarity = int>
class BySimilaritySelector
{
public:
    void add(const T& value, const Similarity& similarity)
    {
        candidates.emplace_back(value, similarity);
    }

    void remove(const T& value)
    {
        const auto itr = range::find_if(candidates, [&](const auto& candidate) {
            return candidate.value == value;
        });
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
                                           : std::make_optional(itr->value);
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
    struct Candidate
    {
        T value;
        Similarity similarity;

        Candidate(const T& value, const Similarity& similarity)
            : value(value)
            , similarity(similarity)
        {
        }
    };

    std::vector<Candidate> candidates;
};



class LogCopyObserver : public LogObserver
{
public:
    virtual ~LogCopyObserver() = default;



    virtual void update(const std::string& log) override
    {
        _log_copy += log;
    }



    const std::string& get_copy() const
    {
        return _log_copy;
    }


private:
    std::string _log_copy;
};

std::unique_ptr<LogCopyObserver> log_copy_observer;


std::array<
    std::vector<lua::WrappedFunction>,
    static_cast<size_t>(WishHook::_size)>
    wish_hooks;



bool call_hook(WishHook type, const std::string& input)
{
    for (auto&& hooks : wish_hooks.at(static_cast<size_t>(type)))
    {
        if (hooks.call_with_result(false, input))
        {
            return true;
        }
    }
    return false;
}



std::string fix_wish(const std::string& text)
{
    using namespace strutil;

    auto ret{text};

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
    net_send_wish(
        i18n::s.get("core.wish.your_wish", inputlog(0)),
        cnven(log_copy_observer->get_copy()));

    log_copy_observer.reset();
}



int select_wished_character(const std::string& input)
{
    constexpr int default_result = 37;
    using namespace strutil;

    BySimilaritySelector<int> selector;
    const auto wish = remove_extra_str(input);
    for (int i = 0; i < 800; ++i)
    {
        int similarity{};
        auto name = chara_db_get_name(int2charaid(i));
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
    flt();
    if (const auto chara = chara_create(
            -1,
            select_wished_character(inputlog),
            cdata.player().position.x,
            cdata.player().position.y))
    {
        txt(chara->name + " is summoned.");
    }
}



void wish_for_card()
{
    flt();
    nooracle = 1;
    chara_create(56, select_wished_character(inputlog), -3, 0);
    nooracle = 0;
    flt();
    if (const auto item = itemcreate_map_inv(504, cdata.player().position, 0))
    {
        item->subname = charaid2int(cdata.tmp().id);
        item->param1 = cdata.tmp().image;
        chara_vanquish(cdata.tmp());
        txt(i18n::s.get(
            "core.wish.something_appears_from_nowhere", item.unwrap()));
    }
}



void wish_for_figure()
{
    flt();
    nooracle = 1;
    chara_create(56, select_wished_character(inputlog), -3, 0);
    nooracle = 0;
    flt();
    if (const auto item = itemcreate_map_inv(503, cdata.player().position, 0))
    {
        item->subname = charaid2int(cdata.tmp().id);
        item->param1 = cdata.tmp().image;
        chara_vanquish(cdata.tmp());
        txt(i18n::s.get(
            "core.wish.something_appears_from_nowhere", item.unwrap()));
    }
}



/// Returns true if `wish` equals one of the special words. English words are
/// available in all languages.
/// @params key The I18N key associated with the special words. Note that it
/// does not contain the prefix, "core.wish.special_wish.".
bool match_special_wish(
    const std::string& wish,
    const std::string& key,
    const std::vector<std::string>& english_words)
{
    return wish_match(
        wish,
        WishMatchType::perfect,
        "core.wish.special_wish." + key,
        english_words);
}



/// Returns true if `wish` equals one of the special words. English words are
/// available in all languages.
/// @params key The I18N key associated with the special words. Note that it
/// does not contain the prefix, "core.wish.general_wish.".
bool match_general_wish(
    const std::string& wish,
    const std::string& key,
    const std::vector<std::string>& english_words)
{
    return wish_match(
        wish,
        WishMatchType::include,
        "core.wish.general_wish." + key,
        english_words);
}



bool grant_special_wishing(const std::string& wish)
{
    if (match_special_wish(wish, "god_inside", {"god inside"}))
    {
        txt(i18n::s.get("core.wish.wish_god_inside"));
    }
    else if (match_special_wish(wish, "man_inside", {"man inside"}))
    {
        txt(i18n::s.get("core.wish.wish_man_inside"));
    }
    else if (match_special_wish(wish, "ehekatl", {"ehekatl"}))
    {
        txt(i18n::s.get("core.wish.wish_ehekatl"));
        flt();
        chara_create(
            -1, 331, cdata.player().position.x, cdata.player().position.y);
    }
    else if (match_special_wish(wish, "lulwy", {"lulwy"}))
    {
        txt(i18n::s.get("core.wish.wish_lulwy"));
        flt();
        chara_create(
            -1, 306, cdata.player().position.x, cdata.player().position.y);
    }
    else if (match_special_wish(wish, "opatos", {"opatos"}))
    {
        txt(i18n::s.get("core.wish.wish_opatos"));
        flt();
        chara_create(
            -1, 338, cdata.player().position.x, cdata.player().position.y);
    }
    else if (match_special_wish(wish, "kumiromi", {"kumiromi"}))
    {
        txt(i18n::s.get("core.wish.wish_kumiromi"));
        flt();
        chara_create(
            -1, 339, cdata.player().position.x, cdata.player().position.y);
    }
    else if (match_special_wish(wish, "mani", {"mani"}))
    {
        txt(i18n::s.get("core.wish.wish_mani"));
        flt();
        chara_create(
            -1, 342, cdata.player().position.x, cdata.player().position.y);
    }
    else if (match_special_wish(wish, "youth", {"youth", "age", "beauty"}))
    {
        txt(i18n::s.get("core.wish.wish_youth"));

        const auto this_year = game_date().year();
        const auto youngest_age = 12;
        const auto y = cdata.player().birthday.year();
        const auto m = cdata.player().birthday.month();
        const auto d = cdata.player().birthday.day();
        const auto new_y = std::min(y + 20, this_year - youngest_age);
        cdata.player().birthday = time::Date{new_y, m, d};
    }
    else if (match_special_wish(
                 wish, "alias", {"aka", "title", "name", "alias"}))
    {
        txt(i18n::s.get("core.wish.wish_alias.what_is_your_new_alias"));
        if (const auto result = select_alias(RandomTitleType::character))
        {
            txt(i18n::s.get("core.wish.wish_alias.new_alias", result->alias));
            cdata.player().alias = result->alias;
        }
        else
        {
            txt(i18n::s.get("core.wish.wish_alias.no_change"));
        }
    }
    else if (match_special_wish(wish, "sex", {"sex"}))
    {
        cdata.player().sex = !cdata.player().sex;

        txt(i18n::s.get(
            "core.wish.wish_sex",
            cdata.player(),
            i18n::s.get_enum("core.ui.sex", cdata.player().sex)));
    }
    else if (match_special_wish(
                 wish, "redemption", {"redemption", "atonement"}))
    {
        if (cdata.player().karma >= 0)
        {
            txt(i18n::s.get("core.wish.wish_redemption.you_are_not_a_sinner"));
        }
        else
        {
            modify_karma(cdata.player(), -cdata.player().karma / 2);
            txt(i18n::s.get(
                "core.wish.wish_redemption.what_a_convenient_wish"));
        }
    }
    else if (match_special_wish(wish, "death", {"death"}))
    {
        txt(i18n::s.get("core.wish.wish_death"));
        damage_hp(cdata.player(), 99999, -11);
    }
    else if (match_special_wish(wish, "ally", {"friend", "company", "ally"}))
    {
        deferred_event_add("core.reunoin_with_pets");
    }
    else if (match_special_wish(
                 wish, "gold", {"money", "gold", "wealth", "fortune"}))
    {
        const auto amount = debug_is_wizard()
            ? (1000 * 1000 * 1000)
            : (cdata.player().level / 3 + 1) * 10000;
        txt(i18n::s.get("core.wish.wish_gold"),
            Message::color{ColorIndex::orange});
        flt();
        itemcreate_map_inv(54, cdata.player().position, amount);
    }
    else if (match_special_wish(
                 wish,
                 "small_medal",
                 {"small medal", "small coin", "medal", "coin"}))
    {
        const auto amount = debug_is_wizard() ? 1000 : 3 + rnd(3);
        txt(i18n::s.get("core.wish.wish_small_medal"),
            Message::color{ColorIndex::orange});
        flt();
        itemcreate_map_inv(622, cdata.player().position, amount);
    }
    else if (match_special_wish(wish, "platinum", {"platinum", "platina"}))
    {
        const auto amount = debug_is_wizard() ? (1000 * 1000) : 5;
        txt(i18n::s.get("core.wish.wish_platinum"),
            Message::color{ColorIndex::orange});
        flt();
        itemcreate_map_inv(55, cdata.player().position, amount);
    }
    else
    {
        return false; // No match
    }

    return true; // Grant some wishing.
}



bool wish_for_item(Character& chara, const std::string& input)
{
    using namespace strutil;

    BySimilaritySelector<int> selector;
    const auto wish = fix_wish(input);
    for (const auto& item_data : the_item_db.values())
    {
        const auto id = item_data.integer_id;

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

    while (true)
    {
        const auto opt_id = selector.get();
        if (!opt_id)
            break;

        const auto id = *opt_id;

        flt(cdata.player().level + 10, Quality::miracle);
        if (id == 558 || id == 556 || id == 557 || id == 664)
        {
            fixlv = calcfixlv(Quality::good);
        }
        if (id == 630)
        {
            objfix = 2;
        }

        nostack = 1;
        nooracle = 1;
        auto item = itemcreate_map_inv(id, chara.position, 0);
        nooracle = 0;

        if (!item)
            continue;

        // Unwishable item
        if (item->is_precious || item->quality == Quality::special)
        {
            if (!debug_is_wizard())
            {
                // Remove this item and retry.
                selector.remove(id);
                item->remove();
                game()->item_memories.decrement_generate_count(item->id);
                continue;
            }
        }

        if (item->id == "core.gold_piece")
        {
            item->set_number(
                cdata.player().level * cdata.player().level * 50 + 20000);
        }
        else if (item->id == "core.platinum_coin")
        {
            item->set_number(8 + rnd(5));
        }
        else if (item->id == "core.holy_well")
        {
            item->remove();
            flt();
            if (const auto well = itemcreate_map_inv(516, chara.position, 3))
            {
                well->curse_state = CurseState::blessed;
                txt(i18n::s.get("core.wish.it_is_sold_out"));
                item = well;
            }
            else
            {
                continue;
            }
        }
        if (the_item_db[item->id]->category == ItemCategory::potion ||
            the_item_db[item->id]->category == ItemCategory::scroll)
        {
            item->set_number(3 + rnd(2));
            if (item->value >= 20000)
            {
                item->set_number(1);
            }
            else if (item->value >= 10000)
            {
                item->set_number(2);
            }
            else if (item->value >= 5000)
            {
                item->set_number(3);
            }
            switch (the_item_db[item->id]->integer_id)
            {
            case 559: item->set_number(2 + rnd(2)); break;
            case 502: item->set_number(2); break;
            case 243: item->set_number(1); break;
            case 621: item->set_number(1); break;
            case 706: item->set_number(1); break;
            }
        }

        item_identify(item.unwrap(), IdentifyState::completely);
        txt(i18n::s.get("core.wish.something_appears", item.unwrap()));
        return true;
    }

    return false;
}



bool wish_for_skill(const std::string& input)
{
    using namespace strutil;

    BySimilaritySelector<int> selector;
    const auto wish = fix_wish(input);

    for (const auto& ability_data : the_skill_db.values())
    {
        const int id = ability_data.integer_id;
        const bool is_basic_attribute_excluding_life_and_mana =
            10 <= id && id <= 19;
        const bool is_skill = 100 <= id && id <= 399;

        if (!is_basic_attribute_excluding_life_and_mana && !is_skill)
        {
            continue;
        }

        auto name = the_skill_db.get_text(id, "name");
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
        const auto name = the_skill_db.get_text(id, "name");
        if (!name.empty())
        {
            if (cdata.player().skills().base_level(
                    *the_skill_db.get_id_from_integer(id)) == 0)
            {
                txt(i18n::s.get("core.wish.you_learn_skill", name),
                    Message::color{ColorIndex::orange});
                chara_gain_skill(cdata.player(), id, 1);
            }
            else
            {
                txt(i18n::s.get("core.wish.your_skill_improves", name),
                    Message::color{ColorIndex::orange});
                chara_gain_fixed_skill_exp(cdata.player(), id, 1000);
                skill_add_potential(
                    cdata.player(), *the_skill_db.get_id_from_integer(id), 25);
            }
        }
        else
        {
            txt(i18n::s.get("core.common.nothing_happens"));
            return false;
        }
    }
    else
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        return false;
    }
    return true;
}



bool process_wish(Character& chara, optional<std::string> wish)
{
    using namespace strutil;

    txt(i18n::s.get("core.wish.what_do_you_wish_for"),
        Message::color{ColorIndex::orange});

    if (wish)
    {
        inputlog(0) = *wish;
    }
    else
    {
        input_text_dialog((windoww - 290) / 2 + inf_screenx, winposy(90), 16);
    }

    txt(i18n::s.get("core.wish.your_wish", inputlog(0)));

    save_trigger_autosaving();

    log_copy_observer = std::make_unique<LogCopyObserver>();
    subscribe_log(log_copy_observer.get());

    if (call_hook(WishHook::first, inputlog(0)))
    {
        return true;
    }

    if (inputlog(0) == "" || inputlog(0) == u8" ")
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        return false;
    }
    if (en)
    {
        inputlog = to_lower(inputlog);
    }

    snd("core.ding2");

    if (call_hook(WishHook::before_vanilla_special, inputlog(0)))
    {
        return true;
    }

    if (grant_special_wishing(inputlog))
    {
        return true;
    }

    if (call_hook(WishHook::after_vanilla_special, inputlog(0)))
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
        if (debug_is_wizard())
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

    if (call_hook(WishHook::before_vanilla_item, inputlog(0)))
    {
        return true;
    }

    if (!skip_item && wish_for_item(chara, inputlog))
    {
        return true;
    }

    if (call_hook(WishHook::after_vanilla_item, inputlog(0)))
    {
        return true;
    }

    if (call_hook(WishHook::before_vanilla_skill, inputlog(0)))
    {
        return true;
    }

    if (wish_for_skill(inputlog))
    {
        return true;
    }

    if (call_hook(WishHook::after_vanilla_skill, inputlog(0)))
    {
        return true;
    }

    if (call_hook(WishHook::last, inputlog(0)))
    {
        return true;
    }

    return false;
}

} // namespace



namespace elona
{

bool what_do_you_wish_for(Character& chara, optional<std::string> wish)
{
    const auto did_wish_something = process_wish(chara, wish);
    if (did_wish_something)
    {
        wish_end();
    }
    return did_wish_something;
}



bool wish_match(
    const std::string& input,
    WishMatchType match_type,
    const std::string& i18n_key_to_word_list,
    const std::vector<std::string>& english_words)
{
    auto words = i18n::s.get_list(i18n_key_to_word_list);
    words.insert(
        std::end(words), std::begin(english_words), std::end(english_words));

    return range::any_of(words, [&](const auto& word) {
        switch (match_type)
        {
        case WishMatchType::prefix: return strutil::starts_with(input, word);
        case WishMatchType::suffix: return strutil::ends_with(input, word);
        case WishMatchType::include: return strutil::contains(input, word);
        case WishMatchType::perfect: return input == word;
        default: throw "unreachable";
        }
    });
}



void wish_add(WishHook hook, lua::WrappedFunction callback)
{
    wish_hooks.at(static_cast<size_t>(hook)).push_back(callback);
}

} // namespace elona
