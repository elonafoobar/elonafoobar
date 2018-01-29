require './parser.rb'
require './flowanalyzer.rb'
require './gotoanalyzer.rb'
require './gotosimplifier.rb'



ast = Marshal.load(STDIN)


# Delete dead code
flow_analyzer = FlowAnalyzer.new
flow_analyzer.visit(ast)
function_table = {}
ast.functions.each do |func|
  if func.mark != MARK_WHITE
    function_table[func.name] = func
  end
end


g = GotoAnalyzer.new
function_table.each_value(&g.method(:visit))


internal_labels = {}
simplified_labels = {}
g.label_table.each do |k, v|
  next if function_table.has_key?(k)
  if v.called.size == 1 && v.called.first == v.defined
    internal_labels[k] = 0 # 0 is dummy data.
  elsif k.length > :label_xxxx.length && k.to_s.end_with?('1')
    simplified_labels[k] = v
  end
end



s = GotoSimplifier.new(simplified_labels, internal_labels, function_table)
function_table.each_value(&s.method(:visit))


# g2 = GotoAnalyzer.new
# function_table.each_value(&g2.method(:visit))
#
#
# File.open('txt', 'w') do |f|
#   g2.label_table.each do |k, v|
#     next if function_table.has_key?(k)
#     next if v.called.empty?
#
#     if v.called.size != 1 || v.called.first != v.defined
#       f.puts "#{k}:"
#       f.puts "    defined at #{v.defined || '<unknown>'}"
#       f.puts "    called by #{v.called.join(', ')}"
#     end
#   end
# end





# Replace 'var' parameters
function_table.each do |name, func|
  if %i[getinheritance item_separate route_info].include?(name)
    # int&
    # getinheritance(int, array, var)
    # item_separate(var)
    # route_info(var, var, int)
    func.parameters.each do |param|
      if param.type == :var
        param.type = :elona_ref_type_int
      end
    end
  else
    # std::string&
    func.parameters.each do |param|
      if param.type == :var
        param.type = :elona_ref_type_str
      end
    end
  end
end



Marshal.dump(function_table, STDOUT)
