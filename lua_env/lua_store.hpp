#pragma once

#include "../thirdparty/sol2/sol.hpp"
#include "../character.hpp"
#include "../position.hpp"
#include <vector>
#include <unordered_map>
#include <boost/variant.hpp>
#include <boost/serialization/strong_typedef.hpp>

namespace elona
{
namespace lua
{

/***
 * A data storage mechanism for preserving data in mods and allowing
 * for the serialization and deserialization of mod data. It marshals
 * supported Lua types to their equivalent C++ types and vice versa.
 * Any unsupported Lua type is stored as a Lua table reference
 * instead.
 *
 * Mods will each be provided with a shared opinter to their
 * individual store instance in their sandboxed environment and can
 * write to it like any Lua table, with these exceptions:
 *
 * - Table keys have to be strings.
 * - The store can't be set by setting a new table on it as it
 *   overwrites the original reference. TODO: This needs to be
 *   prevented somehow by overriding the mod environment's metatable
 *   to have read-only globals.
 */
class store
{


public:
    void clear() { store_inner.clear(); }
    void set(std::string key, const sol::object&);
    sol::object get(std::string key, sol::state_view& view);

    /***
     * A variant representing all possible objects that can be kept in
     * a store.
     *
     * Characters and items are not included since they are wrapped
     * into handles, which are Lua tables.
     */
    typedef boost::variant<int,
                           bool,
                           std::string,
                           sol::table,
                           position_t> object;

    /***
     * Creates an API binding to the Store on the global Lua state.
     *
     * For testing use only.
     */
    void init(sol::state &state);

    /***
     * Creates an API binding to the Store usertype, for use in an
     * environment.
     *
     * This does not automatically provide a reference to the store.
     * It needs to be set after this function is called (see the
     * constructor of mod_info in lua_env).
     */
    void init_no_attach(sol::state &state);
private:

    /***
     * Binds the LuaStore usertype to the given Lua state.
     */
    static void bind(sol::state&);

    /***
     * Serializes a compatible userdata object (for now, only positions)
     */
    static object serialize_userdata(const sol::object&);

    static sol::table serialize_table(sol::state_view&, sol::table&);
    static void convert_table_value(sol::object&, sol::state_view&);

    /***
     * Deserializes a compatible userdata object (for now, only positions)
     */
    static sol::object deserialize_userdata(const store::object&, sol::state_view&);

    static sol::object deserialize_position(position_t, sol::state_view&);
private:
    std::unordered_map<std::string, std::pair<sol::type, object>> store_inner;
};


} // namespace lua
} // namespace elona
