#include "type_class.hpp"



namespace elona
{

ClassDB the_class_db;
const constexpr char* data::LuaLazyCacheTraits<ClassDB>::type_id;



ClassData ClassDB::convert(const lua::ConfigTable& data, const std::string& id)
{
    DATA_OPT_OR(ordering, int, 0);
    DATA_OPT_OR(is_extra, bool, true);
    DATA_OPT_OR(item_type, int, 0);
    DATA_OPT_OR(equipment_type, int, 0);
    DATA_TABLE(skills, int, int);

    return ClassData{
        id,
        ordering,
        is_extra,
        item_type,
        equipment_type,
        skills,
    };
}

} // namespace elona
