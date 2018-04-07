#include "ctrl_file.hpp"
#include "ability.hpp"
#include "character.hpp"
#include "elona.hpp"
#include "filesystem.hpp"
#include "item.hpp"
#include "putit.hpp"
#include "variables.hpp"


using namespace elona;


namespace
{


template <typename T>
void load_v1(
    const fs::path& filepath,
    elona_vector1<T>& data,
    size_t begin,
    size_t end)
{
    std::ifstream in(filepath.native());
    putit::binary_iarchive ar(in);
    for (size_t i = begin; i < end; ++i)
    {
        ar.load(data(i));
    }
}


template <typename T>
void save_v1(
    const fs::path& filepath,
    elona_vector1<T>& data,
    size_t begin,
    size_t end)
{
    std::ofstream out(filepath.native());
    putit::binary_oarchive ar(out);
    for (size_t i = begin; i < end; ++i)
    {
        ar.save(data(i));
    }
}


template <typename T>
void load_v2(
    const fs::path& filepath,
    elona_vector2<T>& data,
    size_t i_begin,
    size_t i_end,
    size_t j_begin,
    size_t j_end)
{
    std::ifstream in(filepath.native());
    putit::binary_iarchive ar{in};
    for (size_t j = j_begin; j < j_end; ++j)
    {
        for (size_t i = i_begin; i < i_end; ++i)
        {
            ar.load(data(i, j));
        }
    }
}


template <typename T>
void save_v2(
    const fs::path& filepath,
    elona_vector2<T>& data,
    size_t i_begin,
    size_t i_end,
    size_t j_begin,
    size_t j_end)
{
    std::ofstream out(filepath.native());
    putit::binary_oarchive ar{out};
    for (size_t j = j_begin; j < j_end; ++j)
    {
        for (size_t i = i_begin; i < i_end; ++i)
        {
            ar.save(data(i, j));
        }
    }
}


template <typename T>
void load_v3(
    const fs::path& filepath,
    elona_vector3<T>& data,
    size_t i_begin,
    size_t i_end,
    size_t j_begin,
    size_t j_end,
    size_t k_begin,
    size_t k_end)
{
    std::ifstream in(filepath.native());
    putit::binary_iarchive ar{in};
    for (size_t k = k_begin; k < k_end; ++k)
    {
        for (size_t j = j_begin; j < j_end; ++j)
        {
            for (size_t i = i_begin; i < i_end; ++i)
            {
                ar.load(data(i, j, k));
            }
        }
    }
}


template <typename T>
void save_v3(
    const fs::path& filepath,
    elona_vector3<T>& data,
    size_t i_begin,
    size_t i_end,
    size_t j_begin,
    size_t j_end,
    size_t k_begin,
    size_t k_end)
{
    std::ofstream out(filepath.native());
    putit::binary_oarchive ar{out};
    for (size_t k = k_begin; k < k_end; ++k)
    {
        for (size_t j = j_begin; j < j_end; ++j)
        {
            for (size_t i = i_begin; i < i_end; ++i)
            {
                ar.save(data(i, j, k));
            }
        }
    }
}


template <typename T>
void load(const fs::path& filepath, T& data, size_t begin, size_t end)
{
    std::ifstream in(filepath.native());
    putit::binary_iarchive ar{in};
    for (size_t i = begin; i < end; ++i)
    {
        ar.load(data[i]);
    }
}


template <typename T>
void save(const fs::path& filepath, T& data, size_t begin, size_t end)
{
    std::ofstream out(filepath.native());
    putit::binary_oarchive ar{out};
    for (size_t i = begin; i < end; ++i)
    {
        ar.save(data[i]);
    }
}



void fmode_8_7(bool read)
{
    folder = fs::path(u8"./save/"s + playerid + u8"/").generic_string();
    if (!read)
    {
        playerheader = ""s + cdatan(0, 0) + u8" Lv:"s + cdata[0].level + u8" "s
            + mdatan(0);
        bsave(folder + u8"header.txt"s, playerheader);
    }

    {
        const auto filepath = folder + u8"gdata.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                load_v1(filepath, gdata, 0, 1000);
            }
        }
        else
        {
            save_v1(filepath, gdata, 0, 1000);
        }
    }

    {
        const auto filepath = folder + u8"cdata.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                load(filepath, cdata, 0, 57);
            }
        }
        else
        {
            save(filepath, cdata, 0, 57);
        }
    }

    {
        const auto filepath = folder + u8"sdata.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                std::ifstream in{filepath};
                putit::binary_iarchive ar{in};
                for (int cc = 0; cc < 57; ++cc)
                {
                    for (int i = 0; i < 600; ++i)
                    {
                        ar.load(sdata.get(i, cc));
                    }
                }
            }
        }
        else
        {
            std::ofstream out{filepath};
            putit::binary_oarchive ar{out};
            for (int cc = 0; cc < 57; ++cc)
            {
                for (int i = 0; i < 600; ++i)
                {
                    ar.save(sdata.get(i, cc));
                }
            }
        }
    }

    {
        const auto filepath = folder + u8"spell.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                load_v1(filepath, spell, 0, 200);
            }
        }
        else
        {
            save_v1(filepath, spell, 0, 200);
        }
    }

    {
        const auto filepath = folder + u8"inv.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                load(filepath, inv, 0, 1320);
            }
        }
        else
        {
            save(filepath, inv, 0, 1320);
        }
    }

    {
        const auto filepath = folder + u8"kitem.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                load_v2(filepath, itemmemory, 0, 3, 0, 800);
            }
        }
        else
        {
            save_v2(filepath, itemmemory, 0, 3, 0, 800);
        }
    }

    {
        const auto filepath = folder + u8"knpc.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                load_v2(filepath, npcmemory, 0, 2, 0, 800);
            }
        }
        else
        {
            save_v2(filepath, npcmemory, 0, 2, 0, 800);
        }
    }

    {
        const auto filepath = folder + u8"adata.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                load_v2(filepath, adata, 0, 40, 0, 500);
            }
        }
        else
        {
            save_v2(filepath, adata, 0, 40, 0, 500);
        }
    }

    {
        const auto filepath = folder + u8"spact.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                load_v1(filepath, spact, 0, 500);
            }
        }
        else
        {
            save_v1(filepath, spact, 0, 500);
        }
    }

    {
        const auto filepath = folder + u8"qdata.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                load_v2(filepath, qdata, 0, 20, 0, 500);
            }
        }
        else
        {
            save_v2(filepath, qdata, 0, 20, 0, 500);
        }
    }

    {
        const auto filepath = folder + u8"mat.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                load_v1(filepath, mat, 0, 400);
            }
        }
        else
        {
            save_v1(filepath, mat, 0, 400);
        }
    }

    {
        const auto filepath = folder + u8"trait.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                load_v1(filepath, trait, 0, 500);
            }
        }
        else
        {
            save_v1(filepath, trait, 0, 500);
        }
    }

    {
        const auto filepath = folder + u8"pcc.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                load_v2(filepath, pcc, 0, 30, 0, 20);
            }
        }
        else
        {
            save_v2(filepath, pcc, 0, 30, 0, 20);
        }
    }

    {
        const auto filepath = folder + u8"card.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                load_v2(filepath, card, 0, 100, 0, 40);
            }
        }
        else
        {
            save_v2(filepath, card, 0, 100, 0, 40);
        }
    }

    {
        const auto filepath = folder + u8"krecipe.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                if (gdata_version >= 1200)
                {
                    load_v1(filepath, recipememory, 0, 1200);
                }
            }
        }
        else
        {
            save_v1(filepath, recipememory, 0, 1200);
        }
    }

    {
        const auto filepath = folder + u8"art.log"s;
        if (!read)
        {
            std::ofstream out{filepath};
            range::for_each(artifactlocation, [&](const auto& line) {
                out << line << std::endl;
            });
        }
        if (read)
        {
            artifactlocation.clear();
            range::copy(
                fileutil::read_by_line{filepath},
                std::back_inserter(artifactlocation));
        }
    }

    {
        const auto filepath = folder + u8"news.log"s;
        notesel(newsbuff);
        if (!read)
        {
            std::ofstream out{filepath};
            out << newsbuff(0) << std::endl;
        }
        if (read)
        {
            newsbuff(0).clear();
            std::ifstream in{filepath};
            std::string tmp;
            while (std::getline(in, tmp))
            {
                newsbuff(0) += tmp + '\n';
            }
        }
    }

    arrayfile(read, u8"cdatan1", folder + u8"cdatan.s1");
    arrayfile(read, u8"qname", folder + u8"qname.s1");
    arrayfile(read, u8"gdatan", folder + u8"gdatan.s1");
    if (!read)
    {
        bsave(folder + u8"evnum.s1"s, evnum);
        bsave(folder + u8"evdata1.s1"s, evdata1);
        bsave(folder + u8"evdata2.s1"s, evdata2);
        bsave(folder + u8"evlist.s1"s, evlist);
    }
    else
    {
        if (fs::exists(folder + u8"evnum.s1"s))
        {
            bload(folder + u8"evnum.s1"s, evnum);
        }
        if (fs::exists(folder + u8"evdata1.s1"s))
        {
            bload(folder + u8"evdata1.s1"s, evdata1);
        }
        if (fs::exists(folder + u8"evdata2.s1"s))
        {
            bload(folder + u8"evdata2.s1"s, evdata2);
        }
        if (fs::exists(folder + u8"evlist.s1"s))
        {
            bload(folder + u8"evlist.s1"s, evlist);
        }
    }
}


