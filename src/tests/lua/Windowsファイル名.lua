require_relative("tests/lua/support/minctest")

lrun("test requiring of non-ASCII filenames", function()
        local test = require_relative("tests/lua/support/テスト")
        lequal(test, "こんにちは")
end)
