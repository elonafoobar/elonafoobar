trait.prefix = {
  feat = "[Feat]",
  mutation = "[Mutation]",
  nature = "[Race]",
  ether_disease = "[Disease]",
}


trait['24'] = {
  name = {
    _0 = "Short Distance Runner",
    _1 = "Middle Distance Runner",
    _2 = "Long Distance Runner",
  },
  how_to_acquiit = "Years of training strengthens your stamina.",
  description = function(self, stage)
    return ({
      "You have good stamina. [Stamina+]",
      "You have very good stamina. [Stamina++]",
      "You have outstanding stamina. [Stamina+++]",
    })[stage - self.min + 1]
  end,
}

trait['3'] = {
  name = {
    _0 = "Vampiric Ability",
  },
  how_to_acquire = "Your vampire friend teaches you how to suck blood.",
  description = function(self, stage)
    return ({
      "You can suck blood now.",
    })[stage - self.min + 1]
  end,
}

trait['40'] = {
  name = {
    _0 = "Natural Leader",
  },
  how_to_acquire = "You find how to strengthen your allies for a short time.",
  description = function(self, stage)
    return ({
      "You can temporally strengthen your allies.",
    })[stage - self.min + 1]
  end,
}

trait['13'] = {
  name = {
    _0 = "Dimensional Move",
  },
  how_to_acquire = "You hit upon an idea of insta-teleport from a dream.",
  description = function(self, stage)
    return ({
      "You can insta-teleport to nearby tiles.",
    })[stage - self.min + 1]
  end,
}

trait['14'] = {
  name = {
    _0 = "Fire Breath",
  },
  how_to_acquire = "Too much drinking makes you want to breath fire.",
  description = function(self, stage)
    return ({
      "You can breath fire.",
    })[stage - self.min + 1]
  end,
}

trait['22'] = {
  name = {
    _0 = "Hypnotism",
  },
  how_to_acquire = "Suddenly, you know how to make everyone sleep.",
  description = function(self, stage)
    return ({
      "You can hypnotize single target.",
    })[stage - self.min + 1]
  end,
}

trait['23'] = {
  name = {
    _0 = "Poison Nail",
  },
  how_to_acquire = "Researching poisons leads you to a method to poison others.",
  description = function(self, stage)
    return ({
      "You can poison a creature.",
    })[stage - self.min + 1]
  end,
}

trait['21'] = {
  name = {
    _0 = "Sexy",
    _1 = "Lady Killer",
  },
  how_to_acquire = "You learn sexy poses.",
  description = function(self, stage)
    return ({
      "You are sexy. [CHR+4]",
      "You are a lady killer. [CHR+8]",
    })[stage - self.min + 1]
  end,
}

trait['5'] = {
  name = {
    _0 = "Arm Wrestler",
    _1 = "Adept Arm Wrestler",
    _2 = "Master Arm Wrestler",
  },
  how_to_acquire = "Training arm wrestling increases your strength.",
  description = function(self, stage)
    return ({
      "You are an arm wrestler. [STR+3]",
      "You are a good arm wrestler. [STR+6]",
      "You are a master of arm wrestling. [STR+9]",
    })[stage - self.min + 1]
  end,
}

trait['38'] = {
  name = {
    _0 = "Apprentice Accountant",
    _1 = "Expert Accountant",
  },
  how_to_acquire = "Working as an accountant reduces your tax payment.",
  description = function(self, stage)
    return ({
      "You can set expenses off against tax. [TAX-7%]",
      "You are good at setting expenses off against tax. [TAX-15%]",
    })[stage - self.min + 1]
  end,
}

trait['39'] = {
  name = {
    _0 = "Apprentice Quartermaster",
    _1 = "Expert Quartermaster",
  },
  how_to_acquire = "Working as a quartermaster gives you better payoff.",
  description = function(self, stage)
    return ({
      "You sometimes receive quality supplies.",
      "You frequently receive quality supplies.",
    })[stage - self.min + 1]
  end,
}

trait['42'] = {
  name = {
    _0 = "Exorcist",
  },
  how_to_acquire = "Your prayer weakens the power of cursed whisperings.",
  description = function(self, stage)
    return ({
      "Your prayer nullifies cursed whisperings.",
    })[stage - self.min + 1]
  end,
}

