# In-game console

Elona foobar has in-game console re-implemented by using Lua.


## Quickstart

Open the console by pressing `Shift+F12` (this keybinding can be configured).

Then, type your first console command. Following the tradition, the first one is "Hello, world!"

```
>>> :echo "Hello, World!"
Hello, World!
```

To show all of the available commands, type `:?` or `:help`.



## Modes

The console has two kinds of mode, shell mode and Lua mode. The command line starting with `:` is executed in shell mode. Any other inputs are processed in Lua mode. In Lua mode, your input code is executed in an isolated environment from the game. Any variables or functions you defined in the environment will not affect the game, including mods.


## Command namespace

All console commands have own "namespace", usually the mod name where the command is defined. There are two pre-defined namespaces, `_bulitin_` and `_console_`. `_bulitin_` is a namespace for built-in commands defined in C++ or kernel Lua module. `_console_` is one for user-defined commands which are defined via the console. Registered commands are stored in `COMMANDS` table. You can access any commands in Lua mode like this:

```
>>> COMMANDS[namespace][command_name]()
```


## Commands

### `:?`

Alias for `:help`.


### `:help`

```
>>> :help
```

Show all commands.


### `:echo`

```
>>> :echo foo
```

Print the argument to the console.


### `:history`

```
>>> :history
```

Print most recently executed command lines up to 10.


### `:ls`

```
>>> :ls
```

Show all enabled mods with their versions.


### `:wizard`

```
>>> :wizard
```

Activate wizard mode.


### `:voldemort`

```
>>> :voldemort
```

Activate Voldemort mode.


### `:muggle`

```
>>> :muggle
```

Inactivate wizard mode.


### `:wish`

```
>>> :wish [WISH] [NUM]
```

Wish `WISH` `NUM` times.


### `:gain_spell`

```
>>> :gain_spell
```

Learn all spells with much spellstocks.


### `:gain_spact`

```
>>> :gain_spact
```

Learn all spacts (special actions).


### `:gain_exp`

```
>>> :gain_exp [EXP]
```

Gain `EXP` experience (1 billion by default).


### `:gain_fame`

```
>>> :gain_fame [FAME]
```

Gain `FAME` fame (1 million by default).



## Variables

There are some variables available in Lua mode.


### `COMMANDS`

The variable holds all console commands.

```
>>> COMMANDS._builtin_.echo("Hello, World!")
```


### `PROMPT` / `PROMPT2`

They are the prompt text shown in the console. `PROMPT2` is shown when your input Lua snippet is incomplete.

```
>>> PROMPT = "$ "
$ PROMPT2 = "$    "
$ if x < 10 then
$    print("foo")
$    end
```


### `RESULT`

It is the result of the command most recently executed.

```
>>> Chara.player()
>>> p(RESULT.position)
```
