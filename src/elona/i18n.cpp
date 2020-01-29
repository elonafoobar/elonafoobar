#include "i18n.hpp"

#include <fstream>
#include <memory>

#include "config.hpp"
#include "defines.hpp"
#include "elona.hpp"
#include "filesystem.hpp"
#include "random.hpp"
#include "variables.hpp"



namespace elona
{
namespace i18n
{

void Store::init(const std::vector<Store::Location>& locations)
{
    for (const auto& loc : locations)
    {
        load_all_files(loc.locale_dir, loc.mod_id);
    }
}



void Store::load_all_files(
    const fs::path& locale_dir,
    const std::string& mod_id)
{
    for (const auto& entry : filesystem::glob_files(locale_dir))
    {
        std::ifstream ifs{entry.path().native()};
        if (!ifs)
        {
            throw std::runtime_error{
                "Failed to open " +
                filepathutil::make_preferred_path_in_utf8(entry.path())};
        }

        load_from_stream(ifs, filepathutil::to_utf8_path(entry.path()), mod_id);
    }
}



void Store::load_from_string(const std::string& src, const std::string& mod_id)
{
    std::istringstream ss{src};
    load_from_stream(ss, "[string]", mod_id);
}



void Store::load_from_stream(
    std::istream& in,
    const std::string& filepath,
    const std::string& mod_id)
{
    lua::lua->get_i18n_manager().load(in, filepath, mod_id);
}



std::string space_if_needed()
{
    if (jp)
    {
        return "";
    }
    else
    {
        return u8" ";
    }
}

} // namespace i18n
} // namespace elona
