#include "mod_manifest.hpp"

#include "../../thirdparty/json5/json5.hpp"



namespace elona
{
namespace lua
{

namespace
{

struct JSONTable
{
public:
    JSONTable(const fs::path& path)
        : _path(path.to_u8string())
    {
        std::ifstream in{path.native()};
        if (!in)
        {
            throw std::runtime_error{"failed to open " + _path + " to read"};
        }
        std::string source{
            std::istreambuf_iterator<char>{in},
            std::istreambuf_iterator<char>{}};
        try
        {
            const auto value = json5::parse(source);
            _root_object = value.get_object();
        }
        catch (json5::syntax_error& err)
        {
            throw std::runtime_error{
                "failed to parse " + _path + ": " + err.what()};
        }
        catch (json5::invalid_type_error& err)
        {
            throw std::runtime_error{
                "the root value of " + _path +
                " is not an object: " + err.what()};
        }
    }



    template <typename T>
    T get(const char* key)
    {
        if (const auto value = try_get(key))
        {
            return convert<T>(*value, key);
        }
        else
        {
            throw std::runtime_error{
                "failed to load " + _path + ": property \"" + key +
                "\" is required"};
        }
    }


    template <typename T>
    T get_or(const char* key, const T& default_value)
    {
        if (const auto value = try_get(key))
        {
            return convert<T>(*value, key);
        }
        else
        {
            return default_value;
        }
    }


    template <typename T>
    T get_or_default(const char* key)
    {
        return get_or(key, T{});
    }



private:
    std::string _path;
    json5::value::object_type _root_object;



    optional_ref<json5::value> try_get(const char* key)
    {
        const auto itr = _root_object.find(key);
        if (itr == std::end(_root_object))
        {
            return none;
        }
        else
        {
            return itr->second;
        }
    }


    template <typename T>
    T convert(const json5::value& value, const char* key);
};



template <>
std::string JSONTable::convert<std::string>(
    const json5::value& value,
    const char* key)
{
    if (!value.is_string())
    {
        throw std::runtime_error{
            "failed to load " + _path + ": property \"" + key +
            "\" must be a string, but " + to_string(value.type())};
    }
    return value.get_string();
}



template <>
semver::Version JSONTable::convert<semver::Version>(
    const json5::value& value,
    const char* key)
{
    const auto str = convert<std::string>(value, key);
    if (const auto parse_result = semver::Version::parse(str))
    {
        return parse_result.right();
    }
    else
    {
        throw std::runtime_error{
            "failed to load " + _path + ": " + parse_result.left()};
    }
}



template <>
ModManifest::Dependencies JSONTable::convert<ModManifest::Dependencies>(
    const json5::value& value,
    const char* key)
{
    if (!value.is_object())
    {
        throw std::runtime_error{
            "failed to load " + _path + ": property \"" + key +
            "\" must be an object, but " + to_string(value.type())};
    }
    ModManifest::Dependencies result;
    for (const auto& [mod, version] : value.get_object())
    {
        if (!version.is_string())
        {
            throw std::runtime_error{
                "failed to load " + _path + ": key of \"" + key +
                "\" must be a string, but " + to_string(version.type())};
        }
        if (const auto req =
                semver::VersionRequirement::parse(version.get_string()))
        {
            result.emplace(mod, req.right());
        }
        else
        {
            throw std::runtime_error{
                "failed to load " + _path + ": " + req.left()};
        }
    }
    return result;
}

} // namespace



ModManifest ModManifest::load(const fs::path& path)
{
    JSONTable table{path};

    const auto id = table.get<std::string>("id");
    const auto name = table.get_or<std::string>("name", id);
    const auto author = table.get_or_default<std::string>("author");
    const auto description = table.get_or_default<std::string>("description");
    const auto license = table.get_or_default<std::string>("license");
    const auto version = table.get<semver::Version>("version");
    const auto dependencies =
        table.get_or_default<ModManifest::Dependencies>("dependencies");

    return {
        id,
        name,
        author,
        description,
        license,
        version,
        path.parent_path(),
        dependencies,
    };
}



void ModManifest::save() const
{
    if (!path)
    {
        throw std::runtime_error{
            "attempt to save mod manifest having no physical path"};
    }

    json5::value::object_type root_obj;
    root_obj["id"] = id;
    root_obj["name"] = name;
    root_obj["author"] = author;
    root_obj["description"] = description;
    root_obj["license"] = license;
    root_obj["version"] = version.to_string();

    json5::value::object_type deps;
    for (const auto& dep : dependencies)
    {
        deps[dep.first] = dep.second.to_string();
    }
    root_obj["dependencies"] = deps;

    json5::stringify_options opts;
    opts.prettify = true;
    opts.insert_trailing_comma = true;
    opts.unquote_key = true;
    opts.sort_by_key = true;

    const auto manifest_filepath = (*path) / "mod.json";
    std::ofstream out{manifest_filepath.native()};
    if (!out)
    {
        throw std::runtime_error{
            "failed to open mod manifest file to write: " +
            manifest_filepath.to_u8string()};
    }
    out << json5::stringify(root_obj, opts) << std::endl;
}

} // namespace lua
} // namespace elona
