local inspect = require_relative("inspect")

local function insert(node, k, v)
   if node.key == k then
      node.value[#node.value + 1] = v
   elseif k > node.key then
      local next_node = node.left
      if not next_node then
         node.left = { key = k, value = {v}, parent = node }
      else
         insert(next_node, k, v)
      end
   else
      local next_node = node.right
      if not next_node then
         node.right = { key = k, value = {v}, parent = node }
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

local function find_minimum(node)
   local node = node
   while node.left do
      node = node.left
   end
   return node
end

local function replace(node, new_node)
   if node.parent then
      if node == node.parent.left then
         node.parent.left = new_node
      else
         node.parent.right = new_node
      end
   end
   if new_node then
      new_node.parent = node.parent
   end
end

local function find(tbl, value)
   for i, v in ipairs(tbl) do
      if v == value then
         return v, i
      end
   end

   return nil
end

local function remove_value(node, value)
   if node.left then
      if remove_value(node.left, value) then
         return true
      end
   end

   local it, index = find(node.value, value)

   if index then
      table.remove(node.value, index)
      if #node.value > 0 then
         return true
      end

      if node.left and node.right then
         local min = find_minimum(node.right)
         node.value = min.value

         if min.left then
            replace(min, min.left)
         elseif min.right then
            replace(min, min.right)
         else
            replace(min)
         end
      elseif node.left then
         replace(node, node.left)
      elseif node.right then
         replace(node, node.right)
      else
         replace(node)
      end
      return true
   end

   if node.right then
      if remove_value(node.right, value) then
         return true
      end
   end

   return false
end

local function print_tree(node, prefix, tail)
   if tail then
      print(prefix .. "└── " .. node.key .. " " .. inspect(node.value))
   else
      print(prefix .. "├── " .. node.key .. " " .. inspect(node.value))
   end

   local bit = "│   "
   if tail then
      bit = "    "
   end

   if node.left and node.right then
      print_tree(node.left, prefix .. bit, false)
      print_tree(node.right, prefix .. bit, true)
   elseif node.left then
      print_tree(node.left, prefix .. bit, true)
   elseif node.right then
      print_tree(node.right, prefix .. bit, true)
   end
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

function EventTree:remove_value(value)
   if self.tree ~= nil then
      if self.tree.left then
         if remove_value(self.tree.left, value) then
            return true
         end
      end

      local it, index = find(self.tree.value, value)

      if index then
         table.remove(self.tree.value, index)
         if #self.tree.value > 0 then
            return true
         end

         if self.tree.left and self.tree.right then
            local min = find_minimum(self.tree.right)
            self.tree.value = min.value

            if min.left then
               replace(min, min.left)
            elseif min.right then
               replace(min, min.right)
            else
               replace(min)
            end
         elseif self.tree.left then
            self.tree = self.tree.left
         elseif self.tree.right then
            self.tree = self.tree.right
         else
            self.tree = nil
         end
         return true
      end

      if self.tree.right then
         if remove_value(self.tree.right, value) then
            return true
         end
      end
   end
end

function EventTree:print()
   if self.tree ~= nil then
      print_tree(self.tree, "", true)
   end
end

function EventTree.new()
   local t = {}
   setmetatable(t, EventTree)
   return t
end

return EventTree
