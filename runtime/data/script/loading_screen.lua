local native = _ENV.native
local Fs = native.Fs
local Graphics = native.Graphics
local Color = Graphics.Color

local BG_COLOR = Color.rgb(160, 145, 128)
local FG_COLOR = Color.rgb(71, 64, 55)
local FRAME_WIDTH = 480
local FRAME_HEIGHT = 360
local PROGRESS_BAR_WIDTH = 340
local PROGRESS_BAR_HEIGHT = 12

local function draw_wired_box(app, x, y, w, h, color)
   app:draw_line(x, y, x + w, y, color)
   app:draw_line(x + w, y, x + w, y + h, color)
   app:draw_line(x + w, y + h, x, y + h, color)
   app:draw_line(x, y + h, x, y, color)
end

return function(init_thread)
   local app = __APP

   local progress = 0
   local message = ""

   while app:update() do
      if coroutine.status(init_thread) == "dead" then
         if progress < 100 then
            progress = 100
         else
            break
         end
      else
         local ok, message = coroutine.resume(init_thread)
         if ok then
            message = message
            progress = progress + 1
         else
            print(debug.traceback())
            error(message) -- Propagate the error upward
         end
      end

      -- Fill
      app:clear(BG_COLOR)

      -- Frame (2 px)
      draw_wired_box(app,
         (app:screen_width() - FRAME_WIDTH) // 2,
         (app:screen_height() - FRAME_HEIGHT) // 2,
         FRAME_WIDTH - 1,
         FRAME_HEIGHT - 1,
         FG_COLOR)
      draw_wired_box(app,
         (app:screen_width() - FRAME_WIDTH) // 2 - 1,
         (app:screen_height() - FRAME_HEIGHT) // 2 - 1,
         FRAME_WIDTH - 1 + 2,
         FRAME_HEIGHT - 1 + 2,
         FG_COLOR)

      -- Text: Now Loading...
      app:load_font(Fs.get_bundled_font_path(), 36)
      app:set_text_alignment(Graphics.TEXT_ALIGNMENT_CENTER)
      app:draw_text(
         "Now Loading...",
         app:screen_width() // 2,
         (app:screen_height() - FRAME_HEIGHT) // 2 + 70,
         FG_COLOR)

      -- Frame
      draw_wired_box(app,
         (app:screen_width() - FRAME_WIDTH) // 2 + (FRAME_WIDTH - PROGRESS_BAR_WIDTH) // 2,
         (app:screen_height() - FRAME_HEIGHT) // 2 + 180,
         PROGRESS_BAR_WIDTH - 1,
         PROGRESS_BAR_HEIGHT - 1,
         FG_COLOR)

      -- Progress bar
      app:fill_rect(
         (app:screen_width() - FRAME_WIDTH) // 2 + (FRAME_WIDTH - PROGRESS_BAR_WIDTH) // 2 + 2,
         (app:screen_height() - FRAME_HEIGHT) // 2 + 180 + 2,
         (PROGRESS_BAR_WIDTH - 4) * progress // 100,
         PROGRESS_BAR_HEIGHT - 4,
         FG_COLOR)

      -- Message
      app:load_font(Fs.get_bundled_font_path(), 20)
      app:set_text_baseline(Graphics.TEXT_BASELINE_BOTTOM)
      app:draw_text(
         message,
         app:screen_width() // 2,
         (app:screen_height() - FRAME_HEIGHT) // 2 + 180 - 4,
         FG_COLOR)

      -- Progress
      app:load_font(Fs.get_bundled_font_path(), 16)
      app:set_text_baseline(Graphics.TEXT_BASELINE_TOP)
      app:draw_text(
         tostring(progress).."%",
         app:screen_width() // 2,
         (app:screen_height() - FRAME_HEIGHT) // 2 + 180 + PROGRESS_BAR_HEIGHT + 4,
         FG_COLOR)
   end

   app:set_text_alignment(Graphics.TEXT_ALIGNMENT_LEFT)
   app:set_text_baseline(Graphics.TEXT_BASELINE_TOP)
end
