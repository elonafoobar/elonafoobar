#include "filesystem.hpp"
#include <boost/locale.hpp>

#if BOOST_OS_WINDOWS
// For WideCharToMultiByte().
#include <windows.h>
#define USE_UTF16_AS_FILEPATH 1
#else
#define USE_UTF16_AS_FILEPATH 0
#endif


namespace
{


#if USE_UTF16_AS_FILEPATH
int get_needed_buffer_size(const wchar_t* str)
{
    return WideCharToMultiByte(CP_THREAD_ACP, 0, str, -1, NULL, 0, NULL, NULL);
}


int utf16_to_ansi(const wchar_t* from, char* to, int buffer_size)
{
    return WideCharToMultiByte(
        CP_THREAD_ACP, 0, from, -1, to, buffer_size, NULL, NULL);
}
#endif


} // namespace



namespace elona
{
namespace filesystem
{


std::string make_preferred_path_in_utf8(const fs::path& path)
{
    // Since make_preferred() modifies this and `path` is const, need to copy
    // it.
    auto path_ = path;
    return boost::locale::conv::utf_to_utf<char>(
        path_.make_preferred().native());
}


std::string to_narrow_path(const fs::path& path)
{
#if USE_UTF16_AS_FILEPATH
    const auto wide_c_str = path.native().c_str();

    int needed_length = get_needed_buffer_size(wide_c_str);
    if (needed_length == 0)
        throw "TODO";
    auto buffer = std::make_unique<char[]>(needed_length);
    int used_length = utf16_to_ansi(wide_c_str, buffer.get(), needed_length);
    if (used_length == 0)
        throw "TODO";

    return std::string{buffer.get()};
#else
    return path.native();
#endif
}


} // namespace filesystem
} // namespace elona
