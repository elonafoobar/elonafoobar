#pragma once

#include <unordered_map>
#include "filesystem.hpp"
#include "lib/noncopyable.hpp"



namespace elona
{


enum class file_operation_t
{
    _1,
    _2,
    _5,
    _6,
    _9,
    _10,
    _11,
    _12,
    _13,
    _14,
    _15,
    _16,
    _17,
};



enum class file_operation2_t
{
    _3,
    _4,
    _7,
    _8,
    _23,
    _24,
};



class save_t : public lib::noncopyable
{
public:
    static save_t& instance();


    void clear();
    void add(const fs::path& filename);
    void remove(const fs::path& filename);

    void save(const fs::path& save_dir);


private:
    save_t() = default;

    std::unordered_map<fs::path, bool> saved_files;
};



void ctrl_file(file_operation_t file_operation);
void ctrl_file(file_operation2_t file_operation, const fs::path& filepath);
void tmpload(const fs::path& filename);
bool writeloadedbuff(const fs::path& filename);
void writeloadedbuff_clear();


} // namespace elona
