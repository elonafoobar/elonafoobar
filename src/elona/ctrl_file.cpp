#include "ctrl_file.hpp"

#include <set>

#include "../util/fileutil.hpp"
#include "ability.hpp"
#include "area.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "deferred_event.hpp"
#include "elona.hpp"
#include "filesystem.hpp"
#include "item.hpp"
#include "log.hpp"
#include "lua_env/handle_manager.hpp"
#include "lua_env/lua_env.hpp"
#include "lua_env/mod_serializer.hpp"
#include "map.hpp"
#include "mef.hpp"
#include "quest.hpp"
#include "save_header.hpp"
#include "serialization/serialization.hpp"
#include "serialization/utils.hpp"
#include "variables.hpp"



namespace elona
{

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
        lines.resize(57 * 10);
        auto itr = std::begin(lines);
        for (int i = 0; i < 57; ++i)
        {
            cdata[i].name = *itr;
            ++itr;
            cdata[i].alias = *itr;
            ++itr;
            cdata[i].race = data::InstanceId{*itr};
            ++itr;
            cdata[i].class_ = data::InstanceId{*itr};
            ++itr;
            cdata[i].talk = *itr;
            ++itr;
            ++itr;
            ++itr;
            ++itr;
            ++itr;
            ++itr;
        }
    }
    else if (fmode_str == u8"cdatan2"s)
    {
        lines.resize(188 * 10);
        auto itr = std::begin(lines);
        for (int i = ELONA_MAX_PARTY_CHARACTERS; i < ELONA_MAX_CHARACTERS; ++i)
        {
            cdata[i].name = *itr;
            ++itr;
            cdata[i].alias = *itr;
            ++itr;
            cdata[i].race = data::InstanceId{*itr};
            ++itr;
            cdata[i].class_ = data::InstanceId{*itr};
            ++itr;
            cdata[i].talk = *itr;
            ++itr;
            ++itr;
            ++itr;
            ++itr;
            ++itr;
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
            u8"Error: fail to write " +
            filepathutil::make_preferred_path_in_utf8(filepath));
    }

    if (fmode_str == u8"qname"s)
    {
        for (int i = 0; i < 500; ++i)
        {
            out << qname(i) << std::endl;
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
            out << cdata[i].name << std::endl;
            out << cdata[i].alias << std::endl;
            out << cdata[i].race.get() << std::endl;
            out << cdata[i].class_.get() << std::endl;
            out << cdata[i].talk << std::endl;
            out << std::endl;
            out << std::endl;
            out << std::endl;
            out << std::endl;
            out << std::endl;
        }
    }
    else if (fmode_str == u8"cdatan2"s)
    {
        for (int i = ELONA_MAX_PARTY_CHARACTERS; i < ELONA_MAX_CHARACTERS; ++i)
        {
            out << cdata[i].name << std::endl;
            out << cdata[i].alias << std::endl;
            out << cdata[i].race.get() << std::endl;
            out << cdata[i].class_.get() << std::endl;
            out << cdata[i].talk << std::endl;
            out << std::endl;
            out << std::endl;
            out << std::endl;
            out << std::endl;
            out << std::endl;
        }
    }

    writeloadedbuff(filepath.filename());
    Save::instance().add(filepath.filename());
}



void arrayfile(
    bool fread,
    const std::string& fmode_str,
    const fs::path& filepath)
{
    if (!fread)
    {
        arrayfile_write(fmode_str, filepath);
    }
    else
    {
        tmpload(filepath.filename());
        arrayfile_read(fmode_str, filepath);
    }
}



template <typename F>
void load_internal(const fs::path& filepath, F do_load)
{
    std::ifstream in{filepath.native(), std::ios::binary};
    if (in.fail())
    {
        throw std::runtime_error(
            u8"Could not open file at "s +
            filepathutil::to_utf8_path(filepath));
    }
    serialization::binary::IArchive ar{in};
    do_load(ar);
}



