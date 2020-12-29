--- Functions to be used inside translations, like "${itemname(_1, _2, _3)}".

-- Require common formatting.
require("../_common/functions.lua")

local FOV = ELONA.require("core.FOV")
local I18N = ELONA.require("core.I18N")
local Item = ELONA.require("core.Item")
local string = string

ELONA.i18n:add_function {
   ordinal = function(n)
      return tostring(n)
   end,

   he = function(chara)
      if not chara then
         return "彼"
      end

      if chara.sex == "male" then
         return "彼"
      else
         return "彼女"
      end
   end,

   his = function(chara)
      if not chara then
         return "彼の"
      end

      if chara.index == 0 then
         return "あなたの"
      elseif chara.sex == "male" then
         return "彼の"
      else
         return "彼女の"
      end
   end,

   him = function(chara)
      if not chara then
         return "彼"
      end

      if chara.sex == "male" then
         return "彼"
      else
         return "彼女"
      end
   end,

   kare_wa = function(chara)
      if not chara then
         return "それは"
      end

      if chara.index == 0 then
         return ""
      elseif not FOV.you_see(chara) then
         return "それは"
      else
         return chara.basename .. "は"
      end
   end,
}
