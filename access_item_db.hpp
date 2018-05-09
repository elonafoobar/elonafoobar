#pragma once

namespace elona
{

enum class item_db_query_t : int // TODO rename to item_db_query_t
{
    charge_level = 2,
    initialize = 3,
    fixmaterial = 10,
    read = 13,
    zap = 14,
    drink = 15,
    is_offerable = 16,
    identified = 17,
};

enum class read_item_t
{
    none,
    normal_book,
    decodable_book,
    scroll,
    deed,
};

struct item_db_result
{
    bool error;
    bool is_offerable;
    read_item_t read_item;
    int effect_id;
    int effect_power;
};


item_db_result access_item_db(item_db_query_t);

}
