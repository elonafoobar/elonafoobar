require './parser.rb'

Marshal.dump(Parser.new.parse(STDIN), STDOUT)
