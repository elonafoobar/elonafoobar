#pragma once

#include <deque>
#include <string>
#include <vector>
#include "../snail/color.hpp"



namespace elona
{

struct MessageLogSpan
{
    std::string text;
    snail::Color color;


    MessageLogSpan(const std::string& text, const snail::Color& color)
        : text(text)
        , color(color)
    {
    }
};



struct MessageLogLine
{
private:
    using Container = std::vector<MessageLogSpan>;
    using ConstIterator = Container::const_iterator;


public:
    void append(const std::string& text, const snail::Color& color);



    ConstIterator begin() const
    {
        return spans.begin();
    }


    ConstIterator end() const
    {
        return spans.end();
    }


private:
    Container spans;
};



struct MessageLog
{
public:
    void append(const std::string& text, const snail::Color& color);

    void linebreak();

    size_t line_size() const
    {
        return lines.size();
    }

    const MessageLogLine& at(size_t index) const
    {
        return lines.at(index);
    }


private:
    std::deque<MessageLogLine> lines;
};



extern MessageLog message_log;

} // namespace elona
