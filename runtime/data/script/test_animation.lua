local Animation = Elona.require("Animation")
local Chara = Elona.require("Chara")
local Enums = Elona.require("Enums")
local Event = Elona.require("Event")
local Input = Elona.require("Input")
local Item = Elona.require("Item")
local Rand = Elona.require("Rand")

local LuaPosition = Elona.require("LuaPosition")

local choice = 0
local switcher = nil

local function make_sandbag(x, y, chara_id)
   Item.create(x, y, 733, 1)
   local chara = Chara.create(x, y, chara_id)
   chara:set_flag(Enums.CharaFlag.IsHungOnSandBag, true)
   return chara
end

local function query(chara)
   if not switcher or chara.index ~= switcher.index then
      return
   end

   choice = Input.prompt_number("Which?", 15, choice + 1) - 1
end

local function go()
   local my_pos = Chara.player().position
   local other_pos = LuaPosition.new(my_pos.x + 5, my_pos.y + 5)

   if choice == 0 then
      Animation.play_failure_to_cast(my_pos)
   elseif choice == 1 then
      Animation.play_bright_aura(my_pos, Rand.rnd(4))
   elseif choice == 2 then
      Animation.play_breath(my_pos, other_pos, 50)
   elseif choice == 3 then
      Animation.play_ball_atomic_bomb(my_pos, Rand.rnd(5) + 1)
   elseif choice == 4 then
      Animation.play_ball_magic(my_pos, Rand.rnd(5) + 1, 50)
   elseif choice == 5 then
      Animation.play_bolt(my_pos, other_pos, 50, Rand.rnd(5) + 1)
   elseif choice == 6 then
      Animation.play_throwing_object(my_pos, other_pos, 500, 3)
   elseif choice == 7 then
      Animation.play_swarm(my_pos)
   elseif choice == 8 then
      Animation.play_ranged_attack(my_pos, other_pos, 0, 0, 500, 0)
   elseif choice == 9 then
      Animation.play_melee_attack(my_pos, Rand.coinflip(), 0, Rand.rnd(200), Rand.coinflip())
   elseif choice == 10 then
      Animation.play_gene_engineering(my_pos)
   elseif choice == 11 then
      Animation.play_miracle()
   elseif choice == 12 then
      Animation.play_meteor()
   elseif choice == 13 then
      Animation.play_ragnarok()
   elseif choice == 14 then
      Animation.play_breaking(my_pos)
   end
end

local function setup()
   Chara.create(24, 24, 170)
   switcher = make_sandbag(25, 23, 241)
end

Event.register(Event.EventKind.GameInitialized, setup)
Event.register(Event.EventKind.AllTurnsFinished, go)
Event.register(Event.EventKind.CharaDamaged, query)
