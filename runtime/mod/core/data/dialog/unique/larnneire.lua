return {
   root = "core.talk.unique.larnneire",
   nodes = {
      __start = {
         text = {
            {"dialog"}
         },
         choices = {
            {"mission", "choices.mission"},
            {"north_tyris", "choices.north_tyris"},
            {"fairy_tale", "choices.fairy_tale"},
            {"__END__", "__BYE__"}
         }
      },
      fairy_tale = {
         text = {
            {"fairy_tale._0"},
            {"fairy_tale._1"},
            {"fairy_tale._2"},
            {"fairy_tale._3"},
            {"fairy_tale._4"},
            {"fairy_tale._5"},
         },
         choices = {{"__start", "__MORE__"}}
      },
      north_tyris = {
         text = {
            {"north_tyris._0"},
            {"north_tyris._1"},
         },
         choices = {{"__start", "__MORE__"}}
      },
      mission = {
         text = {
            {"mission"},
         },
         choices = {{"__start", "__MORE__"}}
      }
   }
}
