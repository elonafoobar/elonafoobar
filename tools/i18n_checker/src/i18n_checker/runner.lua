local checker = require "i18n_checker.checker"
local format = require "i18n_checker.format"
local fs = require "i18n_checker.fs"
local locale = require "i18n_checker.locale"
local utils = require "i18n_checker.utils"
local inspect = require "inspect"

local sformat = string.format
local sfind = string.find

local runner = {}

local function validate_inputs(inputs)
   if type(inputs) ~= "table" then
      return nil, ("inputs table expected, got %s"):format(inputs)
   end

   for index, input in ipairs(inputs) do
      local context = ("invalid input table at index [%d]"):format(index)

      if type(input) ~= "table" then
         return nil, ("%s: table expected, got %s"):format(context, type(input))
      end

      local specifies_source

      for _, field in ipairs({"file", "path"}) do
         if input[field] ~= nil then
            if field == "file" then
               if io.type(input[field]) ~= "file" then
                  return nil, ("%s: invalid field 'file': open file expected, got %s"):format(
                     context, type(input[field]))
               end
            end
         end

         specifies_source = true
      end

      if not specifies_source then
         return nil, ("%s: one of fields 'path' or 'file' must be present"):format(context)
      end
   end

   return true
end

local function prepare_inputs(inputs, dir_pattern)
   local current_dir = fs.get_current_dir()

   local res = {}

   local function add(input)
      if input.path then
         input.path = input.path:gsub("^%.[/\\]([^/])", "%1")
         input.abs_path = fs.normalize(fs.join(current_dir, input.path))
      end

      local abs_filename

      if input.filename then
         abs_filename = fs.normalize(fs.join(current_dir, input.filename))
      else
         input.filename = input.path
         abs_filename = input.abs_path
      end

      table.insert(res, input)
   end

   for _, input in ipairs(inputs) do
      if input.path then
         if fs.is_dir(input.path) then
            local filenames, err_map = fs.extract_files(input.path, dir_pattern)

            for _, filename in ipairs(filenames) do
               local err = err_map[filename]
               if err then
                  add({path = filename, fatal = "I/O", msg = err, filename = input.filename})
               else
                  add({path = filename, filename = input.filename})
               end
            end
         else
            add({path = input.path, filename = input.filename})
         end
      elseif input.file then
         add({file = input.file, filename = input.filename})
      else
         -- Validation should ensure this never happens.
         error("input doesn't specify source to check")
      end
   end

   return res
end

local function add_new_reports(inputs, func)
   local sources = {}
   local original_indexes = {}

   for index, input in ipairs(inputs) do
      if not input.fatal and not input.cached_report then
         if input.string then
            table.insert(sources, input.string)
            table.insert(original_indexes, index)
         else
            local source, err = utils.read_file(input.path or input.file)

            if source then
               table.insert(sources, {text = source, filename = input.path or input.file})
               table.insert(original_indexes, index)
            else
               input.fatal = "I/O"
               input.msg = err
            end
         end
      end
   end

   local reports = utils.map(func, sources)

   for index, report in ipairs(reports) do
      inputs[original_indexes[index]].new_report = report
   end
end

local function add_and_merge(inputs, func)
   add_new_reports(inputs, func)
   local sources = utils.map(function(t) return t.new_report end, inputs)
   local final = utils.merge(table.unpack(sources))
   return final
end

local function build_locale_table(inputs)
   return add_and_merge(inputs, locale.make_table)
end

local function is_expanded_key(key)
   return sfind(key, "%.%d+%.") or sfind(key, "%.%d+$")
end

local function get_reports(inputs, locale_table)
   add_new_reports(inputs, checker.get_report(locale_table))

   local not_used = {}

   for _, item in pairs(locale_table) do
      if not item.used then
         if not_used[item.filename] == nil then
            not_used[item.filename] = {}
         end

         if is_expanded_key(item.key) then
            table.insert(not_used[item.filename],
                         {line = 0,
                          column = 0,
                          key = item.key,
                          kind = "error",
                          msg = "Duplicate translation key found"})
         else
            table.insert(not_used[item.filename],
                         {line = 0,
                          column = 0,
                          key = item.key,
                          kind = "error",
                          msg = "Unused translation found in store"})
         end
      end
   end

   for filename, item in pairs(not_used) do
      inputs[#inputs+1] = {abs_path = filename, path = filename, new_report = item}
   end

   return inputs
end

local function filter_warnings(reports)
   for _, report in pairs(reports) do
      report.new_report = utils.filter(report.new_report, function(i) return i.kind ~= "warning" end)
   end
end

local function tally_warnings(report)
   local warnings = 0
   local errors = 0

   for _, item in pairs(report) do
      for _, res in pairs(item.new_report) do
         if res.kind == "warning" then
            warnings = warnings + 1
         elseif res.kind == "error" then
            errors = errors + 1
         end
      end
   end

   report.warnings = warnings
   report.errors = errors
end

function runner.format(report)
   local reports = format.format(report)
   local final = utils.flatten(reports)
   return utils.join_strings(final, "\n")
end

function runner.check(inputs, opts)
   local ok, err = validate_inputs(inputs)

   if not ok then
      error(("bad argument #1 to 'check' (%s)"):format(err))
   end

   local path = fs.join(opts.root_path, "runtime", "locale", opts.source_language)
   if not fs.is_dir(path) then
      error(("no such locale path: (%s)"):format(path))
   end

   local locale_inputs = prepare_inputs({{path = path}}, "%.hcl$")
   local locale_table = build_locale_table(locale_inputs)

   local prepared_inputs = prepare_inputs(inputs, "%.[hc]pp$")
   local report = get_reports(prepared_inputs, locale_table)

   if not opts.warnings then
      filter_warnings(report)
   end

   tally_warnings(report)

   return report
end

return runner
