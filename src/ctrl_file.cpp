#include "ctrl_file.hpp"
#include <set>
#include "ability.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "elona.hpp"
#include "filesystem.hpp"
#include "item.hpp"
#include "log.hpp"
#include "lua_env/lua_env.hpp"
#include "mef.hpp"
#include "putit.hpp"
#include "variables.hpp"

using namespace elona;


namespace
{


std::set<fs::path> loaded_files;



void arrayfile_read(const std::string& fmode_str, const fs::path& filepath)
{
    std::vector<std::string> lines;
    if (fs::exists(filepath))
    {
        range::copy(
            fileutil::read_by_line(filepath), std::back_inserter(lines));
    }

    if (fmode_str == u8"qname"s)
    {
        lines.resize(500);
        auto itr = std::begin(lines);
        for (int i = 0; i < 500; ++i)
        {
            qname(i) = *itr;
            ++itr;
        }
    }
    else if (fmode_str == u8"gdatan"s)
    {
        lines.resize(50);
        auto itr = std::begin(lines);
        for (int i = 0; i < 50; ++i)
        {
            gdatan(i) = *itr;
            ++itr;
        }
    }
    else if (fmode_str == u8"mdatan"s)
    {
        lines.resize(2);
        auto itr = std::begin(lines);
        for (int i = 0; i < 2; ++i)
        {
            mdatan(i) = *itr;
            ++itr;
        }
    }
    else if (fmode_str == u8"cdatan1"s)
    {
        if (lines.size() <= 57 * 10 / 2)
            lines.resize(57 * 10 / 2);
        else
            lines.resize(57 * 10);
        auto itr = std::begin(lines);
        for (int i = 0; i < 57; ++i)
        {
            for (int j = 0; j < 10; ++j)
            {
                if (lines.size() <= 57 * 10 / 2 && j >= 10 / 2)
                    break;
                cdatan(j, i) = *itr;
                ++itr;
            }
        }
    }
    else if (fmode_str == u8"cdatan2"s)
    {
        if (lines.size() <= 188 * 10 / 2)
            lines.resize(188 * 10 / 2);
        else
            lines.resize(188 * 10);
        auto itr = std::begin(lines);
        for (int i = ELONA_MAX_PARTY_CHARACTERS; i < ELONA_MAX_CHARACTERS; ++i)
        {
            for (int j = 0; j < 10; ++j)
            {
                if (lines.size() <= 188 * 10 / 2 && j >= 10 / 2)
                    break;
                cdatan(j, i) = *itr;
                ++itr;
            }
        }
    }
    else if (fmode_str == u8"cdatan3"s)
    {
        if (lines.size() <= 10 / 2)
            lines.resize(10 / 2);
        else
            lines.resize(10);
        auto itr = std::begin(lines);
        for (int j = 0; j < 10; ++j)
        {
            if (lines.size() < 10 / 2 && j >= 10 / 2)
                break;
            cdatan(j, tg) = *itr;
            ++itr;
        }
    }
}



void arrayfile_write(const std::string& fmode_str, const fs::path& filepath)
{
    std::ofstream out{filepath.native(), std::ios::binary};
    if (!out)
    {
        throw std::runtime_error(
            u8"Error: fail to write "
            + filesystem::make_preferred_path_in_utf8(filepath));
    }

    if (fmode_str == u8"qname"s)
    {
        for (int i = 0; i < 500; ++i)
        {
            out << qname(i) << std::endl;
        }
    }
    else if (fmode_str == u8"gdatan"s)
    {
        for (int i = 0; i < 50; ++i)
        {
            out << gdatan(i) << std::endl;
        }
    }
    else if (fmode_str == u8"mdatan"s)
    {
        for (int i = 0; i < 2; ++i)
        {
            out << mdatan(i) << std::endl;
        }
    }
    else if (fmode_str == u8"cdatan1"s)
    {
        for (int i = 0; i < 57; ++i)
        {
            for (int j = 0; j < 10; ++j)
            {
                out << cdatan(j, i) << std::endl;
            }
        }
    }
    else if (fmode_str == u8"cdatan2"s)
    {
        for (int i = ELONA_MAX_PARTY_CHARACTERS; i < ELONA_MAX_CHARACTERS; ++i)
        {
            for (int j = 0; j < 10; ++j)
            {
                out << cdatan(j, i) << std::endl;
            }
        }
    }
    else if (fmode_str == u8"cdatan3"s)
    {
        for (int j = 0; j < 10; ++j)
        {
            out << cdatan(j, tg) << std::endl;
        }
    }

    writeloadedbuff(filepath.filename());
    if (elona_export == 0)
    {
        Save::instance().add(filepath.filename());
    }
}



void arrayfile(
    bool fread,
    const std::string& fmode_str,
    const fs::path& filepath)
{
    if (!fread)
    {
        ELONA_LOG("arrayfile_write: " << filepath);
        arrayfile_write(fmode_str, filepath);
    }
    else
    {
        tmpload(filepath.filename());
        arrayfile_read(fmode_str, filepath);
    }

    elona_export = 0;
}


template <typename T>
void load_v1(
    const fs::path& filepath,
    elona_vector1<T>& data,
    size_t begin,
    size_t end,
    bool gzip = false)
{
    std::ifstream in{filepath.native(), std::ios::binary};
    if (in.fail())
    {
        ELONA_LOG("error:could not open file at");
        throw std::runtime_error(
            u8"Could not open file at "s + filepath.string());
    }
    putit::BinaryIArchive ar(in, gzip);
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
    size_t end,
    bool gzip = false)
{
    std::ofstream out{filepath.native(), std::ios::binary};
    if (out.fail())
    {
        throw std::runtime_error(
            u8"Could not open file at "s + filepath.string());
    }
    putit::BinaryOArchive ar(out, gzip);
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
    size_t j_end,
    bool gzip = false)
{
    std::ifstream in{filepath.native(), std::ios::binary};
    if (in.fail())
    {
        throw std::runtime_error(
            u8"Could not open file at "s + filepath.string());
    }
    putit::BinaryIArchive ar{in, gzip};
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
    size_t j_end,
    bool gzip = false)
{
    std::ofstream out{filepath.native(), std::ios::binary};
    if (out.fail())
    {
        throw std::runtime_error(
            u8"Could not open file at "s + filepath.string());
    }
    putit::BinaryOArchive ar{out, gzip};
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
    size_t k_end,
    bool gzip = false)
{
    std::ifstream in{filepath.native(), std::ios::binary};
    if (in.fail())
    {
        throw std::runtime_error(
            u8"Could not open file at "s + filepath.string());
    }
    putit::BinaryIArchive ar{in, gzip};
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
    size_t k_end,
    bool gzip = false)
{
    std::ofstream out{filepath.native(), std::ios::binary};
    if (out.fail())
    {
        throw std::runtime_error(
            u8"Could not open file at "s + filepath.string());
    }
    putit::BinaryOArchive ar{out, gzip};
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
    if (in.fail())
    {
        throw std::runtime_error(
            u8"Could not open file at "s + filepath.string());
    }
    putit::BinaryIArchive ar{in};
    for (size_t i = begin; i < end; ++i)
    {
        ar.load(data[i]);
    }
}


template <typename T>
void save(const fs::path& filepath, T& data, size_t begin, size_t end)
{
    std::ofstream out{filepath.native(), std::ios::binary};
    if (out.fail())
    {
        throw std::runtime_error(
            u8"Could not open file at "s + filepath.string());
    }
    putit::BinaryOArchive ar{out};
    for (size_t i = begin; i < end; ++i)
    {
        ar.save(data[i]);
    }
}


// reads or writes global save data:
// - save game header file (on write)
// - character/skill/inventory data for the player and characters in their party
// - global variables
// - NPC memory
// - Item identification memory
// - Foobar save data
// - quest data
// - list of pending events
// - lots of things relevant to the player only, like traits/material
// counts/spell data/recipes...
// - trading cards
// - appearance of the character (PCC)
// - adventurer news
// - artifact discovery information
// - other things...
void fmode_7_8(bool read, const fs::path& dir)
{
    foobar_data.version = latest_version;

    if (!fs::exists(dir))
    {
        fs::create_directory(dir);
    }

    if (!read)
    {
        playerheader =
            cdatan(0, 0) + u8" Lv:" + cdata.player().level + u8" " + mdatan(0);
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
        const auto filepath = dir / u8"foobar_data.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                std::ifstream in{filepath.native(), std::ios::binary};
                putit::BinaryIArchive ar{in};
                ar.load(foobar_data);
            }
        }
        else
        {
            std::ofstream out{filepath.native(), std::ios::binary};
            putit::BinaryOArchive ar{out};
            ar.save(foobar_data);
        }
    }

    {
        const auto filepath = dir / u8"cdata.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                for (int index = 0; index < ELONA_MAX_PARTY_CHARACTERS; index++)
                {
                    lua::lua->get_handle_manager().remove_chara_handle(
                        cdata[index]);
                }
                load(filepath, cdata, 0, ELONA_MAX_PARTY_CHARACTERS);
                for (int index = 0; index < ELONA_MAX_PARTY_CHARACTERS; index++)
                {
                    cdata[index].index = index;
                    lua::lua->get_handle_manager().create_chara_handle(
                        cdata[index]);
                }
            }
        }
        else
        {
            save(filepath, cdata, 0, ELONA_MAX_PARTY_CHARACTERS);
        }
    }

    {
        const auto filepath = dir / u8"sdata.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                std::ifstream in{filepath.native(), std::ios::binary};
                putit::BinaryIArchive ar{in};
                for (int cc = 0; cc < ELONA_MAX_PARTY_CHARACTERS; ++cc)
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
            putit::BinaryOArchive ar{out};
            for (int cc = 0; cc < ELONA_MAX_PARTY_CHARACTERS; ++cc)
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
                for (int index = 0; index < 1320; index++)
                {
                    lua::lua->get_handle_manager().remove_item_handle(
                        inv[index]);
                }
                load(filepath, inv, 0, 1320);
                for (int index = 0; index < 1320; index++)
                {
                    inv[index].index = index;
                    lua::lua->get_handle_manager().create_item_handle(
                        inv[index]);
                }
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
                fileutil::read_by_line(filepath),
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

    ELONA_LOG("dir:" << dir);

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
    ELONA_LOG("ctrlfile7:end")
}


