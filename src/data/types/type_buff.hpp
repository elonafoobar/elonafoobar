#include "../../enums.hpp"
#include "../../lua_env/wrapped_function.hpp"
#include "../lua_lazy_cache.hpp"

namespace elona
{

struct BuffData
{
    int id;
    sol::table self;
    BuffType type;
    lua::WrappedFunction duration;
    lua::WrappedFunction on_refresh;
    optional<lua::WrappedFunction> on_removal;
    lua::WrappedFunction description;
};

ELONA_DEFINE_LUA_DB(BuffDB, BuffData, true, "core.buff")

extern BuffDB the_buff_db;

} // namespace elona
