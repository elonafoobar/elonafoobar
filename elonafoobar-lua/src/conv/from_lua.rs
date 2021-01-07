use crate::ffi;
use crate::types::{AsLuaInt, LuaFloat, LuaInt, LuaUserdata};
use anyhow::Result;

pub trait FromLuaValue: Sized {
    fn pop(state: ffi::State) -> Result<Self>;
}

impl FromLuaValue for LuaInt {
    fn pop(state: ffi::State) -> Result<Self> {
        let value = ffi::lua_tointeger(state, -1)?;
        ffi::lua_pop_one(state);
        Ok(value)
    }
}

impl FromLuaValue for LuaFloat {
    fn pop(state: ffi::State) -> Result<Self> {
        let value = ffi::lua_tonumber(state, -1)?;
        ffi::lua_pop_one(state);
        Ok(value)
    }
}

impl FromLuaValue for bool {
    // Any Lua values are automatically converted to boolean.
    // * Truthy: any values other than falsy ones
    // * Falsy: `nil` or `false`
    fn pop(state: ffi::State) -> Result<Self> {
        let value = ffi::lua_toboolean(state, -1);
        ffi::lua_pop_one(state);
        Ok(value)
    }
}

impl FromLuaValue for &str {
    fn pop(state: ffi::State) -> Result<Self> {
        let value = ffi::lua_tostring(state, -1)?;
        ffi::lua_pop_one(state);
        Ok(value)
    }
}

impl<T> FromLuaValue for AsLuaInt<T>
where
    T: FromLuaInt,
{
    fn pop(state: ffi::State) -> Result<Self> {
        let lua_int = LuaInt::pop(state)?;
        Ok(AsLuaInt(T::from_lua_int(lua_int)?))
    }
}

impl<T> FromLuaValue for &T
where
    T: LuaUserdata,
{
    fn pop(state: ffi::State) -> Result<Self> {
        let value = ffi::luaL_testudata(state, -1, T::NAME)?;
        ffi::lua_pop_one(state);
        Ok(value)
    }
}

impl<T> FromLuaValue for &mut T
where
    T: LuaUserdata,
{
    fn pop(state: ffi::State) -> Result<Self> {
        let value = ffi::luaL_testudata_mut(state, -1, T::NAME)?;
        ffi::lua_pop_one(state);
        Ok(value)
    }
}

impl<T> FromLuaValue for Option<&T>
where
    T: LuaUserdata,
{
    fn pop(state: ffi::State) -> Result<Self> {
        // TODO: deny non-T values except for `nil`
        let value = ffi::luaL_testudata(state, -1, T::NAME).ok();
        ffi::lua_pop_one(state);
        Ok(value)
    }
}

impl<T> FromLuaValue for Option<&mut T>
where
    T: LuaUserdata,
{
    fn pop(state: ffi::State) -> Result<Self> {
        // TODO: deny non-T values except for `nil`
        let value = ffi::luaL_testudata_mut(state, -1, T::NAME).ok();
        ffi::lua_pop_one(state);
        Ok(value)
    }
}

pub trait FromLuaInt: Sized {
    fn from_lua_int(value: LuaInt) -> Result<Self>;
}

pub trait FromLuaValues: Sized {
    fn pop_all(state: ffi::State) -> Result<Self>;
}

impl<T1> FromLuaValues for T1
where
    T1: FromLuaValue,
{
    fn pop_all(state: ffi::State) -> Result<Self> {
        ffi::check_nargs(state, 1)?;
        T1::pop(state)
    }
}

// Support 0-tuple to 10-tuple
impl FromLuaValues for () {
    fn pop_all(_lua_state: ffi::State) -> Result<Self> {
        Ok(())
    }
}

impl<T1> FromLuaValues for (T1,)
where
    T1: FromLuaValue,
{
    fn pop_all(state: ffi::State) -> Result<Self> {
        ffi::check_nargs(state, 1)?;
        let v1 = T1::pop(state)?;
        Ok((v1,))
    }
}

impl<T1, T2> FromLuaValues for (T1, T2)
where
    T1: FromLuaValue,
    T2: FromLuaValue,
{
    fn pop_all(state: ffi::State) -> Result<Self> {
        ffi::check_nargs(state, 2)?;
        let v2 = T2::pop(state)?;
        let v1 = T1::pop(state)?;
        Ok((v1, v2))
    }
}

impl<T1, T2, T3> FromLuaValues for (T1, T2, T3)
where
    T1: FromLuaValue,
    T2: FromLuaValue,
    T3: FromLuaValue,
{
    fn pop_all(state: ffi::State) -> Result<Self> {
        ffi::check_nargs(state, 3)?;
        let v3 = T3::pop(state)?;
        let v2 = T2::pop(state)?;
        let v1 = T1::pop(state)?;
        Ok((v1, v2, v3))
    }
}

impl<T1, T2, T3, T4> FromLuaValues for (T1, T2, T3, T4)
where
    T1: FromLuaValue,
    T2: FromLuaValue,
    T3: FromLuaValue,
    T4: FromLuaValue,
{
    fn pop_all(state: ffi::State) -> Result<Self> {
        ffi::check_nargs(state, 4)?;
        let v4 = T4::pop(state)?;
        let v3 = T3::pop(state)?;
        let v2 = T2::pop(state)?;
        let v1 = T1::pop(state)?;
        Ok((v1, v2, v3, v4))
    }
}

impl<T1, T2, T3, T4, T5> FromLuaValues for (T1, T2, T3, T4, T5)
where
    T1: FromLuaValue,
    T2: FromLuaValue,
    T3: FromLuaValue,
    T4: FromLuaValue,
    T5: FromLuaValue,
{
    fn pop_all(state: ffi::State) -> Result<Self> {
        ffi::check_nargs(state, 5)?;
        let v5 = T5::pop(state)?;
        let v4 = T4::pop(state)?;
        let v3 = T3::pop(state)?;
        let v2 = T2::pop(state)?;
        let v1 = T1::pop(state)?;
        Ok((v1, v2, v3, v4, v5))
    }
}

