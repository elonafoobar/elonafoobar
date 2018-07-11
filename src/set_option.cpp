#include "audio.hpp"
#include "config.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "macro.hpp"
#include "menu.hpp"
#include "network.hpp"
#include "ui.hpp"
#include "variables.hpp"

using namespace elona;


namespace
{


class config_menu_item_base
{
public:
    std::string name;
    std::string key;

    config_menu_item_base(const std::string& key, const std::string& locale_key)
        : key(key)
    {
        name = i18n::s.get(locale_key + ".name");
    }

    virtual ~config_menu_item_base() noexcept = default;

    virtual void change(int) {}
    virtual std::string get_message() { return ""; }
};


class config_menu_item_yesno : public config_menu_item_base
{
public:
    bool variable;
    std::string yes;
    std::string no;

    config_menu_item_yesno(
        const std::string& key,
        const std::string& locale_key,
        bool variable,
        const std::string& yes,
        const std::string& no)
        : config_menu_item_base(key, locale_key)
        , variable(variable)
        , yes(yes)
        , no(no)
    {
    }

    void change(int p)
    {
        if (!variable && p == 1)
        {
            variable = true;
        }
        else if (variable && p == -1)
        {
            variable = false;
        }

        config::instance().set(key, variable);
    }
    std::string get_message() { return variable ? yes : no; }

    virtual ~config_menu_item_yesno() noexcept = default;
};


class config_menu_item_info : public config_menu_item_base
{
public:
    std::string info;

    config_menu_item_info(const std::string& key,
                          const std::string& locale_key,
                          const std::string& info)
        : config_menu_item_base(key, locale_key)
        , info(info)
    {
    }

    virtual ~config_menu_item_info() noexcept = default;

    std::string get_message() { return info; }
};


class config_menu_item_integer : public config_menu_item_base
{
public:
    int variable;
    int min;
    int max;
    std::string text;

    config_menu_item_integer(
        const std::string& key,
        const std::string& locale_key,
        int variable,
        int min,
        int max,
        const std::string& text)
        : config_menu_item_base(key, locale_key)
        , variable(variable)
        , min(min)
        , max(max)
        , text(text)
    {
    }

    void change(int p)
    {
        variable = clamp(variable + p, min, max);
        config::instance().set(key, variable);
    }

    std::string get_message()
    {
        return i18n::fmt_hil(text, variable);
    }

    virtual ~config_menu_item_integer() noexcept = default;


private:
    static constexpr const char* marker = u8"{}";
};


class config_menu_item_choice : public config_menu_item_base
{
public:
    int variable;
    std::vector<std::string> texts;

    config_menu_item_choice(
        const std::string& key,
        const std::string& locale_key,
        int variable,
        const std::vector<std::string>& texts)
        : config_menu_item_base(key, locale_key)
        , variable(variable)
        , texts(texts)
    {
    }

    void change(int p)
    {
        variable += p;
        if (variable < 0)
        {
            variable = 0;
        }
        if (variable > static_cast<int>(texts.size() - 1))
        {
            variable = static_cast<int>(texts.size() - 1);
        }
        config::instance().set(key, variable);
    }

    std::string get_message()
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

