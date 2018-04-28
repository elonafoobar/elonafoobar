#include "config.hpp"
#include "elona.hpp"
#include "macro.hpp"
#include "variables.hpp"

using namespace elona;


namespace
{


class config_menu_item_base
{
public:
    std::string name;

    config_menu_item_base(const std::string& name)
        : name(name)
    {
    }

    virtual ~config_menu_item_base() noexcept = default;
};


class config_menu_item_yesno : public config_menu_item_base
{
public:
    int& variable;
    std::string yes;
    std::string no;

    config_menu_item_yesno(
        const std::string& name,
        int& variable,
        const std::string& yes,
        const std::string& no)
        : config_menu_item_base(name)
        , variable(variable)
        , yes(yes)
        , no(no)
    {
    }

    virtual ~config_menu_item_yesno() noexcept = default;
};


class config_menu_item_info : public config_menu_item_base
{
public:
    std::string info;

    config_menu_item_info(const std::string& name, const std::string& info)
        : config_menu_item_base(name)
        , info(info)
    {
    }

    virtual ~config_menu_item_info() noexcept = default;
};


class config_menu_item_integer : public config_menu_item_base
{
public:
    int& variable;
    std::string text;

    config_menu_item_integer(
        const std::string& name,
        int& variable,
        const std::string& text)
        : config_menu_item_base(name)
        , variable(variable)
        , text(text)
    {
    }


    std::string get_text()
    {
        auto ret{text};
        ret.replace(
            ret.find(marker), std::strlen(marker), std::to_string(variable));
        return ret;
    }

    virtual ~config_menu_item_integer() noexcept = default;


private:
    static constexpr const char* marker = u8"{}";
};


class config_menu_item_choice : public config_menu_item_base
{
public:
    int& variable;
    std::vector<std::string> texts;

    config_menu_item_choice(
        const std::string& name,
        int& variable,
        const std::vector<std::string>& texts)
        : config_menu_item_base(name)
        , variable(variable)
        , texts(texts)
    {
    }


    std::string get_text()
    {
        return texts[variable];
    }

    virtual ~config_menu_item_choice() noexcept = default;
};


class config_menu
{
public:
    std::string title;
    std::vector<std::unique_ptr<config_menu_item_base>> items;
    int width;
    int height;