trait['9'] = {
  name = {
    _0 = "Tough",
    _1 = "Pretty Tough",
    _2 = "Awfully Tough",
  },
  how_to_acquire = "Pushing your head against a wall makes you tougher.",
  description = function(self, stage)
    return ({
      "You are tough. [CON+3]",
      "You are pretty tough. [CON+6]",
      "You are awfully tough. [CON+9]",
    })[stage - self.min + 1]
  end,
}

trait['20'] = {
  name = {
    _0 = "Martial Artist",
    _1 = "Ken-Sei",
  },
  how_to_acquire = "You learn tricks of martial arts from fighting in streets.",
  description = function(self, stage)
    return ({
      "You know martial arts. [Martial Arts+3]",
      "You mastered martial arts. [Martial Arts+6]",
    })[stage - self.min + 1]
  end,
}

trait['12'] = {
  name = {
    _0 = "Concentration",
    _1 = "More Concentration",
  },
  how_to_acquire = "Daily meditation increases your casting skill.",
  description = function(self, stage)
    return ({
      "You concentrate while casting. [Casting+4]",
      "You concentrate more while casting. [Casting+8]",
    })[stage - self.min + 1]
  end,
}

trait['43'] = {
  name = {
    _0 = "Shield Bash",
  },
  how_to_acquire = "Mastering shield increases your chance of shield bash.",
  description = function(self, stage)
    return ({
      "You can bash with your shield more frequently.",
    })[stage - self.min + 1]
  end,
}

trait['44'] = {
  name = {
    _0 = "Gentle Face",
  },
  how_to_acquire = "Your gentle face prevents your enemies from escaping.",
  description = function(self, stage)
    return ({
      "Your attacks don't cause enemies to run.",
    })[stage - self.min + 1]
  end,
}

trait['19'] = {
  name = {
    _0 = "Ambidextrous",
    _1 = "Improved Ambidextrous",
  },
  how_to_acquire = "Years of training increases your two weapon fighting skill.",
  description = function(self, stage)
    return ({
      "You can handle multiple weapons. [Dual Wield+4]",
      "You mastered multiple weapon style. [Two Wield+8]",
    })[stage - self.min + 1]
  end,
}

trait['15'] = {
  name = {
    _0 = "Conquer Darkness",
    _1 = "Conquer Deep Darkness",
  },
  how_to_acquire = "Living in darkness makes you resistant to darkness.",
  description = function(self, stage)
    return ({
      "You don't fear darkness. [RES Darkness+]",
      "You can dance in darkness. [RES Darkness++]",
    })[stage - self.min + 1]
  end,
}

trait['18'] = {
  name = {
    _0 = "Poison Tolerance",
    _1 = "More Poison Tolerance",
  },
  how_to_acquire = "Being a taster for a noble grants you resistance to poison.",
  description = function(self, stage)
    return ({
      "You have a torerance to poison. [RES Poison+]",
      "You have a strong tolerance to poison. [RES Poison++]",
    })[stage - self.min + 1]
  end,
}

trait['16'] = {
  name = {
    _0 = "Negotiator",
    _1 = "Great Negotiator",
  },
  how_to_acquire = "Working under a trader improves your negotiation skill.",
  description = function(self, stage)
    return ({
      "You are a negotiator. [Negotiation+4]",
      "You are a great negotiator. [Negotiation+8]",
    })[stage - self.min + 1]
  end,
}

trait['17'] = {
  name = {
    _0 = "Believer",
    _1 = "Zealot",
  },
  how_to_acquire = "Training under a priest deepens your faith.",
  description = function(self, stage)
    return ({
      "You really believe in god. [Faith+4]",
      "You are a zealot. [Faith+8]",
    })[stage - self.min + 1]
  end,
}

trait['1'] = {
  name = {
    _0 = "Lucky",
    _1 = "Incredibly Lucky",
    _2 = "Goddess of Luck",
  },
  how_to_acquire = "Sighting a falling star brings you luck.",
  description = function(self, stage)
    return ({
      "You are lucky",
      "You can rely on a good dose of luck.",
      "The goddess of luck smiles on you.",
    })[stage - self.min + 1]
  end,
}

