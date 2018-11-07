#include "network.hpp"
// #include "audio.hpp"
// #include "config/config.hpp"
// #include "elona.hpp"
// #include "i18n.hpp"
#include "input.hpp"
// #include "input_prompt.hpp"
// #include "macro.hpp"
#include "message.hpp"
// #include "random.hpp"
// #include "ui.hpp"
#include "variables.hpp"



namespace elona
{

void show_chat_dialog()
{
    inputlog = "";
    input_text_dialog(80, windowh - inf_verh - 70, 38);
    if (inputlog == ""s)
    {
        return;
    }
    if (jp)
    {
        inputlog = u8"「"s + inputlog + u8"」"s;
    }
    else
    {
        inputlog = u8"\""s + inputlog + u8"\""s;
    }
    txt(inputlog);
}

} // namespace elona
