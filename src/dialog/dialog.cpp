#include "../talk.hpp"
#include "../ui/ui_menu_dialog.hpp"
#include "../variables.hpp"

namespace elona
{

static void _dialog_error(const std::string& node_id, const std::string& text)
{
    txtef(color_index_t::red);
    txt(node_id + ": Dialog error: " + text);
}

bool dialog_node_behavior_generator::apply(
    dialog&,
    dialog_node& the_dialog_node)
{
    sol::table result = lua::lua->get_export_manager().call(callback_generator);

    if (result == sol::lua_nil)
    {
        _dialog_error(
            the_dialog_node.id,
            callback_generator + ": Returned value was nil.");
        return false;
    }

    the_dialog_node.text.clear();
    for (const auto& pair : result)
    {
        std::string text = pair.second;
        the_dialog_node.text.emplace_back(text);
    }

    the_dialog_node.choices.clear();
    for (const auto& pair : choices)
    {
        std::string locale_key = pair.second["locale_key"];
        sol::object next_node_id = pair.second["next_node_id"];

        dialog_choice choice;
        choice.locale_key = locale_key;
        if (next_node_id != sol::lua_nil)
        {
            choice.next_node_id = next_node_id.as<std::string>();
        }

        the_dialog_node.choices.emplace_back(choice);
    }

    return true;
}

bool dialog_node_behavior_redirector::apply(dialog& the_dialog, dialog_node&)
{
    std::string result =
        lua::lua->get_export_manager().call(callback_redirector);

    return the_dialog.advance(result, 0);
}

bool dialog_node_behavior_inherit_choices::apply(
    dialog& the_dialog,
    dialog_node& the_dialog_node)
{
    if (is_applying)
    {
        _dialog_error(
            the_dialog_node.id,
            "Cannot inherit dialog choices from other inherit nodes "
            "cyclically.");
        is_applying = false;
        return false;
    }

    is_applying = true;
    auto& node = the_dialog.nodes.at(node_id_for_choices);

    if (!the_dialog.apply_node_behavior(node))
    {
        is_applying = false;
        return false;
    }

    the_dialog_node.choices = node.choices;
    is_applying = false;

    return true;
}


void dialog_start(const std::string& id)
{
    dialog the_dialog(id);
    the_dialog.show();
}

bool dialog::has_more_text()
{
    if (!current_node_id)
    {
        return false;
    }

    return true;
}

bool dialog::state_is_valid()
{
    const auto it = nodes.find(*node_id);
    if (it == nodes.end())
    {
        dialog_error(*current_node_id, "No such node " + *node_id);
        return false;
    }

    const auto& node = it->second;
    size_t text_amount = node.text.size();

    if (text_amount == 0)
    {
        _dialog_error(*current_node_id, "No text was found in dialog node");
        return false;
    }

    if (text_index > text_amount)
    {
        throw std::runtime_error(
            *node_id + ": BUG: Dialog has " + text_amount + " texts, but "
            + text_index + " was requested");

        return false;
    }

    if (node.choices.size() == 0)
    {
        _dialog_error(*current_node_id, "No choices were found in dialog node");
        return false;
    }

    return true;
}

bool dialog::is_cancelable_now()
{
    return false;
}

static bool _run_callback(optional<std::string>& callback)
{
    try
    {
        if (callback)
        {
            lua::lua.get_registry_manager().run_callback(*callback);
        }
        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool dialog::run_callback_before()
{
    return _run_callback(current_node().callback_before);
}

bool dialog::run_callback_after()
{
    return _run_callback(current_node().callback_after);
}

bool dialog::apply_node_behavior(dialog_node& node)
{
    try
    {
        return node.behavior.apply(*this, node);
    }
    catch (const sol::error& err)
    {
        _dialog_error(node.id, err.what());
        return false;
    }
}

bool dialog::advance(optional<const std::string&> node_id, size_t text_index)
{
    if (!node_id)
    {
        current_node_id = none;
        current_text_index = 0;
        return;
    }

    auto it = nodes.find(*node_id);
    if (it == nodes.end())
    {
        dialog_error(current_node_id, "No such node " + *node_id);
        return false;
    }

    if (!apply_node_behavior(it->second))
    {
        return false;
    }

    current_node_id = *node_id;
    current_text_index = text_index;

    return true;
}

void dialog::show()
{
    while (!the_dialog.has_more_text())
    {
        if (!the_dialog.state_is_valid())
        {
            return;
        }

        if (!the_dialog.run_callback_before())
        {
            return;
        }

        bool cancelable = the_dialog.is_cancelable_now();
        auto result = ui::ui_menu_dialog(the_dialog, cancelable).show();

        if (result.canceled)
        {
            if (scenemode)
            {
                scene_cut = 1;
            }
            talk_reset_variables();
            return;
        }

        if (!the_dialog.run_callback_after())
        {
            return;
        }

        if (!the_dialog.advance(*result.value, 0))
        {
            return;
        }
    }
}

} // namespace elona
