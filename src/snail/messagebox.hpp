#pragma once

#include <string>



namespace elona
{
namespace snail
{

enum class MessageBox
{
    error,
    warning,
    info,
};



void show_message_box(
    MessageBox flag,
    const std::string& title,
    const std::string& message);

} // namespace snail
} // namespace elona
