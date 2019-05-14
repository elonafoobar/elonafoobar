local data = { _table = {} }
function data:add_multi(tbl)
   for _, v in ipairs(tbl) do
      self:add(v)
   end
end
function data:add(data)
   self._table[data.id] = data
end


local GUI = Elona.require("GUI")

data:add(
   {
      type = "core.map_object",
      id = "voting_box",
      legacy_id = 31,
      on_activate = function() GUI.snd("core.chat") end
   }
)


return { ["core.map_object"] = data._table }
