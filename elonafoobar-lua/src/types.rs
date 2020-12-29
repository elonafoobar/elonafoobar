pub type LuaInt = i64;
pub type LuaFloat = f64;

// TODO
pub struct LuaTable {}

pub trait LuaUserdata {
    const NAME: &'static str;
}

pub struct AsLuaInt<T>(pub T);