    config_menu(const std::string& title, int width, int height)
        : title(title)
        , width(width)
        , height(height)
    {
    }
};



std::vector<config_menu> create_config_menu()
{
    std::vector<config_menu> ret;

#define ELONA_CONFIG_ITEM(name) \
    ret.back().items.emplace_back(std::make_unique<config_menu_item_base>(name))

#define ELONA_CONFIG_ITEM_YESNO(name, var, yes, no) \
    ret.back().items.emplace_back( \
        std::make_unique<config_menu_item_yesno>(name, var, yes, no))

#define ELONA_CONFIG_ITEM_INFO(name, info) \
    ret.back().items.emplace_back( \
        std::make_unique<config_menu_item_info>(name, info))

#define ELONA_CONFIG_ITEM_INTEGER(name, var, text) \
    ret.back().items.emplace_back( \
        std::make_unique<config_menu_item_integer>(name, var, text))

#define ELONA_CONFIG_ITEM_CHOICE(name, var, ...) \
    ret.back().items.emplace_back(std::make_unique<config_menu_item_choice>( \
        name, var, std::vector<std::string>{__VA_ARGS__}))

    ret.emplace_back(lang(u8"オプション", u8"Option"), 370, 285);
    ELONA_CONFIG_ITEM(lang(u8"ゲームの設定", u8"Game Setting"));
    ELONA_CONFIG_ITEM(lang(u8"画面と音の設定", u8"Screen & Sound"));
    ELONA_CONFIG_ITEM(lang(u8"ネット機能の設定", u8"Network Setting"));
    ELONA_CONFIG_ITEM(lang(u8"詳細な設定", u8"Detailed Setting"));
    ELONA_CONFIG_ITEM(lang(u8"ゲームパッド", u8"Game Pad"));
    ELONA_CONFIG_ITEM(lang(u8"メッセージとログ", u8"Message & Log"));
    ELONA_CONFIG_ITEM(lang(u8"言語(Language)", u8"Language"));
    ELONA_CONFIG_ITEM(lang(u8"拡張設定(Foobar)", u8"Ex setting(Foobar)"));

    ret.emplace_back(lang(u8"ゲームの設定", u8"Game Setting"), 440, 340);
    ELONA_CONFIG_ITEM_YESNO(
        lang(u8"ノルンの冒険ガイド", u8"Extra Help"),
        cfg_extrahelp,
        lang(u8"あり", u8"Show"),
        lang(u8"なし", u8"Don't show"));
    ELONA_CONFIG_ITEM_YESNO(
        lang(u8"非好戦的NPCを無視", u8"Neutral Npcs"),
        cfg_ignoredislike,
        lang(u8"する", u8"Ignore"),
        lang(u8"しない", u8"Attack"));
    ELONA_CONFIG_ITEM_CHOICE(
        lang(u8"zキーの割当て", u8"Assign z key"),
        cfg_zkey,
        lang(u8"ｸｨｯｸﾒﾆｭｰ", u8"Quick menu"),
        lang(u8"道具を振る", u8"Zap"),
        lang(u8"割当なし", u8"Don't assign"), );
    ELONA_CONFIG_ITEM_CHOICE(
        lang(u8"xキーの割当て", u8"Assign x key"),
        cfg_xkey,
        lang(u8"ｸｲｯｸｲﾝﾍﾞﾝﾄﾘ", u8"Quick Inv"),
        lang(u8"道具を調べる", u8"Identify"),
        lang(u8"割当なし", u8"Don't assign"), );
    ELONA_CONFIG_ITEM(lang(u8"走り始める歩数", u8"Start Running After"));
    ELONA_CONFIG_ITEM_INTEGER(
        lang(u8"歩きの速さ", u8"Walk Speed"), cfg_walkwait, u8"{} wait");
    ELONA_CONFIG_ITEM_INTEGER(
        lang(u8"攻撃の間隔", u8"Attack Interval"), cfg_attackwait, u8"{} wait");

    ret.emplace_back(lang(u8"画面と音の設定", u8"Screen & Sound"), 440, 370);
    ELONA_CONFIG_ITEM(lang(u8"サウンドの再生*", u8"Sound*"));
    ELONA_CONFIG_ITEM(lang(u8"midiの再生*", u8"Music*"));
    ELONA_CONFIG_ITEM(lang(u8"画面モード*", u8"Screen Mode*"));
    ELONA_CONFIG_ITEM(lang(u8"画面の大きさ*", u8"Screen Resolution*"));
    ELONA_CONFIG_ITEM_YESNO(
        lang(u8"スクロール", u8"Smooth Scroll"),
        cfg_scroll,
        lang(u8"する", u8"Yes"),
        lang(u8"しない", u8"No"));
    ELONA_CONFIG_ITEM_YESNO(
        lang(u8"主人公中心に描写", u8"Always Center"),
        cfg_alwayscenter,
        lang(u8"する", u8"Yes"),
        lang(u8"しない", u8"No"));
    ELONA_CONFIG_ITEM_YESNO(
        lang(u8"心臓の音", u8"Heartbeat Sound"),
        cfg_heart,
        lang(u8"再生する", u8"Play"),
        lang(u8"再生しない", u8"Don't play"));
    ELONA_CONFIG_ITEM_YESNO(
        lang(u8"攻撃時アニメ", u8"Attack Animation"),
        cfg_attackanime,
        lang(u8"アニメあり", u8"Yes"),
        lang(u8"アニメなし", u8"No"));
    ELONA_CONFIG_ITEM_YESNO(
        lang(u8"天候エフェクト", u8"Weather Effect"),
        cfg_env,
        lang(u8"アニメあり", u8"Always"),
        lang(u8"アニメなし", u8"No animation"));
    ELONA_CONFIG_ITEM_CHOICE(
        lang(u8"光源の描写", u8"Lighting"),
        cfg_shadow,
        lang(u8"高画質", u8"High"),
        lang(u8"低画質", u8"Low"), );
    ELONA_CONFIG_ITEM_YESNO(
        lang(u8"アイテムの影描写", u8"object Shadow"),
        cfg_objectshadow,
        lang(u8"あり（低速）", u8"Yes(Fast)"),
        lang(u8"なし（高速）", u8"No(Slow)"));

    ret.emplace_back(lang(u8"ネット機能の設定", u8"Network Setting"), 440, 300);
    ELONA_CONFIG_ITEM_YESNO(
        lang(u8"ネットの使用", u8"Use Network"),
        cfg_net,
        lang(u8"する", u8"Yes"),
        lang(u8"しない", u8"No"));
    ELONA_CONFIG_ITEM_YESNO(
        lang(u8"定期的に接続", u8"Constantly Connect"),
        cfg_netwish,
        lang(u8"する", u8"Yes"),
        lang(u8"しない", u8"No"));
    ELONA_CONFIG_ITEM_YESNO(
        lang(u8"チャットをフィルタ", u8"Filter Chat"),
        cfg_netchat,
        lang(u8"する", u8"Yes"),
        lang(u8"しない", u8"No"));

    ret.emplace_back(lang(u8"詳細な設定", u8"Detailed Setting"), 440, 300);
    ELONA_CONFIG_ITEM_INTEGER(
        lang(u8"走りの速さ", u8"Run Speed"), cfg_runwait, u8"{} wait");
    ELONA_CONFIG_ITEM_YESNO(
        lang(u8"numlockを自動制御", u8"Auto Numlock"),
        cfg_autonumlock,
        lang(u8"する", u8"Yes"),
        lang(u8"しない", u8"No"));
    ELONA_CONFIG_ITEM_INFO(
        lang(u8"タイトルの水の波紋", u8"Title Water Effect"),
        lang(u8"オフ(未実装)", u8"No(unsupported)"));
    ELONA_CONFIG_ITEM_INTEGER(
        lang(u8"画面の更新頻度", u8"Screen Refresh"), cfg_scrsync, u8"{} wait");
    ELONA_CONFIG_ITEM_YESNO(
        lang(u8"走り時スクロール", u8"Scroll When Run"),
        cfg_runscroll,
        lang(u8"する", u8"Yes"),
        lang(u8"しない", u8"No"));
    ELONA_CONFIG_ITEM_CHOICE(
        lang(u8"オートターンの挙動", u8"Auto Turn Speed"),
        cfg_autoturn,
        lang(u8"普通", u8"Normal"),
        lang(u8"速め", u8"High"),
        lang(u8"省略", u8"Highest"));
    ELONA_CONFIG_ITEM_YESNO(
        lang(u8"イベントの短縮", u8"Skip Random Events"),
        cfg_skiprandevents,
        lang(u8"する", u8"Yes"),
        lang(u8"しない", u8"No"));

    ret.emplace_back(lang(u8"ゲームパッド", u8"Game Pad"), 440, 430);
    ELONA_CONFIG_ITEM(lang(u8"ゲームパッド", u8"Game Pad"));
    ELONA_CONFIG_ITEM(lang(u8"決定キー", u8"Enter/Ok"));
    ELONA_CONFIG_ITEM(lang(u8"キャンセルキー", u8"Cancel"));
    ELONA_CONFIG_ITEM(lang(u8"所持品", u8"Inventory"));
    ELONA_CONFIG_ITEM(lang(u8"行動", u8"Action"));
    ELONA_CONFIG_ITEM(lang(u8"斜め移動(L)", u8"diagonal Move/(L)"));
    ELONA_CONFIG_ITEM(lang(u8"拾う(R)", u8"Pick/(R)"));
    ELONA_CONFIG_ITEM(lang(u8"射撃(R)", u8"Shoot/(R)"));
    ELONA_CONFIG_ITEM(lang(u8"目標(L)", u8"Target/(L)"));
    ELONA_CONFIG_ITEM(lang(u8"ポーズメニュー", u8"Pause/Menu"));
    ELONA_CONFIG_ITEM(lang(u8"ヘルプ", u8"Help"));
    ELONA_CONFIG_ITEM(lang(u8"キャラ情報", u8"Chara-sheet"));
    ELONA_CONFIG_ITEM(lang(u8"装填", u8"Reload"));

    ret.emplace_back(lang(u8"メッセージとログ", u8"Message&Log"), 440, 300);
    ELONA_CONFIG_ITEM_YESNO(
        lang(u8"ﾒｯｾｰｼﾞに分表示追加", u8"Add time info"),
        cfg_msgaddtime,
        lang(u8"する", u8"Yes"),
        lang(u8"しない", u8"No"));
    ELONA_CONFIG_ITEM(lang(u8"過去のﾒｯｾｰｼﾞの透過", u8"Transparency"));

    ret.emplace_back(lang(u8"言語(Language)", u8"Language"), 440, 300);
    ELONA_CONFIG_ITEM_CHOICE(
        lang(u8"言語*", u8"Language*"),
        cfg_language,
        u8"Japanese",
        u8"English");

    ret.emplace_back(
        lang(u8"拡張設定(Foobar)", u8"Ex setting(Foobar)"), 440, 300);
    ELONA_CONFIG_ITEM_CHOICE(
        lang(u8"ペットのHPバー", u8"Pets' HP bar"),
        cfg_hp_bar,
        lang(u8"表示しない", u8"Don't show"),
        lang(u8"左側に表示", u8"Show left side"),
        lang(u8"右側に表示", u8"Show right side"));
    ELONA_CONFIG_ITEM_YESNO(
        lang(u8"紐のアイコン表示", u8"Leash icon"),
        cfg_leash_icon,
        lang(u8"する", u8"Show"),
        lang(u8"しない", u8"Don't show"));

#undef ELONA_CONFIG_ITEM
#undef ELONA_CONFIG_ITEM_YESNO
#undef ELONA_CONFIG_ITEM_INFO
#undef ELONA_CONFIG_ITEM_INTEGER
#undef ELONA_CONFIG_ITEM_CHOICE

    return ret;
}



} // namespace



