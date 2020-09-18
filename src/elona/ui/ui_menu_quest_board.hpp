#pragma once
#include "ui_menu.hpp"

namespace elona
{

struct Quest;



namespace ui
{

class UIMenuQuestBoard : public UIMenu<int>
{
public:
    UIMenuQuestBoard()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuQuestBoard::ResultType> on_key(
        const std::string& key);

private:
    void _draw_background();
    void _draw_window();
    void _draw_key(int);
    void _draw_keys();
    void _draw_list_entry_title(int, const std::string&);
    void _draw_list_entry_date(const std::string&);
    void _draw_list_entry_giver_name(int);
    void _draw_list_entry_difficulty(int, int);
    void _draw_list_entry_desc();
    void _draw_list_entry(int, int);
    void _draw_list_entries();
};

} // namespace ui
} // namespace elona
