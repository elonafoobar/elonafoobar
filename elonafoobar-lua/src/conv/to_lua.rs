use crate::ffi::{self, c_int};
use crate::types::{AsLuaInt, LuaFloat, LuaInt, LuaUserdata};
use anyhow::Result;
use elonafoobar_utils as utils;
use std::path::PathBuf;

pub trait ToLuaValue: Sized {
    fn push(self, state: ffi::State) -> Result<()>;
}

impl ToLuaValue for LuaInt {
    fn push(self, state: ffi::State) -> Result<()> {
        ffi::lua_pushinteger(state, self);
        Ok(())
    }
}

impl ToLuaValue for LuaFloat {
    fn push(self, state: ffi::State) -> Result<()> {
        ffi::lua_pushnumber(state, self);
        Ok(())
    }
}

impl ToLuaValue for bool {
    fn push(self, state: ffi::State) -> Result<()> {
        ffi::lua_pushboolean(state, self);
        Ok(())
    }
}

impl ToLuaValue for String {
    fn push(self, state: ffi::State) -> Result<()> {
        ffi::lua_pushstring(state, &self)?;
        Ok(())
    }
}

impl ToLuaValue for PathBuf {
    fn push(self, state: ffi::State) -> Result<()> {
        let string = utils::path::path_to_str(&self).to_owned();
        string.push(state)
    }
}

impl<T> ToLuaValue for AsLuaInt<T>
where
    T: IntoLuaInt,
{
    fn push(self, state: ffi::State) -> Result<()> {
        let value = self.0.into_lua_int()?;
        value.push(state)
    }
}

impl<T> ToLuaValue for Vec<T>
where
    T: ToLuaValue,
{
    fn push(self, state: ffi::State) -> Result<()> {
        ffi::lua_createtable(state, self.len() as c_int, 0);
        let mut index = 1;
        for element in self {
            element.push(state)?;
            ffi::lua_rawseti(state, -2, index);
            index += 1;
        }
        Ok(())
    }
}

impl<T> ToLuaValue for Option<T>
where
    T: ToLuaValue,
{
    fn push(self, state: ffi::State) -> Result<()> {
        match self {
            Some(value) => value.push(state),
            None => {
                ffi::lua_pushnil(state);
                Ok(())
            }
        }
    }
}

impl<T> ToLuaValue for T
where
    T: LuaUserdata,
{
    fn push(self, state: ffi::State) -> Result<()> {
        let mut ptr = ffi::lua_newuserdata_of::<T>(state)?;
        unsafe { ptr.as_uninit_mut() }.write(self);
        ffi::luaL_setmetatable(state, T::NAME)?;
        Ok(())
    }
}

pub trait IntoLuaInt: Sized {
    fn into_lua_int(self) -> Result<LuaInt>;
}

pub trait ToLuaValues: Sized {
    fn push_all(self, state: ffi::State) -> Result<ffi::Nresults>;
}

impl<T1> ToLuaValues for T1
where
    T1: ToLuaValue,
{
    fn push_all(self, state: ffi::State) -> Result<ffi::Nresults> {
        self.push(state)?;
        Ok(1)
    }
}

// Support 0-tuple to 10-tuple
impl ToLuaValues for () {
    fn push_all(self, _lua_state: ffi::State) -> Result<ffi::Nresults> {
        Ok(0)
    }
}

impl<T1> ToLuaValues for (T1,)
where
    T1: ToLuaValue,
{
    fn push_all(self, state: ffi::State) -> Result<ffi::Nresults> {
        self.0.push(state)?;
        Ok(1)
    }
}

impl<T1, T2> ToLuaValues for (T1, T2)
where
    T1: ToLuaValue,
    T2: ToLuaValue,
{
    fn push_all(self, state: ffi::State) -> Result<ffi::Nresults> {
        self.0.push(state)?;
        self.1.push(state)?;
        Ok(2)
    }
}

impl<T1, T2, T3> ToLuaValues for (T1, T2, T3)
where
    T1: ToLuaValue,
    T2: ToLuaValue,
    T3: ToLuaValue,
{
    fn push_all(self, state: ffi::State) -> Result<ffi::Nresults> {
        self.0.push(state)?;
        self.1.push(state)?;
        self.2.push(state)?;
        Ok(3)
    }
}

impl<T1, T2, T3, T4> ToLuaValues for (T1, T2, T3, T4)
where
    T1: ToLuaValue,
    T2: ToLuaValue,
    T3: ToLuaValue,
    T4: ToLuaValue,
{
    fn push_all(self, state: ffi::State) -> Result<ffi::Nresults> {
        self.0.push(state)?;
        self.1.push(state)?;
        self.2.push(state)?;
        self.3.push(state)?;
        Ok(4)
    }
}

