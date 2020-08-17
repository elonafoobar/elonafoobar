#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "internal/memory_cell.hpp"
#include "ref.hpp"



namespace elona::eobject
{

template <typename T>
class Pool
{
    friend struct Ref<T>;



public:
    static Pool& instance()
    {
        // TODO: work-argound for use-after-free
        // See issue #1713
        static Pool* ptr = new Pool();
        return *ptr;
    }



    Ref<T> create()
    {
        for (auto&& block : _objects)
        {
            for (auto&& cell : *block)
            {
                if (cell.ref_count == 0 && cell.weak_ref_count == 0)
                {
                    cell.ref_count = 1;
                    cell.weak_ref_count = 1;
                    return Ref<T>{&cell};
                }
            }
        }

        _objects.emplace_back(std::make_unique<block_type>());
        cell_type* new_cell = &_objects.back()->front();
        new_cell->ref_count = 1;
        new_cell->weak_ref_count = 1;
        return Ref<T>{new_cell};
    }



private:
    static constexpr size_t block_size = 256 /* TODO */;

    using cell_type = internal::MemoryCell<T>;
    using block_type = std::array<cell_type, block_size>;
    using storage_type = std::vector<std::unique_ptr<block_type>>; // non-null



    storage_type _objects;



    Pool() noexcept;
    ~Pool() noexcept;

    Pool(const Pool&) = delete;
    Pool(Pool&&) = delete;
    Pool& operator=(const Pool&) = delete;
    Pool& operator=(Pool&&) = delete;



    void finalize(cell_type* obj_ptr);
    void destroy(cell_type* obj_ptr);
};

} // namespace elona::eobject
