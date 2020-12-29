local I18N = require("core.I18N")

I18N.add {
   net = {
      failed_to_send = "Failed to send a message.",
      failed_to_receive = "Failed to receive messages.",

      chat = {
         wait_more = "You think you should wait a little more.",
         message = '"{$1}"',
         sent_message = "{$1} {$2} says, {$3}",
      },

      death = {
         sent_message = "{$1} {$2} {$3} in {$4} {$5}",
      },

      wish = {
         sent_message = "{$1} {$2} goes wild with joy, {$3} {$4}",
      },

      news = {
         bomb = "[Palmia Times {$1}] Atomic Bomb Explosion in {$4}",
         void = "[Palmia Times {$1}] {$2} {$3} Reaches Void {$4}",
         ehekatl = "[Palmia Times {$1}] {$2} {$3} Gets Statue of Ehekatl",
         fire = "[Palmia Times {$1}] Noyel Big Fire, Someone Releases Giant",
      },

      alias = {
         message = "Your favorite alias♪1",

         title = "Voting Box",
         hint = "Enter [Vote] ",
         choice = "Choice",
         vote = "Vote",

         submit = "Submit your alias.",
         cannot_vote_until = "You can't vote until {$1}.",
         prompt = "Which one do you want to vote?",

         rank = "{ordinal($1)}",
         selected = "",

         ok = "Ok",
         need_to_wait = "You need to wait before submitting a new vote.",
         i_like = "\"I like {$1}!\"",
         you_vote = "You vote.",
      },
   },
}
