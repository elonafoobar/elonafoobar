local Env = {}



function Env.new(term)
   local self = {
      COMMANDS = {},
      RESULT = nil,
      PROMPT = ">>> ",
      PROMPT2 = ">>>    ",
      TERM = term,
   }

   prelude.import(self)

   self.print = function(x)
      term.println(tostring(x))
   end
   self.p = function(...)
      term.println(self.inspect(...))
   end

   setmetatable(self, {__index = Env})
   return self
end



function Env:register_command(id, callback)
   self.COMMANDS[id] = callback
end



function Env:inject_core_api(core)
   for name, table in pairs(core) do
      self[name] = table
   end
end



return Env
