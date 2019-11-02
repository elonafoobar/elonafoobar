// Original: Boost.Beast 1.69's example
// https://www.boost.org/doc/libs/1_69_0/libs/beast/example/http/client/async/http_client_async.cpp
// https://www.boost.org/doc/libs/1_69_0/libs/beast/example/http/client/async-ssl/http_client_async_ssl.cpp
//
// Copyright (c) 2016-2017 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast

#include "../../request.hpp"
#include <functional>
#include <string>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/optional.hpp>
#include "../../../../thirdparty/uri/include/network/uri.hpp"
#include "../../error.hpp"
#include "../../response.hpp"
#include "detail.hpp"

// On Windows, DELETE macro may be defined. A wield syntax error occurred around
// the token.
#ifdef DELETE
#undef DELETE
#endif

namespace asio = boost::asio;
namespace beast = boost::beast;
using tcp = asio::ip::tcp;
using error_code = boost::system::error_code;



namespace elona
{
namespace spider
{
namespace http
{

namespace
{

beast::http::verb spider2beast_verb(Verb v)
{
    switch (v)
    {
    case Verb::GET: return beast::http::verb::get;
    case Verb::HEAD: return beast::http::verb::head;
    case Verb::POST: return beast::http::verb::post;
    case Verb::PUT: return beast::http::verb::put;
    case Verb::DELETE: return beast::http::verb::delete_;
    case Verb::OPTIONS: return beast::http::verb::options;
    case Verb::PATCH: return beast::http::verb::patch;
    case Verb::CONNECT: return beast::http::verb::connect;
    case Verb::TRACE: return beast::http::verb::trace;
    default: return beast::http::verb::unknown;
    }
}



// Unfortunately, Boost.Beast currently does not have URL parser.
struct ParsedURL
{
    /// @throws Error
    ParsedURL(const Url& raw_url)
    {
        using namespace network;

        // Parse
        std::error_code ec;
        const auto url = make_uri(raw_url, ec);
        if (ec)
        {
            throw Error{"Invalid URL: " + raw_url};
        }

        // Is https?
        is_https = (url.has_scheme() && url.scheme().to_string() == "https");

        // Set host.
        if (url.has_host())
        {
            host = url.host().to_string();
        }
        else
        {
            throw Error{"No host name: " + raw_url};
        }

        // Set port.
        if (url.has_port())
        {
            port = url.port().to_string();
        }
        else
        {
            port = is_https ? "443" : "80";
        }

        // Set target.
        if (url.has_path())
        {
            target = url.path().to_string();
        }
        if (target.empty())
        {
            target = "/";
        }
        if (url.has_query())
        {
            target += "?" + url.query().to_string();
        }
        if (url.has_fragment())
        {
            target += "#" + url.fragment().to_string();
        }
    }



    bool is_https;
    std::string host;
    std::string port;
    std::string target;
};



class Session : public std::enable_shared_from_this<Session>
{
private:
    using Resolver = tcp::resolver;
    using Socket = tcp::socket;
    using SecureSocket = asio::ssl::stream<Socket>;
    using Buffer = beast::flat_buffer;
    using RawRequest = beast::http::request<beast::http::string_body>;
    using RawResponse = beast::http::response<beast::http::string_body>;
    using FullfilledHandler = std::function<void(Response)>;
    using RejectedHandler = std::function<void(Error)>;



public:
    Session(asio::io_context& io_context, asio::ssl::context& ssl_context)
        : _resolver(io_context)
        , _socket(io_context)
        , _secure_socket(io_context, ssl_context)
    {
    }



