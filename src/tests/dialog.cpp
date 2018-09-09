#include "../thirdparty/catch2/catch.hpp"

#include "../dialog/dialog_data.hpp"
#include "../dialog/dialog_decoder.hpp"
#include "../lua_env/config_table.hpp"
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
    auto result = lua.get_state()->safe_script(R"(
local HCL = require "hclua"
local parsed = HCL.parse(_DIALOG)

if parsed.msg then
  -- parse failed
  return nil
end

local dialog = parsed.dialog
dialog._full_id = "core.dialog:test"
return dialog
)");

    if (!result.valid())
    {
        return none;
    }

    auto parsed = result.get<sol::table>();

    if (parsed == sol::lua_nil)
    {
        return none;
    }

    try
    {
        lua::ConfigTable wrapped_result(parsed);
        return DialogDecoderLogic(lua.get_export_manager())
            .decode(wrapped_result);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return none;
    }
}

} // namespace

TEST_CASE("Loading an invalid dialog should fail", "[Dialog]")
{
    lua::LuaEnv lua;

    REQUIRE_NONE(load(
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

    REQUIRE_NONE(load(
        R"(
dialog {
    nodes {
    }
}
)",
        lua));
}

TEST_CASE(
    "Loading a dialog node with blank choices should cause invalid state",
    "[Dialog]")
{
    lua::LuaEnv lua;

    auto data = load(
        R"(
dialog {
    nodes {
        _start {
            text = "foo"
        }
    }
}
)",
        lua);

    REQUIRE_SOME(data);

    REQUIRE_FALSE(data->state_is_valid());
}

TEST_CASE(
    "Loading a dialog node with blank text should cause invalid state",
    "[Dialog]")
{
    lua::LuaEnv lua;

    auto data = load(
        R"(
dialog {
    nodes {
        _start {
            choices = End
        }
    }
}
)",
        lua);
}

TEST_CASE(
    "Loading a dialog node with text of the wrong type should fail",
    "[Dialog]")
{
    lua::LuaEnv lua;

    REQUIRE_NONE(load(
        R"(
dialog {
    nodes {
        _start {
            text = 42
            choices = End
        }
    }
}
)",
        lua));
}