void fmode_14_15(bool read)
{
    std::string filepath;
    if (!read)
    {
        folder = fs::path(u8"./tmp/").generic_string();
    }
    if (read)
    {
        folder = fs::path(u8"./save/"s + geneuse + u8"/").generic_string();
    }
    if (!read)
    {
        playerheader =
            ""s + cdatan(0, 0) + u8"(Lv"s + cdata[0].level + u8")の遺伝子"s;
        filepath = folder + u8"gene_header.txt"s;
        bsave(filepath, playerheader);
        fileadd(filepath);
    }

    {
        const auto filepath = folder + u8"g_cdata.s1"s;
        if (read)
        {
            if (fs::exists(filepath))
            {
                load(filepath, cdata, 0, 57);
            }
        }
        else
        {
            fileadd(filepath);
            save(filepath, cdata, 0, 57);
        }
    }

    {
        const auto filepath = folder + u8"g_sdata.s1"s;
        if (read)
        {
            if (fs::exists(filepath))
            {
                std::ifstream in{filepath};
                putit::binary_iarchive ar{in};
                for (int cc = 0; cc < 57; ++cc)
                {
                    for (int i = 0; i < 600; ++i)
                    {
                        ar.load(sdata.get(i, cc));
                    }
                }
            }
        }
        else
        {
            fileadd(""s + filepath);
            std::ofstream out{filepath};
            putit::binary_oarchive ar{out};
            for (int cc = 0; cc < 57; ++cc)
            {
                for (int i = 0; i < 600; ++i)
                {
                    ar.save(sdata.get(i, cc));
                }
            }
        }
    }

    {
        const auto filepath = folder + u8"g_spell.s1"s;
        if (read)
        {
            if (fs::exists(filepath))
            {
                load_v1(filepath, spell, 0, 200);
            }
        }
        else
        {
            fileadd(""s + filepath);
            save_v1(filepath, spell, 0, 200);
        }
    }

    {
        const auto filepath = folder + u8"g_inv.s1"s;
        if (read)
        {
            if (fs::exists(filepath))
            {
                load(filepath, inv, 0, 1320);
            }
        }
        else
        {
            fileadd(filepath);
            save(filepath, inv, 0, 1320);
        }
    }

    {
        const auto filepath = folder + u8"g_spact.s1"s;
        if (read)
        {
            if (fs::exists(filepath))
            {
                load_v1(filepath, spact, 0, 500);
            }
        }
        else
        {
            fileadd(""s + filepath);
            save_v1(filepath, spact, 0, 500);
        }
    }

    {
        const auto filepath = folder + u8"g_mat.s1"s;
        if (read)
        {
            if (fs::exists(filepath))
            {
                load_v1(filepath, mat, 0, 400);
            }
        }
        else
        {
            fileadd(""s + filepath);
            save_v1(filepath, mat, 0, 400);
        }
    }

    {
        const auto filepath = folder + u8"g_card.s1"s;
        if (read)
        {
            if (fs::exists(filepath))
            {
                load_v2(filepath, card, 0, 100, 0, 40);
            }
        }
        else
        {
            fileadd(""s + filepath);
            save_v2(filepath, card, 0, 100, 0, 40);
        }
    }

    {
        const auto filepath = folder + u8"g_genetemp.s1"s;
        if (read)
        {
            if (fs::exists(filepath))
            {
                load_v1(filepath, genetemp, 0, 1000);
            }
        }
        else
        {
            fileadd(""s + filepath);
            save_v1(filepath, genetemp, 0, 1000);
        }
    }
}


