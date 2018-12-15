/**
 * It is based on Boost.Random library and modified by KI to compilable without
 * other Boost dependencies. For the original authors, thier copyright, and the
 * license applied to this file, see below notice.
 *
 * To avoid name conflict, renamed `namespace boost::random` to `namespace boostrandom`.
 */

/* boost random/traits.hpp header file
 *
 * Copyright John Maddock 2015
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * These traits classes serve two purposes: they are designed to mostly
 * work out of the box for multiprecision types (ie number types that are
 * C++ class types and not integers or floats from type-traits point of view),
 * they are also a potential point of specialization for user-defined
 * number types.
 *
 * $Id$
 */

#ifndef BOOSTRANDOM_TRAITS_HPP
#define BOOSTRANDOM_TRAITS_HPP

#include <limits>

namespace boostrandom {
namespace traits {
   // \cond show_private
   template <class T, bool intrinsic>
   struct make_unsigned_imp
   {
      typedef typename std::make_unsigned<T>::type type;
   };
   template <class T>
   struct make_unsigned_imp<T, false>
   {
      static_assert(std::numeric_limits<T>::is_specialized, "");
      static_assert(std::numeric_limits<T>::is_signed == false, "");
      static_assert(std::numeric_limits<T>::is_integer == true, "");
      typedef T type;
   };
   // \endcond
   /** \brief Converts the argument type T to an unsigned type.
   *
   * This trait has a single member `type` which is the unsigned type corresponding to T.
   * Note that
   * if T is signed, then member `type` *should define a type with one more bit precision than T*.  For built-in
   * types this trait defaults to `std::make_unsigned<T>::type`.  For user defined types it simply asserts that
   * the argument type T is an unsigned integer (using std::numeric_limits).
   * User defined specializations may be provided for other cases.
   */
   template <class T>
   struct make_unsigned
   // \cond show_private
      : public make_unsigned_imp < T, std::is_integral<T>::value > 
      // \endcond
   {};
   // \cond show_private
   template <class T, bool intrinsic>
   struct make_unsigned_or_unbounded_imp
   {
      typedef typename std::make_unsigned<T>::type type;
   };
   template <class T>
   struct make_unsigned_or_unbounded_imp<T, false>
   {
      static_assert(std::numeric_limits<T>::is_specialized, "");
      static_assert((std::numeric_limits<T>::is_signed == false) || (std::numeric_limits<T>::is_bounded == false), "");
      static_assert(std::numeric_limits<T>::is_integer == true, "");
      typedef T type;
   };
   // \endcond
   /** \brief Converts the argument type T to either an unsigned type or an unbounded integer type.
   *
   * This trait has a single member `type` which is either the unsigned type corresponding to T or an unbounded
   * integer type.  This trait is used to generate types suitable for the calculation of a range: as a result
   * if T is signed, then member `type` *should define a type with one more bit precision than T*.  For built-in
   * types this trait defaults to `std::make_unsigned<T>::type`.  For user defined types it simply asserts that
   * the argument type T is either an unbounded integer, or an unsigned one (using std::numeric_limits).
   * User defined specializations may be provided for other cases.
   */
   template <class T>
   struct make_unsigned_or_unbounded
      // \cond show_private
      : public make_unsigned_or_unbounded_imp < T, std::is_integral<T>::value > 
      // \endcond
   {};
}

} // namespace boostrandom

#endif // BOOSTRANDOM_TRAITS_HPP
