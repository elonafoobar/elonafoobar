require("tests/lua/support/minctest")

local Enums = require("core.Enums")

lrun("test Enums.new_enum", function()
   local Vanilla = Enums.new_enum {
      stable = 1160,
      xmas = 1161,
      develop = 1220,
   }

   lequal(Vanilla:is_valid_value(1160), true)
   lequal(Vanilla:is_valid_value(42), false)
   lequal(Vanilla:is_valid_name("develop"), true)
   lequal(Vanilla:is_valid_name("nyan"), false)
end)

lrun("test known enums", function()
   lequal(Enums.CurseState.BLESSED, 1)
   lequal(Enums.Quality[5], "GODLY")
   lequal(Enums.IdentifyState.invalid, nil)
end)
