local class = prelude.class
local string = prelude.string

local graphics = require("graphics")

local exports = {}

local STATE = {}

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
      graphics.set_alpha_mod(255)
      graphics.set_color_mod(255, 255, 255)
   end
end

local Cursor = class("core.ui.Cursor")

function Cursor:__init(page, position)
   self.page = page
   self.position = position
end

exports.Cursor = Cursor

function exports.clear()
   STATE = {}
end

function exports.render()
end

function exports.window(title, keyhint, x, y, width, height)
   draw_window(x + 4, y + 4, width, height - height % 8, true)
   draw_window(x, y, width, height - height % 8, false)

   --[[
   if not string.isempty(title) then
      draw_window2(
         x + 34,
         y - 4,
         45 * width // 100 + clamp(int(strlen_u(title) * 8 - 120), 0, 200),
         32,
         1,
         1)
   end

   graphics.draw_image("core.tip_icon", x + 30 + x_offset, y + height - 47 - height % 8)

   graphics.draw_line(
      x + 50 + x_offset,
      y + height - 48 - height % 8,
      x + width - 40,
      y + height - 48 - height % 8,
      {194, 170, 146})
   graphics.draw_line(
      x + 50 + x_offset,
      y + height - 49 - height % 8,
      x + width - 40,
      y + height - 49 - height % 8,
      {234, 220, 188})

   font(15 + en - en * 2)
   bmes(
      title,
      x + 45 * width // 200 + 34 - strlen_u(title) * 4 + clamp(int(strlen_u(title) * 8 - 120), 0, 200) // 2,
      y + 4 + vfix,
      {255, 255, 255},
      {20, 10, 0})

   font(12 + sizefix - en * 2)
   mes(key_help, x + 58 + x_offset, y + height - 43 - height % 8)

   if pagesize ~= 0 then
      local page_str = ("Page.%d/%d"):format(page + 1, pagemax + 1)
      font(12 + sizefix - en * 2, bold)
      mes(page_str,
         x + width - strlen_u(page_str) * 7 - 40 - y_offset,
         y + height - 65 - height % 8)
   end
   --]]

   STATE.wx = x
   STATE.wy = y
   STATE.ww = width
   STATE.wh = height
end

function exports.list_item(text, x, y)
   local x_offset = exports.compat.wx()
   local y_offset = exports.compat.wy()
   graphics.set_draw_color(0, 0, 0)
   graphics.draw_text(text, x + x_offset, y + y_offset)
end

exports.compat = {
   wx = function() return assert(STATE.wx) end,
   wy = function() return assert(STATE.wy) end,
   ww = function() return assert(STATE.ww) end,
   wh = function() return assert(STATE.wh) end,
}

return exports