void fmode_2_1(bool read)
{
    std::string filepath;
    folder = fs::path(u8"./tmp/").generic_string();

    {
        const auto filepath = folder + u8"mdata_"s + mid + u8".s2"s;
        if (read)
        {
            load_v1(filepath, mdata, 0, 100);
        }
        else
        {
            fileadd(""s + filepath);
            save_v1(filepath, mdata, 0, 100);
        }
    }

    {
        const auto filepath = folder + u8"map_"s + mid + u8".s2"s;
        if (read)
        {
            DIM4(map, mdata(0), mdata(1), 10);
            DIM3(mapsync, mdata(0), mdata(1));
            DIM3(mef, 9, 200);
            load_v3(filepath, map, 0, mdata(0), 0, mdata(1), 0, 10);
        }
        else
        {
            fileadd(""s + filepath);
            save_v3(filepath, map, 0, mdata(0), 0, mdata(1), 0, 10);
        }
    }

    {
        const auto filepath = folder + u8"cdata_"s + mid + u8".s2"s;
        if (read)
        {
            load(filepath, cdata, 57, 245);
        }
        else
        {
            fileadd(filepath);
            save(filepath, cdata, 57, 245);
        }
    }

    {
        const auto filepath = folder + u8"sdata_"s + mid + u8".s2"s;
        if (read)
        {
            std::ifstream in{filepath};
            putit::binary_iarchive ar{in};
            for (int cc = 57; cc < 245; ++cc)
            {
                for (int i = 0; i < 600; ++i)
                {
                    ar.load(sdata.get(i, cc));
                }
            }
        }
        else
        {
            fileadd(""s + filepath);
            std::ofstream out{filepath};
            putit::binary_oarchive ar{out};
            for (int cc = 57; cc < 245; ++cc)
            {
                for (int i = 0; i < 600; ++i)
                {
                    ar.save(sdata.get(i, cc));
                }
            }
        }
    }

    {
        const auto filepath = folder + u8"mef_"s + mid + u8".s2"s;
        if (read)
        {
            if (mdata(21) == 0)
            {
                for (int y = 0; y < mdata(1); ++y)
                {
                    for (int x = 0; x < mdata(0); ++x)
                    {
                        map(x, y, 8) = 0;
                    }
                }
                mdata(21) = 1;
            }
            else
            {
                load_v2(filepath, mef, 0, 9, 0, 200);
            }
        }
        else
        {
            fileadd(""s + filepath);
            save_v2(filepath, mef, 0, 9, 0, 200);
        }
    }

    arrayfile(read, u8"cdatan2", folder + u8"cdatan_"s + mid + u8".s2");
    arrayfile(read, u8"mdatan", folder + u8"mdatan_"s + mid + u8".s2");
}


