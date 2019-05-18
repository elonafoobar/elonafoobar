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

struct ConfigMenuHistory
{
    int cs;
    int submenu;
};

void set_option()
{
    int submenu = 0;
    cs = 0;
    std::stack<ConfigMenuHistory> history;

    const auto config_screen = create_config_screen();

    while (true)
    {
        auto& menu_def = config_screen.at(submenu);
        const auto result = menu_def->query();

        if (result)
        {
            if (result->go_back)
            {
                {
                    const auto& prev = history.top();
                    cs = prev.cs;
                    submenu = prev.submenu;
                }
                history.pop();
            }
            // Don't push history if the submenu index returned is the same
            // (user viewed and exited the help text of an option)
            else if (result->submenu != submenu)
            {
                history.push({cs, submenu});
                cs = 0;
                submenu = result->submenu;
            }
        }
        else
        {
            break;
        }
    }
}

} // namespace elona
