#pragma once
#include <string>



namespace elona::i18n
{


void load(const char* language = "jp"); // TODO
std::string _(const std::string&);


} // namespace elona::i18n
