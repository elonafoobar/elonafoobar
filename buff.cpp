#include "buff.hpp"


namespace elona
{


buff_db::buff_db()
{
    storage.emplace(0, buff_data{buff_data::type_t::buff}); // dummy
    storage.emplace(1, buff_data{buff_data::type_t::buff});
    storage.emplace(2, buff_data{buff_data::type_t::hex});
    storage.emplace(3, buff_data{buff_data::type_t::buff});
    storage.emplace(4, buff_data{buff_data::type_t::buff});
    storage.emplace(5, buff_data{buff_data::type_t::buff});
    storage.emplace(6, buff_data{buff_data::type_t::hex});
    storage.emplace(7, buff_data{buff_data::type_t::buff});
    storage.emplace(8, buff_data{buff_data::type_t::hex});
    storage.emplace(9, buff_data{buff_data::type_t::hex});
    storage.emplace(10, buff_data{buff_data::type_t::buff});
    storage.emplace(11, buff_data{buff_data::type_t::hex});
    storage.emplace(12, buff_data{buff_data::type_t::buff});
    storage.emplace(13, buff_data{buff_data::type_t::hex});
    storage.emplace(14, buff_data{buff_data::type_t::buff});
    storage.emplace(15, buff_data{buff_data::type_t::buff});
    storage.emplace(16, buff_data{buff_data::type_t::hex});
    storage.emplace(17, buff_data{buff_data::type_t::buff});
    storage.emplace(18, buff_data{buff_data::type_t::buff});
    storage.emplace(19, buff_data{buff_data::type_t::buff});
    storage.emplace(20, buff_data{buff_data::type_t::food});
    storage.emplace(21, buff_data{buff_data::type_t::food});
    storage.emplace(22, buff_data{buff_data::type_t::food});
    storage.emplace(23, buff_data{buff_data::type_t::food});
    storage.emplace(24, buff_data{buff_data::type_t::food});
    storage.emplace(25, buff_data{buff_data::type_t::food});
    storage.emplace(26, buff_data{buff_data::type_t::food});
    storage.emplace(27, buff_data{buff_data::type_t::food});
    storage.emplace(28, buff_data{buff_data::type_t::food});
}



} // namespace elona
