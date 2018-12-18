#include "fov.hpp"
#include "character.hpp"
#include "map.hpp"
#include "variables.hpp"

namespace elona
{

std::array<std::array<int, 2>, 17> fovlist;

int dy_at_modfov = 0;
int dx_at_modfov = 0;
int ay_at_modfov = 0;
int ax_at_modfov = 0;
int ty_at_modfov = 0;
int tx_at_modfov = 0;
int sx_at_modfov = 0;
int sy_at_modfov = 0;
int f2_at_modfov = 0;
int f1_at_modfov = 0;
int qy_at_modfov = 0;
int m_at_modfov = 0;
int qx_at_modfov = 0;

bool is_in_fov(const Position& pos)
{
    return mapsync(pos.x, pos.y) == msync;
}



bool is_in_fov(const Character& cc)
{
    return cc.vision_flag == msync || cc.index == game_data.mount;
}



int fov_los(int x1, int y1, int x2, int y2)
{
    if (x1 < 0 || map_data.width <= x1 || y1 < 0 || map_data.height <= y1 ||
        x2 < 0 || map_data.width <= x2 || y2 < 0 || map_data.height <= y2)
    {
        // Out of range
        return 0;
    }

    dy_at_modfov = y2 - y1;
    dx_at_modfov = x2 - x1;
    ay_at_modfov = std::abs(dy_at_modfov);
    ax_at_modfov = std::abs(dx_at_modfov);
    if (ax_at_modfov < 2 && ay_at_modfov < 2)
    {
        return 1;
    }
    if (dx_at_modfov == 0)
    {
        if (dy_at_modfov > 0)
        {
            ty_at_modfov = y1 + 1;
            while (1)
            {
                if (ty_at_modfov >= y2)
                {
                    break;
                }
                if (chipm(7, cell_data.at(x1, ty_at_modfov).chip_id_actual) & 1)
                {
                    return 0;
                }
                if (chipm(7, cell_data.at(x1, ty_at_modfov).feats % 1000) & 1)
                {
                    return 0;
                }
                ++ty_at_modfov;
            }
        }
        else
        {
            ty_at_modfov = y1 - 1;
            while (1)
            {
                if (ty_at_modfov <= y2)
                {
                    break;
                }
                if (chipm(7, cell_data.at(x1, ty_at_modfov).chip_id_actual) & 1)
                {
                    return 0;
                }
                if (chipm(7, cell_data.at(x1, ty_at_modfov).feats % 1000) & 1)
                {
                    return 0;
                }
                --ty_at_modfov;
            }
        }
        return 1;
    }
    if (dy_at_modfov == 0)
    {
        if (dx_at_modfov > 0)
        {
            tx_at_modfov = x1 + 1;
            while (1)
            {
                if (tx_at_modfov >= x2)
                {
                    break;
                }
                if (chipm(7, cell_data.at(tx_at_modfov, y1).chip_id_actual) & 1)
                {
                    return 0;
                }
                if (chipm(7, cell_data.at(tx_at_modfov, y1).feats % 1000) & 1)
                {
                    return 0;
                }
                ++tx_at_modfov;
            }
        }
        else
        {
            tx_at_modfov = x1 - 1;
            while (1)
            {
                if (tx_at_modfov <= x2)
                {
                    break;
                }
                if (chipm(7, cell_data.at(tx_at_modfov, y1).chip_id_actual) & 1)
                {
                    return 0;
                }
                if (chipm(7, cell_data.at(tx_at_modfov, y1).feats % 1000) & 1)
                {
                    return 0;
                }
                --tx_at_modfov;
            }
        }
        return 1;
    }
    if (dx_at_modfov < 0)
    {
        sx_at_modfov = -1;
    }
    else
    {
        sx_at_modfov = 1;
    }
    if (dy_at_modfov < 0)
    {
        sy_at_modfov = -1;
    }
    else
    {
        sy_at_modfov = 1;
    }
    if (ax_at_modfov == 1)
    {
        if (ay_at_modfov == 2)
        {
            if ((chipm(7, cell_data.at(x1, y1 + sy_at_modfov).chip_id_actual) &
                 1) == 0)
            {
                if ((chipm(
                         7,
                         cell_data.at(x1, (y1 + sy_at_modfov)).feats % 1000) &
                     1) == 0)
                {
                    return 1;
                }
            }
        }
    }
    else if (ay_at_modfov == 1)
    {
        if (ax_at_modfov == 2)
        {
            if ((chipm(7, cell_data.at(x1 + sx_at_modfov, y1).chip_id_actual) &
                 1) == 0)
            {
                if ((chipm(
                         7,
                         cell_data.at((x1 + sx_at_modfov), y1).feats % 1000) &
                     1) == 0)
                {
                    return 1;
                }
            }
        }
    }
    f2_at_modfov = ax_at_modfov * ay_at_modfov;
    f1_at_modfov = f2_at_modfov << 1;
    if (ax_at_modfov >= ay_at_modfov)
    {
        qy_at_modfov = ay_at_modfov * ay_at_modfov;
        m_at_modfov = qy_at_modfov << 1;
        tx_at_modfov = x1 + sx_at_modfov;
        if (qy_at_modfov == f2_at_modfov)
        {
            ty_at_modfov = y1 + sy_at_modfov;
            qy_at_modfov -= f1_at_modfov;
        }
        else
        {
            ty_at_modfov = y1;
        }
        while (1)
        {
            if (x2 - tx_at_modfov == 0)
            {
                break;
            }
            if (chipm(
                    7,
                    cell_data.at(tx_at_modfov, ty_at_modfov).chip_id_actual) &
                1)
            {
                return 0;
            }
            if (chipm(
                    7, cell_data.at(tx_at_modfov, ty_at_modfov).feats % 1000) &
                1)
            {
                return 0;
            }
            qy_at_modfov += m_at_modfov;
            if (qy_at_modfov < f2_at_modfov)
            {
                tx_at_modfov += sx_at_modfov;
            }
            else if (qy_at_modfov > f2_at_modfov)
            {
                ty_at_modfov += sy_at_modfov;
                if (chipm(
                        7,
                        cell_data.at(tx_at_modfov, ty_at_modfov)
                            .chip_id_actual) &
                    1)
                {
                    return 0;
                }
                if (chipm(
                        7,
                        cell_data.at(tx_at_modfov, ty_at_modfov).feats % 1000) &
                    1)
                {
                    return 0;
                }
                qy_at_modfov -= f1_at_modfov;
                tx_at_modfov += sx_at_modfov;
            }
            else
            {
                ty_at_modfov += sy_at_modfov;
                qy_at_modfov -= f1_at_modfov;
                tx_at_modfov += sx_at_modfov;
            }
        }
    }
    else
    {
        qx_at_modfov = ax_at_modfov * ax_at_modfov;
        m_at_modfov = qx_at_modfov << 1;
        ty_at_modfov = y1 + sy_at_modfov;
        if (qx_at_modfov == f2_at_modfov)
        {
            tx_at_modfov = x1 + sx_at_modfov;
            qx_at_modfov -= f1_at_modfov;
        }
        else
        {
            tx_at_modfov = x1;
        }
        while (1)
        {
            if (y2 - ty_at_modfov == 0)
            {
                break;
            }
            if (chipm(
                    7,
                    cell_data.at(tx_at_modfov, ty_at_modfov).chip_id_actual) &
                1)
            {
                return 0;
            }
            if (chipm(
                    7, cell_data.at(tx_at_modfov, ty_at_modfov).feats % 1000) &
                1)
            {
                return 0;
            }
            qx_at_modfov += m_at_modfov;
            if (qx_at_modfov < f2_at_modfov)
            {
                ty_at_modfov += sy_at_modfov;
            }
            else if (qx_at_modfov > f2_at_modfov)
            {
                tx_at_modfov += sx_at_modfov;
                if (chipm(
                        7,
                        cell_data.at(tx_at_modfov, ty_at_modfov)
                            .chip_id_actual) &
                    1)
                {
                    return 0;
                }
                if (chipm(
                        7,
                        cell_data.at(tx_at_modfov, ty_at_modfov).feats % 1000) &
                    1)
                {
                    return 0;
                }
                qx_at_modfov -= f1_at_modfov;
                ty_at_modfov += sy_at_modfov;
            }
            else
            {
                tx_at_modfov += sx_at_modfov;
                qx_at_modfov -= f1_at_modfov;
                ty_at_modfov += sy_at_modfov;
            }
        }
    }
    return 1;
}



int get_route(int x1, int y1, int x2, int y2)
{
    int p_at_modfov = 0;
    DIM3(route, 2, 100);
    dy_at_modfov = y2 - y1;
    dx_at_modfov = x2 - x1;
    if (y2 == y1)
    {
        if (x2 == x1)
        {
            route(0, 0) = 2;
            route(1, 0) = 0;
            maxroute = 1;
            return 1;
        }
    }
    ay_at_modfov = std::abs(dy_at_modfov);
    ax_at_modfov = std::abs(dx_at_modfov);
    p_at_modfov = 0;
    if (dx_at_modfov == 0)
    {
        if (dy_at_modfov > 0)
        {
            ty_at_modfov = y1 + 1;
            route(0, p_at_modfov) = 2;
            route(1, p_at_modfov) = 1;
            ++p_at_modfov;
            while (1)
            {
                if (ty_at_modfov >= y2)
                {
                    break;
                }
                if (chipm(7, cell_data.at(x1, ty_at_modfov).chip_id_actual) & 1)
                {
                    return 0;
                }
                if (chipm(7, cell_data.at(x1, ty_at_modfov).feats % 1000) & 1)
                {
                    return 0;
                }
                ++ty_at_modfov;
                route(0, p_at_modfov) = 2;
                route(1, p_at_modfov) = 1;
                ++p_at_modfov;
            }
        }
        else
        {
            ty_at_modfov = y1 - 1;
            route(0, p_at_modfov) = 2;
            route(1, p_at_modfov) = -1;
            ++p_at_modfov;
            while (1)
            {
                if (ty_at_modfov <= y2)
                {
                    break;
                }
                if (chipm(7, cell_data.at(x1, ty_at_modfov).chip_id_actual) & 1)
                {
                    return 0;
                }
                if (chipm(7, cell_data.at(x1, ty_at_modfov).feats % 1000) & 1)
                {
                    return 0;
                }
                --ty_at_modfov;
                route(0, p_at_modfov) = 2;
                route(1, p_at_modfov) = -1;
                ++p_at_modfov;
            }
        }
        maxroute = p_at_modfov;
        return 1;
    }
    if (dy_at_modfov == 0)
    {
        if (dx_at_modfov > 0)
        {
            tx_at_modfov = x1 + 1;
            route(0, p_at_modfov) = 1;
            route(1, p_at_modfov) = 1;
            ++p_at_modfov;
            while (1)
            {
                if (tx_at_modfov >= x2)
                {
                    break;
                }
                if (chipm(7, cell_data.at(tx_at_modfov, y1).chip_id_actual) & 1)
                {
                    return 0;
                }
                if (chipm(7, cell_data.at(tx_at_modfov, y1).feats % 1000) & 1)
                {
                    return 0;
                }
                ++tx_at_modfov;
                route(0, p_at_modfov) = 1;
                route(1, p_at_modfov) = 1;
                ++p_at_modfov;
            }
        }
        else
        {
            tx_at_modfov = x1 - 1;
            route(0, p_at_modfov) = 1;
            route(1, p_at_modfov) = -1;
            ++p_at_modfov;
            while (1)
            {
                if (tx_at_modfov <= x2)
                {
                    break;
                }
                if (chipm(7, cell_data.at(tx_at_modfov, y1).chip_id_actual) & 1)
                {
                    return 0;
                }
                if (chipm(7, cell_data.at(tx_at_modfov, y1).feats % 1000) & 1)
                {
                    return 0;
                }
                --tx_at_modfov;
                route(0, p_at_modfov) = 1;
                route(1, p_at_modfov) = -1;
                ++p_at_modfov;
            }
        }
        maxroute = p_at_modfov;
        return 1;
    }
    if (dx_at_modfov < 0)
    {
        sx_at_modfov = -1;
    }
    else
    {
        sx_at_modfov = 1;
    }
    if (dy_at_modfov < 0)
    {
        sy_at_modfov = -1;
    }
    else
    {
        sy_at_modfov = 1;
    }
    if (ax_at_modfov == 1)
    {
        if (ay_at_modfov == 2)
        {
            if ((chipm(7, cell_data.at(x1, y1 + sy_at_modfov).chip_id_actual) &
                 1) == 0)
            {
                if ((chipm(
                         7,
                         cell_data.at(x1, (y1 + sy_at_modfov)).feats % 1000) &
                     1) == 0)
                {
                    p_at_modfov = 0;
                    route(0, p_at_modfov) = 2;
                    route(1, p_at_modfov) = sy_at_modfov;
                    ++p_at_modfov;
                    route(0, p_at_modfov) = 2;
                    route(1, p_at_modfov) = 0;
                    ++p_at_modfov;
                    route(0, p_at_modfov) = 1;
                    route(1, p_at_modfov) = sx_at_modfov;
                    ++p_at_modfov;
                    maxroute = p_at_modfov;
                    return 1;
                }
            }
        }
    }
    else if (ay_at_modfov == 1)
    {
        if (ax_at_modfov == 2)
        {
            if ((chipm(7, cell_data.at(x1 + sx_at_modfov, y1).chip_id_actual) &
                 1) == 0)
            {
                if ((chipm(
                         7,
                         cell_data.at((x1 + sx_at_modfov), y1).feats % 1000) &
                     1) == 0)
                {
                    route(0, p_at_modfov) = 1;
                    route(1, p_at_modfov) = sx_at_modfov;
                    ++p_at_modfov;
                    route(0, p_at_modfov) = 1;
                    route(1, p_at_modfov) = 0;
                    ++p_at_modfov;
                    route(0, p_at_modfov) = 2;
                    route(1, p_at_modfov) = sy_at_modfov;
                    ++p_at_modfov;
                    maxroute = p_at_modfov;
                    return 1;
                }
            }
        }
    }
    f2_at_modfov = ax_at_modfov * ay_at_modfov;
    f1_at_modfov = f2_at_modfov << 1;
    if (ax_at_modfov >= ay_at_modfov)
    {
        qy_at_modfov = ay_at_modfov * ay_at_modfov;
        m_at_modfov = qy_at_modfov << 1;
        tx_at_modfov = x1 + sx_at_modfov;
        route(0, p_at_modfov) = 1;
        route(1, p_at_modfov) = sx_at_modfov;
        ++p_at_modfov;
        if (qy_at_modfov == f2_at_modfov)
        {
            ty_at_modfov = y1 + sy_at_modfov;
            route(0, p_at_modfov) = 2;
            route(1, p_at_modfov) = sy_at_modfov;
            ++p_at_modfov;
            qy_at_modfov -= f1_at_modfov;
        }
        else
        {
            ty_at_modfov = y1;
        }
        while (1)
        {
            if (x2 - tx_at_modfov == 0)
            {
                break;
            }
            if (chipm(
                    7,
                    cell_data.at(tx_at_modfov, ty_at_modfov).chip_id_actual) &
                1)
            {
                return 0;
            }
            if (chipm(
                    7, cell_data.at(tx_at_modfov, ty_at_modfov).feats % 1000) &
                1)
            {
                return 0;
            }
            qy_at_modfov += m_at_modfov;
            if (qy_at_modfov < f2_at_modfov)
            {
                tx_at_modfov += sx_at_modfov;
                route(0, p_at_modfov) = 1;
                route(1, p_at_modfov) = sx_at_modfov;
                ++p_at_modfov;
            }
            else if (qy_at_modfov > f2_at_modfov)
            {
                ty_at_modfov += sy_at_modfov;
                route(0, p_at_modfov) = 2;
                route(1, p_at_modfov) = sy_at_modfov;
                ++p_at_modfov;
                if (chipm(
                        7,
                        cell_data.at(tx_at_modfov, ty_at_modfov)
                            .chip_id_actual) &
                    1)
                {
                    return 0;
                }
                if (chipm(
                        7,
                        cell_data.at(tx_at_modfov, ty_at_modfov).feats % 1000) &
                    1)
                {
                    return 0;
                }
                qy_at_modfov -= f1_at_modfov;
                tx_at_modfov += sx_at_modfov;
                route(0, p_at_modfov) = 1;
                route(1, p_at_modfov) = sx_at_modfov;
                ++p_at_modfov;
            }
            else
            {
                ty_at_modfov += sy_at_modfov;
                route(0, p_at_modfov) = 2;
                route(1, p_at_modfov) = sy_at_modfov;
                ++p_at_modfov;
                qy_at_modfov -= f1_at_modfov;
                tx_at_modfov += sx_at_modfov;
                route(0, p_at_modfov) = 1;
                route(1, p_at_modfov) = sx_at_modfov;
                ++p_at_modfov;
            }
        }
    }
    else
    {
        qx_at_modfov = ax_at_modfov * ax_at_modfov;
        m_at_modfov = qx_at_modfov << 1;
        ty_at_modfov = y1 + sy_at_modfov;
        route(0, p_at_modfov) = 2;
        route(1, p_at_modfov) = sy_at_modfov;
        ++p_at_modfov;
        if (qx_at_modfov == f2_at_modfov)
        {
            tx_at_modfov = x1 + sx_at_modfov;
            route(0, p_at_modfov) = 1;
            route(1, p_at_modfov) = sx_at_modfov;
            ++p_at_modfov;
            qx_at_modfov -= f1_at_modfov;
        }
        else
        {
            tx_at_modfov = x1;
        }
        while (1)
        {
            if (y2 - ty_at_modfov == 0)
            {
                break;
            }
            if (chipm(
                    7,
                    cell_data.at(tx_at_modfov, ty_at_modfov).chip_id_actual) &
                1)
            {
                return 0;
            }
            if (chipm(
                    7, cell_data.at(tx_at_modfov, ty_at_modfov).feats % 1000) &
                1)
            {
                return 0;
            }
            qx_at_modfov += m_at_modfov;
            if (qx_at_modfov < f2_at_modfov)
            {
                ty_at_modfov += sy_at_modfov;
                route(0, p_at_modfov) = 2;
                route(1, p_at_modfov) = sy_at_modfov;
                ++p_at_modfov;
            }
            else if (qx_at_modfov > f2_at_modfov)
            {
                tx_at_modfov += sx_at_modfov;
                route(0, p_at_modfov) = 1;
                route(1, p_at_modfov) = sx_at_modfov;
                ++p_at_modfov;
                if (chipm(
                        7,
                        cell_data.at(tx_at_modfov, ty_at_modfov)
                            .chip_id_actual) &
                    1)
                {
                    return 0;
                }
                if (chipm(
                        7,
                        cell_data.at(tx_at_modfov, ty_at_modfov).feats % 1000) &
                    1)
                {
                    return 0;
                }
                qx_at_modfov -= f1_at_modfov;
                ty_at_modfov += sy_at_modfov;
                route(0, p_at_modfov) = 2;
                route(1, p_at_modfov) = sy_at_modfov;
                ++p_at_modfov;
            }
            else
            {
                tx_at_modfov += sx_at_modfov;
                route(0, p_at_modfov) = 1;
                route(1, p_at_modfov) = sx_at_modfov;
                ++p_at_modfov;
                qx_at_modfov -= f1_at_modfov;
                ty_at_modfov += sy_at_modfov;
                route(0, p_at_modfov) = 2;
                route(1, p_at_modfov) = sy_at_modfov;
                ++p_at_modfov;
            }
        }
    }
    maxroute = p_at_modfov;
    return 1;
}



void init_fovlist()
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
