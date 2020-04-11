#pragma once

#include <string>
#include <vector>

#include "../optional.hpp"



namespace elona
{
namespace term
{

using Line = std::string;
using LineDisplay = std::string;



struct Cursor
{
    // 0-indexed
    size_t line = 0;

    // 0-indexed
    size_t column = 0;
};



class Term
{
public:
    Term()
    {
    }



    void set_size(size_t num_lines, size_t num_columns) noexcept
    {
        _num_lines = num_lines;
        _num_columns = num_columns;
    }



    size_t num_lines() const noexcept
    {
        return _num_lines;
    }



    size_t num_columns() const noexcept
    {
        return _num_columns;
    }



    void print(const std::string s)
    {
        if (s.empty())
            return;

        if (_lines.empty())
        {
            _lines.emplace_back();
        }

        for (const auto& c : s)
        {
            if (c == '\n')
            {
                newline();
            }
            else
            {
                _lines.back() += c;
                _cursor.column += 1;
            }
        }
    }



    void println(const std::string& s)
    {
        if (s.empty())
        {
            print("\n");
        }
        else if (s[s.size() - 1] == '\n')
        {
            print(s);
        }
        else
        {
            print(s + '\n');
        }
    }



    void delete_line()
    {
        if (_lines.empty())
            return;

        _lines.at(_cursor.line) = "";
        _cursor.column = 0;
    }



    void newline()
    {
        _lines.emplace_back();
        _cursor.line += 1;
        _cursor.column = 0;
        if (_lines.size() >= _num_lines)
        {
            _display_offset += 1;
        }
    }



    void scroll_to_top()
    {
        _display_offset = 0;
    }



    void scroll_to_bottom()
    {
        if (_lines.size() < _num_lines)
        {
            _display_offset = 0;
        }
        else
        {
            _display_offset = _lines.size() - _num_lines;
        }
    }



    void scroll_by(int n)
    {
        if (n == 0)
            return;
        if (_lines.empty())
            return;

        if (n < 0)
        {
            if (_display_offset < static_cast<size_t>(-n))
            {
                _display_offset = 0;
            }
            else
            {
                _display_offset += n;
            }
        }
        else
        {
            if (_lines.size() <= _display_offset + n)
            {
                _display_offset = _lines.size() - 1;
            }
            else
            {
                _display_offset += n;
            }
        }
    }



    void scroll_page_by(int n)
    {
        scroll_by(n * static_cast<int>(num_lines()));
    }



    std::vector<LineDisplay> lines_display() const
    {
        std::vector<LineDisplay> ret;
        for (size_t i = 0; i < _num_lines; ++i)
        {
            const auto index = i + _display_offset;
            if (_lines.size() <= index)
            {
                break;
            }
            ret.push_back(_lines.at(index));
        }
        return ret;
    }



    const Cursor& cursor() const noexcept
    {
        return _cursor;
    }



    optional<Cursor> cursor_display() const noexcept
    {
        if (_cursor.line < _display_offset)
        {
            return none;
        }
        else if (_num_lines + _display_offset <= _cursor.line)
        {
            return none;
        }
        else
        {
            return Cursor{_cursor.line - _display_offset, _cursor.column};
        }
    }



private:
    size_t _num_lines;
    size_t _num_columns;
    std::vector<Line> _lines;
    size_t _display_offset = 0;
    Cursor _cursor;
};

} // namespace term
} // namespace elona
