local Chara = Elona.require("Chara")
local Pos = Elona.require("Pos")
local Magic = Elona.require("Magic")
local Event = Elona.require("Event")
local GUI = Elona.require("GUI")
local Game = Elona.require("Game")
local I18n = Elona.require("I18n")
local Internal = Elona.require("Internal")
local Item = Elona.require("Item")
local Map = Elona.require("Map")
local Math = Elona.require("Math")
local Rand = Elona.require("Rand")
local Skill = Elona.require("Skill")
local World = Elona.require("World")
local table = Elona.require("table")

local function modify_impression(speaker)
   if speaker.interest > 0 then
      if speaker.relation ~= "Ally" then
         if not Chara.is_ally(speaker) then
            if Rand.one_in(3) then
               if speaker.impression < 100 then
                  if Rand.rnd(Skill.level(Chara.player(), 17)) > 10 then
                     speaker:modify_impression(Rand.rnd(3))
                  else
                     speaker:modify_impression(Rand.rnd(3) * -1)
                  end
               end
            end
            speaker.interest = speaker.interest - Rand.rnd(30)
            speaker.time_interest_revive = World.time() + 8
         end
      end
   end
end

local function meet_guest()
   if Game.data.left_turns_of_timestop == 0 then
      Event.add(25)
   end
   return "__end__"
end

local function do_not_meet_guest(t)
   Game.data.number_of_waiting_guests = Game.data.number_of_waiting_guests - 1
   t.more { "core.locale.talk.npc.maid.do_not_meet", t.speaker }
   return "npc"
end

local function talk(_, state)
   state.text = ""
   return "npc"
end

local function is_shop(role)
   return (role >= 1000 and role < 2000) or role == 2003
end

local function criminal_check(t)
   if is_shop(t.speaker.role) then
      if Chara.player().karma < -30 and not Chara.get_flag(Chara.player(), "IsIncognito") then
         if Map.new_id() ~= "core.derphy" and not Map.new_id() ~= "core.your_home" then
            return true
         end
      end
   end
   return false
end

local function buy(t, state)
   if not criminal_check(t) then
      state.text = "core.locale.talk.npc.shop.criminal.buy"
      return "npc"
   end

   Internal.talk_shop_buy(t);

   state.text = ""
   return "npc"
end

local function sell(t, state)
   if not criminal_check(t) then
      state.text = "core.locale.talk.npc.shop.criminal.sell"
      return "npc"
   end

   Internal.talk_shop_sell(t);

   state.text = ""
   return "npc"
end

local function go_hostile()
   for _, chara in Chara.iter_others() do
      if chara.role == 14 or chara.role == 16 or chara.role == 1010 then
         chara.relation = "Enemy"
         chara.hate = 80
         chara.emotion_icon = 218
      end
   end
end

local function attack(t, state)
   local result = t.choices("core.locale.talk.npc.shop.attack.dialog",
                            {"attack", "core.locale.talk.npc.shop.attack.choices.attack"},
                            {"go_back", "core.locale.talk.npc.shop.attack.choices.go_back"})

   if result.choice == "attack" then
      go_hostile()
      return "__END__"
   end

   state.text = {"core.locale.talk.npc.common.you_kidding", t.speaker}
   return "npc"
end

local function invest(t, state)
   local choices = {}
   local cost = Internal.calcinvestvalue()
   if Chara.player().gold >= cost then
      table.insert(choices, {"invest", "core.locale.talk.npc.shop.invest.choices.invest"})
   end
   table.insert(choices, {"reject", "core.locale.talk.npc.shop.invest.choices.reject"})

   -- chatesc = 1
   local result = t.choices({"core.locale.talk.npc.shop.invest.ask", cost, t.speaker}, choices)

   if result.choice == "invest" then
      GUI.play_sound("core.paygold1")
      Chara.player().gold = Chara.player().gold - cost
      Chara.player():gain_skill_exp(160, 600)
      t.speaker.shop_rank = t.speaker.shop_rank + Rand.rnd(2) + 2
      state.text = {"core.locale.talk.npc.common.thanks", t.speaker}
   else
      state.text = {"core.locale.talk.npc.common.you_kidding", t.speaker}
   end

   if Map.new_id() == "core.your_home" then
      Internal.calccosthire()
   end

   return "npc"
end

local function resurrect_cost(ally)
   if ally.state ~= "PetDead" then
      return 100
   end

   return ally.level * ally.level * 15
end

local function call_ally(t, state)
   local choices = {}
   local ally = Chara.select_ally("CallBack")
   if ally then
      if Chara.is_alive(ally) then
         state.text = {"core.locale.talk.npc.bartender.call_ally.no_need", t.speaker}
         return "npc"
      end

      local cost = resurrect_cost(ally)

      if Chara.player().gold >= cost then
         table.insert(choices, {"pay", "core.locale.talk.npc.bartender.call_ally.choices.pay"})
      end
      table.insert(choices, {"go_back", "core.locale.talk.npc.bartender.call_ally.choices.go_back"})

      -- chatesc = 1
      local result = t.choices({"core.locale.talk.npc.bartender.call_ally.cost", cost, t.speaker}, choices)

      if result.choice == "pay" then
         GUI.play_sound("core.paygold1")
         Chara.player().gold = Chara.player().gold - cost
         state.text = {"core.locale.talk.npc.bartender.call_ally.brings_back", t.speaker, ally}
         Chara.revive(ally)
      else
         state.text = {"core.locale.talk.npc.common.you_kidding", t.speaker}
      end
   else
      state.text = {"core.locale.talk.npc.common.you_kidding", t.speaker}
   end
   return "npc"
