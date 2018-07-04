local utils = require "elocheck.utils"
local lfs = require "lfs"

local fs = {}

function fs.get_current_dir()
   return assert(lfs.currentdir())
end

function fs.split_base(path)
   if utils.is_windows then
      if path:match("^%a:\\") then
         return path:sub(1, 3), path:sub(4)
      else
         -- Disregard UNC paths and relative paths with drive letter.
         return "", path
      end
   else
      if path:match("^/") then
         if path:match("^//") then
            return "//", path:sub(3)
         else
            return "/", path:sub(2)
         end
      else
         return "", path
      end
   end
end

function fs.is_absolute(path)
   return fs.split_base(path) ~= ""
end

function fs.normalize(path)
   if utils.is_windows then
      path = path:lower()
   end
   local base, rest = fs.split_base(path)
   rest = rest:gsub("[/\\]", utils.dir_sep)

   local parts = {}

   for part in rest:gmatch("[^"..utils.dir_sep.."]+") do
      if part ~= "." then
         if part == ".." and #parts > 0 and parts[#parts] ~= ".." then
            parts[#parts] = nil
         else
            parts[#parts + 1] = part
         end
      end
   end

   if base == "" and #parts == 0 then
      return "."
   else
      return base..table.concat(parts, utils.dir_sep)
   end
end

function fs.is_dir(path)
   return lfs.attributes(path, "mode") == "directory"
end

function fs.is_file(path)
   return lfs.attributes(path, "mode") == "file"
end

local function ensure_dir_sep(path)
   if path:sub(-1) ~= utils.dir_sep then
      return path .. utils.dir_sep
   end

   return path
end

local function join_two_paths(base, path)
   if base == "" or fs.is_absolute(path) then
      return path
   else
      return ensure_dir_sep(base) .. path
   end
end

function fs.join(base, ...)
   local res = base

   for i = 1, select("#", ...) do
      res = join_two_paths(res, select(i, ...))
   end

   return res
end

-- Returns list of all files in directory matching pattern.
-- Returns nil, error message on error.
function fs.extract_files(dir_path, pattern)
   local res = {}
   local err_map = {}

   local function scan(dir)
      local ok, iter, state, var = pcall(lfs.dir, dir)

      if not ok then
         local err = utils.unprefix(iter, "cannot open " .. dir .. ": ")
         err = "couldn't recursively check: " .. err
         err_map[dir] = err
         table.insert(res, dir)
         return
      end

      for path in iter, state, var do
         if path ~= "." and path ~= ".." then
            local full_path = fs.join(dir, path)

            if fs.is_dir(full_path) then
               scan(full_path)

            elseif path:match(pattern) and fs.is_file(full_path) then
               table.insert(res, full_path)
            end
         end
      end
   end

   scan(dir_path)
   table.sort(res)
   return res, err_map
end

return fs
