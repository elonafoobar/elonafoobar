local Item = Elona.require("Item")
local Rand = Elona.require("Rand")

local chara_drop = {}

function chara_drop.create(chara, drop)
   if drop.on_create then
      chara_drop.on_create({chara = chara})
   elseif drop.id then
      Item.create(chara.position, drop.id, 0)
   else
      local args = {
         level = drop.level,
         flttypemajor = drop.flttypemajor,
         flttypeminor = drop.flttypeminor,
         quality = drop.quality
      }
      Item.roll(chara.position, args)
   end
end

function chara_drop.run_drop(chara, drop_data)
   local drops = drop_data.drops

   if drop_data.on_generate then
      drops = drop_data.on_generate({chara = chara})
   end

   for _, drop in ipairs(drops) do
      if not drop.one_in or Rand.one_in(drop.one_in) then
         chara_drop.create(chara, drop)
      end
   end
end

function chara_drop.drop(chara, drops)
   for _, drop_id in ipairs(drops) do
      local drop_data = data.raw["core.chara_drop"][drop_id]
      if drop_data then
         chara_drop.run_drop(chara, drop_data)
      end
   end
end

function chara_drop.drop_from_chara(chara)
   local drops = data.raw["core.chara"][chara.new_id].drops
   chara_drop.drop(chara, drops)
end

return chara_drop