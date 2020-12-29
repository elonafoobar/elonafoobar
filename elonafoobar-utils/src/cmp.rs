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
 * Ported to Rust by KI. Please see the above URL for the original Java code,
 * originally called "AlphanumComparator".
 */

use std::cmp::Ordering;

/*
 * This is an updated version with enhancements made by Daniel Migowski,
 * Andre Bogus, and David Koelle. Updated by David Koelle in 2017.
 */

/// Compare `s1` and `s2` by natural ordering.
pub fn cmp(s1: impl AsRef<[u8]>, s2: impl AsRef<[u8]>) -> Ordering {
    let s1 = s1.as_ref();
    let s2 = s2.as_ref();

    let mut s1_marker: usize = 0;
    let mut s2_marker: usize = 0;

    while s1_marker < s1.len() && s2_marker < s2.len() {
        let s1_chunk = get_chunk(s1, s1_marker);
        s1_marker += s1_chunk.len();
        let s2_chunk = get_chunk(s2, s2_marker);
        s2_marker += s2_chunk.len();
        assert!(!s1_chunk.is_empty() && !s2_chunk.is_empty());

        if s1_chunk[0].is_ascii_digit() && s2_chunk[0].is_ascii_digit() {
            // If both chunks contain numeric characters, sort them numerically.
            // Simple chunk comparison by len.
            if s1_chunk.len() == s2_chunk.len() {
                // If equal, the first different number counts
                if s1_chunk != s2_chunk {
                    return s1_chunk.cmp(s2_chunk);
                }
            // else, continue the loop.
            } else {
                return s1_chunk.len().cmp(&s2_chunk.len());
            }
        } else {
            match s1_chunk.cmp(&s2_chunk) {
                Ordering::Equal => (),
                Ordering::Less => return Ordering::Less,
                Ordering::Greater => return Ordering::Greater,
            }
        }
        // else, continue the loop.
    }

    // In this case, `s1` is a part of `s2` or otherwise.
    // E.g., "abc" < "abcd"; compared by their lengths.
    s1.len().cmp(&s2.len())
}

fn get_chunk(s: &[u8], from: usize) -> &[u8] {
    assert!(from < s.len());
    for to in (from + 1)..s.len() {
        // Find the next chunk boundary.
        if s[from].is_ascii_digit() != s[to].is_ascii_digit() {
            return &s[from..to];
        }
    }
    &s[from..]
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_cmp() {
        let strings = &mut [
            "dazzle2",
            "dazzle2",
            "dazzle10",
            "dazzle1",
            "dazzle2.7",
            "dazzle2.10",
            "2",
            "10",
            "10",
            "1",
            "EctoMorph6",
            "EctoMorph62",
            "EctoMorph7",
        ];
        strings.sort_by(|s1, s2| cmp(s1, s2));

        let expected = &[
            "1",
            "2",
            "10",
            "10",
            "EctoMorph6",
            "EctoMorph7",
            "EctoMorph62",
            "dazzle1",
            "dazzle2",
            "dazzle2",
            "dazzle2.7",
            "dazzle2.10",
            "dazzle10",
        ];

        assert_eq!(strings, expected);
    }
}
