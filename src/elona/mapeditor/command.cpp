#include "command.hpp"

#include "../magic.hpp"
#include "../map.hpp"
#include "../variables.hpp"



namespace elona
{
namespace mapeditor
{

void PutTileCommand::redo()
{
    cell_data.at(_x, _y).chip_id_actual = _tile_to;
    cell_data.at(_x, _y).chip_id_memory = _tile_to;
}



void PutTileCommand::undo()
{
    cell_data.at(_x, _y).chip_id_actual = _tile_from;
    cell_data.at(_x, _y).chip_id_memory = _tile_from;
}



void CreateWallCommand::redo()
{
    tlocx = _x;
    tlocy = _y;
    tile = _tile_to;
    efid = 438;
    magic();
}



void CreateWallCommand::undo()
{
    cell_data.at(_x, _y).chip_id_actual = _tile_from;
    cell_data.at(_x, _y).chip_id_memory = _tile_from;
}

} // namespace mapeditor
} // namespace elona
