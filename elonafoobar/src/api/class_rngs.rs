use anyhow::Result;
use elonafoobar_log::trace;
use elonafoobar_lua::macros::lua_function;
use elonafoobar_lua::types::{LuaFloat, LuaInt, LuaUserdata};
use elonafoobar_lua::Lua;
use elonafoobar_rand::rngs::DefaultGenerator as RandDefaultGenerator;

const MODULE_NAME: &str = "random.DefaultGenerator";

pub struct DefaultGenerator(RandDefaultGenerator);

impl LuaUserdata for DefaultGenerator {
    const NAME: &'static str = "__native.random.DefaultGenerator";
}

pub fn bind(lua: &mut Lua) -> Result<()> {
    trace!("Bind {} class", DefaultGenerator::NAME);
    lua.bind_class::<DefaultGenerator, _>(|lua| -> Result<()> {
        lua.set_function("new", lua_new)?;
        lua.set_function("rnd", lua_rnd)?;
        lua.set_function("rnd_range", lua_rnd_range)?;
        lua.set_function("rnd_small", lua_rnd_small)?;
        lua.set_function("rnd_range_small", lua_rnd_range_small)?;
        lua.set_function("frnd", lua_frnd)?;
        lua.set_function("frnd_01", lua_frnd_01)?;
        lua.set_function("frnd_range", lua_frnd_range)?;
        lua.set_function("one_in", lua_one_in)?;
        lua.set_function("n_in", lua_n_in)?;
        lua.set_function("percent", lua_percent)?;
        lua.set_function("roll", lua_roll)?;
        lua.set_function("choice", lua_choice)?;
        lua.set_function("sample", lua_sample)?;
        lua.set_function("shuffle", lua_shuffle)?;
        lua.set_function("set_seed", lua_set_seed)?;
        lua.set_function("seed", lua_seed)?;
        lua.set_function("incdec", lua_incdec)?;
        Ok(())
    })
}

#[lua_function]
fn lua_new(seed: LuaInt) -> DefaultGenerator {
    DefaultGenerator(RandDefaultGenerator::with_seed(seed))
}

#[lua_function]
fn lua_rnd(self_: &mut DefaultGenerator, n: LuaInt) -> LuaInt {
    self_.0.rnd(n)
}

#[lua_function]
fn lua_rnd_range(self_: &mut DefaultGenerator, min: LuaInt, max: LuaInt) -> LuaInt {
    self_.0.rnd_range(min, max)
}

#[lua_function]
fn lua_rnd_small(self_: &mut DefaultGenerator, n: LuaInt) -> LuaInt {
    self_.0.rnd_small(n)
}

#[lua_function]
fn lua_rnd_range_small(self_: &mut DefaultGenerator, min: LuaInt, max: LuaInt) -> LuaInt {
    self_.0.rnd_range_small(min, max)
}

#[lua_function]
fn lua_frnd(self_: &mut DefaultGenerator, p: LuaFloat) -> LuaFloat {
    self_.0.frnd(p)
}

#[lua_function]
fn lua_frnd_01(self_: &mut DefaultGenerator) -> LuaFloat {
    self_.0.frnd_01()
}

#[lua_function]
fn lua_frnd_range(self_: &mut DefaultGenerator, min: LuaFloat, max: LuaFloat) -> LuaFloat {
    self_.0.frnd_range(min, max)
}

#[lua_function]
fn lua_one_in(self_: &mut DefaultGenerator, m: LuaInt) -> bool {
    self_.0.one_in(m)
}

#[lua_function]
fn lua_n_in(self_: &mut DefaultGenerator, n: LuaInt, m: LuaInt) -> bool {
    self_.0.n_in(n, m)
}

#[lua_function]
fn lua_percent(self_: &mut DefaultGenerator, p: LuaInt) -> bool {
    self_.0.percent(p)
}

#[lua_function]
fn lua_roll(self_: &mut DefaultGenerator, rolls: LuaInt, faces: LuaInt, bonus: LuaInt) -> LuaInt {
    self_.0.roll(rolls, faces, bonus)
}

#[lua_function]
fn lua_choice() -> LuaInt {
    todo!()
}

#[lua_function]
fn lua_sample() -> LuaInt {
    todo!()
}

#[lua_function]
fn lua_shuffle() -> LuaInt {
    todo!()
}

#[lua_function]
fn lua_set_seed(self_: &mut DefaultGenerator, new_seed: LuaInt) -> LuaInt {
    self_.0.set_seed(new_seed)
}

#[lua_function]
fn lua_seed(self_: &DefaultGenerator) -> LuaInt {
    self_.0.seed()
}

#[lua_function]
fn lua_incdec(self_: &mut DefaultGenerator, n: LuaInt) -> LuaInt {
    self_.0.incdec(n)
}
