#include "dialog_decoder.hpp"
#include "../lua_env/config_table.hpp"
#include "../lua_env/lua_env.hpp"
#include "../message.hpp"
#include "dialog.hpp"
#include "dialog_data.hpp"

namespace elona
{

optional<DialogData> DialogDecoder::decode(const std::string& id)
{
    return decode(id, *lua::lua.get());
}

/**
 * Parse an id of the format "core.dialog:test.some_dialog".
 *
 * @param datatype_mod_name Expected originating mod ("core")
 * @param datatype_name Expected data kind ("dialog")
 * @param id "core.dialog:test.some_dialog"
 *
 * @throws if the ID is not of the form "1.2:3.4"
 * @return ("test", "some_dialog")
 */
static std::pair<std::string, std::string> parse_id(
    const std::string& datatype_mod_name,
    const std::string& datatype_name,
    const std::string& id)
{
    std::string datatype_fqn, datatype_id;
    std::tie(datatype_fqn, datatype_id) = strutil::split_on_string(id, ":");

    std::string mod_name, data_name;
    std::tie(mod_name, data_name) = strutil::split_on_string(datatype_fqn, ".");

    if (datatype_mod_name != mod_name || datatype_name != data_name)
    {
        throw std::runtime_error(
            "Expected id of format \"" + datatype_mod_name + "." + datatype_name
            + "\", got \"" + mod_name + "." + data_name + "\"");
    }

    return strutil::split_on_string(datatype_id, ".");
}

optional<DialogData> DialogDecoder::decode(
    const std::string& id,
    lua::LuaEnv& lua)
{
    try
    {
        std::string mod_name, data_id;
        std::tie(mod_name, data_id) = parse_id("core", "dialog", id);

        sol::table dialog_table = *lua.get_data_manager().get().raw(
            "core.dialog", mod_name + "." + data_id);

        lua::ConfigTable dialog_table_data(dialog_table);

        return DialogDecoderLogic(lua.get_export_manager())
            .decode(dialog_table_data);
    }
    catch (const std::exception& e)
    {
        txtef(ColorIndex::red);
        txt(id + ": Dialog decoding error: " + e.what());
        return none;
    }
}

void DialogDecoderLogic::parse_text(
    lua::ConfigTable& node_data,
    const std::string& full_id,
    DialogNode& the_dialog_node)
{
    if (auto node_text_opt = node_data.optional<sol::object>("text"))
    {
        sol::object node_text = *node_text_opt;
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
        else
        {
            throw std::runtime_error(
                full_id + ": \"text\" must be either a table or string.");
        }
    }
}

void DialogDecoderLogic::parse_choice_string(
    const std::string& choice,
    DialogNode& the_dialog_node)
{
    if (choice == "End")
    {
        the_dialog_node.choices.emplace_back("core.locale.ui.bye"s, none);
    }
    else
    {
        // value acts as next node label to move to
        the_dialog_node.choices.emplace_back("core.locale.ui.more"s, choice);
    }
}

void DialogDecoderLogic::parse_choice_table(
    sol::table& node_choices_table,
    const std::string& full_id,
    DialogNode& the_dialog_node)
{
    for (const auto& pair : node_choices_table)
    {
        lua::ConfigTable choice_data(pair.second.as<sol::table>(), full_id);

        auto text_key = choice_data.required<std::string>("text");
        auto next_node = choice_data.required<std::string>("node");

        if (next_node == "End")
        {
            the_dialog_node.choices.emplace_back(text_key, none);
        }
        else
        {
            the_dialog_node.choices.emplace_back(text_key, next_node);
        }
    }
}

void DialogDecoderLogic::parse_choices(
    lua::ConfigTable& node_data,
    const std::string& full_id,
    DialogNode& the_dialog_node)
{
    if (auto node_choices_opt = node_data.optional<sol::object>("choices"))
    {
        sol::object node_choices = *node_choices_opt;

        if (node_choices.is<std::string>())
        {
            parse_choice_string(
                node_choices.as<std::string>(), the_dialog_node);
        }
        else if (node_choices.is<sol::table>())
        {
            sol::table node_choices_table = node_choices.as<sol::table>();
            parse_choice_table(node_choices_table, full_id, the_dialog_node);
        }
        else
        {
            throw std::runtime_error(
                full_id + ": \"choices\" must be either a table or string.");
        }
    }
}

// Shared between decoder and node generator logic
void DialogDecoderLogic::parse_text_choices(
    lua::ConfigTable& node_data,
    const std::string& full_id,
    DialogNode& the_dialog_node)
{
    parse_text(node_data, full_id, the_dialog_node);
    parse_choices(node_data, full_id, the_dialog_node);
}

void DialogDecoderLogic::parse_node_behavior(
    lua::ConfigTable& node_data,
    const std::string& full_id,
    DialogNode& the_dialog_node)
{
    the_dialog_node.behavior = std::make_shared<DialogNodeBehavior>();

    int behaviors = 0;
    if (auto cb = node_data.optional<std::string>("generator"))
    {
        the_dialog_node.behavior =
            std::make_shared<DialogNodeBehaviorGenerator>(*cb);
        behaviors++;
    }
    if (auto cb = node_data.optional<std::string>("redirector"))
    {
        the_dialog_node.behavior =
            std::make_shared<DialogNodeBehaviorRedirector>(*cb);
        behaviors++;
    }
    if (auto node_id = node_data.optional<std::string>("inherit_choices"))
    {
        the_dialog_node.behavior =
            std::make_shared<DialogNodeBehaviorInheritChoices>(*node_id);
        behaviors++;
    }

    if (behaviors > 1)
    {
        throw std::runtime_error(
            full_id + ": Only one of \"generator\", \"redirector\", or \"inherit_choices\" can be used at a time");
    }
}

void DialogDecoderLogic::parse_run_before_after(
    lua::ConfigTable& node_data,
    DialogNode& the_dialog_node)
{
    if (auto cb = node_data.optional<std::string>("run_before"))
    {
        the_dialog_node.callback_before = *cb;
    }

    if (auto cb = node_data.optional<std::string>("run_after"))
    {
        the_dialog_node.callback_after = *cb;
    }
}

DialogNode DialogDecoderLogic::parse_node(
    lua::ConfigTable node_data,
    const std::string& node_id)
{
    DialogNode the_dialog_node;

    parse_text_choices(node_data, node_id, the_dialog_node);
    parse_node_behavior(node_data, node_id, the_dialog_node);
    parse_run_before_after(node_data, the_dialog_node);

    return the_dialog_node;
}

DialogData DialogDecoderLogic::decode(lua::ConfigTable& table)
{
    DialogData::map_type nodes;
    std::string full_id = table.required<std::string>("_full_id");

    sol::object nodes_table = table.required<sol::object>("nodes");
    if (nodes_table == sol::lua_nil)
    {
        throw std::runtime_error(full_id + ": missing \"nodes\" field");
    }

    for (const auto& pair : nodes_table.as<sol::table>())
    {
        std::string node_name = pair.first.as<std::string>();
        std::string node_id = full_id + "." + node_name;
        lua::ConfigTable node_data(pair.second.as<sol::table>(), node_id);

        DialogNode the_dialog_node = parse_node(node_data, node_id);
        the_dialog_node.id = node_id;

        nodes.insert(std::make_pair(node_id, std::move(the_dialog_node)));
    }

    std::string starting_node = full_id + "._start";
    if (nodes.find(starting_node) == nodes.end())
    {
        throw std::runtime_error(
            full_id + ": Cannot find starting dialog node " + starting_node);
    }

    DialogData the_dialog(nodes, starting_node, export_manager);
    return the_dialog;
}

} // namespace elona
