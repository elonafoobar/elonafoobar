#include "trait.hpp"

#include "../util/range.hpp"
#include "ability.hpp"
#include "character.hpp"
#include "elona.hpp"
#include "game.hpp"
#include "i18n.hpp"
#include "optional.hpp"
#include "ui.hpp"
#include "variables.hpp"



namespace
{

void trait_format_other_parameterized(
    const I18NKey& i18n_prefix,
    int tid,
    int min)
{
    optional<std::string> text = none;
    I18NKey full_prefix = i18n_prefix + ".negative.levels";
    const auto level =
        cdata.player().traits().level(*the_trait_db.get_id_from_integer(tid));

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
    if (cdata.player().traits().level(*the_trait_db.get_id_from_integer(tid)) >=
        0)
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
    else if (
        cdata.player().traits().level(*the_trait_db.get_id_from_integer(tid)) <
        0)
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
    return cdata.player().traits().level(
               *the_trait_db.get_id_from_integer(tid)) >= 0 &&
        i18n::s.get_enum_property_optional(i18n_prefix + ".levels", "name", 0);
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
    I18NKey i18n_prefix = "core.trait._" + std::to_string(tid);
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
    case 4:
        return cdata.player().traits().level(
                   *the_trait_db.get_id_from_integer(id)) == 0 ||
            cdata.player().level >= 5;
    case 6: return cdata.player().get_skill(159).base_level > 0;
    case 7:
        return cdata.player().traits().level(
                   *the_trait_db.get_id_from_integer(id)) == 0 ||
            cdata.player().level >= 5;
    case 10: return cdata.player().get_skill(173).base_level > 0;
    case 12: return cdata.player().get_skill(172).base_level > 0;
    case 16: return cdata.player().get_skill(156).base_level > 0;
    case 19: return cdata.player().get_skill(166).base_level > 0;
    case 43: return cdata.player().get_skill(168).base_level > 0;
    default: return true;
    }
}

} // namespace



