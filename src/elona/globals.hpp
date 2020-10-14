#pragma once

#include "data/id.hpp"



#ifdef ELONA_DEFINE_GLOBAL_INSTANCE
#define ELONA_EXTERN(declaration) declaration
#else
#define ELONA_EXTERN(declaration) extern declaration
#endif



namespace elona
{

enum class AdditionalItemInfo;



ELONA_EXTERN(AdditionalItemInfo g_show_additional_item_info);


// proc fury/splitting/active-form damage text from damage_hp()? 1 if not, 2 if
// yes
ELONA_EXTERN(int g_proc_damage_events_flag);

ELONA_EXTERN(int g_chara_last_attacked_by_player);

ELONA_EXTERN(bool g_player_is_changing_equipment);

ELONA_EXTERN(bool g_is_autodig_enabled);

// For rendering weather effect. See ui.cpp
ELONA_EXTERN(data::InstanceId g_prev_weather);

} // namespace elona



#undef ELONA_EXTERN
