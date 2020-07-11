#pragma once

#include "eobject/forward.hpp"
#include "optional.hpp"



namespace elona
{

struct Item;



struct IndexItemRef
{
    constexpr IndexItemRef() noexcept = default;


    constexpr IndexItemRef(std::nullptr_t) noexcept
        : IndexItemRef()
    {
    }


    static constexpr IndexItemRef from_index(int item_index) noexcept
    {
        return IndexItemRef{item_index};
    }


    static IndexItemRef from_ref(ItemRef item) noexcept;
    static IndexItemRef from_opt(OptionalItemRef item) noexcept;



    explicit operator bool() const noexcept
    {
        return _objid != 0;
    }



    bool operator==(IndexItemRef other) const noexcept
    {
        return _objid == other._objid;
    }

    bool operator!=(IndexItemRef other) const noexcept
    {
        return !(*this == other);
    }



    ItemRef as_ref() const;
    OptionalItemRef as_opt() const;



    template <typename Archive>
    void serialize(Archive& ar)
    {
        ar(_objid);
    }



private:
    int64_t _objid = 0;



    constexpr explicit IndexItemRef(int item_index) noexcept
        : _objid(item_index + 1)
    {
    }
};

} // namespace elona
