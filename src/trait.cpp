#include "trait.hpp"
#include "ability.hpp"
#include "cat.hpp"
#include "character.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "optional.hpp"
#include "range.hpp"
#include "variables.hpp"

using namespace elona;


namespace elona
{


TraitDB the_trait_db;


void TraitDB::define(lua_State* L)
{
    const char* id = luaL_checkstring(L, -2);
    if (!id)
        throw std::runtime_error(u8"Error: fail to load trait data");

    ELONA_CAT_DB_FIELD_INTEGER(type, 0);
    ELONA_CAT_DB_FIELD_INTEGER(min, 0);
    ELONA_CAT_DB_FIELD_INTEGER(max, 0);

    storage.emplace(
        std::stoi(id), // TODO
        TraitData{
            std::stoi(id),
            TraitData::Type(type),
            min,
            max,
        });
}


namespace
{
void trait_format_other_parameterized(
    const I18NKey& i18n_prefix,
    int tid,
    int min)
{
    optional<std::string> text = none;
    I18NKey full_prefix = i18n_prefix + ".negative.levels";
    int level = trait(tid);

    // Assumptions:
    // 1. Ether Disease traits are not named.
    // 2. Ether Disease traits only have negative levels.
    // 3. Ether Disease traits will always have at least one negative level.
    // 4. Each Ether Disease trait level may have a unique parameter to pass in.

    if (level < 0)
    {
        for (int cnt = 0; cnt < (-min); cnt++)
        {
            int index = cnt + 3;
            switch (tid)
            {
            case 202:
                // "You have sores on your face. [CHR${_1}]"
                traitrefn(index) = i18n::s.get_enum(
                    full_prefix, cnt, level * (4 + cdata.player().level / 5));
                break;
            case 203:
                // "Your feet transformed into hooves. [SPD+${_1} Can't wear
                // boots]"
                traitrefn(index) = i18n::s.get_enum(
                    full_prefix, cnt, 20 + cdata.player().level / 2);
                break;
            case 204:
                // "You have 4 eyes. [PER+${_1} CHR${_2}]"
                traitrefn(index) = i18n::s.get_enum(
                    full_prefix,
                    cnt,
                    (5 + cdata.player().level / 3),
                    (5 + cdata.player().level / 3) * -1);
                break;
            case 205:
                // "You have grown feather. [SPD+${_1} Weight-20% Can't wear
                // cloaks]"
                traitrefn(index) = i18n::s.get_enum(
                    full_prefix, cnt, (12 + cdata.player().level / 4));
                break;
            case 206:
                // "Your neck is extremely thick. [CHR${_1} PV+${_2} Can't wear
                // amulets]"
                traitrefn(index) = i18n::s.get_enum(
                    full_prefix,
                    cnt,
                    (5 + cdata.player().level / 5) * -1,
                    (12 + cdata.player().level));
                break;
            case 207:
                // "Desire for violence arises within you. [DV${_1} Dmg
                // bonus+${_2}]"
                traitrefn(index) = i18n::s.get_enum(
                    full_prefix,
                    cnt,
                    (15 + cdata.player().level * 3 / 2) * -1,
                    (5 + cdata.player().level * 2 / 3));
                break;
            case 208:
                // "Your head has grown huge. [CON${_1} DEX${_2} LER+${_3}
                // WIL+${_4}]"
                traitrefn(index) = i18n::s.get_enum(
                    full_prefix,
                    cnt,
                    (5 + cdata.player().level / 3) * -1,
                    (4 + cdata.player().level / 4) * -1,
                    (6 + cdata.player().level / 2),
                    (2 + cdata.player().level / 6));
                break;
            case 211:
                // "You suffer debilitation. [HP-15% STR${_1}]"
                traitrefn(index) = i18n::s.get_enum(
                    full_prefix, cnt, (4 + cdata.player().level / 2) * -1);
                break;
            case 212:
                // "You have dementia. [MP-15% MAG${_1}]"
                traitrefn(index) = i18n::s.get_enum(
                    full_prefix, cnt, (4 + cdata.player().level / 2) * -1);
                break;
            case 213:
                // "You are covered by heavy carapace. [PV+${_1} SPD${_2}]"
                traitrefn(index) = i18n::s.get_enum(
                    full_prefix,
                    cnt,
                    (15 + cdata.player().level / 2),
                    (20 + cdata.player().level / 2) * -1);
                break;
            default:
                traitrefn(index) = i18n::s.get_enum(full_prefix, cnt);
                break;
            }
        }
    }
}

void trait_format_other_parameterless(
    const I18NKey& i18n_prefix,
    int tid,
    int min,
    int max)
{
    // Change in positive direction
    if (trait(tid) >= 0)
    {
        if (auto text = i18n::s.get_optional(i18n_prefix + ".positive.name"))
        {
            traitrefn(2) = *text;
        }
        for (int cnt = 0; cnt < max; cnt++)
        {
            traitrefn(cnt + 3) =
                i18n::s.get_enum(i18n_prefix + ".positive.levels", cnt);
        }
    }
    // Change in negative direction
    else if (trait(tid) < 0)
    {
        if (auto text = i18n::s.get_optional(i18n_prefix + ".negative.name"))
        {
            traitrefn(2) = *text;
        }
        for (int cnt = 0; cnt < (-min); cnt++)
        {
            traitrefn(cnt + 3) =
                i18n::s.get_enum(i18n_prefix + ".negative.levels", cnt);
        }
    }
}

bool trait_is_obtainable(const I18NKey& i18n_prefix, int tid)
{
    return trait(tid) >= 0
        && i18n::s.get_enum_property_opt(i18n_prefix + ".levels", "name", 0);
}


void trait_format_other(const I18NKey& i18n_prefix, int tid, int min, int max)
{
    if (auto text = i18n::s.get_optional(i18n_prefix + ".positive.gain"))
    {
        traitrefn(0) = *text;
    }
    if (auto text = i18n::s.get_optional(i18n_prefix + ".negative.gain"))
    {
        traitrefn(1) = *text;
    }

    if (tid >= 200)
    {
        // Ether Disease traits could have parameters to pass
        // into the format string, so format them separately.
        trait_format_other_parameterized(i18n_prefix, tid, min);
    }
    else
    {
        trait_format_other_parameterless(i18n_prefix, tid, min, max);
    }
}

void trait_format_obtainable(const I18NKey& i18n_prefix, int max)
{
    traitrefn(2) = i18n::s.get(i18n_prefix + ".desc");

    for (int cnt = 0; cnt < max; cnt++)
    {
        traitrefn2(cnt) =
            i18n::s.get_enum_property(i18n_prefix + ".levels", "name", cnt);
        traitrefn(cnt + 3) =
            i18n::s.get_enum_property(i18n_prefix + ".levels", "desc", cnt);
    }
}

void trait_format(int tid, int min, int max)
{
    I18NKey i18n_prefix = "core.locale.trait._" + std::to_string(tid);
    optional<std::string> text = none;

    traitrefn(0) = "";
    traitrefn(1) = "";
    traitrefn(2) = "";

    if (trait_is_obtainable(i18n_prefix, tid))
    {
        trait_format_obtainable(i18n_prefix, max);
    }
    else
    {
        trait_format_other(i18n_prefix, tid, min, max);
    }
}



/**
 * Returns if you can acquire the trait. Note that it returns true for traits
 * other than feats such as ether disease.
 */
bool is_acquirable(int id)
{
    switch (id)
    {
    case 4: return trait(id) == 0 || cdata.player().level >= 5;
    case 6: return sdata.get(159, 0).original_level > 0;
    case 7: return trait(id) == 0 || cdata.player().level >= 5;
    case 10: return sdata.get(173, 0).original_level > 0;
    case 12: return sdata.get(172, 0).original_level > 0;
    case 16: return sdata.get(156, 0).original_level > 0;
    case 19: return sdata.get(166, 0).original_level > 0;
    case 43: return sdata.get(168, 0).original_level > 0;
    default: return true;
    }
}


} // namespace


int trait_get_info(int traitmode, int tid)
{
    const auto data = the_trait_db[tid];
    if (!data)
    {
        return 0;
    }

    if (traitmode == 0)
    {
        traitref(0) = int(data->type);
        traitref(1) = data->min;
        traitref(2) = data->max;

        trait_format(tid, data->min, data->max);

        return is_acquirable(tid) ? 1 : -1;
    }

    if (tid == 24)
    {
        return 1;
    }
    if (tid == 3)
    {
        spact(1) = 1;
        return 1;
    }
    if (tid == 40)
    {
        spact(56) = 1;
        return 1;
    }
    if (tid == 13)
    {
        spact(27) = 1;
        return 1;
    }
    if (tid == 14)
    {
        spact(2) = 1;
        return 1;
    }
    if (tid == 22)
    {
        spact(18) = 1;
        return 1;
    }
    if (tid == 23)
    {
        spact(15) = 1;
        return 1;
    }
    if (tid == 21)
    {
        sdata(17, 0) =
            clamp(sdata(17, 0) + trait(tid) * 4, int{sdata(17, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 5)
    {
        sdata(10, 0) =
            clamp(sdata(10, 0) + trait(tid) * 3, int{sdata(10, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 38)
    {
        return 1;
    }
    if (tid == 39)
    {
        return 1;
    }
    if (tid == 42)
    {
        return 1;
    }
    if (tid == 9)
    {
        sdata(11, 0) =
            clamp(sdata(11, 0) + trait(tid) * 3, int{sdata(11, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 20)
    {
        sdata(106, 0) =
            clamp(sdata(106, 0) + trait(tid) * 3, int{sdata(106, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 12)
    {
        sdata(172, 0) =
            clamp(sdata(172, 0) + trait(tid) * 4, int{sdata(172, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 43)
    {
        cdata.player().has_power_bash() = true;
        return 1;
    }
    if (tid == 44)
    {
        return 1;
    }
    if (tid == 19)
    {
        sdata(166, 0) =
            clamp(sdata(166, 0) + trait(tid) * 4, int{sdata(166, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 15)
    {
        sdata(53, 0) = clamp(
            sdata(53, 0) + trait(tid) * 50 / 2, int{sdata(53, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 18)
    {
        sdata(55, 0) = clamp(
            sdata(55, 0) + trait(tid) * 50 / 2, int{sdata(55, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 16)
    {
        sdata(156, 0) =
            clamp(sdata(156, 0) + trait(tid) * 4, int{sdata(156, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 17)
    {
        sdata(181, 0) =
            clamp(sdata(181, 0) + trait(tid) * 4, int{sdata(181, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 1)
    {
        sdata(19, 0) =
            clamp(sdata(19, 0) + trait(tid) * 5, int{sdata(19, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 2)
    {
        sdata(2, 0) =
            clamp(sdata(2, 0) + trait(tid) * 5, int{sdata(2, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 11)
    {
        sdata(3, 0) =
            clamp(sdata(3, 0) + trait(tid) * 5, int{sdata(3, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 6)
    {
        sdata(159, 0) =
            clamp(sdata(159, 0) + trait(tid) * 3, int{sdata(159, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 4)
    {
        sdata(18, 0) =
            clamp(sdata(18, 0) + trait(tid) * 5, int{sdata(18, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 7)
    {
        cdata.player().pv = clamp(
            cdata.player().pv + trait(tid) * 5,
            int{cdata.player().pv > 0},
            9999);
        return 1;
    }
    if (tid == 8)
    {
        cdata.player().dv = clamp(
            cdata.player().dv + trait(tid) * 4,
            int{cdata.player().dv > 0},
            9999);
        return 1;
    }
    if (tid == 10)
    {
        sdata(173, 0) =
            clamp(sdata(173, 0) + trait(tid) * 2, int{sdata(173, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 41)
    {
        return 1;
    }
    if (tid == 25)
    {
        cdata.player().pv += trait(tid) * 3;
        return 1;
    }
    if (tid == 26)
    {
        sdata(12, 0) =
            clamp(sdata(12, 0) + trait(tid) * 3, int{sdata(12, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 27)
    {
        sdata(154, 0) =
            clamp(sdata(154, 0) + trait(tid) * 4, int{sdata(154, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 28)
    {
        sdata(18, 0) =
            clamp(sdata(18, 0) + trait(tid) * 5, int{sdata(18, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 29)
    {
        sdata(10, 0) =
            clamp(sdata(10, 0) + trait(tid) * 3, int{sdata(10, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 30)
    {
        sdata(17, 0) =
            clamp(sdata(17, 0) + trait(tid) * 5, int{sdata(17, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 31)
    {
        if (sdata.get(165, 0).original_level != 0)
        {
            sdata(165, 0) = clamp(
                sdata(165, 0) + trait(tid) * 4, int{sdata(165, 0) > 0}, 9999);
        }
        return 1;
    }
    if (tid == 32)
    {
        sdata(60, 0) =
            clamp(sdata(60, 0) + trait(tid) * 50, int{sdata(60, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 33)
    {
        sdata(57, 0) =
            clamp(sdata(57, 0) + trait(tid) * 50, int{sdata(57, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 34)
    {
        sdata(50, 0) =
            clamp(sdata(50, 0) + trait(tid) * 50, int{sdata(50, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 35)
    {
        sdata(51, 0) =
            clamp(sdata(51, 0) + trait(tid) * 50, int{sdata(51, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 36)
    {
        sdata(52, 0) =
            clamp(sdata(52, 0) + trait(tid) * 50, int{sdata(52, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 37)
    {
        sdata(13, 0) =
            clamp(sdata(13, 0) + trait(tid) * 5, int{sdata(13, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 150)
    {
        sdata(50, 0) =
            clamp(sdata(50, 0) + trait(tid) * 50, int{sdata(50, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 151)
    {
        sdata(51, 0) =
            clamp(sdata(51, 0) + trait(tid) * 50, int{sdata(51, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 152)
    {
        sdata(55, 0) =
            clamp(sdata(55, 0) + trait(tid) * 50, int{sdata(55, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 155)
    {
        sdata(53, 0) =
            clamp(sdata(53, 0) + trait(tid) * 50, int{sdata(53, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 156)
    {
        return 1;
    }
    if (tid == 160)
    {
        sdata(60, 0) = clamp(sdata(60, 0) + 150, int{sdata(60, 0) > 0}, 9999);
        sdata(52, 0) = clamp(sdata(52, 0) + 100, int{sdata(52, 0) > 0}, 9999);
        sdata(53, 0) = clamp(sdata(53, 0) + 200, int{sdata(53, 0) > 0}, 9999);
        sdata(57, 0) = clamp(sdata(57, 0) + 50, int{sdata(57, 0) > 0}, 9999);
        sdata(59, 0) = clamp(sdata(59, 0) + 100, int{sdata(59, 0) > 0}, 9999);
        sdata(54, 0) = clamp(sdata(54, 0) + 200, int{sdata(54, 0) > 0}, 9999);
        sdata(58, 0) = clamp(sdata(58, 0) + 100, int{sdata(58, 0) > 0}, 9999);
        sdata(51, 0) = clamp(sdata(51, 0) + 100, int{sdata(51, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 161)
    {
        if (cdata.player().dv > 0)
        {
            cdata.player().dv = cdata.player().dv * 125 / 100 + 50;
        }
        return 1;
    }
    if (tid == 162)
    {
        return 1;
    }
    if (tid == 169)
    {
        return 1;
    }
    if (tid == 163)
    {
        return 1;
    }
    if (tid == 164)
    {
        return 1;
    }
    if (tid == 165)
    {
        return 1;
    }
    if (tid == 166)
    {
        return 1;
    }
    if (tid == 167)
    {
        return 1;
    }
    if (tid == 157)
    {
        return 1;
    }
    if (tid == 158)
    {
        return 1;
    }
    if (tid == 159)
    {
        return 1;
    }
    if (tid == 154)
    {
        return 1;
    }
    if (tid == 153)
    {
        sdata(60, 0) =
            clamp(sdata(60, 0) + trait(tid) * 50, int{sdata(60, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 0)
    {
        return 1;
    }
    if (tid == 168)
    {
        return 1;
    }
    if (tid == 201)
    {
        return 1;
    }
    if (tid == 202)
    {
        sdata(17, 0) = clamp(
            sdata(17, 0) + trait(tid) * (4 + cdata.player().level / 5),
            int{sdata(17, 0) > 0},
            9999);
        return 1;
    }
    if (tid == 203)
    {
        sdata(18, 0) = clamp(
            sdata(18, 0) + (20 + cdata.player().level / 2),
            int{sdata(18, 0) > 0},
            9999);
        return 1;
    }
    if (tid == 204)
    {
        sdata(17, 0) = clamp(
            sdata(17, 0) + (5 + cdata.player().level / 3) * -1,
            int{sdata(17, 0) > 0},
            9999);
        sdata(13, 0) = clamp(
            sdata(13, 0) + (5 + cdata.player().level / 3),
            int{sdata(13, 0) > 0},
            9999);
        return 1;
    }
    if (tid == 205)
    {
        cdata.player().is_floating() = true;
        sdata(18, 0) = clamp(
            sdata(18, 0) + (12 + cdata.player().level / 4),
            int{sdata(18, 0) > 0},
            9999);
        return 1;
    }
    if (tid == 206)
    {
        sdata(17, 0) = clamp(
            sdata(17, 0) + (5 + cdata.player().level / 5) * -1,
            int{sdata(17, 0) > 0},
            9999);
        cdata.player().pv += 12 + cdata.player().level;
        return 1;
    }
    if (tid == 207)
    {
        cdata.player().dv += (15 + cdata.player().level * 3 / 2) * -1;
        return 1;
    }
    if (tid == 208)
    {
        sdata(11, 0) = clamp(
            sdata(11, 0) + (5 + cdata.player().level / 3) * -1,
            int{sdata(11, 0) > 0},
            9999);
        sdata(12, 0) = clamp(
            sdata(12, 0) + (4 + cdata.player().level / 4) * -1,
            int{sdata(12, 0) > 0},
            9999);
        sdata(14, 0) = clamp(
            sdata(14, 0) + (6 + cdata.player().level / 2),
            int{sdata(14, 0) > 0},
            9999);
        sdata(15, 0) = clamp(
            sdata(15, 0) + (2 + cdata.player().level / 6),
            int{sdata(15, 0) > 0},
            9999);
        return 1;
    }
    if (tid == 209)
    {
        return 1;
    }
    if (tid == 210)
    {
        return 1;
    }
    if (tid == 211)
    {
        sdata(10, 0) = clamp(
            sdata(10, 0) + (4 + cdata.player().level / 2) * -1,
            int{sdata(10, 0) > 0},
            9999);
        sdata(2, 0) = clamp(sdata(2, 0) + -15, int{sdata(2, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 212)
    {
        sdata(16, 0) = clamp(
            sdata(16, 0) + (4 + cdata.player().level / 2) * -1,
            int{sdata(16, 0) > 0},
            9999);
        sdata(3, 0) = clamp(sdata(3, 0) + -15, int{sdata(3, 0) > 0}, 9999);
        return 1;
    }
    if (tid == 213)
    {
        sdata(18, 0) = clamp(
            sdata(18, 0) + (20 + cdata.player().level / 2) * -1,
            int{sdata(18, 0) > 0},
            9999);
        cdata.player().pv += 15 + cdata.player().level / 2;
        return 1;
    }
    if (tid == 214)
    {
        return 1;
    }
    if (tid == 215)
    {
        return 1;
    }
    if (tid == 216)
    {
        sdata(55, 0) = clamp(sdata(55, 0) + 100, int{sdata(55, 0) > 0}, 9999);
        return 1;
    }
    return 0;
}



void trait_load_desc()
{
    int featrq = 0;

    listmax = 0;
    if (tc == 0 && game_data.acquirable_feat_count > 0)
    {
        list(0, listmax) = -1;
        list(1, listmax) = 0;
        ++listmax;
    }
    f = 0;
    for (int cnt = 0; cnt < 217; ++cnt)
    {
        if (tc != 0)
        {
            break;
        }
        int stat = trait_get_info(0, cnt);
        if (stat == 0)
        {
            continue;
        }
        if (stat == 1)
        {
            if (traitref == 0)
            {
                if (game_data.acquirable_feat_count > 0)
                {
                    list(0, listmax) = cnt;
                    list(1, listmax) = cnt + 1;
                    ++listmax;
                }
            }
        }
        if (trait(cnt) != 0)
        {
            list(0, listmax) = cnt;
            list(1, listmax) = 10000 + cnt + 1;
            ++listmax;
            ++f;
        }
    }
    if (f != 0)
    {
        list(0, listmax) = -2;
        list(1, listmax) = 10000;
        ++listmax;
    }
    sort_list_by_column1();
    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
    {
        i = list(0, cnt);
        if (i < 0)
        {
            if (i == -1)
            {
                s = i18n::s.get("core.locale.trait.window.available_feats");
            }
            if (i == -2)
            {
                s = i18n::s.get("core.locale.trait.window.feats_and_traits");
            }
            listn(0, cnt) = s;
            continue;
        }
        int tid = i;
        int stat = trait_get_info(0, tid);
        featrq = stat;
        s = "";
        if (list(1, cnt) < 10000)
        {
            if (trait(tid) < traitref(2))
            {
                s = traitrefn2(trait(tid));
            }
            else
            {
                s = traitrefn2(traitref(2) - 1) + u8"(MAX)"s;
            }
            if (featrq == -1)
            {
                s += u8"("s
                    + i18n::s.get("core.locale.trait.window.requirement")
                    + u8")"s;
            }
            pos(wx + 30, wy + 61 + cnt * 19);
            x = 84;
        }
        else
        {
            pos(wx + 45, wy + 61 + cnt * 19);
            x = 70;
            if (traitref == 0)
            {
                s = u8"["s
                    + i18n::s.get("core.locale.trait.window.category.feat")
                    + u8"]"s;
            }
            if (traitref == 1)
            {
                s = u8"["s
                    + i18n::s.get("core.locale.trait.window.category.mutation")
                    + u8"]"s;
            }
            if (traitref == 2)
            {
                s = u8"["s
                    + i18n::s.get("core.locale.trait.window.category.race")
                    + u8"]"s;
            }
            if (traitref == 3)
            {
                s = u8"["s
                    + i18n::s.get(
                          "core.locale.trait.window.category.ether_disease")
                    + u8"]"s;
            }
            s += traitrefn(2 + std::abs(trait(tid)));
        }
        listn(0, cnt) = s;
    }
    if (cdata[tc].is_incognito() == 1)
    {
        list(0, listmax) = 1;
        list(1, listmax) = 99999;
        listn(0, listmax) = u8"["s
            + i18n::s.get("core.locale.trait.window.category.etc") + u8"]"s
            + i18n::s.get("core.locale.trait.incognito");
        ++listmax;
    }
    if (cdata[tc].is_pregnant() == 1)
    {
        list(0, listmax) = 1;
        list(1, listmax) = 99999;
        listn(0, listmax) = u8"["s
            + i18n::s.get("core.locale.trait.window.category.etc") + u8"]"s
            + i18n::s.get("core.locale.trait.pregnant");
        ++listmax;
    }
    if (cdata[tc].has_anorexia() == 1)
    {
        list(0, listmax) = 1;
        list(1, listmax) = 99999;
        listn(0, listmax) = u8"["s
            + i18n::s.get("core.locale.trait.window.category.etc") + u8"]"s
            + i18n::s.get("core.locale.trait.anorexia");
        ++listmax;
    }
    if (cdata[tc].speed_correction_value != 0)
    {
        list(0, listmax) = 1;
        list(1, listmax) = 99999;
        listn(0, listmax) = u8"["s
            + i18n::s.get("core.locale.trait.window.category.etc") + u8"]"s
            + i18n::s.get(
                  "core.locale.trait.body_is_complicated",
                  cdata[tc].speed_correction_value);
        ++listmax;
    }
    if (tc == 0 && gdata_ether_disease_speed != 0)
    {
        if (gdata_ether_disease_speed > 0)
        {
            list(0, listmax) = 1;
            list(1, listmax) = 99999;
            listn(0, listmax) = u8"["s
                + i18n::s.get("core.locale.trait.window.category.etc") + u8"]"s
                + i18n::s.get("core.locale.trait.ether_disease_grows.fast");
            ++listmax;
        }
        else
        {
            list(0, listmax) = 1;
            list(1, listmax) = 99999;
            listn(0, listmax) = u8"["s
                + i18n::s.get("core.locale.trait.window.category.etc") + u8"]"s
                + i18n::s.get("core.locale.trait.ether_disease_grows.slow");
            ++listmax;
        }
    }
}


} // namespace elona
