#include "ctrl_file.hpp"
#include "ability.hpp"
#include "character.hpp"
#include "elona.hpp"
#include "filesystem.hpp"
#include "foobar_save.hpp"
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
    std::ifstream in{filepath.native(), std::ios::binary};
	if (in.fail()) {
		throw std::runtime_error(u8"Could not open file at "s + filepath.string());
	}
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
    std::ofstream out{filepath.native(), std::ios::binary};
	if (out.fail()) {
		throw std::runtime_error(u8"Could not open file at "s + filepath.string());
	}
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
    std::ifstream in{filepath.native(), std::ios::binary};
	if (in.fail()) {
		throw std::runtime_error(u8"Could not open file at "s + filepath.string());
	}
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
    std::ofstream out{filepath.native(), std::ios::binary};
	if (out.fail()) {
		throw std::runtime_error(u8"Could not open file at "s + filepath.string());
	}
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
    std::ifstream in{filepath.native(), std::ios::binary};
	if (in.fail()) {
		throw std::runtime_error(u8"Could not open file at "s + filepath.string());
	}
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
    std::ofstream out{filepath.native(), std::ios::binary};
	if (out.fail()) {
		throw std::runtime_error(u8"Could not open file at "s + filepath.string());
	}
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
    std::ifstream in{filepath.native(), std::ios::binary};
	if (in.fail()) {
		throw std::runtime_error(u8"Could not open file at "s + filepath.string());
	}
    putit::binary_iarchive ar{in};
    for (size_t i = begin; i < end; ++i)
    {
        ar.load(data[i]);
    }
}


template <typename T>
void save(const fs::path& filepath, T& data, size_t begin, size_t end)
{
    std::ofstream out{filepath.native(), std::ios::binary};
	if (out.fail()) {
		throw std::runtime_error(u8"Could not open file at "s + filepath.string());
	}
    putit::binary_oarchive ar{out};
    for (size_t i = begin; i < end; ++i)
    {
        ar.save(data[i]);
    }
}



void fmode_7_8(bool read)
{
    const auto dir = filesystem::dir::save(playerid);
	if (!fs::exists(dir)) {
		fs::create_directory(dir);
	}

    if (!read)
    {
        playerheader =
            cdatan(0, 0) + u8" Lv:" + cdata[0].level + u8" " + mdatan(0);
        bsave(dir / u8"header.txt", playerheader);
    }

    {
        const auto filepath = dir / u8"gdata.s1";
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
        const auto filepath = dir / u8"foobar_save.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                std::ifstream in{filepath.native(), std::ios::binary};
                putit::binary_iarchive ar{in};
                ar.load(foobar_save);
            }
        }
        else
        {
            std::ofstream out{filepath.native(), std::ios::binary};
            putit::binary_oarchive ar{out};
            ar.save(foobar_save);
        }
    }

    {
        const auto filepath = dir / u8"cdata.s1";
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
        const auto filepath = dir / u8"sdata.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                std::ifstream in{filepath.native(), std::ios::binary};
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
            std::ofstream out{filepath.native(), std::ios::binary};
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
        const auto filepath = dir / u8"spell.s1";
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
        const auto filepath = dir / u8"inv.s1";
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
        const auto filepath = dir / u8"kitem.s1";
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
        const auto filepath = dir / u8"knpc.s1";
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
        const auto filepath = dir / u8"adata.s1";
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
        const auto filepath = dir / u8"spact.s1";
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
        const auto filepath = dir / u8"qdata.s1";
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
        const auto filepath = dir / u8"mat.s1";
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
        const auto filepath = dir / u8"trait.s1";
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
        const auto filepath = dir / u8"pcc.s1";
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
        const auto filepath = dir / u8"card.s1";
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
        const auto filepath = dir / u8"krecipe.s1";
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
        const auto filepath = dir / u8"art.log";
        if (!read)
        {
            std::ofstream out{filepath.native(), std::ios::binary};
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
        const auto filepath = dir / u8"news.log";
        notesel(newsbuff);
        if (!read)
        {
            std::ofstream out{filepath.native(), std::ios::binary};
            out << newsbuff(0) << std::endl;
        }
        if (read)
        {
            newsbuff(0).clear();
            std::ifstream in{filepath.native(), std::ios::binary};
            std::string tmp;
            while (std::getline(in, tmp))
            {
                newsbuff(0) += tmp + '\n';
            }
        }
    }

    arrayfile(read, u8"cdatan1", dir / u8"cdatan.s1");
    arrayfile(read, u8"qname", dir / u8"qname.s1");
    arrayfile(read, u8"gdatan", dir / u8"gdatan.s1");
    if (!read)
    {
        bsave(dir / u8"evnum.s1", evnum);
        bsave(dir / u8"evdata1.s1", evdata1);
        bsave(dir / u8"evdata2.s1", evdata2);
        bsave(dir / u8"evlist.s1", evlist);
    }
    else
    {
        if (fs::exists(dir / u8"evnum.s1"))
        {
            bload(dir / u8"evnum.s1", evnum);
        }
        if (fs::exists(dir / u8"evdata1.s1"))
        {
            bload(dir / u8"evdata1.s1", evdata1);
        }
        if (fs::exists(dir / u8"evdata2.s1"))
        {
            bload(dir / u8"evdata2.s1", evdata2);
        }
        if (fs::exists(dir / u8"evlist.s1"))
        {
            bload(dir / u8"evlist.s1", evlist);
        }
    }
}