trait['2'] = {
  name = {
    _0 = "Apprentice Ascetic",
    _1 = "Journeyman Ascetic",
    _2 = "Expert Ascetic",
    _3 = "Master Ascetic",
    _4 = "Legendary Ascetic",
  },
  how_to_acquire = "Being an ascetic increases your HP.",
  description = function(self, stage)
    return ({
      "You are an apprentice of an ascetic. [HP+5%]",
      "You are a journeyman of an ascetic. [HP+10%]",
      "You are an expert of an ascetic. [HP+15%]",
      "You are a master of an ascetic. [HP+20%]",
      "You are an legendary ascetic. [HP+25%]",
    })[stage - self.min + 1]
  end,
}

trait['11'] = {
  name = {
    _0 = "Magical Gene",
    _1 = "Magical Cell",
    _2 = "Magical Blood",
    _3 = "Magic Body",
    _4 = "Magic Being",
  },
  how_to_acquire = "You gain MP by using gene manipulation.",
  description = function(self, stage)
    return ({
      "Your genes contain magic. [MP+5%]",
      "Your cells contain magica [MP+10%]",
      "Your blood contain magic [MP+15%]",
      "Your body is made of magic. [MP+20%]",
      "Magic dominats your entire body. [MP+25%",
    })[stage - self.min + 1]
  end,
}

trait['6'] = {
  name = {
    _0 = "Careful",
    _1 = "Very Careful",
  },
  how_to_acquire = "You search around carefully to spot traps.",
  description = function(self, stage)
    return ({
      "You are cautious about traps. [Detection+3]",
      "You are very cautious about traps. [Detection+6]",
    })[stage - self.min + 1]
  end,
}

trait['4'] = {
  name = {
    _0 = "Agile",
    _1 = "Very Agile",
  },
  how_to_acquire = "Chasing cats increases your speed.",
  description = function(self, stage)
    return ({
      "You can run fast. [SPD+5]",
      "You can run faster than a cat. [SPD+10]",
    })[stage - self.min + 1]
  end,
}

trait['7'] = {
  name = {
    _0 = "Stone Defense",
    _1 = "Iron Defense",
    _2 = "Steel Defense",
  },
  how_to_acquire = "You establish your own defensive style.",
  description = function(self, stage)
    return ({
      "Your defense is as hard as stone. [PV+5]",
      "Your defense is as hard as iron. [PV+10]",
      "Your defense is as hard as steel. [PV+15]",
    })[stage - self.min + 1]
  end,
}

trait['8'] = {
  name = {
    _0 = "Dodge",
    _1 = "Improved Dodge",
    _2 = "Greater Dodge",
  },
  how_to_acquire = "You learn how to dodge attacks.",
  description = function(self, stage)
    return ({
      "You can somewhat dodge enemy attacks. [DV+4]",
      "You can dodge enemy attacks. [DV+8]",
      "You can really dodge enemy attacks. [DV+12]",
    })[stage - self.min + 1]
  end,
}

trait['10'] = {
  name = {
    _0 = "Evade",
    _1 = "Improved Evade",
    _2 = "Greater Evade",
  },
  how_to_acquire = "You improve your evasion skill.",
  description = function(self, stage)
    return ({
      "You can somewhat evade enemy attacks. [Evasion+2]",
      "You can evade enemy attacks. [Evasion+4]",
      "You can really evade enemy attacks. [Evasion+6]",
    })[stage - self.min + 1]
  end,
}

trait['41'] = {
  description = function(self, stage)
    return ({
      "You have no trouble eating human flesh.",
    })[stage - self.min + 1]
  end,
  message_positive = "You are charmed by the flavor of human flesh.",
  message_negative = "You can no longer accept human flesh.",
}

trait['25'] = {
  description = function(self, stage)
    return ({
      "Your skin is collapsing. [PV-9]",
      "Your skin is fragile. [PV-6]",
      "Your skin is white. [PV-3]",
      nil,
      "Your skin is hard. [PV+3]",
      "Your skin is very hard. [PV+6]",
      "Your skin is as hard as iron. [PV+9]",
    })[stage - self.min + 1]
  end,
  message_positive = "Your skin becomes harder.",
  message_negative = "Your skin becomes pale.",
}

