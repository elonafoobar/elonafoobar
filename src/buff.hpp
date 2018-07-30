#pragma once

#include <unordered_map>
#include "cat.hpp"



namespace elona
{



struct buff_data
{
    enum class type_t
    {
        buff,
        hex,
        food,
    };


    int id;
    cat::ref self;
    type_t type;
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



int buff_find(int prm_799, int prm_800);
int buff_add(int prm_801, int prm_802, int prm_803, int prm_804);
void buff_delete(int prm_805, int prm_806);



} // namespace elona
