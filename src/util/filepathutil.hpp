#pragma once

// Prevent some old features from being defined.
// See also https://www.boost.org/doc/libs/1_66_0/libs/filesystem/doc/index.htm.
#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
#include <boost/optional.hpp>



namespace filepathutil
{

boost::filesystem::path u8path(const std::string&);
std::string make_preferred_path_in_utf8(const boost::filesystem::path& path);
std::string to_utf8_path(const boost::filesystem::path& path);
std::string to_forward_slashes(const boost::filesystem::path& path);
boost::optional<boost::filesystem::path::string_type> get_executable_path();

/**
 * Check if @a filename is portable on many platforms. It returns the same
 * result for the same @a filename regardless of the platform where you compile
 * this file and the program runs.
 *
 * @param filename The filename to check
 * @returns True if @a filename is portable; otherwise, false.
 */
bool is_portable_path(const boost::filesystem::path& filename);

} // namespace filepathutil
