local native = _ENV.native
local Fs = native.Fs
local Color = native.Graphics.Color

local prelude = _ENV.prelude
local p = prelude.p

local data = require("data")
local enums = require("enums")

local exports = {}

local CONTEXT = {}
local ASSET_CACHES = {}

exports.Color = Color

exports.AnchorX = enums.new_enum {
   LEFT = 1,
   CENTER = 2,
   RIGHT = 3,
}

exports.AnchorY = enums.new_enum {
   TOP = 1,
   CENTER = 2,
   BOTTOM = 3,
}

function exports.reset_context()
   CONTEXT.color = Color.rgb(255, 255, 255)
   CONTEXT.alpha_mod = 255
   CONTEXT.color_mod = Color.rgb(255, 255, 255)
end

function exports.load_image(id)
   local asset_data = data.get("core.asset", id)

   local cache = ASSET_CACHES[id]
   if cache then
      return cache, asset_data -- cache hit
   end

   if not asset_data then
      log_error(("graphics: asset data 'core.asset#%s' not found"):format(id))
      return nil
   end

   if asset_data.file then
      local path = asset_data["$file__resolved"]
      if not path then
         path = Fs.resolve_path_for_mod(asset_data.file)
         asset_data["$file__resolved"] = path
      end
      local image = __APP:load_image(path, asset_data.key_color)
      log_info(("graphics: load image file '%s'"):format(path))
      ASSET_CACHES[id] = image
      return image, asset_data
   else
      assert(asset_data.source)
      -- TODO support non-core assets
      return exports.load_image("core."..asset_data.source), asset_data
   end
end

function exports.draw_image(id, dst_x, dst_y, dst_width, dst_height, opts)
   local image, asset_data = exports.load_image(id)
   if not image then
      return
   end

   dst_width = dst_width or asset_data.width
   dst_height = dst_height or asset_data.height

   if opts then
      local anchor_x, anchor_y = opts.anchor_x, opts.anchor_y
      if anchor_x then
         if anchor_x == exports.AnchorX.CENTER then
            dst_x = dst_x - dst_width // 2
         elseif anchor_x == exports.AnchorX.RIGHT then
            dst_x = dst_x - dst_width
         end
      end
      if anchor_y then
         if anchor_y == exports.AnchorY.CENTER then
            dst_y = dst_y - dst_height // 2
         elseif anchor_y == exports.AnchorY.BOTTOM then
            dst_y = dst_y - dst_height
         end
      end
   end

   image:set_alpha_mod(CONTEXT.alpha_mod)
   image:set_color_mod(CONTEXT.color_mod)
   __APP:draw_image(
      image,
      asset_data.x,
      asset_data.y,
      asset_data.width,
      asset_data.height,
      dst_x,
      dst_y,
      dst_width,
      dst_height)
end

function exports.draw_image_clipped(id, src_x, src_y, src_width, src_height, dst_x, dst_y, dst_width, dst_height, opts)
   local image, asset_data = exports.load_image(id)
   if not image then
      return
   end

   dst_width = dst_width or src_width
   dst_height = dst_height or src_height

   if opts then
      local anchor_x, anchor_y = opts.anchor_x, opts.anchor_y
      if anchor_x then
         if anchor_x == exports.AnchorX.CENTER then
            dst_x = dst_x - dst_width // 2
         elseif anchor_x == exports.AnchorX.RIGHT then
            dst_x = dst_x - dst_width
         end
      end
      if anchor_y then
         if anchor_y == exports.AnchorY.CENTER then
            dst_y = dst_y - dst_height // 2
         elseif anchor_y == exports.AnchorY.BOTTOM then
            dst_y = dst_y - dst_height
         end
      end
   end

   image:set_alpha_mod(CONTEXT.alpha_mod)
   image:set_color_mod(CONTEXT.color_mod)
   __APP:draw_image(
      image,
      asset_data.x + src_x,
      asset_data.y + src_y,
      src_width,
      src_height,
      dst_x,
      dst_y,
      dst_width,
      dst_height)
end

function exports.set_draw_color(arg1, arg2, arg3)
   if arg1 and arg2 and arg3 then
      CONTEXT.color = Color.rgb(arg1, arg2, arg3)
   else
      CONTEXT.color = arg1
   end
end

function exports.set_alpha_mod(a)
   CONTEXT.alpha_mod = a
end

function exports.set_color_mod(arg1, arg2, arg3)
   if arg1 and arg2 and arg3 then
      CONTEXT.color_mod = Color.rgb(arg1, arg2, arg3)
   else
      CONTEXT.color_mod = arg1
   end
end

function exports.clear()
   __APP:clear(CONTEXT.color)
end

function exports.draw_line(x1, y1, x2, y2)
   __APP:draw_line(x1, y1, x2, y2, CONTEXT.color)
end

function exports.fill_rect(x, y, w, h)
   __APP:fill_rect(x, y, w, h, CONTEXT.color)
end

function exports.draw_text(text, x, y)
   __APP:draw_text(text, x, y, CONTEXT.color)
end

function exports.draw_text_with_shadow(text, x, y, shadow_color)
   __APP:draw_text_with_shadow(text, x, y, CONTEXT.color, shadow_color)
end

function exports.screen_width()
   return __APP:screen_width()
end

function exports.screen_height()
   return __APP:screen_height()
end

function exports.set_font_size(point_size)
   __APP:load_font(Fs.get_bundled_font_path(), point_size)
end

return exports
