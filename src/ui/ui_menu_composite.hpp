#pragma once
#include <vector>
#include "../audio.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"
#include "ui_menu.hpp"


namespace elona
{
namespace ui
{

template <typename T>
class ui_menu_composite : public ui_menu<T>
{
protected:
    using menu_type = ui_menu<T>;

    struct menu_info
    {
        menu_info(
            std::unique_ptr<menu_type> _menu,
            int _image,
            int _sound,
            std::string _text)
            : image(_image)
            , sound(_sound)
            , text(_text)
        {
            menu = std::move(_menu);
        }

        std::unique_ptr<menu_type> menu;
        int image;
        int sound;
        std::string text;
    };

    using menu_list = std::vector<menu_info>;

public:
    ui_menu_composite(size_t selected)
        : _selected(selected)
    {
        _menu_switched = true;
    }

protected:
    void push_back(
        std::unique_ptr<menu_type> menu,
        int image,
        int sound,
        const i18n_key& locale_key)
    {
        std::string text = i18n::s.get(locale_key);
        _menus.emplace_back(std::move(menu), image, sound, text);
    }

    virtual void add_menus() = 0;

    virtual bool init()
    {
        add_menus();

        if (_menus.size() == 0)
        {
            return false;
        }

        _selected = std::min(std::max(_selected, (size_t)0), _menus.size());

        // TODO: move to ui_menu
        snd(_menus[_selected].sound);

        return true;
    }

    virtual void update()
    {
        if (_menu_switched)
        {
            screenupdate = -1;
            update_screen();
            _menus[_selected].menu->init();
            _menu_switched = false;
        }

        _menus[_selected].menu->update();

        _draw_menu_icons();
    }

    virtual void draw()
    {
        _menus[_selected].menu->draw();
    }

    virtual optional<typename ui_menu<T>::result> on_key(const std::string& key)
    {
        if (auto result = _menus[_selected].menu->on_key(key))
        {
            return result;
        }

        if (key == key_next || key == key_prev)
        {
            size_t prev_menu = _selected;
            if (key == key_next)
            {
                if (_selected >= _menus.size() - 1)
                {
                    _selected = 0;
                }
                else
                {
                    _selected++;
                }
            }
            if (key == key_prev)
            {
                if (_selected <= 0)
                {
                    _selected = _menus.size() - 1;
                }
                else
                {
                    _selected--;
                }
            }
            if (prev_menu != _selected)
            {
                snd(_menus[_selected].sound);
                _menu_switched = true;
                ui_menu<T>::set_reupdate();
            }
        }

        if (_menus[_selected].menu->_reupdate)
        {
            ui_menu<T>::set_reupdate();
            _menus[_selected].menu->_reupdate = false;
        }

        return none;
    }

private:
    void _draw_menu_icon_background(int x, int y, int width)
    {
        font(12 + sizefix - en * 2);
        window2(x, y, width, 22, 5, 5);
        pos(x - 28, y - 8);
        gcopy(3, 64, 288, 50, 32);
    }

    void _draw_single_menu_item(
        size_t menu_index,
        const menu_info& menu,
        int x,
        int y)
    {
        pos(x + menu_index * 50 + 20, y - 24);
        gcopy(3, 288 + menu.image * 48, 48, 48, 48);

        if (_selected == menu_index)
        {
            gmode(5, 70);
            pos(x + menu_index * 50 + 20, y - 24);
            gcopy(3, 288 + menu.image * 48, 48, 48, 48);
            gmode(2);
        }

        bmes(
            menu.text,
            x + menu_index * 50 + 46 - strlen_u(menu.text) * 3,
            y + 7,
            _selected == menu_index ? snail::color{255, 255, 255}
                                    : snail::color{165, 165, 165});
    }

    void _draw_menu_icons()
    {
        int x = windoww - (50 * _menus.size() + 60);
        int y = 34;
        int width = 50 * _menus.size() + 40;

        _draw_menu_icon_background(x, y, width);

        size_t menu_index = 0;
        for (const auto& menu : _menus)
        {
            _draw_single_menu_item(menu_index, menu, x, y);

            menu_index++;
        }

        bmes(
            ""s + key_prev + u8","s + key_next + u8",Tab ["s
                + i18n::s.get("core.locale.ui.menu.change") + u8"]"s,
            x + width - 150,
            y + 28);
    }

private:
    menu_list _menus;
    size_t _selected;
    bool _menu_switched;
};

} // namespace ui
} // namespace elona