// reads or writes gene data.
void fmode_14_15(bool read)
{
    const auto dir =
        read ? filesystem::dir::save(geneuse) : filesystem::dir::tmp();
    if (!read)
    {
        playerheader =
            cdatan(0, 0) + u8"(Lv" + cdata.player().level + u8")の遺伝子";
        const auto filepath = dir / u8"gene_header.txt";
        bsave(filepath, playerheader);
        Save::instance().add(filepath.filename());
    }

    {
        const auto filepath = dir / u8"g_cdata.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                for (int index = 0; index < ELONA_MAX_PARTY_CHARACTERS; index++)
                {
                    lua::lua->get_handle_manager().remove_chara_handle(
                        cdata[index]);
                }
                load(filepath, cdata, 0, ELONA_MAX_PARTY_CHARACTERS);
                for (int index = 0; index < ELONA_MAX_PARTY_CHARACTERS; index++)
                {
                    cdata[index].index = index;
                    lua::lua->get_handle_manager().create_chara_handle(
                        cdata[index]);
                }
            }
        }
        else
        {
            Save::instance().add(filepath.filename());
            save(filepath, cdata, 0, ELONA_MAX_PARTY_CHARACTERS);
        }
    }

    {
        const auto filepath = dir / u8"g_sdata.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                std::ifstream in{filepath.native(), std::ios::binary};
                putit::BinaryIArchive ar{in};
                for (int cc = 0; cc < ELONA_MAX_PARTY_CHARACTERS; ++cc)
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
            Save::instance().add(filepath.filename());
            std::ofstream out{filepath.native(), std::ios::binary};
            putit::BinaryOArchive ar{out};
            for (int cc = 0; cc < ELONA_MAX_PARTY_CHARACTERS; ++cc)
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
            Save::instance().add(filepath.filename());
            save_v1(filepath, spell, 0, 200);
        }
    }

    {
        const auto filepath = dir / u8"g_inv.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                for (int index = 0; index < 1320; index++)
                {
                    lua::lua->get_handle_manager().remove_item_handle(
                        inv[index]);
                }
                load(filepath, inv, 0, 1320);
                for (int index = 0; index < 1320; index++)
                {
                    inv[index].index = index;
                    lua::lua->get_handle_manager().create_item_handle(
                        inv[index]);
                }
            }
        }
        else
        {
            Save::instance().add(filepath.filename());
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
            Save::instance().add(filepath.filename());
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
            Save::instance().add(filepath.filename());
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
            Save::instance().add(filepath.filename());
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
            Save::instance().add(filepath.filename());
            save_v1(filepath, genetemp, 0, 1000);
        }
    }
}


