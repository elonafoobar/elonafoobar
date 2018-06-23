# elomod
Welcome traveler! This is the documentation for the ElonaFoobar mod API.

Before proceeding, **please note** that the API will almost certainly undergo substantial changes before it is stabilized. If you write anything with the API, expect that it **will** break sometime in the future, until all the serious design/implementation issues and bugs have been worked out.

## Testing it out
Start a new game and activate `voldemort` mode by pressing F12. All characters should have health bars visible. Now press `~` (that's the tilde key) to bring up the debug console. You can use this to run Lua code in-game. Run this code to print something in the console.

```
Debug.print("Hello.")
```

It should output the following.

![debug_print](../debug_print.png)

The text `Hello.` should be printed, followed by `nil`. The last thing printed after execution (in this case, `nil`) is the return value of the statement that was run.

To spawn a monster next to your character, run these two lines of code. You can use variables defined in earlier code statements in later ones.

```
pos = Chara.player().position
Chara.create(pos.x, pos.y+1, 3)
```

A putit should be created right in front of you.

Now let's run a function at a given interval. Run this code to spawn an item after each turn ends.

```
Event.register(Event.EventKind.AllTurnsFinished, function() Item.create(Map.random_pos(), 792) end)
```

Wait many turns. Soon the map will be flooded with putitoros!

![putitoros](../putitoros.png)

To stop the event from running, run the following function.

```
Event.clear()
```

## Writing scripts
You can run a script at startup by adding a parameter to your `config.json`. Copy the `life.lua` example into your `data/script` folder, and add this line to your `config.json`:

```
"startup_script": "life.lua"
```

Starting the game will place you in a script testing map, isolated from your other saves. There you can see the script in action. You can also load scripts from the debug console by running `Debug.load_script("<script name>.lua")`.

The `life.lua` script will run Conway's Game of Life by setting tiles in the map. Let's break down how it works.

### Module requires

```
local Map = Elona.require("Map")
local Enums = Elona.require("Enums")
local Event = Elona.require("Event")
local Rand = Elona.require("Rand")
```

At the top, we have some defines. All modules related to the core API can be obtained by using `Elona.require`.

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
      local grid = Store.grid
      if grid == nil then
         Store.grid = create_life_grid()
         grid = Store.grid
      end
      for y = 1, Map.width() do
         for x = 1, Map.height() do
            local tile
            if Store.grid[x][y] == 1 and Map.can_access(x, y) then
               tile = Map.generate_tile(Enums.TileKind.Wall)
            else
               tile = Map.generate_tile(Enums.TileKind.Room)
            end
            Map.set_tile(x, y, tile)
            Map.set_tile_memory(x, y, tile)
         end
      end
      Store.grid = evolve(grid)
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
      local grid = Store.grid
      if grid == nil then
         Store.grid = create_life_grid()
         grid = Store.grid
      end
```

The table `Store` is for keeping any global data we need inside our script. In this case, we store the state of our life grid. This state will be preserved between subsequent calls to `run_life`. We also check if the store doesn't have our grid and create it if so.

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
            if Store.grid[x][y] == 1 and Map.can_access(x, y) then
               tile = Map.generate_tile(Enums.TileKind.Wall)
            else
               tile = Map.generate_tile(Enums.TileKind.Room)
            end
            Map.set_tile(x, y, tile)
            Map.set_tile_memory(x, y, tile)
```

Here is where we make use of the `Map` module to modify the map. You can read the documentation for `Map.can_access`, `Map.generate_tile` and `Map.set_tile` elsewhere in the docs. Essentially, if the simulation reports a cell with value 1, we set that square to a wall tile, else to a floor tile. We also make sure to set the player's memory of that tile so they can see it even if it's out of field of view.

We also use the enum type `TileKind` here. Some functions take enums to denote one of several different states an object can be in, like the curse state of an object (`Blessed`, `None`, `Cursed`, or `Doomed`). These will typically be found inside the `Enum` module.

```
      Store.grid = evolve(grid)
```

Lastly, we call our logic function to update the state of our life grid.

### Events

```
Event.register(Event.EventKind.MapInitialized, run_life)
Event.register(Event.EventKind.AllTurnsFinished, run_life)
```

Finally, this is the most critical part of the script: hooking it up so it can be ran in response to in-game events. The `Event.register` function will set up a function you provide to be called when an in-game event is fired. In this case, we want to run our function `run_life` when the map is first loaded and every time all characters in the map have finished moving. There are various kinds of events you can listen for, and they are listed in the documentation for `Defines.EventKind`.

That's all for this tutorial. Go forth and find game-breaking bugs! (and preferably report them to us)
