#pragma once

#include <string>
#include <utility>
#include <vector>



namespace elona
{

namespace detail
{

struct only_once_t
{
};



void set_only_once();
void txt_internal(std::vector<std::string>);


inline void txt_unpack(std::vector<std::string>&)
{
}


template <typename... Args>
void txt_unpack(std::vector<std::string>& messages, only_once_t, Args&&... args)
{
    set_only_once();
    txt_unpack(messages, std::forward<Args>(args)...);
}


template <typename... Args>
void txt_unpack(
    std::vector<std::string>& messages,
    const std::string& s,
    Args&&... args)
{
    messages.push_back(s);
    txt_unpack(messages, std::forward<Args>(args)...);
}


template <typename... Args>
void txt_unpack(
    std::vector<std::string>& messages,
    std::string&& s,
    Args&&... args)
{
    messages.push_back(std::move(s));
    txt_unpack(messages, std::forward<Args>(args)...);
}

} // namespace detail



namespace message
{

constexpr detail::only_once_t only_once;

}



class LogObserver
{
public:
    virtual ~LogObserver();
    virtual void update(const std::string& log) = 0;
};


void subscribe_log(LogObserver* observer);
void unsubscribe_log(LogObserver* observer);



namespace detail
{

extern std::vector<LogObserver*> observers;

} // namespace detail


enum class ColorIndex;

void txtcontinue();
void txtef(ColorIndex);
void txtef(int = 0);
void txtnew();
void msg_clear();
void msg_halt();
void anime_halt(int x, int y);

void msg_append_begin(const std::string&);
void msg_append(const std::string&);
void msg_append_end();



template <typename... Args>
void txt(Args&&... args)
{
    std::vector<std::string> messages;
    detail::txt_unpack(messages, args...);
    detail::txt_internal(messages);
}

} // namespace elona
