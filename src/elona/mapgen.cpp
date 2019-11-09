#include "mapgen.hpp"

#include "area.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "ctrl_file.hpp"
#include "elona.hpp"
#include "enums.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "mef.hpp"
#include "quest.hpp"
#include "random.hpp"
#include "variables.hpp"



namespace elona
{

// TODO
extern elona_vector1<int> roomheight;
extern elona_vector1<int> roomwidth;
extern elona_vector1<int> roomx;
extern elona_vector1<int> roomy;
extern int cr;
extern int roomsum;
extern int tile_pot;

} // namespace elona



namespace
{

struct CellObjData
{
    int type;
    int tile;
};



enum class Direction
{
    north = 0,
    east = 1,
    west = 2,
    south = 3,
};



int tile_board;
int tile_townboard;
int tile_votebox;

std::vector<CellObjData> cellobjdata;



bool is_N_or_S(Direction d)
{
    return d == Direction::north || d == Direction::south;
}



bool is_E_or_W(Direction d)
{
    return d == Direction::east || d == Direction::west;
}



/// @a func takes (x, y) and returns nothing.
template <typename F>
void for_each_cell(F func)
{
    for (int y = 0; y < map_data.height; ++y)
    {
        for (int x = 0; x < map_data.width; ++x)
        {
            func(x, y);
        }
    }
}



void place_chara_on_entrance(Character& chara, int entrance_type)
{
    int x{};
    int y{};

    switch (entrance_type)
    {
    case 0:
        // Debug map (ID: 499) does not have valid entrance type.
        break;
    case 1: // Upstairs
        x = map_data.stair_up_pos % 1000;
        y = map_data.stair_up_pos / 1000;
        break;
    case 2: // Downstairs
        x = map_data.stair_down_pos % 1000;
        y = map_data.stair_down_pos / 1000;
        break;
    case 3: // Direction
        switch (game_data.player_next_move_direction)
        {
        case 0: // North
            x = map_data.width / 2;
            y = 1;
            if (game_data.current_map == mdata_t::MapId::noyel)
            {
                x = 5;
            }
            if (game_data.current_map == mdata_t::MapId::lumiest)
            {
                x = 25;
                y = 1;
            }
            break;
        case 1: // East
            x = map_data.width - 2;
            y = map_data.height / 2;
            if (game_data.current_map == mdata_t::MapId::palmia)
            {
                y = 22;
            }
            if (game_data.current_map == mdata_t::MapId::lumiest)
            {
                x = 58;
                y = 21;
            }
            break;
        case 2: // West
            x = 1;
            y = map_data.height / 2;
            if (game_data.current_map == mdata_t::MapId::noyel)
            {
                y = 3;
            }
            if (game_data.current_map == mdata_t::MapId::lumiest)
            {
                x = 25;
                y = 1;
            }
            break;
        case 3: // South
            x = map_data.width / 2;
            y = map_data.height - 2;
            if (game_data.current_map == mdata_t::MapId::palmia)
            {
                x = 30;
            }
            if (game_data.current_map == mdata_t::MapId::noyel)
            {
                x = 28;
            }
            if (game_data.current_map == mdata_t::MapId::lumiest)
            {
                x = 58;
                y = 21;
            }
            break;
        default: assert(0); break;
        }

        if (game_data.current_map == mdata_t::MapId::larna)
        {
            x = 1;
            y = 14;
        }
        if (game_data.player_x_on_map_leave != -1)
        {
            x = game_data.player_x_on_map_leave;
            y = game_data.player_y_on_map_leave;
        }
        break;
    case 4: // Center
        x = map_data.width / 2;
        y = map_data.height / 2;
        break;
    case 5: // Random
        x = rnd(map_data.width - 5) + 2;
        y = rnd(map_data.height - 5) + 2;
        break;
    case 6: // World map
        x = game_data.pc_x_in_world_map + rnd(chara.index / 5 + 1);
        y = game_data.pc_y_in_world_map + rnd(chara.index / 5 + 1);
        break;
    case 7: // Custom
        x = mapstartx;
        y = mapstarty;
        break;
    case 8: // Bottom
        x = map_data.width / 2;
        y = map_data.height - 2;
        break;
    default: assert(0); break;
    }

    cxinit = x;
    cyinit = y;
    chara_place(chara);
}



void convert_tiles_at_random()
{
    for_each_cell([&](int x, int y) {
        auto& chip = cell_data.at(x, y).chip_id_actual;

        if (chip == 0)
        {
            chip = tile_default +
                (rnd(tile_default(2)) == 0) * rnd(tile_default(1));
        }
        else if (chip == 1)
        {
            chip = tile_wall + (rnd(tile_wall(2)) == 0) * rnd(tile_wall(1));
        }
        else if (chip == 3)
        {
            chip = tile_room + (rnd(tile_room(2)) == 0) * rnd(tile_room(1));
        }
        else if (chip == 4)
        {
            chip = tile_default +
                (rnd(tile_default(2)) == 0) * rnd(tile_default(1));
        }
        else if (chip >= 100)
        {
            chip =
                tile_tunnel + (rnd(tile_tunnel(2)) == 0) * rnd(tile_tunnel(1));
        }
    });
}



bool can_dig_cell(int x, int y)
{
    if (x < 1 || map_data.width - 2 < x || y < 1 || map_data.height - 2 < y)
    {
        return false; // out of range
    }
    if (cell_data.at(x, y).chip_id_actual == 100)
    {
        return true;
    }
    return cell_data.at(x, y).chip_id_actual == 0;
}



void create_room_door(
    Direction door_direction,
    bool roomdoor_is_not_3,
    int room_x,
    int room_y,
    int room_w,
    int room_h)
{
    std::vector<int> door_positions(
        is_N_or_S(door_direction) ? room_w - 2 : room_h - 2);
    for (size_t i = 0; i < door_positions.size(); ++i)
    {
        door_positions[i] = static_cast<int>(i);
    }
    shuffle(door_positions);

    for (const auto& door_pos : door_positions)
    {
        int x{};
        int y{};
        switch (door_direction)
        {
        case Direction::north:
            x = door_pos + room_x + 1;
            y = room_y;
            break;
        case Direction::east:
            x = room_x + room_w - 1;
            y = door_pos + room_y + 1;
            break;
        case Direction::west:
            x = room_x;
            y = door_pos + room_y + 1;
            break;
        case Direction::south:
            x = door_pos + room_x + 1;
            y = room_y + room_h - 1;
            break;
        }

        bool can_create_door = true;
        for (const auto& n : {-1, 1})
        {
            const auto dx = is_N_or_S(door_direction) ? x : x + n;
            const auto dy = is_N_or_S(door_direction) ? y + n : y;
            if (dx < 0 || map_data.width <= dx || dy < 0 ||
                map_data.height <= dy)
            {
                can_create_door = false;
                break;
            }
            if (cell_data.at(dx, dy).chip_id_actual == 1)
            {
                can_create_door = false;
                break;
            }
        }
        if (can_create_door)
        {
            cell_data.at(x, y).chip_id_actual = 3;
            if (roomdoor_is_not_3)
            {
                const auto lock = rnd_capped(
                    std::abs(game_data.current_dungeon_level * 3 / 2) + 1);
                cell_featset(x, y, tile_doorclosed, 21, lock);
            }
            break;
        }
    }
}



void place_upstairs_at_random_pos(int x, int y, int w, int h)
{
    map_place_upstairs(rnd(w - 2) + x + 1, rnd(h - 2) + y + 1);
}



void place_downstairs_at_random_pos(int x, int y, int w, int h)
{
    map_place_downstairs(rnd(w - 2) + x + 1, rnd(h - 2) + y + 1);
}



template <typename F>
void _place_trap_web_or_barrel_internal(F put_object)
{
    for (int _i = 0; _i < 4; ++_i)
    {
        const int x = rnd(map_data.width - 5) + 2;
        const int y = rnd(map_data.height - 5) + 2;
        if ((chip_data.for_cell(x, y).effect & 4) == 0)
        {
            if (cell_data.at(x, y).feats == 0)
            {
                put_object(x, y);
                return;
            }
        }
    }
}



void place_trap()
{
    _place_trap_web_or_barrel_internal([&](int x, int y) {
        const int trap_type = rnd(8);
        if (game_data.current_dungeon_level <= 5)
        {
            if (trap_type == 1 || trap_type == 5 || trap_type == 6)
            {
                return;
            }
        }
        if (game_data.current_dungeon_level <= 25)
        {
            if (trap_type == 7)
            {
                return;
            }
        }
        cell_featset(x, y, 0, 14, trap_type);
    });
}



void place_web(int power)
{
    _place_trap_web_or_barrel_internal(
        [&](int x, int y) { mef_add(x, y, 1, 11, -1, power); });
}



void place_barrel()
{
    _place_trap_web_or_barrel_internal(
        [&](int x, int y) { cell_featset(x, y, tile_pot, 30); });
}



void make_door()
{
    for (cr = 0; cr < roomsum; ++cr)
    {
        /*
        A -------------- B
        |................|
        |.a dungeon room.|
        |................|
        D -------------- C

        i in [  0,     W   ) => from A to B
        i in [  W,    W+H  ) => from B to C
        i in [ W+H,  2W+H  ) => from C to D
        i in [ 2W+H, 2W+2H ) => from D to A
        */
        const int W = roomwidth(cr);
        const int H = roomheight(cr);
        for (int i = 0; i < (W + H) * 2; ++i)
        {
            const int k = i % (W + H);
            int dx = k < W ? k : W - 1;
            int dy = k < W ? 0 : k - W;
            if (W + H <= i)
            {
                dx = W - 1 - dx;
                dy = H - 1 - dy;
            }

            const int x = dx + roomx(cr);
            const int y = dy + roomy(cr);
            if (cell_data.at(x, y).chip_id_actual != 1)
            {
                const int lock = rnd_capped(
                    std::abs(game_data.current_dungeon_level * 3 / 2) + 1);
                cell_featset(x, y, tile_doorclosed, 21, lock);
            }
        }
    }
}



optional<int> _setup_map_generation_parameters()
{
    const auto& area = area_data[game_data.current_map];

    int dungeon_type = 1;
    if (rnd(30) == 0)
    {
        dungeon_type = 3;
    }

    if (area.type == mdata_t::MapType::dungeon)
    {
        dungeon_type = 2;
        if (rnd(4) == 0)
        {
            dungeon_type = 1;
        }
        if (rnd(6) == 0)
        {
            dungeon_type = 10;
        }
        if (rnd(10) == 0)
        {
            dungeon_type = 4;
        }
        if (rnd(25) == 0)
        {
            dungeon_type = 8;
        }
        if (rnd(20) == 0)
        {
            map_data.tileset = 10;
        }
    }
    if (area.type == mdata_t::MapType::dungeon_forest)
    {
        dungeon_type = 2;
        if (rnd(6) == 0)
        {
            dungeon_type = 1;
        }
        if (rnd(6) == 0)
        {
            dungeon_type = 10;
        }
        if (rnd(25) == 0)
        {
            dungeon_type = 8;
        }
        if (rnd(20) == 0)
        {
            dungeon_type = 4;
        }
    }
    if (area.type == mdata_t::MapType::dungeon_tower)
    {
        dungeon_type = 1;
        if (rnd(5) == 0)
        {
            dungeon_type = 4;
        }
        if (rnd(10) == 0)
        {
            dungeon_type = 3;
        }
        if (rnd(25) == 0)
        {
            dungeon_type = 2;
        }
        if (rnd(40) == 0)
        {
            map_data.tileset = 10;
        }
    }
    if (area.type == mdata_t::MapType::dungeon_castle)
    {
        dungeon_type = 1;
        if (rnd(5) == 0)
        {
            dungeon_type = 4;
        }
        if (rnd(6) == 0)
        {
            dungeon_type = 5;
        }
        if (rnd(7) == 0)
        {
            dungeon_type = 2;
        }
        if (rnd(40) == 0)
        {
            map_data.tileset = 10;
        }
    }

    if (area.id == mdata_t::MapId::lesimas)
    {
        map_data.max_crowd_density += game_data.current_dungeon_level / 2;
        map_data.tileset = 101;
        if (rnd(20) == 0)
        {
            map_data.tileset = 10;
        }
        if (game_data.current_dungeon_level < 35)
        {
            map_data.tileset = 0;
        }
        if (game_data.current_dungeon_level < 20)
        {
            map_data.tileset = 100;
        }
        if (game_data.current_dungeon_level < 10)
        {
            map_data.tileset = 200;
        }
        if (game_data.current_dungeon_level < 5)
        {
            map_data.tileset = 0;
        }
        dungeon_type = 1;
        for (int cnt = 0; cnt < 1; ++cnt)
        {
            if (game_data.current_dungeon_level == 1)
            {
                dungeon_type = 2;
                break;
            }
            if (game_data.current_dungeon_level == 5)
            {
                dungeon_type = 5;
                break;
            }
            if (game_data.current_dungeon_level == 10)
            {
                dungeon_type = 3;
                break;
            }
            if (game_data.current_dungeon_level == 15)
            {
                dungeon_type = 5;
                break;
            }
            if (game_data.current_dungeon_level == 20)
            {
                dungeon_type = 3;
                break;
            }
            if (game_data.current_dungeon_level == 25)
            {
                dungeon_type = 5;
                break;
            }
            if (game_data.current_dungeon_level == 30)
            {
                dungeon_type = 3;
                break;
            }
            if (game_data.current_dungeon_level < 30)
            {
                if (rnd(4) == 0)
                {
                    dungeon_type = 2;
                }
            }
            if (rnd(5) == 0)
            {
                dungeon_type = 4;
            }
            if (rnd(20) == 0)
            {
                dungeon_type = 8;
            }
            if (rnd(6) == 0)
            {
                dungeon_type = 10;
            }
        }
    }
    if (area.id == mdata_t::MapId::tower_of_fire)
    {
        map_data.max_crowd_density += game_data.current_dungeon_level / 2;
        map_data.tileset = 7;
        dungeon_type = 1;
    }
    if (area.id == mdata_t::MapId::crypt_of_the_damned)
    {
        map_data.max_crowd_density += game_data.current_dungeon_level / 2;
        map_data.tileset = 0;
        dungeon_type = 1;
    }
    if (area.id == mdata_t::MapId::ancient_castle)
    {
        map_data.max_crowd_density += game_data.current_dungeon_level / 2;
        map_data.tileset = 200;
        dungeon_type = 1;
    }
    if (area.id == mdata_t::MapId::mountain_pass)
    {
        dungeon_type = 8;
    }
    if (area.id == mdata_t::MapId::puppy_cave)
    {
        dungeon_type = 10;
    }
    if (area.id == mdata_t::MapId::minotaurs_nest)
    {
        dungeon_type = 9;
    }
    if (area.id == mdata_t::MapId::quest)
    {
        if (game_data.executing_immediate_quest_type == 1001)
        {
            map_data.tileset = 300;
            map_data.width = 28 + rnd(6);
            map_data.height = 20 + rnd(6);
            dungeon_type = 6;
        }
        if (game_data.executing_immediate_quest_type == 1009)
        {
            initialize_quest_map_party();
            return none;
        }
        if (game_data.executing_immediate_quest_type == 1006)
        {
            initialize_quest_map_crop();
            return none;
        }
        if (game_data.executing_immediate_quest_type == 1008)
        {
            initialize_quest_map_town();
            return none;
        }
        if (game_data.executing_immediate_quest_type == 1010)
        {
            initialize_quest_map_town();
            return none;
        }
    }

    return dungeon_type;
}

} // namespace



