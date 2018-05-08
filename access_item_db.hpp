#pragma once

enum class item_db_t : int
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

struct item_db_result
{
    bool error;
    bool is_offerable;
    int efid;
    int efp;
};


item_db_result access_item_db(item_db_t);
