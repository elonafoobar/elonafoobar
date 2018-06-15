#pragma once

#include <stack>
#include "../lib/noncopyable.hpp"
#include "node.hpp"


namespace elona
{
namespace snail
{



class scene_base : public node
{
public:
    std::shared_ptr<scene_base> parent() noexcept
    {
        return _parent;
    }


    explicit scene_base(std::shared_ptr<scene_base> parent = nullptr);
    virtual ~scene_base() = default;


private:
    std::shared_ptr<scene_base> _parent;
};



class scene_manager final : public lib::noncopyable
{
public:
    std::shared_ptr<scene_base> current_scene();


    scene_manager() = default;
    virtual ~scene_manager() override = default;


    void push(std::shared_ptr<scene_base> new_scene);
    void pop();
    void pop_all();
    void replace(std::shared_ptr<scene_base> new_scene);


private:
    std::stack<std::shared_ptr<scene_base>> _scene_stack;
};



} // namespace snail
} // namespace elona
