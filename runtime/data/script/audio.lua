local Fs = native.Fs

local config = require("config")
local data = require("data")

local exports = {}

local PLAYING_MUSIC = nil

--- @tfield integer
--- Special value for infinite loop
exports.LOOP_FOREVER = -1

--- Plays music.
--- @tparam string music_id The music ID
--- @tparam[opt] integer loop_times The loop times. If not given, the music will be played once.
function exports.play_music(music_id, loop_times)
   if not config.get("core.screen.music") then
      return
   end
   if PLAYING_MUSIC == music_id then
      return
   end

   local music_data = data.get("core.music", music_id)
   if not music_data then
      log_error(("audio: cannot find music data of '%s'"):format(music_id))
      return
   end

   local path = music_data["$file__resolved"]
   if not path then
      path = Fs.resolve_path_for_mod(music_data.file)
   end
   local volume = music_data.volume or 128

   __APP:stop_music()
   __APP:load_music(path)
   __APP:set_music_volume(volume * config.get("core.screen.music_volume") // 8)
   __APP:play_music(loop_times or 1)

   PLAYING_MUSIC = music_id
end

return exports
