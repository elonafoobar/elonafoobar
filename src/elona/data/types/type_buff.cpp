#include "type_buff.hpp"
#include "../../lua_env/enums/enums.hpp"

namespace elona
{

BuffDB the_buff_db;
const constexpr char* data::LuaLazyCacheTraits<BuffDB>::type_id;


BuffData BuffDB::convert(const lua::ConfigTable& data, const std::string& id)
{
    auto legacy_id = data.required<int>("id");
    DATA_ENUM(buff_type, BuffType, BuffTypeTable, BuffType::buff);
    DATA_REQ_FUNC(duration);
    DATA_REQ_FUNC(on_refresh);
    DATA_OPT_FUNC(on_removal);
    DATA_REQ_FUNC(description);

    return BuffData{
        legacy_id,
        data.storage,
        buff_type,
        duration,
        on_refresh,
        on_removal,
        description,
    };
}

} // namespace elona
