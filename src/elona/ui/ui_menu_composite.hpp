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
class UIMenuComposite : public UIMenu<T>
{
protected:
    using MenuType = UIMenu<T>;

    struct MenuInfo
    {
        MenuInfo(std::unique_ptr<MenuType> _menu, int _image, std::string _text)
            : image(_image)
            , text(_text)
        {
            menu = std::move(_menu);
        }

        std::unique_ptr<MenuType> menu;
        int image;
        std::string text;
    };

    using MenuList = std::vector<MenuInfo>;

public:
    UIMenuComposite(size_t selected)
        : _selected(selected)
    {
        _menu_switched = true;
    }

    size_t selected_index() const noexcept
    {
        return _selected;
    }

protected:
    void push_back(
        std::unique_ptr<MenuType> menu,
        int image,
        const I18NKey& locale_key)
    {
        std::string text = i18n::s.get(locale_key);
        _menus.emplace_back(std::move(menu), image, text);
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

    virtual optional<typename UIMenu<T>::Result> on_key(
        const std::string& action)
    {
        // Update index of selected list item in the contained menu, otherwise
        // it will never be set.
        _menus[_selected].menu->_index = UIMenu<T>::_index;

        if (action == "next_menu" || action == "previous_menu")
        {
            size_t prev_menu = _selected;
            if (action == "next_menu")
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
            if (action == "previous_menu")
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
                _menu_switched = true;
                UIMenu<T>::set_reupdate();
            }
        }
        else if (auto result = _menus[_selected].menu->on_key(action))
        {
            return result;
        }

        if (_menus[_selected].menu->_reupdate)
        {
            UIMenu<T>::set_reupdate();
            _menus[_selected].menu->_reupdate = false;
        }

        if (_menus[_selected].menu->_reinit)
        {
            // trigger init() to be called in update().
            _menu_switched = true;
            UIMenu<T>::set_reupdate();
            _menus[_selected].menu->_reinit = false;
        }

        return none;
    }

private:
    void _draw_menu_icon_background(int x, int y, int width)
    {
        font(12 + sizefix - en * 2);
        window2(x, y, width, 22, 5, 5);
        gcopy(3, 64, 288, 50, 32, x - 28, y - 8);
    }

    void _draw_single_menu_item(
        size_t menu_index,
        const MenuInfo& menu,
        int x,
        int y)
    {
        gcopy(
            3,
            288 + menu.image * 48,
            48,
            48,
            48,
            x + menu_index * 50 + 20,
            y - 24);

        if (_selected == menu_index)
        {
            gmode(5, 70);
            gcopy(
                3,
                288 + menu.image * 48,
                48,
                48,
                48,
                x + menu_index * 50 + 20,
                y - 24);
            gmode(2);
        }

        bmes(
            menu.text,
            x + menu_index * 50 + 46 - strlen_u(menu.text) * 3,
            y + 7,
            _selected == menu_index ? snail::Color{255, 255, 255}
                                    : snail::Color{165, 165, 165});
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
            ""s + key_prev + u8","s + key_next + u8",Tab,Ctrl+Tab ["s +
                i18n::s.get("core.locale.ui.menu.change") + u8"]"s,
            x + width - 215,
            y + 28);
    }

private:
    MenuList _menus;
    size_t _selected;
    bool _menu_switched;
};

} // namespace ui
} // namespace elona
