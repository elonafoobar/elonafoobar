#include "../../snail/application.hpp"
#include "../audio.hpp"
#include "../draw.hpp"
#include "../elona.hpp"
#include "../i18n.hpp"
#include "../input.hpp"
#include "../macro.hpp"
#include "../menu.hpp"
#include "../network.hpp"
#include "../ui/ui_menu_config.hpp"
#include "../variables.hpp"
#include "config_menu.hpp"
#include "create_config_screen.hpp"


namespace elona
{

void set_option()
{
    int submenu = 0;
    cs = 0;

    const auto ConfigScreen = create_config_screen();

    while (true)
    {
        auto& menu_def = ConfigScreen[submenu];
        auto result = menu_def->query(submenu);

        if (result)
        {
            submenu = *result;
        }
        else
        {
            break;
        }
    }
}

} // namespace elona
