#pragma once

#include "../lib/noncopyable.hpp"
#include "renderer.hpp"


namespace elona
{
namespace snail
{



class node : public lib::noncopyable
{
public:
    int frame() const noexcept
    {
        return _frame;
    }


    node() = default;
    virtual ~node() override = default;

    virtual void update() = 0;
    virtual void render(renderer& renderer) = 0;


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
