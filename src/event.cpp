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

int event_find(int prm_288)
{
    int f_at_m17 = 0;
    f_at_m17 = 0;
    for (int cnt = 0, cnt_end = (evnum); cnt < cnt_end; ++cnt)
    {
        if (evlist(cnt) == prm_288)
        {
            f_at_m17 = 1;
        }
    }
    return f_at_m17;
}

void event_add(int prm_289, int prm_290, int prm_291)
{
    if (evproc)
    {
        evlist(evnum) = evlist(evnum - 1);
        evdata1(evnum) = evdata1(evnum - 1);
        evdata2(evnum) = evdata2(evnum - 1);
        evlist(evnum - 1) = prm_289;
        evdata1(evnum - 1) = prm_290;
        evdata2(evnum - 1) = prm_291;
    }
    else
    {
        evlist(evnum) = prm_289;
        evdata1(evnum) = prm_290;
        evdata2(evnum) = prm_291;
    }
    ++evnum;
    return;
}

turn_result_t event_start_proc()
{
    evproc = 1;
    proc_event();
    evproc = 0;
    --evnum;
    evlist(evnum) = 0;
    if (chatteleport == 1)
    {
        chatteleport = 0;
        return turn_result_t::exit_map;
    }
    return turn_result_t::turn_begin;
}

} // namespace elona
