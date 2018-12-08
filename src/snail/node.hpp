#pragma once

#include "../util/noncopyable.hpp"
#include "renderer.hpp"


namespace elona
{
namespace snail
{



class Node : public lib::noncopyable
{
public:
    int frame() const noexcept
    {
        return _frame;
    }


    Node() = default;
    virtual ~Node() override = default;

    virtual void update() = 0;
    virtual void render(Renderer& renderer) = 0;


    // internal
    void _increase_frame()
    {
        ++_frame;
    }


private:
    int _frame = 0;
};



} // namespace snail
} // namespace elona