trait['26'] = {
  description = function(self, stage)
    return ({
      "You have terrible joint creakings. [DEX-9]",
      "You are worrying about your joint creakings. [DEX-6]",
      "Your joints creak. [DEX-3]",
      nil,
      "Your joints are flexible. [DEX+3]",
      "Your joints are very flexible. [DEX+6]",
      "Your joints are incredibly flexible. [DEX+9]",
    })[stage - self.min + 1]
  end,
  message_positive = "Your joints become flexible.",
  message_negative = "Your joints creak.",
}

trait['27'] = {
  description = function(self, stage)
    return ({
      "You constantly have an attack of anemia. [Regeneration--]",
      "You suffer from anemia. [Regeneration-]",
      nil,
      "Your wounds regenerate rapidly. [Regeneration+]",
      "Your wounds regenerate instantly. [Regeneration++]",
    })[stage - self.min + 1]
  end,
  message_positive = "Suddenly your blood become greenish!",
  message_negative = "Your metabolism slows down.",
}

trait['28'] = {
  description = function(self, stage)
    return ({
      "Your legs are broken. [SPD-15]",
      "Your legs are very twisted. [SPD-10]",
      "Your legs are twisted. [SPD-5]",
      nil,
      "You have lithe legs. [SPD+5]",
      "You have very lithe legs. [SPD+10]",
      "You have ideal legs. [SPD+15]",
    })[stage - self.min + 1]
  end,
  message_positive = "Your legs become lithe.",
  message_negative = "Your legs are twisted!",
}

trait['29'] = {
  description = function(self, stage)
    return ({
      "Your arms are just decorative. [STR-9]",
      "Your arms are very thin. [STR-6]",
      "Your arms are thin. [STR-3]",
      nil,
      "You have well-knit arms. [STR+3]",
      "You have well-muscled arms. [STR+6]",
      "You have ideal arms. [STR+9]",
    })[stage - self.min + 1]
  end,
  message_positive = "Your arms grow stronger.",
  message_negative = "Your arms become thin.",
}

trait['30'] = {
  description = function(self, stage)
    return ({
      "Everyone is frightened when you talk.[CHR-10]",
      "Your voice is hasky.[CHR-5]",
      nil,
      "Your voice is sweet.[CHR+5]",
      "Your voice charms everyone.[CHR+10]",
    })[stage - self.min + 1]
  end,
  message_positive = "Your voice becomes lovely.",
  message_negative = "Your voice becomes scary.",
}

trait['31'] = {
  description = function(self, stage)
    return ({
      "You are really stupid.[Memorization-8]",
      "You are stupid.[Memorization-4]",
      nil,
      "Your brain is mechanized.[Memorization+4]",
      "Your brain is fully mechanized.[Memorization+8]",
    })[stage - self.min + 1]
  end,
  message_positive = "Your brain is mechanized!",
  message_negative = "Your brain degenerates.",
}

trait['32'] = {
  description = function(self, stage)
    return ({
      "You have weakness to magic.[RES Magic-]",
      nil,
      "You have resistance to magic.[RES Magic+]",
    })[stage - self.min + 1]
  end,
  message_positive = "You gain resistance to magic.",
  message_negative = "You lose resistance to magic.",
}

trait['33'] = {
  description = function(self, stage)
    return ({
      "Your eardrums are thin.[RES Sound-]",
      nil,
      "Your eardrums are thick.[RES Sound+]",
    })[stage - self.min + 1]
  end,
  message_positive = "Your eardrums become thick.",
  message_negative = "Your eardrums become thin.",
}

trait['34'] = {
  description = function(self, stage)
    return ({
      "Your skin gets gooseflesh.[RES Fire-]",
      nil,
      "Your blood is boiling. [RES Fire+]",
    })[stage - self.min + 1]
  end,
  message_positive = "Your blood starts to boil.",
  message_negative = "Your skin gets gooseflesh.",
}

