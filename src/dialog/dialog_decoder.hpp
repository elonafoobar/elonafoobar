#pragma once
#include <string>
#include "../optional.hpp"
#include "../thirdparty/sol2/sol.hpp"

namespace elona
{

namespace lua
{
class ExportManager;
class LuaEnv;
class ConfigTable;
} // namespace lua

class DialogData;
class DialogNode;

class DialogDecoder
{
public:
    optional<DialogData> decode(const std::string& id);
    optional<DialogData> decode(const std::string& id, lua::LuaEnv& lua);
};

class DialogDecoderLogic
{
public:
    DialogDecoderLogic(lua::ExportManager& export_manager)
        : export_manager(export_manager)
    {
    }

public:
    DialogData decode(lua::ConfigTable& data);

    /**
     * Parses a Lua table containing the text and choices of a dialog node.
     *
     * It expects a Lua table of this format.
     * {
     *   text = "mod.locale.1"
     *   -- or alternatively
     *   text = {"mod.locale.1", "mod.locale.2", "mod.locale.3"},
     *
     *   choices = {
     *     {text = "mod.locale.4", node = "core.dialog:dialog.node1},
     *     {text = "mod.locale.5", node = "core.dialog:dialog.node2},
     *   }
     *   -- or alternatively
     *   choices = "core.dialog:dialog.node3"
     * }
     *
     * Choices and text can be left out at the decoding stage. The reason is to
     * allow programmatic methods of changing text/choices, without the
     * requirement to specify text/choices that will be overwritten anyway.
     * However, if no text or choices are available at the point of displaying
     * the dialog, a user error will occur.
     *
     * @param node_data Lua table containing data
     * @param full_id Full ID of node being parsed (for debugging)
     * @param the_dialog_node Dialog node to add data to (will be modified)
     */
    void parse_text_choices(
        lua::ConfigTable& node_data,
        const std::string& full_id,
        DialogNode& the_dialog_node);

private:
    lua::ExportManager& export_manager;

    void parse_text(
        lua::ConfigTable& node_data,
        const std::string& full_id,
        DialogNode& the_dialog_node);


    void parse_choice_string(
        const std::string& choice,
        DialogNode& the_dialog_node);
    void parse_choice_table(
        sol::table& node_choices_table,
        const std::string& full_id,
        DialogNode& the_dialog_node);
    void parse_choices(
        lua::ConfigTable& node_data,
        const std::string& full_id,
        DialogNode& the_dialog_node);

    void parse_node_behavior(
        lua::ConfigTable& node_data,
        const std::string& full_id,
        DialogNode& the_dialog_node);

    void parse_run_before_after(
        lua::ConfigTable& node_data,
        DialogNode& the_dialog_node);

    DialogNode parse_node(
        lua::ConfigTable node_data,
        const std::string& node_id);
};

} // namespace elona
