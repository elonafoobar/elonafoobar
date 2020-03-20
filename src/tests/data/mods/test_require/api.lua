local function hello()
   return "Hello!"
end

ELONA.api:add {
   Hello = {hello = hello}
}