trait['35'] = {
  description = function(self, stage)
    return ({
      "Your skin is sheer.[RES Cold-]",
      nil,
      "Your skin is covered by frost.[RES Cold+]",
    })[stage - self.min + 1]
  end,
  message_positive = "You feel hot-headed.",
  message_negative = "You shiver.",
}

trait['36'] = {
  description = function(self, stage)
    return ({
      "You have weakness to lightning.[RES Lightning-]",
      nil,
      "You have resistance to lightning.[RES Lightning+]",
    })[stage - self.min + 1]
  end,
  message_positive = "You gain resistance to lightning.",
  message_negative = "You lose resistance to lightning.",
}

trait['37'] = {
  description = function(self, stage)
    return ({
      "You are blind in one eye. [PER-10]",
      "You are partially color-blind. [PER-5]",
      nil,
      "You have the eyes of a cat. [PER+5]",
      "You have the eyes of a hawk. [PER+10]",
    })[stage - self.min + 1]
  end,
  message_positive = "Your eyes glow.",
  message_negative = "Your sight is weakened.",
}

trait['150'] = {
  description = function(self, stage)
    return ({
      "You have strong weakness to fire.",
      "You have weakness to fire.",
      nil,
      "You have resistance to fire.",
      "You have strong resistance to fire.",
    })[stage - self.min + 1]
  end,
}

trait['151'] = {
  description = function(self, stage)
    return ({
      "You have strong weakness to cold.",
      "You have weakness to cold.",
      nil,
      "You have resistance to cold.",
      "You have strong resistance to cold.",
    })[stage - self.min + 1]
  end,
}

trait['152'] = {
  description = function(self, stage)
    return ({
      "You have strong weakness to poison.",
      "You have weakness to poison.",
      nil,
      "You have resistance to poison.",
      "You have strong resistance to poison.",
    })[stage - self.min + 1]
  end,
}

trait['155'] = {
  description = function(self, stage)
    return ({
      "You have strong weakness to darkness.",
      "You have weakness to darkness.",
      nil,
      "You have resistance to darkness.",
      "You have strong resistance to darkness.",
    })[stage - self.min + 1]
  end,
}

trait['156'] = {
  description = function(self, stage)
    return ({
      "You take less damages from the mana reaction.",
    })[stage - self.min + 1]
  end,
}

trait['160'] = {
  description = function(self, stage)
    return ({
      "You have outstanding resistances.",
    })[stage - self.min + 1]
  end,
}

trait['161'] = {
  description = function(self, stage)
    return ({
      "You can't wear equipment weight more than 1s. [DV++]",
    })[stage - self.min + 1]
  end,
}

trait['162'] = {
  description = function(self, stage)
    return ({
      "You don't feel guilty. [Karma limit -20]",
    })[stage - self.min + 1]
  end,
}

trait['169'] = {
  description = function(self, stage)
    return ({
      "You are a good man. [Karma limit +20]",
    })[stage - self.min + 1]
  end,
}

trait['163'] = {
  description = function(self, stage)
    return ({
      "Quality stuff are generated around you.",
    })[stage - self.min + 1]
  end,
}

trait['164'] = {
  description = function(self, stage)
    return ({
      "You are given physical damage reduction.",
    })[stage - self.min + 1]
  end,
}

trait['165'] = {
  description = function(self, stage)
    return ({
      "Elemental spells you cast are empowered.",
    })[stage - self.min + 1]
  end,
}

trait['166'] = {
  description = function(self, stage)
    return ({
      "You are surrounded by an aura that cures sanity.",
    })[stage - self.min + 1]
  end,
}

trait['167'] = {
  description = function(self, stage)
    return ({
      "You moe.",
    })[stage - self.min + 1]
  end,
}

trait['157'] = {
  description = function(self, stage)
    return ({
      "You won't be dim.",
    })[stage - self.min + 1]
  end,
}

trait['158'] = {
  description = function(self, stage)
    return ({
      "Your digestion is slow.",
    })[stage - self.min + 1]
  end,
}

trait['159'] = {
  description = function(self, stage)
    return ({
      "You can gather more materials.",
    })[stage - self.min + 1]
  end,
}

