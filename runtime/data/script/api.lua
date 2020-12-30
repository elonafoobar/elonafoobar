local Api = {}

local api_table = {}

function Api.register(module_path, table)
   -- TODO: duplicate check?
   api_table[module_path] = table
end

function Api.require(module_path)
   log_trace("ELONA.require('"..module_path.."')")
   local ret = api_table[module_path]
   if ret == nil then
      -- TBD: error()
      return ret
   else
      return ret
   end
end

return Api
