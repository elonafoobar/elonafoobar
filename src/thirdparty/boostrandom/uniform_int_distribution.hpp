/**
 * It is based on Boost.Random library and modified by KI to compilable without
 * other Boost dependencies. For the original authors, thier copyright, and the
 * license applied to this file, see below notice.
 *
 * Limitations:
 * In order to make it easy to implement, this implementation has several
 * limitations, compared to the original one.
 * - Lacks `uniform_int_distribution::param_type`.
 * - Lacks stream operator `uniform_int_distribution` to input/output the distribution's range.
 * - Lacks support to equality operators(`operator==` and `operator!=`).
 * - The 1st template type parameter of `uniform_int_distribution`, `T`, must
 *   be one of the built-in integer types.
 * - Does not support old compilers that do not support C++11.
 * - Assumes "#pragma once" directive works as expected.
 *
 * To avoid name conflict, renamed `namespace boost::random` to `namespace boostrandom`.
 */

/* boost random/uniform_int_distribution.hpp header file
 *
 * Copyright Jens Maurer 2000-2001
 * Copyright Steven Watanabe 2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 *
 * Revision history
 *  2001-04-08  added min<max assertion (N. Becker)
 *  2001-02-18  moved to individual header files
 */

#ifndef BOOSTRANDOM_UNIFORM_INT_DISTRIBUTION_HPP
#define BOOSTRANDOM_UNIFORM_INT_DISTRIBUTION_HPP

#include <cassert>
#include "detail/signed_unsigned_tools.hpp"

