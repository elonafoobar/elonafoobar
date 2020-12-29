use crate::types::{LuaFloat, LuaInt};
use anyhow::{bail, format_err, Result};
use elonafoobar_lua_sys as sys;
use elonafoobar_utils as utils;
use std::ffi::{c_void, CStr, CString};
use std::fs::File;
use std::io::{BufRead, BufReader};
use std::mem::size_of;
pub use std::os::raw::{c_char, c_int, c_ulong};
use std::path::Path;
use std::ptr::NonNull;

pub use sys::lua_State;
pub type State = NonNull<lua_State>;

pub type Nresults = c_int;

#[allow(non_snake_case)]
pub fn luaL_newstate() -> Result<State> {
    let state = unsafe { sys::luaL_newstate() };
    NonNull::new(state).ok_or_else(|| format_err!("failed to create a new Lua state"))
}

#[allow(non_snake_case)]
pub fn luaL_openlibs(state: State) {
    unsafe {
        sys::luaL_openlibs(state.as_ptr());
    }
}

pub fn lua_getglobal(state: State, name: &str, expected_type: c_int) -> Result<()> {
    let name_c = CString::new(name)?;
    let actual_type = unsafe { sys::lua_getglobal(state.as_ptr(), name_c.as_ptr()) };

    if actual_type == expected_type {
        Ok(())
    } else if actual_type == LUA_TNIL {
        Err(format_err!("global variable '{}' not found", name))
    } else {
        Err(format_err!(
            "global variable '{}' is not {}, but {}",
            name,
            lua_typename(expected_type),
            lua_typename(actual_type)
        ))
    }
}

pub fn lua_pushstring(state: State, s: &str) -> Result<()> {
    let state = state.as_ptr();

    let s_cstring = CString::new(s)?;
    let allocated_ptr = unsafe { sys::lua_pushstring(state, s_cstring.as_ptr()) };

    if allocated_ptr.is_null() {
        Err(format_err!("failed to push a string '{}'", s))
    } else {
        Ok(())
    }
}

pub fn lua_pushinteger(state: State, value: LuaInt) {
    unsafe {
        sys::lua_pushinteger(state.as_ptr(), value);
    }
}

pub fn lua_pushnumber(state: State, value: LuaFloat) {
    unsafe {
        sys::lua_pushnumber(state.as_ptr(), value);
    }
}

pub fn lua_pushboolean(state: State, value: bool) {
    unsafe {
        sys::lua_pushboolean(state.as_ptr(), if value { 1 } else { 0 });
    }
}

pub fn lua_pushlightuserdata(state: State, raw_pointer: *mut c_void) {
    unsafe {
        sys::lua_pushlightuserdata(state.as_ptr(), raw_pointer);
    }
}

pub fn lua_pushcfunction(state: State, c_function_pointer: extern "C" fn(*mut lua_State) -> c_int) {
    lua_pushcclosure(state, c_function_pointer, 0);
}

pub fn lua_pushcclosure(
    state: State,
    c_function_pointer: extern "C" fn(*mut lua_State) -> c_int,
    upvalues: c_int,
) {
    unsafe {
        sys::lua_pushcclosure(state.as_ptr(), Some(c_function_pointer), upvalues);
    }
}

pub fn lua_pushnil(state: State) {
    unsafe {
        sys::lua_pushnil(state.as_ptr());
    }
}

pub fn lua_pop_one(state: State) {
    unsafe {
        sys::lua_settop(state.as_ptr(), -2);
    }
}

pub fn lua_rawset(state: State, idx: c_int) {
    unsafe {
        sys::lua_rawset(state.as_ptr(), idx);
    }
}

pub fn lua_rawseti(state: State, idx: c_int, item_index: LuaInt) {
    unsafe {
        sys::lua_rawseti(state.as_ptr(), idx, item_index);
    }
}

pub fn lua_rawget(state: State, idx: c_int) {
    unsafe {
        sys::lua_rawget(state.as_ptr(), idx);
    }
}

pub fn lua_swap(state: State) {
    unsafe {
        sys::lua_rotate(state.as_ptr(), -2, 1);
    }
}

pub fn lua_pcall(state: State, nargs: c_int, nresults: c_int) -> Result<()> {
    let state = state.as_ptr();

    let result = unsafe { sys::lua_pcallk(state, nargs, nresults, 0, 0, None) };
    if result == LUA_OK {
        return Ok(());
    }

    // TODO more user-friendly error message
    let error_message =
        unsafe { CStr::from_ptr(sys::lua_tolstring(state, -1, std::ptr::null_mut())) }.to_str()?;
    match result {
        LUA_ERRRUN => Err(format_err!("a runtime error in pcall: {}", error_message)),
        LUA_ERRMEM => Err(format_err!(
            "memory allocation error in pcall: {}",
            error_message
        )),
        LUA_ERRERR => Err(format_err!(
            "error while running error handler in pcall: {}",
            error_message
        )),
        _ => Err(format_err!("a fatal error in pcall: {}", error_message)),
    }
}