void fmode_14_15(bool read)
{
    const auto dir =
        read ? filesystem::dir::save(geneuse) : filesystem::dir::tmp();
    if (!read)
    {
        playerheader = cdatan(0, 0) + u8"(Lv" + cdata[0].level + u8")の遺伝子";
        const auto filepath = dir / u8"gene_header.txt";
        bsave(filepath, playerheader);
        fileadd(filepath);
    }

    {
        const auto filepath = dir / u8"g_cdata.s1";
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
        const auto filepath = dir / u8"g_sdata.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                std::ifstream in{filepath.native(), std::ios::binary};
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
            fileadd(filepath);
            std::ofstream out{filepath.native(), std::ios::binary};
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
        const auto filepath = dir / u8"g_spell.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                load_v1(filepath, spell, 0, 200);
            }
        }
        else
        {
            fileadd(filepath);
            save_v1(filepath, spell, 0, 200);
        }
    }

    {
        const auto filepath = dir / u8"g_inv.s1";
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
        const auto filepath = dir / u8"g_spact.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                load_v1(filepath, spact, 0, 500);
            }
        }
        else
        {
            fileadd(filepath);
            save_v1(filepath, spact, 0, 500);
        }
    }

    {
        const auto filepath = dir / u8"g_mat.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                load_v1(filepath, mat, 0, 400);
            }
        }
        else
        {
            fileadd(filepath);
            save_v1(filepath, mat, 0, 400);
        }
    }

    {
        const auto filepath = dir / u8"g_card.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                load_v2(filepath, card, 0, 100, 0, 40);
            }
        }
        else
        {
            fileadd(filepath);
            save_v2(filepath, card, 0, 100, 0, 40);
        }
    }

    {
        const auto filepath = dir / u8"g_genetemp.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                load_v1(filepath, genetemp, 0, 1000);
            }
        }
        else
        {
            fileadd(filepath);
            save_v1(filepath, genetemp, 0, 1000);
        }
    }
}


