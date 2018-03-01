local BUFF_TYPE_BUFF = 0
local BUFF_TYPE_HEX = 1
local BUFF_TYPE_FOOD = 2


local function clamp(x, min, max)
  return math.min(math.max(x, min), max)
end

--[[
for i = 0, 20 do
  print(clamp(i, 3, 10))
end
--]]


buff['1'] = {
  type_ = BUFF_TYPE_BUFF,
  duration = function(power)
    return 10 + power // 10
  end,
  _effect = function(power)
    return 25 + power // 15
  end,
}
buff['2'] = {
  type_ = BUFF_TYPE_HEX,
  duration = function(power)
    return 5 + power // 40
  end,
  _effect = function(power)
    return 0
  end,
}
buff['3'] = {
  type_ = BUFF_TYPE_BUFF,
  duration = function(power)
    return 12 + power // 20
  end,
  _effect = function(power)
    return 0
  end,
}
buff['4'] = {
  type_ = BUFF_TYPE_BUFF,
  duration = function(power)
    return 4 + power // 6
  end,
  _effect = function(power)
    return 0
  end,
}
buff['5'] = {
  type_ = BUFF_TYPE_BUFF,
  duration = function(power)
    return 8 + power // 30
  end,
  _effect = function(power)
    return 50 + math.sqrt(power // 5) // 1
  end,
}
buff['6'] = {
  type_ = BUFF_TYPE_HEX,
  duration = function(power)
    return 8 + power // 30
  end,
  _effect = function(power)
    return math.min(20 + power // 20, 50)
  end,
}
buff['7'] = {
  type_ = BUFF_TYPE_BUFF,
  duration = function(power)
    return 10 + power // 4
  end,
  _effect = function(power)
    return 5 + power // 30
  end,
}
buff['8'] = {
  type_ = BUFF_TYPE_HEX,
  duration = function(power)
    return 6 + power // 10
  end,
  _effect = function(power)
    return 0
  end,
}
buff['9'] = {
  type_ = BUFF_TYPE_HEX,
  duration = function(power)
    return 4 + power // 15
  end,
  _effect = function(power)
    return 0
  end,
}
buff['10'] = {
  type_ = BUFF_TYPE_BUFF,
  duration = function(power)
    return 15 + power // 5
  end,
  _effect = function(power)
    return 50 + power // 3 * 2
  end,
}
buff['11'] = {
  type_ = BUFF_TYPE_HEX,
  duration = function(power)
    return 4 + power // 15
  end,
  _effect = function(power)
    return 0
  end,
}
buff['12'] = {
  type_ = BUFF_TYPE_BUFF,
  duration = function(power)
    return 10 + power // 4
  end,
  _effect = function(power)
    return 6 + power // 40, 3 + power // 100
  end,
}
buff['13'] = {
  type_ = BUFF_TYPE_HEX,
  duration = function(power)
    return power
  end,
  _effect = function(power)
    return 20
  end,
}
buff['14'] = {
  type_ = BUFF_TYPE_BUFF,
  duration = function(power)
    return 7
  end,
  _effect = function(power)
    return 155 + power // 5
  end,
}
buff['15'] = {
  type_ = BUFF_TYPE_BUFF,
  duration = function(power)
    return 4 + power // 40
  end,
  _effect = function(power)
    return 0
  end,
}
buff['16'] = {
  type_ = BUFF_TYPE_HEX,
  duration = function(power)
    return 20
  end,
  _effect = function(power)
    return 0
  end,
}
buff['17'] = {
  type_ = BUFF_TYPE_BUFF,
  duration = function(power)
    return 5
  end,
  _effect = function(power)
    return 120
  end,
}
buff['18'] = {
  type_ = BUFF_TYPE_BUFF,
  duration = function(power)
    return 66
  end,
  _effect = function(power)
    return clamp(25 + power // 17, 25, 80)
  end,
}
buff['19'] = {
  type_ = BUFF_TYPE_BUFF,
  duration = function(power)
    return 777
  end,
  _effect = function(power)
    return power
  end,
}
buff['20'] = {
  type_ = BUFF_TYPE_FOOD,
  duration = function(power)
    return 10 + power // 10;
  end,
  _effect = function(power)
    return power
  end,
}
buff['21'] = {
  type_ = BUFF_TYPE_FOOD,
  duration = function(power)
    return 10 + power // 10;
  end,
  _effect = function(power)
    return power
  end,
}
buff['22'] = {
  type_ = BUFF_TYPE_FOOD,
  duration = function(power)
    return 10 + power // 10;
  end,
  _effect = function(power)
    return power
  end,
}
buff['23'] = {
  type_ = BUFF_TYPE_FOOD,
  duration = function(power)
    return 10 + power // 10;
  end,
  _effect = function(power)
    return power
  end,
}
buff['24'] = {
  type_ = BUFF_TYPE_FOOD,
  duration = function(power)
    return 10 + power // 10;
  end,
  _effect = function(power)
    return power
  end,
}
buff['25'] = {
  type_ = BUFF_TYPE_FOOD,
  duration = function(power)
    return 10 + power // 10;
  end,
  _effect = function(power)
    return power
  end,
}
buff['26'] = {
  type_ = BUFF_TYPE_FOOD,
  duration = function(power)
    return 10 + power // 10;
  end,
  _effect = function(power)
    return power
  end,
}
buff['27'] = {
  type_ = BUFF_TYPE_FOOD,
  duration = function(power)
    return 10 + power // 10;
  end,
  _effect = function(power)
    return power
  end,
}
buff['28'] = {
  type_ = BUFF_TYPE_FOOD,
  duration = function(power)
    return 10 + power // 10;
  end,
  _effect = function(power)
    return power
  end,
}

-- vim: et sw=2 sts=2
