#pragma once

#include "filesystem.hpp"



namespace elona
{


enum class file_operation_t
{
    _1,
    _2,
    _5,
    _6,
    _7,
    _8,
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
    _23,
    _24,
};


void ctrl_file(file_operation_t file_operation);
void ctrl_file(file_operation2_t file_operation, const fs::path& filepath);
void fileadd(const fs::path& filepath, int prm_693 = 0);


} // namespace elona
