#pragma once

#include <cassert>

#include <stdexcept>
#include <type_traits>
#include <utility>

#include "../serialization/concepts.hpp"
#include "id.hpp"
#include "internal/_pending_ids.hpp"
#include "internal/memory_cell_incomplete.hpp"



namespace elona::eobject
{

template <typename T>
class Pool;

template <typename T>
struct Ref;

template <typename T>
struct OptionalRef;



class bad_optional_error : public std::logic_error
{
    using std::logic_error::logic_error;
};



/**
 * A reference-counted smart pointer of T. It usually holds a valid
 * object, i.e., points to non-null address, with one exception: a moved Ref
 * points to null. Because C++ runtime calls destructor even for moved values,
 * smart pointers in C++ cannot totally reject null to support move semantics.
 * When using this struct, you don't have to check its validity, but never use
 * moved values (It is safe to re-assign some valid value to a moved Ref and
 * then use the Ref, but it is not recommended).
 */
template <typename T>
struct Ref
{
    static_assert(std::is_class_v<T>);
    static_assert(!std::is_const_v<T>);
    static_assert(!std::is_volatile_v<T>);

    friend class Pool<T>;
    friend struct OptionalRef<T>;



public:
    /// Copy constructor.
    Ref(const Ref& other) noexcept
        : _ptr(other._ptr)
    {
        inc_ref_count();
    }


    /// Move constructor.
    Ref(Ref&& other) noexcept
        : _ptr(other._ptr)
    {
        other._ptr = nullptr;
    }


    /// Copy assignment.
    Ref& operator=(const Ref& other) noexcept
    {
        dec_ref_count();
        _ptr = other._ptr;
        inc_ref_count();
        return *this;
    }


    /// Move assignment.
    Ref& operator=(Ref&& other) noexcept
    {
        _ptr = other._ptr;
        other._ptr = nullptr;
        return *this;
    }


    /// Assignment from nullptr_t is deleted because Ref is non-null reference.
    Ref& operator=(std::nullptr_t) = delete;



    /// It returns non-null pointer in most cases, except for that you call it
    /// against a moved value.
    T* get_raw_ptr() const noexcept
    {
        return _ptr ? &_ptr->value : nullptr;
    }



    /// It it safe operation in most cases, except for that you call it against
    /// a moved value.
    T* operator->() const
    {
        return get_raw_ptr();
    }



    /// Compares reference identity.
    bool operator==(const Ref& other) const noexcept
    {
        return _ptr == other._ptr;
    }



    /// Compares reference identity.
    bool operator!=(const Ref& other) const noexcept
    {
        return _ptr != other._ptr;
    }



    /// Compares reference identity.
    bool operator==(const OptionalRef<T>& other) const noexcept
    {
        return _ptr == other._ref._ptr;
    }



    /// Compares reference identity.
    bool operator!=(const OptionalRef<T>& other) const noexcept
    {
        return _ptr != other._ref._ptr;
    }



private:
    internal::MemoryCell<T>* _ptr;



    /// Default constructor is hidden because Ref is non-null reference.
    /// If you want to make a null reference, use OptionalRef.
    Ref()
        : _ptr(nullptr)
    {
    }



    /// Constructor from a raw pointer.
    explicit Ref(internal::MemoryCell<T>* ptr)
        : _ptr(ptr)
    {
    }



    void inc_ref_count()
    {
        if (_ptr)
        {
            internal::inc_ref_count(_ptr);
        }
    }



    void dec_ref_count()
    {
        if (_ptr)
        {
            internal::dec_ref_count(_ptr);
            if (internal::ref_count(_ptr) == 0)
            {
                Pool<T>::instance().finalize(_ptr);

                internal::dec_weak_ref_count(_ptr);
                if (internal::weak_ref_count(_ptr) == 0)
                {
                    Pool<T>::instance().destroy(_ptr);
                }
            }
        }
    }
};



/**
 * An optional reference-counted smart pointer of T. Note that it can be null
 * contrast to Ref. When using this struct, you must check its validity before
 * dereferencing.
 */
template <typename T>
struct OptionalRef
{
    friend struct Ref<T>;



public:
    /// Default constructor; constructs null reference.
    OptionalRef() noexcept
        : _ref()
    {
    }


    /// Constructor from nullptr_t; constructs null reference.
    OptionalRef(std::nullptr_t)
        : _ref()
    {
    }



    /// Copy constructor.
    OptionalRef(const OptionalRef& other) noexcept = default;


    /// Move constructor.
    OptionalRef(OptionalRef&& other) noexcept = default;



    /// Constructor from a non-null reference.
    OptionalRef(const Ref<T>& other) noexcept
        : _ref(other)
    {
    }


    /// Constructor from a non-null reference.
    OptionalRef(Ref<T>&& other) noexcept
        : _ref(std::move(other))
    {
    }



    /// Assignment from nullptr_t.
    OptionalRef& operator=(std::nullptr_t)
    {
        return (*this = Ref<T>{});
    }


    /// Copy assignment.
    OptionalRef& operator=(const OptionalRef& other) noexcept = default;


    /// Move assignment.
    OptionalRef& operator=(OptionalRef&& other) noexcept = default;



    /// Copy assignment from a non-null reference.
    OptionalRef& operator=(const Ref<T>& other) noexcept
    {
        _ref = other;
        return *this;
    }


    /// Move assignment from a non-null reference.
    OptionalRef& operator=(Ref<T>&& other) noexcept
    {
        _ref = std::move(other);
        return *this;
    }



    /// Unwrap this OptionalRef and convert to Ref with null check.
    /// @throw bad_optional_error if this is null.
    Ref<T> unwrap() const
    {
        if (is_null())
        {
            throw bad_optional_error{
                "OptionalRef::unwrap(): attempt to unwrap null reference."};
        }

        return _ref;
    }



    /// Returns true if it is null reference.
    constexpr bool is_null() const noexcept
    {
        return _ref._ptr == nullptr;
    }



    /// Returns true if it is null reference.
    bool operator!() const noexcept
    {
        return is_null();
    }



    /// It returns a raw pointer.
    T* get_raw_ptr() const noexcept
    {
        return _ref.get_raw_ptr();
    }



    T* operator->() const
    {
        if (is_null())
        {
            throw bad_optional_error{
                "OptionalRef::operator->(): attempt to access member of null reference"};
        }
        return get_raw_ptr();
    }



    /// Returns true if it points to a valid object.
    explicit operator bool() const noexcept
    {
        return !is_null();
    }



    /// Compares reference identity.
    bool operator==(const OptionalRef& other) const noexcept
    {
        return _ref._ptr == other._ref._ptr;
    }



    /// Compares reference identity.
    bool operator!=(const OptionalRef& other) const noexcept
    {
        return _ref._ptr != other._ref._ptr;
    }



    /// Compares reference identity.
    bool operator==(const Ref<T>& other) const noexcept
    {
        return _ref._ptr == other._ptr;
    }



    /// Compares reference identity.
    bool operator!=(const Ref<T>& other) const noexcept
    {
        return _ref._ptr != other._ptr;
    }



    template <typename Archive>
    void serialize(Archive& ar)
    {
        if constexpr (serialization::concepts::is_iarchive_v<Archive>)
        {
            Id obj_id;
            ar(obj_id);
            internal::_pending_ids<T>.emplace_back(this, obj_id);
        }
        else
        {
            Id obj_id = is_null() ? Id::nil() : get_raw_ptr()->obj_id;
            ar(obj_id);
        }
    }



private:
    Ref<T> _ref;
};



// TODO weak reference support

} // namespace elona::eobject
