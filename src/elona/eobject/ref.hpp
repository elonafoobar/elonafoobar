#pragma once

#include <type_traits>



namespace elona::eobject
{

template <typename T>
struct Ref;

template <typename T>
struct OptionalRef;



/**
 * A reference-counted smart pointer of T. It usually holds a valid
 * object, i.e., points to non-null address, with one exception: a moved Ref
 * points to null. Because C++ runtime calls destructor even for moved values,
 * smart pointers in C++ cannot totally reject null to support move semantics.
 * When using this struct, you don't have to check its validity, but never use
 * moved values (It is safe to re-assign some valid value to a moved Ref and
 * then use the Ref, but it is not recommended). Also, note that it is a
 * reference-counted. Copy of the struct needs more cost than raw pointers.
 * This struct hides copy constructor and copy assignment operator by marking
 * them as private methods to prevent you from calling such inefficient
 * operations unintendedly. If you need to copy a Ref struct, you have to call
 * `Ref::clone()` explicitly. It makes a copy of it with incrementing
 * reference count and returns it to the caller.
 *
 * // Example:
 * Ref<T> a_reference = other_reference.clone();   move constructor
 * a_reference = other_reference.clone();          move assignment
 *
 * Since the result of `Ref::clone()` is rvalue, these lines do move.
 */
template <typename T>
struct Ref
{
    static_assert(std::is_class_v<T>);
    static_assert(!std::is_const_v<T>);
    static_assert(!std::is_volatile_v<T>);

    friend struct OptionalRef<T>;



public:
    /// Default ctor is deleted because Ref is non-null reference.
    Ref() = delete;



    /// Ctor from nullptr_t is deleted because Ref is non-null reference.
    Ref(std::nullptr_t) = delete;



    /// Ctor from a raw pointer.
    explicit Ref(T* ptr) noexcept
        : _ptr(ptr)
    {
    }



    /// Move ctor.
    Ref(Ref&& other) noexcept
        : _ptr(other._ptr)
    {
        other._ptr = nullptr;
    }



    /// Ctor from an optional reference.
    explicit Ref(OptionalRef<T>&& other) noexcept
        : _ptr(other._ptr)
    {
        other._ptr = nullptr;
    }



    /// Returns a copy of this Ref.
    Ref clone() const& noexcept
    {
        return Ref{*this};
    }



    /// Returns a copy of this Ref. (for rvalue)
    Ref clone() const&& noexcept
    {
        return Ref{std::move(*this)};
    }



    /// Move ctor.
    Ref& operator=(Ref&& other) noexcept
    {
        _ptr = other._ptr;
        other._ptr = nullptr;
        return *this;
    }



    /// Assignment from nullptr_t is deleted because Ref is non-null reference.
    Ref& operator=(std::nullptr_t) = delete;



    /// It returns false in most cases, except for that you call it against a
    /// moved value.
    constexpr bool is_null() const noexcept
    {
        return _ptr == nullptr;
    }



    /// It returns non-null pointer in most cases, except for that you call it
    /// against a moved value.
    T* get_raw_ptr() const noexcept
    {
        return _ptr;
    }



    /// It it safe operation in most cases, except for that you call it against
    /// a moved value.
    T& get_raw_ref() const
    {
        return *get_raw_ptr();
    }



    /// Returns true if it is null reference.
    bool operator!() const noexcept
    {
        return is_null();
    }



    /// It returns true in most cases, except for that you call it against a
    /// moved value.
    explicit operator bool() const noexcept
    {
        return !is_null();
    }



    /// It it safe operation in most cases, except for that you call it against
    /// a moved value.
    T* operator->() const
    {
        return get_raw_ptr();
    }



    /// It it safe operation in most cases, except for that you call it against
    /// a moved value.
    T& operator*() const
    {
        return get_raw_ref();
    }



    /// Compares reference identity.
    bool operator==(const Ref& other) noexcept
    {
        return _ptr == other._ptr;
    }



    /// Compares reference identity.
    bool operator!=(const Ref& other) noexcept
    {
        return _ptr != other._ptr;
    }



    /// Compares reference identity.
    bool operator==(const OptionalRef<T>& other) noexcept
    {
        return _ptr == other._ptr;
    }



    /// Compares reference identity.
    bool operator!=(const OptionalRef<T>& other) noexcept
    {
        return _ptr != other._ptr;
    }



private:
    T* _ptr;



    /// Copy ctor is hidden because it needs more cost.
    Ref(const Ref& other) noexcept
        : _ptr(other._ptr)
    {
    }



