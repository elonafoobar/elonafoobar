#include "lson.hpp"

namespace elona
{
namespace lua
{
namespace lson
{

namespace
{

sol::state& lson_state()
{
    static sol::state L;
    // Don't open any libraries.
    return L;
}

} // namespace



Value parse_file(const fs::path& path)
{
    sol::environment env(lson_state(), sol::create);
    (void)lson_state().safe_script_file(filepathutil::to_utf8_path(path), env);
    return Value{env};
}

} // namespace lson
} // namespace lua
} // namespace elona
