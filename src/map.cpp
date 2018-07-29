#include "map.hpp"
#include "character.hpp"
#include "ctrl_file.hpp"
#include "elona.hpp"
#include "item.hpp"
#include "item_db.hpp"
#include "itemgen.hpp"
#include "map_cell.hpp"
#include "mef.hpp"
#include "position.hpp"
#include "variables.hpp"



namespace elona
{



void map_reload(const std::string& map_filename)
{
    fmapfile = (filesystem::dir::map() / map_filename).generic_string();
    ctrl_file(file_operation_t::map_load_map_obj_files);

    for (int y = 0; y < mdata_map_height; ++y)
    {
        for (int x = 0; x < mdata_map_width; ++x)
        {
            map(x, y, 8) = 0;
            map(x, y, 9) = 0;
        }
    }

    mef_clear_all();

    for (const auto& i : items(-1))
    {
        if (inv[i].number > 0)
        {
            if (inv[i].own_state == 1)
            {
                if (the_item_db[inv[i].id]->category == 57000)
                {
                    item_remove(inv[i]);
                    cell_refresh(inv[i].position.x, inv[i].position.y);
                }
            }
        }
    }

    for (int i = 0; i < 400; ++i)
    {
        if (cmapdata(0, i) == 0)
            continue;
        const auto x = cmapdata(1, i);
        const auto y = cmapdata(2, i);
        if (cmapdata(4, i) == 0)
        {
            if (map(x, y, 4) == 0)
            {
                flt();
                int stat = itemcreate(-1, cmapdata(0, i), x, y, 0);
                if (stat != 0)
                {
                    inv[ci].own_state = cmapdata(3, i);
                }
            }
            cell_refresh(x, y);
        }
    }
}



} // namespace elona
