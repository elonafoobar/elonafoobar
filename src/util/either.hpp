#pragma once

#include <boost/variant.hpp>



/**
 * Utility module for safe error handling.
 * It is highly inspired by Haskell's Data.Either.
 */
namespace either
{

namespace detail
{

template <typename T>
struct left_holder
{
    T value;
};



template <typename T>
struct right_holder
{
    T value;
};

} // namespace detail



/// Make a left value.
template <typename T>
detail::left_holder<T> left(T&& value)
{
    return {std::forward<T>(value)};
}



/// Make a right value.
template <typename T>
detail::right_holder<T> right(T&& value)
{
    return {std::forward<T>(value)};
}



/**
 * Represents either left or right.
 * Typically, left means failure, and right means success. It is because right
 * is *right*.
 * The template parameters, Left and Right, are wrapped by left_holder and
 * right_holder because boost::variant cannot take the same type.
 */
template <typename Left, typename Right>
struct either
    : public boost::
          variant<detail::left_holder<Left>, detail::right_holder<Right>>
{
private:
    using left_holder = detail::left_holder<Left>;
    using right_holder = detail::right_holder<Right>;

    using base_type = boost::variant<left_holder, right_holder>;



public:
    enum class which_type
    {
        left,
        right,
    };


    using left_type = Left;
    using right_type = Right;



    /// Constructs with the left value.
    either(const left_holder& value)
        : base_type(value)
    {
    }



    /// Move-constructs with the left value.
    either(left_holder&& value)
        : base_type(value)
    {
    }



    /// Constructs with the right value.
    either(const right_holder& value)
        : base_type(value)
    {
    }



    /// Move-constructs with the right value.
    either(right_holder&& value)
        : base_type(value)
    {
    }



    /// Factory method to build a left value.
    static either left_of(const left_type& left)
    {
        return either(left_holder{left});
    }



    /// Factory method to build a left value.
    static either left_of(left_type&& left)
    {
        return either(left_holder{std::move(left)});
    }



    /// Factory method to build a right value.
    static either right_of(const right_type& right)
    {
        return either(right_holder{right});
    }



    /// Factory method to build a right value.
    static either right_of(right_type&& right)
    {
        return either(right_holder{std::move(right)});
    }



    /// Get which type the either has.
    which_type which() const
    {
        return base_type::which() == 0 ? which_type::left : which_type::right;
    }



    bool is_left() const
    {
        return which() == which_type::left;
    }



    bool is_right() const
    {
        return which() == which_type::right;
    }



    /// Return true if it is right; otherwise false.
    explicit operator bool() const
    {
        return is_right();
    }



    /// Get the left value.
    left_type& left()
    {
        return boost::get<left_holder>(*this).value;
    }


    /// Get the left value.
    const left_type& left() const
    {
        return boost::get<left_holder>(*this).value;
    }



    /// Get the right value.
    right_type& right()
    {
        return boost::get<right_holder>(*this).value;
    }


    /// Get the right value.
    const right_type& right() const
    {
        return boost::get<right_holder>(*this).value;
    }
};

} // namespace either
