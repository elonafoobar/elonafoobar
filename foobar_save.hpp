#pragma once

#include "version.hpp"


namespace elona
{


struct foobar_save_t
{
    bool is_autodig_enabled{};
    version_t version;


    void initialize();


    template <typename Archive>
    void serialize(Archive& ar)
    {
        ar(is_autodig_enabled);
    }
};


extern foobar_save_t foobar_save;


} // namespace elona
