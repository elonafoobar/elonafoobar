trait.prefix = {
  feat = "[フィート]",
  mutation = "[変異]",
  nature = "[先天]",
  ether_disease = "[ｴｰﾃﾙ病]",
}


trait['24'] = {
  name = {
    _0 = "短距離走者",
    _1 = "中距離走者",
    _2 = "長距離走者",
  },
  how_to_acquiit = "長年の特訓の成果がスタミナを高める",
  description = function(self, stage)
    return ({
      "あなたは持久力がある[スタミナ+]",
      "あなたはかなり持久力がある[スタミナ++]",
      "あなたの持久力は恐ろしい[スタミナ上昇]",
    })[stage]
  end,
}

trait['3'] = {
  name = {
    _0 = "吸血鬼",
  },
  how_to_acquire = "吸血鬼の友人から血の吸い方を学ぶ",
  description = function(self, stage)
    return "あなたは血を吸うことができる"
  end,
}

trait['40'] = {
  name = {
    _0 = "指導者",
  },
  how_to_acquire = "指導を続けるうちに、仲間を一時的に強くする方法を見つける",
  description = function(self, stage)
    return "あなたは仲間を一時的に強くできる"
  end,
}

trait['13'] = {
  name = {
    _0 = "空間歪曲",
  },
  how_to_acquire = "夢の中で近くへの瞬間移動を思いつく",
  description = function(self, stage)
    return "あなたは空間を曲げられる"
  end,
}

trait['14'] = {
  name = {
    _0 = "火炎芸",
  },
  how_to_acquire = "酒を飲んでいるうちに火を噴けるようになる",
  description = function(self, stage)
    return "あなたは口から火を噴ける"
  end,
}

trait['22'] = {
  name = {
    _0 = "催眠術師",
  },
  how_to_acquire = "突如として眠りの手を覚える",
  description = function(self, stage)
    return "あなたは催眠をかけることができる"
  end,
}

trait['23'] = {
  name = {
    _0 = "毒の知恵",
  },
  how_to_acquire = "毒の研究の結果、毒の手を覚える",
  description = function(self, stage)
    return "あなたは毒を盛ることができる"
  end,
}

trait['21'] = {
  name = {
    _0 = "セクシー",
    _1 = "色魔",
  },
  how_to_acquire = "セクシーなポーズを学ぶ",
  description = function(self, stage)
    return ({
      "あなたはセクシーだ[魅力+4]",
      "あなたはとんでもない色魔だ[魅力+8] ",
    })[stage]
  end,
}

trait['5'] = {
  name = {
    _0 = "腕相撲",
    _1 = "腕相撲の達人",
    _2 = "腕相撲のチャンピオン",
  },
  how_to_acquire = "腕相撲の特訓で筋力を高める",
  description = function(self, stage)
    return ({
      "あなたは腕相撲が強い[筋力+3]",
      "あなたは腕相撲の達人だ[筋力+6]",
      "あなたは腕相撲のチャンピオンだ[筋力+9]",
    })[stage]
  end,
}

trait['38'] = {
  name = {
    _0 = "見習い会計士",
    _1 = "熟練会計士",
  },
  how_to_acquire = "会計の技能を磨き税金を減らす",
  description = function(self, stage)
    return ({
      "あなたは税金の計算に強い[税金7%減]",
      "あなたは税金の計算にとても強い[税金15%減]",
    })[stage]
  end,
}

trait['39'] = {
  name = {
    _0 = "見習い補給係",
    _1 = "熟練補給係",
  },
  how_to_acquire = "補給係としての経験が、給料物資の品質を上げる",
  description = function(self, stage)
    return ({
      "あなたはたまに質の高い補給品を受け取る",
      "あなたは頻繁に質の高い補給品を受け取る",
    })[stage]
  end,
}

trait['42'] = {
  name = {
    _0 = "祈祷師",
  },
  how_to_acquire = "祈祷を捧げることで、呪いの言葉の効力を弱める",
  description = function(self, stage)
    return "あなたの祈りは呪いの言葉を掻き消す"
  end,
}

trait['9'] = {
  name = {
    _0 = "我慢強い",
    _1 = "とても我慢強い",
    _2 = "恐ろしく我慢強い",
  },
  how_to_acquire = "頭を壁にぶつけて耐久力を高める",
  description = function(self, stage)
    return ({
      "あなたは我慢強い[耐久+3]",
      "あなたはとても我慢強い[耐久+6]",
      "あなたは恐ろしく我慢強い[耐久+9]",
    })[stage]
  end,
}