// reads or writes map-local data for the map with id "mid" (map data,
// tiles, characters, skill status, map effects, character names)
// does not read/write cdata or sdata for player or party characters.
void fmode_1_2(bool read)
{
    const auto dir = filesystem::dir::tmp();

    {
        const auto filepath = dir / (u8"mdata_"s + mid + u8".s2");
        if (read)
        {
            tmpload(u8"mdata_"s + mid + u8".s2");
            load_v1(filepath, mdata, 0, 100);
        }
        else
        {
            Save::instance().add(filepath.filename());
            writeloadedbuff(u8"mdata_"s + mid + u8".s2");
            save_v1(filepath, mdata, 0, 100);
        }
    }

    {
        const auto filepath = dir / (u8"map_"s + mid + u8".s2");
        if (read)
        {
            DIM4(map, mdata_map_width, mdata_map_height, 10);
            DIM3(mapsync, mdata_map_width, mdata_map_height);
            DIM3(mef, 9, MEF_MAX);
            tmpload(u8"map_"s + mid + u8".s2");
            load_v3(
                filepath, map, 0, mdata_map_width, 0, mdata_map_height, 0, 10);
        }
        else
        {
            Save::instance().add(filepath.filename());
            writeloadedbuff(u8"map_"s + mid + u8".s2");
            save_v3(
                filepath, map, 0, mdata_map_width, 0, mdata_map_height, 0, 10);
        }
    }

    {
        const auto filepath = dir / (u8"cdata_"s + mid + u8".s2");
        if (read)
        {
            for (int index = ELONA_MAX_PARTY_CHARACTERS;
                 index < ELONA_MAX_CHARACTERS;
                 index++)
            {
                lua::lua->get_handle_manager().remove_chara_handle(
                    cdata[index]);
            }
            tmpload(u8"cdata_"s + mid + u8".s2");
            load(
                filepath,
                cdata,
                ELONA_MAX_PARTY_CHARACTERS,
                ELONA_MAX_CHARACTERS);
            for (int index = ELONA_MAX_PARTY_CHARACTERS;
                 index < ELONA_MAX_CHARACTERS;
                 index++)
            {
                cdata[index].index = index;
                lua::lua->get_handle_manager().create_chara_handle(
                    cdata[index]);
            }
        }
        else
        {
            Save::instance().add(filepath.filename());
            writeloadedbuff(u8"cdata_"s + mid + u8".s2");
            save(
                filepath,
                cdata,
                ELONA_MAX_PARTY_CHARACTERS,
                ELONA_MAX_CHARACTERS);
        }
    }

    {
        const auto filepath = dir / (u8"sdata_"s + mid + u8".s2");
        if (read)
        {
            tmpload(u8"sdata_"s + mid + u8".s2");
            std::ifstream in{filepath.native(), std::ios::binary};
            putit::BinaryIArchive ar{in};
            for (int cc = ELONA_MAX_PARTY_CHARACTERS; cc < ELONA_MAX_CHARACTERS;
                 ++cc)
            {
                for (int i = 0; i < 600; ++i)
                {
                    ar.load(sdata.get(i, cc));
                }
            }
        }
        else
        {
            Save::instance().add(filepath.filename());
            writeloadedbuff(u8"sdata_"s + mid + u8".s2");
            std::ofstream out{filepath.native(), std::ios::binary};
            putit::BinaryOArchive ar{out};
            for (int cc = ELONA_MAX_PARTY_CHARACTERS; cc < ELONA_MAX_CHARACTERS;
                 ++cc)
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
            if (mdata_map_mefs_loaded_flag == 0)
            {
                for (int y = 0; y < mdata_map_height; ++y)
                {
                    for (int x = 0; x < mdata_map_width; ++x)
                    {
                        map(x, y, 8) = 0;
                    }
                }
                mdata_map_mefs_loaded_flag = 1;
            }
            else
            {
                tmpload(u8"mef_"s + mid + u8".s2");
                load_v2(filepath, mef, 0, 9, 0, MEF_MAX);
            }
        }
        else
        {
            Save::instance().add(filepath.filename());
            writeloadedbuff(u8"mef_"s + mid + u8".s2");
            save_v2(filepath, mef, 0, 9, 0, MEF_MAX);
        }
    }

    arrayfile(read, u8"cdatan2", dir / (u8"cdatan_"s + mid + u8".s2"));
    arrayfile(read, u8"mdatan", dir / (u8"mdatan_"s + mid + u8".s2"));
}