    virtual void draw() const
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
};

class config_menu_joystick : public config_menu
{
public:
    void draw() const
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
};


#define ELONA_CONFIG_ITEM(def_key, locale_key)                                  \
    ret.back().items.emplace_back(std::make_unique<config_menu_item_base>(def_key, locale_key))

#define ELONA_CONFIG_ITEM_YESNO(def_key, locale_key, yes, no)   \
    ret.back().items.emplace_back( \
        std::make_unique<config_menu_item_yesno>(def_key, locale_key, conf.get<bool>(def_key), yes, no))

#define ELONA_CONFIG_ITEM_INFO(def_key, locale_key, info)       \
    ret.back().items.emplace_back( \
        std::make_unique<config_menu_item_info>(def_key, locale_key, info))

#define ELONA_CONFIG_ITEM_INTEGER(def_key, locale_key, formatter)       \
    ret.back().items.emplace_back( \
        std::make_unique<config_menu_item_integer>(def_key, locale_key, \
                                                   conf.get<int>(def_key), \
                                                   conf.get_def().get_min(def_key), \
                                                   conf.get_def().get_max(def_key), \
                                                   formatter))

#define ELONA_CONFIG_ITEM_CHOICE(def_key, locale_key, choices)                  \
    ret.back().items.emplace_back(std::make_unique<config_menu_item_choice>(def_key, locale_key, conf.get<int>(def_key), choices))


void visit_section(config&, const std::string&, std::vector<config_menu>&);
void visit_config_item(config&, const std::string&, std::vector<config_menu>&);


void visit_toplevel(config& conf, std::vector<config_menu>& ret)
{
    std::string def_key = "core.config";
    auto children = conf.get_def().get_children(def_key);
    int font_size = 14;
    int w = 370;
    int h = 165 + ((font_size + 1) * children.size());

    std::string menu_name_key = conf.get_def().get_locale_root() + ".name";
    ret.emplace_back(i18n::s.get(menu_name_key), w, h);

    // Add the names of top-level config menu sections if they are visible.
    for (const auto& child : conf.get_def().get_children(def_key))
    {
        // EX: "core.config.language"
        std::string section_key = def_key + "." + child;

        if (conf.get_def().is_visible(section_key))
        {
            // EX: "core.locale.config.menu.language"
            std::string locale_key = conf.get_def().get_locale_root() + "." + child;

            ELONA_CONFIG_ITEM(section_key, locale_key);
        }
    }

    // Add all sections and their config items.
    for (const auto& child : conf.get_def().get_children(def_key))
    {
        visit_section(conf, child, ret);
    }
}

void visit_section(config& conf, const std::string& current_key, std::vector<config_menu>& ret)
{
    // EX: "core.config.language"
    std::string def_key = "core.config." + current_key;

    // EX: "core.locale.config.menu.language"
    std::string locale_key = conf.get_def().get_locale_root() + "." + current_key;

    auto children = conf.get_def().get_children(def_key);
    int font_size = 14;
    int w = 440;
    int h = 165 + ((font_size + 1) * children.size());

    // Ensure the section exists in the config definition.
    if (!conf.get_def().exists(def_key))
    {
        throw std::runtime_error("No such config option \"" + current_key + "\".");
    }
    if (!conf.get_def().is_visible(def_key))
    {
        return;
    }

    // Add the translated name to the menu.
    std::cout << locale_key << std::endl;
    ret.emplace_back(i18n::s.get(locale_key + ".name"), w, h);

    // Visit child config items of this section.
    for (const auto& child : conf.get_def().get_children(def_key))
    {
        visit_config_item(conf, current_key + "." + child, ret);
    }
}

void visit_config_item(config& conf, const std::string& current_key, std::vector<config_menu>& ret)
{
    std::string def_key = "core.config." + current_key;
    std::string locale_key = conf.get_def().get_locale_root() + "." + current_key;

    if (!conf.get_def().exists(def_key))
    {
        throw std::runtime_error("No such config option \"" + current_key + "\".");
    }
    if (!conf.get_def().is_visible(def_key))
    {
        return;
    }

    if (conf.get_def().is<spec::bool_def>(def_key))
    {
        // Determine which text to use for true/false ("Yes"/"No", "Play"/"Don't Play", etc.)
        std::string yes_no = "core.locale.config.common_yes_no.default";
        if (auto text = i18n::s.get_optional(locale_key + ".yes_no"))
        {
            yes_no = *text;
        }
        ELONA_CONFIG_ITEM_YESNO(def_key, locale_key,
                                i18n::s.get(yes_no + ".yes"),
                                i18n::s.get(yes_no + ".no"));
    }
    else if (conf.get_def().is<spec::int_def>(def_key))
    {
        // TODO move to lua
        std::string formatter = "${_1}";
        if (auto text = i18n::s.get_optional(locale_key + ".formatter"))
        {
            formatter = *text;
        }
        ELONA_CONFIG_ITEM_INTEGER(def_key, locale_key, formatter);
    }
    else if (conf.get_def().is<spec::enum_def>(def_key))
    {
        // Add the translated names of all variants.
        const auto& variants = conf.get_def().get_variants(def_key);
        std::vector<std::string> choices;

        for (const auto& variant : variants)
        {
            choices.emplace_back(i18n::s.get(locale_key + ".variants." + variant));
        }

        ELONA_CONFIG_ITEM_CHOICE(def_key, locale_key, choices);
    }
    else if (conf.get_def().is<spec::string_def>(def_key))
    {
        // ignore
        // TODO: don't ignore, allow text input
    }
    else if (conf.get_def().is<spec::list_def>(def_key))
    {
        // ignore
    }
    else if (conf.get_def().is<spec::section_def>(def_key))
    {
        throw std::runtime_error("You cannot currently define nested sections.");
    }
    else
    {
        throw std::runtime_error("unknown config def item");
    }
}

std::vector<config_menu> create_config_menu()
{
    std::vector<config_menu> ret;
    auto& conf = config::instance();

    visit_toplevel(conf, ret);

    // ret.emplace_back(lang(u8"オプション", u8"Option"), 370, 285);
    // ELONA_CONFIG_ITEM(lang(u8"ゲームの設定", u8"Game Setting"));
    // ELONA_CONFIG_ITEM(lang(u8"画面と音の設定", u8"Screen & Sound"));
    // ELONA_CONFIG_ITEM(lang(u8"ネット機能の設定", u8"Network Setting"));
    // ELONA_CONFIG_ITEM(lang(u8"詳細な設定", u8"Detailed Setting"));
    // ELONA_CONFIG_ITEM(lang(u8"ゲームパッド", u8"Game Pad"));
    // ELONA_CONFIG_ITEM(lang(u8"メッセージとログ", u8"Message & Log"));
    // ELONA_CONFIG_ITEM(lang(u8"言語(Language)", u8"Language"));
    // ELONA_CONFIG_ITEM(lang(u8"拡張設定(Foobar)", u8"Ex setting(Foobar)"));

    // ret.emplace_back(lang(u8"ゲームの設定", u8"Game Setting"), 440, 380);
    // ELONA_CONFIG_ITEM_YESNO(
    //     lang(u8"ノルンの冒険ガイド", u8"Extra Help"),
    //     config::instance().extrahelp,
    //     lang(u8"あり", u8"Show"),
    //     lang(u8"なし", u8"Don't show"));
    // ELONA_CONFIG_ITEM_YESNO(
    //     lang(u8"Extra種族", u8"Extra Race"),
    //     config::instance().extrarace,
    //     lang(u8"あり", u8"On"),
    //     lang(u8"なし", u8"Off"));
    // ELONA_CONFIG_ITEM_YESNO(
    //     lang(u8"Extra職業", u8"Extra Class"),
    //     config::instance().extraclass,
    //     lang(u8"あり", u8"On"),
    //     lang(u8"なし", u8"Off"));
    // ELONA_CONFIG_ITEM_YESNO(
    //     lang(u8"非好戦的NPCを無視", u8"Neutral Npcs"),
    //     config::instance().ignoredislike,
    //     lang(u8"する", u8"Ignore"),
    //     lang(u8"しない", u8"Attack"));
    // ELONA_CONFIG_ITEM_CHOICE(
    //     lang(u8"zキーの割当て", u8"Assign z key"),
    //     config::instance().zkey,
    //     lang(u8"ｸｨｯｸﾒﾆｭｰ", u8"Quick menu"),
    //     lang(u8"道具を振る", u8"Zap"),
    //     lang(u8"割当なし", u8"Don't assign"), );
    // ELONA_CONFIG_ITEM_CHOICE(
    //     lang(u8"xキーの割当て", u8"Assign x key"),
    //     config::instance().xkey,
    //     lang(u8"ｸｲｯｸｲﾝﾍﾞﾝﾄﾘ", u8"Quick Inv"),
    //     lang(u8"道具を調べる", u8"Identify"),
    //     lang(u8"割当なし", u8"Don't assign"), );
    // ELONA_CONFIG_ITEM(lang(u8"走り始める歩数", u8"Start Running After"));
    // ELONA_CONFIG_ITEM_INTEGER(
    //     lang(u8"歩きの速さ", u8"Walk Speed"),
    //     config::instance().walkwait,
    //     u8"{} wait");
    // ELONA_CONFIG_ITEM_INTEGER(
    //     lang(u8"攻撃の間隔", u8"Attack Interval"),
    //     config::instance().attackwait,
    //     u8"{} wait");
    // ELONA_CONFIG_ITEM_INTEGER(
    //     lang(u8"アニメウェイト", u8"Animation Wait"),
    //     config::instance().animewait,
    //     u8"{} wait");
    // ELONA_CONFIG_ITEM_INTEGER(
    //     lang(u8"アラートウェイト", u8"Alert Wait"),
    //     config::instance().alert,
    //     u8"{} wait");
    // ELONA_CONFIG_ITEM_INTEGER(
    //     lang(u8"キーウェイト", u8"Key Wait"),
    //     config::instance().keywait,
    //     u8"{} wait");

    // ret.emplace_back(lang(u8"画面と音の設定", u8"Screen & Sound"), 440, 370);
    // ELONA_CONFIG_ITEM(lang(u8"サウンドの再生*", u8"Sound*"));
    // ELONA_CONFIG_ITEM(lang(u8"midiの再生*", u8"Music*"));
    // ELONA_CONFIG_ITEM(lang(u8"画面モード*", u8"Screen Mode*"));
    // ELONA_CONFIG_ITEM(lang(u8"画面の大きさ*", u8"Screen Resolution*"));
    // ELONA_CONFIG_ITEM_YESNO(
    //     lang(u8"スクロール", u8"Smooth Scroll"),
    //     config::instance().scroll,
    //     lang(u8"する", u8"Yes"),
    //     lang(u8"しない", u8"No"));
    // ELONA_CONFIG_ITEM_YESNO(
    //     lang(u8"主人公中心に描写", u8"Always Center"),
    //     config::instance().alwayscenter,
    //     lang(u8"する", u8"Yes"),
    //     lang(u8"しない", u8"No"));
    // ELONA_CONFIG_ITEM_YESNO(
    //     lang(u8"心臓の音", u8"Heartbeat Sound"),
    //     config::instance().heart,
    //     lang(u8"再生する", u8"Play"),
    //     lang(u8"再生しない", u8"Don't play"));
    // ELONA_CONFIG_ITEM_YESNO(
    //     lang(u8"攻撃時アニメ", u8"Attack Animation"),
    //     config::instance().attackanime,
    //     lang(u8"アニメあり", u8"Yes"),
    //     lang(u8"アニメなし", u8"No"));
    // ELONA_CONFIG_ITEM_YESNO(
    //     lang(u8"天候エフェクト", u8"Weather Effect"),
    //     config::instance().env,
    //     lang(u8"アニメあり", u8"Always"),
    //     lang(u8"アニメなし", u8"No animation"));
    // ELONA_CONFIG_ITEM_CHOICE(
    //     lang(u8"光源の描写", u8"Lighting"),
    //     config::instance().shadow,
    //     lang(u8"高画質", u8"High"),
    //     lang(u8"低画質", u8"Low"), );
    // ELONA_CONFIG_ITEM_YESNO(
    //     lang(u8"アイテムの影描写", u8"object Shadow"),
    //     config::instance().objectshadow,
    //     lang(u8"あり（低速）", u8"Yes(Fast)"),
    //     lang(u8"なし（高速）", u8"No(Slow)"));

    // ret.emplace_back(lang(u8"ネット機能の設定", u8"Network Setting"), 440, 300);
    // ELONA_CONFIG_ITEM_YESNO(
    //     lang(u8"ネットの使用", u8"Use Network"),
    //     config::instance().net,
    //     lang(u8"する", u8"Yes"),
    //     lang(u8"しない", u8"No"));
    // ELONA_CONFIG_ITEM_YESNO(
    //     lang(u8"定期的に接続", u8"Constantly Connect"),
    //     config::instance().netwish,
    //     lang(u8"する", u8"Yes"),
    //     lang(u8"しない", u8"No"));
    // ELONA_CONFIG_ITEM_YESNO(
    //     lang(u8"チャットをフィルタ", u8"Filter Chat"),
    //     config::instance().netchat,
    //     lang(u8"する", u8"Yes"),
    //     lang(u8"しない", u8"No"));

    // ret.emplace_back(lang(u8"詳細な設定", u8"Detailed Setting"), 440, 300);
    // ELONA_CONFIG_ITEM_INTEGER(
    //     lang(u8"走りの速さ", u8"Run Speed"),
    //     config::instance().runwait,
    //     u8"{} wait");
    // ELONA_CONFIG_ITEM_YESNO(
    //     lang(u8"numlockを自動制御", u8"Auto Numlock"),
    //     config::instance().autonumlock,
    //     lang(u8"する", u8"Yes"),
    //     lang(u8"しない", u8"No"));
    // ELONA_CONFIG_ITEM_INFO(
    //     lang(u8"タイトルの水の波紋", u8"Title Water Effect"),
    //     lang(u8"オフ(未実装)", u8"No(unsupported)"));
    // ELONA_CONFIG_ITEM_INTEGER(
    //     lang(u8"画面の更新頻度", u8"Screen Refresh"),
    //     config::instance().scrsync,
    //     u8"{} wait");
    // ELONA_CONFIG_ITEM_YESNO(
    //     lang(u8"走り時スクロール", u8"Scroll When Run"),
    //     config::instance().runscroll,
    //     lang(u8"する", u8"Yes"),
    //     lang(u8"しない", u8"No"));
    // ELONA_CONFIG_ITEM_CHOICE(
    //     lang(u8"オートターンの挙動", u8"Auto Turn Speed"),
    //     config::instance().autoturn,
    //     lang(u8"普通", u8"Normal"),
    //     lang(u8"速め", u8"High"),
    //     lang(u8"省略", u8"Highest"));
    // ELONA_CONFIG_ITEM_YESNO(
    //     lang(u8"イベントの短縮", u8"Skip Random Events"),
    //     config::instance().skiprandevents,
    //     lang(u8"する", u8"Yes"),
    //     lang(u8"しない", u8"No"));

    // ret.emplace_back(lang(u8"ゲームパッド", u8"Game Pad"), 440, 430);
    // ELONA_CONFIG_ITEM(lang(u8"ゲームパッド", u8"Game Pad"));
    // ELONA_CONFIG_ITEM(lang(u8"決定キー", u8"Enter/Ok"));
    // ELONA_CONFIG_ITEM(lang(u8"キャンセルキー", u8"Cancel"));
    // ELONA_CONFIG_ITEM(lang(u8"所持品", u8"Inventory"));
    // ELONA_CONFIG_ITEM(lang(u8"行動", u8"Action"));
    // ELONA_CONFIG_ITEM(lang(u8"斜め移動(L)", u8"diagonal Move/(L)"));
    // ELONA_CONFIG_ITEM(lang(u8"拾う(R)", u8"Pick/(R)"));
    // ELONA_CONFIG_ITEM(lang(u8"射撃(R)", u8"Shoot/(R)"));
    // ELONA_CONFIG_ITEM(lang(u8"目標(L)", u8"Target/(L)"));
    // ELONA_CONFIG_ITEM(lang(u8"ポーズメニュー", u8"Pause/Menu"));
    // ELONA_CONFIG_ITEM(lang(u8"ヘルプ", u8"Help"));
    // ELONA_CONFIG_ITEM(lang(u8"キャラ情報", u8"Chara-sheet"));
    // ELONA_CONFIG_ITEM(lang(u8"装填", u8"Reload"));

    // ret.emplace_back(lang(u8"メッセージとログ", u8"Message&Log"), 440, 300);
    // ELONA_CONFIG_ITEM_YESNO(
    //     lang(u8"ﾒｯｾｰｼﾞに分表示追加", u8"Add time info"),
    //     config::instance().msgaddtime,
    //     lang(u8"する", u8"Yes"),
    //     lang(u8"しない", u8"No"));
    // ELONA_CONFIG_ITEM(lang(u8"過去のﾒｯｾｰｼﾞの透過", u8"Transparency"));

    // ret.emplace_back(lang(u8"言語(Language)", u8"Language"), 440, 300);
    // ELONA_CONFIG_ITEM_CHOICE(
    //     lang(u8"言語*", u8"Language*"),
    //     config::instance().language,
    //     u8"Japanese",
    //     u8"English");

    // ret.emplace_back(
    //     lang(u8"拡張設定(Foobar)", u8"Ex setting(Foobar)"), 440, 300);
    // ELONA_CONFIG_ITEM_CHOICE(
    //     lang(u8"ペットのHPバー", u8"Pets' HP bar"),
    //     config::instance().hp_bar,
    //     lang(u8"表示しない", u8"Don't show"),
    //     lang(u8"左側に表示", u8"Show left side"),
    //     lang(u8"右側に表示", u8"Show right side"));
    // ELONA_CONFIG_ITEM_YESNO(
    //     lang(u8"紐のアイコン表示", u8"Leash icon"),
    //     config::instance().leash_icon,
    //     lang(u8"する", u8"Show"),
    //     lang(u8"しない", u8"Don't show"));
    // ELONA_CONFIG_ITEM_YESNO(
    //     lang(u8"Autopick", u8"Autopick"),
    //     config::instance().use_autopick,
    //     lang(u8"使う", u8"On"),
    //     lang(u8"使わない", u8"Off"));
    // ELONA_CONFIG_ITEM_YESNO(
    //     lang(u8"オートセーブ", u8"Autosave"),
    //     config::instance().autosave,
    //     lang(u8"有効", u8"On"),
    //     lang(u8"無効", u8"Off"));
    // ELONA_CONFIG_ITEM(lang(u8"入荷頻度", u8"Restock Interval"));
    // ELONA_CONFIG_ITEM_YESNO(
    //     lang(u8"ダメージポップアップ", u8"Damage popup"),
    //     config::instance().damage_popup,
    //     lang(u8"あり", u8"On"),
    //     lang(u8"なし", u8"Off"));

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

int submenu = 0;

void set_option()
{
    const auto display_modes =
        snail::application::instance().get_display_modes();
    std::string default_display_mode =
        snail::application::instance().get_default_display_mode();
    std::vector<std::string> display_mode_names;
    std::string cfg_display_mode = config::instance().display_mode;

    int display_mode_index = -1;
    int index = 0;
    int default_index = 0;

    for (const auto pair : display_modes)
    {
        display_mode_names.emplace_back(pair.first);
        if (pair.first == cfg_display_mode)
        {
            display_mode_index = index;
        }
        else if (pair.first == default_display_mode)
        {
            default_index = index;
        }
        index++;
    }
    if (display_mode_index == -1 || config::instance().display_mode == "")
    {
        cfg_display_mode = default_display_mode;
        display_mode_index = default_index;
    }

    const auto config_menu_definitions = create_config_menu();

set_option_begin:
    listmax = 0;
    page = 0;
    pagesize = 18;
    cs = 0;
    cc = 0;
    cs_bk = -1;
    page_bk = 0;
    cs_bk2 = 0;

    int bg_variant_buffer = mode == 10 ? 2 : 4;
    load_background_variants(bg_variant_buffer);
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
        picload(filesystem::dir::graphic() / u8"title.bmp", 1);
        gcopy(4, 0, 0, 800, 600, windoww, windowh);
        gsel(0);
        gmode(0);
        pos(0, 0);
        gcopy(4, 0, 0, windoww, windowh);
        gmode(2);
    }

    auto& menu_def = config_menu_definitions[submenu];
    auto menu_title = menu_def.title;
    auto width = menu_def.width;
    auto height = menu_def.height;

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
            if (config::instance().zkey == 0)
            {
                key_quick = u8"z"s;
                key_zap = u8"Z"s;
            }
            else
            {
                key_zap = u8"z"s;
                key_quick = u8"Z"s;
            }

            if (config::instance().xkey == 0)
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
        display_topic(i18n::s.get("core.locale.config.common.menu"), wx + 34, wy + 36);
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
        pos(wx + ww / 3, wy + wh / 2);
        gmode(4, 50);
        gcopy_c(p, cmbg / 4 % 4 * 180, cmbg / 4 / 4 % 2 * 300, 180, 300, x, y);
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
        // if (submenu == 5)
        // {
        //     p(0) = 0;
        //     p(1) = cnvjkey(key_enter);
        //     p(2) = cnvjkey(key_cancel);
        //     p(3) = cnvjkey(key_quickinv);
        //     p(4) = cnvjkey(key_quick);
        //     p(5) = cnvjkey(key_alter);
        //     p(6) = cnvjkey(key_get);
        //     p(7) = cnvjkey(key_fire);
        //     p(8) = cnvjkey(key_target);
        //     p(9) = cnvjkey(key_esc);
        //     p(10) = cnvjkey(key_help);
        //     p(11) = cnvjkey(key_charainfo);
        //     p(12) = cnvjkey(key_ammo);
        //     for (int cnt = 1; cnt < 20; ++cnt)
        //     {
        //         list(1, cnt) = p(cnt);
        //     }
        // }
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
            s = listn(0, p);
            if (submenu == 0)
            {
                x = 8;
            }
            else
            {
                x = 0;
            }
            // if (submenu == 3)
            // {
            //     if (config::instance().net == 0)
            //     {
            //         if (cnt >= 1)
            //         {
            //             continue;
            //         }
            //     }
            // }
            cs_list(cs == cnt, s, wx + 56 + x, wy + 66 + cnt * 19 - 1, 0);
            if ((submenu != 5 || cnt <= 0) && submenu != 0)
            {
                pos(wx + 220, wy + 66 + cnt * 19 - 5);
                gcopy(3, 312, 336, 24, 24);
                pos(wx + 358, wy + 66 + cnt * 19 - 5);
                gcopy(3, 336, 336, 24, 24);
            }
            pos(wx + 250, wy + 66 + cnt * 19);

            mes(config_menu_definitions[submenu].items[cnt].get()->get_message());

            // else if (submenu == 1)
            // {
            //     if (cnt == 6)
            //     {
            //         if (config::instance().startrun >= 20)
            //         {
            //             mes(lang(u8"走らない"s, u8"Don't run"s));
            //         }
            //         else
            //         {
            //             mes(lang(
            //                 ""s + (config::instance().startrun + 1)
            //                     + u8"歩目から"s,
            //                 u8"After "s + (config::instance().startrun + 1)
            //                     + u8" steps"s));
            //         }
            //     }
            // }
            // else if (submenu == 2)
            // {
            //     if (cnt == 0)
            //     {
            //         s(0) = lang(u8"なし"s, u8"Off"s);
            //         s(1) = lang(u8"あり"s, u8"On"s);
            //         mes(s(cfg_sound2));
            //     }
            //     if (cnt == 1)
            //     {
            //         s(0) = lang(u8"なし"s, u8"None"s);
            //         s(1) = lang(u8"direct music"s, u8"Direct music"s);
            //         s(2) = lang(u8"MCI"s, u8"MCI"s);
            //         mes(s(cfg_music2));
            //     }
            //     if (cnt == 2)
            //     {
            //         s(0) = lang(u8"ウィンドウ"s, u8"Window mode"s);
            //         s(1) = lang(u8"フルスクリーン"s, u8"Full screen"s);
            //         s(2) = lang(u8"フルスクリーン2"s, u8"Desktop fullscr"s);
            //         mes(s(cfg_fullscreen2));
            //     }
            //     if (cnt == 3)
            //     {
            //         mes(cfg_display_mode);
            //     }
            // }
            // else if (submenu == 5)
            // {
            //     if (cnt == 0)
            //     {
            //         s(0) = lang(u8"使用しない"s, u8"Don't use"s);
            //         s(1) = lang(u8"使用する"s, u8"Use"s);
            //         mes(s(config::instance().joypad));
            //     }
            //     else if (list(1, cnt) == -1)
            //     {
            //         mes(lang(u8"未設定"s, u8"Unassigned"s));
            //     }
            //     else
            //     {
            //         mes(lang(u8"ボタン"s, u8"Button"s) + list(1, cnt));
            //     }
            // }
            // else if (submenu == 6)
            // {
            //     if (cnt == 1)
            //     {
            //         mes(""s + config::instance().msgtrans * 10 + u8" %"s);
            //     }
            // }
            // else if (submenu == 8)
            // {
            //     if (cnt == 4)
            //     {
            //         const auto value = config::instance().restock_interval;
            //         if (value)
            //         {
            //             mes(std::to_string(value)
            //                 + lang(u8"日", u8" day" + _s2(value)));
            //         }
            //         else
            //         {
            //             mes(lang(u8"毎回更新", u8"Every time"));
            //         }
            //     }
            // }
        }