template <typename F>
void save_internal(const fs::path& filepath, F do_save)
{
    std::ofstream out{filepath.native(), std::ios::binary};
    if (out.fail())
    {
        throw std::runtime_error(
            u8"Could not open file at "s +
            filepathutil::to_utf8_path(filepath));
    }
    serialization::binary::OArchive ar{out};
    do_save(ar);
}



template <typename T>
void load_v1(
    const fs::path& filepath,
    elona_vector1<T>& data,
    size_t begin,
    size_t end)
{
    load_internal(filepath, [&](auto& ar) {
        for (size_t i = begin; i < end; ++i)
        {
            ar(data(i));
        }
    });
}


template <typename T>
void save_v1(
    const fs::path& filepath,
    elona_vector1<T>& data,
    size_t begin,
    size_t end)
{
    save_internal(filepath, [&](auto& ar) {
        for (size_t i = begin; i < end; ++i)
        {
            ar(data(i));
        }
    });
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
    load_internal(filepath, [&](auto& ar) {
        for (size_t j = j_begin; j < j_end; ++j)
        {
            for (size_t i = i_begin; i < i_end; ++i)
            {
                ar(data(i, j));
            }
        }
    });
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
    save_internal(filepath, [&](auto& ar) {
        for (size_t j = j_begin; j < j_end; ++j)
        {
            for (size_t i = i_begin; i < i_end; ++i)
            {
                ar(data(i, j));
            }
        }
    });
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
    load_internal(filepath, [&](auto& ar) {
        for (size_t k = k_begin; k < k_end; ++k)
        {
            for (size_t j = j_begin; j < j_end; ++j)
            {
                for (size_t i = i_begin; i < i_end; ++i)
                {
                    ar(data(i, j, k));
                }
            }
        }
    });
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
    save_internal(filepath, [&](auto& ar) {
        for (size_t k = k_begin; k < k_end; ++k)
        {
            for (size_t j = j_begin; j < j_end; ++j)
            {
                for (size_t i = i_begin; i < i_end; ++i)
                {
                    ar(data(i, j, k));
                }
            }
        }
    });
}


template <typename T>
void load_vec(const fs::path& filepath, std::vector<T>& data)
{
    load_internal(filepath, [&](auto& ar) {
        for (auto&& element : data)
        {
            ar(element);
        }
    });
}


template <typename T>
void load(const fs::path& filepath, T& data, size_t begin, size_t end)
{
    load_internal(filepath, [&](auto& ar) {
        for (size_t i = begin; i < end; ++i)
        {
            ar(data[i]);
        }
    });
}


template <typename T>
void save(const fs::path& filepath, T& data, size_t begin, size_t end)
{
    save_internal(filepath, [&](auto& ar) {
        for (size_t i = begin; i < end; ++i)
        {
            ar(data[i]);
        }
    });
}


template <typename T>
void load(const fs::path& filepath, T& data)
{
    load_internal(filepath, [&](auto& ar) { ar(data); });
}


template <typename T>
void save(const fs::path& filepath, T& data)
{
    save_internal(filepath, [&](auto& ar) { ar(data); });
}



void restore_handles(int index_start, int index_end)
{
    sol::table obj_ids = lua::lua->get_state()->create_table();
    for (int index = index_start; index < index_end; ++index)
    {
        auto& obj = cdata[index];
        const auto key = reinterpret_cast<int64_t>(std::addressof(obj));
        obj_ids[key] = obj.obj_id.to_string();
    }

    auto& handle_mgr = lua::lua->get_handle_manager();
    handle_mgr.merge_handles(Character::lua_type(), obj_ids);

    ELONA_LOG("lua.mod") << "Loaded handle data for " << Character::lua_type()
                         << " in [" << index_start << "," << index_end << "]";

    for (int index = index_start; index < index_end; index++)
    {
        handle_mgr.resolve_handle(cdata[index]);
    }
}



bool will_resolve_object_reference = false;

void schedule_object_reference_resolution()
{
    will_resolve_object_reference = true;
}



OptionalItemRef resolve_object_reference(const ObjId& obj_id)
{
    return ItemIdTable::instance().get(obj_id);
}



