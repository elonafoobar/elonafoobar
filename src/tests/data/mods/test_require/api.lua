local function hello()
   return "Hello!"
end

api:add {
   Hello = {hello = hello}
}
