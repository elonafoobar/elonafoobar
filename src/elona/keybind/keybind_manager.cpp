#include "keybind_manager.hpp"
#include "../../util/strutil.hpp"
#include "../filesystem.hpp"
#include "../variables.hpp"
#include "keybind.hpp"
#include "keybind_deserializer.hpp"
#include "keybind_serializer.hpp"



namespace
{

std::string key_autodig;
std::string key_east;
std::string key_look;
std::string key_north;
std::string key_northeast;
std::string key_northwest;
std::string key_quick;
std::string key_quickload;
std::string key_quicksave;
std::string key_rest;
std::string key_south;
std::string key_southeast;
std::string key_southwest;
std::string key_west;

} // namespace



namespace elona
{

KeybindManager& KeybindManager::instance()
{
    static KeybindManager the_instance;
    return the_instance;
}

KeybindManager::GroupedMapType KeybindManager::create_category_to_action_list()
{
    GroupedMapType result;

    for (const auto& pair : keybind::actions)
    {
        const auto& action_id = pair.first;
        const auto& action = pair.second;
        result.emplace(action.category, action_id);
    }

    return result;
}

void KeybindManager::save()
{
    auto path = filesystem::dir::exe() / u8"keybindings.hcl";
    std::ofstream file{path.native(), std::ios::binary};
    if (!file)
    {
        throw std::runtime_error{
            u8"Failed to open: "s +
            filepathutil::make_preferred_path_in_utf8(path)};
    }

    KeybindSerializer(*this).save(file);
}

void KeybindManager::load()
{
    clear();

    auto path = filesystem::dir::exe() / u8"keybindings.hcl";
    std::ifstream file{path.native(), std::ios::binary};

    if (file)
    {
        initialize_known_actions(keybind::actions);
        load_permanent_bindings(keybind::actions);
        KeybindDeserializer(*this).load(file);
    }
    else
    {
        load_default_bindings(keybind::actions);
        save();
    }
}

void KeybindManager::initialize_known_actions(const ActionMap& actions)
{
    for (const auto& pair : actions)
    {
        const auto& action_id = pair.first;

        register_binding(action_id);
    }
}

void KeybindManager::load_permanent_bindings(const ActionMap& actions)
{
    for (const auto& pair : actions)
    {
        const auto& action_id = pair.first;
        const auto& action = pair.second;

        auto& the_binding = binding(action_id);
        for (const auto& keybind : action.default_keybinds)
        {
            if (!keybind_is_bindable_key(keybind.main))
            {
                // Permanently bind keys that shouldn't be unbound (escape,
                // enter, and directional keys)
                the_binding.permanent = keybind;
            }
        }
    }
}

void KeybindManager::load_default_bindings(const ActionMap& actions)
{
    initialize_known_actions(actions);
    load_permanent_bindings(actions);

    for (const auto& pair : actions)
    {
        const auto& action_id = pair.first;
        const auto& action = pair.second;

        auto& the_binding = binding(action_id);
        for (const auto& keybind : action.default_keybinds)
        {
            if (keybind_is_bindable_key(keybind.main))
            {
                if (the_binding.primary.empty())
                {
                    the_binding.primary = keybind;
                }
                else if (the_binding.alternate.empty())
                {
                    the_binding.alternate = keybind;
                }
                else
                {
                    assert(false);
                }
            }
        }
    }
}

std::vector<std::string> KeybindManager::find_conflicts(
    const std::string& action_id,
    const Keybind& keybind)
{
    auto action_category = keybind::actions.at(action_id).category;
    std::vector<std::string> conflicts;

    auto can_conflict_with =
        keybind_conflicting_action_categories(action_category);

    for (const auto& pair : keybind::actions)
    {
        const auto& action_id = pair.first;
        const auto& action = pair.second;
        bool action_could_conflict =
            can_conflict_with.find(action.category) != can_conflict_with.end();

        if (action_could_conflict)
        {
            const auto& action_binding = binding(action_id);
            if (action_binding.primary == keybind
                || action_binding.alternate == keybind
                /* || (keybind.is_joystick() && keybind.joystick == keybind.main) */)
            {
                conflicts.emplace_back(action_id);
            }
        }
    }

    return conflicts;
}


static std::string _binding_name(
    KeybindManager& keybind_manager,
    const std::string& action_id)
{
    if (!keybind_manager.is_registered(action_id))
    {
        return "";
    }

    std::string result = "";
    auto& binding = keybind_manager.binding(action_id);
    if (!binding.primary.empty())
    {
        result = binding.primary.to_string();
    }
    if (result == "" && !binding.alternate.empty())
    {
        result = binding.primary.to_string();
    }
    if (result == "" && binding.joystick != snail::Key::none)
    {
        if (auto name_opt = keybind_key_name(binding.joystick))
        {
            result = *name_opt;
        }
    }

    strutil::try_remove_prefix(result, "Keypad ");
    return result;
}

// TODO: delete this.
void keybind_regenerate_key_names()
{
    auto& km = KeybindManager::instance();

    // clang-format off
    key_north     = _binding_name(km, "north");
    key_south     = _binding_name(km, "south");
    key_west      = _binding_name(km, "west");
    key_east      = _binding_name(km, "east");
    key_northwest = _binding_name(km, "northwest");
    key_northeast = _binding_name(km, "northeast");
    key_southwest = _binding_name(km, "southwest");
    key_southeast = _binding_name(km, "southeast");
    key_prev      = key_northwest;
    key_next      = key_northeast;
    key_wait      = _binding_name(km, "wait");
    key_cancel    = _binding_name(km, "cancel");
    key_pageup    = _binding_name(km, "next_page");
    key_pagedown  = _binding_name(km, "previous_page");
    key_mode      = _binding_name(km, "switch_mode");
    key_mode2     = _binding_name(km, "switch_mode_2");
    key_quick     = _binding_name(km, "quick_menu");
    key_zap       = _binding_name(km, "zap");
    key_inventory = _binding_name(km, "inventory");
    key_get       = _binding_name(km, "get");
    key_drop      = _binding_name(km, "drop");
    key_charainfo = _binding_name(km, "chara_info");
    key_enter     = _binding_name(km, "enter");
    key_eat       = _binding_name(km, "eat");
    key_wear      = _binding_name(km, "wear");
    key_cast      = _binding_name(km, "cast");
    key_drink     = _binding_name(km, "drink");
    key_read      = _binding_name(km, "read");
    key_fire      = _binding_name(km, "fire");
    key_godown    = _binding_name(km, "go_down");
    key_goup      = _binding_name(km, "go_up");
    key_save      = _binding_name(km, "save");
    key_search    = _binding_name(km, "search");
    key_interact  = _binding_name(km, "interact");
    key_identify  = _binding_name(km, "identify");
    key_skill     = _binding_name(km, "skill");
    key_close     = _binding_name(km, "close");
    key_rest      = _binding_name(km, "rest");
    key_target    = _binding_name(km, "target");
    key_dig       = _binding_name(km, "dig");
    key_use       = _binding_name(km, "use");
    key_bash      = _binding_name(km, "bash");
    key_open      = _binding_name(km, "open");
    key_dip       = _binding_name(km, "dip");
    key_pray      = _binding_name(km, "pray");
    key_offer     = _binding_name(km, "offer");
    key_journal   = _binding_name(km, "journal");
    key_material  = _binding_name(km, "material");
    key_trait     = _binding_name(km, "trait");
    key_look      = _binding_name(km, "look");
    key_give      = _binding_name(km, "give");
    key_throw     = _binding_name(km, "throw");
    key_ammo      = _binding_name(km, "ammo");
    key_autodig   = _binding_name(km, "autodig");
    key_quicksave = _binding_name(km, "quicksave");
    key_quickload = _binding_name(km, "quickload");
    key_help      = _binding_name(km, "help");
    key_msglog    = _binding_name(km, "message_log");
    // clang-format on
}

} // namespace elona
