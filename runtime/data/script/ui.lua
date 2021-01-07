local class = prelude.class
local math = prelude.math
local string = prelude.string
local utf8 = prelude.utf8

local data = require("data")
local graphics = require("graphics")
local Color = graphics.Color

local exports = {}

local STATE = {
   wx = 0,
   wy = 0,
   ww = 1,
   wh = 1,
   pagesize = 0,
   page = 0,
   pagemax = 0,
}

-- TODO
local function calc_text_width(s)
   local width = 0
   for _, c in utf8.codes(s) do
      if c < 127 then
         width = width + 1
      else
         width = width + 2
      end
   end
   return width
end

local function draw_window(x, y, width, height, shadow)
   if shadow then
      graphics.set_alpha_mod(127)
      graphics.set_color_mod(31, 31, 31)
   end

   local x3 = width + x - width % 8 - 64
   local y3 = height + y - height % 8 - 64
   if y3 < y + 14 then
      y3 = y + 14
   end

   if not shadow then
      -- Top left
      graphics.draw_image_clipped("core.window", 0, 0, 64, 48, x, y)
   end
   -- Top right
   graphics.draw_image_clipped("core.window", 208, 0, 56, 48, x3, y)
   -- Bottom left
   graphics.draw_image_clipped("core.window", 0, 144, 64, 48, x, y3)
   -- Bottom right
   graphics.draw_image_clipped("core.window", 208, 144, 56, 48, x3, y3)

   for dx = 8, (width // 8 - 8) - 1 do
      if not shadow then
         -- Top middle
         graphics.draw_image_clipped("core.window", (dx - 8) % 18 * 8 + 36, 0, 8, 48, dx * 8 + x, y)
      end
      -- Bottom middle
      graphics.draw_image_clipped("core.window", (dx - 8) % 18 * 8 + 54, 144, 8, 48, dx * 8 + x, y3)
   end

   for dy = 0, (height // 8 - 14) - 1 do
      if not shadow then
         -- Middle left
         graphics.draw_image_clipped("core.window", 0, dy % 12 * 8 + 48, 64, 8, x, dy * 8 + y + 48)
         -- Middle middle
         for dx = 1, (width // 8 - 15) - 1 do
            graphics.draw_image_clipped(
               "core.window",
               dx % 18 * 8 + 64,
               dy % 12 * 8 + 48,
               8,
               8,
               dx * 8 + x + 56,
               dy * 8 + y + 48)
         end
      end
      -- Middle right
      graphics.draw_image_clipped("core.window", 208, dy % 12 * 8 + 48, 56, 8, x3, dy * 8 + y + 48)
   end

   if shadow then
      graphics.clear_alpha_mod()
      graphics.clear_color_mod()
   end
end

local function draw_window2(x, y, width, height, frame_style, fill_style)
   if width < 32 then
      width = 32
   end
   if height < 24 then
      height = 24
   end

   if fill_style == 0 then
      graphics.draw_image_clipped(
         "core.window",
         24,
         24,
         228,
         144,
         x + 4,
         y + 4,
         width - 6,
         height - 8)
   elseif fill_style == 1 then
      graphics.draw_image_clipped(
         "core.window",
         24,
         24,
         228,
         144,
         x + 4,
         y + 4,
         width - 6,
         height - 8)
      graphics.set_draw_color(0, 0, 0, 195)
      graphics.fill_rect(x + 4, y + 4, width - 4, height - 4)
   elseif fill_style == 2 then
      graphics.draw_image_clipped(
         "core.window",
         24,
         24,
         228,
         144,
         x + 4,
         y + 4,
         width - 6,
         height - 8)
      graphics.set_draw_color(0, 0, 0, 210)
      graphics.fill_rect(x + 4, y + 4, width - 4, height - 4)
   elseif fill_style == 3 then
      graphics.draw_image_clipped(
         "core.window",
         24,
         24,
         228,
         144,
         x + 4,
         y + 4,
         width - 6,
         height - 8)
      graphics.set_draw_color(0, 0, 0, 10)
      graphics.fill_rect(x + 4, y + 4, width - 4, height - 4)
   elseif fill_style == 4 then
      graphics.draw_image_clipped(
         "core.window",
         24,
         24,
         228,
         144,
         x + 4,
         y + 4,
         width - 6,
         height - 8)
      graphics.set_draw_color(0, 0, 0, 195)
      graphics.fill_rect(x + 4, y + 4, width - 4, height - 4)
   elseif fill_style == 5 then
      -- do nothing here
   elseif fill_style == 6 then
      gmode(2, 180)
      graphics.draw_image_clipped(
         "core.window",
         24,
         24,
         228,
         144,
         x + width // 2,
         y + height // 2,
         width - 4,
         height - 4,
         {
            anchor_x = graphics.AnchorX.RIGHT,
            anchor_y = graphics.AnchorY.BOTTOM,
         })
   end

   for dx = 0, (width // 16 - 2) - 1 do
      graphics.draw_image_clipped(
         "core.window_frame",
         frame_style * 48 + 16,
         0,
         16,
         16,
         dx * 16 + x + 16,
         y)
      graphics.draw_image_clipped(
         "core.window_frame",
         frame_style * 48 + 16,
         32,
         16,
         16,
         dx * 16 + x + 16,
         y + height - 16)
   end

   local x2 = x + width // 16 * 16 - 16
   local y2 = y + height // 16 * 16 - 16

   graphics.draw_image_clipped(
      "core.window_frame", frame_style * 48 + 16, 0, width % 16, 16, x2, y)
   graphics.draw_image_clipped(
      "core.window_frame",
      frame_style * 48 + 16,
      32,
      width % 16,
      16,
      x2,
      y + height - 16)

   for dy = 0, (height // 16 - 2) - 1 do
      graphics.draw_image_clipped(
         "core.window_frame",
         frame_style * 48,
         16,
         16,
         16,
         x,
         dy * 16 + y + 16)
      graphics.draw_image_clipped(
         "core.window_frame",
         frame_style * 48 + 32,
         16,
         16,
         16,
         x + width - 16,
         dy * 16 + y + 16)
   end

   graphics.draw_image_clipped(
      "core.window_frame", frame_style * 48, 16, 16, height % 16, x, y2)
   graphics.draw_image_clipped(
      "core.window_frame",
      frame_style * 48 + 32,
      16,
      16,
      height % 16,
      x + width - 16,
      y2)
   graphics.draw_image_clipped(
      "core.window_frame", frame_style * 48, 0, 16, 16, x, y)
   graphics.draw_image_clipped(
      "core.window_frame", frame_style * 48, 32, 16, 16, x, y + height - 16)
   graphics.draw_image_clipped(
      "core.window_frame",
      frame_style * 48 + 32,
      0,
      16,
      16,
      x + width - 16,
      y)
   graphics.draw_image_clipped(
      "core.window_frame",
      frame_style * 48 + 32,
      32,
      16,
      16,
      x + width - 16,
      y + height - 16)

   if fill_style == 5 then
      graphics.draw_image_clipped(
         "core.window",
         24,
         24,
         228,
         144,
         x + 2,
         y + 2,
         width - 4,
         height - 5)
      graphics.set_draw_color(0, 0, 0, 195)
      graphics.fill_rect(x + 2, y + 2, width - 4, height - 4)
   end
end

local Cursor = class("core.ui.Cursor")

function Cursor:__init(page, position)
   self.page = page
   self.position = position
end

exports.Cursor = Cursor

function exports.clear()
   STATE = {
      wx = 0,
      wy = 0,
      ww = 1,
      wh = 1,
      pagesize = 0,
      page = 0,
      pagemax = 0,
   }
end

function exports.render()
end

function exports.window(title, key_hint, x, y, width, height, x_offset, y_offset)
   x_offset = x_offset or 0
   y_offset = y_offset or 0

   draw_window(x + 4, y + 4, width, height - height % 8, true)
   draw_window(x, y, width, height - height % 8, false)

   if not string.isempty(title) then
      local text_width = calc_text_width(title) * 8
      local title_frame_x = x + 34
      local title_frame_width = 45 * width // 100 + math.clamp(text_width - 120, 0, 200)

      draw_window2(
         title_frame_x,
         y - 4,
         title_frame_width,
         32,
         1,
         1)

      graphics.set_font(15)
      graphics.set_draw_color(255, 255, 255)
      graphics.draw_text_with_shadow(
         title,
         title_frame_x + (title_frame_width - text_width) // 2,
         y + 4,
         Color.rgb(20, 10, 0))
   end

   graphics.draw_image("core.tip_icon", x + 30 + x_offset, y + height - 47 - height % 8)

   graphics.set_draw_color(194, 170, 146)
   graphics.draw_line(
      x + 50 + x_offset,
      y + height - 48 - height % 8,
      x + width - 40,
      y + height - 48 - height % 8)
   graphics.set_draw_color(234, 220, 188)
   graphics.draw_line(
      x + 50 + x_offset,
      y + height - 49 - height % 8,
      x + width - 40,
      y + height - 49 - height % 8)

   graphics.set_font(12)
   graphics.set_draw_color(0, 0, 0)
   graphics.draw_text(key_hint, x + 58 + x_offset, y + height - 43 - height % 8)

   if STATE.pagesize ~= 0 then
      local page_str = ("Page.%d/%d"):format(STATE.page + 1, STATE.pagemax + 1)
      graphics.set_font(12, graphics.FontStyle.BOLD)
      graphics.draw_text(
         page_str,
         x + width - calc_text_width(page_str) * 7 - 40 - y_offset,
         y + height - 65 - height % 8)
   end

   STATE.wx = x
   STATE.wy = y
   STATE.ww = width
   STATE.wh = height
end

function exports.list_item(is_selected, text, x, y, x_offset, text_color)
   x = x + exports.compat.wx()
   y = y + exports.compat.wy()
   x_offset = x_offset or 0
   text_color = text_color or Color.rgb(10, 10, 10)

   if is_selected then
      local width = math.clamp(calc_text_width(text) * 7 + 32 + x_offset, 10, 480)
      graphics.set_draw_color(127, 191, 255, 95)
      graphics.fill_rect(x, y, width, 19)
      graphics.draw_image("core.list_bullet", x + width - 20, y + 4)
   end

   graphics.set_draw_color(text_color)
   graphics.draw_text(text, x + 4 + x_offset, y + 3)
end

function exports.selection_key(key, x, y)
   x = x + exports.compat.wx()
   y = y + exports.compat.wy()

   graphics.draw_image("core.select_key", x, y)
   local asset_data = assert(data.get("core.asset", "core.select_key"))
   local glyph_size = graphics.calculate_text_size(key)
   graphics.set_font(13)
   graphics.set_draw_color(250, 240, 230)
   graphics.draw_text_with_shadow(
      key,
      x + (asset_data.width - glyph_size.width) // 2 - 2,
      y + (asset_data.height - glyph_size.height) // 2,
      Color.rgb(50, 60, 80))
end

local compat = {}
for k in pairs(STATE) do
   compat[k] = function() return assert(STATE[k]) end
end
exports.compat = compat

return exports
