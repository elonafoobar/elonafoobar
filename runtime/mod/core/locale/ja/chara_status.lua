local i18n = require("core.i18n")

i18n.add {
   chara_status = {
      gain_new_body_part = "{name($1)}の身体から新たな{$2}が生えてきた！",

      karma = {
         changed = "カルマ変動({$1}) ",
         you_are_no_longer_criminal = "あなたの罪は軽くなった。",
         you_are_criminal_now = "あなたは今や罪人だ。",
      },
   },
}
