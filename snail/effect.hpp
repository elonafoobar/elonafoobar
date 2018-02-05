#pragma once

#include "node.hpp"


namespace snail
{
class Effect : public Node
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
