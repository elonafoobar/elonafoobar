require 'set'
require 'fileutils'


variables = Set.new
variable_declarations = {}

File.open('../variables.hpp').each_line(chomp: true) do |line|
  if line =~ /^inline/
    name = line.match(/.* (\w+);/)[1]
    variables << name
    variable_declarations[name] = line.sub('inline ', '')
  elsif !variables.empty?
    break
  end
end


variable_table = {}


Dir.glob('../*.cpp').each do |cpp|
  File.open(cpp).each_line do |line|
    line.gsub(/\b\w+\b/).each do |word|
      if variables.include?(word)
        if variable_table.has_key?(word)
          if variable_table[word] != cpp
            variable_table[word] = ''
          end
        else
          variable_table[word] = cpp
        end
      end
    end
  end
end


variable_table.reject! {|k, v| v.empty?}


Dir.glob('../*.cpp').each do |cpp|
  namespace_first_line = false
  File.open(cpp + '.tmp', 'w') do |out|
    prev = ''
    File.open(cpp).each_line do |line|
      case line
      when /^{$/
        if prev.start_with?('namespace elona')
          namespace_first_line = true
        end
      else
        if namespace_first_line
          namespace_first_line = false
          variable_table.each do |k, v|
            if v == cpp
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
      if variable_table.has_key?(name)
        next
      end
    end
    out.puts line
  end
end

FileUtils.mv('../variables.hpp.tmp', '../variables.hpp')