namespace elona
{

int i_at_m68;
int tx_at_m168 = 0;
int ty_at_m168 = 0;
int dir_at_m168 = 0;
int dest_at_m168 = 0;
int dir2_at_m168 = 0;
int tile_pot = 0;
int rdroomnum = 0;
elona_vector1<int> roomexist;
int rdsize = 0;
int rdsecond = 0;
int rdhiddenpath = 0;
int rdpos = 0;
elona_vector1<int> roomwidth;
int cr = 0;
elona_vector1<int> roomheight;
elona_vector1<int> roomx;
elona_vector1<int> roomy;
int roomdoor = 0;
int roomsum = 0;
int rdroomsizemax = 0;
int rdroomsizemin = 0;
int rdroomupstair = 0;
int rdroomdownstair = 0;
int tmp_at_m172;
int rdroomentrance = 0;
elona_vector1<int> rdval;
int rdtunnel = 0;
int rdextraroom = 0;
int _mclass = 0;
int _bold = 0;
int rx = 0;
int rw = 0;
int ry = 0;
int rh = 0;



void map_initialize()
{
    if (rdroomnum >= 30)
    {
        rdroomnum = 30;
    }
    for (int cnt = 0; cnt < 30; ++cnt)
    {
        roomexist(cnt) = 0;
    }
    cell_data.init(map_data.width, map_data.height);
    DIM3(mapsync, map_data.width, map_data.height);
    DIM3(mef, 9, MEF_MAX);
    map_tileset(map_data.tileset);
}



void map_init_cell_object_data()
{
    const int tile_doorclosed2 = 728;
    const int tile_doorclosed3 = 730;
    tile_trap = 234;
    tile_doorclosed = 726;
    tile_doorclosed4 = 733;
    tile_dooropen = 236;
    tile_downstairs = 231;
    tile_upstairs = 232;
    tile_hidden = 0;
    tile_downlocked = 237;
    tile_re = 238;
    tile_plant = 247;
    tile_board = 727;
    tile_votebox = 729;
    tile_townboard = 732;

    cellobjdata = {
        {
            21,
            tile_doorclosed,
        },
        {
            21,
            tile_doorclosed,
        },
        {
            21,
            tile_doorclosed,
        },
        {
            14,
            0,
        },
        {
            14,
            0,
        },
        {
            10,
            tile_upstairs,
        },
        {
            11,
            tile_downstairs,
        },
        {
            21,
            tile_doorclosed2,
        },
        {
            23,
            tile_board,
        },
        {
            31,
            tile_votebox,
        },
        {
            32,
            0,
        },
        {
            21,
            tile_doorclosed3,
        },
        {
            33,
            tile_townboard,
        },
        {
            21,
            tile_doorclosed4,
        },
    };
}



void map_place_chara_on_pet_arena(Character& chara, ArenaCharaType chara_type)
{
    while (true)
    {
        int x = rnd(7) + 5;
        int y = rnd(6) + 6;
        if (chara_type == ArenaCharaType::allies)
        {
            x += 8;
        }
        cxinit = x;
        cyinit = y;
        chara_place(chara);

        if (chara_type == ArenaCharaType::allies)
        {
            if (chara.position.x >= 13 && chara.position.y >= 6 &&
                chara.position.x < 20 && chara.position.y < 12)
            {
                return; // okay.
            }
        }
        else
        {
            if (chara.position.x >= 5 && chara.position.y >= 6 &&
                chara.position.x < 12 && chara.position.y < 12)
            {
                return; // okay.
            }
        }

        // Invalid position, reset the position and retry.
        cell_data.at(chara.position.x, chara.position.y).chara_index_plus_one =
            0;
    }
}



void map_place_player_and_allies()
{
    if (mode == 11)
        return; // during the first initialization of all towns

    camera = 0;
    for (auto&& chara : cdata.player_and_allies())
    {
        if (chara.state() != Character::State::alive)
            continue;

        // Mount
        if (!chara.is_player())
        {
            if (game_data.mount == chara.index)
            {
                cdata[game_data.mount].position = cdata.player().position;
                continue;
            }
        }
        // Arena fighters
        if (game_data.current_map == mdata_t::MapId::pet_arena)
        {
            if (followerin(chara.index) == 1)
            {
                if (camera == 0)
                {
                    camera = chara.index;
                }
                map_place_chara_on_pet_arena(chara, ArenaCharaType::allies);
                continue;
            }
        }
        // Pets staying in the current map (home, ranch, shop, etc.)
        if (chara.current_map == game_data.current_map)
        {
            if (!chara.is_player())
            {
                cxinit = chara.initial_position.x;
                cyinit = chara.initial_position.y;
                chara_place(chara);
                continue;
            }
        }

        // PC and pets following you
        place_chara_on_entrance(chara, game_data.entrance_type);
    }
}



void map_replace_random_tiles(int tile_id, int density)
{
    const auto n = map_data.width * map_data.height * density / 100 + 1;
    for (int i = 0; i < n; ++i)
    {
        const auto x = rnd(map_data.width);
        const auto y = rnd(map_data.height);
        cell_data.at(x, y).chip_id_actual = tile_id;
    }
}



void map_nextdir1(int x, int y)
{
    if (tx_at_m168 >= x - 4 && tx_at_m168 <= x + 4)
    {
        if (ty_at_m168 >= y - 4 && ty_at_m168 <= y + 4)
        {
            if (tx_at_m168 < x)
            {
                dir_at_m168 = 2;
                if (ty_at_m168 > y)
                {
                    dest_at_m168 = 3;
                }
                else
                {
                    dest_at_m168 = 0;
                }
            }
            if (tx_at_m168 > x)
            {
                dir_at_m168 = 1;
                if (ty_at_m168 > y)
                {
                    dest_at_m168 = 3;
                }
                else
                {
                    dest_at_m168 = 0;
                }
            }
            if (ty_at_m168 < y)
            {
                dir_at_m168 = 0;
                if (tx_at_m168 > x)
                {
                    dest_at_m168 = 1;
                }
                else
                {
                    dest_at_m168 = 2;
                }
            }
            if (ty_at_m168 > y)
            {
                dir_at_m168 = 3;
                if (tx_at_m168 > x)
                {
                    dest_at_m168 = 1;
                }
                else
                {
                    dest_at_m168 = 2;
                }
            }
            return;
        }
    }
    if (dir_at_m168 == 1 || dir_at_m168 == 2)
    {
        if (ty_at_m168 > y)
        {
            dir_at_m168 = 3;
        }
        else
        {
            dir_at_m168 = 0;
        }
        if (tx_at_m168 > x)
        {
            dest_at_m168 = 1;
        }
        else
        {
            dest_at_m168 = 2;
        }
        return;
    }
    else
    {
        if (tx_at_m168 > x)
        {
            dir_at_m168 = 1;
        }
        else
        {
            dir_at_m168 = 2;
        }
        if (ty_at_m168 > y)
        {
            dest_at_m168 = 3;
        }
        else
        {
            dest_at_m168 = 0;
        }
        return;
    }
}



void map_nextdir2(int x, int y)
{
    int p_at_m168 = 0;
    if (dir2_at_m168 != -1)
    {
        if (dir2_at_m168 == 1)
        {
            if (can_dig_cell(tx_at_m168 - 1, ty_at_m168))
            {
                if (tx_at_m168 == x)
                {
                    p_at_m168 = dir2_at_m168;
                    dir2_at_m168 = dir_at_m168;
                    dir_at_m168 = p_at_m168;
                }
                else
                {
                    dir_at_m168 = dir2_at_m168;
                    dir2_at_m168 = -1;
                }
            }
        }
        if (dir2_at_m168 == 2)
        {
            if (can_dig_cell(tx_at_m168 + 1, ty_at_m168))
            {
                if (tx_at_m168 == x)
                {
                    p_at_m168 = dir2_at_m168;
                    dir2_at_m168 = dir_at_m168;
                    dir_at_m168 = p_at_m168;
                }
                else
                {
                    dir_at_m168 = dir2_at_m168;
                    dir2_at_m168 = -1;
                }
            }
        }
        if (dir2_at_m168 == 3)
        {
            if (can_dig_cell(tx_at_m168, ty_at_m168 - 1))
            {
                if (ty_at_m168 == y)
                {
                    p_at_m168 = dir2_at_m168;
                    dir2_at_m168 = dir_at_m168;
                    dir_at_m168 = p_at_m168;
                }
                else
                {
                    dir_at_m168 = dir2_at_m168;
                    dir2_at_m168 = -1;
                }
            }
        }
        if (dir2_at_m168 == 0)
        {
            if (can_dig_cell(tx_at_m168, ty_at_m168 + 1))
            {
                if (ty_at_m168 == y)
                {
                    p_at_m168 = dir2_at_m168;
                    dir2_at_m168 = dir_at_m168;
                    dir_at_m168 = p_at_m168;
                }
                else
                {
                    dir_at_m168 = dir2_at_m168;
                    dir2_at_m168 = -1;
                }
            }
        }
    }
    if (dir_at_m168 == 1 || dir_at_m168 == 2)
    {
        if (tx_at_m168 == x)
        {
            if (ty_at_m168 > y)
            {
                if (can_dig_cell(tx_at_m168, ty_at_m168 - 1))
                {
                    dir2_at_m168 = dir_at_m168;
                    dir_at_m168 = 3;
                }
            }
            if (ty_at_m168 < y)
            {
                if (can_dig_cell(tx_at_m168, ty_at_m168 + 1))
                {
                    dir2_at_m168 = dir_at_m168;
                    dir_at_m168 = 0;
                }
            }
        }
        return;
    }
    else
    {
        if (ty_at_m168 == y)
        {
            if (tx_at_m168 > x)
            {
                if (can_dig_cell(tx_at_m168 - 1, ty_at_m168))
                {
                    dir2_at_m168 = dir_at_m168;
                    dir_at_m168 = 1;
                }
            }
            if (tx_at_m168 < x)
            {
                if (can_dig_cell(tx_at_m168 + 1, ty_at_m168))
                {
                    dir2_at_m168 = dir_at_m168;
                    dir_at_m168 = 2;
                }
            }
        }
        return;
    }
}



int map_digtoentrance1(int x1, int y1, int x2, int y2)
{
    int f_at_m168 = 0;
    int dx_at_m168 = 0;
    int dy_at_m168 = 0;
    tx_at_m168 = x1;
    ty_at_m168 = y1;
    dest_at_m168 = -1;
    f_at_m168 = 0;
    dir2_at_m168 = -1;
    map_nextdir1(x2, y2);
    for (int cnt = 0; cnt < 2000; ++cnt)
    {
        if (tx_at_m168 == x2)
        {
            if (ty_at_m168 + 1 == y2 || ty_at_m168 - 1 == y2)
            {
                f_at_m168 = 1;
                break;
            }
        }
        if (ty_at_m168 == y2)
        {
            if (tx_at_m168 + 1 == x2 || tx_at_m168 - 1 == x2)
            {
                f_at_m168 = 1;
                break;
            }
        }
        map_nextdir2(x2, y2);
        dx_at_m168 = tx_at_m168;
        dy_at_m168 = ty_at_m168;
        if (dir_at_m168 == 1)
        {
            --dx_at_m168;
        }
        if (dir_at_m168 == 2)
        {
            ++dx_at_m168;
        }
        if (dir_at_m168 == 3)
        {
            --dy_at_m168;
        }
        if (dir_at_m168 == 0)
        {
            ++dy_at_m168;
        }
        if (can_dig_cell(dx_at_m168, dy_at_m168))
        {
            tx_at_m168 = dx_at_m168;
            ty_at_m168 = dy_at_m168;
            cell_data.at(dx_at_m168, dy_at_m168).chip_id_actual = 100;
            if (rnd(200) < rdhiddenpath)
            {
                cell_data.at(dx_at_m168, dy_at_m168).chip_id_actual = 4;
                cell_featset(dx_at_m168, dy_at_m168, 0, 22);
            }
        }
        else
        {
            if (dest_at_m168 == 1)
            {
                if (can_dig_cell(tx_at_m168 - 1, ty_at_m168))
                {
                    dir_at_m168 = 1;
                    dest_at_m168 = -2;
                }
            }
            if (dest_at_m168 == 2)
            {
                if (can_dig_cell(tx_at_m168 + 1, ty_at_m168))
                {
                    dir_at_m168 = 2;
                    dest_at_m168 = -2;
                }
            }
            if (dest_at_m168 == 3)
            {
                if (can_dig_cell(tx_at_m168, ty_at_m168 - 1))
                {
                    dir_at_m168 = 3;
                    dest_at_m168 = -2;
                }
            }
            if (dest_at_m168 == 0)
            {
                if (can_dig_cell(tx_at_m168, ty_at_m168 + 1))
                {
                    dir_at_m168 = 0;
                    dest_at_m168 = -2;
                }
            }
            if (dest_at_m168 == -2)
            {
                dest_at_m168 = -1;
                continue;
            }
            map_nextdir1(x2, y2);
        }
    }
    return f_at_m168;
}



void map_set_fog()
{
    for_each_cell([&](int x, int y) {
        cell_data.at(x, y).chip_id_memory =
            tile_fog + (rnd(tile_fog(2)) == 0) * rnd(tile_fog(1));
    });
}



int map_createroom(int type)
{
    int roompos = 0;
    int roomwall = 0;
    if (roomsum >= 30)
    {
        return 0;
    }
    if (type == 0)
    {
        roompos = 0;
        roomwall = 0;
        roomdoor = 0;
    }
    if (type == 1)
    {
        roompos = 1;
        roomwall = 1;
        roomdoor = 0;
    }
    if (type == 2)
    {
        roompos = 2;
        roomwall = 1;
        roomdoor = 1;
    }
    if (type == 3)
    {
        roompos = 3;
        roomwall = 2;
        roomdoor = 3;
    }
    if (type == 4)
    {
        roompos = 4;
        roomwall = 3;
        roomdoor = 0;
    }
    cr = roomsum;
    f = 0;
    for (int cnt = 0; cnt < 100; ++cnt)
    {
        if (roompos == 0)
        {
            roomwidth(cr) = rnd(rdroomsizemax) + rdroomsizemin;
            roomheight(cr) = rnd(rdroomsizemax) + rdroomsizemin;
            roomx(cr) = rnd(map_data.width) + 2;
            roomy(cr) = rnd(map_data.height) + 2;
        }
        if (roompos == 1)
        {
            roomwidth(cr) = (rnd(rdroomsizemax) + rdroomsizemin) / 3 * 3 + 5;
            roomheight(cr) = (rnd(rdroomsizemax) + rdroomsizemin) / 3 * 3 + 5;
            roomx(cr) = rnd(map_data.width) / 3 * 3 + 2;
            roomy(cr) = rnd(map_data.height) / 3 * 3 + 2;
        }
        if (roompos == 2)
        {
            rdpos = rnd(4);
            if (rdpos == 3 || rdpos == 0)
            {
                roomx(cr) = rnd(map_data.width - rdroomsizemin * 3 / 2 - 2) +
                    rdroomsizemin / 2;
                roomwidth(cr) = rnd(rdroomsizemin) + rdroomsizemin / 2 + 3;
                roomheight(cr) = rdroomsizemin;
                if (rdpos == 3)
                {
                    roomy(cr) = 0;
                }
                else
                {
                    roomy(cr) = map_data.height - roomheight(cr);
                }
            }
            if (rdpos == 1 || rdpos == 2)
            {
                roomy(cr) = rnd(map_data.height - rdroomsizemin * 3 / 2 - 2) +
                    rdroomsizemin / 2;
                roomwidth(cr) = rdroomsizemin;
                roomheight(cr) = rnd(rdroomsizemin) + rdroomsizemin / 2 + 3;
                if (rdpos == 1)
                {
                    roomx(cr) = 0;
                }
                else
                {
                    roomx(cr) = map_data.width - roomwidth(cr);
                }
            }
        }
        if (roompos == 3)
        {
            roomwidth(cr) = 3;
            roomheight(cr) = 3;
            x = map_data.width - rdroomsizemin * 2 - roomwidth(cr) - 2 + 1;
            if (x < 1)
            {
                break;
            }
            y = map_data.height - rdroomsizemin * 2 - roomheight(cr) - 2 + 1;
            if (y < 1)
            {
                break;
            }
            roomx(cr) = rdroomsizemin + 1 + rnd(x(0));
            roomy(cr) = rdroomsizemin + 1 + rnd(y(0));
        }
        if (roompos == 4)
        {
            roomwidth(cr) = rnd(rdroomsizemax) + rdroomsizemin;
            roomheight(cr) = rnd(rdroomsizemax) + rdroomsizemin;
            roomx(cr) = rnd(map_data.width - rdroomsizemax - 8) + 3;
            roomy(cr) = rnd(map_data.height - rdroomsizemax - 8) + 3;
        }
        x = roomx(cr) + roomwidth(cr) - 1;
        y = roomy(cr) + roomheight(cr) - 1;
        if (x >= map_data.width)
        {
            continue;
        }
        if (y >= map_data.height)
        {
            continue;
        }
        if (roompos == 1)
        {
            if (x + 1 >= map_data.width)
            {
                continue;
            }
            if (y + 1 >= map_data.height)
            {
                continue;
            }
        }
        if (roompos == 0)
        {
            if (cell_data.at(x, y).chip_id_actual != 3)
            {
                continue;
            }
        }
        bool do_continue{};
        for (p = 0; p < roomsum; ++p)
        {
            if (p == cr)
            {
                continue;
            }
            x1 = roomx(p) - 1 - roomx(cr);
            x2 = -roomwidth(p) - 2 < x1 && x1 < roomwidth(cr);
            y1 = roomy(p) - 1 - roomy(cr);
            y2 = -roomheight(p) - 2 < y1 && y1 < roomheight(cr);
            if (x2 && y2)
            {
                do_continue = true;
                break;
            }
        }
        if (do_continue)
        {
            continue;
        }
        ++roomsum;
        f = 1;
        break;
    }
    if (f == 0)
    {
        return 0;
    }
    if (rnd(2) == 0)
    {
        tile(1) = 1 + rnd(2);
    }
    else
    {
        tile(1) = 0;
    }
    if (rnd(2) == 0)
    {
        tile(2) = 1 + rnd(2);
    }
    else
    {
        tile(2) = 0;
    }
    for (int cnt = 0, cnt_end = (roomheight(cr)); cnt < cnt_end; ++cnt)
    {
        y = roomy(cr) + cnt;
        int cnt2 = cnt;
        for (int cnt = 0, cnt_end = (roomwidth(cr)); cnt < cnt_end; ++cnt)
        {
            x = roomx(cr) + cnt;
            tile = 3;
            if (roomwall != 0)
            {
                if (cnt == 0 || cnt2 == 0 || cnt == roomwidth(cr) - 1 ||
                    cnt2 == roomheight(cr) - 1)
                {
                    if (roomwall == 1)
                    {
                        tile = 1;
                    }
                    if (roomwall == 2)
                    {
                        tile = 4;
                    }
                    if (roomwall == 3)
                    {
                        tile = 3;
                        if (tile(1) == 1)
                        {
                            if (cnt == 0)
                            {
                                tile = 1;
                            }
                        }
                        if (tile(2) == 1)
                        {
                            if (cnt2 == 0)
                            {
                                if (cnt != 0 && cnt != roomwidth(cr) - 1)
                                {
                                    if (rnd(3))
                                    {
                                        flt();
                                        p(0) = 296;
                                        p(1) = 300;
                                        p(2) = 312;
                                        p(3) = 604;
                                        itemcreate_map_inv(
                                            p(rnd(4)), x, y + 1, 0);
                                    }
                                    else if (cnt % 2 == 1)
                                    {
                                        flt();
                                        itemcreate_map_inv(584, x, y + 1, 0);
                                    }
                                }
                                tile = 1;
                            }
                        }
                        if (tile(1) == 2)
                        {
                            if (cnt == roomwidth(cr) - 1)
                            {
                                tile = 1;
                            }
                        }
                        if (tile(2) == 2)
                        {
                            if (cnt2 == roomheight(cr) - 1)
                            {
                                if (rnd(3))
                                {
                                    flt();
                                    p(0) = 296;
                                    p(1) = 300;
                                    p(2) = 312;
                                    p(3) = 604;
                                    itemcreate_map_inv(p(rnd(4)), x, y + 1, 0);
                                }
                                else if (cnt % 2 == 1)
                                {
                                    flt();
                                    itemcreate_map_inv(584, x, y + 1, 0);
                                }
                                tile = 1;
                            }
                        }
                    }
                }
            }
            cell_data.at(x, y).chip_id_actual = tile;
        }
    }
    if (roomdoor == 1)
    {
        create_room_door(
            static_cast<Direction>(rdpos),
            roomdoor != 3,
            roomx(cr),
            roomy(cr),
            roomwidth(cr),
            roomheight(cr));
    }
    if (roomdoor == 2 || roomdoor == 3)
    {
        for (int cnt = 0; cnt < 4; ++cnt)
        {
            rdpos = cnt;
            create_room_door(
                static_cast<Direction>(rdpos),
                roomdoor != 3,
                roomx(cr),
                roomy(cr),
                roomwidth(cr),
                roomheight(cr));
        }
    }
    return 1;
}



void map_place_upstairs(int x, int y)
{
    cell_featset(x, y, tile_upstairs, 10);
    map_data.stair_up_pos = y * 1000 + x;
    rdroomupstair = cr;
}



void map_place_downstairs(int x, int y)
{
    if (area_data[game_data.current_map].deepest_level <=
        game_data.current_dungeon_level)
        return;

    cell_featset(x, y, tile_downstairs, 11);
    map_data.stair_down_pos = y * 1000 + x;
    rdroomdownstair = cr;
}



int map_connectroom()
{
    cr = 0;
    while (cr < roomsum - 1)
    {
        bool ok = false;
        for (int i = 0, n = rnd(rdroomentrance + 1) + 1; i < n; ++i)
        {
            for (int j = cr; j < cr + 2; ++j)
            {
                while (1)
                {
                    dir = rnd(4);
                    x = dirxy(0, dir);
                    y = dirxy(1, dir);
                    if (dir == 1)
                    {
                        dx = roomx(j);
                        dy = roomy(j) + rnd(roomheight(j) - 2) + 1;
                    }
                    if (dir == 2)
                    {
                        dx = roomx(j) + roomwidth(j) - 1;
                        dy = roomy(j) + rnd(roomheight(j) - 2) + 1;
                    }
                    if (dir == 3)
                    {
                        dx = roomx(j) + rnd(roomwidth(j) - 2) + 1;
                        dy = roomy(j);
                    }
                    if (dir == 0)
                    {
                        dx = roomx(j) + rnd(roomwidth(j) - 2) + 1;
                        dy = roomy(j) + roomheight(j) - 1;
                    }
                    if (x != 0)
                    {
                        if (cell_data.at(dx, dy - 1).chip_id_actual == 3 ||
                            cell_data.at(dx, dy + 1).chip_id_actual == 3)
                        {
                            continue;
                        }
                    }
                    if (y != 0)
                    {
                        if (cell_data.at(dx - 1, dy).chip_id_actual == 3 ||
                            cell_data.at(dx + 1, dy).chip_id_actual == 3)
                        {
                            continue;
                        }
                    }
                    break;
                }
                cell_data.at(dx, dy).chip_id_actual = 3;
                roomexist(j) = 1;
                dx += x;
                dy += y;
                cell_data.at(dx, dy).chip_id_actual = 100;
                if (j == cr)
                {
                    tx = dx;
                    ty = dy;
                }
            }
            ok = map_digtoentrance1(tx, ty, dx, dy);
        }
        if (!ok)
        {
            roomexist(cr) = 0;
            roomexist(cr + 1) = 0;
            return 0;
        }
        ++cr;
    }
    return 1;
}



void map_generate_debug_map()
{
    map_data.width = 50;
    map_data.height = 50;
    map_data.atlas_number = 1;
    map_data.turn_cost = 10000;
    map_data.max_crowd_density = map_data.width * map_data.height / 100;
    map_data.tileset = 3;
    map_data.user_map_flag = 0;
    map_data.type = static_cast<int>(mdata_t::MapType::shelter);
    map_data.refresh_type = 1;
    map_initialize();

    for_each_cell([&](int x, int y) { cell_data.at(x, y).chip_id_actual = 3; });

    mdatan(0) = i18n::s.get_enum_property("core.map.unique", "name", 499);
    convert_tiles_at_random();

    mapstartx = 25;
    mapstarty = 25;
    map_place_player_and_allies();
}



void generate_random_nefia()
{
    int rdtype = 0;
    int rdmonsterhouse = 0;
    int rdcreaturepack = 0;
    int rdy3 = 0;
    int rdx3 = 0;
    int mobdensity = 0;
    int itemdensity = 0;

    while (1)
    {
        randomize();
        ++rdtry;
        map_data.user_map_flag = 0;
        map_data.width = 34 + rnd(15);
        map_data.height = 22 + rnd(15);
        map_data.max_crowd_density = map_data.width * map_data.height / 100;
        roomsum = 0;
        rdroomnum = map_data.width * map_data.height / 70;
        rdroomsizemin = 3;
        rdroomsizemax = 4;
        rdroomentrance = 1;
        rdhiddenpath = 20;
        rdval(2) = 2;
        rdtunnel = map_data.width * map_data.height;
        rdextraroom = 10;

        auto rdtype_opt = _setup_map_generation_parameters();
        if (!rdtype_opt)
        {
            // Quest maps can have special generation routines.
            return;
        }

        rdtype = *rdtype_opt;

        int stat = 1;
        if (rdtype == 2)
        {
            initialize_random_nefia_rdtype2();
        }
        if (rdtype == 1)
        {
            stat = initialize_random_nefia_rdtype1();
        }
        if (rdtype == 4)
        {
            initialize_random_nefia_rdtype4();
        }
        if (rdtype == 5)
        {
            initialize_random_nefia_rdtype5();
        }
        if (rdtype == 3)
        {
            initialize_random_nefia_rdtype3();
        }
        if (rdtype == 6)
        {
            map_data.indoors_flag = 2;
            initialize_random_nefia_rdtype6();
            return;
        }
        if (rdtype == 8)
        {
            initialize_random_nefia_rdtype8();
        }
        if (rdtype == 10)
        {
            _mclass = 5 + rnd(4);
            _bold = 2;
            initialize_random_nefia_rdtype10();
        }
        if (rdtype == 9)
        {
            _mclass = 12;
            _bold = 2;
            initialize_random_nefia_rdtype9();
        }
        if (stat != 0)
        {
            break;
        }
    }
    convert_tiles_at_random();
    map_place_player_and_allies();
    rdmonsterhouse = 0;
    rdcreaturepack = 0;
    for (int cnt = 0, cnt_end = (roomsum); cnt < cnt_end; ++cnt)
    {
        rx = roomx(cnt) + 1;
        rw = roomwidth(cnt) - 2;
        ry = roomy(cnt) + 1;
        rh = roomheight(cnt) - 2;
        rdsize = rw * rh;
        for (int cnt = 0, cnt_end = (rnd(rdsize / 8 + 2)); cnt < cnt_end; ++cnt)
        {
            if (rnd(2) == 0)
            {
                flt(calcobjlv(game_data.current_dungeon_level),
                    calcfixlv(Quality::bad));
                flttypemajor = fltsetdungeon();
                itemcreate_map_inv(0, rnd(rw) + rx, rnd(rh) + ry, 0);
            }
            map_set_chara_generation_filter();
            if (const auto chara =
                    chara_create(-1, 0, rnd(rw) + rx, rnd(rh) + ry))
            {
                if (game_data.current_dungeon_level > 3)
                {
                    if (creaturepack != 0)
                    {
                        if (rnd(rdcreaturepack * 5 + 5) == 0)
                        {
                            ++rdcreaturepack;
                            for (int cnt = 0, cnt_end = (10 + rnd(20));
                                 cnt < cnt_end;
                                 ++cnt)
                            {
                                flt(chara->level, calcfixlv(Quality::bad));
                                flttypemajor = creaturepack;
                                chara_create(-1, 0, rnd(rw) + rx, rnd(rh) + ry);
                            }
                            break;
                        }
                    }
                }
            }
        }
        if (cnt == rdroomdownstair)
        {
            continue;
        }
        if (cnt == rdroomupstair)
        {
            continue;
        }
        if (rdmonsterhouse == 0 || rdtype == 2)
        {
            if (rnd(8) == 0)
            {
                if (rw * rh < 40)
                {
                    ++rdmonsterhouse;
                    for (int cnt = ry, cnt_end = cnt + (rh); cnt < cnt_end;
                         ++cnt)
                    {
                        rdy3 = cnt;
                        for (int cnt = rx, cnt_end = cnt + (rw); cnt < cnt_end;
                             ++cnt)
                        {
                            rdx3 = cnt;
                            map_set_chara_generation_filter();
                            chara_create(-1, 0, rdx3, rdy3);
                        }
                    }
                    if (rdtype != 2)
                    {
                        for (int cnt = 0, cnt_end = (rnd(3) + 1); cnt < cnt_end;
                             ++cnt)
                        {
                            flt();
                            flttypemajor = 72000;
                            itemcreate_map_inv(
                                0, rnd(rw) + rx, rnd(rh) + ry, 0);
                        }
                    }
                }
            }
        }
    }
    mobdensity = map_data.max_crowd_density / 4;
    itemdensity = map_data.max_crowd_density / 4;
    if (rdtype == 3)
    {
        flt();
        flttypemajor = choice(fsetwear);
        fixlv = Quality::miracle;
        itemcreate_map_inv(0, -1, -1, 0);
        mobdensity = map_data.max_crowd_density / 2;
        itemdensity = map_data.max_crowd_density / 3;
    }
    if (rdtype == 8)
    {
        mobdensity = map_data.max_crowd_density / 4;
        itemdensity = map_data.max_crowd_density / 10;
    }
    if (rdtype == 10)
    {
        mobdensity = map_data.max_crowd_density / 3;
        itemdensity = map_data.max_crowd_density / 6;
    }
    if (rdtype == 9)
    {
        mobdensity = map_data.max_crowd_density / 3;
        itemdensity = map_data.max_crowd_density / 10;
    }
    for (int cnt = 0, cnt_end = (mobdensity); cnt < cnt_end; ++cnt)
    {
        map_set_chara_generation_filter();
        chara_create(-1, 0, -3, 0);
    }
    for (int cnt = 0, cnt_end = (itemdensity); cnt < cnt_end; ++cnt)
    {
        flt(calcobjlv(game_data.current_dungeon_level),
            calcfixlv(Quality::bad));
        flttypemajor = fltsetdungeon();
        itemcreate_map_inv(0, -1, -1, 0);
    }
    for (int cnt = 0, cnt_end = (rnd(map_data.width * map_data.height / 80));
         cnt < cnt_end;
         ++cnt)
    {
        place_trap();
    }
    if (rnd(5) == 0)
    {
        p = rnd(map_data.width * map_data.height / 40);
        if (rnd(5) == 0)
        {
            p = rnd(map_data.width * map_data.height / 5);
        }
        for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
        {
            place_web(game_data.current_dungeon_level * 10 + 100);
        }
    }
    if (rnd(4) == 0)
    {
        p = clamp(rnd(map_data.width * map_data.height / 500 + 1) + 1, 3, 15);
        for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
        {
            place_barrel();
        }
    }
    if (map_data.refresh_type == 1)
    {
        if (rnd(15 + game_data.quest_flags.kill_count_of_little_sister * 2) ==
            0)
        {
            flt();
            chara_create(-1, 318, -3, 0);
        }
    }
    if (area_data[game_data.current_map].id == mdata_t::MapId::lesimas)
    {
        if (game_data.current_dungeon_level == 3 ||
            game_data.current_dungeon_level == 17 ||
            game_data.current_dungeon_level == 25 ||
            game_data.current_dungeon_level == 44)
        {
            x = map_data.stair_down_pos % 1000;
            y = map_data.stair_down_pos / 1000;
            cell_featset(x, y, tile_downlocked, 11);
        }
    }
}



void initialize_random_nefia_rdtype6()
{
    map_initialize();
    for (int cnt = 0, cnt_end = (map_data.height); cnt < cnt_end; ++cnt)
    {
        p = cnt;
        for (int cnt = 0, cnt_end = (map_data.width); cnt < cnt_end; ++cnt)
        {
            cell_data.at(cnt, p).chip_id_actual = 3;
        }
    }
    for (int cnt = 0, cnt_end = (rnd(map_data.width * map_data.height / 30));
         cnt < cnt_end;
         ++cnt)
    {
        x = rnd(map_data.width);
        y = rnd(map_data.height);
        cell_data.at(x, y).chip_id_actual = 1;
    }
    if (game_data.previous_map2 == 33)
    {
        tile_room(0) = 45;
        tile_room(1) = 6;
    }
    convert_tiles_at_random();
    map_place_player_and_allies();
    map_data.max_crowd_density = 0;
    for (int cnt = 0, cnt_end = (10 + rnd(6)); cnt < cnt_end; ++cnt)
    {
        map_set_chara_generation_filter();
        if (const auto chara = chara_create(-1, 0, -3, 0))
        {
            chara->relationship = -3;
            chara->original_relationship = -3;
        }
    }
    for (int cnt = 0, cnt_end = (10 + rnd(10)); cnt < cnt_end; ++cnt)
    {
        flt();
        flttypemajor = 80000;
        if (const auto item = itemcreate_map_inv(0, -1, -1, 0))
        {
            item->own_state = OwnState::town;
        }
    }
}



int initialize_quest_map_crop()
{
    game_data.left_minutes_of_executing_quest = 120;
    game_data.executing_immediate_quest_time_left_display_period = 9999;
    map_data.indoors_flag = 2;
    map_data.tileset = 4;
    map_data.width = 58 + rnd(16);
    map_data.height = 50 + rnd(16);
    map_initialize();
    for (int cnt = 0, cnt_end = (map_data.height); cnt < cnt_end; ++cnt)
    {
        p = cnt;
        for (int cnt = 0, cnt_end = (map_data.width); cnt < cnt_end; ++cnt)
        {
            cell_data.at(cnt, p).chip_id_actual = tile_default +
                (rnd(tile_default(2)) == 0) * rnd(tile_default(1));
        }
    }
    mdatan(0) = i18n::s.get("core.map.quest.field");
    map_replace_random_tiles(9, 10);
    map_replace_random_tiles(10, 10);
    map_replace_random_tiles(0, 30);
    map_replace_random_tiles(1, 4);
    map_replace_random_tiles(4, 2);
    map_replace_random_tiles(3, 2);
    map_replace_random_tiles(4, 2);
    map_replace_random_tiles(5, 2);
    for (int cnt = 0; cnt < 30; ++cnt)
    {
        int w = rnd(5) + 5;
        int h = rnd(4) + 4;
        dx = rnd(map_data.width);
        dy = rnd(map_data.height);
        if (rnd(2))
        {
            tile = 30;
        }
        else
        {
            tile = 31;
        }
        size = clamp(
            dist(dx, dy, map_data.width / 2, map_data.height / 2) / 8, 0, 8);
        crop = choice(isetcrop);
        for (int cnt = dy, cnt_end = cnt + (h); cnt < cnt_end; ++cnt)
        {
            y = cnt;
            if (y >= map_data.height)
            {
                break;
            }
            for (int cnt = dx, cnt_end = cnt + (w); cnt < cnt_end; ++cnt)
            {
                x = cnt;
                if (x >= map_data.width)
                {
                    break;
                }
                cell_data.at(x, y).chip_id_actual = tile;
                if (rnd(10) != 0 ||
                    !cell_data.at(x, y).item_info_actual.is_empty())
                {
                    continue;
                }
                int item_id;
                if (rnd(4))
                {
                    item_id = crop;
                }
                else
                {
                    item_id = choice(isetcrop);
                }
                flt();
                if (const auto item = itemcreate_map_inv(item_id, x, y, 0))
                {
                    item->own_state = OwnState::crop;
                    p = clamp(size + rnd(rnd(4) + 1), 0, 9);
                    item->weight = item->weight * (80 + p * p * 100) / 100;
                    item->subname = p;
                }
            }
        }
    }
    game_data.entrance_type = 7;
    mapstartx = rnd(map_data.width / 3) + map_data.width / 3;
    mapstarty = rnd(map_data.height / 3) + map_data.height / 3;
    map_place_player_and_allies();
    flt();
    if (const auto item = itemcreate_map_inv(
            560, cdata.player().position.x + 1, cdata.player().position.y, 0))
    {
        item->own_state = OwnState::town;
    }
    for (int cnt = 0, cnt_end = (70 + rnd(20)); cnt < cnt_end; ++cnt)
    {
        x = rnd(map_data.width);
        y = rnd(map_data.height);
        if (cell_data.at(x, y).chip_id_actual != 30 &&
            cell_data.at(x, y).chip_id_actual != 31 &&
            cell_data.at(x, y).item_info_actual.is_empty())
        {
            if (rnd(8))
            {
                flt();
                flttypemajor = 80000;
                if (const auto item = itemcreate_map_inv(0, x, y, 0))
                {
                    item->own_state = OwnState::town;
                }
            }
            else
            {
                cell_featset(x, y, tile_pot, 30);
            }
        }
    }
    map_data.max_crowd_density = 15;
    for (int cnt = 0; cnt < 30; ++cnt)
    {
        map_set_chara_generation_filter();
        chara_create(-1, 0, -3, 0);
    }
    return 1;
}



int initialize_random_nefia_rdtype1()
{
    map_initialize();
    int stat = map_createroom(1);
    if (stat == 0)
    {
        return 0;
    }
    place_upstairs_at_random_pos(
        roomx(cr), roomy(cr), roomwidth(cr), roomheight(cr));
    {
        int stat = map_createroom(1);
        if (stat == 0)
        {
            return 0;
        }
    }
    place_downstairs_at_random_pos(
        roomx(cr), roomy(cr), roomwidth(cr), roomheight(cr));
    for (int cnt = 0, cnt_end = (rdroomnum); cnt < cnt_end; ++cnt)
    {
        map_createroom(1);
    }
    {
        int stat = map_connectroom();
        if (stat == 0)
        {
            return 0;
        }
    }
    make_door();
    return 1;
}



int initialize_random_nefia_rdtype4()
{
    rdroomsizemin = 8;
    map_initialize();
    p = rdroomsizemin - 1;
    for (int cnt = 0, cnt_end = (map_data.height); cnt < cnt_end; ++cnt)
    {
        y = cnt;
        for (int cnt = 0, cnt_end = (map_data.width); cnt < cnt_end; ++cnt)
        {
            x = cnt;
            cell_data.at(x, y).chip_id_actual = 1;
            if (x > p && y > p && x + 1 < map_data.width - p &&
                y + 1 < map_data.height - p)
            {
                cell_data.at(x, y).chip_id_actual = 100;
            }
        }
    }
    int stat = map_createroom(2);
    if (stat == 0)
    {
        return 0;
    }
    place_upstairs_at_random_pos(
        roomx(cr), roomy(cr), roomwidth(cr), roomheight(cr));
    {
        int stat = map_createroom(2);
        if (stat == 0)
        {
            return 0;
        }
    }
    place_downstairs_at_random_pos(
        roomx(cr), roomy(cr), roomwidth(cr), roomheight(cr));
    for (int cnt = 0, cnt_end = (rdroomnum); cnt < cnt_end; ++cnt)
    {
        map_createroom(2);
    }
    if (rnd(2) == 0)
    {
        for (int cnt = 0, cnt_end = (rdroomnum / 4 + 1); cnt < cnt_end; ++cnt)
        {
            map_createroom(3);
        }
    }
    else
    {
        p = rdroomsizemin + 1 + rnd(3);
        for (int cnt = 0, cnt_end = (map_data.height - p * 2); cnt < cnt_end;
             ++cnt)
        {
            y = p + cnt;
            for (int cnt = 0, cnt_end = (map_data.width - p * 2); cnt < cnt_end;
                 ++cnt)
            {
                x = p + cnt;
                cell_data.at(x, y).chip_id_actual = 1;
            }
        }
    }
    return 1;
}



int initialize_random_nefia_rdtype5()
{
    rdroomsizemin = 8;
    map_data.width = 48 + rnd(20);
    map_data.height = 22;
    map_data.max_crowd_density = map_data.width * map_data.height / 20;
    map_initialize();
    p = rdroomsizemin - 1;
    for (int cnt = 0, cnt_end = (map_data.height); cnt < cnt_end; ++cnt)
    {
        y = cnt;
        for (int cnt = 0, cnt_end = (map_data.width); cnt < cnt_end; ++cnt)
        {
            x = cnt;
            cell_data.at(x, y).chip_id_actual = 1;
            if (x > p && y > p && x + 1 < map_data.width - p &&
                y + 1 < map_data.height - p)
            {
                cell_data.at(x, y).chip_id_actual = 100;
            }
        }
    }
    int stat = map_createroom(2);
    if (stat == 0)
    {
        return 0;
    }
    place_upstairs_at_random_pos(
        roomx(cr), roomy(cr), roomwidth(cr), roomheight(cr));
    {
        int stat = map_createroom(2);
        if (stat == 0)
        {
            return 0;
        }
    }
    place_downstairs_at_random_pos(
        roomx(cr), roomy(cr), roomwidth(cr), roomheight(cr));
    for (int cnt = 0, cnt_end = (rdroomnum); cnt < cnt_end; ++cnt)
    {
        map_createroom(2);
    }
    if (rnd(2) == 0)
    {
        for (int cnt = 0, cnt_end = (rdroomnum / 4 + 1); cnt < cnt_end; ++cnt)
        {
            map_createroom(3);
        }
    }
    else
    {
        p = rdroomsizemin + 1 + rnd(3);
        for (int cnt = 0, cnt_end = (map_data.height - p * 2); cnt < cnt_end;
             ++cnt)
        {
            y = p + cnt;
            for (int cnt = 0, cnt_end = (map_data.width - p * 2); cnt < cnt_end;
                 ++cnt)
            {
                x = p + cnt;
                cell_data.at(x, y).chip_id_actual = 1;
            }
        }
    }
    return 1;
}



int initialize_random_nefia_rdtype2()
{
    rdroomsizemax = 3;
    map_initialize();
    dx = map_data.width / 2;
    dy = map_data.height / 2;
    cell_data.at(dx, dy).chip_id_actual = 3;
    p = 0;
    for (int cnt = 0, cnt_end = (rdtunnel); cnt < cnt_end; ++cnt)
    {
        if (rnd(rdval(2)) == 0)
        {
            p = rnd(4);
        }
        if (p == 2)
        {
            ++dx;
            if (dx > map_data.width - 2)
            {
                p = 0;
                dx = map_data.width - 2;
            }
        }
        if (p == 1)
        {
            --dx;
            if (dx < 1)
            {
                p = 3;
                dx = 1;
            }
        }
        if (p == 0)
        {
            ++dy;
            if (dy > map_data.height - 2)
            {
                p = 1;
                dy = map_data.height - 2;
            }
        }
        if (p == 3)
        {
            --dy;
            if (dy < 1)
            {
                p = 2;
                dy = 1;
            }
        }
        cell_data.at(dx, dy).chip_id_actual = 3;
    }
    int stat = map_createroom();
    if (stat == 0)
    {
        return 0;
    }
    place_upstairs_at_random_pos(
        roomx(cr), roomy(cr), roomwidth(cr), roomheight(cr));
    {
        int stat = map_createroom();
        if (stat == 0)
        {
            return 0;
        }
    }
    place_downstairs_at_random_pos(
        roomx(cr), roomy(cr), roomwidth(cr), roomheight(cr));
    for (int cnt = 0, cnt_end = (rdroomnum); cnt < cnt_end; ++cnt)
    {
        map_createroom(0);
    }
    for (int cnt = 0, cnt_end = (rdextraroom); cnt < cnt_end; ++cnt)
    {
        p = 0;
        for (int cnt = 0; cnt < 100; ++cnt)
        {
            x = rnd(map_data.width);
            y = rnd(map_data.height);
            if (cell_data.at(x, y).chip_id_actual == 3)
            {
                dx = rnd(rdroomsizemax) + rdroomsizemin;
                dy = rnd(rdroomsizemax) + rdroomsizemin;
                rx = rnd(dx(0));
                ry = rnd(dy);
                if (x > 1 && y > 1 && x + dx < map_data.width - 2 &&
                    y + dy < map_data.height - 2)
                {
                    p = 1;
                    break;
                }
            }
        }
        if (p == 0)
        {
            continue;
        }
        dy = y;
        for (int cnt = 0, cnt_end = (ry); cnt < cnt_end; ++cnt)
        {
            dx = x;
            for (int cnt = 0, cnt_end = (rx); cnt < cnt_end; ++cnt)
            {
                cell_data.at(dx, dy).chip_id_actual = 3;
                ++dx;
            }
            ++dy;
        }
    }
    return 1;
}



int initialize_random_nefia_rdtype3()
{
    map_data.width = 48 + rnd(20);
    map_data.height = 22;
    map_data.max_crowd_density = map_data.width * map_data.height / 20;
    map_initialize();
    for (int cnt = 0, cnt_end = (map_data.height); cnt < cnt_end; ++cnt)
    {
        y = cnt;
        for (int cnt = 0, cnt_end = (map_data.width); cnt < cnt_end; ++cnt)
        {
            x = cnt;
            if (x == 0 || y == 0 || x + 1 == map_data.width ||
                y + 1 == map_data.height)
            {
                continue;
            }
            cell_data.at(x, y).chip_id_actual = 3;
        }
    }
    p(0) = rnd(map_data.width / 2) + 2;
    p(1) = rnd(map_data.width / 2) + map_data.width / 2 - 2;
    if (rnd(2) == 0)
    {
        p(2) = p;
        p = p(1);
        p(1) = p(2);
    }
    map_place_upstairs(p, rnd(map_data.height - 4) + 2);
    map_place_downstairs(p(1), rnd(map_data.height - 4) + 2);
    return 1;
}



int initialize_quest_map_party()
{
    int roomdiff = 0;
    game_data.left_minutes_of_executing_quest = 60;
    game_data.executing_immediate_quest_time_left_display_period = 9999;
    rdroomsizemin = 5;
    mdatan(0) = i18n::s.get("core.map.quest.party_room");
    map_data.indoors_flag = 1;
    map_data.tileset = 11;
    map_data.width = 38;
    map_data.height = 28;
    map_initialize();
    rdroomnum = 80;
    for (int cnt = 0, cnt_end = (map_data.height); cnt < cnt_end; ++cnt)
    {
        y = cnt;
        for (int cnt = 0, cnt_end = (map_data.width); cnt < cnt_end; ++cnt)
        {
            x = cnt;
            if (x == 0 || y == 0 || x + 1 == map_data.width ||
                y + 1 == map_data.height)
            {
                continue;
            }
            cell_data.at(x, y).chip_id_actual = 100;
        }
    }
    for (int cnt = 0, cnt_end = (rdroomnum); cnt < cnt_end; ++cnt)
    {
        map_createroom(4);
    }
    convert_tiles_at_random();
    for (int cnt = 0; cnt < 500; ++cnt)
    {
        dx = rnd(map_data.width - 5);
        dy = rnd(map_data.height - 5);
        p(0) = 1;
        p(1) = 1;
        for (int cnt = 0; cnt < 4; ++cnt)
        {
            y = dy + cnt;
            for (int cnt = 0; cnt < 4; ++cnt)
            {
                x = dx + cnt;
                if (cell_data.at(x, y).chip_id_actual != tile_tunnel ||
                    !cell_data.at(x, y).item_info_actual.is_empty())
                {
                    p(0) = 0;
                }
                if (cell_data.at(x, y).chip_id_actual != tile_room ||
                    !cell_data.at(x, y).item_info_actual.is_empty())
                {
                    p(1) = 0;
                }
            }
        }
        if (p(0) == 1)
        {
            int n = rnd(5);
            for (int cnt = 0; cnt < 4; ++cnt)
            {
                y = dy + cnt;
                int cnt2 = cnt;
                for (int cnt = 0; cnt < 4; ++cnt)
                {
                    x = dx + cnt;
                    if (n < 2)
                    {
                        if (cnt != 0 && cnt != 3 && cnt2 != 0 && cnt2 != 3)
                        {
                            cell_data.at(x, y).chip_id_actual = 473;
                        }
                    }
                    if (n == 2)
                    {
                        if (cnt == 3 || cnt2 == 3)
                        {
                            break;
                        }
                        if (cnt == 1 && cnt2 == 1)
                        {
                            cell_data.at(x, y).chip_id_actual = 664;
                        }
                        else
                        {
                            cell_data.at(x, y).chip_id_actual = 206;
                            flt();
                            itemcreate_map_inv(91, x, y, 0);
                        }
                    }
                    if (n == 3)
                    {
                        if (cnt == 1 && cnt2 == 1)
                        {
                            cell_data.at(x, y).chip_id_actual = 204;
                            flt();
                            itemcreate_map_inv(585, x, y, 0);
                        }
                    }
                    if (n == 4)
                    {
                        if (cnt == 1 && cnt2 == 1)
                        {
                            flt();
                            cell_data.at(x, y).chip_id_actual = 69;
                            itemcreate_map_inv(138, x, y, 0);
                        }
                    }
                }
            }
        }
        if (p(1) == 1)
        {
            flt();
            itemcreate_map_inv(83, dx + 1, dy + 1, 0);
            if (rnd(2))
            {
                flt();
                itemcreate_map_inv(92, dx + 1, dy, 0);
            }
            if (rnd(2))
            {
                flt();
                itemcreate_map_inv(92, dx + 1, dy + 2, 0);
            }
            if (rnd(2))
            {
                flt();
                itemcreate_map_inv(92, dx, dy + 1, 0);
            }
            if (rnd(2))
            {
                flt();
                itemcreate_map_inv(92, dx + 2, dy + 1, 0);
            }
        }
    }
    list(0, 0) = 171;
    list(1, 0) = 9;
    list(2, 0) = 36;
    list(0, 1) = 269;
    list(1, 1) = 273;
    list(2, 1) = 35;
    list(0, 2) = 269;
    list(1, 2) = 174;
    list(2, 2) = 8;
    list(0, 3) = 174;
    list(1, 3) = 16;
    list(2, 3) = 239;
    list(0, 4) = 16;
    list(1, 4) = 185;
    list(2, 4) = 41;
    list(0, 5) = 185;
    list(1, 5) = 274;
    list(2, 5) = 184;
    list(0, 6) = 274;
    list(1, 6) = 272;
    list(2, 6) = 70;
    list(0, 7) = 272;
    list(1, 7) = 38;
    list(2, 7) = 1;
    list(0, 8) = 38;
    list(1, 8) = 206;
    list(2, 8) = 72;
    list(0, 9) = 206;
    list(1, 9) = 73;
    list(2, 9) = 69;
    for (int cnt = 0, cnt_end = (roomsum); cnt < cnt_end; ++cnt)
    {
        rx = roomx(cnt) + 1;
        rw = roomwidth(cnt) - 2;
        ry = roomy(cnt) + 1;
        rh = roomheight(cnt) - 2;
        rdsize = rw * rh;
        roomdiff =
            clamp(rnd_capped(quest_data.immediate().difficulty / 3 + 3), 0, 9);
        if (rnd(2) == 0)
        {
            x = rnd(rw) + rx;
            y = rnd(rh) + ry;
            if (cell_data.at(x, y).item_info_actual.is_empty())
            {
                flt();
                itemcreate_map_inv(88, x, y, 0);
            }
        }
        if (rnd(3) == 0)
        {
            x = rnd(rw) + rx;
            y = rnd(rh) + ry;
            if (cell_data.at(x, y).item_info_actual.is_empty())
            {
                flt();
                itemcreate_map_inv(313, x, y, 0);
            }
        }
        if (rnd(2) == 0)
        {
            x = rnd(rw) + rx;
            y = rnd(rh) + ry;
            if (cell_data.at(x, y).item_info_actual.is_empty())
            {
                flt();
                itemcreate_map_inv(156, x, y, 0);
            }
        }
        if (rnd(3) == 0)
        {
            x = rnd(rw) + rx;
            y = rnd(rh) + ry;
            if (cell_data.at(x, y).item_info_actual.is_empty())
            {
                flt();
                itemcreate_map_inv(606, x, y, 0);
            }
        }
        for (int cnt = 0,
                 cnt_end = cnt + (rnd(rdsize / 5 + 2) + rdsize / 5 + 3);
             cnt < cnt_end;
             ++cnt)
        {
            flt(roomdiff * 5, calcfixlv(Quality::bad));
            initlv = roomdiff * 7 + rnd(5);
            if (const auto chara = chara_create(
                    -1, list(rnd(3), roomdiff), rnd(rw) + rx, rnd(rh) + ry))
            {
                chara->role = Role::other;
                chara->relationship = -1;
                chara->original_relationship = -1;
                chara->gold = chara->level * (20 + rnd(20));
            }
        }
    }
    game_data.entrance_type = 7;
    mapstartx = rnd(map_data.width / 3) + map_data.width / 3;
    mapstarty = rnd(map_data.height / 3) + map_data.height / 3;
    map_place_player_and_allies();
    map_data.max_crowd_density = 0;
    for (int cnt = 0, cnt_end = (25 + rnd(10)); cnt < cnt_end; ++cnt)
    {
        x = rnd(map_data.width);
        y = rnd(map_data.height);
        if (!cell_data.at(x, y).item_info_actual.is_empty() ||
            chip_data.for_cell(x, y).effect & 4)
        {
            continue;
        }
        flt();
        p(0) = 217;
        p(1) = 218;
        p(2) = 216;
        p(3) = 215;
        p(4) = 215;
        p(5) = 152;
        p(6) = 152;
        p(7) = 91;
        p(8) = 189;
        itemcreate_map_inv(p(rnd(9)), x, y, 0);
    }
    flt();
    if (const auto chara = chara_create(-1, 29, -3, 0))
    {
        chara->role = Role::other;
        chara->relationship = -1;
        chara->original_relationship = -1;
    }
    flt();
    if (const auto chara = chara_create(-1, 231, -3, 0))
    {
        chara->role = Role::other;
        chara->relationship = -1;
        chara->original_relationship = -1;
    }
    flt();
    if (const auto chara = chara_create(-1, 31, -3, 0))
    {
        chara->role = Role::other;
        chara->relationship = -1;
        chara->original_relationship = -1;
    }
    flt();
    if (const auto chara = chara_create(-1, 247, -3, 0))
    {
        chara->role = Role::other;
        chara->relationship = -1;
        chara->original_relationship = -1;
    }
    if (rnd(10) == 0)
    {
        flt();
        if (const auto chara = chara_create(-1, 34, -3, 0))
        {
            chara->role = Role::other;
            chara->relationship = -1;
            chara->original_relationship = -1;
        }
    }
    if (rnd(10) == 0)
    {
        flt();
        if (const auto chara = chara_create(-1, 28, -3, 0))
        {
            chara->role = Role::other;
            chara->relationship = -1;
            chara->original_relationship = -1;
        }
    }
    if (rnd(10) == 0)
    {
        flt();
        if (const auto chara = chara_create(-1, 223, -3, 0))
        {
            chara->role = Role::other;
            chara->relationship = -1;
            chara->original_relationship = -1;
        }
    }
    if (rnd(10) == 0)
    {
        flt();
        if (const auto chara = chara_create(-1, 252, -3, 0))
        {
            chara->role = Role::other;
            chara->relationship = -1;
            chara->original_relationship = -1;
        }
    }
    if (rnd(10) == 0)
    {
        flt();
        if (const auto chara = chara_create(-1, 322, -3, 0))
        {
            chara->role = Role::other;
            chara->relationship = -1;
            chara->original_relationship = -1;
        }
    }
    for (const auto& item : g_inv.ground())
    {
        item->own_state = OwnState::town;
    }
    return 1;
}



void initialize_quest_map_town()
{
    map_data.max_crowd_density = 0;
    map_data.indoors_flag = 2;
    map_init_static_map(map_get_custom_map_name(game_data.previous_map2));
    mdatan(0) = i18n::s.get("core.map.quest.urban_area");
    randomize();
    game_data.entrance_type = 5;
    map_place_player_and_allies();
    map_data.user_map_flag = 0;
    if (game_data.executing_immediate_quest_type == 1008)
    {
        game_data.left_minutes_of_executing_quest = 720;
        game_data.executing_immediate_quest_time_left_display_period = 9999;
        flt();
        initlv = quest_data.immediate().difficulty;
        fixlv = Quality::godly;
        if (const auto chara =
                chara_create(-1, quest_data.immediate().extra_info_1, -3, 0))
        {
            chara->relationship = -3;
            chara->original_relationship = -3;
            quest_data.immediate().extra_info_2 = chara->index;
        }
    }
    if (game_data.executing_immediate_quest_type == 1010)
    {
        for (int cnt = 0, cnt_end = (6 + rnd(4)); cnt < cnt_end; ++cnt)
        {
            flt();
            initlv = quest_data.immediate().difficulty * 3 / 2;
            fixlv = Quality::bad;
            if (const auto chara = chara_create(
                    -1, quest_data.immediate().extra_info_1, -3, 0))
            {
                chara->relationship = -3;
                chara->original_relationship = -3;
            }
        }
    }
    for (const auto& item : g_inv.ground())
    {
        f = 0;
        if (item->id == "core.well" || item->id == "core.fountain")
        {
            item->param1 = -10;
        }
        if (item->id == "core.safe")
        {
            item->param1 = 0;
        }
    }
    for (int cnt = 0, cnt_end = (map_data.height); cnt < cnt_end; ++cnt)
    {
        y = cnt;
        for (int cnt = 0, cnt_end = (map_data.width); cnt < cnt_end; ++cnt)
        {
            x = cnt;
            cell_data.at(x, y).feats = 0;
        }
    }
}



void initialize_random_nefia_rdtype8()
{
    map_data.width = 30;
    map_data.height = 60 + rnd(60);
    map_data.max_crowd_density = map_data.width * map_data.height / 20;
    map_initialize();
    int w = 6;
    dx = map_data.width / 2 - w / 2;
    p = 0;
    for (int cnt = 0, cnt_end = (map_data.height - 4); cnt < cnt_end; ++cnt)
    {
        y = 2 + cnt;
        for (int cnt = 0, cnt_end = (w); cnt < cnt_end; ++cnt)
        {
            x = cnt + dx;
            cell_data.at(x, y).chip_id_actual = 100;
        }
        if (p <= 0)
        {
            if (rnd(2))
            {
                p = rnd(12);
            }
        }
        if (rnd(2))
        {
            if (w > 4)
            {
                w -= rnd(2);
            }
        }
        if (p > 0)
        {
            if (p < 5)
            {
                if (w > 3)
                {
                    w -= rnd(2);
                    --p;
                }
            }
            if (p > 4)
            {
                if (w < 10)
                {
                    ++w;
                    --p;
                }
            }
        }
        if (dx > 1)
        {
            dx -= rnd(2);
        }
        if (dx + w < map_data.width - 1)
        {
            dx += rnd(2);
        }
        if (dx + w > map_data.width)
        {
            w = map_data.width - dx;
        }
    }
    while (1)
    {
        x = rnd(map_data.width);
        y = rnd(15);
        if (cell_data.at(x, y).chip_id_actual == 100)
        {
            map_place_upstairs(x, y);
            break;
        }
    }
    while (1)
    {
        x = rnd(map_data.width);
        y = map_data.height - rnd(15) - 1;
        if (cell_data.at(x, y).chip_id_actual == 100)
        {
            map_place_downstairs(x, y);
            break;
        }
    }
}



void dimmix(elona_vector1<int>& array)
{
    int mx_at_m172 = 0;
    int r_at_m172 = 0;
    mx_at_m172 = array.size();
    for (int cnt = 0, cnt_end = (mx_at_m172); cnt < cnt_end; ++cnt)
    {
        r_at_m172 = cnt + rnd((mx_at_m172 - cnt));
        tmp_at_m172 = array(r_at_m172);
        array(r_at_m172) = array(cnt);
        array(cnt) = tmp_at_m172;
    }
}



void initialize_random_nefia_rdtype9()
{
    map_data.width = _mclass * (_bold * 2) - _bold + 8;
    map_data.height = map_data.width;
    map_data.max_crowd_density = map_data.width * map_data.height / 12;
    map_initialize();
    mapgen_dig_maze();
    rdsecond = 1;
    mapgen_dig_maze();
    rdsecond = 0;
}



void mapgen_dig_maze()
{
    elona_vector1<int> maze;
    int mdig = 0;
    int _hole = 0;
    int sdigx = 0;
    int sdigy = 0;
    int digno = 0;
    int pmdig = 0;
    DIM2(maze, _mclass * _mclass);
    mdig = 0;
    _hole = 0;
    sdigx = _bold;
    sdigy = _bold;
    maze(mdig) = 7;
    elona_vector1<int> way;
    DIM2(way, 4);
    for (int cnt = 0; cnt < 4; ++cnt)
    {
        way(cnt) = cnt;
    }
    i = 0;
    while (1)
    {
        dimmix(way);
        digno = 0;
        for (int cnt = 0; cnt < 4; ++cnt)
        {
            pmdig = mdig;
            if (way(cnt) == 0)
            {
                if (pmdig / _mclass == 0)
                {
                    continue;
                }
                else
                {
                    mdig -= _mclass;
                }
            }
            if (way(cnt) == 1)
            {
                if (pmdig % _mclass == _mclass - 1)
                {
                    continue;
                }
                else
                {
                    ++mdig;
                }
            }
            if (way(cnt) == 2)
            {
                if (pmdig / _mclass == _mclass - 1)
                {
                    continue;
                }
                else
                {
                    mdig += _mclass;
                }
            }
            if (way(cnt) == 3)
            {
                if (pmdig % _mclass == 0)
                {
                    continue;
                }
                else
                {
                    --mdig;
                }
            }
            if (maze(mdig) != _hole)
            {
                mdig = pmdig;
                continue;
            }
            ++i;
            sdigx = pmdig % _mclass * _bold * 2 + _bold;
            sdigy = pmdig / _mclass * _bold * 2 + _bold;
            if (way(cnt) == 0)
            {
                maze(mdig) = 3;
                for (int cnt = 0, cnt_end = (_bold * 2); cnt < cnt_end; ++cnt)
                {
                    y = sdigy - _bold * 2 + cnt - _bold + 4;
                    for (int cnt = 0, cnt_end = (_bold - 1); cnt < cnt_end;
                         ++cnt)
                    {
                        x = sdigx + cnt - _bold + 4;
                        cell_data.at(x, y).chip_id_actual = 100;
                    }
                }
            }
            if (way(cnt) == 1)
            {
                maze(mdig) = 4;
                for (int cnt = 0, cnt_end = (_bold - 1); cnt < cnt_end; ++cnt)
                {
                    y = sdigy + cnt - _bold + 4;
                    for (int cnt = 0, cnt_end = (_bold * 3 - 1); cnt < cnt_end;
                         ++cnt)
                    {
                        x = sdigx + cnt - _bold + 4;
                        cell_data.at(x, y).chip_id_actual = 100;
                    }
                }
            }
            if (way(cnt) == 2)
            {
                maze(mdig) = 1;
                for (int cnt = 0, cnt_end = (_bold * 3 - 1); cnt < cnt_end;
                     ++cnt)
                {
                    y = sdigy + cnt - _bold + 4;
                    for (int cnt = 0, cnt_end = (_bold - 1); cnt < cnt_end;
                         ++cnt)
                    {
                        x = sdigx + cnt - _bold + 4;
                        cell_data.at(x, y).chip_id_actual = 100;
                    }
                }
            }
            if (way(cnt) == 3)
            {
                maze(mdig) = 2;
                for (int cnt = 0, cnt_end = (_bold - 1); cnt < cnt_end; ++cnt)
                {
                    y = sdigy + cnt - _bold + 4;
                    for (int cnt = 0, cnt_end = (_bold * 2); cnt < cnt_end;
                         ++cnt)
                    {
                        x = sdigx + cnt - _bold * 2 - _bold + 4;
                        cell_data.at(x, y).chip_id_actual = 100;
                    }
                }
            }
            digno = 1;
            break;
        }
        if (digno == 1)
        {
            continue;
        }
        if (maze(mdig) == 7)
        {
            break;
        }
        if (maze(mdig) == 1)
        {
            mdig -= _mclass;
            continue;
        }
        if (maze(mdig) == 2)
        {
            ++mdig;
            continue;
        }
        if (maze(mdig) == 3)
        {
            mdig += _mclass;
            continue;
        }
        if (maze(mdig) == 4)
        {
            --mdig;
        }
    }
    if (rdsecond)
    {
        return;
    }
    for (int cnt = 0;; ++cnt)
    {
        x = rnd(map_data.width);
        y = rnd(map_data.height);
        if (cell_data.at(x, y).chip_id_actual != 100)
        {
            continue;
        }
        dx = rnd(map_data.width);
        dy = rnd(map_data.height);
        if (cell_data.at(dx, dy).chip_id_actual != 100)
        {
            continue;
        }
        if (dist(x, y, dx, dy) < 10)
        {
            if (cnt < 1000)
            {
                continue;
            }
        }
        map_place_upstairs(x, y);
        map_place_downstairs(dx, dy);
        break;
    }
}



void initialize_random_nefia_rdtype10()
{
    map_data.width = _mclass * (_bold * 2) - _bold + 8;
    map_data.height = map_data.width;
    map_data.max_crowd_density = map_data.width * map_data.height / 12;
    map_initialize();
    mapgen_dig_maze();
    for (int cnt = 0; cnt < 50; ++cnt)
    {
        int cnt2 = cnt;
        t = 100 + cnt2 + 1;
        while (1)
        {
            x = rnd(map_data.width);
            y = rnd(map_data.height);
            if (cell_data.at(x, y).chip_id_actual != 100)
            {
                continue;
            }
            int w = 10 + rnd(4);
            for (int cnt = 0, cnt_end = (w); cnt < cnt_end; ++cnt)
            {
                dy = cnt + y - w / 2;
                for (int cnt = 0, cnt_end = (w); cnt < cnt_end; ++cnt)
                {
                    dx = cnt + x - w / 2;
                    if (dx < 1 || dy < 1 || dx >= map_data.width - 1 ||
                        dy >= map_data.height - 1)
                    {
                        continue;
                    }
                    if (dist(x, y, dx, dy) >= w / 2)
                    {
                        continue;
                    }
                    tx = dx - 1;
                    ty = dy;
                    if (cell_data.at(tx, ty).chip_id_actual != t)
                    {
                        if (cell_data.at(tx, ty).chip_id_actual != 0)
                        {
                            if (cell_data.at(tx, ty).chip_id_actual != 100)
                            {
                                continue;
                            }
                        }
                    }
                    tx = dx + 1;
                    ty = dy;
                    if (cell_data.at(tx, ty).chip_id_actual != t)
                    {
                        if (cell_data.at(tx, ty).chip_id_actual != 0)
                        {
                            if (cell_data.at(tx, ty).chip_id_actual != 100)
                            {
                                continue;
                            }
                        }
                    }
                    tx = dx;
                    ty = dy - 1;
                    if (cell_data.at(tx, ty).chip_id_actual != t)
                    {
                        if (cell_data.at(tx, ty).chip_id_actual != 0)
                        {
                            if (cell_data.at(tx, ty).chip_id_actual != 100)
                            {
                                continue;
                            }
                        }
                    }
                    tx = dx;
                    ty = dy + 1;
                    if (cell_data.at(tx, ty).chip_id_actual != t)
                    {
                        if (cell_data.at(tx, ty).chip_id_actual != 0)
                        {
                            if (cell_data.at(tx, ty).chip_id_actual != 100)
                            {
                                continue;
                            }
                        }
                    }
                    tx = dx - 1;
                    ty = dy - 1;
                    if (cell_data.at(tx, ty).chip_id_actual != t)
                    {
                        if (cell_data.at(tx, ty).chip_id_actual != 0)
                        {
                            if (cell_data.at(tx, ty).chip_id_actual != 100)
                            {
                                continue;
                            }
                        }
                    }
                    tx = dx + 1;
                    ty = dy - 1;
                    if (cell_data.at(tx, ty).chip_id_actual != t)
                    {
                        if (cell_data.at(tx, ty).chip_id_actual != 0)
                        {
                            if (cell_data.at(tx, ty).chip_id_actual != 100)
                            {
                                continue;
                            }
                        }
                    }
                    tx = dx - 1;
                    ty = dy + 1;
                    if (cell_data.at(tx, ty).chip_id_actual != t)
                    {
                        if (cell_data.at(tx, ty).chip_id_actual != 0)
                        {
                            if (cell_data.at(tx, ty).chip_id_actual != 100)
                            {
                                continue;
                            }
                        }
                    }
                    tx = dx + 1;
                    ty = dy + 1;
                    if (cell_data.at(tx, ty).chip_id_actual != t)
                    {
                        if (cell_data.at(tx, ty).chip_id_actual != 0)
                        {
                            if (cell_data.at(tx, ty).chip_id_actual != 100)
                            {
                                continue;
                            }
                        }
                    }
                    cell_data.at(dx, dy).chip_id_actual = t;
                }
            }
            break;
        }
    }
    for (int cnt = 0, cnt_end = (map_data.height / 2 - 2); cnt < cnt_end; ++cnt)
    {
        y = cnt * 2;
        for (int cnt = 0, cnt_end = (map_data.width / 2 - 2); cnt < cnt_end;
             ++cnt)
        {
            x = cnt * 2;
            if (cell_data.at(x, y).chip_id_actual < 100)
            {
                continue;
            }
            if (cell_data.at(x, y).feats != 0)
            {
                continue;
            }
            if (cell_data.at(x - 1, y).chip_id_actual >= 100)
            {
                if (cell_data.at(x + 1, y).chip_id_actual >= 100)
                {
                    if (cell_data.at(x, y - 1).chip_id_actual == 0)
                    {
                        if (cell_data.at(x, y + 1).chip_id_actual == 0)
                        {
                            cell_featset(
                                x,
                                y,
                                tile_doorclosed,
                                21,
                                rnd_capped(
                                    std::abs(
                                        game_data.current_dungeon_level * 3 /
                                        2) +
                                    1));
                        }
                    }
                    continue;
                }
            }
            if (cell_data.at(x, y - 1).chip_id_actual >= 100)
            {
                if (cell_data.at(x, y + 1).chip_id_actual >= 100)
                {
                    if (cell_data.at(x - 1, y).chip_id_actual == 0)
                    {
                        if (cell_data.at(x + 1, y).chip_id_actual == 0)
                        {
                            cell_featset(
                                x,
                                y,
                                tile_doorclosed,
                                21,
                                rnd_capped(
                                    std::abs(
                                        game_data.current_dungeon_level * 3 /
                                        2) +
                                    1));
                        }
                    }
                    continue;
                }
            }
        }
    }
}



void map_tileset(int tileset_type)
{
    tile_doorclosed = 726;
    tile_dooropen = 236;
    tile_default(0) = 396;
    tile_default(1) = 1;
    tile_default(2) = 1;
    tile_fog(0) = 531;
    tile_fog(1) = 1;
    tile_fog(2) = 1;
    tile_wall(0) = 462;
    tile_wall(1) = 1;
    tile_wall(2) = 1;
    tile_room(0) = 13;
    tile_room(1) = 1;
    tile_room(2) = 1;
    tile_board = 727;
    tile_votebox = 729;
    tile_townboard = 732;
    tile_tunnel(0) = 33;
    tile_tunnel(1) = 1;
    tile_tunnel(2) = 1;
    tile_pot = 242;
    if (tileset_type == 12)
    {
        tile_doorclosed = 733;
        tile_dooropen = 265;
    }
    if (tileset_type == 8)
    {
        tile_doorclosed = 728;
        tile_dooropen = 241;
    }
    if (tileset_type == 9)
    {
        tile_doorclosed = 730;
        tile_dooropen = 264;
    }
    if (tileset_type == 3)
    {
        tile_room = 41;
        tile_tunnel = 41;
        tile_wall = 469;
        tile_fog = tile_wall + 66;
    }
    if (tileset_type == 2)
    {
        tile_wall = 462;
        tile_fog = 529;
    }
    if (tileset_type == 10)
    {
        tile_room = 165;
        tile_tunnel(0) = 33;
        tile_tunnel(1) = 4;
        tile_tunnel(2) = 2;
        tile_wall = 469;
        tile_default = 469;
    }
    if (tileset_type == 11)
    {
        tile_default = 465;
        tile_fog = 530;
        tile_tunnel = 212;
        tile_wall = 467;
        tile_room = 203;
    }
    if (tileset_type == 0)
    {
        tile_default = 469;
        tile_fog = 529;
        tile_tunnel(0) = 33;
        tile_tunnel(1) = 4;
        tile_tunnel(2) = 2;
        tile_wall = 469;
        tile_room(0) = 33;
        tile_room(1) = 4;
        tile_room(2) = 2;
    }
    if (tileset_type == 6)
    {
        tile_default = 469;
        tile_fog = 529;
        tile_tunnel(0) = 45;
        tile_tunnel(1) = 3;
        tile_tunnel(2) = 2;
        tile_wall = 469;
        tile_room(0) = 33;
        tile_room(1) = 6;
        tile_room(2) = 3;
    }
    if (tileset_type == 7)
    {
        tile_default = 474;
        tile_fog = 530;
        tile_tunnel = 68;
        tile_wall = 474;
        tile_room(0) = 66;
        tile_room(1) = 2;
        tile_room(2) = 2;
    }
    if (tileset_type == 300)
    {
        tile_default = 475;
        tile_fog = 528;
        tile_tunnel = 0;
        tile_wall = 475;
        tile_room(0) = 0;
        tile_room(1) = 6;
        tile_room(2) = 6;
    }
    if (tileset_type == 100)
    {
        tile_default = 472;
        tile_fog = 530;
        tile_tunnel = 103;
        tile_wall = 473;
        tile_room(0) = 132;
        tile_room(1) = 3;
        tile_room(2) = 2;
    }
    if (tileset_type == 101)
    {
        tile_default = 477;
        tile_fog = 530;
        tile_tunnel = 100;
        tile_wall = 477;
        tile_room = 99;
    }
    if (tileset_type == 200)
    {
        tile_default = 468;
        tile_fog = 531;
        tile_tunnel(0) = 33;
        tile_tunnel(1) = 4;
        tile_tunnel(2) = 2;
        tile_wall = 462;
        tile_room(0) = 119;
        tile_room(1) = 4;
        tile_room(2) = 2;
    }
    if (tileset_type == 1)
    {
        tile_wall = -1;
        tile_fog(0) = 396;
        tile_fog(1) = 4;
        tile_fog(2) = 2;
    }
    if (tileset_type == 4)
    {
        switch (map_get_field_type())
        {
        case FieldMapType::plain_field:
            tile_default = 0;
            tile_fog = 528;
            break;
        case FieldMapType::forest:
            tile_default = 7;
            tile_fog = 528;
            break;
        case FieldMapType::sea:
            tile_default = 12;
            tile_fog = 528;
            break;
        case FieldMapType::grassland:
            tile_default = 3;
            tile_fog = 528;
            break;
        case FieldMapType::desert:
            tile_default = 19;
            tile_fog = 531;
            break;
        case FieldMapType::snow_field:
            tile_default = 45;
            tile_fog = 532;
            break;
        default: assert(0); break;
        }
    }
}



void initialize_home_mdata()
{
    if (game_data.home_scale == 0)
    {
        map_data.max_item_count = 100;
        game_data.basic_point_of_home_rank = 1000;
    }
    if (game_data.home_scale == 1)
    {
        map_data.max_item_count = 150;
        game_data.basic_point_of_home_rank = 3000;
    }
    if (game_data.home_scale == 2)
    {
        map_data.max_item_count = 200;
        game_data.basic_point_of_home_rank = 5000;
    }
    if (game_data.home_scale == 3)
    {
        map_data.max_item_count = 300;
        game_data.basic_point_of_home_rank = 7000;
    }
    if (game_data.home_scale == 4)
    {
        map_data.max_item_count = 350;
        game_data.basic_point_of_home_rank = 8000;
        map_data.tileset = 8;
    }
    if (game_data.home_scale == 5)
    {
        map_data.max_item_count = 400;
        game_data.basic_point_of_home_rank = 10000;
    }
}



void map_init_static_map(const std::string& map_filename)
{
    ctrl_file_custom_map_read(
        filesystem::dirs::map() / fs::u8path(map_filename));

    map_tileset(map_data.tileset);

    nooracle = 1;
    for (int i = 0; i < 400; ++i)
    {
        const int id = cmapdata(0, i);
        const int x = cmapdata(1, i);
        const int y = cmapdata(2, i);
        const int ex_info = cmapdata(3, i);
        const int type = cmapdata(4, i);

        if (id == 0)
            continue;

        switch (type)
        {
        case 0:
            flt();
            if (const auto item = itemcreate_map_inv(id, x, y, 0))
            {
                item->own_state = static_cast<OwnState>(ex_info);
            }
            break;
        case 1:
            flt();
            chara_create(-1, id, x, y);
            break;
        case 2: {
            const auto& obj_data = cellobjdata[id];
            if (mapupdate)
            {
                if (obj_data.type == 32)
                {
                    continue;
                }
            }
            cell_featset(
                x,
                y,
                obj_data.tile,
                obj_data.type,
                ex_info % 1000,
                ex_info / 1000);
            if (obj_data.type == 10)
            {
                map_data.stair_up_pos = y * 1000 + x;
            }
            if (obj_data.type == 11)
            {
                map_data.stair_down_pos = y * 1000 + x;
            }
            break;
        }
        default: assert(0); break;
        }
    }

    nooracle = 0;
    map_data.user_map_flag = 1;
}



FieldMapType map_get_field_type()
{
    const auto T = game_data.stood_world_map_tile;

    if (4 <= T && T < 9)
    {
        return FieldMapType::forest;
    }
    else if (264 <= T && T < 363)
    {
        return FieldMapType::sea;
    }
    else if (9 <= T && T < 13)
    {
        return FieldMapType::grassland;
    }
    else if (13 <= T && T < 17)
    {
        return FieldMapType::desert;
    }
    else if (
        (26 <= T && T <= 32) || (568 <= T && T <= 570) ||
        (198 <= T && T <= 230))
    {
        return FieldMapType::snow_field;
    }
    else
    {
        return FieldMapType::plain_field;
    }
}

} // namespace elona
