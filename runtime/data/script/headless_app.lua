local HeadlessApp = prelude.class("__native.app.HeadlessApp")

local GuiApp = native.app.App
for fn_name in pairs(GuiApp) do
   HeadlessApp[fn_name] = function()
      log_trace("core.HeadlessApp:"..fn_name.."()")
   end
end

function HeadlessApp:is_headless()
   return true
end

function HeadlessApp:update()
   return true
end

function HeadlessApp:screen_width()
   return 800
end

function HeadlessApp:screen_height()
   return 600
end

function HeadlessApp:load_image()
   return {
      set_alpha_mod = function() end,
      set_color_mod = function() end,
   }
end

function HeadlessApp:calculate_text_size(s)
   return 8 * #s, 14
end

function HeadlessApp:get_music_volume()
   return 0
end

return HeadlessApp
