require("tests/lua/support/minctest")

lrun("test requiring of non-ASCII filenames", function()
        local test = require("tests/lua/support/テスト")
        lequal(test, "こんにちは")
end)
