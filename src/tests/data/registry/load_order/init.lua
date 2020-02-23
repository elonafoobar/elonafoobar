local Data = Elona.game.Data

print('----- init -----')

do
   local spell = Data.get('core.ability', 'elona.healing')
   print(spell)
   local spells = Data.get_table('core.ability')
   print(spells)
end

print('----------')

-- do
--    local spell = data.raw['core.ability']['elona.healing']
--    print(spell)
--    local spells = data.raw['core.ability']
--    print(spells)
-- end
