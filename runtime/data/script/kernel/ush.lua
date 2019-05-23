local ush = {}



local E
local parse = require 'ush/parse'
local execute = require 'ush/execute'



function ush.init(environment)
   E = environment

   -- echo
   ush.register('_BUILTIN_', 'echo', function(...)
      local function do_echo(x, indent)
         if type(x) == 'table' then
            for k, v in pairs(x) do
               if type(k) ~= 'number' or k < 1 or #x < k then
                  E.print(('  '):rep(indent) .. tostring(k))
               end
               do_echo(v, indent + 1)
            end
         else
            E.print(('  '):rep(indent) .. tostring(x))
         end
      end

      local args = {...}
      if #args == 1 then
         do_echo(args[1], -1)
      else
         do_echo(args, -1)
      end
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
      E.COMMANDS._BUILTIN_.echo(E.RESULT)
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
