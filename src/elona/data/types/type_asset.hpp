#pragma once
#include "../lua_lazy_cache.hpp"



namespace elona
{

enum class AssetLoadType
{
    // Not loaded on startup, or not from a file.
    None,

    // Loaded before all assets into a new window buffer.
    Buffer,

    // Creates a new buffer when loaded, but not loaded at startup.
    BufferDeferred,

    // Loaded after buffer initialization.
    Startup,
};



struct AssetData
{
    SharedId id;
    int window_id;
    int x;
    int y;
    int width;
    int height;
    int count_x;
    int count_y;
    optional<fs::path> file;
    AssetLoadType load_type;
};



ELONA_DEFINE_LUA_DB(AssetDB, AssetData, false, "core.asset")



extern AssetDB the_asset_db;

} // namespace elona
