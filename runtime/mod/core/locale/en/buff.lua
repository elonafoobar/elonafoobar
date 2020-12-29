local I18N = ELONA.require("core.I18N")

I18N.add_data_text(
   "core.buff",
   {
      holy_shield = {
         name = "Holy Shield",
         apply = "{name($1)} begin{s($1)} to shine.",
         description = "Increases PV by {$1} /RES+ fear",
      },
      mist_of_silence = {
         name = "Mist of Silence",
         apply = "{name($1)} get{s($1)} surrounded by hazy mist.",
         description = "Inhibits casting",
      },
      regeneration = {
         name = "Regeneration",
         apply = "{name($1)} start{s($1)} to regenerate.",
         description = "Enhances regeneration",
      },
      elemental_shield = {
         name = "Elemental Shield",
         apply = "{name($1)} obtain{s($1)} resistance to element.",
         description = "RES+ fire,cold,lightning",
      },
      speed = {
         name = "Speed",
         apply = "{name($1)} speed{s($1)} up.",
         description = "Increases speed by {$1}",
      },
      slow = {
         name = "Slow",
         apply = "{name($1)} slow{s($1)} down.",
         description = "Decreases speed by {$1}",
      },
      hero = {
         name = "Hero",
         apply = "{name($1)} feel{s($1)} heroic.",
         description = "Increases STR,DEX by {$1} /RES+ fear,confusion",
      },
      mist_of_frailness = {
         name = "Mist of Frailness",
         apply = "{name($1)} feel{s($1)} weak.",
         description = "Halves DV and PV",
      },
      element_scar = {
         name = "Element Scar",
         apply = "{name($1)} lose{s($1)} resistance to element.",
         description = "RES- fire,cold,lightning",
      },
      holy_veil = {
         name = "Holy Veil",
         apply = "{name($1)} receive{s($1)} holy protection.",
         description = "Grants hex protection(power:{$1})",
      },
      nightmare = {
         name = "Nightmare",
         apply = "{name($1)} start{s($1)} to suffer.",
         description = "RES- mind,nerve",
      },
      divine_wisdom = {
         name = "Divine Wisdom",
         apply = "{name($1)} start{s($1)} to think clearly.",
         description = "Increases LER,MAG by {$1}, literacy skill by {$2}",
      },
      punishment = {
         name = "Punishment",
         apply = "{name($1)} incur{s($1)} the wrath of God.",
         description = "Decreases speed by {$1}, PV by {$2}%",
      },
      lulwys_trick = {
         name = "Lulwy's Trick",
         apply = "{name($1)} repeat{s($1)} the name of Lulwy.",
         description = "Increases speed by {$1}",
      },
      incognito = {
         name = "Incognito",
         apply = "{name($1)} start{s($1)} to disguise.",
         description = "Grants new identity",
      },
      death_word = {
         name = "Death Word",
         apply = "{name($1)} receive{s($1)} death verdict.",
         description = "Guaranteed death when the hex ends",
      },
      boost = {
         name = "Boost",
         apply = "{name($1)} gain{s($1)} massive power.",
         description = "Increases speed by {$1}/Boosts physical attributes",
      },
      contingency = {
         name = "Contingency",
         apply = "{name($1)} set{s($1)} up contracts with the Reaper.",
         description = "{$1}% chances taking a lethal damage heals you instead",
      },
      luck = {
         name = "Luck",
         apply = "{name($1)} feel{s($1)} very lucky today!",
         description = "Increases luck by {$1}.",
      },
      grow_strength = {
         name = "Grow Strength",
         apply = "{name($1)} feel{s($1)} rapid STR growth.",
         description = "Increases the growth rate Strength by {$1}",
      },
      grow_constitution = {
         name = "Grow Constitution",
         apply = "{name($1)} feel{s($1)} rapid CON growth.",
         description = "Increases the growth rate Constitution by {$1}",
      },
      grow_dexterity = {
         name = "Grow Dexterity",
         apply = "{name($1)} feel{s($1)} rapid DEX growth.",
         description = "Increases the growth rate Dexterity by {$1}",
      },
      grow_perception = {
         name = "Grow Perception",
         apply = "{name($1)} feel{s($1)} rapid PER growth.",
         description = "Increases the growth rate Perception by {$1}",
      },
      grow_learning = {
         name = "Grow Learning",
         apply = "{name($1)} feel{s($1)} rapid LER growth.",
         description = "Increases the growth rate Learning by {$1}",
      },
      grow_will = {
         name = "Grow Will",
         apply = "{name($1)} feel{s($1)} rapid WIL growth.",
         description = "Increases the growth rate Will by {$1}",
      },
      grow_magic = {
         name = "Grow Magic",
         apply = "{name($1)} feel{s($1)} rapid MAG growth.",
         description = "Increases the growth rate Magic by {$1}",
      },
      grow_charisma = {
         name = "Grow Charisma",
         apply = "{name($1)} feel{s($1)} rapid CHR growth.",
         description = "Increases the growth rate Charisma by {$1}",
      },
      grow_speed = {
         name = "Grow Speed",
         apply = "{name($1)} feel{s($1)} rapid SPD growth.",
         description = "Increases the growth rate Speed by {$1}",
      },
      grow_luck = {
         name = "Grow Luck",
         apply = "{name($1)} feel{s($1)} rapid LCK growth.",
         description = "Increases the growth rate Luck by {$1}",
      },
   }
)
