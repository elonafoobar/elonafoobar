#include "dialog_data.hpp"
#include "../lua_env/config_table.hpp"
#include "../lua_env/export_manager.hpp"
#include "../lua_env/handle_manager.hpp"
#include "../lua_env/lua_env.hpp"
#include "../message.hpp"
#include "../talk.hpp"
#include "../ui/ui_menu_dialog.hpp"
#include "../variables.hpp"
#include "dialog_decoder.hpp"



namespace elona
{

static void _dialog_error(const std::string& node_id, const std::string& text)
{
    std::string message = "Dialog error (" + node_id + "): " + text;

    txt(message, Message::color{ColorIndex::red});
    std::cerr << message << std::endl;
}

bool DialogNodeBehaviorGenerator::apply(
    DialogData& the_dialog,
    DialogNode& the_dialog_node)
{
    the_dialog_node.text.clear();
    the_dialog_node.choices.clear();

    sol::table result = the_dialog.export_manager.call_with_result(
        callback_generator,
        // Type of templated function will be wrong unless there is a cast, for
        // some reason.
        static_cast<sol::table>(sol::lua_nil));

    if (result == sol::lua_nil)
    {
        _dialog_error(
            the_dialog_node.id,
            callback_generator + ": Returned value was nil or not a table.");
        return false;
    }

    // The table format is the same as that of the parsed dialog HCL.
    try
    {
        lua::ConfigTable wrapped_result(
            result, "<retval of " + callback_generator + ">");
        DialogDecoderLogic(the_dialog.export_manager)
            .parse_text_choices(
                wrapped_result, "<generated node>", the_dialog_node);
    }
    catch (const std::exception& e)
    {
        _dialog_error(the_dialog_node.id, e.what());
        return false;
    }

    return true;
}

bool DialogNodeBehaviorRedirector::apply(
    DialogData& the_dialog,
    DialogNode& the_dialog_node)
{
    sol::object result = the_dialog.export_manager.call_with_result(
        callback_redirector,
        // Type of templated function will be wrong unless there is a cast, for
        // some reason.
        static_cast<sol::object>(sol::lua_nil));

    if (result == sol::lua_nil || !result.is<std::string>())
    {
        _dialog_error(
            the_dialog_node.id,
            callback_redirector +
                ": Redirector callback returned invalid node id");
        return false;
    }

    return the_dialog.set_node(result.as<std::string>());
}

bool DialogNodeBehaviorInheritChoices::apply(
    DialogData& the_dialog,
    DialogNode& the_dialog_node)
{
    auto choices = the_dialog.choices_for_node(node_id_for_choices);

    if (choices)
    {
        the_dialog_node.choices = *choices;
        return true;
    }
    else
    {
        _dialog_error(
            the_dialog_node.id,
            "Cannot obtain choices for node " + node_id_for_choices);
        return false;
    }
}


bool DialogData::has_more_text()
{
    if (!current_node_id)
    {
        return false;
    }

    return true;
}

bool DialogData::state_is_valid()
{
    if (!current_node_id)
    {
        return true;
    }

    const auto it = nodes.find(*current_node_id);
    if (it == nodes.end())
    {
        _dialog_error(*current_node_id, "No such dialog node");
        return false;
    }

    const auto& node = it->second;
    size_t text_amount = node.text.size();

    if (text_amount == 0)
    {
        _dialog_error(*current_node_id, "No text was found in dialog node");
        return false;
    }

    if (current_text_index > text_amount)
    {
        throw std::runtime_error(
            *current_node_id + ": BUG: Dialog has " + text_amount +
            " texts, but " + current_text_index + " was requested");

        return false;
    }

    if (node.choices.size() == 0)
    {
        _dialog_error(*current_node_id, "No choices were found in dialog node");
        return false;
    }

    return true;
}

bool DialogData::is_cancelable_now()
{
    return is_cancelable;
}

static bool _run_callback(
    optional<std::string>& callback,
    lua::ExportManager& export_manager)
{
    try
    {
        if (callback)
        {
            export_manager.call_unsafely(*callback);
        }
        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool DialogData::run_callback_before()
{
    return _run_callback(current_node().callback_before, export_manager);
}

bool DialogData::run_callback_after()
{
    return _run_callback(current_node().callback_after, export_manager);
}

bool DialogData::apply_node_behavior(DialogNode& node)
{
    try
    {
        return node.behavior->apply(*this, node);
    }
    catch (const std::exception& e)
    {
        _dialog_error(node.id, e.what());
        return false;
    }
}

bool DialogData::advance(size_t choice_index)
{
    if (!choices())
    {
        if (choice_index != 0)
        {
            _dialog_error(
                *current_node_id,
                "Current node should have \"more\" choice only, but choice "s +
                    choice_index + " was requested"s);
            return false;
        }

        return advance_internal(node_id(), current_text_index + 1);
    }

    size_t choice_amount = choices()->size();
    if (choice_index >= choice_amount)
    {
        _dialog_error(
            *current_node_id,
            "Current node has "s + choice_amount + " choices, but "s +
                choice_index + " was requested"s);
        return false;
    }

    const auto& choice = choices()->at(choice_index);
    return set_node(choice.node_id);
}

bool DialogData::set_node(optional<std::string> node_id)
{
    return advance_internal(node_id, 0);
}

optional<const std::vector<DialogChoice>&> DialogData::choices_for_node(
    const std::string& node_id)
{
    auto it = nodes.find(node_id);
    if (it == nodes.end())
    {
        _dialog_error(*current_node_id, "No such node " + node_id);
        return none;
    }

    if (!it->second.behavior->has_choices())
    {
        return none;
    }

    if (!apply_node_behavior(it->second))
    {
        return none;
    }

    return it->second.choices;
}

bool DialogData::advance_internal(
    optional<std::string> node_id,
    size_t text_index)
{
    if (!node_id)
    {
        current_node_id = none;
        current_text_index = 0;
        return true;
    }

    auto it = nodes.find(*node_id);
    if (it == nodes.end())
    {
        _dialog_error(*current_node_id, "No such node " + *node_id);
        return false;
    }

    current_node_id = *node_id;
    current_text_index = text_index;

    if (!apply_node_behavior(it->second))
    {
        return false;
    }

    if (!state_is_valid())
    {
        return false;
    }

    return true;
}

bool DialogData::show_dialog()
{
    if (!run_callback_before())
    {
        return false;
    }

    bool cancelable = is_cancelable_now();
    auto result = ui::UIMenuDialog(*this, cancelable).show();

    if (result.canceled)
    {
        if (scenemode)
        {
            scene_cut = 1;
        }
        talk_reset_variables();
        // return talk_result_t::talk_end;
        return false;
    }

    if (!run_callback_after())
    {
        return false;
    }

    size_t choice_index = *result.value;
    if (!advance(choice_index))
    {
        return false;
    }

    return true;
}

void DialogData::show()
{
    // The large amount of returns is to guard against user error, since dialogs
    // are loaded externally.

    if (!state_is_valid())
    {
        return;
    }

    while (has_more_text())
    {
        if (!show_dialog())
        {
            return;
        }
    }
}

} // namespace elona
