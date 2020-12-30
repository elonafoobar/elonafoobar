local native = _ENV.native
local Fs = native.Fs
local Color = native.Graphics.Color

local prelude = _ENV.prelude
local p = prelude.p

local Data = require("data")

local Graphics = {}

local CONTEXT = {}

function Graphics.reset_context()
   CONTEXT.color = Color.rgb(255, 255, 255)
end

function Graphics.draw_image(id, x, y, width, height)
   local asset_data = Data.get("core.asset", id)
   if not asset_data then
      log_error(("Asset data 'core.asset#%s' not found"):format(id))
      return
   end

   -- TODO
   Graphics.set_draw_color(0, 0, 0)
   Graphics.fill_rect(x, y, width, height)
end

function Graphics.set_draw_color(arg1, arg2, arg3)
   if arg1 and arg2 and arg3 then
      CONTEXT.color = Color.rgb(arg1, arg2, arg3)
   else
      CONTEXT.color = arg1
   end
end

function Graphics.clear()
   __APP:clear(CONTEXT.color)
end

function Graphics.draw_line(x1, y1, x2, y2)
   __APP:draw_line(x1, y1, x2, y2, CONTEXT.color)
end

function Graphics.fill_rect(x, y, w, h)
   __APP:fill_rect(x, y, w, h, CONTEXT.color)
end

function Graphics.draw_text(text, x, y)
   __APP:draw_text(text, x, y, CONTEXT.color)
end

function Graphics.draw_text_with_shadow(text, x, y, shadow_color)
   __APP:draw_text_with_shadow(text, x, y, CONTEXT.color, shadow_color)
end

function Graphics.screen_width()
   return __APP:screen_width()
end

function Graphics.screen_height()
   return __APP:screen_height()
end

function Graphics.set_font_size(point_size)
   __APP:load_font(Fs.get_bundled_font_path(), point_size)
end

return Graphics
