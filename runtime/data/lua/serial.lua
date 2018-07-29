local Handle = require "handle"
local serpent = require "serpent"

local Serial = {}

Serial.save = serpent.dump
Serial.load = serpent.load

return Serial
