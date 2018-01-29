ADATA = {
  0  => 'category',
  1  => 'x',
  2  => 'y',
  6  => 'enteredDeepestLevel',
  10  => 'deepestLevel',
  16  => 'type',
  17  => 'difficulty',
  20  => 'beatedLordOfDungeon',
  22  => 'arenaCount',
  23  => 'petArenaCount',
  27  => 'rumbleTime',
}


ADATA.each do |key, value|
  # E.g., "cdata(0, 0)" => "cState(0)"
  puts "sed -i '' -e 's/adata(#{key}, /a#{value[0].upcase + value[1..-1]}(/g' ../../start.d"
end
