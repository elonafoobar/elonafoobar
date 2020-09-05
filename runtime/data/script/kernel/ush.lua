local USH = {}



local utils = require("utils")

local execute = require("ush/execute")
local Env = require("ush/env")
local History = require("ush/history")



local Shell = {}



function Shell.new(term)
   local self = {
      _input = "",
      _multiline_input = "",
      _is_multiline = false,
      _history = History.new(),
      _env = Env.new(term),
      _term = term,
   }

   setmetatable(self, {__index = Shell})

   return self
end



function Shell:register_builtins(native_builtin_commands)
   local function register(name, callback)
      self.register("_builtin_", name, callback)
   end

   register("help", function()
      local all_commands = {}
      for mod_id, commands in pairs(self._env.COMMANDS) do
         for name, _ in pairs(commands) do
            all_commands[#all_commands+1] = mod_id.."."..name
         end
      end
      table.sort(all_commands)
      for _, command in ipairs(all_commands) do
         self._term.println(command)
      end
   end)

   register("echo", function(s)
      self._term.println(tostring(s))
   end)

   register("history", function()
      local n = self._history:count()
      if n >= 10 then
         n = 10
      end
      for i = 1, n do
         local idx = self._history:count() - n + i
         local entry = self._history:get(idx)
         self._term.println("  "..tostring(idx).."  "..entry)
      end
   end)

   -- Native commands
   for name, callback in pairs(native_builtin_commands) do
      register(name, callback)
   end
end



function Shell:register(mod_id, name, callback)
   if not mod_id or #mod_id == 0 then
      mod_id = "_console_"
   end
   self._env:register_command(mod_id, name, callback)
end



function Shell:run(cmdline)
   self._interpret(cmdline)
   return self._env.RESULT
end



function Shell:inject_core_api(core)
   self._env:inject_core_api(core)
end



function Shell:send_input(input)
   self._input = input
end



function Shell:welcome()
   self._term.println("Elona foobar <Unknown Shell>")
   self._term.println("Type ':?' or ':help' to list all commands")
   self._term.println("")
end



function Shell:prompt()
   self._term.delete_line()
   if self._is_multiline then
      self._term.print(self._env.PROMPT2..self._input)
   else
      self._term.print(self._env.PROMPT..self._input)
   end
end



function Shell:history_prev()
   local prev_entry = self._history:go_prev()
   if prev_entry then
      self._set_input(prev_entry)
   end
end



function Shell:history_next()
   local next_entry = self._history:go_next()
   if next_entry then
      self._set_input(next_entry)
   end
end



function Shell:interrupt()
   self._set_input("")
   self._multiline_input = ""
   self._is_multiline = false
end



function Shell:enter()
   if #self._input == 0 then
      return
   end

   self._term.println("")

   self._multiline_input = self._multiline_input..self._input
   self._set_input("")
   if self._interpret(self._multiline_input) then
      self._multiline_input = self._multiline_input.."\n"
      self._is_multiline = true
   else
      self._history:push(self._multiline_input)
      self._multiline_input = ""
      self._is_multiline = false
   end
end



-- @treturn boolean True if `input` is incomplete Lua; otherwise false
function Shell:_interpret(input)
   if self._is_command(input) then
      return self._interpret_command(input)
   else
      return self._interpret_lua(input)
   end
end



function Shell:_is_command(s)
   return s:match("^%s*:")
end



function Shell:_interpret_command(input)
   input = input:match("^%s*:%s*(.*)$")
   local ok, result = execute(input, self._env)
   if ok then
      self._env.RESULT = result
      self._print_result(result)
   else
      self._env.RESULT = nil
      self._term.println(tostring(result))
   end
   return false
end



function Shell:_interpret_lua(input)
   local status, result = self._eval(input)

   if status == "incomplete" then
      return true
   elseif status == "syntax_error" then
      self._term.println(result)
      return false
   elseif status then
      self._env.RESULT = result
      self._print_result(result)
      return false
   else
      self._env.RESULT = nil
      self._term.println(tostring(result))
      return false
   end
end



function Shell:_eval(s)
   local parse_result, err = load("return "..s, "ush: "..s, "t", self._env)
   if parse_result == nil then
      parse_result, err = load(s, "ush: "..s, "t", self._env)
   end

   if parse_result == nil then
      if err:match("<eof>", -5) then
         return "incomplete"
      else
         return "syntax_error", err
      end
   end

   return pcall(parse_result)
end



function Shell:_print_result(result)
   if result == nil then
      self._term.println("nil")
   elseif type(result) == "string" then
      self._term.println(result)
   else
      self._term.println(prelude.inspect(result))
   end
end



function Shell:_set_input(input)
   self._input = input
   self._term.set_input(input)
end



function USH.new_shell(term)
   return utils.make_singleton(Shell, term)
end


return USH
