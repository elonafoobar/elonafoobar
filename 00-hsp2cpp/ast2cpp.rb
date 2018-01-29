require './parser.rb'
require './astoptimizer.rb'
require './astprinter.rb'


ast = Marshal.load(STDIN)
opt = ASTOptimizer.new
opt.visit(ast)
ASTPrinter.new(opt.label_table, opt.call_type).visit(ast)
