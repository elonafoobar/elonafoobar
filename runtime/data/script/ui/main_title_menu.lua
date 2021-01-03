local native = _ENV.native
-- TODO
-- local rnd = native.Random.rnd
local S = 42
local function rnd(n)
   S = S * 214013 + 2531011
   return ((S >> 16) & 32767) % n
end

local prelude = _ENV.prelude
local class = prelude.class

local audio = require("audio")
local config = require("config")
local env = require("env")
local graphics = require("graphics")
local i18n = require("i18n")
local ui = require("ui")
local Cursor = ui.Cursor

local MainTitleMenu = class("core.ui.MainTitleMenu")

local PREV_CURSOR = nil

function MainTitleMenu:__init()
   self._background_image_index = 4
   self._ripple_sources = {}
   self._ripples = {}
   self._frame = 0
   self._RIPPLE_IMAGE_SIZE = HOGE
end

function MainTitleMenu:on_shown()
   audio.play_music("core.opening")
   self._cursor = PREV_CURSOR or Cursor.new(1, 1)
end

function MainTitleMenu:on_closed()
   PREV_CURSOR = self._cursor
end

function MainTitleMenu:update()
   self._frame = self._frame + 1

   graphics.draw_image("core.title", 0, 0, graphics.screen_width(), graphics.screen_height())

   graphics.set_draw_color(255, 255, 255)
   graphics.set_font_size(13)
   graphics.draw_text("Elona version 1.22  Developed by Noa", 20, 20)
   graphics.draw_text("  Variant foobar version "..env.VARIANT_VERSION, 20, 38)
   if i18n.language() == "ja" then
      graphics.draw_text("Contributor MSL / View the credits for more", 20, 56)
   elseif i18n.language() == "en" then
      graphics.draw_text("Contributor f1r3fly, Sunstrike, Schmidt, Elvenspirit / View the credits for more", 20, 56)
      graphics.draw_text("Omake/OO translator: Doorknob", 20, 76)
      graphics.draw_text("Cutscenes translator: AnnaBannana", 20, 96)
   end

   ui.window(i18n.get("core.main_menu.title_menu.title"), "TODO:strhint1", 80, (graphics.screen_height() - 308) // 2, 320, 355)

   graphics.set_alpha_mod(191)
   graphics.draw_image(
      "core.deco_title",
      ui.compat.wx() + ui.compat.ww() - 30,
      ui.compat.wy() + ui.compat.wh() - 40,
      nil,
      nil,
      {
         anchor_x = graphics.AnchorX.RIGHT,
         anchor_y = graphics.AnchorY.BOTTOM,
      })

   graphics.set_alpha_mod(50)
   graphics.draw_image(
      "core.g"..tostring(self._background_image_index),
      ui.compat.wx() + 160,
      ui.compat.wy() + ui.compat.wh() // 2,
      ui.compat.ww() // 5 * 4,
      ui.compat.wh() - 80,
      {
         anchor_x = graphics.AnchorX.CENTER,
         anchor_y = graphics.AnchorY.CENTER,
      }
   )
   graphics.set_alpha_mod(255)

   if config.get("core.anime.title_effect") then
      self:_draw_title_effect()
   end

   graphics.set_draw_color(0, 0, 0)

   local function list_item(main, sub, x, y)
      x = x + 80
      y = y + 50
      if i18n.language() == "en" then
         graphics.set_font_size(14)
         return ui.list_item(main, x, y + 1)
      else
         local x_offset = ui.compat.wx()
         local y_offset = ui.compat.wy()
         graphics.set_font_size(11)
         graphics.draw_text(sub, x + x_offset, y - 4 + y_offset)
         graphics.set_font_size(13)
         return ui.list_item(main, x, y + 8)
      end
   end

   local result
   if list_item(i18n.get("core.main_menu.title_menu.continue"), "Restore an Adventurer", 0, 0 * 35) then
      audio.play_sound("core.ok1")
      result = "continue"
   end
   if list_item(i18n.get("core.main_menu.title_menu.new"), "Generate an Adventurer", 0, 1 * 35) then
      audio.play_sound("core.ok1")
      result = "new"
   end
   if list_item(i18n.get("core.main_menu.title_menu.incarnate"), "Incarnate an Adventurer", 0, 2 * 35) then
      audio.play_sound("core.ok1")
      result = "incarnate"
   end
   if list_item(i18n.get("core.main_menu.title_menu.about"), "About", 0, 3 * 35) then
      audio.play_sound("core.ok1")
      result = "about"
   end
   if list_item(i18n.get("core.main_menu.title_menu.options"), "Options", 0, 4 * 35) then
      audio.play_sound("core.ok1")
      result = "options"
   end
   if list_item(i18n.get("core.main_menu.title_menu.mods"), "Mods", 0, 5 * 35) then
      audio.play_sound("core.ok1")
      result = "mods"
   end
   if list_item(i18n.get("core.main_menu.title_menu.exit"), "Exit", 0, 6 * 35) then
      audio.play_sound("core.ok1")
      result = "exit"
   end

   return result
end

function MainTitleMenu:_draw_title_effect()
   if self._frame % 20 == 0 then
      self._ripple_sources[#self._ripple_sources + 1] = {
         0,
         rnd(graphics.screen_width() - 20) + 10,
         rnd(graphics.screen_height() - 20) + 10,
      }
   end

   for _, source in ipairs(self._ripple_sources) do
      if source[1] % 5 == 0 then
         local x, y = source[2], source[3]
         self._ripples[#self._ripples + 1] = {
            0,
            rnd(rnd(3) + 1),
            x - rnd(256) + rnd(256),
            y - rnd(256) + rnd(256),
         }
      end
      source[1] = source[1] + 1
   end

   for _, ripple in ipairs(self._ripples) do
      local t, kind, x, y = table.unpack(ripple)
      local size = t * 3 // 2
      graphics.set_alpha_mod(100 + rnd(6) * 20)
      graphics.draw_image_clipped(
         "core.water_ripple",
         256 * kind,
         0,
         256,
         256,
         x,
         y,
         size,
         size,
         {
            anchor_x = graphics.AnchorX.CENTER,
            anchor_y = graphics.AnchorY.CENTER,
         })
      ripple[1] = t + 1
   end

   do
      local new_ripple_sources = {}
      for _, source in ipairs(self._ripple_sources) do
         if source[1] <= 15 + 5 * rnd(3) then
            new_ripple_sources[#new_ripple_sources + 1] = source
         end
      end
      self._ripple_sources = new_ripple_sources
   end

   do
      local new_ripples = {}
      for _, ripple in ipairs(self._ripples) do
         if ripple[1] <= rnd(rnd(256) + 1) + rnd(256) + 64 then
            new_ripples[#new_ripples + 1] = ripple
         end
      end
      self._ripples = new_ripples
   end
end

return MainTitleMenu
