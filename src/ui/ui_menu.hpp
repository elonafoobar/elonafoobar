#pragma once
#include <string>
#include "../config.hpp"
#include "../input.hpp"
#include "../optional.hpp"
#include "../ui.hpp"
#include "../variables.hpp"

namespace elona
{
namespace ui
{

struct dummy_result
{
};

template <typename T>
class ui_menu
{
public:
    struct result
    {
        result(bool canceled, optional<T> value)
            : canceled(canceled)
            , value(value)
        {
        }

        static result finish(optional<T> res = none)
        {
            return {false, res};
        }

        static result cancel()
        {
            return {true, none};
        }

        bool canceled;
        optional<T> value;
    };

protected:
    using result_type = ui_menu<T>::result;

protected:
    virtual bool init() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual optional<result_type> on_key(const std::string& key) = 0;

    void set_reupdate()
    {
        _reupdate = true;
    }

public:
    ui_menu::result show()
    {
        if (!init())
        {
            return result_type::cancel();
        }

        update();
        _reupdate = false;

        while (true)
        {
            draw();

            _redraw();
            _update_input();

            if (auto res = on_key(elona::key))
            {
                return *res;
            }

            if (_reupdate)
            {
                update();
                _reupdate = false;
            }
        }
    }

private:
    void _redraw()
    {
        redraw();
        await(config::instance().wait1);
    }

    void _update_input()
    {
        key_check();
        cursor_check();
    }

    bool _reupdate = false;
};

} // namespace ui
} // namespace elona