trait['154'] = {
  description = function(self, stage)
    return ({
      "You receive extra bonus points.",
    })[stage - self.min + 1]
  end,
}

trait['153'] = {
  description = function(self, stage)
    return ({
      "You have strong weakness to magic.",
      "You have weakness to magic.",
      nil,
      "You have resistance to magic.",
      "You have strong resistance to magic.",
    })[stage - self.min + 1]
  end,
}

trait['0'] = {
  description = function(self, stage)
    return ({
      "Your body is changing every moment.",
    })[stage - self.min + 1]
  end,
}

trait['168'] = {
  description = function(self, stage)
    return ({
      "Your body slows the Ether Disease progress.",
    })[stage - self.min + 1]
  end,
}

trait['201'] = {
  description = function(self, stage)
    return ({
      "You generate massive gravity. [Weight+30%]",
      "You generate heavy gravity. [Weight+20%]",
      "You generate gravity. [Weight+10%]",
    })[stage - self.min + 1]
  end,
  message_positive = "You wieght less.",
  message_negative = "You start to generate gravity.",
}

trait['202'] = {
  description = function(self, stage)
    return ({
      lang("あなたの顔は崩れかけている[魅力" + -3 * (4 + cdata[0].level / 5) + "]", "Your face is crumbling. [CHR" + -3 * (4 + cdata[0].level / 5) + "]"),
      lang("あなたの顔中に蕁麻疹が出ている[魅力" + -2 * (4 + cdata[0].level / 5) + "]", "Your face is ulcerate. [CHR" + -2 * (4 + cdata[0].level / 5) + "]"),
      lang("あなたの顔はただれている[魅力" + -1 * (4 + cdata[0].level / 5) + "]", "You have sores on your face. [CHR" + -1 * (4 + cdata[0].level / 5) + "]"),
    })[stage - self.min + 1]
  end,
  message_positive = "The swelling in your face decreases.",
  message_negative = "Your face is festered.",
}

trait['203'] = {
  description = function(self, stage)
    return ({
      lang("あなたの足の裏は蹄になっている[足装備不可 速度+" + (20 + cdata[0].level / 2) + "]", "Your feet transformed into hooves. [SPD+" + (20 + cdata[0].level / 2) + " Can't wear boots]"),
    })[stage - self.min + 1]
  end,
  message_positive = "Your feet become normal.",
  message_negative = "Your feet change into hooves.",
}

trait['204'] = {
  description = function(self, stage)
    return ({
      lang("あなたの目は4つある[感覚+" + (5 + cdata[0].level / 3) + " 魅力" + (5 + cdata[0].level / 3) * -1 + "]", "You have 4 eyes. [PER+" + (5 + cdata[0].level / 3) + " CHR" + (5 + cdata[0].level / 3) * -1 + "]"),
    })[stage - self.min + 1]
  end,
  message_positive = "Your eyes become normal.",
  message_negative = "Your eyes are multipling.",
}

trait['205'] = {
  description = function(self, stage)
    return ({
      lang("あなたの背中には羽がある[背中装備不可 重量-20% 速度+" + (12 + cdata[0].level / 4) + "]", "You have grown feather. [SPD+" + (12 + cdata[0].level / 4) + " Weight-20% Can't wear cloaks]"),
    })[stage - self.min + 1]
  end,
  message_positive = "Your feathers wilt.",
  message_negative = "Feathers come out from your back.",
}

trait['206'] = {
  description = function(self, stage)
    return ({
      lang("あなたの首はもの凄く太い[首装備不可 魅力" + (5 + cdata[0].level / 5) * -1 + " PV+" + (12 + cdata[0].level) + "]", "Your neck is extremely thick. [CHR" + (5 + cdata[0].level / 5) * -1 + " PV+" + (12 + cdata[0].level) + " Can't wear amulets]"),
    })[stage - self.min + 1]
  end,
  message_positive = "Your neck becomes thin.",
  message_negative = "Your neck becomes extremely thick.",
}