trait['20'] = {
  name = {
    _0 = "格闘家",
    _1 = "拳聖",
  },
  how_to_acquire = "ストリートファイトに興じ格闘技の技を得る",
  description = function(self, stage)
    return ({
      "あなたは格闘技を会得している[格闘+3]",
      "あなたは拳聖だ[格闘+6]",
    })[stage]
  end,
}

trait['12'] = {
  name = {
    _0 = "集中",
    _1 = "高い集中",
  },
  how_to_acquire = "日々瞑想し詠唱技術を高める",
  description = function(self, stage)
    return ({
      "あなたの集中力は高い[詠唱+4]",
      "あなたは極度に集中できる[詠唱+8]",
    })[stage]
  end,
}

trait['43'] = {
  name = {
    _0 = "盾殴り",
  },
  how_to_acquire = "盾の扱いを身につけ、盾での攻撃機会を増やす",
  description = function(self, stage)
    return "あなたは盾で攻撃する機会を多く得る"
  end,
}

trait['44'] = {
  name = {
    _0 = "優しい笑顔",
  },
  how_to_acquire = "優しい笑顔を習得し、敵が逃げ出すのを防ぐ",
  description = function(self, stage)
    return "あなたの攻撃は敵を恐怖させない"
  end,
}

trait['19'] = {
  name = {
    _0 = "二刀流の習熟",
    _1 = "二刀流の達人",
  },
  how_to_acquire = "長年の修行により二刀流の技術を磨く",
  description = function(self, stage)
    return ({
      "あなたは複数の武器を巧みに操る[二刀流+4]",
      "あなたは二刀流を極めている[二刀流+8]",
    })[stage]
  end,
}

trait['15'] = {
  name = {
    _0 = "暗闇への適正",
    _1 = "暗闇への強い適正",
  },
  how_to_acquire = "地底での生活が暗黒への耐性を高める",
  description = function(self, stage)
    return ({
      "あなたは暗闇に慣れている[暗黒耐性強化]",
      "あなたは闇の中で生活できる[暗黒耐性強化]",
    })[stage]
  end,
}

trait['18'] = {
  name = {
    _0 = "免疫",
    _1 = "強い免疫",
  },
  how_to_acquire = "貴族の毒見係のおかげで毒への耐性を得る",
  description = function(self, stage)
    return ({
      "あなたは毒に免疫がある[毒耐性強化]",
      "あなたには毒に強い免疫がある[毒耐性強化]",
    })[stage]
  end,
}

trait['16'] = {
  name = {
    _0 = "交渉上手",
    _1 = "交渉の神",
  },
  how_to_acquire = "行商人の元で働き交渉の技術を学ぶ",
  description = function(self, stage)
    return ({
      "あなたは交渉が上手い[交渉+4]",
      "あなたの交渉は神ががっている[交渉+8]",
    })[stage]
  end,
}

trait['17'] = {
  name = {
    _0 = "信者",
    _1 = "狂信者",
  },
  how_to_acquire = "神官の下で修行し信仰を深める",
  description = function(self, stage)
    return ({
      "あなたは信仰に篤い[信仰+4]",
      "あなたは猛烈な信者だ[信仰+8]",
    })[stage]
  end,
}

trait['1'] = {
  name = {
    _0 = "幸運の持ち主",
    _1 = "類稀な幸運",
    _2 = "幸運の女神の寵愛",
  },
  how_to_acquire = "流れ星を見て幸運を手にする",
  description = function(self, stage)
    return ({
      "あなたは幸運の持ち主だ",
      "あなたは類稀な幸運の持ち主だ",
      "あなたは幸運の女神の寵愛を受けている",
    })[stage]
  end,
}

trait['2'] = {
  name = {
    _0 = "苦行者見習い",
    _1 = "苦行者",
    _2 = "熟練の苦行者",
    _3 = "苦行の達人",
    _4 = "伝説的苦行者",
  },
  how_to_acquire = "苦行を通じてHPを増やす",
  description = function(self, stage)
    return ({
      "あなたは苦行者の見習いだ[HP+5%]",
      "あなたは立派な苦行者だ[HP+10%]",
      "あなたは熟練した苦行者だ[HP+15%]",
      "あなたは苦行の達人だ[HP+20%]",
      "あなたは伝説的名苦行者だ[HP+25%]",
    })[stage]
  end,
}

