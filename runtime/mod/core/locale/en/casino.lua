i18n.add {
   casino = {
      talk_to_dealer = "You talk to the dealer.",
      can_acquire = "There're some items you can acquire.",

      you_get = "You get {$1} {$2}{s($1)}! (Total:{$3})",
      you_lose = "You lose {$1} {$2}{s($1)}. (Total:{$3})",
      chips_left = "Casino chips left: {$1}",

      window = {
         title = "Casino <<Fortune Cookie>>",
         desc = {
            _0 = "Welcome to the casino, Fortune cookie!",
            _1 = "You can bet the casino chips you have and play some games.",
            _2 = "Enjoy your stay.",
         },
         first = {
            _0 = "Looks like you play for the first time, sir.",
            _1 = "We're offering you 10 free casino chips to try our games.",
         },

         choices = {
            blackjack = "I want to play Blackjack.",
            leave = "Later.",
         },
      },

      blackjack = {
         desc = {
            _0 = "In Blackjack, the hand with the highest total wins as long as it",
            _1 = "doesn't exceed 21. J,Q,K are counted as 10 and A is counted as 1 or 11.",
            _2 = "More bets means better rewards.",
            _3 = "How many tips would you like to bet?",
         },

         no_chips = "Sorry sir, you don't seem to have casino chips.",

         choices = {
            bet = "Bet {$1} chip{s($1)}.",
            quit = "I quit.",
         },

         game = {
            dealer = "Dealer",
            you = "   You",

            your_hand = "Your hand is {$1}.",
            dealers_hand = "The dealer's hand is {$1}.",

            result = {
               draw = "The match is a draw.",
               win = "Congratulations, you win.",
               lose = "You lose.",

               choices = {
                  next_round = "To the next round.",
                  leave = "Bah...!",
               },
            },

            bets = "Bets: {$1}",
            wins = "Wins: {$1}",

            choices = {
               stay = "Stay.",
               hit = "Hit me. (Luck)",
               cheat = "Cheat. (Dex:{$1})",
            },

            bad_feeling = "I have a bad feeling about this card...",

            cheat = {
               dialog = "Cheater!",
               text = "You are caught in cheating...",
               response = "I didn't do it!",
            },

            total_wins = "Congratulations! You've won {$1} times in a row.",
            loot = "{itemname($1)} has been added to your loot list!",
            leave = "Great.",
         },
      },
   },
}
