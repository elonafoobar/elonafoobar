print("yo")
local function merge(a, b)
  for k, v in pairs(b) do
    if type(v) == 'table' then
      if type(a[k]) == 'table' then
        merge(a[k] or {}, b[k] or {})
      else
        a[k] = v
      end
    else
      a[k] = v
    end
  end
  return a
end



local DataStorage = {}

DataStorage.new = function()
  local self = { __storage__ = {} }

  setmetatable(self, {
    __newindex = function(table, key, value)
      if type(value) == 'table' then
        rawset(table.__storage__, key, merge(table.__storage__[key] or {}, value))
      else
        rawset(table.__storage__, key, value)
      end
    end,
    __index = function(table, key)
      return table.__storage__[key]
    end,
  })

  return self
end


ability = DataStorage.new()
buff = DataStorage.new()
character = DataStorage.new()
class = DataStorage.new()
fish = DataStorage.new()
god = DataStorage.new()
item = DataStorage.new()
item_material = DataStorage.new()
race = DataStorage.new()
trait = DataStorage.new()
ui = DataStorage.new()


-- vim: et sw=2 sts=2
