#pragma once

#include "node.hpp"


namespace elona::snail
{


class effect_base : public node
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



} // namespace elona::snail
