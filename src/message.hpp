#pragma once

#include <string>
#include <utility>
#include <vector>
#include "lib/namedparam.hpp"
#include "snail/color.hpp"



namespace elona
{

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

void msg_halt();
void anime_halt(int x, int y);



class Message : public lib::noncopyable
{
public:
    NAMEDPARAM_DEFINE(bool, only_once);
    NAMEDPARAM_DEFINE(ColorIndex, color);



    template <typename... Args>
    void txt(Args&&... args)
    {
        std::vector<std::string> messages;
        _txt_unpack(messages, args...);
        _txt_internal(messages);
    }



    void linebreak();


    void clear();


    void new_turn()
    {
        _new_turn = true;
    }



    void continue_sentence()
    {
        _continue_sentence = true;
    }



    void txtef(ColorIndex color);



    static Message& instance()
    {
        static Message the_instance;
        return the_instance;
    }


    void msg_append_begin(const std::string&);
    void msg_append(const std::string&);
    void msg_append_end();



private:
    bool show_only_once{};
    bool _continue_sentence{};
    snail::Color text_color{255, 255, 255};
    bool fix_text_color{};
    bool _new_turn = true;
    size_t message_width{};
    std::vector<std::string> msg{500 /* TODO inf_maxlog */};
    std::string msgtemp;
    std::string msgtempprev;



    Message() = default;



    void _txt_unpack(std::vector<std::string>&)
    {
    }



    template <typename... Args>
    void
    _txt_unpack(std::vector<std::string>& messages, only_once, Args&&... args)
    {
        show_only_once = true;

        _txt_unpack(messages, std::forward<Args>(args)...);
    }



    template <typename... Args>
    void _txt_unpack(
        std::vector<std::string>& messages,
        color color_,
        Args&&... args)
    {
        txtef(color_);

        _txt_unpack(messages, std::forward<Args>(args)...);
    }



    template <typename... Args>
    void _txt_unpack(
        std::vector<std::string>& messages,
        const char* s,
        Args&&... args)
    {
        messages.emplace_back(s);

        _txt_unpack(messages, std::forward<Args>(args)...);
    }



    template <typename... Args>
    void _txt_unpack(
        std::vector<std::string>& messages,
        const std::string& s,
        Args&&... args)
    {
        messages.push_back(s);

        _txt_unpack(messages, std::forward<Args>(args)...);
    }



    template <typename... Args>
    void _txt_unpack(
        std::vector<std::string>& messages,
        std::string&& s,
        Args&&... args)
    {
        messages.push_back(std::move(s));

        _txt_unpack(messages, std::forward<Args>(args)...);
    }



    void _msg_write(std::string& message);
    void _msg_newline();
    void _txt_conv();
    void _txt_internal(std::vector<std::string> args);
};



template <typename... Args>
void txt(Args&&... args)
{
    Message::instance().txt(std::forward<Args>(args)...);
}

} // namespace elona
