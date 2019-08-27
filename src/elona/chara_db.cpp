#include "ability.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "class.hpp"
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

void chara_db_set_stats(CharaId chara_id)
{
    const auto data = the_character_db[charaid2int(chara_id)];
    if (!data)
    {
        return;
    }

    cdata[rc].id = chara_id;
    cdata[rc].level = initlv != 0 ? initlv : data->level;
    if (voidlv != 0)
    {
        cdata[rc].level = voidlv * (100 + data->level * 2) / 100;
    }
    cdata[rc].ai_calm = data->ai_calm;
    cdata[rc].ai_heal = data->ai_heal;
    cdata[rc].ai_move = data->ai_move;
    cdata[rc].ai_dist = data->ai_dist;
    cdata[rc].ai_act_sub_freq = data->ai_act_sub_freq;
    cdata[rc].normal_actions = data->normal_actions;
    cdata[rc].special_actions = data->special_actions;
    creaturepack = data->creaturepack;
    cdata[rc].can_talk = data->can_talk;
    cdatan(0, rc) = i18n::s.get_m("chara", data->id, "name");
    if (data->has_random_name)
    {
        cdatan(0, rc) = i18n::s.get(
            "core.chara.job.own_name", cdatan(0, rc), random_name());
        cdata[rc].has_own_name() = true;
    }
    cdata[rc].original_relationship = cdata[rc].relationship =
        data->original_relationship;
    if (!data->race.empty())
    {
        race_init_chara(cdata[rc], data->race);
    }
    if (!data->class_.empty())
    {
        class_init_chara(cdata[rc], data->class_);
    }
    cdata[rc].element_of_unarmed_attack = data->element_of_unarmed_attack;

    for (const auto& pair : data->resistances)
    {
        if (const auto ability_data = the_ability_db[pair.first])
        {
            sdata(ability_data->legacy_id, rc) = pair.second;
        }
        else
        {
            // Skip the resistance if undefined.
            ELONA_WARN("lua.data") << "Undefined resistance ID: " << pair.first
                                   << " (character " << data->id << ")";
        }
    }

    if (data->sex != -1)
    {
        cdata[rc].sex = data->sex;
    }
    if (data->image != 0)
    {
        cdata[rc].image = data->image;
    }
    if (cdata[rc].sex == 0 && data->male_image != 0)
    {
        cdata[rc].image = data->male_image;
    }
    if (cdata[rc].sex == 1 && data->female_image != 0)
    {
        cdata[rc].image = data->female_image;
    }
    if (cdata[rc].sex == 0)
    {
        cdata[rc].portrait = data->portrait_male;
    }
    else
    {
        cdata[rc].portrait = data->portrait_female;
    }
    {
        int color = generate_color(data->color, charaid2int(cdata[rc].id));
        cdata[rc].image += color * 1000;
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
    cdata[rc].damage_reaction_info = data->damage_reaction_info;
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
        return i18n::s.get_m("chara", data->id, "name");
    }
    else
    {
        return "";
    }
}



