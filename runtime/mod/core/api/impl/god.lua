local Data = ELONA.require("core.Data")
local table = table



local God = {}



function God.is_offerable(offering, believer)
   if not believer.god then
      return false
   end

   local god_data = Data.get("core.god", believer.god)
   if not god_data then
      return false
   end

   return not not table.contains(god_data.offerings, offering.id)
end



return God