pub fn lua_toboolean(state: State, idx: c_int) -> bool {
    let n = unsafe { sys::lua_toboolean(state.as_ptr(), idx) };
    n != 0
}

pub fn lua_tointeger(state: State, idx: c_int) -> Result<LuaInt> {
    let mut succeeded = 0;
    let value = unsafe { sys::lua_tointegerx(state.as_ptr(), idx, &mut succeeded as *mut _) };
    if succeeded == 0 {
        Err(format_err!("not an integer")) // TODO
    } else {
        Ok(value)
    }
}

pub fn lua_tonumber(state: State, idx: c_int) -> Result<LuaFloat> {
    let mut succeeded = 0;
    let value = unsafe { sys::lua_tonumberx(state.as_ptr(), idx, &mut succeeded as *mut _) };
    if succeeded == 0 {
        Err(format_err!("not a number")) // TODO
    } else {
        Ok(value)
    }
}

pub fn lua_tostring<'a>(state: State, idx: c_int) -> Result<&'a str> {
    let mut len = 0u64;
    let value = unsafe { sys::lua_tolstring(state.as_ptr(), idx, &mut len as *mut _) };
    let _ = len; // TODO
    Ok(unsafe { CStr::from_ptr(value) }.to_str().expect("TODO"))
}

#[allow(non_snake_case)]
pub fn luaL_testudata<'a, T>(state: State, idx: c_int, userdata_name: &str) -> Result<&'a T> {
    let userdata_name = CString::new(userdata_name)?;
    let ptr = unsafe { sys::luaL_testudata(state.as_ptr(), idx, userdata_name.as_ptr()) };
    let ptr = ptr as *mut _;

    let ptr = NonNull::new(ptr).ok_or_else(|| format_err!("touserdata") /* TODO */)?;

    let r = unsafe { ptr.as_ref() };
    Ok(unsafe { &*(r as *const std::ffi::c_void as *const T) })
}

#[allow(non_snake_case)]
pub fn luaL_testudata_mut<'a, T>(
    state: State,
    idx: c_int,
    userdata_name: &str,
) -> Result<&'a mut T> {
    let userdata_name = CString::new(userdata_name)?;
    let ptr = unsafe { sys::luaL_testudata(state.as_ptr(), idx, userdata_name.as_ptr()) };
    let ptr = ptr as *mut _;

    let mut ptr = NonNull::new(ptr).ok_or_else(|| format_err!("touserdata") /* TODO */)?;

    let r = unsafe { ptr.as_mut() };
    Ok(unsafe { &mut *(r as *mut std::ffi::c_void as *mut T) })
}

pub fn lua_touserdata(state: State, idx: c_int) -> *mut c_void {
    unsafe { sys::lua_touserdata(state.as_ptr(), idx) }
}

pub fn lua_newtable(state: State) {
    lua_createtable(state, 0, 0);
}

pub fn lua_createtable(state: State, narr: c_int, nrec: c_int) {
    unsafe {
        sys::lua_createtable(state.as_ptr(), narr, nrec);
    }
}

pub fn set_global(state: State, name: &str) -> Result<()> {
    let name = CString::new(name)?;
    unsafe {
        sys::lua_setglobal(state.as_ptr(), name.as_ptr());
    }
    Ok(())
}

pub fn get_userdata_metatable(state: State, userdata_name: &str) -> Result<()> {
    let userdata_name = CString::new(userdata_name)?;
    unsafe {
        sys::lua_getfield(
            state.as_ptr(),
            sys::LUA_REGISTRYINDEX,
            userdata_name.as_ptr(),
        );
    }
    Ok(())
}

pub fn new_metatable(state: State, userdata_name: &str) -> Result<()> {
    let userdata_name = CString::new(userdata_name)?;
    unsafe {
        sys::luaL_newmetatable(state.as_ptr(), userdata_name.as_ptr());
    }
    Ok(())
}

pub fn lua_newuserdata(state: State, size: usize) -> Result<*mut c_void> {
    let ptr = unsafe { sys::lua_newuserdatauv(state.as_ptr(), size as u64, 1) };
    if ptr.is_null() {
        Err(format_err!("failed to allocate userdata (size = {})", size))
    } else {
        Ok(ptr)
    }
}

pub fn lua_newuserdata_of<T>(state: State) -> Result<NonNull<T>> {
    let ptr = lua_newuserdata(state, size_of::<T>())?;
    let ptr = ptr as *mut _;
    Ok(NonNull::new(ptr).expect("todo"))
}

#[allow(non_snake_case)]
pub fn luaL_setmetatable(state: State, userdata_name: &str) -> Result<()> {
    let userdata_name = CString::new(userdata_name)?;
    unsafe { sys::luaL_setmetatable(state.as_ptr(), userdata_name.as_ptr()) }
    Ok(())
}

pub fn check_nargs(state: State, expected_nargs: c_int) -> Result<()> {
    let actual_nargs = unsafe { sys::lua_gettop(state.as_ptr()) };
    if expected_nargs <= actual_nargs {
        Ok(())
    } else {
        Err(format_err!("check_nargs")) // TODO
    }
}

