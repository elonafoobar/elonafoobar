buff = buff or {}

local function clamp(x, min, max)
  return math.min(math.max(x, min), max)
end


buff['1'] = {
  name = "Holy Shield",
  message_0 = "begin",
  message_1 = " to shine.",
  description = function(power)
    return "Increases PV by " .. tostring(25 + power // 15) .. "/RES+ fear"
  end,
}
buff['2'] = {
  name = "Mist of Silence",
  message_0 = "get",
  message_1 = " surrounded by hazy mist.",
  description = function(power)
    return "Inhibits casting"
  end,
}
buff['3'] = {
  name = "Regeneration",
  message_0 = "start",
  message_1 = " to regenerate.",
  description = function(power)
    return "Enhances regeneration"
  end,
}
buff['4'] = {
  name = "Elemental Shield",
  message_0 = "obtain",
  message_1 = " resistance to element.",
  description = function(power)
    return "RES+ fire,cold,lightning"
  end,
}
buff['5'] = {
  name = "Speed",
  message_0 = "speed",
  message_1 = " up.",
  description = function(power)
    return "Increases speed by " .. tostring(50 + math.sqrt(power // 5) // 1)
  end,
}
buff['6'] = {
  name = "Slow",
  message_0 = "slow",
  message_1 = " down.",
  description = function(power)
    return "Decreases speed by " .. tostring(math.min(20 + power // 20, 50))
  end,
}
buff['7'] = {
  name = "Hero",
  message_0 = "feel",
  message_1 = " heroic.",
  description = function(power)
    return "Increases STR,DEX by " .. tostring(5 + power // 30) .. "/RES+ fear,confusion"
  end,
}
buff['8'] = {
  name = "Mist of Frailness",
  message_0 = "feel",
  message_1 = " weak.",
  description = function(power)
    return "Halves DV and PV"
  end,
}
buff['9'] = {
  name = "Element Scar",
  message_0 = "lose",
  message_1 = " resistance to element.",
  description = function(power)
    return "RES- fire,cold,lightning"
  end,
}
buff['10'] = {
  name = "Holy Veil",
  message_0 = "receive",
  message_1 = " holy protection.",
  description = function(power)
    return "grants hex protection(power:" .. tostring(50 + power // 3 * 2) .. ")"
  end,
}
buff['11'] = {
  name = "Nightmare",
  message_0 = "start",
  message_1 = " to suffer.",
  description = function(power)
    return "RES- mind,nerve"
  end,
}
buff['12'] = {
  name = "Divine Wisdom",
  message_0 = "start",
  message_1 = " to think clearly.",
  description = function(power)
    return "Increases LER,MAG by " .. tostring(6 + power // 40) .. ", literacy skill by " .. tostring(3 + power // 100)
  end,
}
buff['13'] = {
  name = "Punishment",
  message_0 = "incur",
  message_1 = " the wrath of God.",
  description = function(power)
    return "Decreases speed by 20, PV by 20%"
  end,
}
buff['14'] = {
  name = "Lulwy's Trick",
  message_0 = "repeat",
  message_1 = "the name of Lulwy.",
  description = function(power)
    return "Increases speed by " .. tostring(155 + power // 5)
  end,
}
buff['15'] = {
  name = "Incognito",
  message_0 = "start",
  message_1 = " to disguise.",
  description = function(power)
    return "Grants new identify"
  end,
}
buff['16'] = {
  name = "Death Word",
  message_0 = "receive",
  message_1 = " death verdict.",
  description = function(power)
    return "Guaranteed death when the hex ends"
  end,
}
buff['17'] = {
  name = "Boost",
  message_0 = "gain",
  message_1 = " massive power.",
  description = function(power)
    return "Increases speed by 120/Boosts physical attributes"
  end,
}
buff['18'] = {
  name = "Contingency",
  message_0 = "set",
  message_1 = " up contracts with the Reaper.",
  description = function(power)
    return tostring(clamp(25 + power // 17, 25, 80)) .. "% chances taking a lethal damage heals you instead"
  end,
}
buff['19'] = {
  name = "Luck",
  message_0 = "feel",
  message_1 = " very lucky today!",
  description = function(power)
    return "Increase luck by " .. tostring(power) .. "."
  end,
}
buff['20'] = {
  name = "Grow Strength",
  message_0 = "",
  message_1 = " magical effect.",
  description = function(power)
    return "Increases the growth rate " .. ability['10'].name .. " by " .. tostring(power)
  end,
}
buff['21'] = {
  name = "Grow Endurance",
  message_0 = "",
  message_1 = " magical effect.",
  description = function(power)
    return "Increases the growth rate " .. ability['10'].name .. " by " .. tostring(power)
  end,
}
buff['22'] = {
  name = "Grow Dexterity",
  message_0 = "",
  message_1 = " magical effect.",
  description = function(power)
    return "Increases the growth rate " .. ability['10'].name .. " by " .. tostring(power)
  end,
}
buff['23'] = {
  name = "Grow Perception",
  message_0 = "",
  message_1 = " magical effect.",
  description = function(power)
    return "Increases the growth rate " .. ability['10'].name .. " by " .. tostring(power)
  end,
}
buff['24'] = {
  name = "Grow Learning",
  message_0 = "",
  message_1 = " magical effect.",
  description = function(power)
    return "Increases the growth rate " .. ability['10'].name .. " by " .. tostring(power)
  end,
}
buff['25'] = {
  name = "Grow Will",
  message_0 = "",
  message_1 = " magical effect.",
  description = function(power)
    return "Increases the growth rate " .. ability['10'].name .. " by " .. tostring(power)
  end,
}
buff['26'] = {
  name = "Grow Magic",
  message_0 = "",
  message_1 = " magical effect.",
  description = function(power)
    return "Increases the growth rate " .. ability['10'].name .. " by " .. tostring(power)
  end,
}
buff['27'] = {
  name = "Grow Charisma",
  message_0 = "",
  message_1 = " magical effect.",
  description = function(power)
    return "Increases the growth rate " .. ability['10'].name .. " by " .. tostring(power)
  end,
}
buff['28'] = {
  name = "Grow Speed",
  message_0 = "",
  message_1 = " magical effect.",
  description = function(power)
    return "Increases the growth rate " .. ability['10'].name .. " by " .. tostring(power)
  end,
}


-- vim: et sw=2 sts=2
