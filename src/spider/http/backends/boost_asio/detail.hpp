#pragma once

#include <memory>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>



namespace elona
{
namespace spider
{
namespace http
{
namespace detail
{

extern std::unique_ptr<boost::asio::io_context> io_context;
extern std::unique_ptr<boost::asio::ssl::context> ssl_context;

} // namespace detail
} // namespace http
} // namespace spider
} // namespace elona