impl<T1, T2, T3, T4, T5> ToLuaValues for (T1, T2, T3, T4, T5)
where
    T1: ToLuaValue,
    T2: ToLuaValue,
    T3: ToLuaValue,
    T4: ToLuaValue,
    T5: ToLuaValue,
{
    fn push_all(self, state: ffi::State) -> Result<ffi::Nresults> {
        self.0.push(state)?;
        self.1.push(state)?;
        self.2.push(state)?;
        self.3.push(state)?;
        self.4.push(state)?;
        Ok(5)
    }
}

impl<T1, T2, T3, T4, T5, T6> ToLuaValues for (T1, T2, T3, T4, T5, T6)
where
    T1: ToLuaValue,
    T2: ToLuaValue,
    T3: ToLuaValue,
    T4: ToLuaValue,
    T5: ToLuaValue,
    T6: ToLuaValue,
{
    fn push_all(self, state: ffi::State) -> Result<ffi::Nresults> {
        self.0.push(state)?;
        self.1.push(state)?;
        self.2.push(state)?;
        self.3.push(state)?;
        self.4.push(state)?;
        self.5.push(state)?;
        Ok(6)
    }
}

impl<T1, T2, T3, T4, T5, T6, T7> ToLuaValues for (T1, T2, T3, T4, T5, T6, T7)
where
    T1: ToLuaValue,
    T2: ToLuaValue,
    T3: ToLuaValue,
    T4: ToLuaValue,
    T5: ToLuaValue,
    T6: ToLuaValue,
    T7: ToLuaValue,
{
    fn push_all(self, state: ffi::State) -> Result<ffi::Nresults> {
        self.0.push(state)?;
        self.1.push(state)?;
        self.2.push(state)?;
        self.3.push(state)?;
        self.4.push(state)?;
        self.5.push(state)?;
        self.6.push(state)?;
        Ok(7)
    }
}

impl<T1, T2, T3, T4, T5, T6, T7, T8> ToLuaValues for (T1, T2, T3, T4, T5, T6, T7, T8)
where
    T1: ToLuaValue,
    T2: ToLuaValue,
    T3: ToLuaValue,
    T4: ToLuaValue,
    T5: ToLuaValue,
    T6: ToLuaValue,
    T7: ToLuaValue,
    T8: ToLuaValue,
{
    fn push_all(self, state: ffi::State) -> Result<ffi::Nresults> {
        self.0.push(state)?;
        self.1.push(state)?;
        self.2.push(state)?;
        self.3.push(state)?;
        self.4.push(state)?;
        self.5.push(state)?;
        self.6.push(state)?;
        self.7.push(state)?;
        Ok(8)
    }
}

impl<T1, T2, T3, T4, T5, T6, T7, T8, T9> ToLuaValues for (T1, T2, T3, T4, T5, T6, T7, T8, T9)
where
    T1: ToLuaValue,
    T2: ToLuaValue,
    T3: ToLuaValue,
    T4: ToLuaValue,
    T5: ToLuaValue,
    T6: ToLuaValue,
    T7: ToLuaValue,
    T8: ToLuaValue,
    T9: ToLuaValue,
{
    fn push_all(self, state: ffi::State) -> Result<ffi::Nresults> {
        self.0.push(state)?;
        self.1.push(state)?;
        self.2.push(state)?;
        self.3.push(state)?;
        self.4.push(state)?;
        self.5.push(state)?;
        self.6.push(state)?;
        self.7.push(state)?;
        self.8.push(state)?;
        Ok(9)
    }
}

impl<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> ToLuaValues
    for (T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)
where
    T1: ToLuaValue,
    T2: ToLuaValue,
    T3: ToLuaValue,
    T4: ToLuaValue,
    T5: ToLuaValue,
    T6: ToLuaValue,
    T7: ToLuaValue,
    T8: ToLuaValue,
    T9: ToLuaValue,
    T10: ToLuaValue,
{
    fn push_all(self, state: ffi::State) -> Result<ffi::Nresults> {
        self.0.push(state)?;
        self.1.push(state)?;
        self.2.push(state)?;
        self.3.push(state)?;
        self.4.push(state)?;
        self.5.push(state)?;
        self.6.push(state)?;
        self.7.push(state)?;
        self.8.push(state)?;
        self.9.push(state)?;
        Ok(10)
    }
}

/*

# Ruby code to generate impls (ToLuaValues)
(1..10).each do |n|
  ns = (1..n)
  ts = (1..n).map{|n| "T#{n}"}
  puts <<EOS
impl<#{ts.join(", ")}> ToLuaValues for (#{ts.join(", ")})
where
    #{ts.map{|t| "#{t}: ToLuaValue,"}.join("\n    ")}
{
    fn push_all(self, state: ffi::State) -> Result<ffi::Nresults> {
        #{ns.map{|n| "self.#{n - 1}.push(state)?;"}.join("\n        ")}
        Ok(#{n})
    }
}

EOS
end

*/
