c = false
l = false
buf = []

STDIN.each_line.with_index do |line, m|
  if line =~ /^:label_/ && !l
    l = true
    buf << line
    next
  elsif line == "{\n"
    c = true
  elsif line == "}\n"
    if !c && l
      buf[0] = 'function ' + buf[0].chomp[1..-2] + "()\n{"
      puts buf
      buf = []
    else
      puts buf
      buf = []
    end
    l = false
    c = false
    puts '}'
    next
  end

  if buf.empty?
    puts line
  else
    buf << line
  end
end

puts buf
