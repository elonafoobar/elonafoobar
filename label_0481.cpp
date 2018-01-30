#include "elona.hpp"
#include "variables.hpp"


namespace elona
{
void label_0481()
{
    if (dbmode != 1)
    {
        label_1275();
        return;
    }
    dbmax = 0;
    dbsum = 0;
    if (1 > objlv)
    {
        goto label_0482_internal;
    }
    if (fltselect != 1)
    {
        goto label_0482_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0482_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0482_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(792), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0482_internal;
        }
    }
    dbsum += 150000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 792;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0482_internal:
    if (55 > objlv)
    {
        goto label_0483_internal;
    }
    if (fltselect != 3)
    {
        goto label_0483_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_0483_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10001)
        {
            goto label_0483_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(791), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0483_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 55)) * 100) + 1;
    dblist(0, dbmax) = 791;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0483_internal:
    if (1 > objlv)
    {
        goto label_0484_internal;
    }
    if (fltselect != 0)
    {
        goto label_0484_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0484_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 59500)
        {
            goto label_0484_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(790), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0484_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 790;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0484_internal:
    if (1 > objlv)
    {
        goto label_0485_internal;
    }
    if (fltselect != 0)
    {
        goto label_0485_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0485_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 59500)
        {
            goto label_0485_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(789), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0485_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 789;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0485_internal:
    if (15 > objlv)
    {
        goto label_0486_internal;
    }
    if (fltselect != 0)
    {
        goto label_0486_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 24000)
        {
            goto label_0486_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 24001)
        {
            goto label_0486_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(788), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0486_internal;
        }
    }
    dbsum += 50000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 788;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0486_internal:
    if (3 > objlv)
    {
        goto label_0487_internal;
    }
    if (fltselect != 0)
    {
        goto label_0487_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0487_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0487_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(787), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0487_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 3)) * 100) + 1;
    dblist(0, dbmax) = 787;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0487_internal:
    if (1 > objlv)
    {
        goto label_0488_internal;
    }
    if (fltselect != 0)
    {
        goto label_0488_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0488_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0488_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(786), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0488_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 786;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0488_internal:
    if (1 > objlv)
    {
        goto label_0489_internal;
    }
    if (fltselect != 0)
    {
        goto label_0489_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0489_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0489_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(785), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0489_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 785;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0489_internal:
    if (1 > objlv)
    {
        goto label_0490_internal;
    }
    if (fltselect != 0)
    {
        goto label_0490_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 72000)
        {
            goto label_0490_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0490_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(784), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0490_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 784;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0490_internal:
    if (1 > objlv)
    {
        goto label_0491_internal;
    }
    if (fltselect != 0)
    {
        goto label_0491_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0491_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0491_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(783), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0491_internal;
        }
    }
    dbsum += 50000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 783;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0491_internal:
    if (1 > objlv)
    {
        goto label_0492_internal;
    }
    if (fltselect != 0)
    {
        goto label_0492_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0492_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0492_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(782), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0492_internal;
        }
    }
    dbsum += 250000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 782;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0492_internal:
    if (1 > objlv)
    {
        goto label_0493_internal;
    }
    if (fltselect != 0)
    {
        goto label_0493_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_0493_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10003)
        {
            goto label_0493_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(781), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0493_internal;
        }
    }
    dbsum += 50000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 781;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0493_internal:
    if (45 > objlv)
    {
        goto label_0494_internal;
    }
    if (fltselect != 0)
    {
        goto label_0494_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0494_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0494_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(780), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0494_internal;
        }
    }
    dbsum += 10000 / (1000 + abs((objlv - 45)) * 100) + 1;
    dblist(0, dbmax) = 780;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0494_internal:
    if (32 > objlv)
    {
        goto label_0495_internal;
    }
    if (fltselect != 0)
    {
        goto label_0495_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0495_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0495_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(779), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0495_internal;
        }
    }
    dbsum += 10000 / (1000 + abs((objlv - 32)) * 100) + 1;
    dblist(0, dbmax) = 779;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0495_internal:
    if (15 > objlv)
    {
        goto label_0496_internal;
    }
    if (fltselect != 0)
    {
        goto label_0496_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0496_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0496_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(778), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0496_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 778;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0496_internal:
    if (1 > objlv)
    {
        goto label_0497_internal;
    }
    if (fltselect != 3)
    {
        goto label_0497_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0497_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0497_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(777), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0497_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 777;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0497_internal:
    if (1 > objlv)
    {
        goto label_0498_internal;
    }
    if (fltselect != 3)
    {
        goto label_0498_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0498_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0498_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(776), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0498_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 776;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0498_internal:
    if (3 > objlv)
    {
        goto label_0499_internal;
    }
    if (fltselect != 0)
    {
        goto label_0499_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0499_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0499_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(775), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0499_internal;
        }
    }
    dbsum += 50000 / (1000 + abs((objlv - 3)) * 100) + 1;
    dblist(0, dbmax) = 775;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0499_internal:
    if (24 > objlv)
    {
        goto label_0500_internal;
    }
    if (fltselect != 0)
    {
        goto label_0500_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0500_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0500_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(774), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0500_internal;
        }
    }
    dbsum += 150000 / (1000 + abs((objlv - 24)) * 100) + 1;
    dblist(0, dbmax) = 774;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0500_internal:
    if (18 > objlv)
    {
        goto label_0501_internal;
    }
    if (fltselect != 0)
    {
        goto label_0501_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0501_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0501_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(773), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0501_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 18)) * 100) + 1;
    dblist(0, dbmax) = 773;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0501_internal:
    if (1 > objlv)
    {
        goto label_0502_internal;
    }
    if (fltselect != 0)
    {
        goto label_0502_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0502_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 57004)
        {
            goto label_0502_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(772), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0502_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 772;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0502_internal:
    if (1 > objlv)
    {
        goto label_0503_internal;
    }
    if (fltselect != 3)
    {
        goto label_0503_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0503_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0503_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(771), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0503_internal;
        }
    }
    dbsum += 5000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 771;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0503_internal:
    if (1 > objlv)
    {
        goto label_0504_internal;
    }
    if (fltselect != 1)
    {
        goto label_0504_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0504_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0504_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(770), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0504_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 770;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0504_internal:
    if (10 > objlv)
    {
        goto label_0505_internal;
    }
    if (fltselect != 1)
    {
        goto label_0505_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0505_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0505_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(769), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0505_internal;
        }
    }
    dbsum += 5000 / (1000 + abs((objlv - 10)) * 100) + 1;
    dblist(0, dbmax) = 769;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0505_internal:
    if (10 > objlv)
    {
        goto label_0506_internal;
    }
    if (fltselect != 1)
    {
        goto label_0506_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0506_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0506_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(768), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0506_internal;
        }
    }
    dbsum += 5000 / (1000 + abs((objlv - 10)) * 100) + 1;
    dblist(0, dbmax) = 768;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0506_internal:
    if (5 > objlv)
    {
        goto label_0507_internal;
    }
    if (fltselect != 1)
    {
        goto label_0507_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0507_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60004)
        {
            goto label_0507_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(767), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0507_internal;
        }
    }
    dbsum += 25000 / (1000 + abs((objlv - 5)) * 100) + 1;
    dblist(0, dbmax) = 767;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0507_internal:
    if (30 > objlv)
    {
        goto label_0508_internal;
    }
    if (fltselect != 0)
    {
        goto label_0508_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0508_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0508_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(766), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0508_internal;
        }
    }
    dbsum += 10000 / (1000 + abs((objlv - 30)) * 100) + 1;
    dblist(0, dbmax) = 766;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0508_internal:
    if (30 > objlv)
    {
        goto label_0509_internal;
    }
    if (fltselect != 0)
    {
        goto label_0509_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0509_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0509_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(765), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0509_internal;
        }
    }
    dbsum += 10000 / (1000 + abs((objlv - 30)) * 100) + 1;
    dblist(0, dbmax) = 765;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0509_internal:
    if (5 > objlv)
    {
        goto label_0510_internal;
    }
    if (fltselect != 0)
    {
        goto label_0510_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0510_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0510_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(764), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0510_internal;
        }
    }
    dbsum += 25000 / (1000 + abs((objlv - 5)) * 100) + 1;
    dblist(0, dbmax) = 764;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0510_internal:
    if (15 > objlv)
    {
        goto label_0511_internal;
    }
    if (fltselect != 0)
    {
        goto label_0511_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0511_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0511_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(763), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0511_internal;
        }
    }
    dbsum += 40000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 763;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0511_internal:
    if (25 > objlv)
    {
        goto label_0512_internal;
    }
    if (fltselect != 1)
    {
        goto label_0512_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0512_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0512_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(762), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0512_internal;
        }
    }
    dbsum += 5000 / (1000 + abs((objlv - 25)) * 100) + 1;
    dblist(0, dbmax) = 762;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0512_internal:
    if (20 > objlv)
    {
        goto label_0513_internal;
    }
    if (fltselect != 3)
    {
        goto label_0513_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0513_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60005)
        {
            goto label_0513_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(761), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0513_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 20)) * 100) + 1;
    dblist(0, dbmax) = 761;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0513_internal:
    if (1 > objlv)
    {
        goto label_0514_internal;
    }
    if (fltselect != 3)
    {
        goto label_0514_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0514_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0514_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(760), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0514_internal;
        }
    }
    dbsum += 5000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 760;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0514_internal:
    if (1 > objlv)
    {
        goto label_0515_internal;
    }
    if (fltselect != 0)
    {
        goto label_0515_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_0515_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10002)
        {
            goto label_0515_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(759), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0515_internal;
        }
    }
    dbsum += 2000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 759;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0515_internal:
    if (1 > objlv)
    {
        goto label_0516_internal;
    }
    if (fltselect != 3)
    {
        goto label_0516_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 24000)
        {
            goto label_0516_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 24020)
        {
            goto label_0516_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(758), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0516_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 758;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0516_internal:
    if (5 > objlv)
    {
        goto label_0517_internal;
    }
    if (fltselect != 3)
    {
        goto label_0517_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 12000)
        {
            goto label_0517_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 12001)
        {
            goto label_0517_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(757), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0517_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 5)) * 100) + 1;
    dblist(0, dbmax) = 757;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0517_internal:
    if (1 > objlv)
    {
        goto label_0518_internal;
    }
    if (fltselect != 0)
    {
        goto label_0518_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0518_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0518_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(756), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0518_internal;
        }
    }
    dbsum += 150000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 756;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0518_internal:
    if (1 > objlv)
    {
        goto label_0519_internal;
    }
    if (fltselect != 1)
    {
        goto label_0519_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0519_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0519_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(755), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0519_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 755;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0519_internal:
    if (1 > objlv)
    {
        goto label_0520_internal;
    }
    if (fltselect != 1)
    {
        goto label_0520_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0520_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0520_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(754), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0520_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 754;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0520_internal:
    if (28 > objlv)
    {
        goto label_0521_internal;
    }
    if (fltselect != 1)
    {
        goto label_0521_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0521_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0521_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(753), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0521_internal;
        }
    }
    dbsum += 10000 / (1000 + abs((objlv - 28)) * 100) + 1;
    dblist(0, dbmax) = 753;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0521_internal:
    if (1 > objlv)
    {
        goto label_0522_internal;
    }
    if (fltselect != 1)
    {
        goto label_0522_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 72000)
        {
            goto label_0522_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0522_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(752), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0522_internal;
        }
    }
    dbsum += 50000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 752;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0522_internal:
    if (1 > objlv)
    {
        goto label_0523_internal;
    }
    if (fltselect != 1)
    {
        goto label_0523_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0523_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0523_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(751), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0523_internal;
        }
    }
    dbsum += 20000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 751;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0523_internal:
    if (1 > objlv)
    {
        goto label_0524_internal;
    }
    if (fltselect != 1)
    {
        goto label_0524_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0524_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0524_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(750), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0524_internal;
        }
    }
    dbsum += 20000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 750;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0524_internal:
    if (1 > objlv)
    {
        goto label_0525_internal;
    }
    if (fltselect != 0)
    {
        goto label_0525_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0525_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0525_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(749), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0525_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 749;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0525_internal:
    if (1 > objlv)
    {
        goto label_0526_internal;
    }
    if (fltselect != 0)
    {
        goto label_0526_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0526_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0526_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(748), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0526_internal;
        }
    }
    dbsum += 20000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 748;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0526_internal:
    if (1 > objlv)
    {
        goto label_0527_internal;
    }
    if (fltselect != 1)
    {
        goto label_0527_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 55000)
        {
            goto label_0527_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0527_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(747), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0527_internal;
        }
    }
    dbsum += 50000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 747;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0527_internal:
    if (1 > objlv)
    {
        goto label_0528_internal;
    }
    if (fltselect != 1)
    {
        goto label_0528_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0528_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0528_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(746), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0528_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 746;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0528_internal:
    if (1 > objlv)
    {
        goto label_0529_internal;
    }
    if (fltselect != 1)
    {
        goto label_0529_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0529_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0529_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(745), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0529_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 745;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0529_internal:
    if (1 > objlv)
    {
        goto label_0530_internal;
    }
    if (fltselect != 1)
    {
        goto label_0530_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0530_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0530_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(744), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0530_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 744;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0530_internal:
    if (1 > objlv)
    {
        goto label_0531_internal;
    }
    if (fltselect != 1)
    {
        goto label_0531_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0531_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0531_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(743), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0531_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 743;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0531_internal:
    if (1 > objlv)
    {
        goto label_0532_internal;
    }
    if (fltselect != 3)
    {
        goto label_0532_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0532_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0532_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(742), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0532_internal;
        }
    }
    dbsum += 1000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 742;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0532_internal:
    if (25 > objlv)
    {
        goto label_0533_internal;
    }
    if (fltselect != 2)
    {
        goto label_0533_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_0533_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10002)
        {
            goto label_0533_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(741), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0533_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 25)) * 100) + 1;
    dblist(0, dbmax) = 741;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0533_internal:
    if (5 > objlv)
    {
        goto label_0534_internal;
    }
    if (fltselect != 3)
    {
        goto label_0534_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 34000)
        {
            goto label_0534_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 34001)
        {
            goto label_0534_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(740), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0534_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 5)) * 100) + 1;
    dblist(0, dbmax) = 740;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0534_internal:
    if (99 > objlv)
    {
        goto label_0535_internal;
    }
    if (fltselect != 3)
    {
        goto label_0535_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_0535_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10011)
        {
            goto label_0535_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(739), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0535_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 99)) * 100) + 1;
    dblist(0, dbmax) = 739;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0535_internal:
    if (1 > objlv)
    {
        goto label_0536_internal;
    }
    if (fltselect != 0)
    {
        goto label_0536_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0536_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0536_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(738), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0536_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 738;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0536_internal:
    if (20 > objlv)
    {
        goto label_0537_internal;
    }
    if (fltselect != 0)
    {
        goto label_0537_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0537_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0537_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(737), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0537_internal;
        }
    }
    dbsum += 2000 / (1000 + abs((objlv - 20)) * 0) + 1;
    dblist(0, dbmax) = 737;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0537_internal:
    if (1 > objlv)
    {
        goto label_0538_internal;
    }
    if (fltselect != 0)
    {
        goto label_0538_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0538_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0538_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(736), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0538_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 736;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0538_internal:
    if (1 > objlv)
    {
        goto label_0539_internal;
    }
    if (fltselect != 0)
    {
        goto label_0539_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_0539_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10011)
        {
            goto label_0539_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(735), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0539_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 735;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0539_internal:
    if (1 > objlv)
    {
        goto label_0540_internal;
    }
    if (fltselect != 0)
    {
        goto label_0540_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 72000)
        {
            goto label_0540_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0540_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(734), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0540_internal;
        }
    }
    dbsum += 50000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 734;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0540_internal:
    if (1 > objlv)
    {
        goto label_0541_internal;
    }
    if (fltselect != 0)
    {
        goto label_0541_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0541_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0541_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(733), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0541_internal;
        }
    }
    dbsum += 10000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 733;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0541_internal:
    if (5 > objlv)
    {
        goto label_0542_internal;
    }
    if (fltselect != 0)
    {
        goto label_0542_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0542_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0542_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(732), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0542_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 5)) * 0) + 1;
    dblist(0, dbmax) = 732;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0542_internal:
    if (15 > objlv)
    {
        goto label_0543_internal;
    }
    if (fltselect != 0)
    {
        goto label_0543_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0543_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0543_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(731), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0543_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 15)) * 0) + 1;
    dblist(0, dbmax) = 731;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0543_internal:
    if (1 > objlv)
    {
        goto label_0544_internal;
    }
    if (fltselect != 1)
    {
        goto label_0544_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 77000)
        {
            goto label_0544_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0544_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(730), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0544_internal;
        }
    }
    dbsum += 10000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 730;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0544_internal:
    if (1 > objlv)
    {
        goto label_0545_internal;
    }
    if (fltselect != 0)
    {
        goto label_0545_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0545_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0545_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(729), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0545_internal;
        }
    }
    dbsum += 5000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 729;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0545_internal:
    if (13 > objlv)
    {
        goto label_0546_internal;
    }
    if (fltselect != 3)
    {
        goto label_0546_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 19000)
        {
            goto label_0546_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 19001)
        {
            goto label_0546_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(728), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0546_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 13)) * 100) + 1;
    dblist(0, dbmax) = 728;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0546_internal:
    if (15 > objlv)
    {
        goto label_0547_internal;
    }
    if (fltselect != 2)
    {
        goto label_0547_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 14000)
        {
            goto label_0547_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 14003)
        {
            goto label_0547_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(727), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0547_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 727;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0547_internal:
    if (15 > objlv)
    {
        goto label_0548_internal;
    }
    if (fltselect != 3)
    {
        goto label_0548_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 14000)
        {
            goto label_0548_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 14003)
        {
            goto label_0548_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(726), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0548_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 726;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0548_internal:
    if (25 > objlv)
    {
        goto label_0549_internal;
    }
    if (fltselect != 3)
    {
        goto label_0549_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 24000)
        {
            goto label_0549_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 24030)
        {
            goto label_0549_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(725), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0549_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 25)) * 100) + 1;
    dblist(0, dbmax) = 725;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0549_internal:
    if (1 > objlv)
    {
        goto label_0550_internal;
    }
    if (fltselect != 1)
    {
        goto label_0550_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 77000)
        {
            goto label_0550_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0550_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(724), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0550_internal;
        }
    }
    dbsum += 10000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 724;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0550_internal:
    if (25 > objlv)
    {
        goto label_0551_internal;
    }
    if (fltselect != 3)
    {
        goto label_0551_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 34000)
        {
            goto label_0551_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 34001)
        {
            goto label_0551_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(723), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0551_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 25)) * 100) + 1;
    dblist(0, dbmax) = 723;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0551_internal:
    if (25 > objlv)
    {
        goto label_0552_internal;
    }
    if (fltselect != 3)
    {
        goto label_0552_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 34000)
        {
            goto label_0552_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 34001)
        {
            goto label_0552_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(722), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0552_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 25)) * 100) + 1;
    dblist(0, dbmax) = 722;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0552_internal:
    if (1 > objlv)
    {
        goto label_0553_internal;
    }
    if (fltselect != 3)
    {
        goto label_0553_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0553_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0553_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(721), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0553_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 721;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0553_internal:
    if (45 > objlv)
    {
        goto label_0554_internal;
    }
    if (fltselect != 0)
    {
        goto label_0554_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0554_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60004)
        {
            goto label_0554_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(720), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0554_internal;
        }
    }
    dbsum += 2000 / (1000 + abs((objlv - 45)) * 100) + 1;
    dblist(0, dbmax) = 720;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0554_internal:
    if (45 > objlv)
    {
        goto label_0555_internal;
    }
    if (fltselect != 3)
    {
        goto label_0555_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_0555_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10001)
        {
            goto label_0555_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(719), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0555_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 45)) * 100) + 1;
    dblist(0, dbmax) = 719;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0555_internal:
    if (40 > objlv)
    {
        goto label_0556_internal;
    }
    if (fltselect != 3)
    {
        goto label_0556_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 24000)
        {
            goto label_0556_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 24030)
        {
            goto label_0556_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(718), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0556_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 40)) * 100) + 1;
    dblist(0, dbmax) = 718;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0556_internal:
    if (1 > objlv)
    {
        goto label_0557_internal;
    }
    if (fltselect != 1)
    {
        goto label_0557_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0557_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0557_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(717), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0557_internal;
        }
    }
    dbsum += 1000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 717;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0557_internal:
    if (15 > objlv)
    {
        goto label_0558_internal;
    }
    if (fltselect != 3)
    {
        goto label_0558_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 24000)
        {
            goto label_0558_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 24030)
        {
            goto label_0558_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(716), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0558_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 716;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0558_internal:
    if (1 > objlv)
    {
        goto label_0559_internal;
    }
    if (fltselect != 0)
    {
        goto label_0559_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0559_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0559_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(715), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0559_internal;
        }
    }
    dbsum += 1000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 715;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0559_internal:
    if (10 > objlv)
    {
        goto label_0560_internal;
    }
    if (fltselect != 0)
    {
        goto label_0560_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 24000)
        {
            goto label_0560_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 24030)
        {
            goto label_0560_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(714), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0560_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 10)) * 100) + 1;
    dblist(0, dbmax) = 714;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0560_internal:
    if (5 > objlv)
    {
        goto label_0561_internal;
    }
    if (fltselect != 0)
    {
        goto label_0561_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 24000)
        {
            goto label_0561_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 24030)
        {
            goto label_0561_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(713), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0561_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 5)) * 100) + 1;
    dblist(0, dbmax) = 713;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0561_internal:
    if (1 > objlv)
    {
        goto label_0562_internal;
    }
    if (fltselect != 1)
    {
        goto label_0562_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0562_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 53100)
        {
            goto label_0562_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(712), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0562_internal;
        }
    }
    dbsum += 1000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 712;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0562_internal:
    if (1 > objlv)
    {
        goto label_0563_internal;
    }
    if (fltselect != 0)
    {
        goto label_0563_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0563_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0563_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(711), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0563_internal;
        }
    }
    dbsum += 5000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 711;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0563_internal:
    if (15 > objlv)
    {
        goto label_0564_internal;
    }
    if (fltselect != 0)
    {
        goto label_0564_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0564_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0564_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(710), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0564_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 15)) * 0) + 1;
    dblist(0, dbmax) = 710;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0564_internal:
    if (5 > objlv)
    {
        goto label_0565_internal;
    }
    if (fltselect != 0)
    {
        goto label_0565_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0565_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0565_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(709), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0565_internal;
        }
    }
    dbsum += 3000 / (1000 + abs((objlv - 5)) * 0) + 1;
    dblist(0, dbmax) = 709;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0565_internal:
    if (1 > objlv)
    {
        goto label_0566_internal;
    }
    if (fltselect != 0)
    {
        goto label_0566_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 55000)
        {
            goto label_0566_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0566_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(708), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0566_internal;
        }
    }
    dbsum += 3000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 708;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0566_internal:
    if (1 > objlv)
    {
        goto label_0567_internal;
    }
    if (fltselect != 3)
    {
        goto label_0567_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0567_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60005)
        {
            goto label_0567_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(707), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0567_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 707;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0567_internal:
    if (1 > objlv)
    {
        goto label_0568_internal;
    }
    if (fltselect != 0)
    {
        goto label_0568_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0568_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0568_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(706), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0568_internal;
        }
    }
    dbsum += 4000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 706;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0568_internal:
    if (15 > objlv)
    {
        goto label_0569_internal;
    }
    if (fltselect != 3)
    {
        goto label_0569_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 34000)
        {
            goto label_0569_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 34001)
        {
            goto label_0569_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(705), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0569_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 705;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0569_internal:
    if (1 > objlv)
    {
        goto label_0570_internal;
    }
    if (fltselect != 0)
    {
        goto label_0570_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0570_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0570_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(704), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0570_internal;
        }
    }
    dbsum += 10000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 704;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0570_internal:
    if (1 > objlv)
    {
        goto label_0571_internal;
    }
    if (fltselect != 0)
    {
        goto label_0571_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0571_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0571_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(703), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0571_internal;
        }
    }
    dbsum += 75000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 703;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0571_internal:
    if (1 > objlv)
    {
        goto label_0572_internal;
    }
    if (fltselect != 3)
    {
        goto label_0572_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0572_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 57004)
        {
            goto label_0572_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(702), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0572_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 702;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0572_internal:
    if (1 > objlv)
    {
        goto label_0573_internal;
    }
    if (fltselect != 0)
    {
        goto label_0573_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0573_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0573_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(701), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0573_internal;
        }
    }
    dbsum += 20000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 701;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0573_internal:
    if (1 > objlv)
    {
        goto label_0574_internal;
    }
    if (fltselect != 0)
    {
        goto label_0574_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 55000)
        {
            goto label_0574_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0574_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(700), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0574_internal;
        }
    }
    dbsum += 20000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 700;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0574_internal:
    if (1 > objlv)
    {
        goto label_0575_internal;
    }
    if (fltselect != 0)
    {
        goto label_0575_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0575_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0575_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(699), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0575_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 699;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0575_internal:
    if (1 > objlv)
    {
        goto label_0576_internal;
    }
    if (fltselect != 0)
    {
        goto label_0576_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0576_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0576_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(698), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0576_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 698;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0576_internal:
    if (15 > objlv)
    {
        goto label_0577_internal;
    }
    if (fltselect != 0)
    {
        goto label_0577_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0577_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0577_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(697), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0577_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 15)) * 0) + 1;
    dblist(0, dbmax) = 697;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0577_internal:
    if (20 > objlv)
    {
        goto label_0578_internal;
    }
    if (fltselect != 0)
    {
        goto label_0578_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0578_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0578_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(696), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0578_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 20)) * 0) + 1;
    dblist(0, dbmax) = 696;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0578_internal:
    if (30 > objlv)
    {
        goto label_0579_internal;
    }
    if (fltselect != 3)
    {
        goto label_0579_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_0579_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10010)
        {
            goto label_0579_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(695), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0579_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 30)) * 100) + 1;
    dblist(0, dbmax) = 695;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0579_internal:
    if (10 > objlv)
    {
        goto label_0580_internal;
    }
    if (fltselect != 0)
    {
        goto label_0580_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0580_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0580_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(694), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0580_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 10)) * 100) + 1;
    dblist(0, dbmax) = 694;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0580_internal:
    if (10 > objlv)
    {
        goto label_0581_internal;
    }
    if (fltselect != 0)
    {
        goto label_0581_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0581_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60005)
        {
            goto label_0581_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(693), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0581_internal;
        }
    }
    dbsum += 250000 / (1000 + abs((objlv - 10)) * 100) + 1;
    dblist(0, dbmax) = 693;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0581_internal:
    if (1 > objlv)
    {
        goto label_0582_internal;
    }
    if (fltselect != 0)
    {
        goto label_0582_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0582_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60005)
        {
            goto label_0582_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(692), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0582_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 692;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0582_internal:
    if (10 > objlv)
    {
        goto label_0583_internal;
    }
    if (fltselect != 0)
    {
        goto label_0583_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0583_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60005)
        {
            goto label_0583_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(691), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0583_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 10)) * 100) + 1;
    dblist(0, dbmax) = 691;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0583_internal:
    if (15 > objlv)
    {
        goto label_0584_internal;
    }
    if (fltselect != 0)
    {
        goto label_0584_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0584_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60005)
        {
            goto label_0584_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(690), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0584_internal;
        }
    }
    dbsum += 350000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 690;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0584_internal:
    if (1 > objlv)
    {
        goto label_0585_internal;
    }
    if (fltselect != 0)
    {
        goto label_0585_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0585_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0585_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(689), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0585_internal;
        }
    }
    dbsum += 5000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 689;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0585_internal:
    if (1 > objlv)
    {
        goto label_0586_internal;
    }
    if (fltselect != 0)
    {
        goto label_0586_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0586_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0586_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(688), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0586_internal;
        }
    }
    dbsum += 5000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 688;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0586_internal:
    if (3 > objlv)
    {
        goto label_0587_internal;
    }
    if (fltselect != 0)
    {
        goto label_0587_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0587_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0587_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(687), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0587_internal;
        }
    }
    dbsum += 5000000 / (1000 + abs((objlv - 3)) * 0) + 1;
    dblist(0, dbmax) = 687;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0587_internal:
    if (1 > objlv)
    {
        goto label_0588_internal;
    }
    if (fltselect != 3)
    {
        goto label_0588_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0588_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0588_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(686), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0588_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 686;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0588_internal:
    if (1 > objlv)
    {
        goto label_0589_internal;
    }
    if (fltselect != 0)
    {
        goto label_0589_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0589_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0589_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(685), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0589_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 685;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0589_internal:
    if (15 > objlv)
    {
        goto label_0590_internal;
    }
    if (fltselect != 0)
    {
        goto label_0590_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0590_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0590_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(684), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0590_internal;
        }
    }
    dbsum += 10000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 684;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0590_internal:
    if (1 > objlv)
    {
        goto label_0591_internal;
    }
    if (fltselect != 3)
    {
        goto label_0591_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0591_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0591_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(683), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0591_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 683;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0591_internal:
    if (1 > objlv)
    {
        goto label_0592_internal;
    }
    if (fltselect != 3)
    {
        goto label_0592_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0592_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0592_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(682), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0592_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 682;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0592_internal:
    if (1 > objlv)
    {
        goto label_0593_internal;
    }
    if (fltselect != 3)
    {
        goto label_0593_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0593_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0593_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(681), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0593_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 681;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0593_internal:
    if (1 > objlv)
    {
        goto label_0594_internal;
    }
    if (fltselect != 3)
    {
        goto label_0594_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0594_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0594_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(680), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0594_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 680;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0594_internal:
    if (60 > objlv)
    {
        goto label_0595_internal;
    }
    if (fltselect != 3)
    {
        goto label_0595_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_0595_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10005)
        {
            goto label_0595_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(679), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0595_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 60)) * 100) + 1;
    dblist(0, dbmax) = 679;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0595_internal:
    if (60 > objlv)
    {
        goto label_0596_internal;
    }
    if (fltselect != 3)
    {
        goto label_0596_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_0596_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10003)
        {
            goto label_0596_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(678), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0596_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 60)) * 100) + 1;
    dblist(0, dbmax) = 678;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0596_internal:
    if (60 > objlv)
    {
        goto label_0597_internal;
    }
    if (fltselect != 3)
    {
        goto label_0597_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_0597_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10007)
        {
            goto label_0597_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(677), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0597_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 60)) * 100) + 1;
    dblist(0, dbmax) = 677;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0597_internal:
    if (60 > objlv)
    {
        goto label_0598_internal;
    }
    if (fltselect != 3)
    {
        goto label_0598_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_0598_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10006)
        {
            goto label_0598_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(676), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0598_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 60)) * 100) + 1;
    dblist(0, dbmax) = 676;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0598_internal:
    if (60 > objlv)
    {
        goto label_0599_internal;
    }
    if (fltselect != 3)
    {
        goto label_0599_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_0599_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10011)
        {
            goto label_0599_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(675), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0599_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 60)) * 100) + 1;
    dblist(0, dbmax) = 675;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0599_internal:
    if (60 > objlv)
    {
        goto label_0600_internal;
    }
    if (fltselect != 3)
    {
        goto label_0600_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 24000)
        {
            goto label_0600_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 24020)
        {
            goto label_0600_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(674), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0600_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 60)) * 100) + 1;
    dblist(0, dbmax) = 674;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0600_internal:
    if (60 > objlv)
    {
        goto label_0601_internal;
    }
    if (fltselect != 3)
    {
        goto label_0601_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 24000)
        {
            goto label_0601_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 24001)
        {
            goto label_0601_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(673), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0601_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 60)) * 100) + 1;
    dblist(0, dbmax) = 673;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0601_internal:
    if (1 > objlv)
    {
        goto label_0602_internal;
    }
    if (fltselect != 3)
    {
        goto label_0602_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0602_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0602_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(672), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0602_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 672;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0602_internal:
    if (10 > objlv)
    {
        goto label_0603_internal;
    }
    if (fltselect != 3)
    {
        goto label_0603_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0603_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0603_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(671), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0603_internal;
        }
    }
    dbsum += 250000 / (1000 + abs((objlv - 10)) * 0) + 1;
    dblist(0, dbmax) = 671;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0603_internal:
    if (1 > objlv)
    {
        goto label_0604_internal;
    }
    if (fltselect != 0)
    {
        goto label_0604_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 92000)
        {
            goto label_0604_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0604_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(670), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0604_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 670;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0604_internal:
    if (1 > objlv)
    {
        goto label_0605_internal;
    }
    if (fltselect != 0)
    {
        goto label_0605_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 92000)
        {
            goto label_0605_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0605_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(669), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0605_internal;
        }
    }
    dbsum += 150000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 669;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0605_internal:
    if (1 > objlv)
    {
        goto label_0606_internal;
    }
    if (fltselect != 0)
    {
        goto label_0606_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 55000)
        {
            goto label_0606_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0606_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(668), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0606_internal;
        }
    }
    dbsum += 50000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 668;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0606_internal:
    if (3 > objlv)
    {
        goto label_0607_internal;
    }
    if (fltselect != 1)
    {
        goto label_0607_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0607_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0607_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(667), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0607_internal;
        }
    }
    dbsum += 250000 / (1000 + abs((objlv - 3)) * 100) + 1;
    dblist(0, dbmax) = 667;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0607_internal:
    if (1 > objlv)
    {
        goto label_0608_internal;
    }
    if (fltselect != 3)
    {
        goto label_0608_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0608_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0608_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(666), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0608_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 666;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0608_internal:
    if (1 > objlv)
    {
        goto label_0609_internal;
    }
    if (fltselect != 3)
    {
        goto label_0609_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0609_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0609_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(665), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0609_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 665;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0609_internal:
    if (15 > objlv)
    {
        goto label_0610_internal;
    }
    if (fltselect != 0)
    {
        goto label_0610_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 32000)
        {
            goto label_0610_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 32001)
        {
            goto label_0610_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(664), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0610_internal;
        }
    }
    dbsum += 30000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 664;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0610_internal:
    if (1 > objlv)
    {
        goto label_0611_internal;
    }
    if (fltselect != 3)
    {
        goto label_0611_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 64000)
        {
            goto label_0611_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0611_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(663), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0611_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 663;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0611_internal:
    if (1 > objlv)
    {
        goto label_0612_internal;
    }
    if (fltselect != 3)
    {
        goto label_0612_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0612_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 57004)
        {
            goto label_0612_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(662), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0612_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 662;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0612_internal:
    if (15 > objlv)
    {
        goto label_0613_internal;
    }
    if (fltselect != 3)
    {
        goto label_0613_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 18000)
        {
            goto label_0613_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 18002)
        {
            goto label_0613_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(661), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0613_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 661;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0613_internal:
    if (5 > objlv)
    {
        goto label_0614_internal;
    }
    if (fltselect != 0)
    {
        goto label_0614_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0614_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0614_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(660), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0614_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 5)) * 0) + 1;
    dblist(0, dbmax) = 660;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0614_internal:
    if (5 > objlv)
    {
        goto label_0615_internal;
    }
    if (fltselect != 0)
    {
        goto label_0615_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0615_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0615_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(659), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0615_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 5)) * 100) + 1;
    dblist(0, dbmax) = 659;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0615_internal:
    if (14 > objlv)
    {
        goto label_0616_internal;
    }
    if (fltselect != 0)
    {
        goto label_0616_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0616_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0616_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(658), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0616_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 14)) * 100) + 1;
    dblist(0, dbmax) = 658;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0616_internal:
    if (14 > objlv)
    {
        goto label_0617_internal;
    }
    if (fltselect != 0)
    {
        goto label_0617_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0617_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0617_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(657), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0617_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 14)) * 100) + 1;
    dblist(0, dbmax) = 657;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0617_internal:
    if (12 > objlv)
    {
        goto label_0618_internal;
    }
    if (fltselect != 0)
    {
        goto label_0618_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0618_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0618_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(656), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0618_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 12)) * 100) + 1;
    dblist(0, dbmax) = 656;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0618_internal:
    if (1 > objlv)
    {
        goto label_0619_internal;
    }
    if (fltselect != 3)
    {
        goto label_0619_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0619_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 57004)
        {
            goto label_0619_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(655), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0619_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 655;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0619_internal:
    if (40 > objlv)
    {
        goto label_0620_internal;
    }
    if (fltselect != 0)
    {
        goto label_0620_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0620_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60004)
        {
            goto label_0620_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(654), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0620_internal;
        }
    }
    dbsum += 250000 / (1000 + abs((objlv - 40)) * 100) + 1;
    dblist(0, dbmax) = 654;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0620_internal:
    if (1 > objlv)
    {
        goto label_0621_internal;
    }
    if (fltselect != 0)
    {
        goto label_0621_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0621_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0621_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(653), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0621_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 653;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0621_internal:
    if (15 > objlv)
    {
        goto label_0622_internal;
    }
    if (fltselect != 0)
    {
        goto label_0622_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0622_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0622_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(652), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0622_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 652;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0622_internal:
    if (25 > objlv)
    {
        goto label_0623_internal;
    }
    if (fltselect != 0)
    {
        goto label_0623_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0623_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0623_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(651), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0623_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 25)) * 100) + 1;
    dblist(0, dbmax) = 651;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0623_internal:
    if (4 > objlv)
    {
        goto label_0624_internal;
    }
    if (fltselect != 0)
    {
        goto label_0624_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60001)
        {
            goto label_0624_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60001)
        {
            goto label_0624_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(650), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0624_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 4)) * 100) + 1;
    dblist(0, dbmax) = 650;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0624_internal:
    if (10 > objlv)
    {
        goto label_0625_internal;
    }
    if (fltselect != 0)
    {
        goto label_0625_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0625_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0625_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(649), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0625_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 10)) * 100) + 1;
    dblist(0, dbmax) = 649;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0625_internal:
    if (5 > objlv)
    {
        goto label_0626_internal;
    }
    if (fltselect != 0)
    {
        goto label_0626_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0626_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0626_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(648), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0626_internal;
        }
    }
    dbsum += 250000 / (1000 + abs((objlv - 5)) * 100) + 1;
    dblist(0, dbmax) = 648;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0626_internal:
    if (18 > objlv)
    {
        goto label_0627_internal;
    }
    if (fltselect != 0)
    {
        goto label_0627_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0627_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0627_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(647), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0627_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 18)) * 100) + 1;
    dblist(0, dbmax) = 647;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0627_internal:
    if (5 > objlv)
    {
        goto label_0628_internal;
    }
    if (fltselect != 0)
    {
        goto label_0628_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0628_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0628_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(646), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0628_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 5)) * 100) + 1;
    dblist(0, dbmax) = 646;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0628_internal:
    if (35 > objlv)
    {
        goto label_0629_internal;
    }
    if (fltselect != 0)
    {
        goto label_0629_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0629_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0629_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(645), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0629_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 35)) * 100) + 1;
    dblist(0, dbmax) = 645;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0629_internal:
    if (1 > objlv)
    {
        goto label_0630_internal;
    }
    if (fltselect != 0)
    {
        goto label_0630_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0630_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0630_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(644), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0630_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 644;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0630_internal:
    if (1 > objlv)
    {
        goto label_0631_internal;
    }
    if (fltselect != 0)
    {
        goto label_0631_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0631_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60004)
        {
            goto label_0631_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(643), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0631_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 643;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0631_internal:
    if (1 > objlv)
    {
        goto label_0632_internal;
    }
    if (fltselect != 0)
    {
        goto label_0632_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0632_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0632_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(642), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0632_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 642;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0632_internal:
    if (30 > objlv)
    {
        goto label_0633_internal;
    }
    if (fltselect != 3)
    {
        goto label_0633_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 72000)
        {
            goto label_0633_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0633_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(641), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0633_internal;
        }
    }
    dbsum += 50000 / (1000 + abs((objlv - 30)) * 100) + 1;
    dblist(0, dbmax) = 641;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0633_internal:
    if (1 > objlv)
    {
        goto label_0634_internal;
    }
    if (fltselect != 0)
    {
        goto label_0634_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0634_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0634_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(640), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0634_internal;
        }
    }
    dbsum += 40000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 640;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0634_internal:
    if (1 > objlv)
    {
        goto label_0635_internal;
    }
    if (fltselect != 3)
    {
        goto label_0635_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0635_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 57004)
        {
            goto label_0635_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(639), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0635_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 639;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0635_internal:
    if (1 > objlv)
    {
        goto label_0636_internal;
    }
    if (fltselect != 0)
    {
        goto label_0636_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0636_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0636_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(638), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0636_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 638;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0636_internal:
    if (20 > objlv)
    {
        goto label_0637_internal;
    }
    if (fltselect != 2)
    {
        goto label_0637_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0637_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0637_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(637), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0637_internal;
        }
    }
    dbsum += 10000 / (1000 + abs((objlv - 20)) * 100) + 1;
    dblist(0, dbmax) = 637;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0637_internal:
    if (1 > objlv)
    {
        goto label_0638_internal;
    }
    if (fltselect != 0)
    {
        goto label_0638_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0638_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0638_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(636), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0638_internal;
        }
    }
    dbsum += 2000000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 636;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0638_internal:
    if (10 > objlv)
    {
        goto label_0639_internal;
    }
    if (fltselect != 0)
    {
        goto label_0639_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0639_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0639_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(635), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0639_internal;
        }
    }
    dbsum += 250000 / (1000 + abs((objlv - 10)) * 0) + 1;
    dblist(0, dbmax) = 635;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0639_internal:
    if (1 > objlv)
    {
        goto label_0640_internal;
    }
    if (fltselect != 0)
    {
        goto label_0640_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0640_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0640_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(634), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0640_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 634;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0640_internal:
    if (5 > objlv)
    {
        goto label_0641_internal;
    }
    if (fltselect != 0)
    {
        goto label_0641_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 24000)
        {
            goto label_0641_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 24030)
        {
            goto label_0641_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(633), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0641_internal;
        }
    }
    dbsum += 10000 / (1000 + abs((objlv - 5)) * 100) + 1;
    dblist(0, dbmax) = 633;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0641_internal:
    if (1 > objlv)
    {
        goto label_0642_internal;
    }
    if (fltselect != 0)
    {
        goto label_0642_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0642_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0642_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(632), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0642_internal;
        }
    }
    dbsum += 25000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 632;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0642_internal:
    if (15 > objlv)
    {
        goto label_0643_internal;
    }
    if (fltselect != 1)
    {
        goto label_0643_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0643_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0643_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(631), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0643_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 631;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0643_internal:
    if (1 > objlv)
    {
        goto label_0644_internal;
    }
    if (fltselect != 0)
    {
        goto label_0644_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0644_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0644_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(630), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0644_internal;
        }
    }
    dbsum += 5000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 630;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0644_internal:
    if (5 > objlv)
    {
        goto label_0645_internal;
    }
    if (fltselect != 0)
    {
        goto label_0645_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0645_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0645_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(629), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0645_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 5)) * 0) + 1;
    dblist(0, dbmax) = 629;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0645_internal:
    if (10 > objlv)
    {
        goto label_0646_internal;
    }
    if (fltselect != 0)
    {
        goto label_0646_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0646_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0646_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(628), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0646_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 10)) * 0) + 1;
    dblist(0, dbmax) = 628;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0646_internal:
    if (20 > objlv)
    {
        goto label_0647_internal;
    }
    if (fltselect != 3)
    {
        goto label_0647_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 12000)
        {
            goto label_0647_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 12001)
        {
            goto label_0647_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(627), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0647_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 20)) * 100) + 1;
    dblist(0, dbmax) = 627;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0647_internal:
    if (15 > objlv)
    {
        goto label_0648_internal;
    }
    if (fltselect != 0)
    {
        goto label_0648_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0648_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0648_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(626), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0648_internal;
        }
    }
    dbsum += 10000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 626;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0648_internal:
    if (1 > objlv)
    {
        goto label_0649_internal;
    }
    if (fltselect != 1)
    {
        goto label_0649_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0649_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0649_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(625), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0649_internal;
        }
    }
    dbsum += 10000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 625;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0649_internal:
    if (5 > objlv)
    {
        goto label_0650_internal;
    }
    if (fltselect != 0)
    {
        goto label_0650_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 55000)
        {
            goto label_0650_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0650_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(624), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0650_internal;
        }
    }
    dbsum += 5000 / (1000 + abs((objlv - 5)) * 0) + 1;
    dblist(0, dbmax) = 624;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0650_internal:
    if (15 > objlv)
    {
        goto label_0651_internal;
    }
    if (fltselect != 0)
    {
        goto label_0651_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 55000)
        {
            goto label_0651_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0651_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(623), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0651_internal;
        }
    }
    dbsum += 1000 / (1000 + abs((objlv - 15)) * 0) + 1;
    dblist(0, dbmax) = 623;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0651_internal:
    if (1 > objlv)
    {
        goto label_0652_internal;
    }
    if (fltselect != 0)
    {
        goto label_0652_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 77000)
        {
            goto label_0652_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0652_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(622), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0652_internal;
        }
    }
    dbsum += 10000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 622;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0652_internal:
    if (5 > objlv)
    {
        goto label_0653_internal;
    }
    if (fltselect != 0)
    {
        goto label_0653_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0653_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0653_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(621), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0653_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 5)) * 100) + 1;
    dblist(0, dbmax) = 621;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0653_internal:
    if (5 > objlv)
    {
        goto label_0654_internal;
    }
    if (fltselect != 0)
    {
        goto label_0654_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0654_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0654_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(620), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0654_internal;
        }
    }
    dbsum += 150000 / (1000 + abs((objlv - 5)) * 0) + 1;
    dblist(0, dbmax) = 620;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0654_internal:
    if (15 > objlv)
    {
        goto label_0655_internal;
    }
    if (fltselect != 1)
    {
        goto label_0655_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 64000)
        {
            goto label_0655_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0655_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(619), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0655_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 619;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0655_internal:
    if (15 > objlv)
    {
        goto label_0656_internal;
    }
    if (fltselect != 1)
    {
        goto label_0656_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0656_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0656_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(618), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0656_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 618;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0656_internal:
    if (1 > objlv)
    {
        goto label_0657_internal;
    }
    if (fltselect != 1)
    {
        goto label_0657_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 64000)
        {
            goto label_0657_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0657_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(617), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0657_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 617;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0657_internal:
    if (30 > objlv)
    {
        goto label_0658_internal;
    }
    if (fltselect != 1)
    {
        goto label_0658_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 72000)
        {
            goto label_0658_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0658_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(616), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0658_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 30)) * 100) + 1;
    dblist(0, dbmax) = 616;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0658_internal:
    if (1 > objlv)
    {
        goto label_0659_internal;
    }
    if (fltselect != 1)
    {
        goto label_0659_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0659_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0659_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(615), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0659_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 615;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0659_internal:
    if (15 > objlv)
    {
        goto label_0660_internal;
    }
    if (fltselect != 0)
    {
        goto label_0660_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0660_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0660_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(614), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0660_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 614;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0660_internal:
    if (50 > objlv)
    {
        goto label_0661_internal;
    }
    if (fltselect != 0)
    {
        goto label_0661_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0661_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60004)
        {
            goto label_0661_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(613), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0661_internal;
        }
    }
    dbsum += 50000 / (1000 + abs((objlv - 50)) * 100) + 1;
    dblist(0, dbmax) = 613;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0661_internal:
    if (1 > objlv)
    {
        goto label_0662_internal;
    }
    if (fltselect != 0)
    {
        goto label_0662_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0662_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0662_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(612), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0662_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 612;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0662_internal:
    if (1 > objlv)
    {
        goto label_0663_internal;
    }
    if (fltselect != 0)
    {
        goto label_0663_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0663_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0663_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(611), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0663_internal;
        }
    }
    dbsum += 50000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 611;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0663_internal:
    if (18 > objlv)
    {
        goto label_0664_internal;
    }
    if (fltselect != 0)
    {
        goto label_0664_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0664_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0664_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(610), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0664_internal;
        }
    }
    dbsum += 600000 / (1000 + abs((objlv - 18)) * 100) + 1;
    dblist(0, dbmax) = 610;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0664_internal:
    if (1 > objlv)
    {
        goto label_0665_internal;
    }
    if (fltselect != 0)
    {
        goto label_0665_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0665_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0665_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(609), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0665_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 609;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0665_internal:
    if (1 > objlv)
    {
        goto label_0666_internal;
    }
    if (fltselect != 0)
    {
        goto label_0666_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0666_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0666_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(608), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0666_internal;
        }
    }
    dbsum += 600000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 608;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0666_internal:
    if (1 > objlv)
    {
        goto label_0667_internal;
    }
    if (fltselect != 0)
    {
        goto label_0667_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0667_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0667_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(607), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0667_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 607;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0667_internal:
    if (25 > objlv)
    {
        goto label_0668_internal;
    }
    if (fltselect != 0)
    {
        goto label_0668_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0668_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0668_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(606), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0668_internal;
        }
    }
    dbsum += 150000 / (1000 + abs((objlv - 25)) * 100) + 1;
    dblist(0, dbmax) = 606;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0668_internal:
    if (15 > objlv)
    {
        goto label_0669_internal;
    }
    if (fltselect != 0)
    {
        goto label_0669_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0669_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0669_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(605), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0669_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 605;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0669_internal:
    if (1 > objlv)
    {
        goto label_0670_internal;
    }
    if (fltselect != 0)
    {
        goto label_0670_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0670_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0670_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(604), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0670_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 604;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0670_internal:
    if (35 > objlv)
    {
        goto label_0671_internal;
    }
    if (fltselect != 0)
    {
        goto label_0671_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0671_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0671_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(603), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0671_internal;
        }
    }
    dbsum += 10000 / (1000 + abs((objlv - 35)) * 100) + 1;
    dblist(0, dbmax) = 603;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0671_internal:
    if (1 > objlv)
    {
        goto label_0672_internal;
    }
    if (fltselect != 1)
    {
        goto label_0672_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60001)
        {
            goto label_0672_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60001)
        {
            goto label_0672_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(602), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0672_internal;
        }
    }
    dbsum += 50000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 602;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0672_internal:
    if (1 > objlv)
    {
        goto label_0673_internal;
    }
    if (fltselect != 0)
    {
        goto label_0673_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0673_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0673_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(601), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0673_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 601;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0673_internal:
    if (10 > objlv)
    {
        goto label_0674_internal;
    }
    if (fltselect != 1)
    {
        goto label_0674_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 72000)
        {
            goto label_0674_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0674_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(600), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0674_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 10)) * 100) + 1;
    dblist(0, dbmax) = 600;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0674_internal:
    if (30 > objlv)
    {
        goto label_0675_internal;
    }
    if (fltselect != 8)
    {
        goto label_0675_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 80000)
        {
            goto label_0675_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0675_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(599), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0675_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 30)) * 100) + 1;
    dblist(0, dbmax) = 599;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0675_internal:
    if (1 > objlv)
    {
        goto label_0676_internal;
    }
    if (fltselect != 0)
    {
        goto label_0676_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 92000)
        {
            goto label_0676_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0676_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(598), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0676_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 598;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0676_internal:
    if (1 > objlv)
    {
        goto label_0677_internal;
    }
    if (fltselect != 0)
    {
        goto label_0677_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 92000)
        {
            goto label_0677_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0677_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(597), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0677_internal;
        }
    }
    dbsum += 600000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 597;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0677_internal:
    if (10 > objlv)
    {
        goto label_0678_internal;
    }
    if (fltselect != 0)
    {
        goto label_0678_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0678_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0678_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(596), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0678_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 10)) * 100) + 1;
    dblist(0, dbmax) = 596;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0678_internal:
    if (20 > objlv)
    {
        goto label_0679_internal;
    }
    if (fltselect != 0)
    {
        goto label_0679_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0679_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0679_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(595), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0679_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 20)) * 100) + 1;
    dblist(0, dbmax) = 595;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0679_internal:
    if (40 > objlv)
    {
        goto label_0680_internal;
    }
    if (fltselect != 0)
    {
        goto label_0680_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0680_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0680_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(594), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0680_internal;
        }
    }
    dbsum += 50000 / (1000 + abs((objlv - 40)) * 100) + 1;
    dblist(0, dbmax) = 594;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0680_internal:
    if (30 > objlv)
    {
        goto label_0681_internal;
    }
    if (fltselect != 0)
    {
        goto label_0681_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0681_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0681_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(593), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0681_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 30)) * 100) + 1;
    dblist(0, dbmax) = 593;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0681_internal:
    if (1 > objlv)
    {
        goto label_0682_internal;
    }
    if (fltselect != 0)
    {
        goto label_0682_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0682_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0682_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(592), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0682_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 592;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0682_internal:
    if (1 > objlv)
    {
        goto label_0683_internal;
    }
    if (fltselect != 0)
    {
        goto label_0683_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0683_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0683_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(591), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0683_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 591;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0683_internal:
    if (1 > objlv)
    {
        goto label_0684_internal;
    }
    if (fltselect != 0)
    {
        goto label_0684_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 64000)
        {
            goto label_0684_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0684_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(590), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0684_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 590;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0684_internal:
    if (1 > objlv)
    {
        goto label_0685_internal;
    }
    if (fltselect != 8)
    {
        goto label_0685_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 80000)
        {
            goto label_0685_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0685_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(589), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0685_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 589;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0685_internal:
    if (1 > objlv)
    {
        goto label_0686_internal;
    }
    if (fltselect != 8)
    {
        goto label_0686_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 80000)
        {
            goto label_0686_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0686_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(588), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0686_internal;
        }
    }
    dbsum += 250000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 588;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0686_internal:
    if (1 > objlv)
    {
        goto label_0687_internal;
    }
    if (fltselect != 0)
    {
        goto label_0687_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0687_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0687_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(587), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0687_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 587;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0687_internal:
    if (30 > objlv)
    {
        goto label_0688_internal;
    }
    if (fltselect != 0)
    {
        goto label_0688_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0688_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0688_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(586), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0688_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 30)) * 100) + 1;
    dblist(0, dbmax) = 586;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0688_internal:
    if (20 > objlv)
    {
        goto label_0689_internal;
    }
    if (fltselect != 0)
    {
        goto label_0689_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0689_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0689_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(585), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0689_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 20)) * 100) + 1;
    dblist(0, dbmax) = 585;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0689_internal:
    if (1 > objlv)
    {
        goto label_0690_internal;
    }
    if (fltselect != 0)
    {
        goto label_0690_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0690_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0690_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(584), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0690_internal;
        }
    }
    dbsum += 250000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 584;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0690_internal:
    if (1 > objlv)
    {
        goto label_0691_internal;
    }
    if (fltselect != 0)
    {
        goto label_0691_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0691_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0691_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(583), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0691_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 583;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0691_internal:
    if (1 > objlv)
    {
        goto label_0692_internal;
    }
    if (fltselect != 0)
    {
        goto label_0692_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0692_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0692_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(582), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0692_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 582;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0692_internal:
    if (1 > objlv)
    {
        goto label_0693_internal;
    }
    if (fltselect != 0)
    {
        goto label_0693_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 56000)
        {
            goto label_0693_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0693_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(581), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0693_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 581;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0693_internal:
    if (12 > objlv)
    {
        goto label_0694_internal;
    }
    if (fltselect != 0)
    {
        goto label_0694_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0694_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0694_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(580), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0694_internal;
        }
    }
    dbsum += 600000 / (1000 + abs((objlv - 12)) * 100) + 1;
    dblist(0, dbmax) = 580;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0694_internal:
    if (30 > objlv)
    {
        goto label_0695_internal;
    }
    if (fltselect != 1)
    {
        goto label_0695_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 72000)
        {
            goto label_0695_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0695_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(579), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0695_internal;
        }
    }
    dbsum += 50000 / (1000 + abs((objlv - 30)) * 100) + 1;
    dblist(0, dbmax) = 579;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0695_internal:
    if (1 > objlv)
    {
        goto label_0696_internal;
    }
    if (fltselect != 0)
    {
        goto label_0696_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0696_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0696_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(578), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0696_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 578;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0696_internal:
    if (10 > objlv)
    {
        goto label_0697_internal;
    }
    if (fltselect != 0)
    {
        goto label_0697_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0697_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0697_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(577), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0697_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 10)) * 0) + 1;
    dblist(0, dbmax) = 577;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0697_internal:
    if (1 > objlv)
    {
        goto label_0698_internal;
    }
    if (fltselect != 0)
    {
        goto label_0698_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0698_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0698_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(576), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0698_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 576;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0698_internal:
    if (1 > objlv)
    {
        goto label_0699_internal;
    }
    if (fltselect != 0)
    {
        goto label_0699_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 64000)
        {
            goto label_0699_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0699_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(575), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0699_internal;
        }
    }
    dbsum += 250000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 575;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0699_internal:
    if (1 > objlv)
    {
        goto label_0700_internal;
    }
    if (fltselect != 0)
    {
        goto label_0700_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0700_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0700_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(574), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0700_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 574;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0700_internal:
    if (1 > objlv)
    {
        goto label_0701_internal;
    }
    if (fltselect != 0)
    {
        goto label_0701_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0701_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0701_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(573), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0701_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 573;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0701_internal:
    if (1 > objlv)
    {
        goto label_0702_internal;
    }
    if (fltselect != 1)
    {
        goto label_0702_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0702_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 53100)
        {
            goto label_0702_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(572), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0702_internal;
        }
    }
    dbsum += 1000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 572;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0702_internal:
    if (3 > objlv)
    {
        goto label_0703_internal;
    }
    if (fltselect != 0)
    {
        goto label_0703_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0703_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0703_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(571), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0703_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 3)) * 100) + 1;
    dblist(0, dbmax) = 571;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0703_internal:
    if (4 > objlv)
    {
        goto label_0704_internal;
    }
    if (fltselect != 0)
    {
        goto label_0704_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 56000)
        {
            goto label_0704_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0704_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(570), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0704_internal;
        }
    }
    dbsum += 700000 / (1000 + abs((objlv - 4)) * 0) + 1;
    dblist(0, dbmax) = 570;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0704_internal:
    if (4 > objlv)
    {
        goto label_0705_internal;
    }
    if (fltselect != 0)
    {
        goto label_0705_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0705_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0705_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(569), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0705_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 4)) * 0) + 1;
    dblist(0, dbmax) = 569;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0705_internal:
    if (1 > objlv)
    {
        goto label_0706_internal;
    }
    if (fltselect != 0)
    {
        goto label_0706_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0706_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0706_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(568), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0706_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 568;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0706_internal:
    if (1 > objlv)
    {
        goto label_0707_internal;
    }
    if (fltselect != 0)
    {
        goto label_0707_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0707_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0707_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(567), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0707_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 567;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0707_internal:
    if (1 > objlv)
    {
        goto label_0708_internal;
    }
    if (fltselect != 0)
    {
        goto label_0708_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0708_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0708_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(566), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0708_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 566;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0708_internal:
    if (8 > objlv)
    {
        goto label_0709_internal;
    }
    if (fltselect != 0)
    {
        goto label_0709_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 56000)
        {
            goto label_0709_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0709_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(565), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0709_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 8)) * 0) + 1;
    dblist(0, dbmax) = 565;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0709_internal:
    if (8 > objlv)
    {
        goto label_0710_internal;
    }
    if (fltselect != 0)
    {
        goto label_0710_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0710_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0710_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(564), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0710_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 8)) * 0) + 1;
    dblist(0, dbmax) = 564;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0710_internal:
    if (1 > objlv)
    {
        goto label_0711_internal;
    }
    if (fltselect != 0)
    {
        goto label_0711_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 55000)
        {
            goto label_0711_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0711_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(563), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0711_internal;
        }
    }
    dbsum += 50000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 563;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0711_internal:
    if (1 > objlv)
    {
        goto label_0712_internal;
    }
    if (fltselect != 1)
    {
        goto label_0712_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0712_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0712_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(562), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0712_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 562;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0712_internal:
    if (1 > objlv)
    {
        goto label_0713_internal;
    }
    if (fltselect != 1)
    {
        goto label_0713_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 72000)
        {
            goto label_0713_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0713_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(561), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0713_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 561;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0713_internal:
    if (1 > objlv)
    {
        goto label_0714_internal;
    }
    if (fltselect != 1)
    {
        goto label_0714_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 72000)
        {
            goto label_0714_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0714_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(560), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0714_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 560;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0714_internal:
    if (1 > objlv)
    {
        goto label_0715_internal;
    }
    if (fltselect != 0)
    {
        goto label_0715_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0715_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0715_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(559), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0715_internal;
        }
    }
    dbsum += 30000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 559;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0715_internal:
    if (15 > objlv)
    {
        goto label_0716_internal;
    }
    if (fltselect != 0)
    {
        goto label_0716_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 32000)
        {
            goto label_0716_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 32001)
        {
            goto label_0716_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(558), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0716_internal;
        }
    }
    dbsum += 25000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 558;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0716_internal:
    if (25 > objlv)
    {
        goto label_0717_internal;
    }
    if (fltselect != 0)
    {
        goto label_0717_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 20000)
        {
            goto label_0717_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 20001)
        {
            goto label_0717_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(557), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0717_internal;
        }
    }
    dbsum += 10000 / (1000 + abs((objlv - 25)) * 100) + 1;
    dblist(0, dbmax) = 557;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0717_internal:
    if (30 > objlv)
    {
        goto label_0718_internal;
    }
    if (fltselect != 0)
    {
        goto label_0718_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 18000)
        {
            goto label_0718_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 18002)
        {
            goto label_0718_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(556), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0718_internal;
        }
    }
    dbsum += 25000 / (1000 + abs((objlv - 30)) * 100) + 1;
    dblist(0, dbmax) = 556;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0718_internal:
    if (5 > objlv)
    {
        goto label_0719_internal;
    }
    if (fltselect != 0)
    {
        goto label_0719_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0719_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0719_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(555), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0719_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 5)) * 100) + 1;
    dblist(0, dbmax) = 555;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0719_internal:
    if (1 > objlv)
    {
        goto label_0720_internal;
    }
    if (fltselect != 0)
    {
        goto label_0720_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0720_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 58500)
        {
            goto label_0720_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(554), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0720_internal;
        }
    }
    dbsum += 250000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 554;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0720_internal:
    if (1 > objlv)
    {
        goto label_0721_internal;
    }
    if (fltselect != 0)
    {
        goto label_0721_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0721_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 58500)
        {
            goto label_0721_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(553), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0721_internal;
        }
    }
    dbsum += 250000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 553;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0721_internal:
    if (25 > objlv)
    {
        goto label_0722_internal;
    }
    if (fltselect != 0)
    {
        goto label_0722_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 20000)
        {
            goto label_0722_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 20001)
        {
            goto label_0722_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(552), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0722_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 25)) * 100) + 1;
    dblist(0, dbmax) = 552;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0722_internal:
    if (3 > objlv)
    {
        goto label_0723_internal;
    }
    if (fltselect != 0)
    {
        goto label_0723_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 56000)
        {
            goto label_0723_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0723_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(551), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0723_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 3)) * 0) + 1;
    dblist(0, dbmax) = 551;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0723_internal:
    if (5 > objlv)
    {
        goto label_0724_internal;
    }
    if (fltselect != 0)
    {
        goto label_0724_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0724_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0724_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(550), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0724_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 5)) * 0) + 1;
    dblist(0, dbmax) = 550;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0724_internal:
    if (12 > objlv)
    {
        goto label_0725_internal;
    }
    if (fltselect != 0)
    {
        goto label_0725_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0725_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0725_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(549), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0725_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 12)) * 0) + 1;
    dblist(0, dbmax) = 549;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0725_internal:
    if (7 > objlv)
    {
        goto label_0726_internal;
    }
    if (fltselect != 0)
    {
        goto label_0726_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0726_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0726_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(548), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0726_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 7)) * 0) + 1;
    dblist(0, dbmax) = 548;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0726_internal:
    if (1 > objlv)
    {
        goto label_0727_internal;
    }
    if (fltselect != 1)
    {
        goto label_0727_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 72000)
        {
            goto label_0727_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0727_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(547), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0727_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 547;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0727_internal:
    if (4 > objlv)
    {
        goto label_0728_internal;
    }
    if (fltselect != 0)
    {
        goto label_0728_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0728_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0728_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(546), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0728_internal;
        }
    }
    dbsum += 600000 / (1000 + abs((objlv - 4)) * 0) + 1;
    dblist(0, dbmax) = 546;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0728_internal:
    if (5 > objlv)
    {
        goto label_0729_internal;
    }
    if (fltselect != 0)
    {
        goto label_0729_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 56000)
        {
            goto label_0729_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0729_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(545), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0729_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 5)) * 0) + 1;
    dblist(0, dbmax) = 545;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0729_internal:
    if (1 > objlv)
    {
        goto label_0730_internal;
    }
    if (fltselect != 0)
    {
        goto label_0730_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0730_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0730_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(544), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0730_internal;
        }
    }
    dbsum += 1500000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 544;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0730_internal:
    if (1 > objlv)
    {
        goto label_0731_internal;
    }
    if (fltselect != 1)
    {
        goto label_0731_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0731_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 53100)
        {
            goto label_0731_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(543), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0731_internal;
        }
    }
    dbsum += 1000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 543;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0731_internal:
    if (1 > objlv)
    {
        goto label_0732_internal;
    }
    if (fltselect != 1)
    {
        goto label_0732_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0732_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 53100)
        {
            goto label_0732_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(542), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0732_internal;
        }
    }
    dbsum += 1000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 542;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0732_internal:
    if (1 > objlv)
    {
        goto label_0733_internal;
    }
    if (fltselect != 0)
    {
        goto label_0733_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0733_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0733_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(541), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0733_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 541;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0733_internal:
    if (20 > objlv)
    {
        goto label_0734_internal;
    }
    if (fltselect != 0)
    {
        goto label_0734_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0734_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0734_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(540), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0734_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 20)) * 100) + 1;
    dblist(0, dbmax) = 540;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0734_internal:
    if (30 > objlv)
    {
        goto label_0735_internal;
    }
    if (fltselect != 0)
    {
        goto label_0735_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0735_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0735_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(539), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0735_internal;
        }
    }
    dbsum += 50000 / (1000 + abs((objlv - 30)) * 100) + 1;
    dblist(0, dbmax) = 539;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0735_internal:
    if (28 > objlv)
    {
        goto label_0736_internal;
    }
    if (fltselect != 0)
    {
        goto label_0736_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0736_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0736_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(538), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0736_internal;
        }
    }
    dbsum += 50000 / (1000 + abs((objlv - 28)) * 100) + 1;
    dblist(0, dbmax) = 538;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0736_internal:
    if (14 > objlv)
    {
        goto label_0737_internal;
    }
    if (fltselect != 0)
    {
        goto label_0737_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0737_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0737_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(537), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0737_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 14)) * 100) + 1;
    dblist(0, dbmax) = 537;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0737_internal:
    if (15 > objlv)
    {
        goto label_0738_internal;
    }
    if (fltselect != 0)
    {
        goto label_0738_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0738_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0738_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(536), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0738_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 536;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0738_internal:
    if (5 > objlv)
    {
        goto label_0739_internal;
    }
    if (fltselect != 0)
    {
        goto label_0739_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0739_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0739_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(535), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0739_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 5)) * 100) + 1;
    dblist(0, dbmax) = 535;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0739_internal:
    if (18 > objlv)
    {
        goto label_0740_internal;
    }
    if (fltselect != 0)
    {
        goto label_0740_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0740_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0740_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(534), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0740_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 18)) * 100) + 1;
    dblist(0, dbmax) = 534;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0740_internal:
    if (22 > objlv)
    {
        goto label_0741_internal;
    }
    if (fltselect != 0)
    {
        goto label_0741_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0741_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0741_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(533), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0741_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 22)) * 100) + 1;
    dblist(0, dbmax) = 533;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0741_internal:
    if (23 > objlv)
    {
        goto label_0742_internal;
    }
    if (fltselect != 0)
    {
        goto label_0742_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0742_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0742_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(532), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0742_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 23)) * 100) + 1;
    dblist(0, dbmax) = 532;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0742_internal:
    if (19 > objlv)
    {
        goto label_0743_internal;
    }
    if (fltselect != 0)
    {
        goto label_0743_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0743_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0743_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(531), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0743_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 19)) * 100) + 1;
    dblist(0, dbmax) = 531;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0743_internal:
    if (1 > objlv)
    {
        goto label_0744_internal;
    }
    if (fltselect != 0)
    {
        goto label_0744_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 80000)
        {
            goto label_0744_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0744_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(530), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0744_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 530;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0744_internal:
    if (1 > objlv)
    {
        goto label_0745_internal;
    }
    if (fltselect != 0)
    {
        goto label_0745_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 80000)
        {
            goto label_0745_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0745_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(529), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0745_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 529;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0745_internal:
    if (1 > objlv)
    {
        goto label_0746_internal;
    }
    if (fltselect != 0)
    {
        goto label_0746_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 80000)
        {
            goto label_0746_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0746_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(528), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0746_internal;
        }
    }
    dbsum += 1500000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 528;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0746_internal:
    if (1 > objlv)
    {
        goto label_0747_internal;
    }
    if (fltselect != 0)
    {
        goto label_0747_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 80000)
        {
            goto label_0747_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0747_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(527), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0747_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 527;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0747_internal:
    if (1 > objlv)
    {
        goto label_0748_internal;
    }
    if (fltselect != 0)
    {
        goto label_0748_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 80000)
        {
            goto label_0748_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0748_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(526), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0748_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 526;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0748_internal:
    if (1 > objlv)
    {
        goto label_0749_internal;
    }
    if (fltselect != 1)
    {
        goto label_0749_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 80000)
        {
            goto label_0749_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0749_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(525), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0749_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 525;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0749_internal:
    if (1 > objlv)
    {
        goto label_0750_internal;
    }
    if (fltselect != 0)
    {
        goto label_0750_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 80000)
        {
            goto label_0750_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0750_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(524), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0750_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 524;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0750_internal:
    if (1 > objlv)
    {
        goto label_0751_internal;
    }
    if (fltselect != 0)
    {
        goto label_0751_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 80000)
        {
            goto label_0751_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0751_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(523), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0751_internal;
        }
    }
    dbsum += 3000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 523;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0751_internal:
    if (1 > objlv)
    {
        goto label_0752_internal;
    }
    if (fltselect != 1)
    {
        goto label_0752_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0752_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 53100)
        {
            goto label_0752_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(522), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0752_internal;
        }
    }
    dbsum += 1000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 522;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0752_internal:
    if (1 > objlv)
    {
        goto label_0753_internal;
    }
    if (fltselect != 1)
    {
        goto label_0753_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0753_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 53100)
        {
            goto label_0753_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(521), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0753_internal;
        }
    }
    dbsum += 1000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 521;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0753_internal:
    if (10 > objlv)
    {
        goto label_0754_internal;
    }
    if (fltselect != 0)
    {
        goto label_0754_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 20000)
        {
            goto label_0754_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 20001)
        {
            goto label_0754_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(520), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0754_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 10)) * 100) + 1;
    dblist(0, dbmax) = 520;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0754_internal:
    if (1 > objlv)
    {
        goto label_0755_internal;
    }
    if (fltselect != 0)
    {
        goto label_0755_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0755_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0755_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(519), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0755_internal;
        }
    }
    dbsum += 2000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 519;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0755_internal:
    if (7 > objlv)
    {
        goto label_0756_internal;
    }
    if (fltselect != 0)
    {
        goto label_0756_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 56000)
        {
            goto label_0756_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0756_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(518), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0756_internal;
        }
    }
    dbsum += 450000 / (1000 + abs((objlv - 7)) * 0) + 1;
    dblist(0, dbmax) = 518;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0756_internal:
    if (5 > objlv)
    {
        goto label_0757_internal;
    }
    if (fltselect != 0)
    {
        goto label_0757_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 56000)
        {
            goto label_0757_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0757_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(517), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0757_internal;
        }
    }
    dbsum += 700000 / (1000 + abs((objlv - 5)) * 0) + 1;
    dblist(0, dbmax) = 517;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0757_internal:
    if (1 > objlv)
    {
        goto label_0758_internal;
    }
    if (fltselect != 0)
    {
        goto label_0758_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0758_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0758_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(516), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0758_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 516;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0758_internal:
    if (5 > objlv)
    {
        goto label_0759_internal;
    }
    if (fltselect != 0)
    {
        goto label_0759_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0759_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0759_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(515), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0759_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 5)) * 0) + 1;
    dblist(0, dbmax) = 515;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0759_internal:
    if (80 > objlv)
    {
        goto label_0760_internal;
    }
    if (fltselect != 3)
    {
        goto label_0760_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 24000)
        {
            goto label_0760_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 24021)
        {
            goto label_0760_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(514), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0760_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 80)) * 100) + 1;
    dblist(0, dbmax) = 514;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0760_internal:
    if (1 > objlv)
    {
        goto label_0761_internal;
    }
    if (fltselect != 0)
    {
        goto label_0761_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 25000)
        {
            goto label_0761_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 25030)
        {
            goto label_0761_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(513), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0761_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 513;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0761_internal:
    if (1 > objlv)
    {
        goto label_0762_internal;
    }
    if (fltselect != 0)
    {
        goto label_0762_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 24000)
        {
            goto label_0762_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 24021)
        {
            goto label_0762_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(512), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0762_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 512;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0762_internal:
    if (3 > objlv)
    {
        goto label_0763_internal;
    }
    if (fltselect != 0)
    {
        goto label_0763_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0763_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0763_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(511), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0763_internal;
        }
    }
    dbsum += 250000 / (1000 + abs((objlv - 3)) * 100) + 1;
    dblist(0, dbmax) = 511;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0763_internal:
    if (1 > objlv)
    {
        goto label_0764_internal;
    }
    if (fltselect != 1)
    {
        goto label_0764_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 72000)
        {
            goto label_0764_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0764_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(510), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0764_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 510;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0764_internal:
    if (10 > objlv)
    {
        goto label_0765_internal;
    }
    if (fltselect != 0)
    {
        goto label_0765_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0765_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0765_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(509), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0765_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 10)) * 0) + 1;
    dblist(0, dbmax) = 509;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0765_internal:
    if (1 > objlv)
    {
        goto label_0766_internal;
    }
    if (fltselect != 0)
    {
        goto label_0766_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0766_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0766_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(508), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0766_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 508;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0766_internal:
    if (10 > objlv)
    {
        goto label_0767_internal;
    }
    if (fltselect != 0)
    {
        goto label_0767_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0767_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0767_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(507), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0767_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 10)) * 0) + 1;
    dblist(0, dbmax) = 507;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0767_internal:
    if (1 > objlv)
    {
        goto label_0768_internal;
    }
    if (fltselect != 0)
    {
        goto label_0768_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0768_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0768_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(506), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0768_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 506;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0768_internal:
    if (5 > objlv)
    {
        goto label_0769_internal;
    }
    if (fltselect != 0)
    {
        goto label_0769_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 55000)
        {
            goto label_0769_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0769_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(505), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0769_internal;
        }
    }
    dbsum += 25000 / (1000 + abs((objlv - 5)) * 0) + 1;
    dblist(0, dbmax) = 505;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0769_internal:
    if (1 > objlv)
    {
        goto label_0770_internal;
    }
    if (fltselect != 1)
    {
        goto label_0770_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 62000)
        {
            goto label_0770_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0770_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(504), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0770_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 504;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0770_internal:
    if (1 > objlv)
    {
        goto label_0771_internal;
    }
    if (fltselect != 1)
    {
        goto label_0771_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 62000)
        {
            goto label_0771_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0771_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(503), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0771_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 503;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0771_internal:
    if (30 > objlv)
    {
        goto label_0772_internal;
    }
    if (fltselect != 0)
    {
        goto label_0772_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0772_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0772_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(502), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0772_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 30)) * 0) + 1;
    dblist(0, dbmax) = 502;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0772_internal:
    if (15 > objlv)
    {
        goto label_0773_internal;
    }
    if (fltselect != 0)
    {
        goto label_0773_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0773_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0773_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(501), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0773_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 15)) * 0) + 1;
    dblist(0, dbmax) = 501;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0773_internal:
    if (1 > objlv)
    {
        goto label_0774_internal;
    }
    if (fltselect != 0)
    {
        goto label_0774_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0774_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0774_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(500), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0774_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 500;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0774_internal:
    if (3 > objlv)
    {
        goto label_0775_internal;
    }
    if (fltselect != 0)
    {
        goto label_0775_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0775_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0775_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(499), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0775_internal;
        }
    }
    dbsum += 250000 / (1000 + abs((objlv - 3)) * 100) + 1;
    dblist(0, dbmax) = 499;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0775_internal:
    if (3 > objlv)
    {
        goto label_0776_internal;
    }
    if (fltselect != 0)
    {
        goto label_0776_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0776_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0776_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(498), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0776_internal;
        }
    }
    dbsum += 250000 / (1000 + abs((objlv - 3)) * 100) + 1;
    dblist(0, dbmax) = 498;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0776_internal:
    if (3 > objlv)
    {
        goto label_0777_internal;
    }
    if (fltselect != 0)
    {
        goto label_0777_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0777_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0777_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(497), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0777_internal;
        }
    }
    dbsum += 250000 / (1000 + abs((objlv - 3)) * 100) + 1;
    dblist(0, dbmax) = 497;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0777_internal:
    if (10 > objlv)
    {
        goto label_0778_internal;
    }
    if (fltselect != 0)
    {
        goto label_0778_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 24000)
        {
            goto label_0778_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 24020)
        {
            goto label_0778_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(496), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0778_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 10)) * 100) + 1;
    dblist(0, dbmax) = 496;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0778_internal:
    if (1 > objlv)
    {
        goto label_0779_internal;
    }
    if (fltselect != 0)
    {
        goto label_0779_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0779_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0779_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(495), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0779_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 495;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0779_internal:
    if (1 > objlv)
    {
        goto label_0780_internal;
    }
    if (fltselect != 0)
    {
        goto label_0780_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0780_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0780_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(494), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0780_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 494;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0780_internal:
    if (1 > objlv)
    {
        goto label_0781_internal;
    }
    if (fltselect != 0)
    {
        goto label_0781_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0781_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0781_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(493), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0781_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 493;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0781_internal:
    if (11 > objlv)
    {
        goto label_0782_internal;
    }
    if (fltselect != 0)
    {
        goto label_0782_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0782_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0782_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(492), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0782_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 11)) * 100) + 1;
    dblist(0, dbmax) = 492;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0782_internal:
    if (18 > objlv)
    {
        goto label_0783_internal;
    }
    if (fltselect != 0)
    {
        goto label_0783_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0783_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0783_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(491), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0783_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 18)) * 100) + 1;
    dblist(0, dbmax) = 491;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0783_internal:
    if (15 > objlv)
    {
        goto label_0784_internal;
    }
    if (fltselect != 0)
    {
        goto label_0784_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0784_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0784_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(490), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0784_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 490;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0784_internal:
    if (1 > objlv)
    {
        goto label_0785_internal;
    }
    if (fltselect != 0)
    {
        goto label_0785_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0785_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0785_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(489), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0785_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 489;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0785_internal:
    if (11 > objlv)
    {
        goto label_0786_internal;
    }
    if (fltselect != 0)
    {
        goto label_0786_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0786_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0786_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(488), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0786_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 11)) * 100) + 1;
    dblist(0, dbmax) = 488;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0786_internal:
    if (12 > objlv)
    {
        goto label_0787_internal;
    }
    if (fltselect != 0)
    {
        goto label_0787_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0787_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0787_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(487), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0787_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 12)) * 100) + 1;
    dblist(0, dbmax) = 487;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0787_internal:
    if (5 > objlv)
    {
        goto label_0788_internal;
    }
    if (fltselect != 0)
    {
        goto label_0788_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0788_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0788_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(486), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0788_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 5)) * 100) + 1;
    dblist(0, dbmax) = 486;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0788_internal:
    if (3 > objlv)
    {
        goto label_0789_internal;
    }
    if (fltselect != 0)
    {
        goto label_0789_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 56000)
        {
            goto label_0789_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0789_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(485), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0789_internal;
        }
    }
    dbsum += 700000 / (1000 + abs((objlv - 3)) * 0) + 1;
    dblist(0, dbmax) = 485;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0789_internal:
    if (1 > objlv)
    {
        goto label_0790_internal;
    }
    if (fltselect != 0)
    {
        goto label_0790_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0790_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0790_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(484), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0790_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 484;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0790_internal:
    if (1 > objlv)
    {
        goto label_0791_internal;
    }
    if (fltselect != 0)
    {
        goto label_0791_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 25000)
        {
            goto label_0791_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 25002)
        {
            goto label_0791_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(483), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0791_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 483;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0791_internal:
    if (1 > objlv)
    {
        goto label_0792_internal;
    }
    if (fltselect != 0)
    {
        goto label_0792_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 24000)
        {
            goto label_0792_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 24003)
        {
            goto label_0792_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(482), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0792_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 482;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0792_internal:
    if (5 > objlv)
    {
        goto label_0793_internal;
    }
    if (fltselect != 0)
    {
        goto label_0793_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0793_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0793_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(481), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0793_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 5)) * 0) + 1;
    dblist(0, dbmax) = 481;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0793_internal:
    if (5 > objlv)
    {
        goto label_0794_internal;
    }
    if (fltselect != 0)
    {
        goto label_0794_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 56000)
        {
            goto label_0794_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0794_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(480), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0794_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 5)) * 0) + 1;
    dblist(0, dbmax) = 480;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0794_internal:
    if (10 > objlv)
    {
        goto label_0795_internal;
    }
    if (fltselect != 0)
    {
        goto label_0795_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0795_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0795_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(479), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0795_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 10)) * 0) + 1;
    dblist(0, dbmax) = 479;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0795_internal:
    if (1 > objlv)
    {
        goto label_0796_internal;
    }
    if (fltselect != 0)
    {
        goto label_0796_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0796_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0796_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(478), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0796_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 478;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0796_internal:
    if (1 > objlv)
    {
        goto label_0797_internal;
    }
    if (fltselect != 0)
    {
        goto label_0797_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 32000)
        {
            goto label_0797_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 32001)
        {
            goto label_0797_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(477), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0797_internal;
        }
    }
    dbsum += 700000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 477;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0797_internal:
    if (10 > objlv)
    {
        goto label_0798_internal;
    }
    if (fltselect != 0)
    {
        goto label_0798_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 32000)
        {
            goto label_0798_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 32001)
        {
            goto label_0798_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(476), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0798_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 10)) * 100) + 1;
    dblist(0, dbmax) = 476;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0798_internal:
    if (15 > objlv)
    {
        goto label_0799_internal;
    }
    if (fltselect != 0)
    {
        goto label_0799_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 32000)
        {
            goto label_0799_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 32001)
        {
            goto label_0799_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(475), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0799_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 475;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0799_internal:
    if (15 > objlv)
    {
        goto label_0800_internal;
    }
    if (fltselect != 0)
    {
        goto label_0800_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 32000)
        {
            goto label_0800_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 32001)
        {
            goto label_0800_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(474), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0800_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 474;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0800_internal:
    if (1 > objlv)
    {
        goto label_0801_internal;
    }
    if (fltselect != 0)
    {
        goto label_0801_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 34000)
        {
            goto label_0801_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 34001)
        {
            goto label_0801_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(473), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0801_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 473;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0801_internal:
    if (5 > objlv)
    {
        goto label_0802_internal;
    }
    if (fltselect != 0)
    {
        goto label_0802_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 34000)
        {
            goto label_0802_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 34001)
        {
            goto label_0802_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(472), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0802_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 5)) * 100) + 1;
    dblist(0, dbmax) = 472;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0802_internal:
    if (10 > objlv)
    {
        goto label_0803_internal;
    }
    if (fltselect != 0)
    {
        goto label_0803_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 34000)
        {
            goto label_0803_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 34001)
        {
            goto label_0803_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(471), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0803_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 10)) * 100) + 1;
    dblist(0, dbmax) = 471;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0803_internal:
    if (10 > objlv)
    {
        goto label_0804_internal;
    }
    if (fltselect != 0)
    {
        goto label_0804_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 34000)
        {
            goto label_0804_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 34001)
        {
            goto label_0804_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(470), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0804_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 10)) * 100) + 1;
    dblist(0, dbmax) = 470;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0804_internal:
    if (30 > objlv)
    {
        goto label_0805_internal;
    }
    if (fltselect != 0)
    {
        goto label_0805_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 34000)
        {
            goto label_0805_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 34001)
        {
            goto label_0805_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(469), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0805_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 30)) * 100) + 1;
    dblist(0, dbmax) = 469;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0805_internal:
    if (30 > objlv)
    {
        goto label_0806_internal;
    }
    if (fltselect != 0)
    {
        goto label_0806_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 34000)
        {
            goto label_0806_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 34001)
        {
            goto label_0806_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(468), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0806_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 30)) * 100) + 1;
    dblist(0, dbmax) = 468;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0806_internal:
    if (60 > objlv)
    {
        goto label_0807_internal;
    }
    if (fltselect != 0)
    {
        goto label_0807_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 12000)
        {
            goto label_0807_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 12001)
        {
            goto label_0807_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(467), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0807_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 60)) * 100) + 1;
    dblist(0, dbmax) = 467;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0807_internal:
    if (1 > objlv)
    {
        goto label_0808_internal;
    }
    if (fltselect != 0)
    {
        goto label_0808_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 12000)
        {
            goto label_0808_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 12001)
        {
            goto label_0808_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(466), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0808_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 466;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0808_internal:
    if (15 > objlv)
    {
        goto label_0809_internal;
    }
    if (fltselect != 0)
    {
        goto label_0809_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 12000)
        {
            goto label_0809_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 12001)
        {
            goto label_0809_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(465), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0809_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 465;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0809_internal:
    if (30 > objlv)
    {
        goto label_0810_internal;
    }
    if (fltselect != 0)
    {
        goto label_0810_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 12000)
        {
            goto label_0810_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 12001)
        {
            goto label_0810_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(464), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0810_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 30)) * 100) + 1;
    dblist(0, dbmax) = 464;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0810_internal:
    if (1 > objlv)
    {
        goto label_0811_internal;
    }
    if (fltselect != 0)
    {
        goto label_0811_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 12000)
        {
            goto label_0811_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 12002)
        {
            goto label_0811_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(463), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0811_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 463;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0811_internal:
    if (30 > objlv)
    {
        goto label_0812_internal;
    }
    if (fltselect != 0)
    {
        goto label_0812_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 20000)
        {
            goto label_0812_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 20001)
        {
            goto label_0812_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(462), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0812_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 30)) * 100) + 1;
    dblist(0, dbmax) = 462;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0812_internal:
    if (15 > objlv)
    {
        goto label_0813_internal;
    }
    if (fltselect != 0)
    {
        goto label_0813_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 20000)
        {
            goto label_0813_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 20001)
        {
            goto label_0813_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(461), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0813_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 461;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0813_internal:
    if (30 > objlv)
    {
        goto label_0814_internal;
    }
    if (fltselect != 0)
    {
        goto label_0814_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 19000)
        {
            goto label_0814_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 19001)
        {
            goto label_0814_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(460), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0814_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 30)) * 100) + 1;
    dblist(0, dbmax) = 460;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0814_internal:
    if (15 > objlv)
    {
        goto label_0815_internal;
    }
    if (fltselect != 0)
    {
        goto label_0815_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 19000)
        {
            goto label_0815_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 19001)
        {
            goto label_0815_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(459), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0815_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 459;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0815_internal:
    if (30 > objlv)
    {
        goto label_0816_internal;
    }
    if (fltselect != 0)
    {
        goto label_0816_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 18000)
        {
            goto label_0816_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 18001)
        {
            goto label_0816_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(458), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0816_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 30)) * 100) + 1;
    dblist(0, dbmax) = 458;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0816_internal:
    if (30 > objlv)
    {
        goto label_0817_internal;
    }
    if (fltselect != 0)
    {
        goto label_0817_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 18000)
        {
            goto label_0817_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 18002)
        {
            goto label_0817_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(457), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0817_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 30)) * 100) + 1;
    dblist(0, dbmax) = 457;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0817_internal:
    if (15 > objlv)
    {
        goto label_0818_internal;
    }
    if (fltselect != 0)
    {
        goto label_0818_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 18000)
        {
            goto label_0818_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 18002)
        {
            goto label_0818_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(456), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0818_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 456;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0818_internal:
    if (1 > objlv)
    {
        goto label_0819_internal;
    }
    if (fltselect != 0)
    {
        goto label_0819_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 18000)
        {
            goto label_0819_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 18002)
        {
            goto label_0819_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(455), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0819_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 455;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0819_internal:
    if (60 > objlv)
    {
        goto label_0820_internal;
    }
    if (fltselect != 0)
    {
        goto label_0820_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 14000)
        {
            goto label_0820_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 14003)
        {
            goto label_0820_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(454), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0820_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 60)) * 100) + 1;
    dblist(0, dbmax) = 454;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0820_internal:
    if (50 > objlv)
    {
        goto label_0821_internal;
    }
    if (fltselect != 0)
    {
        goto label_0821_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 14000)
        {
            goto label_0821_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 14003)
        {
            goto label_0821_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(453), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0821_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 50)) * 100) + 1;
    dblist(0, dbmax) = 453;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0821_internal:
    if (40 > objlv)
    {
        goto label_0822_internal;
    }
    if (fltselect != 0)
    {
        goto label_0822_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 14000)
        {
            goto label_0822_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 14003)
        {
            goto label_0822_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(452), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0822_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 40)) * 100) + 1;
    dblist(0, dbmax) = 452;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0822_internal:
    if (20 > objlv)
    {
        goto label_0823_internal;
    }
    if (fltselect != 0)
    {
        goto label_0823_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 14000)
        {
            goto label_0823_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 14003)
        {
            goto label_0823_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(451), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0823_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 20)) * 100) + 1;
    dblist(0, dbmax) = 451;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0823_internal:
    if (10 > objlv)
    {
        goto label_0824_internal;
    }
    if (fltselect != 0)
    {
        goto label_0824_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 14000)
        {
            goto label_0824_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 14003)
        {
            goto label_0824_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(450), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0824_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 10)) * 100) + 1;
    dblist(0, dbmax) = 450;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0824_internal:
    if (1 > objlv)
    {
        goto label_0825_internal;
    }
    if (fltselect != 0)
    {
        goto label_0825_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 14000)
        {
            goto label_0825_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 14003)
        {
            goto label_0825_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(449), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0825_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 449;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0825_internal:
    if (15 > objlv)
    {
        goto label_0826_internal;
    }
    if (fltselect != 0)
    {
        goto label_0826_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 22000)
        {
            goto label_0826_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 22001)
        {
            goto label_0826_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(448), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0826_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 448;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0826_internal:
    if (1 > objlv)
    {
        goto label_0827_internal;
    }
    if (fltselect != 0)
    {
        goto label_0827_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 22000)
        {
            goto label_0827_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 22003)
        {
            goto label_0827_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(447), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0827_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 447;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0827_internal:
    if (30 > objlv)
    {
        goto label_0828_internal;
    }
    if (fltselect != 0)
    {
        goto label_0828_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 22000)
        {
            goto label_0828_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 22001)
        {
            goto label_0828_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(446), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0828_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 30)) * 100) + 1;
    dblist(0, dbmax) = 446;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0828_internal:
    if (15 > objlv)
    {
        goto label_0829_internal;
    }
    if (fltselect != 0)
    {
        goto label_0829_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 22000)
        {
            goto label_0829_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 22003)
        {
            goto label_0829_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(445), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0829_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 445;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0829_internal:
    if (35 > objlv)
    {
        goto label_0830_internal;
    }
    if (fltselect != 0)
    {
        goto label_0830_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 16000)
        {
            goto label_0830_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 16003)
        {
            goto label_0830_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(444), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0830_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 35)) * 100) + 1;
    dblist(0, dbmax) = 444;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0830_internal:
    if (25 > objlv)
    {
        goto label_0831_internal;
    }
    if (fltselect != 0)
    {
        goto label_0831_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 16000)
        {
            goto label_0831_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 16003)
        {
            goto label_0831_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(443), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0831_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 25)) * 100) + 1;
    dblist(0, dbmax) = 443;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0831_internal:
    if (20 > objlv)
    {
        goto label_0832_internal;
    }
    if (fltselect != 0)
    {
        goto label_0832_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 16000)
        {
            goto label_0832_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 16003)
        {
            goto label_0832_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(442), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0832_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 20)) * 100) + 1;
    dblist(0, dbmax) = 442;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0832_internal:
    if (10 > objlv)
    {
        goto label_0833_internal;
    }
    if (fltselect != 0)
    {
        goto label_0833_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 16000)
        {
            goto label_0833_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 16003)
        {
            goto label_0833_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(441), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0833_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 10)) * 100) + 1;
    dblist(0, dbmax) = 441;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0833_internal:
    if (45 > objlv)
    {
        goto label_0834_internal;
    }
    if (fltselect != 0)
    {
        goto label_0834_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 16000)
        {
            goto label_0834_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 16003)
        {
            goto label_0834_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(440), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0834_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 45)) * 100) + 1;
    dblist(0, dbmax) = 440;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0834_internal:
    if (40 > objlv)
    {
        goto label_0835_internal;
    }
    if (fltselect != 0)
    {
        goto label_0835_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 16000)
        {
            goto label_0835_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 16001)
        {
            goto label_0835_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(439), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0835_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 40)) * 100) + 1;
    dblist(0, dbmax) = 439;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0835_internal:
    if (30 > objlv)
    {
        goto label_0836_internal;
    }
    if (fltselect != 0)
    {
        goto label_0836_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 16000)
        {
            goto label_0836_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 16001)
        {
            goto label_0836_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(438), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0836_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 30)) * 100) + 1;
    dblist(0, dbmax) = 438;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0836_internal:
    if (20 > objlv)
    {
        goto label_0837_internal;
    }
    if (fltselect != 0)
    {
        goto label_0837_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 16000)
        {
            goto label_0837_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 16001)
        {
            goto label_0837_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(437), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0837_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 20)) * 100) + 1;
    dblist(0, dbmax) = 437;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0837_internal:
    if (50 > objlv)
    {
        goto label_0838_internal;
    }
    if (fltselect != 0)
    {
        goto label_0838_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 16000)
        {
            goto label_0838_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 16001)
        {
            goto label_0838_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(436), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0838_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 50)) * 100) + 1;
    dblist(0, dbmax) = 436;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0838_internal:
    if (10 > objlv)
    {
        goto label_0839_internal;
    }
    if (fltselect != 0)
    {
        goto label_0839_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 16000)
        {
            goto label_0839_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 16001)
        {
            goto label_0839_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(435), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0839_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 10)) * 100) + 1;
    dblist(0, dbmax) = 435;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0839_internal:
    if (15 > objlv)
    {
        goto label_0840_internal;
    }
    if (fltselect != 0)
    {
        goto label_0840_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0840_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0840_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(434), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0840_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 15)) * 0) + 1;
    dblist(0, dbmax) = 434;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0840_internal:
    if (10 > objlv)
    {
        goto label_0841_internal;
    }
    if (fltselect != 0)
    {
        goto label_0841_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0841_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0841_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(433), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0841_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 10)) * 0) + 1;
    dblist(0, dbmax) = 433;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0841_internal:
    if (8 > objlv)
    {
        goto label_0842_internal;
    }
    if (fltselect != 0)
    {
        goto label_0842_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0842_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0842_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(432), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0842_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 8)) * 0) + 1;
    dblist(0, dbmax) = 432;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0842_internal:
    if (5 > objlv)
    {
        goto label_0843_internal;
    }
    if (fltselect != 0)
    {
        goto label_0843_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0843_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0843_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(431), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0843_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 5)) * 0) + 1;
    dblist(0, dbmax) = 431;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0843_internal:
    if (5 > objlv)
    {
        goto label_0844_internal;
    }
    if (fltselect != 0)
    {
        goto label_0844_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0844_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0844_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(430), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0844_internal;
        }
    }
    dbsum += 80000 / (1000 + abs((objlv - 5)) * 0) + 1;
    dblist(0, dbmax) = 430;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0844_internal:
    if (1 > objlv)
    {
        goto label_0845_internal;
    }
    if (fltselect != 0)
    {
        goto label_0845_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0845_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0845_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(429), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0845_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 429;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0845_internal:
    if (1 > objlv)
    {
        goto label_0846_internal;
    }
    if (fltselect != 0)
    {
        goto label_0846_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0846_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60004)
        {
            goto label_0846_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(428), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0846_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 428;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0846_internal:
    if (1 > objlv)
    {
        goto label_0847_internal;
    }
    if (fltselect != 0)
    {
        goto label_0847_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0847_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 58005)
        {
            goto label_0847_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(427), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0847_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 427;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0847_internal:
    if (1 > objlv)
    {
        goto label_0848_internal;
    }
    if (fltselect != 0)
    {
        goto label_0848_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0848_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 58005)
        {
            goto label_0848_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(426), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0848_internal;
        }
    }
    dbsum += 80000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 426;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0848_internal:
    if (1 > objlv)
    {
        goto label_0849_internal;
    }
    if (fltselect != 0)
    {
        goto label_0849_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0849_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 58005)
        {
            goto label_0849_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(425), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0849_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 425;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0849_internal:
    if (1 > objlv)
    {
        goto label_0850_internal;
    }
    if (fltselect != 0)
    {
        goto label_0850_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0850_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 58005)
        {
            goto label_0850_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(424), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0850_internal;
        }
    }
    dbsum += 80000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 424;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0850_internal:
    if (1 > objlv)
    {
        goto label_0851_internal;
    }
    if (fltselect != 0)
    {
        goto label_0851_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0851_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 58005)
        {
            goto label_0851_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(423), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0851_internal;
        }
    }
    dbsum += 80000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 423;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0851_internal:
    if (1 > objlv)
    {
        goto label_0852_internal;
    }
    if (fltselect != 0)
    {
        goto label_0852_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0852_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 58005)
        {
            goto label_0852_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(422), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0852_internal;
        }
    }
    dbsum += 80000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 422;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0852_internal:
    if (1 > objlv)
    {
        goto label_0853_internal;
    }
    if (fltselect != 0)
    {
        goto label_0853_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0853_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 58500)
        {
            goto label_0853_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(421), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0853_internal;
        }
    }
    dbsum += 20000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 421;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0853_internal:
    if (1 > objlv)
    {
        goto label_0854_internal;
    }
    if (fltselect != 0)
    {
        goto label_0854_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0854_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 58500)
        {
            goto label_0854_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(420), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0854_internal;
        }
    }
    dbsum += 250000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 420;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0854_internal:
    if (1 > objlv)
    {
        goto label_0855_internal;
    }
    if (fltselect != 0)
    {
        goto label_0855_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0855_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 58500)
        {
            goto label_0855_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(419), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0855_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 419;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0855_internal:
    if (1 > objlv)
    {
        goto label_0856_internal;
    }
    if (fltselect != 0)
    {
        goto label_0856_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0856_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 58500)
        {
            goto label_0856_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(418), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0856_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 418;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0856_internal:
    if (1 > objlv)
    {
        goto label_0857_internal;
    }
    if (fltselect != 0)
    {
        goto label_0857_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0857_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 58500)
        {
            goto label_0857_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(417), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0857_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 417;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0857_internal:
    if (1 > objlv)
    {
        goto label_0858_internal;
    }
    if (fltselect != 0)
    {
        goto label_0858_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 72000)
        {
            goto label_0858_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0858_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(416), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0858_internal;
        }
    }
    dbsum += 25000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 416;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0858_internal:
    if (1 > objlv)
    {
        goto label_0859_internal;
    }
    if (fltselect != 0)
    {
        goto label_0859_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 72000)
        {
            goto label_0859_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0859_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(415), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0859_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 415;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0859_internal:
    if (18 > objlv)
    {
        goto label_0860_internal;
    }
    if (fltselect != 1)
    {
        goto label_0860_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0860_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0860_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(414), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0860_internal;
        }
    }
    dbsum += 50000 / (1000 + abs((objlv - 18)) * 100) + 1;
    dblist(0, dbmax) = 414;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0860_internal:
    if (18 > objlv)
    {
        goto label_0861_internal;
    }
    if (fltselect != 1)
    {
        goto label_0861_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0861_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0861_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(413), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0861_internal;
        }
    }
    dbsum += 50000 / (1000 + abs((objlv - 18)) * 100) + 1;
    dblist(0, dbmax) = 413;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0861_internal:
    if (12 > objlv)
    {
        goto label_0862_internal;
    }
    if (fltselect != 0)
    {
        goto label_0862_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 56000)
        {
            goto label_0862_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0862_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(412), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0862_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 12)) * 0) + 1;
    dblist(0, dbmax) = 412;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0862_internal:
    if (1 > objlv)
    {
        goto label_0863_internal;
    }
    if (fltselect != 0)
    {
        goto label_0863_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0863_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0863_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(411), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0863_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 411;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0863_internal:
    if (1 > objlv)
    {
        goto label_0864_internal;
    }
    if (fltselect != 0)
    {
        goto label_0864_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0864_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0864_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(410), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0864_internal;
        }
    }
    dbsum += 600000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 410;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0864_internal:
    if (1 > objlv)
    {
        goto label_0865_internal;
    }
    if (fltselect != 0)
    {
        goto label_0865_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 92000)
        {
            goto label_0865_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0865_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(409), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0865_internal;
        }
    }
    dbsum += 1500000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 409;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0865_internal:
    if (1 > objlv)
    {
        goto label_0866_internal;
    }
    if (fltselect != 0)
    {
        goto label_0866_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 92000)
        {
            goto label_0866_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0866_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(408), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0866_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 408;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0866_internal:
    if (1 > objlv)
    {
        goto label_0867_internal;
    }
    if (fltselect != 0)
    {
        goto label_0867_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 92000)
        {
            goto label_0867_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0867_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(407), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0867_internal;
        }
    }
    dbsum += 600000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 407;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0867_internal:
    if (1 > objlv)
    {
        goto label_0868_internal;
    }
    if (fltselect != 0)
    {
        goto label_0868_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 92000)
        {
            goto label_0868_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0868_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(406), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0868_internal;
        }
    }
    dbsum += 2000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 406;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0868_internal:
    if (1 > objlv)
    {
        goto label_0869_internal;
    }
    if (fltselect != 0)
    {
        goto label_0869_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 92000)
        {
            goto label_0869_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0869_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(405), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0869_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 405;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0869_internal:
    if (1 > objlv)
    {
        goto label_0870_internal;
    }
    if (fltselect != 0)
    {
        goto label_0870_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 92000)
        {
            goto label_0870_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0870_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(404), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0870_internal;
        }
    }
    dbsum += 1500000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 404;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0870_internal:
    if (1 > objlv)
    {
        goto label_0871_internal;
    }
    if (fltselect != 0)
    {
        goto label_0871_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 92000)
        {
            goto label_0871_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0871_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(403), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0871_internal;
        }
    }
    dbsum += 700000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 403;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0871_internal:
    if (1 > objlv)
    {
        goto label_0872_internal;
    }
    if (fltselect != 0)
    {
        goto label_0872_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 92000)
        {
            goto label_0872_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0872_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(402), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0872_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 402;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0872_internal:
    if (1 > objlv)
    {
        goto label_0873_internal;
    }
    if (fltselect != 0)
    {
        goto label_0873_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 92000)
        {
            goto label_0873_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0873_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(401), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0873_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 401;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0873_internal:
    if (1 > objlv)
    {
        goto label_0874_internal;
    }
    if (fltselect != 0)
    {
        goto label_0874_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 92000)
        {
            goto label_0874_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0874_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(400), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0874_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 400;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0874_internal:
    if (1 > objlv)
    {
        goto label_0875_internal;
    }
    if (fltselect != 0)
    {
        goto label_0875_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 92000)
        {
            goto label_0875_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0875_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(399), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0875_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 399;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0875_internal:
    if (3 > objlv)
    {
        goto label_0876_internal;
    }
    if (fltselect != 0)
    {
        goto label_0876_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0876_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0876_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(398), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0876_internal;
        }
    }
    dbsum += 600000 / (1000 + abs((objlv - 3)) * 0) + 1;
    dblist(0, dbmax) = 398;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0876_internal:
    if (3 > objlv)
    {
        goto label_0877_internal;
    }
    if (fltselect != 0)
    {
        goto label_0877_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0877_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0877_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(397), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0877_internal;
        }
    }
    dbsum += 700000 / (1000 + abs((objlv - 3)) * 0) + 1;
    dblist(0, dbmax) = 397;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0877_internal:
    if (3 > objlv)
    {
        goto label_0878_internal;
    }
    if (fltselect != 0)
    {
        goto label_0878_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0878_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0878_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(396), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0878_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 3)) * 0) + 1;
    dblist(0, dbmax) = 396;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0878_internal:
    if (5 > objlv)
    {
        goto label_0879_internal;
    }
    if (fltselect != 0)
    {
        goto label_0879_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0879_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0879_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(395), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0879_internal;
        }
    }
    dbsum += 700000 / (1000 + abs((objlv - 5)) * 0) + 1;
    dblist(0, dbmax) = 395;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0879_internal:
    if (1 > objlv)
    {
        goto label_0880_internal;
    }
    if (fltselect != 0)
    {
        goto label_0880_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 72000)
        {
            goto label_0880_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0880_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(394), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0880_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 394;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0880_internal:
    if (1 > objlv)
    {
        goto label_0881_internal;
    }
    if (fltselect != 0)
    {
        goto label_0881_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0881_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0881_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(393), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0881_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 393;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0881_internal:
    if (1 > objlv)
    {
        goto label_0882_internal;
    }
    if (fltselect != 0)
    {
        goto label_0882_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0882_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0882_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(392), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0882_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 392;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0882_internal:
    if (11 > objlv)
    {
        goto label_0883_internal;
    }
    if (fltselect != 0)
    {
        goto label_0883_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 56000)
        {
            goto label_0883_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0883_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(391), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0883_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 11)) * 0) + 1;
    dblist(0, dbmax) = 391;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0883_internal:
    if (5 > objlv)
    {
        goto label_0884_internal;
    }
    if (fltselect != 0)
    {
        goto label_0884_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0884_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0884_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(390), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0884_internal;
        }
    }
    dbsum += 150000 / (1000 + abs((objlv - 5)) * 0) + 1;
    dblist(0, dbmax) = 390;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0884_internal:
    if (5 > objlv)
    {
        goto label_0885_internal;
    }
    if (fltselect != 0)
    {
        goto label_0885_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0885_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0885_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(389), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0885_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 5)) * 0) + 1;
    dblist(0, dbmax) = 389;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0885_internal:
    if (1 > objlv)
    {
        goto label_0886_internal;
    }
    if (fltselect != 0)
    {
        goto label_0886_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0886_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0886_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(388), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0886_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 388;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0886_internal:
    if (11 > objlv)
    {
        goto label_0887_internal;
    }
    if (fltselect != 0)
    {
        goto label_0887_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0887_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0887_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(387), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0887_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 11)) * 0) + 1;
    dblist(0, dbmax) = 387;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0887_internal:
    if (2 > objlv)
    {
        goto label_0888_internal;
    }
    if (fltselect != 0)
    {
        goto label_0888_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0888_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0888_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(386), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0888_internal;
        }
    }
    dbsum += 700000 / (1000 + abs((objlv - 2)) * 0) + 1;
    dblist(0, dbmax) = 386;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0888_internal:
    if (7 > objlv)
    {
        goto label_0889_internal;
    }
    if (fltselect != 0)
    {
        goto label_0889_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 56000)
        {
            goto label_0889_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0889_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(385), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0889_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 7)) * 0) + 1;
    dblist(0, dbmax) = 385;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0889_internal:
    if (3 > objlv)
    {
        goto label_0890_internal;
    }
    if (fltselect != 0)
    {
        goto label_0890_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0890_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0890_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(384), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0890_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 3)) * 0) + 1;
    dblist(0, dbmax) = 384;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0890_internal:
    if (14 > objlv)
    {
        goto label_0891_internal;
    }
    if (fltselect != 0)
    {
        goto label_0891_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0891_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0891_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(383), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0891_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 14)) * 0) + 1;
    dblist(0, dbmax) = 383;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0891_internal:
    if (1 > objlv)
    {
        goto label_0892_internal;
    }
    if (fltselect != 0)
    {
        goto label_0892_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0892_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0892_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(382), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0892_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 382;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0892_internal:
    if (10 > objlv)
    {
        goto label_0893_internal;
    }
    if (fltselect != 0)
    {
        goto label_0893_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0893_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0893_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(381), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0893_internal;
        }
    }
    dbsum += 700000 / (1000 + abs((objlv - 10)) * 0) + 1;
    dblist(0, dbmax) = 381;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0893_internal:
    if (1 > objlv)
    {
        goto label_0894_internal;
    }
    if (fltselect != 0)
    {
        goto label_0894_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0894_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0894_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(380), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0894_internal;
        }
    }
    dbsum += 700000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 380;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0894_internal:
    if (1 > objlv)
    {
        goto label_0895_internal;
    }
    if (fltselect != 0)
    {
        goto label_0895_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0895_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0895_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(379), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0895_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 379;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0895_internal:
    if (2 > objlv)
    {
        goto label_0896_internal;
    }
    if (fltselect != 0)
    {
        goto label_0896_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0896_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0896_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(378), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0896_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 2)) * 0) + 1;
    dblist(0, dbmax) = 378;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0896_internal:
    if (8 > objlv)
    {
        goto label_0897_internal;
    }
    if (fltselect != 0)
    {
        goto label_0897_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 56000)
        {
            goto label_0897_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0897_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(377), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0897_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 8)) * 0) + 1;
    dblist(0, dbmax) = 377;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0897_internal:
    if (1 > objlv)
    {
        goto label_0898_internal;
    }
    if (fltselect != 0)
    {
        goto label_0898_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0898_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0898_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(376), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0898_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 376;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0898_internal:
    if (1 > objlv)
    {
        goto label_0899_internal;
    }
    if (fltselect != 0)
    {
        goto label_0899_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0899_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0899_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(375), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0899_internal;
        }
    }
    dbsum += 700000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 375;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0899_internal:
    if (7 > objlv)
    {
        goto label_0900_internal;
    }
    if (fltselect != 0)
    {
        goto label_0900_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0900_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0900_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(374), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0900_internal;
        }
    }
    dbsum += 700000 / (1000 + abs((objlv - 7)) * 0) + 1;
    dblist(0, dbmax) = 374;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0900_internal:
    if (13 > objlv)
    {
        goto label_0901_internal;
    }
    if (fltselect != 0)
    {
        goto label_0901_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0901_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0901_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(373), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0901_internal;
        }
    }
    dbsum += 700000 / (1000 + abs((objlv - 13)) * 0) + 1;
    dblist(0, dbmax) = 373;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0901_internal:
    if (8 > objlv)
    {
        goto label_0902_internal;
    }
    if (fltselect != 0)
    {
        goto label_0902_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0902_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0902_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(372), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0902_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 8)) * 100) + 1;
    dblist(0, dbmax) = 372;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0902_internal:
    if (8 > objlv)
    {
        goto label_0903_internal;
    }
    if (fltselect != 0)
    {
        goto label_0903_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0903_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0903_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(371), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0903_internal;
        }
    }
    dbsum += 700000 / (1000 + abs((objlv - 8)) * 0) + 1;
    dblist(0, dbmax) = 371;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0903_internal:
    if (9 > objlv)
    {
        goto label_0904_internal;
    }
    if (fltselect != 0)
    {
        goto label_0904_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0904_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0904_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(370), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0904_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 9)) * 100) + 1;
    dblist(0, dbmax) = 370;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0904_internal:
    if (8 > objlv)
    {
        goto label_0905_internal;
    }
    if (fltselect != 0)
    {
        goto label_0905_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0905_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0905_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(369), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0905_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 8)) * 0) + 1;
    dblist(0, dbmax) = 369;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0905_internal:
    if (1 > objlv)
    {
        goto label_0906_internal;
    }
    if (fltselect != 0)
    {
        goto label_0906_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0906_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0906_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(368), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0906_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 368;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0906_internal:
    if (10 > objlv)
    {
        goto label_0907_internal;
    }
    if (fltselect != 0)
    {
        goto label_0907_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0907_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0907_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(367), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0907_internal;
        }
    }
    dbsum += 600000 / (1000 + abs((objlv - 10)) * 0) + 1;
    dblist(0, dbmax) = 367;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0907_internal:
    if (4 > objlv)
    {
        goto label_0908_internal;
    }
    if (fltselect != 0)
    {
        goto label_0908_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 56000)
        {
            goto label_0908_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0908_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(366), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0908_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 4)) * 0) + 1;
    dblist(0, dbmax) = 366;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0908_internal:
    if (3 > objlv)
    {
        goto label_0909_internal;
    }
    if (fltselect != 0)
    {
        goto label_0909_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0909_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0909_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(365), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0909_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 3)) * 0) + 1;
    dblist(0, dbmax) = 365;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0909_internal:
    if (1 > objlv)
    {
        goto label_0910_internal;
    }
    if (fltselect != 0)
    {
        goto label_0910_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0910_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0910_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(364), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0910_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 364;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0910_internal:
    if (12 > objlv)
    {
        goto label_0911_internal;
    }
    if (fltselect != 0)
    {
        goto label_0911_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0911_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0911_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(363), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0911_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 12)) * 0) + 1;
    dblist(0, dbmax) = 363;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0911_internal:
    if (10 > objlv)
    {
        goto label_0912_internal;
    }
    if (fltselect != 0)
    {
        goto label_0912_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0912_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0912_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(362), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0912_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 10)) * 0) + 1;
    dblist(0, dbmax) = 362;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0912_internal:
    if (1 > objlv)
    {
        goto label_0913_internal;
    }
    if (fltselect != 1)
    {
        goto label_0913_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 72000)
        {
            goto label_0913_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0913_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(361), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0913_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 361;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0913_internal:
    if (30 > objlv)
    {
        goto label_0914_internal;
    }
    if (fltselect != 3)
    {
        goto label_0914_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 32000)
        {
            goto label_0914_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 32001)
        {
            goto label_0914_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(360), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0914_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 30)) * 100) + 1;
    dblist(0, dbmax) = 360;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0914_internal:
    if (35 > objlv)
    {
        goto label_0915_internal;
    }
    if (fltselect != 3)
    {
        goto label_0915_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_0915_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10007)
        {
            goto label_0915_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(359), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0915_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 35)) * 100) + 1;
    dblist(0, dbmax) = 359;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0915_internal:
    if (35 > objlv)
    {
        goto label_0916_internal;
    }
    if (fltselect != 3)
    {
        goto label_0916_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_0916_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10006)
        {
            goto label_0916_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(358), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0916_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 35)) * 100) + 1;
    dblist(0, dbmax) = 358;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0916_internal:
    if (30 > objlv)
    {
        goto label_0917_internal;
    }
    if (fltselect != 3)
    {
        goto label_0917_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 32000)
        {
            goto label_0917_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 32001)
        {
            goto label_0917_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(357), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0917_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 30)) * 100) + 1;
    dblist(0, dbmax) = 357;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0917_internal:
    if (30 > objlv)
    {
        goto label_0918_internal;
    }
    if (fltselect != 3)
    {
        goto label_0918_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_0918_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10004)
        {
            goto label_0918_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(356), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0918_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 30)) * 100) + 1;
    dblist(0, dbmax) = 356;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0918_internal:
    if (20 > objlv)
    {
        goto label_0919_internal;
    }
    if (fltselect != 3)
    {
        goto label_0919_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 22000)
        {
            goto label_0919_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 22003)
        {
            goto label_0919_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(355), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0919_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 20)) * 100) + 1;
    dblist(0, dbmax) = 355;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0919_internal:
    if (5 > objlv)
    {
        goto label_0920_internal;
    }
    if (fltselect != 0)
    {
        goto label_0920_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0920_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0920_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(354), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0920_internal;
        }
    }
    dbsum += 600000 / (1000 + abs((objlv - 5)) * 100) + 1;
    dblist(0, dbmax) = 354;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0920_internal:
    if (7 > objlv)
    {
        goto label_0921_internal;
    }
    if (fltselect != 0)
    {
        goto label_0921_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0921_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0921_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(353), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0921_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 7)) * 100) + 1;
    dblist(0, dbmax) = 353;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0921_internal:
    if (7 > objlv)
    {
        goto label_0922_internal;
    }
    if (fltselect != 0)
    {
        goto label_0922_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0922_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0922_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(352), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0922_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 7)) * 100) + 1;
    dblist(0, dbmax) = 352;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0922_internal:
    if (5 > objlv)
    {
        goto label_0923_internal;
    }
    if (fltselect != 0)
    {
        goto label_0923_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0923_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0923_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(351), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0923_internal;
        }
    }
    dbsum += 600000 / (1000 + abs((objlv - 5)) * 100) + 1;
    dblist(0, dbmax) = 351;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0923_internal:
    if (3 > objlv)
    {
        goto label_0924_internal;
    }
    if (fltselect != 0)
    {
        goto label_0924_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0924_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0924_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(350), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0924_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 3)) * 100) + 1;
    dblist(0, dbmax) = 350;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0924_internal:
    if (3 > objlv)
    {
        goto label_0925_internal;
    }
    if (fltselect != 0)
    {
        goto label_0925_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0925_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0925_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(349), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0925_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 3)) * 100) + 1;
    dblist(0, dbmax) = 349;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0925_internal:
    if (17 > objlv)
    {
        goto label_0926_internal;
    }
    if (fltselect != 0)
    {
        goto label_0926_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0926_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0926_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(348), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0926_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 17)) * 100) + 1;
    dblist(0, dbmax) = 348;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0926_internal:
    if (10 > objlv)
    {
        goto label_0927_internal;
    }
    if (fltselect != 0)
    {
        goto label_0927_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0927_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0927_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(347), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0927_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 10)) * 100) + 1;
    dblist(0, dbmax) = 347;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0927_internal:
    if (15 > objlv)
    {
        goto label_0928_internal;
    }
    if (fltselect != 0)
    {
        goto label_0928_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0928_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0928_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(346), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0928_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 346;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0928_internal:
    if (12 > objlv)
    {
        goto label_0929_internal;
    }
    if (fltselect != 0)
    {
        goto label_0929_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_0929_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0929_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(345), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0929_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 12)) * 100) + 1;
    dblist(0, dbmax) = 345;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0929_internal:
    if (1 > objlv)
    {
        goto label_0930_internal;
    }
    if (fltselect != 1)
    {
        goto label_0930_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0930_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 53100)
        {
            goto label_0930_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(344), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0930_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 344;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0930_internal:
    if (1 > objlv)
    {
        goto label_0931_internal;
    }
    if (fltselect != 0)
    {
        goto label_0931_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0931_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0931_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(343), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0931_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 343;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0931_internal:
    if (1 > objlv)
    {
        goto label_0932_internal;
    }
    if (fltselect != 0)
    {
        goto label_0932_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_0932_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0932_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(342), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0932_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 342;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0932_internal:
    if (1 > objlv)
    {
        goto label_0933_internal;
    }
    if (fltselect != 0)
    {
        goto label_0933_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 62000)
        {
            goto label_0933_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0933_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(341), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0933_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 341;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0933_internal:
    if (1 > objlv)
    {
        goto label_0934_internal;
    }
    if (fltselect != 0)
    {
        goto label_0934_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 62000)
        {
            goto label_0934_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0934_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(340), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0934_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 340;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0934_internal:
    if (1 > objlv)
    {
        goto label_0935_internal;
    }
    if (fltselect != 0)
    {
        goto label_0935_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 62000)
        {
            goto label_0935_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0935_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(339), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0935_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 339;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0935_internal:
    if (1 > objlv)
    {
        goto label_0936_internal;
    }
    if (fltselect != 0)
    {
        goto label_0936_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 62000)
        {
            goto label_0936_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0936_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(338), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0936_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 338;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0936_internal:
    if (1 > objlv)
    {
        goto label_0937_internal;
    }
    if (fltselect != 0)
    {
        goto label_0937_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 62000)
        {
            goto label_0937_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0937_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(337), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0937_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 337;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0937_internal:
    if (18 > objlv)
    {
        goto label_0938_internal;
    }
    if (fltselect != 0)
    {
        goto label_0938_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0938_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0938_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(336), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0938_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 18)) * 100) + 1;
    dblist(0, dbmax) = 336;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0938_internal:
    if (8 > objlv)
    {
        goto label_0939_internal;
    }
    if (fltselect != 0)
    {
        goto label_0939_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0939_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0939_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(335), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0939_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 8)) * 100) + 1;
    dblist(0, dbmax) = 335;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0939_internal:
    if (22 > objlv)
    {
        goto label_0940_internal;
    }
    if (fltselect != 0)
    {
        goto label_0940_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0940_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0940_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(334), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0940_internal;
        }
    }
    dbsum += 150000 / (1000 + abs((objlv - 22)) * 100) + 1;
    dblist(0, dbmax) = 334;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0940_internal:
    if (1 > objlv)
    {
        goto label_0941_internal;
    }
    if (fltselect != 0)
    {
        goto label_0941_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 91000)
        {
            goto label_0941_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0941_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(333), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0941_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 333;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0941_internal:
    if (3 > objlv)
    {
        goto label_0942_internal;
    }
    if (fltselect != 0)
    {
        goto label_0942_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0942_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0942_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(332), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0942_internal;
        }
    }
    dbsum += 20000 / (1000 + abs((objlv - 3)) * 100) + 1;
    dblist(0, dbmax) = 332;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0942_internal:
    if (3 > objlv)
    {
        goto label_0943_internal;
    }
    if (fltselect != 0)
    {
        goto label_0943_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0943_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0943_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(331), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0943_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 3)) * 100) + 1;
    dblist(0, dbmax) = 331;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0943_internal:
    if (1 > objlv)
    {
        goto label_0944_internal;
    }
    if (fltselect != 0)
    {
        goto label_0944_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 64000)
        {
            goto label_0944_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0944_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(330), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0944_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 330;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0944_internal:
    if (1 > objlv)
    {
        goto label_0945_internal;
    }
    if (fltselect != 0)
    {
        goto label_0945_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0945_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0945_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(329), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0945_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 329;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0945_internal:
    if (18 > objlv)
    {
        goto label_0946_internal;
    }
    if (fltselect != 0)
    {
        goto label_0946_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0946_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0946_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(328), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0946_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 18)) * 100) + 1;
    dblist(0, dbmax) = 328;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0946_internal:
    if (1 > objlv)
    {
        goto label_0947_internal;
    }
    if (fltselect != 0)
    {
        goto label_0947_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0947_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0947_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(327), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0947_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 327;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0947_internal:
    if (1 > objlv)
    {
        goto label_0948_internal;
    }
    if (fltselect != 0)
    {
        goto label_0948_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0948_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0948_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(326), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0948_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 326;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0948_internal:
    if (9 > objlv)
    {
        goto label_0949_internal;
    }
    if (fltselect != 0)
    {
        goto label_0949_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0949_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60004)
        {
            goto label_0949_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(325), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0949_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 9)) * 100) + 1;
    dblist(0, dbmax) = 325;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0949_internal:
    if (1 > objlv)
    {
        goto label_0950_internal;
    }
    if (fltselect != 0)
    {
        goto label_0950_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0950_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0950_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(324), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0950_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 324;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0950_internal:
    if (7 > objlv)
    {
        goto label_0951_internal;
    }
    if (fltselect != 0)
    {
        goto label_0951_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0951_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0951_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(323), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0951_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 7)) * 100) + 1;
    dblist(0, dbmax) = 323;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0951_internal:
    if (4 > objlv)
    {
        goto label_0952_internal;
    }
    if (fltselect != 0)
    {
        goto label_0952_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0952_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0952_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(322), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0952_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 4)) * 100) + 1;
    dblist(0, dbmax) = 322;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0952_internal:
    if (1 > objlv)
    {
        goto label_0953_internal;
    }
    if (fltselect != 0)
    {
        goto label_0953_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0953_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0953_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(321), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0953_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 321;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0953_internal:
    if (1 > objlv)
    {
        goto label_0954_internal;
    }
    if (fltselect != 0)
    {
        goto label_0954_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0954_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0954_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(320), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0954_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 320;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0954_internal:
    if (1 > objlv)
    {
        goto label_0955_internal;
    }
    if (fltselect != 0)
    {
        goto label_0955_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0955_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60004)
        {
            goto label_0955_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(319), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0955_internal;
        }
    }
    dbsum += 600000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 319;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0955_internal:
    if (1 > objlv)
    {
        goto label_0956_internal;
    }
    if (fltselect != 0)
    {
        goto label_0956_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0956_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0956_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(318), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0956_internal;
        }
    }
    dbsum += 600000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 318;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0956_internal:
    if (1 > objlv)
    {
        goto label_0957_internal;
    }
    if (fltselect != 0)
    {
        goto label_0957_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0957_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0957_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(317), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0957_internal;
        }
    }
    dbsum += 600000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 317;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0957_internal:
    if (18 > objlv)
    {
        goto label_0958_internal;
    }
    if (fltselect != 0)
    {
        goto label_0958_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0958_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0958_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(316), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0958_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 18)) * 100) + 1;
    dblist(0, dbmax) = 316;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0958_internal:
    if (1 > objlv)
    {
        goto label_0959_internal;
    }
    if (fltselect != 1)
    {
        goto label_0959_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0959_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0959_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(315), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0959_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 315;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0959_internal:
    if (1 > objlv)
    {
        goto label_0960_internal;
    }
    if (fltselect != 1)
    {
        goto label_0960_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0960_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0960_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(314), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0960_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 314;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0960_internal:
    if (1 > objlv)
    {
        goto label_0961_internal;
    }
    if (fltselect != 1)
    {
        goto label_0961_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0961_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0961_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(313), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0961_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 313;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0961_internal:
    if (1 > objlv)
    {
        goto label_0962_internal;
    }
    if (fltselect != 1)
    {
        goto label_0962_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0962_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0962_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(312), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0962_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 312;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0962_internal:
    if (19 > objlv)
    {
        goto label_0963_internal;
    }
    if (fltselect != 0)
    {
        goto label_0963_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0963_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0963_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(311), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0963_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 19)) * 100) + 1;
    dblist(0, dbmax) = 311;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0963_internal:
    if (1 > objlv)
    {
        goto label_0964_internal;
    }
    if (fltselect != 0)
    {
        goto label_0964_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0964_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60004)
        {
            goto label_0964_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(310), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0964_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 310;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0964_internal:
    if (7 > objlv)
    {
        goto label_0965_internal;
    }
    if (fltselect != 0)
    {
        goto label_0965_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0965_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0965_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(309), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0965_internal;
        }
    }
    dbsum += 250000 / (1000 + abs((objlv - 7)) * 100) + 1;
    dblist(0, dbmax) = 309;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0965_internal:
    if (1 > objlv)
    {
        goto label_0966_internal;
    }
    if (fltselect != 0)
    {
        goto label_0966_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0966_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0966_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(308), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0966_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 308;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0966_internal:
    if (1 > objlv)
    {
        goto label_0967_internal;
    }
    if (fltselect != 0)
    {
        goto label_0967_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0967_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60004)
        {
            goto label_0967_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(307), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0967_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 307;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0967_internal:
    if (1 > objlv)
    {
        goto label_0968_internal;
    }
    if (fltselect != 0)
    {
        goto label_0968_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0968_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0968_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(306), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0968_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 306;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0968_internal:
    if (18 > objlv)
    {
        goto label_0969_internal;
    }
    if (fltselect != 0)
    {
        goto label_0969_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0969_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60004)
        {
            goto label_0969_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(305), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0969_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 18)) * 100) + 1;
    dblist(0, dbmax) = 305;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0969_internal:
    if (1 > objlv)
    {
        goto label_0970_internal;
    }
    if (fltselect != 0)
    {
        goto label_0970_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0970_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60004)
        {
            goto label_0970_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(304), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0970_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 304;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0970_internal:
    if (12 > objlv)
    {
        goto label_0971_internal;
    }
    if (fltselect != 0)
    {
        goto label_0971_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0971_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60004)
        {
            goto label_0971_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(303), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0971_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 12)) * 100) + 1;
    dblist(0, dbmax) = 303;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0971_internal:
    if (4 > objlv)
    {
        goto label_0972_internal;
    }
    if (fltselect != 0)
    {
        goto label_0972_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0972_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0972_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(302), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0972_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 4)) * 100) + 1;
    dblist(0, dbmax) = 302;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0972_internal:
    if (1 > objlv)
    {
        goto label_0973_internal;
    }
    if (fltselect != 0)
    {
        goto label_0973_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 64000)
        {
            goto label_0973_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0973_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(301), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0973_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 301;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0973_internal:
    if (7 > objlv)
    {
        goto label_0974_internal;
    }
    if (fltselect != 0)
    {
        goto label_0974_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0974_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0974_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(300), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0974_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 7)) * 100) + 1;
    dblist(0, dbmax) = 300;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0974_internal:
    if (14 > objlv)
    {
        goto label_0975_internal;
    }
    if (fltselect != 0)
    {
        goto label_0975_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0975_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0975_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(299), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0975_internal;
        }
    }
    dbsum += 150000 / (1000 + abs((objlv - 14)) * 100) + 1;
    dblist(0, dbmax) = 299;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0975_internal:
    if (7 > objlv)
    {
        goto label_0976_internal;
    }
    if (fltselect != 0)
    {
        goto label_0976_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0976_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0976_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(298), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0976_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 7)) * 100) + 1;
    dblist(0, dbmax) = 298;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0976_internal:
    if (15 > objlv)
    {
        goto label_0977_internal;
    }
    if (fltselect != 0)
    {
        goto label_0977_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0977_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60004)
        {
            goto label_0977_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(297), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0977_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 297;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0977_internal:
    if (18 > objlv)
    {
        goto label_0978_internal;
    }
    if (fltselect != 0)
    {
        goto label_0978_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0978_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0978_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(296), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0978_internal;
        }
    }
    dbsum += 250000 / (1000 + abs((objlv - 18)) * 100) + 1;
    dblist(0, dbmax) = 296;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0978_internal:
    if (1 > objlv)
    {
        goto label_0979_internal;
    }
    if (fltselect != 0)
    {
        goto label_0979_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0979_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0979_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(295), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0979_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 295;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0979_internal:
    if (1 > objlv)
    {
        goto label_0980_internal;
    }
    if (fltselect != 0)
    {
        goto label_0980_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0980_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0980_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(294), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0980_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 294;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0980_internal:
    if (1 > objlv)
    {
        goto label_0981_internal;
    }
    if (fltselect != 0)
    {
        goto label_0981_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0981_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0981_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(293), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0981_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 293;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0981_internal:
    if (1 > objlv)
    {
        goto label_0982_internal;
    }
    if (fltselect != 0)
    {
        goto label_0982_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0982_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0982_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(292), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0982_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 292;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0982_internal:
    if (1 > objlv)
    {
        goto label_0983_internal;
    }
    if (fltselect != 0)
    {
        goto label_0983_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0983_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0983_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(291), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0983_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 291;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0983_internal:
    if (10 > objlv)
    {
        goto label_0984_internal;
    }
    if (fltselect != 0)
    {
        goto label_0984_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 56000)
        {
            goto label_0984_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0984_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(290), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0984_internal;
        }
    }
    dbsum += 20000 / (1000 + abs((objlv - 10)) * 0) + 1;
    dblist(0, dbmax) = 290;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0984_internal:
    if (15 > objlv)
    {
        goto label_0985_internal;
    }
    if (fltselect != 0)
    {
        goto label_0985_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_0985_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0985_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(289), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0985_internal;
        }
    }
    dbsum += 20000 / (1000 + abs((objlv - 15)) * 0) + 1;
    dblist(0, dbmax) = 289;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0985_internal:
    if (1 > objlv)
    {
        goto label_0986_internal;
    }
    if (fltselect != 0)
    {
        goto label_0986_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_0986_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0986_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(288), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0986_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 288;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0986_internal:
    if (10 > objlv)
    {
        goto label_0987_internal;
    }
    if (fltselect != 0)
    {
        goto label_0987_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0987_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0987_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(287), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0987_internal;
        }
    }
    dbsum += 80000 / (1000 + abs((objlv - 10)) * 0) + 1;
    dblist(0, dbmax) = 287;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0987_internal:
    if (1 > objlv)
    {
        goto label_0988_internal;
    }
    if (fltselect != 0)
    {
        goto label_0988_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0988_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 52001)
        {
            goto label_0988_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(286), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0988_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 286;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0988_internal:
    if (1 > objlv)
    {
        goto label_0989_internal;
    }
    if (fltselect != 0)
    {
        goto label_0989_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_0989_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 52001)
        {
            goto label_0989_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(285), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0989_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 285;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0989_internal:
    if (1 > objlv)
    {
        goto label_0990_internal;
    }
    if (fltselect != 1)
    {
        goto label_0990_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 72000)
        {
            goto label_0990_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0990_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(284), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0990_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 284;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0990_internal:
    if (1 > objlv)
    {
        goto label_0991_internal;
    }
    if (fltselect != 1)
    {
        goto label_0991_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 72000)
        {
            goto label_0991_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0991_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(283), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0991_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 283;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0991_internal:
    if (1 > objlv)
    {
        goto label_0992_internal;
    }
    if (fltselect != 0)
    {
        goto label_0992_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0992_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0992_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(282), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0992_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 282;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0992_internal:
    if (1 > objlv)
    {
        goto label_0993_internal;
    }
    if (fltselect != 0)
    {
        goto label_0993_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0993_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0993_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(281), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0993_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 281;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0993_internal:
    if (1 > objlv)
    {
        goto label_0994_internal;
    }
    if (fltselect != 0)
    {
        goto label_0994_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0994_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0994_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(280), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0994_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 280;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0994_internal:
    if (1 > objlv)
    {
        goto label_0995_internal;
    }
    if (fltselect != 0)
    {
        goto label_0995_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0995_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0995_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(279), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0995_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 279;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0995_internal:
    if (10 > objlv)
    {
        goto label_0996_internal;
    }
    if (fltselect != 0)
    {
        goto label_0996_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0996_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0996_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(278), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0996_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 10)) * 100) + 1;
    dblist(0, dbmax) = 278;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0996_internal:
    if (4 > objlv)
    {
        goto label_0997_internal;
    }
    if (fltselect != 0)
    {
        goto label_0997_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0997_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0997_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(277), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0997_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 4)) * 100) + 1;
    dblist(0, dbmax) = 277;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0997_internal:
    if (8 > objlv)
    {
        goto label_0998_internal;
    }
    if (fltselect != 0)
    {
        goto label_0998_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_0998_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0998_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(276), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0998_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 8)) * 100) + 1;
    dblist(0, dbmax) = 276;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0998_internal:
    if (1 > objlv)
    {
        goto label_0999_internal;
    }
    if (fltselect != 0)
    {
        goto label_0999_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 64000)
        {
            goto label_0999_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_0999_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(275), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_0999_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 275;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_0999_internal:
    if (1 > objlv)
    {
        goto label_1000_internal;
    }
    if (fltselect != 0)
    {
        goto label_1000_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 64000)
        {
            goto label_1000_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1000_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(274), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1000_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 274;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1000_internal:
    if (1 > objlv)
    {
        goto label_1001_internal;
    }
    if (fltselect != 0)
    {
        goto label_1001_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 64000)
        {
            goto label_1001_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1001_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(273), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1001_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 273;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1001_internal:
    if (15 > objlv)
    {
        goto label_1002_internal;
    }
    if (fltselect != 0)
    {
        goto label_1002_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_1002_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1002_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(272), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1002_internal;
        }
    }
    dbsum += 700000 / (1000 + abs((objlv - 15)) * 0) + 1;
    dblist(0, dbmax) = 272;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1002_internal:
    if (10 > objlv)
    {
        goto label_1003_internal;
    }
    if (fltselect != 0)
    {
        goto label_1003_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_1003_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1003_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(271), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1003_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 10)) * 0) + 1;
    dblist(0, dbmax) = 271;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1003_internal:
    if (3 > objlv)
    {
        goto label_1004_internal;
    }
    if (fltselect != 0)
    {
        goto label_1004_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_1004_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1004_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(270), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1004_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 3)) * 0) + 1;
    dblist(0, dbmax) = 270;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1004_internal:
    if (3 > objlv)
    {
        goto label_1005_internal;
    }
    if (fltselect != 0)
    {
        goto label_1005_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_1005_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1005_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(269), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1005_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 3)) * 0) + 1;
    dblist(0, dbmax) = 269;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1005_internal:
    if (5 > objlv)
    {
        goto label_1006_internal;
    }
    if (fltselect != 0)
    {
        goto label_1006_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_1006_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1006_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(268), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1006_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 5)) * 0) + 1;
    dblist(0, dbmax) = 268;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1006_internal:
    if (3 > objlv)
    {
        goto label_1007_internal;
    }
    if (fltselect != 0)
    {
        goto label_1007_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_1007_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1007_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(267), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1007_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 3)) * 0) + 1;
    dblist(0, dbmax) = 267;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1007_internal:
    if (1 > objlv)
    {
        goto label_1008_internal;
    }
    if (fltselect != 0)
    {
        goto label_1008_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_1008_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10003)
        {
            goto label_1008_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(266), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1008_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 266;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1008_internal:
    if (10 > objlv)
    {
        goto label_1009_internal;
    }
    if (fltselect != 0)
    {
        goto label_1009_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_1009_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1009_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(265), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1009_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 10)) * 0) + 1;
    dblist(0, dbmax) = 265;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1009_internal:
    if (12 > objlv)
    {
        goto label_1010_internal;
    }
    if (fltselect != 0)
    {
        goto label_1010_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_1010_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1010_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(264), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1010_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 12)) * 0) + 1;
    dblist(0, dbmax) = 264;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1010_internal:
    if (6 > objlv)
    {
        goto label_1011_internal;
    }
    if (fltselect != 0)
    {
        goto label_1011_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_1011_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1011_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(263), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1011_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 6)) * 0) + 1;
    dblist(0, dbmax) = 263;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1011_internal:
    if (1 > objlv)
    {
        goto label_1012_internal;
    }
    if (fltselect != 0)
    {
        goto label_1012_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_1012_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1012_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(262), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1012_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 262;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1012_internal:
    if (3 > objlv)
    {
        goto label_1013_internal;
    }
    if (fltselect != 0)
    {
        goto label_1013_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1013_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1013_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(261), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1013_internal;
        }
    }
    dbsum += 5000000 / (1000 + abs((objlv - 3)) * 100) + 1;
    dblist(0, dbmax) = 261;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1013_internal:
    if (3 > objlv)
    {
        goto label_1014_internal;
    }
    if (fltselect != 0)
    {
        goto label_1014_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1014_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 57001)
        {
            goto label_1014_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(260), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1014_internal;
        }
    }
    dbsum += 5000000 / (1000 + abs((objlv - 3)) * 100) + 1;
    dblist(0, dbmax) = 260;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1014_internal:
    if (3 > objlv)
    {
        goto label_1015_internal;
    }
    if (fltselect != 0)
    {
        goto label_1015_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1015_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 57002)
        {
            goto label_1015_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(259), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1015_internal;
        }
    }
    dbsum += 5000000 / (1000 + abs((objlv - 3)) * 100) + 1;
    dblist(0, dbmax) = 259;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1015_internal:
    if (3 > objlv)
    {
        goto label_1016_internal;
    }
    if (fltselect != 0)
    {
        goto label_1016_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1016_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1016_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(258), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1016_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 3)) * 100) + 1;
    dblist(0, dbmax) = 258;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1016_internal:
    if (1 > objlv)
    {
        goto label_1017_internal;
    }
    if (fltselect != 0)
    {
        goto label_1017_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_1017_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1017_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(257), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1017_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 257;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1017_internal:
    if (1 > objlv)
    {
        goto label_1018_internal;
    }
    if (fltselect != 0)
    {
        goto label_1018_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_1018_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1018_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(256), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1018_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 256;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1018_internal:
    if (1 > objlv)
    {
        goto label_1019_internal;
    }
    if (fltselect != 0)
    {
        goto label_1019_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_1019_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1019_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(255), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1019_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 255;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1019_internal:
    if (5 > objlv)
    {
        goto label_1020_internal;
    }
    if (fltselect != 0)
    {
        goto label_1020_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1020_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60005)
        {
            goto label_1020_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(254), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1020_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 5)) * 100) + 1;
    dblist(0, dbmax) = 254;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1020_internal:
    if (1 > objlv)
    {
        goto label_1021_internal;
    }
    if (fltselect != 0)
    {
        goto label_1021_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_1021_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 52002)
        {
            goto label_1021_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(253), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1021_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 253;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1021_internal:
    if (15 > objlv)
    {
        goto label_1022_internal;
    }
    if (fltselect != 0)
    {
        goto label_1022_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_1022_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1022_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(252), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1022_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 15)) * 0) + 1;
    dblist(0, dbmax) = 252;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1022_internal:
    if (10 > objlv)
    {
        goto label_1023_internal;
    }
    if (fltselect != 0)
    {
        goto label_1023_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_1023_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1023_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(251), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1023_internal;
        }
    }
    dbsum += 700000 / (1000 + abs((objlv - 10)) * 0) + 1;
    dblist(0, dbmax) = 251;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1023_internal:
    if (8 > objlv)
    {
        goto label_1024_internal;
    }
    if (fltselect != 0)
    {
        goto label_1024_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_1024_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1024_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(250), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1024_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 8)) * 0) + 1;
    dblist(0, dbmax) = 250;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1024_internal:
    if (1 > objlv)
    {
        goto label_1025_internal;
    }
    if (fltselect != 0)
    {
        goto label_1025_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_1025_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1025_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(249), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1025_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 249;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1025_internal:
    if (8 > objlv)
    {
        goto label_1026_internal;
    }
    if (fltselect != 0)
    {
        goto label_1026_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_1026_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1026_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(248), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1026_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 8)) * 0) + 1;
    dblist(0, dbmax) = 248;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1026_internal:
    if (15 > objlv)
    {
        goto label_1027_internal;
    }
    if (fltselect != 0)
    {
        goto label_1027_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_1027_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1027_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(247), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1027_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 15)) * 0) + 1;
    dblist(0, dbmax) = 247;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1027_internal:
    if (12 > objlv)
    {
        goto label_1028_internal;
    }
    if (fltselect != 0)
    {
        goto label_1028_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_1028_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1028_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(246), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1028_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 12)) * 0) + 1;
    dblist(0, dbmax) = 246;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1028_internal:
    if (1 > objlv)
    {
        goto label_1029_internal;
    }
    if (fltselect != 0)
    {
        goto label_1029_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_1029_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1029_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(245), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1029_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 245;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1029_internal:
    if (5 > objlv)
    {
        goto label_1030_internal;
    }
    if (fltselect != 0)
    {
        goto label_1030_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_1030_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1030_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(244), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1030_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 5)) * 0) + 1;
    dblist(0, dbmax) = 244;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1030_internal:
    if (15 > objlv)
    {
        goto label_1031_internal;
    }
    if (fltselect != 0)
    {
        goto label_1031_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_1031_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1031_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(243), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1031_internal;
        }
    }
    dbsum += 25000 / (1000 + abs((objlv - 15)) * 0) + 1;
    dblist(0, dbmax) = 243;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1031_internal:
    if (1 > objlv)
    {
        goto label_1032_internal;
    }
    if (fltselect != 0)
    {
        goto label_1032_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_1032_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1032_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(242), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1032_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 242;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1032_internal:
    if (1 > objlv)
    {
        goto label_1033_internal;
    }
    if (fltselect != 0)
    {
        goto label_1033_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 72000)
        {
            goto label_1033_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1033_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(241), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1033_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 241;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1033_internal:
    if (1 > objlv)
    {
        goto label_1034_internal;
    }
    if (fltselect != 0)
    {
        goto label_1034_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 72000)
        {
            goto label_1034_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1034_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(240), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1034_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 240;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1034_internal:
    if (1 > objlv)
    {
        goto label_1035_internal;
    }
    if (fltselect != 0)
    {
        goto label_1035_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 72000)
        {
            goto label_1035_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1035_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(239), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1035_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 239;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1035_internal:
    if (1 > objlv)
    {
        goto label_1036_internal;
    }
    if (fltselect != 0)
    {
        goto label_1036_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1036_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1036_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(238), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1036_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 238;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1036_internal:
    if (1 > objlv)
    {
        goto label_1037_internal;
    }
    if (fltselect != 0)
    {
        goto label_1037_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1037_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1037_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(237), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1037_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 237;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1037_internal:
    if (1 > objlv)
    {
        goto label_1038_internal;
    }
    if (fltselect != 0)
    {
        goto label_1038_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_1038_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1038_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(236), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1038_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 236;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1038_internal:
    if (1 > objlv)
    {
        goto label_1039_internal;
    }
    if (fltselect != 0)
    {
        goto label_1039_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_1039_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10008)
        {
            goto label_1039_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(235), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1039_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 235;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1039_internal:
    if (1 > objlv)
    {
        goto label_1040_internal;
    }
    if (fltselect != 0)
    {
        goto label_1040_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_1040_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10010)
        {
            goto label_1040_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(234), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1040_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 234;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1040_internal:
    if (3 > objlv)
    {
        goto label_1041_internal;
    }
    if (fltselect != 0)
    {
        goto label_1041_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1041_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1041_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(233), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1041_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 3)) * 100) + 1;
    dblist(0, dbmax) = 233;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1041_internal:
    if (1 > objlv)
    {
        goto label_1042_internal;
    }
    if (fltselect != 0)
    {
        goto label_1042_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_1042_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10001)
        {
            goto label_1042_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(232), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1042_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 232;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1042_internal:
    if (1 > objlv)
    {
        goto label_1043_internal;
    }
    if (fltselect != 0)
    {
        goto label_1043_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 24000)
        {
            goto label_1043_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 24020)
        {
            goto label_1043_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(231), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1043_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 231;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1043_internal:
    if (1 > objlv)
    {
        goto label_1044_internal;
    }
    if (fltselect != 0)
    {
        goto label_1044_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 24000)
        {
            goto label_1044_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 24001)
        {
            goto label_1044_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(230), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1044_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 230;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1044_internal:
    if (1 > objlv)
    {
        goto label_1045_internal;
    }
    if (fltselect != 0)
    {
        goto label_1045_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_1045_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10006)
        {
            goto label_1045_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(229), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1045_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 229;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1045_internal:
    if (1 > objlv)
    {
        goto label_1046_internal;
    }
    if (fltselect != 0)
    {
        goto label_1046_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_1046_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10007)
        {
            goto label_1046_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(228), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1046_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 228;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1046_internal:
    if (1 > objlv)
    {
        goto label_1047_internal;
    }
    if (fltselect != 0)
    {
        goto label_1047_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_1047_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10005)
        {
            goto label_1047_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(227), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1047_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 227;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1047_internal:
    if (1 > objlv)
    {
        goto label_1048_internal;
    }
    if (fltselect != 0)
    {
        goto label_1048_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_1048_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10010)
        {
            goto label_1048_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(226), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1048_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 226;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1048_internal:
    if (1 > objlv)
    {
        goto label_1049_internal;
    }
    if (fltselect != 0)
    {
        goto label_1049_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_1049_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10003)
        {
            goto label_1049_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(225), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1049_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 225;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1049_internal:
    if (1 > objlv)
    {
        goto label_1050_internal;
    }
    if (fltselect != 0)
    {
        goto label_1050_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_1050_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10002)
        {
            goto label_1050_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(224), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1050_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 224;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1050_internal:
    if (1 > objlv)
    {
        goto label_1051_internal;
    }
    if (fltselect != 0)
    {
        goto label_1051_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_1051_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1051_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(223), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1051_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 223;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1051_internal:
    if (1 > objlv)
    {
        goto label_1052_internal;
    }
    if (fltselect != 0)
    {
        goto label_1052_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 64000)
        {
            goto label_1052_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 64000)
        {
            goto label_1052_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(222), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1052_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 222;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1052_internal:
    if (1 > objlv)
    {
        goto label_1053_internal;
    }
    if (fltselect != 0)
    {
        goto label_1053_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 64000)
        {
            goto label_1053_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1053_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(221), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1053_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 221;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1053_internal:
    if (1 > objlv)
    {
        goto label_1054_internal;
    }
    if (fltselect != 0)
    {
        goto label_1054_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 64000)
        {
            goto label_1054_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 64000)
        {
            goto label_1054_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(220), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1054_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 220;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1054_internal:
    if (1 > objlv)
    {
        goto label_1055_internal;
    }
    if (fltselect != 0)
    {
        goto label_1055_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_1055_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 64000)
        {
            goto label_1055_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(219), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1055_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 219;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1055_internal:
    if (1 > objlv)
    {
        goto label_1056_internal;
    }
    if (fltselect != 0)
    {
        goto label_1056_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 64000)
        {
            goto label_1056_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1056_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(218), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1056_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 218;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1056_internal:
    if (1 > objlv)
    {
        goto label_1057_internal;
    }
    if (fltselect != 0)
    {
        goto label_1057_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 64000)
        {
            goto label_1057_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1057_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(217), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1057_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 217;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1057_internal:
    if (1 > objlv)
    {
        goto label_1058_internal;
    }
    if (fltselect != 0)
    {
        goto label_1058_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 64000)
        {
            goto label_1058_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1058_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(216), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1058_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 216;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1058_internal:
    if (1 > objlv)
    {
        goto label_1059_internal;
    }
    if (fltselect != 0)
    {
        goto label_1059_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 64000)
        {
            goto label_1059_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 64100)
        {
            goto label_1059_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(215), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1059_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 215;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1059_internal:
    if (1 > objlv)
    {
        goto label_1060_internal;
    }
    if (fltselect != 0)
    {
        goto label_1060_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 64000)
        {
            goto label_1060_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 64000)
        {
            goto label_1060_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(214), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1060_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 214;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1060_internal:
    if (1 > objlv)
    {
        goto label_1061_internal;
    }
    if (fltselect != 0)
    {
        goto label_1061_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_1061_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10007)
        {
            goto label_1061_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(213), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1061_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 213;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1061_internal:
    if (1 > objlv)
    {
        goto label_1062_internal;
    }
    if (fltselect != 0)
    {
        goto label_1062_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_1062_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10006)
        {
            goto label_1062_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(212), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1062_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 212;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1062_internal:
    if (1 > objlv)
    {
        goto label_1063_internal;
    }
    if (fltselect != 0)
    {
        goto label_1063_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_1063_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10011)
        {
            goto label_1063_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(211), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1063_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 211;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1063_internal:
    if (1 > objlv)
    {
        goto label_1064_internal;
    }
    if (fltselect != 0)
    {
        goto label_1064_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 24000)
        {
            goto label_1064_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 24030)
        {
            goto label_1064_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(210), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1064_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 210;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1064_internal:
    if (1 > objlv)
    {
        goto label_1065_internal;
    }
    if (fltselect != 0)
    {
        goto label_1065_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_1065_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1065_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(209), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1065_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 209;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1065_internal:
    if (1 > objlv)
    {
        goto label_1066_internal;
    }
    if (fltselect != 0)
    {
        goto label_1066_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 77000)
        {
            goto label_1066_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1066_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(208), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1066_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 208;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1066_internal:
    if (35 > objlv)
    {
        goto label_1067_internal;
    }
    if (fltselect != 2)
    {
        goto label_1067_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 24000)
        {
            goto label_1067_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 24001)
        {
            goto label_1067_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(207), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1067_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 35)) * 100) + 1;
    dblist(0, dbmax) = 207;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1067_internal:
    if (40 > objlv)
    {
        goto label_1068_internal;
    }
    if (fltselect != 2)
    {
        goto label_1068_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_1068_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10003)
        {
            goto label_1068_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(206), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1068_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 40)) * 100) + 1;
    dblist(0, dbmax) = 206;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1068_internal:
    if (1 > objlv)
    {
        goto label_1069_internal;
    }
    if (fltselect != 0)
    {
        goto label_1069_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_1069_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 52002)
        {
            goto label_1069_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(205), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1069_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 205;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1069_internal:
    if (1 > objlv)
    {
        goto label_1070_internal;
    }
    if (fltselect != 0)
    {
        goto label_1070_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1070_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1070_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(204), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1070_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 204;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1070_internal:
    if (10 > objlv)
    {
        goto label_1071_internal;
    }
    if (fltselect != 0)
    {
        goto label_1071_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 56000)
        {
            goto label_1071_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1071_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(203), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1071_internal;
        }
    }
    dbsum += 800000 / (1000 + abs((objlv - 10)) * 0) + 1;
    dblist(0, dbmax) = 203;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1071_internal:
    if (4 > objlv)
    {
        goto label_1072_internal;
    }
    if (fltselect != 0)
    {
        goto label_1072_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 56000)
        {
            goto label_1072_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1072_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(202), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1072_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 4)) * 0) + 1;
    dblist(0, dbmax) = 202;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1072_internal:
    if (1 > objlv)
    {
        goto label_1073_internal;
    }
    if (fltselect != 0)
    {
        goto label_1073_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1073_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 57003)
        {
            goto label_1073_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(201), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1073_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 201;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1073_internal:
    if (1 > objlv)
    {
        goto label_1074_internal;
    }
    if (fltselect != 0)
    {
        goto label_1074_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1074_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 57003)
        {
            goto label_1074_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(200), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1074_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 200;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1074_internal:
    if (1 > objlv)
    {
        goto label_1075_internal;
    }
    if (fltselect != 0)
    {
        goto label_1075_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1075_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 57003)
        {
            goto label_1075_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(199), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1075_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 199;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1075_internal:
    if (1 > objlv)
    {
        goto label_1076_internal;
    }
    if (fltselect != 0)
    {
        goto label_1076_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1076_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 57003)
        {
            goto label_1076_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(198), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1076_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 198;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1076_internal:
    if (1 > objlv)
    {
        goto label_1077_internal;
    }
    if (fltselect != 0)
    {
        goto label_1077_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1077_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 57004)
        {
            goto label_1077_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(197), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1077_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 197;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1077_internal:
    if (1 > objlv)
    {
        goto label_1078_internal;
    }
    if (fltselect != 0)
    {
        goto label_1078_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1078_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 57004)
        {
            goto label_1078_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(196), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1078_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 196;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1078_internal:
    if (1 > objlv)
    {
        goto label_1079_internal;
    }
    if (fltselect != 0)
    {
        goto label_1079_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1079_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 57004)
        {
            goto label_1079_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(195), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1079_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 195;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1079_internal:
    if (1 > objlv)
    {
        goto label_1080_internal;
    }
    if (fltselect != 0)
    {
        goto label_1080_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1080_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 57004)
        {
            goto label_1080_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(194), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1080_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 194;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1080_internal:
    if (1 > objlv)
    {
        goto label_1081_internal;
    }
    if (fltselect != 0)
    {
        goto label_1081_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1081_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 64000)
        {
            goto label_1081_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(193), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1081_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 193;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1081_internal:
    if (1 > objlv)
    {
        goto label_1082_internal;
    }
    if (fltselect != 0)
    {
        goto label_1082_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1082_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1082_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(192), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1082_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 192;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1082_internal:
    if (1 > objlv)
    {
        goto label_1083_internal;
    }
    if (fltselect != 0)
    {
        goto label_1083_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1083_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 64000)
        {
            goto label_1083_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(191), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1083_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 191;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1083_internal:
    if (1 > objlv)
    {
        goto label_1084_internal;
    }
    if (fltselect != 0)
    {
        goto label_1084_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1084_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 57003)
        {
            goto label_1084_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(190), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1084_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 190;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1084_internal:
    if (1 > objlv)
    {
        goto label_1085_internal;
    }
    if (fltselect != 0)
    {
        goto label_1085_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1085_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1085_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(189), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1085_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 189;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1085_internal:
    if (1 > objlv)
    {
        goto label_1086_internal;
    }
    if (fltselect != 0)
    {
        goto label_1086_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1086_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 57003)
        {
            goto label_1086_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(188), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1086_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 188;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1086_internal:
    if (1 > objlv)
    {
        goto label_1087_internal;
    }
    if (fltselect != 0)
    {
        goto label_1087_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1087_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 57003)
        {
            goto label_1087_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(187), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1087_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 187;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1087_internal:
    if (1 > objlv)
    {
        goto label_1088_internal;
    }
    if (fltselect != 0)
    {
        goto label_1088_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1088_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 57003)
        {
            goto label_1088_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(186), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1088_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 186;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1088_internal:
    if (1 > objlv)
    {
        goto label_1089_internal;
    }
    if (fltselect != 0)
    {
        goto label_1089_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1089_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 57003)
        {
            goto label_1089_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(185), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1089_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 185;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1089_internal:
    if (1 > objlv)
    {
        goto label_1090_internal;
    }
    if (fltselect != 0)
    {
        goto label_1090_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1090_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 57003)
        {
            goto label_1090_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(184), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1090_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 184;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1090_internal:
    if (1 > objlv)
    {
        goto label_1091_internal;
    }
    if (fltselect != 0)
    {
        goto label_1091_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1091_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 57004)
        {
            goto label_1091_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(183), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1091_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 183;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1091_internal:
    if (1 > objlv)
    {
        goto label_1092_internal;
    }
    if (fltselect != 0)
    {
        goto label_1092_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1092_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 57004)
        {
            goto label_1092_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(182), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1092_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 182;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1092_internal:
    if (1 > objlv)
    {
        goto label_1093_internal;
    }
    if (fltselect != 0)
    {
        goto label_1093_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1093_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 57004)
        {
            goto label_1093_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(181), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1093_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 181;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1093_internal:
    if (1 > objlv)
    {
        goto label_1094_internal;
    }
    if (fltselect != 0)
    {
        goto label_1094_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1094_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 57004)
        {
            goto label_1094_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(180), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1094_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 180;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1094_internal:
    if (1 > objlv)
    {
        goto label_1095_internal;
    }
    if (fltselect != 0)
    {
        goto label_1095_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1095_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 64000)
        {
            goto label_1095_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(179), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1095_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 179;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1095_internal:
    if (1 > objlv)
    {
        goto label_1096_internal;
    }
    if (fltselect != 0)
    {
        goto label_1096_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1096_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 57003)
        {
            goto label_1096_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(178), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1096_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 178;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1096_internal:
    if (1 > objlv)
    {
        goto label_1097_internal;
    }
    if (fltselect != 0)
    {
        goto label_1097_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 57000)
        {
            goto label_1097_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 57003)
        {
            goto label_1097_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(177), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1097_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 177;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1097_internal:
    if (3 > objlv)
    {
        goto label_1098_internal;
    }
    if (fltselect != 0)
    {
        goto label_1098_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 56000)
        {
            goto label_1098_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1098_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(176), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1098_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 3)) * 0) + 1;
    dblist(0, dbmax) = 176;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1098_internal:
    if (8 > objlv)
    {
        goto label_1099_internal;
    }
    if (fltselect != 0)
    {
        goto label_1099_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 56000)
        {
            goto label_1099_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1099_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(175), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1099_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 8)) * 0) + 1;
    dblist(0, dbmax) = 175;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1099_internal:
    if (5 > objlv)
    {
        goto label_1100_internal;
    }
    if (fltselect != 0)
    {
        goto label_1100_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1100_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60004)
        {
            goto label_1100_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(174), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1100_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 5)) * 100) + 1;
    dblist(0, dbmax) = 174;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1100_internal:
    if (1 > objlv)
    {
        goto label_1101_internal;
    }
    if (fltselect != 1)
    {
        goto label_1101_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60001)
        {
            goto label_1101_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60001)
        {
            goto label_1101_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(173), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1101_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 173;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1101_internal:
    if (1 > objlv)
    {
        goto label_1102_internal;
    }
    if (fltselect != 1)
    {
        goto label_1102_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60002)
        {
            goto label_1102_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60002)
        {
            goto label_1102_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(172), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1102_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 172;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1102_internal:
    if (1 > objlv)
    {
        goto label_1103_internal;
    }
    if (fltselect != 1)
    {
        goto label_1103_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60002)
        {
            goto label_1103_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60002)
        {
            goto label_1103_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(171), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1103_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 171;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1103_internal:
    if (10 > objlv)
    {
        goto label_1104_internal;
    }
    if (fltselect != 0)
    {
        goto label_1104_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1104_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1104_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(170), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1104_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 10)) * 100) + 1;
    dblist(0, dbmax) = 170;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1104_internal:
    if (20 > objlv)
    {
        goto label_1105_internal;
    }
    if (fltselect != 0)
    {
        goto label_1105_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1105_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1105_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(169), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1105_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 20)) * 100) + 1;
    dblist(0, dbmax) = 169;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1105_internal:
    if (10 > objlv)
    {
        goto label_1106_internal;
    }
    if (fltselect != 0)
    {
        goto label_1106_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1106_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1106_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(168), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1106_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 10)) * 100) + 1;
    dblist(0, dbmax) = 168;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1106_internal:
    if (5 > objlv)
    {
        goto label_1107_internal;
    }
    if (fltselect != 0)
    {
        goto label_1107_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1107_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1107_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(167), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1107_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 5)) * 100) + 1;
    dblist(0, dbmax) = 167;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1107_internal:
    if (5 > objlv)
    {
        goto label_1108_internal;
    }
    if (fltselect != 0)
    {
        goto label_1108_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1108_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 64000)
        {
            goto label_1108_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(166), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1108_internal;
        }
    }
    dbsum += 50000 / (1000 + abs((objlv - 5)) * 100) + 1;
    dblist(0, dbmax) = 166;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1108_internal:
    if (1 > objlv)
    {
        goto label_1109_internal;
    }
    if (fltselect != 0)
    {
        goto label_1109_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1109_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 64000)
        {
            goto label_1109_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(165), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1109_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 165;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1109_internal:
    if (1 > objlv)
    {
        goto label_1110_internal;
    }
    if (fltselect != 0)
    {
        goto label_1110_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1110_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 64000)
        {
            goto label_1110_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(164), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1110_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 164;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1110_internal:
    if (4 > objlv)
    {
        goto label_1111_internal;
    }
    if (fltselect != 0)
    {
        goto label_1111_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1111_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1111_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(163), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1111_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 4)) * 100) + 1;
    dblist(0, dbmax) = 163;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1111_internal:
    if (1 > objlv)
    {
        goto label_1112_internal;
    }
    if (fltselect != 0)
    {
        goto label_1112_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1112_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1112_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(162), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1112_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 162;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1112_internal:
    if (1 > objlv)
    {
        goto label_1113_internal;
    }
    if (fltselect != 0)
    {
        goto label_1113_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_1113_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1113_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(161), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1113_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 161;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1113_internal:
    if (1 > objlv)
    {
        goto label_1114_internal;
    }
    if (fltselect != 0)
    {
        goto label_1114_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_1114_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1114_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(160), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1114_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 160;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1114_internal:
    if (1 > objlv)
    {
        goto label_1115_internal;
    }
    if (fltselect != 0)
    {
        goto label_1115_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1115_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1115_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(159), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1115_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 159;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1115_internal:
    if (1 > objlv)
    {
        goto label_1116_internal;
    }
    if (fltselect != 0)
    {
        goto label_1116_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1116_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1116_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(158), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1116_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 158;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1116_internal:
    if (14 > objlv)
    {
        goto label_1117_internal;
    }
    if (fltselect != 0)
    {
        goto label_1117_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1117_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1117_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(157), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1117_internal;
        }
    }
    dbsum += 250000 / (1000 + abs((objlv - 14)) * 100) + 1;
    dblist(0, dbmax) = 157;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1117_internal:
    if (1 > objlv)
    {
        goto label_1118_internal;
    }
    if (fltselect != 0)
    {
        goto label_1118_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1118_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1118_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(156), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1118_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 156;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1118_internal:
    if (4 > objlv)
    {
        goto label_1119_internal;
    }
    if (fltselect != 0)
    {
        goto label_1119_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1119_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1119_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(155), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1119_internal;
        }
    }
    dbsum += 250000 / (1000 + abs((objlv - 4)) * 100) + 1;
    dblist(0, dbmax) = 155;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1119_internal:
    if (4 > objlv)
    {
        goto label_1120_internal;
    }
    if (fltselect != 0)
    {
        goto label_1120_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1120_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1120_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(154), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1120_internal;
        }
    }
    dbsum += 250000 / (1000 + abs((objlv - 4)) * 100) + 1;
    dblist(0, dbmax) = 154;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1120_internal:
    if (4 > objlv)
    {
        goto label_1121_internal;
    }
    if (fltselect != 0)
    {
        goto label_1121_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1121_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1121_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(153), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1121_internal;
        }
    }
    dbsum += 250000 / (1000 + abs((objlv - 4)) * 100) + 1;
    dblist(0, dbmax) = 153;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1121_internal:
    if (1 > objlv)
    {
        goto label_1122_internal;
    }
    if (fltselect != 0)
    {
        goto label_1122_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1122_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1122_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(152), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1122_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 152;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1122_internal:
    if (17 > objlv)
    {
        goto label_1123_internal;
    }
    if (fltselect != 0)
    {
        goto label_1123_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1123_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1123_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(151), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1123_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 17)) * 100) + 1;
    dblist(0, dbmax) = 151;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1123_internal:
    if (17 > objlv)
    {
        goto label_1124_internal;
    }
    if (fltselect != 0)
    {
        goto label_1124_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1124_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1124_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(150), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1124_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 17)) * 100) + 1;
    dblist(0, dbmax) = 150;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1124_internal:
    if (1 > objlv)
    {
        goto label_1125_internal;
    }
    if (fltselect != 0)
    {
        goto label_1125_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1125_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1125_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(149), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1125_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 149;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1125_internal:
    if (1 > objlv)
    {
        goto label_1126_internal;
    }
    if (fltselect != 0)
    {
        goto label_1126_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1126_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1126_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(148), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1126_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 148;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1126_internal:
    if (1 > objlv)
    {
        goto label_1127_internal;
    }
    if (fltselect != 0)
    {
        goto label_1127_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1127_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1127_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(147), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1127_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 147;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1127_internal:
    if (1 > objlv)
    {
        goto label_1128_internal;
    }
    if (fltselect != 0)
    {
        goto label_1128_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1128_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1128_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(146), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1128_internal;
        }
    }
    dbsum += 250000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 146;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1128_internal:
    if (1 > objlv)
    {
        goto label_1129_internal;
    }
    if (fltselect != 0)
    {
        goto label_1129_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1129_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1129_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(145), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1129_internal;
        }
    }
    dbsum += 250000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 145;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1129_internal:
    if (1 > objlv)
    {
        goto label_1130_internal;
    }
    if (fltselect != 0)
    {
        goto label_1130_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1130_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1130_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(144), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1130_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 144;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1130_internal:
    if (1 > objlv)
    {
        goto label_1131_internal;
    }
    if (fltselect != 0)
    {
        goto label_1131_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1131_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1131_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(143), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1131_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 143;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1131_internal:
    if (14 > objlv)
    {
        goto label_1132_internal;
    }
    if (fltselect != 0)
    {
        goto label_1132_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1132_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1132_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(142), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1132_internal;
        }
    }
    dbsum += 150000 / (1000 + abs((objlv - 14)) * 100) + 1;
    dblist(0, dbmax) = 142;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1132_internal:
    if (1 > objlv)
    {
        goto label_1133_internal;
    }
    if (fltselect != 0)
    {
        goto label_1133_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1133_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1133_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(141), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1133_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 141;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1133_internal:
    if (1 > objlv)
    {
        goto label_1134_internal;
    }
    if (fltselect != 0)
    {
        goto label_1134_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_1134_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1134_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(140), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1134_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 140;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1134_internal:
    if (20 > objlv)
    {
        goto label_1135_internal;
    }
    if (fltselect != 0)
    {
        goto label_1135_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1135_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1135_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(139), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1135_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 20)) * 100) + 1;
    dblist(0, dbmax) = 139;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1135_internal:
    if (18 > objlv)
    {
        goto label_1136_internal;
    }
    if (fltselect != 0)
    {
        goto label_1136_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1136_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1136_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(138), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1136_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 18)) * 100) + 1;
    dblist(0, dbmax) = 138;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1136_internal:
    if (1 > objlv)
    {
        goto label_1137_internal;
    }
    if (fltselect != 0)
    {
        goto label_1137_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1137_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1137_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(137), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1137_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 137;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1137_internal:
    if (1 > objlv)
    {
        goto label_1138_internal;
    }
    if (fltselect != 0)
    {
        goto label_1138_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1138_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1138_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(136), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1138_internal;
        }
    }
    dbsum += 250000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 136;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1138_internal:
    if (1 > objlv)
    {
        goto label_1139_internal;
    }
    if (fltselect != 0)
    {
        goto label_1139_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1139_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1139_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(135), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1139_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 135;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1139_internal:
    if (1 > objlv)
    {
        goto label_1140_internal;
    }
    if (fltselect != 0)
    {
        goto label_1140_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1140_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1140_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(134), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1140_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 134;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1140_internal:
    if (1 > objlv)
    {
        goto label_1141_internal;
    }
    if (fltselect != 0)
    {
        goto label_1141_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1141_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1141_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(133), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1141_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 133;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1141_internal:
    if (1 > objlv)
    {
        goto label_1142_internal;
    }
    if (fltselect != 0)
    {
        goto label_1142_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1142_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1142_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(132), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1142_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 132;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1142_internal:
    if (11 > objlv)
    {
        goto label_1143_internal;
    }
    if (fltselect != 0)
    {
        goto label_1143_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1143_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1143_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(131), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1143_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 11)) * 100) + 1;
    dblist(0, dbmax) = 131;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1143_internal:
    if (9 > objlv)
    {
        goto label_1144_internal;
    }
    if (fltselect != 0)
    {
        goto label_1144_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1144_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1144_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(130), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1144_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 9)) * 100) + 1;
    dblist(0, dbmax) = 130;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1144_internal:
    if (7 > objlv)
    {
        goto label_1145_internal;
    }
    if (fltselect != 0)
    {
        goto label_1145_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1145_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1145_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(129), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1145_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 7)) * 100) + 1;
    dblist(0, dbmax) = 129;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1145_internal:
    if (1 > objlv)
    {
        goto label_1146_internal;
    }
    if (fltselect != 0)
    {
        goto label_1146_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1146_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1146_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(128), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1146_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 128;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1146_internal:
    if (1 > objlv)
    {
        goto label_1147_internal;
    }
    if (fltselect != 0)
    {
        goto label_1147_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 59000)
        {
            goto label_1147_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1147_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(127), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1147_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 127;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1147_internal:
    if (1 > objlv)
    {
        goto label_1148_internal;
    }
    if (fltselect != 0)
    {
        goto label_1148_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1148_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1148_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(126), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1148_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 126;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1148_internal:
    if (15 > objlv)
    {
        goto label_1149_internal;
    }
    if (fltselect != 0)
    {
        goto label_1149_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 56000)
        {
            goto label_1149_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1149_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(125), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1149_internal;
        }
    }
    dbsum += 250000 / (1000 + abs((objlv - 15)) * 0) + 1;
    dblist(0, dbmax) = 125;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1149_internal:
    if (1 > objlv)
    {
        goto label_1150_internal;
    }
    if (fltselect != 0)
    {
        goto label_1150_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1150_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1150_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(124), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1150_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 124;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1150_internal:
    if (8 > objlv)
    {
        goto label_1151_internal;
    }
    if (fltselect != 0)
    {
        goto label_1151_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 56000)
        {
            goto label_1151_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1151_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(123), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1151_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 8)) * 0) + 1;
    dblist(0, dbmax) = 123;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1151_internal:
    if (8 > objlv)
    {
        goto label_1152_internal;
    }
    if (fltselect != 0)
    {
        goto label_1152_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 56000)
        {
            goto label_1152_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1152_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(122), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1152_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 8)) * 0) + 1;
    dblist(0, dbmax) = 122;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1152_internal:
    if (1 > objlv)
    {
        goto label_1153_internal;
    }
    if (fltselect != 0)
    {
        goto label_1153_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 56000)
        {
            goto label_1153_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1153_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(121), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1153_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 121;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1153_internal:
    if (2 > objlv)
    {
        goto label_1154_internal;
    }
    if (fltselect != 0)
    {
        goto label_1154_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 56000)
        {
            goto label_1154_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1154_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(120), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1154_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 2)) * 0) + 1;
    dblist(0, dbmax) = 120;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1154_internal:
    if (3 > objlv)
    {
        goto label_1155_internal;
    }
    if (fltselect != 0)
    {
        goto label_1155_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 56000)
        {
            goto label_1155_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1155_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(119), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1155_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 3)) * 0) + 1;
    dblist(0, dbmax) = 119;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1155_internal:
    if (5 > objlv)
    {
        goto label_1156_internal;
    }
    if (fltselect != 0)
    {
        goto label_1156_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_1156_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1156_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(118), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1156_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 5)) * 0) + 1;
    dblist(0, dbmax) = 118;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1156_internal:
    if (1 > objlv)
    {
        goto label_1157_internal;
    }
    if (fltselect != 0)
    {
        goto label_1157_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 64000)
        {
            goto label_1157_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1157_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(117), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1157_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 117;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1157_internal:
    if (1 > objlv)
    {
        goto label_1158_internal;
    }
    if (fltselect != 0)
    {
        goto label_1158_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_1158_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1158_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(116), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1158_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 116;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1158_internal:
    if (1 > objlv)
    {
        goto label_1159_internal;
    }
    if (fltselect != 0)
    {
        goto label_1159_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1159_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1159_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(115), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1159_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 115;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1159_internal:
    if (1 > objlv)
    {
        goto label_1160_internal;
    }
    if (fltselect != 0)
    {
        goto label_1160_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1160_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1160_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(114), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1160_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 114;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1160_internal:
    if (1 > objlv)
    {
        goto label_1161_internal;
    }
    if (fltselect != 0)
    {
        goto label_1161_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1161_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1161_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(113), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1161_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 113;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1161_internal:
    if (22 > objlv)
    {
        goto label_1162_internal;
    }
    if (fltselect != 0)
    {
        goto label_1162_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1162_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1162_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(112), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1162_internal;
        }
    }
    dbsum += 150000 / (1000 + abs((objlv - 22)) * 100) + 1;
    dblist(0, dbmax) = 112;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1162_internal:
    if (17 > objlv)
    {
        goto label_1163_internal;
    }
    if (fltselect != 0)
    {
        goto label_1163_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1163_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1163_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(111), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1163_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 17)) * 100) + 1;
    dblist(0, dbmax) = 111;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1163_internal:
    if (5 > objlv)
    {
        goto label_1164_internal;
    }
    if (fltselect != 0)
    {
        goto label_1164_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1164_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1164_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(110), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1164_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 5)) * 100) + 1;
    dblist(0, dbmax) = 110;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1164_internal:
    if (1 > objlv)
    {
        goto label_1165_internal;
    }
    if (fltselect != 0)
    {
        goto label_1165_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60001)
        {
            goto label_1165_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60001)
        {
            goto label_1165_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(109), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1165_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 109;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1165_internal:
    if (3 > objlv)
    {
        goto label_1166_internal;
    }
    if (fltselect != 0)
    {
        goto label_1166_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1166_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1166_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(108), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1166_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 3)) * 100) + 1;
    dblist(0, dbmax) = 108;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1166_internal:
    if (1 > objlv)
    {
        goto label_1167_internal;
    }
    if (fltselect != 0)
    {
        goto label_1167_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1167_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1167_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(107), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1167_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 107;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1167_internal:
    if (7 > objlv)
    {
        goto label_1168_internal;
    }
    if (fltselect != 0)
    {
        goto label_1168_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1168_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1168_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(106), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1168_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 7)) * 100) + 1;
    dblist(0, dbmax) = 106;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1168_internal:
    if (7 > objlv)
    {
        goto label_1169_internal;
    }
    if (fltselect != 0)
    {
        goto label_1169_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1169_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1169_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(105), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1169_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 7)) * 100) + 1;
    dblist(0, dbmax) = 105;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1169_internal:
    if (1 > objlv)
    {
        goto label_1170_internal;
    }
    if (fltselect != 0)
    {
        goto label_1170_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1170_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1170_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(104), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1170_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 104;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1170_internal:
    if (11 > objlv)
    {
        goto label_1171_internal;
    }
    if (fltselect != 0)
    {
        goto label_1171_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1171_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1171_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(103), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1171_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 11)) * 100) + 1;
    dblist(0, dbmax) = 103;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1171_internal:
    if (1 > objlv)
    {
        goto label_1172_internal;
    }
    if (fltselect != 0)
    {
        goto label_1172_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1172_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1172_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(102), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1172_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 102;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1172_internal:
    if (1 > objlv)
    {
        goto label_1173_internal;
    }
    if (fltselect != 0)
    {
        goto label_1173_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1173_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1173_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(101), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1173_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 101;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1173_internal:
    if (13 > objlv)
    {
        goto label_1174_internal;
    }
    if (fltselect != 0)
    {
        goto label_1174_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1174_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1174_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(100), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1174_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 13)) * 100) + 1;
    dblist(0, dbmax) = 100;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1174_internal:
    if (1 > objlv)
    {
        goto label_1175_internal;
    }
    if (fltselect != 0)
    {
        goto label_1175_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1175_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1175_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(99), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1175_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 99;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1175_internal:
    if (1 > objlv)
    {
        goto label_1176_internal;
    }
    if (fltselect != 0)
    {
        goto label_1176_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1176_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1176_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(98), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1176_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 98;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1176_internal:
    if (1 > objlv)
    {
        goto label_1177_internal;
    }
    if (fltselect != 0)
    {
        goto label_1177_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1177_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1177_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(97), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1177_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 97;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1177_internal:
    if (9 > objlv)
    {
        goto label_1178_internal;
    }
    if (fltselect != 0)
    {
        goto label_1178_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1178_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1178_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(96), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1178_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 9)) * 100) + 1;
    dblist(0, dbmax) = 96;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1178_internal:
    if (7 > objlv)
    {
        goto label_1179_internal;
    }
    if (fltselect != 0)
    {
        goto label_1179_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1179_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1179_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(95), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1179_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 7)) * 100) + 1;
    dblist(0, dbmax) = 95;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1179_internal:
    if (1 > objlv)
    {
        goto label_1180_internal;
    }
    if (fltselect != 0)
    {
        goto label_1180_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1180_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1180_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(94), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1180_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 94;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1180_internal:
    if (1 > objlv)
    {
        goto label_1181_internal;
    }
    if (fltselect != 0)
    {
        goto label_1181_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1181_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1181_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(93), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1181_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 93;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1181_internal:
    if (3 > objlv)
    {
        goto label_1182_internal;
    }
    if (fltselect != 0)
    {
        goto label_1182_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1182_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1182_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(92), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1182_internal;
        }
    }
    dbsum += 600000 / (1000 + abs((objlv - 3)) * 100) + 1;
    dblist(0, dbmax) = 92;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1182_internal:
    if (1 > objlv)
    {
        goto label_1183_internal;
    }
    if (fltselect != 0)
    {
        goto label_1183_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1183_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1183_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(91), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1183_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 91;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1183_internal:
    if (12 > objlv)
    {
        goto label_1184_internal;
    }
    if (fltselect != 0)
    {
        goto label_1184_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1184_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1184_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(90), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1184_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 12)) * 100) + 1;
    dblist(0, dbmax) = 90;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1184_internal:
    if (12 > objlv)
    {
        goto label_1185_internal;
    }
    if (fltselect != 0)
    {
        goto label_1185_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1185_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1185_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(89), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1185_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 12)) * 100) + 1;
    dblist(0, dbmax) = 89;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1185_internal:
    if (20 > objlv)
    {
        goto label_1186_internal;
    }
    if (fltselect != 0)
    {
        goto label_1186_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1186_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60005)
        {
            goto label_1186_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(88), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1186_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 20)) * 100) + 1;
    dblist(0, dbmax) = 88;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1186_internal:
    if (5 > objlv)
    {
        goto label_1187_internal;
    }
    if (fltselect != 0)
    {
        goto label_1187_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1187_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1187_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(87), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1187_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 5)) * 100) + 1;
    dblist(0, dbmax) = 87;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1187_internal:
    if (5 > objlv)
    {
        goto label_1188_internal;
    }
    if (fltselect != 0)
    {
        goto label_1188_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1188_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1188_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(86), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1188_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 5)) * 100) + 1;
    dblist(0, dbmax) = 86;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1188_internal:
    if (15 > objlv)
    {
        goto label_1189_internal;
    }
    if (fltselect != 0)
    {
        goto label_1189_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1189_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1189_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(85), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1189_internal;
        }
    }
    dbsum += 300000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 85;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1189_internal:
    if (18 > objlv)
    {
        goto label_1190_internal;
    }
    if (fltselect != 0)
    {
        goto label_1190_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1190_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1190_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(84), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1190_internal;
        }
    }
    dbsum += 200000 / (1000 + abs((objlv - 18)) * 100) + 1;
    dblist(0, dbmax) = 84;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1190_internal:
    if (7 > objlv)
    {
        goto label_1191_internal;
    }
    if (fltselect != 0)
    {
        goto label_1191_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1191_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1191_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(83), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1191_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 7)) * 100) + 1;
    dblist(0, dbmax) = 83;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1191_internal:
    if (1 > objlv)
    {
        goto label_1192_internal;
    }
    if (fltselect != 0)
    {
        goto label_1192_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1192_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1192_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(82), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1192_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 82;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1192_internal:
    if (1 > objlv)
    {
        goto label_1193_internal;
    }
    if (fltselect != 0)
    {
        goto label_1193_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1193_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1193_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(81), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1193_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 81;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1193_internal:
    if (5 > objlv)
    {
        goto label_1194_internal;
    }
    if (fltselect != 0)
    {
        goto label_1194_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1194_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 60004)
        {
            goto label_1194_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(80), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1194_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 5)) * 100) + 1;
    dblist(0, dbmax) = 80;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1194_internal:
    if (20 > objlv)
    {
        goto label_1195_internal;
    }
    if (fltselect != 0)
    {
        goto label_1195_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1195_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1195_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(79), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1195_internal;
        }
    }
    dbsum += 100000 / (1000 + abs((objlv - 20)) * 100) + 1;
    dblist(0, dbmax) = 79;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1195_internal:
    if (12 > objlv)
    {
        goto label_1196_internal;
    }
    if (fltselect != 0)
    {
        goto label_1196_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1196_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1196_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(78), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1196_internal;
        }
    }
    dbsum += 600000 / (1000 + abs((objlv - 12)) * 100) + 1;
    dblist(0, dbmax) = 78;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1196_internal:
    if (1 > objlv)
    {
        goto label_1197_internal;
    }
    if (fltselect != 0)
    {
        goto label_1197_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 60000)
        {
            goto label_1197_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1197_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(77), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1197_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 77;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1197_internal:
    if (45 > objlv)
    {
        goto label_1198_internal;
    }
    if (fltselect != 0)
    {
        goto label_1198_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_1198_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 52001)
        {
            goto label_1198_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(76), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1198_internal;
        }
    }
    dbsum += 150000 / (1000 + abs((objlv - 45)) * 0) + 1;
    dblist(0, dbmax) = 76;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1198_internal:
    if (45 > objlv)
    {
        goto label_1199_internal;
    }
    if (fltselect != 0)
    {
        goto label_1199_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_1199_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 52001)
        {
            goto label_1199_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(75), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1199_internal;
        }
    }
    dbsum += 250000 / (1000 + abs((objlv - 45)) * 0) + 1;
    dblist(0, dbmax) = 75;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1199_internal:
    if (35 > objlv)
    {
        goto label_1200_internal;
    }
    if (fltselect != 0)
    {
        goto label_1200_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_1200_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 52001)
        {
            goto label_1200_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(74), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1200_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 35)) * 0) + 1;
    dblist(0, dbmax) = 74;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1200_internal:
    if (30 > objlv)
    {
        goto label_1201_internal;
    }
    if (fltselect != 3)
    {
        goto label_1201_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_1201_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10002)
        {
            goto label_1201_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(73), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1201_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 30)) * 100) + 1;
    dblist(0, dbmax) = 73;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1201_internal:
    if (25 > objlv)
    {
        goto label_1202_internal;
    }
    if (fltselect != 0)
    {
        goto label_1202_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_1202_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 52001)
        {
            goto label_1202_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(72), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1202_internal;
        }
    }
    dbsum += 600000 / (1000 + abs((objlv - 25)) * 0) + 1;
    dblist(0, dbmax) = 72;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1202_internal:
    if (15 > objlv)
    {
        goto label_1203_internal;
    }
    if (fltselect != 0)
    {
        goto label_1203_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_1203_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 52001)
        {
            goto label_1203_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(71), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1203_internal;
        }
    }
    dbsum += 700000 / (1000 + abs((objlv - 15)) * 50) + 1;
    dblist(0, dbmax) = 71;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1203_internal:
    if (8 > objlv)
    {
        goto label_1204_internal;
    }
    if (fltselect != 0)
    {
        goto label_1204_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_1204_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 52001)
        {
            goto label_1204_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(70), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1204_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 8)) * 50) + 1;
    dblist(0, dbmax) = 70;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1204_internal:
    if (4 > objlv)
    {
        goto label_1205_internal;
    }
    if (fltselect != 0)
    {
        goto label_1205_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_1205_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 52001)
        {
            goto label_1205_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(69), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1205_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 4)) * 100) + 1;
    dblist(0, dbmax) = 69;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1205_internal:
    if (1 > objlv)
    {
        goto label_1206_internal;
    }
    if (fltselect != 0)
    {
        goto label_1206_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_1206_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 52001)
        {
            goto label_1206_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(68), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1206_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 68;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1206_internal:
    if (1 > objlv)
    {
        goto label_1207_internal;
    }
    if (fltselect != 0)
    {
        goto label_1207_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 34000)
        {
            goto label_1207_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 34001)
        {
            goto label_1207_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(67), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1207_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 67;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1207_internal:
    if (1 > objlv)
    {
        goto label_1208_internal;
    }
    if (fltselect != 0)
    {
        goto label_1208_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 19000)
        {
            goto label_1208_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 19001)
        {
            goto label_1208_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(66), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1208_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 66;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1208_internal:
    if (1 > objlv)
    {
        goto label_1209_internal;
    }
    if (fltselect != 0)
    {
        goto label_1209_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 20000)
        {
            goto label_1209_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 20001)
        {
            goto label_1209_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(65), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1209_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 65;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1209_internal:
    if (50 > objlv)
    {
        goto label_1210_internal;
    }
    if (fltselect != 3)
    {
        goto label_1210_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_1210_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10002)
        {
            goto label_1210_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(64), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1210_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 50)) * 100) + 1;
    dblist(0, dbmax) = 64;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1210_internal:
    if (35 > objlv)
    {
        goto label_1211_internal;
    }
    if (fltselect != 3)
    {
        goto label_1211_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_1211_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10011)
        {
            goto label_1211_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(63), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1211_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 35)) * 100) + 1;
    dblist(0, dbmax) = 63;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1211_internal:
    if (1 > objlv)
    {
        goto label_1212_internal;
    }
    if (fltselect != 0)
    {
        goto label_1212_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 25000)
        {
            goto label_1212_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 25020)
        {
            goto label_1212_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(62), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1212_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 62;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1212_internal:
    if (1 > objlv)
    {
        goto label_1213_internal;
    }
    if (fltselect != 0)
    {
        goto label_1213_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 25000)
        {
            goto label_1213_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 25001)
        {
            goto label_1213_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(61), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1213_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 61;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1213_internal:
    if (1 > objlv)
    {
        goto label_1214_internal;
    }
    if (fltselect != 0)
    {
        goto label_1214_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 24000)
        {
            goto label_1214_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 24020)
        {
            goto label_1214_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(60), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1214_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 60;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1214_internal:
    if (30 > objlv)
    {
        goto label_1215_internal;
    }
    if (fltselect != 0)
    {
        goto label_1215_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 14000)
        {
            goto label_1215_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 14003)
        {
            goto label_1215_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(59), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1215_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 30)) * 100) + 1;
    dblist(0, dbmax) = 59;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1215_internal:
    if (1 > objlv)
    {
        goto label_1216_internal;
    }
    if (fltselect != 0)
    {
        goto label_1216_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 24000)
        {
            goto label_1216_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 24001)
        {
            goto label_1216_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(58), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1216_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 58;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1216_internal:
    if (30 > objlv)
    {
        goto label_1217_internal;
    }
    if (fltselect != 2)
    {
        goto label_1217_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_1217_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10002)
        {
            goto label_1217_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(57), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1217_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 30)) * 100) + 1;
    dblist(0, dbmax) = 57;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1217_internal:
    if (40 > objlv)
    {
        goto label_1218_internal;
    }
    if (fltselect != 3)
    {
        goto label_1218_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_1218_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10002)
        {
            goto label_1218_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(56), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1218_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 40)) * 100) + 1;
    dblist(0, dbmax) = 56;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1218_internal:
    if (1 > objlv)
    {
        goto label_1219_internal;
    }
    if (fltselect != 0)
    {
        goto label_1219_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 69000)
        {
            goto label_1219_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1219_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(55), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1219_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 55;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1219_internal:
    if (1 > objlv)
    {
        goto label_1220_internal;
    }
    if (fltselect != 0)
    {
        goto label_1220_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 68000)
        {
            goto label_1220_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1220_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(54), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1220_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 54;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1220_internal:
    if (1 > objlv)
    {
        goto label_1221_internal;
    }
    if (fltselect != 0)
    {
        goto label_1221_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 64000)
        {
            goto label_1221_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1221_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(53), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1221_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 53;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1221_internal:
    if (1 > objlv)
    {
        goto label_1222_internal;
    }
    if (fltselect != 0)
    {
        goto label_1222_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 64000)
        {
            goto label_1222_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1222_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(52), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1222_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 52;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1222_internal:
    if (1 > objlv)
    {
        goto label_1223_internal;
    }
    if (fltselect != 0)
    {
        goto label_1223_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 64000)
        {
            goto label_1223_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 64000)
        {
            goto label_1223_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(51), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1223_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 51;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1223_internal:
    if (1 > objlv)
    {
        goto label_1224_internal;
    }
    if (fltselect != 0)
    {
        goto label_1224_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 64000)
        {
            goto label_1224_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 64000)
        {
            goto label_1224_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(50), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1224_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 50;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1224_internal:
    if (1 > objlv)
    {
        goto label_1225_internal;
    }
    if (fltselect != 0)
    {
        goto label_1225_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 64000)
        {
            goto label_1225_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1225_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(49), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1225_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 49;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1225_internal:
    if (1 > objlv)
    {
        goto label_1226_internal;
    }
    if (fltselect != 0)
    {
        goto label_1226_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 64000)
        {
            goto label_1226_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1226_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(48), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1226_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 48;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1226_internal:
    if (1 > objlv)
    {
        goto label_1227_internal;
    }
    if (fltselect != 0)
    {
        goto label_1227_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 64000)
        {
            goto label_1227_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 64100)
        {
            goto label_1227_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(47), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1227_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 47;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1227_internal:
    if (1 > objlv)
    {
        goto label_1228_internal;
    }
    if (fltselect != 0)
    {
        goto label_1228_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 64000)
        {
            goto label_1228_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 64000)
        {
            goto label_1228_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(46), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1228_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 46;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1228_internal:
    if (1 > objlv)
    {
        goto label_1229_internal;
    }
    if (fltselect != 0)
    {
        goto label_1229_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 64000)
        {
            goto label_1229_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 64000)
        {
            goto label_1229_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(45), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1229_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 45;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1229_internal:
    if (1 > objlv)
    {
        goto label_1230_internal;
    }
    if (fltselect != 0)
    {
        goto label_1230_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 77000)
        {
            goto label_1230_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 64000)
        {
            goto label_1230_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(44), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1230_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 44;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1230_internal:
    if (1 > objlv)
    {
        goto label_1231_internal;
    }
    if (fltselect != 0)
    {
        goto label_1231_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 64000)
        {
            goto label_1231_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 64000)
        {
            goto label_1231_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(43), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1231_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 43;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1231_internal:
    if (1 > objlv)
    {
        goto label_1232_internal;
    }
    if (fltselect != 0)
    {
        goto label_1232_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 77000)
        {
            goto label_1232_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 77001)
        {
            goto label_1232_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(42), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1232_internal;
        }
    }
    dbsum += 250000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 42;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1232_internal:
    if (1 > objlv)
    {
        goto label_1233_internal;
    }
    if (fltselect != 0)
    {
        goto label_1233_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 77000)
        {
            goto label_1233_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 77001)
        {
            goto label_1233_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(41), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1233_internal;
        }
    }
    dbsum += 400000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 41;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1233_internal:
    if (1 > objlv)
    {
        goto label_1234_internal;
    }
    if (fltselect != 0)
    {
        goto label_1234_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 77000)
        {
            goto label_1234_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 77001)
        {
            goto label_1234_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(40), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1234_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 40;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1234_internal:
    if (1 > objlv)
    {
        goto label_1235_internal;
    }
    if (fltselect != 0)
    {
        goto label_1235_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 77000)
        {
            goto label_1235_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 77001)
        {
            goto label_1235_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(39), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1235_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 39;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1235_internal:
    if (1 > objlv)
    {
        goto label_1236_internal;
    }
    if (fltselect != 0)
    {
        goto label_1236_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 77000)
        {
            goto label_1236_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1236_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(38), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1236_internal;
        }
    }
    dbsum += 500000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 38;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1236_internal:
    if (1 > objlv)
    {
        goto label_1237_internal;
    }
    if (fltselect != 0)
    {
        goto label_1237_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 77000)
        {
            goto label_1237_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1237_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(37), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1237_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 37;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1237_internal:
    if (1 > objlv)
    {
        goto label_1238_internal;
    }
    if (fltselect != 0)
    {
        goto label_1238_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 77000)
        {
            goto label_1238_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1238_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(36), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1238_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 36;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1238_internal:
    if (1 > objlv)
    {
        goto label_1239_internal;
    }
    if (fltselect != 0)
    {
        goto label_1239_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 77000)
        {
            goto label_1239_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1239_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(35), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1239_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 35;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1239_internal:
    if (1 > objlv)
    {
        goto label_1240_internal;
    }
    if (fltselect != 0)
    {
        goto label_1240_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_1240_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1240_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(34), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1240_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 34;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1240_internal:
    if (1 > objlv)
    {
        goto label_1241_internal;
    }
    if (fltselect != 0)
    {
        goto label_1241_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_1241_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1241_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(33), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1241_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 33;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1241_internal:
    if (1 > objlv)
    {
        goto label_1242_internal;
    }
    if (fltselect != 0)
    {
        goto label_1242_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_1242_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1242_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(32), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1242_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 32;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1242_internal:
    if (1 > objlv)
    {
        goto label_1243_internal;
    }
    if (fltselect != 0)
    {
        goto label_1243_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_1243_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 52002)
        {
            goto label_1243_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(31), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1243_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 31;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1243_internal:
    if (1 > objlv)
    {
        goto label_1244_internal;
    }
    if (fltselect != 0)
    {
        goto label_1244_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_1244_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1244_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(30), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1244_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 30;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1244_internal:
    if (1 > objlv)
    {
        goto label_1245_internal;
    }
    if (fltselect != 0)
    {
        goto label_1245_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_1245_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1245_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(29), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1245_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 29;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1245_internal:
    if (1 > objlv)
    {
        goto label_1246_internal;
    }
    if (fltselect != 0)
    {
        goto label_1246_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_1246_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1246_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(28), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1246_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 28;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1246_internal:
    if (1 > objlv)
    {
        goto label_1247_internal;
    }
    if (fltselect != 0)
    {
        goto label_1247_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_1247_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1247_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(27), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1247_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 27;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1247_internal:
    if (1 > objlv)
    {
        goto label_1248_internal;
    }
    if (fltselect != 0)
    {
        goto label_1248_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 52000)
        {
            goto label_1248_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1248_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(26), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1248_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 26;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1248_internal:
    if (1 > objlv)
    {
        goto label_1249_internal;
    }
    if (fltselect != 1)
    {
        goto label_1249_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 55000)
        {
            goto label_1249_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1249_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(25), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1249_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 25;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1249_internal:
    if (1 > objlv)
    {
        goto label_1250_internal;
    }
    if (fltselect != 0)
    {
        goto label_1250_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 55000)
        {
            goto label_1250_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1250_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(24), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1250_internal;
        }
    }
    dbsum += 2000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 24;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1250_internal:
    if (1 > objlv)
    {
        goto label_1251_internal;
    }
    if (fltselect != 1)
    {
        goto label_1251_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 55000)
        {
            goto label_1251_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1251_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(23), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1251_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 23;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1251_internal:
    if (10 > objlv)
    {
        goto label_1252_internal;
    }
    if (fltselect != 0)
    {
        goto label_1252_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_1252_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1252_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(22), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1252_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 10)) * 0) + 1;
    dblist(0, dbmax) = 22;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1252_internal:
    if (6 > objlv)
    {
        goto label_1253_internal;
    }
    if (fltselect != 0)
    {
        goto label_1253_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_1253_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1253_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(21), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1253_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 6)) * 0) + 1;
    dblist(0, dbmax) = 21;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1253_internal:
    if (1 > objlv)
    {
        goto label_1254_internal;
    }
    if (fltselect != 0)
    {
        goto label_1254_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 54000)
        {
            goto label_1254_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1254_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(20), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1254_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 20;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1254_internal:
    if (1 > objlv)
    {
        goto label_1255_internal;
    }
    if (fltselect != 0)
    {
        goto label_1255_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 56000)
        {
            goto label_1255_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1255_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(19), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1255_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 19;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1255_internal:
    if (4 > objlv)
    {
        goto label_1256_internal;
    }
    if (fltselect != 0)
    {
        goto label_1256_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 56000)
        {
            goto label_1256_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1256_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(18), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1256_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 4)) * 0) + 1;
    dblist(0, dbmax) = 18;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1256_internal:
    if (1 > objlv)
    {
        goto label_1257_internal;
    }
    if (fltselect != 0)
    {
        goto label_1257_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_1257_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1257_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(17), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1257_internal;
        }
    }
    dbsum += 70000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 17;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1257_internal:
    if (1 > objlv)
    {
        goto label_1258_internal;
    }
    if (fltselect != 0)
    {
        goto label_1258_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_1258_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1258_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(16), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1258_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 16;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1258_internal:
    if (1 > objlv)
    {
        goto label_1259_internal;
    }
    if (fltselect != 0)
    {
        goto label_1259_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_1259_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1259_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(15), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1259_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 15;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1259_internal:
    if (1 > objlv)
    {
        goto label_1260_internal;
    }
    if (fltselect != 0)
    {
        goto label_1260_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 53000)
        {
            goto label_1260_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999)
        {
            goto label_1260_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(14), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1260_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 0) + 1;
    dblist(0, dbmax) = 14;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1260_internal:
    if (1 > objlv)
    {
        goto label_1261_internal;
    }
    if (fltselect != 0)
    {
        goto label_1261_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 32000)
        {
            goto label_1261_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 32001)
        {
            goto label_1261_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(13), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1261_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 13;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1261_internal:
    if (15 > objlv)
    {
        goto label_1262_internal;
    }
    if (fltselect != 0)
    {
        goto label_1262_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 18000)
        {
            goto label_1262_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 18001)
        {
            goto label_1262_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(12), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1262_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 12;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1262_internal:
    if (1 > objlv)
    {
        goto label_1263_internal;
    }
    if (fltselect != 0)
    {
        goto label_1263_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 18000)
        {
            goto label_1263_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 18001)
        {
            goto label_1263_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(11), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1263_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 11;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1263_internal:
    if (1 > objlv)
    {
        goto label_1264_internal;
    }
    if (fltselect != 0)
    {
        goto label_1264_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 22000)
        {
            goto label_1264_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 22001)
        {
            goto label_1264_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(10), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1264_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 10;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1264_internal:
    if (30 > objlv)
    {
        goto label_1265_internal;
    }
    if (fltselect != 0)
    {
        goto label_1265_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 22000)
        {
            goto label_1265_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 22003)
        {
            goto label_1265_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(9), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1265_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 30)) * 100) + 1;
    dblist(0, dbmax) = 9;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1265_internal:
    if (1 > objlv)
    {
        goto label_1266_internal;
    }
    if (fltselect != 0)
    {
        goto label_1266_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 16000)
        {
            goto label_1266_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 16003)
        {
            goto label_1266_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(8), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1266_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 8;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1266_internal:
    if (1 > objlv)
    {
        goto label_1267_internal;
    }
    if (fltselect != 0)
    {
        goto label_1267_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 16000)
        {
            goto label_1267_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 16001)
        {
            goto label_1267_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(7), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1267_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 7;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1267_internal:
    if (30 > objlv)
    {
        goto label_1268_internal;
    }
    if (fltselect != 0)
    {
        goto label_1268_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 12000)
        {
            goto label_1268_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 12002)
        {
            goto label_1268_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(6), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1268_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 30)) * 100) + 1;
    dblist(0, dbmax) = 6;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1268_internal:
    if (15 > objlv)
    {
        goto label_1269_internal;
    }
    if (fltselect != 0)
    {
        goto label_1269_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 12000)
        {
            goto label_1269_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 12002)
        {
            goto label_1269_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(5), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1269_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 15)) * 100) + 1;
    dblist(0, dbmax) = 5;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1269_internal:
    if (1 > objlv)
    {
        goto label_1270_internal;
    }
    if (fltselect != 0)
    {
        goto label_1270_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_1270_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10004)
        {
            goto label_1270_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(4), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1270_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 4;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1270_internal:
    if (1 > objlv)
    {
        goto label_1271_internal;
    }
    if (fltselect != 0)
    {
        goto label_1271_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_1271_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10009)
        {
            goto label_1271_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(3), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1271_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 3;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1271_internal:
    if (1 > objlv)
    {
        goto label_1272_internal;
    }
    if (fltselect != 0)
    {
        goto label_1272_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_1272_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10003)
        {
            goto label_1272_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(2), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1272_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 2;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1272_internal:
    if (1 > objlv)
    {
        goto label_1273_internal;
    }
    if (fltselect != 0)
    {
        goto label_1273_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 10000)
        {
            goto label_1273_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 10002)
        {
            goto label_1273_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(1), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1273_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 1;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1273_internal:
    if (1 > objlv)
    {
        goto label_1274_internal;
    }
    if (fltselect != 1)
    {
        goto label_1274_internal;
    }
    if (flttypemajor != 0)
    {
        if (flttypemajor != 99999999)
        {
            goto label_1274_internal;
        }
    }
    if (flttypeminor != 0)
    {
        if (flttypeminor != 99999999)
        {
            goto label_1274_internal;
        }
    }
    if (filtermax != 0)
    {
        dbtmp = 1;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (filtermax); cnt < cnt_end; ++cnt)
            {
                if (instr(filter_item(0), 0, filtern(cnt)) == -1)
                {
                    dbtmp = 0;
                    break;
                }
            }
        }
        if (dbtmp == 0)
        {
            goto label_1274_internal;
        }
    }
    dbsum += 1000000 / (1000 + abs((objlv - 1)) * 100) + 1;
    dblist(0, dbmax) = 0;
    dblist(1, dbmax) = dbsum;
    ++dbmax;
label_1274_internal:
    if (dbsum != 0)
    {
        exrand_rnd(dbtmp, dbsum);
        {
            int cnt = 0;
            for (int cnt_end = cnt + (dbmax); cnt < cnt_end; ++cnt)
            {
                if (dblist(1, cnt) > dbtmp)
                {
                    dbid = dblist(0, cnt);
                    break;
                }
            }
        }
    }
    else
    {
        dbid = 25;
    }
    return;
}


} // namespace elona
