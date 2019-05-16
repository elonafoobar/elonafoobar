--- WARNING: This file is always implicitly loaded by C++.
--- Don't change anything here unless you know what you're doing!

Elona.core.Debug.inspect = require("inspect").inspect
Elona.core.HCL = require "hclua"
Elona.core.Iter = require "iter"
Elona.core.ReadOnly = require "readonly"
Elona.core.string = require "string"

Elona.core.table = require "table_ext"
Elona.core.coroutine = require "coroutine"
Elona.core.Math = Elona.core.table.merge(require "math_ext", Elona.core.Math)

_LOADED = true
