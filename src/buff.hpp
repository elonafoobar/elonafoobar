#pragma once

#include <unordered_map>
#include "cat.hpp"
#include "optional.hpp"



namespace elona
{



struct BuffData
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



class BuffDB;


namespace cat
{

template <>
struct CatDBTraits<BuffDB>
{
    using id_type = int;
    using data_type = BuffData;
    static constexpr const char* filename = u8"buff.lua";
    static constexpr const char* table_name = u8"buff";
};

} // namespace cat



class BuffDB : public cat::CatDB<BuffDB>
{
public:
    BuffDB();

    void define(lua_State* L);
};


extern BuffDB the_buff_db;


struct Character;
struct Buff;


bool buff_has(const Character& cc, int id);
optional_ref<const Buff> buff_find(const Character& cc, int id);
void buff_add(
    Character& cc,
    int id,
    int power,
    int turns,
    optional_ref<const Character> doer = none);
void buff_delete(Character& cc, int prm_806);



} // namespace elona
