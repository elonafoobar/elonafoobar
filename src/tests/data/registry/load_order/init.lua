local Data = ELONA.require("core.Data")

print('----- init -----')

do
   local spell = Data.get('core.ability', 'core.healing')
   print(spell)
   local spells = Data.get_table('core.ability')
   print(spells)
end

print('----------')

-- do
--    local spell = data.raw['core.ability']['core.healing']
--    print(spell)
--    local spells = data.raw['core.ability']
--    print(spells)
-- end
