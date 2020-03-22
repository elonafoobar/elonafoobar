/*
 * The Alphanum Algorithm is an improved sorting algorithm for strings
 * containing numbers.  Instead of sorting numbers in ASCII order like
 * a standard sort, this algorithm sorts numbers in numeric order.
 *
 * The Alphanum Algorithm is discussed at http://www.DaveKoelle.com
 *
 * Released under the MIT License - https://opensource.org/licenses/MIT
 *
 * Copyright 2007-2017 David Koelle
 * Copyright 2018 KI
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */



/*
 * Ported to C++ by KI. Please see the above URL for the original Java code,
 * originally called "AlphanumComparator".
 * The modified version same as this file is distributed here:
 *   https://github.com/ki-foobar/natural_order_comparator
 */



#pragma once

#include <cassert>
#include <cctype>

#include <algorithm>
#include <string>



namespace lib
{

/**
 * This is an updated version with enhancements made by Daniel Migowski,
 * Andre Bogus, and David Koelle. Updated by David Koelle in 2017.
 *
 * It is used as a comparison object typically specified to some container's
 * template arguments such as `std::map` and `std::set`.
 */
template <typename StringType>
struct basic_natural_order_comparator
{
public:
    using string_type = StringType;
    using first_argument_type = string_type;
    using second_argument_type = string_type;
    using result_type = bool;
    using value_type = typename string_type::value_type;
    using size_type = typename string_type::size_type;



    /*
     * Returns true if `s1` is less than `s2`; otherwise, false.
     */
    bool operator()(const string_type& s1, const string_type& s2) const
    {
        size_type s1_marker = 0;
        size_type s2_marker = 0;

        while (s1_marker < s1.length() && s2_marker < s2.length())
        {
            const auto s1_chunk = _get_chunk(s1, s1_marker);
            s1_marker += s1_chunk.length();

            const auto s2_chunk = _get_chunk(s2, s2_marker);
            s2_marker += s2_chunk.length();

            // If both chunks contain numeric characters, sort them numerically.
            if (std::isdigit(s1_chunk.front()) &&
                std::isdigit(s2_chunk.front()))
            {
                // Simple chunk comparison by length.
                if (s1_chunk.length() == s2_chunk.length())
                {
                    // If equal, the first different number counts
                    if (s1_chunk != s2_chunk)
                    {
                        return s1_chunk < s2_chunk;
                    }
                    // else, continue the loop.
                }
                else
                {
                    return s1_chunk.length() < s2_chunk.length();
                }
            }
            else if (s1_chunk != s2_chunk)
            {
                return s1_chunk < s2_chunk;
            }
            // else, continue the loop.
        }

        // In this case, `s1` is a part of `s2` or otherwise.
        // E.g., "abc" < "abcd"; compared by their lengths.
        return s1.length() < s2.length();
    }



private:
    string_type _get_chunk(const string_type& s, size_type from) const
    {
        assert(from < s.length());

        if (std::isdigit(s[from]))
        {
            // Find the next "non-digit" character.
            const auto to = std::find_if(
                std::begin(s) + from + 1, std::end(s), [](value_type c) {
                    return !std::isdigit(c);
                });
            return s.substr(from, std::distance(std::begin(s), to) - from);
        }
        else
        {
            // Find the next "digit" character.
            const auto to = std::find_if(
                std::begin(s) + from + 1, std::end(s), [](value_type c) {
                    return std::isdigit(c);
                });
            return s.substr(from, std::distance(std::begin(s), to) - from);
        }
    }
};



// Aliases
using natural_order_comparator = basic_natural_order_comparator<std::string>;
using wnatural_order_comparator = basic_natural_order_comparator<std::wstring>;
using u16natural_order_comparator =
    basic_natural_order_comparator<std::u16string>;
using u32natural_order_comparator =
    basic_natural_order_comparator<std::u32string>;

} // namespace lib
