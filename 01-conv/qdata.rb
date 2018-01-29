QDATA = {
  0 => 'randomSeed',
  1 => 'map',
  2 => 'timeToWithdraw',
  3 => 'type',
  5 => 'difficulty',
  6 => 'gold',
  7 => 'reward',
  8 => 'flag',
  9 => 'deadline',
  12 => 'param1',
  13 => 'param2',
}


QDATA.each do |key, value|
  # E.g., "cdata(0, 0)" => "cState(0)"
  puts "sed -i '' -e 's/qdata(#{key}, /q#{value[0].upcase + value[1..-1]}(/g' ../../start.d"
end
