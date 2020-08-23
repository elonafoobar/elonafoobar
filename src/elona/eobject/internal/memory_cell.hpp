#pragma once

#include "memory_cell_incomplete.hpp"



namespace elona::eobject::internal
{

template <typename T>
struct MemoryCell
{
    size_t ref_count;
    size_t weak_ref_count;
    T value;



    MemoryCell() noexcept
        : ref_count(0)
        , weak_ref_count(0)
        , value()
    {
    }



    MemoryCell(const MemoryCell&) = delete;
    MemoryCell(MemoryCell&&) = delete;
    MemoryCell& operator=(const MemoryCell&) = delete;
    MemoryCell& operator=(MemoryCell&&) = delete;
};

} // namespace elona::eobject::internal
