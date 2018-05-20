#include "network.hpp"
#include "audio.hpp"
#include "config.hpp"
#include "elona.hpp"
#include "input.hpp"
#include "macro.hpp"
#include "ui.hpp"
#include "variables.hpp"


std::string url_at_m147;
std::string chatsendurl;
std::string conurl_at_m147;
elona_vector1<std::string> cgiurl3;
std::string votesendurl;
elona_vector1<std::string> cgiurl2;
std::string textreadurl;
std::string chatreadurl;
std::string votereadurl;



namespace elona
{



void netload(const std::string& prm_194)
{
    int res_at_m0 = 0;
    std::string estr_at_m0;
    netrequest(prm_194);
    while (1)
    {
        netexec(res_at_m0);
        if (res_at_m0)
        {
            break;
        }
        await(50);
    }
    if (res_at_m0 > 0)
    {
        return;
    }
    neterror(estr_at_m0);
    dialog(u8"エラー:"s + estr_at_m0);
    return;
}



int net_send(const std::string& prm_883, int prm_884)
{
    std::string chattemp;
    std::string msg_at_m147;
    if (config::instance().net == 0)
    {
        return 0;
    }
    chattemp = prm_883;
    if (prm_884 == 0)
    {
        fix_input_chat2(chattemp);
    }
    fix_input_chat(chattemp);
    if (prm_884 == 0)
    {
        url_at_m147 = chatsendurl;
        msg_at_m147 = u8"&comment="s + chattemp;
    }
    else if (gdata_wizard)
    {
        return 1;
    }
    conurl_at_m147 = u8"hpcgi3.nifty.com"s;
    if (prm_884 == 1)
    {
        conurl_at_m147 = cgiurl3;
        url_at_m147 = votesendurl;
        msg_at_m147 = u8"&vote="s + chattemp;
    }
    if (prm_884 == 2)
    {
        conurl_at_m147 = cgiurl3;
        url_at_m147 = votesendurl;
        msg_at_m147 = u8"&namber="s + chattemp;
    }
    if (prm_884 == 0)
    {
        conurl_at_m147 = cgiurl2;
    }
    {
        int stat = sockopen(0, conurl_at_m147, 80);
        if (stat)
        {
            sockclose();
            txt(u8"["s + stat + u8"]"s
                + lang(
                      u8"ネットに繋がっていない。"s,
                      u8"You need an internet connection."s));
            return 0;
        }
    }
    {
        int stat = sockput(u8"GET "s + url_at_m147 + msg_at_m147 +
        u8" HTTP/1.0\nHost:www.nifty.com???\nUser-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows 98; Win 9x 4.90)\n\n"s);
        if (stat)
        {
            sockclose();
            txt(lang(u8"送信に失敗した。"s, u8"Failed to send a message."s));
            return 0;
        }
    }
    sockclose();
    return 1;
}



int net_read(int prm_885)
{
    int lastchat = 0;
    std::string a_at_m147;
    int sz_at_m147 = 0;
    int t_at_m147 = 0;
    int header_at_m147 = 0;
    int tail_at_m147 = 0;
    int chat_count_at_m147 = 0;
    int count_latest_at_m147 = 0;
    std::string chat_date_at_m147;
    std::string chat_msg_at_m147;
    std::string chat_ip_at_m147;
    chatnew = "";
    SDIM2(netbuf, 20000);
    netbuf = "";
    if (config::instance().net == 0)
    {
        return 0;
    }
    if (prm_885 == 5)
    {
        url_at_m147 = textreadurl;
        conurl_at_m147 = cgiurl3;
    }
    if (prm_885 == 0)
    {
        url_at_m147 = chatreadurl;
        conurl_at_m147 = cgiurl2;
    }
    if (prm_885 == 1)
    {
        url_at_m147 = votereadurl;
        conurl_at_m147 = cgiurl3;
    }
    if (prm_885 == 2)
    {
        url_at_m147 = u8"/rfish/userfile/cliplog.txt"s;
        conurl_at_m147 = u8"homepage3.nifty.com"s;
    }
    if (prm_885 == 3)
    {
        url_at_m147 = u8"/rfish/file/welcome.txt"s;
        conurl_at_m147 = u8"homepage3.nifty.com"s;
    }
    if (prm_885 == 4)
    {
        url_at_m147 = u8"http://homepage3.nifty.com/rfish/file/server.txt"s;
        conurl_at_m147 = u8"homepage3.nifty.com"s;
    }
    {
        int stat = sockopen(0, conurl_at_m147, 80);
        if (stat)
        {
            sockclose();
            return 0;
        }
    }
    {
        int stat = sockput(
            u8"GET "s + url_at_m147
            + u8" HTTP/1.0\nHost:???\nUser-Agent: HSP ver3.0\n\n"s);
        if (stat)
        {
            sockclose();
            return 0;
        }
    }
    a_at_m147 = "";
    sz_at_m147 = 0;
    t_at_m147 = 0;
label_1393_internal:
    await(0);
    ++t_at_m147;
    if (t_at_m147 > 10000)
    {
        if (getkey(snail::key::escape))
        {
            txt(u8"[Chat Skipped]"s);
            sockclose();
            return 0;
        }
    }
    {
        int stat = sockget(a_at_m147, 64);
        if (stat)
        {
            sockclose();
            return 0;
        }
    }
    if (a_at_m147[0] == 0)
    {
        goto label_1394_internal;
        return 0;
    }
    netbuf += a_at_m147;
    sz_at_m147 += 64;
    if (sz_at_m147 > 30000)
    {
        goto label_1394_internal;
        return 0;
    }
    goto label_1393_internal;
label_1394_internal:
    sockclose();
    if (prm_885 == 1 || prm_885 == 4)
    {
        header_at_m147 = instr(netbuf, 0, u8"\n\n"s) + 4;
    }
    else
    {
        header_at_m147 = instr(netbuf, 0, u8"<!--START-->"s) + 13;
    }
    for (int cnt = 0;; ++cnt)
    {
        if (prm_885 == 4)
        {
            netbuf = strmid(netbuf, header_at_m147, 2000);
            break;
        }
        if (prm_885 == 5)
        {
            tail_at_m147 = instr(netbuf, header_at_m147, u8"%"s);
            if (tail_at_m147 == -1)
            {
                break;
            }
            listn(0, listmax) = strmid(netbuf, header_at_m147, tail_at_m147);
            header_at_m147 += tail_at_m147 + 1;
            ++listmax;
        }
        if (prm_885 == 1)
        {
            tail_at_m147 = instr(netbuf, header_at_m147, u8"<>"s);
            if (tail_at_m147 == -1)
            {
                break;
            }
            if (listmax > 100)
            {
                break;
            }
            list(0, listmax) =
                elona::stoi(strmid(netbuf, header_at_m147, tail_at_m147));
            header_at_m147 += tail_at_m147 + 2;
            tail_at_m147 = instr(netbuf, header_at_m147, u8"<>"s);
            listn(0, listmax) =
                ""s + strmid(netbuf, header_at_m147, tail_at_m147);
            header_at_m147 += tail_at_m147 + 2;
            tail_at_m147 = instr(netbuf, header_at_m147, u8"<>"s);
            list(1, listmax) =
                elona::stoi(strmid(netbuf, header_at_m147, tail_at_m147));
            header_at_m147 += tail_at_m147 + 2;
            listn(1, listmax) = ""s + list(1, listmax);
            tail_at_m147 = instr(netbuf, header_at_m147, u8"<>"s);
            header_at_m147 += tail_at_m147 + 2;
            tail_at_m147 = instr(netbuf, header_at_m147, u8"<>"s);
            header_at_m147 += tail_at_m147 + 3;
            ++listmax;
        }
        if (prm_885 == 0)
        {
            tail_at_m147 = instr(netbuf, header_at_m147, u8"%"s);
            if (tail_at_m147 == -1)
            {
                break;
            }
            chat_count_at_m147 =
                elona::stoi(strmid(netbuf, header_at_m147, tail_at_m147));
            header_at_m147 += tail_at_m147 + 1;
            if (cnt == 0)
            {
                if (chat_count_at_m147 > count_latest_at_m147)
                {
                    count_latest_at_m147 = chat_count_at_m147;
                }
            }
            if (cnt == 1)
            {
                if (lastchat == 0)
                {
                    break;
                }
            }
            if (chat_count_at_m147 <= lastchat)
            {
                break;
            }
            tail_at_m147 = instr(netbuf, header_at_m147, u8"%"s);
            chat_date_at_m147 = strmid(netbuf, header_at_m147, tail_at_m147);
            header_at_m147 += tail_at_m147 + 1;
            tail_at_m147 = instr(netbuf, header_at_m147, u8"%"s);
            chat_msg_at_m147 = strmid(netbuf, header_at_m147, tail_at_m147);
            header_at_m147 += tail_at_m147 + 1;
            tail_at_m147 = instr(netbuf, header_at_m147, u8"%"s);
            chat_ip_at_m147 = strmid(netbuf, header_at_m147, tail_at_m147);
            header_at_m147 += tail_at_m147 + 2;
            chatnew += ""s + chat_msg_at_m147 + u8"\n"s;
        }
        if (prm_885 == 3)
        {
            tail_at_m147 = instr(netbuf, header_at_m147, u8"%"s);
            if (tail_at_m147 == -1)
            {
                break;
            }
            tail_at_m147 = instr(netbuf, header_at_m147, u8"%"s);
            s = strmid(netbuf, header_at_m147, tail_at_m147);
            header_at_m147 += tail_at_m147 + 1;
            tail_at_m147 = instr(netbuf, header_at_m147, u8"%"s);
            s(1) = strmid(netbuf, header_at_m147, tail_at_m147);
            header_at_m147 += tail_at_m147 + 1;
            break;
        }
    }
    if (prm_885 == 0)
    {
        lastchat = count_latest_at_m147;
    }
    return 1;
}



int net_dllist(const std::string& prm_886, int prm_887)
{
    std::string file_at_m147;
    int size_at_m147 = 0;
    int p_at_m147 = 0;
    int f_at_m147 = 0;
    int nxt_at_m147 = 0;
    std::string s_at_m147;
    netinit();
    neturl(u8"http://homepage3.nifty.com/rfish/userfile/"s);
    file_at_m147 = (filesystem::dir::user() / u8"net.tmp").generic_string();
    if (fs::exists(file_at_m147))
    {
        elona_delete(file_at_m147);
    }
    netdlname(file_at_m147);
    netload(u8"cliplog.txt"s);
    if (!fs::exists(file_at_m147))
    {
        return 0;
    }
    notesel(netbuf);
    {
        netbuf(0).clear();
        std::ifstream in{file_at_m147, std::ios::binary};
        std::string tmp;
        while (std::getline(in, tmp))
        {
            netbuf(0) += tmp + '\n';
        }
    }
    size_at_m147 = fs::file_size(file_at_m147);
    p_at_m147 = 0;
    for (int cnt = 0; cnt < 10000; ++cnt)
    {
        if (!strutil::contains(netbuf(0), u8"<", p_at_m147)
            || p_at_m147 + 1 >= size_at_m147)
        {
            break;
        }
        f_at_m147 = 0;
        for (int cnt = 0; cnt < 14; ++cnt)
        {
            nxt_at_m147 = instr(netbuf, p_at_m147, u8"<"s);
            if (nxt_at_m147 == -1)
            {
                break;
            }
            s_at_m147 = strmid(netbuf, p_at_m147, nxt_at_m147);
            p_at_m147 += nxt_at_m147 + 2;
            if (cnt == 0)
            {
                list(0, listmax) = listmax;
                list(1, listmax) = elona::stoi(s_at_m147);
            }
            if (cnt == 2)
            {
                listn(0, listmax) = ""s + s_at_m147;
                listn(1, listmax) = u8"net"s;
            }
            if (cnt == 3)
            {
                list(2, listmax) = elona::stoi(s_at_m147);
                if (elona::stoi(s_at_m147) != 100001)
                {
                    if (prm_887 == 0)
                    {
                        f_at_m147 = 1;
                    }
                }
            }
            if (cnt == 5)
            {
                listn(0, listmax) += u8" "s + s_at_m147;
            }
            if (cnt == 9)
            {
                if (s_at_m147 != prm_886)
                {
                    f_at_m147 = 1;
                }
            }
        }
        if (f_at_m147 == 0)
        {
            ++listmax;
        }
        ++p_at_m147;
    }
    return 1;
}



int net_dl(const std::string& prm_888, const std::string& prm_889)
{
    if (fs::exists(filesystem::dir::user() / prm_889))
    {
        elona_delete(filesystem::dir::user() / prm_889);
    }
    neturl(u8"http://homepage3.nifty.com/rfish/userfile/"s);
    netdlname((filesystem::dir::user() / prm_889).generic_string());
    netload(prm_888);
    if (!fs::exists(filesystem::dir::user() / u8"user" / prm_889))
    {
        return 0;
    }
    return 1;
}



void initialize_server_info()
{
    elona_vector1<std::string> serverlist;
    SDIM1(cgiurl2);
    SDIM1(cgiurl3);
    SDIM2(serverlist, 200);
    notesel(serverlist);
    int stat = net_read(4);
    if (stat == 1 && config::instance().serverlist == 0)
    {
        serverlist = netbuf;
    }
    else
    {
        {
            serverlist(0).clear();
            std::ifstream in{(filesystem::dir::exe() / u8"server.txt").native(),
                             std::ios::binary};
            std::string tmp;
            while (std::getline(in, tmp))
            {
                serverlist(0) += tmp + '\n';
            }
        }
        netbuf = serverlist;
        dialog(""s + serverlist);
    }
    p = instr(netbuf, 0, u8"%"s);
    cgiurl2 = strmid(netbuf, 0, p);
    cgiurl3 = strmid(netbuf, p + 1, instr(netbuf, p + 1, u8"%"s));
    {
        std::ofstream out{(filesystem::dir::exe() / u8"./server.txt").native(),
                          std::ios::binary};
        out << serverlist(0) << std::endl;
    }
    if (jp)
    {
        chatreadurl = u8"http://www."s + cgiurl2 + u8"/log.txt"s;
        chatsendurl = u8"http://www."s + cgiurl2
            + u8"/cgi-bin/wtalk/wtalk2.cgi?mode=regist"s;
        votesendurl = u8"http://www."s + cgiurl3
            + u8"/cgi-bin/vote/votec.cgi?no=1&mode=wri"s;
        votereadurl = u8"http://www."s + cgiurl3 + u8"/vote.txt"s;
    }
    else
    {
        chatreadurl = u8"http://www."s + cgiurl2 + u8"/logen.txt"s;
        chatsendurl = u8"http://www."s + cgiurl2
            + u8"/cgi-bin/wtalken/wtalk2.cgi?mode=regist"s;
        votesendurl = u8"http://www."s + cgiurl3
            + u8"/cgi-bin/vote/votec.cgi?no=0&mode=wri"s;
        votereadurl = u8"http://www."s + cgiurl3 + u8"/voteen.txt"s;
    }
    textreadurl = u8"http://www."s + cgiurl3 + u8"/text.txt"s;
    return;
}



void show_chat_dialog()
{
    int chatdeny = 0;
    if (chatdeny == 1)
    {
        if (chatturn > 20)
        {
            chatdeny = 0;
        }
        else
        {
            txt(lang(
                u8"もう少し待った方がいい気がする。"s,
                u8"You think you should wait a little more."s));
            return;
        }
    }
    if (jp)
    {
        imeset(1);
    }
    inputlog = "";
    input_text_dialog(80, windowh - inf_verh - 70, 38);
    imeset(0);
    if (inputlog == ""s)
    {
        return;
    }
    if (jp)
    {
        inputlog = u8"「"s + inputlog + u8"」"s;
    }
    else
    {
        inputlog = u8"\""s + inputlog + u8"\""s;
    }
    txt(inputlog);
    net_send(
        u8"chat"s + cdatan(1, 0) + lang(""s, u8" "s) + cdatan(0, 0)
        + lang(""s, u8" says, "s) + inputlog);
    chatturn = 0;
    chatdeny = 1;
    return;
}



int voting_box()
{
label_14001_internal:
    gsel(4);
    for (int cnt = 0; cnt < 8; ++cnt)
    {
        pos(cnt % 4 * 180, cnt / 4 * 300);
        picload(
            filesystem::dir::graphic() / (u8"g"s + (cnt + 1) + u8".bmp"), 1);
    }
    gsel(0);
    listmax = 0;
    page = 0;
    pagesize = 16;
    cs = 0;
    cc = 0;
    cs_bk = -1;
    for (int cnt = 0; cnt < 6; ++cnt)
    {
        listn(0, cnt) = u8"Could not connect to the server."s;
    }
    listmax = 0;
    net_read(5);
    txt(lang(listn(0, 1), listn(0, 2)));
    listmax = 0;
    list(0, listmax) = -999;
    list(1, listmax) = 0;
    listn(0, listmax) =
        lang(u8"あなたの異名を登録する"s, u8"Submit your alias."s);
    ++listmax;
    net_read(1);
    if (gdata_next_voting_time > gdata_hour + gdata_day * 24
            + gdata_month * 24 * 30 + gdata_year * 24 * 30 * 12)
    {
        comctrl = 0;
        txt(lang(
            u8"あなたの投票権はまだ復活していない("s
                + cnvdate(gdata_next_voting_time) + u8"まで)"s,
            u8"You can't vote until "s + cnvdate(gdata_next_voting_time)
                + u8"."s));
        for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
        {
            if (cnt == 0)
            {
                continue;
            }
            list(1, cnt) = 1000000 - list(1, cnt);
        }
        sort_list_and_listn_by_column1();
    }
    else
    {
        comctrl = 1;
        txt(lang(
            u8"どの候補に投票する？"s, u8"Which one do you want to vote?"s));
        for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
        {
            if (cnt == 0)
            {
                continue;
            }
            list(1, cnt) = rnd(10000);
        }
        sort_list_and_listn_by_column1();
        if (listmax > pagesize)
        {
            listmax = pagesize;
        }
    }
    windowshadow = 1;
label_1401_internal:
    cs_bk = -1;
    pagemax = (listmax - 1) / pagesize;
    if (page < 0)
    {
        page = pagemax;
    }
    else if (page > pagemax)
    {
        page = 0;
    }
label_1402_internal:
    s(0) = lang(u8"投票箱"s, u8"Voting Box"s);
    s(1) = lang(u8"決定 [投票する項目を選択]  "s, u8"Enter [Vote] "s) + strhint2
        + strhint3;
    display_window((windoww - 640) / 2 + inf_screenx, winposy(448), 640, 448);
    x = ww / 5 * 3;
    y = wh - 80;
    gmode(4, 180, 300, 50);
    pos(wx + ww / 3 * 2, wy + wh / 2);
    grotate(4, cmbg / 4 % 4 * 180, cmbg / 4 / 4 % 2 * 300, 0, x, y);
    gmode(2);
    s(0) = lang(u8"投票項目"s, u8"Choice"s);
    s(1) = "";
    s(2) = lang(u8"備考"s, u8"Vote"s);
    display_topic(s, wx + 28, wy + 36);
    display_topic(s(2), wx + 440, wy + 36);
    keyrange = 0;
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        key_list(cnt) = key_select(cnt);
        ++keyrange;
        if (cnt % 2 == 0)
        {
            pos(wx + 70, wy + 66 + cnt * 19);
            gfini(540, 18);
            gfdec2(12, 14, 16);
        }
        display_key(wx + 58, wy + 66 + cnt * 19 - 2, cnt);
    }
    gmode(2);
    font(14 - en * 2);
    cs_listbk();
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        i = list(0, p);
        s(0) = ""s + listn(0, p);
        s(1) = ""s + listn(1, p);
        if (p != 0)
        {
            pos(wx + 90, wy + 66 + cnt * 19 + 2);
            if (comctrl == 0)
            {
                mes(lang(u8"第"s + p + u8"位"s, cnvrank(p)));
            }
            else
            {
                mes(lang(u8"候補"s, ""s));
            }
        }
        cs_list(cs == cnt, s, wx + 138, wy + 66 + cnt * 19 - 1);
        if (i != -999)
        {
            pos(wx + 462, wy + 66 + cnt * 19 + 2);
            mes(s(1));
        }
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
    redraw();
    await(config::instance().wait1);
    key_check();
    cursor_check();
    ELONA_GET_SELECTED_ITEM(p, cs = i);
    if (p != -1)
    {
        if (p == -999)
        {
            net_send(""s + cdatan(1, 0) + lang(""s, u8" "s) + cdatan(0, 0), 1);
            ELONA_APPEND_PROMPT(lang(u8"オッケー"s, u8"Ok"s), u8"y"s, u8"0"s);
            rtval = show_prompt(promptx, prompty, 200);
            goto label_14001_internal;
        }
        if (gdata_next_voting_time > gdata_hour + gdata_day * 24
                + gdata_month * 24 * 30 + gdata_year * 24 * 30 * 12)
        {
            snd(27);
            txt(lang(
                u8"まだ投票権が復活していない。"s,
                u8"You need to wait before submitting a new vote."s));
            goto label_1401_internal;
        }
        gdata_next_voting_time = gdata_hour + gdata_day * 24
            + gdata_month * 24 * 30 + gdata_year * 24 * 30 * 12 + 168;
        txt(lang(
            u8"「"s + listn(0, (cs + pagesize * page)) + u8"は素敵！」"s,
            u8"\"I like "s + listn(0, (cs + pagesize * page)) + u8"!\""s));
        txt(lang(u8"投票した。"s, u8"You vote."s));
        net_send(""s + p, 2);
        modrank(6, 100, 5);
        ELONA_APPEND_PROMPT(lang(u8"オッケー"s, u8"Ok"s), u8"y"s, u8"0"s);
        rtval = show_prompt(promptx, prompty, 200);
        goto label_14001_internal;
    }
    if (key == key_pageup)
    {
        if (pagemax != 0)
        {
            snd(1);
            ++page;
            goto label_1401_internal;
        }
    }
    if (key == key_pagedown)
    {
        if (pagemax != 0)
        {
            snd(1);
            --page;
            goto label_1401_internal;
        }
    }
    if (key == key_cancel)
    {
        return -1;
    }
    goto label_1402_internal;
}



} // namespace elona
