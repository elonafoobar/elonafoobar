require 'set'
require 'fileutils'


variables = []
variable_declarations = {}

File.open('../variables.hpp').each_line(chomp: true) do |line|
  if line =~ /^inline/
    name = line.match(/.* (\w+);/)[1]
    if name.include?('_at_')
      variables << name
      variable_declarations[name] = line.sub('inline ', '')
    end
  elsif !variables.empty?
    break
  end
end


variables = variables.to_set


variable_table = {}



Dir.glob('../*.cpp').each do |cpp|
  function = '<unknown>'
  prev = ''
  File.open(cpp).each_line do |line|
    case line
    when /^{$/
      function = prev
    when /^}$/
      function = '<unknown>'
    else
      line.gsub(/\b\w+\b/).each do |word|
        if variables.include?(word)
          if variable_table.has_key?(word)
            if variable_table[word] != function
              variable_table[word] = ''
            end
          else
            variable_table[word] = function
          end
        end
      end
    end
    prev = line
  end
end


variable_table.reject! {|k, v| v.empty?}


# variable_table.each do |k, v|
#   puts "#{k} #{v}"
# end



Dir.glob('../*.cpp').each do |cpp|
  function = '<unknown>'
  prev = ''
  function_first_line = false
  File.open(cpp + '.tmp', 'w') do |out|
    File.open(cpp).each_line do |line|
      case line
      when /^{$/
        function = prev
        function_first_line = true
      when /^}$/
        function = '<unknown>'
      else
        if function_first_line
          function_first_line = false
          variable_table.each do |k, v|
            if v == function
              decl = variable_declarations[k]
              if decl.start_with?('int')
                decl = decl[0..-2] + ' = 0;'
              end
              out.puts '    ' + decl
            end
          end
        end
      end
      out.puts line
      prev = line
    end
  end

  FileUtils.mv(cpp + '.tmp', cpp)
end



File.open('../variables.hpp.tmp', 'w') do |out|
  File.open('../variables.hpp').each_line do |line|
    if line =~ /^inline/ && (match_data = line.match(/.* (\w+);/))
      name = match_data[1]
      if name.include?('_at_') && variable_table.has_key?(name)
        next
      end
    end
    out.puts line
  end
end

FileUtils.mv('../variables.hpp.tmp', '../variables.hpp')