void fmode_20_19(bool read)
{
    std::string filepath;
    folder = fs::path(u8"./user/").generic_string();

    {
        const auto filepath = folder + u8"m1_0.t"s;
        if (read)
        {
            load_v1(filepath, mdata, 0, 100);
        }
        else
        {
            save_v1(filepath, mdata, 0, 100);
        }
    }

    {
        const auto filepath = folder + u8"m2_0.t"s;
        if (read)
        {
            DIM4(map, mdata(0), mdata(1), 10);
            DIM3(mapsync, mdata(0), mdata(1));
            DIM3(mef, 9, 200);
            load_v3(filepath, map, 0, mdata(0), 0, mdata(1), 0, 10);
        }
        else
        {
            save_v3(filepath, map, 0, mdata(0), 0, mdata(1), 0, 10);
        }
    }

    {
        const auto filepath = folder + u8"m3_0.t"s;
        if (read)
        {
            load(filepath, inv, 1320, 5480);
        }
        else
        {
            save(filepath, inv, 1320, 5480);
        }
    }

    elona_export = 1;
    arrayfile(read, u8"mdatan", folder + u8"m4_0.t");
    if (!read)
    {
        zipadd(u8"m1_0.t"s);
        zipadd(u8"m2_0.t"s);
        zipadd(u8"m3_0.t"s);
        zipadd(u8"m4_0.t"s);
    }
}


