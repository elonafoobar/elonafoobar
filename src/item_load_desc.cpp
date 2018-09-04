#include "calc.hpp"
#include "db_item.hpp"
#include "enchantment.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "util.hpp"

namespace elona
{

static void _load_single_item_description_text(
    const I18NKey& desc_key_prefix,
    int& p)
{
    auto desc_opt = i18n::s.get_optional(desc_key_prefix + ".text");
    if (!desc_opt)
    {
        return;
    }
    std::string buf = *desc_opt;
    if (auto footnote = i18n::s.get_optional(desc_key_prefix + ".footnote"))
    {
        buf += "\n" + *footnote;
    }
    list(0, p) = static_cast<int>(ItemDescriptionType::normal);
    listn(0, p) = "";
    ++p;
    notesel(buf);
    for (int cnt = 0, cnt_end = (noteinfo()); cnt < cnt_end; ++cnt)
    {
        std::string desc_line;
        noteget(desc_line, cnt);
        constexpr size_t max_width = 66;
        if (strlen_u(desc_line) > max_width)
        {
            int total_size = 0;
            for (size_t i = 0; i < strlen_u(desc_line) / max_width + 1; ++i)
            {
                auto one_line = strutil::take_by_width(
                    desc_line.substr(total_size), max_width);
                int one_line_size = one_line.size();
                if (strutil::starts_with(
                        desc_line, u8"。", one_line_size + total_size))
                {
                    one_line += u8"。";
                    one_line_size += std::strlen(u8"。");
                }
                if (strutil::starts_with(
                        desc_line, u8"、", one_line_size + total_size))
                {
                    one_line += u8"、";
                    one_line_size += std::strlen(u8"、");
                }
                if (strmid(desc_line, total_size, one_line_size) == ""s)
                {
                    break;
                }
                list(0, p) = static_cast<int>(ItemDescriptionType::small_font);
                listn(0, p) = one_line;
                ++p;
                total_size += one_line_size;
            }
        }
        else
        {
            list(0, p) = static_cast<int>(ItemDescriptionType::normal);
            listn(0, p) = desc_line;
            if (cnt == noteinfo() - 1)
            {
                list(0, p) = static_cast<int>(ItemDescriptionType::small_font_italic);
            }
            ++p;
        }
    }
}


static void _load_item_description_text(
    const I18NKey& locale_key_prefix,
    int& p)
{
    for (int cnt = 0; cnt < 3; ++cnt)
    {
        _load_single_item_description_text(
            locale_key_prefix + ".description._" + std::to_string(cnt), p);
    }
}

static void _load_item_main_description_text(
    const I18NKey& locale_key_prefix,
    int& p)
{
    if (auto text =
            i18n::s.get_optional(locale_key_prefix + ".description.main.text"))
    {
        list(0, p) = static_cast<int>(ItemDescriptionType::text);
        listn(0, p) = *text;
        ++p;
    }
}

static void _load_item_stat_text(int ci, int& p)
{
    if (inv[ci].material != 0)
    {
        list(0, p) = static_cast<int>(ItemDescriptionType::text);
        listn(0, p) = i18n::s.get(
            "core.locale.item.desc.it_is_made_of",
            i18n::_(
                u8"item_material", std::to_string(inv[ci].material), u8"name"));
        ++p;
    }
    if (inv[ci].material == 8)
    {
        list(0, p) = static_cast<int>(ItemDescriptionType::text);
        listn(0, p) =
            i18n::s.get("core.locale.item.desc.speeds_up_ether_disease");
        ++p;
    }
    if (ibit(1, ci))
    {
        list(0, p) = static_cast<int>(ItemDescriptionType::text);
        listn(0, p) = i18n::s.get("core.locale.item.desc.bit.acidproof");
        ++p;
    }
    if (ibit(2, ci))
    {
        list(0, p) = static_cast<int>(ItemDescriptionType::text);
        listn(0, p) = i18n::s.get("core.locale.item.desc.bit.fireproof");
        ++p;
    }
    if (ibit(5, ci))
    {
        list(0, p) = static_cast<int>(ItemDescriptionType::text);
        listn(0, p) = i18n::s.get("core.locale.item.desc.bit.precious");
        ++p;
    }
    if (ibit(8, ci))
    {
        list(0, p) = static_cast<int>(ItemDescriptionType::text);
        listn(0, p) =
            i18n::s.get("core.locale.item.desc.bit.blessed_by_ehekatl");
        ++p;
    }
    if (ibit(9, ci))
    {
        list(0, p) = static_cast<int>(ItemDescriptionType::text);
        listn(0, p) = i18n::s.get("core.locale.item.desc.bit.stolen");
        ++p;
    }
    if (ibit(10, ci))
    {
        list(0, p) = static_cast<int>(ItemDescriptionType::text);
        listn(0, p) = i18n::s.get("core.locale.item.desc.bit.alive")
            + u8" [Lv:"s + inv[ci].param1 + u8" Exp:"s
            + clamp(inv[ci].param2 * 100 / calcexpalive(inv[ci].param1), 0, 100)
            + u8"%]"s;
        ++p;
    }
    if (ibit(16, ci))
    {
        list(0, p) = static_cast<int>(ItemDescriptionType::text);
        listn(0, p) = i18n::s.get("core.locale.item.desc.bit.show_room_only");
        ++p;
    }
    if (ibit(17, ci))
    {
        list(0, p) = static_cast<int>(ItemDescriptionType::text);
        listn(0, p) = i18n::s.get("core.locale.item.desc.bit.handmade");
        ++p;
    }
    if (inv[ci].dice_x != 0)
    {
        const auto pierce = calc_rate_to_pierce(inv[ci].id);
        list(0, p) = static_cast<int>(ItemDescriptionType::weapon_info);
        listn(0, p) =
            i18n::s.get("core.locale.item.desc.weapon.it_can_be_wielded")
            + u8" ("s + inv[ci].dice_x + u8"d"s + inv[ci].dice_y
            + i18n::s.get("core.locale.item.desc.weapon.pierce") + pierce
            + u8"%)"s;
        ++p;
        if (reftype == 10000)
        {
            if (inv[ci].weight <= 1500)
            {
                list(0, p) = static_cast<int>(ItemDescriptionType::weapon_info);
                listn(0, p) = i18n::s.get("core.locale.item.desc.weapon.light");
                ++p;
            }
            if (inv[ci].weight >= 4000)
            {
                list(0, p) = static_cast<int>(ItemDescriptionType::weapon_info);
                listn(0, p) = i18n::s.get("core.locale.item.desc.weapon.heavy");
                ++p;
            }
        }
    }
    if (inv[ci].hit_bonus != 0 || inv[ci].damage_bonus != 0)
    {
        list(0, p) = static_cast<int>(ItemDescriptionType::weapon_info);
        listn(0, p) = i18n::s.get(
            "core.locale.item.desc.bonus",
            inv[ci].hit_bonus,
            inv[ci].damage_bonus);
        ++p;
    }
    if (inv[ci].pv != 0 || inv[ci].dv != 0)
    {
        list(0, p) = static_cast<int>(ItemDescriptionType::armor_info);
        listn(0, p) =
            i18n::s.get("core.locale.item.desc.dv_pv", inv[ci].dv, inv[ci].pv);
        ++p;
    }
    if (inv[ci].id == 701)
    {
        int card_count{};
        for (int i = 0; i < 1000; ++i)
        {
            if (card(0, i))
                ++card_count;
        }
        int npc_count{};
        for (const auto& discord : the_character_db)
        {
            UNUSED(discord);
            ++npc_count;
        }
        const auto percentage = std::min(100 * card_count / npc_count, 100);
        list(0, p) = static_cast<int>(ItemDescriptionType::text);
        listn(0, p) = i18n::s.get("core.locale.item.desc.deck") + u8": "s
            + card_count + u8"/" + npc_count + u8"(" + percentage + u8"%)";
        ++p;
    }
}

static void _load_item_enchantment_desc(int ci, int& p)
{
    int inhmax = 0;
    elona_vector1<int> inhlist;
    getinheritance(ci, inhlist, inhmax);

    for (int cnt = 0; cnt < 15; ++cnt)
    {
        if (inv[ci].enchantments[cnt].id == 0)
        {
            break;
        }
        get_enchantment_description(
            inv[ci].enchantments[cnt].id,
            inv[ci].enchantments[cnt].power,
            reftype);
        listn(0, p) = i18n::s.get("core.locale.enchantment.it") + s;
        list(0, p) = rtval;
        list(1, p) = rtval(1);
        if (inhmax > 0)
        {
            int cnt2 = cnt;
            for (int cnt = 0, cnt_end = (inhmax); cnt < cnt_end; ++cnt)
            {
                if (cnt2 == inhlist(cnt))
                {
                    list(0, p) += 10000;
                    break;
                }
            }
        }
        ++p;
    }
    if (ibit(15, ci))
    {
        list(0, p) = static_cast<int>(ItemDescriptionType::enchantment);
        listn(0, p) = i18n::s.get("core.locale.item.desc.bit.eternal_force");
        ++p;
    }
}


void item_load_desc(int ci, int& p)
{
    const I18NKey& locale_key_prefix =
        the_item_db[inv[ci].id]->locale_key_prefix;

    if (inv[ci].identification_state
        == IdentifyState::completely_identified)
    {
        _load_item_main_description_text(locale_key_prefix, p);
    }
    if (inv[ci].identification_state
        >= IdentifyState::almost_identified)
    {
        _load_item_stat_text(ci, p);
    }
    if (inv[ci].identification_state
        <= IdentifyState::partly_identified)
    {
        list(0, p) = static_cast<int>(ItemDescriptionType::normal);
        listn(0, p) = i18n::s.get("core.locale.item.desc.have_to_identify");
        ++p;
    }
    if (inv[ci].identification_state
        == IdentifyState::completely_identified)
    {
        _load_item_enchantment_desc(ci, p);
        _load_item_description_text(locale_key_prefix, p);
    }
    if (p == 0)
    {
        list(0, p) = static_cast<int>(ItemDescriptionType::normal);
        listn(0, p) = i18n::s.get("core.locale.item.desc.no_information");
        ++p;
    }
}

} // namespace elona
