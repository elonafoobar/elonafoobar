inspect = require "mods/core/inspect"

-- Automatically import the core API tables.
for name, data in pairs(_API_TABLES) do
   _G[name] = data
end

_API_TABLES = nil
