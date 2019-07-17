local function join_tables(t1, t2)
   for k, v in pairs(t2) do
      t1[k] = v
   end

   return t1
end

local function scan_recursive(exports, current_key)
   local results = {}
   for k, v in pairs(exports) do
      if type(k) == "string" then
         local next_key = current_key .. "." .. k
         if type(v) == "function" then
            results[next_key] = v
         elseif type(v) == "table" then
            results = join_tables(results, scan_recursive(v, next_key))
         end
      end
   end
   return results
end

local function scan_exports(all_apis)
   local all_exports = {}
   for mod_name, api_table in pairs(all_apis) do
      local exports = api_table["Exports"]
      if exports ~= nil and type(exports) == "table" then
         for key, value in pairs(scan_recursive(exports, mod_name)) do
            all_exports[key] = value
         end
      end
   end
   return all_exports
end

return scan_exports
