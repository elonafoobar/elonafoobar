#pragma once

#include "../util/iterable_priority_queue.hpp"
#include "../util/range.hpp"
#include "data/id.hpp"
#include "typedefs.hpp"



namespace elona
{

enum class TurnResult;



/**
 * Deferred game event. Its execution is "deferred" until the next player turn
 * comes.
 */
struct DeferredEvent
{
    /// ID
    data::InstanceId id{};

    /// Queue priority. The larger it is, the earlier the event is fired.
    lua_int priority{};

    /// Extension data
    lua_table ext{};



    DeferredEvent(data::InstanceId id, lua_int priority, lua_table ext = {})
        : id(id)
        , priority(priority)
        , ext(ext)
    {
    }
};



/**
 * Priority queue of @ref DeferredEvent.
 */
struct DeferredEventQueue
{
    const DeferredEvent& top()
    {
        assert(!_queue.empty());
        return _queue.top();
    }



    bool empty() const noexcept
    {
        return _queue.empty();
    }



    bool has(data::InstanceId id) const
    {
        return range::find_if(_queue, [id](const auto& e) {
                   return e.id == id;
               }) != _queue.end();
    }



    void push(const DeferredEvent& event)
    {
        _queue.push(event);
    }



    void pop()
    {
        _queue.pop();
    }



private:
    struct EventComparator
    {
        bool operator()(const DeferredEvent& lhs, const DeferredEvent& rhs)
            const noexcept
        {
            return lhs.priority < rhs.priority;
        }
    };


    // See `iterable_priority_queue`'s comment for the meaning of "iterable".
    lib::iterable_priority_queue<
        DeferredEvent,
        std::vector<DeferredEvent>,
        EventComparator>
        _queue;
};



optional<data::InstanceId> deferred_event_processing_event();
bool deferred_event_has_pending_events();
void deferred_event_add(const DeferredEvent& event);
void deferred_event_add(data::InstanceId id);
bool deferred_event_find(data::InstanceId id);
TurnResult deferred_event_start_proc();

} // namespace elona
