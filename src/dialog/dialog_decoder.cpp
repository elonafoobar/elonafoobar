#include "dialog_decoder.hpp"
#include "../lua_env/lua_registry.hpp"
#include "dialog.hpp"

namespace elona
{

dialog dialog_decoder::decode(const std::string& id)
{
    return decode(id, *lua::lua.get());
}

dialog dialog_decoder::decode(const std::string& id, lua::lua_env& lua)
{
    sol::table dialog_table =
        lua.get_registry_manager().get_table("core", "dialog");

    sol::table dialog_data = dialog_table["core"][id];

    return decode(dialog_data, lua);
}

dialog dialog_decoder::decode(sol::table table, lua::lua_env& lua)
{
    dialog the_dialog;
    std::string full_id = table["_full_id"];
    optional<dialog_node_behavior> behavior = dialog_node_behavior{};

    for (const auto& pair : table)
    {
        dialog_node the_dialog_node;

        std::string node_name = pair.first;
        sol::table node_data = pair.second;

        std::string node_id = full_id + "." + node_name;
        the_dialog_node.id = node_id;

        sol::object node_text = node_data["text"];
        if (node_text != sol::lua_nil)
        {
            if (node_text.is<std::string>())
            {
                the_dialog_node.text.emplace_back(node_text.as<std::string>());
            }
            else if (node_text.is<sol::table>())
            {
                for (const auto& pair : node_text.as<sol::table>())
                {
                    std::string text = pair.second;
                    the_dialog_node.text.emplace_back(text);
                }
            }
        }

        if (node_data["generator"] != sol::lua_nil)
        {
            std::string callback_generator = node_choices["generator"];
            if (!lua.get_registry_manager().has_function(callback_generator))
            {
                throw std::runtime_error(
                    full_id + ": Node \"" + node_name
                    + "\" has unknown Lua callback " + callback_generator);
            }
            behavior = dialog_node_behavior_generator{callback_generator};
        }
        else if (node_data["redirector"] != sol::lua_nil)
        {
            // TODO dry
            std::string callback_redirector = node_choices["redirector"];
            if (!lua.get_registry_manager().has_function(callback_redirector))
            {
                throw std::runtime_error(
                    full_id + ": Node \"" + node_name
                    + "\" has unknown Lua callback " + callback_redirector);
            }
            behavior = dialog_node_behavior_redirector{callback_redirector};
        }

        if (node_data["run_before"] != sol::lua_nil)
        {
            // TODO dry
            std::string callback_before = node_choices["run_before"];
            if (!lua.get_registry_manager().has_function(callback_before))
            {
                throw std::runtime_error(
                    full_id + ": Node \"" + node_name
                    + "\" has unknown Lua callback " + callback_before);
            }
            the_dialog.callback_before = callback_before;
        }

        if (node_data["run_after"] != sol::lua_nil)
        {
            // TODO dry
            std::string callback_after = node_choices["run_after"];
            if (!lua.get_registry_manager().has_function(callback_after))
            {
                throw std::runtime_error(
                    full_id + ": Node \"" + node_name
                    + "\" has unknown Lua callback " + callback_after);
            }
            the_dialog.callback_after = callback_after;
        }

        sol::object node_choices = node_data["choices"];
        if (node_choices != sol::lua_nil)
        {
            if (node_choices.is<std::string>())
            {
                if (node_choices.as<std::string>() == "End")
                {
                    the_dialog_node.choices.emplace_back("bye", none);
                }
            }
            else if (node_choices.is<sol::table>())
            {
                if (node_choices["inherit"] != sol::lua_nil)
                {
                    // TODO dry
                    std::string node_id_for_choices = node_choices["inherit"];
                    behavior = dialog_node_behavior_inherit_choices{
                        node_id_for_choices};
                }
                else
                {
                    for (const auto& pair : node_choices)
                    {
                        std::string text_key = pair.second["text"];
                        std::string next_node_id = pair.second;

                        if (next_node_id != "End")
                        {
                            the_dialog_node.choices.emplace_back(
                                text_key, next_node_id);
                        }
                        else
                        {
                            the_dialog_node.choices.emplace_back(
                                text_key, none);
                        }
                    }
                }
            }
        }

        the_dialog.nodes.insert(the_dialog_node.id, the_dialog_node);
    }
}

} // namespace elona