void fmode_1_2(bool read)
{
    const auto dir = filesystem::dir::tmp();

    {
        const auto filepath = dir / (u8"mdata_"s + mid + u8".s2");
        if (read)
        {
            load_v1(filepath, mdata, 0, 100);
        }
        else
        {
            fileadd(filepath);
            save_v1(filepath, mdata, 0, 100);
        }
    }

    {
        const auto filepath = dir / (u8"map_"s + mid + u8".s2");
        if (read)
        {
            DIM4(map, mdata(0), mdata(1), 10);
            DIM3(mapsync, mdata(0), mdata(1));
            DIM3(mef, 9, 200);
            load_v3(filepath, map, 0, mdata(0), 0, mdata(1), 0, 10);
        }
        else
        {
            fileadd(filepath);
            save_v3(filepath, map, 0, mdata(0), 0, mdata(1), 0, 10);
        }
    }

    {
        const auto filepath = dir / (u8"cdata_"s + mid + u8".s2");
        if (read)
        {
            load(filepath, cdata, 57, ELONA_MAX_CHARACTERS);
        }
        else
        {
            fileadd(filepath);
            save(filepath, cdata, 57, ELONA_MAX_CHARACTERS);
        }
    }

    {
        const auto filepath = dir / (u8"sdata_"s + mid + u8".s2");
        if (read)
        {
            std::ifstream in{filepath.native(), std::ios::binary};
            putit::binary_iarchive ar{in};
            for (int cc = 57; cc < ELONA_MAX_CHARACTERS; ++cc)
            {
                for (int i = 0; i < 600; ++i)
                {
                    ar.load(sdata.get(i, cc));
                }
            }
        }
        else
        {
            fileadd(filepath);
            std::ofstream out{filepath.native(), std::ios::binary};
            putit::binary_oarchive ar{out};
            for (int cc = 57; cc < ELONA_MAX_CHARACTERS; ++cc)
            {
                for (int i = 0; i < 600; ++i)
                {
                    ar.save(sdata.get(i, cc));
                }
            }
        }
    }

    {
        const auto filepath = dir / (u8"mef_"s + mid + u8".s2");
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
            fileadd(filepath);
            save_v2(filepath, mef, 0, 9, 0, 200);
        }
    }

    arrayfile(read, u8"cdatan2", dir / (u8"cdatan_"s + mid + u8".s2"));
    arrayfile(read, u8"mdatan", dir / (u8"mdatan_"s + mid + u8".s2"));
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


void fmode_5_6(bool read)
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
            DIM3(mapsync, mdata(0), mdata(1)); // TODO length_exception
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


void fmode_3_4(bool read, const fs::path& filename)
{
    const auto filepath = filesystem::dir::tmp() / filename;
    if (read)
    {
        load(filepath, inv, 1320, 5480);
    }
    else
    {
        fileadd(filepath);
        save(filepath, inv, 1320, 5480);
    }
}



void fmode_23_24(bool read, const fs::path& filepath)
{
    if (read)
    {
        fileadd(filepath);
        save_v1(filepath, deck, 0, 1000);
    }
    else
    {
        load_v1(filepath, deck, 0, 1000);
    }
}


void fmode_17()
{
    const auto dir = filesystem::dir::tmp();

    if (!fs::exists(dir / (u8"cdata_"s + mid + u8".s2")))
        return;

    {
        const auto filepath = dir / (u8"cdata_"s + mid + u8".s2");
        if (true)
        {
            load(filepath, cdata, 57, ELONA_MAX_CHARACTERS);
        }
        else
        {
            fileadd(filepath);
            save(filepath, cdata, 57, ELONA_MAX_CHARACTERS);
        }
    }

    {
        const auto filepath = dir / (u8"sdata_"s + mid + u8".s2");
        if (true)
        {
            std::ifstream in{filepath.native(), std::ios::binary};
            putit::binary_iarchive ar{in};
            for (int cc = 57; cc < ELONA_MAX_CHARACTERS; ++cc)
            {
                for (int i = 0; i < 600; ++i)
                {
                    ar.load(sdata.get(i, cc));
                }
            }
        }
        else
        {
            fileadd(filepath);
            std::ofstream out{filepath.native(), std::ios::binary};
            putit::binary_oarchive ar{out};
            for (int cc = 57; cc < ELONA_MAX_CHARACTERS; ++cc)
            {
                for (int i = 0; i < 600; ++i)
                {
                    ar.save(sdata.get(i, cc));
                }
            }
        }
    }

    arrayfile(true, u8"cdatan2", dir / (u8"cdatan_"s + mid + u8".s2"));
}


