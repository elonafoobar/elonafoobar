#include "hcl.hpp"
#include "thirdparty/microhil/hil.hpp"

#include <fstream>
#include <memory>
#include "cat.hpp"
#include "defines.hpp"
#include "elona.hpp"
#include "filesystem.hpp"
#include "i18n.hpp"
#include "random.hpp"
#include "variables.hpp"



namespace elona
{
namespace i18n
{

i18n::store s;

void store::init(const std::vector<store::location>& locations)
{
    clear();

    for (const auto& loc : locations)
    {
        load(loc.locale_dir, loc.mod_name);
    }
}

void store::load(const fs::path& path, const std::string& mod_name)
{
    for (const auto& entry :
         filesystem::dir_entries{path, filesystem::dir_entries::type::file})
    {
        std::ifstream ifs(entry.path().native());
        if (!ifs)
        {
            throw std::runtime_error{
                "Failed to open "
                + filesystem::make_preferred_path_in_utf8(entry.path())};
        }

        load(ifs, entry.path().string(), mod_name);
    }
}

void store::load(
    std::istream& is,
    const std::string& hcl_file,
    const std::string& mod_name)
{
    const hcl::Value& value = hclutil::load(is, hcl_file);

    if (!value.is<hcl::Object>() || !value.has("locale"))
    {
        throw i18n_error(hcl_file, "\"locale\" object not found");
    }

    const hcl::Value locale = value["locale"];

    visit_object(locale.as<hcl::Object>(), mod_name + ".locale", hcl_file);
}

void store::visit_object(
    const hcl::Object& object,
    const std::string& current_key,
    const std::string& hcl_file)
{
    for (const auto& pair : object)
    {
        visit(pair.second, current_key + "." + pair.first, hcl_file);
    }
}

void store::visit_string(
    const std::string& string,
    const std::string& current_key,
    const std::string& hcl_file)
{
    std::stringstream ss(string);

    hil::ParseResult p = hil::parse(ss);
    // TODO validate ident names?
    if (!p.valid())
    {
        throw i18n_error(hcl_file, "HIL parse error: " + p.errorReason);
    }

    storage.emplace(current_key, std::move(p.context));
}

void store::visit_list(
    const hcl::List& list,
    const std::string& current_key,
    const std::string& hcl_file)
{
    std::vector<hil::Context> parsed;

    for (const auto& item : list)
    {
        if (!item.is<std::string>())
        {
            throw i18n_error(
                hcl_file,
                current_key + ": List must only contain string values.");
        }

        std::stringstream ss(item.as<std::string>());

        hil::ParseResult p = hil::parse(ss);
        // TODO validate ident names?
        if (!p.valid())
        {
            throw i18n_error(hcl_file, "HIL parse error: " + p.errorReason);
        }
        parsed.push_back(std::move(p.context));
    }

    list_storage.emplace(current_key, std::move(parsed));
}

void store::visit(
    const hcl::Value& value,
    const std::string& current_key,
    const std::string& hcl_file)
{
    if (value.is<std::string>())
    {
        visit_string(value.as<std::string>(), current_key, hcl_file);
    }
    if (value.is<hcl::List>())
    {
        visit_list(value.as<hcl::List>(), current_key, hcl_file);
    }
    else if (value.is<hcl::Object>())
    {
        visit_object(value.as<hcl::Object>(), current_key, hcl_file);
    }
}


#define ELONA_DEFINE_I18N_BUILTIN(func_name, return_value) \
    if (func.name == func_name) \
    { \
        return return_value; \
    }

#define ELONA_DEFINE_I18N_BUILTIN_CHARA(func_name, func_ident) \
    if (func.name == func_name) \
    { \
        int tc_bk = tc; \
        tc = chara.index; \
        std::string val; \
        if (func.args.size() > 1) \
            val = func_ident(func.args[1].as<int>()); \
        else \
            val = func_ident(); \
        tc = tc_bk; \
        return val; \
    }

#define UNKNOWN_FUNCTION(type) \
    "<unknown function(" + func.name + ", " + type + ")>"

std::string format_builtins_argless(const hil::FunctionCall& func)
{
    ELONA_DEFINE_I18N_BUILTIN("you", name(0));

    return UNKNOWN_FUNCTION("argless");
}

inline std::string builtin_he(const hil::FunctionCall& func, int chara_index)
{
    bool bilingual = false;
    if (func.args.size() > 1)
    {
        bilingual = func.args[1].as<bool>();
    }
    return he(chara_index, bilingual);
}

inline std::string builtin_his(const hil::FunctionCall& func, int chara_index)
{
    bool bilingual = false;
    if (func.args.size() > 1)
    {
        bilingual = func.args[1].as<bool>();
    }
    return his(chara_index, bilingual);
}

inline std::string builtin_him(const hil::FunctionCall& func, int chara_index)
{
    bool bilingual = false;
    if (func.args.size() > 1)
    {
        bilingual = func.args[1].as<bool>();
    }
    return him(chara_index, bilingual);
}

inline std::string builtin_s(const hil::FunctionCall& func, int chara_index)
{
    bool needs_e = false;
    if (func.args.size() > 1)
    {
        needs_e = func.args[1].as<bool>();
    }
    return _s(chara_index, needs_e);
}

inline std::string builtin_itemname(
    const hil::FunctionCall& func,
    const item& item)
{
    int number = item.number();
    bool needs_article = true;
    if (func.args.size() > 1)
    {
        number = func.args[1].as<int>();
    }
    if (func.args.size() > 2)
    {
        needs_article = func.args[2].as<bool>();
    }
    return itemname(item.index, number, needs_article ? 0 : 1);
}

std::string format_builtins_bool(const hil::FunctionCall& func, bool value)
{
    ELONA_DEFINE_I18N_BUILTIN("s", builtin_s(func, value ? 0 : 1));
    ELONA_DEFINE_I18N_BUILTIN("is", is(value ? 0 : 1));

    return UNKNOWN_FUNCTION("bool");
}

std::string format_builtins_string(
    const hil::FunctionCall& func,
    std::string value)
{
    ELONA_DEFINE_I18N_BUILTIN("trim_job", sncnv(value));

    return UNKNOWN_FUNCTION("string");
}

std::string format_builtins_integer(const hil::FunctionCall& func, int value)
{
    // For plural
    ELONA_DEFINE_I18N_BUILTIN("s", value == 1 ? u8""s : u8"s"s);
    // For third person singular
    ELONA_DEFINE_I18N_BUILTIN("s2", value == 1 ? u8"s"s : u8""s);

    return UNKNOWN_FUNCTION("integer");
}

std::string format_builtins_character(
    const hil::FunctionCall& func,
    const character& chara)
{
    ELONA_DEFINE_I18N_BUILTIN("name", name(chara.index));
    ELONA_DEFINE_I18N_BUILTIN("basename", cdatan(0, chara.index));
    ELONA_DEFINE_I18N_BUILTIN("he", builtin_he(func, chara.index));
    ELONA_DEFINE_I18N_BUILTIN("his", builtin_his(func, chara.index));
    ELONA_DEFINE_I18N_BUILTIN("him", builtin_him(func, chara.index));

    // English only
    ELONA_DEFINE_I18N_BUILTIN("s", builtin_s(func, chara.index));
    ELONA_DEFINE_I18N_BUILTIN("is", is(chara.index));
    ELONA_DEFINE_I18N_BUILTIN("does", does(chara.index == 0));
    ELONA_DEFINE_I18N_BUILTIN("have", have(chara.index));
    ELONA_DEFINE_I18N_BUILTIN("himself", yourself(chara.index));
    ELONA_DEFINE_I18N_BUILTIN("his_owned", your(chara.index));
    ELONA_DEFINE_I18N_BUILTIN("name_nojob", sncnv(cdatan(0, chara.index)));

    // Japanese only
    ELONA_DEFINE_I18N_BUILTIN("kare_wa", npcn(chara.index));

    ELONA_DEFINE_I18N_BUILTIN_CHARA("yoro", _yoro);
    ELONA_DEFINE_I18N_BUILTIN_CHARA("dozo", _dozo);
    ELONA_DEFINE_I18N_BUILTIN_CHARA("thanks", _thanks);
    ELONA_DEFINE_I18N_BUILTIN_CHARA("rob", _rob);
    ELONA_DEFINE_I18N_BUILTIN_CHARA("ka", _ka);
    ELONA_DEFINE_I18N_BUILTIN_CHARA("da", _da);
    ELONA_DEFINE_I18N_BUILTIN_CHARA("nda", _nda);
    ELONA_DEFINE_I18N_BUILTIN_CHARA("noka", _noka);
    ELONA_DEFINE_I18N_BUILTIN_CHARA("kana", _kana);
    ELONA_DEFINE_I18N_BUILTIN_CHARA("kimi", _kimi);
    ELONA_DEFINE_I18N_BUILTIN_CHARA("ru", _ru);
    ELONA_DEFINE_I18N_BUILTIN_CHARA("tanomu", _tanomu);
    ELONA_DEFINE_I18N_BUILTIN_CHARA("ore", _ore);
    ELONA_DEFINE_I18N_BUILTIN_CHARA("ga", _ga);
    ELONA_DEFINE_I18N_BUILTIN_CHARA("dana", _dana);
    ELONA_DEFINE_I18N_BUILTIN_CHARA("kure", _kure);
    ELONA_DEFINE_I18N_BUILTIN_CHARA("daro", _daro);
    ELONA_DEFINE_I18N_BUILTIN_CHARA("yo", _yo);
    ELONA_DEFINE_I18N_BUILTIN_CHARA("aru", _aru);
    ELONA_DEFINE_I18N_BUILTIN_CHARA("u", _u);
    ELONA_DEFINE_I18N_BUILTIN_CHARA("na", _na);
    ELONA_DEFINE_I18N_BUILTIN_CHARA("ta", _ta);

    return UNKNOWN_FUNCTION("character");
}

std::string format_builtins_item(
    const hil::FunctionCall& func,
    const item& item)
{
    ELONA_DEFINE_I18N_BUILTIN("itemname", builtin_itemname(func, item));
    ELONA_DEFINE_I18N_BUILTIN("itembasename", ioriginalnameref(item.id));

    // English only
    ELONA_DEFINE_I18N_BUILTIN("is", is2(item.number()));
    ELONA_DEFINE_I18N_BUILTIN("s", _s2(item.number()));
    ELONA_DEFINE_I18N_BUILTIN("does", does(item.number()));

    return UNKNOWN_FUNCTION("item");
}

#undef ELONA_DEFINE_I18N_BUILTIN
#undef ELONA_DEFINE_I18N_BUILTIN_CHARA
#undef UNKNOWN_FUNCTION


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

std::string space_if_needed()
{
    if (jp)
    {
        return "";
    }
    else
    {
        return u8" ";
    }
}



} // namespace i18n
} // namespace elona
