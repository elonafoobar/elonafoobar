#include "draw.hpp"
#include "elona.hpp"
#include "variables.hpp"


namespace elona
{


void prepare_item_image(int id, int color_or_character_id)
{
    const auto x = chipi(0, id);
    const auto y = chipi(1, id);
    const auto w = chipi(2, id);
    const auto h = chipi(3, id);

    gsel(1);
    boxf(0, 960, w, h + 960);

    if (id == 528)
    {
        const auto character_id = color_or_character_id;
        gmode(2);
        pos(0, 960);
        gcopy(1, 0, 768, inf_tiles, inf_tiles);
        pos(0, 1008);
        gzoom(
            22,
            20,
            5,
            chipc(0, character_id) + 8,
            chipc(1, character_id) + 4
                + (chipc(3, character_id) > inf_tiles) * 8,
            chipc(2, character_id) - 16,
            chipc(3, character_id) - 8
                - (chipc(3, character_id) > inf_tiles) * 10,
            1);
        pos(6, 974);
        gcopy(1, 0, 1008, 22, 20);
        gsel(0);
    }
    else if (id == 531)
    {
        const auto character_id = color_or_character_id;
        pos(8, 1058 - chipc(3, character_id));
        gcopy(
            5,
            chipc(0, character_id) + 8,
            chipc(1, character_id) + 2,
            chipc(2, character_id) - 16,
            chipc(3, character_id) - 8);
        gmode(4, -1, -1, 150);
        color(0, 0, 0);
        pos(0, 960 + (chipc(3, character_id) == inf_tiles) * 48);
        gcopy(
            1,
            144,
            768 + (chipc(3, character_id) > inf_tiles) * 48,
            inf_tiles,
            chipc(3, character_id) + (chipc(3, character_id) > inf_tiles) * 48);
        gmode(2);
        gsel(0);
    }
    else
    {
        const auto color = color_or_character_id;
        pos(0, 960);
        gcopy(1, x, y, w, h);
        gfini(w, h);
        gfdec2(c_col(0, color), c_col(1, color), c_col(2, color));
        gsel(0);
    }
}



} // namespace elona