end

local function slave_cost(chara)
   local value = Skill.get(chara, 10) * Skill.get(chara, 11) + chara.level * chara.level + 1000

   if value > 50000 then
      value = 50000
   end

   if Chara.get_flag(chara, "Splits") or Chara.get_flag(chara, "Splits2") then
      value = 10
   end

   return value
end

local function buy_ally(t, state, fltn)
   local choices = {}

   local chara = Internal.make_temp_chara(fltn)
   local cost = slave_cost(chara)

   if Chara.player().gold >= cost then
      table.insert(choices, {"pay", "core.locale.talk.npc.slave_trader.buy.choices.pay"})
   end
   table.insert(choices, {"go_back", "core.locale.talk.npc.slave_trader.buy.choices.go_back"})

   -- chatesc = 1
   local result = t.choices({"core.locale.talk.npc.slave_trader.buy.cost", chara.name, cost, t.speaker}, choices)

   if result.choice == "pay" then
      GUI.txt(I18n.get("core.locale.talk.npc.slave_trader.buy.you_buy", chara.name))
      GUI.txt("core.paygold1")
      Chara.player().gold = Chara.player().gold - cost
      chara:recruit_as_ally()
      state.text = {"core.locale.talk.npc.common.thanks", t.speaker}
   else
      state.text = {"core.locale.talk.npc.common.you_kidding", t.speaker}
   end

   return "npc"
end

local function buy_slave(t, state)
   return buy_ally(t, state, "man")
end

local function buy_horse(t, state)
   return buy_ally(t, state, "horse")
end

local function sell_slave(t, state)
   local ally = Chara.select_ally("Sell")

   if ally then
      local value = slave_cost(ally) * 2 / 3
      local result = t.choices({"core.locale.talk.npc.slave_trader.sell.price", value, t.speaker},
         {"deal", "core.locale.talk.npc.slave_trader.sell.choices.deal"},
         {"go_back", "core.locale.talk.npc.slave_trader.sell.choices.go_back"})

      if result.choice == "deal" then
         GUI.txt(I18n.get("core.locale.talk.npc.slave_trader.sell.you_sell_off", ally.name))
         GUI.play_sound("core.getgold1")
         Chara.player():earn_gold(value)
         Internal.sell_ally(ally)
         state.text = {"core.locale.talk.npc.common.thanks", t.speaker}
      else
         state.text = {"core.locale.talk.npc.common.you_kidding", t.speaker}
      end
   end

   return "npc"
end

local function wait_at_town(t)
   t.more { "core.locale.talk.npc.ally.wait_at_town", t.speaker }
   Internal.order_ally_wait(t.speaker)
   return "__END__"
end

local function ask_for_marriage(t, state)
   if t.speaker.impression < 200 then
      state.text = "core.locale.talk.npc.ally.marriage.refuses"
      return "npc"
   end
   t.speaker:set_flag("IsMarried", true)
   t.more { "core.locale.talk.npc.ally.marriage.accepts" }
   Internal.marry(t.speaker)
   return "__END__"
end

local function make_gene(t)
   if Map.new_id() == "core.shelter" then
      t.more { "core.locale.talk.npc.ally.make_gene.refuses", t.speaker }
      return "__END__"
   end

   t.more { "core.locale.talk.npc.ally.make_gene.accepts" }
   Internal.make_gene(t.speaker)
   return "__END__"
end

local function silence(t, state)
   if not Chara.get_flag(t.speaker, "IsSilent") then
      t.speaker:set_flag("IsSilent", true)
      state.text = {"core.locale.talk.npc.ally.silence.start", t.speaker}
   else
      t.speaker:set_flag("IsSilent", false)
      state.text = {"core.locale.talk.npc.ally.silence.stop", t.speaker}
   end

   return "npc"
end

local function abandon(t, state)
   local result = t.choices({"core.locale.talk.npc.ally.abandon.prompt", t.speaker},
      {"yes", "core.locale.talk.npc.ally.abandon.choices.yes"},
      {"no", "core.locale.talk.npc.ally.abandon.choices.no"})

   if result.choice == "yes" then
      GUI.txt(I18n.get("core.locale.talk.npc.ally.abandon.you_abandoned", t.speaker))
      Internal.abandon_ally(t.speaker)
      return "__END__"
   end

   state.text = ""
   return "npc"
end

local function ammo(t, state)
   local choices = {}
   local cost = Internal.reload_cost(Chara.player(), false)

   if cost == 0 then
      state.text = "core.locale.talk.npc.shop.ammo.no_ammo"
      return "npc"
   end

   if Chara.player().gold > cost then
      table.insert(choices, {"pay", "core.locale.talk.npc.shop.ammo.choices.pay"})
   end
   table.insert(choices, {"go_back", "core.locale.talk.npc.shop.ammo.choices.go_back"})

   local result = t.choices({"core.locale.talk.npc.shop.ammo.cost", cost, t.speaker})

   if result.choice == "pay" then
      GUI.snd("core.paygold1")
      Chara.player().gold = Chara.player().gold - cost
      Internal.reload_cost(Chara.player(), true)
      state.text = {"core.locale.talk.npc.common.thanks", t.speaker}
   else
      state.text = {"core.locale.talk.npc.common.you_kidding", t.speaker}
   end

   return "npc"
end

local function meal_cost()
   return 140
end

