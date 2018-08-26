#include "dialog_decoder.hpp"
#include "../lua_env/lua_env.hpp"
#include "dialog.hpp"

namespace elona
{

optional<dialog_data> dialog_decoder::decode(const std::string& id)
{
    return decode(id, *lua::lua.get());
}

optional<dialog_data> dialog_decoder::decode(
    const std::string& id,
    lua::lua_env& lua)
{
    try
    {
        sol::table dialog_table =
            *lua.get_registry_manager().get_table("core", "dialog");

        sol::table dialog_table_data = dialog_table["core"][id];

        return decode(dialog_table_data, lua);
    }
    catch (const std::exception& e)
    {
        txtef(color_index_t::red);
        txt(id + ": Dialog decoding error: " + e.what());
        return none;
    }
}

dialog_data dialog_decoder::decode(sol::table table, lua::lua_env& lua)
{
    dialog_data::map_type nodes;
    std::string full_id = table["_full_id"];
    optional<dialog_node_behavior> behavior = dialog_node_behavior{};

    for (const auto& pair : table)
    {
        dialog_node the_dialog_node;

        std::string node_name = pair.first.as<std::string>();
        sol::table node_data = pair.second.as<sol::table>();

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
                    std::string text = pair.second.as<std::string>();
                    the_dialog_node.text.emplace_back(text);
                }
            }
        }

        if (node_data["generator"] != sol::lua_nil)
        {
            std::string callback_generator = node_data["generator"];
            if (!lua.get_export_manager().has_function(callback_generator))
            {
                throw std::runtime_error(
                    full_id + ": Node \"" + node_name
                    + "\" has unknown Lua callback " + callback_generator);
            }
            behavior = dialog_node_behavior_generator(callback_generator);
        }
        else if (node_data["redirector"] != sol::lua_nil)
        {
            // TODO dry
            std::string callback_redirector = node_data["redirector"];
            if (!lua.get_export_manager().has_function(callback_redirector))
            {
                throw std::runtime_error(
                    full_id + ": Node \"" + node_name
                    + "\" has unknown Lua callback " + callback_redirector);
            }
            behavior = dialog_node_behavior_redirector(callback_redirector);
        }
        else if (node_data["inherit_choices"] != sol::lua_nil)
        {
            // TODO dry
            std::string node_id_for_choices = node_data["inherit"];
            behavior =
                dialog_node_behavior_inherit_choices(node_id_for_choices);
        }

        if (node_data["run_before"] != sol::lua_nil)
        {
            // TODO dry
            std::string callback_before = node_data["run_before"];
            if (!lua.get_export_manager().has_function(callback_before))
            {
                throw std::runtime_error(
                    full_id + ": Node \"" + node_name
                    + "\" has unknown Lua callback " + callback_before);
            }
            the_dialog_node.callback_before = callback_before;
        }

        if (node_data["run_after"] != sol::lua_nil)
        {
            // TODO dry
            std::string callback_after = node_data["run_after"];
            if (!lua.get_export_manager().has_function(callback_after))
            {
                throw std::runtime_error(
                    full_id + ": Node \"" + node_name
                    + "\" has unknown Lua callback " + callback_after);
            }
            the_dialog_node.callback_after = callback_after;
        }

        sol::object node_choices = node_data["choices"];
        if (node_choices != sol::lua_nil)
        {
            if (node_choices.is<std::string>())
            {
                if (node_choices.as<std::string>() == "End")
                {
                    // TODO: move "bye" text into locale
                    the_dialog_node.choices.emplace_back("bye"s, none);
                }
            }
            else if (node_choices.is<sol::table>())
            {
                sol::table node_choices_table = node_choices.as<sol::table>();
                for (const auto& pair : node_choices_table)
                {
                    sol::table choice_data = pair.second.as<sol::table>();
                    std::string text_key = choice_data["text"];
                    std::string node_id = choice_data["node_id"];

                    if (node_id != "End")
                    {
                        the_dialog_node.choices.emplace_back(text_key, node_id);
                    }
                    else
                    {
                        the_dialog_node.choices.emplace_back(text_key, none);
                    }
                }
            }
        }

        nodes.emplace(the_dialog_node.id, the_dialog_node);
    }

    std::string starting_node = full_id + "._start";
    if (nodes.find(starting_node) == nodes.end())
    {
        throw std::runtime_error(
            full_id + ": Cannot find starting dialog node " + starting_node);
    }

    dialog_data the_dialog(nodes, starting_node);
    return the_dialog;
}

} // namespace elona
