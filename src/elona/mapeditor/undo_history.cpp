#include "undo_history.hpp"



namespace elona
{
namespace mapeditor
{

void UndoHistory::push_and_execute_command(CommandPtr&& command)
{
    // Clear future history first.
    _commands.resize(_current);

    // Push the new one.
    command->redo();
    _commands.emplace_back(std::move(command));
    _current += 1;
}



bool UndoHistory::can_redo() const
{
    // Has any redoable commands?
    return _current < _commands.size();
}



void UndoHistory::redo()
{
    if (!can_redo())
        return;

    auto&& cmd = _commands.at(_current);
    cmd->redo();
    _current += 1;
}



bool UndoHistory::can_undo() const
{
    // Has any undoable commands?
    return 0 < _current;
}



void UndoHistory::undo()
{
    if (!can_undo())
        return;

    auto&& cmd = _commands.at(_current - 1);
    cmd->undo();
    _current -= 1;
}

} // namespace mapeditor
} // namespace elona
