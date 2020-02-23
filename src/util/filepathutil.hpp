#pragma once

#include <filesystem>
#include <optional>



namespace filepathutil
{

std::filesystem::path u8path(const std::string&);
std::string make_preferred_path_in_utf8(const std::filesystem::path& path);
std::string to_utf8_path(const std::filesystem::path& path);
std::string to_forward_slashes(const std::filesystem::path& path);
std::optional<std::filesystem::path::string_type> get_executable_path();

/**
 * Check if @a filename is portable on many platforms. It returns the same
 * result for the same @a filename regardless of the platform where you compile
 * this file and the program runs.
 *
 * @param filename The filename to check
 * @returns True if @a filename is portable; otherwise, false.
 */
bool is_portable_path(const std::filesystem::path& filename);

} // namespace filepathutil
