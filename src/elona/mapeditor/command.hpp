#pragma once

#include <memory>



namespace elona
{
namespace mapeditor
{

class AbstractCommand
{
public:
    virtual ~AbstractCommand() = default;

    virtual void redo() = 0;
    virtual void undo() = 0;
};



class PutTileCommand : public AbstractCommand
{
public:
    PutTileCommand(int x, int y, int tile_from, int tile_to)
        : _x(x)
        , _y(y)
        , _tile_from(tile_from)
        , _tile_to(tile_to)
    {
    }


    virtual ~PutTileCommand() = default;

    virtual void redo() override;
    virtual void undo() override;



private:
    int _x;
    int _y;
    int _tile_from;
    int _tile_to;
};



class CreateWallCommand : public AbstractCommand
{
public:
    CreateWallCommand(int x, int y, int tile_from, int tile_to)
        : _x(x)
        , _y(y)
        , _tile_from(tile_from)
        , _tile_to(tile_to)
    {
    }


    virtual ~CreateWallCommand() = default;

    virtual void redo() override;
    virtual void undo() override;



private:
    int _x;
    int _y;
    int _tile_from;
    int _tile_to;
};



using CommandPtr = std::unique_ptr<AbstractCommand>;


template <typename Command, typename... Args>
std::unique_ptr<Command> make_command(Args&&... args)
{
    return std::make_unique<Command>(std::forward<Args>(args)...);
}

} // namespace mapeditor
} // namespace elona
