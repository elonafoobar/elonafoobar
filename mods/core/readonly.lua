local ReadOnly = {}

function ReadOnly.make_read_only(t)
	for x, y in pairs(t) do
		if type(x) == "table" then
			if type(y) == "table" then
				t[ReadOnly.make_read_only(x)] = ReadOnly.make_read_only[y]
			else
				t[ReadOnly.make_read_only(x)] = y
			end
		elseif type(y) == "table" then
			t[x] = ReadOnly.make_read_only(y)
		end
	end

	local proxy = {}
	local mt = {
		-- hide the actual table being accessed
		__metatable = "read only table",
		__index = function(_, k) return t[k] end,
		__pairs = function() return pairs(t) end,
		__newindex = function (_,_,_)
			error("attempt to update a read-only table", 2)
		end
	}
	setmetatable(proxy, mt)
	return proxy
end

local oldpairs = pairs
function pairs(t)
	local mt = getmetatable(t)
	if mt==nil then
		return oldpairs(t)
	elseif type(mt.__pairs) ~= "function" then
		return oldpairs(t)
	end

	return mt.__pairs()
end

return ReadOnly