void clear_pending_ids()
{
    eobject::internal::_pending_ids<Item>.clear();
}



void resolve_pending_ids()
{
    for (auto& [ref_ptr, obj_id] : eobject::internal::_pending_ids<Item>)
    {
        *ref_ptr = resolve_object_reference(obj_id);
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
    if (!fs::exists(dir))
    {
        fs::create_directory(dir);
    }

    if (!read)
    {
        SaveHeader::save(dir);
    }

    {
        const auto filepath = dir / u8"version.s0";
        if (read)
        {
            // Do nothing.
        }
        else
        {
            auto v = latest_version;
            serialization::binary::save(filepath, v);
        }
    }

    {
        const auto filepath = dir / u8"gdata.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                load_v1(filepath, gdata, 0, 1000);
                game_data.unpack_from(gdata);
            }
        }
        else
        {
            game_data.pack_to(gdata);
            save_v1(filepath, gdata, 0, 1000);
        }
    }

    {
        const auto filepath = dir / u8"foobar_data.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                serialization::binary::load(filepath, foobar_data);
            }
        }
        else
        {
            serialization::binary::save(filepath, foobar_data);
        }
    }

    {
        const auto filepath = dir / u8"cdata.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                load(filepath, cdata, 0, ELONA_MAX_PARTY_CHARACTERS);
                for (int index = 0; index < ELONA_MAX_PARTY_CHARACTERS; index++)
                {
                    cdata[index].index = index;
                }

                restore_handles(0, ELONA_MAX_PARTY_CHARACTERS);
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
                serialization::binary::IArchive ar{in};
                for (int chara_index = 0;
                     chara_index < ELONA_MAX_PARTY_CHARACTERS;
                     ++chara_index)
                {
                    for (int i = 0; i < 600; ++i)
                    {
                        ar(sdata.get(i, chara_index));
                    }
                }
            }
        }
        else
        {
            std::ofstream out{filepath.native(), std::ios::binary};
            serialization::binary::OArchive ar{out};
            for (int chara_index = 0; chara_index < ELONA_MAX_PARTY_CHARACTERS;
                 ++chara_index)
            {
                for (int i = 0; i < 600; ++i)
                {
                    ar(sdata.get(i, chara_index));
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
                load_internal(filepath, [&](auto& ar) {
                    for (auto&& inv : g_inv.global())
                    {
                        inv.clear();
                        const auto n = inv.size();
                        for (size_t i = 0; i < n; ++i)
                        {
                            bool exists;
                            ar(exists);
                            if (exists)
                            {
                                const auto item_ref =
                                    Inventory::create(InventorySlot{&inv, i});
                                auto& item = *item_ref.get_raw_ptr();
                                ar(item);
                                ItemIdTable::instance().add(item_ref);
                            }
                        }
                    }
                });
            }
        }
        else
        {
            save_internal(filepath, [&](auto& ar) {
                for (auto&& inv : g_inv.global())
                {
                    const auto n = inv.size();
                    for (size_t i = 0; i < n; ++i)
                    {
                        bool exists = !!inv.at(i);
                        ar(exists);
                        if (exists)
                        {
                            const auto item_ref = inv.at(i).unwrap();
                            auto& item = *item_ref.get_raw_ptr();
                            ar(item);
                        }
                    }
                }
            });
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
                area_data.unpack_from(adata);
            }
        }
        else
        {
            area_data.pack_to(adata);
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
                quest_data.unpack_from(qdata);
            }
        }
        else
        {
            quest_data.pack_to(qdata);
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
                if (game_data.version >= 1200)
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

    arrayfile(read, u8"cdatan1", dir / u8"cdatan.s1");
    arrayfile(read, u8"qname", dir / u8"qname.s1");

    // TODO: Delete this line when the v1.0.0 stable is released!
    if (!read && fs::exists(dir / u8"gdatan.s1"))
    {
        fs::remove(dir / u8"gdatan.s1");
    }

    if (!read)
    {
        event_save(dir / "deferred_events.s1");
    }
    else
    {
        if (fs::exists(dir / "deferred_events.s1"))
        {
            event_load(dir / "deferred_events.s1");
        }
    }

    lua::ModSerializer mod_serializer(*lua::lua);
    if (read)
    {
        lua::lua->get_mod_manager().clear_global_stores();
    }

    {
        const auto filepath = dir / u8"mod.s1";
        if (read)
        {
            if (fs::exists(filepath))
            {
                std::ifstream in{filepath.native(), std::ios::binary};
                serialization::binary::IArchive ar{in};
                mod_serializer.load_mod_store_data(
                    ar, lua::ModEnv::StoreType::global);
            }
        }
        else
        {
            std::ofstream out{filepath.native(), std::ios::binary};
            serialization::binary::OArchive ar{out};
            mod_serializer.save_mod_store_data(
                ar, lua::ModEnv::StoreType::global);
        }
    }

    if (read)
    {
        resolve_pending_ids();
        clear_pending_ids();
    }
}


