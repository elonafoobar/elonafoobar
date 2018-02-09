#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "optional_ref.hpp"


namespace elona
{


struct class_data
{
    std::string id;
    bool is_extra;
    int item_type;
};



class class_db
{
public:
    class_db();


    optional_ref<class_data> operator[](const std::string& id) const;


private:
    std::unordered_map<std::string, class_data> storage;
};


inline class_db the_class_db;


inline int cequipment = 0;
std::vector<std::string> get_available_classes();
int access_class_info(int dbmode, const std::string& dbidn);


} // namespace elona
