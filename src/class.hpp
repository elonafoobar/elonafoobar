#pragma once

#include <string>
#include <vector>
#include "data/types/type_class.hpp"


namespace elona
{

extern int cequipment;
std::vector<std::reference_wrapper<const ClassData>> class_get_available(
    bool is_extra_class);
int access_class_info(int dbmode, const std::string& class_id);

} // namespace elona