    // Start the asynchronous operation
    void
    send(const Request& request, FullfilledHandler done, RejectedHandler failed)
    {
        _original_request = request; // Store for redirect.
        _done = done;
        _failed = failed;

        _url = request.url();
        _timeout = request.timeout();

        // 120; old IE's maximum redirect count.
        _redirects = std::min(120, std::max(0, request.max_redirects()));

        const auto parsed_url = parse_url(request.url());
        if (!parsed_url)
        {
            return;
        }
        _setup_request(request, *parsed_url);

        _is_https = parsed_url->is_https;
        if (_is_https)
        {
            // Set SNI Hostname (many hosts need this to handshake successfully)
            if (!SSL_set_tlsext_host_name(
                    _secure_socket.native_handle(), parsed_url->host.c_str()))
            {
                boost::system::error_code ec{
                    static_cast<int>(::ERR_get_error()),
                    asio::error::get_ssl_category()};
                throw Error{ec.message() + " " + _url};
            }
        }

        // Look up the domain name
        auto self = shared_from_this();
        _resolver.async_resolve(
            parsed_url->host,
            parsed_url->port,
            [this, self](const auto& ec, const auto& results) {
                on_resolve(ec, results);
            });
    }



private:
    Resolver _resolver;
    bool _is_https;
    Socket _socket;
    SecureSocket _secure_socket;
    Buffer _buffer;
    Request _original_request;
    RawRequest _request;
    RawResponse _response;
    int _timeout; // in milliseconds
    int _redirects;
    FullfilledHandler _done;
    RejectedHandler _failed;
    Url _url; // for error message



    void _setup_request(const Request& request, const ParsedURL& parsed_url)
    {
        _request.version(11); // HTTP/1.1
        _request.method(spider2beast_verb(request.verb()));

        // URL
        _request.target(parsed_url.target);

        // Headers
        _request.set(beast::http::field::host, parsed_url.host);
        _request.set(beast::http::field::user_agent, "spider");
        for (const auto& header : request.headers())
        {
            _request.set(header.first, header.second);
        }

        // Body
        _request.body() = request.body();

        // Add Content-Length header automatically.
        _request.prepare_payload();
    }



    Response _construct_response()
    {
        Response res;
        res.status = _response.result_int();
        for (const auto& header : _response)
        {
            res.headers[header.name_string().to_string()] =
                header.value().to_string();
        }
        res.body = _response.body();

        return res;
    }



    void on_resolve(const error_code& ec, Resolver::results_type results)
    {
        if (ec)
        {
            fail("Failed to resolve host name: " + _url);
            return;
        }

        // Make the connection on the IP address we get from a lookup
        auto self = shared_from_this();
        asio::async_connect(
            _is_https ? _secure_socket.next_layer() : _socket,
            std::begin(results),
            std::end(results),
            [this, self](const auto& ec, const auto&) { on_connect(ec); });
    }



    void on_connect(const error_code& ec)
    {
        if (ec)
        {
            fail("Failed to connect to the host: " + _url);
            return;
        }

        auto self = shared_from_this();
        if (_is_https)
        {
            // Handshake.
            _secure_socket.async_handshake(
                asio::ssl::stream_base::client,
                [this, self](const auto& ec) { on_handshake(ec); });
        }
        else
        {
            // Send the HTTP request to the remote host
            beast::http::async_write(
                _socket, _request, [this, self](const auto& ec, const auto&) {
                    on_write(ec);
                });
        }
    }



    void on_handshake(boost::system::error_code ec)
    {
        if (ec)
        {
            fail("Failed to hanshake with the host: " + _url);
            return;
        }

        // Send the HTTP request to the remote host
        auto self = shared_from_this();
        beast::http::async_write(
            _secure_socket,
            _request,
            [this, self](const auto& ec, const auto&) { on_write(ec); });
    }



    void on_write(const error_code& ec)
    {
        if (ec)
        {
            fail("Failed to send a request: " + _url);
            return;
        }

        // Receive the HTTP response
        auto self = shared_from_this();
        if (_is_https)
        {
            beast::http::async_read(
                _secure_socket,
                _buffer,
                _response,
                [this, self](const auto& ec, const auto&) { on_read(ec); });
        }
        else
        {
            beast::http::async_read(
                _socket,
                _buffer,
                _response,
                [this, self](const auto& ec, const auto&) { on_read(ec); });
        }
    }



