#include "mod_version_resolver.hpp"

#include "../../util/topological_sorter.hpp"
#include "../json5util.hpp"
#include "../log.hpp"
#include "interface.hpp"
#include "mod_manifest.hpp"



namespace elona
{
namespace lua
{

namespace
{

auto parse_mod_list(std::istream& in)
{
    using Result = either::either<std::string, ModList::RequirementList>;

    const auto parse_result = json5util::parse_stream(in);
    if (!parse_result)
    {
        return Result::left_of(parse_result.left());
    }

    const auto& json5_value = parse_result.right();
    if (!json5_value.is_object())
    {
        return Result::left_of("the top level item must be an object");
    }
    const auto& root_obj = json5_value.get_object();
    const auto mods_obj_itr = root_obj.find("mods");
    if (mods_obj_itr == std::end(root_obj))
    {
        return Result::left_of("\"mods\" field is required");
    }
    const auto& mods_obj_value = mods_obj_itr->second;
    if (!mods_obj_value.is_object())
    {
        return Result::left_of("\"mods\" field mut be an object");
    }
    const auto& mods_obj = mods_obj_value.get_object();

    ModList::RequirementList ret;
    for (const auto& pair : mods_obj)
    {
        const auto& mod_id = pair.first;
        const auto& mod_req_value = pair.second;
        if (!mod_req_value.is_string())
        {
            return Result::left_of("mod version requirement must be a string");
        }
        const auto mod_requirement =
            semver::VersionRequirement::parse(mod_req_value.get_string());
        if (!mod_requirement)
        {
            return Result::left_of(mod_requirement.left());
        }
        ret.emplace(mod_id, mod_requirement.right());
    }

    return Result::right_of(ret);
}



auto calculate_loading_order(
    const ResolvedModList::ModVersionMap& mod_versions,
    const ModIndex& index)
{
    using Result = either::
        either<std::vector<std::string>, ResolvedModList::SortedModList>;

    TopologicalSorter<std::string> sorter;

    for (const auto& pair : mod_versions)
    {
        const auto& mod = pair.first;
        const auto& version = pair.second;
        sorter.add(mod);

        for (const auto& dep_mod_id : index.get_dependencies(mod, version))
        {
            sorter.add_dependency(mod, dep_mod_id);
        }
    }

    std::vector<std::string> result;
    std::vector<std::string> cyclic_dependencies;
    std::tie(result, cyclic_dependencies) = sorter.sort();

    if (cyclic_dependencies.empty())
    {
        return Result::right_of(result);
    }
    else
    {
        return Result::left_of(cyclic_dependencies);
    }
}

} // namespace



ModList ModList::from_file(const fs::path& path)
{
    std::ifstream in{path.native()};
    return from_stream(in, filepathutil::to_utf8_path(path));
}



ModList ModList::from_string(const std::string& str)
{
    std::istringstream in{str};
    return from_stream(in, "[string]");
}



ModList ModList::from_stream(std::istream& in, const std::string& filepath)
{
    RequirementList mods;
    if (in)
    {
        auto result = parse_mod_list(in);
        if (result)
        {
            mods = std::move(result.right());
        }
        else
        {
            ELONA_WARN("mod") << "failed to load mod list file (" << filepath
                              << "): " << result.left();
        }
    }
    mods.emplace(std::make_pair(
        "core", semver::VersionRequirement::parse("= 0.2.6").right()));
    return ModList{mods};
}



void ModList::save(const fs::path& path)
{
    json5::value::object_type root_obj;
    json5::value::object_type requirements;
    for (const auto& pair : _mods)
    {
        requirements[pair.first] = pair.second.to_string();
    }
    root_obj["mods"] = requirements;

    json5::stringify_options opts;
    opts.prettify = true;
    opts.insert_trailing_comma = true;
    opts.unquote_key = true;
    opts.sort_by_key = true;

    std::ofstream out{path.native()};
    if (!out)
    {
        throw std::runtime_error{"failed to open mod list file to write: " +
                                 filepathutil::to_utf8_path(path)};
    }
    out << json5::stringify(root_obj, opts) << std::endl;
}



ModIndex ModIndex::traverse(const fs::path& mod_root_dir)
{
    std::unordered_map<std::string, std::vector<IndexEntry>> mods;

    for (const auto& mod_dir : normal_mod_dirs(mod_root_dir))
    {
        ModManifest manifest = ModManifest::load(mod_dir / "mod.json");
        const auto& id = manifest.id;
        const auto& version = manifest.version;
        const auto& dependencies = manifest.dependencies;

        if (mods.find(id) == std::end(mods))
        {
            mods.emplace(id, std::vector<IndexEntry>{});
        }
        mods[id].push_back(IndexEntry{version, dependencies});
    }

    return ModIndex{mods};
}



ModIndex::QueryResult ModIndex::query_latest(
    const std::string& id,
    const semver::VersionRequirement& requirement) const
{
    const auto itr = _mods.find(id);
    if (itr == std::end(_mods))
    {
        return QueryResult::left_of("Mod not found: " + id);
    }
    const auto& versions = itr->second;
    for (auto i = versions.rbegin(), end = versions.rend(); i != end; ++i)
    {
        if (requirement.is_satisfied(i->version))
        {
            return QueryResult::right_of(*i);
        }
    }
    return QueryResult::left_of(
        "Mod not found: " + id + " (" + requirement.to_string() + ")");
}



std::vector<std::string> ModIndex::get_dependencies(
    const std::string& id,
    const semver::Version& version) const
{
    const auto itr = _mods.find(id);
    if (itr == std::end(_mods))
    {
        throw std::runtime_error{"Mod not found: " + id};
    }
    const auto& versions = itr->second;
    for (const auto& v : versions)
    {
        if (v.version == version)
        {
            std::vector<std::string> ret;
            for (const auto& pair : v.dependencies)
            {
                ret.push_back(pair.first);
            }
            return ret;
        }
    }
    throw std::runtime_error{
        "Mod '" + id + "' does not have the version: " + version.to_string()};
}



std::string ModIndex::to_string() const
{
    std::ostringstream ss;
    ss << "Mod Index" << std::endl;
    ss << "=========" << std::endl;
    for (const auto& pair : _mods)
    {
        const auto& id = pair.first;
        const auto& versions = pair.second;
        for (const auto& mod : versions)
        {
            ss << "* " << id << "-" << mod.version.to_string() << std::endl;
            for (const auto& dep_pair : mod.dependencies)
            {
                const auto& dep_id = dep_pair.first;
                const auto& dep_req = dep_pair.second;
                ss << "  -> " << dep_id << " (" << dep_req.to_string() << ")"
                   << std::endl;
            }
        }
        ss << std::endl;
    }
    return ss.str();
}



// TODO: check that the mod identifiers are valid.
ModVersionResolver::ResolveResult ModVersionResolver::resolve(
    const ModList& list,
    const ModLock& lock,
    const ModIndex& index)
{
    (void)lock; // TODO

    auto pending_dependencies = list.mods();
    ResolvedModList::ModVersionMap resolved_dependencies;

    while (!pending_dependencies.empty())
    {
        const auto deps = pending_dependencies;
        pending_dependencies.clear();
        for (const auto& pair : deps)
        {
            const auto& mod_id = pair.first;
            const auto& requirement = pair.second;
            const auto existing_dependency = resolved_dependencies.find(mod_id);
            if (existing_dependency != std::end(resolved_dependencies))
            {
                if (requirement.is_satisfied(existing_dependency->second))
                {
                    continue;
                }
                else
                {
                    // TODO: backtrack to find the version which satisfies the
                    // requirement.
                    return ResolveResult::left_of(
                        "failed to resolve mod dependencies: " + mod_id + " (" +
                        requirement.to_string() + ")");
                }
            }
            else
            {
                const auto index_query_result =
                    index.query_latest(mod_id, requirement);
                if (index_query_result)
                {
                    const auto& mod = index_query_result.right().get();
                    resolved_dependencies.emplace(mod_id, mod.version);
                    for (const auto& pair : mod.dependencies)
                    {
                        const auto& id = pair.first;
                        const auto& req = pair.second;
                        pending_dependencies.emplace(id, req);
                    }
                }
                else
                {
                    // TODO: backtrack to find the version which satisfies the
                    // requirement.
                    return ResolveResult::left_of(index_query_result.left());
                }
            }
        }
    }

    const auto sort_result =
        calculate_loading_order(resolved_dependencies, index);
    if (sort_result)
    {
        return ResolveResult::right_of(
            ResolvedModList{resolved_dependencies, sort_result.right()});
    }
    else
    {
        std::string error_message;
        for (const auto& id : sort_result.left())
        {
            if (!error_message.empty())
            {
                error_message += " -> ";
            }
            error_message += id;
        }
        return ResolveResult::left_of(
            "cyclic dependencies are detected: " + error_message);
    }
}

} // namespace lua
} // namespace elona
