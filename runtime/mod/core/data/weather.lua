local Data = ELONA.require("core.Data")

Data.define_prototype("weather")
Data.add(
   "core.weather",
   {
      sunny = {
         integer_id = 0,
      },
      etherwind = {
         integer_id = 1,
      },
      snow = {
         integer_id = 2,
      },
      rain = {
         integer_id = 3,
      },
      hard_rain = {
         integer_id = 4,
      },
   }
)
