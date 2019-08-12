#pragma once

#include "ui_menu.hpp"



namespace elona
{
namespace ui
{

class UIMenuVotingBox : public UIMenu<DummyResult>
{
public:
    UIMenuVotingBox()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuAdventurers::ResultType> on_key(
        const std::string& key);

private:
    bool _can_vote_now;
};

} // namespace ui
} // namespace elona
