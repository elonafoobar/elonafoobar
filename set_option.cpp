#include "elona.hpp"
#include "variables.hpp"



namespace elona
{


void label_2743(bool = true);


int submenu = 0;


void set_option()
{
    int cfg_sound2 = 0;
    int cfg_music2 = 0;
    int cfg_fullscreen2 = 0;
    int windoww2 = 0;
    int windowh2 = 0;
    int sel = 0;
    listmax = 0;
    page = 0;
    pagesize = 18;
    cs = 0;
    cc = 0;
    cs_bk = -1;
    page_bk = 0;
    cs_bk2 = 0;
    cfg_sound2 = cfg_sound;
    cfg_music2 = cfg_music;
    cfg_fullscreen2 = cfg_fullscreen;
    windoww2 = windoww;
    windowh2 = windowh;
    if (mode == 10)
    {
        sel = 2;
    }
    else
    {
        sel = 4;
    }
    gsel(sel);
    {
        int cnt = 0;
        for (int cnt_end = cnt + (8); cnt < cnt_end; ++cnt)
        {
            pos(cnt % 4 * 180, cnt / 4 * 300);
            picload(fs::u8path(u8"./graphic/g"s + (cnt + 1) + u8".bmp"), 1);
        }
    }
    gsel(0);
    redraw(0);
    if (mode == 0)
    {
        screenupdate = -1;
        label_1419();
    }
    if (mode == 10)
    {
        gsel(4);
        gmode(0);
        pos(0, 0);
        picload(fs::u8path(u8"./graphic/title.bmp"), 1);
        gzoom(windoww, windowh, 4, 0, 0, 800, 600);
        gsel(0);
        gmode(0);
        pos(0, 0);
        gcopy(4, 0, 0, windoww, windowh);
        gmode(2);
    }
    if (submenu == 0)
    {
        if (jp)
        {
            q = u8"オプション"s;
            s(0) = u8"ゲームの設定"s;
            s(1) = u8"画面と音の設定"s;
            s(2) = u8"ネット機能の設定"s;
            s(3) = u8"詳細な設定"s;
            s(4) = u8"ゲームパッド"s;
            s(5) = u8"メッセージとログ"s;
            s(6) = u8"言語(Language)"s;
            s(7) = "";
        }
        if (en)
        {
            q = u8"Option"s;
            s(0) = u8"Game Setting"s;
            s(1) = u8"Screen & Sound"s;
            s(2) = u8"Network Setting"s;
            s(3) = u8"Detailed Setting"s;
            s(4) = u8"Game Pad"s;
            s(5) = u8"Message & Log"s;
            s(6) = u8"Language"s;
            s(7) = "";
        }
        dx = 370;
        dy = 270;
    }
    if (submenu == 1)
    {
        if (jp)
        {
            q = u8"ゲームの設定"s;
            s(0) = u8"ノルンの冒険ガイド"s;
            s(1) = u8"非好戦的NPCを無視"s;
            s(2) = u8"zキーの割当て"s;
            s(3) = u8"xキーの割当て"s;
            s(4) = u8"走り始める歩数"s;
            s(5) = u8"歩きの速さ"s;
            s(6) = u8"攻撃の間隔"s;
            s(7) = "";
        }
        if (en)
        {
            q = u8"Game Setting"s;
            s(0) = u8"Extra Help"s;
            s(1) = u8"Neutral Npcs"s;
            s(2) = u8"Assign z key"s;
            s(3) = u8"Assign x key"s;
            s(4) = u8"Start Running After"s;
            s(5) = u8"Walk Speed"s;
            s(6) = u8"Attack Interval"s;
            s(7) = "";
        }
        dx = 440;
        dy = 340;
    }
    if (submenu == 2)
    {
        if (jp)
        {
            q = u8"画面と音の設定"s;
            s(0) = u8"サウンドの再生*"s;
            s(1) = u8"midiの再生*"s;
            s(2) = u8"画面モード*"s;
            s(3) = u8"画面の大きさ*"s;
            s(4) = u8"スクロール"s;
            s(5) = u8"主人公中心に描写"s;
            s(6) = u8"心臓の音"s;
            s(7) = u8"攻撃時アニメ"s;
            s(8) = u8"天候エフェクト"s;
            s(9) = u8"光源の描写"s;
            s(10) = u8"アイテムの影描写"s;
            s(11) = "";
        }
        if (en)
        {
            q = u8"Screen & Sound"s;
            s(0) = u8"Sound*"s;
            s(1) = u8"Music*"s;
            s(2) = u8"Screen Mode*"s;
            s(3) = u8"Screen Resolution*"s;
            s(4) = u8"Smooth Scroll"s;
            s(5) = u8"Always Center"s;
            s(6) = u8"Heartbeat Sound"s;
            s(7) = u8"Attack Animation"s;
            s(8) = u8"Weather Effect"s;
            s(9) = u8"Lighting"s;
            s(10) = u8"object Shadow"s;
            s(11) = "";
        }
        dx = 440;
        dy = 370;
    }
    if (submenu == 3)
    {
        if (jp)
        {
            q = u8"ネット機能の設定"s;
            s(0) = u8"ネットの使用"s;
            s(1) = u8"定期的に接続"s;
            s(2) = u8"チャットをフィルタ"s;
            s(3) = "";
        }
        if (en)
        {
            q = u8"Network Setting"s;
            s(0) = u8"Use Network"s;
            s(1) = u8"Constantly Connect"s;
            s(2) = u8"Filter Chat"s;
            s(3) = "";
        }
        dx = 440;
        dy = 300;
    }
    if (submenu == 4)
    {
        if (jp)
        {
            q = u8"詳細な設定"s;
            s(0) = u8"走りの速さ"s;
            s(1) = u8"numlockを自動制御"s;
            s(2) = u8"タイトルの水の波紋"s;
            s(3) = u8"画面の更新頻度"s;
            s(4) = u8"走り時スクロール"s;
            s(5) = u8"オートターンの挙動"s;
            s(6) = u8"イベントの短縮"s;
            s(7) = "";
        }
        if (en)
        {
            q = u8"Detailed Setting"s;
            s(0) = u8"Run Speed"s;
            s(1) = u8"Auto Numlock"s;
            s(2) = u8"Title Water Effect"s;
            s(3) = u8"Screen Refresh"s;
            s(4) = u8"Scroll When Run"s;
            s(5) = u8"Auto Turn Speed"s;
            s(6) = u8"Skip Random Events"s;
            s(7) = "";
        }
        dx = 440;
        dy = 300;
    }
    if (submenu == 5)
    {
        if (jp)
        {
            q = u8"ゲームパッド"s;
            s(0) = u8"ゲームパッド"s;
            s(1) = u8"決定キー"s;
            s(2) = u8"キャンセルキー"s;
            s(3) = u8"所持品"s;
            s(4) = u8"行動"s;
            s(5) = u8"斜め移動(L)"s;
            s(6) = u8"拾う(R)"s;
            s(7) = u8"射撃(R)"s;
            s(8) = u8"目標(L)"s;
            s(9) = u8"ポーズメニュー"s;
            s(10) = u8"ヘルプ"s;
            s(11) = u8"キャラ情報"s;
            s(12) = u8"装填"s;
            s(13) = "";
        }
        if (en)
        {
            q = u8"Game Pad"s;
            s(0) = u8"Game Pad"s;
            s(1) = u8"Enter/Ok"s;
            s(2) = u8"Cancel"s;
            s(3) = u8"Inventory"s;
            s(4) = u8"Action"s;
            s(5) = u8"diagonal Move/(L)"s;
            s(6) = u8"Pick/(R)"s;
            s(7) = u8"Shoot/(R)"s;
            s(8) = u8"Target/(L)"s;
            s(9) = u8"Peuse/Menu"s;
            s(10) = u8"Help"s;
            s(11) = u8"Chara-sheet"s;
            s(12) = u8"Reload"s;
            s(13) = "";
        }
        dx = 440;
        dy = 430;
    }
    if (submenu == 6)
    {
        if (jp)
        {
            q = u8"メッセージとログ"s;
            s(0) = u8"ﾒｯｾｰｼﾞに分表示追加"s;
            s(1) = u8"過去のﾒｯｾｰｼﾞの透過"s;
            s(2) = "";
        }
        if (en)
        {
            q = u8"Message&Log"s;
            s(0) = u8"Add time info"s;
            s(1) = u8"Transparency"s;
            s(2) = "";
        }
        dx = 440;
        dy = 300;
    }
    if (submenu == 7)
    {
        if (jp)
        {
            q = u8"言語(Language)"s;
            s(0) = u8"言語*"s;
            s(1) = "";
        }
        if (en)
        {
            q = u8"Language"s;
            s(0) = u8"Language*"s;
            s(1) = "";
        }
        dx = 440;
        dy = 300;
    }
    {
        int cnt = 0;
        for (int cnt_end = cnt + (20); cnt < cnt_end; ++cnt)
        {
            if (s(cnt) == ""s)
            {
                break;
            }
            list(0, listmax) = cnt;
            listn(0, listmax) = s(cnt);
            ++listmax;
        }
    }
    windowshadow = 1;
label_2724_internal:
    if (cfg_zkey == 0)
    {
        key_quick = u8"z"s;
        key_zap = u8"Z"s;
    }
    else if (cfg_zkey == 1)
    {
        key_zap = u8"z"s;
        key_quick = u8"Z"s;
    }
    if (cfg_xkey == 0)
    {
        key_quickinv = u8"x"s;
        key_inventory = u8"X"s;
    }
    else if (cfg_xkey == 1)
    {
        key_inventory = u8"x"s;
        key_quickinv = u8"X"s;
    }
    redraw(0);
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
label_2725_internal:
    redraw(0);
    s(0) = q;
    s(1) = strhint3;
    pagesize = 0;
    if (mode == 1)
    {
        display_window(
            (windoww - dx) / 2 + inf_screenx, winposy(dy, 1), dx, dy);
    }
    else
    {
        display_window(
            (windoww - dx) / 2 + inf_screenx, winposy(dy) - 12, dx, dy);
    }
    pagesize = listmax;
    display_topic(lang(u8"項目"s, u8"Menu"s), wx + 34, wy + 36);
    if (mode == 10)
    {
        p = 2;
    }
    else
    {
        p = 4;
    }
    x = ww / 5 * 3;
    y = wh - 80;
    gmode(4, 180, 300, 50);
    pos(wx + ww / 3, wy + wh / 2);
    grotate(p, cmbg / 4 % 4 * 180, cmbg / 4 / 4 % 2 * 300, 0, x, y);
    gmode(2);
    keyrange = 0;
    {
        int cnt = 0;
        for (int cnt_end = cnt + (pagesize); cnt < cnt_end; ++cnt)
        {
            p = pagesize * page + cnt;
            if (p >= listmax)
            {
                break;
            }
            if (submenu == 0)
            {
                key_list(cnt) = key_select(cnt);
                ++keyrange;
                display_key(wx + 32, wy + 66 + cnt * 19 - 2, cnt);
            }
            else
            {
                key_list(cnt) = key_cancel;
                ++keyrange;
            }
        }
    }
    if (submenu == 5)
    {
        p(0) = 0;
        p(1) = cnvjkey(key_enter);
        p(2) = cnvjkey(key_cancel);
        p(3) = cnvjkey(key_quickinv);
        p(4) = cnvjkey(key_quick);
        p(5) = cnvjkey(key_alter);
        p(6) = cnvjkey(key_get);
        p(7) = cnvjkey(key_fire);
        p(8) = cnvjkey(key_target);
        p(9) = cnvjkey(key_esc);
        p(10) = cnvjkey(key_help);
        p(11) = cnvjkey(key_charainfo);
        p(12) = cnvjkey(key_ammo);
        {
            int cnt = 1;
            for (int cnt_end = cnt + (19); cnt < cnt_end; ++cnt)
            {
                list(1, cnt) = p(cnt);
            }
        }
    }
    font(lang(cfg_font1, cfg_font2), 14 - en * 2, 0);
    cs_listbk();
    {
        int cnt = 0;
        for (int cnt_end = cnt + (pagesize); cnt < cnt_end; ++cnt)
        {
            p = pagesize * page + cnt;
            if (p >= listmax)
            {
                break;
            }
            i = list(0, p);
            s = listn(0, p);
            if (submenu == 0)
            {
                x = 8;
            }
            else
            {
                x = 0;
            }
            if (submenu == 3)
            {
                if (cfg_net == 0)
                {
                    if (cnt >= 1)
                    {
                        continue;
                    }
                }
            }
            cs_list(cnt, s, wx + 56 + x, wy + 66 + cnt * 19 - 1, 19, 0);
            if ((submenu != 5 || cnt <= 0) && submenu != 0)
            {
                pos(wx + 220, wy + 66 + cnt * 19 - 5);
                gcopy(3, 312, 336, 24, 24);
                pos(wx + 358, wy + 66 + cnt * 19 - 5);
                gcopy(3, 336, 336, 24, 24);
            }
            pos(wx + 250, wy + 66 + cnt * 19);
            color(0, 0, 0);
            if (submenu == 1)
            {
                if (cnt == 0)
                {
                    if (jp)
                    {
                        s(0) = u8"なし"s;
                        s(1) = u8"あり"s;
                    }
                    else
                    {
                        s(0) = u8"Don't show"s;
                        s(1) = u8"Show"s;
                    }
                    mes(s(cfg_extrahelp));
                }
                if (cnt == 1)
                {
                    if (jp)
                    {
                        s(0) = u8"しない"s;
                        s(1) = u8"する"s;
                    }
                    else
                    {
                        s(0) = u8"Attack"s;
                        s(1) = u8"Ignore"s;
                    }
                    mes(s(cfg_ignoredislike));
                }
                if (cnt == 2)
                {
                    if (jp)
                    {
                        s(0) = u8"ｸｨｯｸﾒﾆｭｰ"s;
                        s(1) = u8"道具を振る"s;
                        s(2) = u8"割当なし"s;
                    }
                    else
                    {
                        s(0) = u8"Quick menu"s;
                        s(1) = u8"Zap"s;
                        s(2) = u8"Don't assign"s;
                    }
                    mes(s(cfg_zkey));
                }
                if (cnt == 3)
                {
                    if (jp)
                    {
                        s(0) = u8"ｸｲｯｸｲﾝﾍﾞﾝﾄﾘ"s;
                        s(1) = u8"道具を調べる"s;
                        s(2) = u8"割当なし"s;
                    }
                    else
                    {
                        s(0) = u8"Quick Inv"s;
                        s(1) = u8"Identify"s;
                        s(2) = u8"Don't assign"s;
                    }
                    mes(s(cfg_xkey));
                }
                if (cnt == 4)
                {
                    if (cfg_startrun >= 20)
                    {
                        if (jp)
                        {
                            mes(u8"走らない"s);
                        }
                        else
                        {
                            mes(u8"Dont't run"s);
                        }
                    }
                    else if (jp)
                    {
                        mes(""s + (cfg_startrun + 1) + u8"歩目から"s);
                    }
                    else
                    {
                        mes(u8"After "s + (cfg_startrun + 1) + u8" steps"s);
                    }
                }
                if (cnt == 5)
                {
                    mes(""s + cfg_walkwait + u8" wait"s);
                }
                if (cnt == 6)
                {
                    mes(""s + cfg_attackwait + u8" wait"s);
                }
            }
            if (submenu == 2)
            {
                if (cnt == 0)
                {
                    if (jp)
                    {
                        s(0) = u8"なし"s;
                        s(1) = u8"direct sound"s;
                        s(2) = u8"MCI"s;
                    }
                    else
                    {
                        s(0) = u8"None"s;
                        s(1) = u8"Direct sound"s;
                        s(2) = u8"MCI"s;
                    }
                    mes(s(cfg_sound2));
                }
                if (cnt == 1)
                {
                    if (jp)
                    {
                        s(0) = u8"なし"s;
                        s(1) = u8"direct music"s;
                        s(2) = u8"MCI"s;
                    }
                    else
                    {
                        s(0) = u8"None"s;
                        s(1) = u8"Direct music"s;
                        s(2) = u8"MCI"s;
                    }
                    mes(s(cfg_music2));
                }
                if (cnt == 2)
                {
                    if (jp)
                    {
                        s(0) = u8"ウィンドウ"s;
                        s(1) = u8"フルスクリーン"s;
                    }
                    else
                    {
                        s(0) = u8"Window mode"s;
                        s(1) = u8"Full screen"s;
                    }
                    mes(s(cfg_fullscreen2));
                }
                if (cnt == 3)
                {
                    mes(""s + windoww2 + u8" * "s + windowh2);
                }
                if (cnt == 4)
                {
                    if (jp)
                    {
                        s(0) = u8"しない"s;
                        s(1) = u8"する"s;
                    }
                    else
                    {
                        s(0) = u8"No"s;
                        s(1) = u8"Yes"s;
                    }
                    mes(s(cfg_scroll));
                }
                if (cnt == 5)
                {
                    if (jp)
                    {
                        s(0) = u8"しない"s;
                        s(1) = u8"する"s;
                    }
                    else
                    {
                        s(0) = u8"No"s;
                        s(1) = u8"Yes"s;
                    }
                    mes(s(cfg_alwayscenter));
                }
                if (cnt == 6)
                {
                    if (jp)
                    {
                        s(0) = u8"再生しない"s;
                        s(1) = u8"再生する"s;
                    }
                    else
                    {
                        s(0) = u8"Don't play"s;
                        s(1) = u8"Play"s;
                    }
                    mes(s(cfg_heart));
                }
                if (cnt == 7)
                {
                    if (jp)
                    {
                        s(0) = u8"アニメなし"s;
                        s(1) = u8"アニメあり"s;
                    }
                    else
                    {
                        s(0) = u8"No"s;
                        s(1) = u8"Yes"s;
                    }
                    mes(s(cfg_attackanime));
                }
                if (cnt == 8)
                {
                    if (jp)
                    {
                        s(0) = u8"アニメなし"s;
                        s(1) = u8"アニメあり"s;
                    }
                    else
                    {
                        s(0) = u8"No animation"s;
                        s(1) = u8"Always"s;
                    }
                    mes(s(cfg_env));
                }
                if (cnt == 9)
                {
                    if (jp)
                    {
                        s(0) = u8"高画質"s;
                        s(1) = u8"低画質"s;
                    }
                    else
                    {
                        s(0) = u8"High"s;
                        s(1) = u8"Low"s;
                    }
                    mes(s(cfg_shadow));
                }
                if (cnt == 10)
                {
                    if (jp)
                    {
                        s(0) = u8"なし（高速）"s;
                        s(1) = u8"あり（低速）"s;
                    }
                    else
                    {
                        s(0) = u8"No(Slow)"s;
                        s(1) = u8"Yes(Fast)"s;
                    }
                    mes(s(cfg_objectshadow));
                }
            }
            if (submenu == 3)
            {
                if (cnt == 0)
                {
                    if (jp)
                    {
                        s(0) = u8"しない"s;
                        s(1) = u8"する"s;
                    }
                    else
                    {
                        s(0) = u8"No"s;
                        s(1) = u8"Yes"s;
                    }
                    mes(s(cfg_net));
                }
                if (cnt == 1)
                {
                    if (jp)
                    {
                        s(0) = u8"しない"s;
                        s(1) = u8"する"s;
                    }
                    else
                    {
                        s(0) = u8"No"s;
                        s(1) = u8"Yes"s;
                    }
                    mes(s(cfg_netwish));
                }
                if (cnt == 2)
                {
                    if (jp)
                    {
                        s(0) = u8"しない"s;
                        s(1) = u8"する"s;
                    }
                    else
                    {
                        s(0) = u8"No"s;
                        s(1) = u8"Yes"s;
                    }
                    mes(s(cfg_netchat));
                }
            }
            if (submenu == 4)
            {
                if (cnt == 0)
                {
                    mes(""s + cfg_runwait + u8" wait"s);
                }
                if (cnt == 1)
                {
                    if (jp)
                    {
                        s(0) = u8"しない"s;
                        s(1) = u8"する"s;
                    }
                    else
                    {
                        s(0) = u8"No"s;
                        s(1) = u8"Yes"s;
                    }
                    mes(s(cfg_autonumlock));
                }
                if (cnt == 2)
                {
                    if (jp)
                    {
                        s(0) = u8"オフ(オンには出来ません)"s;
                        s(1) = u8"オフ(オンには出来ません)"s;
                    }
                    else
                    {
                        s(0) = u8"No(unsupported)"s;
                        s(1) = u8"No(unsupported)"s;
                    }
                    mes(s(0));
                }
                if (cnt == 3)
                {
                    if (jp)
                    {
                        s(0) = u8"オフ"s;
                        s(1) = u8"オン"s;
                    }
                    else
                    {
                        s(0) = u8"No"s;
                        s(1) = u8"Yes"s;
                    }
                    mes(""s + cfg_scrsync + u8" wait"s);
                }
                if (cnt == 4)
                {
                    if (jp)
                    {
                        s(0) = u8"しない"s;
                        s(1) = u8"する"s;
                    }
                    else
                    {
                        s(0) = u8"No"s;
                        s(1) = u8"Yes"s;
                    }
                    mes(s(cfg_runscroll));
                }
                if (cnt == 5)
                {
                    if (jp)
                    {
                        s(0) = u8"普通"s;
                        s(1) = u8"速め"s;
                        s(2) = u8"省略"s;
                    }
                    else
                    {
                        s(0) = u8"Normal"s;
                        s(1) = u8"High"s;
                        s(2) = u8"Highest"s;
                    }
                    mes(s(cfg_autoturn));
                }
                if (cnt == 6)
                {
                    if (jp)
                    {
                        s(0) = u8"しない"s;
                        s(1) = u8"する"s;
                    }
                    else
                    {
                        s(0) = u8"No"s;
                        s(1) = u8"Yes"s;
                    }
                    mes(s(cfg_skiprandevents));
                }
            }
            if (submenu == 5)
            {
                if (cnt == 0)
                {
                    if (jp)
                    {
                        s(0) = u8"使用しない"s;
                        s(1) = u8"使用する"s;
                    }
                    else
                    {
                        s(0) = u8"Don't use"s;
                        s(1) = u8"Use"s;
                    }
                    mes(s(cfg_joypad));
                }
                else if (list(1, cnt) == -1)
                {
                    mes(lang(u8"未設定"s, u8"Unassigned"s));
                }
                else
                {
                    mes(lang(u8"ボタン"s, u8"Button"s) + list(1, cnt));
                }
            }
            if (submenu == 6)
            {
                if (cnt == 0)
                {
                    if (jp)
                    {
                        s(0) = u8"しない"s;
                        s(1) = u8"する"s;
                    }
                    else
                    {
                        s(0) = u8"No"s;
                        s(1) = u8"Yes"s;
                    }
                    mes(s(cfg_msgaddtime));
                }
                if (cnt == 1)
                {
                    mes(""s + cfg_msgtrans * 10 + u8" %"s);
                }
            }
            if (submenu == 7)
            {
                if (cnt == 0)
                {
                    s(0) = u8"Japanese"s;
                    s(1) = u8"English"s;
                    mes(s(cfg_language));
                }
            }
        }
    }
    if (submenu != 0)
    {
        if (submenu != 5)
        {
            pos(wx + 40, wy + wh - 70);
            font(lang(cfg_font1, cfg_font2), 12 + sizefix - en * 2, 0);
            color(0, 0, 0);
            if (jp)
            {
                mes(u8"* 印のついた項目は、ゲームの再起動後に適用されます"s);
            }
            else
            {
                mes(u8"Items marked with * require restart to apply changes."s);
            }
        }
    }
    if (submenu == 5)
    {
        pos(wx + 40, wy + wh - 110);
        font(lang(cfg_font1, cfg_font2), 12 + sizefix - en * 2, 0);
        color(0, 0, 0);
        if (jp)
        {
            mes(u8"ボタンを割り当てたい項目にカーソルをあわせて\nゲームパッドのボタンを押してください。(L),(R)の付いている\n項目は、メニュー画面でタブの移動に使われます。"s);
        }
        else
        {
            mes(u8"To assign a button, move the cursor to\nan item and press the button."s);
        }
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
    redraw(1);
    await(cfg_wait1);
    key_check();
    cursor_check();
    p = -1;
    {
        int cnt = 0;
        for (int cnt_end = cnt + (keyrange); cnt < cnt_end; ++cnt)
        {
            if (key == key_select(cnt))
            {
                p = list(0, pagesize * page + cnt);
                cs = cnt;
                break;
            }
        }
    }
    if (p != -1)
    {
        if (submenu == 0)
        {
            submenu = p + 1;
            snd(20);
            set_option();
            return;
        }
    }
    if (submenu == 5)
    {
        if (cs > 0)
        {
            DIGETJOYSTATE(j, 0);
            f = 0;
            {
                int cnt = 0;
                for (int cnt_end = cnt + (12); cnt < cnt_end; ++cnt)
                {
                    if (HMMBITCHECK(j, 4 + cnt))
                    {
                        p = cnt;
                        valn = "";
                        {
                            int cnt = 0;
                            for (int cnt_end = cnt + (12); cnt < cnt_end; ++cnt)
                            {
                                jkey(cnt) = "";
                            }
                        }
                        list(1, cs) = p;
                        {
                            int cnt = 1;
                            for (int cnt_end = cnt + (19); cnt < cnt_end; ++cnt)
                            {
                                if (cs == cnt)
                                {
                                    continue;
                                }
                                --list(1, cnt);
                                if (list(1, cnt) == p || list(1, cnt) <= -1)
                                {
                                    list(1, cnt) = 12;
                                }
                            }
                        }
                        valn(0) = u8"key_enter."s;
                        valn(1) = key_enter;
                        valn(2) = ""s + list(1, 1);
                        valn(3) = "";
                        jkey(list(1, 1)) = ""s + key_enter;
                        label_2713();
                        valn(0) = u8"key_cancel."s;
                        valn(1) = key_cancel;
                        valn(2) = ""s + list(1, 2);
                        valn(3) = "";
                        jkey(list(1, 2)) = ""s + key_cancel;
                        label_2713();
                        valn(0) = u8"key_quickinv."s;
                        valn(1) = key_quickinv;
                        valn(2) = ""s + list(1, 3);
                        valn(3) = "";
                        jkey(list(1, 3)) = ""s + key_quickinv;
                        label_2713();
                        valn(0) = u8"key_quick."s;
                        valn(1) = key_quick;
                        valn(2) = ""s + list(1, 4);
                        valn(3) = "";
                        jkey(list(1, 4)) = ""s + key_quick;
                        label_2713();
                        valn(0) = u8"key_alter."s;
                        valn(1) = key_alter;
                        valn(2) = ""s + list(1, 5);
                        valn(3) = "";
                        jkey(list(1, 5)) = ""s + key_alter;
                        label_2713();
                        valn(0) = u8"key_get."s;
                        valn(1) = key_get;
                        valn(2) = ""s + list(1, 6);
                        valn(3) = "";
                        jkey(list(1, 6)) = ""s + key_get;
                        label_2713();
                        valn(0) = u8"key_fire."s;
                        valn(1) = key_fire;
                        valn(2) = ""s + list(1, 7);
                        valn(3) = "";
                        jkey(list(1, 7)) = ""s + key_fire;
                        label_2713();
                        valn(0) = u8"key_target."s;
                        valn(1) = key_target;
                        valn(2) = ""s + list(1, 8);
                        valn(3) = "";
                        jkey(list(1, 8)) = ""s + key_target;
                        label_2713();
                        valn(0) = u8"key_esc."s;
                        valn(1) = key_esc;
                        valn(2) = ""s + list(1, 9);
                        valn(3) = "";
                        jkey(list(1, 9)) = ""s + key_esc;
                        label_2713();
                        valn(0) = u8"key_help."s;
                        valn(1) = key_help;
                        valn(2) = ""s + list(1, 10);
                        valn(3) = "";
                        jkey(list(1, 10)) = ""s + key_help;
                        label_2713();
                        valn(0) = u8"key_charainfo."s;
                        valn(1) = key_charainfo;
                        valn(2) = ""s + list(1, 11);
                        valn(3) = "";
                        jkey(list(1, 11)) = ""s + key_charainfo;
                        label_2713();
                        valn(0) = u8"key_ammo."s;
                        valn(1) = key_ammo;
                        valn(2) = ""s + list(1, 12);
                        valn(3) = "";
                        jkey(list(1, 12)) = ""s + key_ammo;
                        label_2713();
                        p(0) = 0;
                        p(1) = cnvjkey(key_enter);
                        p(2) = cnvjkey(key_cancel);
                        p(3) = cnvjkey(key_quickinv);
                        p(4) = cnvjkey(key_quick);
                        p(5) = cnvjkey(key_alter);
                        p(6) = cnvjkey(key_get);
                        p(7) = cnvjkey(key_fire);
                        p(8) = cnvjkey(key_target);
                        p(9) = cnvjkey(key_esc);
                        p(10) = cnvjkey(key_help);
                        p(11) = cnvjkey(key_charainfo);
                        p(12) = cnvjkey(key_ammo);
                        {
                            int cnt = 1;
                            for (int cnt_end = cnt + (19); cnt < cnt_end; ++cnt)
                            {
                                list(1, cnt) = p(cnt);
                            }
                        }
                        f = 1;
                        break;
                    }
                }
            }
            if (f)
            {
                snd(20);
                await(200);
                goto label_2724_internal;
            }
        }
    }
    if (key == key_pageup || key == key_pagedown)
    {
        if (key == key_pageup)
        {
            p = 1;
        }
        else
        {
            p = -1;
        }
        if (submenu == 1)
        {
            if (cs == 0)
            {
                cfg_extrahelp += p;
                if (cfg_extrahelp > 1)
                {
                    cfg_extrahelp = 1;
                }
                else if (cfg_extrahelp < 0)
                {
                    cfg_extrahelp = 0;
                }
                snd(20);
                valn(0) = u8"extraHelp."s;
                valn(1) = std::to_string(cfg_extrahelp);
                label_2713();
                goto label_2724_internal;
            }
            if (cs == 1)
            {
                cfg_ignoredislike += p;
                if (cfg_ignoredislike > 1)
                {
                    cfg_ignoredislike = 1;
                }
                else if (cfg_ignoredislike < 0)
                {
                    cfg_ignoredislike = 0;
                }
                snd(20);
                valn(0) = u8"ignoreDislike."s;
                valn(1) = std::to_string(cfg_ignoredislike);
                label_2713();
                goto label_2724_internal;
            }
            if (cs == 2)
            {
                cfg_zkey += p;
                if (cfg_zkey > 2)
                {
                    cfg_zkey = 2;
                }
                else if (cfg_zkey < 0)
                {
                    cfg_zkey = 0;
                }
                snd(20);
                valn(0) = u8"zkey."s;
                valn(1) = std::to_string(cfg_zkey);
                label_2713();
                goto label_2724_internal;
            }
            if (cs == 3)
            {
                cfg_xkey += p;
                if (cfg_xkey > 2)
                {
                    cfg_xkey = 2;
                }
                else if (cfg_xkey < 0)
                {
                    cfg_xkey = 0;
                }
                snd(20);
                valn(0) = u8"xkey."s;
                valn(1) = std::to_string(cfg_xkey);
                label_2713();
                goto label_2724_internal;
            }
            if (cs == 4)
            {
                cfg_startrun += p;
                if (cfg_startrun > 20)
                {
                    cfg_startrun = 20;
                }
                else if (cfg_startrun < 0)
                {
                    cfg_startrun = 0;
                }
                snd(20);
                valn(0) = u8"startRun."s;
                valn(1) = std::to_string(cfg_startrun);
                label_2713();
                goto label_2724_internal;
            }
            if (cs == 5)
            {
                cfg_walkwait += p;
                if (cfg_walkwait > 10)
                {
                    cfg_walkwait = 10;
                }
                else if (cfg_walkwait < 1)
                {
                    cfg_walkwait = 1;
                }
                snd(20);
                valn(0) = u8"walkWait."s;
                valn(1) = std::to_string(cfg_walkwait);
                label_2713();
                goto label_2724_internal;
            }
            if (cs == 6)
            {
                cfg_attackwait += p;
                if (cfg_attackwait > 20)
                {
                    cfg_attackwait = 20;
                }
                else if (cfg_attackwait < 1)
                {
                    cfg_attackwait = 1;
                }
                snd(20);
                valn(0) = u8"attackWait."s;
                valn(1) = std::to_string(cfg_attackwait);
                label_2713();
                goto label_2724_internal;
            }
        }
        if (submenu == 2)
        {
            if (cs == 0)
            {
                cfg_sound2 += p;
                if (cfg_sound2 > 2)
                {
                    cfg_sound2 = 2;
                }
                else if (cfg_sound2 < 0)
                {
                    cfg_sound2 = 0;
                }
                snd(20);
                valn(0) = u8"sound."s;
                valn(1) = std::to_string(cfg_sound2);
                label_2713();
                goto label_2724_internal;
            }
            if (cs == 1)
            {
                cfg_music2 += p;
                if (cfg_music2 > 2)
                {
                    cfg_music2 = 2;
                }
                else if (cfg_music2 < 0)
                {
                    cfg_music2 = 0;
                }
                snd(20);
                valn(0) = u8"music."s;
                valn(1) = std::to_string(cfg_music2);
                label_2713();
                goto label_2724_internal;
            }
            if (cs == 2)
            {
                cfg_fullscreen2 += p;
                if (cfg_fullscreen2 > 1)
                {
                    cfg_fullscreen2 = 1;
                }
                else if (cfg_fullscreen2 < 0)
                {
                    cfg_fullscreen2 = 0;
                }
                snd(20);
                valn(0) = u8"fullscreen."s;
                valn(1) = std::to_string(cfg_fullscreen2);
                label_2713();
                goto label_2724_internal;
            }
            if (cs == 4)
            {
                cfg_scroll += p;
                if (cfg_scroll > 1)
                {
                    cfg_scroll = 1;
                }
                else if (cfg_scroll < 0)
                {
                    cfg_scroll = 0;
                }
                snd(20);
                valn(0) = u8"scroll."s;
                valn(1) = std::to_string(cfg_scroll);
                label_2713();
                goto label_2724_internal;
            }
            if (cs == 5)
            {
                cfg_alwayscenter += p;
                if (cfg_alwayscenter > 1)
                {
                    cfg_alwayscenter = 1;
                }
                else if (cfg_alwayscenter < 0)
                {
                    cfg_alwayscenter = 0;
                }
                snd(20);
                valn(0) = u8"alwaysCenter."s;
                valn(1) = std::to_string(cfg_alwayscenter);
                label_2713();
                goto label_2724_internal;
            }
            if (cs == 6)
            {
                cfg_heart += p;
                if (cfg_heart > 1)
                {
                    cfg_heart = 1;
                }
                else if (cfg_heart < 0)
                {
                    cfg_heart = 0;
                }
                snd(20);
                valn(0) = u8"heartbeat."s;
                valn(1) = std::to_string(cfg_heart);
                label_2713();
                goto label_2724_internal;
            }
            if (cs == 7)
            {
                cfg_attackanime += p;
                if (cfg_attackanime > 1)
                {
                    cfg_attackanime = 1;
                }
                else if (cfg_attackanime < 0)
                {
                    cfg_attackanime = 0;
                }
                snd(20);
                valn(0) = u8"attackAnime."s;
                valn(1) = std::to_string(cfg_attackanime);
                label_2713();
                goto label_2724_internal;
            }
            if (cs == 8)
            {
                cfg_env += p;
                if (cfg_env > 1)
                {
                    cfg_env = 1;
                }
                else if (cfg_env < 0)
                {
                    cfg_env = 0;
                }
                snd(20);
                valn(0) = u8"envEffect."s;
                valn(1) = std::to_string(cfg_env);
                label_2713();
                goto label_2724_internal;
            }
            if (cs == 9)
            {
                cfg_shadow += p;
                if (cfg_shadow > 1)
                {
                    cfg_shadow = 1;
                }
                else if (cfg_shadow < 0)
                {
                    cfg_shadow = 0;
                }
                snd(20);
                valn(0) = u8"shadow."s;
                valn(1) = std::to_string(cfg_shadow);
                label_2713();
                goto label_2724_internal;
            }
            if (cs == 10)
            {
                cfg_objectshadow += p;
                if (cfg_objectshadow > 1)
                {
                    cfg_objectshadow = 1;
                }
                else if (cfg_objectshadow < 0)
                {
                    cfg_objectshadow = 0;
                }
                snd(20);
                valn(0) = u8"objectShadow."s;
                valn(1) = std::to_string(cfg_objectshadow);
                label_2713();
                goto label_2724_internal;
            }
            if (cs == 3)
            {
                x(0) = 800;
                x(1) = 800;
                x(2) = 1024;
                x(3) = 1152;
                x(4) = 1280;
                x(5) = 1280;
                y(0) = 600;
                y(1) = 696;
                y(2) = 768;
                y(3) = 864;
                y(4) = 768;
                y(5) = 1024;
                i = 0;
                {
                    int cnt = 0;
                    for (int cnt_end = cnt + (5); cnt < cnt_end; ++cnt)
                    {
                        if (windoww2 == x(cnt))
                        {
                            if (windowh2 == y(cnt))
                            {
                                i = cnt;
                                break;
                            }
                        }
                    }
                }
                i += p;
                if (i < 0)
                {
                    i = 0;
                }
                else if (i > 4)
                {
                    i = 4;
                }
                windoww2 = x(i);
                windowh2 = y(i);
                valn(0) = u8"windowW."s;
                valn(1) = ""s + windoww2;
                label_2713();
                valn(0) = u8"windowH."s;
                valn(1) = ""s + windowh2;
                label_2713();
                snd(20);
                goto label_2724_internal;
            }
        }
        if (submenu == 3)
        {
            if (cs == 0)
            {
                cfg_net += p;
                if (cfg_net > 1)
                {
                    cfg_net = 1;
                }
                else if (cfg_net < 0)
                {
                    cfg_net = 0;
                }
                snd(20);
                valn(0) = u8"net."s;
                valn(1) = std::to_string(cfg_net);
                label_2713();
                goto label_2724_internal;
            }
            if (cs == 1)
            {
                cfg_netwish += p;
                if (cfg_netwish > 1)
                {
                    cfg_netwish = 1;
                }
                else if (cfg_netwish < 0)
                {
                    cfg_netwish = 0;
                }
                snd(20);
                valn(0) = u8"netWish."s;
                valn(1) = std::to_string(cfg_netwish);
                label_2713();
                goto label_2724_internal;
            }
            if (cs == 2)
            {
                cfg_netchat += p;
                if (cfg_netchat > 1)
                {
                    cfg_netchat = 1;
                }
                else if (cfg_netchat < 0)
                {
                    cfg_netchat = 0;
                }
                snd(20);
                valn(0) = u8"netChat."s;
                valn(1) = std::to_string(cfg_netchat);
                label_2713();
                goto label_2724_internal;
            }
        }
        if (submenu == 4)
        {
            if (cs == 0)
            {
                cfg_runwait += p;
                if (cfg_runwait > 5)
                {
                    cfg_runwait = 5;
                }
                else if (cfg_runwait < 2)
                {
                    cfg_runwait = 2;
                }
                snd(20);
                valn(0) = u8"runWait."s;
                valn(1) = std::to_string(cfg_runwait);
                label_2713();
                goto label_2724_internal;
            }
            if (cs == 1)
            {
                cfg_autonumlock += p;
                if (cfg_autonumlock > 1)
                {
                    cfg_autonumlock = 1;
                }
                else if (cfg_autonumlock < 0)
                {
                    cfg_autonumlock = 0;
                }
                snd(20);
                valn(0) = u8"autoNumlock."s;
                valn(1) = std::to_string(cfg_autonumlock);
                label_2713();
                goto label_2724_internal;
            }
            if (cs == 2)
            {
                snd(20);
                valn(0) = u8"titleEffect."s;
                valn(1) = std::to_string(0);
                label_2713();
                goto label_2724_internal;
            }
            if (cs == 3)
            {
                cfg_scrsync += p;
                if (cfg_scrsync > 25)
                {
                    cfg_scrsync = 25;
                }
                else if (cfg_scrsync < 2)
                {
                    cfg_scrsync = 2;
                }
                snd(20);
                valn(0) = u8"scr_sync."s;
                valn(1) = std::to_string(cfg_scrsync);
                label_2713();
                goto label_2724_internal;
            }
            if (cs == 4)
            {
                cfg_runscroll += p;
                if (cfg_runscroll > 1)
                {
                    cfg_runscroll = 1;
                }
                else if (cfg_runscroll < 0)
                {
                    cfg_runscroll = 0;
                }
                snd(20);
                valn(0) = u8"scroll_run."s;
                valn(1) = std::to_string(cfg_runscroll);
                label_2713();
                goto label_2724_internal;
            }
            if (cs == 5)
            {
                cfg_autoturn += p;
                if (cfg_autoturn > 2)
                {
                    cfg_autoturn = 2;
                }
                else if (cfg_autoturn < 0)
                {
                    cfg_autoturn = 0;
                }
                snd(20);
                valn(0) = u8"autoTurnType."s;
                valn(1) = std::to_string(cfg_autoturn);
                label_2713();
                goto label_2724_internal;
            }
            if (cs == 6)
            {
                cfg_skiprandevents += p;
                if (cfg_skiprandevents > 1)
                {
                    cfg_skiprandevents = 1;
                }
                else if (cfg_skiprandevents < 0)
                {
                    cfg_skiprandevents = 0;
                }
                snd(20);
                valn(0) = u8"skipRandEvents."s;
                valn(1) = std::to_string(cfg_skiprandevents);
                label_2713();
                goto label_2724_internal;
            }
        }
        if (submenu == 5)
        {
            if (cs == 0)
            {
                cfg_joypad += p;
                if (cfg_joypad > 1)
                {
                    cfg_joypad = 1;
                }
                else if (cfg_joypad < 0)
                {
                    cfg_joypad = 0;
                }
                snd(20);
                valn(0) = u8"joypad."s;
                valn(1) = std::to_string(cfg_joypad);
                label_2713();
                goto label_2724_internal;
            }
        }
        if (submenu == 6)
        {
            if (cs == 0)
            {
                cfg_msgaddtime += p;
                if (cfg_msgaddtime > 1)
                {
                    cfg_msgaddtime = 1;
                }
                else if (cfg_msgaddtime < 0)
                {
                    cfg_msgaddtime = 0;
                }
                snd(20);
                valn(0) = u8"msg_addTime."s;
                valn(1) = std::to_string(cfg_msgaddtime);
                label_2713();
                goto label_2724_internal;
            }
            if (cs == 1)
            {
                cfg_msgtrans += p;
                if (cfg_msgtrans > 5)
                {
                    cfg_msgtrans = 5;
                }
                else if (cfg_msgtrans < 0)
                {
                    cfg_msgtrans = 0;
                }
                snd(20);
                valn(0) = u8"msg_trans."s;
                valn(1) = std::to_string(cfg_msgtrans);
                label_2713();
                goto label_2724_internal;
            }
        }
        if (submenu == 7)
        {
            if (cs == 0)
            {
                cfg_language += p;
                if (cfg_language > 1)
                {
                    cfg_language = 1;
                }
                else if (cfg_language < 0)
                {
                    cfg_language = 0;
                }
                snd(20);
                valn(0) = u8"language."s;
                valn(1) = std::to_string(cfg_language);
                label_2713();
                goto label_2724_internal;
            }
        }
    }
    if (key == key_cancel)
    {
        if (submenu != 0)
        {
            submenu = 0;
            set_option();
            return;
        }
        label_2716();
        if (mode == 0)
        {
            if (cfg_net)
            {
                label_1398();
            }
            label_1419();
            label_2743(false);
        }
        else
        {
            label_2115();
            return;
        }
    }
    goto label_2725_internal;
}



} // namespace elona
