#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class ui_menu_feats : public ui_menu<dummy_result>
{
public:
    ui_menu_feats(bool decorate)
        : _decorate(decorate)
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<ui_menu_feats::result_type> on_key(const std::string& key);

private:
    bool _decorate;
    int _featrq = 0;
};

} // namespace ui
} // namespace elona
