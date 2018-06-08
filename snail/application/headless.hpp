#pragma once

#include "../scene.hpp"
#include "../effect.hpp"


namespace elona
{
namespace snail
{

class application final
{
public:
    size_t frame() const noexcept
    {
        return 1;
    }


    int width() const noexcept
    {
        return 1;
    }


    int height() const noexcept
    {
        return 1;
    }

    const std::string& title() const noexcept
    {
        return _title;
    }


    void set_title(const std::string& title);


    ~application() = default;

    static application& instance();


    void initialize(const std::string& title);

    void quit();

    // NOTE: Do not depend on the order of finalization.
    void register_finalizer(std::function<void()> finalizer);


    renderer& get_renderer()
    {
        return *_renderer;
    }


    void proc_event();


private:
    application() = default;
    std::unique_ptr<renderer> _renderer;
    bool _will_quit = false;
    const std::string _title = "";

    void main_loop();
};

}
}
