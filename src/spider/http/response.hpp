#pragma once

#include "types.hpp"



namespace elona
{
namespace spider
{
namespace http
{

struct Response
{
    Status status;
    Headers headers;
    Body body;
};

} // namespace http
} // namespace spider
} // namespace elona
