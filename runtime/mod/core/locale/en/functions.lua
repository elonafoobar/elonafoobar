--- Functions to be used inside translations, like "${itemname(_1, _2, _3)}".

-- Require common formatting.
require("../_common/functions.lua")

local FOV = ELONA.require("core.FOV")
local I18N = ELONA.require("core.I18N")
local Item = ELONA.require("core.Item")
local string = string

I18N.add_function {
   ordinal = function(n)
      if n % 10 == 1 and n ~= 11 then
         return tostring(n) .. "st"
      elseif n % 10 == 2 and n ~= 12 then
         return tostring(n) .. "nd"
      elseif n % 10 == 3 and n ~= 13 then
         return tostring(n) .. "rd"
      else
         return tostring(n) .. "th"
      end
   end,

   trim_job = function(name_with_job)
      return string.gsub(name_with_job, " .*", " ")
   end,

   capitalize = function(str)
      if str == "" then
         return str
      end

      return str:gsub("^%l", string.upper)
   end,

   he = function(chara, ignore_sight)
      if not chara then
         return "it"
      end

      if ignore_sight then
         if chara.sex == "male" then
            return "he"
         else
            return "she"
         end
      end

      if chara.index < 0 or chara.index >= 245 then
         return "it"
      elseif not FOV.you_see(chara) then
         return "it"
      elseif chara.index == 0 then
         return "you"
      elseif chara.sex == "male" then
         return "he"
      else
         return "she"
      end
   end,

   his = function(chara, ignore_sight)
      if not chara then
         return "its"
      end

      if ignore_sight then
         if chara.index == 0 then
            return "your"
         elseif chara.sex == "male" then
            return "his"
         else
            return "her"
         end
      end

      if chara.index < 0 or chara.index >= 245 then
         return "its"
      elseif not FOV.you_see(chara) then
         return "its"
      elseif chara.index == 0 then
         return "your"
      elseif chara.sex == "male" then
         return "his"
      else
         return "her"
      end
   end,

   him = function(chara, ignore_sight)
      if not chara then
         return "it"
      end

      if ignore_sight then
         if chara.sex == "male" then
            return "him"
         else
            return "her"
         end
      end

      if chara.index < 0 or chara.index >= 245 then
         return "it"
      elseif not FOV.you_see(chara) then
         return "it"
      elseif chara.index == 0 then
         return "yourself"
      elseif chara.sex == "male" then
         return "him"
      else
         return "her"
      end
   end,

   is = function(object)
      if not object then
         return "is"
      end

      if object == true then
         return "are"
      elseif object == false then
         return "is"
      end

      if object.lua_type == "LuaItem" then
         if object.number > 1 then
            return "are"
         else
            return "is"
         end
      end

      if object.index == 0 then
         return "are"
      else
         return "is"
      end
   end,

   s = function(object, need_e)
      if not object then
         return need_e and "es" or "s"
      end

      if object == true then
         if need_e then
            return "es"
         else
            return "s"
         end
      elseif object == false then
         return ""
      end

      if type(object) == "number" then
         if object == 1 then
            return ""
         else
            return "s"
         end
      end

      if object.lua_type == "LuaItem" then
         if object.number == 1 then
            return ""
         else
            return "s"
         end
      end

      if object.index == 0 then
         return ""
      elseif need_e then
         return "es"
      else
         return "s"
      end
   end,

   does = function(object)
      if not object then
         return "does"
      end

      if object.lua_type == "LuaItem" then
         if object.number == 1 then
            return "do"
         else
            return "does"
         end
      end

      if object.index == 0 then
         return "do"
      else
         return "does"
      end
   end,

   have = function(chara)
      if not chara then
         return "has"
      end

      if chara.index == 0 then
         return "have"
      else
         return "has"
      end
   end,

   himself = function(chara)
      if not chara then
         return "itself"
      end

      if chara.index < 0 or chara.index >= 245 then
         return "itself"
      elseif not FOV.you_see(chara) then
         return "itself"
      elseif chara.index == 0 then
         return "yourself"
      elseif chara.sex == "male" then
         return "himself"
      else
         return "herself"
      end
   end,

   his_owned = function(chara)
      if not chara then
         return "'s"
      end

      if chara.index == 0 then
         return "r"
      else
         return "'s"
      end
   end,

   name_nojob = function(chara)
      return i18n.en.trim_job(chara.basename)
   end,
}
