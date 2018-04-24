#include "draw.hpp"
#include "character.hpp"
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
            5,
            chipc(0, character_id) + 8,
            chipc(1, character_id) + 4
                + (chipc(3, character_id) > inf_tiles) * 8,
            chipc(2, character_id) - 16,
            chipc(3, character_id) - 8
                - (chipc(3, character_id) > inf_tiles) * 10,
            22,
            20);
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



void show_hp_bar(show_hp_bar_side side, int inf_clocky)
{
    const bool right = side == show_hp_bar_side::right_side;

    int cnt{};
    for (int i = 1; i < 16; ++i)
    {
        auto& cc = cdata[i];
        if ((cc.state == 1 || cc.state == 6)
            && cdata[i].has_been_used_stethoscope())
        {
            const auto name = cdatan(0, i);
            const int x = 16 + (windoww - strlen_u(name) * 7 - 16) * right;
            const int y = inf_clocky + 200 - 180 * right + cnt * 32;
            // std::cout << "HP bar(" << i << "):name: " << position_t{x, y} <<
            // std::endl;
            pos(x, y);
            color(0, 0, 0);
            const auto color = cc.state == 1 ? snail::color{255, 255, 255}
                                             : snail::color{255, 35, 35};
            bmes(name, color.r, color.g, color.b);
            if (cc.state == 1)
            {
                const int width = clamp(cc.hp * 30 / cc.max_hp, 1, 30);
                const int x_ = 16 + (windoww - 108) * right;
                const int y_ = y + 17;
                // std::cout << "HP bar(" << i << "):bar:  " << position_t{x_,
                // y_} << std::endl;
                pos(x_, y_);
                gzoom(3, 480 - width, 517, width, 3, width * 3, 9);

                // Show leash icon.
                if (cfg_leash_icon && cdata[i].is_leashed())
                {
                    constexpr int leash = 631;
                    prepare_item_image(leash, 2);
                    const int icon_width = chipi(2, leash);
                    const int icon_height = chipi(3, leash);

                    pos(right ? std::min(x, x_) - icon_width / 2
                              : std::max(x_ + 90, int(x + strlen_u(name) * 7)),
                        y);
                    gzoom(
                        1,
                        0,
                        960,
                        icon_width,
                        icon_height,
                        icon_width / 2,
                        icon_height / 2,
                        true);
                    gmode(5);
                    gzoom(
                        1,
                        0,
                        960,
                        icon_width,
                        icon_height,
                        icon_width / 2,
                        icon_height / 2,
                        true);
                    gmode(2);
                }
            }
            ++cnt;
        }
    }
}



} // namespace elona