trait['11'] = {
  name = {
    _0 = "魔力の遺伝子",
    _1 = "魔力の細胞",
    _2 = "魔力の血液",
    _3 = "魔力の肉体",
    _4 = "魔力の支配",
  },
  how_to_acquire = "遺伝子組み換えを行いMPを増やす",
  description = function(self, stage)
    return ({
      "あなたは魔力の遺伝子を持っている[MP+5%]",
      "あなたは魔力の細胞を持っている[MP+10%]",
      "あなたには魔力の血液が流れている[MP+15%]",
      "あなたの肉体は魔力を帯びている[MP+20%]",
      "あなたは魔力を支配している[MP+25%]",
    })[stage]
  end,
}

trait['6'] = {
  name = {
    _0 = "罠への注意",
    _1 = "罠への警戒",
  },
  how_to_acquire = "周りを注意深く観察し、罠の発見を容易にする",
  description = function(self, stage)
    return ({
      "あなたは罠に注意している[探知+3]",
      "あなたは罠に警戒している[探知+6]",
    })[stage]
  end,
}

trait['4'] = {
  name = {
    _0 = "俊足",
    _1 = "韋駄天",
  },
  how_to_acquire = "猫を追いかけて速くなる",
  description = function(self, stage)
    return ({
      "あなたは速く走ることができる[速度+5]",
      "あなたは猫よりも速い[速度+10]",
    })[stage]
  end,
}

trait['7'] = {
  name = {
    _0 = "石の守備",
    _1 = "鉄の守備",
    _2 = "鋼の守備",
  },
  how_to_acquire = "受身を会得しPVを上昇させる",
  description = function(self, stage)
    return ({
      "あなたの防御は石のように硬い[PV+5]",
      "あなたの守備は鉄壁だ[PV+10]",
      "あなたの防御は鋼のように固い[PV+15]",
    })[stage]
  end,
}

trait['8'] = {
  name = {
    _0 = "見極め",
    _1 = "見極めの熟練者",
    _2 = "見極めの達人",
  },
  how_to_acquire = "敵の動きを見極めDVを上昇させる",
  description = function(self, stage)
    return ({
      "あなたは見切れる[DV+4]",
      "あなたはかなり見切れる[DV+8]",
      "あなたの見切りは伝説的だ[DV+12]",
    })[stage]
  end,
}

trait['10'] = {
  name = {
    _0 = "回避の修練者",
    _1 = "回避の熟練者",
    _2 = "回避の達人",
  },
  how_to_acquire = "回避の技術に磨きをかける",
  description = function(self, stage)
    return ({
      "あなたは回避に長けている[回避+2]",
      "あなたは華麗に回避する[回避+4]",
      "あなたは回避の達人だ[回避+6]",
    })[stage]
  end,
}

trait['41'] = {
  description = function(self, stage)
    return "あなたは人肉を食べることに抵抗がない"
  end,
  message_positive = "あなたは人肉の味の虜になった。",
  message_negative = "あなたは人肉の味に飽きた。",
}

trait['25'] = {
  description = function(self, stage)
    return ({
      "あなたの皮膚は崩れている[PV-9]",
      "あなたの皮膚は脆い[PV-6]",
      "あなたの皮膚は白い[PV-3]",
      nil,
      "あなたの皮膚は硬い[PV+3]",
      "あなたの皮膚はとても硬い[PV+6]",
      "あなたは鉄のような皮膚を持っている[PV+9]",
    })[stage + 4]
  end,
  message_positive = "あなたの皮膚は硬くなった。",
  message_negative = "あなたの皮膚は薄くなった。",
}

trait['26'] = {
  description = function(self, stage)
    return ({
      "あなたはひどい関節痛を抱えている[器用-9]",
      "あなたは関節痛に悩んでいる[器用-6]",
      "あなたの関節はきしむ[器用-3]",
      nil,
      "あなたの関節はしなやかだ[器用+3]",
      "あなたの関節はとてもしなやかだ[器用+6]",
      "あなたの関節は驚くほどしなやかだ[器用+9]",
    })[stage + 4]
  end,
  message_positive = "あなたの関節はしなやかになった。",
  message_negative = "あなたの関節は痛み出した。",
}

trait['27'] = {
  description = function(self, stage)
    return ({
      "あなたの顔には血の気が全くない[自然治癒弱化]",
      "あなたは血の気が少ない[自然治癒弱化]",
      nil,
      "あなたの傷跡は再生する[自然治癒強化]",
      "あなたの傷は瞬く間にふさがる[自然治癒強化]",
    })[stage + 3]
  end,
  message_positive = "あなたの血液は緑っぽくなった。",
  message_negative = "あなたの血液は薄れた。",
}

