#include "fov.hpp"

#include "character.hpp"
#include "data/types/type_skill.hpp"
#include "game.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "skill.hpp"
#include "variables.hpp"



namespace elona
{

namespace
{

bool is_blocked(int x, int y)
{
    return (chip_data.for_cell(x, y).effect & 1) ||
        (chip_data.for_feat(x, y).effect & 1);
}

} // namespace



std::array<std::array<int, 2>, 17> fovlist;

bool is_in_fov(const Position& pos)
{
    return mapsync(pos.x, pos.y) == msync;
}



bool is_in_fov(const Character& chara)
{
    return chara.fov_flag == msync || chara.index == game()->mount;
}



bool fov_los(const Position& p1, const Position& p2)
{
    const auto [x1, y1] = p1;
    const auto [x2, y2] = p2;

    if (x1 < 0 || map_data.width <= x1 || y1 < 0 || map_data.height <= y1 ||
        x2 < 0 || map_data.width <= x2 || y2 < 0 || map_data.height <= y2)
    {
        // Out of range
        return false;
    }

    const auto dx = std::abs(x2 - x1);
    const auto dy = std::abs(y2 - y1);
    const auto sx = x1 <= x2 ? 1 : -1;
    const auto sy = y1 <= y2 ? 1 : -1;

    if (dx <= 1 && dy <= 1)
    {
        // p2 is adjacent to p1.
        return true;
    }

    if (dx == 0)
    {
        /*
         * Directly North or South
         *
         * X: p1
         * Y: p2
         * Z: the cell to check sight
         *  +---+---+---+---+---+
         *  |   |   | X |   |   |
         *  +---+---+---+---+---+
         *  |   |   | Z |   |   |
         *  +---+---+---+---+---+
         *  |   |   | Z |   |   |
         *  +   .   . . .   .   +
         *  |   .   . Z .   .   |
         *  +   .   . . .   .   +
         *  |   |   | Z |   |   |
         *  +---+---+---+---+---+
         *  |   |   | Z |   |   |
         *  +---+---+---+---+---+
         *  |   |   | Y |   |   |
         *  +---+---+---+---+---+
         */
        for (int y = y1 + sy; y != y2; y += sy)
        {
            if (is_blocked(x1, y))
            {
                return false;
            }
        }
        return true;
    }

    if (dy == 0)
    {
        /*
         * Directly East or West
         *
         * X: p1
         * Y: p2
         * Z: the cell to check sight
         *  +---+---+---+---+---+---+---+
         *  |   |   |           |   |   |
         *  +---+---+-- . . . --+---+---+
         *  |   |   |           |   |   |
         *  +---+---+-- . . . --+---+---+
         *  | X | Z | Z . Z . Z | Z | Y |
         *  +---+---+-- . . . --+---+---+
         *  |   |   |           |   |   |
         *  +---+---+-- . . . --+---+---+
         *  |   |   |           |   |   |
         *  +---+---+---+---+---+---+---+
         */
        for (int x = x1 + sx; x != x2; x += sx)
        {
            if (is_blocked(x, y1))
            {
                return false;
            }
        }
        return true;
    }

    if (dx == 1 && dy == 2)
    {
        /*
         * Like the move of chess' knight or shogi's 八方桂
         *
         * X: p1
         * Y: p2
         * Z: the cell to check sight
         *  +---+---+---+---+---+
         *  |   | Y |   | Y |   |
         *  +---+---+---+---+---+
         *  |   |   | Z |   |   |
         *  +---+---+---+---+---+
         *  |   |   | X |   |   |
         *  +---+---+---+---+---+
         *  |   |   | Z |   |   |
         *  +---+---+---+---+---+
         *  |   | Y |   | Y |   |
         *  +---+---+---+---+---+
         */
        if (!is_blocked(x1, y1 + sy))
        {
            return true;
        }
    }

    if (dy == 1 && dx == 2)
    {
        /*
         * Like the move of chess' knight or shogi's 八方桂
         *
         * X: p1
         * Y: p2
         * Z: the cell to check sight
         *  +---+---+---+---+---+
         *  |   |   |   |   |   |
         *  +---+---+---+---+---+
         *  | Y |   |   |   | Y |
         *  +---+---+---+---+---+
         *  |   | Z | X | Z |   |
         *  +---+---+---+---+---+
         *  | Y |   |   |   | Y |
         *  +---+---+---+---+---+
         *  |   |   |   |   |   |
         *  +---+---+---+---+---+
         */
        if (!is_blocked(x1 + sx, y1))
        {
            return true;
        }
    }

    if (dx == dy)
    {
        /*
         * Special case: the slope of the LOS is 1.
         *
         * X: p1
         * Y: p2
         * Z: the cell to check sight
         *  +---+---+---+---+---+---+---+---+---+
         *  | Y |   |   |   |   |   |   |   | Y |
         *  +-- .   .   .   .   .   .   .   . --+
         *  |     . .   .   .   .   .   . .     |
         *  +-- .   +---+---+---+---+---+   . --+
         *  |       | Z |   |   |   | Z |       |
         *  +-- .   +---+---+---+---+---+   . --+
         *  |       |   | Z |   | Z |   |       |
         *  +-- .   +---+---+---+---+---+   . --+
         *  |       |   |   | X |   |   |       |
         *  +-- .   +---+---+---+---+---+   . --+
         *  |       |   | Z |   | Z |   |       |
         *  +-- .   +---+---+---+---+---+   . --+
         *  |       | Z |   |   |   | Z |       |
         *  +-- .   +---+---+---+---+---+   . --+
         *  |     . .   .   .   .   .   . .     |
         *  +-- .   .   .   .   .   .   .   . --+
         *  | Y |   |   |   |   |   |   |   | Y |
         *  +---+---+---+---+---+---+---+---+---+
         */
        for (int x = x1 + sx, y = y1 + sy; x != x2; x += sx, y += sy)
        {
            if (is_blocked(x, y))
            {
                return false;
            }
        }
        return true;
    }

    // All special cases have been handled. Then, trace the LOS by using
    // an integer-based line drawing algorithm like "Bresenham's algorithm".
    // cf. https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm.

    // In this algorithm, each grid is a same-size square and has no space
    // between each other. The start/end point is the center of p1 and p2.
    if (dx > dy)
    {
        // Let m = dy/dx, the slope of the LOS.
        // Let f = 2*dx, the scaling factor.
        // qy is scaled by f to calculate all on integer.
        int qy = dy; // dy = (m/2) * f
        int y = y1;
        for (int x = x1 + sx; x != x2; x += sx)
        {
            if (is_blocked(x, y))
            {
                return false;
            }
            qy += 2 * dy; // 2 * dy = m * f
            if (qy >= dx) // dx = 1/2 * f
            {
                y += sy;
                // "qy == dx" is a special case: the LOS goes through a
                // "corner" of grid, not across an edge.
                if (qy != dx && is_blocked(x, y))
                {
                    return false;
                }
                qy -= 2 * dx; // 2 * dx = 1 * f
            }
        }
        return true;
    }
    else
    {
        // Let m = dx/dy, the slope of the LOS.
        // Let f = 2*dy, the scaling factor.
        // qx is scaled by f to calculate all on integer.
        int qx = dx; // dx = (m/2) * f
        int x = x1;
        for (int y = y1 + sy; y != y2; y += sy)
        {
            if (is_blocked(x, y))
            {
                return false;
            }
            qx += 2 * dx; // 2 * dx = m * f
            if (qx >= dy) // dy = 1/2 * f
            {
                x += sx;
                // "qx == dy" is a special case: the LOS goes through a
                // "corner" of grid, not across an edge.
                if (qx != dy && is_blocked(x, y))
                {
                    return false;
                }
                qx -= 2 * dy; // 2 * dy = 1 * f
            }
        }
        return true;
    }
}



std::vector<std::pair<int, int>> fov_get_route(
    const Position& p1,
    const Position& p2)
{
    const auto [x1, y1] = p1;
    const auto [x2, y2] = p2;

    if (p1 == p2)
    {
        return {
            {2, 0},
        };
    }

    const auto dx = std::abs(x2 - x1);
    const auto dy = std::abs(y2 - y1);
    const auto sx = x1 <= x2 ? 1 : -1;
    const auto sy = y1 <= y2 ? 1 : -1;

    if (dx == 0)
    {
        std::vector<std::pair<int, int>> ret;
        ret.push_back({2, sy});
        for (int y = y1 + sy; y != y2; y += sy)
        {
            if (is_blocked(x1, y))
            {
                return {};
            }
            ret.push_back({2, sy});
        }
        return ret;
    }

    if (dy == 0)
    {
        std::vector<std::pair<int, int>> ret;
        ret.push_back({1, sx});
        for (int x = x1 + sx; x != x2; x += sx)
        {
            if (is_blocked(x, y1))
            {
                return {};
            }
            ret.push_back({1, sx});
        }
        return ret;
    }

    if (dx == 1 && dy == 2)
    {
        if (!is_blocked(x1, y1 + sy))
        {
            return {
                {2, sy},
                {2, 0},
                {1, sx},
            };
        }
    }

    if (dy == 1 && dx == 2)
    {
        if (!is_blocked(x1 + sx, y1))
        {
            return {
                {1, sx},
                {1, 0},
                {2, sy},
            };
        }
    }

    if (dx == dy)
    {
        std::vector<std::pair<int, int>> ret;
        ret.push_back({1, sx});
        ret.push_back({2, sy});
        for (int x = x1 + sx, y = y1 + sy; x != x2; x += sx, y += sy)
        {
            if (is_blocked(x, y))
            {
                return {};
            }
            ret.push_back({2, sy});
            ret.push_back({1, sx});
        }
        return ret;
    }

    if (dx > dy)
    {
        std::vector<std::pair<int, int>> ret;
        ret.push_back({1, sx});
        int qy = dy;
        int y = y1;
        for (int x = x1 + sx; x != x2; x += sx)
        {
            if (is_blocked(x, y))
            {
                return {};
            }
            qy += 2 * dy;
            if (qy >= dx)
            {
                y += sy;
                ret.push_back({2, sy});
                if (qy != dx && is_blocked(x, y))
                {
                    return {};
                }
                qy -= 2 * dx;
            }
            ret.push_back({1, sx});
        }
        return ret;
    }
    else
    {
        std::vector<std::pair<int, int>> ret;
        ret.push_back({2, sy});
        int qx = dx;
        int x = x1;
        for (int y = y1 + sy; y != y2; y += sy)
        {
            if (is_blocked(x, y))
            {
                return {};
            }
            qx += 2 * dx;
            if (qx >= dy)
            {
                x += sx;
                ret.push_back({1, sx});
                if (qx != dy && is_blocked(x, y))
                {
                    return {};
                }
                qx -= 2 * dy;
            }
            ret.push_back({2, sy});
        }
        return ret;
    }
}



RouteInfo route_info(
    int& x,
    int& y,
    int step,
    const std::vector<std::pair<int, int>>& route)
{
    if (route.size() == 0)
    {
        return RouteInfo::skip;
    }

    if (route.at(step % route.size()).first == 1)
    {
        x += route.at(step % route.size()).second;
    }
    else
    {
        y += route.at(step % route.size()).second;
    }

    if (step % route.size() % 2 == 0)
    {
        if (route.at((step + 1) % route.size()).first !=
            route.at(step % route.size()).first)
        {
            return RouteInfo::skip;
        }
    }
    if (step >= static_cast<int>(route.size()))
    {
        if (x < scx || y < scy || x >= scx + inf_screenw ||
            y >= scy + inf_screenh)
        {
            return RouteInfo::stop;
        }
        if (x < 0 || y < 0 || x >= map_data.width || y >= map_data.height)
        {
            return RouteInfo::stop;
        }
        if (chip_data.for_cell(x, y).effect & 1)
        {
            return RouteInfo::stop;
        }
        if (cell_data.at(x, y).feats != 0)
        {
            cell_featread(x, y);
            if (chip_data[feat].effect & 1)
            {
                return RouteInfo::stop;
            }
        }
    }
    if (route.at(step % route.size()).second == 0)
    {
        return RouteInfo::skip;
    }
    return RouteInfo::go;
}



std::vector<Position> fov_get_breath_route(
    const Position& source_pos,
    int range,
    const std::vector<std::pair<int, int>>& route)
{
    auto [x0, y0] = source_pos;

    std::vector<Position> ret;
    for (int step = 0; step < range; ++step)
    {
        if (route.at(step % route.size()).first == 1)
        {
            x0 += route.at(step % route.size()).second;
        }
        else
        {
            y0 += route.at(step % route.size()).second;
        }

        int breath_width;
        switch (step)
        {
        case 0: breath_width = 1; break;
        case 1:
        case 2:
        case 3: breath_width = 3; break;
        case 4:
        case 5: breath_width = 5; break;
        default: breath_width = 3; break;
        }

        for (int dy = 0; dy < breath_width; ++dy)
        {
            const auto y = y0 + dy - breath_width / 2;
            for (int dx = 0; dx < breath_width; ++dx)
            {
                const auto x = x0 + dx - breath_width / 2;
                if (x < scx || y < scy || x >= scx + inf_screenw ||
                    y >= scy + inf_screenh)
                {
                    continue;
                }
                if (x < 0 || y < 0 || x >= map_data.width ||
                    y >= map_data.height)
                {
                    continue;
                }
                if (chip_data.for_cell(x, y).effect & 1)
                {
                    continue;
                }

                if (range::find(ret, Position{x, y}) == ret.end())
                {
                    ret.push_back(Position{x, y});
                }
            }
        }
    }

    return ret;
}



void fov_init_fovlist()
{
    std::array<std::array<bool, fov_max + 2>, fov_max + 2> fovmap;
    for (int y = 0; y < fov_max + 2; ++y)
    {
        for (int x = 0; x < fov_max + 2; ++x)
        {
            fovmap[y][x] =
                dist(x, y, (fov_max + 2) / 2, (fov_max + 2) / 2) <= fov_max / 2;
        }
    }
    for (int y = 0; y < fov_max + 2; ++y)
    {
        bool f{};
        for (int x = 0; x < fov_max + 2; ++x)
        {
            if (fovmap[y][x])
            {
                if (!f)
                {
                    fovlist[y][0] = x;
                    f = true;
                }
            }
            else
            {
                if (f)
                {
                    fovlist[y][1] = x;
                    break;
                }
            }
        }
    }
}

} // namespace elona
