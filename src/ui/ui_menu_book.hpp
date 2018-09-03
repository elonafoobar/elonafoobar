#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class UIMenuBook : public UIMenu<DummyResult>
{
public:
    UIMenuBook(int book_id)
        : _book_id(book_id)
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuBook::result_type> on_key(const std::string& key);

private:
    int _book_id;
};

} // namespace ui
} // namespace elona