void fmode_10()
{
    for (const auto& entry : filesystem::dir_entries(
             filesystem::dir::tmp(),
             filesystem::dir_entries::type::file,
             std::regex{u8R"(.*\..*)"}))
    {
        elona_delete(entry.path());
    }
}


void fmode_9()
{
    elona_delete(filesystem::dir::save(playerid));
}


void fmode_11_12(file_operation_t file_operation)
{
    if (file_operation == file_operation_t::_12)
    {
        if (!fs::exists(filesystem::dir::tmp() / (u8"mdata_"s + mid + u8".s2")))
        {
            return;
        }
    }
    auto filepath = filesystem::dir::tmp() / (u8"map_"s + mid + u8".s2");
    if (!fs::exists(filepath))
        return;

    elona_delete(filepath);
    fileadd(filepath, 1);
    if (file_operation == file_operation_t::_11)
    {
        filepath = filesystem::dir::tmp() / (u8"cdata_"s + mid + u8".s2");
        elona_delete(filepath);
        fileadd(filepath, 1);
        filepath = filesystem::dir::tmp() / (u8"sdata_"s + mid + u8".s2");
        elona_delete(filepath);
        fileadd(filepath, 1);
        filepath = filesystem::dir::tmp() / (u8"cdatan_"s + mid + u8".s2");
        elona_delete(filepath);
        fileadd(filepath, 1);
        filepath = filesystem::dir::tmp() / (u8"inv_"s + mid + u8".s2");
        elona_delete(filepath);
        fileadd(filepath, 1);
    }
    filepath = filesystem::dir::tmp() / (u8"mdata_"s + mid + u8".s2");
    elona_delete(filepath);
    fileadd(filepath, 1);
    filepath = filesystem::dir::tmp() / (u8"mdatan_"s + mid + u8".s2");
    elona_delete(filepath);
    fileadd(filepath, 1);
    filepath = filesystem::dir::tmp() / (u8"mef_"s + mid + u8".s2");
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
             filesystem::dir::tmp(),
             filesystem::dir_entries::type::file,
             std::regex{u8R"(.*_)"s + area + u8R"(_.*\..*)"}))
    {
        elona_delete(entry.path());
        fileadd(entry.path(), 1);
    }
}



} // namespace


namespace elona
{


void ctrl_file(file_operation_t file_operation)
{
    notesel(filemod);
    gdata_play_time = gdata_play_time + timeGetTime() / 1000 - time_begin;
    time_begin = timeGetTime() / 1000;

    switch (file_operation)
    {
    case file_operation_t::_1:
    case file_operation_t::_2:
        fmode_1_2(file_operation == file_operation_t::_1);
        break;
    case file_operation_t::_5:
    case file_operation_t::_6:
        fmode_5_6(file_operation == file_operation_t::_5);
        break;
    case file_operation_t::_7:
    case file_operation_t::_8:
        fmode_7_8(file_operation == file_operation_t::_7);
        break;
    case file_operation_t::_9: fmode_9(); break;
    case file_operation_t::_10: fmode_10(); break;
    case file_operation_t::_11:
    case file_operation_t::_12: fmode_11_12(file_operation); break;
    case file_operation_t::_13: fmode_13(); break;
    case file_operation_t::_14:
    case file_operation_t::_15:
        fmode_14_15(file_operation == file_operation_t::_15);
        break;
    case file_operation_t::_17: fmode_17(); break;
    case file_operation_t::_16: fmode_16(); break;
    default: assert(0);
    }
}


void ctrl_file(file_operation2_t file_operation, const fs::path& filepath)
{
    notesel(filemod);
    gdata_play_time = gdata_play_time + timeGetTime() / 1000 - time_begin;
    time_begin = timeGetTime() / 1000;

    switch (file_operation)
    {
    case file_operation2_t::_3:
    case file_operation2_t::_4:
        fmode_3_4(file_operation == file_operation2_t::_3, filepath);
        break;
    case file_operation2_t::_23:
    case file_operation2_t::_24:
        fmode_23_24(file_operation == file_operation2_t::_24, filepath);
        break;
    default: assert(0);
    }
}



} // namespace elona
