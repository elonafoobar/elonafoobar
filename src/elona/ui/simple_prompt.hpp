#pragma once
#include <string>
#include "../audio.hpp"
#include "../input.hpp"
#include "../ui.hpp"
#include "../variables.hpp"

namespace elona
{
namespace ui
{

template <typename T>
class SimplePrompt
{
public:
    SimplePrompt(std::string message)
        : _message(message)
    {
    }

    SimplePrompt()
        : _message("")
    {
    }

    SimplePrompt(int width, int height)
        : _message("")
        , _width(width)
        , _height(height)
    {
    }

    T query()
    {
        init();

        while (true)
        {
            if (auto it = update())
            {
                return *it;
            }
        }
    }

protected:
    virtual void init()
    {
        snd("core.pop2");

        _font_size = 13 + sizefix - en * 2;

        if (_width == 0 && _height == 0)
        {
            _width = 100;
            _height = 100;

            std::string line;
            std::istringstream ss(_message);
            while (std::getline(ss, line))
            {
                _width = std::max(_width, strlen_u(line) * 8 + 40);
                _height += _font_size;
            }
        }

        _x = promptx - (_width / 2);
        _y = prompty - (_height / 2);

        draw();

        snail::Input::instance().clear_pressed_keys_and_modifiers();
    }

    virtual void draw_window()
    {
        gmode(2, 80);
        window(_x + 12, _y + 12, _width, _height, true); // Shadow
        gmode(2);

        window(_x + 8, _y + 8, _width, _height, false);
    }

    virtual void draw()
    {
        draw_window();

        font(_font_size);
        mes(_x + 40, _y + _font_size + 36, _message);

        redraw();
    }

    virtual optional<T> update() = 0;


    std::string _message;
    int _x{};
    int _y{};
    size_t _width{};
    size_t _height{};
    int _font_size{};
};

} // namespace ui
} // namespace elona
