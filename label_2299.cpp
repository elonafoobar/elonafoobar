#include "elona.hpp"
#include "variables.hpp"


namespace elona
{
int label_2654();


void label_2299()
{
    if (dbmode != 1) {
        stat = label_2654();
        return;
        return;
    }
    dbsum = 0;
    dbmax = 0;
    if (1 > objlv) { goto label_2300_internal; }
    if (fltselect != 1) { goto label_2300_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2300_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"slime"s) { goto label_2300_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(2), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2300_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 1)) * 400) + 1;
    dblist(0, dbmax) = 0;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2300_internal:
    if (1 > objlv) { goto label_2301_internal; }
    if (fltselect != 3) { goto label_2301_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2301_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"god"s) { goto label_2301_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(3), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2301_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 1)) * 400) + 1;
    dblist(0, dbmax) = 343;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2301_internal:
    if (35 > objlv) { goto label_2302_internal; }
    if (fltselect != 7) { goto label_2302_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2302_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2302_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(4), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2302_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 35)) * 400) + 1;
    dblist(0, dbmax) = 1;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2302_internal:
    if (22 > objlv) { goto label_2303_internal; }
    if (fltselect != 1) { goto label_2303_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2303_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"juere"s) { goto label_2303_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(5), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2303_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 22)) * 400) + 1;
    dblist(0, dbmax) = 353;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2303_internal:
    if (20 > objlv) { goto label_2304_internal; }
    if (fltselect != 1) { goto label_2304_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2304_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2304_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(6), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2304_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 20)) * 400) + 1;
    dblist(0, dbmax) = 70;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2304_internal:
    if (20 > objlv) { goto label_2305_internal; }
    if (fltselect != 7) { goto label_2305_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2305_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2305_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(7), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2305_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 20)) * 400) + 1;
    dblist(0, dbmax) = 69;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2305_internal:
    if (40 > objlv) { goto label_2306_internal; }
    if (fltselect != 7) { goto label_2306_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2306_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2306_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(8), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2306_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 40)) * 400) + 1;
    dblist(0, dbmax) = 73;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2306_internal:
    if (20 > objlv) { goto label_2307_internal; }
    if (fltselect != 7) { goto label_2307_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2307_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2307_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(9), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2307_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 20)) * 400) + 1;
    dblist(0, dbmax) = 74;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2307_internal:
    if (50 > objlv) { goto label_2308_internal; }
    if (fltselect != 7) { goto label_2308_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2308_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2308_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(10), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2308_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 50)) * 400) + 1;
    dblist(0, dbmax) = 206;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2308_internal:
    if (20 > objlv) { goto label_2309_internal; }
    if (fltselect != 7) { goto label_2309_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2309_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2309_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(11), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2309_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 20)) * 400) + 1;
    dblist(0, dbmax) = 38;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2309_internal:
    if (40 > objlv) { goto label_2310_internal; }
    if (fltselect != 7) { goto label_2310_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2310_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2310_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(12), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2310_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 40)) * 400) + 1;
    dblist(0, dbmax) = 40;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2310_internal:
    if (69 > objlv) { goto label_2311_internal; }
    if (fltselect != 1) { goto label_2311_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2311_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2311_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(13), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2311_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 69)) * 400) + 1;
    dblist(0, dbmax) = 333;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2311_internal:
    if (40 > objlv) { goto label_2312_internal; }
    if (fltselect != 9) { goto label_2312_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2312_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2312_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(14), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2312_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 40)) * 400) + 1;
    dblist(0, dbmax) = 76;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2312_internal:
    if (40 > objlv) { goto label_2313_internal; }
    if (fltselect != 9) { goto label_2313_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2313_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"yerles"s) { goto label_2313_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(15), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2313_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 40)) * 400) + 1;
    dblist(0, dbmax) = 77;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2313_internal:
    if (10 > objlv) { goto label_2314_internal; }
    if (fltselect != 9) { goto label_2314_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2314_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2314_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(16), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2314_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 10)) * 400) + 1;
    dblist(0, dbmax) = 204;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2314_internal:
    if (55 > objlv) { goto label_2315_internal; }
    if (fltselect != 3) { goto label_2315_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2315_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"elea"s) { goto label_2315_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(17), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2315_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 55)) * 400) + 1;
    dblist(0, dbmax) = 2;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2315_internal:
    if (1 > objlv) { goto label_2316_internal; }
    if (fltselect != 1) { goto label_2316_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2316_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2316_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(18), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2316_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 1)) * 400) + 1;
    dblist(0, dbmax) = 37;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2316_internal:
    if (20 > objlv) { goto label_2317_internal; }
    if (fltselect != 3) { goto label_2317_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2317_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"juere"s) { goto label_2317_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(19), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2317_internal; }
    }
    dbsum += 1000 / (500 + abs((objlv - 20)) * 400) + 1;
    dblist(0, dbmax) = 23;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2317_internal:
    if (6 > objlv) { goto label_2318_internal; }
    if (fltselect != 2) { goto label_2318_internal; }
    if (npcmemory(1, 26) != 0) { goto label_2318_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2318_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2318_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(20), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2318_internal; }
    }
    dbsum += 1000 / (500 + abs((objlv - 6)) * 400) + 1;
    dblist(0, dbmax) = 26;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2318_internal:
    if (42 > objlv) { goto label_2319_internal; }
    if (fltselect != 2) { goto label_2319_internal; }
    if (npcmemory(1, 27) != 0) { goto label_2319_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2319_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2319_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(21), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2319_internal; }
    }
    dbsum += 1000 / (500 + abs((objlv - 42)) * 400) + 1;
    dblist(0, dbmax) = 27;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2319_internal:
    if (78 > objlv) { goto label_2320_internal; }
    if (fltselect != 3) { goto label_2320_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2320_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"juere"s) { goto label_2320_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(22), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2320_internal; }
    }
    dbsum += 1000 / (500 + abs((objlv - 78)) * 400) + 1;
    dblist(0, dbmax) = 28;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2320_internal:
    if (50 > objlv) { goto label_2321_internal; }
    if (fltselect != 3) { goto label_2321_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2321_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"juere"s) { goto label_2321_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(23), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2321_internal; }
    }
    dbsum += 1000 / (500 + abs((objlv - 50)) * 400) + 1;
    dblist(0, dbmax) = 29;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2321_internal:
    if (25 > objlv) { goto label_2322_internal; }
    if (fltselect != 3) { goto label_2322_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2322_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"dragon"s) { goto label_2322_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(24), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2322_internal; }
    }
    dbsum += 1000 / (500 + abs((objlv - 25)) * 400) + 1;
    dblist(0, dbmax) = 140;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2322_internal:
    if (20 > objlv) { goto label_2323_internal; }
    if (fltselect != 3) { goto label_2323_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2323_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2323_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(25), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2323_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 20)) * 400) + 1;
    dblist(0, dbmax) = 30;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2323_internal:
    if (20 > objlv) { goto label_2324_internal; }
    if (fltselect != 3) { goto label_2324_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2324_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"juere"s) { goto label_2324_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(26), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2324_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 20)) * 400) + 1;
    dblist(0, dbmax) = 31;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2324_internal:
    if (130 > objlv) { goto label_2325_internal; }
    if (fltselect != 3) { goto label_2325_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2325_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"cat"s) { goto label_2325_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(27), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2325_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 130)) * 400) + 1;
    dblist(0, dbmax) = 351;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2325_internal:
    if (1 > objlv) { goto label_2326_internal; }
    if (fltselect != 3) { goto label_2326_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2326_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2326_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(28), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2326_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 1)) * 400) + 1;
    dblist(0, dbmax) = 352;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2326_internal:
    if (20 > objlv) { goto label_2327_internal; }
    if (fltselect != 2) { goto label_2327_internal; }
    if (npcmemory(1, 32) != 0) { goto label_2327_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2327_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2327_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(29), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2327_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 20)) * 400) + 1;
    dblist(0, dbmax) = 32;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2327_internal:
    if (20 > objlv) { goto label_2328_internal; }
    if (fltselect != 3) { goto label_2328_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2328_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"elea"s) { goto label_2328_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(30), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2328_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 20)) * 400) + 1;
    dblist(0, dbmax) = 33;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2328_internal:
    if (20 > objlv) { goto label_2329_internal; }
    if (fltselect != 3) { goto label_2329_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2329_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"elea"s) { goto label_2329_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(31), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2329_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 20)) * 400) + 1;
    dblist(0, dbmax) = 34;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2329_internal:
    if (10 > objlv) { goto label_2330_internal; }
    if (fltselect != 3) { goto label_2330_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2330_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2330_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(32), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2330_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 10)) * 400) + 1;
    dblist(0, dbmax) = 139;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2330_internal:
    if (10 > objlv) { goto label_2331_internal; }
    if (fltselect != 3) { goto label_2331_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2331_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2331_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(33), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2331_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 10)) * 400) + 1;
    dblist(0, dbmax) = 146;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2331_internal:
    if (10 > objlv) { goto label_2332_internal; }
    if (fltselect != 3) { goto label_2332_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2332_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2332_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(34), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2332_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 10)) * 400) + 1;
    dblist(0, dbmax) = 142;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2332_internal:
    if (28 > objlv) { goto label_2333_internal; }
    if (fltselect != 3) { goto label_2333_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2333_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"lich"s) { goto label_2333_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(35), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2333_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 28)) * 400) + 1;
    dblist(0, dbmax) = 141;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2333_internal:
    if (25 > objlv) { goto label_2334_internal; }
    if (fltselect != 3) { goto label_2334_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2334_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2334_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(36), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2334_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 25)) * 400) + 1;
    dblist(0, dbmax) = 143;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2334_internal:
    if (24 > objlv) { goto label_2335_internal; }
    if (fltselect != 3) { goto label_2335_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2335_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2335_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(37), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2335_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 24)) * 400) + 1;
    dblist(0, dbmax) = 144;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2335_internal:
    if (16 > objlv) { goto label_2336_internal; }
    if (fltselect != 3) { goto label_2336_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2336_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"dragon"s) { goto label_2336_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(38), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2336_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 16)) * 400) + 1;
    dblist(0, dbmax) = 145;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2336_internal:
    if (350 > objlv) { goto label_2337_internal; }
    if (fltselect != 3) { goto label_2337_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2337_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"god"s) { goto label_2337_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(39), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2337_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 350)) * 400) + 1;
    dblist(0, dbmax) = 306;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2337_internal:
    if (350 > objlv) { goto label_2338_internal; }
    if (fltselect != 3) { goto label_2338_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2338_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"god"s) { goto label_2338_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(40), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2338_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 350)) * 400) + 1;
    dblist(0, dbmax) = 331;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2338_internal:
    if (1200 > objlv) { goto label_2339_internal; }
    if (fltselect != 3) { goto label_2339_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2339_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"god"s) { goto label_2339_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(41), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2339_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 1200)) * 400) + 1;
    dblist(0, dbmax) = 336;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2339_internal:
    if (350 > objlv) { goto label_2340_internal; }
    if (fltselect != 3) { goto label_2340_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2340_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"god"s) { goto label_2340_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(42), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2340_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 350)) * 400) + 1;
    dblist(0, dbmax) = 338;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2340_internal:
    if (350 > objlv) { goto label_2341_internal; }
    if (fltselect != 3) { goto label_2341_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2341_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"god"s) { goto label_2341_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(43), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2341_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 350)) * 400) + 1;
    dblist(0, dbmax) = 339;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2341_internal:
    if (350 > objlv) { goto label_2342_internal; }
    if (fltselect != 3) { goto label_2342_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2342_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"god"s) { goto label_2342_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(44), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2342_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 350)) * 400) + 1;
    dblist(0, dbmax) = 342;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2342_internal:
    if (1200 > objlv) { goto label_2343_internal; }
    if (fltselect != 3) { goto label_2343_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2343_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"god"s) { goto label_2343_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(45), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2343_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 1200)) * 400) + 1;
    dblist(0, dbmax) = 340;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2343_internal:
    if (1 > objlv) { goto label_2344_internal; }
    if (fltselect != 0) { goto label_2344_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 3) { goto label_2344_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"slime"s) { goto label_2344_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(46), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2344_internal; }
    }
    dbsum += 80000 / (500 + abs((objlv - 1)) * 400) + 1;
    dblist(0, dbmax) = 3;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2344_internal:
    if (4 > objlv) { goto label_2345_internal; }
    if (fltselect != 0) { goto label_2345_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 3) { goto label_2345_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"slime"s) { goto label_2345_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(47), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2345_internal; }
    }
    dbsum += 70000 / (500 + abs((objlv - 4)) * 400) + 1;
    dblist(0, dbmax) = 4;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2345_internal:
    if (10 > objlv) { goto label_2346_internal; }
    if (fltselect != 0) { goto label_2346_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 3) { goto label_2346_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"slime"s) { goto label_2346_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(48), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2346_internal; }
    }
    dbsum += 70000 / (500 + abs((objlv - 10)) * 400) + 1;
    dblist(0, dbmax) = 169;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2346_internal:
    if (16 > objlv) { goto label_2347_internal; }
    if (fltselect != 0) { goto label_2347_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 3) { goto label_2347_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"slime"s) { goto label_2347_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(49), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2347_internal; }
    }
    dbsum += 70000 / (500 + abs((objlv - 16)) * 400) + 1;
    dblist(0, dbmax) = 194;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2347_internal:
    if (9 > objlv) { goto label_2348_internal; }
    if (fltselect != 0) { goto label_2348_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2348_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"slime"s) { goto label_2348_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(50), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2348_internal; }
    }
    dbsum += 25000 / (500 + abs((objlv - 9)) * 400) + 1;
    dblist(0, dbmax) = 286;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2348_internal:
    if (22 > objlv) { goto label_2349_internal; }
    if (fltselect != 0) { goto label_2349_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2349_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"slime"s) { goto label_2349_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(51), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2349_internal; }
    }
    dbsum += 25000 / (500 + abs((objlv - 22)) * 400) + 1;
    dblist(0, dbmax) = 285;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2349_internal:
    if (20 > objlv) { goto label_2350_internal; }
    if (fltselect != 0) { goto label_2350_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2350_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"drake"s) { goto label_2350_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(52), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2350_internal; }
    }
    dbsum += 25000 / (500 + abs((objlv - 20)) * 400) + 1;
    dblist(0, dbmax) = 287;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2350_internal:
    if (52 > objlv) { goto label_2351_internal; }
    if (fltselect != 0) { goto label_2351_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2351_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"machine"s) { goto label_2351_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(53), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2351_internal; }
    }
    dbsum += 15000 / (500 + abs((objlv - 52)) * 400) + 1;
    dblist(0, dbmax) = 327;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2351_internal:
    if (1 > objlv) { goto label_2352_internal; }
    if (fltselect != 0) { goto label_2352_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2352_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"rabbit"s) { goto label_2352_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(54), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2352_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 1)) * 400) + 1;
    dblist(0, dbmax) = 5;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2352_internal:
    if (1 > objlv) { goto label_2353_internal; }
    if (fltselect != 0) { goto label_2353_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2353_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"snail"s) { goto label_2353_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(55), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2353_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 1)) * 400) + 1;
    dblist(0, dbmax) = 6;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2353_internal:
    if (3 > objlv) { goto label_2354_internal; }
    if (fltselect != 0) { goto label_2354_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2354_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2354_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(56), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2354_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 3)) * 400) + 1;
    dblist(0, dbmax) = 7;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2354_internal:
    if (4 > objlv) { goto label_2355_internal; }
    if (fltselect != 5) { goto label_2355_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2355_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2355_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(57), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2355_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 4)) * 400) + 1;
    dblist(0, dbmax) = 8;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2355_internal:
    if (2 > objlv) { goto label_2356_internal; }
    if (fltselect != 5) { goto label_2356_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2356_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2356_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(58), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2356_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 2)) * 400) + 1;
    dblist(0, dbmax) = 9;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2356_internal:
    if (5 > objlv) { goto label_2357_internal; }
    if (fltselect != 9) { goto label_2357_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2357_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2357_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(59), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2357_internal; }
    }
    dbsum += 2000 / (500 + abs((objlv - 5)) * 400) + 1;
    dblist(0, dbmax) = 269;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2357_internal:
    if (32 > objlv) { goto label_2358_internal; }
    if (fltselect != 9) { goto label_2358_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2358_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2358_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(60), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2358_internal; }
    }
    dbsum += 10000 / (500 + abs((objlv - 32)) * 100) + 1;
    dblist(0, dbmax) = 320;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2358_internal:
    if (5 > objlv) { goto label_2359_internal; }
    if (fltselect != 9) { goto label_2359_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2359_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2359_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(61), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2359_internal; }
    }
    dbsum += 2000 / (500 + abs((objlv - 5)) * 400) + 1;
    dblist(0, dbmax) = 273;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2359_internal:
    if (16 > objlv) { goto label_2360_internal; }
    if (fltselect != 7) { goto label_2360_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2360_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"juere"s) { goto label_2360_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(62), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2360_internal; }
    }
    dbsum += 2000 / (500 + abs((objlv - 16)) * 400) + 1;
    dblist(0, dbmax) = 326;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2360_internal:
    if (5 > objlv) { goto label_2361_internal; }
    if (fltselect != 9) { goto label_2361_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2361_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2361_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(63), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2361_internal; }
    }
    dbsum += 2000 / (500 + abs((objlv - 5)) * 400) + 1;
    dblist(0, dbmax) = 270;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2361_internal:
    if (12 > objlv) { goto label_2362_internal; }
    if (fltselect != 1) { goto label_2362_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2362_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2362_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(64), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2362_internal; }
    }
    dbsum += 2000 / (500 + abs((objlv - 12)) * 400) + 1;
    dblist(0, dbmax) = 349;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2362_internal:
    if (35 > objlv) { goto label_2363_internal; }
    if (fltselect != 3) { goto label_2363_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2363_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2363_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(65), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2363_internal; }
    }
    dbsum += 2000 / (500 + abs((objlv - 35)) * 400) + 1;
    dblist(0, dbmax) = 348;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2363_internal:
    if (5 > objlv) { goto label_2364_internal; }
    if (fltselect != 1) { goto label_2364_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2364_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2364_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(66), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2364_internal; }
    }
    dbsum += 2000 / (500 + abs((objlv - 5)) * 400) + 1;
    dblist(0, dbmax) = 347;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2364_internal:
    if (8 > objlv) { goto label_2365_internal; }
    if (fltselect != 9) { goto label_2365_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2365_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2365_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(67), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2365_internal; }
    }
    dbsum += 2000 / (500 + abs((objlv - 8)) * 400) + 1;
    dblist(0, dbmax) = 271;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2365_internal:
    if (8 > objlv) { goto label_2366_internal; }
    if (fltselect != 9) { goto label_2366_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2366_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2366_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(68), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2366_internal; }
    }
    dbsum += 2000 / (500 + abs((objlv - 8)) * 400) + 1;
    dblist(0, dbmax) = 335;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2366_internal:
    if (3 > objlv) { goto label_2367_internal; }
    if (fltselect != 9) { goto label_2367_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2367_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2367_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(69), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2367_internal; }
    }
    dbsum += 2000 / (500 + abs((objlv - 3)) * 400) + 1;
    dblist(0, dbmax) = 337;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2367_internal:
    if (6 > objlv) { goto label_2368_internal; }
    if (fltselect != 9) { goto label_2368_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2368_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2368_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(70), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2368_internal; }
    }
    dbsum += 2000 / (500 + abs((objlv - 6)) * 400) + 1;
    dblist(0, dbmax) = 272;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2368_internal:
    if (10 > objlv) { goto label_2369_internal; }
    if (fltselect != 9) { goto label_2369_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2369_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2369_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(71), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2369_internal; }
    }
    dbsum += 2000 / (500 + abs((objlv - 10)) * 400) + 1;
    dblist(0, dbmax) = 274;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2369_internal:
    if (26 > objlv) { goto label_2370_internal; }
    if (fltselect != 9) { goto label_2370_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2370_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"eulderna"s) { goto label_2370_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(72), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2370_internal; }
    }
    dbsum += 2000 / (500 + abs((objlv - 26)) * 400) + 1;
    dblist(0, dbmax) = 289;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2370_internal:
    if (26 > objlv) { goto label_2371_internal; }
    if (fltselect != 9) { goto label_2371_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2371_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"juere"s) { goto label_2371_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(73), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2371_internal; }
    }
    dbsum += 2000 / (500 + abs((objlv - 26)) * 400) + 1;
    dblist(0, dbmax) = 293;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2371_internal:
    if (26 > objlv) { goto label_2372_internal; }
    if (fltselect != 9) { goto label_2372_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2372_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2372_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(74), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2372_internal; }
    }
    dbsum += 2000 / (500 + abs((objlv - 26)) * 400) + 1;
    dblist(0, dbmax) = 295;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2372_internal:
    if (1 > objlv) { goto label_2373_internal; }
    if (fltselect != 5) { goto label_2373_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2373_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2373_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(75), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2373_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 1)) * 400) + 1;
    dblist(0, dbmax) = 35;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2373_internal:
    if (1 > objlv) { goto label_2374_internal; }
    if (fltselect != 5) { goto label_2374_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2374_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2374_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(76), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2374_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 1)) * 400) + 1;
    dblist(0, dbmax) = 36;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2374_internal:
    if (1 > objlv) { goto label_2375_internal; }
    if (fltselect != 0) { goto label_2375_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2375_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2375_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(77), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2375_internal; }
    }
    dbsum += 60000 / (500 + abs((objlv - 1)) * 400) + 1;
    dblist(0, dbmax) = 174;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2375_internal:
    if (1 > objlv) { goto label_2376_internal; }
    if (fltselect != 0) { goto label_2376_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2376_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"sheep"s) { goto label_2376_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(78), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2376_internal; }
    }
    dbsum += 30000 / (500 + abs((objlv - 1)) * 400) + 1;
    dblist(0, dbmax) = 10;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2376_internal:
    if (2 > objlv) { goto label_2377_internal; }
    if (fltselect != 0) { goto label_2377_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2377_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"frog"s) { goto label_2377_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(79), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2377_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 2)) * 400) + 1;
    dblist(0, dbmax) = 11;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2377_internal:
    if (3 > objlv) { goto label_2378_internal; }
    if (fltselect != 0) { goto label_2378_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2378_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"yerles"s) { goto label_2378_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(80), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2378_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 3)) * 400) + 1;
    dblist(0, dbmax) = 12;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2378_internal:
    if (3 > objlv) { goto label_2379_internal; }
    if (fltselect != 0) { goto label_2379_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 5) { goto label_2379_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"kobolt"s) { goto label_2379_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(81), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2379_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 3)) * 400) + 1;
    dblist(0, dbmax) = 13;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2379_internal:
    if (2 > objlv) { goto label_2380_internal; }
    if (fltselect != 0) { goto label_2380_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 7) { goto label_2380_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"yeek"s) { goto label_2380_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(82), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2380_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 2)) * 400) + 1;
    dblist(0, dbmax) = 236;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2380_internal:
    if (6 > objlv) { goto label_2381_internal; }
    if (fltselect != 0) { goto label_2381_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 7) { goto label_2381_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"yeek"s) { goto label_2381_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(83), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2381_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 6)) * 400) + 1;
    dblist(0, dbmax) = 238;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2381_internal:
    if (4 > objlv) { goto label_2382_internal; }
    if (fltselect != 0) { goto label_2382_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 7) { goto label_2382_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"yeek"s) { goto label_2382_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(84), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2382_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 4)) * 400) + 1;
    dblist(0, dbmax) = 241;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2382_internal:
    if (9 > objlv) { goto label_2383_internal; }
    if (fltselect != 0) { goto label_2383_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 7) { goto label_2383_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"yeek"s) { goto label_2383_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(85), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2383_internal; }
    }
    dbsum += 50000 / (500 + abs((objlv - 9)) * 400) + 1;
    dblist(0, dbmax) = 240;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2383_internal:
    if (6 > objlv) { goto label_2384_internal; }
    if (fltselect != 0) { goto label_2384_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 12) { goto label_2384_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"yeek"s) { goto label_2384_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(86), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2384_internal; }
    }
    dbsum += 150000 / (500 + abs((objlv - 6)) * 400) + 1;
    dblist(0, dbmax) = 237;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2384_internal:
    if (18 > objlv) { goto label_2385_internal; }
    if (fltselect != 0) { goto label_2385_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 12) { goto label_2385_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2385_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(87), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2385_internal; }
    }
    dbsum += 25000 / (500 + abs((objlv - 18)) * 400) + 1;
    dblist(0, dbmax) = 244;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2385_internal:
    if (25 > objlv) { goto label_2386_internal; }
    if (fltselect != 0) { goto label_2386_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2386_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"rock"s) { goto label_2386_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(88), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2386_internal; }
    }
    dbsum += 20000 / (500 + abs((objlv - 25)) * 400) + 1;
    dblist(0, dbmax) = 245;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2386_internal:
    if (10 > objlv) { goto label_2387_internal; }
    if (fltselect != 0) { goto label_2387_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2387_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2387_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(89), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2387_internal; }
    }
    dbsum += 15000 / (500 + abs((objlv - 10)) * 200) + 1;
    dblist(0, dbmax) = 321;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2387_internal:
    if (14 > objlv) { goto label_2388_internal; }
    if (fltselect != 3) { goto label_2388_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 7) { goto label_2388_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"yeek"s) { goto label_2388_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(90), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2388_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 14)) * 400) + 1;
    dblist(0, dbmax) = 242;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2388_internal:
    if (5 > objlv) { goto label_2389_internal; }
    if (fltselect != 7) { goto label_2389_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2389_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2389_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(91), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2389_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 5)) * 400) + 1;
    dblist(0, dbmax) = 239;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2389_internal:
    if (4 > objlv) { goto label_2390_internal; }
    if (fltselect != 0) { goto label_2390_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2390_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"centipede"s) { goto label_2390_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(92), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2390_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 4)) * 400) + 1;
    dblist(0, dbmax) = 14;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2390_internal:
    if (4 > objlv) { goto label_2391_internal; }
    if (fltselect != 0) { goto label_2391_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2391_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"mushroom"s) { goto label_2391_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(93), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2391_internal; }
    }
    dbsum += 50000 / (500 + abs((objlv - 4)) * 400) + 1;
    dblist(0, dbmax) = 15;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2391_internal:
    if (8 > objlv) { goto label_2392_internal; }
    if (fltselect != 0) { goto label_2392_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2392_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"mushroom"s) { goto label_2392_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(94), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2392_internal; }
    }
    dbsum += 50000 / (500 + abs((objlv - 8)) * 400) + 1;
    dblist(0, dbmax) = 283;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2392_internal:
    if (21 > objlv) { goto label_2393_internal; }
    if (fltselect != 0) { goto label_2393_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2393_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"mushroom"s) { goto label_2393_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(95), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2393_internal; }
    }
    dbsum += 50000 / (500 + abs((objlv - 21)) * 400) + 1;
    dblist(0, dbmax) = 284;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2393_internal:
    if (5 > objlv) { goto label_2394_internal; }
    if (fltselect != 7) { goto label_2394_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2394_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"yerles"s) { goto label_2394_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(96), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2394_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 5)) * 400) + 1;
    dblist(0, dbmax) = 16;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2394_internal:
    if (5 > objlv) { goto label_2395_internal; }
    if (fltselect != 7) { goto label_2395_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2395_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"yerles"s) { goto label_2395_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(97), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2395_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 5)) * 400) + 1;
    dblist(0, dbmax) = 39;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2395_internal:
    if (5 > objlv) { goto label_2396_internal; }
    if (fltselect != 7) { goto label_2396_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2396_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"yerles"s) { goto label_2396_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(98), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2396_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 5)) * 400) + 1;
    dblist(0, dbmax) = 171;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2396_internal:
    if (5 > objlv) { goto label_2397_internal; }
    if (fltselect != 7) { goto label_2397_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2397_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"yerles"s) { goto label_2397_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(99), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2397_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 5)) * 400) + 1;
    dblist(0, dbmax) = 172;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2397_internal:
    if (20 > objlv) { goto label_2398_internal; }
    if (fltselect != 7) { goto label_2398_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2398_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"yerles"s) { goto label_2398_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(100), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2398_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 20)) * 400) + 1;
    dblist(0, dbmax) = 173;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2398_internal:
    if (5 > objlv) { goto label_2399_internal; }
    if (fltselect != 7) { goto label_2399_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2399_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2399_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(101), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2399_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 5)) * 400) + 1;
    dblist(0, dbmax) = 71;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2399_internal:
    if (5 > objlv) { goto label_2400_internal; }
    if (fltselect != 1) { goto label_2400_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2400_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2400_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(102), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2400_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 5)) * 400) + 1;
    dblist(0, dbmax) = 72;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2400_internal:
    if (25 > objlv) { goto label_2401_internal; }
    if (fltselect != 3) { goto label_2401_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2401_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2401_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(103), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2401_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 25)) * 400) + 1;
    dblist(0, dbmax) = 79;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2401_internal:
    if (35 > objlv) { goto label_2402_internal; }
    if (fltselect != 3) { goto label_2402_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2402_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2402_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(104), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2402_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 35)) * 400) + 1;
    dblist(0, dbmax) = 80;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2402_internal:
    if (5 > objlv) { goto label_2403_internal; }
    if (fltselect != 0) { goto label_2403_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 2) { goto label_2403_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"orc"s) { goto label_2403_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(105), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2403_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 5)) * 400) + 1;
    dblist(0, dbmax) = 17;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2403_internal:
    if (7 > objlv) { goto label_2404_internal; }
    if (fltselect != 0) { goto label_2404_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2404_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"lizardman"s) { goto label_2404_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(106), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2404_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 7)) * 400) + 1;
    dblist(0, dbmax) = 281;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2404_internal:
    if (18 > objlv) { goto label_2405_internal; }
    if (fltselect != 0) { goto label_2405_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2405_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"minotaur"s) { goto label_2405_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(107), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2405_internal; }
    }
    dbsum += 70000 / (500 + abs((objlv - 18)) * 400) + 1;
    dblist(0, dbmax) = 282;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2405_internal:
    if (22 > objlv) { goto label_2406_internal; }
    if (fltselect != 0) { goto label_2406_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2406_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"minotaur"s) { goto label_2406_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(108), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2406_internal; }
    }
    dbsum += 70000 / (500 + abs((objlv - 22)) * 400) + 1;
    dblist(0, dbmax) = 296;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2406_internal:
    if (23 > objlv) { goto label_2407_internal; }
    if (fltselect != 0) { goto label_2407_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2407_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"minotaur"s) { goto label_2407_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(109), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2407_internal; }
    }
    dbsum += 70000 / (500 + abs((objlv - 23)) * 400) + 1;
    dblist(0, dbmax) = 298;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2407_internal:
    if (25 > objlv) { goto label_2408_internal; }
    if (fltselect != 0) { goto label_2408_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2408_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"minotaur"s) { goto label_2408_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(110), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2408_internal; }
    }
    dbsum += 40000 / (500 + abs((objlv - 25)) * 400) + 1;
    dblist(0, dbmax) = 299;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2408_internal:
    if (31 > objlv) { goto label_2409_internal; }
    if (fltselect != 3) { goto label_2409_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2409_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"minotaur"s) { goto label_2409_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(111), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2409_internal; }
    }
    dbsum += 40000 / (500 + abs((objlv - 31)) * 400) + 1;
    dblist(0, dbmax) = 300;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2409_internal:
    if (14 > objlv) { goto label_2410_internal; }
    if (fltselect != 0) { goto label_2410_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 2) { goto label_2410_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"troll"s) { goto label_2410_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(112), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2410_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 14)) * 400) + 1;
    dblist(0, dbmax) = 251;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2410_internal:
    if (5 > objlv) { goto label_2411_internal; }
    if (fltselect != 0) { goto label_2411_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 4) { goto label_2411_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"elea"s) { goto label_2411_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(113), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2411_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 5)) * 400) + 1;
    dblist(0, dbmax) = 18;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2411_internal:
    if (5 > objlv) { goto label_2412_internal; }
    if (fltselect != 0) { goto label_2412_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 4) { goto label_2412_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"elea"s) { goto label_2412_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(114), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2412_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 5)) * 400) + 1;
    dblist(0, dbmax) = 24;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2412_internal:
    if (12 > objlv) { goto label_2413_internal; }
    if (fltselect != 0) { goto label_2413_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2413_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"asura"s) { goto label_2413_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(115), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2413_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 12)) * 400) + 1;
    dblist(0, dbmax) = 309;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2413_internal:
    if (26 > objlv) { goto label_2414_internal; }
    if (fltselect != 0) { goto label_2414_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2414_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"asura"s) { goto label_2414_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(116), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2414_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 26)) * 400) + 1;
    dblist(0, dbmax) = 310;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2414_internal:
    if (37 > objlv) { goto label_2415_internal; }
    if (fltselect != 0) { goto label_2415_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2415_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"asura"s) { goto label_2415_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(117), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2415_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 37)) * 400) + 1;
    dblist(0, dbmax) = 311;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2415_internal:
    if (5 > objlv) { goto label_2416_internal; }
    if (fltselect != 7) { goto label_2416_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2416_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2416_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(118), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2416_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 5)) * 400) + 1;
    dblist(0, dbmax) = 41;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2416_internal:
    if (5 > objlv) { goto label_2417_internal; }
    if (fltselect != 7) { goto label_2417_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2417_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2417_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(119), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2417_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 5)) * 400) + 1;
    dblist(0, dbmax) = 75;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2417_internal:
    if (5 > objlv) { goto label_2418_internal; }
    if (fltselect != 0) { goto label_2418_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2418_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"mandrake"s) { goto label_2418_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(120), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2418_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 5)) * 400) + 1;
    dblist(0, dbmax) = 19;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2418_internal:
    if (5 > objlv) { goto label_2419_internal; }
    if (fltselect != 0) { goto label_2419_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2419_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"beetle"s) { goto label_2419_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(121), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2419_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 5)) * 400) + 1;
    dblist(0, dbmax) = 22;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2419_internal:
    if (10 > objlv) { goto label_2420_internal; }
    if (fltselect != 0) { goto label_2420_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 2) { goto label_2420_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"orc"s) { goto label_2420_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(122), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2420_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 10)) * 400) + 1;
    dblist(0, dbmax) = 20;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2420_internal:
    if (25 > objlv) { goto label_2421_internal; }
    if (fltselect != 2) { goto label_2421_internal; }
    if (npcmemory(1, 25) != 0) { goto label_2421_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 2) { goto label_2421_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"orc"s) { goto label_2421_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(123), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2421_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 25)) * 400) + 1;
    dblist(0, dbmax) = 25;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2421_internal:
    if (8 > objlv) { goto label_2422_internal; }
    if (fltselect != 0) { goto label_2422_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 9) { goto label_2422_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"zombie"s) { goto label_2422_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(124), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2422_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 8)) * 400) + 1;
    dblist(0, dbmax) = 21;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2422_internal:
    if (1 > objlv) { goto label_2423_internal; }
    if (fltselect != 0) { goto label_2423_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2423_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"bat"s) { goto label_2423_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(125), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2423_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 1)) * 400) + 1;
    dblist(0, dbmax) = 42;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2423_internal:
    if (10 > objlv) { goto label_2424_internal; }
    if (fltselect != 0) { goto label_2424_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2424_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"bat"s) { goto label_2424_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(126), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2424_internal; }
    }
    dbsum += 70000 / (500 + abs((objlv - 10)) * 400) + 1;
    dblist(0, dbmax) = 43;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2424_internal:
    if (30 > objlv) { goto label_2425_internal; }
    if (fltselect != 0) { goto label_2425_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2425_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"bat"s) { goto label_2425_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(127), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2425_internal; }
    }
    dbsum += 60000 / (500 + abs((objlv - 30)) * 400) + 1;
    dblist(0, dbmax) = 44;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2425_internal:
    if (15 > objlv) { goto label_2426_internal; }
    if (fltselect != 0) { goto label_2426_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2426_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"ent"s) { goto label_2426_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(128), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2426_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 15)) * 400) + 1;
    dblist(0, dbmax) = 45;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2426_internal:
    if (15 > objlv) { goto label_2427_internal; }
    if (fltselect != 0) { goto label_2427_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2427_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"ent"s) { goto label_2427_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(129), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2427_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 15)) * 400) + 1;
    dblist(0, dbmax) = 46;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2427_internal:
    if (20 > objlv) { goto label_2428_internal; }
    if (fltselect != 0) { goto label_2428_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2428_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"lich"s) { goto label_2428_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(130), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2428_internal; }
    }
    dbsum += 60000 / (500 + abs((objlv - 20)) * 400) + 1;
    dblist(0, dbmax) = 47;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2428_internal:
    if (30 > objlv) { goto label_2429_internal; }
    if (fltselect != 0) { goto label_2429_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2429_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"lich"s) { goto label_2429_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(131), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2429_internal; }
    }
    dbsum += 50000 / (500 + abs((objlv - 30)) * 400) + 1;
    dblist(0, dbmax) = 48;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2429_internal:
    if (45 > objlv) { goto label_2430_internal; }
    if (fltselect != 0) { goto label_2430_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2430_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"lich"s) { goto label_2430_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(132), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2430_internal; }
    }
    dbsum += 40000 / (500 + abs((objlv - 45)) * 400) + 1;
    dblist(0, dbmax) = 49;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2430_internal:
    if (18 > objlv) { goto label_2431_internal; }
    if (fltselect != 0) { goto label_2431_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2431_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"lich"s) { goto label_2431_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(133), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2431_internal; }
    }
    dbsum += 10000 / (500 + abs((objlv - 18)) * 400) + 1;
    dblist(0, dbmax) = 307;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2431_internal:
    if (35 > objlv) { goto label_2432_internal; }
    if (fltselect != 0) { goto label_2432_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2432_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"lich"s) { goto label_2432_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(134), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2432_internal; }
    }
    dbsum += 10000 / (500 + abs((objlv - 35)) * 400) + 1;
    dblist(0, dbmax) = 308;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2432_internal:
    if (5 > objlv) { goto label_2433_internal; }
    if (fltselect != 0) { goto label_2433_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2433_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"hound"s) { goto label_2433_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(135), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2433_internal; }
    }
    dbsum += 80000 / (500 + abs((objlv - 5)) * 400) + 1;
    dblist(0, dbmax) = 50;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2433_internal:
    if (10 > objlv) { goto label_2434_internal; }
    if (fltselect != 0) { goto label_2434_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 14) { goto label_2434_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"hound"s) { goto label_2434_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(136), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2434_internal; }
    }
    dbsum += 70000 / (500 + abs((objlv - 10)) * 400) + 1;
    dblist(0, dbmax) = 51;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2434_internal:
    if (10 > objlv) { goto label_2435_internal; }
    if (fltselect != 0) { goto label_2435_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 15) { goto label_2435_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"hound"s) { goto label_2435_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(137), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2435_internal; }
    }
    dbsum += 70000 / (500 + abs((objlv - 10)) * 400) + 1;
    dblist(0, dbmax) = 52;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2435_internal:
    if (12 > objlv) { goto label_2436_internal; }
    if (fltselect != 0) { goto label_2436_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 16) { goto label_2436_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"hound"s) { goto label_2436_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(138), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2436_internal; }
    }
    dbsum += 70000 / (500 + abs((objlv - 12)) * 400) + 1;
    dblist(0, dbmax) = 53;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2436_internal:
    if (12 > objlv) { goto label_2437_internal; }
    if (fltselect != 0) { goto label_2437_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 17) { goto label_2437_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"hound"s) { goto label_2437_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(139), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2437_internal; }
    }
    dbsum += 70000 / (500 + abs((objlv - 12)) * 400) + 1;
    dblist(0, dbmax) = 54;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2437_internal:
    if (18 > objlv) { goto label_2438_internal; }
    if (fltselect != 0) { goto label_2438_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 18) { goto label_2438_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"hound"s) { goto label_2438_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(140), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2438_internal; }
    }
    dbsum += 50000 / (500 + abs((objlv - 18)) * 400) + 1;
    dblist(0, dbmax) = 55;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2438_internal:
    if (18 > objlv) { goto label_2439_internal; }
    if (fltselect != 0) { goto label_2439_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 19) { goto label_2439_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"hound"s) { goto label_2439_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(141), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2439_internal; }
    }
    dbsum += 50000 / (500 + abs((objlv - 18)) * 400) + 1;
    dblist(0, dbmax) = 56;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2439_internal:
    if (15 > objlv) { goto label_2440_internal; }
    if (fltselect != 0) { goto label_2440_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 20) { goto label_2440_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"hound"s) { goto label_2440_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(142), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2440_internal; }
    }
    dbsum += 50000 / (500 + abs((objlv - 15)) * 400) + 1;
    dblist(0, dbmax) = 57;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2440_internal:
    if (22 > objlv) { goto label_2441_internal; }
    if (fltselect != 0) { goto label_2441_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 21) { goto label_2441_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"hound"s) { goto label_2441_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(143), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2441_internal; }
    }
    dbsum += 40000 / (500 + abs((objlv - 22)) * 400) + 1;
    dblist(0, dbmax) = 58;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2441_internal:
    if (25 > objlv) { goto label_2442_internal; }
    if (fltselect != 0) { goto label_2442_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 22) { goto label_2442_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"hound"s) { goto label_2442_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(144), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2442_internal; }
    }
    dbsum += 40000 / (500 + abs((objlv - 25)) * 400) + 1;
    dblist(0, dbmax) = 59;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2442_internal:
    if (30 > objlv) { goto label_2443_internal; }
    if (fltselect != 0) { goto label_2443_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 23) { goto label_2443_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"hound"s) { goto label_2443_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(145), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2443_internal; }
    }
    dbsum += 40000 / (500 + abs((objlv - 30)) * 400) + 1;
    dblist(0, dbmax) = 60;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2443_internal:
    if (4 > objlv) { goto label_2444_internal; }
    if (fltselect != 0) { goto label_2444_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2444_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"rabbit"s) { goto label_2444_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(146), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2444_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 4)) * 400) + 1;
    dblist(0, dbmax) = 61;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2444_internal:
    if (10 > objlv) { goto label_2445_internal; }
    if (fltselect != 0) { goto label_2445_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2445_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"rabbit"s) { goto label_2445_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(147), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2445_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 10)) * 400) + 1;
    dblist(0, dbmax) = 62;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2445_internal:
    if (7 > objlv) { goto label_2446_internal; }
    if (fltselect != 0) { goto label_2446_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2446_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"ghost"s) { goto label_2446_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(148), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2446_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 7)) * 400) + 1;
    dblist(0, dbmax) = 63;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2446_internal:
    if (3 > objlv) { goto label_2447_internal; }
    if (fltselect != 0) { goto label_2447_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2447_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"ghost"s) { goto label_2447_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(149), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2447_internal; }
    }
    dbsum += 70000 / (500 + abs((objlv - 3)) * 400) + 1;
    dblist(0, dbmax) = 64;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2447_internal:
    if (8 > objlv) { goto label_2448_internal; }
    if (fltselect != 0) { goto label_2448_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2448_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"ent"s) { goto label_2448_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(150), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2448_internal; }
    }
    dbsum += 40000 / (500 + abs((objlv - 8)) * 400) + 1;
    dblist(0, dbmax) = 312;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2448_internal:
    if (19 > objlv) { goto label_2449_internal; }
    if (fltselect != 0) { goto label_2449_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2449_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"ent"s) { goto label_2449_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(151), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2449_internal; }
    }
    dbsum += 40000 / (500 + abs((objlv - 19)) * 400) + 1;
    dblist(0, dbmax) = 313;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2449_internal:
    if (12 > objlv) { goto label_2450_internal; }
    if (fltselect != 0) { goto label_2450_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2450_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"spirit"s) { goto label_2450_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(152), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2450_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 12)) * 400) + 1;
    dblist(0, dbmax) = 65;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2450_internal:
    if (30 > objlv) { goto label_2451_internal; }
    if (fltselect != 0) { goto label_2451_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2451_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"spirit"s) { goto label_2451_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(153), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2451_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 30)) * 400) + 1;
    dblist(0, dbmax) = 66;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2451_internal:
    if (2 > objlv) { goto label_2452_internal; }
    if (fltselect != 0) { goto label_2452_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2452_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"eye"s) { goto label_2452_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(154), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2452_internal; }
    }
    dbsum += 80000 / (500 + abs((objlv - 2)) * 400) + 1;
    dblist(0, dbmax) = 67;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2452_internal:
    if (14 > objlv) { goto label_2453_internal; }
    if (fltselect != 0) { goto label_2453_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2453_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"eye"s) { goto label_2453_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(155), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2453_internal; }
    }
    dbsum += 60000 / (500 + abs((objlv - 14)) * 400) + 1;
    dblist(0, dbmax) = 315;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2453_internal:
    if (7 > objlv) { goto label_2454_internal; }
    if (fltselect != 0) { goto label_2454_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2454_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"eye"s) { goto label_2454_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(156), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2454_internal; }
    }
    dbsum += 60000 / (500 + abs((objlv - 7)) * 400) + 1;
    dblist(0, dbmax) = 316;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2454_internal:
    if (29 > objlv) { goto label_2455_internal; }
    if (fltselect != 0) { goto label_2455_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2455_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"eye"s) { goto label_2455_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(157), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2455_internal; }
    }
    dbsum += 60000 / (500 + abs((objlv - 29)) * 400) + 1;
    dblist(0, dbmax) = 314;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2455_internal:
    if (20 > objlv) { goto label_2456_internal; }
    if (fltselect != 0) { goto label_2456_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2456_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"wyvern"s) { goto label_2456_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(158), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2456_internal; }
    }
    dbsum += 50000 / (500 + abs((objlv - 20)) * 400) + 1;
    dblist(0, dbmax) = 68;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2456_internal:
    if (15 > objlv) { goto label_2457_internal; }
    if (fltselect != 0) { goto label_2457_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2457_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"eulderna"s) { goto label_2457_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(159), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2457_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 15)) * 400) + 1;
    dblist(0, dbmax) = 78;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2457_internal:
    if (5 > objlv) { goto label_2458_internal; }
    if (fltselect != 0) { goto label_2458_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2458_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"wasp"s) { goto label_2458_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(160), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2458_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 5)) * 400) + 1;
    dblist(0, dbmax) = 81;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2458_internal:
    if (10 > objlv) { goto label_2459_internal; }
    if (fltselect != 0) { goto label_2459_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2459_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"wasp"s) { goto label_2459_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(161), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2459_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 10)) * 400) + 1;
    dblist(0, dbmax) = 82;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2459_internal:
    if (22 > objlv) { goto label_2460_internal; }
    if (fltselect != 0) { goto label_2460_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2460_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"giant"s) { goto label_2460_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(162), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2460_internal; }
    }
    dbsum += 60000 / (500 + abs((objlv - 22)) * 400) + 1;
    dblist(0, dbmax) = 83;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2460_internal:
    if (40 > objlv) { goto label_2461_internal; }
    if (fltselect != 0) { goto label_2461_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2461_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"giant"s) { goto label_2461_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(163), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2461_internal; }
    }
    dbsum += 50000 / (500 + abs((objlv - 40)) * 400) + 1;
    dblist(0, dbmax) = 84;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2461_internal:
    if (7 > objlv) { goto label_2462_internal; }
    if (fltselect != 0) { goto label_2462_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2462_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"imp"s) { goto label_2462_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(164), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2462_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 7)) * 400) + 1;
    dblist(0, dbmax) = 85;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2462_internal:
    if (16 > objlv) { goto label_2463_internal; }
    if (fltselect != 0) { goto label_2463_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2463_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"imp"s) { goto label_2463_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(165), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2463_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 16)) * 400) + 1;
    dblist(0, dbmax) = 86;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2463_internal:
    if (27 > objlv) { goto label_2464_internal; }
    if (fltselect != 0) { goto label_2464_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2464_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"imp"s) { goto label_2464_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(166), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2464_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 27)) * 400) + 1;
    dblist(0, dbmax) = 87;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2464_internal:
    if (4 > objlv) { goto label_2465_internal; }
    if (fltselect != 0) { goto label_2465_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2465_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"hand"s) { goto label_2465_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(167), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2465_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 4)) * 400) + 1;
    dblist(0, dbmax) = 88;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2465_internal:
    if (11 > objlv) { goto label_2466_internal; }
    if (fltselect != 0) { goto label_2466_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2466_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"hand"s) { goto label_2466_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(168), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2466_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 11)) * 400) + 1;
    dblist(0, dbmax) = 89;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2466_internal:
    if (15 > objlv) { goto label_2467_internal; }
    if (fltselect != 0) { goto label_2467_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2467_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"hand"s) { goto label_2467_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(169), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2467_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 15)) * 400) + 1;
    dblist(0, dbmax) = 90;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2467_internal:
    if (5 > objlv) { goto label_2468_internal; }
    if (fltselect != 0) { goto label_2468_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2468_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"ghost"s) { goto label_2468_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(170), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2468_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 5)) * 400) + 1;
    dblist(0, dbmax) = 91;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2468_internal:
    if (13 > objlv) { goto label_2469_internal; }
    if (fltselect != 0) { goto label_2469_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2469_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"ghost"s) { goto label_2469_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(171), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2469_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 13)) * 400) + 1;
    dblist(0, dbmax) = 92;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2469_internal:
    if (8 > objlv) { goto label_2470_internal; }
    if (fltselect != 0) { goto label_2470_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2470_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"mandrake"s) { goto label_2470_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(172), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2470_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 8)) * 400) + 1;
    dblist(0, dbmax) = 93;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2470_internal:
    if (19 > objlv) { goto label_2471_internal; }
    if (fltselect != 0) { goto label_2471_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2471_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"mandrake"s) { goto label_2471_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(173), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2471_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 19)) * 400) + 1;
    dblist(0, dbmax) = 94;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2471_internal:
    if (10 > objlv) { goto label_2472_internal; }
    if (fltselect != 0) { goto label_2472_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2472_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"snake"s) { goto label_2472_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(174), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2472_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 10)) * 400) + 1;
    dblist(0, dbmax) = 95;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2472_internal:
    if (18 > objlv) { goto label_2473_internal; }
    if (fltselect != 0) { goto label_2473_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2473_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"snake"s) { goto label_2473_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(175), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2473_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 18)) * 400) + 1;
    dblist(0, dbmax) = 96;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2473_internal:
    if (16 > objlv) { goto label_2474_internal; }
    if (fltselect != 0) { goto label_2474_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2474_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"drake"s) { goto label_2474_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(176), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2474_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 16)) * 400) + 1;
    dblist(0, dbmax) = 97;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2474_internal:
    if (16 > objlv) { goto label_2475_internal; }
    if (fltselect != 0) { goto label_2475_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2475_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"drake"s) { goto label_2475_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(177), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2475_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 16)) * 400) + 1;
    dblist(0, dbmax) = 98;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2475_internal:
    if (7 > objlv) { goto label_2476_internal; }
    if (fltselect != 0) { goto label_2476_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 13) { goto label_2476_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"zombie"s) { goto label_2476_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(178), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2476_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 7)) * 400) + 1;
    dblist(0, dbmax) = 99;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2476_internal:
    if (14 > objlv) { goto label_2477_internal; }
    if (fltselect != 0) { goto label_2477_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 13) { goto label_2477_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"zombie"s) { goto label_2477_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(179), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2477_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 14)) * 400) + 1;
    dblist(0, dbmax) = 100;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2477_internal:
    if (22 > objlv) { goto label_2478_internal; }
    if (fltselect != 0) { goto label_2478_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 13) { goto label_2478_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"zombie"s) { goto label_2478_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(180), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2478_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 22)) * 400) + 1;
    dblist(0, dbmax) = 101;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2478_internal:
    if (28 > objlv) { goto label_2479_internal; }
    if (fltselect != 3) { goto label_2479_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 13) { goto label_2479_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"zombie"s) { goto label_2479_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(181), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2479_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 28)) * 400) + 1;
    dblist(0, dbmax) = 257;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2479_internal:
    if (19 > objlv) { goto label_2480_internal; }
    if (fltselect != 0) { goto label_2480_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 13) { goto label_2480_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"zombie"s) { goto label_2480_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(182), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2480_internal; }
    }
    dbsum += 50000 / (500 + abs((objlv - 19)) * 400) + 1;
    dblist(0, dbmax) = 254;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2480_internal:
    if (2 > objlv) { goto label_2481_internal; }
    if (fltselect != 0) { goto label_2481_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 1) { goto label_2481_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"goblin"s) { goto label_2481_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(183), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2481_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 2)) * 400) + 1;
    dblist(0, dbmax) = 102;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2481_internal:
    if (6 > objlv) { goto label_2482_internal; }
    if (fltselect != 0) { goto label_2482_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 1) { goto label_2482_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"goblin"s) { goto label_2482_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(184), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2482_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 6)) * 400) + 1;
    dblist(0, dbmax) = 103;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2482_internal:
    if (8 > objlv) { goto label_2483_internal; }
    if (fltselect != 0) { goto label_2483_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 1) { goto label_2483_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"goblin"s) { goto label_2483_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(185), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2483_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 8)) * 400) + 1;
    dblist(0, dbmax) = 104;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2483_internal:
    if (10 > objlv) { goto label_2484_internal; }
    if (fltselect != 0) { goto label_2484_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 1) { goto label_2484_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"goblin"s) { goto label_2484_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(186), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2484_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 10)) * 400) + 1;
    dblist(0, dbmax) = 105;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2484_internal:
    if (12 > objlv) { goto label_2485_internal; }
    if (fltselect != 0) { goto label_2485_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2485_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"ghost"s) { goto label_2485_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(187), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2485_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 12)) * 400) + 1;
    dblist(0, dbmax) = 106;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2485_internal:
    if (12 > objlv) { goto label_2486_internal; }
    if (fltselect != 0) { goto label_2486_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2486_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"ghost"s) { goto label_2486_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(188), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2486_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 12)) * 400) + 1;
    dblist(0, dbmax) = 107;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2486_internal:
    if (4 > objlv) { goto label_2487_internal; }
    if (fltselect != 0) { goto label_2487_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 11) { goto label_2487_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"bear"s) { goto label_2487_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(189), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2487_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 4)) * 400) + 1;
    dblist(0, dbmax) = 108;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2487_internal:
    if (10 > objlv) { goto label_2488_internal; }
    if (fltselect != 0) { goto label_2488_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 11) { goto label_2488_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"bear"s) { goto label_2488_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(190), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2488_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 10)) * 400) + 1;
    dblist(0, dbmax) = 109;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2488_internal:
    if (28 > objlv) { goto label_2489_internal; }
    if (fltselect != 0) { goto label_2489_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 11) { goto label_2489_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"bear"s) { goto label_2489_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(191), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2489_internal; }
    }
    dbsum += 50000 / (500 + abs((objlv - 28)) * 400) + 1;
    dblist(0, dbmax) = 344;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2489_internal:
    if (15 > objlv) { goto label_2490_internal; }
    if (fltselect != 0) { goto label_2490_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2490_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"armor"s) { goto label_2490_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(192), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2490_internal; }
    }
    dbsum += 40000 / (500 + abs((objlv - 15)) * 400) + 1;
    dblist(0, dbmax) = 110;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2490_internal:
    if (25 > objlv) { goto label_2491_internal; }
    if (fltselect != 0) { goto label_2491_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2491_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"armor"s) { goto label_2491_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(193), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2491_internal; }
    }
    dbsum += 30000 / (500 + abs((objlv - 25)) * 400) + 1;
    dblist(0, dbmax) = 111;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2491_internal:
    if (35 > objlv) { goto label_2492_internal; }
    if (fltselect != 0) { goto label_2492_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2492_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"armor"s) { goto label_2492_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(194), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2492_internal; }
    }
    dbsum += 30000 / (500 + abs((objlv - 35)) * 400) + 1;
    dblist(0, dbmax) = 112;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2492_internal:
    if (45 > objlv) { goto label_2493_internal; }
    if (fltselect != 0) { goto label_2493_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2493_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"armor"s) { goto label_2493_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(195), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2493_internal; }
    }
    dbsum += 30000 / (500 + abs((objlv - 45)) * 400) + 1;
    dblist(0, dbmax) = 113;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2493_internal:
    if (22 > objlv) { goto label_2494_internal; }
    if (fltselect != 0) { goto label_2494_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2494_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"medusa"s) { goto label_2494_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(196), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2494_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 22)) * 400) + 1;
    dblist(0, dbmax) = 114;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2494_internal:
    if (33 > objlv) { goto label_2495_internal; }
    if (fltselect != 0) { goto label_2495_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2495_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"medusa"s) { goto label_2495_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(197), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2495_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 33)) * 400) + 1;
    dblist(0, dbmax) = 115;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2495_internal:
    if (44 > objlv) { goto label_2496_internal; }
    if (fltselect != 0) { goto label_2496_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2496_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"medusa"s) { goto label_2496_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(198), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2496_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 44)) * 400) + 1;
    dblist(0, dbmax) = 116;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2496_internal:
    if (8 > objlv) { goto label_2497_internal; }
    if (fltselect != 0) { goto label_2497_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2497_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"cupid"s) { goto label_2497_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(199), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2497_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 8)) * 400) + 1;
    dblist(0, dbmax) = 117;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2497_internal:
    if (9 > objlv) { goto label_2498_internal; }
    if (fltselect != 0) { goto label_2498_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2498_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"phantom"s) { goto label_2498_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(200), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2498_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 9)) * 400) + 1;
    dblist(0, dbmax) = 118;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2498_internal:
    if (30 > objlv) { goto label_2499_internal; }
    if (fltselect != 0) { goto label_2499_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2499_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"dinosaur"s) { goto label_2499_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(201), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2499_internal; }
    }
    dbsum += 50000 / (500 + abs((objlv - 30)) * 400) + 1;
    dblist(0, dbmax) = 248;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2499_internal:
    if (13 > objlv) { goto label_2500_internal; }
    if (fltselect != 0) { goto label_2500_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2500_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"harpy"s) { goto label_2500_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(202), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2500_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 13)) * 400) + 1;
    dblist(0, dbmax) = 119;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2500_internal:
    if (32 > objlv) { goto label_2501_internal; }
    if (fltselect != 0) { goto label_2501_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2501_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"dragon"s) { goto label_2501_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(203), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2501_internal; }
    }
    dbsum += 30000 / (500 + abs((objlv - 32)) * 400) + 1;
    dblist(0, dbmax) = 120;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2501_internal:
    if (40 > objlv) { goto label_2502_internal; }
    if (fltselect != 0) { goto label_2502_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2502_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"dragon"s) { goto label_2502_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(204), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2502_internal; }
    }
    dbsum += 20000 / (500 + abs((objlv - 40)) * 400) + 1;
    dblist(0, dbmax) = 121;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2502_internal:
    if (40 > objlv) { goto label_2503_internal; }
    if (fltselect != 0) { goto label_2503_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2503_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"dragon"s) { goto label_2503_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(205), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2503_internal; }
    }
    dbsum += 20000 / (500 + abs((objlv - 40)) * 400) + 1;
    dblist(0, dbmax) = 122;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2503_internal:
    if (40 > objlv) { goto label_2504_internal; }
    if (fltselect != 0) { goto label_2504_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2504_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"dragon"s) { goto label_2504_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(206), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2504_internal; }
    }
    dbsum += 20000 / (500 + abs((objlv - 40)) * 400) + 1;
    dblist(0, dbmax) = 123;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2504_internal:
    if (45 > objlv) { goto label_2505_internal; }
    if (fltselect != 0) { goto label_2505_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2505_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"dragon"s) { goto label_2505_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(207), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2505_internal; }
    }
    dbsum += 10000 / (500 + abs((objlv - 45)) * 400) + 1;
    dblist(0, dbmax) = 124;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2505_internal:
    if (50 > objlv) { goto label_2506_internal; }
    if (fltselect != 0) { goto label_2506_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2506_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"dragon"s) { goto label_2506_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(208), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2506_internal; }
    }
    dbsum += 10000 / (500 + abs((objlv - 50)) * 400) + 1;
    dblist(0, dbmax) = 125;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2506_internal:
    if (23 > objlv) { goto label_2507_internal; }
    if (fltselect != 0) { goto label_2507_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2507_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"cerberus"s) { goto label_2507_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(209), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2507_internal; }
    }
    dbsum += 40000 / (500 + abs((objlv - 23)) * 400) + 1;
    dblist(0, dbmax) = 126;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2507_internal:
    if (4 > objlv) { goto label_2508_internal; }
    if (fltselect != 0) { goto label_2508_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2508_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"centipede"s) { goto label_2508_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(210), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2508_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 4)) * 400) + 1;
    dblist(0, dbmax) = 255;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2508_internal:
    if (24 > objlv) { goto label_2509_internal; }
    if (fltselect != 0) { goto label_2509_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2509_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"centipede"s) { goto label_2509_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(211), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2509_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 24)) * 400) + 1;
    dblist(0, dbmax) = 256;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2509_internal:
    if (3 > objlv) { goto label_2510_internal; }
    if (fltselect != 0) { goto label_2510_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 6) { goto label_2510_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"spider"s) { goto label_2510_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(212), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2510_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 3)) * 400) + 1;
    dblist(0, dbmax) = 127;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2510_internal:
    if (11 > objlv) { goto label_2511_internal; }
    if (fltselect != 0) { goto label_2511_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 6) { goto label_2511_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"spider"s) { goto label_2511_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(213), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2511_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 11)) * 400) + 1;
    dblist(0, dbmax) = 128;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2511_internal:
    if (21 > objlv) { goto label_2512_internal; }
    if (fltselect != 0) { goto label_2512_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 6) { goto label_2512_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"spider"s) { goto label_2512_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(214), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2512_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 21)) * 400) + 1;
    dblist(0, dbmax) = 129;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2512_internal:
    if (15 > objlv) { goto label_2513_internal; }
    if (fltselect != 0) { goto label_2513_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 6) { goto label_2513_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"spider"s) { goto label_2513_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(215), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2513_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 15)) * 400) + 1;
    dblist(0, dbmax) = 130;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2513_internal:
    if (28 > objlv) { goto label_2514_internal; }
    if (fltselect != 0) { goto label_2514_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 6) { goto label_2514_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"spider"s) { goto label_2514_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(216), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2514_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 28)) * 400) + 1;
    dblist(0, dbmax) = 131;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2514_internal:
    if (13 > objlv) { goto label_2515_internal; }
    if (fltselect != 0) { goto label_2515_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2515_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"golem"s) { goto label_2515_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(217), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2515_internal; }
    }
    dbsum += 40000 / (500 + abs((objlv - 13)) * 400) + 1;
    dblist(0, dbmax) = 132;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2515_internal:
    if (19 > objlv) { goto label_2516_internal; }
    if (fltselect != 0) { goto label_2516_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2516_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"golem"s) { goto label_2516_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(218), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2516_internal; }
    }
    dbsum += 40000 / (500 + abs((objlv - 19)) * 400) + 1;
    dblist(0, dbmax) = 133;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2516_internal:
    if (25 > objlv) { goto label_2517_internal; }
    if (fltselect != 0) { goto label_2517_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2517_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"golem"s) { goto label_2517_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(219), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2517_internal; }
    }
    dbsum += 40000 / (500 + abs((objlv - 25)) * 400) + 1;
    dblist(0, dbmax) = 134;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2517_internal:
    if (30 > objlv) { goto label_2518_internal; }
    if (fltselect != 0) { goto label_2518_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2518_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"golem"s) { goto label_2518_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(220), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2518_internal; }
    }
    dbsum += 30000 / (500 + abs((objlv - 30)) * 400) + 1;
    dblist(0, dbmax) = 135;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2518_internal:
    if (35 > objlv) { goto label_2519_internal; }
    if (fltselect != 0) { goto label_2519_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2519_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"golem"s) { goto label_2519_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(221), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2519_internal; }
    }
    dbsum += 20000 / (500 + abs((objlv - 35)) * 400) + 1;
    dblist(0, dbmax) = 136;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2519_internal:
    if (40 > objlv) { goto label_2520_internal; }
    if (fltselect != 0) { goto label_2520_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2520_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"golem"s) { goto label_2520_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(222), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2520_internal; }
    }
    dbsum += 15000 / (500 + abs((objlv - 40)) * 400) + 1;
    dblist(0, dbmax) = 137;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2520_internal:
    if (50 > objlv) { goto label_2521_internal; }
    if (fltselect != 0) { goto label_2521_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2521_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"golem"s) { goto label_2521_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(223), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2521_internal; }
    }
    dbsum += 15000 / (500 + abs((objlv - 50)) * 400) + 1;
    dblist(0, dbmax) = 138;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2521_internal:
    if (16 > objlv) { goto label_2522_internal; }
    if (fltselect != 0) { goto label_2522_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2522_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"crab"s) { goto label_2522_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(224), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2522_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 16)) * 400) + 1;
    dblist(0, dbmax) = 147;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2522_internal:
    if (18 > objlv) { goto label_2523_internal; }
    if (fltselect != 0) { goto label_2523_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2523_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"centipede"s) { goto label_2523_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(225), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2523_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 18)) * 400) + 1;
    dblist(0, dbmax) = 148;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2523_internal:
    if (20 > objlv) { goto label_2524_internal; }
    if (fltselect != 0) { goto label_2524_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2524_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"goblin"s) { goto label_2524_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(226), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2524_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 20)) * 400) + 1;
    dblist(0, dbmax) = 149;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2524_internal:
    if (12 > objlv) { goto label_2525_internal; }
    if (fltselect != 0) { goto label_2525_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 9) { goto label_2525_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"skeleton"s) { goto label_2525_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(227), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2525_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 12)) * 400) + 1;
    dblist(0, dbmax) = 150;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2525_internal:
    if (20 > objlv) { goto label_2526_internal; }
    if (fltselect != 0) { goto label_2526_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 9) { goto label_2526_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"skeleton"s) { goto label_2526_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(228), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2526_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 20)) * 400) + 1;
    dblist(0, dbmax) = 151;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2526_internal:
    if (20 > objlv) { goto label_2527_internal; }
    if (fltselect != 0) { goto label_2527_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 9) { goto label_2527_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"eulderna"s) { goto label_2527_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(229), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2527_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 20)) * 400) + 1;
    dblist(0, dbmax) = 152;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2527_internal:
    if (12 > objlv) { goto label_2528_internal; }
    if (fltselect != 0) { goto label_2528_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2528_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"piece"s) { goto label_2528_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(230), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2528_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 12)) * 400) + 1;
    dblist(0, dbmax) = 153;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2528_internal:
    if (16 > objlv) { goto label_2529_internal; }
    if (fltselect != 0) { goto label_2529_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2529_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"piece"s) { goto label_2529_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(231), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2529_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 16)) * 400) + 1;
    dblist(0, dbmax) = 154;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2529_internal:
    if (18 > objlv) { goto label_2530_internal; }
    if (fltselect != 0) { goto label_2530_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2530_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"piece"s) { goto label_2530_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(232), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2530_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 18)) * 400) + 1;
    dblist(0, dbmax) = 155;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2530_internal:
    if (18 > objlv) { goto label_2531_internal; }
    if (fltselect != 0) { goto label_2531_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2531_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"piece"s) { goto label_2531_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(233), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2531_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 18)) * 400) + 1;
    dblist(0, dbmax) = 156;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2531_internal:
    if (22 > objlv) { goto label_2532_internal; }
    if (fltselect != 0) { goto label_2532_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2532_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"piece"s) { goto label_2532_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(234), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2532_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 22)) * 400) + 1;
    dblist(0, dbmax) = 157;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2532_internal:
    if (22 > objlv) { goto label_2533_internal; }
    if (fltselect != 0) { goto label_2533_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2533_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"piece"s) { goto label_2533_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(235), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2533_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 22)) * 400) + 1;
    dblist(0, dbmax) = 158;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2533_internal:
    if (20 > objlv) { goto label_2534_internal; }
    if (fltselect != 0) { goto label_2534_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 8) { goto label_2534_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2534_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(236), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2534_internal; }
    }
    dbsum += 25000 / (500 + abs((objlv - 20)) * 400) + 1;
    dblist(0, dbmax) = 159;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2534_internal:
    if (20 > objlv) { goto label_2535_internal; }
    if (fltselect != 0) { goto label_2535_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 8) { goto label_2535_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2535_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(237), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2535_internal; }
    }
    dbsum += 25000 / (500 + abs((objlv - 20)) * 400) + 1;
    dblist(0, dbmax) = 160;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2535_internal:
    if (20 > objlv) { goto label_2536_internal; }
    if (fltselect != 0) { goto label_2536_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 8) { goto label_2536_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2536_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(238), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2536_internal; }
    }
    dbsum += 25000 / (500 + abs((objlv - 20)) * 400) + 1;
    dblist(0, dbmax) = 161;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2536_internal:
    if (12 > objlv) { goto label_2537_internal; }
    if (fltselect != 3) { goto label_2537_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2537_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"juere"s) { goto label_2537_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(239), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2537_internal; }
    }
    dbsum += 25000 / (500 + abs((objlv - 12)) * 400) + 1;
    dblist(0, dbmax) = 302;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2537_internal:
    if (10 > objlv) { goto label_2538_internal; }
    if (fltselect != 0) { goto label_2538_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2538_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"juere"s) { goto label_2538_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(240), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2538_internal; }
    }
    dbsum += 25000 / (500 + abs((objlv - 10)) * 400) + 1;
    dblist(0, dbmax) = 303;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2538_internal:
    if (10 > objlv) { goto label_2539_internal; }
    if (fltselect != 0) { goto label_2539_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2539_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"juere"s) { goto label_2539_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(241), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2539_internal; }
    }
    dbsum += 25000 / (500 + abs((objlv - 10)) * 400) + 1;
    dblist(0, dbmax) = 304;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2539_internal:
    if (10 > objlv) { goto label_2540_internal; }
    if (fltselect != 0) { goto label_2540_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2540_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"juere"s) { goto label_2540_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(242), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2540_internal; }
    }
    dbsum += 25000 / (500 + abs((objlv - 10)) * 400) + 1;
    dblist(0, dbmax) = 305;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2540_internal:
    if (5 > objlv) { goto label_2541_internal; }
    if (fltselect != 0) { goto label_2541_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2541_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"yerles"s) { goto label_2541_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(243), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2541_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 5)) * 400) + 1;
    dblist(0, dbmax) = 162;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2541_internal:
    if (22 > objlv) { goto label_2542_internal; }
    if (fltselect != 0) { goto label_2542_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2542_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"yerles"s) { goto label_2542_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(244), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2542_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 22)) * 400) + 1;
    dblist(0, dbmax) = 234;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2542_internal:
    if (45 > objlv) { goto label_2543_internal; }
    if (fltselect != 3) { goto label_2543_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2543_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"juere"s) { goto label_2543_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(245), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2543_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 45)) * 400) + 1;
    dblist(0, dbmax) = 231;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2543_internal:
    if (17 > objlv) { goto label_2544_internal; }
    if (fltselect != 0) { goto label_2544_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2544_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"yerles"s) { goto label_2544_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(246), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2544_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 17)) * 400) + 1;
    dblist(0, dbmax) = 232;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2544_internal:
    if (7 > objlv) { goto label_2545_internal; }
    if (fltselect != 0) { goto label_2545_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2545_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"juere"s) { goto label_2545_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(247), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2545_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 7)) * 400) + 1;
    dblist(0, dbmax) = 233;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2545_internal:
    if (15 > objlv) { goto label_2546_internal; }
    if (fltselect != 0) { goto label_2546_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2546_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"juere"s) { goto label_2546_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(248), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2546_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 15)) * 400) + 1;
    dblist(0, dbmax) = 235;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2546_internal:
    if (9 > objlv) { goto label_2547_internal; }
    if (fltselect != 0) { goto label_2547_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2547_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"yerles"s) { goto label_2547_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(249), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2547_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 9)) * 400) + 1;
    dblist(0, dbmax) = 163;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2547_internal:
    if (4 > objlv) { goto label_2548_internal; }
    if (fltselect != 0) { goto label_2548_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2548_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"cat"s) { goto label_2548_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(250), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2548_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 4)) * 400) + 1;
    dblist(0, dbmax) = 164;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2548_internal:
    if (3 > objlv) { goto label_2549_internal; }
    if (fltselect != 0) { goto label_2549_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2549_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"cat"s) { goto label_2549_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(251), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2549_internal; }
    }
    dbsum += 1000 / (500 + abs((objlv - 3)) * 0) + 1;
    dblist(0, dbmax) = 246;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2549_internal:
    if (9 > objlv) { goto label_2550_internal; }
    if (fltselect != 0) { goto label_2550_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2550_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"cat"s) { goto label_2550_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(252), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2550_internal; }
    }
    dbsum += 10000 / (500 + abs((objlv - 9)) * 0) + 1;
    dblist(0, dbmax) = 332;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2550_internal:
    if (18 > objlv) { goto label_2551_internal; }
    if (fltselect != 0) { goto label_2551_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 10) { goto label_2551_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"cat"s) { goto label_2551_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(253), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2551_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 18)) * 400) + 1;
    dblist(0, dbmax) = 229;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2551_internal:
    if (25 > objlv) { goto label_2552_internal; }
    if (fltselect != 3) { goto label_2552_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2552_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"catgod"s) { goto label_2552_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(254), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2552_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 25)) * 400) + 1;
    dblist(0, dbmax) = 230;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2552_internal:
    if (20 > objlv) { goto label_2553_internal; }
    if (fltselect != 0) { goto label_2553_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2553_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"cat"s) { goto label_2553_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(255), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2553_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 20)) * 400) + 1;
    dblist(0, dbmax) = 228;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2553_internal:
    if (4 > objlv) { goto label_2554_internal; }
    if (fltselect != 0) { goto label_2554_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 10) { goto label_2554_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"dog"s) { goto label_2554_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(256), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2554_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 4)) * 400) + 1;
    dblist(0, dbmax) = 165;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2554_internal:
    if (1 > objlv) { goto label_2555_internal; }
    if (fltselect != 3) { goto label_2555_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2555_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"dog"s) { goto label_2555_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(257), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2555_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 1)) * 400) + 1;
    dblist(0, dbmax) = 225;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2555_internal:
    if (4 > objlv) { goto label_2556_internal; }
    if (fltselect != 3) { goto label_2556_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2556_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"roran"s) { goto label_2556_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(258), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2556_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 4)) * 400) + 1;
    dblist(0, dbmax) = 226;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2556_internal:
    if (5 > objlv) { goto label_2557_internal; }
    if (fltselect != 3) { goto label_2557_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2557_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2557_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(259), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2557_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 5)) * 400) + 1;
    dblist(0, dbmax) = 227;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2557_internal:
    if (4 > objlv) { goto label_2558_internal; }
    if (fltselect != 0) { goto label_2558_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2558_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"roran"s) { goto label_2558_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(260), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2558_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 4)) * 400) + 1;
    dblist(0, dbmax) = 166;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2558_internal:
    if (1 > objlv) { goto label_2559_internal; }
    if (fltselect != 0) { goto label_2559_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2559_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"rat"s) { goto label_2559_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(261), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2559_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 1)) * 400) + 1;
    dblist(0, dbmax) = 167;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2559_internal:
    if (1 > objlv) { goto label_2560_internal; }
    if (fltselect != 0) { goto label_2560_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2560_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"shell"s) { goto label_2560_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(262), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2560_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 1)) * 400) + 1;
    dblist(0, dbmax) = 168;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2560_internal:
    if (1 > objlv) { goto label_2561_internal; }
    if (fltselect != 0) { goto label_2561_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2561_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"yerles"s) { goto label_2561_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(263), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2561_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 1)) * 400) + 1;
    dblist(0, dbmax) = 170;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2561_internal:
    if (80 > objlv) { goto label_2562_internal; }
    if (fltselect != 3) { goto label_2562_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2562_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"catgod"s) { goto label_2562_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(264), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2562_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 80)) * 400) + 1;
    dblist(0, dbmax) = 175;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2562_internal:
    if (1 > objlv) { goto label_2563_internal; }
    if (fltselect != 1) { goto label_2563_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2563_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"roran"s) { goto label_2563_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(265), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2563_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 1)) * 400) + 1;
    dblist(0, dbmax) = 176;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2563_internal:
    if (50 > objlv) { goto label_2564_internal; }
    if (fltselect != 1) { goto label_2564_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2564_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"roran"s) { goto label_2564_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(266), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2564_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 50)) * 400) + 1;
    dblist(0, dbmax) = 249;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2564_internal:
    if (1 > objlv) { goto label_2565_internal; }
    if (fltselect != 1) { goto label_2565_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2565_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"catsister"s) { goto label_2565_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(267), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2565_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 1)) * 400) + 1;
    dblist(0, dbmax) = 210;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2565_internal:
    if (1 > objlv) { goto label_2566_internal; }
    if (fltselect != 1) { goto label_2566_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2566_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"roran"s) { goto label_2566_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(268), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2566_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 1)) * 400) + 1;
    dblist(0, dbmax) = 211;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2566_internal:
    if (80 > objlv) { goto label_2567_internal; }
    if (fltselect != 3) { goto label_2567_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2567_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"machinegod"s) { goto label_2567_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(269), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2567_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 80)) * 400) + 1;
    dblist(0, dbmax) = 177;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2567_internal:
    if (80 > objlv) { goto label_2568_internal; }
    if (fltselect != 3) { goto label_2568_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2568_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"undeadgod"s) { goto label_2568_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(270), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2568_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 80)) * 400) + 1;
    dblist(0, dbmax) = 178;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2568_internal:
    if (35 > objlv) { goto label_2569_internal; }
    if (fltselect != 1) { goto label_2569_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2569_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2569_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(271), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2569_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 35)) * 400) + 1;
    dblist(0, dbmax) = 179;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2569_internal:
    if (45 > objlv) { goto label_2570_internal; }
    if (fltselect != 3) { goto label_2570_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2570_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"dwarf"s) { goto label_2570_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(272), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2570_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 45)) * 400) + 1;
    dblist(0, dbmax) = 208;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2570_internal:
    if (45 > objlv) { goto label_2571_internal; }
    if (fltselect != 3) { goto label_2571_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2571_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"dwarf"s) { goto label_2571_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(273), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2571_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 45)) * 400) + 1;
    dblist(0, dbmax) = 209;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2571_internal:
    if (1 > objlv) { goto label_2572_internal; }
    if (fltselect != 4) { goto label_2572_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2572_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"cat"s) { goto label_2572_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(274), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2572_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 1)) * 400) + 1;
    dblist(0, dbmax) = 180;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2572_internal:
    if (10 > objlv) { goto label_2573_internal; }
    if (fltselect != 4) { goto label_2573_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2573_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"hound"s) { goto label_2573_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(275), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2573_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 10)) * 400) + 1;
    dblist(0, dbmax) = 181;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2573_internal:
    if (8 > objlv) { goto label_2574_internal; }
    if (fltselect != 0) { goto label_2574_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2574_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2574_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(276), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2574_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 8)) * 400) + 1;
    dblist(0, dbmax) = 182;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2574_internal:
    if (15 > objlv) { goto label_2575_internal; }
    if (fltselect != 7) { goto label_2575_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2575_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2575_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(277), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2575_internal; }
    }
    dbsum += 20000 / (500 + abs((objlv - 15)) * 400) + 1;
    dblist(0, dbmax) = 183;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2575_internal:
    if (9 > objlv) { goto label_2576_internal; }
    if (fltselect != 7) { goto label_2576_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2576_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2576_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(278), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2576_internal; }
    }
    dbsum += 40000 / (500 + abs((objlv - 9)) * 400) + 1;
    dblist(0, dbmax) = 184;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2576_internal:
    if (20 > objlv) { goto label_2577_internal; }
    if (fltselect != 7) { goto label_2577_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2577_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"yerles"s) { goto label_2577_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(279), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2577_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 20)) * 400) + 1;
    dblist(0, dbmax) = 185;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2577_internal:
    if (10 > objlv) { goto label_2578_internal; }
    if (fltselect != 1) { goto label_2578_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2578_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"yerles"s) { goto label_2578_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(280), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2578_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 10)) * 400) + 1;
    dblist(0, dbmax) = 350;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2578_internal:
    if (5 > objlv) { goto label_2579_internal; }
    if (fltselect != 0) { goto label_2579_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2579_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"machine"s) { goto label_2579_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(281), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2579_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 5)) * 400) + 1;
    dblist(0, dbmax) = 186;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2579_internal:
    if (13 > objlv) { goto label_2580_internal; }
    if (fltselect != 0) { goto label_2580_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2580_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"machine"s) { goto label_2580_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(282), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2580_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 13)) * 400) + 1;
    dblist(0, dbmax) = 187;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2580_internal:
    if (30 > objlv) { goto label_2581_internal; }
    if (fltselect != 0) { goto label_2581_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2581_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"machine"s) { goto label_2581_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(283), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2581_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 30)) * 400) + 1;
    dblist(0, dbmax) = 188;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2581_internal:
    if (22 > objlv) { goto label_2582_internal; }
    if (fltselect != 3) { goto label_2582_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2582_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"bike"s) { goto label_2582_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(284), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2582_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 22)) * 400) + 1;
    dblist(0, dbmax) = 345;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2582_internal:
    if (8 > objlv) { goto label_2583_internal; }
    if (fltselect != 0) { goto label_2583_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2583_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"bike"s) { goto label_2583_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(285), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2583_internal; }
    }
    dbsum += 5000 / (500 + abs((objlv - 8)) * 400) + 1;
    dblist(0, dbmax) = 346;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2583_internal:
    if (15 > objlv) { goto label_2584_internal; }
    if (fltselect != 0) { goto label_2584_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2584_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"machine"s) { goto label_2584_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(286), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2584_internal; }
    }
    dbsum += 25000 / (500 + abs((objlv - 15)) * 400) + 1;
    dblist(0, dbmax) = 341;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2584_internal:
    if (25 > objlv) { goto label_2585_internal; }
    if (fltselect != 0) { goto label_2585_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2585_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"machine"s) { goto label_2585_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(287), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2585_internal; }
    }
    dbsum += 50000 / (500 + abs((objlv - 25)) * 400) + 1;
    dblist(0, dbmax) = 258;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2585_internal:
    if (8 > objlv) { goto label_2586_internal; }
    if (fltselect != 0) { goto label_2586_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2586_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"eye"s) { goto label_2586_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(288), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2586_internal; }
    }
    dbsum += 60000 / (500 + abs((objlv - 8)) * 400) + 1;
    dblist(0, dbmax) = 189;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2586_internal:
    if (19 > objlv) { goto label_2587_internal; }
    if (fltselect != 0) { goto label_2587_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2587_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"eye"s) { goto label_2587_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(289), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2587_internal; }
    }
    dbsum += 60000 / (500 + abs((objlv - 19)) * 400) + 1;
    dblist(0, dbmax) = 190;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2587_internal:
    if (14 > objlv) { goto label_2588_internal; }
    if (fltselect != 0) { goto label_2588_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2588_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"wisp"s) { goto label_2588_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(290), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2588_internal; }
    }
    dbsum += 50000 / (500 + abs((objlv - 14)) * 400) + 1;
    dblist(0, dbmax) = 191;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2588_internal:
    if (5 > objlv) { goto label_2589_internal; }
    if (fltselect != 0) { goto label_2589_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2589_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"crab"s) { goto label_2589_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(291), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2589_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 5)) * 400) + 1;
    dblist(0, dbmax) = 192;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2589_internal:
    if (15 > objlv) { goto label_2590_internal; }
    if (fltselect != 0) { goto label_2590_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2590_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"crab"s) { goto label_2590_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(292), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2590_internal; }
    }
    dbsum += 70000 / (500 + abs((objlv - 15)) * 400) + 1;
    dblist(0, dbmax) = 193;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2590_internal:
    if (1 > objlv) { goto label_2591_internal; }
    if (fltselect != 0) { goto label_2591_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2591_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"chicken"s) { goto label_2591_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(293), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2591_internal; }
    }
    dbsum += 30000 / (500 + abs((objlv - 1)) * 400) + 1;
    dblist(0, dbmax) = 195;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2591_internal:
    if (7 > objlv) { goto label_2592_internal; }
    if (fltselect != 0) { goto label_2592_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2592_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"mandrake"s) { goto label_2592_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(294), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2592_internal; }
    }
    dbsum += 60000 / (500 + abs((objlv - 7)) * 400) + 1;
    dblist(0, dbmax) = 196;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2592_internal:
    if (5 > objlv) { goto label_2593_internal; }
    if (fltselect != 0) { goto label_2593_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2593_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"mandrake"s) { goto label_2593_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(295), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2593_internal; }
    }
    dbsum += 20000 / (500 + abs((objlv - 5)) * 400) + 1;
    dblist(0, dbmax) = 201;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2593_internal:
    if (18 > objlv) { goto label_2594_internal; }
    if (fltselect != 0) { goto label_2594_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2594_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"mandrake"s) { goto label_2594_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(296), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2594_internal; }
    }
    dbsum += 60000 / (500 + abs((objlv - 18)) * 400) + 1;
    dblist(0, dbmax) = 197;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2594_internal:
    if (30 > objlv) { goto label_2595_internal; }
    if (fltselect != 0) { goto label_2595_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2595_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"mandrake"s) { goto label_2595_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(297), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2595_internal; }
    }
    dbsum += 60000 / (500 + abs((objlv - 30)) * 400) + 1;
    dblist(0, dbmax) = 198;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2595_internal:
    if (12 > objlv) { goto label_2596_internal; }
    if (fltselect != 0) { goto label_2596_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2596_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"stalker"s) { goto label_2596_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(298), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2596_internal; }
    }
    dbsum += 30000 / (500 + abs((objlv - 12)) * 400) + 1;
    dblist(0, dbmax) = 199;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2596_internal:
    if (26 > objlv) { goto label_2597_internal; }
    if (fltselect != 0) { goto label_2597_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2597_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"stalker"s) { goto label_2597_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(299), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2597_internal; }
    }
    dbsum += 30000 / (500 + abs((objlv - 26)) * 400) + 1;
    dblist(0, dbmax) = 200;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2597_internal:
    if (80 > objlv) { goto label_2598_internal; }
    if (fltselect != 3) { goto label_2598_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2598_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"giant"s) { goto label_2598_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(300), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2598_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 80)) * 400) + 1;
    dblist(0, dbmax) = 202;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2598_internal:
    if (10 > objlv) { goto label_2599_internal; }
    if (fltselect != 1) { goto label_2599_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2599_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2599_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(301), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2599_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 10)) * 400) + 1;
    dblist(0, dbmax) = 203;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2599_internal:
    if (1 > objlv) { goto label_2600_internal; }
    if (fltselect != 1) { goto label_2600_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2600_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"yerles"s) { goto label_2600_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(302), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2600_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 1)) * 400) + 1;
    dblist(0, dbmax) = 205;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2600_internal:
    if (30 > objlv) { goto label_2601_internal; }
    if (fltselect != 3) { goto label_2601_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2601_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"giant"s) { goto label_2601_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(303), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2601_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 30)) * 400) + 1;
    dblist(0, dbmax) = 207;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2601_internal:
    if (1 > objlv) { goto label_2602_internal; }
    if (fltselect != 3) { goto label_2602_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2602_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"juere"s) { goto label_2602_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(304), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2602_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 1)) * 400) + 1;
    dblist(0, dbmax) = 212;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2602_internal:
    if (1 > objlv) { goto label_2603_internal; }
    if (fltselect != 3) { goto label_2603_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2603_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"roran"s) { goto label_2603_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(305), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2603_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 1)) * 400) + 1;
    dblist(0, dbmax) = 213;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2603_internal:
    if (10 > objlv) { goto label_2604_internal; }
    if (fltselect != 3) { goto label_2604_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2604_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"roran"s) { goto label_2604_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(306), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2604_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 10)) * 400) + 1;
    dblist(0, dbmax) = 221;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2604_internal:
    if (15 > objlv) { goto label_2605_internal; }
    if (fltselect != 3) { goto label_2605_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2605_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"roran"s) { goto label_2605_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(307), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2605_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 15)) * 400) + 1;
    dblist(0, dbmax) = 222;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2605_internal:
    if (10 > objlv) { goto label_2606_internal; }
    if (fltselect != 3) { goto label_2606_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2606_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2606_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(308), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2606_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 10)) * 400) + 1;
    dblist(0, dbmax) = 223;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2606_internal:
    if (7 > objlv) { goto label_2607_internal; }
    if (fltselect != 3) { goto label_2607_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2607_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2607_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(309), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2607_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 7)) * 400) + 1;
    dblist(0, dbmax) = 224;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2607_internal:
    if (15 > objlv) { goto label_2608_internal; }
    if (fltselect != 3) { goto label_2608_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2608_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2608_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(310), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2608_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 15)) * 400) + 1;
    dblist(0, dbmax) = 243;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2608_internal:
    if (4 > objlv) { goto label_2609_internal; }
    if (fltselect != 3) { goto label_2609_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2609_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2609_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(311), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2609_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 4)) * 400) + 1;
    dblist(0, dbmax) = 247;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2609_internal:
    if (45 > objlv) { goto label_2610_internal; }
    if (fltselect != 3) { goto label_2610_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2610_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2610_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(312), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2610_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 45)) * 400) + 1;
    dblist(0, dbmax) = 252;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2610_internal:
    if (25 > objlv) { goto label_2611_internal; }
    if (fltselect != 3) { goto label_2611_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2611_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"juere"s) { goto label_2611_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(313), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2611_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 25)) * 400) + 1;
    dblist(0, dbmax) = 253;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2611_internal:
    if (20 > objlv) { goto label_2612_internal; }
    if (fltselect != 3) { goto label_2612_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2612_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"juere"s) { goto label_2612_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(314), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2612_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 20)) * 400) + 1;
    dblist(0, dbmax) = 259;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2612_internal:
    if (38 > objlv) { goto label_2613_internal; }
    if (fltselect != 3) { goto label_2613_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2613_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2613_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(315), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2613_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 38)) * 400) + 1;
    dblist(0, dbmax) = 301;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2613_internal:
    if (2 > objlv) { goto label_2614_internal; }
    if (fltselect != 0) { goto label_2614_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2614_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"juere"s) { goto label_2614_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(316), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2614_internal; }
    }
    dbsum += 30000 / (500 + abs((objlv - 2)) * 400) + 1;
    dblist(0, dbmax) = 214;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2614_internal:
    if (5 > objlv) { goto label_2615_internal; }
    if (fltselect != 0) { goto label_2615_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2615_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"juere"s) { goto label_2615_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(317), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2615_internal; }
    }
    dbsum += 30000 / (500 + abs((objlv - 5)) * 400) + 1;
    dblist(0, dbmax) = 215;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2615_internal:
    if (35 > objlv) { goto label_2616_internal; }
    if (fltselect != 0) { goto label_2616_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2616_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"juere"s) { goto label_2616_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(318), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2616_internal; }
    }
    dbsum += 30000 / (500 + abs((objlv - 35)) * 400) + 1;
    dblist(0, dbmax) = 217;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2616_internal:
    if (50 > objlv) { goto label_2617_internal; }
    if (fltselect != 0) { goto label_2617_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2617_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"yith"s) { goto label_2617_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(319), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2617_internal; }
    }
    dbsum += 20000 / (500 + abs((objlv - 50)) * 400) + 1;
    dblist(0, dbmax) = 216;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2617_internal:
    if (45 > objlv) { goto label_2618_internal; }
    if (fltselect != 0) { goto label_2618_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2618_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"yith"s) { goto label_2618_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(320), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2618_internal; }
    }
    dbsum += 40000 / (500 + abs((objlv - 45)) * 400) + 1;
    dblist(0, dbmax) = 218;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2618_internal:
    if (38 > objlv) { goto label_2619_internal; }
    if (fltselect != 0) { goto label_2619_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2619_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"orc"s) { goto label_2619_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(321), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2619_internal; }
    }
    dbsum += 80000 / (500 + abs((objlv - 38)) * 400) + 1;
    dblist(0, dbmax) = 219;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2619_internal:
    if (65 > objlv) { goto label_2620_internal; }
    if (fltselect != 0) { goto label_2620_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2620_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"yith"s) { goto label_2620_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(322), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2620_internal; }
    }
    dbsum += 30000 / (500 + abs((objlv - 65)) * 400) + 1;
    dblist(0, dbmax) = 220;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2620_internal:
    if (13 > objlv) { goto label_2621_internal; }
    if (fltselect != 0) { goto label_2621_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2621_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"fairy"s) { goto label_2621_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(323), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2621_internal; }
    }
    dbsum += 50000 / (500 + abs((objlv - 13)) * 400) + 1;
    dblist(0, dbmax) = 250;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2621_internal:
    if (8 > objlv) { goto label_2622_internal; }
    if (fltselect != 3) { goto label_2622_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2622_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"servant"s) { goto label_2622_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(324), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2622_internal; }
    }
    dbsum += 50000 / (500 + abs((objlv - 8)) * 400) + 1;
    dblist(0, dbmax) = 260;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2622_internal:
    if (8 > objlv) { goto label_2623_internal; }
    if (fltselect != 3) { goto label_2623_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2623_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"servant"s) { goto label_2623_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(325), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2623_internal; }
    }
    dbsum += 50000 / (500 + abs((objlv - 8)) * 400) + 1;
    dblist(0, dbmax) = 261;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2623_internal:
    if (8 > objlv) { goto label_2624_internal; }
    if (fltselect != 3) { goto label_2624_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2624_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"servant"s) { goto label_2624_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(326), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2624_internal; }
    }
    dbsum += 50000 / (500 + abs((objlv - 8)) * 400) + 1;
    dblist(0, dbmax) = 262;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2624_internal:
    if (8 > objlv) { goto label_2625_internal; }
    if (fltselect != 3) { goto label_2625_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2625_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"servant"s) { goto label_2625_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(327), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2625_internal; }
    }
    dbsum += 50000 / (500 + abs((objlv - 8)) * 400) + 1;
    dblist(0, dbmax) = 263;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2625_internal:
    if (8 > objlv) { goto label_2626_internal; }
    if (fltselect != 3) { goto label_2626_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2626_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"servant"s) { goto label_2626_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(328), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2626_internal; }
    }
    dbsum += 50000 / (500 + abs((objlv - 8)) * 400) + 1;
    dblist(0, dbmax) = 264;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2626_internal:
    if (8 > objlv) { goto label_2627_internal; }
    if (fltselect != 3) { goto label_2627_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2627_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"servant"s) { goto label_2627_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(329), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2627_internal; }
    }
    dbsum += 50000 / (500 + abs((objlv - 8)) * 400) + 1;
    dblist(0, dbmax) = 265;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2627_internal:
    if (8 > objlv) { goto label_2628_internal; }
    if (fltselect != 3) { goto label_2628_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2628_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"servant"s) { goto label_2628_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(330), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2628_internal; }
    }
    dbsum += 50000 / (500 + abs((objlv - 8)) * 400) + 1;
    dblist(0, dbmax) = 266;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2628_internal:
    if (1 > objlv) { goto label_2629_internal; }
    if (fltselect != 0) { goto label_2629_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2629_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"horse"s) { goto label_2629_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(331), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2629_internal; }
    }
    dbsum += 10000 / (500 + abs((objlv - 1)) * 400) + 1;
    dblist(0, dbmax) = 267;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2629_internal:
    if (4 > objlv) { goto label_2630_internal; }
    if (fltselect != 0) { goto label_2630_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2630_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"horse"s) { goto label_2630_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(332), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2630_internal; }
    }
    dbsum += 10000 / (500 + abs((objlv - 4)) * 400) + 1;
    dblist(0, dbmax) = 276;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2630_internal:
    if (10 > objlv) { goto label_2631_internal; }
    if (fltselect != 0) { goto label_2631_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2631_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"horse"s) { goto label_2631_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(333), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2631_internal; }
    }
    dbsum += 10000 / (500 + abs((objlv - 10)) * 400) + 1;
    dblist(0, dbmax) = 275;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2631_internal:
    if (15 > objlv) { goto label_2632_internal; }
    if (fltselect != 0) { goto label_2632_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2632_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"horse"s) { goto label_2632_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(334), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2632_internal; }
    }
    dbsum += 10000 / (500 + abs((objlv - 15)) * 400) + 1;
    dblist(0, dbmax) = 268;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2632_internal:
    if (20 > objlv) { goto label_2633_internal; }
    if (fltselect != 0) { goto label_2633_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2633_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"horse"s) { goto label_2633_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(335), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2633_internal; }
    }
    dbsum += 10000 / (500 + abs((objlv - 20)) * 400) + 1;
    dblist(0, dbmax) = 277;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2633_internal:
    if (6 > objlv) { goto label_2634_internal; }
    if (fltselect != 0) { goto label_2634_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2634_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"mutant"s) { goto label_2634_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(336), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2634_internal; }
    }
    dbsum += 70000 / (500 + abs((objlv - 6)) * 400) + 1;
    dblist(0, dbmax) = 278;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2634_internal:
    if (15 > objlv) { goto label_2635_internal; }
    if (fltselect != 3) { goto label_2635_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2635_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"yerles"s) { goto label_2635_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(337), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2635_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 15)) * 400) + 1;
    dblist(0, dbmax) = 279;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2635_internal:
    if (10 > objlv) { goto label_2636_internal; }
    if (fltselect != 3) { goto label_2636_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2636_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2636_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(338), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2636_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 10)) * 400) + 1;
    dblist(0, dbmax) = 280;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2636_internal:
    if (55 > objlv) { goto label_2637_internal; }
    if (fltselect != 3) { goto label_2637_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2637_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2637_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(339), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2637_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 55)) * 400) + 1;
    dblist(0, dbmax) = 288;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2637_internal:
    if (38 > objlv) { goto label_2638_internal; }
    if (fltselect != 3) { goto label_2638_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2638_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2638_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(340), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2638_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 38)) * 400) + 1;
    dblist(0, dbmax) = 290;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2638_internal:
    if (55 > objlv) { goto label_2639_internal; }
    if (fltselect != 3) { goto label_2639_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2639_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"juere"s) { goto label_2639_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(341), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2639_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 55)) * 400) + 1;
    dblist(0, dbmax) = 292;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2639_internal:
    if (38 > objlv) { goto label_2640_internal; }
    if (fltselect != 3) { goto label_2640_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2640_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"juere"s) { goto label_2640_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(342), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2640_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 38)) * 400) + 1;
    dblist(0, dbmax) = 294;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2640_internal:
    if (55 > objlv) { goto label_2641_internal; }
    if (fltselect != 3) { goto label_2641_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2641_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2641_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(343), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2641_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 55)) * 400) + 1;
    dblist(0, dbmax) = 291;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2641_internal:
    if (38 > objlv) { goto label_2642_internal; }
    if (fltselect != 3) { goto label_2642_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2642_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"norland"s) { goto label_2642_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(344), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2642_internal; }
    }
    dbsum += 100000 / (500 + abs((objlv - 38)) * 400) + 1;
    dblist(0, dbmax) = 297;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2642_internal:
    if (28 > objlv) { goto label_2643_internal; }
    if (fltselect != 0) { goto label_2643_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2643_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"roran"s) { goto label_2643_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(345), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2643_internal; }
    }
    dbsum += 50000 / (500 + abs((objlv - 28)) * 400) + 1;
    dblist(0, dbmax) = 317;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2643_internal:
    if (30 > objlv) { goto label_2644_internal; }
    if (fltselect != 3) { goto label_2644_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2644_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"machinegod"s) { goto label_2644_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(346), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2644_internal; }
    }
    dbsum += 50000 / (500 + abs((objlv - 30)) * 400) + 1;
    dblist(0, dbmax) = 318;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2644_internal:
    if (1 > objlv) { goto label_2645_internal; }
    if (fltselect != 3) { goto label_2645_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2645_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"mutant"s) { goto label_2645_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(347), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2645_internal; }
    }
    dbsum += 50000 / (500 + abs((objlv - 1)) * 400) + 1;
    dblist(0, dbmax) = 319;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2645_internal:
    if (15 > objlv) { goto label_2646_internal; }
    if (fltselect != 3) { goto label_2646_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2646_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"roran"s) { goto label_2646_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(348), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2646_internal; }
    }
    dbsum += 50000 / (500 + abs((objlv - 15)) * 400) + 1;
    dblist(0, dbmax) = 322;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2646_internal:
    if (7 > objlv) { goto label_2647_internal; }
    if (fltselect != 3) { goto label_2647_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2647_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"juere"s) { goto label_2647_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(349), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2647_internal; }
    }
    dbsum += 50000 / (500 + abs((objlv - 7)) * 400) + 1;
    dblist(0, dbmax) = 334;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2647_internal:
    if (12 > objlv) { goto label_2648_internal; }
    if (fltselect != 0) { goto label_2648_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2648_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"ghost"s) { goto label_2648_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(350), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2648_internal; }
    }
    dbsum += 10000 / (500 + abs((objlv - 12)) * 0) + 1;
    dblist(0, dbmax) = 323;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2648_internal:
    if (10 > objlv) { goto label_2649_internal; }
    if (fltselect != 0) { goto label_2649_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2649_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"quickling"s) { goto label_2649_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(351), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2649_internal; }
    }
    dbsum += 15000 / (500 + abs((objlv - 10)) * 400) + 1;
    dblist(0, dbmax) = 324;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2649_internal:
    if (17 > objlv) { goto label_2650_internal; }
    if (fltselect != 0) { goto label_2650_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2650_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"quickling"s) { goto label_2650_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(352), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2650_internal; }
    }
    dbsum += 15000 / (500 + abs((objlv - 17)) * 400) + 1;
    dblist(0, dbmax) = 325;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2650_internal:
    if (3 > objlv) { goto label_2651_internal; }
    if (fltselect != 0) { goto label_2651_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2651_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"metal"s) { goto label_2651_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(353), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2651_internal; }
    }
    dbsum += 2000 / (500 + abs((objlv - 3)) * 0) + 1;
    dblist(0, dbmax) = 328;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2651_internal:
    if (1 > objlv) { goto label_2652_internal; }
    if (fltselect != 0) { goto label_2652_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2652_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"metal"s) { goto label_2652_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(354), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2652_internal; }
    }
    dbsum += 5000 / (500 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 329;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2652_internal:
    if (19 > objlv) { goto label_2653_internal; }
    if (fltselect != 0) { goto label_2653_internal; }
    if (flttypemajor != 0) {
        if (flttypemajor != 0) { goto label_2653_internal; }
    }
    if (fltnrace != u8""s) {
        if (fltnrace != u8"dinosaur"s) { goto label_2653_internal; }
    }
    if (filtermax != 0) {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                if (instr(filter_creature(355), 0, filtern(cnt)) == -1) {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0) { goto label_2653_internal; }
    }
    dbsum += 40000 / (500 + abs((objlv - 19)) * 400) + 1;
    dblist(0, dbmax) = 330;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_2653_internal : {
    int cnt = 0;
    for (int cnt_end = cnt + (usernpcmax); cnt < cnt_end; ++cnt) {
        if (cmshade) { break; }
        if (fltselect != userdata(12, cnt)) { continue; }
        if (flttypemajor != 0) { continue; }
        if (fltnrace != u8""s) {
            if (fltnrace != userdatan(2, cnt)) { continue; }
        }
        if (userdata(2, cnt) > objlv) { continue; }
        if (filtermax != 0) {
            dbtmp = 1;
            dbtmp2 = cnt;
            {
                int cnt = 0;
                for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt) {
                    if (instr(userdatan(4, dbtmp2), 0, filtern(cnt)) == -1) {
                        dbtmp = 0;
                        break;
                    }
                }
            }
            if (dbtmp == 0) { continue; }
        }
        dbsum += limit(userdata(6, cnt), 1, 500) * 1000 /
                (500 + abs((objlv - userdata(2, cnt))) * 400) +
            1;
        unlist(dbmax) = cnt;
        dblist(0, dbmax) = 343;
        dblist(1, dbmax) = dbsum;
        ++dbmax;
    }
}
    if (dbsum != 0) {
        exrand_rnd(dbtmp, dbsum);
        {
            int cnt = 0;
            for (int cnt_end = cnt + (dbmax); cnt < cnt_end; ++cnt) {
                if (dblist(1, cnt) > dbtmp) {
                    dbid = dblist(0, cnt);
                    if (dbid == 343) { cdata(157, rc) = unlist(cnt); }
                    break;
                }
            }
        }
    } else {
        dbid = 0;
    }
    return;
}


} // namespace elona
