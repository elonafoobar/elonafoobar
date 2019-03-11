#pragma once
#include <queue>
#include <string>

namespace elona
{

/**
 * Queue of keybind actions that are executed first before any user input is
 * queried. It is used by the mod macro system to programmatically send inputs
 * to the game.
 */
class MacroActionQueue
{
    using Action = std::string;

    const std::string default_action = "";

public:
    void push(const Action& action)
    {
        _queue.push(action);
    }

    void clear()
    {
        while (!empty())
        {
            pop();
        }
    }

    bool empty()
    {
        return _queue.empty();
    }

    Action pop()
    {
        if (empty())
        {
            return default_action;
        }

        Action result = _queue.front();
        _queue.pop();
        return result;
    }

private:
    std::queue<Action> _queue;
};

namespace keybind
{
extern MacroActionQueue macro_action_queue;
}

} // namespace elona
