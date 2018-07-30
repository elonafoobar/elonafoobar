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
  on_refresh = function(self, cc, power, turn)
    cdata(cc):pv(cdata(cc):pv() + self._effect(power))
    cdata(cc):fear(0)
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
  on_refresh = function(self, cc, power, turn)
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
  on_refresh = function(self, cc, power, turn)
    sdata(154, cc):current_level(sdata(154, cc):current_level() + 40)
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
  on_refresh = function(self, cc, power, turn)
    sdata(50, cc):current_level(sdata(50, cc):current_level() + 100)
    sdata(51, cc):current_level(sdata(51, cc):current_level() + 100)
    sdata(52, cc):current_level(sdata(52, cc):current_level() + 100)
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
  on_refresh = function(self, cc, power, turn)
    sdata(18, cc):current_level(sdata(18, cc):current_level() + self._effect(power))
  end,
  _effect = function(power)
    return math.modf(50 + math.sqrt(power // 5))
  end,
}
buff['6'] = {
  type_ = BUFF_TYPE_HEX,
  duration = function(power)
    return 8 + power // 30
  end,
  on_refresh = function(self, cc, power, turn)
    sdata(18, cc):current_level(sdata(18, cc):current_level() - self._effect(power))
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
  on_refresh = function(self, cc, power, turn)
    sdata(10, cc):current_level(sdata(10, cc):current_level() + self._effect(power))
    sdata(12, cc):current_level(sdata(12, cc):current_level() + self._effect(power))
    cdata(cc):fear(0)
    cdata(cc):confused(0)
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
  on_refresh = function(self, cc, power, turn)
    cdata(cc):dv(cdata(cc):dv() // 2)
    cdata(cc):pv(cdata(cc):pv() // 2)
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
  on_refresh = function(self, cc, power, turn)
    sdata(50, cc):current_level(
      clamp(sdata(50, cc):current_level() - 100, sdata(50, cc):current_level() and 1 or 0, 9999))
    sdata(51, cc):current_level(
      clamp(sdata(51, cc):current_level() - 100, sdata(51, cc):current_level() and 1 or 0, 9999))
    sdata(52, cc):current_level(
      clamp(sdata(52, cc):current_level() - 100, sdata(52, cc):current_level() and 1 or 0, 9999))
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
  on_refresh = function(self, cc, power, turn)
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
  on_refresh = function(self, cc, power, turn)
    sdata(58, cc):current_level(
      clamp(sdata(58, cc):current_level() - 100, sdata(58, cc):current_level() and 1 or 0, 9999))
    sdata(54, cc):current_level(
      clamp(sdata(54, cc):current_level() - 100, sdata(54, cc):current_level() and 1 or 0, 9999))
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
  on_refresh = function(self, cc, power, turn)
    local a, b = self._effect(power)
    sdata(14, cc):current_level(sdata(14, cc):current_level() + a)
    sdata(16, cc):current_level(sdata(16, cc):current_level() + a)
    sdata(150, cc):current_level(sdata(150, cc):current_level() + b)
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
  on_refresh = function(self, cc, power, turn)
    sdata(18, cc):current_level(sdata(18, cc):current_level() - self._effect(power))
    if cdata(cc):pv() > 1 then
      cdata(cc):pv(cdata(cc):pv() - cdata(cc):pv() // 5)
    end
  end,
  _effect = function(power)
    return 20, 20
  end,
}
buff['14'] = {
  type_ = BUFF_TYPE_BUFF,
  duration = function(power)
    return 7
  end,
  on_refresh = function(self, cc, power, turn)
    sdata(18, cc):current_level(sdata(18, cc):current_level() + self._effect(power))
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
  on_refresh = function(self, cc, power, turn)
    cbitmod(16, cc, 1)
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
  on_refresh = function(self, cc, power, turn)
    cbitmod(973, cc, 1)
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
  on_refresh = function(self, cc, power, turn)
    sdata(18, cc):current_level(sdata(18, cc):current_level() + self._effect(power))
    sdata(10, cc):current_level(sdata(10, cc):current_level() * 150 // 100 + 10)
    sdata(12, cc):current_level(sdata(12, cc):current_level() * 150 // 100 + 10)
    sdata(154, cc):current_level(sdata(154, cc):current_level() + 50)
    cdata(cc):pv(cdata(cc):pv() * 150 // 100 + 25)
    cdata(cc):dv(cdata(cc):dv() * 150 // 100 + 25)
    cdata(cc):hit_bonus(cdata(cc):hit_bonus() * 150 // 100 + 50)
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
  on_refresh = function(self, cc, power, turn)
    cbitmod(980, cc, 1)
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
  on_refresh = function(self, cc, power, turn)
    sdata(19, cc):current_level(sdata(19, cc):current_level() + self._effect(power))
  end,
  _effect = function(power)
    return power
  end,
}
buff['20'] = {
  type_ = BUFF_TYPE_FOOD,
  duration = function(power)
    return 10 + power // 10
  end,
  on_refresh = function(self, cc, power, turn)
    cdata(cc):growth_buffs(0, self._effect(power))
  end,
  _effect = function(power)
    return power
  end,
}
buff['21'] = {
  type_ = BUFF_TYPE_FOOD,
  duration = function(power)
    return 10 + power // 10
  end,
  on_refresh = function(self, cc, power, turn)
    cdata(cc):growth_buffs(1, self._effect(power))
  end,
  _effect = function(power)
    return power
  end,
}
buff['22'] = {
  type_ = BUFF_TYPE_FOOD,
  duration = function(power)
    return 10 + power // 10
  end,
  on_refresh = function(self, cc, power, turn)
    cdata(cc):growth_buffs(2, self._effect(power))
  end,
  _effect = function(power)
    return power
  end,
}
buff['23'] = {
  type_ = BUFF_TYPE_FOOD,
  duration = function(power)
    return 10 + power // 10
  end,
  on_refresh = function(self, cc, power, turn)
    cdata(cc):growth_buffs(3, self._effect(power))
  end,
  _effect = function(power)
    return power
  end,
}
buff['24'] = {
  type_ = BUFF_TYPE_FOOD,
  duration = function(power)
    return 10 + power // 10
  end,
  on_refresh = function(self, cc, power, turn)
    cdata(cc):growth_buffs(4, self._effect(power))
  end,
  _effect = function(power)
    return power
  end,
}
buff['25'] = {
  type_ = BUFF_TYPE_FOOD,
  duration = function(power)
    return 10 + power // 10
  end,
  on_refresh = function(self, cc, power, turn)
    cdata(cc):growth_buffs(5, self._effect(power))
  end,
  _effect = function(power)
    return power
  end,
}
buff['26'] = {
  type_ = BUFF_TYPE_FOOD,
  duration = function(power)
    return 10 + power // 10
  end,
  on_refresh = function(self, cc, power, turn)
    cdata(cc):growth_buffs(6, self._effect(power))
  end,
  _effect = function(power)
    return power
  end,
}
buff['27'] = {
  type_ = BUFF_TYPE_FOOD,
  duration = function(power)
    return 10 + power // 10
  end,
  on_refresh = function(self, cc, power, turn)
    cdata(cc):growth_buffs(7, self._effect(power))
  end,
  _effect = function(power)
    return power
  end,
}
buff['28'] = {
  type_ = BUFF_TYPE_FOOD,
  duration = function(power)
    return 10 + power // 10
  end,
  on_refresh = function(self, cc, power, turn)
    cdata(cc):growth_buffs(8, self._effect(power))
  end,
  _effect = function(power)
    return power
  end,
}
buff['29'] = {
  type_ = BUFF_TYPE_FOOD,
  duration = function(power)
    return 10 + power // 10
  end,
  on_refresh = function(self, cc, power, turn)
    cdata(cc):growth_buffs(9, self._effect(power))
  end,
  _effect = function(power)
    return power
  end,
}

-- vim: et sw=2 sts=2
