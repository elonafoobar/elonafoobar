#pragma once

#include <boost/optional.hpp>
#include <boost/variant.hpp>



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



template <typename T>
detail::left_holder<T> left(T&& value)
{
    return {std::forward<T>(value)};
}



template <typename T>
detail::right_holder<T> right(T&& value)
{
    return {std::forward<T>(value)};
}



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



    either(const left_holder& value)
        : base_type(value)
    {
    }



    either(left_holder&& value)
        : base_type(value)
    {
    }



    either(const right_holder& value)
        : base_type(value)
    {
    }



    either(right_holder&& value)
        : base_type(value)
    {
    }



    static either left_of(const left_type& left)
    {
        return either(left_holder{left});
    }



    static either left_of(left_type&& left)
    {
        return either(left_holder{std::move(left)});
    }



    static either right_of(const right_type& right)
    {
        return either(right_holder{right});
    }



    static either right_of(right_type&& right)
    {
        return either(right_holder{std::move(right)});
    }



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



    explicit operator bool() const
    {
        return is_right();
    }



    left_type& left()
    {
        return boost::get<left_holder>(*this).value;
    }


    const left_type& left() const
    {
        return boost::get<left_holder>(*this).value;
    }



    right_type& right()
    {
        return boost::get<right_holder>(*this).value;
    }


    const right_type& right() const
    {
        return boost::get<right_holder>(*this).value;
    }
};

} // namespace either
