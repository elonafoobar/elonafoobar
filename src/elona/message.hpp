#pragma once

#include <string>
#include <utility>
#include <vector>

#include "../snail/color.hpp"
#include "../util/namedparam.hpp"



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
    void txt(const std::string& message, Args&&... args)
    {
        _txt_unpack(args...);
        _txt_internal(message);
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


    /**
     * Messages passed to these three functions are "buffered". They does not
     * shown immediately, and the output of them is delayed until
     * buffered_message_end() is called.
     * @example
     * Message::instance().buffered_message_begin("1");
     * Message::instance().buffered_message_append("2");
     * Message::instance().buffered_message_append("3");
     * // The joined message "123" is shwon at the below line.
     * Message::instance().buffered_message_end();
     */
    void buffered_message_begin(const std::string& message);
    void buffered_message_append(const std::string& message);
    void buffered_message_end();



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



    void _txt_unpack()
    {
    }



    template <typename... Args>
    void _txt_unpack(only_once, Args&&... args)
    {
        show_only_once = true;

        _txt_unpack(std::forward<Args>(args)...);
    }



    template <typename... Args>
    void _txt_unpack(color color_, Args&&... args)
    {
        txtef(color_);

        _txt_unpack(std::forward<Args>(args)...);
    }



    void _msg_write(std::string& message);
    void _msg_newline();
    void _txt_conv();
    void _txt_internal(const std::string& message);
};



template <typename... Args>
void txt(const std::string& message, Args&&... args)
{
    Message::instance().txt(message, std::forward<Args>(args)...);
}

} // namespace elona
