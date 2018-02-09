#pragma once
#include <string>
#include <vector>



namespace elona::i18n
{


void load(const std::string& language = "jp"); // TODO



std::string _(
    const std::string& key_head,
    const std::vector<std::string>& key_tail);


template <typename... Args>
std::string _(const std::string& key_head, const Args&... key_tail)
{
    return _(key_head, {key_tail...});
}



} // namespace elona::i18n
