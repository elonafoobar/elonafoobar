#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "cat.hpp"


namespace elona
{


struct ClassData
{
    std::string id;
    int ordering;
    bool is_extra;
    int item_type;
    int equipment_type;
    std::unordered_map<int, int> skills;
};



class ClassDB;


namespace cat
{

template <>
struct CatDBTraits<ClassDB>
{
    using IdType = std::string;
    using DataType = ClassData;
    static constexpr const char* filename = u8"class.lua";
    static constexpr const char* table_name = u8"class";
};

} // namespace cat



class ClassDB : public cat::CatDB<ClassDB>
{
public:
    ClassDB() = default;

    void define(lua_State* L);
    std::vector<std::reference_wrapper<const ClassData>> get_available_classes(
        bool is_extra_class) const;
};


extern ClassDB the_class_db;


extern int cequipment;
std::vector<std::string> get_available_classes();
int access_class_info(int dbmode, const std::string& dbidn);


} // namespace elona
