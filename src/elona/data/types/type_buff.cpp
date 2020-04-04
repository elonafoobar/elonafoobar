#include "type_buff.hpp"

#include "../../lua_env/enums/enums.hpp"

namespace elona
{

BuffDB the_buff_db;
const constexpr char* data::DatabaseTraits<BuffDB>::type_id;



BuffData BuffDB::convert(const lua::ConfigTable& data, const std::string& id)
{
    DATA_LEGACY_ID();
    DATA_ENUM(buff_type, BuffType, BuffTypeTable, BuffType::buff);
    DATA_REQ(duration, sol::protected_function);
    DATA_REQ(on_refresh, sol::protected_function);
    DATA_OPT(on_removal, sol::protected_function);
    DATA_REQ(description, sol::protected_function);

    optional<lua::WrappedFunction> on_removal_ = none;
    if (on_removal)
    {
        on_removal_ = lua::WrappedFunction(id, *on_removal);
    }

    return BuffData{
        data::InstanceId{id},
        legacy_id,
        data.storage,
        buff_type,
        lua::WrappedFunction(id, duration),
        lua::WrappedFunction(id, on_refresh),
        on_removal_,
        lua::WrappedFunction(id, description),
    };
}

} // namespace elona
