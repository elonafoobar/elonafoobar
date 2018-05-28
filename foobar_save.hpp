#pragma once

#include "version.hpp"


namespace elona
{


struct foobar_save_t
{
    // NOTE: Don't add new fields unless you add them to serialization, which
    // will break save compatibility.
    bool is_autodig_enabled{};
    version_t version;


    void initialize();


    template <typename Archive>
    void serialize(Archive& ar)
    {
        // WARNING: Changing this will break save compatibility!
        ar(is_autodig_enabled);
    }
};


extern foobar_save_t foobar_save;


} // namespace elona
