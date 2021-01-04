local exports = {}

function exports.get_nth_selection_key(n)
   return ({
      "a", "b", "c", "d", "e", "f", "g", "h", "i", "j",
      "k", "l", "m", "n", "o", "p", "q", "r", "s", "t",
      "u", "v", "w", "x", "y", "z",
   })[n] or "?"
end

return exports
