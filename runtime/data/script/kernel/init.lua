--- WARNING: This file is always implicitly loaded by C++.
--- Don't change anything here unless you know what you're doing!

Elona.game.Debug.inspect = require_relative("inspect").inspect
Elona.game.HCL = require_relative("hclua")
Elona.game.Iter = require_relative("iter")
Elona.game.ReadOnly = require_relative("readonly")
Elona.game.string = require_relative("string")

Elona.game.Math = require_relative("math_ext")
Elona.game.table = require_relative("table_ext")
Elona.game.coroutine = require_relative("coroutine")

_LOADED = true
