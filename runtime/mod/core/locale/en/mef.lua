local I18N = ELONA.require("core.I18N")

I18N.add {
   mef = {
      bomb_counter = "*{$1}*",

      melts = "{name($1)} melt{s($1)}.",
      is_burnt = "{name($1)} {is($1)} burnt.",
      steps_in_pool = "{name($1)} step{s($1)} in the pool.",
      destroys_cobweb = "{name($1)} destroy{s($1)} the cobweb.",
      is_caught_in_cobweb = "{name($1)} {is($1)} caught in a cobweb.",
      attacks_illusion_in_mist = "{name($1)} attack{s($1)} an illusion in the mist.",
   },
}