void fmode_16()
{
    DIM3(cmapdata, 5, 400);

    load_v3(
        fmapfile + u8".map",
        map,
        0,
        mdata_map_width,
        0,
        mdata_map_height,
        0,
        3,
        true);

    const auto filepath = fmapfile + u8".obj"s;
    if (!fs::exists(filepath))
    {
        return;
    }
    load_v2(filepath, cmapdata, 0, 5, 0, 400, true);
}


// reads or writes a custom map.
// this is currently never called to write anything.
void fmode_5_6(bool read)
{
    if (read)
    {
        DIM3(cmapdata, 5, 400);
        DIM3(mef, 9, MEF_MAX);
    }

    {
        const auto filepath = fmapfile + u8".idx"s;
        if (read)
        {
            load_v1(filepath, mdatatmp, 0, 100, true);
            for (int j = 0; j < 5; ++j)
            {
                mdata(j) = mdatatmp(j);
            }
        }
        else
        {
            save_v1(filepath, mdata, 0, 100, true);
        }
    }

    {
        const auto filepath = fmapfile + u8".map"s;
        if (read)
        {
            DIM4(map, mdata_map_width, mdata_map_height, 10);
            DIM3(
                mapsync,
                mdata_map_width,
                mdata_map_height); // TODO length_exception
            load_v3(
                filepath,
                map,
                0,
                mdata_map_width,
                0,
                mdata_map_height,
                0,
                10,
                true);
        }
        else
        {
            save_v3(
                filepath,
                map,
                0,
                mdata_map_width,
                0,
                mdata_map_height,
                0,
                10,
                true);
        }
    }

    {
        const auto filepath = fmapfile + u8".obj"s;
        if (read)
        {
            if (fs::exists(filepath))
            {
                load_v2(filepath, cmapdata, 0, 5, 0, 400, true);
            }
        }
        else
        {
            save_v2(filepath, cmapdata, 0, 5, 0, 400, true);
        }
    }
}


