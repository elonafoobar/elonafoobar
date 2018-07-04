local Parser = require 'hclua.parser'
local Decoder = require 'hclua.decoder'

local function parse(source)
   local ok, result = pcall(Parser.parse, source)
   if not ok then
      return result
   end
   return Decoder.decode(result)
end

return {
   parse = parse
}
