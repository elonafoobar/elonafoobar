local a = require("data/script.lua")
local b = require("data/script.lua")

assert(a.value() == 0)
assert(b.value() == 0)

a.increment_locally()

assert(a.value() == 1)
assert(b.value() == 1)

local c = require("data/script2.lua")
assert(c.abs == "abs")
assert(c.rel == "rel")