void fmode_22_21(bool read)
{
    int id = 0;
    folder = fs::path(u8"./user/").generic_string();
    if (read)
    {
        tg = 0;
    }
    else
    {
        tg = 1;
    }
    enemyteam = -1;
    gdata(86) = 0;
    SDIM1(untaglist);
    for (int cnt = 0; cnt < 245; ++cnt)
    {
        if (!read)
        {
            if (list(0, cnt) == 0)
            {
                continue;
            }
            tg = cnt;
        }
        else
        {
            if (!fs::exists(folder + u8"c1_"s + id + u8".t"s))
            {
                break;
            }
            tg = 0;
            for (int cnt = 57; cnt < 245; ++cnt)
            {
                if (cdata[cnt].state == 0)
                {
                    tg = cnt;
                    break;
                }
            }
            if (tg == 0)
            {
                break;
            }
        }
        {
            const auto filepath = folder + u8"c1_"s + id + u8".t"s;
            if (read)
            {
                load(filepath, cdata, tg, tg + 1);
            }
            else
            {
                save(filepath, cdata, tg, tg + 1);
            }
            continue;
        }
        {
            const auto filepath = folder + u8"c2_"s + id + u8".t"s;
            if (read)
            {
                std::ifstream in{filepath};
                putit::binary_iarchive ar{in};
                for (int i = 0; i < 600; ++i)
                {
                    ar.load(sdata.get(i, tg));
                }
            }
            else
            {
                std::ofstream out{filepath};
                putit::binary_oarchive ar{out};
                for (int i = 0; i < 600; ++i)
                {
                    ar.save(sdata.get(i, tg));
                }
            }
        }
        {
            const auto filepath = folder + u8"c3_"s + id + u8".t"s;
            const auto tmp = inv_getheader(tg);
            const auto invhead = tmp.first;
            const auto invrange = tmp.second;
            if (read)
            {
                load(filepath, inv, invhead, invhead + invrange);
            }
            else
            {
                save(filepath, inv, invhead, invhead + invrange);
            }
        }
        elona_export = 1;
        arrayfile(read, u8"cdatan3", folder + u8"c4_"s + id + u8".t");
        if (!read)
        {
            zipadd(u8"c1_"s + id + u8".t"s);
            zipadd(u8"c2_"s + id + u8".t"s);
            zipadd(u8"c3_"s + id + u8".t"s);
            zipadd(u8"c4_"s + id + u8".t"s);
            if (cdata[tg].id == 343)
            {
                if (fs::exists(folder + userdatan(6, cdata[tg].cnpc_id)))
                {
                    if (cdata[tg].cnpc_id != usernpcmax)
                    {
                        if (instr(
                                untaglist,
                                0,
                                u8"/"s + userdatan(0, cdata[tg].cnpc_id)
                                    + u8"/"s)
                            == -1)
                        {
                            if (gdata(86) < 10)
                            {
                                bcopy(
                                    folder + userdatan(6, cdata[tg].cnpc_id),
                                    folder + u8"_tmp_"s + gdata(86)
                                        + u8".npc"s);
                                zipadd(u8"_tmp_"s + gdata(86) + u8".npc"s);
                                untaglist += u8"/"s
                                    + userdatan(0, cdata[tg].cnpc_id) + u8"/"s;
                                ++gdata(86);
                            }
                        }
                    }
                }
            }
        }
        else
        {
            for (const auto& cnt : items(tg))
            {
                inv[cnt].body_part = 0;
            }
            for (int cnt = 100; cnt < 130; ++cnt)
            {
                cdata_body_part(tg, cnt) =
                    cdata_body_part(tg, cnt) / 10000 * 10000;
            }
            rc = tg;
            wear_most_valuable_equipment_for_all_body_parts();
            cdata[rc].item_which_will_be_used = 0;
            rowactend(rc);
            cbitmod(967, rc, 0);
            cbitmod(968, rc, 0);
            cdata[rc].hp = cdata[rc].max_hp;
            cdata[rc].mp = cdata[rc].max_mp;
            cbitmod(960, rc, 0);
            cbitmod(989, tc, 0);
            if (importmode == 0)
            {
                cdata[tg].character_role = 20;
                cdata[tg].gold = 0;
                if (cdata[tg].relationship >= 10)
                {
                    if (userrelation == 0)
                    {
                        cdata[tg].relationship = 0;
                        cdata[tg].original_relationship = 0;
                    }
                    else
                    {
                        cdata[tg].relationship = -3;
                        cdata[tg].original_relationship = -3;
                    }
                }
                cxinit = cdata[tg].position.x;
                cyinit = cdata[tg].position.y;
                place_character();
            }
            if (importmode == 1)
            {
                if (enemyteam == -1)
                {
                    enemyteam = rc;
                }
                cdata[rc].relationship = -3;
                cdata[rc].original_relationship = -3;
                map_placearena(rc, 1);
            }
        }
        ++id;
    }
}


