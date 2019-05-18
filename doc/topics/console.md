# In-game console

Elona foobar has in-game console re-implemented by using Lua.


## Quickstart

Enter wizard mode by pressing `F12`, and type `~` to open console window. TODO: the default keybinding will be changed soon.

Then, type your first console command. Following the tradition, the first one is "Hello, world!"

```
> echo "Hello, World!"
Hello, World!
```

To show all of the available commands, do `help` command or use `?` instead.



## Details

### Mode

The console has two kinds of mode, shell mode and Lua mode. When you are in shell mode, you will see the prompt `>`. In Lua mode, the prompt changes to `lua>`. In command mode, the first string is regarded as a command name, and the rest is passed to the command, like Unix shells. Lua mode provides a simple REPL environment (read-eval-print loop). For both modes, all execution of commands and functions are performed in an isolated environment (pseudo mode `_CONSOLE_`), so that no side-effect happens to the game.


### Command namespace

All console commands have own "namespace", usually the mod name where the command is defined. There are two pre-defined namespaces, `_BULITIN_` and `_CONSOLE_`. `_BULITIN_` is a namespace for built-in commands defined from C++ code or kernel Lua module. `_CONSOLE_` is one for user-defined commands which are defined via the console. (TODO: but currently, there is no way to define new commands from console.) Registered commands are stored in `COMMANDS` table. You can access any commands in Lua mode like this:

```
lua> COMMANDS[namespace][command_name]()
```


### Pipeline

In contrast to Unix shell, `ush` flushes *object* to pipeline (it is similar to PowerShell).



### Command line syntax

In this section, I will explain syntax of command line input in shell mode.


**Sequential execution**

```
> xxx a b c; yyy d e f
```


**Consitional execution**

```
> xxx a b c && yyy d e f
> xxx a b c || yyy d e f
```


**Pipeline**

```
> xxx a b c | yyy d e f
```

Lua supports multiple result, but the shell does not. Only the first result is passed to the next.


**Redirect**

```
> xxx a b c > file
```

Input redirect is not supported.


**Command grouping**

```
> { xxx a b c; yyy a b c }
> ( xxx a b c; yyy a b c )
```

Commands enclosed by `{` and `}` are executed in the current shell. In contrast, commands enclosed by `(` and `)` are executed in a subshell.


**Variables**

```
> echo $VARIABLE
> echo ${VARIABLE}
```


**Command substitution**

```
> echo $(xxx a b c)
```


**Embedded Lua expression**

```
> echo (( 1 + 2 ))
> echo [[ 1 + 2 ]]
```

The latter notation returns only boolean, i.e., the result of the expression is cast to boolean.


**String quoting and escaping**

```
> echo "\"1 2 3\""
> echo '"1 2 3"'
> echo \"1\ 2\ 3\"
```

The three commands will output the same result. Double quotation allows you to write escape sequence, command substitution, and variable reference in the quoted strings, but single quote does not.
