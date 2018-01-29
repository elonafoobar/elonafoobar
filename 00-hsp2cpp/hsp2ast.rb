require './parser.rb'
require './astoptimizer.rb'
require './astprinter.rb'


Marshal.dump(Parser.new.parse(STDIN), STDOUT)