// reads or writes map-local item data (inv_xx.s2)
// does not read/write player or party character inventories.
void fmode_3_4(bool read, const fs::path& filename)
{
    const auto filepath = filesystem::dir::tmp() / filename;
    if (read)
    {
        for (int index = 1320; index < 5480; index++)
        {
            lua::lua->get_handle_manager().remove_item_handle(inv[index]);
        }
        tmpload(filename);
        load(filepath, inv, 1320, 5480);
        for (int index = 1320; index < 5480; index++)
        {
            inv[index].index = index;
            lua::lua->get_handle_manager().create_item_handle(inv[index]);
        }
    }
    else
    {
        Save::instance().add(filepath.filename());
        tmpload(filename);
        save(filepath, inv, 1320, 5480);
    }
}



void fmode_23_24(bool read, const fs::path& filepath)
{
    if (read)
    {
        Save::instance().add(filepath.filename());
        save_v1(filepath, deck, 0, 1000);
    }
    else
    {
        load_v1(filepath, deck, 0, 1000);
    }
}


// reads character and skill data when upgrading the character's home.
void fmode_17()
{
    const auto dir = filesystem::dir::tmp();

    if (!fs::exists(dir / (u8"cdata_"s + mid + u8".s2")))
        return;

    {
        const auto filepath = dir / (u8"cdata_"s + mid + u8".s2");
        for (int index = ELONA_MAX_PARTY_CHARACTERS;
             index < ELONA_MAX_CHARACTERS;
             index++)
        {
            lua::lua->get_handle_manager().remove_chara_handle(cdata[index]);
        }
        tmpload(u8"cdata_"s + mid + u8".s2");
        load(filepath, cdata, ELONA_MAX_PARTY_CHARACTERS, ELONA_MAX_CHARACTERS);
        for (int index = ELONA_MAX_PARTY_CHARACTERS;
             index < ELONA_MAX_CHARACTERS;
             index++)
        {
            cdata[index].index = index;
            lua::lua->get_handle_manager().create_chara_handle(cdata[index]);
        }
    }

    {
        const auto filepath = dir / (u8"sdata_"s + mid + u8".s2");
        tmpload(u8"sdata_"s + mid + u8".s2");
        std::ifstream in{filepath.native(), std::ios::binary};
        putit::BinaryIArchive ar{in};
        for (int cc = ELONA_MAX_PARTY_CHARACTERS; cc < ELONA_MAX_CHARACTERS;
             ++cc)
        {
            for (int i = 0; i < 600; ++i)
            {
                ar.load(sdata.get(i, cc));
            }
        }
    }

    arrayfile(true, u8"cdatan2", dir / (u8"cdatan_"s + mid + u8".s2"));
}


