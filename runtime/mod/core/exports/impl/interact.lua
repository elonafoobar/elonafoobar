local Action = Elona.require("Action")
local Chara = Elona.require("Chara")
local Event = Elona.require("Event")
local GUI = Elona.require("GUI")
local I18N = Elona.require("I18N")
local World = Elona.require("World")
local Input = Elona.require("Input")
local Item = Elona.require("Item")
local Map = Elona.require("Map")
local table = Elona.require("table")

local interact = {}

local function add_interact_choices(e)
   local function add_choice(key, cb)
      local root = "core.locale.action.interact.choices"
      GUI.txt("add choice " .. key .. " ")
      table.insert(e.choices, { root .. "." .. key, cb })
   end

   if not Chara.is_player(e.target) then
      if Chara.player():get_ailment("Confused") == 0 then
         add_choice("talk", interact.talk)
         add_choice("attack", interact.attack)
      end
      if not e.target:get_flag("IsEscorted") and not e.target:get_flag("IsEscortedInSubQuest") then
         if Chara.is_ally(e.target) then
            add_choice("inventory", interact.inventory)
         else
            add_choice("give", interact.give)
         end
         if e.target:get_flag("IsLivestock") then
            add_choice("bring_out", interact.bring_out)
         end
         if Chara.is_ally(e.target) then
            add_choice("appearance", interact.appearance)
         end
      end
      add_choice("teach_words", interact.teach_words)
      add_choice("change_tone", interact.change_tone)
      if Map.id() ~= "core.show_house" and e.target:get_flag("IsHungOnSandBag") then
         add_choice("release", interact.release)
      end
   end
   add_choice("name", interact.name)
   if World.data.wizard then
      add_choice("info", interact.info)
   end
end

function interact.talk(e)
   return Action.talk_to(e.target)
end

function interact.attack(e)
   GUI.update_screen(false)
   return Action.melee_attack(Chara.player(), e.target)
end

function interact.inventory(e)
   GUI.update_screen(false)
   return Action.manage_inventory(e.target)
end

function interact.give(e)
   return Action.give_item(e.target)
end

function interact.name(e)
   GUI.update_screen(false)
   GUI.txt(I18N.get("core.locale.action.interact.name.prompt", e.target))
   local name = Input.prompt_text(12, 220)
   if name == "" then
      GUI.txt(I18N.get("core.locale.action.interact.name.cancel"))
   else
      e.target.basename = name
      e.target:set_flag("HasOwnName", true)
      GUI.txt(I18N.get("core.locale.action.interact.name.you_named", e.target))
   end
   GUI.update_screen(false)
   return "TurnContinue"
end

function interact.bring_out(e)
   e.target:recruit_as_ally()
   GUI.update_screen(false)
   return "TurnEnd"
end

function interact.info(e)
   return Action.show_investigate_screen(e.target)
end

function interact.teach_words(e)
   GUI.txt(I18N.get("core.locale.action.interact.change_tone.prompt", e.target))
   local tone = Input.prompt_text(20, 360)
   e.target:set_flag("HasCustomTalk", false)
   if tone == "" then
      e.target.tone = ""
   else
      e.target.tone = tone
      GUI.txt(tone, "Cyan")
   end
   GUI.update_screen(false)
   return "TurnContinue"
end

function interact.appearance(e)
   return Action.change_appearance(e.target)
end

function interact.release(e)
   GUI.play_sound("core.build1")
   e.target:set_flag("IsHungOnSandBag", false)
   GUI.txt(I18N.get("core.locale.action.interact.release", e.target))
   Item.create(e.target.position, "core.sand_bag")
   GUI.update_screen(false)
   return "TurnContinue"
end

function interact.change_tone(e)
   return Action.change_tone(e.target)
end

Event.register("core.before_interact_menu", add_interact_choices)

function interact.start(target)
   local result = Event.trigger("core.before_interact_menu", {target = target, choices = {}})
   if result.blocked or type(result.choices) ~= "table" then
      return "TurnContinue"
   end

   local choices = result.choices
   local text = {}
   for _, v in ipairs(choices) do
      text[#text+1] = I18N.get(v[1])
   end

   local index = Input.prompt_choice(text, 200)

   if not index then
      GUI.update_screen(false)
      return "TurnContinue"
   end

   local callback = choices[index][2]
   return callback({target = target}) or "TurnContinue"
end

return interact
