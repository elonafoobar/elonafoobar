local Graphics = require("graphics")

local UI = {}

local STATE = {}

function UI.clear()
   STATE = {}
end

function UI.render()
   -- TODO
end

function UI.window_begin(title, keyhint, x, y, width, height)
   -- TODO
   STATE[#STATE + 1] = {
      title = title,
      keyhint = keyhint,
      x = x,
      y = y,
      absolute_x = x,
      absolute_y = y,
      width = width,
      height = height,
      children = {},
   }
   -- TODO
   Graphics.fill_rect(x, y, width, height)
end

function UI.window_end()
   -- TODO
end

function UI.list_begin(x, y)
   -- TODO
   local window = UI.get_current_window()
   local children = window.children
   children[#children + 1] = {
      x = x,
      y = y,
      absolute_x = window.absolute_x + x,
      absolute_y = window.absolute_y + y,
   }
end

function UI.list_end()
   -- TODO
end

function UI.list_item(text, x, y)
   -- TODO
   local x_offset = UI.get_current_list().absolute_x
   local y_offset = UI.get_current_list().absolute_y
   Graphics.set_draw_color(0, 0, 0)
   Graphics.draw_text(text, x + x_offset, y + y_offset)
end

function UI.get_current_window()
   return STATE[#STATE]
end

function UI.get_current_list()
   local children = UI.get_current_window().children
   return children[#children]
end

return UI
