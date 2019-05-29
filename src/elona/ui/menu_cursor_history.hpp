#pragma once

#include <stack>
#include <unordered_map>
#include "../optional.hpp"



namespace elona
{
namespace ui
{

/**
 * Holds a page and a position in the current page. It must point to somewhere,
 * and does not allow invalid position.
 */
struct MenuCursor
{
    using Page = int;
    using Position = int;



    MenuCursor(Page page, Position position)
        : _page(page)
        , _pos(position)
    {
    }



    explicit MenuCursor(Position position)
        : _page(0)
        , _pos(position)
    {
    }



    MenuCursor()
        : _page(0)
        , _pos(0)
    {
    }



    MenuCursor(const MenuCursor&) = default;
    MenuCursor(MenuCursor&&) = default;
    MenuCursor& operator=(const MenuCursor&) = default;
    MenuCursor& operator=(MenuCursor&&) = default;



    // 0-indexed, but displayed as 1-indexed to players.
    Page page() const noexcept
    {
        return _page;
    }



    // 0-indexed, but displayed as 1-indexed to players.
    Position position() const noexcept
    {
        return _pos;
    }



private:
    Page _page;
    Position _pos;
};



/*
 * Menu lifecycle and cursor history.
 *
 * init();
 * cursor = MenuCursorHistory::instance().restore("key");
 * while (true)
 * {
 *     cursor = player's input
 *
 *     MenuCursorHistory::instance().push(cursor);
 *     open_submenu();
 *     cursor = MenuCursorHistory::instance().pop();
 * }
 *
 * MenuCursorHistory::instance().save("key", cursor);
 * close();
 */
class MenuCursorHistory
{
public:
    using Key = std::string;



    static MenuCursorHistory& instance()
    {
        static MenuCursorHistory instance;
        return instance;
    }



    /// Push the current menu cursor. Call it before opening a submenu.
    void push(const MenuCursor& cursor)
    {
        _stack.push(cursor);
    }



    /// Pop the top of the stack and return it. Call it after a submenu is
    /// closed.
    /// If the current window is in the top level and has no parent window, this
    /// function returns none.
    optional<MenuCursor> pop()
    {
        if (_stack.empty())
        {
            return none;
        }
        else
        {
            const auto ret = _stack.top();
            _stack.pop();
            return ret;
        }
    }



    /// Save the current menu cursor with unique key prefixed mod name (when you
    /// call it from native code, prefix "core" to the key). Call it before the
    /// current menu is about to be closed.
    void save(const Key& key, const MenuCursor& cursor)
    {
        _history[key] = cursor;
    }



    /// Restore the previous menu cursor by the key. Call it after
    /// initialization.
    /// If the current menu is opened for the first time, this function returns
    /// none.
    optional<MenuCursor> restore(const Key& key)
    {
        const auto itr = _history.find(key);
        if (itr == std::end(_history))
        {
            return none;
        }
        else
        {
            return itr->second;
        }
    }



private:
    MenuCursorHistory() = default;

    std::unordered_map<Key, MenuCursor> _history;
    std::stack<MenuCursor> _stack;
};

} // namespace ui
} // namespace elona
