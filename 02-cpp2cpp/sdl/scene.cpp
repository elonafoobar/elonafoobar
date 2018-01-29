#include "scene.hpp"
#include <cassert>

using namespace snail;


Scene::Scene(std::shared_ptr<Scene> parent)
    : _parent(parent)
{
}



std::shared_ptr<Scene> SceneManager::current_scene()
{
    assert(_scene_stack.size() >= 1);
    return _scene_stack.top();
}



void SceneManager::push(std::shared_ptr<Scene> new_scene)
{
    _scene_stack.push(new_scene);
}



void SceneManager::pop()
{
    assert(_scene_stack.size() >= 1);
    _scene_stack.pop();
}



void SceneManager::pop_all()
{
    while (!_scene_stack.empty())
    {
        _scene_stack.pop();
    }
}



void SceneManager::replace(std::shared_ptr<Scene> new_scene)
{
    pop();
    push(new_scene);
}
