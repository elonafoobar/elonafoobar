#include "../thirdparty/catch2/catch.hpp"

#include "../dialog/dialog_data.hpp"
#include "../dialog/dialog_decoder.hpp"
#include "../lua_env/lua_env.hpp"
#include "../testing.hpp"
#include "tests.hpp"
#include "util.hpp"

using namespace std::literals::string_literals;
using namespace elona;

namespace
{

optional<DialogData> load(const std::string& str, lua::LuaEnv& lua)
{
    lua.get_state()->set("_DIALOG", str);
    sol::optional<sol::table> parsed = lua.get_state()->safe_script(R"(
local HCL = require "hclua"
local parsed = HCL.parse(_DIALOG)

if parsed.msg then
  -- parse failed
  return nil
end

local dialog = parsed.dialog
dialog._full_id = "test.dialog.test"
return dialog
)");

    if (!parsed)
    {
        return none;
    }

    return DialogDecoderLogic(lua.get_export_manager()).decode(*parsed);
}

bool load_fails(const std::string& str, lua::LuaEnv& lua)
{
    return !static_cast<bool>(load(str, lua));
}

} // namespace

TEST_CASE("Loading an invalid dialog should provide nothing", "[Dialog]")
{
    lua::LuaEnv lua;

    REQUIRE(load_fails(
        R"(
dialog {
    foo = "bar"
}
)",
        lua));
}


TEST_CASE("Loading a dialog without any nodes should fail", "[Dialog]")
{
    lua::LuaEnv lua;

    REQUIRE(load_fails(
        R"(
dialog {
    nodes {
    }
}
)",
        lua));
}

TEST_CASE("Loading a dialog node with blank choices should fail", "[Dialog]")
{
    lua::LuaEnv lua;

    REQUIRE(load_fails(
        R"(
dialog {
    nodes {
        _start {
            text = "foo"
        }
    }
}
)",
        lua));
}

TEST_CASE("Loading a dialog node with blank text should fail", "[Dialog]")
{
    lua::LuaEnv lua;

    REQUIRE(load_fails(
        R"(
dialog {
    nodes {
        _start {
            choices = End
        }
    }
}
)",
        lua));
}

TEST_CASE(
    "Loading a dialog node choice with blank text should fail",
    "[Dialog]")
{
    lua::LuaEnv lua;

    REQUIRE(load_fails(
        R"(
dialog {
    nodes {
        _start {
            text = "foo"
            choices = [
                {
                    node = "bar"
                }
            ]
        }
    }
}
)",
        lua));
}

TEST_CASE(
    "Loading a dialog node choice with blank next node should fail",
    "[Dialog]")
{
    lua::LuaEnv lua;

    REQUIRE(load_fails(
        R"(
dialog {
    nodes {
        _start {
            text = "foo"
            choices = [
                {
                    text = "bar"
                }
            ]
        }
    }
}
)",
        lua));
}

TEST_CASE("Loading a dialog without a _start node should fail", "[Dialog]")
{
    lua::LuaEnv lua;

    REQUIRE(load_fails(
        R"(
dialog {
    nodes {
        foo {
            text = "bar"
            choices = End
        }
    }
}
)",
        lua));
}

TEST_CASE(
    "Loading a dialog node with unknown Lua callback should fail "
    "(before/after)",
    "[Dialog]")
{
    lua::LuaEnv lua;

    REQUIRE(load_fails(
        R"(
dialog {
    nodes {
        _start {
            text = "bar"
            run_before = "baz"
            choices = End
        }
    }
}
)",
        lua));

    REQUIRE(load_fails(
        R"(
dialog {
    nodes {
        _start {
            text = "bar"
            run_after = "baz"
            choices = End
        }
    }
}
)",
        lua));
}

TEST_CASE(
    "Loading a dialog node with unknown Lua callback should fail (generator)",
    "[Dialog]")
{
    lua::LuaEnv lua;

    REQUIRE(load_fails(
        R"(
dialog {
    nodes {
        _start {
            text = "bar"
            generator = "baz"
            choices = End
        }
    }
}
)",
        lua));
}

TEST_CASE(
    "Loading a dialog node with unknown Lua callback should fail (redirector)",
    "[Dialog]")
{
    lua::LuaEnv lua;

    REQUIRE(load_fails(
        R"(
dialog {
    nodes {
        _start {
            text = "bar"
            redirector = "baz"
            choices = End
        }
    }
}
)",
        lua));
}

TEST_CASE(
    "Loading a dialog node with more than one extra behavior should fail",
    "[Dialog]")
{
    lua::LuaEnv lua;
    testing::register_lua_function(lua, "test", "my_callback()", "return nil");

    REQUIRE(load_fails(
        R"(
dialog {
    nodes {
        _start {
            text = "foo"
            generator = "exports:test.my_callback"
            redirector = "exports:test.my_callback"
            choices = End
        }
    }
}
)",
        lua));

    REQUIRE(load_fails(
        R"(
dialog {
    nodes {
        _start {
            text = "foo"
            redirector = "exports:test.my_callback"
            inherit_choices = "bar"
            choices = End
        }
    }
}
)",
        lua));
}

TEST_CASE(
    "Using a string as a node's text field should make single text",
    "[Dialog]")
{
    lua::LuaEnv lua;

    auto data = load(
        R"(
dialog {
    nodes {
        _start {
            text = "foo"
            choices = End
        }
    }
}
)",
        lua);

    REQUIRE_SOME(data);
    REQUIRE(data->text_key() == "foo");
    REQUIRE_SOME(data->choices());
    REQUIRE(data->choices()->size() == 1);
}

TEST_CASE(
    "Using an array as a node's text field should chain multiple texts",
    "[Dialog]")
{
    lua::LuaEnv lua;

    auto data = load(
        R"(
dialog {
    nodes {
        _start {
            text = ["foo", "bar", "baz"]
            choices = End
        }
    }
}
)",
        lua);

    REQUIRE_SOME(data);
    REQUIRE(data->text_key() == "foo");
    REQUIRE_NONE(data->choices());
}

TEST_CASE(
    "Advancing a multiple text node should show the next text",
    "[Dialog]")
{
    lua::LuaEnv lua;

    auto data = load(
        R"(
dialog {
    nodes {
        _start {
            text = ["foo", "bar", "baz"]
            choices = End
        }
    }
}
)",
        lua);

    REQUIRE(data->text_index() == 0);

    REQUIRE(data->advance(0));

    REQUIRE(data->text_index() == 1);
    REQUIRE(data->text_key() == "bar");
    REQUIRE_NONE(data->choices());

    REQUIRE(data->advance(0));

    REQUIRE(data->text_index() == 2);
    REQUIRE(data->text_key() == "baz");
    REQUIRE_SOME(data->choices());
    REQUIRE(data->choices()->size() == 1);
}

TEST_CASE(
    "Advancing past end of dialog should make it run out of text",
    "[Dialog]")
{
    lua::LuaEnv lua;

    auto data = load(
        R"(
dialog {
    nodes {
        _start {
            text = ["foo", "bar"]
            choices = End
        }
    }
}
)",
        lua);

    REQUIRE_SOME(data->node_id());

    REQUIRE(data->advance(0));

    REQUIRE_SOME(data->node_id());

    REQUIRE(data->advance(0));

    REQUIRE_NONE(data->node_id());
}
