require './ast.rb'
require './simpletypeanalyzer.rb'
require './statanalyzer.rb'
require './typetable.rb'
require './astprinter.rb'

function_table = Marshal.load(STDIN)


type_table = TypeTable.new

invalid_return = []

ta1 = SimpleTypeAnalyzer.new(type_table, invalid_return)
function_table.each_value(&ta1.method(:visit))
invalid_return.uniq!


ta2 = SimpleTypeAnalyzer.new(type_table, invalid_return)
function_table.each_value(&ta2.method(:visit))
invalid_return.uniq!


File.open('variables.hpp', 'w') do |file|
  file.puts 'namespace elona'
  file.puts '{'
  type_table.dump_ctype(file)
  file.puts '}'
end

# type_table.dump(STDOUT)



function_table[:_fdialog] = nil
function_table[:rm_crlf] = nil
function_table[:talk_conv] = nil


sta = StatAnalyzer.new
function_table.each_value(&sta.method(:visit))



p = ASTPrinter.new(type_table, invalid_return, sta.stat_return)
function_table.each_value(&p.method(:visit))
