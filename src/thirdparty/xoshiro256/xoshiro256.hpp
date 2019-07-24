/*  Written in 2018 by David Blackman and Sebastiano Vigna (vigna@acm.org)

To the extent possible under law, the author has dedicated all copyright
and related and neighboring rights to this software to the public domain
worldwide. This software is distributed without any warranty.

See <http://creativecommons.org/publicdomain/zero/1.0/>. */
#pragma once

#include "splitmix64.hpp"


/* This is xoshiro256** 1.0, our all-purpose, rock-solid generator. It has
   excellent (sub-ns) speed, a state (256 bits) that is large enough for
   any parallel application, and it passes all tests we are aware of.

   For generating just floating-point numbers, xoshiro256+ is even faster.

   The state must be seeded so that it is not everywhere zero. If you have
   a 64-bit seed, we suggest to seed a splitmix64 generator and use its
   output to fill s. */

namespace xoshiro256
{

class xoshiro256_engine
{
public:
    using result_type = uint64_t;
    using seed_type = uint64_t;



    xoshiro256_engine(seed_type initial_seed)
    {
        seed(initial_seed);
    }



    void seed(seed_type new_seed)
    {
        splitmix64_engine seed_gen(new_seed);
        s[0] = seed_gen.next();
        s[1] = seed_gen.next();
        s[2] = seed_gen.next();
        s[3] = seed_gen.next();
    }



    result_type operator()()
    {
        const result_type result_starstar = rotl(s[1] * 5, 7) * 9;

        const result_type t = s[1] << 17;

        s[2] ^= s[0];
        s[3] ^= s[1];
        s[1] ^= s[2];
        s[0] ^= s[3];

        s[2] ^= t;

        s[3] = rotl(s[3], 45);

        return result_starstar;
    }



    static constexpr result_type min()
    {
        return 0;
    }



    static constexpr result_type max()
    {
        return static_cast<result_type>(-1);
    }



private:
    static result_type rotl(const result_type x, int k)
    {
        return (x << k) | (x >> (64 - k));
    }


    result_type s[4];
};

} // namespace xoshiro256
