#pragma once

#include "optional.hpp"



namespace elona
{

struct Item;



struct ItemRef
{
    constexpr ItemRef() noexcept = default;


    static constexpr ItemRef null() noexcept
    {
        return ItemRef{};
    }


    static constexpr ItemRef from_index(int item_index) noexcept
    {
        return ItemRef{item_index};
    }


    static ItemRef from_ref(Item& item) noexcept;
    static ItemRef from_opt(optional_ref<Item> item) noexcept;



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



    bool operator==(ItemRef other) const noexcept
    {
        return _objid == other._objid;
    }

    bool operator!=(ItemRef other) const noexcept
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
        return *this == ItemRef::from_opt(other);
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



    constexpr explicit ItemRef(int item_index) noexcept
        : _objid(item_index + 1)
    {
    }
};



// clang-format off
inline bool operator==(const Item&              lhs, ItemRef rhs) noexcept { return rhs == lhs; }
inline bool operator!=(const Item&              lhs, ItemRef rhs) noexcept { return rhs != lhs; }
inline bool operator==(optional_ref<Item>       lhs, ItemRef rhs) noexcept { return rhs == lhs; }
inline bool operator!=(optional_ref<Item>       lhs, ItemRef rhs) noexcept { return rhs != lhs; }
inline bool operator==(optional_ref<const Item> lhs, ItemRef rhs) noexcept { return rhs == lhs; }
inline bool operator!=(optional_ref<const Item> lhs, ItemRef rhs) noexcept { return rhs != lhs; }
// clang-format on

} // namespace elona