void fmode_16()
{
    DIM3(cmapdata, 5, 400);

    load_v3(fmapfile + u8".map", map, 0, mdata(0), 0, mdata(1), 0, 3);

    const auto filepath = fmapfile + u8".obj"s;
    if (!fs::exists(filepath))
    {
        return;
    }
    load_v2(filepath, cmapdata, 0, 5, 0, 400);
}


void fmode_6_5(bool read)
{
    if (read)
    {
        DIM3(cmapdata, 5, 400);
        DIM3(mef, 9, 200);
    }

    {
        const auto filepath = fmapfile + u8".idx"s;
        if (read)
        {
            load_v1(filepath, mdatatmp, 0, 100);
            for (int j = 0; j < 5; ++j)
            {
                mdata(j) = mdatatmp(j);
            }
        }
        else
        {
            save_v1(filepath, mdata, 0, 100);
        }
    }

    {
        const auto filepath = fmapfile + u8".map"s;
        if (read)
        {
            DIM4(map, mdata(0), mdata(1), 10);
            DIM3(mapsync, mdata(0), mdata(1));
            load_v3(filepath, map, 0, mdata(0), 0, mdata(1), 0, 10);
        }
        else
        {
            save_v3(filepath, map, 0, mdata(0), 0, mdata(1), 0, 10);
        }
    }

    {
        const auto filepath = fmapfile + u8".obj"s;
        if (read)
        {
            if (fs::exists(filepath))
            {
                load_v2(filepath, cmapdata, 0, 5, 0, 400);
            }
        }
        else
        {
            save_v2(filepath, cmapdata, 0, 5, 0, 400);
        }
    }
}


void fmode_4_3(bool read, const fs::path& file)
{
    const auto path = fs::path(u8"./tmp") / file;
    if (read)
    {
        load(path, inv, 1320, 5480);
    }
    else
    {
        fileadd(path.generic_string());
        save(path, inv, 1320, 5480);
    }
}



void fmode_23_24(bool read, const fs::path& filepath)
{
    if (read)
    {
        fileadd(filepath.generic_string());
        save_v1(filepath, deck, 0, 1000);
    }
    else
    {
        load_v1(filepath, deck, 0, 1000);
    }
}


void fmode_18_17(bool read, const fs::path& file)
{
    folder = fs::path(u8"./tmp/").generic_string();
    if (!fs::exists(file.generic_string() + u8"cdata_"s + mid + u8".s2"s))
    {
        return;
    }

    {
        const auto filepath = folder + u8"cdata_"s + mid + u8".s2"s;
        if (read)
        {
            load(filepath, cdata, 57, 245);
        }
        else
        {
            fileadd(filepath);
            save(filepath, cdata, 57, 245);
        }
    }

    {
        const auto filepath = folder + u8"sdata_"s + mid + u8".s2"s;
        if (read)
        {
            std::ifstream in{filepath};
            putit::binary_iarchive ar{in};
            for (int cc = 57; cc < 245; ++cc)
            {
                for (int i = 0; i < 600; ++i)
                {
                    ar.load(sdata.get(i, cc));
                }
            }
        }
        else
        {
            fileadd(""s + filepath);
            std::ofstream out{filepath};
            putit::binary_oarchive ar{out};
            for (int cc = 57; cc < 245; ++cc)
            {
                for (int i = 0; i < 600; ++i)
                {
                    ar.save(sdata.get(i, cc));
                }
            }
        }
    }

    arrayfile(read, u8"cdatan2", folder + u8"cdatan_"s + mid + u8".s2");
}


