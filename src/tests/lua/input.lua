require "tests/lua/support/minctest"

local Input = Elona.require("Input")

lrun("test Input.prompt_choice", function()
        lequal(Input.prompt_choice(), nil)
end)

lrun("test Input.prompt_number", function()
        lequal(Input.prompt_number("", -1), nil)
end)
