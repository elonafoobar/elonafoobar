local I18N = require("core.I18N")

I18N.add {
   tcg = {
      card = {
         creature = "クリーチャー",
         race = "種族",
         land = "土地",
         spell = "スペル",
         domain = "ドメイン",
         rare = "レア度",
         skill = "スキル",
      },

      end_main_phase = "メインフェイズを終了する。",
      no_blocker = "ブロックしない。",

      sacrifice = {
         you = "カードを捧げた。",
         opponent = "相手はカードを捧げた。",
      },

      ref = {
         choose_one_card = "自分のデッキからカードを1枚選び受け取る。",
         draws_two_cards = "プレイヤーはカードを2枚ドローする。",
         return_creature = "場のクリーチャー1体を選択し、所有者の手札に戻す。",
      },

      put = {
         field_full = "これ以上は場に出せない。",
         not_enough_mana = "マナが足りない。",
      },

      domain = {
         lulwy = "ルルウィ",
         kumiromi = "クミロミ",
         yacatect = "ヤカテクト",
         jure = "ジュア",
         mani = "マニ",
      },

      deck = {
         color = {
            white = "白",
            blue = "青",
            silver = "銀",
            red = "赤",
            black = "黒",
         },

         name = "{$1}のデッキ",
         new = "新規作成",

         choices = {
            edit = "デッキの構築",
            set_as_main = "メインデッキに設定",
         },
      },

      select = {
         hint = ",Tab [フィルター切替]  決定ｷｰ [カード選択]  ｷｬﾝｾﾙｷｰ [終了]",
      },

      menu = {
         list = "候補",
         deck = "デッキ",

         save_and_exit = "セーブして終了",
         just_exit = "セーブしないで終了",
      },

      card_not_available = "未実装のカード",

      action = {
         put = "↑   カードを出す。",
         sacrifice = "↓   カードを捧げてマナを得る(1ターンに1回)。",
         declare_attack = "↑   攻撃を宣言する。",
         block = "↑   ブロックする。",
         use_skill = "決定 スキルを使用する。",
         no_action_available = "可能な行動はない。",
         surrender = "降参する",
      },
   },
}
