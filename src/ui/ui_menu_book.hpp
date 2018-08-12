#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class ui_menu_book : public ui_menu<dummy_result>
{
public:
    ui_menu_book(int book_id)
        : _book_id(book_id)
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<ui_menu_book::result_type> on_key(const std::string& key);

private:
    int _book_id;
};

} // namespace ui
} // namespace elona
