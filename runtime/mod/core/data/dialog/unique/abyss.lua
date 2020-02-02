local Chara = Elona.game.Chara
local GUI = Elona.game.GUI
local Math = Elona.game.Math
local I18N = Elona.game.I18N
local Item = Elona.game.Item
local World = Elona.game.World
local table = Elona.game.table

local common = require("data/dialog/common")

local function start_trial()
    World.data.joining_thieves_guild = 1
    GUI.show_journal_update_message()
end

local function join_guild()
    World.data.ranks[8] = 10000

    World.join_guild("thieves")

    GUI.txt(I18N.get("core.quest.completed"))
    GUI.play_sound("core.complete1")
    GUI.show_journal_update_message()
    GUI.txt(I18N.get("core.talk.unique.abyss.nonmember.joined"), "Orange")
end

local function move_self(t)
   t.speaker:move_to(17, 17)
   t.speaker.initial_position.x = 17
   t.speaker.initial_position.y = 17
end

local function update_quota()
   World.data.thieves_guild_quota_recurring = true
   World.data.thieves_guild_quota = (10000 - World.data.ranks[8]) * 6 + 1000
   GUI.show_journal_update_message()
end

local function receive_reward()
   World.data.thieves_guild_quota_recurring = false
   Item.create(Chara.player().position, {objlv = 51 - World.data.ranks[8] / 200, flttypemajor = 60000})
   Item.create(Chara.player().position, "core.gold_piece", 10000 - World.data.ranks[8] + 1000)
   Item.create(Chara.player().position, "core.platinum_coin", Math.clamp(3 - World.data.ranks[8] / 3000, 1, 3))

   common.quest_completed()

   World.modify_ranking(8, 500, 8)
end

return {
   id = "abyss",
   root = "core.talk.unique.abyss",
   nodes = {
      __start = function()
         if World.belongs_to_guild("thieves") == false then
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
         if World.data.joining_thieves_guild == 0 then
            return "guild_join_start"
         elseif World.data.left_bill <= 4 then
            return "guild_join_waiting"
         end

         return "guild_join_finish"
      end,
      guild_join_start = {
         text = {
            {"nonmember.want_to_join._0"},
            start_trial,
            {"nonmember.want_to_join._1"},
         },
         choices = {
            {"__start", "__MORE__"},
         }
      },
      guild_join_waiting = {
         text = {
            {"nonmember.quota"},
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
            if not World.data.thieves_guild_quota_recurring then
               table.insert(choices, {"guild_quota_new", "core.talk.unique.lexus.member.choices.new_quota"})
            else
               table.insert(choices, {"guild_quota_check", "core.talk.unique.lexus.member.choices.report_quota"})
            end
            table.insert(choices, {"__END__", "__BYE__"})

            return choices
         end
      },
      guild_quota_new = {
         text = {
            update_quota,
            {"member.new_quota", args = function() return {World.data.thieves_guild_quota} end},
         },
         choices = {
            {"__start", "__MORE__"},
         }
      },
      guild_quota_check = function()
         if World.data.thieves_guild_quota > 0 then
            return "guild_quota_waiting"
         end
         return "guild_quota_finish"
      end,
      guild_quota_waiting = {
         text = {
            {"core.talk.unique.lexus.member.report_quota.waiting"},
         },
         choices = {
            {"__start", "__MORE__"},
         }
      },
      guild_quota_finish = {
         text = {
            receive_reward,
            {"core.talk.unique.lexus.member.report_quota.end"},
         },
      },
   }
}
