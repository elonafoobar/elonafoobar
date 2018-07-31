#include "lua_env.hpp"

#include <iterator>
#include "../ability.hpp"
#include "../audio.hpp"
#include "../character.hpp"
#include "../dmgheal.hpp"
#include "../enchantment.hpp"
#include "../fov.hpp"
#include "../gdata.hpp"
#include "../i18n.hpp"
#include "../input.hpp"
#include "../item.hpp"
#include "../itemgen.hpp"
#include "../log.hpp"
#include "../map.hpp"
#include "../map_cell.hpp"
#include "../position.hpp"
#include "../status_ailment.hpp"
#include "../trait.hpp"
#include "../ui.hpp"
#include "../variables.hpp"

/***
 * See doc/api for the API documentation.
 * Be sure to update it if you change anything here.
 * LDoc is completely broken when it comes to parsing C++.
 */
namespace elona
{

namespace lua
{

namespace Chara
{
bool is_alive(lua_character_handle);
bool is_player(lua_character_handle);
bool is_ally(lua_character_handle);
bool flag(lua_character_handle, int);
int count();
sol::optional<lua_character_handle> player();
sol::optional<lua_character_handle> create(const position_t&, int);
sol::optional<lua_character_handle> create_xy(int, int, int);

void bind(sol::table& Elona);
}; // namespace Chara

bool Chara::is_alive(lua_character_handle handle)
{
    if (!lua::lua->get_handle_manager().handle_is_valid(handle))
    {
        return false;
    }

    auto& chara = lua::lua->get_handle_manager().get_ref<character>(handle);
    return chara.state == 1;
}

bool Chara::is_player(lua_character_handle handle)
{
    auto& chara = lua::lua->get_handle_manager().get_ref<character>(handle);
    return chara.index == 0;
}

bool Chara::is_ally(lua_character_handle handle)
{
    auto& chara = lua::lua->get_handle_manager().get_ref<character>(handle);
    return !Chara::is_player(handle) && chara.index <= 16;
}

int Chara::count()
{
    return gdata_crowd_density;
}

bool Chara::flag(lua_character_handle handle, int flag)
{
    if (flag < 5 || flag > 991 || (flag > 32 && flag < 960))
    {
        return false;
    }
    auto& chara = lua::lua->get_handle_manager().get_ref<character>(handle);
    return chara._flags[flag] == 1;
}

sol::optional<lua_character_handle> Chara::player()
{
    if (elona::cdata[0].state == 0)
    {
        return sol::nullopt;
    }
    else
    {
        lua_character_handle handle =
            lua::lua->get_handle_manager().get_handle(elona::cdata[0]);
        return handle;
    }
}

sol::optional<lua_character_handle> Chara::create(
    const position_t& position,
    int id)
{
    return Chara::create_xy(position.x, position.y, id);
}

sol::optional<lua_character_handle> Chara::create_xy(int x, int y, int id)
{
    elona::flt();
    if (elona::chara_create(-1, id, x, y) != 0)
    {
        lua_character_handle handle =
            lua::lua->get_handle_manager().get_handle(
                elona::cdata[elona::rc]);
        return handle;
    }
    else
    {
        return sol::nullopt;
    }
}

void Chara::bind(sol::table& Elona)
{
    sol::table Chara = Elona.create_named("Chara");
    Chara.set_function("is_alive", Chara::is_alive);
    Chara.set_function("is_player", Chara::is_player);
    Chara.set_function("is_ally", Chara::is_ally);
    Chara.set_function("count", Chara::count);
    Chara.set_function("flag", Chara::flag);
    Chara.set_function("player", Chara::player);
    Chara.set_function(
        "create", sol::overload(Chara::create, Chara::create_xy));
}

namespace Pos
{
int dist(const position_t&, const position_t&);
int dist_xy(int, int, int, int);

void bind(sol::table& Elona);
} // namespace Pos

int Pos::dist(const position_t& from, const position_t& to)
{
    return Pos::dist_xy(from.x, from.y, to.x, to.y);
}

int Pos::dist_xy(int fx, int fy, int tx, int ty)
{
    return elona::dist(fx, fy, tx, ty);
}

void Pos::bind(sol::table& Elona)
{
    sol::table Pos = Elona.create_named("Pos");
    Pos.set_function("dist", sol::overload(Pos::dist, Pos::dist_xy));
}


namespace World
{
int time();

void bind(sol::table& Elona);
}; // namespace World

int World::time()
{
    return gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
        + gdata_year * 24 * 30 * 12;
}

void World::bind(sol::table& Elona)
{
    sol::table World = Elona.create_named("World");
    World.set_function("time", World::time);
}


namespace Magic
{
void cast_self(lua_character_handle, int, int, const position_t&);
void cast(lua_character_handle, lua_character_handle, int, int);

void bind(sol::table& Elona);
} // namespace Magic

void Magic::cast_self(
    lua_character_handle caster_handle,
    int effect_id,
    int effect_power,
    const position_t& target_location)
{
    elona::tlocx = target_location.x;
    elona::tlocy = target_location.y;
    Magic::cast(caster_handle, caster_handle, effect_id, effect_power);
}

void Magic::cast(
    lua_character_handle caster_handle,
    lua_character_handle target_handle,
    int effect_id,
    int effect_power)
{
    int ccbk = elona::cc;
    int tcbk = elona::tc;

    try
    {
        auto caster = lua::lua->get_handle_manager().get_ref<character>(caster_handle);
        auto target = lua::lua->get_handle_manager().get_ref<character>(target_handle);
        elona::cc = caster.index;
        elona::tc = target.index;
        elona::efid = effect_id;
        elona::efp = effect_power;
        elona::magic();
        elona::cc = ccbk;
        elona::tc = tcbk;
    }
    catch (std::exception& e)
    {
        // Always reset the values of cc/tc if a handle is invalid.
        elona::cc = ccbk;
        elona::tc = tcbk;

        // Throw the exception so the calling script receives it.
        throw e;
    }
}

void Magic::bind(sol::table& Elona)
{
    sol::table Magic = Elona.create_named("Magic");
    Magic.set_function("cast", sol::overload(Magic::cast_self, Magic::cast));
}

namespace Map
{
int width();
int height();
bool is_overworld();
bool valid(const position_t&);
bool valid_xy(int, int);
bool can_access(const position_t&);
bool can_access_xy(int, int);
position_t bound_within(const position_t&);
position_t random_pos();
int generate_tile(tile_kind_t);
void set_tile(const position_t&, int);
void set_tile_xy(int, int, int);
void set_tile_memory(const position_t&, int);
void set_tile_memory_xy(int, int, int);

void bind(sol::table& Elona);
} // namespace Map

int Map::width()
{
    return mdata_map_width;
}

int Map::height()
{
    return mdata_map_height;
}

bool Map::is_overworld()
{
    return elona::mdata_map_atlas_number == 0;
}

bool Map::valid(const position_t& position)
{
    return Map::valid_xy(position.x, position.y);
}

bool Map::valid_xy(int x, int y)
{
    if (Map::is_overworld())
    {
        return false;
    }
    if (x < 0 || y < 0 || x >= Map::width() || y >= Map::height())
    {
        return false;
    }

    return elona::map(x, y, 0) != 0;
}

bool Map::can_access(const position_t& position)
{
    return Map::can_access_xy(position.x, position.y);
}

bool Map::can_access_xy(int x, int y)
{
    if (Map::is_overworld())
    {
        return false;
    }
    elona::cell_check(x, y);
    return cellaccess != 0;
}

position_t Map::bound_within(const position_t& position)
{
    int x = clamp(position.x, 0, mdata_map_width - 1);
    int y = clamp(position.y, 0, mdata_map_height - 1);
    return position_t{x, y};
}

position_t Map::random_pos()
{
    return Map::bound_within(
        position_t{elona::rnd(mdata_map_width - 1), elona::rnd(mdata_map_height - 1)});
}

int Map::generate_tile(tile_kind_t type)
{
    return elona::cell_get_type(type);
}

void Map::set_tile(const position_t& position, int type)
{
    Map::set_tile_xy(position.x, position.y, type);
}

void Map::set_tile_xy(int x, int y, int type)
{
    if (Map::is_overworld())
    {
        return;
    }
    if (!Map::valid_xy(x, y))
    {
        return;
    }

    elona::map(x, y, 0) = type;
}

void Map::set_tile_memory(const position_t& position, int type)
{
    Map::set_tile_memory_xy(position.x, position.y, type);
}

void Map::set_tile_memory_xy(int x, int y, int type)
{
    if (Map::is_overworld())
    {
        return;
    }
    if (!Map::valid_xy(x, y))
    {
        return;
    }

    elona::map(x, y, 2) = type;
}

void Map::bind(sol::table& Elona)
{
    sol::table Map = Elona.create_named("Map");
    Map.set_function("width", Map::width);
    Map.set_function("height", Map::height);
    Map.set_function("is_overworld", Map::is_overworld);
    Map.set_function("valid", sol::overload(Map::valid, Map::valid_xy));
    Map.set_function(
        "can_access", sol::overload(Map::can_access, Map::can_access_xy));
    Map.set_function("bound_within", Map::bound_within);
    Map.set_function("random_pos", Map::random_pos);
    Map.set_function("generate_tile", Map::generate_tile);
    Map.set_function(
        "set_tile", sol::overload(Map::set_tile, Map::set_tile_xy));
    Map.set_function(
        "set_tile_memory",
        sol::overload(Map::set_tile_memory, Map::set_tile_memory_xy));
}

namespace FOV
{
bool los(const position_t&, const position_t&);
bool los_xy(int, int, int, int);
bool you_see(lua_character_handle);
bool you_see_pos(const position_t&);
bool you_see_pos_xy(int, int);
void refresh();

void bind(sol::table& Elona);
}; // namespace FOV

bool FOV::los(const position_t& from, const position_t& to)
{
    return FOV::los_xy(from.x, from.y, to.x, to.y);
}

bool FOV::los_xy(int fx, int fy, int tx, int ty)
{
    return elona::fov_los(fx, fy, tx, ty) == 1;
}

bool FOV::you_see(lua_character_handle handle)
{
    auto& chara = lua::lua->get_handle_manager().get_ref<character>(handle);
    return elona::is_in_fov(chara.index);
}

bool FOV::you_see_pos(const position_t& pos)
{
    return elona::is_in_fov(pos) == 1;
}

bool FOV::you_see_pos_xy(int x, int y)
{
    return elona::is_in_fov(position_t(x, y)) == 1;
}

void FOV::refresh()
{
    gmode(2);
    sxfix = 0;
    syfix = 0;
    update_scrolling_info();
    update_slight();
    label_1433();
}

void FOV::bind(sol::table& Elona)
{
    sol::table FOV = Elona.create_named("FOV");
    FOV.set_function("los", sol::overload(FOV::los, FOV::los_xy));
    FOV.set_function(
        "you_see",
        sol::overload(FOV::you_see_pos, FOV::you_see_pos_xy, FOV::you_see));
    FOV.set_function("refresh", FOV::refresh);
}


namespace Rand
{
int rnd(int n);
bool one_in(int n);
bool coinflip();

void bind(sol::table& Elona);
}; // namespace Rand


int Rand::rnd(int n)
{
    return elona::rnd(n);
}

bool Rand::one_in(int n)
{
    return Rand::rnd(n) == 0;
}

bool Rand::coinflip()
{
    return Rand::one_in(2);
}

void Rand::bind(sol::table& Elona)
{
    sol::table Rand = Elona.create_named("Rand");
    Rand.set_function("rnd", Rand::rnd);
    Rand.set_function("one_in", Rand::one_in);
    Rand.set_function("coinflip", Rand::coinflip);
}

namespace Item
{
int count();
sol::optional<lua_item_handle> create(const position_t&, int, int);
sol::optional<lua_item_handle> create_xy(int, int, int, int);
bool has_enchantment(const lua_item_handle, int);
void remove(lua_item_handle);

void bind(sol::table& Elona);
} // namespace Item

int Item::count()
{
    return inv_sum(-1);
}

sol::optional<lua_item_handle>
Item::create(const position_t& position, int id, int number)
{
    return Item::create_xy(position.x, position.y, id, number);
}

sol::optional<lua_item_handle> Item::create_xy(int x, int y, int id, int number)
{
    elona::flt();
    if (elona::itemcreate(-1, id, x, y, number) != 0)
    {
        lua_item_handle handle = lua::lua->get_handle_manager().get_handle(
            elona::inv[elona::ci]); // TODO deglobalize ci
        return handle;
    }
    else
    {
        return sol::nullopt;
    }
}

bool Item::has_enchantment(const lua_item_handle handle, int id)
{
    auto& item_ref = lua::lua->get_handle_manager().get_ref<item>(handle);
    return elona::encfindspec(item_ref.index, id);
}

void Item::remove(lua_item_handle handle)
{
    auto& item_ref = lua::lua->get_handle_manager().get_ref<item>(handle);
    item_ref.remove();
}

void Item::bind(sol::table& Elona)
{
    sol::table Item = Elona.create_named("Item");
    Item.set_function("count", Item::count);
    Item.set_function("create", sol::overload(Item::create, Item::create_xy));
    Item.set_function("remove", Item::remove);
    Item.set_function("has_enchantment", Item::has_enchantment);
}


namespace Skill
{
int level(int, lua_character_handle);

void bind(sol::table& Elona);
} // namespace Skill

int Skill::level(int skill, lua_character_handle handle)
{
    if (skill < 0 || skill >= 600)
    {
        return -1;
    }
    auto& chara = lua::lua->get_handle_manager().get_ref<character>(handle);
    return elona::sdata(skill, chara.index);
}

void Skill::bind(sol::table& Elona)
{
    sol::table Skill = Elona.create_named("Skill");
    Skill.set_function("level", Skill::level);
}


namespace Trait
{
sol::optional<int> level(int);
sol::optional<int> min(int);
sol::optional<int> max(int);
void set(int, int);
void modify(int, int);

void bind(sol::table& Elona);
} // namespace Trait

sol::optional<int> Trait::level(int trait_id)
{
    if (trait_get_info(0, trait_id) == 0)
    {
        return sol::nullopt;
    }
    return elona::trait(trait_id);
}

sol::optional<int> Trait::min(int trait_id)
{
    if (trait_get_info(0, trait_id) == 0)
    {
        return sol::nullopt;
    }
    return elona::traitref(1);
}

sol::optional<int> Trait::max(int trait_id)
{
    if (trait_get_info(0, trait_id) == 0)
    {
        return sol::nullopt;
    }
    return elona::traitref(2);
}

void Trait::set(int trait_id, int level)
{
    if (trait_get_info(0, trait_id) == 0)
    {
        return;
    }
    if (elona::trait(trait_id) < level
        && elona::trait(trait_id) < elona::traitref(2)
        && traitrefn(0) != "")
    {
        snd(61);
        elona::txtef(2);
        elona::txt(traitrefn(0));
    }
    else if (elona::trait(trait_id) > level
             && elona::trait(trait_id) > elona::traitref(1)
             && traitrefn(1) != "")
    {
        snd(61);
        elona::txtef(3);
        elona::txt(traitrefn(1));
    }
    elona::trait(trait_id) = clamp(level,
                                   elona::traitref(1),
                                   elona::traitref(2));
    chara_refresh(0);
}

void Trait::modify(int trait_id, int delta)
{
    if (trait_get_info(0, trait_id) == 0)
    {
        return;
    }
    if (delta > 0
        && elona::trait(trait_id) < elona::traitref(2)
        && traitrefn(0) != "")
    {
        snd(61);
        elona::txtef(2);
        elona::txt(traitrefn(0));
    }
    else if (delta < 0
             && elona::trait(trait_id) > elona::traitref(1)
             && traitrefn(1) != "")
    {
        snd(61);
        elona::txtef(3);
        elona::txt(traitrefn(1));
    }
    elona::trait(trait_id) = clamp(elona::trait(trait_id) + delta,
                                   elona::traitref(1),
                                   elona::traitref(2));
    chara_refresh(0);
}

void Trait::bind(sol::table& Elona)
{
    sol::table Trait = Elona.create_named("Trait");
    Trait.set_function("level", Trait::level);
    Trait.set_function("min", Trait::min);
    Trait.set_function("max", Trait::max);
    Trait.set_function("set", Trait::set);
    Trait.set_function("modify", Trait::modify);
}



namespace Input
{
bool yes_no(const std::string&);
sol::optional<int> prompt_number(const std::string&, int);
sol::optional<int> prompt_number_with_initial(const std::string&, int, int);
sol::optional<std::string> prompt_text(const std::string&, bool);
sol::optional<int> prompt_choice(sol::variadic_args);

void bind(sol::table&);
}; // namespace GUI

bool Input::yes_no(const std::string& message)
{
    txt(message + " ");
    ELONA_YES_NO_PROMPT();
    int rtval = show_prompt(promptx, prompty, 160);
    return rtval == 0;
}

sol::optional<int> Input::prompt_number(const std::string& message, int max)
{
    return Input::prompt_number_with_initial(message, max, 0);
}

sol::optional<int> Input::prompt_number_with_initial(const std::string& message,
                                                     int max,
                                                     int initial)
{
    if (max < 1)
    {
        throw sol::error("Input.prompt_number called with max < 1");
    }

    txt(message + " ");
    input_number_dialog(
        (windoww - 200) / 2 + inf_screenx,
        winposy(60),
        max,
        initial);

    if (rtval == -1)
    {
        return sol::nullopt;
    }

    return elona::stoi(elona::inputlog(0));
}

sol::optional<std::string> Input::prompt_text(const std::string& message, bool is_cancelable)
{
    txt(message + " ");
    bool canceled = input_text_dialog((windoww - 360) / 2 + inf_screenx, winposy(90), 20, is_cancelable, true);
    if (canceled)
    {
        return sol::nullopt;
    }

    return elona::inputlog(0);
}

sol::optional<int> Input::prompt_choice(sol::variadic_args args)
{
    if (args.size() == 0)
    {
        throw sol::error("Input.prompt_choice called with no arguments");
    }

    for (size_t i = 0; i < args.size(); i++)
    {
        ELONA_APPEND_PROMPT(args[i].as<std::string>(), u8"null"s, std::to_string(i));
    }

    int rtval = show_prompt(promptx, prompty, 160);
    if (rtval == -1)
    {
        return sol::nullopt;
    }

    // Lua tables are 1-indexed, so add 1 to the result.
    return rtval + 1;
}

void Input::bind(sol::table& Elona)
{
    sol::table Input = Elona.create_named("Input");
    Input.set_function("yes_no", Input::yes_no);
    Input.set_function("prompt_choice", Input::prompt_choice);
    Input.set_function("prompt_number", sol::overload(Input::prompt_number,
                                                      Input::prompt_number_with_initial));
    Input.set_function("prompt_text", Input::prompt_text);
}


namespace GUI
{
void txt(const std::string&);
void txtnew();
void txt_txtef(const std::string&, color_index_t);
void txtef(color_index_t);
void bind(sol::table&);
}; // namespace GUI

void GUI::txt(const std::string& message)
{
    elona::txt(message);
}

void GUI::txt_txtef(const std::string& message, color_index_t color)
{
    GUI::txtef(color);
    elona::txt(message);
}

void GUI::txtef(color_index_t color)
{
    if (color < color_index_t::none || color > color_index_t::yellow_green)
    {
        return;
    }
    elona::txtef(color);
}

void GUI::txtnew()
{
    elona::txtnew();
}

void GUI::bind(sol::table& Elona)
{
    sol::table GUI = Elona.create_named("GUI");
    GUI.set_function("txt", sol::overload(GUI::txt, GUI::txt_txtef));
    GUI.set_function("txtef", GUI::txtef);
    GUI.set_function("txtnew", GUI::txtnew);
}


namespace I18N
{
std::string get(const std::string&, sol::variadic_args);
sol::optional<std::string> get_optional(const std::string&, sol::variadic_args);
std::string get_enum(const std::string&, int, sol::variadic_args);
std::string get_enum_property(
    const std::string&,
    const std::string&,
    int,
    sol::variadic_args);
sol::optional<std::string> get_enum_property_optional(
    const std::string&,
    const std::string&,
    int,
    sol::variadic_args);

void bind(sol::table&);
} // namespace I18N

std::string I18N::get(const std::string& key, sol::variadic_args args)
{
    switch (args.size())
    {
    case 0: return i18n::s.get(key);
    case 1: return i18n::s.get(key, args[0].get<sol::object>());
    case 2:
        return i18n::s.get(
            key, args[0].get<sol::object>(), args[1].get<sol::object>());
    case 3:
        return i18n::s.get(
            key,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>());
    case 4:
        return i18n::s.get(
            key,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>());
    case 5:
        return i18n::s.get(
            key,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>(),
            args[4].get<sol::object>());
    case 6:
    default:
        return i18n::s.get(
            key,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>(),
            args[4].get<sol::object>(),
            args[5].get<sol::object>());
    }
}

sol::optional<std::string> I18N::get_optional(
    const std::string& key,
    sol::variadic_args args)
{
    optional<std::string> opt = none;

    switch (args.size())
    {
    case 0: opt = i18n::s.get_optional(key); break;
    case 1: opt = i18n::s.get_optional(key, args[0].get<sol::object>()); break;
    case 2:
        opt = i18n::s.get_optional(
            key, args[0].get<sol::object>(), args[1].get<sol::object>());
        break;
    case 3:
        opt = i18n::s.get_optional(
            key,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>());
        break;
    case 4:
        opt = i18n::s.get_optional(
            key,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>());
        break;
    case 5:
        opt = i18n::s.get_optional(
            key,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>(),
            args[4].get<sol::object>());
        break;
    case 6:
    default:
        opt = i18n::s.get_optional(
            key,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>(),
            args[4].get<sol::object>(),
            args[5].get<sol::object>());
        break;
    }

    if (opt)
    {
        return *opt;
    }

    return sol::nullopt;
}

std::string
I18N::get_enum(const std::string& key, int index, sol::variadic_args args)
{
    switch (args.size())
    {
    case 0: return i18n::s.get_enum(key, index);
    case 1: return i18n::s.get_enum(key, index, args[0].get<sol::object>());
    case 2:
        return i18n::s.get_enum(
            key, index, args[0].get<sol::object>(), args[1].get<sol::object>());
    case 3:
        return i18n::s.get_enum(
            key,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>());
    case 4:
        return i18n::s.get_enum(
            key,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>());
    case 5:
        return i18n::s.get_enum(
            key,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>(),
            args[4].get<sol::object>());
    case 6:
    default:
        return i18n::s.get_enum(
            key,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>(),
            args[4].get<sol::object>(),
            args[5].get<sol::object>());
    }
}

std::string I18N::get_enum_property(
    const std::string& key_head,
    const std::string& key_tail,
    int index,
    sol::variadic_args args)
{
    optional<std::string> opt = none;

    switch (args.size())
    {
    case 0: return i18n::s.get_enum_property(key_head, key_tail, index);
    case 1:
        return i18n::s.get_enum_property(
            key_head, key_tail, index, args[0].get<sol::object>());
    case 2:
        return i18n::s.get_enum_property(
            key_head,
            key_tail,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>());
    case 3:
        return i18n::s.get_enum_property(
            key_head,
            key_tail,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>());
    case 4:
        return i18n::s.get_enum_property(
            key_head,
            key_tail,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>());
    case 5:
        return i18n::s.get_enum_property(
            key_head,
            key_tail,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>(),
            args[4].get<sol::object>());
    case 6:
    default:
        return i18n::s.get_enum_property(
            key_head,
            key_tail,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>(),
            args[4].get<sol::object>(),
            args[5].get<sol::object>());
    }
}

sol::optional<std::string> I18N::get_enum_property_optional(
    const std::string& key_head,
    const std::string& key_tail,
    int index,
    sol::variadic_args args)
{
    optional<std::string> opt = none;

    switch (args.size())
    {
    case 0:
        opt = i18n::s.get_enum_property_opt(key_head, key_tail, index);
        break;
    case 1:
        opt = i18n::s.get_enum_property_opt(
            key_head, key_tail, index, args[0].get<sol::object>());
        break;
    case 2:
        opt = i18n::s.get_enum_property_opt(
            key_head,
            key_tail,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>());
        break;
    case 3:
        opt = i18n::s.get_enum_property_opt(
            key_head,
            key_tail,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>());
        break;
    case 4:
        opt = i18n::s.get_enum_property_opt(
            key_head,
            key_tail,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>());
        break;
    case 5:
        opt = i18n::s.get_enum_property_opt(
            key_head,
            key_tail,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>(),
            args[4].get<sol::object>());
        break;
    case 6:
    default:
        opt = i18n::s.get_enum_property_opt(
            key_head,
            key_tail,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>(),
            args[4].get<sol::object>(),
            args[5].get<sol::object>());
    }

    if (opt)
    {
        return *opt;
    }

    return sol::nullopt;
}

void I18N::bind(sol::table& Elona)
{
    sol::table I18N = Elona.create_named("I18N");
    I18N.set_function("get", I18N::get);
    I18N.set_function("get_optional", I18N::get_optional);
    I18N.set_function("get_enum", I18N::get_enum);
    I18N.set_function("get_enum_property", I18N::get_enum_property);
    I18N.set_function(
        "get_enum_property_optional", I18N::get_enum_property_optional);
}


namespace Math
{
int clamp(int, int, int);

void bind(sol::table&);
} // namespace Math

int Math::clamp(int n, int min, int max)
{
    return elona::clamp(n, min, max);
}

void Math::bind(sol::table& Elona)
{
    sol::table Math = Elona.create_named("Math");
    Math.set_function("clamp", Math::clamp);
}


namespace Debug
{
void log(const std::string&);
void report_error(const std::string&);
void dump_characters();
void dump_items();

void bind(sol::table& Elona);
} // namespace Debug

void Debug::log(const std::string& message)
{
    ELONA_LOG(message);
}

void Debug::report_error(const std::string& message)
{
    std::istringstream sstream(message);
    std::string line;

    GUI::txtef(color_index_t::red);
    GUI::txt("Script error: ");
    while (getline(sstream, line, '\n'))
    {
        GUI::txtef(color_index_t::red);
        GUI::txt(line + "  ");
    }

    ELONA_LOG("Script error: " << message);
    std::cerr << "Script error: " << message << std::endl;
}

void Debug::dump_characters()
{
    ELONA_LOG("===== Charas =====")
    for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
    {
        if (elona::cdata[cnt].state != 0)
            ELONA_LOG(
                elona::cdata[cnt].index
                << ") Name: " << elona::name(cnt)
                << ", Pos: " << elona::cdata[cnt].position);
    }
}

void Debug::dump_items()
{
    ELONA_LOG("===== Items  =====")
    for (const auto& cnt : items(-1))
    {
        if (elona::inv[cnt].number() != 0)
            ELONA_LOG(
                elona::inv[cnt].index
                << ") Name: " << elona::itemname(cnt)
                << ", Pos: " << elona::inv[cnt].position << ", Curse: "
                << static_cast<int>(elona::inv[cnt].curse_state) << ", Ident: "
                << static_cast<int>(elona::inv[cnt].identification_state)
                << ", Count: " << elona::inv[cnt].count);
    }
}

void Debug::bind(sol::table& Elona)
{
    sol::table Debug = Elona.create_named("Debug");
    Debug.set_function("log", Debug::log);
    Debug.set_function("report_error", Debug::report_error);
    Debug.set_function("dump_characters", Debug::dump_characters);
    Debug.set_function("dump_items", Debug::dump_items);
}


/***
 * Methods on usertype classes.
 *
 * The below methods do not take handles as a first argument, because
 * handles can transparently pass their underlying C++ references to
 * them.
 */

namespace LuaCharacter
{
void damage_hp(character&, int);
void damage_hp_source(character&, int, damage_source_t);
void damage_hp_chara(character&, int, lua_character_handle handle);
void apply_ailment(character&, status_ailment_t, int);
bool recruit_as_ally(character&);
void set_flag(character&, int, bool);
void gain_skill(character&, int, int);
void gain_skill_stock(character&, int, int, int);
void gain_skill_exp(character&, int, int);
void modify_trait(character&, int, int);
} // namespace LuaCharacter

void LuaCharacter::damage_hp(character& self, int amount)
{
    LuaCharacter::damage_hp_source(self, amount, damage_source_t::unseen_hand);
}

void LuaCharacter::damage_hp_source(
    character& self,
    int amount,
    damage_source_t source)
{
    elona::dmghp(self.index, amount, static_cast<int>(source));
}

void LuaCharacter::damage_hp_chara(
    character& self,
    int amount,
    lua_character_handle handle)
{
    auto other = lua::lua->get_handle_manager().get_ref<character>(handle);
    elona::dmghp(self.index, amount, other.index);
}

void LuaCharacter::apply_ailment(
    character& self,
    status_ailment_t ailment,
    int power)
{
    assert(power > 0);
    elona::dmgcon(self.index, ailment, power);
}

bool LuaCharacter::recruit_as_ally(character& self)
{
    // can't use Chara methods because they take a handle...
    // TODO: DRY (would need to be far-reaching)
    if (self.state == 0 || (self.index != 0 && self.index <= 16)
        || self.index == 0)
    {
        return false;
    }
    elona::rc = self.index;
    return new_ally_joins() == 1;
}

void LuaCharacter::set_flag(character& self, int flag, bool value)
{
    if (flag < 5 || flag > 991 || (flag > 32 && flag < 960))
    {
        return;
    }
    self._flags[flag] = value ? 1 : 0;
}

void LuaCharacter::gain_skill(character& self, int skill, int initial_level)
{
    LuaCharacter::gain_skill_stock(self, skill, initial_level, 0);
}

void LuaCharacter::gain_skill_stock(
    character& self,
    int skill,
    int initial_level,
    int initial_stock)
{
    if (skill < 0 || skill >= 600)
    {
        return;
    }
    elona::skillgain(self.index, skill, initial_level, initial_stock);
}

void LuaCharacter::gain_skill_exp(character& self, int skill, int amount)
{
    if (skill < 0 || skill >= 600)
    {
        return;
    }
    elona::skillmod(skill, self.index, amount);
}

/***
 * Set up usertype tables in Sol so we can call methods with them.
 */
void init_usertypes(lua_env& lua)
{
    lua.get_state()->new_usertype<position_t>(
        "LuaPosition",
        sol::constructors<position_t(), position_t(int, int)>(),
        "x",
        &position_t::x,
        "y",
        &position_t::y);
    lua.get_state()->new_usertype<character>(
        character::lua_type(),
        "lua_type",
        &character::lua_type,
        "damage_hp",
        sol::overload(
            &LuaCharacter::damage_hp,
            &LuaCharacter::damage_hp_source,
            &LuaCharacter::damage_hp_chara),
        "apply_ailment",
        &LuaCharacter::apply_ailment,
        "recruit_as_ally",
        &LuaCharacter::recruit_as_ally,
        "set_flag",
        &LuaCharacter::set_flag,
        "gain_skill",
        sol::overload(
            &LuaCharacter::gain_skill, &LuaCharacter::gain_skill_stock),
        "gain_skill_exp",
        &LuaCharacter::gain_skill_exp,
        "hp",
        sol::readonly(&character::hp),
        "max_hp",
        sol::readonly(&character::max_hp),
        "mp",
        sol::readonly(&character::mp),
        "max_mp",
        sol::readonly(&character::max_mp),
        "sp",
        sol::readonly(&character::sp),
        "max_sp",
        sol::readonly(&character::max_sp),
        "shop_rank",
        &character::shop_rank,
        "character_role",
        &character::character_role,
        "index",
        sol::readonly(&character::index),
        "id",
        sol::readonly(&character::id),
        "position",
        &character::position,
        "name",
        sol::property([](character& c) { return elona::cdatan(0, c.index); }),
        "experience",
        &character::experience);
    lua.get_state()->new_usertype<item>(
        item::lua_type(),
        "lua_type",
        &item::lua_type,
        "set_number",
        &item::set_number,
        "curse_state",
        &item::curse_state,
        "identify_state",
        &item::identification_state,
        "index",
        sol::readonly(&item::index),
        "position",
        &item::position,
        "number",
        sol::property([](item& i) { return i.number(); }),
        "id",
        &item::id,
        "count",
        &item::count,
        "name",
        sol::property([](item& i) { return elona::itemname(i.index); }),
        "subname",
        &item::subname,
        "param1",
        &item::param1,
        "param2",
        &item::param2
        );
}


api_manager::api_manager(lua_env* lua)
{
    this->lua = lua;
    this->api_env = sol::environment(
        *(this->lua->get_state()),
        sol::create,
        this->lua->get_state()->globals());

    // Bind the API tables at e.g. Elona["core"]["Chara"]
    sol::table Elona = api_env.create_named("Elona");
    sol::table core = Elona.create_named("core");

    Chara::bind(core);
    Pos::bind(core);
    World::bind(core);
    FOV::bind(core);
    Magic::bind(core);
    Rand::bind(core);
    Item::bind(core);
    Skill::bind(core);
    Trait::bind(core);
    Input::bind(core);
    GUI::bind(core);
    I18N::bind(core);
    Map::bind(core);
    Debug::bind(core);

    // register usertypes globally, so the handle manager can get at them.
    init_usertypes(*lua);
}

bool api_manager::is_loaded()
{
    bool loaded = api_env["_LOADED"];
    return loaded;
}

sol::optional<sol::table> api_manager::try_find_api(
    const std::string& module_namespace,
    const std::string& module_name) const
{
    sol::optional<sol::table> table = api_env["Elona"][module_namespace];
    if (!table)
    {
        return sol::nullopt;
    }
    sol::optional<sol::table> result = (*table)[module_name];

    return result;
}

void api_manager::add_api(const std::string& module_namespace, sol::table& module_table)
{
    if (api_env["Elona"][module_namespace] == sol::lua_nil)
    {
        api_env["Elona"][module_namespace] = lua->get_state()->create_table();
    }

    sol::table api_table = api_env["Elona"][module_namespace].get<sol::table>();
    for (const auto& pair : module_table)
    {
        if (!pair.first.is<std::string>())
        {
            throw sol::error("Error loading mod " + module_namespace +
                             ": Mod API tables must only have string keys.");
        }
        api_table[pair.first.as<std::string>()] = pair.second;
    }
}

int api_manager::get_enum_value(const std::string& enum_name,
                                const std::string& variant) const
{
    sol::optional<sol::table> Enums = try_find_api("core", "Enums");
    if (!Enums)
        throw std::runtime_error("Enum table not loaded in API manager (" + enum_name + "." + variant + ")");

    sol::optional<sol::table> enum_table = (*Enums)[enum_name];

    if (!enum_table)
        throw std::runtime_error("No such enum \"" + enum_name + "\"");

    sol::optional<int> enum_value =  (*enum_table)[variant];

    if (!enum_value)
        throw std::runtime_error("No such enum value \"" + variant + "\" for enum \"" + enum_name + "\"");

    return *enum_value;
}

void api_manager::load_lua_support_libraries(lua_env& lua)
{
    // Don't load the support libraries again if they're already
    // loaded, because all the tables will be read-only.
    if (is_loaded())
    {
        return;
    }

    auto result = lua.get_state()->safe_script_file(
        filesystem::make_preferred_path_in_utf8(filesystem::dir::data() / "lua" / "init.lua"),
        api_env);

    if (!result.valid())
    {
        sol::error err = result;
        std::string what = err.what();
        ELONA_LOG(what);
        throw std::runtime_error("Failed initializing Lua support libraries.");
    }
}

void api_manager::lock()
{
    lua->get_state()->safe_script(R"(
Elona = Elona.core.ReadOnly.make_read_only(Elona)
)", api_env);
}

sol::table api_manager::bind(lua_env& lua)
{
    return lua.get_state()->create_table_with(
        "require",
        sol::overload(
            [&lua](const std::string& parent, const std::string& module) {
                sol::optional<sol::table> result = sol::nullopt;
                result = lua.get_api_manager().try_find_api(parent, module);
                return result;
            },

            // If no mod name is provided, assume it is "core".
            [&lua](const std::string& module) {
                sol::optional<sol::table> result = sol::nullopt;
                result = lua.get_api_manager().try_find_api("core", module);
                return result;
            }));
}

void api_manager::set_on(lua_env& lua)
{
    lua.get_state()->set("Elona", bind(lua));
}

sol::table api_manager::get_master_api_table()
{
    return api_env["Elona"];
}

sol::table api_manager::get_api_table()
{
    return api_env["Elona"]["core"];
}

} // namespace lua
} // namespace elona
