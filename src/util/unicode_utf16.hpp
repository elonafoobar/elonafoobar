#pragma once
#include <string>

namespace lib
{
namespace unicode
{

std::string utf16_to_utf8(const wchar_t*, const wchar_t*);

std::string utf16_to_utf8(const std::wstring&);

std::wstring utf8_to_utf16(const std::string&);

}
}
