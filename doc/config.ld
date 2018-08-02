--luacheck: ignore
project = "Lua API"
title = "Lua API"
description = "Elona foobar Mod API"
full_description = [[
  Core API for modding Elona foobar
]]
no_lua_ref = true
convert_opt = true
sort = false
no_return_or_parms = false
not_luadoc = true
merge = false
backtick_references = false
format = "discount"
template_escape = ">"
dir = "./doc"
examples = {"./doc/examples"}
topics = {"./doc/readme.md", "./doc/topics/i18n.md", "./doc/topics/i18n_functions.md"}

new_type("event", "Events", false, "Event Parameters")
new_type("enum", "Enums", false, "Enum Values")

custom_see_handler("^(http[s]?%:%/%/.-) (.+)$",
    function(url, name)
        return name, url
    end
)

local lua_url = "https://www.lua.org/pil/%s.html%s"

custom_see_handler("^nil$", function() return "nil", lua_url:format("2.1", "") end)
custom_see_handler("^number$", function() return "number", lua_url:format("2.3", "") end)
custom_see_handler("^table$", function() return "table", lua_url:format("2.5", "") end)
custom_see_handler("^function$", function() return "function", lua_url:format("2.6", "") end)
custom_see_handler("^userdata$", function() return "userdata", lua_url:format("2.7", "") end)
custom_see_handler("^array$", function() return "array", lua_url:format("11.1", "") end)
custom_see_handler("^iterator$", function() return "iterator", lua_url:format("7.3", "") end)

