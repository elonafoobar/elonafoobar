--- Functions to be used inside translations, like "${itemname(_1, _2, _3)}".
local i18n = require("core.i18n")
local Item = require("core.Item")
local string = string


i18n.add_function {
   you = function()
      return i18n.get("core.chara.you")
   end,

   name = function(chara)
      if not chara or not chara.name then
         return i18n.get("core.chara.something")
      end
      return chara.name
   end,

   basename = function(chara)
      if not chara or not chara.name then
         return i18n.get("core.chara.something")
      end
      return chara.basename
   end,

   itemname = function(item, number, needs_article)
      if not item then
         return i18n.get("core.chara.something")
      end
      if item.lua_type ~= "LuaItem" then
         return i18n.get("core.chara.something")
      end
      if number == nil then
         number = item.number
      end
      if needs_article == nil then
         needs_article = true
      end

      return Item.itemname(item, number, needs_article)
   end,

   itembasename = function(item)
      if not item then
         return i18n.get("core.chara.something")
      end
      if item.lua_type ~= "LuaItem" then
         return i18n.get("core.chara.something")
      end
      return item.basename
   end,

   zfill = function(n, width)
      return string.format("%0"..tostring(width).."d", n)
   end,
}
