local Data = require("core.Data")

Data.define_prototype("activity")

Data.add(
   "core.activity",
   {
      eat = {
         integer_id = 1,
      },
      read = {
         integer_id = 2,
      },
      travel = {
         integer_id = 3,
      },
      sleep = {
         integer_id = 4,
      },
      dig_wall = {
         integer_id = 5,
      },
      perform = {
         integer_id = 6,
      },
      fish = {
         integer_id = 7,
      },
      search_material = {
         integer_id = 8,
      },
      dig_around = {
         integer_id = 9,
      },
      -- Activity `integer_id` 10 is used for several purposes in vanilla. In foobar, it is separated to each activity.
      sleep = {
         -- integer_id = 10, gdata(91) = 100
      },
      build_shelter = {
         -- integer_id = 10, gdata(91) = 101
      },
      enter_shelter = {
         -- integer_id = 10, gdata(91) = 102
      },
      harvest = {
         -- integer_id = 10, gdata(91) = 103
      },
      study = {
         -- integer_id = 10, gdata(91) = 104
      },
      steal = {
         -- integer_id = 10, gdata(91) = 105
      },
      sex = {
         integer_id = 11,
      },
      blend = {
         integer_id = 12,
      },
   }
)
