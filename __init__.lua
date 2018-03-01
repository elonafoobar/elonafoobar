local function merge(a, b)
  for k, v in pairs(b) do
    if type(v) == 'table' then
      if type(a[k] or nil) == 'table' then
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


local metatable = {
  __newindex = function(table, key, value)
    if type(value) == 'table' then
      rawset(table, key, merge(table[key] or {}, value or {}))
    else
      rawset(table, key, value)
    end
  end
}


ability = {}
setmetatable(ability, metatable)

buff = {}
setmetatable(buff, metatable)

character = {}
setmetatable(character, metatable)

class = {}
setmetatable(class, metatable)

item = {}
setmetatable(item, metatable)

race = {}
setmetatable(race, metatable)

trait = {}
setmetatable(trait, metatable)

god = {}
setmetatable(god, metatable)

ui = {}
setmetatable(ui, metatable)


-- vim: et sw=2 sts=2
