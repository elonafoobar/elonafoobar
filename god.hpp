#pragma once

#include <string>
#include <unordered_map>


namespace elona
{


using god_id_t = std::string;


namespace core_god
{

// constexpr const char* eyth = u8"eyth";
constexpr const char* mani = u8"mani";
constexpr const char* lulwy = u8"lulwy";
constexpr const char* itzpalt = u8"itzpalt";
constexpr const char* ehekatl = u8"ehekatl";
constexpr const char* opatos = u8"opatos";
constexpr const char* jure = u8"jure";
constexpr const char* kumiromi = u8"kumiromi";

} // namespace core_god


struct god_data
{
    god_id_t id;
};


class god_db
{
public:
    god_db();

    const god_data& operator[](const god_id_t& id) const;

private:
    std::unordered_map<god_id_t, god_data> storage;
};


inline god_db the_god_db;


} // namespace elona