void fmode_10()
{
    for (const auto& entry : filesystem::dir_entries(
             filesystem::dir::tmp(),
             filesystem::DirEntryRange::Type::file,
             std::regex{u8R"(.*\..*)"}))
    {
        fs::remove_all(entry.path());
    }
}


// deletes a saved game.
void fmode_9()
{
    fs::remove_all(filesystem::dir::save(playerid));
}


// deletes a map and optionally deletes characters/skills/items in it.
// the optional case is so the characters/skills/items can be
// preserved in the case of upgrading the player's home.
void fmode_11_12(FileOperation file_operation)
{
    if (file_operation == FileOperation::map_delete_preserve_items)
    {
        tmpload(u8"mdata_"s + mid + u8".s2");
        if (!fs::exists(filesystem::dir::tmp() / (u8"mdata_"s + mid + u8".s2")))
        {
            // We tried preserving the characters/items, but the home
            // map to transfer them from didn't exist.
            return;
        }
    }
    auto filepath = filesystem::dir::tmp() / (u8"map_"s + mid + u8".s2");
    tmpload(u8"map_"s + mid + u8".s2");
    if (!fs::exists(filepath))
        return;

    fs::remove_all(filepath);
    Save::instance().remove(filepath.filename());
    if (file_operation == FileOperation::map_delete)
    {
        filepath = filesystem::dir::tmp() / (u8"cdata_"s + mid + u8".s2");
        if (fs::exists(filepath))
        {
            fs::remove_all(filepath);
        }
        else
        {
            writeloadedbuff(filepath.filename());
        }
        Save::instance().remove(filepath.filename());
        filepath = filesystem::dir::tmp() / (u8"sdata_"s + mid + u8".s2");
        if (fs::exists(filepath))
        {
            fs::remove_all(filepath);
        }
        else
        {
            writeloadedbuff(filepath.filename());
        }
        Save::instance().remove(filepath.filename());
        filepath = filesystem::dir::tmp() / (u8"cdatan_"s + mid + u8".s2");
        if (fs::exists(filepath))
        {
            fs::remove_all(filepath);
        }
        else
        {
            writeloadedbuff(filepath.filename());
        }
        Save::instance().remove(filepath.filename());
        filepath = filesystem::dir::tmp() / (u8"inv_"s + mid + u8".s2");
        if (fs::exists(filepath))
        {
            fs::remove_all(filepath);
        }
        else
        {
            writeloadedbuff(filepath.filename());
        }
        Save::instance().remove(filepath.filename());
    }
    filepath = filesystem::dir::tmp() / (u8"mdata_"s + mid + u8".s2");
    if (fs::exists(filepath))
    {
        fs::remove_all(filepath);
    }
    else
    {
        writeloadedbuff(filepath.filename());
    }
    Save::instance().remove(filepath.filename());
    filepath = filesystem::dir::tmp() / (u8"mdatan_"s + mid + u8".s2");
    if (fs::exists(filepath))
    {
        fs::remove_all(filepath);
    }
    else
    {
        writeloadedbuff(filepath.filename());
    }
    Save::instance().remove(filepath.filename());
    filepath = filesystem::dir::tmp() / (u8"mef_"s + mid + u8".s2");
    if (fs::exists(filepath))
    {
        fs::remove_all(filepath);
    }
    else
    {
        writeloadedbuff(filepath.filename());
    }

    Save::instance().remove(filepath.filename());
}


