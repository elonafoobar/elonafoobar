local jarowinkler = require 'ush/jarowinkler'



local _did_you_mean_threshold = 0.8



local function _is_assignment(ast)
   return false -- TODO
end



local function _normalize_command_name(s)
   return s:lower():gsub('-', '_')
end



local Executor = {}



function Executor.new(E)
   local self = {
      pipe_args = {},
      E = E,
   }
   setmetatable(self, {__index = Executor})
   return self
end



function Executor:_look_up_command(command_name)
   -- special alias for 'help'
   if command_name == '?' then
      command_name = 'help'
   else
      command_name = _normalize_command_name(command_name)
   end
   local has_namespace = command_name:find('%.')

   local commands = {}
   for namespace, command_table in pairs(self.E.COMMANDS) do
      for name, callback in pairs(command_table) do
         local full_name = namespace .. '.' .. name
         if has_namespace then
            if full_name == command_name then
               return callback -- perfect match; return it immediately.
            end
         else
            if name == command_name then
               -- partial match; add it to candidates.
               commands[#commands+1] = {
                  namespace = namespace,
                  name = name,
                  full_name = full_name,
                  callback = callback,
               }
               break
            end
         end
      end
   end

   if #commands == 1 then
      return commands[1].callback
   end

   if #commands > 1 then
      if #commands == 2 then
         -- If one of the two is built-in command, the other overrides it and is executed.
         if commands[1].namespace == '_BUILTIN_' then return commands[2].callback end
         if commands[2].namespace == '_BUILTIN_' then return commands[1].callback end
         -- If one of the two is user-defined command, the other overrides it and is executed.
         if commands[1].namespace == '_CONSOLE_' then return commands[2].callback end
         if commands[2].namespace == '_CONSOLE_' then return commands[1].callback end
      end

      -- Ambiguous invocation.
      self.E.print("Command invocation '" .. name .. "' is ambiguous:")
      table.sort(commands, function(a, b) return a.full_name < b.full_name end)
      for _, cmd in ipairs(commands) do
         self.E.print('  ' .. cmd.full_name)
      end

      return nil -- Not found
   end

   assert(#commands == 0)

   -- Do "Did you mean?" suggestion.
   local did_you_mean = {}
   local calculator = jarowinkler.DefaultCalculator.new()
   for _, cmd in ipairs(commands) do
      local distance = calculator:distance(command_name, has_namespace and cmd.full_name or cmd.name)
      if distance >= _did_you_mean_threshold then
         did_you_mean[#did_you_mean+1] = {distance = distance, command_name = full_name}
      end
   end
   table.sort(did_you_mean, function(a, b) return a.distance < b.distance end)

   self.E.print('Command not found: ' .. command_name)
   if #did_you_mean ~= 0 then
      if #did_you_mean == 1 then
         self.E.print("Did you mean '" .. did_you_mean[1].command_name .. "'?")
      else
         self.E.print("Did you mean these command?")
         for _, cmd in ipairs(did_you_mean) do
            self.E.print('  ' .. cmd.command_name)
         end
      end
   end

   return nil -- Not found
end



function Executor:execute(ast)
   return self:dispatch(ast)
end



function Executor:invoke(cmd_name, args)
   local pipe_arg = self.pipe_args[#self.pipe_args]
   if pipe_arg then
      args[#args+1] = pipe_arg
      table.remove(self.pipe_args)
   end

   local cmd = self:_look_up_command(cmd_name)
   if not cmd then return nil end

   -- self.E.print('RUN  ' .. cmd_name .. '  ' .. table.concat(args, ' '))
   return cmd(table.unpack(args))
end



function Executor:dispatch(ast)
   local method_name = 'visit_' .. ast.class
   return self[method_name](self, ast)
end



function Executor:visit_commandlistthen(ast)
   self.E.RESULT = self:dispatch(ast.lhs)
   self.E.RESULT = self:dispatch(ast.rhs)
   return self.E.RESULT
end



function Executor:visit_commandlistand(ast)
   self.E.RESULT = self:dispatch(ast.lhs)
   if self.E.RESULT then
      self.E.RESULT = self:dispatch(ast.rhs)
   end
   return self.E.RESULT
end



function Executor:visit_commandlistor(ast)
   self.E.RESULT = self:dispatch(ast.lhs)
   if not self.E.RESULT then
      self.E.RESULT = self:dispatch(ast.rhs)
   end
   return self.E.RESULT
end



function Executor:visit_pipeline(ast)
   self.E.RESULT = self:dispatch(ast.lhs)
   self.pipe_args[#self.pipe_args+1] = self.E.RESULT
   self.E.RESULT = self:dispatch(ast.rhs)
   return self.E.RESULT
end



function Executor:visit_redirectcommand(ast)
   error('TODO')
end



function Executor:visit_simplecommand(ast)
   if _is_assignment(ast) then
      error('TODO')
   else
      local cmd_name = self:dispatch(ast.command_name)
      local args = {}
      for _, arg in ipairs(ast.arguments) do
         args[#args+1] = self:dispatch(arg)
      end
      return self:invoke(cmd_name, args)
   end
end



function Executor:visit_commandgroup(ast)
   if ast.subshell then
      error('TODO')
   else
      self.E.RESULT = self:dispatch(ast.command)
   end
   return self.E.RESULT
end



function Executor:visit_stringliteral(ast)
   return ast.string
end



function Executor:visit_variable(ast)
   -- self.E.print('Variable: ${' .. ast.name .. '}')
   return self.E[ast.name]
end



function Executor:visit_commandsubstitution(ast)
   error('TODO')
end



function Executor:visit_string(ast)
   local ss = {}
   for _, segment in ipairs(ast.segments) do
      ss[#ss+1] = self:dispatch(segment)
   end
   return table.concat(ss)
end



return function(ast, E)
   local exe = Executor.new(E)
   return exe:execute(ast)
end
