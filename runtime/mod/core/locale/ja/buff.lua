local I18N = ELONA.require("core.I18N")

I18N.add_data_text(
   "core.buff",
   {
      holy_shield = {
         name = "聖なる盾",
         apply = "{name($1)}は光り輝いた。",
         description = "PVを{$1}上昇/耐恐怖",
      },
      mist_of_silence = {
         name = "沈黙の霧",
         apply = "{name($1)}はぼやけた霧に覆われた。",
         description = "魔法の使用を禁止",
      },
      regeneration = {
         name = "リジェネレーション",
         apply = "{name($1)}の代謝が活性化した。",
         description = "自然回復強化",
      },
      elemental_shield = {
         name = "元素保護",
         apply = "{name($1)}は元素への耐性を得た。",
         description = "炎冷気電撃耐性の獲得",
      },
      speed = {
         name = "加速",
         apply = "{name($1)}は機敏になった。",
         description = "{$1}の加速",
      },
      slow = {
         name = "鈍足",
         apply = "{name($1)}は鈍重になった。",
         description = "{$1}の鈍足",
      },
      hero = {
         name = "英雄",
         apply = "{name($1)}の士気が向上した。",
         description = "筋力・器用を{$1}上昇/耐恐怖/耐混乱",
      },
      mist_of_frailness = {
         name = "脆弱の霧",
         apply = "{name($1)}は脆くなった。",
         description = "DVとPVを半減",
      },
      element_scar = {
         name = "元素の傷跡",
         apply = "{name($1)}は元素への耐性を失った。",
         description = "炎冷気電撃耐性の減少",
      },
      holy_veil = {
         name = "ホーリーヴェイル",
         apply = "{name($1)}は聖なる衣に保護された。",
         description = "ﾊﾟﾜｰ{$1}の呪い(hex)への抵抗",
      },
      nightmare = {
         name = "ナイトメア",
         apply = "{name($1)}は悪夢に襲われた。",
         description = "神経幻惑耐性の減少",
      },
      divine_wisdom = {
         name = "知者の加護",
         apply = "{name($1)}の思考は冴え渡った。",
         description = "習得・魔力を{$1}上昇/読書を{$2}上昇",
      },
      punishment = {
         name = "天罰",
         apply = "{name($1)}は雷に打たれた！",
         description = "{$1}の鈍足/PVを{$2}%減少",
      },
      lulwys_trick = {
         name = "ルルウィの憑依",
         apply = "{name($1)}にルルウィが乗り移った。",
         description = "{$1}の加速",
      },
      incognito = {
         name = "インコグニート",
         apply = "{name($1)}は別人になりすました。",
         description = "変装",
      },
      death_word = {
         name = "死の宣告",
         apply = "{name($1)}は死の宣告を受けた！",
         description = "呪いが完了したときに確実なる死",
      },
      boost = {
         name = "ブースト",
         apply = "{name($1)}はブーストした！",
         description = "{$1}の加速と能力のアップ",
      },
      contingency = {
         name = "契約",
         apply = "{name($1)}は死神と契約した。",
         description = "致命傷を負ったとき{$1}%の確率でダメージ分回復。",
      },
      luck = {
         name = "幸運",
         apply = "{name($1)}に幸運な日が訪れた！",
         description = "{$1}の幸運の上昇",
      },
      grow_strength = {
         name = "筋力の成長",
         apply = "",
         description = "筋力の成長率を{$1}%上昇",
      },
      grow_constitution = {
         name = "耐久の成長",
         apply = "",
         description = "耐久の成長率を{$1}%上昇",
      },
      grow_dexterity = {
         name = "器用の成長",
         apply = "",
         description = "器用の成長率を{$1}%上昇",
      },
      grow_perception = {
         name = "感覚の成長",
         apply = "",
         description = "感覚の成長率を{$1}%上昇",
      },
      grow_learning = {
         name = "習得の成長",
         apply = "",
         description = "習得の成長率を{$1}%上昇",
      },
      grow_will = {
         name = "意思の成長",
         apply = "",
         description = "意思の成長率を{$1}%上昇",
      },
      grow_magic = {
         name = "魔力の成長",
         apply = "",
         description = "魔力の成長率を{$1}%上昇",
      },
      grow_charisma = {
         name = "魅力の成長",
         apply = "",
         description = "魅力の成長率を{$1}%上昇",
      },
      grow_speed = {
         name = "速度の成長",
         apply = "",
         description = "速度の成長率を{$1}%上昇",
      },
      grow_luck = {
         name = "運勢の成長",
         apply = "",
         description = "運勢の成長率を{$1}%上昇",
      },
   }
)
