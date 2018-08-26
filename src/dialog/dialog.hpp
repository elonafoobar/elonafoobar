#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "../optional.hpp"

namespace elona
{

class dialog;
struct dialog_node;

struct dialog_choice
{
    std::string locale_key;
    optional<std::string> next_node_id;
};

struct dialog_node_behavior
{
    friend class dialog;

    virtual bool apply(dialog&, dialog_node&)
    {
        return true;
    }
};

/// This node is generated from calling a Lua callback.
struct dialog_node_behavior_generator : dialog_node_behavior
{
    virtual bool apply(dialog&, dialog_node&);

    std::string callback_generator;
};

/// This node redirects to another node without showing text. The node
/// to redirect to is determined by calling a Lua function.
struct dialog_node_behavior_redirector : dialog_node_behavior
{
    virtual bool apply(dialog&, dialog_node&);

    std::string callback_redirector;
};

/// This node uses the choices of another node.
struct dialog_node_behavior_inherit_choices : dialog_node_behavior
{
    virtual bool apply(dialog&, dialog_node&);

    std::string node_id_for_choices;
    bool is_applying = false;
};

struct dialog_node
{
    std::string id;
    std::vector<std::string> text;
    std::vector<dialog_choice> choices;

    /// Lua callback IDs to run before/after the node is displayed.
    optional<std::string> callback_before;
    optional<std::string> callback_after;

    /// Behavior to apply to the dialog state, like changing the
    /// current dialog node or programmatically generating nodes.
    dialog_node_behavior behavior;
};

class dialog
{
public:
    dialog()
    {
    }

    dialog(const std::string& id)
    {
    }

public:
    void show();

    const std::string& text() const
    {
        return current_node().text.at(current_text_index);
    }

    optional<const std::vector<dialog_choice>&> choices() const
    {
        if (current_text_index != current_node().text.size() - 1)
        {
            return none;
        }

        return current_node().choices;
    }

    size_t text_index() const
    {
        return current_text_index;
    }

    dialog_node& current_node()
    {
        assert(current_node_id);
        return nodes.at(*current_node_id);
    }

    const dialog_node& current_node() const
    {
        assert(current_node_id);
        return nodes.at(*current_node_id);
    }

private:
    bool has_more_text();
    bool state_is_valid();
    bool is_cancelable_now();

    /// Returns false on failure.
    bool run_callback_before();

    /// Returns false on failure.
    bool run_callback_after();

    /// Returns false on failure.
    bool apply_node_behavior(dialog_node& node);

    /// Returns false on failure.
    bool advance(optional<const std::string&> node_id);

    size_t current_text_index = 0;
    optional<std::string> current_node_id = none;
    std::unordered_map<std::string, dialog_node> nodes;
};

void dialog_start(const std::string& id);

} // namespace elona
