#include "memory_cell.hpp"

#include "../../item.hpp"



namespace elona::eobject::internal
{

template <typename T>
size_t ref_count(MemoryCell<T>* self)
{
    return self->ref_count;
}



template <typename T>
size_t weak_ref_count(MemoryCell<T>* self)
{
    return self->weak_ref_count;
}



template <typename T>
void inc_ref_count(MemoryCell<T>* self)
{
    ++self->ref_count;
}



template <typename T>
void dec_ref_count(MemoryCell<T>* self)
{
    --self->ref_count;
}



template <typename T>
void inc_weak_ref_count(MemoryCell<T>* self)
{
    ++self->weak_ref_count;
}



template <typename T>
void dec_weak_ref_count(MemoryCell<T>* self)
{
    --self->weak_ref_count;
}



template size_t ref_count<Item>(MemoryCell<Item>* self);
template size_t weak_ref_count<Item>(MemoryCell<Item>* self);
template void inc_ref_count<Item>(MemoryCell<Item>* self);
template void dec_ref_count<Item>(MemoryCell<Item>* self);
template void inc_weak_ref_count<Item>(MemoryCell<Item>* self);
template void dec_weak_ref_count<Item>(MemoryCell<Item>* self);

} // namespace elona::eobject::internal
