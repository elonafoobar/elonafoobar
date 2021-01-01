local core = {}

core.audio = require("audio")
core.data = require("data")
core.enums = require("enums")
core.env = require("env")
core.graphics = require("graphics")
core.i18n = require("i18n")
core.ui = require("ui")

local config = require("config")
core.config = { get = config.get, set = config.set, save = config.save }

return core
