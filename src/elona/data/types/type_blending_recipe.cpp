#include "type_blending_recipe.hpp"

#include "../util.hpp"



namespace elona
{

BlendingRecipeDB the_blending_recipe_db;
const constexpr char* data::DatabaseTraits<BlendingRecipeDB>::type_id;



BlendingRecipeData BlendingRecipeDB::convert(
    const lua::ConfigTable& data,
    const std::string& id)
{
    DATA_LEGACY_ID();
    DATA_OPT_OR(type, int, 0);
    DATA_OPT_OR(required_turns, int, 1);
    DATA_OPT_OR(required_hours, int, 0);
    const auto required_skills =
        data::convert_id_number_table(data, "required_skills");
    int number_of_materials = data.required<sol::table>("materials").size();
    DATA_OPT_OR(known, bool, false);
    DATA_OPT_OR(generated, bool, false);
    DATA_REQ(on_success, sol::protected_function);

    return BlendingRecipeData{
        data::InstanceId{id},
        legacy_id,
        type,
        required_turns,
        required_hours,
        required_skills,
        number_of_materials,
        known,
        generated,
        lua::WrappedFunction(id, on_success),
    };
}

} // namespace elona
