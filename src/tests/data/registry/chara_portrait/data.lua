local Data = ELONA.require("core.Data")

Data.add(
   "core.chara",
   {
      no_portrait = {
         integer_id = 9999,
         portrait = "",
      },
      random_portrait = {
         integer_id = 9998,
         portrait = "__random__",
      },
      undefined_portrait = {
         integer_id = 9997,
         portrait = "john_doe",
      },
      loyter_portrait = {
         integer_id = 9996,
         portrait = "core.loyter",
      },
      male_portrait_only = {
         integer_id = 9995,
         portrait = {
            male = "male_portrait_only",
         },
      },
      female_portrait_only = {
         integer_id = 9994,
         portrait = {
            female = "female_portrait_only",
         },
      },
      both_portrait = {
         integer_id = 9993,
         portrait = {
            male = "male_portrait",
            female = "female_portrait",
         },
      },
   }
)
