#pragma once

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


    static IndexItemRef from_ref(Item& item) noexcept;
    static IndexItemRef from_opt(optional_ref<Item> item) noexcept;



    explicit operator bool() const noexcept
    {
        return _objid != 0;
    }


    Item& operator*() const
    {
        return as_ref();
    }


    Item* operator->() const
    {
        return as_ptr();
    }



    bool operator==(IndexItemRef other) const noexcept
    {
        return _objid == other._objid;
    }

    bool operator!=(IndexItemRef other) const noexcept
    {
        return !(*this == other);
    }



    bool operator==(const Item& other) const noexcept;

    bool operator!=(const Item& other) const noexcept
    {
        return !(*this == other);
    }



    bool operator==(optional_ref<Item>& other) const noexcept
    {
        return *this == IndexItemRef::from_opt(other);
    }

    bool operator!=(optional_ref<Item>& other) const noexcept
    {
        return !(*this == other);
    }



    bool operator==(optional_ref<const Item>& other) const noexcept;

    bool operator!=(optional_ref<const Item>& other) const noexcept
    {
        return !(*this == other);
    }



    Item& as_ref() const;
    Item* as_ptr() const;
    optional_ref<Item> as_opt() const;



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



// clang-format off
inline bool operator==(const Item&              lhs, IndexItemRef rhs) noexcept { return rhs == lhs; }
inline bool operator!=(const Item&              lhs, IndexItemRef rhs) noexcept { return rhs != lhs; }
inline bool operator==(optional_ref<Item>       lhs, IndexItemRef rhs) noexcept { return rhs == lhs; }
inline bool operator!=(optional_ref<Item>       lhs, IndexItemRef rhs) noexcept { return rhs != lhs; }
inline bool operator==(optional_ref<const Item> lhs, IndexItemRef rhs) noexcept { return rhs == lhs; }
inline bool operator!=(optional_ref<const Item> lhs, IndexItemRef rhs) noexcept { return rhs != lhs; }
// clang-format on

} // namespace elona