TEST_CASE(
    "Loading a dialog node with choices of the wrong type should fail",
    "[Dialog]")
{
    lua::LuaEnv lua;

    REQUIRE_NONE(load(
        R"(
dialog {
    nodes {
        _start {
            text = "foo"
            choices = 42
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

    REQUIRE_NONE(load(
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

    REQUIRE_NONE(load(
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

    REQUIRE_NONE(load(
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

    REQUIRE_NONE(load(
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

    REQUIRE_NONE(load(
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

    REQUIRE_NONE(load(
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

    REQUIRE_NONE(load(
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

    REQUIRE_NONE(load(
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

    REQUIRE_NONE(load(
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

    REQUIRE_SOME(data);
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

    REQUIRE_SOME(data);
    REQUIRE_SOME(data->node_id());

    REQUIRE(data->advance(0));

    REQUIRE_SOME(data->node_id());

    REQUIRE(data->advance(0));

    REQUIRE_NONE(data->node_id());
}

TEST_CASE("Selecting a dialog choice should move to its node", "[Dialog]")
{
    lua::LuaEnv lua;

    auto data = load(
        R"(
dialog {
    nodes {
        _start {
            text = "foo"
            choices = [{
                text = "choice_a"
                node = "core.dialog:test.a"
            },
            {
                text = "choice_b"
                node = "core.dialog:test.b"
            }]
        }
        a {
            text = "bar"
            choices = End
        }
        b {
            text = "baz"
            choices = End
        }
    }
}
)",
        lua);

    REQUIRE_SOME(data);
    REQUIRE_SOME(data->node_id());
    REQUIRE(*data->node_id() == "core.dialog:test._start");

    REQUIRE(data->advance(1));

    REQUIRE_SOME(data->node_id());
    REQUIRE(*data->node_id() == "core.dialog:test.b");
    REQUIRE(data->text_key() == "baz");
}

TEST_CASE(
    "Choosing a node with a string as choices field should move to that node",
    "[Dialog]")
{
    lua::LuaEnv lua;

    auto data = load(
        R"(
dialog {
    nodes {
        _start {
            text = "foo"
            choices = "core.dialog:test.a"
        }
        a {
            text = "bar"
            choices = End
        }
    }
}
)",
        lua);

    REQUIRE_SOME(data);
    REQUIRE_SOME(data->node_id());

    REQUIRE(data->advance(0));

    REQUIRE_SOME(data->node_id());
    REQUIRE(*data->node_id() == "core.dialog:test.a");
    REQUIRE(data->text_key() == "bar");
}


TEST_CASE("Generating a nil result should fail", "[Dialog Behavior: Generator]")
{
    lua::LuaEnv lua;
    testing::register_lua_function(lua, "test", "my_callback()", "return nil");

    auto data = load(
        R"(
dialog {
    nodes {
        _start {
            generator = "exports:test.my_callback"
        }
    }
}
)",
        lua);

    REQUIRE_SOME(data);

    REQUIRE_FALSE(data->state_is_valid());
}

TEST_CASE(
    "Generating an invalid table should fail",
    "[Dialog Behavior: Generator]")
{
    lua::LuaEnv lua;
    testing::register_lua_function(lua, "test", "my_callback()", R"(
return {
    text = "bar"
}
)");

    auto data = load(
        R"(
dialog {
    nodes {
        _start {
            generator = "exports:test.my_callback"
        }
    }
}
)",
        lua);

    REQUIRE_SOME(data);

    REQUIRE_FALSE(data->state_is_valid());
}

TEST_CASE(
    "Generation of node should be reflected in node data",
    "[Dialog Behavior: Generator]")
{
    lua::LuaEnv lua;
    testing::register_lua_function(lua, "test", "my_callback()", R"(
return {
    text = "bar",
    choices = {
        {text = "choice_a", node = "core.dialog:test.a"},
        {text = "choice_b", node = "core.dialog:test.b"}
    }
}
)");

    auto data = load(
        R"(
dialog {
    nodes {
        _start {
            generator = "exports:test.my_callback"
        }
        a {
            text = "baz"
            choices = "core.dialog:test._start"
        }
        b {
            text = "quux"
            choices = End
        }
    }
}
)",
        lua);

    REQUIRE_SOME(data);
    REQUIRE_SOME(data->node_id());

    REQUIRE(data->state_is_valid());

    REQUIRE(data->advance(0));
    REQUIRE(*data->node_id() == "core.dialog:test.a");
    REQUIRE(data->text_key() == "baz");

    // Loop back to start and generate again
    REQUIRE(data->advance(0));

    REQUIRE(data->advance(1));
    REQUIRE(*data->node_id() == "core.dialog:test.b");
    REQUIRE(data->text_key() == "quux");
}

TEST_CASE(
    "Redirecting to an invalid node ID should fail",
    "[Dialog Behavior: Redirector]")
{
    lua::LuaEnv lua;
    testing::register_lua_function(
        lua, "test", "my_callback()", R"(return 42)");

    auto data = load(
        R"(
dialog {
    nodes {
        _start {
            redirector = "exports:test.my_callback"
        }
    }
}
)",
        lua);

    REQUIRE_SOME(data);

    REQUIRE_FALSE(data->state_is_valid());
}

TEST_CASE(
    "Redirecting to a nonexistent node ID should fail",
    "[Dialog Behavior: Redirector]")
{
    lua::LuaEnv lua;
    testing::register_lua_function(
        lua, "test", "my_callback()", R"(return "core.dialog:test.foo")");

    auto data = load(
        R"(
dialog {
    nodes {
        _start {
            redirector = "exports:test.my_callback"
        }
    }
}
)",
        lua);

    REQUIRE_SOME(data);

    REQUIRE_FALSE(data->state_is_valid());
}

TEST_CASE(
    "Redirector behavior should move to computed dialog node ID",
    "[Dialog Behavior: Redirector]")
{
    lua::LuaEnv lua;
    testing::register_lua_function(
        lua, "test", "my_callback()", R"(return "core.dialog:test.a")");

    auto data = load(
        R"(
dialog {
    nodes {
        _start {
            redirector = "exports:test.my_callback"
        }
        a {
            text = "foo"
            choices = End
        }
    }
}
)",
        lua);

    REQUIRE_SOME(data);

    REQUIRE(data->state_is_valid());
    REQUIRE(*data->node_id() == "core.dialog:test.a");
    REQUIRE(data->text_key() == "foo");
}

TEST_CASE(
    "Inheriting choices from invalid node specifier should fail",
    "[Dialog Behavior: Redirector]")
{
    lua::LuaEnv lua;

    auto data = load(
        R"(
dialog {
    nodes {
        _start {
            inherit_choices = 42
        }
    }
}
)",
        lua);

    REQUIRE_SOME(data);

    REQUIRE_FALSE(data->state_is_valid());
}

TEST_CASE(
    "Inheriting choices from nonexistent node ID should fail",
    "[Dialog Behavior: Redirector]")
{
    lua::LuaEnv lua;

    auto data = load(
        R"(
dialog {
    nodes {
        _start {
            inherit_choices = "core.dialog:test.foo"
        }
    }
}
)",
        lua);

    REQUIRE_SOME(data);

    REQUIRE_FALSE(data->state_is_valid());
}

TEST_CASE(
    "Inheriting choices from redirector should fail",
    "[Dialog Behavior: Redirector]")
{
    lua::LuaEnv lua;
    testing::register_lua_function(
        lua, "test", "my_callback()", R"(return "core.dialog:test.b")");

    auto data = load(
        R"(
dialog {
    nodes {
        _start {
            inherit_choices = "core.dialog:test.a"
        }
        a {
            redirector = "exports:test.my_callback"
        }
        b {
            text = "foo"
            choices = End
        }
    }
}
)",
        lua);

    REQUIRE_SOME(data);

    REQUIRE_FALSE(data->state_is_valid());
}

TEST_CASE(
    "Inheriting choices from other inherit choices node should fail",
    "[Dialog Behavior: Redirector]")
{
    lua::LuaEnv lua;

    auto data = load(
        R"(
dialog {
    nodes {
        _start {
            inherit_choices = "core.dialog:test.a"
        }
        a {
            inherit_choices = "core.dialog:test.b"
        }
        b {
            text = "foo"
            choices = End
        }
    }
}
)",
        lua);

    REQUIRE_SOME(data);

    REQUIRE_FALSE(data->state_is_valid());
}

TEST_CASE(
    "Inheriting choices from static node should be reflected",
    "[Dialog Behavior: Redirector]")
{
    lua::LuaEnv lua;

    auto data = load(
        R"(
dialog {
    nodes {
        _start {
            text = "foo"
            inherit_choices = "core.dialog:test.a"
        }
        a {
            text = "bar"
            choices = [{
                text = "choice_a"
                node = "core.dialog:test.a"
            },
            {
                text = "choice_b"
                node = End
            }]
        }
    }
}
)",
        lua);

    REQUIRE_SOME(data);

    REQUIRE(data->state_is_valid());
    REQUIRE_SOME(data->node_id());
    REQUIRE(*data->node_id() == "core.dialog:test._start");
    REQUIRE_SOME(data->choices());

    const auto& choices = *data->choices();
    REQUIRE(choices.size() == 2);

    REQUIRE(choices.at(0).locale_key == "choice_a");
    REQUIRE_SOME(choices.at(0).node_id);
    REQUIRE(*choices.at(0).node_id == "core.dialog:test.a");

    REQUIRE(choices.at(1).locale_key == "choice_b");
    REQUIRE_NONE(choices.at(1).node_id);

    REQUIRE(data->advance(0));
    REQUIRE(*data->node_id() == "core.dialog:test.a");
}

TEST_CASE(
    "Inheriting choices from generator node should be reflected",
    "[Dialog Behavior: Redirector]")
{
    lua::LuaEnv lua;
    testing::register_lua_function(lua, "test", "my_callback()", R"(
return {
    text = "bar",
    choices = {
        {text = "choice_a", node = "core.dialog:test.a"},
        {text = "choice_b", node = "End"}
    }
}
)");

    auto data = load(
        R"(
dialog {
    nodes {
        _start {
            text = "foo"
            inherit_choices = "core.dialog:test.a"
        }
        a {
            generator = "exports:test.my_callback"
        }
    }
}
)",
        lua);

    REQUIRE_SOME(data);

    REQUIRE(data->state_is_valid());
    REQUIRE_SOME(data->node_id());
    REQUIRE(*data->node_id() == "core.dialog:test._start");
    REQUIRE_SOME(data->choices());

    const auto& choices = *data->choices();
    REQUIRE(choices.size() == 2);

    REQUIRE(choices.at(0).locale_key == "choice_a");
    REQUIRE_SOME(choices.at(0).node_id);
    REQUIRE(*choices.at(0).node_id == "core.dialog:test.a");

    REQUIRE(choices.at(1).locale_key == "choice_b");
    REQUIRE_NONE(choices.at(1).node_id);

    REQUIRE(data->advance(0));
    REQUIRE(*data->node_id() == "core.dialog:test.a");
}
