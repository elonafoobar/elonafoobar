#include "ctrl_file.hpp"
#include "character.hpp"
#include "elona.hpp"
#include "filesystem.hpp"
#include "item.hpp"
#include "variables.hpp"


using namespace elona;


namespace
{


void fmode_8_7(int fmode)
{
    int fsize = 0;
    folder = fs::u8path(u8"./save/"s + playerid + u8"/");
    if (fmode == 8)
    {
        elona::fread = 0;
    }
    if (fmode == 7)
    {
        elona::fread = 1;
    }
    if (fmode == 8)
    {
        playerheader = ""s + cdatan(0, 0) + u8" Lv:"s + cdata_level(0) + u8" "s
            + mdatan(0);
        bsave(folder + u8"header.txt"s, playerheader);
    }
    {
        int cnt = 0;
        for (int cnt_end = cnt + (15); cnt < cnt_end; ++cnt)
        {
            file = folder;
            if (cnt == 0)
            {
                file += u8"gdata.s1"s;
                fsize = 4000;
            }
            if (cnt == 1)
            {
                file += u8"cdata.s1"s;
                fsize = 114000;
            }
            if (cnt == 2)
            {
                file += u8"sdata.s1"s;
                fsize = 273600;
            }
            if (cnt == 3)
            {
                file += u8"spell.s1"s;
                fsize = 800;
            }
            if (cnt == 4)
            {
                file += u8"inv.s1"s;
                fsize = 369600;
            }
            if (cnt == 5)
            {
                file += u8"kitem.s1"s;
                fsize = 9600;
            }
            if (cnt == 6)
            {
                file += u8"knpc.s1"s;
                fsize = 6400;
            }
            if (cnt == 7)
            {
                file += u8"adata.s1"s;
                fsize = 80000;
            }
            if (cnt == 8)
            {
                file += u8"spact.s1"s;
                fsize = 2000;
            }
            if (cnt == 9)
            {
                file += u8"qdata.s1"s;
                fsize = 40000;
            }
            if (cnt == 10)
            {
                file += u8"mat.s1"s;
                fsize = 1600;
            }
            if (cnt == 11)
            {
                file += u8"trait.s1"s;
                fsize = 2000;
            }
            if (cnt == 12)
            {
                file += u8"pcc.s1"s;
                fsize = 2400;
            }
            if (cnt == 13)
            {
                file += u8"card.s1"s;
                fsize = 16000;
            }
            if (cnt == 14)
            {
                file += u8"krecipe.s1"s;
                fsize = 4800;
            }
            if (elona::fread == 1)
            {
                if (!fs::exists(file))
                {
                    continue;
                }
            }
            if (elona::fread == 0)
            {
                zOpen(hgz, file, 1, 3);
            }
            if (elona::fread == 1)
            {
                zOpen(hgz, file, 0);
            }
            if (cnt == 0)
            {
                if (elona::fread == 0)
                {
                    zWrite(gdata, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(gdata, hgz, fsize);
                }
            }
            if (cnt == 1)
            {
                if (elona::fread == 0)
                {
                    zWrite(cdata, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(cdata, hgz, fsize);
                }
            }
            if (cnt == 2)
            {
                if (elona::fread == 0)
                {
                    zWrite(sdata, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(sdata, hgz, fsize);
                }
            }
            if (cnt == 3)
            {
                if (elona::fread == 0)
                {
                    zWrite(spell, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(spell, hgz, fsize);
                }
            }
            if (cnt == 4)
            {
                if (elona::fread == 0)
                {
                    zWrite(inv, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(inv, hgz, fsize);
                }
            }
            if (cnt == 5)
            {
                if (elona::fread == 0)
                {
                    zWrite(itemmemory, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(itemmemory, hgz, fsize);
                }
            }
            if (cnt == 6)
            {
                if (elona::fread == 0)
                {
                    zWrite(npcmemory, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(npcmemory, hgz, fsize);
                }
            }
            if (cnt == 7)
            {
                if (elona::fread == 0)
                {
                    zWrite(adata, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(adata, hgz, fsize);
                }
            }
            if (cnt == 8)
            {
                if (elona::fread == 0)
                {
                    zWrite(spact, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(spact, hgz, fsize);
                }
            }
            if (cnt == 9)
            {
                if (elona::fread == 0)
                {
                    zWrite(qdata, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(qdata, hgz, fsize);
                }
            }
            if (cnt == 10)
            {
                if (elona::fread == 0)
                {
                    zWrite(mat, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(mat, hgz, fsize);
                }
            }
            if (cnt == 11)
            {
                if (elona::fread == 0)
                {
                    zWrite(trait, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(trait, hgz, fsize);
                }
            }
            if (cnt == 12)
            {
                if (elona::fread == 0)
                {
                    zWrite(pcc, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(pcc, hgz, fsize);
                }
            }
            if (cnt == 13)
            {
                if (elona::fread == 0)
                {
                    zWrite(card, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(card, hgz, fsize);
                }
            }
            if (cnt == 14)
            {
                if (elona::fread == 0)
                {
                    zWrite(recipememory, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    if (gdata_version >= 1200)
                    {
                        zRead(recipememory, hgz, fsize);
                    }
                }
            }
            zClose(hgz);
        }
    }
    file = folder + u8"art.log"s;
    if (elona::fread == 0)
    {
        std::ofstream out{file};
        range::for_each(artifactlocation, [&](const auto& line) {
            out << line << std::endl;
        });
    }
    if (elona::fread == 1)
    {
        artifactlocation.clear();
        range::copy(
            fileutil::read_by_line{file}, std::back_inserter(artifactlocation));
    }
    file = folder + u8"news.log"s;
    notesel(newsbuff);
    if (elona::fread == 0)
    {
        std::ofstream out{file};
        out << newsbuff(0) << std::endl;
    }
    if (elona::fread == 1)
    {
        newsbuff(0).clear();
        std::ifstream in{file};
        std::string tmp;
        while (std::getline(in, tmp))
        {
            newsbuff(0) += tmp + '\n';
        }
    }
    file = folder + u8"cdatan.s1"s;
    arrayfile(u8"cdatan1");
    file = folder + u8"qname.s1"s;
    arrayfile(u8"qname");
    file = folder + u8"gdatan.s1"s;
    arrayfile(u8"gdatan");
    if (elona::fread == 0)
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


void fmode_14_15(int fmode)
{
    int fsize = 0;
    if (fmode == 14)
    {
        elona::fread = 0;
        folder = fs::u8path(u8"./tmp/");
    }
    if (fmode == 15)
    {
        elona::fread = 1;
        folder = fs::u8path(u8"./save/"s + geneuse + u8"/");
    }
    if (fmode == 14)
    {
        playerheader =
            ""s + cdatan(0, 0) + u8"(Lv"s + cdata_level(0) + u8")の遺伝子"s;
        file = folder + u8"gene_header.txt"s;
        bsave(file, playerheader);
        fileadd(file);
    }
    {
        int cnt = 0;
        for (int cnt_end = cnt + (9); cnt < cnt_end; ++cnt)
        {
            file = folder;
            if (cnt == 0)
            {
                file += u8"gene.s1"s;
                fsize = 400;
            }
            if (cnt == 1)
            {
                file += u8"g_cdata.s1"s;
                fsize = 114000;
            }
            if (cnt == 2)
            {
                file += u8"g_sdata.s1"s;
                fsize = 273600;
            }
            if (cnt == 3)
            {
                file += u8"g_spell.s1"s;
                fsize = 800;
            }
            if (cnt == 4)
            {
                file += u8"g_inv.s1"s;
                fsize = 369600;
            }
            if (cnt == 5)
            {
                file += u8"g_spact.s1"s;
                fsize = 2000;
            }
            if (cnt == 6)
            {
                file += u8"g_mat.s1"s;
                fsize = 1600;
            }
            if (cnt == 7)
            {
                file += u8"g_card.s1"s;
                fsize = 16000;
            }
            if (cnt == 8)
            {
                file += u8"g_genetemp.s1"s;
                fsize = 4000;
            }
            if (elona::fread == 1)
            {
                if (!fs::exists(file))
                {
                    continue;
                }
            }
            if (elona::fread == 0)
            {
                zOpen(hgz, file, 1, 3);
                fileadd(""s + file);
            }
            if (elona::fread == 1)
            {
                zOpen(hgz, file, 0);
            }
            if (cnt == 1)
            {
                if (elona::fread == 0)
                {
                    zWrite(cdata, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(cdata, hgz, fsize);
                }
            }
            if (cnt == 2)
            {
                if (elona::fread == 0)
                {
                    zWrite(sdata, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(sdata, hgz, fsize);
                }
            }
            if (cnt == 3)
            {
                if (elona::fread == 0)
                {
                    zWrite(spell, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(spell, hgz, fsize);
                }
            }
            if (cnt == 4)
            {
                if (elona::fread == 0)
                {
                    zWrite(inv, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(inv, hgz, fsize);
                }
            }
            if (cnt == 5)
            {
                if (elona::fread == 0)
                {
                    zWrite(spact, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(spact, hgz, fsize);
                }
            }
            if (cnt == 6)
            {
                if (elona::fread == 0)
                {
                    zWrite(mat, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(mat, hgz, fsize);
                }
            }
            if (cnt == 7)
            {
                if (elona::fread == 0)
                {
                    zWrite(card, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(card, hgz, fsize);
                }
            }
            if (cnt == 8)
            {
                if (elona::fread == 0)
                {
                    zWrite(gdata, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(genetemp, hgz, fsize);
                }
            }
            zClose(hgz);
        }
    }
}


void fmode_2_1(int fmode)
{
    int fsize = 0;
    folder = fs::u8path(u8"./tmp/");
    if (fmode == 2)
    {
        elona::fread = 0;
    }
    if (fmode == 1)
    {
        elona::fread = 1;
    }
    {
        int cnt = 0;
        for (int cnt_end = cnt + (5); cnt < cnt_end; ++cnt)
        {
            file = folder;
            if (cnt == 0)
            {
                file += u8"mdata_"s + mid + u8".s2"s;
                fsize = 400;
            }
            if (cnt == 1)
            {
                if (elona::fread == 1)
                {
                    DIM4(map, mdata(0), mdata(1), 10);
                    DIM3(mapsync, mdata(0), mdata(1));
                    DIM3(mef, 9, 200);
                }
                file += u8"map_"s + mid + u8".s2"s;
                fsize = mdata(0) * mdata(1) * 10 * 4;
            }
            if (cnt == 2)
            {
                file += u8"cdata_"s + mid + u8".s2"s;
                fsize = 376000;
            }
            if (cnt == 3)
            {
                file += u8"sdata_"s + mid + u8".s2"s;
                fsize = 902400;
            }
            if (cnt == 4)
            {
                if (elona::fread)
                {
                    if (mdata(21) == 0)
                    {
                        {
                            int cnt = 0;
                            for (int cnt_end = cnt + (mdata(1)); cnt < cnt_end;
                                 ++cnt)
                            {
                                cnt2 = cnt;
                                {
                                    int cnt = 0;
                                    for (int cnt_end = cnt + (mdata(0));
                                         cnt < cnt_end;
                                         ++cnt)
                                    {
                                        map(cnt, cnt2, 8) = 0;
                                    }
                                }
                            }
                        }
                        mdata(21) = 1;
                        continue;
                    }
                }
                file += u8"mef_"s + mid + u8".s2"s;
                fsize = 7200;
            }
            if (elona::fread == 0)
            {
                zOpen(hgz, file, 1, 3);
                fileadd(""s + file);
            }
            if (elona::fread == 1)
            {
                zOpen(hgz, file, 0);
            }
            if (cnt == 0)
            {
                if (elona::fread == 0)
                {
                    zWrite(mdata, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(mdata, hgz, fsize);
                }
            }
            if (cnt == 1)
            {
                if (elona::fread == 0)
                {
                    zWrite(map, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(map, hgz, fsize);
                }
            }
            if (cnt == 2)
            {
                if (elona::fread == 0)
                {
                    zWrite(cdata, hgz, fsize, 57);
                }
                if (elona::fread == 1)
                {
                    zRead(cdata, hgz, fsize, 57);
                }
            }
            if (cnt == 3)
            {
                if (elona::fread == 0)
                {
                    zWrite(sdata, hgz, fsize, 57);
                }
                if (elona::fread == 1)
                {
                    zRead(sdata, hgz, fsize, 57);
                }
            }
            if (cnt == 4)
            {
                if (elona::fread == 0)
                {
                    zWrite(mef, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(mef, hgz, fsize);
                }
            }
            zClose(hgz);
        }
    }
    file = folder + u8"cdatan_"s + mid + u8".s2"s;
    arrayfile(u8"cdatan2");
    file = folder + u8"mdatan_"s + mid + u8".s2"s;
    arrayfile(u8"mdatan");
}


void fmode_20_19(int fmode)
{
    int fsize = 0;
    folder = fs::u8path(u8"./user/");
    if (fmode == 20)
    {
        elona::fread = 0;
    }
    if (fmode == 19)
    {
        elona::fread = 1;
    }
    {
        int cnt = 0;
        for (int cnt_end = cnt + (3); cnt < cnt_end; ++cnt)
        {
            file = folder;
            if (cnt == 0)
            {
                file += u8"m1_"s + id + u8".t"s;
                fsize = 400;
            }
            if (cnt == 1)
            {
                if (elona::fread == 1)
                {
                    DIM4(map, mdata(0), mdata(1), 10);
                    DIM3(mapsync, mdata(0), mdata(1));
                    DIM3(mef, 9, 200);
                }
                file += u8"m2_"s + id + u8".t"s;
                fsize = mdata(0) * mdata(1) * 10 * 4;
            }
            if (cnt == 2)
            {
                file += u8"m3_"s + id + u8".t"s;
                fsize = 1164800;
            }
            if (elona::fread == 0)
            {
                zOpen(hgz, file, 1, 3);
            }
            if (elona::fread == 1)
            {
                zOpen(hgz, file, 0);
            }
            if (cnt == 0)
            {
                if (elona::fread == 0)
                {
                    zWrite(mdata, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(mdata, hgz, fsize);
                }
            }
            if (cnt == 1)
            {
                if (elona::fread == 0)
                {
                    zWrite(map, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(map, hgz, fsize);
                }
            }
            if (cnt == 2)
            {
                if (elona::fread == 0)
                {
                    zWrite(inv, hgz, fsize, 1320);
                }
                if (elona::fread == 1)
                {
                    zRead(inv, hgz, fsize, 1320);
                }
            }
            zClose(hgz);
        }
    }
    file = folder + u8"m4_"s + id + u8".t"s;
    elona_export = 1;
    arrayfile(u8"mdatan");
    if (elona::fread == 0)
    {
        zipadd(u8"m1_"s + id + u8".t"s);
        zipadd(u8"m2_"s + id + u8".t"s);
        zipadd(u8"m3_"s + id + u8".t"s);
        zipadd(u8"m4_"s + id + u8".t"s);
    }
}


void fmode_22_21(int fmode)
{
    int fsize = 0;
    folder = fs::u8path(u8"./user/");
    if (fmode == 22)
    {
        elona::fread = 0;
        tg = 1;
    }
    if (fmode == 21)
    {
        elona::fread = 1;
        tg = 0;
    }
    enemyteam = -1;
    gdata(86) = 0;
    SDIM1(untaglist);
    {
        int cnt = 0;
        for (int cnt_end = cnt + (245); cnt < cnt_end; ++cnt)
        {
            if (elona::fread == 0)
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
                {
                    int cnt = 57;
                    for (int cnt_end = cnt + (188); cnt < cnt_end; ++cnt)
                    {
                        if (cdata_state(cnt) == 0)
                        {
                            tg = cnt;
                            break;
                        }
                    }
                }
                if (tg == 0)
                {
                    break;
                }
            }
            {
                int cnt = 0;
                for (int cnt_end = cnt + (3); cnt < cnt_end; ++cnt)
                {
                    file = folder;
                    if (cnt == 0)
                    {
                        file += u8"c1_"s + id + u8".t"s;
                        fsize = 2000;
                    }
                    if (cnt == 1)
                    {
                        file += u8"c2_"s + id + u8".t"s;
                        fsize = 4800;
                    }
                    if (cnt == 2)
                    {
                        file += u8"c3_"s + id + u8".t"s;
                        inv_getheader(tg);
                        fsize = 280 * invrange;
                    }
                    if (elona::fread == 0)
                    {
                        zOpen(hgz, file, 1, 3);
                    }
                    if (elona::fread == 1)
                    {
                        zOpen(hgz, file, 0);
                    }
                    if (cnt == 0)
                    {
                        if (elona::fread == 0)
                        {
                            zWrite(cdata, hgz, fsize, tg);
                        }
                        if (elona::fread == 1)
                        {
                            zRead(cdata, hgz, fsize, tg);
                        }
                    }
                    if (cnt == 1)
                    {
                        if (elona::fread == 0)
                        {
                            zWrite(sdata, hgz, fsize, tg);
                        }
                        if (elona::fread == 1)
                        {
                            zRead(sdata, hgz, fsize, tg);
                        }
                    }
                    if (cnt == 2)
                    {
                        if (elona::fread == 0)
                        {
                            zWrite(inv, hgz, fsize, invhead);
                        }
                        if (elona::fread == 1)
                        {
                            zRead(inv, hgz, fsize, invhead);
                        }
                    }
                    zClose(hgz);
                }
            }
            file = folder + u8"c4_"s + id + u8".t"s;
            elona_export = 1;
            arrayfile(u8"cdatan3");
            if (elona::fread == 0)
            {
                zipadd(u8"c1_"s + id + u8".t"s);
                zipadd(u8"c2_"s + id + u8".t"s);
                zipadd(u8"c3_"s + id + u8".t"s);
                zipadd(u8"c4_"s + id + u8".t"s);
                if (cdata_id(tg) == 343)
                {
                    if (fs::exists(folder + userdatan(6, cdata_cnpc_id(tg))))
                    {
                        if (cdata_cnpc_id(tg) != usernpcmax)
                        {
                            if (instr(
                                    untaglist,
                                    0,
                                    u8"/"s + userdatan(0, cdata_cnpc_id(tg))
                                        + u8"/"s)
                                == -1)
                            {
                                if (gdata(86) < 10)
                                {
                                    bcopy(
                                        folder
                                            + userdatan(6, cdata_cnpc_id(tg)),
                                        folder + u8"_tmp_"s + gdata(86)
                                            + u8".npc"s);
                                    zipadd(u8"_tmp_"s + gdata(86) + u8".npc"s);
                                    untaglist += u8"/"s
                                        + userdatan(0, cdata_cnpc_id(tg))
                                        + u8"/"s;
                                    ++gdata(86);
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                inv_getheader(tg);
                {
                    int cnt = invhead;
                    for (int cnt_end = cnt + (invrange); cnt < cnt_end; ++cnt)
                    {
                        inv_body_part(cnt) = 0;
                    }
                }
                {
                    int cnt = 100;
                    for (int cnt_end = cnt + (30); cnt < cnt_end; ++cnt)
                    {
                        cdata_body_part(tg, cnt) =
                            cdata_body_part(tg, cnt) / 10000 * 10000;
                    }
                }
                rc = tg;
                label_2666();
                cdata_item_which_will_be_used(rc) = 0;
                rowactend(rc);
                cbitmod(967, rc, 0);
                cbitmod(968, rc, 0);
                cdata_hp(rc) = cdata_max_hp(rc);
                cdata_mp(rc) = cdata_max_mp(rc);
                cbitmod(960, rc, 0);
                cbitmod(989, tc, 0);
                if (importmode == 0)
                {
                    cdata_character_role(tg) = 20;
                    cdata_gold(tg) = 0;
                    if (cdata_relationship(tg) >= 10)
                    {
                        if (userrelation == 0)
                        {
                            cdata_relationship(tg) = 0;
                            cdata_original_relationship(tg) = 0;
                        }
                        else
                        {
                            cdata_relationship(tg) = -3;
                            cdata_original_relationship(tg) = -3;
                        }
                    }
                    cxinit = cdata_x(tg);
                    cyinit = cdata_y(tg);
                    label_1532();
                }
                if (importmode == 1)
                {
                    if (enemyteam == -1)
                    {
                        enemyteam = rc;
                    }
                    cdata_relationship(rc) = -3;
                    cdata_original_relationship(rc) = -3;
                    map_placearena(rc, 1);
                }
            }
            ++id;
        }
    }
}


void fmode_16(int fmode)
{
    int fsize = 0;
    DIM3(cmapdata, 5, 400);
    {
        int cnt = 0;
        for (int cnt_end = cnt + (2); cnt < cnt_end; ++cnt)
        {
            if (cnt == 0)
            {
                file = fmapfile + u8".map"s;
                fsize = mdata(0) * mdata(1) * 3 * 4;
            }
            if (cnt == 1)
            {
                file = fmapfile + u8".obj"s;
                fsize = 8000;
            }
            if (cnt == 1)
            {
                if (!fs::exists(file))
                {
                    continue;
                }
            }
            zOpen(hgz, file, 0);
            if (cnt == 0)
            {
                zRead(map, hgz, fsize);
            }
            if (cnt == 1)
            {
                zRead(cmapdata, hgz, fsize);
            }
            zClose(hgz);
        }
    }
}


void fmode_6_5(int fmode)
{
    int fsize = 0;
    if (fmode == 6)
    {
        elona::fread = 0;
    }
    if (fmode == 5)
    {
        elona::fread = 1;
        DIM3(cmapdata, 5, 400);
    }
    {
        int cnt = 0;
        for (int cnt_end = cnt + (3); cnt < cnt_end; ++cnt)
        {
            if (cnt == 0)
            {
                file = fmapfile + u8".idx"s;
                fsize = 400;
            }
            if (cnt == 1)
            {
                if (elona::fread == 1)
                {
                    DIM4(map, mdata(0), mdata(1), 10);
                    DIM3(mapsync, mdata(0), mdata(1));
                    DIM3(mef, 9, 200);
                }
                file = fmapfile + u8".map"s;
                fsize = mdata(0) * mdata(1) * 10 * 4;
            }
            if (cnt == 2)
            {
                file = fmapfile + u8".obj"s;
                fsize = 8000;
            }
            if (cnt == 2 && elona::fread == 1)
            {
                if (!fs::exists(file))
                {
                    continue;
                }
            }
            if (elona::fread == 0)
            {
                zOpen(hgz, file, 1, 3);
            }
            if (elona::fread == 1)
            {
                zOpen(hgz, file, 0);
            }
            if (cnt == 0)
            {
                if (elona::fread == 0)
                {
                    zWrite(mdata, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(mdatatmp, hgz, fsize);
                    {
                        int cnt = 0;
                        for (int cnt_end = cnt + (5); cnt < cnt_end; ++cnt)
                        {
                            mdata(cnt) = mdatatmp(cnt);
                        }
                    }
                }
            }
            if (cnt == 1)
            {
                if (elona::fread == 0)
                {
                    zWrite(map, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(map, hgz, fsize);
                }
            }
            if (cnt == 2)
            {
                if (elona::fread == 0)
                {
                    zWrite(cmapdata, hgz, fsize);
                }
                if (elona::fread == 1)
                {
                    zRead(cmapdata, hgz, fsize);
                }
            }
            zClose(hgz);
        }
    }
}


void fmode_4_3(int fmode)
{
    int fsize = 0;
    folder = fs::u8path(u8"./tmp/");
    if (fmode == 4)
    {
        elona::fread = 0;
    }
    if (fmode == 3)
    {
        elona::fread = 1;
    }
    file = folder + file;
    fsize = 1164800;
    if (elona::fread == 0)
    {
        zOpen(hgz, file, 1, 3);
        fileadd(file);
    }
    if (elona::fread == 1)
    {
        zOpen(hgz, file, 0);
    }
    if (elona::fread == 0)
    {
        zWrite(inv, hgz, fsize, 1320);
    }
    if (elona::fread == 1)
    {
        zRead(inv, hgz, fsize, 1320);
    }
    zClose(hgz);
}



void fmode_23_24(int fmode)
{
    int fsize = 0;
    if (fmode == 23)
    {
        elona::fread = 0;
    }
    if (fmode == 24)
    {
        elona::fread = 1;
    }
    fsize = 4000;
    if (elona::fread == 0)
    {
        zOpen(hgz, file, 1, 3);
        fileadd(""s + file);
    }
    if (elona::fread == 1)
    {
        zOpen(hgz, file, 0);
    }
    if (elona::fread == 0)
    {
        zWrite(deck, hgz, fsize);
    }
    if (elona::fread == 1)
    {
        zRead(deck, hgz, fsize);
    }
    zClose(hgz);
}


void fmode_18_17(int fmode)
{
    int fsize = 0;
    folder = fs::u8path(u8"./tmp/");
    if (fmode == 18)
    {
        elona::fread = 0;
    }
    if (fmode == 17)
    {
        elona::fread = 1;
    }
    if (!fs::exists(file + u8"cdata_"s + mid + u8".s2"s))
    {
        return;
    }
    {
        int cnt = 0;
        for (int cnt_end = cnt + (5); cnt < cnt_end; ++cnt)
        {
            file = folder;
            if (cnt == 0)
            {
                file += u8"cdata_"s + mid + u8".s2"s;
                fsize = 376000;
            }
            if (cnt == 1)
            {
                file += u8"sdata_"s + mid + u8".s2"s;
                fsize = 902400;
            }
            if (elona::fread == 0)
            {
                zOpen(hgz, file, 1, 3);
                fileadd(""s + file);
            }
            if (elona::fread == 1)
            {
                zOpen(hgz, file, 0);
            }
            if (cnt == 0)
            {
                if (elona::fread == 0)
                {
                    zWrite(cdata, hgz, fsize, 57);
                }
                if (elona::fread == 1)
                {
                    zRead(cdata, hgz, fsize, 57);
                }
            }
            if (cnt == 1)
            {
                if (elona::fread == 0)
                {
                    zWrite(sdata, hgz, fsize, 57);
                }
                if (elona::fread == 1)
                {
                    zRead(sdata, hgz, fsize, 57);
                }
            }
            zClose(hgz);
        }
    }
    file = folder + u8"cdatan_"s + mid + u8".s2"s;
    arrayfile(u8"cdatan2");
}


void fmode_10(int fmode)
{
    int fsize = 0;
    bool no_file = true;
    for (const auto& entry : filesystem::dir_entries(
             fs::u8path(u8"./tmp"),
             filesystem::dir_entries::type::file,
             std::regex{u8R"(.*\..*)"}))
    {
        no_file = false;
        elona_delete(entry.path());
    }
    if (no_file)
        return;
}


void fmode_9(int fmode)
{
    int fsize = 0;
    elona_delete(fs::u8path(u8"./save/"s + playerid));
}


void fmode_11_12(int fmode)
{
    int fsize = 0;
    if (fmode == 12)
    {
        if (!fs::exists(fs::u8path(u8"./tmp/mdata_"s + mid + u8".s2")))
        {
            return;
        }
    }
    file = fs::u8path(u8"./tmp/map_"s + mid + u8".s2");
    if (!fs::exists(file))
    {
        return;
    }
    elona_delete(file);
    fileadd(file, 1);
    if (fmode == 11)
    {
        file = fs::u8path(u8"./tmp/cdata_"s + mid + u8".s2");
        elona_delete(file);
        fileadd(file, 1);
        file = fs::u8path(u8"./tmp/sdata_"s + mid + u8".s2");
        elona_delete(file);
        fileadd(file, 1);
        file = fs::u8path(u8"./tmp/cdatan_"s + mid + u8".s2");
        elona_delete(file);
        fileadd(file, 1);
        file = fs::u8path(u8"./tmp/inv_"s + mid + u8".s2");
        elona_delete(file);
        fileadd(file, 1);
    }
    file = fs::u8path(u8"./tmp/mdata_"s + mid + u8".s2");
    elona_delete(file);
    fileadd(file, 1);
    file = fs::u8path(u8"./tmp/mdatan_"s + mid + u8".s2");
    elona_delete(file);
    fileadd(file, 1);
    file = fs::u8path(u8"./tmp/mef_"s + mid + u8".s2");
    elona_delete(file);
    fileadd(file, 1);
}


void fmode_13(int fmode)
{
    int fsize = 0;
    {
        int cnt = 0;
        for (int cnt_end = cnt + (40); cnt < cnt_end; ++cnt)
        {
            adata(cnt, area) = 0;
        }
    }
    for (const auto& entry : filesystem::dir_entries(
             fs::u8path(u8"./tmp"),
             filesystem::dir_entries::type::file,
             std::regex{u8R"(.*_)"s + area + u8R"(_.*\..*)"}))
    {
        elona_delete(entry.path());
        fileadd(entry.path().generic_u8string(), 1);
    }
}



} // namespace


namespace elona
{


void ctrl_file(int mode)
{
    notesel(filemod);
    gdata_play_time = gdata_play_time + timeGetTime() / 1000 - time_begin;
    time_begin = timeGetTime() / 1000;

    switch (mode)
    {
    case 8:
    case 7: fmode_8_7(mode); break;
    case 14:
    case 15: fmode_14_15(mode); break;
    case 2:
    case 1: fmode_2_1(mode); break;
    case 20:
    case 19: fmode_20_19(mode); break;
    case 22:
    case 21: fmode_22_21(mode); break;
    case 16: fmode_16(mode); break;
    case 6:
    case 5: fmode_6_5(mode); break;
    case 4:
    case 3: fmode_4_3(mode); break;
    case 23:
    case 24: fmode_23_24(mode); break;
    case 18:
    case 17: fmode_18_17(mode); break;
    case 10: fmode_10(mode); break;
    case 9: fmode_9(mode); break;
    case 11:
    case 12: fmode_11_12(mode); break;
    case 13: fmode_13(mode); break;
    default: assert(0);
    }
}



} // namespace elona
