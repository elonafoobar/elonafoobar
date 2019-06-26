#include "net.hpp"
#include <chrono>
#include "../spider/http.hpp"
#include "config/config.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "message.hpp"
#include "variables.hpp"

#include "../thirdparty/nlohmannjson/json.hpp"

using namespace nlohmann;
using namespace spider::http;



namespace elona
{

namespace
{

using Clock = std::chrono::steady_clock;
using TimePoint = Clock::time_point;
using Duration = Clock::duration;


constexpr size_t ChatKind_size = static_cast<size_t>(ChatKind::_size);

std::array<TimePoint, ChatKind_size> last_chat_sent_at;

constexpr std::array<Duration, ChatKind_size> chat_sending_interval{{
    std::chrono::minutes{5}, // chat
    std::chrono::minutes{2}, // dead
    std::chrono::hours{1}, // wish
}};

Duration chat_receive_interval = std::chrono::minutes{5};
TimePoint last_chat_received_at;

constexpr const char* schema = "https";
constexpr const char* host = "cv.elonafoobar.com";
constexpr const char* version = "v1";

const std::string chat_url =
    std::string(schema) + "://" + host + "/" + version + "/chats/";
const std::string poll_url =
    std::string(schema) + "://" + host + "/" + version + "/polls/";
const std::string vote_url =
    std::string(schema) + "://" + host + "/" + version + "/votes/";

int last_received_chat_id = -1;



Headers common_headers_get{{"Connection", "close"},
                           {"User-Agent", latest_version.user_agent()}};
Headers common_headers_post{{"Connection", "close"},
                            {"User-Agent", latest_version.user_agent()},
                            {"Content-Type", "application/json"}};



bool can_send_chat_now(ChatKind kind)
{
    const auto idx = static_cast<size_t>(kind);
    return chat_sending_interval[idx] < Clock::now() - last_chat_sent_at[idx];
}



std::string replace_f_word(std::string str)
{
    // same as vanilla.
    str = strutil::replace(str, u8"fucking", u8"nyoro~n");
    str = strutil::replace(str, u8"fuck", u8"nyou talk funny");
    return str;
}



void send_chat(ChatKind kind, const std::string& message)
{
    if (!can_send_chat_now(kind))
    {
        return;
    }

    json payload;
    payload["kind"] = static_cast<int>(kind);
    payload["message"] = replace_f_word(message);

    Request req{
        Verb::POST, chat_url, common_headers_post, Body{payload.dump()}};
    req.send(
        [](const auto& response) {
            if (response.status / 100 != 2)
            {
                txt(i18n::s.get("core.locale.net.failed_to_send"));
                ELONA_WARN("net.post") << chat_url << " " << response.status
                                       << " " << response.body;
                return;
            }
        },
        [](const auto& error) {
            txt(i18n::s.get("core.locale.net.failed_to_send"));
            ELONA_WARN(error.what());
        });

    last_chat_sent_at[static_cast<size_t>(kind)] = Clock::now();
}

} // namespace



std::vector<ChatData> net_receive_chats(bool skip_old_chat)
{
    if (!Config::instance().net)
    {
        return {};
    }
    if (Clock::now() - last_chat_received_at < chat_receive_interval)
    {
        return {};
    }

    bool done = false;
    std::vector<ChatData> chats;

    Request req{Verb::GET, chat_url, common_headers_get};
    req.send(
        [&](const auto& response) {
            if (response.status / 100 != 2)
            {
                txt(i18n::s.get("core.locale.net.failed_to_receive"));
                ELONA_WARN("net.get") << chat_url << " " << response.status
                                      << " " << response.body;
                done = true;
                return;
            }

            const auto chats_json = json::parse(response.body);
            for (const json& chat_json : chats_json)
            {
                auto kind = chat_json["kind"].get<int>();
                auto id = chat_json["id"].get<int>();
                if (id <= last_received_chat_id)
                {
                    if (skip_old_chat)
                    {
                        continue;
                    }
                }
                else
                {
                    last_received_chat_id = id;
                }
                if (kind == static_cast<int>(ChatKind::chat) &&
                    Config::instance().net_chat)
                {
                    continue;
                }
                chats.emplace_back(
                    id,
                    static_cast<ChatKind>(kind),
                    chat_json["created_at"].get<std::string>(),
                    chat_json["message"].get<std::string>());
            }
            done = true;
        },
        [&](const auto& error) {
            txt(i18n::s.get("core.locale.net.failed_to_receive"));
            ELONA_WARN(error.what());
            done = true;
        });

    while (!done)
    {
        // TODO: show loading cycle.
        await(10);
    }

    last_chat_received_at = Clock::now();
    return chats;
}



std::vector<PollData> net_receive_polls()
{
    if (!Config::instance().net)
    {
        return {};
    }

    bool done = false;
    std::vector<PollData> polls;

    Request req{Verb::GET, poll_url, common_headers_get};
    req.send(
        [&](const auto& response) {
            if (response.status / 100 != 2)
            {
                txt(i18n::s.get("core.locale.net.failed_to_receive"));
                ELONA_WARN("net.get") << poll_url << " " << response.status
                                      << " " << response.body;
                done = true;
                return;
            }

            const auto polls_json = json::parse(response.body);
            for (const json& poll_json : polls_json)
            {
                polls.emplace_back(
                    poll_json["id"].get<int>(),
                    poll_json["name"].get<std::string>(),
                    poll_json["vote_count"].get<int>());
            }
            done = true;
        },
        [&](const auto& error) {
            txt(i18n::s.get("core.locale.net.failed_to_receive"));
            ELONA_WARN(error.what());
            done = true;
        });

    while (!done)
    {
        // TODO: show loading cycle.
        await(10);
    }

    return polls;
}



void net_send_chat(const std::string& message)
{
    if (!Config::instance().net || !Config::instance().net_chat)
    {
        return;
    }

    send_chat(
        ChatKind::chat,
        i18n::s.get(
            "core.locale.net.chat.sent_message",
            cdatan(1, 0),
            cdatan(0, 0),
            message));
}



void net_send_death(
    const std::string& cause,
    const std::string& map,
    const std::string& last_words)
{
    if (!Config::instance().net)
    {
        return;
    }
    if (game_data.wizard)
    {
        return;
    }

    send_chat(
        ChatKind::dead,
        i18n::s.get(
            "core.locale.net.dead.sent_message",
            cdatan(1, 0),
            cdatan(0, 0),
            cause,
            map,
            last_words));
}



void net_send_wish(const std::string& input, const std::string& result)
{
    if (!Config::instance().net || !Config::instance().net_wish)
    {
        return;
    }
    if (game_data.wizard)
    {
        return;
    }

    send_chat(
        ChatKind::wish,
        i18n::s.get(
            "core.locale.net.wish.sent_message",
            cdatan(1, 0),
            cdatan(0, 0),
            input,
            result));
}



void net_send_poll(const std::string& name)
{
    json payload;
    payload["name"] = name;

    Request req{
        Verb::POST, poll_url, common_headers_post, Body{payload.dump()}};
    req.send(
        [](const auto& response) {
            if (response.status / 100 != 2)
            {
                txt(i18n::s.get("core.locale.net.failed_to_send"));
                ELONA_WARN("net.post") << poll_url << " " << response.status
                                       << " " << response.body;
                return;
            }
        },
        [](const auto& error) {
            txt(i18n::s.get("core.locale.net.failed_to_send"));
            ELONA_WARN(error.what());
        });
}



void net_send_vote(int poll_id)
{
    json payload;
    payload["poll"] = poll_id;

    Request req{
        Verb::POST, vote_url, common_headers_post, Body{payload.dump()}};
    req.send(
        [](const auto& response) {
            if (response.status / 100 != 2)
            {
                txt(i18n::s.get("core.locale.net.failed_to_send"));
                ELONA_WARN("net.post") << vote_url << " " << response.status
                                       << " " << response.body;
                return;
            }
        },
        [](const auto& error) {
            txt(i18n::s.get("core.locale.net.failed_to_send"));
            ELONA_WARN(error.what());
        });
}



bool net_can_send_chat_now()
{
    return can_send_chat_now(ChatKind::chat);
}



std::string ChatData::as_log() const
{
    return message;
}



std::string ChatData::as_chat_history() const
{
    // TODO created_at
    return created_at + message;
}

} // namespace elona
