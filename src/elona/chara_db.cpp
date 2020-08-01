#include "ability.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "class.hpp"
#include "data/types/type_ability.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "food.hpp"
#include "i18n.hpp"
#include "lua_env/interface.hpp"
#include "lua_env/lua_env.hpp"
#include "message.hpp"
#include "race.hpp"
#include "random.hpp"
#include "text.hpp"
#include "variables.hpp"



namespace elona
{

void chara_db_set_stats(Character& chara, CharaId chara_id)
{
    const auto data = the_character_db[charaid2int(chara_id)];
    if (!data)
    {
        return;
    }

    chara.id = chara_id;
    chara.level = initlv != 0 ? initlv : data->level;
    if (voidlv != 0)
    {
        chara.level = voidlv * (100 + data->level * 2) / 100;
    }
    chara.ai_calm = data->ai_calm;
    chara.ai_heal = data->ai_heal;
    chara.ai_move = data->ai_move;
    chara.ai_dist = data->ai_dist;
    chara.ai_act_sub_freq = data->ai_act_sub_freq;
    chara.normal_actions = data->normal_actions;
    chara.special_actions = data->special_actions;
    creaturepack = data->creaturepack;
    chara.can_talk = data->can_talk;
    chara.name = the_character_db.get_text(data->id, "name");
    if (data->has_random_name)
    {
        chara.name =
            i18n::s.get("core.chara.job.own_name", chara.name, random_name());
        chara.has_own_name() = true;
    }
    chara.original_relationship = chara.relationship =
        data->original_relationship;
    if (data->race_id != "")
    {
        race_init_chara(chara, data->race_id);
    }
    if (data->class_id != "")
    {
        class_init_chara(chara, data->class_id);
    }
    chara.element_of_unarmed_attack = data->element_of_unarmed_attack;

    for (const auto& pair : data->resistances)
    {
        if (const auto ability_data = the_ability_db[pair.first])
        {
            chara.get_skill(ability_data->legacy_id).level = pair.second;
        }
        else
        {
            // Skip the resistance if undefined.
            ELONA_WARN("lua.data")
                << "Undefined resistance ID: " << pair.first.get()
                << " (character " << data->id.get() << ")";
        }
    }

    if (data->sex != -1)
    {
        chara.sex = data->sex;
    }
    if (data->image != 0)
    {
        chara.image = data->image;
    }
    if (chara.sex == 0 && data->male_image != 0)
    {
        chara.image = data->male_image;
    }
    if (chara.sex == 1 && data->female_image != 0)
    {
        chara.image = data->female_image;
    }
    if (chara.sex == 0)
    {
        chara.portrait = data->portrait_male;
    }
    else
    {
        chara.portrait = data->portrait_female;
    }
    {
        int color = generate_color(data->color, charaid2int(chara.id));
        chara.image += color * 1000;
    }
    eqammo(0) = data->eqammo_0;
    eqammo(1) = data->eqammo_1;
    eqmultiweapon = data->eqmultiweapon;
    eqrange(0) = data->eqrange_0;
    eqrange(1) = data->eqrange_1;
    eqring1 = data->eqring1;
    eqtwohand = data->eqtwohand;
    eqweapon1 = data->eqweapon1;
    if (data->fixlv == 6)
    {
        fixlv = Quality::special;
    }
    cspecialeq = data->cspecialeq;
    chara.damage_reaction_info = data->damage_reaction_info;
}



int chara_db_get_item_type(CharaId chara_id)
{
    if (const auto data = the_character_db[charaid2int(chara_id)])
    {
        return data->item_type;
    }
    else
    {
        return 0;
    }
}



std::string chara_db_get_filter(CharaId chara_id)
{
    if (const auto data = the_character_db[charaid2int(chara_id)])
    {
        return data->filter;
    }
    else
    {
        return "";
    }
}



std::string chara_db_get_name(CharaId chara_id)
{
    if (const auto data = the_character_db[charaid2int(chara_id)])
    {
        return the_character_db.get_text(data->id, "name");
    }
    else
    {
        return "";
    }
}



void chara_db_invoke_eating_effect(Character& eater, CharaId chara_id)
{
    const auto data = the_character_db[charaid2int(chara_id)];
    if (data && data->corpse_eating_callback)
    {
        lua::call(*data->corpse_eating_callback, lua::handle(eater));
    }
}



void chara_db_get_special_equipments(CharaId chara_id)
{
    switch (charaid2int(chara_id))
    {
    case 2: eqweapon1 = 63; return;
    case 23: eqweapon1 = 64; return;
    case 28: eqweapon1 = 73; return;
    case 351:
        eqtwohand = 1;
        eqweapon1 = 232;
        return;
    case 33: eqweapon1 = 206; return;
    case 34:
        eqweapon1 = 1;
        eqrange = 207;
        eqammo(0) = 25001;
        eqammo(1) = 3;
        return;
    case 141: eqweapon1 = 358; return;
    case 143: eqweapon1 = 359; return;
    case 144: eqweapon1 = 356; return;
    case 145: eqring1 = 357; return;
    case 336:
        eqtwohand = 1;
        eqweapon1 = 739;
        return;
    case 338:
        eqtwohand = 1;
        eqweapon1 = 739;
        return;
    case 339:
        eqtwohand = 1;
        eqweapon1 = 739;
        return;
    case 342:
        eqtwohand = 1;
        eqweapon1 = 739;
        return;
    case 340:
        eqtwohand = 1;
        eqweapon1 = 739;
        return;
    case 299: eqtwohand = 1; return;
    case 300:
        eqweapon1 = 695;
        eqtwohand = 1;
        return;
    case 309: eqmultiweapon = 2; return;
    case 310: eqmultiweapon = 266; return;
    case 311: eqmultiweapon = 224; return;
    case 307:
        eqweapon1 = 735;
        eqtwohand = 1;
        return;
    case 308: eqweapon1 = 735; return;
    case 50: eqtwohand = 1; return;
    case 90: eqtwohand = 1; return;
    case 151: eqtwohand = 1; return;
    case 156: eqtwohand = 1; return;
    case 303: eqtwohand = 1; return;
    case 163: eqrange = 210; return;
    case 170: eqrange = 210; return;
    case 177:
        eqweapon1 = 1;
        eqrange = 514;
        eqammo(0) = 25030;
        eqammo(1) = 3;
        return;
    case 212: eqweapon1 = 56; return;
    case 301: eqtwohand = 1; return;
    case 317:
        eqweapon1 = 232;
        eqtwohand = 1;
        return;
    case 318:
        eqrange(0) = 496;
        eqrange(1) = 4;
        eqammo(0) = 25020;
        eqammo(1) = 3;
        return;
    default: return;
    }
}



void chara_db_get_talk(CharaId chara_id, int talk_type)
{
    switch (chara_id)
    {
    case CharaId::younger_sister:
    case CharaId::younger_sister_of_mansion: {
        std::string text = i18n::s.get_enum("core.ui.onii", cdata.player().sex);

        if (talk_type == 100)
        {
            if (const auto msg =
                    i18n::s.get_optional("core.ui.young_sister.random", text))
            {
                txt(*msg, Message::color{ColorIndex::cyan});
                return;
            }
        }
        if (talk_type == 104)
        {
            if (const auto msg =
                    i18n::s.get_optional("core.ui.young_sister.okaeri", text))
            {
                txt(*msg, Message::color{ColorIndex::cyan});
                return;
            }
        }
        break;
    }
    case CharaId::maid: {
        std::string text =
            i18n::s.get_enum("core.ui.syujin", cdata.player().sex);

        if (talk_type == 100)
        {
            if (const auto msg =
                    i18n::s.get_optional("core.ui.maid.random", text))
            {
                txt(*msg, Message::color{ColorIndex::cyan});
                return;
            }
        }
        if (talk_type == 102)
        {
            if (const auto msg =
                    i18n::s.get_optional("core.ui.maid.died", text))
            {
                txt(*msg, Message::color{ColorIndex::cyan});
                return;
            }
        }
        if (talk_type == 104)
        {
            if (const auto msg =
                    i18n::s.get_optional("core.ui.maid.okaeri", text))
            {
                txt(*msg, Message::color{ColorIndex::cyan});
                return;
            }
        }
        break;
    }
    case CharaId::younger_cat_sister: {
        std::string text = i18n::s.get_enum("core.ui.onii", cdata.player().sex);

        if (talk_type == 100)
        {
            if (const auto msg =
                    i18n::s.get_optional("core.ui.cat_sister.random", text))
            {
                txt(*msg, Message::color{ColorIndex::cyan});
                return;
            }
        }
        if (talk_type == 104)
        {
            if (const auto msg =
                    i18n::s.get_optional("core.ui.cat_sister.okaeri", text))
            {
                txt(*msg, Message::color{ColorIndex::cyan});
                return;
            }
        }
        break;
    }
    default: break;
    }

    const auto dialog_id = "text_" + std::to_string(talk_type);
    if (const auto text = the_character_db.get_text_optional(
            charaid2int(chara_id), dialog_id))
    {
        txt(*text, Message::color{ColorIndex::cyan});
    }
}

} // namespace elona
