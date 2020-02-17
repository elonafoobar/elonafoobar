local Chara = Elona.game.Chara
local GUI = Elona.game.GUI
local I18N = Elona.game.I18N
local Internal = Elona.game.Internal
local Item = Elona.game.Item
local World = Elona.game.World
local table = Elona.game.table

local function upgrade_cart_cost()
   return (World.data.current_cart_limit - World.data.initial_cart_limit) // 10000 + 1
end

local function upgrade_cart_amount()
   return 10000
end

local function upgrade_cargo_limit()
   local cost = upgrade_cart_cost()
   local amount = upgrade_cart_amount()
   local small_medals = Item.find("core.small_medal", "PlayerInventory")

   GUI.txtnew()
   GUI.txt(I18N.get(
          "core.talk.unique.miral.upgrade_cart.give.limit_increased",
          Item.weight_string(amount)))
   GUI.play_sound("core.build1")

   small_medals.number = small_medals.number - cost
   World.data.current_cart_limit = World.data.current_cart_limit + amount
   Chara.player():refresh_burden_state()
end

return {
   id = "miral",
   root = "core.talk.unique.miral",
   nodes = {
      __start = {
         text = {
            {"dialog"},
         },
         choices = {
            {"small_medals", "choices.small_medals"},
            {"upgrade_cart", "choices.upgrade_cart"},
            {"__END__", "__BYE__"},
         }
      },
      small_medals = {
         text = {
            {"small_medals"},
         },
         choices = {
            {"__start", "__MORE__"},
         },
         on_finish = function(t)
            Internal.trade_small_medals(t.speaker)
         end
      },
      upgrade_cart = {
         text = {
            {"upgrade_cart.dialog", args = function() return {upgrade_cart_cost()} end},
         },
         choices = function()
            local choices = {}
            local cost = upgrade_cart_cost()
            local small_medals = Item.find("core.small_medal", "PlayerInventory")
            if small_medals ~= nil then
               if small_medals.number >= cost then
                  table.insert(choices, {"upgrade_cart_give", "upgrade_cart.choices.give"})
               end
            end
            table.insert(choices, {"upgrade_cart_go_back", "upgrade_cart.choices.go_back"})

            return choices
         end
      },
      upgrade_cart_go_back = {
         text = {
            {"upgrade_cart.go_back"},
         },
         choices = {
            {"__start", "__MORE__"},
         }
      },
      upgrade_cart_give = {
         text = {
            upgrade_cargo_limit,
            {"upgrade_cart.give.dialog"},
         },
         choices = {
            {"__start", "__MORE__"},
         },
      },
   }
}
