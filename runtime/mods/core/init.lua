--- WARNING: This mod is always implicitly loaded by C++.
--- Don't change anything here unless you know what you're doing!

Elona.core.Debug.inspect = require "mods/core/inspect"
Elona.core.Iter = require "mods/core/iter"
Elona.core.ReadOnly = require "mods/core/readonly"
Elona.core.table = require "mods/core/table"

-- All the core API tables should be loaded by now, so we can make
-- them all read-only to prevent user code from modifying them.
Elona.core = Elona.core.ReadOnly.make_read_only(Elona.core)

_LOADED = true
