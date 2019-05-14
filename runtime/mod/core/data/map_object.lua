local GUI = Elona.require("GUI")

data:define_type("map_object")
data:add_multi(
   "core.map_object",
   {
      {
         id = "voting_box",
         legacy_id = 31,
         tiles = {"core.1_729"},
         on_activate = function() GUI.snd("core.chat") end
      },
      {
         id = "small_medal",
         legacy_id = 32,
         tiles = {"core.1_0"},
      },
      {
         id = "door_closed",
         legacy_id = 21,
         tiles = {"core.1_726", "core.1_728", "core.1_730", "core.1_733"},
      },
      {
         id = "door_opened",
         legacy_id = 20,
         tiles = {"core.1_236", "core.1_241", "core.1_264", "core.1_265"}
      },
      {
         id = "world_map_location",
         legacy_id = 15,
         tiles = {"core.1_0"},
      },
      {
         id = "hidden_path",
         legacy_id = 22,
         tiles = {"core.1_0"},
      },
      {
         id = "spot0",
         legacy_id = 28,
         tiles = {"core.1_246"},
      },
      {
         id = "spot1",
         legacy_id = 27,
         tiles = {"core.1_243"},
      },
      {
         id = "spot2",
         legacy_id = 26,
         tiles = {"core.1_245"},
      },
      {
         id = "spot3",
         legacy_id = 25,
         tiles = {"core.1_234"},
      },
      {
         id = "plant",
         legacy_id = 29,
         tiles = {"core.1_247", "core.1_248", "core.1_249", "core.1_250"},
      },
      {
         id = "stairs_down",
         legacy_id = 11,
         tiles = {"core.1_231"},
      },
      {
         id = "stairs_up",
         legacy_id = 10,
         tiles = {"core.1_232"},
      },
      {
         id = "trap",
         legacy_id = 14,
         tiles = {"core.1_234"},
      },
   }
)