// reads or writes gene data.
void fmode_14_15(bool read)
{
    const auto dir =
        read ? filesystem::dirs::save(geneuse) : filesystem::dirs::tmp();
    if (!read)
    {
        playerheader = cdata.player().name + u8"(Lv" + cdata.player().level +
            u8")の遺伝子";
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
                load(filepath, cdata, 0, ELONA_MAX_PARTY_CHARACTERS);
                for (int index = 0; index < ELONA_MAX_PARTY_CHARACTERS; index++)
                {
                    cdata[index].index = index;
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
                serialization::binary::IArchive ar{in};
                for (int chara_index = 0;
                     chara_index < ELONA_MAX_PARTY_CHARACTERS;
                     ++chara_index)
                {
                    for (int i = 0; i < 600; ++i)
                    {
                        ar(sdata.get(i, chara_index));
                    }
                }
            }
        }
        else
        {
            Save::instance().add(filepath.filename());
            std::ofstream out{filepath.native(), std::ios::binary};
            serialization::binary::OArchive ar{out};
            for (int chara_index = 0; chara_index < ELONA_MAX_PARTY_CHARACTERS;
                 ++chara_index)
            {
                for (int i = 0; i < 600; ++i)
                {
                    ar(sdata.get(i, chara_index));
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
                load_internal(filepath, [&](auto& ar) {
                    for (auto&& inv : g_inv.global())
                    {
                        inv.clear();
                        const auto n = inv.size();
                        for (size_t i = 0; i < n; ++i)
                        {
                            bool exists;
                            ar(exists);
                            if (exists)
                            {
                                const auto item_ref =
                                    Inventory::create(InventorySlot{&inv, i});
                                auto& item = *item_ref.get_raw_ptr();
                                ar(item);
                            }
                        }
                    }
                });
            }
        }
        else
        {
            Save::instance().add(filepath.filename());
            save_internal(filepath, [&](auto& ar) {
                for (auto&& inv : g_inv.global())
                {
                    const auto n = inv.size();
                    for (size_t i = 0; i < n; ++i)
                    {
                        bool exists = !!inv.at(i);
                        ar(exists);
                        if (exists)
                        {
                            const auto item_ref = inv.at(i).unwrap();
                            auto& item = *item_ref.get_raw_ptr();
                            ar(item);
                        }
                    }
                }
            });
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

#if 0 // TODO
    if (read)
    {
        resolve_pending_ids();
        clear_pending_ids();
    }
#endif
}


// reads or writes map-local data for the map with id "mid" (map data,
// tiles, characters, skill status, map effects, character names)
// does not read/write cdata or sdata for player or party characters.
void fmode_1_2(bool read)
{
    const auto dir = filesystem::dirs::tmp();

    {
        const auto filepath = dir / (u8"mdata_"s + mid + u8".s2");
        if (read)
        {
            tmpload(u8"mdata_"s + mid + u8".s2");
            load_v1(filepath, mdata, 0, 100);
            map_data.unpack_from(mdata);
        }
        else
        {
            Save::instance().add(filepath.filename());
            writeloadedbuff(u8"mdata_"s + mid + u8".s2");
            map_data.pack_to(mdata);
            save_v1(filepath, mdata, 0, 100);
        }
    }

    {
        const auto filepath = dir / (u8"map_"s + mid + u8".s2");
        if (read)
        {
            DIM3(mapsync, map_data.width, map_data.height);
            DIM3(mef, 9, MEF_MAX);
            tmpload(u8"map_"s + mid + u8".s2");
            load(filepath, cell_data);
        }
        else
        {
            Save::instance().add(filepath.filename());
            writeloadedbuff(u8"map_"s + mid + u8".s2");
            save(filepath, cell_data);
        }
    }

    {
        const auto filepath = dir / (u8"cdata_"s + mid + u8".s2");
        if (read)
        {
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
            }

            restore_handles(ELONA_MAX_PARTY_CHARACTERS, ELONA_MAX_CHARACTERS);
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
            serialization::binary::IArchive ar{in};
            for (int chara_index = ELONA_MAX_PARTY_CHARACTERS;
                 chara_index < ELONA_MAX_CHARACTERS;
                 ++chara_index)
            {
                for (int i = 0; i < 600; ++i)
                {
                    ar(sdata.get(i, chara_index));
                }
            }
        }
        else
        {
            Save::instance().add(filepath.filename());
            writeloadedbuff(u8"sdata_"s + mid + u8".s2");
            std::ofstream out{filepath.native(), std::ios::binary};
            serialization::binary::OArchive ar{out};
            for (int chara_index = ELONA_MAX_PARTY_CHARACTERS;
                 chara_index < ELONA_MAX_CHARACTERS;
                 ++chara_index)
            {
                for (int i = 0; i < 600; ++i)
                {
                    ar(sdata.get(i, chara_index));
                }
            }
        }
    }

    {
        const auto filepath = dir / (u8"mef_"s + mid + u8".s2");
        if (read)
        {
            if (map_data.mefs_loaded_flag == 0)
            {
                for (int y = 0; y < map_data.height; ++y)
                {
                    for (int x = 0; x < map_data.width; ++x)
                    {
                        cell_data.at(x, y).mef_index_plus_one = 0;
                    }
                }
                map_data.mefs_loaded_flag = 1;
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

    lua::ModSerializer mod_serializer(*lua::lua);
    if (read)
    {
        lua::lua->get_mod_manager().clear_map_local_stores();
    }

    // Mod map-local store data (Store.map)
    {
        const auto filepath = dir / (u8"mod_map_"s + mid + u8".s2");
        if (read)
        {
            tmpload(u8"mod_map_"s + mid + u8".s2");

            std::ifstream in{filepath.native(), std::ios::binary};
            serialization::binary::IArchive ar{in};
            mod_serializer.load_mod_store_data(ar, lua::ModEnv::StoreType::map);
        }
        else
        {
            Save::instance().add(filepath.filename());
            writeloadedbuff(u8"mod_map_"s + mid + u8".s2");

            std::ofstream out{filepath.native(), std::ios::binary};
            serialization::binary::OArchive ar{out};
            mod_serializer.save_mod_store_data(ar, lua::ModEnv::StoreType::map);
        }
    }

    schedule_object_reference_resolution();
}



void fmode_16()
{
    DIM3(cmapdata, 5, 400);

    std::vector<int> tile_grid(cell_data.width() * cell_data.height());
    load_vec(fmapfile + u8".map", tile_grid);
    cell_data.load_tile_grid(tile_grid);

    const auto filepath = fmapfile + u8".obj"s;
    if (!fs::exists(filepath))
    {
        return;
    }
    load_v2(filepath, cmapdata, 0, 5, 0, 400);
}


// reads or writes a custom map.
// this is currently never called to write anything, as the built-in map editor
// from 1.22 was removed.
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
            load_v1(filepath, mdatatmp, 0, 100);
            for (int j = 0; j < 5; ++j)
            {
                mdata(j) = mdatatmp(j);
            }
            map_data.width = mdata(0);
            map_data.height = mdata(1);
            map_data.atlas_number = mdata(2);
            map_data.next_regenerate_date = mdata(3);
            map_data.stair_down_pos = mdata(4);
        }
        else
        {
            map_data.pack_to(mdata);
            save_v1(filepath, mdata, 0, 100);
        }
    }

    {
        const auto filepath = fmapfile + u8".map"s;
        if (read)
        {
            DIM3(
                mapsync,
                map_data.width,
                map_data.height); // TODO length_exception
            cell_data.init(map_data.width, map_data.height);
            std::vector<int> tile_grid(map_data.width * map_data.height);
            load_vec(fmapfile + u8".map", tile_grid);
            cell_data.load_tile_grid(tile_grid);
        }
        else
        {
            save(filepath, cell_data);
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


// reads or writes map-local item data (inv_xx.s2)
// does not read/write player or party character inventories.
void fmode_3_4(bool read, const fs::path& filename)
{
    const auto filepath = filesystem::dirs::tmp() / filename;
    if (read)
    {
        tmpload(filename);

        load_internal(filepath, [&](auto& ar) {
            for (auto&& inv : g_inv.map_local())
            {
                inv.clear();
                const auto n = inv.size();
                for (size_t i = 0; i < n; ++i)
                {
                    bool exists;
                    ar(exists);
                    if (exists)
                    {
                        const auto item_ref =
                            Inventory::create(InventorySlot{&inv, i});
                        auto& item = *item_ref.get_raw_ptr();
                        ar(item);
                    }
                }
            }
        });
    }
    else
    {
        Save::instance().add(filepath.filename());
        tmpload(filename);

        save_internal(filepath, [&](auto& ar) {
            for (auto&& inv : g_inv.map_local())
            {
                const auto n = inv.size();
                for (size_t i = 0; i < n; ++i)
                {
                    bool exists = !!inv.at(i);
                    ar(exists);
                    if (exists)
                    {
                        const auto item_ref = inv.at(i).unwrap();
                        auto& item = *item_ref.get_raw_ptr();
                        ar(item);
                    }
                }
            }
        });
    }

    if (read)
    {
        if (will_resolve_object_reference)
        {
            resolve_pending_ids();
            clear_pending_ids();
            will_resolve_object_reference = false;
        }
    }
}



void fmode_23_24(bool read, const fs::path& filepath)
{
    if (read)
    {
        load_v1(filepath, deck, 0, 1000);
    }
    else
    {
        Save::instance().add(filepath.filename());
        save_v1(filepath, deck, 0, 1000);
    }
}


// reads character and skill data when upgrading the character's home.
void fmode_17()
{
    const auto dir = filesystem::dirs::tmp();

    if (!fs::exists(dir / (u8"cdata_"s + mid + u8".s2")))
        return;

    {
        const auto filepath = dir / (u8"cdata_"s + mid + u8".s2");
        tmpload(u8"cdata_"s + mid + u8".s2");
        load(filepath, cdata, ELONA_MAX_PARTY_CHARACTERS, ELONA_MAX_CHARACTERS);
        for (int index = ELONA_MAX_PARTY_CHARACTERS;
             index < ELONA_MAX_CHARACTERS;
             index++)
        {
            cdata[index].index = index;
        }
    }

    {
        const auto filepath = dir / (u8"sdata_"s + mid + u8".s2");
        tmpload(u8"sdata_"s + mid + u8".s2");
        std::ifstream in{filepath.native(), std::ios::binary};
        serialization::binary::IArchive ar{in};
        for (int chara_index = ELONA_MAX_PARTY_CHARACTERS;
             chara_index < ELONA_MAX_CHARACTERS;
             ++chara_index)
        {
            for (int i = 0; i < 600; ++i)
            {
                ar(sdata.get(i, chara_index));
            }
        }
    }

    arrayfile(true, u8"cdatan2", dir / (u8"cdatan_"s + mid + u8".s2"));

#if 0
    if (read)
    {
        resolve_pending_ids();
        clear_pending_ids();
    }
#endif
}


void fmode_10()
{
    for (const auto& entry : filesystem::glob_files(
             filesystem::dirs::tmp(), std::regex{u8R"(.*\..*)"}))
    {
        fs::remove_all(entry.path());
    }
}


// deletes a saved game.
void fmode_9()
{
    fs::remove_all(filesystem::dirs::save(playerid));
}


// deletes a map and optionally deletes characters/skills/items in it.
// the optional case is so the characters/skills/items can be
// preserved in the case of upgrading the player's home.
void fmode_11_12(FileOperation file_operation)
{
    if (file_operation == FileOperation::map_delete_preserve_items)
    {
        tmpload(u8"mdata_"s + mid + u8".s2");
        if (!fs::exists(
                filesystem::dirs::tmp() / (u8"mdata_"s + mid + u8".s2")))
        {
            // We tried preserving the characters/items, but the home
            // map to transfer them from didn't exist.
            return;
        }
    }
    auto filepath = filesystem::dirs::tmp() / (u8"map_"s + mid + u8".s2");
    tmpload(u8"map_"s + mid + u8".s2");
    if (!fs::exists(filepath))
        return;

    auto delete_file = [](const fs::path& tmpfile) {
        auto filepath = filesystem::dirs::tmp() / tmpfile;
        if (fs::exists(filepath))
        {
            fs::remove_all(filepath);
        }
        else
        {
            writeloadedbuff(filepath.filename());
        }
        Save::instance().remove(filepath.filename());
    };

    fs::remove_all(filepath);
    Save::instance().remove(filepath.filename());
    if (file_operation == FileOperation::map_delete)
    {
        delete_file("cdata_"s + mid + ".s2");
        delete_file("sdata_"s + mid + ".s2");
        delete_file("cdatan_"s + mid + ".s2");
        delete_file("inv_"s + mid + ".s2");
        delete_file("mod_map_"s + mid + ".s2");
    }
    delete_file("mdata_"s + mid + ".s2");
    delete_file("mdatan_"s + mid + ".s2");
    delete_file("mef_"s + mid + ".s2");
}


// deletes files inside the temporary directory (tmp/)
void fmode_13()
{
    area_data[area].clear();

    for (const auto& entry : filesystem::glob_files(
             filesystem::dirs::save(playerid),
             std::regex{u8R"(.*_)"s + area + u8R"(_.*\..*)"}))
    {
        writeloadedbuff(entry.path().filename());
        Save::instance().remove(entry.path().filename());
    }
    for (const auto& entry : filesystem::glob_files(
             filesystem::dirs::tmp(),
             std::regex{u8R"(.*_)"s + area + u8R"(_.*\..*)"}))
    {
        Save::instance().remove(entry.path().filename());
        fs::remove_all(entry.path());
    }
}

} // namespace



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
    saved_files[filename] = true;
}



void Save::remove(const fs::path& filename)
{
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
                filesystem::dirs::tmp() / filename,
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
    ELONA_LOG("save.ctrl_file")
        << "ctrl_file " << static_cast<int>(file_operation) << " mid: " << mid
        << " fmapfile: " << fmapfile;

    game_data.play_time =
        game_data.play_time + timeGetTime() / 1000 - time_begin;
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
    ELONA_LOG("save.ctrl_file")
        << "ctrl_file2 " << static_cast<int>(file_operation) << " mid: " << mid
        << " filepath: " << filepathutil::to_utf8_path(filepath);

    game_data.play_time =
        game_data.play_time + timeGetTime() / 1000 - time_begin;
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
        return;
    }

    // Then, needs copy.
    const auto original_file = filesystem::dirs::save(playerid) / filename;
    if (fs::exists(original_file))
    {
        ELONA_LOG("save.ctrl_file")
            << "tmpload " << filepathutil::to_utf8_path(original_file);

        fs::copy_file(
            original_file,
            filesystem::dirs::tmp() / filename,
            fs::copy_option::overwrite_if_exists);
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
