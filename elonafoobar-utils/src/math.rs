use num_traits::int::PrimInt;

#[inline]
pub fn clamp<T, U>(value: T) -> U
where
    T: PrimInt + From<U>,
    U: PrimInt,
{
    let min: T = U::min_value().into();
    let max: T = U::max_value().into();

    if value < min {
        U::min_value()
    } else if max < value {
        U::max_value()
    } else {
        U::from(value).expect("It must be valid as `U` here")
    }
}
