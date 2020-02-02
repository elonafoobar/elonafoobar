-- local Data = Elona.game.Data
--
-- local spell = Data.get('core.ability', 'load_order.expecto_patronum')
-- spell.cost = 100

-- work-around: Data API internally refers to global LuaEnv, elona::lua::lua,
-- but test code creates isolated LuaEnv. As two LuaEnv are different, the
-- above code which calls Data.get() does not work properly.
local spell = data.raw['core.ability']['load_order.expecto_patronum']
spell.cost = 100
