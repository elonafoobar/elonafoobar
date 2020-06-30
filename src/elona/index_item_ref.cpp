#include "index_item_ref.hpp"

#include "item.hpp"



namespace elona
{

IndexItemRef IndexItemRef::from_ref(Item& item) noexcept
{
    return from_index(item.index());
}



IndexItemRef IndexItemRef::from_opt(optional_ref<Item> item) noexcept
{
    return item ? from_ref(*item) : nullptr;
}



bool IndexItemRef::operator==(const Item& other) const noexcept
{
    return *this == IndexItemRef::from_index(other.index());
}



bool IndexItemRef::operator==(optional_ref<const Item>& other) const noexcept
{
    if (other)
    {
        return *this == IndexItemRef::from_index(other->index());
    }
    else
    {
        return !(*this);
    }
}



Item& IndexItemRef::as_ref() const
{
    assert(*this);
    return *g_inv[_objid - 1];
}



Item* IndexItemRef::as_ptr() const
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



optional_ref<Item> IndexItemRef::as_opt() const
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
