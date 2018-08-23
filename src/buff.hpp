#pragma once

#include <unordered_map>
#include "cat.hpp"
#include "optional.hpp"



namespace elona
{



struct buff_data
{
    enum class Type
    {
        buff,
        hex,
        food,
    };


    int id;
    cat::ref self;
    Type type;
    cat::ref duration;
    cat::ref on_refresh;
};



class buff_db;


namespace cat
{

template <>
struct cat_db_traits<buff_db>
{
    using id_type = int;
    using data_type = buff_data;
    static constexpr const char* filename = u8"buff.lua";
    static constexpr const char* table_name = u8"buff";
};

} // namespace cat



class buff_db : public cat::cat_db<buff_db>
{
public:
    buff_db();

    void define(lua_State* L);
};


extern buff_db the_buff_db;


struct character;
struct buff_t;


bool buff_has(const character& cc, int id);
optional_ref<const buff_t> buff_find(const character& cc, int id);
void buff_add(
    character& cc,
    int id,
    int power,
    int turns,
    optional_ref<const character> doer = none);
void buff_delete(character& cc, int prm_806);



} // namespace elona
