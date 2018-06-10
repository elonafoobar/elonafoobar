require "tests/lua/support/minctest"

local I18N = Elona.require("I18N")

local Chara = Elona.require("Chara")
local FOV = Elona.require("FOV")
local Item = Elona.require("Item")

lrun("test I18N.get", function()
        Testing.start_in_debug_map()

        Testing.load_translations([[
locale {
  foo = "bar"
  baz = "You passed in ${_1} and ${_2}."
  hoge = "You ${is(true)} nice."
  piyo = "She ${is(false)} nice."
  hello = "Hello, ${name(_1)}!"
  hello_base = "Hello, ${basename(_1)}!"
}
]])

        lequal(I18N.get("core.locale.foo"), "bar")
        lequal(I18N.get("core.locale.baz", "dood", 42), "You passed in dood and 42.")
        lequal(I18N.get("core.locale.baz", "dood"), "You passed in dood and <error>.")
        lequal(I18N.get("core.locale.hoge", "dood", 42), "You are nice.")
        lequal(I18N.get("core.locale.piyo", "dood", 42), "She is nice.")

        local chara = Chara.create(23, 23, 3)
        FOV.refresh();
        lequal(I18N.get("core.locale.hello", chara), "Hello, プチ!")
        lequal(I18N.get("core.locale.hello_base", chara), "Hello, プチ!")

        local item = Item.create(0, 1, 792, 3)
        lequal(I18N.get("core.locale.hello", item), "Hello, 3個のプチトロ!")
        lequal(I18N.get("core.locale.hello_base", item), "Hello, プチトロ!")
end)

lrun("test I18N.get_optional", function()
        Testing.start_in_debug_map()

        Testing.load_translations([[
locale {
  foo = "bar"
  baz = "You passed in ${_1} and ${_2}."
  hoge = "You ${is(true)} nice."
  piyo = "She ${is(false)} nice."
  hello = "Hello, ${name(_1)}!"
  hello_base = "Hello, ${basename(_1)}!"
}
]])

        lequal(I18N.get_optional("core.locale.foo"), "bar")
        lequal(I18N.get_optional("core.locale.baz", "dood", 42), "You passed in dood and 42.")
        lequal(I18N.get_optional("core.locale.baz", "dood"), "You passed in dood and <error>.")
        lequal(I18N.get_optional("core.locale.hoge", "dood", 42), "You are nice.")
        lequal(I18N.get_optional("core.locale.piyo", "dood", 42), "She is nice.")

        local chara = Chara.create(23, 23, 3)
        FOV.refresh();
        lequal(I18N.get_optional("core.locale.hello", chara), "Hello, プチ!")
        lequal(I18N.get_optional("core.locale.hello_base", chara), "Hello, プチ!")

        local item = Item.create(0, 1, 792, 3)
        lequal(I18N.get_optional("core.locale.hello", item), "Hello, 3個のプチトロ!")
        lequal(I18N.get_optional("core.locale.hello_base", item), "Hello, プチトロ!")

        lequal(I18N.get_optional("core.locale.asdfg"), nil)
        lequal(I18N.get_optional(""), nil)
end)

assert(lresults())
