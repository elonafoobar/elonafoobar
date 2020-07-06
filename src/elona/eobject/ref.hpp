#pragma once

#include <stdexcept>
#include <type_traits>
#include <utility>



namespace elona::eobject
{

template <typename T>
struct Ref;

template <typename T>
struct OptionalRef;



class null_reference_exception : public std::logic_error
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
 *
 * Note: reference counting is not implemented yet.
 */
template <typename T>
struct Ref
{
    static_assert(std::is_class_v<T>);
    static_assert(!std::is_const_v<T>);
    static_assert(!std::is_volatile_v<T>);

    friend struct OptionalRef<T>;



public:
    /// Constructor from nullptr_t is deleted because Ref is non-null reference.
    Ref(std::nullptr_t) = delete;



    /// Constructor from a raw pointer.
    /// @throw std::null_reference_exception if @a ptr is null.
    explicit Ref(T* ptr)
        : _ptr(ptr)
    {
        if (!ptr)
        {
            throw null_reference_exception{
                "Ref::Ref(): attempt to construct null reference."};
        }
    }



    /// Copy constructor.
    Ref(const Ref& other) noexcept = default;

    /// Move constructor.
    Ref(Ref&& other) noexcept = default;


    /// Copy assignment.
    Ref& operator=(const Ref& other) noexcept = default;


    /// Move assignment.
    Ref& operator=(Ref&& other) noexcept = default;


    /// Assignment from nullptr_t is deleted because Ref is non-null reference.
    Ref& operator=(std::nullptr_t) = delete;



    /// It returns non-null pointer in most cases, except for that you call it
    /// against a moved value.
    T* get_raw_ptr() const noexcept
    {
        return _ptr;
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
    T* _ptr;



    /// Default constructor is hidden because Ref is non-null reference.
    /// If you want to make a null reference, use OptionalRef.
    Ref()
        : _ptr(nullptr)
    {
    }



    struct no_null_check_tag
    {
    };


    /// Constructor from a raw pointer without null check. @a ptr can be null.
    /// This overload is provided for OptionalRef to construct null Ref.
    /// The second parameter is just a tag to distinguish it from `Ref(T*)`
    /// version.
    explicit Ref(T* ptr, no_null_check_tag) noexcept
        : _ptr(ptr)
    {
    }



    /// Constructors from OptionalRef are deleted because it potentially makes
    /// null Ref. If you want to convert an OptionalRef which is surely
    /// non-null, please call OptionalRef::unwrap().
    Ref(const OptionalRef<T>& other) = delete;
    Ref(OptionalRef<T>&& other) = delete;
};



/**
 * An optional reference-counted smart pointer of T. Note that it can be null
 * contrast to Ref. When using this struct, you must check its validity before
 * dereferencing.
 *
 * Note: reference counting is not implemented yet.
 */
template <typename T>
struct OptionalRef
{
    static_assert(std::is_class_v<T>);
    static_assert(!std::is_const_v<T>);
    static_assert(!std::is_volatile_v<T>);

    friend struct Ref<T>;



public:
    /// Default constructor; constructs null reference.
    OptionalRef() noexcept
        : _ref(nullptr, typename Ref<T>::no_null_check_tag{})
    {
    }


    /// Constructor from nullptr_t; constructs null reference.
    OptionalRef(std::nullptr_t)
        : _ref(nullptr, typename Ref<T>::no_null_check_tag{})
    {
    }



    /// Constructor from a raw pointer. @a ptr can be null.
    explicit OptionalRef(T* ptr) noexcept
        : _ref(ptr, typename Ref<T>::no_null_check_tag{})
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
        _ref._ptr = nullptr;
        return *this;
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
    /// @throw null_reference_exception if this is null.
    Ref<T> unwrap() const
    {
        if (is_null())
        {
            throw null_reference_exception{
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
        return _ref._ptr;
    }



    T* operator->() const
    {
        if (is_null())
        {
            throw null_reference_exception{
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



private:
    Ref<T> _ref;
};

} // namespace elona::eobject
