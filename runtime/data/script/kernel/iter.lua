local Iter = {}

function Iter.rectangle_iter_step (size, pos)
   local old = pos
   pos.x = pos.x + 1
   if pos.x == size.sx then
      pos.x = size.x
      pos.y = pos.y + 1
      if pos.y == size.sy then
         return nil, nil
      end
   end

   return pos, old
end

function Iter.rectangle_iter (x, y, sx, sy)
   if x >= sx or y >= sy then
      error("Invalid parameters passed to Iter.rectangle_iter")
   end
   return Iter.rectangle_iter_step, {sx=sx+1, sy=sy+1, x=x}, {x=x-1, y=y}
end

return Iter
