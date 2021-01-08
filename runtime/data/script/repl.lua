local function eval(s, env)
   local parse_result, err = load("return "..s, "ush: "..s, "t", env)
   if parse_result == nil then
      parse_result, err = load(s, "ush: "..s, "t", env)
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

function interpret_lua(s, env)
   local status, result = eval(s, env)

   if status == "incomplete" then
      return true
   elseif status == "syntax_error" then
      print(result)
      return false
   elseif status then
      env.RESULT = result
      prelude.p(result)
      return false
   else
      env.RESULT = nil
      print(tostring(result))
      return false
   end
end

-- REPL, Read-Eval-Print Loop
return function()
   -- TODO: use 'ush' module.

   local env = {}
   for k, v in pairs(require("prelude.init")) do
      env[k] = v
   end
   for k, v in pairs(require("core_api")) do
      env[k] = v
   end

   print("Elona foobar <Unknown Shell>")
   print("Type ':?' or ':help' to list all commands")
   print("")

   while true do
      io.write(">>> ")
      local input = io.read("l")
      if input == nil or input == "" then
         goto continue
      end
      if input:sub(1, 1) == ":" then
         -- Command
         if input == ":exit" then
            break
         end
      else
         -- Lua
         interpret_lua(input, env)
      end

      ::continue::
   end
end
