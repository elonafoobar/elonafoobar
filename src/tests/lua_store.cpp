#include "../thirdparty/catch2/catch.hpp"
#include "../thirdparty/sol2/sol.hpp"

#include "tests.hpp"
#include "../character.hpp"
#include "../item.hpp"
#include "../itemgen.hpp"
#include "../lua_env/lua_store.hpp"
#include "../testing.hpp"
#include "../variables.hpp"

using namespace std::literals::string_literals;

TEST_CASE("Test that strings can be set/retrieved", "[Lua: Store]")
{
    sol::state sol;
    sol.open_libraries(sol::lib::base);
    elona::lua::store store;
    store.init(sol);

    auto view = sol::state_view(sol);
    auto obj = sol::make_object(sol, "dood");
    store.set("my_string"s, obj);

    std::string my_string = sol["Store"]["my_string"];
    REQUIRE(my_string == std::string("dood"));
    REQUIRE_NOTHROW(sol.safe_script(R"(assert(Store["my_string"] == "dood"))"));

    REQUIRE_NOTHROW(sol.safe_script(R"(Store["my_string"] = "putit")"));
    my_string = sol["Store"]["my_string"];
    REQUIRE(my_string == std::string("putit"));
    my_string = store.get("my_string", view).as<std::string>();
    REQUIRE(my_string == std::string("putit"));
}

TEST_CASE("Test that booleans can be set/retrieved", "[Lua: Store]")
{
    sol::state sol;
    sol.open_libraries(sol::lib::base);
    elona::lua::store store;
    store.init(sol);

    auto view = sol::state_view(sol);
    auto obj = sol::make_object(sol, false);
    store.set("my_bool"s, obj);

    bool my_bool = sol["Store"]["my_bool"];
    REQUIRE(my_bool == false);
    REQUIRE_NOTHROW(sol.safe_script(R"(assert(Store["my_bool"] == false))"));

    REQUIRE_NOTHROW(sol.safe_script(R"(Store["my_bool"] = true)"));
    my_bool = sol["Store"]["my_bool"];
    REQUIRE(my_bool == true);
    my_bool = store.get("my_bool", view).as<bool>();
    REQUIRE(my_bool == true);
}


TEST_CASE("Test that integers can be set/retrieved", "[Lua: Store]")
{
    sol::state sol;
    sol.open_libraries(sol::lib::base);
    elona::lua::store store;
    store.init(sol);

    auto view = sol::state_view(sol);
    auto obj = sol::make_object(sol, 42);
    store.set("my_int"s, obj);

    int my_int = sol["Store"]["my_int"];
    REQUIRE(my_int == 42);
    REQUIRE_NOTHROW(sol.safe_script(R"(assert(Store["my_int"] == 42))"));

    REQUIRE_NOTHROW(sol.safe_script(R"(Store["my_int"] = 84)"));
    my_int = sol["Store"]["my_int"];
    REQUIRE(my_int == 84);
    my_int = store.get("my_int", view).as<int>();
    REQUIRE(my_int == 84);
}

TEST_CASE("Test that tables can be set", "[Lua: Store]")
{
    sol::state sol;
    sol.open_libraries(sol::lib::base);
    elona::lua::store store;
    store.init(sol);

    REQUIRE_NOTHROW(sol.safe_script(R"(Store["my_table"] = { [0]=42, [1]="Scut!", [2]=false, [3]=nil, bell=" *リン* " })"));

    sol::table my_table = sol["Store"]["my_table"];

    std::size_t tablesize = 4;
    std::size_t iterations = 0;
    auto fx = [&iterations](sol::object key, sol::object value) {
        ++iterations;
        sol::type keytype = key.get_type();
        switch (keytype) {
        case sol::type::number:
            switch (key.as<int>()) {
            case 0:
                REQUIRE((value.as<int>() == 42));
                break;
            case 1:
                REQUIRE((value.as<std::string>() == "Scut!"));
                break;
            case 2:
                REQUIRE((value.as<bool>() == false));
                break;
            case 3:
                REQUIRE((value.is<sol::lua_nil_t>()));
                break;
            }
            break;
        case sol::type::string:
            if (key.as<std::string>() == "bell") {
                REQUIRE((value.as<std::string>() == " *リン* "));
            }
            break;
        default:
            break;
        }
    };
    my_table.for_each(fx);
    REQUIRE(iterations == tablesize);

    auto fxpair = [&fx](std::pair<sol::object, sol::object> kvp) { fx(kvp.first, kvp.second); };
    iterations = 0;
    my_table.for_each(fxpair);
    REQUIRE(iterations == tablesize);
}

