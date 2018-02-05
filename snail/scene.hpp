#pragma once

#include <stack>
#include "../lib/noncopyable.hpp"
#include "node.hpp"


namespace snail
{
class Scene : public Node
{
public:
    std::shared_ptr<Scene> parent() noexcept
    {
        return _parent;
    }


    explicit Scene(std::shared_ptr<Scene> parent = nullptr);
    virtual ~Scene() = default;


private:
    std::shared_ptr<Scene> _parent;
};



class SceneManager final : public lib::noncopyable
{
public:
    std::shared_ptr<Scene> current_scene();


    SceneManager() = default;
    virtual ~SceneManager() override = default;


    void push(std::shared_ptr<Scene> new_scene);
    void pop();
    void pop_all();
    void replace(std::shared_ptr<Scene> new_scene);


private:
    std::stack<std::shared_ptr<Scene>> _scene_stack;
};


} // namespace snail
