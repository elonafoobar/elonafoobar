locale {
    ui {
        yes = "ああ"
        no = "いや…"
        bye = "さようなら"
        more = "(続く)"

        save = " *保存* "
        playtime = "${_1}時間${_2}分${_3}秒"
        save_on_suspend = "アプリが中断された。セーブします。"

        date = "${_1}年${_2}月${_3}日"
        date_hour = "${_1}時"

        article = "${_1}"

        gold = " gold"
        platinum = " plat"
        unit_of_weight = "s"

        no_gold = "(所持金が足りない！)"
        invalid_target = "その方向には、操作できる対象はない。"

        assign_shortcut = "{${_1}}キーにショートカットを割り当てた。"

        curse_state {
            cursed = "呪われた"
            blessed = "祝福された"
            doomed = "堕落した"
        }

        menu {
            change = "メニュー切替"
            chara {
                chara = "情報"
                wear = "装備"
                feat = "特徴"
                material = "ﾏﾃﾘｱﾙ"
            }
            spell {
                spell = "魔法"
                skill = "技能"
            }
            log {
                log = "ログ"
                journal = "日誌"
                chat = "チャット"
            }
            town {
                chart = "チャート"
                economy = "街情報"
                politics = "法律"
            }
        }

        hint {
            cursor = "ｶｰｿﾙ [選択]  "
            page = " [ページ切替]  "
            close = "Shift,Esc [閉じる]  "
            back = "Shift,Esc [戻る]  "
            enter = "決定、"
            known_info = " [既知の情報]  "
            mode = " [情報切替]  "
            portrait = "p [ポートレイト変更]  "
            shortcut = "0〜9 [ショートカット]  "
            help = " [説明]  "
        }

        quick_menu {
            # Page 1
            help = "ヘルプ"
            log = "ログ"
            chara = "シート"
            journal = "日誌"

            # Page 2
            wear = "装備"
            rest = "休息"
            spell = "魔法"
            skill = "技能"
            fire = "射撃"
            dig = "掘る"

            # Page 3
            pray = "祈る"
            ammo = "装填"
            interact = "干渉"
            bash = "体当り"

            # Page selection
            info = "情報"
            action = "行動"
            etc = "特殊"
        }

        exhelp {
            title = "- ノルンの冒険ガイド -"
        }

        message {
            key_hint = "Up,Down [1行ｽｸﾛｰﾙ]   Left,Right [1ﾍﾟｰｼﾞｽｸﾛｰﾙ]   他のキーを押すと閉じる"
        }

        chat {
            key_hint = "何かキーを押すと閉じる"
        }

        scene {
            which = "どのシーンを再生する？"
            you_can_play = "アンロックされたシーンを再生できます。\nシーンNoは連続していません。"
            scene_no = "シーン No."
            has_been_played = "シーンの再生を終えた。"
        }

        spell {
            title = "魔法の詠唱"

            name = "魔法の名称"
            cost = "消費MP"
            stock = "ｽﾄｯｸ"
            lv_chance = "Lv/成功"
            effect = "効果"

            turn_counter = "ﾀｰﾝ"
            power = "ﾊﾟﾜｰ"
        }

        skill {
            title = "能力の発動"

            name = "能力の名称"
            cost = "コスト"
            detail = "能力の効果"
        }

        chara_sheet {
            title {
                default = "キャラクターシート"
                training = "能力訓練"
                learning = "能力の習得"
            }

            category {
                skill = "◆ スキルと特殊能力"
                weapon_proficiency = "◆ 武器の専門"
                resistance = "◆ 耐性と抵抗力"
            }

            train_which_skill = "どの能力を訓練する？"
            you_can_spend_bonus = "残り ${_1} のボーナスをスキルに分配できる"

            attributes = "能力(元の値)  - 潜在能力"
            combat_rolls = "各種修正"
            history = "冒険の軌跡"
            blessing_and_hex = "祝福と呪い"
            extra_info = "その他"

            damage {
                protect = "軽減"
                evade = "回避"

                hit = "命中"

                melee = "武器"
                unarmed = "格闘"
                dist = "射撃"
            }

            exp {
                level = "レベル"
                exp = "経験"
                next_level = "必要値"
                god = "信仰"
                guild = "所属"
            }

            personal {
                name = "名前"
                aka = "異名"
                race = "種族"
                sex = "性別"
                class = "職業"
                age = "年齢"
                height = "身長"
                weight = "体重"

                age_counter = "歳"
            }

            attribute {
                life = "生命力"
                mana = "マナ"
                sanity = "狂気度"
                speed = "速度"
                fame = "名声"
                karma = "カルマ"
                melee = "打撃修正"
                shoot = "射撃修正"
            }

            time {
                turns = "ターン"
                days = "経過日"
                kills = "殺害数"
                time = "総時間"

                turn_counter = "${_1}ターン"
                days_counter = "${_1}日"
            }

            weight {
                cargo_weight = "荷車重量"
                cargo_limit = "荷車限界"
                equip_weight = "装備重量"
                deepest_level = "最深到達"

                level_counter = "${_1}階相当"
            }

            buff {
                duration = "(${_1})ﾀｰﾝの間、"
                is_not_currently = "今は持続効果を受けていない"
                hint = "説明"
            }

            skill {
                name = "能力の名称"
                level = "Lv"
                potential = "潜在"
                detail = "効果"
                resist = "${_1}耐性"
            }

            hint {
                # TODO trim whitespace and brackets
                hint = "ｶｰｿﾙ [祝福と呪いの情報]  "
                spend_bonus = "決定 [ボーナスの分配]  "
                reroll = "決定ｷｰ [リロール]  "
                confirm = "Shift,Esc [最終確認]"
                train_skill = "決定 [スキルを訓練]  "
                learn_skill = "決定 [スキルを習得]  "
                blessing_info = "ｶｰｿﾙ [祝福と呪いの情報] "
                track_skill = "スキルトラック"
            }
        }

        equip {
            title = "装備品"

            category = "部位"
            name = "装備品名称"
            weight = "重さ"

            resist {
                _0 = "火"
                _1 = "冷"
                _2 = "雷"
                _3 = "闇"
                _4 = "幻"
                _5 = "毒"
                _6 = "獄"
                _7 = "音"
                _8 = "神"
                _9 = "沌"
                _10 = "魔"
            }

            maintenance {
                _0 = "筋"
                _1 = "耐"
                _2 = "器"
                _3 = "感"
                _4 = "習"
                _5 = "意"
                _6 = "魔"
                _7 = "魅"
                _8 = "速"
                _9 = "運"
            }

            ailment {
                _0 = "盲"
                _1 = "麻"
                _2 = "混"
                _3 = "恐"
                _4 = "睡"
                _5 = "毒"
            }

            fireproof = "熱"
            acidproof = "酸"

            equip_weight = "装備重量"
            hit_bonus = "命中修正"
            damage_bonus = "ダメージ修正"

            main_hand = "利手"

            cannot_be_taken_off = "${itemname(_1)}は外せない。"
            you_unequip = "${itemname(_1)}を外した。"
        }

        material {
            name = "所持マテリアル"
            detail = "説明"
        }

        appearance {
            hint = "左右キー [変更]  ｷｬﾝｾﾙ [閉じる]"

            # Whitespace is significant.
            # Text is limited to 8~9 halfwidth characters.
            basic {
                title = "肖像の変更"
                category = "項目"

                done       = "決定    "
                portrait   = "肖像　　"
                hair       = "髪　　　"
                sub_hair   = "副髪　　"
                hair_color = "髪の色　"
                body       = "体　　　"
                cloth      = "服　　　"
                pants      = "ﾊﾟﾝﾂ　　"
                set_detail = "詳細設定"

                custom     = "ｶｽﾀﾑｷｬﾗ "
                riding     = "乗馬時　"
            }
            detail {
                body_color  = "体の色　"
                cloth_color = "服の色　"
                pants_color = "ﾊﾟﾝﾂの色"
                etc_1       = "ｱｸｾｻﾘ1　"
                etc_2       = "ｱｸｾｻﾘ2　"
                etc_3       = "ｱｸｾｻﾘ3　"
                eyes        = "目　　　"
                set_basic   = "基本設定"
            }
            equipment {
                title = "装備表示の変更"
                part = "項目"

                done   = "決定    "
                chest  = "胸部鎧　"
                leg    = "脚部鎧　"
                belt   = "ベルト　"
                glove  = "ｸﾞﾛｰﾌﾞ　"
                mantle = "マント　"
            }
        }

        journal {
            rank {
                fame = "名声"
                pay = "給料: 約 ${_1} gold  "
                deadline = "ノルマ: ${_1}日以内"

                arena = "EXバトル: 勝利 ${_1}回 最高Lv${_2}"
            }

            income {
                # TODO remove tags
                salary {
                    title = "◆ 給料(毎月1日と15日に支給)"
                    sum = "@BL　合計　　 : 約 ${_1} gold"
                }
                bills {
                    title = "◆ 請求書内訳(毎月1日に発行)"
                    labor = "@RE　人件費  : 約 ${_1} gold"
                    maintenance = "@RE　運営費  : 約 ${_1} gold"
                    tax = "@RE　税金    : 約 ${_1} gold"
                    sum = "@RE　合計　  : 約 ${_1} gold"
                    unpaid = "現在未払いの請求書は${_1}枚"
                }
            }
        }

        board {
            title = "掲載されている依頼"

            difficulty = "★"
            difficulty_counter = "★×${_1}"

            no_new_notices = "新しい依頼は掲示されていないようだ。"
            do_you_meet = "依頼主に会う？"
        }

        npc_list {
            title = "NPC一覧"

            wage = "給料"
            init_cost = "雇用費(給料)"
            name = "NPCの名前"
            info = "情報"

            age_counter = " ${_1}歳"
            gold_counter = "${_1} gold"
        }

        reserve {
            title = "予約リスト"

            name = "アイテムの名前"
            status = "予約状況"

            not_reserved = "入荷なし"
            reserved = "入荷予定"

            unavailable = "「その本は入手できないね」"
        }

        adventurers {
            title = "冒険者ランク"

            name_and_rank = "冒険者の名前とランク"
            fame_lv = "名声(Lv)"
            location = "現在地"

            unknown = "不明"
            hospital = "病院"

            rank_counter = "位"
        }

        alias {
            title = "異名の選択"

            list = "異名の候補"
            reroll = "別の名前を考える"
        }

        town_chart {
            title = "ポストチャート"

            chart = "${_1}のチャート"

            no_economy = "この場所には経済活動がない。"
            empty = "不在"
        }

        economy {
            information = "街の概要"
            finance = "街の財政"

            population = "人口"
            basic_tax = "基本税"
            excise_tax = "消費税"

            population_detail = "人口推移の詳細"
            finance_detail = "収支の詳細"
        }

        politics {
            law = "法律"
            global = "国法"
            law_of = "${_1}の法"

            name = "この国の首都は${_1}だ。"
            taxes = "この街の消費税は${_1}%だ。"
            well_pollution = "この街の井戸水の汚染は深刻だ(死者${_1}人）。"
            lawless = "この街では殺人が許される。"
        }

        ally_list {
            name = "仲間の情報"
            status = "状態"
            proceed = "決定"

            dead = "(死んでいる)"
            waiting = "待機"
            alive = "(生きている)"

            call {
                prompt = "誰を呼び戻す？"
                title = "呼び戻す仲間"

                waiting = "(待機している)"
            }
            sell {
                prompt = "誰を売り飛ばす？"
                title = "売り飛ばす仲間"

                value = "値段"
            }
            pet_arena {
                prompt = "試合の規定人数"
                title = "出場する仲間"

                in = " *出場* "

                need_at_least_one = "最低でも一人の参加者が必要だ。"
                is_dead = "死んでいる。"
                too_many = "参加枠を超えている。"
            }
            shop {
                prompt = "誰を店長にする？"
                title = "店長候補"

                chr_negotiation = "魅力/交渉"
            }
            ranch {
                prompt = "誰をブリーダーにする？"
                title = "ブリーダー候補"

                breed_power = "繁殖力"
            }
            stayer {
                prompt = "誰を滞在させる？"
                title = "滞在状態の変更"
            }
            gene_engineer {
                prompt = "対象にする仲間は？"
                title = "仲間"

                body_skill = "獲得部位/技能"
                none = "なし"

                skill_too_low = "遺伝子学のスキルが足りない。"
            }
        }

        analysis {
            title = "自己の分析"
            result = "分析結果"
        }

        manual {
            topic = "項目"
            keys {
                list = "キーの一覧"
                item {
                    title = "アイテムに関するキー"

                    get = "アイテムを取る(get)"
                    drop = "アイテムを置く(drop)"
                    examine = "アイテムを調べる(examine)"
                    wear_wield = "装備する(wear,wield)"
                    eat = "食べる(eat)"
                    quaff = "飲む(quaff)"
                    read = "読む(read)"
                    zap = "振る(zap)"
                    tool = "道具を使う(tool)"
                    blend = "調合(blend)"
                    throw = "投げる(throw)"
                    ammo = "装填(ammo)"
                }
                action {
                    title = "行動に関するキー"

                    search = "周囲を調べる(search)"
                    cast = "魔法を唱える(cast)"
                    interact = "干渉する(interact)"
                    go_down = "階段を降りる,入る(go down)"
                    go_up = "階段を昇る(go up)"
                    wait = "その場で待機(wait)"
                    target = "ターゲットを指定(target)"
                    fire = "射撃する(fire)"
                    apply = "能力を使う(apply)"
                    bash = "体当たりする(bash)"
                    dig = "穴を掘る(dig)"
                    open = "鍵を開ける(open)"
                }
                info {
                    title = "情報に関するキー"

                    chara = "能力・スキル情報(chara)"
                    journal = "冒険日誌を表示(journal)"
                    help = "ヘルプを表示(help)"
                    log = "メッセージログを表示(log)"
                    material = "マテリアル表示(material)"
                    feat = "特徴の表示(feat)"
                }
                other {
                    title = "その他のキー"

                    save = "セーブして終了(save)"
                    pray = "神に祈る(pray)"
                    offer = "神に捧げる(offer)"
                    close = "ドアを閉める(close)"
                    give = "与える(give)"

                    hide_interface = "インタフェース非表示"
                    export_chara_sheet = "キャラ情報の出力"
                    console = "コンソールの表示"
                }
            }
        }

        impression {
            _0 = "天敵",
            _1 = "嫌い",
            _2 = "うざい",
            _3 = "普通",
            _4 = "好意的",
            _5 = "友達",
            _6 = "親友",
            _7 = "魂の友",
            _8 = "*Love*",
        }

        weather {
            _0 = "",
            _1 = "*エーテル*",
            _2 = "雪",
            _3 = "雨",
            _4 = "雷雨",
        }

        home {
            _0 = "洞窟",
            _1 = "森のほったて小屋",
            _2 = "住み心地のいい家",
            _3 = "セレブ邸",
            _4 = "サイバーハウス",
            _5 = "小城",
        }

        furniture {
            _0 = "",
            _1 = "みすぼらしい",
            _2 = "気になる",
            _3 = "いい感じの",
            _4 = "マダム殺しの",
            _5 = "思わず見入りそうな",
            _6 = "マニア向けの",
            _7 = "凄く華麗な",
            _8 = "王家御用達の",
            _9 = "芸術的な",
            _10 = "神々しい",
            _11 = "世界最高の",
        }

        weight {
            _0 = "超ミニに",
            _1 = "小振りに",
            _2 = "手ごろに",
            _3 = "やや大きく",
            _4 = "どでかく",
            _5 = "かなり巨大に",
            _6 = "化け物サイズに",
            _7 = "人より大きく",
            _8 = "伝説的サイズに",
            _9 = "象より重く",
        }

        reward {
            _0 = "",
            _1 = "装備品",
            _2 = "魔道具",
            _3 = "防具",
            _4 = "武器",
            _5 = "補給品",
        }

        time {
            _0 = "深夜",
            _1 = "夜明け",
            _2 = "朝",
            _3 = "昼",
            _4 = "宵",
            _5 = "夜",
            _6 = "",
            _7 = "",
        }

        attribute {
            _0 = "筋力",
            _1 = "耐久",
            _2 = "器用",
            _3 = "感覚",
            _4 = "習得",
            _5 = "意思",
            _6 = "魔力",
            _7 = "魅力",
        }

        quality {
            _0 = "",
            _1 = "粗悪",
            _2 = "良質",
            _3 = "高品質",
            _4 = "奇跡",
            _5 = "神器",
            _6 = "特別",
        }

        resistance {
            _0 = "致命的な弱点",
            _1 = "弱点",
            _2 = "耐性なし",
            _3 = "弱い耐性",
            _4 = "普通の耐性",
            _5 = "強い耐性",
            _6 = "素晴らしい耐性",
        }

        mark {
            _0 = "。",
            _1 = "？",
            _2 = "！",
            _3 = "",
        }

        sex {
            _0 = "男",
            _1 = "女",
        }

        sex2 {
            _0 = "男",
            _1 = "女",
        }

        sex3 {
            male = "男性"
            female = "女性"
        }

        onii {
            _0 = "お兄",
            _1 = "お姉",
        }

        syujin {
            _0 = "ご主人様",
            _1 = "お嬢様",
        }

        inventory_command {
            _0 = "",
            _1 = "調べる",
            _2 = "置く",
            _3 = "拾う",
            _4 = "",
            _5 = "食べる",
            _6 = "装備する",
            _7 = "読む",
            _8 = "飲む",
            _9 = "振る",
            _10 = "渡す",
            _11 = "購入する",
            _12 = "売却する",
            _13 = "鑑定する",
            _14 = "使う",
            _15 = "開く",
            _16 = "料理する",
            _17 = "調合",
            _18 = "混ぜる対象",
            _19 = "捧げる",
            _20 = "交換する",
            _21 = "提示する",
            _22 = "取る",
            _23 = "対象の",
            _24 = "入れる",
            _25 = "もらう",
            _26 = "投げる",
            _27 = "盗む",
            _28 = "交換する",
            _29 = "予約する",
        }

        body_part {
            _0 = "",
            _1 = "頭",
            _2 = "首",
            _3 = "背中",
            _4 = "胴体",
            _5 = "手",
            _6 = "指",
            _7 = "腕",
            _8 = "腰",
            _9 = "足",
            _10 = "遠隔",
            _11 = "矢弾",
        }

        action {
            _0 = "行動",
            _1 = "食事",
            _2 = "読書",
            _3 = "移動",
            _4 = "休息",
            _5 = "採掘",
            _6 = "演奏",
            _7 = "釣り",
            _8 = "採取",
            _9 = "探索",
            _10 = "行動",
            _11 = "行動",
            _12 = "行動",
            _13 = "行動",
        }

        cast_style {
            _0 = "魔法を詠唱した。",
            _1 = "糸を吐いた。",
            _2 = "体液をまき散らした。",
            _3 = "触手を伸ばした。",
            _4 = "鋭く睨んだ。",
            _5 = "胞子を飛ばした。",
            _6 = "細かく振動した。",
        }

        random_item {
            potion {
                name = "ポーション"
                _0 = "透明な",
                _1 = "緑色の",
                _2 = "青い",
                _3 = "金色の",
                _4 = "茶色い",
                _5 = "赤い",
            }

            spellbook {
                name = "魔法書"
                _0 = "分厚い",
                _1 = "苔むした",
                _2 = "真新しい",
                _3 = "豪華な",
                _4 = "古びた",
                _5 = "血の滴る",
            }

            scroll {
                name = "巻物"
                _0 = "かすれた",
                _1 = "苔むした",
                _2 = "ぼろぼろの",
                _3 = "難しそうな",
                _4 = "古びた",
                _5 = "血文字の",
            }

            rod {
                name = "魔法棒"
                _0 = "鉄の",
                _1 = "つたの",
                _2 = "サファイアの",
                _3 = "金の",
                _4 = "木の",
                _5 = "錆の",
            }

            ring {
                name = "指輪"
                _0 = "鉄の",
                _1 = "緑の",
                _2 = "サファイアの",
                _3 = "金の",
                _4 = "木の",
                _5 = "錆びた",
            }
        }


        cheer_up_message {
            _1 = "ラーネイレ「がんばれ〜」",
            _2 = "ロミアス「陰ながら応援しているよ（ニヤリ）」",
            _3 = "クミロミ「…大丈夫…だよね？」",
            _4 = "ルルウィ「あら、思いの他がんばるのね」",
            _5 = "ラーネイレ「いけない。このままでは…手遅れになってしまうわ…」",
            _6 = "ロミアス「まだまだ、これからだろう（ニヤリ）」",
            _7 = "ルルウィ「休憩しなさい。壊れちゃったら、私の役にたてないじゃない」",
            _8 = "ルルウィ「何を言っても無駄のようね。好きにするといいわ」",
            _12 = "オパートス「フハハハハッフハー」",
            _24 = "虚空「希望はまだあるはずだ」",
        }

        autodig {
            mode = "採掘",
            enabled = "自動採掘をオンにした。",
            disabled = "自動採掘をオフにした。",
        }

        autopick {
            do_you_really_pick_up = "${name(_1)}を拾う？"
            do_you_really_destroy = "${name(_1)}を破壊する？"
            destroyed = "${name(_1)}を破壊した。"
            do_you_really_open = "${name(_1)}を開ける？"
        }

        # TODO: move them somewhere else.
        young_sister {
            random = [
                "「${_1}ちゃんー」",
                "「${_1}ちゃん！」",
                "「${_1}ちゃ〜ん」",
                "「${_1}ちゃんっ」",
                "「${_1}ちゃん？」",
                "「${_1}〜ちゃん」",
                "「${_1}ちゃん♪」",
            ]
            okaeri = [
                "「おかえり、${_1}ちゃん！」",
                "「おかえりなさーい、${_1}ちゃん♪」",
                "「待ってたよ、${_1}ちゃん」",
            ]
        }

        maid {
            random = [
                "「${_1}〜」",
                "${_1}〜",
                "「用事はありませんか♪」",
                "メイドの熱い視線を感じる…",
            ]
            died = [
                "「ダメぇ！」",
                "「${_1}ー！」",
            ]
            okaeri = [
                "「おかえりなさいませ、${_1}〜」",
                "「おかえりなさいまし〜」",
            ]
        }

        cat_sister {
            random = [
                "「${_1}ちゃんー」",
                "「${_1}ちゃん！」",
                "「${_1}ちゃ〜ん」",
                "「${_1}ちゃんっ」",
                "「${_1}ちゃん？」",
                "「${_1}〜ちゃん」",
                "「${_1}ちゃん♪」",
            ]
            okaeri = [
                "「おかえりにゃ、${_1}ちゃん！」",
                "「おかえりなさいにゃー、${_1}ちゃん♪」",
                "「待ってたにゃ、${_1}ちゃん」",
            ]
        }
    }
}
