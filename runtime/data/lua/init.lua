--- WARNING: This file is always implicitly loaded by C++.
--- Don't change anything here unless you know what you're doing!

Elona.core.Debug.inspect = require "inspect"
Elona.core.Enums = require "enums"
Elona.core.HCL = require "hclua"
Elona.core.Iter = require "iter"
Elona.core.ReadOnly = require "readonly"
Elona.core.table = require "table"

-- All the core API tables should be loaded by now, so we can make
-- them all read-only to prevent user code from modifying them.
Elona.core = Elona.core.ReadOnly.make_read_only(Elona.core)

_LOADED = true
