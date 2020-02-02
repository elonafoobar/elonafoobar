local table = require("table")

--- Given a candidate search function, iterates over the table, calling the function
--- for each element in the table, and returns the first element the search function returned true.
--- Passes the index as second argument to the function.
--- @usage a= { 1, 2, 3, 4, 5}
---table.find(a, function(v) return v % 2 == 0 end) --produces: 2
--- @usage a = {1, 2, 3, 4, 5}
---table.find(a, function(v, k, x) return k % 2 == 1 end) --produces: 1
-- @tparam table tbl the table to be searched
-- @tparam function func the function to use to search for any matching element
-- @param[opt] ... additional arguments passed to the function
-- @treturn ?|nil|Mixed the first found value, or nil if none was found
function table.find(tbl, func, ...)
    for k, v in pairs(tbl) do
        if func(v, k, ...) then
            return v, k
        end
    end
    return nil
end

--- Merges two tables &mdash; values from first get overwritten by the second.
--- @usage
-- function some_func(x, y, args)
--     args = table.merge({option1=false}, args)
--     if opts.option1 == true then return x else return y end
-- end
-- some_func(1,2) -- returns 2
-- some_func(1,2,{option1=true}) -- returns 1
-- @tparam table tblA first table
-- @tparam table tblB second table
-- @tparam[opt=false] boolean array_merge set to true to merge the tables as an array or false for an associative array
-- @treturn array|table an array or an associated array where tblA and tblB have been merged
function table.merge(tblA, tblB, array_merge)
    if not tblB then
        return tblA
    end
    if array_merge then
        for _, v in pairs(tblB) do
            table.insert(tblA, v)
        end

    else
        for k, v in pairs(tblB) do
            tblA[k] = v
        end
    end
    return tblA
end

--- Creates a deep copy of table without copying userdata objects.
-- @tparam table object the table to copy
-- @treturn table a copy of the table
function table.deepcopy(object)
    local lookup_table = {}
    local function _copy(this_object)
        if type(this_object) ~= "table" then
            return this_object
        elseif this_object.__self then
            return this_object
        elseif lookup_table[this_object] then
            return lookup_table[this_object]
        end
        local new_table = {}
        lookup_table[this_object] = new_table
        for index, value in pairs(this_object) do
            new_table[_copy(index)] = _copy(value)
        end
        return setmetatable(new_table, getmetatable(this_object))
    end
    return _copy(object)
end

--- Returns true if the table contains a given value.
-- @tparam table tbl the table to search
-- @param value the value to search for
function table.contains(tbl, value)
   local function predicate(v)
      return v == value
   end
   return table.find(tbl, predicate)
end

return table