local function eat(t, state)
   local cost = meal_cost()
   if Chara.player().gold < cost then
      state.text = "core.locale.ui.no_gold"
      return "npc"
   end

   if Chara.player().nutrition >= 15000 then
      state.text = {"core.locale.talk.npc.innkeeper.eat.not_hungry", t.speaker}
      return "npc"
   end

   GUI.snd("core.paygold1")
   Chara.player().gold = Chara.player().gold - cost
   GUI.snd("core.eat1")
   Chara.player().nutrition = 15000
   state.text = {"core.locale.talk.npc.innkeeper.eat.here_you_are", t.speaker}
   GUI.txt(I18n.get("core.locale.talk.npc.innkeeper.eat.results"))
   GUI.show_eating_message(Chara.player())
   Chara.proc_anorexia(Chara.player())

   return "npc"
end

local function identify_cost(kind)
   local cost = 300

   if kind == 2 then
      cost = 5000
   end
   if kind == 1 then
      local need_to_identify = 0

      for _, item in Item.iter(0, 200) do
         if item.number ~= 0 and item.identify_state ~= "Completely" then
            need_to_identify = need_to_identify + 1
         end
      end

      if need_to_identify > 1 then
         cost = cost * need_to_identify * 70 / 100
      end
      cost = cost * 100 / (100 + Skill.get(Chara.player(), 156) * 2)

      if World.belongs_to_guild("fighters") then
         cost = cost / 2
      end

      return cost
   end
end

local function identify_base(t, state, kind)
   local cost = identify_cost(kind)
   if Chara.player().gold < cost then
      state.text = "core.locale.ui.no_gold"
      return "npc"
   end

   local found = false

   for _, item in Item.iter(0, 200) do
      if item.number ~= 0 and item.identify_state ~= "Completely" then
         found = true
         break
      end
   end

   if not found then
      state.text = {"core.locale.talk.npc.wizard.identify.already", t.speaker}
      return "npc"
   end

   if kind == 1 then
      Chara.player().gold = Chara.player().gold - cost
      local identified = 0
      local identified_completely = 0

      for _, item in Item.iter(0, 200) do
         if item.number > 0 and item.identify_state ~= "Completely" then
            local new_state = Item.identify(item, 250)
            Item.stack(0, item, true)
            identified = identified + 1
            if new_state == "Completely" then
               identified_completely = identified_completely + 1
            end
         end

         GUI.txt("core.locale.talk.npc.wizard.identify.count", identified, identified_completely)
         state.text = {"core.locale.talk.npc.wizard.identify.finished", t.speaker}
      end
   else
      local power = 250

      if kind == 2 then
         power = 1000
      end

      local result, canceled = Internal.cast_identify(power)
      if canceled then
         state.text = {"core.locale.talk.npc.common.you_kidding", t.speaker}
      end
      if result.choice == "Completely" then
         state.text = {"core.locale.talk.npc.wizard.identify.finished", t.speaker}
      else
         state.text = {"core.locale.talk.npc.wizard.identify.need_investigate", t.speaker}
      end
      Chara.player().gold = Chara.player().gold - cost
   end

   GUI.snd("core.paygold1")
   return "npc"
end

local function identify(t, state)
   return identify_base(t, state, 0)
end

local function identify_all(t, state)
   return identify_base(t, state, 1)
end

local function investigate(t, state)
   return identify_base(t, state, 2)
end

local function train(t, state)
   local selected_skill = Internal.select_skill(true)
   if not selected_skill then
      state.text = {"core.locale.talk.npc.trainer.leave", t.speaker}
      return "npc"
   end

   local choices = {}
   local cost = Internal.train_cost(selected_skill, Chara.player())

   if Chara.player().platinum >= cost then
      table.insert(choices, {"accept", "core.locale.talk.npc.trainer.choices.train.accept"})
   end
   table.insert(choices, {"go_back", "core.locale.talk.npc.trainer.choices.go_back"})

   -- chatesc = 1
   local result = t.choices({"core.locale.talk.npc.trainer.cost.training",
                             I18n.get_m("core.locale.ability",
                                        data.raw["core.ability"][selected_skill],
                                        "name"),
                             cost,
                             t.speaker},
      choices)

   if result.choice == "accept" then
      GUI.snd("core.paygold1")
      Chara.player().platinum = Chara.player().platinum - cost
      local skill = Chara.player():get_skill(selected_skill)
      skill:modify_potential(Math.clamp(15 - skill.potential) / 15, 2, 15)
      state.text = {"core.locale.talk.npc.trainer.finish.training", t.speaker}
   else
      state.text = {"core.locale.talk.npc.trainer.leave", t.speaker}
   end

   return "npc"
end

local function learn(t, state)
   local selected_skill = Internal.select_skill(false)
   if not selected_skill then
      state.text = {"core.locale.talk.npc.trainer.leave", t.speaker}
      return "npc"
   end

   local choices = {}
   local cost = Internal.learn_cost(selected_skill, Chara.player())

   if Chara.player().platinum >= cost then
      table.insert(choices, {"accept", "core.locale.talk.npc.trainer.choices.learn.accept"})
   end
   table.insert(choices, {"go_back", "core.locale.talk.npc.trainer.choices.go_back"})

   -- chatesc = 1
   local result = t.choices({"core.locale.talk.npc.trainer.cost.learning",
                             I18n.get_m("core.locale.ability",
                                        data.raw["core.ability"][selected_skill],
                                        "name"),
                             cost,
                             t.speaker},
      choices)

   if result.choice == "accept" then
      GUI.snd("core.paygold1")
      Chara.player().platinum = Chara.player().platinum - cost
      Chara.player():gain_skill(selected_skill)
      Game.data.number_of_learned_skills_by_trainer = Game.data.number_of_learned_skills_by_trainer + 1
      state.text = {"core.locale.talk.npc.trainer.finish.learning", t.speaker}
   else
      state.text = {"core.locale.talk.npc.trainer.leave", t.speaker}
   end

   return "npc"
