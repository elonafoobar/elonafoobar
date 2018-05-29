#include "lua_store.hpp"

#include "../thirdparty/sol2/sol.hpp"
#include "../character.hpp"
#include "../item.hpp"
#include "../optional.hpp"
#include "../position.hpp"
#include <vector>
#include <unordered_map>
#include <boost/variant.hpp>
#include <cassert>

namespace elona
{
namespace lua
{

void store::init(sol::state& state)
{
    if(state["Store"].valid()) // already exists
        return;

    bind(state);
    state["Store"] = this;
}

void store::init(sol::state& state, sol::environment& env)
{
    bind(state);
    // Set the pointer to this store outside of here.
}

void store::bind(sol::state& state)
{
    //sol::table metatable = state.create_table_with();

    state.new_usertype<lua::store>("LuaStore",
                                   sol::meta_function::new_index , [](lua::store& s, std::string key, const sol::object val, sol::this_state tstate){
        s.set(key, val);
                                   },
                                   sol::meta_function::index , [](lua::store& s, std::string key, sol::this_state tstate) {
        sol::state_view view(tstate);
        return s.get(key, view);
    });
}

void store::set(std::string key, const sol::object &val)
{
    store::object obj;
    auto type = val.get_type();
    switch(type)
    {
    case sol::type::none:break;
    case sol::type::lua_nil:break;
    case sol::type::string:
        obj = val.as<std::string>();
        break;
    case sol::type::number:
        obj = val.as<int>();
        break;
    case sol::type::thread:break;
    case sol::type::boolean:
        obj = val.as<bool>();
        break;
    case sol::type::function:break;
    case sol::type::userdata:
        obj = serialize_userdata(val);
        break;
    case sol::type::lightuserdata:break;
    case sol::type::poly:break;
    case sol::type::table:
        obj = val.as<sol::table>();
        break;
    }
    store_inner[key.data()] = {type, obj};
}

store::object store::serialize_userdata(const sol::object &val)
{
    store::object obj = sol::nil;

    // Characters and items will be stored in handle tables already.
    // There is no need to serialize them.
    if(val.is<position_t&>())
    {
        position_t pos = val.as<position_t>();
        obj = pos;
    }
    else
    {
        assert(0);
    }
    return obj;
}

void store::convert_table_value(sol::object& value, sol::state_view& view)
{
    sol::type valuetype = value.get_type();
    switch (valuetype) {
    case sol::type::number:
    case sol::type::string:
    case sol::type::boolean:
    case sol::type::lua_nil:
        break;
    case sol::type::userdata:
    {
        store::object obj = serialize_userdata(value);
        if(obj.type() == typeid(position_t))
        {
            // do nothing
        }
        else
        {
            assert(0);
        }
    }
    break;
    case sol::type::table:
    {
        sol::table t = value;
        value = serialize_table(view, t);
    }
    break;
    default:
        // The user tried storing an unsupported value.
        assert(0);
        break;
    }
}

sol::table store::serialize_table(sol::state_view& view, sol::table& table)
{
    auto fx = [&](sol::object key, sol::object value) {
        convert_table_value(key, view);
        convert_table_value(value, view);
    };
    table.for_each(fx);
    return table;
}

sol::object store::get(std::string key, sol::state_view& view)
{
    auto val = store_inner.find(key.data());
    if (val == store_inner.end())
        return sol::lua_nil;

    const auto& pair = val->second;
    const auto& type = pair.first;
    const auto& obj = pair.second;

    switch(type)
    {
    case sol::type::none:break;
    case sol::type::lua_nil:break;
    case sol::type::string:
        assert(obj.type() == typeid(std::string));
        return sol::object(view, sol::in_place, boost::get<std::string>(obj));
    case sol::type::number:
        assert(obj.type() == typeid(int));
        return sol::make_object(view, boost::get<int>(obj));
    case sol::type::thread:break;
    case sol::type::boolean:
        assert(obj.type() == typeid(bool));
        return sol::make_object(view, boost::get<bool>(obj));
    case sol::type::function:break;
    case sol::type::userdata:
        return deserialize_userdata(obj, view);
    case sol::type::lightuserdata:break;
    case sol::type::poly:break;
    case sol::type::table:
        assert(obj.type() == typeid(sol::table));
        return boost::get<sol::table>(obj);
    }
    return sol::lua_nil;
}

sol::object store::deserialize_position(const position_t pos, sol::state_view& view)
{
    return sol::make_object(view, pos);
}

sol::object store::deserialize_userdata(const store::object& obj, sol::state_view& view)
{
    // Characters and items will be stored in handle tables already.
    // There is no need to deserialize them.
    if (obj.type() == typeid(position_t))
    {
        return deserialize_position(boost::get<position_t>(obj), view);
    }
    else {
        assert(0);
        return sol::lua_nil;
    }
}

} // namespace lua
} // namespace elona
