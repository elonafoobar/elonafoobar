#include "message_log.hpp"



namespace
{

// TODO: should be configurable.
constexpr int max_log_lines = 1000;

} // namespace



namespace elona
{

MessageLog message_log;



void MessageLogLine::append(const std::string& text, const snail::Color& color)
{
    spans.emplace_back(text, color);
}



void MessageLog::append(const std::string& text, const snail::Color& color)
{
    if (lines.empty())
    {
        lines.emplace_back();
    }

    lines.back().append(text, color);
}



void MessageLog::linebreak()
{
    lines.emplace_back();
    if (lines.size() > max_log_lines)
    {
        lines.erase(std::begin(lines));
    }
}

} // namespace elona
