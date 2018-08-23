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

template <typename T>
class ui_menu_composite;

struct dummy_result
{
};

template <typename T>
class ui_menu
{
    friend class ui_menu_composite<T>;

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

public:
    virtual bool init() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual optional<result_type> on_key(const std::string& key) = 0;

protected:
    /**
     * Runs update() after the next cycle.
     */
    void set_reupdate()
    {
        _reupdate = true;
    }

    /**
     * Reinitializes this menu in-place on the next cycle by calling init(), for
     * example after opening another menu inside of it that modifies "list".
     */
    void set_reinit()
    {
        _reinit = true;
    }

public:
    ui_menu::result show()
    {
        while (true)
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

                if (_reinit)
                {
                    _reinit = false;

                    // Break out of this loop and run init() again at the top.
                    break;
                }
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
    bool _reinit = false;
};

} // namespace ui
} // namespace elona
