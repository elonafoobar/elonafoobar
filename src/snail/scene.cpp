#include "scene.hpp"
#include <cassert>

namespace elona
{
namespace snail
{


scene_base::scene_base(std::shared_ptr<scene_base> parent)
    : _parent(parent)
{
}



std::shared_ptr<scene_base> scene_manager::current_scene()
{
    assert(_scene_stack.size() >= 1);
    return _scene_stack.top();
}



void scene_manager::push(std::shared_ptr<scene_base> new_scene)
{
    _scene_stack.push(new_scene);
}



void scene_manager::pop()
{
    assert(_scene_stack.size() >= 1);
    _scene_stack.pop();
}



void scene_manager::pop_all()
{
    while (!_scene_stack.empty())
    {
        _scene_stack.pop();
    }
}



void scene_manager::replace(std::shared_ptr<scene_base> new_scene)
{
    pop();
    push(new_scene);
}


} // namespace snail
} // namespace elona