end

local function show_adventurers(t, state)
   Internal.show_adventurers()
   state.text = {"core.locale.talk.npc.informer.show_adventurers", t.speaker}
   return "npc"
end

local function investigate_ally(t, state)
   local choices = {}
   local ally = Chara.select_ally("Investigate")
   if ally then
      local cost = 10000

      if Chara.player().gold >= cost then
         table.insert(choices, {"pay", "core.locale.talk.npc.informer.investigate_ally.choices.pay"})
      end
      table.insert(choices, {"go_back", "core.locale.talk.npc.informer.investigate_ally.choices.go_back"})

      -- chatesc = 1
      local result = t.choices({"core.locale.talk.npc.informer.investigate_ally.cost", t.speaker}, choices)

      if result.choice == "pay" then
         GUI.snd("core.paygold1")
         Chara.player().gold = Chara.player().gold - cost
         Internal.investigate_ally(ally)
         state.text = ""
      else
         state.text = {"core.locale.talk.npc.common.you_kidding", t.speaker}
      end
   else
      state.text = {"core.locale.talk.npc.common.you_kidding", t.speaker}
   end

   return "npc"
end

local function restore_cost()
   if World.belongs_to_guild("fighters") then
      return 250
   else
      return 500
   end
end

local function restore_attributes(t, state)
   local cost = restore_cost()

   if Chara.player().gold < cost then
      state.text = "core.locale.ui.no_gold"
      return "npc"
   end

   GUI.snd("core.paygold1")
   Chara.player().gold = Chara.player().gold - cost

   for _, chara in Chara.iter(0, 16) do
      if Chara.is_alive(chara) then
         Magic.cast(chara, 439, 100)
         Magic.cast(chara, 440, 100)
      end
   end

   Internal.talk_start()
   state.text = {"core.locale.talk.npc.healer.restore_attributes", t.speaker}
   return "npc"
end

local function trade(t, state)
   local result = Chara.trade(t.speaker)

   if result then
      state.text = {"core.locale.talk.npc.common.thanks", t.speaker}
   else
      state.text = {"core.locale.talk.npc.common.you_kidding", t.speaker}
   end

   return "npc"
end

local function hire_adventurer_cost(chara)
   return 250 + chara.level * chara.level * 30
end

local function hire(t, state)
   local choices = {}
   local cost = hire_adventurer_cost(t.speaker)

   if Chara.player().gold >= cost then
      table.insert(choices, {"pay", "core.locale.talk.npc.informer.investigate_ally.choices.pay"})
   end
   table.insert(choices, {"go_back", "core.locale.talk.npc.informer.investigate_ally.choices.go_back"})

   local result = t.choices({"core.locale.talk.npc.adventurer.hire.cost", cost, t.speaker})

   if result.choice == "pay" then
      GUI.snd("core.paygold1")
      Chara.player().gold = Chara.player().gold - cost
      t.speaker:recruit_as_adventurer()
      state.text = {"core.locale.talk.npc.common.thank", t.speaker}
   else
      state.text = {"core.locale.talk.npc.common.you_kidding", t.speaker}
   end

   return "npc"
end

local function join_adventurer_min_level()
   return Chara.player().level * 3 / 2 + 10
end

local function join(t, state)
   if join_adventurer_min_level() < t.speaker.level then
      state.text = {"core.locale.talk.npc.adventurer.join.too_weak", t.speaker}
      return "npc"
   end

   if t.speaker.impression >= 200 and t.hire_count > 2 then
      t.more { "core.locale.talk.npc.adventurer.join.accept", t.speaker }
      if Chara.free_ally_slot() == 0 then
         state.text = {"core.locale.talk.npc.adventurer.join.party_full", t.speaker}
         return "npc"
      end
      Internal.make_adventurer_join(t.speaker)
      return "__END__"
   end

   state.text = {"core.locale.talk.npc.adventurer.join.not_known", t.speaker}
   return "npc"
end

local function enter_duel(t, state)
   Chara.dismount(false)
   Internal.randomize_arena_fame()

   if Internal.arena_rumble_is_over() then
      state.text = {"core.locale.talk.npc.arena_master.enter.game_is_over", t.speaker}
      return "npc"
   end

   Internal.randomize_arena_duel()

   local target = Internal.generate_arena_target()

   -- chatesc = 1
   local result = t.choices({ "core.locale.talk.npc.arena_master.enter.target", target.name, t.speaker},
      {
         {"enter", "core.locale.talk.npc.arena_master.enter.choices.enter"},
         {"leave", "core.locale.talk.npc.arena_master.enter.choices.leave"}
      }
   )

   if result.choice == "enter" then
      Internal.enter_arena()
   else
      state.text = {"core.locale.talk.npc.arena_master.enter.cancel", t.speaker}
   end
end

local function enter_rumble(t, state)
   Chara.dismount(false)
   Internal.randomize_arena_fame()

   if Internal.arena_rumble_is_over() then
      state.text = {"core.locale.talk.npc.arena_master.enter.game_is_over", t.speaker}
      return "npc"
   end

   local target_level = Internal.generate_rumble_target()

   -- chatesc = 1
   local result = t.choices({"core.locale.talk.npc.arena_master.enter.target_group", target_level, t.speaker},
      {
         {"enter", "core.locale.talk.npc.arena_master.enter.choices.enter"},
         {"leave", "core.locale.talk.npc.arena_master.enter.choices.leave"}
      }
   )

   if result.choice == "enter" then
      Internal.enter_arena()
   else
      state.text = {"core.locale.talk.npc.arena_master.enter.cancel", t.speaker}
   end
