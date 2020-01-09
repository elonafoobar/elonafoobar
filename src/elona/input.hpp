#pragma once
#include <string>
#include "../snail/input.hpp"
#include "enums.hpp"
#include "optional.hpp"


namespace elona
{

enum class ActionCategory;
class InputContext;

enum class PromptType
{
    normal,
    cannot_cancel,
    with_number,
};



void input_number_dialog(int x, int y, int max_number, int initial_number = 0);

bool input_text_dialog(
    int x,
    int y,
    int val2,
    bool is_cancelable = true,
    bool limit_length = true);

StickKey stick(StickKey allow_repeat_keys = StickKey::none);

std::string key_check(KeyWaitDelay = KeyWaitDelay::always);
std::string key_check_pc_turn(KeyWaitDelay = KeyWaitDelay::always);
std::string cursor_check_ex();
std::string cursor_check_ex(int& index);
std::string get_selected_item(int& p_);
optional<int> get_shortcut(const std::string& action);
bool is_modifier_pressed(snail::ModKey modifier);
void wait_key_released();
void wait_key_pressed(bool only_enter_or_cancel = false);



enum class HaltInput
{
    // Halt all input regardless of configuration.
    force,
    // Halt all input if `core.animation.alert_wait` is non-zero.
    alert,
};

void input_halt_input(HaltInput mode);



/**
 * The result of yes_no() function. There are 3 kinds of result, cancled,
 * yes, and no.
 */
struct YesNo
{
private:
    enum class Type
    {
        canceled,
        yes,
        no,
    };


public:
    // Exporting these namese here allows you to omit "Type::" qualifier. A
    // plain enum (not enum class) does not need qualifier, but can be converted
    // from/to its underlying type.

    /// The prompt was canceled by user.
    static constexpr Type canceled = Type::canceled;
    /// User chose "yes".
    static constexpr Type yes = Type::yes;
    /// User chose "no".
    static constexpr Type no = Type::no;


    constexpr YesNo(Type type)
        : _type(type)
    {
    }


    /// @return True if "yes", otherwise false.
    explicit operator bool() const
    {
        return _type == Type::yes;
    }


    bool operator==(YesNo other) const
    {
        return _type == other._type;
    }


    bool operator!=(YesNo other) const
    {
        return !(*this == other);
    }


    bool operator==(Type other) const
    {
        return _type == other;
    }


    bool operator!=(Type other) const
    {
        return !(*this == other);
    }


private:
    Type _type;
};


/**
 * Shows a simple prompt to query "yes" or "no".
 */
YesNo yes_no();

} // namespace elona