trait['28'] = {
  description = function(self, stage)
    return ({
      "あなたの脚は折れている[速度下降]",
      "あなたの脚はとてもねじれている[速度下降]",
      "あなたの脚はねじれている[速度下降]",
      nil,
      "あなたの脚はしなやかだ[速度上昇]",
      "あなたの脚はとてもしなやかだ[速度上昇]",
      "あなたの脚は理想的な形をしている[速度上昇]",
    })[stage + 4]
  end,
  message_positive = "あなたの脚はしなやかになった。",
  message_negative = "あなたの脚はねじれた。",
}

trait['29'] = {
  description = function(self, stage)
    return ({
      "あなたの腕には筋肉がない[腕力-9]",
      "あなたの腕はとてもたるんでいる[筋力-6]",
      "あなたの腕はたるんでいる[筋力-3]",
      nil,
      "あなたの腕はひきしまっている[筋力+3]",
      "あなたの腕は強力だ[筋力+6]",
      "あなたの腕は筋肉の塊だ[筋力+9]",
    })[stage + 4]
  end,
  message_positive = "あなたの腕の筋肉が増えた。",
  message_negative = "あなたの腕の贅肉が増えた。",
}

trait['30'] = {
  description = function(self, stage)
    return ({
      "あなたが喋ると皆逃げる[魅力-10]",
      "あなたの声はかれている[魅力-5]",
      nil,
      "あなたは美声を持っている[魅力+5]",
      "あなたの声は全てを魅了する[魅力+10]",
    })[stage + 3]
  end,
  message_positive = "あなたの声はよく通る。",
  message_negative = "あなたの声はかれた。",
}

trait['31'] = {
  description = function(self, stage)
    return ({
      "あなたは痴呆だ[暗記-8]",
      "あなたは少しぼけている[暗記-4]",
      nil,
      "あなたの脳は機械化している[暗記+4]",
      "あなたの脳は完璧な機械だ[暗記+8]",
    })[stage + 3]
  end,
  message_positive = "あなたの脳は機械化した。",
  message_negative = "あなたの脳は原始化した。",
}

trait['32'] = {
  description = function(self, stage)
    return ({
      "あなたは魔法に弱い[魔法耐性弱化]",
      nil,
      "あなたは魔法に耐性がある[魔法耐性強化]",
    })[stage + 2]
  end,
  message_positive = "あなたは魔法の耐性を得た。",
  message_negative = "あなたは魔法の耐性を失った。",
}

trait['33'] = {
  description = function(self, stage)
    return ({
      "あなたの鼓膜は薄い[音耐性弱化]",
      nil,
      "あなたの鼓膜は厚い[音耐性強化]",
    })[stage + 2]
  end,
  message_positive = "あなたの鼓膜は厚くなった。",
  message_negative = "あなたの鼓膜は薄くなった。",
}

trait['34'] = {
  description = function(self, stage)
    return ({
      "あなたの腕には鳥肌がたっている[火炎耐性弱化]",
      nil,
      "あなたの血は滾っている[火炎耐性強化]",
    })[stage + 2]
  end,
  message_positive = "あなたの血は滾りだした。",
  message_negative = "あなたの腕に鳥肌がたった。",
}

trait['35'] = {
  description = function(self, stage)
    return ({
      "あなたの皮膚は寒さに弱い[冷気耐性弱化]",
      nil,
      "あなたの皮膚には霜が付いている[冷気耐性強化]",
    })[stage + 2]
  end,
  message_positive = "あなたの皮膚は冷たくなった。",
  message_negative = "あなたは汗をかきはじめた。",
}

trait['36'] = {
  description = function(self, stage)
    return ({
      "あなたの身体は電気を良く通す[電撃耐性弱化]",
      nil,
      "あなたは非電導体だ[電撃耐性強化]",
    })[stage + 2]
  end,
  message_positive = "あなたは非電導体になった。",
  message_negative = "あなたの身体は電気を良く通す。",
}

trait['37'] = {
  description = function(self, stage)
    return ({
      "あなたは片目がない[感覚-10]",
      "あなたは色弱だ[感覚-5]",
      nil,
      "あなたは猫の目をしている[感覚+5]",
      "あなたは鷹の目をしている[感覚+10]",
    })[stage + 3]
  end,
  message_positive = "あなたの目は細くなった。",
  message_negative = "あなたの視力は低下した。",
}

