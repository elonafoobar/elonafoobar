local Parser = require 'hclua.parser'
local Decoder = require 'hclua.decoder'
local open = io.open

local function parse(source)
   local ok, result = pcall(Parser.parse, source)
   if not ok then
      return result
   end
   return Decoder.decode(result)
end

local function parse_file(filepath)
   local function read_file(path)
      local file = open(path, "rb")
      if not file then return nil end

      local content = file:read "*a"
      file:close()
      return content
   end

   local content = read_file(filepath)

   return parse(content)
end

return {
   parse = parse,
   parse_file = parse_file,
}
