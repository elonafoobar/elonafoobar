local Chara = Elona.require("Chara")
local Data = Elona.require("Data")
local Internal = Elona.require("Internal")
local Rand = Elona.require("Rand")
local GUI = Elona.require("GUI")
local Math = Elona.require("Math")
local I18N = Elona.require("I18N")
local Item = Elona.require("Item")
local World = Elona.require("World")
local table = Elona.require("table")
local string = Elona.require("string")

local common = require("data/dialog/common")

local function start_trial()
    World.data.joining_fighters_guild = 1
    GUI.show_journal_update_message()
    World.data.fighters_guild_target = Internal.generate_fighters_guild_target(10)
    World.data.fighters_guild_quota = 15
end

local function join_guild()
    World.data.ranks[8] = 10000

    World.join_guild("fighters")

    GUI.txt(I18N.get("core.locale.quest.completed"))
    GUI.play_sound("core.complete1")
    GUI.show_journal_update_message()
    GUI.txt(I18N.get("core.locale.talk.unique.doria.nonmember.joined"), "Orange")
end

local function move_self(t)
   t.speaker:move_to(29, 2)
   t.speaker.initial_position.x = 29
   t.speaker.initial_position.y = 2
end

local function update_quota()
   World.data.fighters_guild_target = Internal.generate_fighters_guild_target(Chara.player().level + 10)
   World.data.fighters_guild_quota = 2 + Rand.between(2, 5)
   World.data.fighters_guild_quota_recurring = true
   GUI.show_journal_update_message()
end

local function receive_reward()
   World.data.fighters_guild_quota_recurring = false
   Item.create(Chara.player().position, {objlv = 51 - World.data.ranks[8] / 200, quality = "Good", flttypemajor = 10000})
   Item.create(Chara.player().position, "core.gold_piece", 10000 - World.data.ranks[8] + 1000)
   Item.create(Chara.player().position, "core.platinum_coin", Math.clamp(4 - World.data.ranks[8] / 2500, 1, 4))

   common.quest_completed()

   World.modify_ranking(8, 500, 8)
end

local function extract_id_parts(key)
   return string.match(key, "(.+)%.(.+)")
end

local function quota_args()
   local id = Data.get_id_by_legacy("core.chara", World.data.fighters_guild_target)
   local mod_id, instance_id = extract_id_parts(id)
   local name = I18N.get(mod_id .. ".locale.chara." .. instance_id .. ".name")
   return {World.data.fighters_guild_quota, name}
end

return {
   id = "doria",
   root = "core.locale.talk.unique.doria",
   nodes = {
      __start = function()
         if World.belongs_to_guild("fighters") == false then
            return "guild_nonmember"
         end

         return "guild_member"
      end,

      guild_nonmember = {
         text = {
            {"nonmember.dialog"},
         },
         choices = {
            {"guild_desc", "nonmember.choices.tell_me_about"},
            {"guild_join_check", "nonmember.choices.want_to_join"},
            {"__END__", "__BYE__"}
         }
      },
      guild_desc = {
         text = {
            {"nonmember.tell_me_about"},
         },
         choices = {
            {"__start", "__MORE__"},
         }
      },
      guild_join_check = function()
         if World.data.joining_fighters_guild == 0 then
            return "guild_join_start"
         elseif World.data.fighters_guild_quota > 0 then
            return "guild_join_waiting"
         end

         return "guild_join_finish"
      end,
      guild_join_start = {
         text = {
            {"nonmember.want_to_join._0"},
            start_trial,
            {"nonmember.want_to_join._1", args = quota_args},
         },
         choices = {
            {"__start", "__MORE__"},
         }
      },
      guild_join_waiting = {
         text = {
            {"nonmember.quota", args = quota_args},
         },
         choices = {
            {"__start", "__MORE__"},
         }
      },
      guild_join_finish = {
         text = {
            {"nonmember.end._0"},
            join_guild,
            {"nonmember.end._1"},
         },
         on_finish = move_self,
      },

      guild_member = {
         text = {
            move_self,
            {"member.dialog", args = function() return {World.ranking_title(8), Chara.player().basename} end},
         },
         choices = function()
            local choices = {}
            if not World.data.fighters_guild_quota_recurring then
               table.insert(choices, {"guild_quota_new", "core.locale.talk.unique.lexus.member.choices.new_quota"})
            else
               table.insert(choices, {"guild_quota_check", "core.locale.talk.unique.lexus.member.choices.report_quota"})
            end
            table.insert(choices, {"__END__", "__BYE__"})

            return choices
         end
      },
      guild_quota_new = {
         text = {
            update_quota,
            {"member.new_quota", args = quota_args},
         },
         choices = {
            {"__start", "__MORE__"},
         }
      },
      guild_quota_check = function()
         if World.data.fighters_guild_quota > 0 then
            return "guild_quota_waiting"
         end
         return "guild_quota_finish"
      end,
      guild_quota_waiting = {
         text = {
            {"core.locale.talk.unique.lexus.member.report_quota.waiting"},
         },
         choices = {
            {"__start", "__MORE__"},
         }
      },
      guild_quota_finish = {
         text = {
            receive_reward,
            {"core.locale.talk.unique.lexus.member.report_quota.end"},
         },
      },
   }
}