end

local function score_arena(t, state)
   state.text = {"core.locale.talk.npc.arena_master.streak", Internal.winning_streak_in_arena(), t.speaker}
   return "npc"
end

local function register_duel(t, state)
   Internal.randomize_pet_arena_fame()

   local level = Internal.generate_pet_duel_target()

   -- chatesc = 1
   local result = t.choices({"core.locale.talk.npc.pet_arena_master.register.target", level, t.speaker},
      {
         {"enter", "core.locale.talk.npc.pet_arena_master.register.choices.enter"},
         {"leave", "core.locale.talk.npc.pet_arena_master.register.choices.leave"}
      }
   )

   if result.choice == "enter" then
      Internal.set_pet_arena_followers()
      local ally = Chara.select_ally("PetArena")
      if ally == nil then
         state.text = {"core.locale.talk.npc.arena_master.enter.cancel", t.speaker}
         return "npc"
      end

      Internal.enter_pet_arena()
   else
      state.text = {"core.locale.talk.npc.arena_master.enter.cancel", t.speaker}
   end
end

local function register_team(t, state)
   Internal.randomize_pet_arena_fame()
   local count, level = Internal.generate_pet_team_target()

   -- chatesc = 1
   local result = t.choices({"core.locale.talk.npc.pet_arena_master.register.target_group", count, level, t.speaker},
      {
         {"enter", "core.locale.talk.npc.pet_arena_master.register.choices.enter"},
         {"leave", "core.locale.talk.npc.pet_arena_master.register.choices.leave"}
      }
   )

   if result.choice == "enter" then
      Internal.set_pet_arena_followers()
      local ally = Chara.select_ally("PetArena")
      if ally == nil then
         state.text = {"core.locale.talk.npc.arena_master.enter.cancel", t.speaker}
         return "npc"
      end

      Internal.enter_pet_arena()
   else
      state.text = {"core.locale.talk.npc.arena_master.enter.cancel", t.speaker}
   end
end

local function score_pet_arena(t, state)
   state.text = {"core.locale.talk.npc.arena_master.streak", Internal.winning_streak_in_pet_arena(), t.speaker}
   return "npc"
end

local function think_of_house_name(t, state)
   Internal.set_map_name(Rand.random_title("Character"))
   if Rand.one_in(5) then
      Internal.set_map_name(I18n.get("core.locale.talk.npc.maid.think_of_house_name.suffixes", Map.name()))
   end

   GUI.update_screen(false)

   state.text = {"core.locale.talk.npc.maid.think_of_house_name.come_up_with", Map.name(), t.speaker}
   return "npc"
end

local function indulgence_cost()
   return -(Chara.player().karma + 30) * (Chara.player.fame / 2 + Chara.player.level * 200)
end

local function buy_indulgence(t, state)
   if Chara.player().karma >= -30 then
      state.text = "core.locale.talk.npc.sister.buy_indulgence.karma_is_not_low"
      return "npc"
   end

   local choices = {}
   local cost = indulgence_cost()

   if Chara.player().gold >= cost then
      table.insert(choices, {"buy", "core.locale.talk.npc.sister.buy_indulgence.choices.buy"})
   end
   table.insert(choices, {"go_back", "core.locale.talk.npc.sister.buy_indulgence.choices.go_back"})

   local result = t.choices({"core.locale.talk.npc.sister.buy_indulgence.cost", cost, t.speaker}, choices)

   if result.choice == "buy" then
      GUI.snd("core.paygold1")
      Chara.player().gold = Chara.player().gold - cost
      Chara.player():modify_karma((Chara.player().karma + 30) * -1 + 1)
      state.text = {"core.locale.talk.npc.common.thanks", t.speaker}
   else
      state.text = {"core.locale.talk.npc.common.you_kidding", t.speaker}
   end

   return "npc"
end

local function where_is(t, state, opts)
   local client = Internal.find_quest_client(opts.client)
   local dir = Pos.direction(Chara.player().position, client.position)
   local dir_string

   if dir == 1 then
      dir_string = I18n.get("core.locale.talk.npc.guard.where_is.direction.west")
   elseif dir == 2 then
      dir_string = I18n.get("core.locale.talk.npc.guard.where_is.direction.east")
   elseif dir == 3 then
      dir_string = I18n.get("core.locale.talk.npc.guard.where_is.direction.north")
   else
      dir_string = I18n.get("core.locale.talk.npc.guard.where_is.direction.south")
   end

   local dist = Pos.dist(Chara.player().position, client.position)

   if t.speaker == client then
      state.text = {"core.locale.talk.npc.common.you_kidding", t.speaker}
   elseif not Chara.is_alive(client) then
      state.text = {"core.locale.talk.npc.guard.where_is.dead", t.speaker}
   elseif dist < 6 then
      state.text = {"core.locale.talk.npc.guard.where_is.very_close", dir_string, client.name, t.speaker}
   elseif dist < 12 then
      state.text = {"core.locale.talk.npc.guard.where_is.close", dir_string, client.name, t.speaker}
   elseif dist < 20 then
      state.text = {"core.locale.talk.npc.guard.where_is.moderate", dir_string, client.name, t.speaker}
   elseif dist < 35 then
      state.text = {"core.locale.talk.npc.guard.where_is.far", dir_string, client.name, t.speaker}
   else
      state.text = {"core.locale.talk.npc.guard.where_is.very_far", dir_string, client.name, t.speaker}
   end

   return "npc"
