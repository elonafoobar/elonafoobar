require("tests/lua/support/minctest")

local I18N = ELONA.require("core.I18N")

local Chara = ELONA.require("core.Chara")
local FOV = ELONA.require("core.FOV")
local Item = ELONA.require("core.Item")

lrun("test I18N.get", function()
        Testing.start_in_debug_map()

        Testing.reinit_core_and_load_translations([[
local I18N = ELONA.require("core.I18N")

I18N.add {
   foo = "bar",
   baz = "You passed in {$1} and {$2}.",
   hoge = "You {is(true)} nice.",
   piyo = "She {is(false)} nice.",
   hello = "Hello, {name($1)}!",
   hello_base = "Hello, {basename($1)}!",
   item = "Got {itemname($1)}!",
   item_base = "Got {itembasename($1)}!",
}
]])

        lequal(I18N.get("test.foo"), "bar")
        lequal(I18N.get("test.baz", "dood", 42), "You passed in dood and 42.")
        lequal(I18N.get("test.baz", "dood"), "You passed in dood and <missing argument #2>.")
        lequal(I18N.get("test.hoge", "dood", 42), "You are nice.")
        lequal(I18N.get("test.piyo", "dood", 42), "She is nice.")

        local chara = Chara.create(23, 23, "core.putit")
        chara.basename = "putit"
        FOV.refresh();
        lequal(I18N.get("test.hello", chara), "Hello, the putit!")
        lequal(I18N.get("test.hello_base", chara), "Hello, putit!")

        local item = Item.create(0, 1, "core.putitoro", 3)
        lequal(I18N.get("test.item", item), "Got 3 putitoros!")
        lequal(I18N.get("test.item_base", item), "Got putitoro!")
end)

lrun("test I18N.get_optional", function()
        Testing.start_in_debug_map()

        Testing.load_translations([[
local I18N = ELONA.require("core.I18N")

I18N.add {
   foo = "bar",
   baz = "You passed in {$1} and {$2}.",
   hoge = "You {is(true)} nice.",
   piyo = "She {is(false)} nice.",
   hello = "Hello, {name($1)}!",
   hello_base = "Hello, {basename($1)}!",
   item = "Got {itemname($1)}!",
   item_base = "Got {itembasename($1)}!",
}
]])

        lequal(I18N.get_optional("test.foo"), "bar")
        lequal(I18N.get_optional("test.baz", "dood", 42), "You passed in dood and 42.")
        lequal(I18N.get_optional("test.baz", "dood"), "You passed in dood and <missing argument #2>.")
        lequal(I18N.get_optional("test.hoge", "dood", 42), "You are nice.")
        lequal(I18N.get_optional("test.piyo", "dood", 42), "She is nice.")

        lequal(I18N.get_optional("test.asdfg"), nil)
        lequal(I18N.get_optional(""), nil)
end)

lrun("test I18N.get_enum", function()
        Testing.load_translations([[
local I18N = ELONA.require("core.I18N")

I18N.add {
  foo = {
    _0 = "bar",
    _1 = "baz",
    _2 = "hoge {$1}",
  }
}
]])

        lequal(I18N.get_enum("test.foo", 0), "bar")
        lequal(I18N.get_enum("test.foo", 1), "baz")
        lequal(I18N.get_enum("test.foo", 2), "hoge <missing argument #1>")
        lequal(I18N.get_enum("test.foo", 2, "quux"), "hoge quux")
end)

lrun("test I18N.get_enum_property", function()
        Testing.load_translations([[
local I18N = ELONA.require("core.I18N")

I18N.add {
   foo1 = {
      _0 = {
         name = "foo",
         desc = "bar",
      },
      _1 = {
         name = "baz",
         desc = "quux",
      },
      _2 = {
         name = "hoge",
         desc = "piyo {$1}",
      },
   }
}
]])

        lequal(I18N.get_enum_property("test.foo1", "name", 0), "foo")
        lequal(I18N.get_enum_property("test.foo1", "name", 1), "baz")
        lequal(I18N.get_enum_property("test.foo1", "name", 2), "hoge")
        lequal(I18N.get_enum_property("test.foo1", "desc", 0), "bar")
        lequal(I18N.get_enum_property("test.foo1", "desc", 1), "quux")
        lequal(I18N.get_enum_property("test.foo1", "desc", 2), "piyo <missing argument #1>")
        lequal(I18N.get_enum_property("test.foo1", "desc", 2, "fuga"), "piyo fuga")
end)

lrun("test I18N.get_enum_property_optional", function()
        Testing.load_translations([[
local I18N = ELONA.require("core.I18N")

I18N.add {
   foo2 = {
      _0 = {
         name = "foo",
      },
      _1 = {
         name = "baz",
         desc = "bar {$1}",
      },
   }
}
]])

        lequal(I18N.get_enum_property_optional("test.foo2", "name", 0), "foo")
        lequal(I18N.get_enum_property_optional("test.foo2", "name", 1), "baz")
        lequal(I18N.get_enum_property_optional("test.foo2", "desc", 0), nil)
        lequal(I18N.get_enum_property_optional("test.foo2", "desc", 0, "hoge"), nil)
        lequal(I18N.get_enum_property_optional("test.foo2", "desc", 1), "bar <missing argument #1>")
        lequal(I18N.get_enum_property_optional("test.foo2", "desc", 1, "hoge"), "bar hoge")
end)