trait['150'] = {
  description = function(self, stage)
    return ({
      "あなたはかなり火炎に弱い",
      "あなたは火炎に弱い",
      nil,
      "あなたは火炎に耐性がある",
      "あなたは火炎にかなりの耐性がある",
    })[stage + 3]
  end,
}

trait['151'] = {
  description = function(self, stage)
    return ({
      "あなたはかなり冷気に弱い",
      "あなたは冷気に弱い",
      nil,
      "あなたは冷気に耐性がある",
      "あなたは冷気にかなりの耐性がある",
    })[stage + 3]
  end,
}

trait['152'] = {
  description = function(self, stage)
    return ({
      "あなたはかなり毒に弱い",
      "あなたは毒に弱い",
      nil,
      "あなたは毒に耐性がある",
      "あなたは毒にかなりの耐性がある",
    })[stage + 3]
  end,
}

trait['155'] = {
  description = function(self, stage)
    return ({
      "あなたはかなり暗黒に弱い",
      "あなたは暗黒に弱い",
      nil,
      "あなたは暗黒に耐性がある",
      "あなたは暗黒にかなりの耐性がある",
    })[stage + 3]
  end,
}

trait['156'] = {
  description = function(self, stage)
    return "あなたはマナの反動を軽減できる"
  end,
}

trait['160'] = {
  description = function(self, stage)
    return "あなたは高い耐性をもっている"
  end,
}

trait['161'] = {
  description = function(self, stage)
    return "あなたは1s以上の物を装備できない[DV上昇]"
  end,
}

trait['162'] = {
  description = function(self, stage)
    return "あなたは罪悪感を感じない[カルマ上限-20]"
  end,
}

trait['169'] = {
  description = function(self, stage)
    return "あなたは良い心を持っている[カルマ上限+20]"
  end,
}

trait['163'] = {
  description = function(self, stage)
    return "あなたの周りでは質の高いエンチャントが生成される"
  end,
}

trait['164'] = {
  description = function(self, stage)
    return "あなたが受ける物理ダメージは軽減される"
  end,
}

trait['165'] = {
  description = function(self, stage)
    return "あなたの元素魔法は強化されている"
  end,
}

trait['166'] = {
  description = function(self, stage)
    return "あなたは周囲の狂気を緩和する"
  end,
}

trait['167'] = {
  description = function(self, stage)
    return "あなたは萌える"
  end,
}

trait['157'] = {
  description = function(self, stage)
    return "あなたは朦朧状態にならない"
  end,
}

trait['158'] = {
  description = function(self, stage)
    return "あなたの食料の消化は遅い"
  end,
}

trait['159'] = {
  description = function(self, stage)
    return "あなたはより多く採取できる"
  end,
}

trait['154'] = {
  description = function(self, stage)
    return "あなたには追加の成長ボーナスが与えられる"
  end,
}

trait['153'] = {
  description = function(self, stage)
    return ({
      "あなたはかなり魔法に弱い",
      "あなたは魔法に弱い",
      nil,
      "あなたは魔法に耐性がある",
      "あなたは魔法にかなりの耐性がある",
    })[stage + 3]
  end,
}

trait['0'] = {
  description = function(self, stage)
    return "あなたの肉体は刻々と変化する"
  end,
}

trait['168'] = {
  description = function(self, stage)
    return "あなたのエーテル病の進行は遅い"
  end,
}

trait['201'] = {
  description = function(self, stage)
    return ({
      "あなたは重力を生み出している[重量+10%]",
      "あなたは大きな重力を生み出している[重量+20%]",
      "あなたはとてつもない重力を生み出している[重量+30%]",
    })[-stage]
  end,
  message_positive = "あなたの周りの重力は軽減した。",
  message_negative = "あなたは重力を発するようになった。",
}