TEST_CASE("Test that tables can be retrieved", "[Lua: Store]")
{
    sol::state sol;
    sol.open_libraries(sol::lib::base);
    elona::lua::store store;
    store.init(sol);

    sol::table my_table = sol.create_table_with(0, 42,
                                                1, "Scut!",
                                                2, false,
                                                3, sol::lua_nil, // does nothing
                                                "bell"," *リン* ");
    auto view = sol::state_view(sol);
    auto obj = sol::object(my_table);
    store.set("my_table"s, obj);

    my_table = sol["Store"]["my_table"];

    std::size_t tablesize = 4;
    std::size_t iterations = 0;
    auto fx = [&iterations](sol::object key, sol::object value) {
        ++iterations;
        sol::type keytype = key.get_type();
        switch (keytype) {
        case sol::type::number:
            switch (key.as<int>()) {
            case 0:
                REQUIRE((value.as<int>() == 42));
                break;
            case 1:
                REQUIRE((value.as<std::string>() == "Scut!"));
                break;
            case 2:
                REQUIRE((value.as<bool>() == false));
                break;
            case 3:
                REQUIRE((value.is<sol::lua_nil_t>()));
                break;
            }
            break;
        case sol::type::string:
            if (key.as<std::string>() == "bell") {
                REQUIRE((value.as<std::string>() == " *リン* "));
            }
            break;
        default:
            break;
        }
    };
    my_table.for_each(fx);
    REQUIRE(iterations == tablesize);

    auto fxpair = [&fx](std::pair<sol::object, sol::object> kvp) { fx(kvp.first, kvp.second); };
    iterations = 0;
    my_table.for_each(fxpair);
    REQUIRE(iterations == tablesize);
}

TEST_CASE("Test that positions can be set", "[Lua: Store]")
{
    sol::state sol;
    sol.open_libraries(sol::lib::base);
    elona::lua::store store;
    store.init(sol);

    sol.new_usertype<position_t>( "LuaPosition",
                                  "x", &position_t::x,
                                  "y", &position_t::y
        );

    position_t my_position = { 24, 47 };

    auto view = sol::state_view(sol);
    auto obj = sol::make_object(sol, my_position);
    store.set("my_position"s, obj);

    my_position = sol["Store"]["my_position"];
    REQUIRE(my_position.x == 24);
    REQUIRE(my_position.y == 47);
    REQUIRE_NOTHROW(sol.safe_script(R"(assert(Store["my_position"].x == 24))"));
    REQUIRE_NOTHROW(sol.safe_script(R"(assert(Store["my_position"].y == 47))"));
}

TEST_CASE("Test isolation between environments", "[Lua: Store]")
{
    sol::state sol;
    sol.open_libraries(sol::lib::base);

    sol::environment first_env(sol, sol::create, sol.globals());
    sol::environment second_env(sol, sol::create, sol.globals());
    elona::lua::store first_store;
    elona::lua::store second_store;
    first_store.init_no_attach(sol);
    second_store.init_no_attach(sol);
    first_env["Store"] = first_store;
    second_env["Store"] = second_store;

    REQUIRE_NOTHROW(sol.safe_script(R"(Store["message"] = "dood")", first_env));
    REQUIRE_NOTHROW(sol.safe_script(R"(Store["message"] = "putit")", second_env));

    REQUIRE_NOTHROW(sol.safe_script(R"(assert(Store["message"] == "dood"))", first_env));
    REQUIRE_NOTHROW(sol.safe_script(R"(assert(Store["message"] == "putit"))", second_env));
}


TEST_CASE("Test multiple table assignment", "[Lua: Store]")
{
    sol::state sol;
    sol.open_libraries(sol::lib::base);
    elona::lua::store store;
    store.init(sol);

    REQUIRE_NOTHROW(sol.safe_script(R"(Store.thing = { [0]=0,[1]=1,[2]=2,[3]={1,2,3} })"));

    sol::table my_table = sol["Store"]["thing"];
    int a = my_table[0];
    int b = my_table[1];
    int c = my_table[2];
    REQUIRE(a == 0);
    REQUIRE(b == 1);
    REQUIRE(c == 2);

    REQUIRE_NOTHROW(sol.safe_script(R"(Store.thing = { [0]=2,[1]=1,[2]=0,[3]={3,2,1} })"));

    my_table = sol["Store"]["thing"];
    a = my_table[0];
    b = my_table[1];
    c = my_table[2];
    REQUIRE(a == 2);
    REQUIRE(b == 1);
    REQUIRE(c == 0);
}