void chara_db_invoke_eating_effect(CharaId chara_id)
{
    const auto data = the_character_db[charaid2int(chara_id)];
    if (data && data->corpse_eating_callback)
    {
        lua::call(*data->corpse_eating_callback, lua::handle(cdata[cc]));
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
    {
        std::string text = i18n::s.get_enum("core.ui.onii", cdata.player().sex);

        if (talk_type == 100)
        {
            if (jp)
            {
                txt(u8"「" + text + u8"ちゃんー」",
                    u8"「" + text + u8"ちゃん！」",
                    u8"「" + text + u8"ちゃ〜ん」",
                    u8"「" + text + u8"ちゃんっ」",
                    u8"「" + text + u8"ちゃん？」",
                    u8"「" + text + u8"〜ちゃん」",
                    u8"「" + text + u8"ちゃん♪」",
                    Message::color{ColorIndex::cyan});
                return;
            }
        }
        if (talk_type == 104)
        {
            if (jp)
            {
                txt(u8"「おかえり、" + text + u8"ちゃん！」",
                    u8"「おかえりなさーい、" + text + u8"ちゃん♪」",
                    u8"「待ってたよ、" + text + u8"ちゃん」",
                    Message::color{ColorIndex::cyan});
                return;
            }
        }
    }
    case CharaId::maid:
    {
        std::string text =
            i18n::s.get_enum("core.ui.syujin", cdata.player().sex);

        if (talk_type == 100)
        {
            if (jp)
            {
                txt(u8"「" + text + u8"〜」",
                    text + u8"〜",
                    u8"「用事はありませんか♪」",
                    u8"メイドの熱い視線を感じる…",
                    Message::color{ColorIndex::cyan});
                return;
            }
        }
        if (talk_type == 102)
        {
            if (jp)
            {
                txt(u8"「ダメぇ！」",
                    u8"「" + text + u8"ー！」",
                    Message::color{ColorIndex::cyan});
                return;
            }
        }
        if (talk_type == 104)
        {
            if (jp)
            {
                txt(u8"「おかえりなさいませ、" + text + u8"〜」",
                    u8"「おかえりなさいまし〜」",
                    Message::color{ColorIndex::cyan});
                return;
            }
        }
    }
    case CharaId::younger_cat_sister:
    {
        std::string text = i18n::s.get_enum("core.ui.onii", cdata.player().sex);

        if (talk_type == 100)
        {
            if (jp)
            {
                txt(u8"「" + text + u8"ちゃんー」",
                    u8"「" + text + u8"ちゃん！」",
                    u8"「" + text + u8"ちゃ〜ん」",
                    u8"「" + text + u8"ちゃんっ」",
                    u8"「" + text + u8"ちゃん？」",
                    u8"「" + text + u8"〜ちゃん」",
                    u8"「" + text + u8"ちゃん♪」",
                    Message::color{ColorIndex::cyan});
                return;
            }
        }
        if (talk_type == 104)
        {
            if (jp)
            {
                txt(u8"「おかえりにゃ、" + text + u8"ちゃん！」",
                    u8"「おかえりなさいにゃー、" + text + u8"ちゃん♪」",
                    u8"「待ってたにゃ、" + text + u8"ちゃん」",
                    Message::color{ColorIndex::cyan});
                return;
            }
        }
    }
    case CharaId::younger_sister_of_mansion:
    {
        std::string text = i18n::s.get_enum("core.ui.onii", cdata.player().sex);

        if (talk_type == 100)
        {
            if (jp)
            {
                txt(u8"「" + text + u8"ちゃんー」",
                    u8"「" + text + u8"ちゃん！」",
                    u8"「" + text + u8"ちゃ〜ん」",
                    u8"「" + text + u8"ちゃんっ」",
                    u8"「" + text + u8"ちゃん？」",
                    u8"「" + text + u8"〜ちゃん」",
                    u8"「" + text + u8"ちゃん♪」",
                    Message::color{ColorIndex::cyan});
                return;
            }
        }
        if (talk_type == 104)
        {
            if (jp)
            {
                txt(u8"「おかえり、" + text + u8"ちゃん！」",
                    u8"「おかえりなさーい、" + text + u8"ちゃん♪」",
                    u8"「待ってたよ、" + text + u8"ちゃん」",
                    Message::color{ColorIndex::cyan});
                return;
            }
        }
    }
    default: break;
    }

    const auto chara_id_str =
        the_character_db.get_id_from_legacy(charaid2int(chara_id))->get();
    const auto dialog_id = "text_" + std::to_string(talk_type);
    if (const auto text =
            i18n::s.get_m_optional("chara", chara_id_str, dialog_id))
    {
        txt(*text, Message::color{ColorIndex::cyan});
    }
}

} // namespace elona
