local function join_tables(t1, t2)
   for k, v in pairs(t2) do
      t1[k] = v
   end

   return t1
end

local function scan_recursive(exports, current_key)
   local results = {}
   for k, v in pairs(exports) do
      if type(k) ~= "string" then
         error("Export function names must be strings.")
      end
      local next_key = current_key .. "." .. k
      if type(v) == "table" then
         results = join_tables(results, scan_recursive(v, next_key))
      elseif type(v) == "function" then
         results[next_key] = v
      end
   end
   return results
end

local function scan_exports(all_apis)
   local all_exports = {}
   for mod_name, api_table in pairs(all_apis) do
      local exports = api_table["Exports"]
      if exports ~= nil and type(exports) == "table" then
         local base_key = "exports:" .. mod_name
         for key, value in pairs(scan_recursive(exports, base_key)) do
            print("add export " .. key)
            all_exports[key] = value
         end
      end
   end
   print("done\n")
   return all_exports
end

return scan_exports
