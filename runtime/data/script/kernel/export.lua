local Export = {}


local pairs, type = pairs, type


local function join_tables(t1, t2)
   for k, v in pairs(t2) do
      t1[k] = v
   end

   return t1
end

local function scan_recursive(seen, exports, current_key)
   local results = {}
   for k, v in pairs(exports) do
      if type(k) == "string" then
         local next_key = current_key.."."..k
         if type(v) == "function" then
            results[next_key] = v
         elseif type(v) == "table" then
            if not seen[v] then
               seen[v] = true
               results = join_tables(results, scan_recursive(seen, v, next_key))
            end
         end
      end
   end
   return results
end

function Export.scan_exports(all_apis)
   local all_exports = {}
   local seen = {}
   for mod_name, api_table in pairs(all_apis) do
      if type(api_table) == "table" then
         for key, value in pairs(scan_recursive(seen, api_table, mod_name)) do
            all_exports[key] = value
         end
      end
   end
   return all_exports
end

return Export