end

local function lost_item(t, _, opts)
   local item = Item.find(0, opts.id)

   item.number = item.number - 1

   if item.param1 == 0 then
      -- chatesc = 1
      t.more({"core.locale.talk.npc.guard.lost.empty.dialog", t.speaker},
         "core.locale.talk.npc.guard.lost.empty.response")
      Chara.player():modify_karma(-5)
   else
      -- chatesc = 1
      t.more({"core.locale.talk.npc.guard.lost.dialog", t.speaker},
         "core.locale.talk.npc.guard.lost.response")
      Chara.player():modify_karma(5)
      Game.data.lost_wallet_count = Game.data.lost_wallet_count + 1
      if Game.data.lost_wallet_count >= 4 then
         t.more {"core.locale.talk.npc.guard.lost.found_often.dialog._0", t.speaker}

         -- chatesc = 1
         t.more({"core.locale.talk.npc.guard.lost.found_often.dialog._1", t.speaker},
            "core.locale.talk.npc.guard.lost.found_often.response")
         Chara.player():modify_karma(-10)
      end
   end

   return "npc"
end

local function wizard_return(t)
   t.more {"core.locale.talk.npc.wizard.return", t.speaker}
   World.try_to_return()
   return "__END__"
end

local function reserve(_, state)
   Internal.show_spell_writer_menu()
   state.text = ""
   return "npc"
end

local function sex(t, state)
   local result = t.choices({"core.locale.talk.npc.common.sex.prompt", t.speaker},
      {
         {"accept", "core.locale.talk.npc.common.sex.choices.accept"},
         {"go_back", "core.locale.talk.npc.common.sex.choices.go_back"}
      }
   )

   if result.choice == "go_back" then
      state.text = {"core.locale.talk.npc.common.you_kidding", t.speaker}
      return "npc"
   end

   t.more({"core.locale.talk.npc.common.sex.start", t.speaker},
      "core.locale.talk.npc.common.sex.response")

   Internal.continuous_action_sex()
   return "__END__"
end

local function prostitute_cost(chara)
   return Skill.get(chara, 17) * 25 + 100 + Chara.player().fame / 10
end

local function buy_prostitute(t, state)
   local choices = {}
   local cost = prostitute_cost()

   if Chara.player().gold >= cost then
      table.insert(choices, {"accept", "core.locale.talk.npc.common.sex.choices.accept"})
   end
   table.insert(choices, {"go_back", "core.locale.talk.npc.common.sex.choices.go_back"})

   local result = t.choices({"core.locale.talk.npc.prostitute.buy", cost, t.speaker},
      choices)

   if result.choice == "go_back" then
      state.text = {"core.locale.talk.npc.common.you_kidding", t.speaker}
      return "npc"
   end

    GUI.snd("core.paygold1");
    Chara.player().gold = Chara.player().gold - cost
    t.speaker:earn_gold(cost);

    t.more({"core.locale.talk.npc.common.sex.start", t.speaker},
       "core.locale.talk.npc.common.sex.response")

   Internal.continuous_action_sex()

   return "__END__"
end

local function hire_caravan(t, state)
   local choices = Internal.get_caravan_talk_choices()
   local result = t.choices("core.locale.talk.npc.caravan_master.hire.tset", choices)

   if result.choice == "go_back" then
      state.text = {"core.locale.talk.npc.common.you_kidding", t.speaker}
   end

   Internal.hire_caravan(result.opts.map_id)
   return "__END__"
end

local function fire(t, state)
   local result = t.choices({"core.locale.talk.npc.servant.fire.prompt", t.speaker},
      {
         {"yes", "core.locale.talk.npc.servant.fire.choices.yes"},
         {"no", "core.locale.talk.npc.servant.fire.choices.no"},
      }
   )

   if result.choice == "yes" then
      GUI.txt(I18n.get("core.locale.talk.npc.servant.fire.you_dismiss", t.speaker))
      Chara.vanquish(t.speaker)
      Internal.calccosthire()
      return "__END__"
   end

   state.text = ""
   return "npc"
end

local function sell_paels_mom(t, state)
   local result = t.choices("core.locale.talk.npc.moyer.sell_paels_mom.prompt",
      {
         {"sell", "core.locale.talk.npc.moyer.sell_paels_mom.choices.sell"},
         {"go_back", "core.locale.talk.npc.moyer.sell_paels_mom.choices.go_back"},
      }
   )

   if result.choice == "sell" then
      Chara.player():modify_karma(-20)
      GUI.snd("core.getgold1")
      Chara.player():earn_gold(50000)
      Internal.set_quest_flag("pael_and_her_mom", 1002);
      local paels_mom = Chara.find(222)
      paels_mom:set_inital_position(48, 18)
      state.text = {"core.locale.talk.npc.common.thanks", t.speaker}
   else
      state.text = {"core.locale.talk.npc.common.you_kidding", t.speaker}
   end

   return "npc"
end

local function bye()
   Internal.proc_chat_teleport()

   return "__END__"
end

