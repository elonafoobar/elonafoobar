#pragma once
#include "enums.hpp"


namespace elona
{

extern int TODO_show_prompt_val;

enum class ActionCategory;
class InputContext;

enum class PromptType
{
    normal,
    cannot_cancel,
    with_number,
};

int show_prompt(
    int x,
    int y,
    int width,
    PromptType type = PromptType::normal,
    int initial_number = 0);


void input_number_dialog(int x, int y, int max_number, int initial_number = 0);

bool input_text_dialog(
    int x,
    int y,
    int val2,
    bool is_cancelable = true,
    bool limit_length = true);

StickKey stick(StickKey allow_repeat_keys = StickKey::none);

void key_check(KeyWaitDelay = KeyWaitDelay::always);
void wait_key_released();
void wait_key_pressed(bool only_enter_or_cancel = false);


} // namespace elona
