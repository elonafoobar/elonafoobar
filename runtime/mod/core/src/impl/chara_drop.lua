local Data = require("core.Data")
local Item = require("core.Item")
local Rand = require("core.Rand")

local chara_drop = {}

function chara_drop.create(chara, drop)
   if drop.on_create then
      drop.on_create({chara = chara})
   elseif drop.id then
      Item.create(chara.position, drop.id)
   else
      local args = {
         level = drop.level,
         flttypemajor = drop.flttypemajor,
         flttypeminor = drop.flttypeminor,
         quality = drop.quality
      }
      Item.create(chara.position, args)
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
      local drop_data = Data.get("core.chara_drop", drop_id)
      if drop_data then
         chara_drop.run_drop(chara, drop_data)
      end
   end
end

function chara_drop.drop_from_chara(chara)
   local drops = Data.get("core.chara", chara.id).drops

   if drops then
      chara_drop.drop(chara, drops)
   end
end

return chara_drop
