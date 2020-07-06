#include "index_item_ref.hpp"

#include "item.hpp"



namespace elona
{

IndexItemRef IndexItemRef::from_ref(ItemRef item) noexcept
{
    return from_index(item->index());
}



IndexItemRef IndexItemRef::from_opt(OptionalItemRef item) noexcept
{
    return item ? from_ref(item.unwrap()) : nullptr;
}



ItemRef IndexItemRef::as_ref() const
{
    assert(*this);
    return g_inv[_objid - 1];
}



OptionalItemRef IndexItemRef::as_opt() const
{
    return *this ? OptionalItemRef{as_ref()} : nullptr;
}

} // namespace elona