    /// Copy asssignment is hidden because it needs more cost.
    Ref& operator=(const Ref& other) noexcept
    {
        _ptr = other._ptr;
        return *this;
    }



    /// Copy ctor from OptionalRef is deleted because it needs more cost.
    Ref(const OptionalRef<T>& other) = delete;
};



/**
 * An optional reference-counted smart pointer of T. Note that it can be null
 * contrast to Ref. When using this struct, you must check its validity before
 * dereferencing. Also, note that it is a reference-counted. Copy of the struct
 * needs more cost than raw pointers. This struct hides copy constructor
 * and copy assignment operator by marking them as private methods to prevent
 * you from calling such inefficient operations unintendedly. If you need to
 * copy a OptionalRef struct, you have to call `OptionalRef::clone()`
 * explicitly. It makes a copy of it with incrementing reference count and
 * returns it to the caller.
 *
 * // Example:
 * OptionalRef<T> a_reference = other_reference.clone();   move constructor
 * a_reference = other_reference.clone();                  move assignment
 *
 * Since the result of `OptionalRef::clone()` is rvalue, these lines do move.
 */
template <typename T>
struct OptionalRef
{
    static_assert(std::is_class_v<T>);
    static_assert(!std::is_const_v<T>);
    static_assert(!std::is_volatile_v<T>);

    friend struct Ref<T>;



public:
    /// Default ctor, null.
    OptionalRef()
        : _ptr(nullptr)
    {
    }



    /// Ctor from nullptr_t.
    OptionalRef(std::nullptr_t)
        : _ptr(nullptr)
    {
    }



    /// Ctor from a raw pointer.
    explicit OptionalRef(T* ptr) noexcept
        : _ptr(ptr)
    {
    }



    /// Move ctor.
    OptionalRef(OptionalRef&& other) noexcept
        : _ptr(other._ptr)
    {
        other._ptr = nullptr;
    }



    /// Ctor from a non-null reference.
    OptionalRef(Ref<T>&& other) noexcept
        : _ptr(other._ptr)
    {
        other._ptr = nullptr;
    }



    /// Returns a copy of this OptionalRef.
    OptionalRef clone() const& noexcept
    {
        return OptionalRef{*this};
    }



    /// Returns a copy of this OptionalRef. (for rvalue)
    OptionalRef clone() const&& noexcept
    {
        return OptionalRef{std::move(*this)};
    }



    /// Move ctor.
    OptionalRef& operator=(OptionalRef&& other) noexcept
    {
        _ptr = other._ptr;
        other._ptr = nullptr;
        return *this;
    }



    /// Assignment from nullptr_t.
    OptionalRef& operator=(std::nullptr_t)
    {
        _ptr = nullptr;
        return *this;
    }



    /// Returns true if it is null reference.
    constexpr bool is_null() const noexcept
    {
        return _ptr == nullptr;
    }



    /// It returns an internal pointer.
    T* get_raw_ptr() const noexcept
    {
        return _ptr;
    }



    /// Don't call it against null OptionalRef.
    T& get_raw_ref() const
    {
        return *get_raw_ptr();
    }



    /// Returns true if it is null reference.
    bool operator!() const noexcept
    {
        return is_null();
    }



    /// Returns true if it points to a valid object.
    explicit operator bool() const noexcept
    {
        return !is_null();
    }



    /// Don't call it against null OptionalRef.
    T* operator->() const
    {
        return get_raw_ptr();
    }



    /// Don't call it against null OptionalRef.
    T& operator*() const
    {
        return get_raw_ref();
    }



    /// Compares reference identity.
    bool operator==(const OptionalRef& other) noexcept
    {
        return _ptr == other._ptr;
    }



    /// Compares reference identity.
    bool operator!=(const OptionalRef& other) noexcept
    {
        return _ptr != other._ptr;
    }



    /// Compares reference identity.
    bool operator==(const Ref<T>& other) noexcept
    {
        return _ptr == other._ptr;
    }



    /// Compares reference identity.
    bool operator!=(const Ref<T>& other) noexcept
    {
        return _ptr != other._ptr;
    }



private:
    T* _ptr;



    /// Copy ctor is hidden because it needs more cost.
    OptionalRef(const OptionalRef& other) noexcept
        : _ptr(other._ptr)
    {
    }



    /// Copy asssignment is hidden because it needs more cost.
    OptionalRef& operator=(const OptionalRef& other) noexcept
    {
        _ptr = other._ptr;
        return *this;
    }



    /// Copy ctor from Ref is deleted because it needs more cost.
    OptionalRef(const Ref<T>& other) = delete;
};

} // namespace elona::eobject
