#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class ui_menu_god : public ui_menu<int>
{
public:
    ui_menu_god(int god_id, bool already_believing)
        : _god_id(god_id)
        , _already_believing(already_believing)
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<ui_menu_god::result_type> on_key(const std::string& key);

private:
    int _god_id;
    bool _already_believing;
};

} // namespace ui
} // namespace elona