local npc = {
   name = "npc",

   nodes = {
      meet_guest = meet_guest,
      do_not_meet_guest = do_not_meet_guest,
      talk = talk,
      buy = buy,
      sell = sell,
      attack = attack,
      invest = invest,
      call_ally = call_ally,
      buy_slave = buy_slave,
      sell_slave = sell_slave,
      buy_horse = buy_horse,
      wait_at_town = wait_at_town,
      ask_for_marriage = ask_for_marriage,
      make_gene = make_gene,
      silence_start = silence,
      silence_stop = silence,
      abandon = abandon,
      ammo = ammo,
      eat = eat,
      identify = identify,
      identify_all = identify_all,
      investigate = investigate,
      train = train,
      learn = learn,
      show_adventurers = show_adventurers,
      investigate_ally = investigate_ally,
      restore_attributes = restore_attributes,
      trade = trade,
      hire = hire,
      join = join,
      enter_duel = enter_duel,
      enter_rumble = enter_rumble,
      score_arena = score_arena,
      register_duel = register_duel,
      register_team = register_team,
      score_pet_arena = score_pet_arena,
      think_of_house_name = think_of_house_name,
      buy_indulgence = buy_indulgence,
      where_is = where_is,
      lost_item = lost_item,
      wizard_return = wizard_return,
      reserve = reserve,
      sex = sex,
      buy_prostitute = buy_prostitute,
      hire_caravan = hire_caravan,
      fire = fire,
      sell_paels_mom = sell_paels_mom,
      bye = bye,

      __start = function()
         return "npc"
      end,

      npc = function(t, state)
         local text = state.text

         if text == nil or text == "" then
            text = Internal.get_npc_talk(t.speaker)
            modify_impression(t.speaker)
         end

         local choices = {}
         local role = t.speaker.role
         local function add_choice(id, locale_opts, opts)
            table.insert(choices, { id, locale_opts, opts })
         end

         if role == 18 then
            add_choice("meet_guest", "core.locale.talk.npc.maid.choices.meet_guest")
            add_choice("do_not_meet_guest", "core.locale.talk.npc.maid.choices.do_not_meet")
         end
         if t.interest > 0 and not state.is_unique then
            add_choice("talk", "core.locale.talk.npc.common.choices.talk")
         end
         if is_shop(role) then
            add_choice("buy", "core.locale.talk.npc.shop.choices.buy")
            add_choice("sell", "core.locale.talk.npc.shop.choices.sell")

            if role == 1010 then
               add_choice("attack", "core.locale.talk.npc.shop.choices.attack")
            end
            if role ~= 1010 and t.speaker.role ~= 1009 then
               add_choice("invest", "core.locale.talk.npc.shop.choices.invest")
            end
         end
         if role == 9 then
            add_choice("call_ally", "core.locale.talk.npc.bartender.choices.call_ally")
         end
         if role == 17 then
            if Chara.free_ally_slot() ~= 0 then
               add_choice("buy_slave", "core.locale.talk.npc.slave_trader.choices.buy")
            end
            add_choice("sell_slave", "core.locale.talk.npc.slave_trader.choices.sell")
         end
         if role == 22 then
            if Chara.free_ally_slot() ~= 0 then
               add_choice("buy_horse", "core.locale.talk.npc.horse_keeper.choices.buy");
            end
         end

         if Chara.is_ally(t.speaker) then
            if not (Chara.get_flag(t.speaker, "IsEscorted") or Chara.get_flag(t.speaker, "IsEscortedInSubQuest")) then
               add_choice("wait_at_town", "core.locale.talk.npc.ally.choices.wait_at_town")
               if not Chara.get_flag(t.speaker, "IsMarried") then
                  add_choice("ask_for_marriage", "core.locale.talk.npc.ally.choices.ask_for_marriage")
               elseif Game.session_hours() >= 15 then
                  add_choice("make_gene", "core.locale.talk.npc.ally.choices.make_gene")
               end
               if t.speaker.can_talk ~= 0 then
                  if not Chara.get_flag(t.speaker, "IsSilent") then
                     add_choice("silence_start", "core.locale.talk.npc.ally.choices.silence.start")
                  else
                     add_choice("silence_start", "core.locale.talk.npc.ally.choices.silence.stop")
                  end
               end
               add_choice("abandon", "core.locale.talk.npc.ally.choices.abandon")
            end
         end

         if role == 1000 or t.speaker.role == 1001 then
            add_choice("ammo", "core.locale.talk.npc.shop.choices.ammo")
         end
         if role == 1005 then
            add_choice("eat", "core.locale.talk.npc.innkeeper.choices.eat", {meal_cost()})
         end
         if role == 5 then
            add_choice("identify", {"core.locale.talk.npc.wizard.choices.identify", identify_cost(0)})
            add_choice("identify_all", {"core.locale.talk.npc.wizard.choices.identify_all", identify_cost(1)})
            add_choice("investigate", {"core.locale.talk.npc.wizard.choices.investigate", identify_cost(2)})
         end
         if role == 7 then
            add_choice("train", "core.locale.talk.npc.trainer.choices.train.ask")
            add_choice("learn", "core.locale.talk.npc.trainer.choices.learn.ask")
         end
         if role == 8 then
            add_choice("show_adventurers", "core.locale.talk.npc.informer.choices.show_adventurers")
            add_choice("investigate_ally", "core.locale.talk.npc.informer.choices.investigate_ally")
         end
         if role == 12 then
            add_choice("restore_attributes", {"core.locale.talk.npc.healer.choices.restore_attributes", restore_cost()})
         end
         if role == 13 then
            add_choice("trade", "core.locale.talk.npc.common.choices.trade")
            if not Chara.get_flag(t.speaker, "IsContracting") then
               add_choice("hire", "core.locale.talk.npc.common.choices.hire")
               add_choice("join", "core.locale.talk.npc.common.choices.join")
            end
         end
         if role == 10 then
            add_choice("enter_duel", "core.locale.talk.npc.arena_master.choices.enter_duel")
            add_choice("enter_rumble", "core.locale.talk.npc.arena_master.choices.enter_rumble")
            add_choice("score_arena", "core.locale.talk.npc.arena_master.choices.score")
         end
         if role == 11 then
            add_choice("register_duel", "core.locale.talk.npc.pet_arena_master.choices.register_duel")
            add_choice("register_team", "core.locale.talk.npc.pet_arena_master.choices.register_team")
            add_choice("score_pet_arena", "core.locale.talk.npc.arena_master.choices.score")
         end
         if role == 18 then
            add_choice("think_of_house_name", "core.locale.talk.npc.maid.choices.think_of_house_name")
         end
         if role == 19 then
            add_choice("buy_indulgence", "core.locale.talk.npc.sister.choices.buy_indulgence")
         end
         if Internal.talk_check_trade(t.speaker) then
            add_choice("trade", "core.locale.talk.npc.common.choices.trade")
         end
         if role == 14 then
            local client = Internal.quest_client()
            if client ~= nil then
               add_choice("where_is", {"core.locale.talk.npc.guard.choices.where_is", client.name}, {client = client})
            end
            if Item.find(0, 283) then
               add_choice("lost_item", "core.locale.talk.npc.guard.choices.lost_wallet", {id = 283})
            end
            if Item.find(0, 284) then
               add_choice("lost_item", "core.locale.talk.npc.guard.choices.lost_suitcase", {id = 284})
            end
         end
         if role == 21 then
            add_choice("wizard_return", "core.locale.talk.npc.wizard.choices.return")
         end
         if role == 1020 then
            if World.belongs_to_guild("mages") then
               add_choice("reserve", "core.locale.talk.npc.spell_writer.choices.reserve")
            end
         end
         if Chara.get_flag(t.speaker, "Drunk") then
            if Map.new_id() ~= "core.show_house" then
               if not Chara.is_ally(t.speaker) then
                  if Event.id() == -1 then
                     add_choice("sex", "core.locale.talk.npc.common.choices.sex")
                  end
               end
            end
         end
         if t.speaker.id == 335 and Event.id() == -1 then
            add_choice("buy_prostitute", "core.locale.talk.npc.prostitute.choices.buy")
         end
         if role == 23 then
            add_choice("hire_caravan", "core.locale.talk.npc.caravan_master.choices.hire")
         end

         for _, choice in ipairs(Internal.talk_quest_choices()) do
            table.insert(choices, choice)
         end

         -- TODO replace with Map.id()
         if Map.new_id() == "core.your_home" then
            if Chara.is_other(t.speaker) then
               if role ~= 0 then
                  if (role < 2000 or role >= 3000) and Event.id() == -1 then
                     add_choice("fire", "core.locale.talk.npc.servant.choices.fire")
                  end
               end
            end
         end

         if role == 1015 then
            if Internal.quest_flag("pael_and_her_mom") == 1000 then
               local paels_mom = Chara.find("core.paels_mom")
               if Chara.is_alive(paels_mom) then
                  add_choice("sell_paels_mom", "core.locale.talk.npc.moyer.choices.sell_paels_mom")
               end
            end
         end

         add_choice("bye", "core.locale.ui.bye")

         return t.choices(text, choices)
      end
   }
}

