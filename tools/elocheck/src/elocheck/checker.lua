local scanner = require "elocheck.scanner"
local utils = require "elocheck.utils"
local inspect = require "inspect"

local sfind = string.find
local sgmatch = string.gmatch
local sgsub = string.gsub

local checker = {}

local function remove_quotes(s)
   return sgsub(s, "\"(.*)\"", "%1")
end

local function capture_strings(arg_string)
   local strings = {}

   for match in sgmatch(arg_string, "\".*\"") do
      strings[#strings+1] = remove_quotes(match)
   end

   return strings
end

local dispatchers = {}

local function try_get_key(args)
   local strings = capture_strings(args[1])
   local locale_key = strings[1]
   if locale_key and sfind(locale_key, "core%.locale%.") then
      return locale_key
   end
   return nil
end

local function try_get_enum_index(arg)
   if not arg then
      return nil
   end

   -- get max index based on integer argument
   if sfind(arg, "^%d+$") then
      return tonumber(arg)
   end

   -- get max index based on call to rnd(n)
   if sfind(arg, "^rnd%(%d+%)$") then
      local number = sgsub(arg, "^rnd%((%d+)%)$", "%1")
      return tonumber(number) - 1
   end

   return nil
end

local function get_max_enum_value(locale_table, key_head)
   local i = 0

   while true do
      if not locale_table[key_head .. "._" .. tostring(i)] then
         break
      end
      i = i + 1
   end

   return i - 1
end

local function check_get(locale_table, args)
   local results = {}
   local locale_key = try_get_key(args)
   if locale_key then
      if locale_table[locale_key] == nil then
         results[#results+1] = {key = locale_key,
                                kind = "error",
                                msg = "Translation found in code but not in store"}
      else
         locale_table[locale_key].used = true
      end
   end

   return results
end

local function check_enum(locale_table, locale_key, index_stmt, property)
   local results = {}
   local max_enum_value = get_max_enum_value(locale_table, locale_key)
   local index = try_get_enum_index(index_stmt)

   if index then
      if index > max_enum_value then
         results[#results+1] = {key = locale_key,
                                kind = "warning",
                                msg = "Argument may be greater than enum max " ..
                                   "(" .. index_stmt .. " > " .. max_enum_value .. ")"}
      end

      if property then
         if not locale_table[locale_key .. "._0." .. property] then
            results[#results+1] = {key = locale_key,
                                   kind = "warning",
                                   msg = "Enum property \"" .. property .. "\" may be missing (on index 0)"}
         end
      end
   else
      if max_enum_value == -1 then
         results[#results+1] = {key = locale_key,
                                kind = "warning",
                                msg = "Key was declared as enum but no element '_0' was found"}
      else
         results[#results+1] = {key = locale_key,
                                kind = "warning",
                                msg = "Unable to introspect enum max. Manually verify that "
                                   .. "(" .. index_stmt .. " <= " .. max_enum_value .. ")"}
      end
   end

   return results
end

local function check_get_enum(locale_table, args)
   local locale_key = try_get_key(args)
   local results = {}
   if locale_key then
      if locale_table[locale_key] == nil then
         results[#results+1] = {key = locale_key,
                                kind = "error",
                                msg = "Translation found in code but not in store"}
      else
         locale_table[locale_key].used = true
         return check_enum(locale_table, locale_key, args[2])
      end
   end
   return results
end

local function check_get_property(locale_table, args)
   local locale_key = try_get_key(args)
   local results = {}
   if locale_key then
         if sfind(locale_key, "death_by") then
            print(locale_key)
         end
      if locale_table[locale_key] == nil then
         results[#results+1] = {key = locale_key,
                                kind = "error",
                                msg = "Translation found in code but not in store"}
      else
         locale_table[locale_key].used = true
         return check_enum(locale_table, locale_key, args[3], remove_quotes(args[2]))
      end
   end
   return results
end

dispatchers["i18n::s.get"] = check_get
dispatchers["i18n::s.get_optional"] = check_get

dispatchers["i18n::s.get_enum"] = check_get_enum
dispatchers["i18n::s.get_enum_optional"] = check_get_enum

dispatchers["i18n::s.get_enum_property"] = check_get_property
dispatchers["i18n::s.get_enum_property_opt"] = check_get_property

dispatchers["i18n::s.init"] = function() return {} end
dispatchers["i18n::s.load"] = function() return {} end

-- Checks an input .cpp source for missing translations. Also marks
-- the translations found in the locale table.
-- Returns the issues found.
local function check(locale_table, source)
   local state = scanner.new(source)
   local results = {}

   while true do
      local result = state:scan("i18n::s%.")

      if result ~= nil then
         if result.args[1] then
            local dispatcher = dispatchers[result.name]
            if not dispatcher then
               error("Unknown function: " .. result.name)
            end
            local new_results = dispatcher(locale_table, result.args)

            for _, res in pairs(new_results) do
               local loc = state:location()
               res.line = loc.line
               res.column = loc.column
            end

            results = utils.merge(results, new_results)
         end
      end

      if state:peek() == nil then
         break
      end
   end

   return results
end

function checker.get_report(locale_table)
   return function(source)
      return check(locale_table, source.text)
   end
end

return checker