pub fn get_debug_info_source(state: State, level: c_int) -> Result<String> {
    unsafe {
        let getinfo_flag = CString::new("S")?;

        let mut ar = sys::lua_Debug {
            event: 0,
            name: std::ptr::null(),
            namewhat: std::ptr::null(),
            what: std::ptr::null(),
            source: std::ptr::null(),
            srclen: 0,
            currentline: 0,
            linedefined: 0,
            lastlinedefined: 0,
            nups: 0,
            nparams: 0,
            isvararg: 0,
            istailcall: 0,
            ftransfer: 0,
            ntransfer: 0,
            short_src: [0; 60],
            i_ci: std::ptr::null_mut(),
        };
        let result = sys::lua_getstack(state.as_ptr(), level, &mut ar as *mut _);
        if result == 0 {
            return Err(format_err!("TODO"));
        }
        let result = sys::lua_getinfo(state.as_ptr(), getinfo_flag.as_ptr(), &mut ar as *mut _);
        if result == 0 {
            return Err(format_err!("TODO"));
        }

        Ok(CStr::from_ptr(ar.source).to_str().expect("TODO").to_owned())
    }
}

pub fn lua_load(state: State, path: &Path) -> Result<()> {
    extern "C" fn reader(
        _state: *mut sys::lua_State,
        data: *mut c_void,
        read_byte: *mut c_ulong,
    ) -> *const c_char {
        let buf_reader = data as *mut BufReader<File>;
        let mut buf_reader = NonNull::new(buf_reader).expect("todo");
        let buf_reader = unsafe { buf_reader.as_mut() };
        let mut read_byte = NonNull::new(read_byte).expect("todo");
        let read_byte = unsafe { read_byte.as_mut() };
        let (ret, len) = match buf_reader.fill_buf() {
            Ok(inner_buffer) => {
                if inner_buffer.is_empty() {
                    (std::ptr::null(), 0)
                } else {
                    (
                        unsafe { CStr::from_bytes_with_nul_unchecked(inner_buffer).as_ptr() },
                        inner_buffer.len(),
                    )
                }
            }
            Err(_) => (std::ptr::null(), 0),
        };
        *read_byte = len as _;
        buf_reader.consume(len);
        ret
    }

    let load_mode_flag = CString::new("t")?;
    let chunkname = utils::path::path_to_str(path);
    let chunkname = CString::new(chunkname)?;

    let file = File::open(path)?;
    let mut buf_reader = BufReader::new(file);
    utils::io::skip_bom(&mut buf_reader)?;

    unsafe {
        let data = &mut buf_reader as *mut BufReader<_> as *mut c_void;

        let load_result = sys::lua_load(
            state.as_ptr(),
            Some(reader),
            data,
            chunkname.as_ptr(),
            load_mode_flag.as_ptr(),
        );
        match load_result {
            LUA_OK => Ok(()),
            LUA_ERRSYNTAX => bail!("Syntax error"),
            LUA_ERRMEM => bail!("Memory error"),
            _ => bail!("a fatal error in Lua"),
        }
    }
}

#[allow(non_snake_case)]
pub fn luaL_error(state: State, error_message: &str) {
    // TODO
    let _ignore_errors = lua_pushstring(state, error_message);
    unsafe {
        sys::lua_error(state.as_ptr());
        // ^ never returns
    }
}

pub fn lua_typename(ty: c_int) -> &'static str {
    const TYPES: &[&str] = &[
        "nil", "boolean", "userdata", "number", "string", "table", "function", "userdata", "thread",
    ];
    if 0 <= ty && ty < TYPES.len() as c_int {
        TYPES[ty as usize]
    } else {
        "unknown"
    }
}

pub const LUA_TNIL: c_int = sys::LUA_TNIL as c_int;
// pub const LUA_TBOOLEAN: c_int = sys::LUA_TBOOLEAN as c_int;
// pub const LUA_TLIGHTUSERDATA: c_int = sys::LUA_TLIGHTUSERDATA as c_int;
// pub const LUA_TNUMBER: c_int = sys::LUA_TNUMBER as c_int;
// pub const LUA_TSTRING: c_int = sys::LUA_TSTRING as c_int;
pub const LUA_TTABLE: c_int = sys::LUA_TTABLE as c_int;
// pub const LUA_TFUNCTION: c_int = sys::LUA_TFUNCTION as c_int;
// pub const LUA_TUSERDATA: c_int = sys::LUA_TUSERDATA as c_int;
// pub const LUA_TTHREAD: c_int = sys::LUA_TTHREAD as c_int;
pub const LUA_OK: c_int = sys::LUA_OK as c_int;
pub const LUA_ERRSYNTAX: c_int = sys::LUA_ERRSYNTAX as c_int;
pub const LUA_ERRRUN: c_int = sys::LUA_ERRRUN as c_int;
pub const LUA_ERRMEM: c_int = sys::LUA_ERRMEM as c_int;
pub const LUA_ERRERR: c_int = sys::LUA_ERRERR as c_int;
pub const LUA_REGISTRYINDEX: c_int = sys::LUA_REGISTRYINDEX;
