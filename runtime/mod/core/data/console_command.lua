local Chara = require("core.Chara")
local Config = require("core.Config")
local Console = require("core.Console")
local data = require("core.data")
local Debug = require("core.Debug")
local Internal = require("core.Internal")
local Wish = require("core.Wish")



data.define_prototype("console_command")
data.add(
   "core.console_command",
   {
      history = {
         on_execute = function()
            local history = Console.get_history()
            local n = history:count()
            if n >= 10 then
               n = 10
            end
            for i = 1, n do
               local idx = history:count() - n + i
               local entry = history:get(idx)
               Console.print("  "..tostring(idx).."  "..entry)
            end
         end,
      },
      echo = {
         on_execute = function(s)
            Console.print(tostring(s))
         end,
      },
      help = {
         on_execute = function()
            local all_commands = {}
            for id, _ in pairs(data.get_table("core.console_command")) do
               all_commands[#all_commands+1] = id
            end
            table.sort(all_commands)
            for _, command in ipairs(all_commands) do
               Console.print(command)
            end
         end,
      },
      ls = {
         on_execute = function()
            local mods = Internal.get_enabled_mods()
            for _, mod in ipairs(mods) do
               Console.print(mod)
            end
         end,
      },
      wizard = {
         on_execute = function()
            Debug.enable_wizard()
            Console.print("Wizard mode activated.")
         end,
      },
      voldemort = {
         on_execute = function()
            if not Debug.is_wizard() then
               Debug.enable_wizard()
               Console.print("Wizard mode activated.")
            end

            -- TODO generalize more
            Config.set("core.wizard.can_cast_all_spells", true)
            Config.set("core.wizard.can_unlock_all_keys", true)
            Config.set("core.wizard.no_hp_damage", true)
            Config.set("core.wizard.no_hungry", true)
            Config.set("core.wizard.no_mp_damage", true)
            Config.set("core.wizard.no_sleepy", true)
            Config.set("core.wizard.no_sp_damage", true)
            Config.set("core.wizard.no_spellstock_cost", true)
            Config.set("core.wizard.skip_random_event", true)

            Console.print("I AM LORD VOLDEMORT.")
         end,
      },
      muggle = {
         wizard_only = true,
         on_execute = function()
            Debug.disable_wizard()
            Console.print("Wizard mode inactivated.")
         end,
      },
      wish = {
         wizard_only = true,
         on_execute = function(wish, num)
            num = tonumber(num or 1)
            if num < 1 then
               num = 1
            end
            for _i = 1, num do
               Wish.wish(wish)
            end
         end,
      },
      gain_spell = {
         wizard_only = true,
         on_execute = function()
            Internal.gain_spell()
         end,
      },
      gain_spact = {
         wizard_only = true,
         on_execute = function()
            Internal.gain_spact()
         end,
      },
      gain_exp = {
         wizard_only = true,
         on_execute = function(exp)
            exp = tonumber(exp or 1000000000)
            Internal.gain_exp(exp)
         end,
      },
      gain_fame = {
         wizard_only = true,
         on_execute = function(fame)
            fame = tonumber(fame or 1000000)
            Chara.player().fame = Chara.player().fame + fame
         end,
      },
   }
)
