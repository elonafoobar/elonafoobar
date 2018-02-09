#pragma once

#include <string>
#include <vector>


namespace elona
{


inline int cequipment = 0;
std::vector<std::string> get_available_classes();
int access_class_info(int dbmode, const std::string& dbidn);


} // namespace elona
