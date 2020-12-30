local Graphics = require("graphics")
local UI = require("ui")

local function main_loop(initial_state)
   local app = __APP

   local ui_layers = {}

   local update_thread = coroutine.create(function()
      while true do
         for _, layer in ipairs(ui_layers) do
            Graphics.reset_context()
            UI.clear()
            layer:update()
            UI.render()
         end
         coroutine.yield()
      end
   end)

   ui_layers[#ui_layers + 1] = initial_state
   while app:update() do
      local ok, result = coroutine.resume(update_thread)
      if not ok then
         error(result)
      end
   end
end

return main_loop
