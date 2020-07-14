#pragma once

#include <cstddef>



namespace elona::eobject::internal
{

template <typename T>
struct MemoryCell;



template <typename T>
size_t ref_count(MemoryCell<T>* self);

template <typename T>
size_t weak_ref_count(MemoryCell<T>* self);

template <typename T>
void inc_ref_count(MemoryCell<T>* self);

template <typename T>
void dec_ref_count(MemoryCell<T>* self);

template <typename T>
void inc_weak_ref_count(MemoryCell<T>* self);

template <typename T>
void dec_weak_ref_count(MemoryCell<T>* self);

} // namespace elona::eobject::internal
