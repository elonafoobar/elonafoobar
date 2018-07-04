local scanner = require "elocheck.scanner"

local function scan(src, wanted)
   local state = scanner.new(src)
   return state:scan(wanted)
end

local function try_match(src, wanted)
   local state = scanner.new(src)
   return state:try_match(wanted)
end

local function match_offset(src, wanted)
   local state = scanner.new(src)
   assert.is_true(state:try_match(wanted))
   return state.offset
end

local function scan_until(src, wanted)
   local state = scanner.new(src)
   return state:scan_until(wanted)
end

local function scan_offset(src, wanted)
   local state = scanner.new(src)
   assert.is_true(state:scan_until(wanted))
   return state.offset
end

describe("Scanner", function()
            describe("try_match", function()
                        it("matches", function()
                              assert.is_true(try_match("asd", "a"))
                              assert.is_true(try_match("i18n::s.get", "i18n::s.get"))
                              assert.is_true(try_match("i18n::s.get(", "i18n::s.get"))
                              assert.is_false(try_match("zxc\nasd", "a"))
                              assert.is_false(try_match("a", "asd"))
                        end)
                        it("sets offset", function()
                              assert.is_same(1, match_offset("asd", "a"))
                              assert.is_same(5, match_offset("zxcvasd", "a"))
                              assert.is_same(1, match_offset("aaaaa", "a"))
                              assert.is_same(6, match_offset("aaaaa\t", "\t"))
                              assert.is_same(1, match_offset("i18n::s.get", "i18n::s.get"))
                              assert.is_same(1, match_offset("i18n::s.get(", "i18n::s.get"))
                        end)
            end)
            describe("scan_until", function()
                        it("scans until", function()
                              assert.is_true(scan_until("zxc\nasd", "a"))
                              assert.is_true(scan_until("zxc\nasd", "s"))
                              assert.is_true(scan_until("zxc\n\n\n\n\n\t\ns\nasd", "a"))
                              assert.is_true(scan_until("i18n::s.get", "i18n::s.get"))
                              assert.is_true(scan_until("\ni18n::s.get()", "i18n::s.get"))
                              assert.is_false(scan_until("a", "asd"))
                              assert.is_false(scan_until("", "asd"))
                              assert.is_false(scan_until("z\nx\nc\nf\nas\nd", "asd"))
                        end)
                        it("sets offset", function()
                              assert.is_same(5, scan_offset("zxc\nasd", "a"))
                              assert.is_same(6, scan_offset("zxc\nasd", "s"))
                              assert.is_same(13, scan_offset("zxc\n\n\n\n\n\t\ns\nasd", "a"))
                              assert.is_same(1, scan_offset("i18n::s.get", "i18n::s.get"))
                              assert.is_same(2, scan_offset("\ni18n::s.get()", "i18n::s.get"))
                        end)
            end)
            it("scans nothing", function()
                  assert.same(nil, scan("", "i18n::s.get"))
                  assert.same(nil, scan("i18n::s.get", "i18n::s.get"))
                  assert.same(nil, scan("i18n::s.get(", "i18n::s.get"))
            end)

            it("scans function", function()
                  assert.same({name = "i18n::s.get", args = {}}, scan("i18n::s.get()", "i18n::s.get"))
                  assert.same({name = "i18n::s.get", args = {"\"asdf\""}},
                     scan("i18n::s.get(\"asdf\")", "i18n::s.get"))
                  assert.same({name = "i18n::s.get", args = {"\"\"asdf\"\""}},
                     scan("i18n::s.get(\"\"asdf\"\")", "i18n::s.get"))
                  assert.same({name = "i18n::s.get", args = {"u8\"asdf\""}},
                     scan("i18n::s.get(u8\"asdf\")", "i18n::s.get"))
                  assert.same({name = "i18n::s.get", args = {"\"asdf\"s"}},
                     scan("i18n::s.get(\"asdf\"s)", "i18n::s.get"))
                  assert.same({name = "i18n::s.get", args = {"u8\"asdf\"s"}},
                     scan("i18n::s.get(u8\"asdf\"s)", "i18n::s.get"))
                  assert.same({name = "i18n::s.get", args = {"\"asdf\"", "2"}},
                     scan("i18n::s.get(\"asdf\", 2)", "i18n::s.get"))
                  assert.same({name = "i18n::s.get_enum_property",
                               args = {"\"core.locale.map.unique\"", "\"name\"", "adata(16, id)"}}, scan([[
 name = i18n::s.get_enum_property(
 "core.locale.map.unique", "name", adata(16, id));
]], "i18n::s.get"))
            end)

            it("scans function with concatenation", function()
                  assert.same({name = "i18n::s.get", args = {"\"asdf\" + \"zxcv\""}},
                     scan("i18n::s.get(\"asdf\" + \"zxcv\")", "i18n::s.get"))
                  assert.same({name = "i18n::s.get", args = {"\"asdf\" + \"zxcv\"", "123"}},
                     scan("i18n::s.get(\"asdf\" + \"zxcv\", 123)", "i18n::s.get"))
            end)
end)
