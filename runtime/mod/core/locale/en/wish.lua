local I18N = require("core.I18N")

I18N.add {
   wish = {
      what_do_you_wish_for = "What do you wish for? ",
      your_wish = "\"{$1}!!\"",

      it_is_sold_out = "It's sold out.",
      something_appears = "{itemname($1)} appear{s($1)}.",
      something_appears_from_nowhere = "{itemname($1)} appear{s($1)} from nowhere.",
      you_learn_skill = "You learn {$1}!",
      your_skill_improves = "Your {$1} skill improves!",

      wish_gold = "Lots of gold pieces appear.",
      wish_platinum = "Platinum pieces appear.",
      wish_small_medal = "Some small coins appear.",
      wish_sex = "{name($1)} become {$2}!",
      wish_youth = "A typical wish.",
      wish_man_inside = "There's no God inside.",
      wish_god_inside = "There's no man inside.",
      wish_ehekatl = "\"Meeewmew!\"",
      wish_lulwy = "\"You dare to call my name?\"",
      wish_opatos = "\"Under construction.\"",
      wish_kumiromi = "\"Under construction.\"",
      wish_mani = "\"Under construction.\"",
      wish_death = "If you wish so...",
      wish_redemption = {
         you_are_not_a_sinner = "You aren't a sinner.",
         what_a_convenient_wish = "What a convenient wish!",
      },
      wish_alias = {
         impossible = "*laugh*",
         what_is_your_new_alias = "What's your new alias?",
         new_alias = "You will be known as <{$1}>.",
         no_change = "What a waste of a wish!",
      },

      general_wish = {
         skill = "skill",
         item = "item",
         card = "card",
         summon = "summon",
         figure = "figure",
      },

      special_wish = {
         god_inside = "god inside",
         man_inside = "man inside",
         ehekatl = "ehekatl",
         lulwy = "lulwy",
         opatos = "opatos",
         kumiromi = "kumiromi",
         mani = "mani",
         youth = {"youth", "age", "beauty"},
         alias = {"aka", "title", "name", "alias"},
         sex = "sex",
         redemption = {"redemption", "atonement"},
         death = "death",
         ally = {"friend", "company", "ally"},
         gold = {"money", "gold", "wealth", "fortune"},
         small_medal = {"coin", "medal", "small coin", "small medal"},
         platinum = {"platina", "platinum"},
         fame = "fame",
      },
   },
}
