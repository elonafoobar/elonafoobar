require "tests/lua/support/minctest"

local Input = Elona.require("Input")

lrun("test Input.prompt_choice", function()
        lok(not pcall(function() Input.prompt_choice() end), "Error not thrown")
end)

lrun("test Input.prompt_number", function()
        lok(not pcall(function() Input.prompt_number("", -1) end), "Error not thrown")
end)
