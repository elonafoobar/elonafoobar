#include "thirdparty/microhcl/hcl.hpp"
#include "thirdparty/microhil/hil.hpp"

#include "i18n.hpp"
#include <memory>
#include <fstream>
#include "cat.hpp"
#include "defines.hpp"
#include "elona.hpp"
#include "filesystem.hpp"
#include "random.hpp"
#include "variables.hpp"



namespace elona
{
namespace i18n
{

i18n::store s;

void store::init(fs::path path)
{
    storage.clear();
    for (const auto& entry : filesystem::dir_entries{
             path, filesystem::dir_entries::type::file})
    {
#ifdef ELONA_OS_WINDOWS
        std::ifstream ifs(entry.path().native());
#else
        std::ifstream ifs(filesystem::make_preferred_path_in_utf8(entry.path()));
#endif
        load(ifs, entry.path().string());
    }
}

void store::load(std::istream& is, const std::string& hcl_file)
{
    hcl::ParseResult parseResult = hcl::parse(is);

    if (!parseResult.valid()) {
        std::cerr << parseResult.errorReason << std::endl;
        throw i18n_error(hcl_file, parseResult.errorReason);
    }

    const hcl::Value& value = parseResult.value;

    if (!value.is<hcl::Object>() || !value.has("locale"))
    {
        throw i18n_error(hcl_file, "\"locale\" object not found");
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
        // TODO validate ident names?
        if (!p.valid())
        {
            throw i18n_error(hcl_file, "HIL parse error: " + p.errorReason);
        }

        storage.emplace(current_key, std::move(p.context));
    }
    else if (value.is<hcl::Object>())
    {
        visit_object(value.as<hcl::Object>(), current_key, hcl_file);
    }
}


#define ELONA_DEFINE_I18N_BUILTIN(func_name, return_value) \
    if(func.name == func_name) \
    { \
        return return_value; \
    }

#define ELONA_DEFINE_I18N_BUILTIN_CHARA(func_name, func_ident) \
    if(func.name == func_name)               \
    { \
        int tc_bk = tc; \
        tc = chara.index; \
        std::string val;                                        \
        if (func.args.size() > 1) \
            val = func_ident(func.args[1].as<int>());   \
        else                                                      \
            val = func_ident();   \
        tc = tc_bk; \
        return val; \
    }

#define UNKNOWN_FUNCTION "<unknown function(" + func.name + ")>"

std::string format_builtins_argless(const hil::FunctionCall& func)
{
    ELONA_DEFINE_I18N_BUILTIN("you", name(0));

    return UNKNOWN_FUNCTION;
}

inline std::string builtin_s(const hil::FunctionCall& func, int chara_index)
{
    bool needs_e = false;
    if(func.args.size() > 1)
    {
        needs_e = func.args[1].as<bool>();
    }
    return _s(chara_index, needs_e);
}

std::string format_builtins_bool(const hil::FunctionCall& func, bool value)
{
    ELONA_DEFINE_I18N_BUILTIN("s", builtin_s(func, value ? 0 : 1));
    ELONA_DEFINE_I18N_BUILTIN("is", is(value ? 0 : 1));

    return UNKNOWN_FUNCTION;
}

std::string format_builtins_character(const hil::FunctionCall& func, const character& chara)
{
    ELONA_DEFINE_I18N_BUILTIN("name", name(chara.index));
    ELONA_DEFINE_I18N_BUILTIN("basename", cdatan(0, chara.index));
    ELONA_DEFINE_I18N_BUILTIN("he2", he(chara.index, 1));
    ELONA_DEFINE_I18N_BUILTIN("his2", his(chara.index, 1));
    ELONA_DEFINE_I18N_BUILTIN("him2", him(chara.index, 1));

    // English only
    ELONA_DEFINE_I18N_BUILTIN("he", he(chara.index));
    ELONA_DEFINE_I18N_BUILTIN("his", his(chara.index));
    ELONA_DEFINE_I18N_BUILTIN("him", him(chara.index));
    ELONA_DEFINE_I18N_BUILTIN("s", builtin_s(func, chara.index));
    ELONA_DEFINE_I18N_BUILTIN("is", is(chara.index));
    ELONA_DEFINE_I18N_BUILTIN("have", have(chara.index));
    ELONA_DEFINE_I18N_BUILTIN("himself", yourself(chara.index));
    ELONA_DEFINE_I18N_BUILTIN("his_owned", your(chara.index));
    ELONA_DEFINE_I18N_BUILTIN("name_nojob", sncnv(cdatan(0, chara.index)));

    // Japanese only
    ELONA_DEFINE_I18N_BUILTIN("kare_wa", npcn(chara.index));

    // TODO refactor
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

    return UNKNOWN_FUNCTION;
}

std::string format_builtins_item(const hil::FunctionCall& func, const item& item)
{
    ELONA_DEFINE_I18N_BUILTIN("name", itemname(item.index));
    ELONA_DEFINE_I18N_BUILTIN("basename", ioriginalnameref(item.id));

    // English only
    ELONA_DEFINE_I18N_BUILTIN("is", is2(item.number));
    ELONA_DEFINE_I18N_BUILTIN("s", _s2(item.number));
    ELONA_DEFINE_I18N_BUILTIN("does", does(item.number));

    return UNKNOWN_FUNCTION;
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
