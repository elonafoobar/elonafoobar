#include "filepathutil.hpp"
#include <algorithm>
#include <boost/locale.hpp>



namespace filepathutil
{

namespace fs = boost::filesystem;
namespace conv = boost::locale::conv;



fs::path u8path(const std::string& str)
{
    return conv::utf_to_utf<fs::path::string_type::value_type>(str);
}



std::string make_preferred_path_in_utf8(const fs::path& path)
{
    auto path_ = path;
    return conv::utf_to_utf<char>(path_.make_preferred().native());
}



std::string to_utf8_path(const fs::path& path)
{
    return conv::utf_to_utf<char>(path.native());
}



std::string to_forward_slashes(const fs::path& path)
{
    std::string path_str = to_utf8_path(path);
    std::replace(path_str.begin(), path_str.end(), '\\', '/');
    return path_str;
}

} // namespace filepathutil
