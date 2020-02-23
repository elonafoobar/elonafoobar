#pragma once

#include <vector>

#include "command.hpp"



namespace elona
{
namespace mapeditor
{

class UndoHistory
{
public:
    UndoHistory() = default;


    void push_and_execute_command(CommandPtr&& command);
    bool can_redo() const;
    void redo();
    bool can_undo() const;
    void undo();


private:
    std::vector<CommandPtr> _commands;

    // The index of the command that will be re-done.
    size_t _current{};
};

} // namespace mapeditor
} // namespace elona
