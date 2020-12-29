local Chara = require("core.Chara")
local Map = require("core.Map")
local GUI = require("core.GUI")
local I18N = require("core.I18N")

local function create_downstairs(x, y, dungeon_level)
   Map.set_feat(x, y, 231, 11, dungeon_level)
end

local function quest_completed()
   GUI.txt(I18N.get("core.quest.completed"))
   GUI.play_sound("core.complete1")
   GUI.txt(I18N.get("core.common.something_is_put_on_the_ground"))
   GUI.show_journal_update_message()
end

local function journal_updated()
   GUI.show_journal_update_message()
end

local function args_name()
   return {Chara.player().basename}
end

local function args_alias()
   return {Chara.player().alias}
end

local function args_speaker(t)
   return {t.speaker}
end

return {
   create_downstairs = create_downstairs,
   quest_completed = quest_completed,
   journal_updated = journal_updated,

   args_name = args_name,
   args_alias = args_alias,
   args_speaker = args_speaker,
}
