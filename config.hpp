#pragma once

#include <string>
#include "lib/noncopyable.hpp"



namespace elona
{


class config : public lib::noncopyable
{
public:
    static config& instance();

private:
    config() = default;
};


void set_config(const std::string& key, int value);
void set_config(const std::string& key, const std::string& value);
void set_config(const std::string& key, const std::string& value1, int value2);



extern int cfg_extraclass;


} // namespace elona
