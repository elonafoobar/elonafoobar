#include "pool.hpp"

#include "../character.hpp"
#include "../item.hpp"
#include "../lua_env/lua_env.hpp"



namespace elona::eobject
{

template <typename T>
Pool<T>::Pool() noexcept
{
}



template <typename T>
Pool<T>::~Pool() noexcept
{
}



template <typename T>
void Pool<T>::finalize(cell_type* obj_ptr)
{
    (void)obj_ptr;
    assert(obj_ptr);
}



template <typename T>
void Pool<T>::destroy(cell_type* obj_ptr)
{
    (void)obj_ptr;
}



template Pool<Item>::Pool() noexcept;
template Pool<Item>::~Pool() noexcept;
template void Pool<Item>::finalize(internal::MemoryCell<Item>*);
template void Pool<Item>::destroy(internal::MemoryCell<Item>*);

} // namespace elona::eobject
