local coroutine_ext = {}
for k, v in pairs(coroutine) do
   coroutine_ext[k] = v
end


return coroutine_ext
