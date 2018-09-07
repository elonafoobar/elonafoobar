#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "../optional.hpp"

namespace elona
{

class DialogData;
struct DialogNode;

struct DialogChoice
{
    DialogChoice(std::string locale_key, optional<std::string> node_id)
        : locale_key(locale_key)
        , node_id(node_id)
    {
    }

    std::string locale_key;
    optional<std::string> node_id;
};

struct DialogNodeBehavior
{
    virtual ~DialogNodeBehavior() = default;

    virtual bool apply(DialogData&, DialogNode&)
    {
        return true;
    }
};

/// This node is generated from calling a Lua callback.
struct DialogNodeBehaviorGenerator : public DialogNodeBehavior
{
    DialogNodeBehaviorGenerator(std::string callback_generator)
        : callback_generator(callback_generator)
    {
    }

    bool apply(DialogData&, DialogNode&);

    std::string callback_generator;
};

/// This node redirects to another node without showing text. The node
/// to redirect to is determined by calling a Lua function.
struct DialogNodeBehaviorRedirector : public DialogNodeBehavior
{
    DialogNodeBehaviorRedirector(std::string callback_redirector)
        : callback_redirector(callback_redirector)
    {
    }

    bool apply(DialogData&, DialogNode&);

    std::string callback_redirector;
};

/// This node uses the choices of another node.
struct DialogNodeBehaviorInheritChoices : public DialogNodeBehavior
{
    DialogNodeBehaviorInheritChoices(std::string node_id_for_choices)
        : node_id_for_choices(node_id_for_choices)
    {
    }

    bool apply(DialogData&, DialogNode&);

    std::string node_id_for_choices;
    bool is_applying = false;
};

struct DialogNode
{
    std::string id;
    std::vector<std::string> text;
    std::vector<DialogChoice> choices;

    /// Lua callback IDs to run before/after the node is displayed.
    optional<std::string> callback_before;
    optional<std::string> callback_after;

    /// Behavior to apply to the dialog state, like changing the
    /// current dialog node or programmatically generating nodes.
    std::shared_ptr<DialogNodeBehavior> behavior;
};

class DialogData
{
public:
    friend struct DialogNodeBehavior;

    typedef std::unordered_map<std::string, DialogNode> map_type;

public:
    DialogData(map_type nodes, std::string starting_node)
        : nodes(nodes)
        , starting_node(starting_node)
    {
    }

public:
    void show();

    const std::string& text_key() const
    {
        return current_node().text.at(current_text_index);
    }

    optional<const std::vector<DialogChoice>&> choices() const
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

    optional<std::string> node_id() const
    {
        return current_node_id;
    }

    /// Returns false on failure.
    bool advance(size_t choice_index);

    /// Returns false on failure.
    bool set_node(optional<std::string> node_id);

    optional<const std::vector<DialogChoice>&> choices_for_node(
        const std::string& node_id);


private:
    DialogNode& current_node()
    {
        assert(current_node_id);
        return nodes.at(*current_node_id);
    }

    const DialogNode& current_node() const
    {
        assert(current_node_id);
        return nodes.at(*current_node_id);
    }

    bool has_more_text();
    bool state_is_valid();
    bool is_cancelable_now();

    /// Returns false on failure.
    bool run_callback_before();

    /// Returns false on failure.
    bool run_callback_after();

    /// Returns false on failure.
    bool apply_node_behavior(DialogNode& node);

    /// Returns false on failure.
    bool advance_internal(optional<std::string> node_id, size_t text_index);

    size_t current_text_index = 0;
    optional<std::string> current_node_id = none;

    map_type nodes;
    std::string starting_node;
};

} // namespace elona
