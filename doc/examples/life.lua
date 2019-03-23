local Map = Elona.require("Map")
local Enums = Elona.require("Enums")
local Event = Elona.require("Event")
local Rand = Elona.require("Rand")

local function create_life_grid()
   local grid = {}
   for i = 1, Map.width() do
      grid[i] = {}

      for j = 1, Map.height() do
         grid[i][j] = Rand.rnd(2)
      end
   end
   return grid
end

-- Appropriated from https://rosettacode.org/wiki/Conway%27s_Game_of_Life#Lua
-- It's a bit messy.
local function evolve(cell)
   local m = #cell
   local cell2 = {}
   for i = 1, m do
      cell2[i] = {}
      for j =1, m do
         cell2[i][j] = cell[i][j]
      end
   end

   for i = 1, m do
      for j = 1, m do
         local count
         if cell2[i][j] == 0 then count = 0 else count = -1 end
         for x = -1, 1 do
            for y = -1, 1 do
               if i+x >= 1 and i+x <= m
                  and j+y >= 1 and j+y <= m
                  and cell2[i+x][j+y] == 1
               then
                  count = count + 1
               end
            end
         end
         if count < 2 or count > 3 then cell[i][j] = 0 end
         if count == 3 then cell[i][j] = 1 end
      end
   end
   return cell
end

local function run_life()
   if not Map.is_overworld() then
      local grid = Store.map.grid
      if grid == nil then
         Store.map.grid = create_life_grid()
         grid = Store.map.grid
      end
      for y = 1, Map.width() do
         for x = 1, Map.height() do
            local tile
            if Store.map.grid[x][y] == 1 and not Map.is_blocked(x, y) then
               tile = Map.generate_tile(Enums.TileKind.Wall)
            else
               tile = Map.generate_tile(Enums.TileKind.Room)
            end
            Map.set_tile(x, y, tile)
            Map.set_memory(x, y, tile)
         end
      end
      Store.map.grid = evolve(grid)
   end
end

Event.register("core.map_initialized", run_life)
Event.register("core.all_turns_finished", run_life)
