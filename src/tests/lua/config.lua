require_relative("tests/lua/support/minctest")

local Config = require("game.Config")

local function lfail(f)
   local ok = pcall(f)
   lequal(ok, false)
end



lrun("test Config.get", function()
   local extra_help = Config.get("core.game.extra_help")
   lequal(type(extra_help), "boolean")
   lequal(extra_help, true)

   local general_wait = Config.get("core.anime.general_wait")
   lequal(type(general_wait), "number")
   lequal(general_wait, 30)

   local font_quality = Config.get("core.font.quality")
   lequal(type(font_quality), "string")
   lequal(font_quality, "high")

   lfail(function()
      Config.get("core.foo") -- not exist
   end)
end)



lrun("test Config.set", function()
   Config.set("core.game.extra_help", false)
   lequal(Config.get("core.game.extra_help"), false)

   Config.set("core.anime.general_wait", 10)
   lequal(Config.get("core.anime.general_wait"), 10)

   Config.set("core.font.quality", "low")
   lequal(Config.get("core.font.quality"), "low")

   lfail(function()
      Config.set("core.foo", 1) -- not exist
   end)

   lfail(function()
      Config.set("core.font.quality", 1) -- invalid type
   end)

   -- Setting nil does nothing.
   Config.set("core.message.transparency", nil)
   lequal(Config.get("core.message.transparency"), 4)
end)
