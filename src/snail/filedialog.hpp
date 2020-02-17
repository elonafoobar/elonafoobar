#pragma once

#include <string>
#include <vector>

#include "filesystem.hpp"



namespace elona
{
namespace snail
{

using u8string = std::string;



enum class FileDialogResultType
{
    error,
    okay,
    cancel,
};



struct FileDialogResult
{
    FileDialogResultType type;
    fs::path filepath;
};



struct FileDialogResultMultiple
{
    FileDialogResultType type;
    std::vector<fs::path> filepath_list;
};



class OpenFileDialog
{
public:
    // Note: `filter_list` is not validated in snail side. DO NOT pass user
    // input directly.
    OpenFileDialog(const fs::path& default_path, const u8string& filter_list)
        : default_path(default_path)
        , filter_list(filter_list)
    {
    }

    FileDialogResult show();


private:
    fs::path default_path;
    u8string filter_list;
};



class OpenMultipleFileDialog
{
public:
    // Note: `filter_list` is not validated in snail side. DO NOT pass user
    // input directly.
    OpenMultipleFileDialog(
        const fs::path& default_path,
        const u8string& filter_list)
        : default_path(default_path)
        , filter_list(filter_list)
    {
    }

    FileDialogResultMultiple show();


private:
    fs::path default_path;
    u8string filter_list;
};



class SaveFileDialog
{
public:
    // Note: `filter_list` is not validated in snail side. DO NOT pass user
    // input directly.
    SaveFileDialog(const fs::path& default_path, const u8string& filter_list)
        : default_path(default_path)
        , filter_list(filter_list)
    {
    }

    FileDialogResult show();


private:
    fs::path default_path;
    u8string filter_list;
};



class OpenFolderDialog
{
public:
    OpenFolderDialog(const fs::path& default_path)
        : default_path(default_path)
    {
    }

    FileDialogResult show();


private:
    fs::path default_path;
};

} // namespace snail
} // namespace elona