impl<T1, T2, T3, T4, T5, T6> FromLuaValues for (T1, T2, T3, T4, T5, T6)
where
    T1: FromLuaValue,
    T2: FromLuaValue,
    T3: FromLuaValue,
    T4: FromLuaValue,
    T5: FromLuaValue,
    T6: FromLuaValue,
{
    fn pop_all(state: ffi::State) -> Result<Self> {
        ffi::check_nargs(state, 6)?;
        let v6 = T6::pop(state)?;
        let v5 = T5::pop(state)?;
        let v4 = T4::pop(state)?;
        let v3 = T3::pop(state)?;
        let v2 = T2::pop(state)?;
        let v1 = T1::pop(state)?;
        Ok((v1, v2, v3, v4, v5, v6))
    }
}

impl<T1, T2, T3, T4, T5, T6, T7> FromLuaValues for (T1, T2, T3, T4, T5, T6, T7)
where
    T1: FromLuaValue,
    T2: FromLuaValue,
    T3: FromLuaValue,
    T4: FromLuaValue,
    T5: FromLuaValue,
    T6: FromLuaValue,
    T7: FromLuaValue,
{
    fn pop_all(state: ffi::State) -> Result<Self> {
        ffi::check_nargs(state, 7)?;
        let v7 = T7::pop(state)?;
        let v6 = T6::pop(state)?;
        let v5 = T5::pop(state)?;
        let v4 = T4::pop(state)?;
        let v3 = T3::pop(state)?;
        let v2 = T2::pop(state)?;
        let v1 = T1::pop(state)?;
        Ok((v1, v2, v3, v4, v5, v6, v7))
    }
}

impl<T1, T2, T3, T4, T5, T6, T7, T8> FromLuaValues for (T1, T2, T3, T4, T5, T6, T7, T8)
where
    T1: FromLuaValue,
    T2: FromLuaValue,
    T3: FromLuaValue,
    T4: FromLuaValue,
    T5: FromLuaValue,
    T6: FromLuaValue,
    T7: FromLuaValue,
    T8: FromLuaValue,
{
    fn pop_all(state: ffi::State) -> Result<Self> {
        ffi::check_nargs(state, 8)?;
        let v8 = T8::pop(state)?;
        let v7 = T7::pop(state)?;
        let v6 = T6::pop(state)?;
        let v5 = T5::pop(state)?;
        let v4 = T4::pop(state)?;
        let v3 = T3::pop(state)?;
        let v2 = T2::pop(state)?;
        let v1 = T1::pop(state)?;
        Ok((v1, v2, v3, v4, v5, v6, v7, v8))
    }
}

impl<T1, T2, T3, T4, T5, T6, T7, T8, T9> FromLuaValues for (T1, T2, T3, T4, T5, T6, T7, T8, T9)
where
    T1: FromLuaValue,
    T2: FromLuaValue,
    T3: FromLuaValue,
    T4: FromLuaValue,
    T5: FromLuaValue,
    T6: FromLuaValue,
    T7: FromLuaValue,
    T8: FromLuaValue,
    T9: FromLuaValue,
{
    fn pop_all(state: ffi::State) -> Result<Self> {
        ffi::check_nargs(state, 9)?;
        let v9 = T9::pop(state)?;
        let v8 = T8::pop(state)?;
        let v7 = T7::pop(state)?;
        let v6 = T6::pop(state)?;
        let v5 = T5::pop(state)?;
        let v4 = T4::pop(state)?;
        let v3 = T3::pop(state)?;
        let v2 = T2::pop(state)?;
        let v1 = T1::pop(state)?;
        Ok((v1, v2, v3, v4, v5, v6, v7, v8, v9))
    }
}

impl<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> FromLuaValues
    for (T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)
where
    T1: FromLuaValue,
    T2: FromLuaValue,
    T3: FromLuaValue,
    T4: FromLuaValue,
    T5: FromLuaValue,
    T6: FromLuaValue,
    T7: FromLuaValue,
    T8: FromLuaValue,
    T9: FromLuaValue,
    T10: FromLuaValue,
{
    fn pop_all(state: ffi::State) -> Result<Self> {
        ffi::check_nargs(state, 10)?;
        let v10 = T10::pop(state)?;
        let v9 = T9::pop(state)?;
        let v8 = T8::pop(state)?;
        let v7 = T7::pop(state)?;
        let v6 = T6::pop(state)?;
        let v5 = T5::pop(state)?;
        let v4 = T4::pop(state)?;
        let v3 = T3::pop(state)?;
        let v2 = T2::pop(state)?;
        let v1 = T1::pop(state)?;
        Ok((v1, v2, v3, v4, v5, v6, v7, v8, v9, v10))
    }
}

/*

# Ruby code to generate impls (FromLuaValues)
(1..10).each do |n|
  ns = (1..n)
  ts = (1..n).map{|n| "T#{n}"}
  puts <<EOS
impl<#{ts.join(", ")}> FromLuaValues for (#{ts.join(", ")},)
where
    #{ts.map{|t| "#{t}: FromLuaValue,"}.join("\n    ")}
{
    fn pop_all(state: ffi::State) -> Result<Self> {
        ffi::check_nargs(state, #{n})?;
        #{ns.reverse_each.map{|n| "let v#{n} = T#{n}::pop(state)?;"}.join("\n        ")}
        Ok((#{ns.map{|n| "v#{n}"}.join(", ")},))
    }
}

EOS
end

*/
