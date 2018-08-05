local Event = Elona.require("Event")
local GUI = Elona.require("GUI")
local I18N = Elona.require("I18N")
-- local Registry = Elona.require("Registry")

local function on_chara_killed()
   Store.global.killed = Store.global.killed + 1
   if Store.global.report then
      GUI.txt(I18N.get("kiroku.locale.on_killed", Store.global.killed))
   end
end

local function on_map_initialized()
   if Store.global.report then
      GUI.txt(I18N.get("kiroku.locale.report", Store.global.killed))

      -- local something = Registry.get_table("kiroku", "test").kiroku.something
      -- GUI.txt("Test: " .. something.blah .. " : " .. something.color)
   end
end

local function init_store()
   if not Store.global.killed then
      Store.global.killed = 0
   end
   Store.global.report = false
end

Event.register(Event.EventKind.CharaKilled, on_chara_killed)
Event.register(Event.EventKind.MapInitialized, on_map_initialized)
Event.register(Event.EventKind.AllModsLoaded, init_store)

return {
   Store = Store
}
