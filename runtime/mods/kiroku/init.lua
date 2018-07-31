local Chara = Elona.require("Chara")
local Event = Elona.require("Event")
local GUI = Elona.require("GUI")

local function on_chara_killed(_victim, killer)
   if killer and Chara.is_player(killer) then
      Store.global.killed = Store.global.killed + 1
      if Store.global.report then
         GUI.txt("Killed: " .. Store.global.killed .. " so far. ")
      end
   end
end

local function report()
   print(Elona.require("Debug").inspect.inspect(Store.global))
   if Store.global.report then
      GUI.txt("You've killed " .. Store.global.killed .. " things so far. ")
   end
end

local function init_store()
   print(Elona.require("Debug").inspect.inspect(Store.global))
   if not Store.global.killed then
      Store.global.killed = 0
   end
   Store.global.report = true
end

Event.register(Event.EventKind.CharaKilled, on_chara_killed)
Event.register(Event.EventKind.MapInitialized, report)
Event.register(Event.EventKind.GameSaved, report)
Event.register(Event.EventKind.GameLoaded, report)
Event.register(Event.EventKind.GameInitialized, init_store)
