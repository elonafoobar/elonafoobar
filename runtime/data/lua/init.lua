--- WARNING: This file is always implicitly loaded by C++.
--- Don't change anything here unless you know what you're doing!

Elona.core.Debug.inspect = require "inspect"
Elona.core.HCL = require "hclua"
Elona.core.Iter = require "iter"
Elona.core.Math = require "math_ext"
Elona.core.ReadOnly = require "readonly"
Elona.core.table = require "table_ext"

-- TEMP
Elona.core.I18N.register_function("name", function() return "Dood" end)

_LOADED = true
