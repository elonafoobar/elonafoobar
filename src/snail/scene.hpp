#pragma once

#include <stack>
#include "../util/noncopyable.hpp"
#include "node.hpp"


namespace elona
{
namespace snail
{



class SceneBase : public Node
{
public:
    std::shared_ptr<SceneBase> parent() noexcept
    {
        return _parent;
    }


    explicit SceneBase(std::shared_ptr<SceneBase> parent = nullptr);
    virtual ~SceneBase() = default;


private:
    std::shared_ptr<SceneBase> _parent;
};



class SceneManager final : public lib::noncopyable
{
public:
    std::shared_ptr<SceneBase> current_scene();


    SceneManager() = default;
    virtual ~SceneManager() override = default;


    void push(std::shared_ptr<SceneBase> new_scene);
    void pop();
    void pop_all();
    void replace(std::shared_ptr<SceneBase> new_scene);


private:
    std::stack<std::shared_ptr<SceneBase>> _scene_stack;
};



} // namespace snail
} // namespace elona