namespace elona
{



int trait_get_info(int traitmode, int tid)
{
    const auto data = the_trait_db[tid];
    if (!data)
    {
        return 0;
    }

    if (traitmode == 0)
    {
        traitref(0) = data->trait_type;
        traitref(1) = data->min;
        traitref(2) = data->max;

        trait_format(tid, data->min, data->max);

        return is_acquirable(tid) ? 1 : -1;
    }

    const auto trait_id = data->id;

    if (tid == 24)
    {
        return 1;
    }
    if (tid == 3)
    {
        cdata.player().spacts().gain("core.drain_blood");
        return 1;
    }
    if (tid == 40)
    {
        cdata.player().spacts().gain("core.cheer");
        return 1;
    }
    if (tid == 13)
    {
        cdata.player().spacts().gain("core.dimensional_move");
        return 1;
    }
    if (tid == 14)
    {
        cdata.player().spacts().gain("core.fire_breath");
        return 1;
    }
    if (tid == 22)
    {
        cdata.player().spacts().gain("core.touch_of_sleep");
        return 1;
    }
    if (tid == 23)
    {
        cdata.player().spacts().gain("core.touch_of_poison");
        return 1;
    }
    if (tid == 21)
    {
        cdata.player().get_skill(17).level = clamp(
            cdata.player().get_skill(17).level +
                cdata.player().traits().level(trait_id) * 4,
            int{cdata.player().get_skill(17).level > 0},
            9999);
        return 1;
    }
    if (tid == 5)
    {
        cdata.player().get_skill(10).level = clamp(
            cdata.player().get_skill(10).level +
                cdata.player().traits().level(trait_id) * 3,
            int{cdata.player().get_skill(10).level > 0},
            9999);
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
        cdata.player().get_skill(11).level = clamp(
            cdata.player().get_skill(11).level +
                cdata.player().traits().level(trait_id) * 3,
            int{cdata.player().get_skill(11).level > 0},
            9999);
        return 1;
    }
    if (tid == 20)
    {
        cdata.player().get_skill(106).level = clamp(
            cdata.player().get_skill(106).level +
                cdata.player().traits().level(trait_id) * 3,
            int{cdata.player().get_skill(106).level > 0},
            9999);
        return 1;
    }
    if (tid == 12)
    {
        cdata.player().get_skill(172).level = clamp(
            cdata.player().get_skill(172).level +
                cdata.player().traits().level(trait_id) * 4,
            int{cdata.player().get_skill(172).level > 0},
            9999);
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
        cdata.player().get_skill(166).level = clamp(
            cdata.player().get_skill(166).level +
                cdata.player().traits().level(trait_id) * 4,
            int{cdata.player().get_skill(166).level > 0},
            9999);
        return 1;
    }
    if (tid == 15)
    {
        cdata.player().get_skill(53).level = clamp(
            cdata.player().get_skill(53).level +
                cdata.player().traits().level(trait_id) * 50 / 2,
            int{cdata.player().get_skill(53).level > 0},
            9999);
        return 1;
    }
    if (tid == 18)
    {
        cdata.player().get_skill(55).level = clamp(
            cdata.player().get_skill(55).level +
                cdata.player().traits().level(trait_id) * 50 / 2,
            int{cdata.player().get_skill(55).level > 0},
            9999);
        return 1;
    }
    if (tid == 16)
    {
        cdata.player().get_skill(156).level = clamp(
            cdata.player().get_skill(156).level +
                cdata.player().traits().level(trait_id) * 4,
            int{cdata.player().get_skill(156).level > 0},
            9999);
        return 1;
    }
    if (tid == 17)
    {
        cdata.player().get_skill(181).level = clamp(
            cdata.player().get_skill(181).level +
                cdata.player().traits().level(trait_id) * 4,
            int{cdata.player().get_skill(181).level > 0},
            9999);
        return 1;
    }
    if (tid == 1)
    {
        cdata.player().get_skill(19).level = clamp(
            cdata.player().get_skill(19).level +
                cdata.player().traits().level(trait_id) * 5,
            int{cdata.player().get_skill(19).level > 0},
            9999);
        return 1;
    }
    if (tid == 2)
    {
        cdata.player().get_skill(2).level = clamp(
            cdata.player().get_skill(2).level +
                cdata.player().traits().level(trait_id) * 5,
            int{cdata.player().get_skill(2).level > 0},
            9999);
        return 1;
    }
    if (tid == 11)
    {
        cdata.player().get_skill(3).level = clamp(
            cdata.player().get_skill(3).level +
                cdata.player().traits().level(trait_id) * 5,
            int{cdata.player().get_skill(3).level > 0},
            9999);
        return 1;
    }
    if (tid == 6)
    {
        cdata.player().get_skill(159).level = clamp(
            cdata.player().get_skill(159).level +
                cdata.player().traits().level(trait_id) * 3,
            int{cdata.player().get_skill(159).level > 0},
            9999);
        return 1;
    }
    if (tid == 4)
    {
        cdata.player().get_skill(18).level = clamp(
            cdata.player().get_skill(18).level +
                cdata.player().traits().level(trait_id) * 5,
            int{cdata.player().get_skill(18).level > 0},
            9999);
        return 1;
    }
    if (tid == 7)
    {
        cdata.player().pv = clamp(
            cdata.player().pv + cdata.player().traits().level(trait_id) * 5,
            int{cdata.player().pv > 0},
            9999);
        return 1;
    }
    if (tid == 8)
    {
        cdata.player().dv = clamp(
            cdata.player().dv + cdata.player().traits().level(trait_id) * 4,
            int{cdata.player().dv > 0},
            9999);
        return 1;
    }
    if (tid == 10)
    {
        cdata.player().get_skill(173).level = clamp(
            cdata.player().get_skill(173).level +
                cdata.player().traits().level(trait_id) * 2,
            int{cdata.player().get_skill(173).level > 0},
            9999);
        return 1;
    }
    if (tid == 41)
    {
        return 1;
    }
    if (tid == 25)
    {
        cdata.player().pv += cdata.player().traits().level(trait_id) * 3;
        return 1;
    }
    if (tid == 26)
    {
        cdata.player().get_skill(12).level = clamp(
            cdata.player().get_skill(12).level +
                cdata.player().traits().level(trait_id) * 3,
            int{cdata.player().get_skill(12).level > 0},
            9999);
        return 1;
    }
    if (tid == 27)
    {
        cdata.player().get_skill(154).level = clamp(
            cdata.player().get_skill(154).level +
                cdata.player().traits().level(trait_id) * 4,
            int{cdata.player().get_skill(154).level > 0},
            9999);
        return 1;
    }
    if (tid == 28)
    {
        cdata.player().get_skill(18).level = clamp(
            cdata.player().get_skill(18).level +
                cdata.player().traits().level(trait_id) * 5,
            int{cdata.player().get_skill(18).level > 0},
            9999);
        return 1;
    }
    if (tid == 29)
    {
        cdata.player().get_skill(10).level = clamp(
            cdata.player().get_skill(10).level +
                cdata.player().traits().level(trait_id) * 3,
            int{cdata.player().get_skill(10).level > 0},
            9999);
        return 1;
    }
    if (tid == 30)
    {
        cdata.player().get_skill(17).level = clamp(
            cdata.player().get_skill(17).level +
                cdata.player().traits().level(trait_id) * 5,
            int{cdata.player().get_skill(17).level > 0},
            9999);
        return 1;
    }
    if (tid == 31)
    {
        if (cdata.player().get_skill(165).base_level != 0)
        {
            cdata.player().get_skill(165).level = clamp(
                cdata.player().get_skill(165).level +
                    cdata.player().traits().level(trait_id) * 4,
                int{cdata.player().get_skill(165).level > 0},
                9999);
        }
        return 1;
    }
    if (tid == 32)
    {
        cdata.player().get_skill(60).level = clamp(
            cdata.player().get_skill(60).level +
                cdata.player().traits().level(trait_id) * 50,
            int{cdata.player().get_skill(60).level > 0},
            9999);
        return 1;
    }
    if (tid == 33)
    {
        cdata.player().get_skill(57).level = clamp(
            cdata.player().get_skill(57).level +
                cdata.player().traits().level(trait_id) * 50,
            int{cdata.player().get_skill(57).level > 0},
            9999);
        return 1;
    }
    if (tid == 34)
    {
        cdata.player().get_skill(50).level = clamp(
            cdata.player().get_skill(50).level +
                cdata.player().traits().level(trait_id) * 50,
            int{cdata.player().get_skill(50).level > 0},
            9999);
        return 1;
    }
    if (tid == 35)
    {
        cdata.player().get_skill(51).level = clamp(
            cdata.player().get_skill(51).level +
                cdata.player().traits().level(trait_id) * 50,
            int{cdata.player().get_skill(51).level > 0},
            9999);
        return 1;
    }
    if (tid == 36)
    {
        cdata.player().get_skill(52).level = clamp(
            cdata.player().get_skill(52).level +
                cdata.player().traits().level(trait_id) * 50,
            int{cdata.player().get_skill(52).level > 0},
            9999);
        return 1;
    }
    if (tid == 37)
    {
        cdata.player().get_skill(13).level = clamp(
            cdata.player().get_skill(13).level +
                cdata.player().traits().level(trait_id) * 5,
            int{cdata.player().get_skill(13).level > 0},
            9999);
        return 1;
    }
    if (tid == 150)
    {
        cdata.player().get_skill(50).level = clamp(
            cdata.player().get_skill(50).level +
                cdata.player().traits().level(trait_id) * 50,
            int{cdata.player().get_skill(50).level > 0},
            9999);
        return 1;
    }
    if (tid == 151)
    {
        cdata.player().get_skill(51).level = clamp(
            cdata.player().get_skill(51).level +
                cdata.player().traits().level(trait_id) * 50,
            int{cdata.player().get_skill(51).level > 0},
            9999);
        return 1;
    }
    if (tid == 152)
    {
        cdata.player().get_skill(55).level = clamp(
            cdata.player().get_skill(55).level +
                cdata.player().traits().level(trait_id) * 50,
            int{cdata.player().get_skill(55).level > 0},
            9999);
        return 1;
    }
    if (tid == 155)
    {
        cdata.player().get_skill(53).level = clamp(
            cdata.player().get_skill(53).level +
                cdata.player().traits().level(trait_id) * 50,
            int{cdata.player().get_skill(53).level > 0},
            9999);
        return 1;
    }
    if (tid == 156)
    {
        return 1;
    }
    if (tid == 160)
    {
        cdata.player().get_skill(60).level = clamp(
            cdata.player().get_skill(60).level + 150,
            int{cdata.player().get_skill(60).level > 0},
            9999);
        cdata.player().get_skill(52).level = clamp(
            cdata.player().get_skill(52).level + 100,
            int{cdata.player().get_skill(52).level > 0},
            9999);
        cdata.player().get_skill(53).level = clamp(
            cdata.player().get_skill(53).level + 200,
            int{cdata.player().get_skill(53).level > 0},
            9999);
        cdata.player().get_skill(57).level = clamp(
            cdata.player().get_skill(57).level + 50,
            int{cdata.player().get_skill(57).level > 0},
            9999);
        cdata.player().get_skill(59).level = clamp(
            cdata.player().get_skill(59).level + 100,
            int{cdata.player().get_skill(59).level > 0},
            9999);
        cdata.player().get_skill(54).level = clamp(
            cdata.player().get_skill(54).level + 200,
            int{cdata.player().get_skill(54).level > 0},
            9999);
        cdata.player().get_skill(58).level = clamp(
            cdata.player().get_skill(58).level + 100,
            int{cdata.player().get_skill(58).level > 0},
            9999);
        cdata.player().get_skill(51).level = clamp(
            cdata.player().get_skill(51).level + 100,
            int{cdata.player().get_skill(51).level > 0},
            9999);
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
        cdata.player().get_skill(60).level = clamp(
            cdata.player().get_skill(60).level +
                cdata.player().traits().level(trait_id) * 50,
            int{cdata.player().get_skill(60).level > 0},
            9999);
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
        cdata.player().get_skill(17).level = clamp(
            cdata.player().get_skill(17).level +
                cdata.player().traits().level(trait_id) *
                    (4 + cdata.player().level / 5),
            int{cdata.player().get_skill(17).level > 0},
            9999);
        return 1;
    }
    if (tid == 203)
    {
        cdata.player().get_skill(18).level = clamp(
            cdata.player().get_skill(18).level +
                (20 + cdata.player().level / 2),
            int{cdata.player().get_skill(18).level > 0},
            9999);
        return 1;
    }
    if (tid == 204)
    {
        cdata.player().get_skill(17).level = clamp(
            cdata.player().get_skill(17).level +
                (5 + cdata.player().level / 3) * -1,
            int{cdata.player().get_skill(17).level > 0},
            9999);
        cdata.player().get_skill(13).level = clamp(
            cdata.player().get_skill(13).level + (5 + cdata.player().level / 3),
            int{cdata.player().get_skill(13).level > 0},
            9999);
        return 1;
    }
    if (tid == 205)
    {
        cdata.player().is_floating() = true;
        cdata.player().get_skill(18).level = clamp(
            cdata.player().get_skill(18).level +
                (12 + cdata.player().level / 4),
            int{cdata.player().get_skill(18).level > 0},
            9999);
        return 1;
    }
    if (tid == 206)
    {
        cdata.player().get_skill(17).level = clamp(
            cdata.player().get_skill(17).level +
                (5 + cdata.player().level / 5) * -1,
            int{cdata.player().get_skill(17).level > 0},
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
        cdata.player().get_skill(11).level = clamp(
            cdata.player().get_skill(11).level +
                (5 + cdata.player().level / 3) * -1,
            int{cdata.player().get_skill(11).level > 0},
            9999);
        cdata.player().get_skill(12).level = clamp(
            cdata.player().get_skill(12).level +
                (4 + cdata.player().level / 4) * -1,
            int{cdata.player().get_skill(12).level > 0},
            9999);
        cdata.player().get_skill(14).level = clamp(
            cdata.player().get_skill(14).level + (6 + cdata.player().level / 2),
            int{cdata.player().get_skill(14).level > 0},
            9999);
        cdata.player().get_skill(15).level = clamp(
            cdata.player().get_skill(15).level + (2 + cdata.player().level / 6),
            int{cdata.player().get_skill(15).level > 0},
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
        cdata.player().get_skill(10).level = clamp(
            cdata.player().get_skill(10).level +
                (4 + cdata.player().level / 2) * -1,
            int{cdata.player().get_skill(10).level > 0},
            9999);
        cdata.player().get_skill(2).level = clamp(
            cdata.player().get_skill(2).level + -15,
            int{cdata.player().get_skill(2).level > 0},
            9999);
        return 1;
    }
    if (tid == 212)
    {
        cdata.player().get_skill(16).level = clamp(
            cdata.player().get_skill(16).level +
                (4 + cdata.player().level / 2) * -1,
            int{cdata.player().get_skill(16).level > 0},
            9999);
        cdata.player().get_skill(3).level = clamp(
            cdata.player().get_skill(3).level + -15,
            int{cdata.player().get_skill(3).level > 0},
            9999);
        return 1;
    }
    if (tid == 213)
    {
        cdata.player().get_skill(18).level = clamp(
            cdata.player().get_skill(18).level +
                (20 + cdata.player().level / 2) * -1,
            int{cdata.player().get_skill(18).level > 0},
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
        cdata.player().get_skill(55).level = clamp(
            cdata.player().get_skill(55).level + 100,
            int{cdata.player().get_skill(55).level > 0},
            9999);
        return 1;
    }
    return 0;
}



void trait_load_desc(Character& chara)
{
    int featrq = 0;

    listmax = 0;
    if (chara.is_player() && game()->acquirable_feat_count > 0)
    {
        list(0, listmax) = -1;
        list(1, listmax) = 0;
        ++listmax;
    }
    f = 0;
    for (int cnt = 0; cnt < 217; ++cnt)
    {
        if (!chara.is_player())
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
                if (game()->acquirable_feat_count > 0)
                {
                    list(0, listmax) = cnt;
                    list(1, listmax) = cnt + 1;
                    ++listmax;
                }
            }
        }
        if (cdata.player().traits().level(
                *the_trait_db.get_id_from_integer(cnt)) != 0)
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
                s = i18n::s.get("core.trait.window.available_feats");
            }
            if (i == -2)
            {
                s = i18n::s.get("core.trait.window.feats_and_traits");
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
            if (cdata.player().traits().level(
                    *the_trait_db.get_id_from_integer(tid)) < traitref(2))
            {
                s = traitrefn2(cdata.player().traits().level(
                    *the_trait_db.get_id_from_integer(tid)));
            }
            else
            {
                s = traitrefn2(traitref(2) - 1) + u8"(MAX)"s;
            }
            if (featrq == -1)
            {
                s += u8"("s + i18n::s.get("core.trait.window.requirement") +
                    u8")"s;
            }
            x = 84;
        }
        else
        {
            x = 70;
            if (traitref == 0)
            {
                s = u8"["s + i18n::s.get("core.trait.window.category.feat") +
                    u8"]"s;
            }
            if (traitref == 1)
            {
                s = u8"["s +
                    i18n::s.get("core.trait.window.category.mutation") + u8"]"s;
            }
            if (traitref == 2)
            {
                s = u8"["s + i18n::s.get("core.trait.window.category.race") +
                    u8"]"s;
            }
            if (traitref == 3)
            {
                s = u8"["s +
                    i18n::s.get("core.trait.window.category.ether_disease") +
                    u8"]"s;
            }
            s += traitrefn(
                2 +
                std::abs(cdata.player().traits().level(
                    *the_trait_db.get_id_from_integer(tid))));
        }
        listn(0, cnt) = s;
    }
    if (chara.is_incognito() == 1)
    {
        list(0, listmax) = 1;
        list(1, listmax) = 99999;
        listn(0, listmax) = u8"["s +
            i18n::s.get("core.trait.window.category.etc") + u8"]"s +
            i18n::s.get("core.trait.incognito");
        ++listmax;
    }
    if (chara.is_pregnant() == 1)
    {
        list(0, listmax) = 1;
        list(1, listmax) = 99999;
        listn(0, listmax) = u8"["s +
            i18n::s.get("core.trait.window.category.etc") + u8"]"s +
            i18n::s.get("core.trait.pregnant");
        ++listmax;
    }
    if (chara.has_anorexia() == 1)
    {
        list(0, listmax) = 1;
        list(1, listmax) = 99999;
        listn(0, listmax) = u8"["s +
            i18n::s.get("core.trait.window.category.etc") + u8"]"s +
            i18n::s.get("core.trait.anorexia");
        ++listmax;
    }
    if (chara.speed_correction_value != 0)
    {
        list(0, listmax) = 1;
        list(1, listmax) = 99999;
        listn(0, listmax) = u8"["s +
            i18n::s.get("core.trait.window.category.etc") + u8"]"s +
            i18n::s.get(
                "core.trait.body_is_complicated", chara.speed_correction_value);
        ++listmax;
    }
    if (chara.is_player() && game()->ether_disease_speed != 0)
    {
        if (game()->ether_disease_speed > 0)
        {
            list(0, listmax) = 1;
            list(1, listmax) = 99999;
            listn(0, listmax) = u8"["s +
                i18n::s.get("core.trait.window.category.etc") + u8"]"s +
                i18n::s.get("core.trait.ether_disease_grows.fast");
            ++listmax;
        }
        else
        {
            list(0, listmax) = 1;
            list(1, listmax) = 99999;
            listn(0, listmax) = u8"["s +
                i18n::s.get("core.trait.window.category.etc") + u8"]"s +
                i18n::s.get("core.trait.ether_disease_grows.slow");
            ++listmax;
        }
    }
}



void clear_trait_data()
{
    DIM2(traitref, 10);
    SDIM3(traitrefn, 80, 9);
    SDIM3(traitrefn2, 20, 6);
}

} // namespace elona
