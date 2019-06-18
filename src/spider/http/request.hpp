#pragma once

#include <functional>
#include "types.hpp"



namespace elona
{
namespace spider
{
namespace http
{

struct Response;
struct Error;



struct MaxRedirects
{
    MaxRedirects(int value)
        : value(value)
    {
    }

    int value;
};



// in milliseconds
struct Timeout
{
    Timeout(int value)
        : value(value)
    {
    }

    int value;
};



struct Request
{
    Request() = default;
    Request(const Request&) = default;
    Request(Request&&) = default;
    Request& operator=(const Request&) = default;
    Request& operator=(Request&&) = default;


    template <typename... Args>
    Request(Verb verb, const Url& url, Args&&... args)
        : _verb(verb)
        , _url(url)
    {
        _construct(std::forward<Args>(args)...);
    }


    void send(
        std::function<void(Response)> done,
        std::function<void(Error)> failed);



    const Verb& verb() const noexcept
    {
        return _verb;
    }


    const Url& url() const noexcept
    {
        return _url;
    }


    // For redirect.
    void set_url(const Url& new_url)
    {
        _url = new_url;
    }


    const Headers& headers() const noexcept
    {
        return _headers;
    }


    int max_redirects() const noexcept
    {
        return _max_redirects;
    }


    int timeout() const noexcept
    {
        return _timeout;
    }



private:
    Verb _verb;
    Url _url;
    Headers _headers;
    Body _body;
    int _max_redirects = 20; // same as Google Chrome
    int _timeout = 0; // in milliseconds



    template <typename Head, typename... Tail>
    void _construct(Head&& head, Tail&&... tail)
    {
        _set(std::forward<Head>(head));
        _construct(std::forward<Tail>(tail)...);
    }


    void _construct()
    {
    }


    void _set(const Body& body)
    {
        _body = body;
    }


    void _set(Body&& body)
    {
        _body = std::move(body);
    }


    void _set(const Headers& headers)
    {
        _headers = headers;
    }


    void _set(Headers&& headers)
    {
        _headers = std::move(headers);
    }


    void _set(MaxRedirects max_redirects)
    {
        _max_redirects = max_redirects.value;
    }


    void _set(Timeout timeout)
    {
        _timeout = timeout.value;
    }
};

} // namespace http
} // namespace spider
} // namespace elona
