#pragma once



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

} // namespace elona
