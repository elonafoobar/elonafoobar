local History = {}



function History.new()
   local self = {
      _entries = {}, -- first, oldest; last, newest
      _cursor = nil,
   }
   setmetatable(self, {__index = History})
   return self
end



function History:count()
   return #self._entries
end



function History:get(index)
   return self._entries[index]
end



function History:push(new_entry)
   self._entries[#self._entries+1] = new_entry
   self._cursor = nil
end



function History:go_prev()
   if #self._entries == 0 then
      return nil -- no history
   end
   if self._cursor == 1 then
      return nil -- no older history
   end

   if self._cursor == nil then
      self._cursor = #self._entries
   else
      self._cursor = self._cursor - 1
   end
   return self._entries[self._cursor]
end



function History:go_next()
   if #self._entries == 0 then
      return nil -- no history
   end
   if self._cursor == nil or self._cursor == #self._entries then
      return nil -- no newer history
   end

   self._cursor = self._cursor + 1
   return self._entries[self._cursor]
end



return History
