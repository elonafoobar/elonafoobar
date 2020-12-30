local api = {}

local API_TABLE = {}

function api.register(module_path, table)
   -- TODO: duplicate check?
   API_TABLE[module_path] = table
end

function api.merge_core_module(module_path, table)
   local existing_table = API_TABLE[module_path]
   if existing_table then
      for k, v in pairs(table) do
         existing_table[k] = v
      end
   else
      api.register(module_path, table)
   end
end

function api.require(module_path)
   log_trace("require('"..module_path.."')")
   local ret = API_TABLE[module_path]
   if ret == nil then
      -- TBD: error()
      return ret
   else
      return ret
   end
end

return api
