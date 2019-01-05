#include "event.hpp"
#include "enums.hpp"
#include "variables.hpp"

namespace elona
{

int evproc = 0;

// TODO add serialization routines local to this file

int event_id()
{
    if (evnum <= 0)
    {
        return -1;
    }
    return evlist(evnum - 1);
}

bool event_was_set()
{
    return evnum != 0;
}

int event_find(int event_type)
{
    int f_at_m17 = 0;
    f_at_m17 = 0;
    for (int cnt = 0, cnt_end = (evnum); cnt < cnt_end; ++cnt)
    {
        if (evlist(cnt) == event_type)
        {
            f_at_m17 = 1;
        }
    }
    return f_at_m17;
}

void event_add(int event_type, int info1, int info2)
{
    if (evproc)
    {
        evlist(evnum) = evlist(evnum - 1);
        evdata1(evnum) = evdata1(evnum - 1);
        evdata2(evnum) = evdata2(evnum - 1);
        evlist(evnum - 1) = event_type;
        evdata1(evnum - 1) = info1;
        evdata2(evnum - 1) = info2;
    }
    else
    {
        evlist(evnum) = event_type;
        evdata1(evnum) = info1;
        evdata2(evnum) = info2;
    }
    ++evnum;
}

TurnResult event_start_proc()
{
    evproc = 1;
    proc_event();
    evproc = 0;
    --evnum;
    evlist(evnum) = 0;
    if (chatteleport == 1)
    {
        chatteleport = 0;
        return TurnResult::exit_map;
    }
    return TurnResult::turn_begin;
}

} // namespace elona
