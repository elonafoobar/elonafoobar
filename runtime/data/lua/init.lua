--- WARNING: This file is always implicitly loaded by C++.
--- Don't change anything here unless you know what you're doing!

Elona.core.Debug.inspect = require "data/lua/inspect"
Elona.core.Iter = require "data/lua/iter"
Elona.core.ReadOnly = require "data/lua/readonly"
Elona.core.HCL = require "data/lua/hclua"
Elona.core.table = require "data/lua/table"

-- All the core API tables should be loaded by now, so we can make
-- them all read-only to prevent user code from modifying them.
Elona.core = Elona.core.ReadOnly.make_read_only(Elona.core)

_LOADED = true