trait['202'] = {
  description = function(self, stage)
    return ({
      "あなたの顔はただれている[魅力" .. (-1 * (4 + cdata(0):level() // 5)) .. "]",
      "あなたの顔中に蕁麻疹が出ている[魅力" .. (-2 * (4 + cdata(0):level() // 5)) .. "]",
      "あなたの顔は崩れかけている[魅力" .. (-3 * (4 + cdata(0):level() // 5)) .. "]",
    })[-stage]
  end,
  message_positive = "あなたの顔のただれは軽くなった。",
  message_negative = "あなたの顔はただれた。",
}

trait['203'] = {
  description = function(self, stage)
    return "あなたの足の裏は蹄になっている[足装備不可 速度+" .. (20 + cdata(0):level() // 2) .. "]"
  end,
  message_positive = "あなたの足は元に戻った。",
  message_negative = "あなたの足の裏は蹄に変形した。",
}

trait['204'] = {
  description = function(self, stage)
    return "あなたの目は4つある[感覚+" .. (5 + cdata(0):level() // 3) .. " 魅力" .. -(5 + cdata(0):level() // 3) .. "]"
  end,
  message_positive = "あなたの目は減った。",
  message_negative = "あなたの目は増殖した。",
}

trait['205'] = {
  description = function(self, stage)
    return "あなたの背中には羽がある[背中装備不可 重量-20% 速度+" .. (12 + cdata(0):level() // 4) .. "]"
  end,
  message_positive = "あなたの背中から羽が消えた。",
  message_negative = "あなたの背中に羽が生えた。",
}

trait['206'] = {
  description = function(self, stage)
    return "あなたの首はもの凄く太い[首装備不可 魅力" .. -(5 + cdata(0):level() // 5) .. " PV+" .. (12 + cdata(0):level()) .. "]"
  end,
  message_positive = "あなたの首は細くなった。",
  message_negative = "あなたの首は太くなった。",
}

trait['207'] = {
  description = function(self, stage)
    return "あなたは殺戮に飢えている[DV" .. -(15 + cdata(0):level() * 3 // 2) .. " ダメージ修正+" .. (5 + cdata(0):level() * 2 // 3) .. "]"
  end,
  message_positive = "あなたの心は落ち着いた。",
  message_negative = "あなたは憎しみに支配された。",
}

trait['208'] = {
  description = function(self, stage)
    return "あなたの頭は巨大化している[耐久" .. -(5 + cdata(0):level() // 3) .. " 器用" .. -(4 + cdata(0):level() // 4) .. " 習得+" .. (6 + cdata(0):level() // 2) .. " 意思+" .. (2 + cdata(0):level() // 6) .. "]"
  end,
  message_positive = "あなたの頭は元に戻った。",
  message_negative = "あなたの頭は巨大化した。",
}

trait['209'] = {
  description = function(self, stage)
    return "あなたは雨を呼ぶ[雨天確率上昇]"
  end,
  message_positive = "あなたの頭上から雨雲が消えた。",
  message_negative = "あなたの頭上に雨雲が現れた。",
}

trait['210'] = {
  description = function(self, stage)
    return "あなたはポーション中毒だ[定期的ポーション消費]"
  end,
  message_positive = "あなたのポーション中毒は消えた。",
  message_negative = "あなたはポーション中毒になった。",
}

trait['211'] = {
  description = function(self, stage)
    return "あなたは衰弱している[HP-15% 筋力" .. -(4 + cdata(0):level() // 2) .. "]"
  end,
  message_positive = "あなたは健康になった。",
  message_negative = "あなたは衰弱した。",
}

trait['212'] = {
  description = function(self, stage)
    return "あなたは痴呆になっている[MP-15% 魔力" .. -(4 + cdata(0):level() // 2) .. "]"
  end,
  message_positive = "あなたは明晰になった。",
  message_negative = "あなたはぼけた。",
}

trait['213'] = {
  description = function(self, stage)
    return "あなたは重い甲殻で覆われている[PV+" .. (15 + cdata(0):level() // 2) .. " 速度" .. -(20 + cdata(0):level() // 2) .. "]"
  end,
  message_positive = "あなたの皮膚から甲殻が消えた。",
  message_negative = "あなたの皮膚は甲殻で覆われた。",
}

trait['214'] = {
  description = function(self, stage)
    return "あなたの周囲の空間は捩れている[ランダムテレポート]"
  end,
  message_positive = "あなたの周囲の空間は元通りになった。",
  message_negative = "あなたの周囲の空間は捩れた。",
}

trait['215'] = {
  description = function(self, stage)
    return "あなたは生きたマナバッテリーだ[杖から魔力抽出]"
  end,
  message_positive = "あなたのマナは元通りになった。",
  message_negative = "あなたのマナは杖から魔力を抽出する。",
}

trait['216'] = {
  description = function(self, stage)
    return "あなたの手から毒が滴っている[ポーション毒化 毒耐性強化]"
  end,
  message_positive = "あなたの手は元通りになった。",
  message_negative = "あなたの手から毒が滴り出した。",
}


-- vim: et sw=2 sts=2
