#include "../../messagebox.hpp"
#include <iostream>



namespace elona
{
namespace snail
{

void show_message_box(
    MessageBox,
    const std::string& title,
    const std::string& message)
{
    std::cout << "Message box (" << title << "): " << message << std::endl;
}

} // namespace snail
} // namespace elona
