#include "../../enums.hpp"
#include "../lua_lazy_cache.hpp"

namespace elona
{

struct BuffData
{
    int id;
    sol::table self;
    BuffType type;
    sol::protected_function duration;
    sol::protected_function on_refresh;
    sol::protected_function description;
};

ELONA_DEFINE_LUA_DB(BuffDB, BuffData, true, "core.buff")

extern BuffDB the_buff_db;

} // namespace elona
