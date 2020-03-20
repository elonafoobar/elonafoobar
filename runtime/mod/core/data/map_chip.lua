local function make_atlas(atlas_index)
   local atlas = {}
   for y=0,24 do
      for x=0,33 do
         local chip_index = x + y * 33
         atlas[chip_index] = {
            legacy_id = chip_index,
            atlas = atlas_index,
            source = {
               x = x * 48,
               y = y * 48
            }
         }
         if chip_index == 824 then
            break
         end
      end
   end
   atlas[#atlas+1] = atlas[0]
   atlas[0] = nil

   return atlas
end

local function convert_atlas(base, atlas_index)
   local atlas = {}
   for i, v in ipairs(base) do
      if i == #base then
         i = 0
      end
      atlas[tostring(atlas_index).."_"..tostring(i)] = v
   end
   return atlas
end

ELONA.data:define_prototype("map_chip")

--
-- Atlas 0
--
do
   local atlas_0 = make_atlas(0)

   atlas_0[233].offset_top = 0
   atlas_0[233].offset_bottom = 0
   for i=26,32 do
      atlas_0[i].kind = 4
   end
   atlas_0[568].kind = 4
   atlas_0[569].kind = 4
   atlas_0[570].kind = 4
   for i=99,131 do
      atlas_0[i].kind = 7
   end
   for i=165,197 do
      atlas_0[i].kind = 8
   end
   for i=198,230 do
      atlas_0[i].kind = 4
   end
   for i=594,598 do
      atlas_0[i].kind = 7
   end
   for i=599,603 do
      atlas_0[i].kind = 8
   end
   for i=107,118 do
      atlas_0[i].kind2 = 9
   end
   for i=173,184 do
      atlas_0[i].kind2 = 9
   end
   for i=206,217 do
      atlas_0[i].kind2 = 9
   end
   atlas_0[604].kind = 10
   for i=605,616 do
      atlas_0[i].kind = 10
      atlas_0[i].kind2 = 9
   end
   for i=396,824 do
      atlas_0[i].effect = 5
   end
   for i=264,296 do
      atlas_0[i].effect = 4
   end
   atlas_0[135].offset_top = 8
   atlas_0[137].offset_top = 16
   atlas_0[140].offset_top = 6
   atlas_0[145].offset_top = 16
   atlas_0[149].offset_top = 16

   for i=99,129 do
      atlas_0[i].is_feat = true
   end

   for i=231,261 do
      atlas_0[i].is_feat = true
   end

   ELONA.data:add("core.map_chip", convert_atlas(atlas_0, 0))
end

--
-- Atlas 1
--
do
   local atlas_1 = make_atlas(1)

   for i=396,824 do
      atlas_1[i].effect = 5
   end
   atlas_1[233].offset_top = 56
   atlas_1[233].offset_bottom = 48
   atlas_1[594].effect = 4
   atlas_1[628].effect = 4
   atlas_1[637].effect = 4
   atlas_1[641].effect = 4
   atlas_1[733].effect = 4
   for i=45,60 do
      atlas_1[i].kind = 4
   end
   atlas_1[82].kind = 4
   atlas_1[83].kind = 4
   atlas_1[84].kind = 4
   for i=462,527 do
      atlas_1[i].wall_kind = 1
      atlas_1[i - 66].wall_kind = 1
   end
   for i=462,494 do
      atlas_1[i].wall_kind = 2
      atlas_1[i - 66].wall_kind = 2
   end
   atlas_1[29].kind = 1
   atlas_1[30].kind = 2
   atlas_1[31].kind = 2
   atlas_1[464].kind = 6
   atlas_1[550].anime_frame = 2
   atlas_1[550].wall_kind = 1
   atlas_1[165].kind = 3
   atlas_1[165].anime_frame = 3
   atlas_1[168].kind = 3
   atlas_1[168].anime_frame = 3
   atlas_1[171].kind = 3
   atlas_1[171].kind2 = 5
   atlas_1[171].anime_frame = 3
   atlas_1[594].kind = 3
   atlas_1[594].anime_frame = 3

   for i=726,756 do
      atlas_1[i].is_feat = true
   end

   for i=231,261 do
      atlas_1[i].is_feat = true
   end

   ELONA.data:add("core.map_chip", convert_atlas(atlas_1, 1))
end

--
-- Atlas 2
--
do
   local atlas_2 = make_atlas(2)

   for j=0,10 do
      for i=0,12 do
         atlas_2[j * 33 + i + 20].kind = 4
      end
   end
   for i=33,65 do
      atlas_2[i].kind = 4
   end
   for i=396,824 do
      atlas_2[i].effect = 5
   end
   atlas_2[233].offset_top = 56
   atlas_2[233].offset_bottom = 48
   atlas_2[594].effect = 4
   for i=462,527 do
      atlas_2[i].wall_kind = 1
      atlas_2[i - 66].wall_kind = 1
   end
   for i=462,494 do
      atlas_2[i].wall_kind = 2
      atlas_2[i - 66].wall_kind = 2
   end
   atlas_2[550].anime_frame = 2
   atlas_2[550].wall_kind = 1
   atlas_2[165].kind = 3
   atlas_2[165].anime_frame = 3
   atlas_2[168].kind = 3
   atlas_2[168].anime_frame = 3
   atlas_2[171].kind = 3
   atlas_2[171].kind2 = 5
   atlas_2[171].anime_frame = 3
   atlas_2[594].kind = 3
   atlas_2[594].anime_frame = 3
   atlas_2[476].wall_kind = 0
   atlas_2[509].wall_kind = 0

   ELONA.data:add("core.map_chip", convert_atlas(atlas_2, 2))
end
