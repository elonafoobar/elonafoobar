require './ast.rb'
require './ctype.rb'



class ASTPrinter < ASTVisitor
  def initialize(type_table, invalid_return, stat_return)
    @type_table = type_table
    @invalid_return = invalid_return
    @stat_return = stat_return
    @context = nil
    @indent = 0
    @in_repeat = 0
    @operator_precedence_stack = [0]
    @cnt = 'cnt'
  end

  def print_(msg)
    print '    ' * @indent
    print msg
  end

  def puts_(msg)
    print '    ' * @indent
    puts msg
  end

  def visit_functiondefinition(ast)
    @context = ast

    # print 'function ' + ast.name.to_s + '('
    return_type = @type_table[ast.name]&.return_type
    unless return_type&.valid?(as_return_type: true)
      return_type = BasicType::VOID
    end
    print "#{return_type.to_ctype} #{ast.name}("
    ast.parameters.each_with_index do |param, i|
      visit(param)
      if i != ast.parameters.length - 1
        print ', '
      end
    end
    puts ')'
    puts '{'
    visit(ast.block)
    puts '}'
  end

  def visit_parameter(ast)
    case ast.type
    when :str
      print 'const std::string&'
    when :elona_ref_type_int
      print 'int&'
    when :elona_ref_type_str
      print 'std::string&'
    else
      print ast.type
    end
    if ast.name
      print ' ' + ast.name.to_s
    end
  end

  def visit_repeatstatement(ast)
    @in_repeat += 1

    # @n ||= 0
    # n = @n
    # @n += 1
    # cnt_save = "cnt_save_#{n}"
    # i = "i_#{n}"
    # e = "end_#{n}"
    #
    # prev_cnt = @cnt
    # @cnt = i
    #
    # # { int cnt_save_N = cnt; int i_N = start; for (int end_N = i_N + (times); (cnt = i_N), i_N < end_N; ++i_N) {
    # # } cnt = cnt_save_N; }
    # print_ "{ int #{cnt_save} = cnt; int #{i} = "
    # if ast.times
    #   if ast.start
    #     visit(ast.start)
    #   else
    #     print 0
    #   end
    #   print "; for (int #{e} = #{i} + ("
    #   visit(ast.times)
    #   print "); (cnt = #{i}), #{i} < #{e}; ++#{i})"
    # else
    #   # { int cnt_save_N = cnt; int i_N = 0; for (; (cnt = i_N), true; ++i_N) {
    #   # } cnt = cnt_save_N; }
    #   print "0; for (; (cnt = #{i}), true; ++#{i})"
    # end
    # puts ' {'
    # visit(ast.block)
    # puts_ "} cnt = #{cnt_save}; }"
    #
    # @cnt = prev_cnt


    # { int cnt = 0; for (int cnt_end = cnt + times; cnt < cnt_end; ++cnt) {
    # } }
    # { int cnt = 0; for (; ; ++cnt) {
    # } }
    print_ "{ int cnt = "
    if ast.times
      if ast.start
        visit(ast.start)
      else
        print 0
      end
      print "; for (int cnt_end = cnt + ("
      visit(ast.times)
      print "); cnt < cnt_end; ++cnt)"
    else
      print "0; for (; ; ++cnt)"
    end
    puts ' {'
    visit(ast.block)
    puts_ "} }"
    
    # @cnt = prev_cnt

    @in_repeat -= 1
  end

  def visit_ifstatement(ast)
    print_ 'if ('
    visit(ast.condition)
    puts ') {'
    visit(ast.true_block)
    if ast.false_block
      puts_ '} else {'
      visit(ast.false_block)
    end
    puts_ '}'
  end

  def visit_block(ast)
    @indent += 1
    ast.statements.each(&method(:visit))
    @indent -= 1
  end

  def visit_expressionstatement(ast)
    print_ ''
    visit(ast.expression)
    puts ';'
  end

  def visit_eventstatement(ast)
    # print_ ast.event.to_s + ' '
    # save_indent = @indent
    # @indent = 0
    # visit(ast.statement)
    # @indent = save_indent
  end

  def visit_labeldeclaration(ast)
    visit(ast.label)
    puts ':'
  end

  def visit_label(ast)
    print ast.name.to_s
  end

  def visit_gotostatement(ast)
    print_ 'goto '
    visit(ast.label)
    puts ';'
  end

  def visit_continuestatement(ast)
    puts_ 'continue;'
  end

  def visit_breakstatement(ast)
    puts_ 'break;'
  end

  def visit_returnstatement(ast)
    if @context.name == :label_2654
      if ast.return_value
        if StringLiteralAST === ast.return_value
          print_ 'refstr = '
          visit(ast.return_value)
          puts ';'
          print_ 'return 0'
        else
          print_ 'return '
          visit(ast.return_value)
        end
      else
        print_ 'return 0'
      end
      puts ';'
    else
      if ast.return_value
        if @type_table[@context.name]&.return_type == BasicType::INT
          print_ 'stat = '
          visit(ast.return_value)
          print '; return stat'
        else
          print_ 'return '
          visit(ast.return_value)
        end
      elsif @invalid_return.include?(@context.name)
        print_ 'stat = 0; return stat'
      else
        print_ 'return'
      end
      puts ';'
    end
  end

  OPERATORS = {
    op__and:                '&&',
    op__or:                 '||',
    op__plus:               '+',
    op__minus:              '-',
    op__multiplication:     '*',
    op__division:           '/',
    op__modulo:             '%',
    op__shift_l:            '<<',
    op__equal:              '==',
    op__not_equal:          '!=',
    op__greater_than:       '>',
    op__greater_than_equal: '>=',
    op__less_than:          '<',
    op__less_than_equal:    '<=',
  }

  def operator_precedence(op)
    case op
    when :op__or; 100
    when :op__and; 200
    when :op__equal; 300
    when :op__not_equal; 300
    when :op__greater_than; 400
    when :op__greater_than_equal; 400
    when :op__less_than; 400
    when :op__less_than_equal; 400
    when :op__shift_l; 500
    when :op__plus; 600
    when :op__minus; 600
    when :op__multiplication; 700
    when :op__division; 700
    when :op__modulo; 700
    else
      raise op.to_s
    end
  end

  def visit_functioncall(ast)
    if ast.function.name == :uop__minus
      @operator_precedence_stack << 9999 # highest precedence
      print '-'
      visit(ast.arguments.first)
      @operator_precedence_stack.pop
    elsif op_str = OPERATORS[ast.function.name]
      op = ast.function.name
      need_paren = @operator_precedence_stack.last > operator_precedence(op)
      lhs = ast.arguments[0]
      rhs = ast.arguments[1]
      print '(' if need_paren
      @operator_precedence_stack << operator_precedence(op)
      visit(lhs)
      @operator_precedence_stack.pop
      print " #{op_str} "
      @operator_precedence_stack << operator_precedence(op) + 1 # Left associative
      visit(rhs)
      @operator_precedence_stack.pop
      print ')' if need_paren
    elsif ast.function.name == :memset
      if VariableAST === ast.arguments.first
        # slight.clear()
        visit(ast.arguments.first)
        print '.clear()'
      elsif ast.arguments.first.arguments.first.value == 0
        # sdata.clear(cc)
        visit(ast.arguments.first.function)
        print '.clear('
        visit(ast.arguments.first.arguments[1])
        print ')'
      else
        # memset(cdata(450, r1), 0, 120);
        # cdata.clear(r1, 450, (120)/sizeof(int))
        visit(ast.arguments.first.function)
        print '.clear('
        visit(ast.arguments.first.arguments[1])
        print ', '
        visit(ast.arguments.first.arguments[0])
        print ', ('
        visit(ast.arguments[2])
        print ') / sizeof(int))'
      end
    elsif ast.function.name == :memcpy
      if VariableAST === ast.arguments.first
        visit(ast.function)
        print '_('
        ast.arguments.each_with_index do |arg, i|
          visit(arg)
          if i != ast.arguments.length - 1
            print ', '
          end
        end
        print ')'
      else
        print 'memcpy('
        visit(ast.arguments[0].function)
        print ', '
        visit(ast.arguments[0].arguments[0])
        print ', '
        visit(ast.arguments[0].arguments[1])
        print ', '
        visit(ast.arguments[1].function)
        print ', '
        visit(ast.arguments[1].arguments[0])
        print ', '
        visit(ast.arguments[1].arguments[1])
        print ', '
        visit(ast.arguments[2])
        print ')'
      end
    elsif (ast.function.name == :zWrite || ast.function.name == :zRead) && FunctionCallAST === ast.arguments.first
      # zWrite(cdata(0, 57), hgz, fsize);
      # zWrite(cdata, hgz, fsize, 57);
      visit(ast.function)
      print '('
      visit(ast.arguments[0].function)
      print ', '
      visit(ast.arguments[1])
      print ', '
      visit(ast.arguments[2])
      print ', '
      visit(ast.arguments[0].arguments[1])
      print ')'
    else
      visit(ast.function)
      print '('
      ast.arguments.each_with_index do |arg, i|
        visit(arg)
        if i != ast.arguments.length - 1
          print ', '
        end
      end
      print ')'
    end
  end

  def visit_letstatement(ast)
    # print_ 'let '
    print_ ''
    if VariableAST === ast.lhs && ast.lhs.name == :cnt
      print @cnt
    else
      visit(ast.lhs)
    end
    case ast.operator
    when :assign
      print ' = '
    when :assign_add
      print ' += '
    when :assign_sub
      print ' -= '
    when :assign_mul
      print ' *= '
    when :assign_div
      print ' /= '
    else
      raise
    end
    visit(ast.rhs)
    puts ';'
  end

  def visit_switchstatement(ast)
    print_ 'switch ('
    visit(ast.expression)
    puts ') {'
    ast.cases.each(&method(:visit))
    puts_ '}'
  end

  def visit_case(ast)
    print_ 'case '
    visit(ast.expression)
    puts ':'
    visit(ast.block)
  end

  def visit_variable(ast)
    if ast.name == :cnt && @in_repeat == 0
      print 'CNT'
      return
    end

    n = ast.name.to_s
    # Double underscores are not allowed in C++.
    if n.start_with?('op__')
      print 'elona_bop_' + n[4..-1]
    elsif n.start_with?('uop__')
      print 'elona_uop_' + n[5..-1]
    else
      print ast.name
    end
  end

  def visit_stringliteral(ast)
    print 'u8"' + ast.value + '"' + 's' # std::literals::string_literals
  end

  def visit_integerliteral(ast)
    print ast.value
  end

  def visit_floatingliteral(ast)
    print ast.value
  end

  def visit_incrementstatement(ast)
    print_ '++'
    if VariableAST === ast.expression && ast.expression.name == :cnt
      print @cnt
    else
      visit(ast.expression)
    end
    puts ';'
  end

  def visit_decrementstatement(ast)
    print_ '--'
    if VariableAST === ast.expression && ast.expression.name == :cnt
      print @cnt
    else
      visit(ast.expression)
    end
    puts ';'
  end
end
