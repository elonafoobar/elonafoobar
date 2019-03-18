local function insert(node, k, v)
   if node.key == k then
      node.value[#node.value + 1] = v
   elseif k > node.key then
      local next_node = node.left
      if not next_node then
         node.left = { key = k, value = {v} }
      else
         insert(next_node, k, v)
      end
   else
      local next_node = node.right
      if not next_node then
         node.right = { key = k, value = {v} }
      else
         insert(next_node, k, v)
      end
   end
end

local function traverse(node, cb, args)
   if node.left then
      if not traverse(node.left, cb, args) then
         return false
      end
   end

   if not cb(node.key, node.value, args) then
      return false
   end

   if node.right then
      if not traverse(node.right, cb, args) then
         return false
      end
   end

   return true
end

local EventTree = {}
EventTree.__index = EventTree

function EventTree:insert(k, v)
   if self.tree == nil then
      self.tree = { key = k, value = {v} }
   else
      insert(self.tree, k, v)
   end
end

function EventTree:traverse(cb, args)
   if self.tree ~= nil then
      traverse(self.tree, cb, args)
   end
end

function EventTree.new()
   local t = {}
   setmetatable(t, EventTree)
   return t
end

return EventTree