        config_menu_definitions[submenu].draw();
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
            if (submenu == 0)
            {
                submenu = p + 1;
                snd(20);
                goto set_option_begin;
            }
        }
        // if (submenu == 5)
        // {
        //     if (cs > 0)
        //     {
        //         int j0 = 0;
        //         DIGETJOYSTATE(j0, 0);
        //         f = 0;
        //         for (int cnt = 0; cnt < 12; ++cnt)
        //         {
        //             if (HMMBITCHECK(j0, 4 + cnt))
        //             {
        //                 p = cnt;
        //                 for (int cnt = 0; cnt < 12; ++cnt)
        //                 {
        //                     jkey(cnt) = "";
        //                 }
        //                 list(1, cs) = p;
        //                 for (int cnt = 1; cnt < 20; ++cnt)
        //                 {
        //                     if (cs == cnt)
        //                     {
        //                         continue;
        //                     }
        //                     --list(1, cnt);
        //                     if (list(1, cnt) == p || list(1, cnt) <= -1)
        //                     {
        //                         list(1, cnt) = 12;
        //                     }
        //                 }
        //                 set_config(u8"enter", key_enter, list(1, 1));
        //                 set_config(u8"cancel", key_cancel, list(1, 2));
        //                 set_config(u8"quickinv", key_quickinv, list(1, 3));
        //                 set_config(u8"quick", key_quick, list(1, 4));
        //                 set_config(u8"alter", key_alter, list(1, 5));
        //                 set_config(u8"get", key_get, list(1, 6));
        //                 set_config(u8"fire", key_fire, list(1, 7));
        //                 set_config(u8"target", key_target, list(1, 8));
        //                 set_config(u8"esc", key_esc, list(1, 9));
        //                 set_config(u8"help", key_help, list(1, 10));
        //                 set_config(u8"charainfo", key_charainfo, list(1, 11));
        //                 set_config(u8"ammo", key_ammo, list(1, 12));
        //                 p(0) = 0;
        //                 p(1) = cnvjkey(key_enter);
        //                 p(2) = cnvjkey(key_cancel);
        //                 p(3) = cnvjkey(key_quickinv);
        //                 p(4) = cnvjkey(key_quick);
        //                 p(5) = cnvjkey(key_alter);
        //                 p(6) = cnvjkey(key_get);
        //                 p(7) = cnvjkey(key_fire);
        //                 p(8) = cnvjkey(key_target);
        //                 p(9) = cnvjkey(key_esc);
        //                 p(10) = cnvjkey(key_help);
        //                 p(11) = cnvjkey(key_charainfo);
        //                 p(12) = cnvjkey(key_ammo);
        //                 for (int cnt = 1; cnt < 20; ++cnt)
        //                 {
        //                     list(1, cnt) = p(cnt);
        //                 }
        //                 f = 1;
        //                 break;
        //             }
        //         }
        //         if (f)
        //         {
        //             snd(20);
        //             await(200);
        //             reset_page = true;
        //             continue;
        //         }
        //     }
        // }
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

            config_menu_definitions[submenu].items[cs].get()->change(p);
            snd(20);
            reset_page = true;
            continue;
        }
        if (key == key_cancel)
        {
            if (submenu != 0)
            {
                // TODO nested menus
                submenu = 0;
                set_option();
                return;
            }
            config::instance().write();
            if (mode == 0)
            {
                if (config::instance().net)
                {
                    initialize_server_info();
                }
            }
            return;
        }
    }
}



} // namespace elona
