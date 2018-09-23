#include "../audio.hpp"
#include "../draw.hpp"
#include "../elona.hpp"
#include "../i18n.hpp"
#include "../input.hpp"
#include "../macro.hpp"
#include "../menu.hpp"
#include "../network.hpp"
#include "../snail/application.hpp"
#include "../ui.hpp"
#include "../ui/ui_menu_config.hpp"
#include "../variables.hpp"
#include "config.hpp"
#include "config_menu.hpp"
#include "create_config_screen.hpp"

#include <sstream>

using namespace elona;


namespace
{


} // namespace



namespace elona
{

static void _show_config_item_desc(const std::string& desc)
{
    size_t width = 100;
    size_t height = 100;
    int font_size = 13 + sizefix - en * 2;
    std::string line;
    std::istringstream ss(desc);

    while (std::getline(ss, line))
    {
        width = std::max(width, strlen_u(line) * 8 + 40);
        height += font_size;
    }

    int x = promptx - (width / 2);
    int y = prompty - (height / 2);

    snd(26);

    while (true)
    {
        window(x + 8, y + 8, width, height, false);

        font(font_size);
        pos(x + 40, y + font_size + 36);
        mes(desc);

        redraw();
        await(Config::instance().wait1);
        key_check();

        if (key != ""s)
        {
            key = ""s;
            break;
        }
    }
}

void set_option()
{
    int submenu = 0;
    cs = 0;

    const auto ConfigScreen = create_config_screen();

    while (true)
    {
        auto& menu_def = ConfigScreen[submenu];
        auto result = ui::UIMenuConfig(*menu_def, submenu).show();

        if (result.value)
        {
            submenu = *result.value;
        }
        else
        {
            break;
        }
    }
}



} // namespace elona
