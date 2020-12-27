#include "calc.hpp"
#include "character.hpp"
#include "class.hpp"
#include "data/types/type_skill.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "food.hpp"
#include "i18n.hpp"
#include "lua_env/interface.hpp"
#include "lua_env/lua_env.hpp"
#include "message.hpp"
#include "race.hpp"
#include "random.hpp"
#include "skill.hpp"
#include "text.hpp"
#include "variables.hpp"



namespace elona
{

void chara_db_set_stats(Character& chara, data::InstanceId chara_id)
{
    const auto data = the_character_db[chara_id];
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
    chara.original_relationship = chara.relationship = data->relationship;
    if (data->race_id != "")
    {
        race_init_chara(chara, data->race_id);
    }
    if (data->class_id != "")
    {
        class_init_chara(chara, data->class_id);
    }
    chara.element_of_unarmed_attack = data->element_of_unarmed_attack;

    for (const auto& [id, level] : data->resistances)
    {
        chara.skills().set_level(id, level);
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
        int color = generate_color(
            data->color, the_character_db.ensure(chara.id).integer_id);
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



int chara_db_get_item_type(data::InstanceId chara_id)
{
    if (const auto data = the_character_db[chara_id])
    {
        return data->item_type;
    }
    else
    {
        return 0;
    }
}



std::string chara_db_get_filter(data::InstanceId chara_id)
{
    if (const auto data = the_character_db[chara_id])
    {
        return data->filter;
    }
    else
    {
        return "";
    }
}



std::string chara_db_get_name(data::InstanceId chara_id)
{
    if (const auto data = the_character_db[chara_id])
    {
        return the_character_db.get_text(data->id, "name");
    }
    else
    {
        return "";
    }
}



void chara_db_invoke_eating_effect(Character& eater, data::InstanceId chara_id)
{
    const auto data = the_character_db[chara_id];
    if (data && data->corpse_eating_callback)
    {
        lua::call(*data->corpse_eating_callback, lua::handle(eater));
    }
}



void chara_db_get_special_equipments(data::InstanceId chara_id)
{
    if (chara_id == "core.zeome")
    {
        eqweapon1 = 63;
    }
    else if (chara_id == "core.orphe")
    {
        eqweapon1 = 64;
    }
    else if (chara_id == "core.whom_dwell_in_the_vanity")
    {
        eqweapon1 = 73;
    }
    else if (chara_id == "core.the_leopard_warrior")
    {
        eqtwohand = 1;
        eqweapon1 = 232;
    }
    else if (chara_id == "core.larnneire")
    {
        eqweapon1 = 206;
    }
    else if (chara_id == "core.lomias")
    {
        eqweapon1 = 1;
        eqrange = 207;
        eqammo(0) = 25001;
        eqammo(1) = 3;
    }
    else if (chara_id == "core.issizzle")
    {
        eqweapon1 = 358;
    }
    else if (chara_id == "core.wynan")
    {
        eqweapon1 = 359;
    }
    else if (chara_id == "core.quruiza")
    {
        eqweapon1 = 356;
    }
    else if (chara_id == "core.corgon")
    {
        eqring1 = 357;
    }
    else if (chara_id == "core.god_inside_ehekatl")
    {
        eqtwohand = 1;
        eqweapon1 = 739;
    }
    else if (chara_id == "core.opatos")
    {
        eqtwohand = 1;
        eqweapon1 = 739;
    }
    else if (chara_id == "core.kumiromi")
    {
        eqtwohand = 1;
        eqweapon1 = 739;
    }
    else if (chara_id == "core.mani")
    {
        eqtwohand = 1;
        eqweapon1 = 739;
    }
    else if (chara_id == "core._test")
    {
        eqtwohand = 1;
        eqweapon1 = 739;
    }
    else if (chara_id == "core.minotaur_king")
        eqtwohand = 1;
    else if (chara_id == "core.ungaga")
    {
        eqweapon1 = 695;
        eqtwohand = 1;
    }
    else if (chara_id == "core.asura")
    {
        eqmultiweapon = 2;
    }
    else if (chara_id == "core.mitra")
    {
        eqmultiweapon = 266;
    }
    else if (chara_id == "core.varuna")
    {
        eqmultiweapon = 224;
    }
    else if (chara_id == "core.executioner")
    {
        eqweapon1 = 735;
        eqtwohand = 1;
    }
    else if (chara_id == "core.messenger_of_death")
    {
        eqweapon1 = 735;
    }
    else if (chara_id == "core.hound")
    {
        eqtwohand = 1;
    }
    else if (chara_id == "core.hand_of_the_murderer")
    {
        eqtwohand = 1;
    }
    else if (chara_id == "core.skeleton_berserker")
    {
        eqtwohand = 1;
    }
    else if (chara_id == "core.knight")
    {
        eqtwohand = 1;
    }
    else if (chara_id == "core.rogue_warrior")
    {
        eqtwohand = 1;
    }
    else if (chara_id == "core.rock_thrower")
    {
        eqrange = 210;
    }
    else if (chara_id == "core.public_performer")
    {
        eqrange = 210;
    }
    else if (chara_id == "core.utima")
    {
        eqweapon1 = 1;
        eqrange = 514;
        eqammo(0) = 25030;
        eqammo(1) = 3;
    }
    else if (chara_id == "core.test_subject")
    {
        eqweapon1 = 56;
    }
    else if (chara_id == "core.conery")
    {
        eqtwohand = 1;
    }
    else if (chara_id == "core.silver_eyed_witch")
    {
        eqweapon1 = 232;
        eqtwohand = 1;
    }
    else if (chara_id == "core.big_daddy")
    {
        eqrange(0) = 496;
        eqrange(1) = 4;
        eqammo(0) = 25020;
        eqammo(1) = 3;
    }
}



void chara_db_get_talk(data::InstanceId chara_id, int talk_type)
{
    if (chara_id == "core.younger_sister" ||
        chara_id == "core.younger_sister_of_mansion")
    {
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
    }
    else if (chara_id == "core.maid")
    {
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
    }
    else if (chara_id == "core.younger_cat_sister")
    {
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
    }

    const auto dialog_id = "text_" + std::to_string(talk_type);
    if (const auto text =
            the_character_db.get_text_optional(chara_id, dialog_id))
    {
        txt(*text, Message::color{ColorIndex::cyan});
    }
}

} // namespace elona
