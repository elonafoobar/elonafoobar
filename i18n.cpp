#include "thirdparty/microhcl/hcl.hpp"
#include "thirdparty/microhil/hil.hpp"

#include "i18n.hpp"
#include <memory>
#include <fstream>
#include "cat.hpp"
#include "elona.hpp"
#include "filesystem.hpp"
#include "random.hpp"
#include "variables.hpp"



namespace elona
{
namespace i18n
{


void store::init(fs::path path)
{
    storage.clear();
    for (const auto& entry : filesystem::dir_entries{
             path, filesystem::dir_entries::type::file})
    {
        std::ifstream ifs(filesystem::make_preferred_path_in_utf8(entry.path()));
        load(ifs, entry.path().string());
    }
}

void store::load(std::istream& is, const std::string& hcl_file)
{
    hcl::ParseResult parseResult = hcl::parse(is);

    if (!parseResult.valid()) {
        std::cerr << parseResult.errorReason << std::endl;
        throw new i18n_error(hcl_file, parseResult.errorReason);
    }

    const hcl::Value& value = parseResult.value;

    if (!value.is<hcl::Object>() || !value.has("locale"))
    {
        throw new i18n_error(hcl_file, "\"locale\" object not found");
    }

    const hcl::Value locale = value["locale"];

    visit_object(locale.as<hcl::Object>(), "core.locale", hcl_file);
}

void store::visit_object(const hcl::Object& object,
                              const std::string& current_key,
                              const std::string& hcl_file)
{
    for (const auto& pair : object)
    {
        visit(pair.second, current_key + "." + pair.first, hcl_file);
    }
}

void store::visit(const hcl::Value& value,
                       const std::string& current_key,
                       const std::string& hcl_file)
{
    if (value.is<std::string>())
    {
        std::stringstream ss(value.as<std::string>());

        hil::ParseResult p = hil::parse(ss);
        if (!p.valid())
        {
            throw new i18n_error(hcl_file, "HIL parse error: " + p.errorReason);
        }

        storage.emplace(current_key, std::move(p.context));
    }
    else if (value.is<hcl::Object>())
    {
        visit_object(value.as<hcl::Object>(), current_key, hcl_file);
    }
}

void load(const std::string& language)
{
    for (auto&& entry : filesystem::dir_entries{
             filesystem::path(u8"lang") / language,
             filesystem::dir_entries::type::file,
         })
    {
        cat::global.load(entry.path());
    }
}


std::string _(
    const std::string& key_head,
    const std::vector<std::string>& key_tail)
{
    lua_getglobal(cat::global.ptr(), key_head.c_str());
    int pop_count = 1;
    for (const auto& k : key_tail)
    {
        lua_getfield(cat::global.ptr(), -1, k.c_str());
        ++pop_count;
    }
    if (lua_istable(cat::global.ptr(), -1))
    {
        lua_rawgeti(
            cat::global.ptr(), -1, rnd(lua_rawlen(cat::global.ptr(), -1)) + 1);
        ++pop_count;
    }
    const char* ret = lua_tostring(cat::global.ptr(), -1);
    lua_pop(cat::global.ptr(), pop_count);
    return ret ? ret : "";
}




} // namespace i18n
} // namespace elona
