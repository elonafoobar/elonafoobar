#pragma once

#ifdef ELONA_DEFINE_GLOBAL_INSTANCE
#define ELONA_EXTERN(declaration) declaration
#else
#define ELONA_EXTERN(declaration) extern declaration
#endif



namespace elona
{

enum class AdditionalItemInfo;



ELONA_EXTERN(AdditionalItemInfo g_show_additional_item_info);

} // namespace elona



#undef ELONA_EXTERN
