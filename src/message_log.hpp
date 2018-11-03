#pragma once

#include <string>
#include "snail/color.hpp"



namespace elona
{

struct MessageLogSpan
{
    std::string content;
    snail::Color color;


    MessageLogSpan(const std::string& content, const snail::Color& color)
        : content(content)
        , color(color)
    {
    }
};



struct MessageLogLine
{
    std::vector<MessageLogSpan> spans;
};



struct MessageLog
{
    std::vector<MessageLogLine> lines;
};

extern MessageLog message_log;

} // namespace elona
