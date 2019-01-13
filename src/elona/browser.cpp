#include "browser.hpp"
#include <cstdlib>
#include <string>
#include "../util/range.hpp"
#include "config/config.hpp"

#ifdef ELONA_OS_WINDOWS
#include <windows.h>
#endif

using namespace std::literals::string_literals;



namespace
{

bool _is_trusted_url(const char* url)
{
    const char* trusted_urls[] = {
        "http://ylvania.org/jp",
        "http://ylvania.org/en",
        "https://elonafoobar.com",
    };

    return range::find(trusted_urls, url) != std::end(trusted_urls);
}

} // namespace



namespace elona
{

void open_browser(const char* url)
{
    if (Config::instance().is_test)
    {
        return;
    }

    if (!_is_trusted_url(url))
    {
        throw std::runtime_error{"Try to open unknown URL!"};
    }

#if defined(ELONA_OS_WINDOWS)
    HWND parent = NULL;
    LPCWSTR operation = NULL;
    // `url` must be ascii only.
    const auto len = std::strlen(url);
    std::basic_string<WCHAR> url_(len, L'\0');
    for (size_t i = 0; i < len; ++i)
    {
        url_[i] = url[i];
    }
    LPCWSTR extra_parameter = NULL;
    LPCWSTR default_dir = NULL;
    INT show_command = SW_SHOWNORMAL;

    ::ShellExecute(
        parent,
        operation,
        url_.c_str(),
        extra_parameter,
        default_dir,
        show_command);
#elif defined(ELONA_OS_MACOS)
    std::system(("open "s + url).c_str());
#elif defined(ELONA_OS_LINUX)
    std::system(("xdg-open "s + url).c_str());
#elif defined(ELONA_OS_ANDROID)
    // TODO: implement for android.
    (void)url;
    return;
#else
#error "Unsupported OS"
#endif
}

} // namespace elona
