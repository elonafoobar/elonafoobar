local native = _ENV.native
local Fs = native.Fs

local Config = require("config")
local data = require("data")
local enums = require("enums")

local Audio = {}

local PLAYING_MUSIC = nil

--- @tfield integer
--- Special value for infinite loop
Audio.LOOP_FOREVER = -1

--- Plays music.
--- @tparam string music_id The music ID
--- @tparam[opt] integer loop_times The loop times. If not given, the music will be played once.
function Audio.play_music(music_id, loop_times)
   if not Config.get("core.screen.music") then
      return
   end
   if PLAYING_MUSIC == music_id then
      return
   end

   local music_data = data.get("core.music", music_id)
   if not music_data then
      log_error("Audio: cannot find music data of '{$1}'", music_id)
      return
   end

   local path = Fs.resolve_path_for_mod(music_data.file)
   local volume = music_data.volume or 128

   __APP:stop_music()
   __APP:load_music(path)
   __APP:set_music_volume(volume * Config.get("core.screen.music_volume") // 8)
   __APP:play_music(loop_times or 1)

   PLAYING_MUSIC = id
end

return Audio
