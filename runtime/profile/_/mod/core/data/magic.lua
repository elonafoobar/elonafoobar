local data = { _table = {} }
function data:add_multi(tbl)
   for _, v in ipairs(tbl) do
      self:add(v)
   end
end
function data:add(data)
   self._table[data.id] = data
end

local magic = require("data/magic/magic")

data:add_multi(
   {
      {
         type = "core.magic",
         id = "eye_of_insanity",
         legacy_id = 636,
         callback = magic.eye_of_insanity
      }
   }
)

return { ["core.magic"] = data._table }
