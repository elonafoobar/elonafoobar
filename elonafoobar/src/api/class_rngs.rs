use anyhow::Result;
use elonafoobar_log::trace;
use elonafoobar_lua::types::{LuaFloat, LuaInt, LuaUserdata};
use elonafoobar_lua::Lua;
use elonafoobar_rand::rngs::DefaultGenerator as RandDefaultGenerator;

pub struct DefaultGenerator(RandDefaultGenerator);

impl LuaUserdata for DefaultGenerator {
    const NAME: &'static str = "_native_.random.rngs.DefaultGenerator";
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

fn lua_new(args: LuaInt) -> Result<DefaultGenerator> {
    trace!("_native_.random.rngs.DefaultGenerator.new()");

    let seed = args;
    Ok(DefaultGenerator(RandDefaultGenerator::with_seed(seed)))
}

fn lua_rnd(args: (&mut DefaultGenerator, LuaInt)) -> Result<LuaInt> {
    trace!("_native_.random.rngs.DefaultGenerator:rnd()");

    let (self_, n) = args;
    Ok(self_.0.rnd(n))
}

fn lua_rnd_range(args: (&mut DefaultGenerator, LuaInt, LuaInt)) -> Result<LuaInt> {
    trace!("_native_.random.rngs.DefaultGenerator:rnd_range()");

    let (self_, min, max) = args;
    Ok(self_.0.rnd_range(min, max))
}

fn lua_rnd_small(args: (&mut DefaultGenerator, LuaInt)) -> Result<LuaInt> {
    trace!("_native_.random.rngs.DefaultGenerator:rnd_small()");

    let (self_, n) = args;
    Ok(self_.0.rnd_small(n))
}

fn lua_rnd_range_small(args: (&mut DefaultGenerator, LuaInt, LuaInt)) -> Result<LuaInt> {
    trace!("_native_.random.rngs.DefaultGenerator:rnd_range_small()");

    let (self_, min, max) = args;
    Ok(self_.0.rnd_range_small(min, max))
}

fn lua_frnd(args: (&mut DefaultGenerator, LuaFloat)) -> Result<LuaFloat> {
    trace!("_native_.random.rngs.DefaultGenerator:frnd()");

    let (self_, p) = args;
    Ok(self_.0.frnd(p))
}

fn lua_frnd_01(args: &mut DefaultGenerator) -> Result<LuaFloat> {
    trace!("_native_.random.rngs.DefaultGenerator:frnd_01()");

    let self_ = args;
    Ok(self_.0.frnd_01())
}

fn lua_frnd_range(args: (&mut DefaultGenerator, LuaFloat, LuaFloat)) -> Result<LuaFloat> {
    trace!("_native_.random.rngs.DefaultGenerator:frnd_range()");

    let (self_, min, max) = args;
    Ok(self_.0.frnd_range(min, max))
}

fn lua_one_in(args: (&mut DefaultGenerator, LuaInt)) -> Result<bool> {
    trace!("_native_.random.rngs.DefaultGenerator:one_in()");

    let (self_, m) = args;
    Ok(self_.0.one_in(m))
}

fn lua_n_in(args: (&mut DefaultGenerator, LuaInt, LuaInt)) -> Result<bool> {
    trace!("_native_.random.rngs.DefaultGenerator:n_in()");

    let (self_, n, m) = args;
    Ok(self_.0.n_in(n, m))
}

fn lua_percent(args: (&mut DefaultGenerator, LuaInt)) -> Result<bool> {
    trace!("_native_.random.rngs.DefaultGenerator:percent()");

    let (self_, p) = args;
    Ok(self_.0.percent(p))
}

fn lua_roll(args: (&mut DefaultGenerator, LuaInt, LuaInt, LuaInt)) -> Result<LuaInt> {
    trace!("_native_.random.rngs.DefaultGenerator:roll()");

    let (self_, rolls, faces, bonus) = args;
    Ok(self_.0.roll(rolls, faces, bonus))
}

fn lua_choice(_args: (&mut DefaultGenerator, LuaInt)) -> Result<LuaInt> {
    trace!("_native_.random.rngs.DefaultGenerator:choice()");
    todo!()
}

fn lua_sample(_args: (&mut DefaultGenerator, LuaInt)) -> Result<LuaInt> {
    trace!("_native_.random.rngs.DefaultGenerator:sample()");
    todo!()
}

fn lua_shuffle(_args: (&mut DefaultGenerator, LuaInt)) -> Result<LuaInt> {
    trace!("_native_.random.rngs.DefaultGenerator:shuffle()");
    todo!()
}

fn lua_set_seed(args: (&mut DefaultGenerator, LuaInt)) -> Result<LuaInt> {
    trace!("_native_.random.rngs.DefaultGenerator:set_seed()");

    let (self_, new_seed) = args;
    Ok(self_.0.set_seed(new_seed))
}

fn lua_seed(args: &DefaultGenerator) -> Result<LuaInt> {
    trace!("_native_.random.rngs.DefaultGenerator:seed()");

    let self_ = args;
    Ok(self_.0.seed())
}

fn lua_incdec(args: (&mut DefaultGenerator, LuaInt)) -> Result<LuaInt> {
    trace!("_native_.random.rngs.DefaultGenerator:incdec()");

    let (self_, n) = args;
    Ok(self_.0.incdec(n))
}
