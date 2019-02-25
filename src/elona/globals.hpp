#pragma once

#ifdef ELONA_DEFINE_GLOBAL_INSTANCE
#define ELONA_EXTERN(declaration) declaration
#else
#define ELONA_EXTERN(declaration) extern declaration
#endif



namespace elona
{

ELONA_EXTERN(bool g_show_resistances);

}



#undef ELONA_EXTERN
