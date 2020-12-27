#include "../util/strutil.hpp"
#include "calc.hpp"
#include "data/types/type_item.hpp"
#include "data/types/type_item_material.hpp"
#include "enchantment.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "variables.hpp"



namespace elona
{

namespace
{

elona_vector1<int> inhlist;



void _load_single_item_description_text(const I18NKey& desc_key_prefix, int& p)
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
                        desc_line, "。", one_line_size + total_size))
                {
                    one_line += "。";
                    one_line_size += std::strlen("。");
                }
                if (strutil::starts_with(
                        desc_line, "、", one_line_size + total_size))
                {
                    one_line += "、";
                    one_line_size += std::strlen("、");
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
                list(0, p) =
                    static_cast<int>(ItemDescriptionType::small_font_italic);
            }
            ++p;
        }
    }
}



void _load_item_description_text(
    const I18NKey& locale_key_prefix,
    int& num_of_desc)
{
    for (int i = 0; i < 3; ++i)
    {
        _load_single_item_description_text(
            locale_key_prefix + ".description._" + std::to_string(i),
            num_of_desc);
    }
}



void _load_item_main_description_text(
    const I18NKey& locale_key_prefix,
    int& num_of_desc)
{
    if (auto text =
            i18n::s.get_optional(locale_key_prefix + ".description.main.text"))
    {
        list(0, num_of_desc) = static_cast<int>(ItemDescriptionType::text);
        listn(0, num_of_desc) = *text;
        ++num_of_desc;
    }
}



void _load_item_stat_text(const ItemRef& item, int& num_of_desc)
{
    if (item->material != "")
    {
        list(0, num_of_desc) = static_cast<int>(ItemDescriptionType::text);
        listn(0, num_of_desc) = i18n::s.get(
            "core.item.desc.it_is_made_of",
            the_item_material_db.get_text(item->material, "name"));
        ++num_of_desc;
    }
    if (item->material == "core.ether")
    {
        list(0, num_of_desc) = static_cast<int>(ItemDescriptionType::text);
        listn(0, num_of_desc) =
            i18n::s.get("core.item.desc.speeds_up_ether_disease");
        ++num_of_desc;
    }
    if (item->is_acidproof)
    {
        list(0, num_of_desc) = static_cast<int>(ItemDescriptionType::text);
        listn(0, num_of_desc) = i18n::s.get("core.item.desc.bit.acidproof");
        ++num_of_desc;
    }
    if (item->is_fireproof)
    {
        list(0, num_of_desc) = static_cast<int>(ItemDescriptionType::text);
        listn(0, num_of_desc) = i18n::s.get("core.item.desc.bit.fireproof");
        ++num_of_desc;
    }
    if (item->is_precious)
    {
        list(0, num_of_desc) = static_cast<int>(ItemDescriptionType::text);
        listn(0, num_of_desc) = i18n::s.get("core.item.desc.bit.precious");
        ++num_of_desc;
    }
    if (item->is_blessed_by_ehekatl)
    {
        list(0, num_of_desc) = static_cast<int>(ItemDescriptionType::text);
        listn(0, num_of_desc) =
            i18n::s.get("core.item.desc.bit.blessed_by_ehekatl");
        ++num_of_desc;
    }
    if (item->is_stolen)
    {
        list(0, num_of_desc) = static_cast<int>(ItemDescriptionType::text);
        listn(0, num_of_desc) = i18n::s.get("core.item.desc.bit.stolen");
        ++num_of_desc;
    }
    if (item->is_alive)
    {
        list(0, num_of_desc) = static_cast<int>(ItemDescriptionType::text);
        listn(0, num_of_desc) = i18n::s.get("core.item.desc.bit.alive") +
            " [Lv:"s + item->param1 + " Exp:"s +
            clamp(item->param2 * 100 / calcexpalive(item->param1), 0, 100) +
            "%]"s;
        ++num_of_desc;
    }
    if (item->is_showroom_only)
    {
        list(0, num_of_desc) = static_cast<int>(ItemDescriptionType::text);
        listn(0, num_of_desc) =
            i18n::s.get("core.item.desc.bit.show_room_only");
        ++num_of_desc;
    }
    if (item->is_handmade)
    {
        list(0, num_of_desc) = static_cast<int>(ItemDescriptionType::text);
        listn(0, num_of_desc) = i18n::s.get("core.item.desc.bit.handmade");
        ++num_of_desc;
    }
    if (item->dice.rolls != 0)
    {
        const auto pierce =
            calc_rate_to_pierce(the_item_db[item->id]->integer_id);
        list(0, num_of_desc) =
            static_cast<int>(ItemDescriptionType::weapon_info);
        listn(0, num_of_desc) =
            i18n::s.get("core.item.desc.weapon.it_can_be_wielded") + " ("s +
            item->dice.rolls + "d"s + item->dice.faces +
            i18n::s.get("core.item.desc.weapon.pierce") + pierce + "%)"s;
        ++num_of_desc;
        if (reftype == 10000)
        {
            if (item->weight <= 1500)
            {
                list(0, num_of_desc) =
                    static_cast<int>(ItemDescriptionType::weapon_info);
                listn(0, num_of_desc) =
                    i18n::s.get("core.item.desc.weapon.light");
                ++num_of_desc;
            }
            if (item->weight >= 4000)
            {
                list(0, num_of_desc) =
                    static_cast<int>(ItemDescriptionType::weapon_info);
                listn(0, num_of_desc) =
                    i18n::s.get("core.item.desc.weapon.heavy");
                ++num_of_desc;
            }
        }
    }
    if (item->hit_bonus != 0 || item->dice.bonus != 0)
    {
        list(0, num_of_desc) =
            static_cast<int>(ItemDescriptionType::weapon_info);
        listn(0, num_of_desc) = i18n::s.get(
            "core.item.desc.bonus", item->hit_bonus, item->dice.bonus);
        ++num_of_desc;
    }
    if (item->pv != 0 || item->dv != 0)
    {
        list(0, num_of_desc) =
            static_cast<int>(ItemDescriptionType::armor_info);
        listn(0, num_of_desc) =
            i18n::s.get("core.item.desc.dv_pv", item->dv, item->pv);
        ++num_of_desc;
    }
}



