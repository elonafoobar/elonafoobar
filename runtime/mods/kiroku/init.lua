local Enums = Elona.require("Enums")
local Event = Elona.require("Event")
local GUI = Elona.require("GUI")
local I18N = Elona.require("I18N")
-- local Registry = Elona.require("Registry")

local function report()
   GUI.txt(I18N.get("kiroku.locale.report", Store.global.killed))

   -- local something = Registry.get_table("kiroku", "test").kiroku.something
   -- GUI.txt("Test: " .. something.blah .. " : " .. something.color)
end

local function on_chara_killed()
   Store.global.killed = Store.global.killed + 1
   if Store.global.report then
      GUI.txt(I18N.get("kiroku.locale.on_killed", Store.global.killed))
   end
end

local function init_store()
   if not Store.global.killed then
      Store.global.killed = 0
   end
   Store.global.report = false
end

local Exports = {}

Exports.on_use = {}

function Exports.on_use.counter(item, chara)
   GUI.txtef(Enums.Color.Gold)
   GUI.txt(item.name .. " : " .. chara.name)
   report()
   return true
end

Event.register(Event.EventKind.CharaKilled, on_chara_killed)
Event.register(Event.EventKind.MapInitialized, function() if Store.global.report then report() end end)
Event.register(Event.EventKind.AllModsLoaded, init_store)

return {
   Store = Store,
   Exports = Exports
}
