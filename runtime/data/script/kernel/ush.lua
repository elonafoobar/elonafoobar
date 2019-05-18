local ush = {}



local E
local parse = require 'ush/parse'
local execute = require 'ush/execute'



function ush.init(environment)
   E = environment

   -- echo
   ush.register('_BUILTIN_', 'echo', function(...)
      -- TODO do not use inspect
      local x = ...
      E.print(E.COMMANDS._BUILTIN_.inspect(x))
      return nil
   end)

   -- help
   ush.register('_BUILTIN_', 'help', function(...)
      local list = {}
      for namespace, command_table in pairs(E.COMMANDS) do
         for name, _ in pairs(command_table) do
            list[#list+1] = namespace .. '.' .. name
         end
      end
      table.sort(list)
      return list
   end)
end



function ush.run(cmdline)
   local ast = parse(cmdline)
   E.RESULT = execute(ast, E)
   if E.RESULT ~= nil then
      E.print(tostring(E.RESULT))
   end
   return E.RESULT
end



function ush.register(mod_name, name, callback)
   if not mod_name or #mod_name == 0 then
      mod_name = '_CONSOLE_'
   end
   if not E.COMMANDS[mod_name] then
      E.COMMANDS[mod_name] = {}
   end
   E.COMMANDS[mod_name][name] = callback
end



return ush