    void on_read(const error_code& ec)
    {
        if (ec)
        {
            fail("Failed to receive a response: " + _url);
            return;
        }

        if (_is_https)
        {
            // Cancel all pending operations.
            error_code ec_;
            _secure_socket.lowest_layer().cancel(ec_);
            // Shut down the TLS socket.
            auto self = shared_from_this();
            _secure_socket.async_shutdown(
                [this, self](const auto& ec) { on_shutdown(ec); });
        }
        else
        {
            error_code ec_;
            _socket.shutdown(Socket::shutdown_both, ec_);

            // not_connected happens sometimes so don't bother reporting it.
            if (ec_ && ec_ != beast::errc::not_connected)
            {
                fail("Failed to shutdown the connection: " + _url);
                return;
            }

            on_successfully_recieved();
        }
    }



    void on_shutdown(const error_code& ec)
    {
        if (ec)
        {
            if (ec == asio::error::eof)
            {
                // Shutdown operation actually succeeded.
                // See this page for rationale:
                // http://stackoverflow.com/questions/25587403/boost-asio-ssl-async-shutdown-always-finishes-with-an-error
                // This behaviour was fixed in Boost 1.70, then Boost suppresses
                // this kind of EOF error.
            }
            else
            {
                // FIXME: work around
                // This shutdown operation always fails with
                // asio::ssl::error::stream_errors::stream_truncated.
                // According to this page,
                // https://github.com/cpp-netlib/cpp-netlib/issues/670
                // to ignore the error is incorrect, but I cannot find
                // an proper handling.

                // fail("Failed to shutdown the connection: " + _url);
                // return;
            }
        }

        // Close the lower layer's connection under TLS socket.
        error_code ec_;
        _secure_socket.lowest_layer().close(ec_);
        if (ec_)
        {
            fail("Failed to shutdown the connection: " + _url);
            return;
        }

        on_successfully_recieved();
    }



    void on_successfully_recieved()
    {
        using namespace beast::http;

        switch (_response.result())
        {
        case status::moved_permanently:
        case status::found:
        case status::see_other:
        case status::temporary_redirect:
        case status::permanent_redirect:
            if (0 < _redirects)
            {
                do_redirect(_response[field::location].to_string());
                return;
            }
            break;
        default: break;
        }

        _done(_construct_response());
    }



    void do_redirect(const std::string& new_url)
    {
        --_redirects;
        if (!new_url.empty() && new_url[0] == '/')
        {
            // Relative URL.
            using namespace network;

            std::error_code _ec;
            const auto base_url = make_uri(_original_request.url(), _ec);
            assert(!_ec);

            std::string url;
            if (base_url.has_scheme())
            {
                url += base_url.scheme().to_string() + "://";
            }
            if (base_url.has_authority())
            {
                url += base_url.authority().to_string();
            }
            url += new_url;
            _original_request.set_url(url);
        }
        else
        {
            _original_request.set_url(new_url);
        }
        send(_original_request, _done, _failed);
    }



    void fail(const std::string& what)
    {
        fail(Error{what});
    }



    void fail(const Error& err)
    {
        _failed(err);
    }



    boost::optional<ParsedURL> parse_url(const Url& raw_url)
    {
        try
        {
            return ParsedURL{raw_url};
        }
        catch (Error& err)
        {
            fail(err.what());
            return boost::none;
        }
    }
};

} // namespace



void Request::send(
    std::function<void(Response)> done,
    std::function<void(Error)> failed)
{
    using namespace detail;

    const auto session = std::make_shared<Session>(*io_context, *ssl_context);
    session->send(*this, done, failed);
}

} // namespace http
} // namespace spider
} // namespace elona
