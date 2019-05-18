#pragma once
#include "ui_menu.hpp"
namespace elona
{
namespace ui
{
class UIMenuGameHelp : public UIMenu<DummyResult>
{
public:
    UIMenuGameHelp()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuGameHelp::ResultType> on_key(const std::string& key);

    void _draw_key_list();
    void _draw_regular_pages();
    void _draw_window();
    void _draw_navigation_menu();
    void _draw_background_vignette(int id, int type);

private:
    struct GameHelp
    {
        void load(const fs::path& filepath);


        const std::vector<std::string>& section_headings() const
        {
            return _section_headings;
        }


        const std::vector<std::string> get_section(size_t index) const
        {
            return _sections.at(index);
        }


    private:
        std::vector<std::vector<std::string>> _sections;
        std::vector<std::string> _section_headings;
    };

    GameHelp _help;
    bool _redraw;
};
} // namespace ui
} // namespace elona
