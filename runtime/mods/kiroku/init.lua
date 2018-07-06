local Event = Elona.require("Event")
local GUI = Elona.require("GUI")

local function on_chara_killed()
   Store.global.killed = Store.global.killed + 1
   if Store.global.report then
      GUI.txt("Killed: " .. Store.global.killed .. " so far. ")
   end
end

local function on_map_initialized()
   GUI.txt("You've killed " .. Store.global.killed .. " things so far. ")
end

local function init_store()
   if not Store.killed then
      Store.global.killed = 0
   end
   Store.global.report = true
end

Event.register(Event.EventKind.CharaKilled, on_chara_killed)
Event.register(Event.EventKind.MapInitialized, on_map_initialized)
Event.register(Event.EventKind.AllModsLoaded, init_store)

return {
   Store = Store
}
