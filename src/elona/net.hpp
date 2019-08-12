#pragma once

#include <string>
#include <vector>



namespace elona
{

enum class ChatKind
{
    chat,
    death,
    wish,
    news,

    _size,
};



struct ChatData
{
    ChatData(
        int id,
        ChatKind kind,
        const std::string& created_at,
        const std::string& message)
        : id(id)
        , kind(kind)
        , created_at(created_at)
        , message(message)
    {
    }


    int id;
    ChatKind kind;
    std::string created_at; // in ISO 8601
    std::string message;


    std::string as_log() const;
    std::string as_chat_history() const;
};



struct PollData
{
    PollData(int id, const std::string& name, int vote_count)
        : id(id)
        , name(name)
        , vote_count(vote_count)
    {
    }

    int id;
    std::string name;
    int vote_count;
};



// receive
std::vector<ChatData> net_receive_chats(bool skip_old_chat);
std::vector<PollData> net_receive_polls();

// send
void net_send_chat(const std::string& message);
void net_send_death(
    const std::string& cause,
    const std::string& map,
    const std::string& last_words);
void net_send_wish(const std::string& input, const std::string& result);
void net_send_news(
    const std::string& locale_id,
    const std::string& extra_info = "");
void net_register_your_name();
void net_send_vote(int poll_id);

bool net_can_send_chat_now();

} // namespace elona
