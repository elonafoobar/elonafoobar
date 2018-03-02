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




local cnt = -1

function keymacro(original_key)
  cnt = cnt + 1
  local n = cnt % 2
  local ret
  if n == 0 then
    ret = "v"
  elseif n == 1 then
    ret = "a"
  end
  if cnt >= 1000 then
    return "n"
  end
  return ret
end



-- vim: et sw=2 sts=2
