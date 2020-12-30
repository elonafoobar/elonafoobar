local native = _ENV.native

local prelude = _ENV.prelude
local class = prelude.class

local Audio = require("audio")
local Env = require("env")
local Graphics = require("graphics")
local I18n = require("i18n")
local UI = require("ui")

local MainTitleMenu = class("core.UI.MainTitleMenu")

function MainTitleMenu:on_shown()
   Audio.play_music("core.main_title_menu")
end

function MainTitleMenu:update()
   Graphics.draw_image("core.title", 0, 0, Graphics.screen_width(), Graphics.screen_height())

   Graphics.set_draw_color(255, 255, 255)
   Graphics.draw_text("Elona version 1.22  Developed by Noa", 20, 20)
   Graphics.draw_text("  Variant foobar version"..Env.VARIANT_VERSION, 20, 38)
   if I18n.language() == "ja" then
      Graphics.draw_text("Contributor MSL / View the credits for more", 20, 56)
   elseif I18n.language() == "en" then
      Graphics.draw_text("Contributor f1r3fly, Sunstrike, Schmidt, Elvenspirit / View the credits for more", 20, 56)
      Graphics.draw_text("Omake/OO translator: Doorknob", 20, 76)
      Graphics.draw_text("Cutscenes translator: AnnaBannana", 20, 96)
   end

   UI.window_begin(I18n.get("core.main_menu.title_menu.title"), "TODO:strhint1", 80, (Graphics.screen_height() - 308) // 2, 320, 355)
   -- TODO cmbg

   -- TODO deco_blend
   -- TODO water ripple

   UI.list_begin(80, 50)

   local function list_item(main, sub, x, y)
      if I18n.language() == "en" then
         Graphics.set_font_size(14)
         return UI.list_item(main, x, y + 1)
      else
         local x_offset = UI.get_current_list().absolute_x
         local y_offset = UI.get_current_list().absolute_y
         Graphics.set_font_size(11)
         Graphics.draw_text(sub, x + x_offset, y - 4 + y_offset)
         Graphics.set_font_size(13)
         return UI.list_item(main, x, y + 8)
      end
   end

   local result
   if list_item(I18n.get("core.main_menu.title_menu.continue"), "Restore an Adventurer", 0, 0 * 35) then
      Audio.play_sound("core.ok1")
      result = "continue"
   end
   if list_item(I18n.get("core.main_menu.title_menu.new"), "Generate an Adventurer", 0, 1 * 35) then
      Audio.play_sound("core.ok1")
      result = "new"
   end
   if list_item(I18n.get("core.main_menu.title_menu.incarnate"), "Incarnate an Adventurer", 0, 2 * 35) then
      Audio.play_sound("core.ok1")
      result = "incarnate"
   end
   if list_item(I18n.get("core.main_menu.title_menu.about"), "About", 0, 3 * 35) then
      Audio.play_sound("core.ok1")
      result = "about"
   end
   if list_item(I18n.get("core.main_menu.title_menu.options"), "Options", 0, 4 * 35) then
      Audio.play_sound("core.ok1")
      result = "options"
   end
   if list_item(I18n.get("core.main_menu.title_menu.mods"), "Mods", 0, 5 * 35) then
      Audio.play_sound("core.ok1")
      result = "mods"
   end
   if list_item(I18n.get("core.main_menu.title_menu.exit"), "Exit", 0, 6 * 35) then
      Audio.play_sound("core.ok1")
      result = "exit"
   end

   UI.list_end()

   UI.window_end()

   return result
end

return MainTitleMenu
