#include "../../core.hpp"

#include <iostream>
#include <thread>

#include "detail.hpp"

namespace asio = boost::asio;



namespace elona
{
namespace spider
{
namespace http
{

namespace
{

std::unique_ptr<asio::executor_work_guard<asio::io_context::executor_type>>
    work_guard;
std::unique_ptr<std::thread> worker_thread;

} // namespace



namespace detail
{

std::unique_ptr<asio::io_context> io_context;
std::unique_ptr<asio::ssl::context> ssl_context;

} // namespace detail



void init()
{
    detail::io_context.reset(new asio::io_context());
    detail::ssl_context.reset(
        new asio::ssl::context(asio::ssl::context::sslv23_client));
    work_guard.reset(
        new asio::executor_work_guard<asio::io_context::executor_type>(
            detail::io_context->get_executor()));
    worker_thread.reset(new std::thread{[]() { detail::io_context->run(); }});
}



void finalize()
{
    work_guard.reset();
    detail::io_context->stop();
    worker_thread->join();
}

} // namespace http
} // namespace spider
} // namespace elona
