local argparse = require "elocheck.argparse"
local fs = require "elocheck.fs"
local runner = require "elocheck.runner"

local exit_codes = {
   ok = 0,
   warnings = 1,
   errors = 2,
   critical = 3
}

local elocheck = {
   _VERSION = "0.1.0"
}

local function critical(msg)
   io.stderr:write("Critical error: "..msg.."\n")
   os.exit(exit_codes.critical)
end

local function get_parser()
   local parser = argparse(
      "elocheck", "elocheck " .. elocheck._VERSION, "")
      :help_max_width(120)

   parser:argument "root_path"
      :description("Root directory of ElonaFoobar repo")
      :args(1)
      :argname "<root_path>"

   parser:argument "source_language"
      :description("Language identifier to check. (en/jp)")
      :args(1)
      :argname "<source_language>"

   parser:flag("--no-warnings", "Disable warnings."):target("warnings"):action("store_false")

   parser:flag("-v --version", "Show version info and exit.")
      :action(function() print(elocheck._VERSION) os.exit(exit_codes.ok) end)

   return parser
end

local function main()
   local parser = get_parser()
   local ok, args = parser:pparse()
   if not ok then
      io.stderr:write(("%s\n\nError: %s\n"):format(parser:get_usage(), args))
      os.exit(exit_codes.critical)
   end

   local inputs = {}

   local files = {fs.join(args.root_path, "src")}

   for _, file in ipairs(files) do
      local input = {path = file}
      table.insert(inputs, input)
   end

   local report, check_err = runner.check(inputs, args)

   if not report then
      critical(check_err)
   end

   local output, format_err = runner.format(report)

   if not output then
      critical(format_err)
   end

   io.stdout:write(output)

   if report.errors > 0 then
      os.exit(exit_codes.errors)
   elseif report.warnings > 0 then
      os.exit(exit_codes.warnings)
   else
      os.exit(exit_codes.ok)
   end
end

main()
