#pragma once



/**
 * Example:
 * // Define a named parameter.
 * NAMEDPARAM_DEFINE(bool, do_something);
 *
 * // Use it.
 * void f(do_something do_something_)
 * {
 *     if (do_something_)
 *     {
 *         ...
 *     }
 * }
 */



namespace namedparam
{

template <typename T, typename Tag>
struct named_parameter_base
{
    named_parameter_base(T&& value)
        : _value(value)
    {
    }


    operator T()
    {
        return _value;
    }


private:
    T _value;
};

} // namespace namedparam



// Since the 2nd template parameter of `named_parameter_base`, Tag, is a
// phantom type, this undefined struct, `struct name##_tag`, is allowed to be
// passed as a template argument.
#define NAMEDPARAM_DEFINE(Type, name) \
    using name = namedparam::named_parameter_base<Type, struct name##_tag>
