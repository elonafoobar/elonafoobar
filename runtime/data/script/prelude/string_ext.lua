local string_ext = {}
for k, v in pairs(string) do
   string_ext[k] = v
end



function string_ext.at(s, i)
   return s:sub(i, i)
end


string_ext.dump = nil


return string_ext
