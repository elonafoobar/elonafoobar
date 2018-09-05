#pragma once

#include "node.hpp"


namespace elona
{
namespace snail
{


class EffectBase : public Node
{
public:
    bool alive() const noexcept
    {
        return _alive;
    }


    virtual bool blocks_user_input() const noexcept = 0;


    void destroy() noexcept
    {
        _alive = false;
    }


private:
    bool _alive = true;
};



} // namespace snail
} // namespace elona
