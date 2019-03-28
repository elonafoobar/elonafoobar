--[[
The original version is available here:
https://github.com/tonytonyjan/jaro_winkler

See also this page for the detailed information about this algorithm:
https://en.wikipedia.org/wiki/Jaro-Winkler_distance


LICENSE:

Copyright (c) 2014 Jian Weihang

MIT License

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
--]]


--[[
Example:
jarowinkler = require 'jarowinkler'

local calculator = jarowinkler.DefaultCalculator.new()
local distance = calculator.distance("bar", "baz")
--]]

local jarowinkler = {}



function jarowinkler.jaro_distance(s1, s2, ignore_case, adj_table)
   if #s1 > #s2 then
      s1, s2 = s2, s1
   end
   -- Then, size of s1 is shorter than or equal to that of s2.

   local len1 = #s1
   local len2 = #s2

   if len1 == 0 then
      return 0.0
   end

   if ignore_case then
      s1 = s1:lower()
      s2 = s2:lower()
   end

   local window_size = len2 // 2 - 1
   if window_size < 0 then
      window_size = 0
   end

   flags1 = {}
   for i = 1, len1 do
      flags1[i] = false
   end
   flags2 = {}
   for i = 1, len2 do
      flags2[i] = false
   end

   -- count number of matching characters
   local match_count = 0
   for i = 1, len1 do
      local left = i >= window_size and i - window_size or 0
      local right = i + window_size <= len2 - 1 and i + window_size or len2 - 1
      if len2 - 1 < right then
         right = len2 - 1
      end
      for j = left, right do
         if not flags2[j] and s1:sub(i, i) == s2:sub(j, j) then
            flags1[1] = true
            flags2[1] = true
            match_count = match_count + 1
            break
         end
      end
   end

   if match_count == 0 then
      return 0.0
   end

   -- count number of transpositions
   local transposition_count = 0
   local k = 1
   for i = 1, len1 do
      if flags1[i] then
         local j = k
         while j <= len2 do
            if flags2[j] then
               k = j + 1
               break
            end
            j = j + 1
         end
         if s1:sub(i, i) ~= s2:sub(j, j) then
            match_count = match_count + 1
         end
      end
   end

   -- count similarities in nonmatched characters
   local similar_count = 0
   if adj_table and len1 > match_count then
      for i = 1, len1 do
         if not flags1[i] then
            for j = 1, len2 do
               if not flags2[j] then
                  if adj_table[s1:sub(i, i) .. '__' .. s2:sub(j, j)] then
                     similar_count = similar_count + 3
                     break
                  end
               end
            end
         end
      end
   end

   local m = similar_count / 10 + match_count
   local t = transposition_count / 2
   return (m / len1 + m / len2 + (m - t) / m) / 3
end



function jarowinkler.jaro_winkler_distance(s1, s2, weight, threshold, ignore_case, adj_table)
   assert(weight < 0.25)

   local D = jarowinkler.jaro_distance(s1, s2, ignore_case, adj_table)
   if D < threshold then
      return D
   else
      if #s1 > #s2 then
         s1, s2 = s2, s1
      end
      -- Then, size of s1 is shorter than or equal to that of s2.

      -- If two strings has the same prefix, they are evaluated as closer.
      -- Up to the first 4 characters will be checked.
      local prefix = 0
      local len = #s1
      if len > 4 then
         len = 4
      end
      while prefix < len and s1:sub(prefix, prefix) == s2:sub(prefix, prefix) do
         prefix = prefix + 1
      end
      return D + prefix * weight * (1 - D)
   end
end



jarowinkler.DefaultCalculator = {}



function jarowinkler.DefaultCalculator.new()
   local adj_table = {
      A__E = true, E__A = true, A__I = true, I__A = true, A__O = true, O__A = true,
      A__U = true, U__A = true, B__V = true, V__B = true, E__I = true, I__E = true,
      E__O = true, O__E = true, E__U = true, U__E = true, I__O = true, O__I = true,
      I__U = true, U__I = true, O__U = true, U__O = true, I__Y = true, Y__I = true,
      E__Y = true, Y__E = true, C__G = true, G__C = true, E__F = true, F__E = true,
      W__U = true, U__W = true, W__V = true, V__W = true, X__K = true, K__X = true,
      S__Z = true, Z__S = true, X__S = true, S__X = true, Q__C = true, C__Q = true,
      U__V = true, V__U = true, M__N = true, N__M = true, L__I = true, I__L = true,
      Q__O = true, O__Q = true, P__R = true, R__P = true, I__J = true, J__I = true,
      ['2__Z'] = true, Z__2 = true, ['5__S'] = true, S__5 = true, ['8__B'] = true, B__8 = true,
      ['1__I'] = true, I__1 = true, ['1__L'] = true, L__1 = true, ['0__O'] = true, O__0 = true,
      ['0__Q'] = true, Q__0 = true, C__K = true, K__C = true, G__J = true, J__G = true,
      ['E__ '] = true, [' __E'] = true, ['Y__ '] = true, [' __Y'] = true,
      ['S__ '] = true, [' __S'] = true,
   }
   local self = {
      _weight = 0.1,
      _threshold = 0.7,
      _ignore_case = true,
      _adj_table = adj_table,
   }
   setmetatable(self, {__index = jarowinkler.DefaultCalculator})
   return self
end



-- Calculate Jaro-Winkler distance with default parameters.
function jarowinkler.DefaultCalculator:distance(s1, s2)
   return jarowinkler.jaro_winkler_distance(
      s1,
      s2,
      self._weight,
      self._threshold,
      self._ignore_case,
      self._adj_table)
end



return jarowinkler