void fmode_10()
{
    for (const auto& entry : filesystem::dir_entries(
             fs::path(u8"./tmp"),
             filesystem::dir_entries::type::file,
             std::regex{u8R"(.*\..*)"}))
    {
        elona_delete(entry.path());
    }
}


void fmode_9()
{
    elona_delete(fs::path(u8"./save/"s + playerid));
}


void fmode_11_12(int fmode)
{
    std::string filepath;
    if (fmode == 12)
    {
        if (!fs::exists(fs::path(u8"./tmp/mdata_"s + mid + u8".s2")))
        {
            return;
        }
    }
    filepath = fs::path(u8"./tmp/map_"s + mid + u8".s2").generic_string();
    if (!fs::exists(filepath))
    {
        return;
    }
    elona_delete(filepath);
    fileadd(filepath, 1);
    if (fmode == 11)
    {
        filepath = fs::path(u8"./tmp/cdata_"s + mid + u8".s2").generic_string();
        elona_delete(filepath);
        fileadd(filepath, 1);
        filepath = fs::path(u8"./tmp/sdata_"s + mid + u8".s2").generic_string();
        elona_delete(filepath);
        fileadd(filepath, 1);
        filepath =
            fs::path(u8"./tmp/cdatan_"s + mid + u8".s2").generic_string();
        elona_delete(filepath);
        fileadd(filepath, 1);
        filepath = fs::path(u8"./tmp/inv_"s + mid + u8".s2").generic_string();
        elona_delete(filepath);
        fileadd(filepath, 1);
    }
    filepath = fs::path(u8"./tmp/mdata_"s + mid + u8".s2").generic_string();
    elona_delete(filepath);
    fileadd(filepath, 1);
    filepath = fs::path(u8"./tmp/mdatan_"s + mid + u8".s2").generic_string();
    elona_delete(filepath);
    fileadd(filepath, 1);
    filepath = fs::path(u8"./tmp/mef_"s + mid + u8".s2").generic_string();
    elona_delete(filepath);
    fileadd(filepath, 1);
}


void fmode_13()
{
    for (int i = 0; i < 40; ++i)
    {
        adata(i, area) = 0;
    }
    for (const auto& entry : filesystem::dir_entries(
             fs::path(u8"./tmp"),
             filesystem::dir_entries::type::file,
             std::regex{u8R"(.*_)"s + area + u8R"(_.*\..*)"}))
    {
        elona_delete(entry.path());
        fileadd(entry.path().generic_string(), 1);
    }
}



} // namespace


namespace elona
{


void ctrl_file(int mode, const fs::path& filepath)
{
    notesel(filemod);
    gdata_play_time = gdata_play_time + timeGetTime() / 1000 - time_begin;
    time_begin = timeGetTime() / 1000;

    switch (mode)
    {
    case 8:
    case 7: fmode_8_7(mode == 7); break;
    case 14:
    case 15: fmode_14_15(mode == 15); break;
    case 2:
    case 1: fmode_2_1(mode == 1); break;
    case 20:
    case 19: fmode_20_19(mode == 19); break;
    case 22:
    case 21: fmode_22_21(mode == 21); break;
    case 16: fmode_16(); break;
    case 6:
    case 5: fmode_6_5(mode == 5); break;
    case 4:
    case 3: fmode_4_3(mode == 3, filepath); break;
    case 23:
    case 24: fmode_23_24(mode == 24, filepath); break;
    case 18:
    case 17: fmode_18_17(mode == 17, filepath); break;
    case 10: fmode_10(); break;
    case 9: fmode_9(); break;
    case 11:
    case 12: fmode_11_12(mode); break;
    case 13: fmode_13(); break;
    default: assert(0);
    }
}



} // namespace elona
