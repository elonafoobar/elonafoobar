# Lua API
Welcome traveler! This is the documentation for the Elona foobar mod API.

Before proceeding, **please note** that the API will almost certainly undergo substantial changes before it is stabilized. If you write anything with the API, expect that it **will** break sometime in the future, until all the serious design/implementation issues and bugs have been worked out.

## Testing it out
You can run a script at startup by adding a parameter to your `config.json`. Copy the `life.lua` example into your `user/script` folder, and add this line to your `config.json`:

```
"startup_script": "life.lua"
```

Starting the game will place you in a script testing map, isolated from your other saves. There you can see the script in action. The `life.lua` script will run Conway's Game of Life by setting tiles in the map. Let's break down how it works.

### Module requires

```
local Map = ELONA.require("core.Map")
local Enums = ELONA.require("core.Enums")
local Event = ELONA.require("core.Event")
local Rand = ELONA.require("core.Rand")
```

At the top, we have some defines. All modules related to the core API can be obtained by using `require`.

### Grid setup

```
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
```

This function will return a new grid for our life simulation. We will use this for setting up the life grid inside our global storage table if it doesn't already exist.

### Logic

```
local function evolve(cell)
-- ...
end
```

This function runs the life simulation. We won't go into the details, but if you're interested you can see [this article](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life).

```
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
               tile = Map.generate_tile("Wall")
            else
               tile = Map.generate_tile("Room")
            end
            Map.set_tile(x, y, tile)
            Map.set_tile_memory(x, y, tile)
         end
      end
      Store.map.grid = evolve(grid)
   end
end
```

Here is the main part of the script. This function updates the game map based on the data we stored. Let's go into detail what it does.

```
   if not Map.is_overworld() then
       -- ...
   end
```

First we need to check if we're traveling in the overworld, where setting tiles on the map wouldn't make sense.

```
      local grid = Store.map.grid
      if grid == nil then
         Store.map.grid = create_life_grid()
         grid = Store.map.grid
      end
```

The table `Store` is for keeping any data we need inside our script.
- `Store.map` holds data that is only relevant to the current map. When the map is changed, it is cleared.
- `Store.global` holds data that persists throughout the entire game session.

In this case, we store the state of our life grid in .map`. This state will be preserved between subsequent calls to `run_life` and will be cleaned up when the map is exited. We also check if the store doesn't have our grid and create it if so.

```
      for y = 1, Map.width() do
         for x = 1, Map.height() do
         -- ...
         end
      end
```

Next we iterate over every x-y pair in the map. Since there is only ever one map loaded at a time, we can call `Map.width` and `Map.height` without passing in anything.

```
            local tile
            if Store.map.grid[x][y] == 1 and not Map.is_blocked(x, y) then
               tile = Map.generate_tile(Enums.TileKind.Wall)
            else
               tile = Map.generate_tile(Enums.TileKind.Room)
            end
            Map.set_tile(x, y, tile)
            Map.set_memory(x, y, tile)
```

Here is where we make use of the `Map` module to modify the map. You can read the documentation for `Map.is_blocked`, `Map.generate_tile` and `Map.set_tile` elsewhere in the docs. Essentially, if the simulation reports a cell with value 1, we set that square to a wall tile, else to a floor tile. We also make sure to set the player's memory of that tile so they can see it even if it's out of field of view.

We also use the enum type `TileKind` here. Some functions take enums to denote one of several different states an object can be in, like the curse state of an object (`Blessed`, `None`, `Cursed`, or `Doomed`). These will typically be found inside the `Enum` module. You also can pass the name of the enum itself without using the `Enums` table (like `Map.generate_tile("Wall")`), to avoid having to `require` `Enums` all the time.

```
      Store.map.grid = evolve(grid)
```

Lastly, we call our logic function to update the state of our life grid.

### Events

```
Event.register("core.map_initialized", run_life)
Event.register("core.all_turns_finished", run_life)
```

Finally, this is the most critical part of the script: hooking it up so it can be ran in response to in-game events. The `Event.register` function will set up a function you provide to be called when an in-game event is fired. In this case, we want to run our function `run_life` when the map is first loaded and every time all characters in the map have finished moving. There are various kinds of events you can listen for, and they are listed in the documentation for `core.event`

That's all for this tutorial. Go forth and find game-breaking bugs! (and preferably report them to us)
