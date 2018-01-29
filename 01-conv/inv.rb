INV = {
  0 => 'stack',
  1 => 'value',
  2 => 'image',
  3 => 'id',
  4 => 'quality',
  5 => 'x',
  6 => 'y',
  7 => 'weight',
  8 => 'identificationState',
  9 => 'count',
  10 => 'diceRoll',
  11 => 'diceSide',
  12 => 'damageBonus',
  13 => 'hitBonus',
  14 => 'DV',
  15 => 'PV',
  16 => 'skillId',
  17 => 'cursedState',
  18 => 'equipment',
  19 => 'function',
  20 => 'enhancementValue',
  21 => 'ownState',
  22 => 'color',
  23 => 'subName',
  24 => 'material',
  25 => 'param1',
  26 => 'param2',
  27 => 'param3',
  28 => 'param4',
  29 => 'difficultyOfIdentification',
}


INV.each do |key, value|
  # E.g., "cdata(0, 0)" => "cState(0)"
  puts "sed -i '' -e 's/inv(#{key}, /i#{value[0].upcase + value[1..-1]}(/g' ../../start.d"
end