// deletes files inside the temporary directory (tmp/)
void fmode_13()
{
    for (int i = 0; i < 40; ++i)
    {
        adata(i, area) = 0;
    }
    for (const auto& entry : filesystem::dir_entries(
             filesystem::dir::save(playerid),
             filesystem::DirEntryRange::Type::file,
             std::regex{u8R"(.*_)"s + area + u8R"(_.*\..*)"}))
    {
        writeloadedbuff(entry.path().filename());
        Save::instance().remove(entry.path().filename());
    }
    for (const auto& entry : filesystem::dir_entries(
             filesystem::dir::tmp(),
             filesystem::DirEntryRange::Type::file,
             std::regex{u8R"(.*_)"s + area + u8R"(_.*\..*)"}))
    {
        Save::instance().remove(entry.path().filename());
        fs::remove_all(entry.path());
    }
}



} // namespace


namespace elona
{



Save& Save::instance()
{
    static Save instance;
    return instance;
}



void Save::clear()
{
    saved_files.clear();
}



void Save::add(const fs::path& filename)
{
    ELONA_LOG("add:" << filename);
    saved_files[filename] = true;
}



void Save::remove(const fs::path& filename)
{
    ELONA_LOG("remove:" << filename);
    saved_files[filename] = false;
}



void Save::save(const fs::path& save_dir)
{
    for (const auto& pair : saved_files)
    {
        const auto& filename = pair.first;
        const auto& is_saved = pair.second;
        if (is_saved)
        {
            fs::copy_file(
                filesystem::dir::tmp() / filename,
                save_dir / filename,
                fs::copy_option::overwrite_if_exists);
        }
        else if (fs::exists(save_dir / filename))
        {
            fs::remove_all(save_dir / filename);
        }
    }
}



void ctrl_file(FileOperation file_operation)
{
    gdata_play_time = gdata_play_time + timeGetTime() / 1000 - time_begin;
    time_begin = timeGetTime() / 1000;

    switch (file_operation)
    {
    case FileOperation::map_read:
    case FileOperation::map_write:
        fmode_1_2(file_operation == FileOperation::map_read);
        break;
    case FileOperation::custom_map_read:
    case FileOperation::custom_map_write:
        fmode_5_6(file_operation == FileOperation::custom_map_read);
        break;
    case FileOperation::save_game_delete: fmode_9(); break;
    case FileOperation::temp_dir_delete: fmode_10(); break;
    case FileOperation::map_delete:
    case FileOperation::map_delete_preserve_items:
        fmode_11_12(file_operation);
        break;
    case FileOperation::temp_dir_delete_area: fmode_13(); break;
    case FileOperation::gene_write:
    case FileOperation::gene_read:
        fmode_14_15(file_operation == FileOperation::gene_read);
        break;
    case FileOperation::map_home_upgrade: fmode_17(); break;
    case FileOperation::map_load_map_obj_files: fmode_16(); break;
    default: assert(0);
    }
}


void ctrl_file(FileOperation2 file_operation, const fs::path& filepath)
{
    gdata_play_time = gdata_play_time + timeGetTime() / 1000 - time_begin;
    time_begin = timeGetTime() / 1000;

    switch (file_operation)
    {
    case FileOperation2::map_items_read:
    case FileOperation2::map_items_write:
        fmode_3_4(file_operation == FileOperation2::map_items_read, filepath);
        break;
    case FileOperation2::global_read:
    case FileOperation2::global_write:
        fmode_7_8(file_operation == FileOperation2::global_read, filepath);
        break;
    case FileOperation2::deck_write:
    case FileOperation2::deck_read:
        fmode_23_24(file_operation == FileOperation2::deck_read, filepath);
        break;
    default: assert(0);
    }
}



void tmpload(const fs::path& filename)
{
    const auto already_exists = writeloadedbuff(filename);
    if (already_exists)
    {
        ELONA_LOG("tmpload:tmp:" << filename);
        return;
    }

    // Then, needs copy.
    const auto original_file = filesystem::dir::save(playerid) / filename;
    if (fs::exists(original_file))
    {
        ELONA_LOG("tmpload:copy:" << filename);
        fs::copy_file(
            original_file,
            filesystem::dir::tmp() / filename,
            fs::copy_option::overwrite_if_exists);
    }
    else
    {
        ELONA_LOG("tmpload:not found:" << original_file);
    }
}



bool writeloadedbuff(const fs::path& filename)
{
    if (filename.empty())
        return true;

    const auto inserted = loaded_files.insert(filename).second;
    return !inserted;
}



void writeloadedbuff_clear()
{
    loaded_files.clear();
}



} // namespace elona
