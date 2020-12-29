local I18N = require("core.I18N")

I18N.add {
   death_by = {
      chara = {
         transformed_into_meat = {
            active = {
               by_spell = "粉々の肉片に変えた。",
               by_chara = "粉々の肉片に変えた。",
            },
            passive = "{name($1)}は粉々の肉片に変えられた。",
         },
         destroyed = {
            active = {
               by_spell = "破壊した。",
               by_chara = "破壊した。",
            },
            passive = "{name($1)}は破壊された。",
         },
         minced = {
            active = {
               by_spell = "ミンチにした。",
               by_chara = "ミンチにした。",
            },
            passive = "{name($1)}はミンチにされた。",
         },
         killed = {
            active = {
               by_spell = "殺した。",
               by_chara = "殺した。",
            },
            passive = "{name($1)}は殺された。",
         },
         death_cause = "{basename($1)}に殺された。",
      },
      element = {
         default = {
            active = {
               by_spell = "殺した。",
               by_chara = "殺した。",
            },
            passive = "{name($1)}は死んだ。",
         },
         _50 = {
            active = {
               by_spell = "燃やし尽くした。",
               by_chara = "燃やし尽くした。",
            },
            passive = "{name($1)}は燃え尽きて灰になった。",
         },
         _51 = {
            active = {
               by_spell = "氷の塊に変えた。",
               by_chara = "氷の塊に変えた。",
            },
            passive = "{name($1)}は氷の彫像になった。",
         },
         _52 = {
            active = {
               by_spell = "焦げカスにした。",
               by_chara = "焦げカスにした。",
            },
            passive = "{name($1)}は雷に打たれ死んだ。",
         },
         _53 = {
            active = {
               by_spell = "闇に飲み込んだ。",
               by_chara = "闇に飲み込んだ。",
            },
            passive = "{name($1)}は闇に蝕まれて死んだ。",
         },
         _54 = {
            active = {
               by_spell = "再起不能にした。",
               by_chara = "再起不能にした。",
            },
            passive = "{name($1)}は発狂して死んだ。",
         },
         _55 = {
            active = {
               by_spell = "毒殺した。",
               by_chara = "毒殺した。",
            },
            passive = "{name($1)}は毒に蝕まれて死んだ。",
         },
         _56 = {
            active = {
               by_spell = "冥界に墜とした。",
               by_chara = "冥界に墜とした。",
            },
            passive = "{name($1)}は冥界に墜ちた。",
         },
         _57 = {
            active = {
               by_spell = "聴覚を破壊し殺した。",
               by_chara = "聴覚を破壊し殺した。",
            },
            passive = "{name($1)}は朦朧となって死んだ。",
         },
         _58 = {
            active = {
               by_spell = "神経を破壊した。",
               by_chara = "神経を破壊した。",
            },
            passive = "{name($1)}は神経を蝕まれて死んだ。",
         },
         _59 = {
            active = {
               by_spell = "混沌の渦に吸い込んだ。",
               by_chara = "混沌の渦に吸い込んだ。",
            },
            passive = "{name($1)}は混沌の渦に吸収された。",
         },
         -- _60
         _61 = {
            active = {
               by_spell = "千切りにした。",
               by_chara = "千切りにした。",
            },
            passive = "{name($1)}は千切りになった。",
         },
         -- _62
         _63 = {
            active = {
               by_spell = "ドロドロに溶かした。",
               by_chara = "ドロドロに溶かした。",
            },
            passive = "{name($1)}は酸に焼かれ溶けた。",
         },
      },
      other = {
         _1 = {
            text = "{name($1)}は罠にかかって死んだ。",
            death_cause = "罠にかかって死んだ。",
         },
         _2 = {
            text = "{name($1)}はマナの反動で死んだ。",
            death_cause = "マナの反動で消滅した。",
         },
         _3 = {
            text = "{name($1)}は餓死した。",
            death_cause = "飢え死にした。",
         },
         _4 = {
            text = "{name($1)}は毒に蝕まれ死んだ。",
            death_cause = "毒にもがき苦しみながら死んだ。",
         },
         _5 = {
            text = "{name($1)}は呪いの力で死んだ。",
            death_cause = "呪い殺された。",
         },
         _6 = {
            text = "{name($1)}は{$2}の重さに耐え切れず死んだ。",
            death_cause = "{$1}の重さに耐え切れず潰れた。",
            backpack = "荷物",
         },
         _7 = {
            text = "{name($1)}は階段から転げ落ちて死んだ。",
            death_cause = "階段から転げ落ちて亡くなった。",
         },
         _8 = {
            text = "{name($1)}は聴衆に殺された。",
            death_cause = "演奏中に激怒した聴衆に殺された。",
         },
         _9 = {
            text = "{name($1)}は焼け死んだ。",
            death_cause = "焼けて消滅した。",
         },
         -- _10
         _11 = {
            text = "{name($1)}は見えざる手に葬られた。",
            death_cause = "見えざる手に葬られた。",
         },
         _12 = {
            text = "{name($1)}は食中毒で死んだ。",
            death_cause = "食中毒で倒れた。",
         },
         _13 = {
            text = "{name($1)}は出血多量で死んだ。",
            death_cause = "血を流しすぎて死んだ。",
         },
         _14 = {
            text = "{name($1)}はエーテルに侵食され死んだ。",
            death_cause = "エーテルの病に倒れた。",
         },
         _15 = {
            text = "{name($1)}は溶けて液体になった。",
            death_cause = "溶けて液体になった。",
         },
         _16 = {
            text = "{name($1)}はバラバラになった。",
            death_cause = "自殺した。",
         },
         _17 = {
            text = "{name($1)}は核爆発に巻き込まれて塵となった。",
            death_cause = "核爆発に巻き込まれて死んだ。",
         },
         _18 = {
            text = "{name($1)}はアイアンメイデンの中で串刺しになって果てた。",
            death_cause = "アイアンメイデンにはさまれて死んだ。",
         },
         _19 = {
            text = "{name($1)}はギロチンで首をちょんぎられて死んだ。",
            death_cause = "ギロチンで首を落とされて死んだ。",
         },
         _20 = {
            text = "{name($1)}は首を吊った。",
            death_cause = "首を吊った。",
         },
         _21 = {
            text = "{name($1)}はもちを喉に詰まらせて死んだ。",
            death_cause = "もちを喉に詰まらせて死んだ。",
         },
      },
   },
}
