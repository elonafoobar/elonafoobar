#include "draw.hpp"
#include "elona.hpp"
#include "variables.hpp"


namespace elona
{


void prepare_item_image(int id, int color)
{
    const auto x = chipi(0, id);
    const auto y = chipi(1, id);
    const auto w = chipi(2, id);
    const auto h = chipi(3, id);

    gsel(1);
    boxf(0, 960, w, h + 960);

    pos(0, 960);
    set_color_mod(
        255 - c_col(0, color), 255 - c_col(1, color), 255 - c_col(2, color));
    gcopy(1, x, y, w, h);
    set_color_mod(255, 255, 255);
    gfini(w, h);
    gfdec2(c_col(0, color), c_col(1, color), c_col(2, color));
    gsel(0);
}



void prepare_item_image(int id, int color, int character_image)
{
    if (id != 528 && id != 531)
    {
        prepare_item_image(id, color);
        return;
    }

    const auto w = chipi(2, id);
    const auto h = chipi(3, id);

    gsel(1);
    boxf(0, 960, w, h + 960);

    if (id == 528) // Cards
    {
        const auto character_id = character_image % 1000;
        const auto character_color = character_image / 1000;
        gmode(2);
        pos(0, 960);
        set_color_mod(
            255 - c_col(0, color),
            255 - c_col(1, color),
            255 - c_col(2, color));
        gcopy(1, 0, 768, inf_tiles, inf_tiles);
        set_color_mod(255, 255, 255);
        pos(0, 1008);
        set_color_mod(
            255 - c_col(0, character_color),
            255 - c_col(1, character_color),
            255 - c_col(2, character_color),
            5);
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
        set_color_mod(255, 255, 255, 5);
        pos(6, 974);
        gcopy(1, 0, 1008, 22, 20);
        gsel(0);
    }
    else // Figures
    {
        const auto character_id = character_image % 1000;
        const auto character_color = character_image / 1000;
        pos(8, 1058 - chipc(3, character_id));
        set_color_mod(
            255 - c_col(0, character_color),
            255 - c_col(1, character_color),
            255 - c_col(2, character_color),
            5);
        gcopy(
            5,
            chipc(0, character_id) + 8,
            chipc(1, character_id) + 2,
            chipc(2, character_id) - 16,
            chipc(3, character_id) - 8);
        set_color_mod(255, 255, 255, 5);
        gmode(4, -1, -1, 192);
        pos(0, 960 + (chipc(3, character_id) == inf_tiles) * 48);
        set_color_mod(
            255 - c_col(0, color),
            255 - c_col(1, color),
            255 - c_col(2, color));
        gcopy(
            1,
            144,
            768 + (chipc(3, character_id) > inf_tiles) * 48,
            inf_tiles,
            chipc(3, character_id) + (chipc(3, character_id) > inf_tiles) * 48);
        set_color_mod(255, 255, 255);
        gmode(2);
        gsel(0);
    }
}



} // namespace elona
