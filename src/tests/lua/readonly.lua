require("tests/lua/support/minctest")

lrun("test API tables are readonly", function()
        local Rand = require("core.Rand")
        lok(not pcall(function() Rand.rnd = nil end), "API table wasn't read only")
end)