return npc

-- t.choices
-- t.more (more or bye?)
-- Chara.revive
-- Internal.abandon_ally(t.speaker)
-- Internal.arena_rumble_is_over()
-- Internal.calccosthire()
-- Internal.calcinvestvalue()
-- Internal.cast_identify(power)
-- Internal.continuous_action_sex()
-- Internal.enter_arena()
-- Internal.enter_pet_arena()
-- Internal.find_quest_client(opts.client)
-- Internal.generate_arena_target()
-- Internal.generate_pet_duel_target()
-- Internal.generate_pet_team_target()
-- Internal.generate_rumble_target()
-- Internal.get_caravan_talk_choices()
-- Internal.get_npc_talk(t.speaker)
-- Internal.hire_caravan(result.opts.map_id)
-- Internal.investigate_ally(ally)
-- Internal.learn_cost(selected_skill, Chara.player())
-- Internal.make_adventurer_join(t.speaker)
-- Internal.make_gene(t.speaker)
-- Internal.make_temp_chara(fltn)
-- Internal.marry(t.speaker)
-- Internal.order_ally_wait(t.speaker)
-- Internal.proc_chat_teleport()
-- Internal.quest_client()
-- Internal.quest_flag("pael_and_her_mom")
-- Internal.randomize_arena_duel()
-- Internal.randomize_arena_fame()
-- Internal.randomize_pet_arena_fame()
-- Internal.reload_cost(Chara.player(), false)
-- Internal.reload_cost(Chara.player(), true)
-- Internal.select_skill(false)
-- Internal.select_skill(true)
-- Internal.sell_ally(ally)
-- Internal.set_map_name()
-- Internal.set_pet_arena_followers()
-- Internal.set_quest_flag("pael_and_her_mom", 1002);
-- Internal.show_adventurers()
-- Internal.show_spell_writer_menu()
-- Internal.talk_check_trade(t.speaker)
-- Internal.talk_quest_choices() do
-- Internal.talk_shop_buy(t);
-- Internal.talk_shop_sell(t);
-- Internal.talk_start()
-- Internal.train_cost(selected_skill, Chara.player())
-- Internal.winning_streak_in_arena()
-- Internal.winning_streak_in_pet_arena()
-- Rand.random_title
-- Game.data
-- World.try_to_return
-- LuaCharacter:earn_gold
