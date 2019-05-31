#include "autopick.hpp"
#include "../util/fileutil.hpp"
#include "../util/strutil.hpp"
#include "data/types/type_item.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "variables.hpp"



namespace
{

struct ModifierMatchResult
{
    bool matched;
    bool has_any_modifier;
    std::string text_without_modifier;
};



struct ModifierMatcher
{
    // It does not contain the prefix, "core.locale.autopick.modifier."
    const char* locale_key;
    std::function<bool(const Item&)> predicate;
};



std::vector<ModifierMatcher> _modifier_matchers = {
    {"all", [](const Item&) { return true; }},
    {"unknown",
     [](const Item& item) {
         return item.identification_state == IdentifyState::unidentified;
     }},
    {"identify_stage1",
     [](const Item& item) {
         return item.identification_state == IdentifyState::partly_identified;
     }},
    {"identify_stage2",
     [](const Item& item) {
         return item.identification_state == IdentifyState::almost_identified;
     }},
    {"identify_stage3",
     [](const Item& item) {
         return item.identification_state ==
             IdentifyState::completely_identified;
     }},
    {"worthless", [](const Item& item) { return item.value <= 10; }},
    {"rotten", [](const Item& item) { return item.param3 < 0; }},
    {"empty",
     [](const Item& item) {
         return the_item_db[item.id]->category == 72000 && item.param1 == 0;
     }},
    {"bad",
     [](const Item& item) {
         return item.identification_state >= IdentifyState::almost_identified &&
             item.quality == Quality::bad;
     }},
    {"good",
     [](const Item& item) {
         return item.identification_state >= IdentifyState::almost_identified &&
             item.quality == Quality::good;
     }},
    {"great",
     [](const Item& item) {
         return item.identification_state >= IdentifyState::almost_identified &&
             item.quality == Quality::great;
     }},
    {"miracle",
     [](const Item& item) {
         return item.identification_state >= IdentifyState::almost_identified &&
             item.quality == Quality::miracle;
     }},
    {"godly",
     [](const Item& item) {
         return item.identification_state >= IdentifyState::almost_identified &&
             item.quality == Quality::godly;
     }},
    {"special",
     [](const Item& item) {
         return item.identification_state >= IdentifyState::almost_identified &&
             item.quality == Quality::special;
     }},
    {"precious",
     [](const Item& item) {
         return item.identification_state >= IdentifyState::almost_identified &&
             item.is_precious();
     }},
    {"blessed",
     [](const Item& item) {
         return item.identification_state >= IdentifyState::almost_identified &&
             item.curse_state == CurseState::blessed;
     }},
    {"cursed",
     [](const Item& item) {
         return item.identification_state >= IdentifyState::almost_identified &&
             item.curse_state == CurseState::cursed;
     }},
    {"doomed",
     [](const Item& item) {
         return item.identification_state >= IdentifyState::almost_identified &&
             item.curse_state == CurseState::doomed;
     }},
    {"alive", [](const Item& item) { return item.is_alive(); }},
};



ModifierMatchResult _check_modifiers(const std::string& text, const Item& item)
{
    const auto word_separator = i18n::s.get("core.locale.meta.word_separator");

    ModifierMatchResult result{
        true, false, word_separator + text + word_separator};

    for (const auto& matcher : _modifier_matchers)
    {
        const auto word = word_separator +
            i18n::s.get(
                "core.locale.autopick.modifier."s + matcher.locale_key) +
            word_separator;
        if (strutil::contains(result.text_without_modifier, word))
        {
            if (matcher.predicate(item))
            {
                result.text_without_modifier = strutil::replace(
                    result.text_without_modifier, word, word_separator);
                result.has_any_modifier = true;
            }
            else
            {
                return {false, true, text};
            }
        }
    }

    return result;
}



bool _check_category(const std::string& text, const Item& item)
{
    const auto category = the_item_db[item.id]->category;
    const auto word_separator = i18n::s.get("core.locale.meta.word_separator");
    const auto text_ = word_separator + text + word_separator;

#define ELONA_AUTOPICK_CATEGORY(locale_key, expected_category) \
    if (strutil::contains( \
            text_, \
            word_separator + \
                i18n::s.get("core.locale.autopick.category." #locale_key) + \
                word_separator)) \
    { \
        return category == expected_category; \
    }

    if (strutil::contains(
            text_,
            word_separator + i18n::s.get("core.locale.autopick.category.item") +
                word_separator))
    {
        return true;
    }
    if (strutil::contains(
            text_,
            word_separator +
                i18n::s.get("core.locale.autopick.category.equipment") +
                word_separator))
    {
        return category < 50000;
    }

    ELONA_AUTOPICK_CATEGORY(melee_weapon, 10000)
    ELONA_AUTOPICK_CATEGORY(helm, 12000)
    ELONA_AUTOPICK_CATEGORY(shield, 14000)
    ELONA_AUTOPICK_CATEGORY(armor, 16000)
    ELONA_AUTOPICK_CATEGORY(boots, 18000)
    ELONA_AUTOPICK_CATEGORY(belt, 19000)
    ELONA_AUTOPICK_CATEGORY(cloak, 20000)
    ELONA_AUTOPICK_CATEGORY(gloves, 22000)
    ELONA_AUTOPICK_CATEGORY(ranged_weapon, 24000)
    ELONA_AUTOPICK_CATEGORY(ammo, 25000)
    ELONA_AUTOPICK_CATEGORY(ring, 32000)
    ELONA_AUTOPICK_CATEGORY(necklace, 34000)
    ELONA_AUTOPICK_CATEGORY(potion, 52000)
    ELONA_AUTOPICK_CATEGORY(scroll, 53000)
    ELONA_AUTOPICK_CATEGORY(spellbook, 54000)
    ELONA_AUTOPICK_CATEGORY(book, 55000)
    ELONA_AUTOPICK_CATEGORY(rod, 56000)
    ELONA_AUTOPICK_CATEGORY(foods, 57000)
    ELONA_AUTOPICK_CATEGORY(tool, 59000)
    ELONA_AUTOPICK_CATEGORY(furniture, 60000)
    ELONA_AUTOPICK_CATEGORY(well, 60001)
    ELONA_AUTOPICK_CATEGORY(altar, 60002)
    ELONA_AUTOPICK_CATEGORY(bodyparts, 62000)
    ELONA_AUTOPICK_CATEGORY(junk, 64000)
    ELONA_AUTOPICK_CATEGORY(gold_piece, 68000)
    ELONA_AUTOPICK_CATEGORY(platinum_coin, 69000)
    ELONA_AUTOPICK_CATEGORY(chest, 72000)
    ELONA_AUTOPICK_CATEGORY(ore, 77000)
    ELONA_AUTOPICK_CATEGORY(tree, 80000)
    ELONA_AUTOPICK_CATEGORY(travelers_food, 91000)
    ELONA_AUTOPICK_CATEGORY(cargo, 92000)

#undef ELONA_AUTOPICK_CATEGORY
    return false;
}

} // namespace



namespace elona
{

Autopick& Autopick::instance()
{
    static Autopick the_instance;
    return the_instance;
}



void Autopick::load(const std::string& player_id)
{
    _clear();

    // Priority: save/xxx/autopick > save/autopick > /autopick
    for (const auto directory : {filesystem::dirs::save(player_id),
                                 filesystem::dirs::save(),
                                 filesystem::dirs::exe()})
    {
        for (const auto filename :
             {u8"autopick", u8"autopick.txt", u8"autopick.txt.txt"})
        {
            const auto filepath = directory / filename;
            bool file_exists = _try_load(filepath);
            if (file_exists)
                break;
        }
    }
}



void Autopick::_clear()
{
    matchers.clear();
}



Autopick::Matcher Autopick::_parse_each_line(std::string line)
{
    Operation op{Operation::Type::pick_up};

    if (strutil::starts_with(line, u8"%=") ||
        strutil::starts_with(line, u8"=%"))
    {
        op.type = Operation::Type::save_and_no_drop;
        line = line.substr(2);
    }
    else
    {
        switch (line.front())
        {
        case '~':
            op.type = Operation::Type::do_nothing;
            line = line.substr(1);
            break;
        case '%':
            op.type = Operation::Type::save;
            line = line.substr(1);
            break;
        case '=':
            op.type = Operation::Type::no_drop;
            line = line.substr(1);
            break;
        case '!':
            op.type = Operation::Type::destroy;
            line = line.substr(1);
            break;
        case '+':
            op.type = Operation::Type::open;
            line = line.substr(1);
            break;
        default: break;
        }
    }

    // xxx:core.sound_id?
    if (!line.empty() && line.back() == '?')
    {
        op.show_prompt = true;
        line = line.substr(0, line.size() - 1);
    }

    // sound
    const auto colon = line.find(':');
    if (colon != std::string::npos)
    {
        auto sound_id = line.substr(colon + 1);
        if (!strutil::contains(sound_id, "."))
        {
            // Adds "core" if no mod prefix.
            sound_id = "core." + sound_id;
        }
        op.sound = SharedId(sound_id);
        line = line.substr(0, colon);
    }

    // xxx?:core.sound_id
    if (!line.empty() && line.back() == '?')
    {
        op.show_prompt = true;
        line = line.substr(0, line.size() - 1);
    }

    return {line, op};
}



bool Autopick::_try_load(const fs::path& filepath)
{
    if (!fs::exists(filepath))
        return false;

    for (const auto& line : fileutil::read_by_line(filepath))
    {
        if (line.empty())
        {
            continue;
        }
        if (strutil::starts_with(line, u8"#"))
        {
            continue;
        }

        matchers.push_back(_parse_each_line(line));
    }

    return true;
}



Autopick::Operation Autopick::get_operation(const Item& ci)
{
    for (const auto& m : matchers)
    {
        if (m.matches(ci))
        {
            return m.op;
        }
    }

    return Operation{};
}



bool Autopick::Matcher::matches(const Item& ci) const
{
    /* Check modifiers. */
    const auto modifier_match_result = _check_modifiers(text, ci);
    if (!modifier_match_result.matched)
    {
        return false;
    }

    /* Check item's name. */
    const auto item_name = cnvitemname(ci.id);
    // You have to know that the item is known as the name to match by the name.
    const auto you_know_the_name =
        ci.identification_state != IdentifyState::unidentified;
    const auto item_name_matched_with_text = you_know_the_name &&
        strutil::contains(item_name,
                          modifier_match_result.text_without_modifier);

    if (item_name_matched_with_text)
    {
        return true;
    }

    /* Check item category. */
    if (!modifier_match_result.has_any_modifier)
    {
        return false;
    }

    return _check_category(modifier_match_result.text_without_modifier, ci);
}

} // namespace elona
