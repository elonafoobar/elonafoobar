use crate::C_RAND_MAX;
use rand::{Rng, SeedableRng};
use std::cmp;

type InnerRng = rand_xoshiro::Xoshiro256StarStar;

pub struct DefaultGenerator {
    seed: i64,
    inner: InnerRng,
}

impl DefaultGenerator {
    pub fn with_seed(seed: i64) -> DefaultGenerator {
        DefaultGenerator {
            seed,
            inner: InnerRng::seed_from_u64(seed as _),
        }
    }

    pub fn rnd(&mut self, n: i64) -> i64 {
        if n <= 0 {
            0
        } else {
            self.inner.gen_range(0..n)
        }
    }

    pub fn rnd_range(&mut self, min: i64, max: i64) -> i64 {
        if max < min {
            min
        } else {
            self.inner.gen_range(min..=max)
        }
    }

    pub fn rnd_small(&mut self, n: i64) -> i64 {
        self.rnd(cmp::min(n, C_RAND_MAX))
    }

    pub fn rnd_range_small(&mut self, min: i64, max: i64) -> i64 {
        if max < min {
            min
        } else {
            min + self.rnd_small(max - min + 1)
        }
    }

    pub fn frnd(&mut self, p: f64) -> f64 {
        // TODO: +inf, -inf, NaN
        if p <= 0.0 {
            0.0
        } else {
            self.inner.gen_range(0.0..p)
        }
    }

    pub fn frnd_01(&mut self) -> f64 {
        self.inner.gen()
    }

    pub fn frnd_range(&mut self, min: f64, max: f64) -> f64 {
        // TODO: +inf, -inf, NaN
        if max < min {
            min
        } else {
            self.inner.gen_range(min..max)
        }
    }

    pub fn one_in(&mut self, m: i64) -> bool {
        self.rnd(m) == 0
    }

    pub fn n_in(&mut self, n: i64, m: i64) -> bool {
        self.rnd(m) < n
    }

    pub fn percent(&mut self, p: i64) -> bool {
        self.n_in(p, 100)
    }

    pub fn roll(&mut self, rolls: i64, faces: i64, bonus: i64) -> i64 {
        // TODO: if `rolls` is large, this function costs a lot.
        let mut sum = 0;
        for _ in 0..rolls {
            sum += self.rnd(faces);
        }
        sum + bonus
    }

    pub fn set_seed(&mut self, new_seed: i64) -> i64 {
        let prev_seed = self.seed();
        *self = Self::with_seed(new_seed);
        prev_seed
    }

    pub fn seed(&self) -> i64 {
        self.seed
    }

    pub fn incdec(&mut self, n: i64) -> i64 {
        (self.one_in(n) as i64) - (self.one_in(n) as i64)
    }
}