namespace boostrandom {
namespace detail {
    

#ifdef BOOST_MSVC
#pragma warning(push)
// disable division by zero warning, since we can't
// actually divide by zero.
#pragma warning(disable:4723)
#endif

template<class Engine, class T>
T generate_uniform_int(
    Engine& eng, T min_value, T max_value)
{
    typedef T result_type;
    typedef typename boostrandom::traits::make_unsigned_or_unbounded<T>::type range_type;
    typedef typename Engine::result_type base_result;
    // ranges are always unsigned or unbounded
    typedef typename boostrandom::traits::make_unsigned_or_unbounded<base_result>::type base_unsigned;
    const range_type range = boostrandom::detail::subtract<result_type>()(max_value, min_value);
    const base_result bmin = (eng.min)();
    const base_unsigned brange =
      boostrandom::detail::subtract<base_result>()((eng.max)(), (eng.min)());

    if(range == 0) {
      return min_value;    
    } else if(brange == range) {
      // this will probably never happen in real life
      // basically nothing to do; just take care we don't overflow / underflow
      base_unsigned v = boostrandom::detail::subtract<base_result>()(eng(), bmin);
      return boostrandom::detail::add<base_unsigned, result_type>()(v, min_value);
    } else if(brange < range) {
      // use rejection method to handle things like 0..3 --> 0..4
      for(;;) {
        // concatenate several invocations of the base RNG
        // take extra care to avoid overflows

        //  limit == floor((range+1)/(brange+1))
        //  Therefore limit*(brange+1) <= range+1
        range_type limit;
        if(range == (std::numeric_limits<range_type>::max)()) {
          limit = range/(range_type(brange)+1);
          if(range % (range_type(brange)+1) == range_type(brange))
            ++limit;
        } else {
          limit = (range+1)/(range_type(brange)+1);
        }

        // We consider "result" as expressed to base (brange+1):
        // For every power of (brange+1), we determine a random factor
        range_type result = range_type(0);
        range_type mult = range_type(1);

        // loop invariants:
        //  result < mult
        //  mult <= range
        while(mult <= limit) {
          // Postcondition: result <= range, thus no overflow
          //
          // limit*(brange+1)<=range+1                   def. of limit       (1)
          // eng()-bmin<=brange                          eng() post.         (2)
          // and mult<=limit.                            loop condition      (3)
          // Therefore mult*(eng()-bmin+1)<=range+1      by (1),(2),(3)      (4)
          // Therefore mult*(eng()-bmin)+mult<=range+1   rearranging (4)     (5)
          // result<mult                                 loop invariant      (6)
          // Therefore result+mult*(eng()-bmin)<range+1  by (5), (6)         (7)
          //
          // Postcondition: result < mult*(brange+1)
          //
          // result<mult                                 loop invariant      (1)
          // eng()-bmin<=brange                          eng() post.         (2)
          // Therefore result+mult*(eng()-bmin) <
          //           mult+mult*(eng()-bmin)            by (1)              (3)
          // Therefore result+(eng()-bmin)*mult <
          //           mult+mult*brange                  by (2), (3)         (4)
          // Therefore result+(eng()-bmin)*mult <
          //           mult*(brange+1)                   by (4)
          result += static_cast<range_type>(static_cast<range_type>(boostrandom::detail::subtract<base_result>()(eng(), bmin)) * mult);

          // equivalent to (mult * (brange+1)) == range+1, but avoids overflow.
          if(mult * range_type(brange) == range - mult + 1) {
              // The destination range is an integer power of
              // the generator's range.
              return(result);
          }

          // Postcondition: mult <= range
          // 
          // limit*(brange+1)<=range+1                   def. of limit       (1)
          // mult<=limit                                 loop condition      (2)
          // Therefore mult*(brange+1)<=range+1          by (1), (2)         (3)
          // mult*(brange+1)!=range+1                    preceding if        (4)
          // Therefore mult*(brange+1)<range+1           by (3), (4)         (5)
          // 
          // Postcondition: result < mult
          //
          // See the second postcondition on the change to result. 
          mult *= range_type(brange)+range_type(1);
        }
        // loop postcondition: range/mult < brange+1
        //
        // mult > limit                                  loop condition      (1)
        // Suppose range/mult >= brange+1                Assumption          (2)
        // range >= mult*(brange+1)                      by (2)              (3)
        // range+1 > mult*(brange+1)                     by (3)              (4)
        // range+1 > (limit+1)*(brange+1)                by (1), (4)         (5)
        // (range+1)/(brange+1) > limit+1                by (5)              (6)
        // limit < floor((range+1)/(brange+1))           by (6)              (7)
        // limit==floor((range+1)/(brange+1))            def. of limit       (8)
        // not (2)                                       reductio            (9)
        //
        // loop postcondition: (range/mult)*mult+(mult-1) >= range
        //
        // (range/mult)*mult + range%mult == range       identity            (1)
        // range%mult < mult                             def. of %           (2)
        // (range/mult)*mult+mult > range                by (1), (2)         (3)
        // (range/mult)*mult+(mult-1) >= range           by (3)              (4)
        //
        // Note that the maximum value of result at this point is (mult-1),
        // so after this final step, we generate numbers that can be
        // at least as large as range.  We have to really careful to avoid
        // overflow in this final addition and in the rejection.  Anything
        // that overflows is larger than range and can thus be rejected.

        // range/mult < brange+1  -> no endless loop
        range_type result_increment =
            generate_uniform_int(
                eng,
                static_cast<range_type>(0),
                static_cast<range_type>(range/mult));
        if(std::numeric_limits<range_type>::is_bounded && ((std::numeric_limits<range_type>::max)() / mult < result_increment)) {
          // The multiplcation would overflow.  Reject immediately.
          continue;
        }
        result_increment *= mult;
        // unsigned integers are guaranteed to wrap on overflow.
        result += result_increment;
        if(result < result_increment) {
          // The addition overflowed.  Reject.
          continue;
        }
        if(result > range) {
          // Too big.  Reject.
          continue;
        }
        return boostrandom::detail::add<range_type, result_type>()(result, min_value);
      }
    } else {                   // brange > range
      typedef base_unsigned mixed_range_type;

      mixed_range_type bucket_size;
      // it's safe to add 1 to range, as long as we cast it first,
      // because we know that it is less than brange.  However,
      // we do need to be careful not to cause overflow by adding 1
      // to brange.  We use mixed_range_type throughout for mixed
      // arithmetic between base_unsigned and range_type - in the case
      // that range_type has more bits than base_unsigned it is always
      // safe to use range_type for this albeit it may be more effient
      // to use base_unsigned.  The latter is a narrowing conversion though
      // which may be disallowed if range_type is a multiprecision type
      // and there are no explicit converison operators.

      if(brange == (std::numeric_limits<base_unsigned>::max)()) {
        bucket_size = static_cast<mixed_range_type>(brange) / (static_cast<mixed_range_type>(range)+1);
        if(static_cast<mixed_range_type>(brange) % (static_cast<mixed_range_type>(range)+1) == static_cast<mixed_range_type>(range)) {
          ++bucket_size;
        }
      } else {
        bucket_size = static_cast<mixed_range_type>(brange + 1) / (static_cast<mixed_range_type>(range)+1);
      }
      for(;;) {
        mixed_range_type result =
          boostrandom::detail::subtract<base_result>()(eng(), bmin);
        result /= bucket_size;
        // result and range are non-negative, and result is possibly larger
        // than range, so the cast is safe
        if(result <= static_cast<mixed_range_type>(range))
          return boostrandom::detail::add<mixed_range_type, result_type>()(result, min_value);
      }
    }
}

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

}

/**
 * The class template uniform_int_distribution models a \random_distribution.
 * On each invocation, it returns a random integer value uniformly
 * distributed in the set of integers {min, min+1, min+2, ..., max}.
 *
 * The template parameter IntType shall denote an integer-like value type.
 */
template<class IntType = int>
class uniform_int_distribution
{
public:
    typedef IntType input_type;
    typedef IntType result_type;

    /**
     * Constructs a uniform_int_distribution. @c min and @c max are
     * the parameters of the distribution.
     *
     * Requires: min <= max
     */
    explicit uniform_int_distribution(
        IntType min_arg = 0,
        IntType max_arg = (std::numeric_limits<IntType>::max)())
      : _min(min_arg), _max(max_arg)
    {
        assert(min_arg <= max_arg);
    }

#ifndef BOOST_PREVENT_MACRO_SUBSTITUTION
#define BOOST_PREVENT_MACRO_SUBSTITUTION
#endif

    /**  Returns the minimum value of the distribution */
    IntType min BOOST_PREVENT_MACRO_SUBSTITUTION () const { return _min; }
    /**  Returns the maximum value of the distribution */
    IntType max BOOST_PREVENT_MACRO_SUBSTITUTION () const { return _max; }

    /**  Returns the minimum value of the distribution */
    IntType a() const { return _min; }
    /**  Returns the maximum value of the distribution */
    IntType b() const { return _max; }

    /**
     * Effects: Subsequent uses of the distribution do not depend
     * on values produced by any engine prior to invoking reset.
     */
    void reset() { }

    /** Returns an integer uniformly distributed in the range [min, max]. */
    template<class Engine>
    result_type operator()(Engine& eng) const
    { return detail::generate_uniform_int(eng, _min, _max); }

private:
    IntType _min;
    IntType _max;
};

} // namespace boostrandom

#endif // BOOSTRANDOM_UNIFORM_INT_HPP
