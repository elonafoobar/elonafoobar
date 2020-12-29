local I18N = ELONA.require("core.I18N")

I18N.add {
   net = {
      failed_to_send = "送信に失敗した。",
      failed_to_receive = "受信に失敗した。",

      chat = {
         wait_more = "もう少し待った方がいい気がする。",
         message = "「{$1}」",
         sent_message = "{$1}{$2}{$3}",
      },

      death = {
         sent_message = "{$1}{$2}は{$4}で{$3}{$5}",
      },

      wish = {
         sent_message = "{$1}{$2}は狂喜して叫んだ。{$3}{$4}",
      },

      news = {
         bomb = "[パルミア・タイムズ {$1}] {$4}で核爆弾炸裂。復旧には3日を要する見込み",
         void = "[パルミア・タイムズ {$1}] {$2}{$3}すくつ{$4}階層に到達",
         ehekatl = "[パルミア・タイムズ {$1}] {$2}{$3}エヘカトル像を入手",
         fire = "[パルミア・タイムズ {$1}] ノイエルで大火災。何者かが巨人を解放か",
      },

      alias = {
         message = "素敵な異名コンテスト♪1",

         title = "投票箱",
         hint = "決定 [投票する項目を選択]  ",
         choice = "投票項目",
         vote = "備考",

         submit = "あなたの異名を登録する",
         cannot_vote_until = "あなたの投票権はまだ復活していない({$1}まで)",
         prompt = "どの候補に投票する？",

         rank = "第{$1}位",
         selected = "候補",

         ok = "オッケー",
         need_to_wait = "まだ投票権が復活していない。",
         i_like = "「{$1}は素敵！」",
         you_vote = "投票した。",
      },
   },
}
