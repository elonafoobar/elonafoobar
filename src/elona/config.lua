local function SectionDef()
   return {
      children = children,
   }
end



local function BooleanDef()
   return {
      default_value = default_value,
   }
end



local function IntegerDef()
   return {
      default_value = default_value,
      min = min,
      max = max,
      step = step,
   }
end



local function StringDef()
   return {
      default_value = default_value,
   }
end



local function ListDef()
   return {
      default_value = default_value,
   }
end



local function EnumDef()
   return {
      default_index = default_index,
      variants = variants,
      pending = false,
   }
end



local UNKNOWN_ENUM = "__unknown__"



local function Object()
end



function load(path, mod_id)
end



local ConfigDef = {}



function ConfigDef.load(filename, mod_id)
   local ok, result = LSON.load_file(filename)
   if not ok then
      error(result)
   end
end



local Config = {}



function Config.load_def()
   def
end



function load_config_preload()
   inject_display_modes()
   inject_languages()
   inject_save_files()

   -- bind
   -- core.language.language
   -- core.screen.fullscreen
   -- core.screen.music
   -- core.screen.sound
   -- core.balance.extra_race
   -- core.balance.extra_class
   -- core.input.joypad
   -- core.input.key_wait
   -- core.game.default_save
   -- core.debug.wizard
   -- core.screen.display_mode
   -- core.android.quick_action_size
   -- core.android.quick_action_transparency

   if not exists(filepath) then
      write_empty_config()
   end

   load(filepath)

   -- core.android.hide_navigation
end



function load_config()
end



function config_get_fullscreen_mode()
end
