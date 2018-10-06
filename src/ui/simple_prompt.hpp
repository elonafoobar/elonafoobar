#pragma once
#include <string>
#include "../audio.hpp"
#include "../input.hpp"
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
        _width = 100;
        _height = 100;
        _font_size = 13 + sizefix - en * 2;

        std::string line;
        std::istringstream ss(_message);
        while (std::getline(ss, line))
        {
            _width = std::max(_width, strlen_u(line) * 8 + 40);
            _height += _font_size;
        }

        _x = promptx - (_width / 2);
        _y = prompty - (_height / 2);

        snd(26);

        gmode(6, 80);
        window(_x + 12, _y + 12, _width, _height, true); // Shadow
        gmode(2);

        window(_x + 8, _y + 8, _width, _height, false);

        font(_font_size);
        pos(_x + 40, _y + _font_size + 36);
        mes(_message);

        snail::Input::instance().clear_pressed_keys_and_modifiers();
        redraw();
    }

    virtual optional<T> update() = 0;


    std::string _message;

private:
    int _x{};
    int _y{};
    size_t _width{};
    size_t _height{};
    int _font_size{};
};

} // namespace ui
} // namespace elona