namespace elona
{


void pc_turn(bool = true);


int submenu = 0;


void set_option()
{
    int cfg_sound2 = cfg_sound;
    int cfg_music2 = cfg_music;
    int cfg_fullscreen2 = cfg_fullscreen;
    int windoww2 = windoww;
    int windowh2 = windowh;

    const auto config_menu_definitions = create_config_menu();

    listmax = 0;
    page = 0;
    pagesize = 18;
    cs = 0;
    cc = 0;
    cs_bk = -1;
    page_bk = 0;
    cs_bk2 = 0;

    gsel(mode == 10 ? 2 : 4);
    for (int i = 0; i < 8; ++i)
    {
        pos(i % 4 * 180, i / 4 * 300);
        picload(filesystem::path(u8"./graphic/g"s + (i + 1) + u8".bmp"), 1);
    }
    gsel(0);

    if (mode == 0)
    {
        screenupdate = -1;
        update_screen();
    }
    if (mode == 10)
    {
        gsel(4);
        gmode(0);
        pos(0, 0);
        picload(filesystem::path(u8"./graphic/title.bmp"), 1);
        gzoom(4, 0, 0, 800, 600, windoww, windowh);
        gsel(0);
        gmode(0);
        pos(0, 0);
        gcopy(4, 0, 0, windoww, windowh);
        gmode(2);
    }

    const auto& menu_def = config_menu_definitions[submenu];
    const auto menu_title = menu_def.title;
    const auto width = menu_def.width;
    const auto height = menu_def.height;

    for (const auto& menu_item : menu_def.items)
    {
        list(0, listmax) = listmax;
        listn(0, listmax) = menu_item->name;
        ++listmax;
    }

    windowshadow = 1;

    bool reset_page = true;
    while (1)
    {
        if (reset_page)
        {
            if (cfg_zkey == 0)
            {
                key_quick = u8"z"s;
                key_zap = u8"Z"s;
            }
            else
            {
                key_zap = u8"z"s;
                key_quick = u8"Z"s;
            }

            if (cfg_xkey == 0)
            {
                key_quickinv = u8"x"s;
                key_inventory = u8"X"s;
            }
            else
            {
                key_inventory = u8"x"s;
                key_quickinv = u8"X"s;
            }

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
            reset_page = false;
        }
        s(0) = menu_title;
        s(1) = strhint3;
        pagesize = 0;
        if (mode == 1)
        {
            display_window(
                (windoww - width) / 2 + inf_screenx,
                winposy(height, 1),
                width,
                height);
        }
        else
        {
            display_window(
                (windoww - width) / 2 + inf_screenx,
                winposy(height) - 12,
                width,
                height);
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
        for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
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
            for (int cnt = 1; cnt < 20; ++cnt)
            {
                list(1, cnt) = p(cnt);
            }
        }
        font(14 - en * 2);
        for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
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
            cs_list(cs == cnt, s, wx + 56 + x, wy + 66 + cnt * 19 - 1, 0);
            if ((submenu != 5 || cnt <= 0) && submenu != 0)
            {
                pos(wx + 220, wy + 66 + cnt * 19 - 5);
                gcopy(3, 312, 336, 24, 24);
                pos(wx + 358, wy + 66 + cnt * 19 - 5);
                gcopy(3, 336, 336, 24, 24);
            }
            pos(wx + 250, wy + 66 + cnt * 19);
            if (auto ptr = dynamic_cast<config_menu_item_yesno*>(
                    config_menu_definitions[submenu].items[cnt].get()))
            {
                mes(ptr->variable ? ptr->yes : ptr->no);
            }
            else if (
                auto ptr = dynamic_cast<config_menu_item_info*>(
                    config_menu_definitions[submenu].items[cnt].get()))
            {
                mes(ptr->info);
            }
            else if (
                auto ptr = dynamic_cast<config_menu_item_integer*>(
                    config_menu_definitions[submenu].items[cnt].get()))
            {
                mes(ptr->get_text());
            }
            else if (
                auto ptr = dynamic_cast<config_menu_item_choice*>(
                    config_menu_definitions[submenu].items[cnt].get()))
            {
                mes(ptr->get_text());
            }
            else if (submenu == 1)
            {
                if (cnt == 4)
                {
                    if (cfg_startrun >= 20)
                    {
                        mes(lang(u8"走らない"s, u8"Don't run"s));
                    }
                    else
                    {
                        mes(lang(
                            ""s + (cfg_startrun + 1) + u8"歩目から"s,
                            u8"After "s + (cfg_startrun + 1) + u8" steps"s));
                    }
                }
            }
            else if (submenu == 2)
            {
                if (cnt == 0)
                {
                    s(0) = lang(u8"なし"s, u8"None"s);
                    s(1) = lang(u8"direct sound"s, u8"Direct sound"s);
                    s(2) = lang(u8"MCI"s, u8"MCI"s);
                    mes(s(cfg_sound2));
                }
                if (cnt == 1)
                {
                    s(0) = lang(u8"なし"s, u8"None"s);
                    s(1) = lang(u8"direct music"s, u8"Direct music"s);
                    s(2) = lang(u8"MCI"s, u8"MCI"s);
                    mes(s(cfg_music2));
                }
                if (cnt == 2)
                {
                    s(0) = lang(u8"ウィンドウ"s, u8"Window mode"s);
                    s(1) = lang(u8"フルスクリーン"s, u8"Full screen"s);
                    mes(s(cfg_fullscreen2));
                }
                if (cnt == 3)
                {
                    mes(""s + windoww2 + u8" * "s + windowh2);
                }
            }
            else if (submenu == 5)
            {
                if (cnt == 0)
                {
                    s(0) = lang(u8"使用しない"s, u8"Don't use"s);
                    s(1) = lang(u8"使用する"s, u8"Use"s);
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
            else if (submenu == 6)
            {
                if (cnt == 1)
                {
                    mes(""s + cfg_msgtrans * 10 + u8" %"s);
                }
            }
        }
        if (submenu != 0)
        {
            if (submenu != 5)
            {
                pos(wx + 40, wy + wh - 70);
                font(12 + sizefix - en * 2);
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
            font(12 + sizefix - en * 2);
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
        redraw();
        await(cfg_wait1);
        key_check();
        cursor_check();
        ELONA_GET_SELECTED_ITEM(p, cs = i);
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
                int j0 = 0;
                DIGETJOYSTATE(j0, 0);
                f = 0;
                for (int cnt = 0; cnt < 12; ++cnt)
                {
                    if (HMMBITCHECK(j0, 4 + cnt))
                    {
                        p = cnt;
                        for (int cnt = 0; cnt < 12; ++cnt)
                        {
                            jkey(cnt) = "";
                        }
                        list(1, cs) = p;
                        for (int cnt = 1; cnt < 20; ++cnt)
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
                        set_config(u8"enter", key_enter, list(1, 1));
                        set_config(u8"cancel", key_cancel, list(1, 2));
                        set_config(u8"quickinv", key_quickinv, list(1, 3));
                        set_config(u8"quick", key_quick, list(1, 4));
                        set_config(u8"alter", key_alter, list(1, 5));
                        set_config(u8"get", key_get, list(1, 6));
                        set_config(u8"fire", key_fire, list(1, 7));
                        set_config(u8"target", key_target, list(1, 8));
                        set_config(u8"esc", key_esc, list(1, 9));
                        set_config(u8"help", key_help, list(1, 10));
                        set_config(u8"charainfo", key_charainfo, list(1, 11));
                        set_config(u8"ammo", key_ammo, list(1, 12));
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
                        for (int cnt = 1; cnt < 20; ++cnt)
                        {
                            list(1, cnt) = p(cnt);
                        }
                        f = 1;
                        break;
                    }
                }
                if (f)
                {
                    snd(20);
                    await(200);
                    reset_page = true;
                    continue;
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
                    set_config(u8"extraHelp", cfg_extrahelp);
                    reset_page = true;
                    continue;
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
                    set_config(u8"ignoreDislike", cfg_ignoredislike);
                    reset_page = true;
                    continue;
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
                    set_config(u8"zkey", cfg_zkey);
                    reset_page = true;
                    continue;
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
                    set_config(u8"xkey", cfg_xkey);
                    reset_page = true;
                    continue;
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
                    set_config(u8"startRun", cfg_startrun);
                    reset_page = true;
                    continue;
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
                    set_config(u8"walkWait", cfg_walkwait);
                    reset_page = true;
                    continue;
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
                    set_config(u8"attackWait", cfg_attackwait);
                    reset_page = true;
                    continue;
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
                    set_config(u8"sound", cfg_sound2);
                    reset_page = true;
                    continue;
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
                    set_config(u8"music", cfg_music2);
                    reset_page = true;
                    continue;
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
                    set_config(u8"fullscreen", cfg_fullscreen2);
                    reset_page = true;
                    continue;
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
                    set_config(u8"scroll", cfg_scroll);
                    reset_page = true;
                    continue;
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
                    set_config(u8"alwaysCenter", cfg_alwayscenter);
                    reset_page = true;
                    continue;
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
                    set_config(u8"heartbeat", cfg_heart);
                    reset_page = true;
                    continue;
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
                    set_config(u8"attackAnime", cfg_attackanime);
                    reset_page = true;
                    continue;
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
                    set_config(u8"envEffect", cfg_env);
                    reset_page = true;
                    continue;
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
                    set_config(u8"shadow", cfg_shadow);
                    reset_page = true;
                    continue;
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
                    set_config(u8"objectShadow", cfg_objectshadow);
                    reset_page = true;
                    continue;
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
                    for (int cnt = 0; cnt < 5; ++cnt)
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
                    set_config(u8"windowW", windoww2);
                    set_config(u8"windowH", windowh2);
                    snd(20);
                    reset_page = true;
                    continue;
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
                    set_config(u8"net", cfg_net);
                    reset_page = true;
                    continue;
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
                    set_config(u8"netWish", cfg_netwish);
                    reset_page = true;
                    continue;
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
                    set_config(u8"netChat", cfg_netchat);
                    reset_page = true;
                    continue;
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
                    set_config(u8"runWait", cfg_runwait);
                    reset_page = true;
                    continue;
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
                    set_config(u8"autoNumlock", cfg_autonumlock);
                    reset_page = true;
                    continue;
                }
                if (cs == 2)
                {
                    snd(20);
                    set_config(u8"titleEffect", 0);
                    reset_page = true;
                    continue;
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
                    set_config(u8"scr_sync", cfg_scrsync);
                    reset_page = true;
                    continue;
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
                    set_config(u8"scroll_run", cfg_runscroll);
                    reset_page = true;
                    continue;
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
                    set_config(u8"autoTurnType", cfg_autoturn);
                    reset_page = true;
                    continue;
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
                    set_config(u8"skipRandEvents", cfg_skiprandevents);
                    reset_page = true;
                    continue;
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
                    set_config(u8"joypad", cfg_joypad);
                    reset_page = true;
                    continue;
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
                    set_config(u8"msg_addTime", cfg_msgaddtime);
                    reset_page = true;
                    continue;
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
                    set_config(u8"msg_trans", cfg_msgtrans);
                    reset_page = true;
                    continue;
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
                    set_config(u8"language", cfg_language);
                    reset_page = true;
                    continue;
                }
            }
            if (submenu == 8)
            {
                if (cs == 0)
                {
                    cfg_hp_bar += p;
                    if (cfg_hp_bar > 2)
                    {
                        cfg_hp_bar = 2;
                    }
                    else if (cfg_hp_bar < 0)
                    {
                        cfg_hp_bar = 0;
                    }
                    snd(20);
                    set_config(u8"hpBar", cfg_hp_bar);
                    reset_page = true;
                    continue;
                }
                if (cs == 1)
                {
                    cfg_leash_icon += p;
                    if (cfg_leash_icon > 1)
                    {
                        cfg_leash_icon = 1;
                    }
                    else if (cfg_leash_icon < 0)
                    {
                        cfg_leash_icon = 0;
                    }
                    snd(20);
                    set_config(u8"leashIcon", cfg_leash_icon);
                    reset_page = true;
                    continue;
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
            load_config();
            if (mode == 0)
            {
                if (cfg_net)
                {
                    initialize_server_info();
                }
            }
            return;
        }
    }
}



} // namespace elona
