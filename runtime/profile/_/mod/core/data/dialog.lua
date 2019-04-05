local data = { _table = {} }
function data:add_multi(tbl)
   for _, v in ipairs(tbl) do
      self:add(v)
   end
end
function data:add(data)
   self._table[data.id] = data
end



local unique = require("data/dialog/unique")

data:add_multi(
   {
      {
         id = "ignored",
         root = "core.locale.talk",
         nodes = {
            __start = {
               text = {
                  {"ignores_you", args = function(t) return {t.speaker} end},
               }
            },
         }
      }
   }
)
data:add_multi(unique)



return { ["core.dialog"] = data._table }