trait['207'] = {
  description = function(self, stage)
    return ({
      lang("あなたは殺戮に飢えている[DV" + (15 + cdata[0].level * 3 / 2) * -1 + " ダメージ修正+" + (5 + cdata[0].level * 2 / 3) + "]", "Desire for violence arises withn in you. [DV" + (15 + cdata[0].level * 3 / 2) * -1 + " Dmg bonus+" + (5 + cdata[0].level * 2 / 3) + "]"),
    })[stage - self.min + 1]
  end,
  message_positive = " A deep sense of peace fills your heart.",
  message_negative = "Hatred dominates your soul.",
}

trait['208'] = {
  description = function(self, stage)
    return ({
      lang("あなたの頭は巨大化している[耐久" + (5 + cdata[0].level / 3) * -1 + " 器用" + (4 + cdata[0].level / 4) * -1 + " 習得+" + (6 + cdata[0].level / 2) + " 意思+" + (2 + cdata[0].level / 6) + "]", "Your head has grown huge. [END" + (5 + cdata[0].level / 3) * -1 + " DEX" + (4 + cdata[0].level / 4) * -1 + " LER+" + (6 + cdata[0].level / 2) + " WIL+" + (2 + cdata[0].level / 6) + "]"),
    })[stage - self.min + 1]
  end,
  message_positive = "Your head is normal size now.",
  message_negative = "Suddenly your head become giant size.",
}

trait['209'] = {
  description = function(self, stage)
    return ({
      "Clouds of rain follow you. [Chance of rain+]",
    })[stage - self.min + 1]
  end,
  message_positive = "Clouds of rain stop following you.",
  message_negative = "Clouds of rain start to follow you.",
}

trait['210'] = {
  description = function(self, stage)
    return ({
      "You are addicted to potion. [Consume potions]",
    })[stage - self.min + 1]
  end,
  message_positive = "You are no longer addicted to potion.",
  message_negative = "Potions! More potions!! Suddenly, You become addicted to potion.",
}

trait['211'] = {
  description = function(self, stage)
    return ({
      lang("あなたは衰弱している[HP-15% 筋力" + (4 + cdata[0].level / 2) * -1 + "]", "You suffer debilitation. [HP-15% STR" + (4 + cdata[0].level / 2) * -1 + "]"),
    })[stage - self.min + 1]
  end,
  message_positive = "You become healthy again.",
  message_negative = "You become weak, very weak.",
}

trait['212'] = {
  description = function(self, stage)
    return ({
      lang("あなたは痴呆になっている[MP-15% 魔力" + (4 + cdata[0].level / 2) * -1 + "]", "You have dementia. [MP-15% MAG" + (4 + cdata[0].level / 2) * -1 + "]"),
    })[stage - self.min + 1]
  end,
  message_positive = "You become confident again.",
  message_negative = "You become feebleminded.",
}

trait['213'] = {
  description = function(self, stage)
    return ({
      lang("あなたは重い甲殻で覆われている[PV+" + (15 + cdata[0].level / 2) + " 速度" + (20 + cdata[0].level / 2) * -1 + "]", "You are covered by heavy carapace. [PV+" + (15 + cdata[0].level / 2) + " SPD" + (20 + cdata[0].level / 2) * -1 + "]"),
    })[stage - self.min + 1]
  end,
  message_positive = "Your carapace starts to break.",
  message_negative = "Heavy carapace starts to cover up your skin.",
}

trait['214'] = {
  description = function(self, stage)
    return ({
      "You are unstablizing space around you. [Random teleporation]",
    })[stage - self.min + 1]
  end,
  message_positive = "You feel steady.",
  message_negative = "You feel unstable.",
}

trait['215'] = {
  description = function(self, stage)
    return ({
      "You are a living mana battery. [Absorb mana from rods]",
    })[stage - self.min + 1]
  end,
  message_positive = "You are no longer a living mana battery.",
  message_negative = "You are a living mana battery.",
}

trait['216'] = {
  description = function(self, stage)
    return ({
      "Poison drips from your hands. [Poison potions RES Poison+]",
    })[stage - self.min + 1]
  end,
  message_positive = "Your hands are clean now.",
  message_negative = "Poison starts to drip from your hands.",
}


-- vim: et sw=2 sts=2
