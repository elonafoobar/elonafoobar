#include "map.hpp"
#include "character.hpp"
#include "ctrl_file.hpp"
#include "elona.hpp"
#include "position.hpp"
#include "item.hpp"
#include "item_db.hpp"
#include "variables.hpp"



namespace elona
{



void map_reload(const std::string& prm_935)
{
    int y_at_m166 = 0;
    int x_at_m166 = 0;
    fmapfile = (filesystem::dir::map() / prm_935).generic_string();
    ctrl_file(file_operation_t::_16);
    for (int cnt = 0, cnt_end = (mdata(1)); cnt < cnt_end; ++cnt)
    {
        y_at_m166 = cnt;
        for (int cnt = 0, cnt_end = (mdata(0)); cnt < cnt_end; ++cnt)
        {
            map(cnt, y_at_m166, 8) = 0;
            map(cnt, y_at_m166, 9) = 0;
        }
    }
    for (int cnt = 0; cnt < 200; ++cnt)
    {
        mef(0, cnt) = 0;
    }
    for (const auto& cnt : items(-1))
    {
        if (inv[cnt].number > 0)
        {
            if (inv[cnt].own_state == 1)
            {
                if (the_item_db[inv[cnt].id]->category == 57000)
                {
                    inv[cnt].number = 0;
                    cell_refresh(inv[cnt].position.x, inv[cnt].position.y);
                }
            }
        }
    }
    for (int cnt = 0; cnt < 400; ++cnt)
    {
        if (cmapdata(0, cnt) == 0)
        {
            continue;
        }
        x_at_m166 = cmapdata(1, cnt);
        y_at_m166 = cmapdata(2, cnt);
        if (cmapdata(4, cnt) == 0)
        {
            if (map(x_at_m166, y_at_m166, 4) == 0)
            {
                flt();
                int stat =
                    itemcreate(-1, cmapdata(0, cnt), x_at_m166, y_at_m166, 0);
                if (stat != 0)
                {
                    inv[ci].own_state = cmapdata(3, cnt);
                }
            }
            cell_refresh(x_at_m166, y_at_m166);
        }
    }
    return;
}



} // namespace elona
