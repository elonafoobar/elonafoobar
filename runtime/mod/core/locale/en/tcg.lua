local I18N = require("core.I18N")

I18N.add {
   tcg = {
      card = {
         creature = "Creature",
         race = "Race",
         land = "Land",
         spell = "Spell",
         domain = "Domain",
         rare = "Rare",
         skill = "Skill",
      },

      end_main_phase = "End your main phase.",
      no_blocker = "No blocker.",

      sacrifice = {
         you = "You sacrifice the card.",
         opponent = "The opponent sacrifices the card.",
      },

      ref = {
         choose_one_card = "Player chooses and receives 1 card from his deck.",
         draws_two_cards = "Player draws 2 cards.",
         return_creature = "Return target creature to its owner's hand.",
      },

      put = {
         field_full = "Your field is full.",
         not_enough_mana = "You don't have enough mana.",
      },

      domain = {
         lulwy = "Lulwy",
         kumiromi = "Kumiromi",
         yacatect = "Yacatect",
         jure = "Jure",
         mani = "etc",
      },

      deck = {
         color = {
            white = "White",
            blue = "Blue",
            silver = "Silver",
            red = "Red",
            black = "Black",
         },

         name = "{$1} Deck",
         new = "New",

         choices = {
            edit = "Edit Deck",
            set_as_main = "Set as Main Deck",
         },
      },

      select = {
         hint = " [Change Filter]  Enter [Select]  Cancel [Exit]",
      },

      menu = {
         list = "List",
         deck = "Deck",

         save_and_exit = "Save & Exit",
         just_exit = "Just Exit",
      },

      card_not_available = "The card isn't available in this version.",

      action = {
         put = "UP: Put the card.",
         sacrifice = "Down: Sacrifice the card.",
         declare_attack = "UP: Declare an attack.",
         block = "UP: Block.",
         use_skill = "ENTER: Use the skill.",
         no_action_available = "There is no action available.",
         surrender = "Surrender",
      },
   },
}
