local core = {}

core.Audio = require("audio")
core.Config = require("config")
core.Data = require("data")
core.Enums = require("enums")
core.Env = require("env")
core.Graphics = require("graphics")
core.I18n = require("i18n")
core.UI = require("ui")

local Config = require("config")
core.Config = { get = Config.get, set = Config.set }

return core
