pub type LuaInt = i64;
pub type LuaFloat = f64;

// TODO
pub struct LuaTable {}

pub trait LuaUserdata {
    const NAME: &'static str;
}

pub struct AsLuaInt<T>(pub T);

pub struct Warn<T> {
    pub value: T,
    pub warning: Option<String>,
}

impl<T> Warn<T> {
    pub fn success(value: T) -> Self {
        Self {
            value,
            warning: None,
        }
    }

    pub fn with_warning(value: T, warning: impl ToString) -> Self {
        Self {
            value,
            warning: Some(warning.to_string()),
        }
    }
}

impl<E: ToString> From<Result<(), E>> for Warn<()> {
    fn from(result: Result<(), E>) -> Self {
        match result {
            Ok(_) => Warn::success(()),
            Err(err) => Warn::with_warning((), err.to_string()),
        }
    }
}
