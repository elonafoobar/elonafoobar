local Rand = Elona.require("Rand")

local Exports = {}

Exports.dialog = {}

function Exports.dialog.redirect()
   if Rand.coinflip() then
      return "core.dialog:dialog.redirect.one"
   else
      return "core.dialog:dialog.redirect.two"
   end
end

return {
   Exports = Exports
}
