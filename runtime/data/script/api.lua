local Api = {}

local API_TABLE = {}

function Api.register(module_path, table)
   -- TODO: duplicate check?
   API_TABLE[module_path] = table
end

function Api.merge_core_module(module_path, table)
   local existing_table = API_TABLE[module_path]
   if existing_table then
      for k, v in pairs(table) do
         existing_table[k] = v
      end
   else
      Api.register(module_path, table)
   end
end

function Api.require(module_path)
   log_trace("require('"..module_path.."')")
   local ret = API_TABLE[module_path]
   if ret == nil then
      -- TBD: error()
      return ret
   else
      return ret
   end
end

return Api
