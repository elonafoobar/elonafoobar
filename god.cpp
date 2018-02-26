#include "god.hpp"
#include <iostream>
#include "elona.hpp"
#include "i18n.hpp"
#include "variables.hpp"


namespace elona
{


void txtgod(const god_id_t& id, int type)
{
    if (std::empty(id))
        return;

    std::string message;
    switch (type)
    {
    case 12: message = i18n::_(u8"god", id, u8"random"); break;
    case 9: message = i18n::_(u8"god", id, u8"kill"); break;
    case 10: message = i18n::_(u8"god", id, u8"night"); break;
    case 11: message = i18n::_(u8"god", id, u8"welcome"); break;
    case 5: message = i18n::_(u8"god", id, u8"believe"); break;
    case 1: message = i18n::_(u8"god", id, u8"betray"); break;
    case 2: message = i18n::_(u8"god", id, u8"take_over"); break;
    case 3: message = i18n::_(u8"god", id, u8"fail_to_take_over"); break;
    case 4: message = i18n::_(u8"god", id, u8"offer"); break;
    case 6: message = i18n::_(u8"god", id, u8"receive_gift"); break;
    case 7: message = i18n::_(u8"god", id, u8"ready_to_receive_gift"); break;
    case 8: message = i18n::_(u8"god", id, u8"ready_to_receive_gift2"); break;
    default: assert(0);
    }

    txtef(5);
    if (type == 6)
    {
        txtmore();
    }
    txt(message);
}


god_db::god_db()
{
}



} // namespace elona
