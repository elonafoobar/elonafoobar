#include "design_mode.hpp"

#include "../audio.hpp"
#include "../character.hpp"
#include "../config.hpp"
#include "../draw.hpp"
#include "../game.hpp"
#include "../i18n.hpp"
#include "../input.hpp"
#include "../map.hpp"
#include "../menu.hpp"
#include "../text.hpp"
#include "../ui.hpp"
#include "../variables.hpp"
#include "undo_history.hpp"



namespace elona
{

extern int cansee;
extern int kdx;
extern int kdy;



namespace mapeditor
{

namespace
{

void prepare_house_board_tiles()
{
    std::vector<int> unavailable_tiles{
        15,  16,  24,  25,  26,  27,  28,  29,  30,  92,  93,  94,  95,  141,
        169, 170, 171, 180, 182, 192, 244, 245, 246, 247, 248, 249, 250, 251,
        252, 253, 254, 255, 256, 257, 258, 292, 293, 294, 309, 310, 311, 312,
        313, 314, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 327, 328,
        329, 330, 331, 332, 333, 334, 335, 336, 337, 338, 339, 340, 341, 342,
        343, 344, 345, 346, 347, 348, 349, 350, 351, 352, 353, 354, 355, 356,
        372, 373, 374, 375, 400, 401, 402, 403, 404, 405, 406, 407, 408, 409,
        410, 411, 412, 413, 414, 415, 416, 417, 418, 419, 422, 431, 432, 433,
        434, 435, 436, 437, 438, 439, 440, 441, 442, 443, 444, 445, 446, 447,
        448, 449, 450, 451, 452, 453, 454, 455};

    p = 0;
    p(1) = 0;

    gsel(2);

    for (int cnt = 0; cnt < 2772; ++cnt)
    {
        bool available{};
        if (cnt < 231)
        {
            available = true;
        }
        if (cnt >= 396 && cnt < 429)
        {
            available = true;
        }
        if (cnt >= 462 && cnt < 495)
        {
            available = true;
        }
        if (cnt >= 561 && cnt < 726)
        {
            available = true;
        }
        if (!available)
        {
            continue;
        }
        if (chip_data[cnt].kind == 2)
        {
            continue;
        }
        if (chip_data[cnt].kind == 1)
        {
            continue;
        }
        if (chip_data[cnt].kind2 == 5)
        {
            continue;
        }
        if (chip_data[cnt].kind == 3)
        {
            if (game_data.home_scale <= 3)
            {
                continue;
            }
            else
            {
                --p(1);
            }
        }
        ++p(1);
        if (range::find(unavailable_tiles, p(1)) != std::end(unavailable_tiles))
        {
            continue;
        }
        list(0, p) = cnt;
        ++p;
        if (chip_data[cnt].anime_frame != 0)
        {
            cnt = cnt + chip_data[cnt].anime_frame - 1;
            continue;
        }
    }

    listmax = p;
    gsel(0);
}



void select_house_board_tile()
{
    snd("core.pop2");

    auto box_size = inf_tiles / 2;
    while (1)
    {
        gmode(0);
        p = 0;
        // TODO
        for (int y = 0; y < 20; ++y)
        {
            for (int x = 0; x < 33; ++x)
            {
                if (p < listmax)
                {
                    const auto& chip = chip_data[list(0, p)];
                    draw_map_tile(
                        list(0, p),
                        x * box_size,
                        y * box_size,
                        inf_tiles,
                        inf_tiles,
                        box_size,
                        box_size);
                    if (chip.effect & 4)
                    {
                        boxl(
                            x * box_size,
                            y * box_size,
                            box_size,
                            box_size,
                            {240, 230, 220});
                    }
                }
                ++p;
            }
        }

        gmode(2);
        redraw();
        await(g_config.general_wait());
        const auto input = stick();
        if (input == StickKey::mouse_left)
        {
            p = mousex / box_size + mousey / box_size * 33;
            if (p >= listmax)
            {
                snd("core.fail1");
                continue;
            }
            tile = list(0, p);
            snd("core.ok1");
            house_board_update_screen();
            return;
        }
        if (input == StickKey::mouse_right)
        {
            house_board_update_screen();
            return;
        }
    }
}



int target_position_homemapmode(UndoHistory& undo_history)
{
    tlocx = tlocinitx;
    tlocy = tlocinity;

    while (1)
    {
        screenupdate = -1;
        update_screen();
        dx = (tlocx - scx) * inf_tiles + inf_screenx;
        dy = (tlocy - scy) * inf_tiles + inf_screeny;
        if (dy + inf_tiles <= windowh - inf_verh)
        {
            snail::Application::instance().get_renderer().set_blend_mode(
                snail::BlendMode::blend);
            snail::Application::instance().get_renderer().set_draw_color(
                {127, 127, 255, 50});
            snail::Application::instance().get_renderer().fill_rect(
                dx,
                dy * (dy > 0),
                inf_tiles -
                    (dx + inf_tiles > windoww) * (dx + inf_tiles - windoww),
                inf_tiles + (dy < 0) * inf_screeny -
                    (dy + inf_tiles > windowh - inf_verh) *
                        (dy + inf_tiles - windowh + inf_verh));
        }
        draw_map_tile(tile, windoww - 80, 20);
        txttargetnpc(tlocx, tlocy);
        redraw();
        auto action = key_check();
        if (action == "enter")
        {
            select_house_board_tile();
            wait_key_released();
            continue;
        }
        if (action == "switch_mode")
        {
            undo_history.undo();
            continue;
        }
        if (action == "identify")
        {
            undo_history.redo();
            continue;
        }
        const auto input = stick(StickKey::mouse_left | StickKey::mouse_right);
        if (input == StickKey::mouse_left)
        {
            action = "enter";
        }
        if (input == StickKey::mouse_right)
        {
            if (chip_data.for_cell(tlocx, tlocy).kind == 2 ||
                chip_data.for_cell(tlocx, tlocy).kind == 1)
            {
                snd("core.fail1");
                wait_key_released();
                continue;
            }
            tile = cell_data.at(tlocx, tlocy).chip_id_actual;
            snd("core.cursor1");
            wait_key_released();
        }
        tx = clamp(mousex - inf_screenx, 0, windoww) / inf_tiles;
        ty = clamp(mousey - inf_screeny, 0, (windowh - inf_verh)) / inf_tiles;
        int stat = key_direction(action);
        if (stat == 1)
        {
            cdata.player().position.x += kdx;
            cdata.player().position.y += kdy;
            if (cdata.player().position.x < 0)
            {
                cdata.player().position.x = 0;
            }
            else if (cdata.player().position.x >= map_data.width)
            {
                cdata.player().position.x = map_data.width - 1;
            }
            if (cdata.player().position.y < 0)
            {
                cdata.player().position.y = 0;
            }
            else if (cdata.player().position.y >= map_data.height)
            {
                cdata.player().position.y = map_data.height - 1;
            }
        }
        tlocx = clamp(tx + scx, 0, map_data.width - 1);
        tlocy = clamp(ty + scy, 0, map_data.height - 1);
        if (action == "enter")
        {
            tlocinitx = 0;
            tlocinity = 0;
            return cansee;
        }
        if (action == "cancel")
        {
            tlocinitx = 0;
            tlocinity = 0;
            update_screen();
            return -1;
        }
    }
}



void fill_tile(int x, int y, int from, int to)
{
    // out of range
    if (x < 0 || map_data.width <= x || y < 0 || map_data.height <= y)
        return;

    if (cell_data.at(x, y).chip_id_actual != from)
        return;

    if ((chip_data[to].effect & 4) != 0 &&
        cell_data.at(x, y).chara_index_plus_one != 0)
        return;

    // Draw one tile.
    cell_data.at(x, y).chip_id_actual = tile;
    cell_data.at(x, y).chip_id_memory = tile;

    // Draw tiles around.
    fill_tile(x - 1, y, from, to);
    fill_tile(x + 1, y, from, to);
    fill_tile(x, y - 1, from, to);
    fill_tile(x, y + 1, from, to);
}

} // namespace



void start_home_map_mode()
{
    UndoHistory undo_history;

    const auto pc_position_prev = cdata.player().position;
    homemapmode = 1;

    prepare_house_board_tiles();

    Message::instance().linebreak();
    txt(i18n::s.get("core.building.home.design.help"));

    tlocinitx = cdata.player().position.x;
    tlocinity = cdata.player().position.y;
    tile = 0;
    while (1)
    {
        await(g_config.general_wait());
        int stat = target_position_homemapmode(undo_history);
        if (stat == -1)
        {
            break;
        }

        if (getkey(snail::Key::ctrl))
        {
            if (cell_data.at(tlocx, tlocy).chip_id_actual != tile)
            {
                fill_tile(
                    tlocx,
                    tlocy,
                    cell_data.at(tlocx, tlocy).chip_id_actual,
                    tile);
            }
        }
        else if (chip_data[tile].effect & 4)
        {
            undo_history.push_and_execute_command(
                make_command<CreateWallCommand>(
                    tlocx,
                    tlocy,
                    cell_data.at(tlocx, tlocy).chip_id_actual,
                    tile));
        }
        else
        {
            undo_history.push_and_execute_command(make_command<PutTileCommand>(
                tlocx, tlocy, cell_data.at(tlocx, tlocy).chip_id_actual, tile));
        }
        tlocinitx = tlocx;
        tlocinity = tlocy;
    }

    homemapmode = 0;
    cdata.player().position = pc_position_prev;
}

} // namespace mapeditor
} // namespace elona
