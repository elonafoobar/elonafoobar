i18n.add {
   building = {
      can_only_use_in_world_map = "それはワールドマップでしか使えない。",
      cannot_build_it_here = "その場所には建てられない。",
      cannot_build_anymore = "もうこれ以上建物は建てられない。",
      really_build_it_here = "本当にこの場所に建設する？ ",

      built_new_house = "新しい家を建てた！ ",
      built_new = "あなたは{$1}を建設した！ ",

      not_enough_money = "お金が足りない…",

      names = {
         _521 = "博物館",
         _522 = "店",
         _542 = "畑",
         _543 = "倉庫",
         _572 = "牧場",
         _712 = "ダンジョン",
      },

      guests = {
         armory = "武具店の{basename($1)}",
         general_store = "雑貨屋の{basename($1)}",
         magic_store = "魔法店の{basename($1)}",
         goods_store = "何でも屋の{basename($1)}",
         blackmarket = "ブラックマーケットの{basename($1)}",
      },

      house_board = {
         only_use_in_home = "ここはあなたの家ではない。",
         item_count = "{$1}には{$2}個のアイテムと{$3}個の家具がある(アイテム最大{$4}個) ",
         what_do = "何をする？",

         choices = {
            assign_a_shopkeeper = "仲間に店主を頼む",
            extend = "店を拡張({$1} GP)",
            assign_a_breeder = "ブリーダーを任命する",
            design = "家の模様替え",
            home_rank = "家の情報",
            allies_in_your_home = "仲間の滞在",
            recruit_a_servant = "使用人を募集する",
            move_a_stayer = "滞在者の移動",
         },
      },

      home = {
         hire = {
            who = "誰を雇用する？",
            too_many_guests = "家はすでに人であふれかえっている。",
            you_hire = "{basename($1)}を家に迎えた。",
         },

         design = {
            help = "マウスの左クリックでタイルの敷設、コントロールキーを押しながらマウスの左クリックで塗りつぶし、右クリックでタイルの取得、移動キーでスクリーン移動、決定キーでタイル一覧、キャンセルキーで終了。",
         },

         move = {
            who = "誰を移動させる？",
            dont_touch_me = "{basename($1)}「触るな！」",
            where = "{basename($1)}をどこに移動させる？",
            invalid = "その場所には移動させることができない。",
            is_moved = "{basename($1)}を移動させた。",
         },

         staying = {
            count = "現在{$1}人の滞在者がいる(最大{$2}人) ",
            remove = {
               ally = "{basename($1)}の滞在を取り消した。",
               worker = "{basename($1)}を役目から外した。",
            },

            add = {
               ally = "{basename($1)}を滞在させた。",
               worker = "{basename($1)}を任命した。",
            },
         },

         rank = {
            title = "家の情報",
            enter_key = "決定ｷｰ,",
            value = "価値",
            heirloom_rank = "家宝ランク",

            type = {
               base = "基本.",
               deco = "家具.",
               heir = "家宝.",
               total = "総合.",
            },

            star = "★",
            place = "{$1}位.",
            change = "家具({$1}点) 家宝({$2}点) ランク変動({$6} {$3}位 → {$4}位 )《{$5}》",
         },
      },

      shop = {
         info = "店",
         extend = "店を拡張した！これからは{$1}個のアイテムを陳列できる。",
         current_shopkeeper = "現在の店主は{basename($1)}だ。",
         no_assigned_shopkeeper = "現在店主はいない。",

         log = {
            no_shopkeeper = "店には店番がいない。",
            could_not_sell = "{$1}人が来客したが、{basename($2)}はアイテムを一つも売れなかった。",
            sold_items = "{$1}人の来客があり、{basename($2)}は{$3}個のアイテムを売却した。{$4}が売り上げとして金庫に保管された。",
            gold = "{$1}gold",
            and_items = "と{$1}個のアイテム",
         },
      },

      ranch = {
         current_breeder = "現在のブリーダーは{basename($1)}だ。",
         no_assigned_breeder = "現在ブリーダーはいない。",
      },

      museum = {
         rank_change = "ランク変動({$4} {$1}位 → {$2}位 )《{$3}》",
      },
   },
}
