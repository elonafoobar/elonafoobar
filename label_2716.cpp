#include "elona.hpp"
#include "variables.hpp"

#include "dup.hpp"

namespace elona
{
void label_2716()
{
    procid = (procid + 1) % 4;
    proclist(procid) = u8"Load config ct:"s + ct;
    notesel(note_buff);
    noteload(exedir + u8"\\config.txt"s);
    {
        int cnt = 0;
        for (int cnt_end = cnt + (noteinfo(0)); cnt < cnt_end; ++cnt) {
            noteget(s, cnt);
            if (instr(s, 0, u8"key_sCancel."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_scancel = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"alert_wait."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_alert = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"anime_wait."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_animewait = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"ignoreDislike."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_ignoredislike = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"wait1."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_wait1 = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"font1."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_font1 = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"font2."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_font2 = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"fontVfix1."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                vfix = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"fontSfix1."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                sizefix = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"story."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_story = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"heartbeat."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_heart = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"extraHelp."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_extrahelp = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"alwaysCenter."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_alwayscenter = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"scroll."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_scroll = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"startRun."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_startrun = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"walkWait."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_walkwait = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"runWait."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_runwait = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"autoTurnType."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_autoturn = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"autoNumlock."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_autonumlock = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"attackWait."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_attackwait = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"attackAnime."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_attackanime = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"envEffect."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_env = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"titleEffect."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_titleeffect = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"net."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_net = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"netWish."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_netwish = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"netChat."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_netchat = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"serverList."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_serverlist = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"shadow."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_shadow = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"objectShadow."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_objectshadow = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"windowAnime."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_windowanime = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"exAnime."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_exanime = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"showSkillMod."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_showskillmod = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"hide_autoIdentify."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_hideautoidentify = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"hide_shopResult."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_hideshopresult = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"msg_trans."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_msgtrans = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"msg_addTime."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_msgaddtime = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"key_cancel."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_cancel = rtvaln;
                jkey(elona_int(rtvaln(1))) = key_cancel;
                continue;
            }
            if (instr(s, 0, u8"key_esc."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_esc = rtvaln;
                jkey(elona_int(rtvaln(1))) = key_esc;
                continue;
            }
            if (instr(s, 0, u8"key_alter."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_alter = rtvaln;
                jkey(elona_int(rtvaln(1))) = key_alter;
                continue;
            }
            if (instr(s, 0, u8"key_north."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_north = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_south."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_south = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_west."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_west = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_east."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_east = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_northwest."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_northwest = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_northeast."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_northeast = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_southwest."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_southwest = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_southeast."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_southeast = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_wait."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_wait = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_inventory."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_inventory = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_help."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_help = rtvaln;
                jkey(elona_int(rtvaln(1))) = key_help;
                continue;
            }
            if (instr(s, 0, u8"key_msglog."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_msglog = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_pageup."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_pageup = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_pagedown."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_pagedown = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_get."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_get = rtvaln;
                jkey(elona_int(rtvaln(1))) = key_get;
                continue;
            }
            if (instr(s, 0, u8"key_get2."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_get2 = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_drop."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_drop = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_charainfo."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_charainfo = rtvaln;
                jkey(elona_int(rtvaln(1))) = key_charainfo;
                continue;
            }
            if (instr(s, 0, u8"key_enter."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_enter = rtvaln;
                jkey(elona_int(rtvaln(1))) = key_enter;
                continue;
            }
            if (instr(s, 0, u8"key_eat."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_eat = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_wear."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_wear = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_cast."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_cast = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_drink."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_drink = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_read."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_read = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_zap."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_zap = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_fire."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_fire = rtvaln;
                jkey(elona_int(rtvaln(1))) = key_fire;
                continue;
            }
            if (instr(s, 0, u8"key_goDown."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_godown = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_goUp."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_goup = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_save."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_save = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_search."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_search = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_interact."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_interact = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_identify."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_identify = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_skill."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_skill = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_close."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_close = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_rest."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_rest = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_target."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_target = rtvaln;
                jkey(elona_int(rtvaln(1))) = key_target;
                continue;
            }
            if (instr(s, 0, u8"key_dig."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_dig = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_use."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_use = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_bash."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_bash = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_open."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_open = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_dip."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_dip = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_pray."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_pray = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_offer."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_offer = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_journal."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_journal = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_material."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_material = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_quick."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_quick = rtvaln;
                jkey(elona_int(rtvaln(1))) = key_quick;
                continue;
            }
            if (instr(s, 0, u8"key_trait."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_trait = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_look."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_look = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_give."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_give = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_throw."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_throw = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_mode."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_mode = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_mode2."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_mode2 = rtvaln;
                continue;
            }
            if (instr(s, 0, u8"key_ammo."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_ammo = rtvaln;
                jkey(elona_int(rtvaln(1))) = key_ammo;
                continue;
            }
            if (instr(s, 0, u8"key_quickinv."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                key_quickinv = rtvaln;
                jkey(elona_int(rtvaln(1))) = key_quickinv;
                continue;
            }
            if (instr(s, 0, u8"zkey."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_zkey = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"xkey."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_xkey = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"scr_sync."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_scrsync = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"scroll_run."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_runscroll = elona_int(rtvaln);
                continue;
            }
            if (instr(s, 0, u8"skipRandEvents."s) != -1) {
                i = 0;
                p = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        p(2) = instr(s, p, u8"\""s);
                        if (p(2) == -1) { break; }
                        p += p(2);
                        p(1) = instr(s, p + 1, u8"\""s);
                        if (p(1) == -1) { break; }
                        rtvaln(i) = strmid(s, p + 1, p(1));
                        p += strlen(rtvaln(i)) + 2;
                        ++i;
                    }
                }
                cfg_skiprandevents = elona_int(rtvaln);
                continue;
            }
            key_prev = key_northwest;
            key_next = key_northeast;
            if (instr(s, 0, u8"key_set."s) != -1) {
                p = 0;
                p(1) = 0;
                {
                    int cnt = 0;
                    for (;; ++cnt) {
                        await();
                        if (instr(s, p, u8","s) == -1) { break; }
                        p += instr(s, p, u8","s) + 1;
                        key_select(p(1)) = strmid(s, p, 1);
                        ++p(1);
                    }
                }
            }
        }
    }
    f = 0;
    if (cfg_zkey == 0) {
        key_quick = u8"z"s;
        key_zap = u8"Z"s;
    } else {
        if (cfg_zkey == 1) {
            key_zap = u8"z"s;
            key_quick = u8"Z"s;
        }
    }
    if (cfg_xkey == 0) {
        key_quickinv = u8"x"s;
        key_inventory = u8"X"s;
    } else {
        if (cfg_xkey == 1) {
            key_inventory = u8"x"s;
            key_quickinv = u8"X"s;
        }
    }
    if (cfg_scrsync == 0) { cfg_scrsync = 3; }
    if (cfg_walkwait == 0) { cfg_walkwait = 5; }
    if (cfg_runwait < 1) { cfg_runwait = 1; }
    if (cfg_attackwait < 1) { cfg_attackwait = 1; }
    if (cfg_startrun >= 20) { cfg_startrun = 1000; }
    if (cfg_language == -1) {
        redraw(0);
        buffer(4);
        picload(exedir + u8"graphic\\lang.bmp"s);
        gsel(0);
        gmode(0);
        p = 0;
    label_2717_internal:
        redraw(0);
        color(0, 0, 0);
        boxf();
        pos(160, 170);
        gcopy(4, 0, 0, 340, 100);
        pos(180, 220 + p * 20);
        gcopy(4, 360, 6, 20, 18);
        redraw(1);
        await(30);
        getkey(a, 40);
        if (a) { p = 1; }
        getkey(a, 98);
        if (a) { p = 1; }
        getkey(a, 38);
        if (a) { p = 0; }
        getkey(a, 104);
        if (a) { p = 0; }
        getkey(a, 13);
        if (a) { goto label_2718_internal; }
        getkey(a, 32);
        if (a) { goto label_2718_internal; }
        goto label_2717_internal;
    label_2718_internal:
        cfg_language = p;
        valn(0) = u8"language."s;
        valn(1) = ""s + p;
        label_2713();
        redraw(0);
    }
    procid = (procid + 1) % 4;
    proclist(procid) = u8"Fix config ct:"s + ct;
    if (cfg_language == 0) {
        jp = 1;
        vfix = 0;
        sizefix = 0;
    } else {
        en = 1;
    }
    if (key_mode == ""s) {
        key_mode = u8"z"s;
        f = 1;
        noteadd(u8"key_mode.\t\"z\""s);
    }
    if (key_mode2 == ""s) {
        key_mode2 = u8"*"s;
        f = 1;
        noteadd(u8"key_mode2.\t\"*\""s);
    }
    if (key_ammo == ""s) {
        key_ammo = u8"A"s;
        f = 1;
        noteadd(u8"key_ammo.\t\"A\""s);
    }
    if (f) { notesave(exedir + u8"\\config.txt"s); }
    return;
}


} // namespace elona