void _load_item_enchantment_desc(const ItemRef& item, int& num_of_desc)
{
    const auto inheritance = item_get_inheritance(item);

    size_t enc_index{};
    for (const auto& enc : item->enchantments)
    {
        get_enchantment_description(
            enc.id, enc.power, the_item_db[item->id]->category);
        listn(0, num_of_desc) = i18n::s.get("core.enchantment.it") + s;
        list(0, num_of_desc) = rtval;
        list(1, num_of_desc) = rtval(1);

        const auto is_inherited =
            range::find(inheritance, enc_index) != std::end(inheritance);
        if (is_inherited)
        {
            list(0, num_of_desc) += 10000;
        }
        ++num_of_desc;
        ++enc_index;
    }

    if (item->is_eternal_force)
    {
        list(0, num_of_desc) =
            static_cast<int>(ItemDescriptionType::enchantment);
        listn(0, num_of_desc) = i18n::s.get("core.item.desc.bit.eternal_force");
        ++num_of_desc;
    }
}

} // namespace



size_t item_load_desc(const ItemRef& item)
{
    int num_of_desc{};

    const I18NKey& locale_key_prefix = the_item_db[item->id]->locale_key_prefix;

    if (item->identify_state == IdentifyState::completely)
    {
        _load_item_main_description_text(locale_key_prefix, num_of_desc);
    }
    if (item->identify_state >= IdentifyState::almost)
    {
        _load_item_stat_text(item, num_of_desc);
    }
    if (item->identify_state <= IdentifyState::partly)
    {
        list(0, num_of_desc) = static_cast<int>(ItemDescriptionType::normal);
        listn(0, num_of_desc) = i18n::s.get("core.item.desc.have_to_identify");
        ++num_of_desc;
    }
    if (item->identify_state == IdentifyState::completely)
    {
        _load_item_enchantment_desc(item, num_of_desc);
        _load_item_description_text(locale_key_prefix, num_of_desc);
    }
    if (num_of_desc == 0)
    {
        list(0, num_of_desc) = static_cast<int>(ItemDescriptionType::normal);
        listn(0, num_of_desc) = i18n::s.get("core.item.desc.no_information");
        ++num_of_desc;
    }

    return static_cast<size_t>(num_of_desc);
}

} // namespace elona
