buff['1'] = {
  name = "聖なる盾",
  message_0 = "は光り輝いた。",
  message_1 = "",
  description = function(self, power)
    return "PVを" .. self._effect(power) .. "上昇/耐恐怖"
  end,
}
buff['2'] = {
  name = "沈黙の霧",
  message_0 = "はぼやけた霧に覆われた。",
  message_1 = "",
  description = function(self, power)
    return "魔法の使用を禁止"
  end,
}
buff['3'] = {
  name = "リジェネレーション",
  message_0 = "の代謝が活性化した。",
  message_1 = "",
  description = function(self, power)
    return "自然回復強化"
  end,
}
buff['4'] = {
  name = "元素保護",
  message_0 = "は元素への耐性を得た。",
  message_1 = "",
  description = function(self, power)
    return "炎冷気電撃耐性の獲得"
  end,
}
buff['5'] = {
  name = "加速",
  message_0 = "は機敏になった。",
  message_1 = "",
  description = function(self, power)
    return self._effect(power) .. "の加速"
  end,
}
buff['6'] = {
  name = "鈍足",
  message_0 = "は鈍重になった。",
  message_1 = "",
  description = function(self, power)
    return self._effect(power) .. "の鈍足"
  end,
}
buff['7'] = {
  name = "英雄",
  message_0 = "の士気が向上した。",
  message_1 = "",
  description = function(self, power)
    return "筋力・器用を" .. self._effect(power) .. "上昇/耐恐怖/耐混乱"
  end,
}
buff['8'] = {
  name = "脆弱の霧",
  message_0 = "は脆くなった。",
  message_1 = "",
  description = function(self, power)
    return "DVとPVを半減"
  end,
}
buff['9'] = {
  name = "元素の傷跡",
  message_0 = "は元素への耐性を失った。",
  message_1 = "",
  description = function(self, power)
    return "炎冷気電撃耐性の減少"
  end,
}
buff['10'] = {
  name = "ホーリーヴェイル",
  message_0 = "は聖なる衣に保護された。",
  message_1 = "",
  description = function(self, power)
    return "ﾊﾟﾜｰ" .. self._effect(power) .. "の呪い(hex)への抵抗"
  end,
}
buff['11'] = {
  name = "ナイトメア",
  message_0 = "は悪夢に襲われた。",
  message_1 = "",
  description = function(self, power)
    return "神経幻惑耐性の減少"
  end,
}
buff['12'] = {
  name = "知者の加護",
  message_0 = "の思考は冴え渡った。",
  message_1 = "",
  description = function(self, power)
    a, b = self._effect(power)
    return "習得・魔力を" .. a .. "上昇/読書を" .. b .. "上昇"
  end,
}
buff['13'] = {
  name = "天罰",
  message_0 = "は雷に打たれた！",
  message_1 = "",
  description = function(self, power)
    a, b = self._effect(power)
    return a .. "の鈍足/PVを" .. b .. "%減少"
  end,
}
buff['14'] = {
  name = "ルルウィの憑依",
  message_0 = "にルルウィが乗り移った。",
  message_1 = "",
  description = function(self, power)
    return self._effect(power) .. "の加速"
  end,
}
buff['15'] = {
  name = "インコグニート",
  message_0 = "は別人になりすました。",
  message_1 = "",
  description = function(self, power)
    return "変装"
  end,
}
buff['16'] = {
  name = "死の宣告",
  message_0 = "は死の宣告を受けた！",
  message_1 = "",
  description = function(self, power)
    return "呪いが完了したときに確実なる死"
  end,
}
buff['17'] = {
  name = "ブースト",
  message_0 = "はブーストした！",
  message_1 = "",
  description = function(self, power)
    return self._effect(power) .. "の加速と能力のアップ"
  end,
}
buff['18'] = {
  name = "契約",
  message_0 = "は死神と契約した。",
  message_1 = "",
  description = function(self, power)
    return "致命傷を負ったとき" .. self._effect(power) .. "%の確率でダメージ分回復。"
  end,
}
buff['19'] = {
  name = "幸運",
  message_0 = "に幸運な日が訪れた！",
  message_1 = "",
  description = function(self, power)
    return self._effect(power) .. "の幸運の上昇"
  end,
}
buff['20'] = {
  name = "筋力の成長",
  message_0 = "",
  message_1 = "",
  description = function(self, power)
    return ability['10'].name .. "の成長率を" .. self._effect(power) .. "%上昇"
  end,
}
buff['21'] = {
  name = "耐久の成長",
  message_0 = "",
  message_1 = "",
  description = function(self, power)
    return ability['11'].name .. "の成長率を" .. self._effect(power) .. "%上昇"
  end,
}
buff['22'] = {
  name = "器用の成長",
  message_0 = "",
  message_1 = "",
  description = function(self, power)
    return ability['12'].name .. "の成長率を" .. self._effect(power) .. "%上昇"
  end,
}
buff['23'] = {
  name = "感覚の成長",
  message_0 = "",
  message_1 = "",
  description = function(self, power)
    return ability['13'].name .. "の成長率を" .. self._effect(power) .. "%上昇"
  end,
}
buff['24'] = {
  name = "習得の成長",
  message_0 = "",
  message_1 = "",
  description = function(self, power)
    return ability['14'].name .. "の成長率を" .. self._effect(power) .. "%上昇"
  end,
}
buff['25'] = {
  name = "意思の成長",
  message_0 = "",
  message_1 = "",
  description = function(self, power)
    return ability['15'].name .. "の成長率を" .. self._effect(power) .. "%上昇"
  end,
}
buff['26'] = {
  name = "魔力の成長",
  message_0 = "",
  message_1 = "",
  description = function(self, power)
    return ability['16'].name .. "の成長率を" .. self._effect(power) .. "%上昇"
  end,
}
buff['27'] = {
  name = "魅力の成長",
  message_0 = "",
  message_1 = "",
  description = function(self, power)
    return ability['17'].name .. "の成長率を" .. self._effect(power) .. "%上昇"
  end,
}
buff['28'] = {
  name = "速度の成長",
  message_0 = "",
  message_1 = "",
  description = function(self, power)
    return ability['18'].name .. "の成長率を" .. self._effect(power) .. "%上昇"
  end,
}
buff['29'] = {
  name = "運勢の成長",
  message_0 = "",
  message_1 = "",
  description = function(self, power)
    return ability['19'].name .. "の成長率を" .. self._effect(power) .. "%上昇"
  end,
}



-- vim: et sw=2 sts=2
