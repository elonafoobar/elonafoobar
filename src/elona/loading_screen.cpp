#include "loading_screen.hpp"
#include "../snail/application.hpp"
#include "filesystem.hpp"
#include "variables.hpp"



namespace
{

constexpr snail::Color bg_color{160, 145, 128};
constexpr snail::Color fg_color{71, 64, 55};
constexpr int frame_width = 480;
constexpr int frame_height = 360;
constexpr int progress_bar_width = 340;
constexpr int progress_bar_height = 12;


void _draw_background()
{
    // fill
    boxf(0, 0, windoww, windowh, bg_color);

    // frame (2 px)
    boxl(
        (windoww - frame_width) / 2,
        (windowh - frame_height) / 2,
        frame_width - 1,
        frame_height - 1,
        fg_color);
    boxl(
        (windoww - frame_width) / 2 - 1,
        (windowh - frame_height) / 2 - 1,
        frame_width - 1 + 2,
        frame_height - 1 + 2,
        fg_color);

    // Now Loading...
    font(36);
    auto& renderer = snail::Application::instance().get_renderer();
    renderer.set_text_alignment(snail::Renderer::TextAlignment::center);
    renderer.render_text(
        u8"Now Loading...",
        windoww / 2,
        (windowh - frame_height) / 2 + 70,
        fg_color);
    renderer.set_text_alignment(snail::Renderer::TextAlignment::left);
}



void _draw_progress_bar(int progress, const std::string& message)
{
    // frame
    boxl(
        (windoww - frame_width) / 2 + (frame_width - progress_bar_width) / 2,
        (windowh - frame_height) / 2 + 180,
        progress_bar_width - 1,
        progress_bar_height - 1,
        fg_color);

    // bar
    boxf(
        (windoww - frame_width) / 2 + (frame_width - progress_bar_width) / 2 +
            2,
        (windowh - frame_height) / 2 + 180 + 2,
        (progress_bar_width - 4) * progress / 100,
        progress_bar_height - 4,
        fg_color);

    // message
    font(20);
    auto& renderer = snail::Application::instance().get_renderer();
    renderer.set_text_alignment(snail::Renderer::TextAlignment::center);
    renderer.set_text_baseline(snail::Renderer::TextBaseline::bottom);
    renderer.render_text(
        message, windoww / 2, (windowh - frame_height) / 2 + 180 - 4, fg_color);

    // percentage
    font(16);
    renderer.set_text_baseline(snail::Renderer::TextBaseline::top);
    renderer.render_text(
        std::to_string(progress) + "%",
        windoww / 2,
        (windowh - frame_height) / 2 + 180 + progress_bar_height + 4,
        fg_color);
    renderer.set_text_alignment(snail::Renderer::TextAlignment::left);
}



void _draw_rolling_putit(int frame, snail::Image& cute_creature)
{
    const std::vector<int> animation_frames{13, 12, 11, 10, 9, 8,  7,  6, 5,
                                            4,  3,  2,  1,  0, 1,  2,  3, 4,
                                            5,  6,  7,  8,  9, 10, 11, 12};

    const std::vector<int> x_offset{
        289,
        289,
        280,
        264,
        238,
        208,
        160,
        125,
        64,
        28,
        2,
        0,
        0,
        0,
    };
    const auto animation_frame =
        animation_frames[(frame / 8) % animation_frames.size()];
    const auto dst_x = (windoww - 374) / 2 + x_offset[animation_frame];
    const auto dst_y = (windowh + frame_height) / 2 - 80 + 2;

    auto& renderer = snail::Application::instance().get_renderer();
    renderer.render_image(
        cute_creature, animation_frame * 85, 0, 85, 80, dst_x, dst_y);
}



void _draw(int frame, int progress, snail::Image& cute_creature)
{
    _draw_background();
    _draw_progress_bar(progress % 101, "Load mod core");
    _draw_rolling_putit(frame, cute_creature);
}

} // namespace



namespace elona
{

void show_loading_screen()
{
    const auto path = filesystem::dirs::graphic() / "rolling_putit.png";
    snail::Image cute_creature(path);

    int frame = 0;
    for (int progress = 0; progress <= 100; ++progress)
    {
        _draw(frame, progress, cute_creature);
        redraw();
        await(30);
        ++frame;
    }
}

} // namespace elona
