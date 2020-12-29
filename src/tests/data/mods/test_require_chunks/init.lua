local a = require_relative("data/script.lua")
local b = require_relative("data/script.lua")

assert(a.value() == 0)
assert(b.value() == 0)

a.increment_locally()

assert(a.value() == 1)
assert(b.value() == 1)

local c = require_relative("data/script2.lua")
assert(c.abs == "abs")
assert(c.rel == "rel")
