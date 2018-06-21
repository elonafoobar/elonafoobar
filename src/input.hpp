#pragma once
#include "enums.hpp"


namespace elona
{

extern int TODO_show_prompt_val;


// val3 = 0 ?
// val3 = 1 normal
// val3 = 2 number
enum class show_prompt_type
{
    normal,
    cannot_cancel,
    with_number,
};

int show_prompt(
    int x,
    int y,
    int width,
    show_prompt_type type = show_prompt_type::normal,
    int initial_number = 0);


void input_number_dialog(int x, int y, int max_number);

bool input_text_dialog(
    int x,
    int y,
    int val2,
    bool is_cancelable = true,
    bool limit_length = true);

void key_check(key_wait_delay_t = key_wait_delay_t::always);
void wait_key_released();
void wait_key_pressed(bool only_enter_or_cancel = false);


} // namespace elona
