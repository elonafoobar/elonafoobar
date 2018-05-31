require "tests/lua/support/minctest"

stds = {}
files = {} -- so the below dofile doesn't error out

-- Load all global tables that are defined inside the .luacheckrc, including "stds"
dofile(".luacheckrc")

local function test_all_tables_defined()
   lrun("test that all API tables are defined in .luacheckrc ", function()
           for table_name, _ in pairs(stds.elona.read_globals.Elona.fields) do
              lok(Elona.require(table_name) ~= nil,
                  "Table Elona." .. table_name .. " defined in .luacheckrc but undefined in Lua")
           end
   end)
end

test_all_tables_defined()

assert(lresults())
