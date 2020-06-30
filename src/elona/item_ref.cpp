#include "item_ref.hpp"

#include "item.hpp"



namespace elona
{

ItemRef ItemRef::from_ref(Item& item) noexcept
{
    return from_index(item.index());
}



ItemRef ItemRef::from_opt(optional_ref<Item> item) noexcept
{
    return item ? from_ref(*item) : null();
}



bool ItemRef::operator==(const Item& other) const noexcept
{
    return *this == ItemRef::from_index(other.index());
}



bool ItemRef::operator==(optional_ref<const Item>& other) const noexcept
{
    if (other)
    {
        return *this == ItemRef::from_index(other->index());
    }
    else
    {
        return !(*this);
    }
}



Item& ItemRef::as_ref() const
{
    assert(*this);
    return g_inv[_objid - 1];
}



Item* ItemRef::as_ptr() const
{
    if (*this)
    {
        return &as_ref();
    }
    else
    {
        return nullptr;
    }
}



optional_ref<Item> ItemRef::as_opt() const
{
    if (*this)
    {
        return as_ref();
    }
    else
    {
        return nullptr;
    }
}

} // namespace elona
