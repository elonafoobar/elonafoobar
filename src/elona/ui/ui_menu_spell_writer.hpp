#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class UIMenuSpellWriter : public UIMenu<DummyResult>
{
public:
    UIMenuSpellWriter()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuSpellWriter::ResultType> on_key(
        const std::string& key);

private:
    void _draw_window();
    void _draw_key(int);
    void _draw_keys();
    void _draw_list_entry_image(int);
    void _draw_list_entry_name(int, int);
    void _draw_list_entry_reserve_status(int, int);
    void _draw_list_entry(int, int);
    void _draw_list_entries();
};

} // namespace ui
} // namespace elona
