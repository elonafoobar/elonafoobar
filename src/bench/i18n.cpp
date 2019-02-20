#include "../thirdparty/hayai/hayai.hpp"

#include <cassert>
#include "../elona/i18n.hpp"
#include "util.hpp"

using namespace elona;

std::string random_string(size_t length)
{
    auto randchar = []() -> char {
        const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}

BENCHMARK(I18n, BenchI18n1Param, 5, 50)
{
    i18n::fmt_hil("${_1}", random_string(10));
}

BENCHMARK(I18n, BenchI18n2Params, 5, 50)
{
    i18n::fmt_hil("${_1} ${_2}", random_string(10), random_string(10));
}

BENCHMARK(I18n, BenchI18n3Params, 5, 50)
{
    i18n::fmt_hil(
        "${_1} ${_2} ${_3}",
        random_string(10),
        random_string(10),
        random_string(10));
}

BENCHMARK(I18n, BenchI18n4Params, 5, 50)
{
    i18n::fmt_hil(
        "${_1} ${_2} ${_3} ${_4}",
        random_string(10),
        random_string(10),
        random_string(10),
        random_string(10));
}

BENCHMARK(I18n, BenchI18n5Params, 5, 50)
{
    i18n::fmt_hil(
        "${_1} ${_2} ${_3} ${_4} ${_5}",
        random_string(10),
        random_string(10),
        random_string(10),
        random_string(10),
        random_string(10));
}

BENCHMARK(I18n, BenchI18n6Params, 5, 50)
{
    i18n::fmt_hil(
        "${_1} ${_2} ${_3} ${_4} ${_5} ${_6}",
        random_string(10),
        random_string(10),
        random_string(10),
        random_string(10),
        random_string(10),
        random_string(10));
}
