require './ast.rb'



class ASTPrinter < ASTVisitor
  def initialize(label_table, call_type)
    @indent = 1
    @top_level = true
    @label_table = label_table
    @call_type = call_type
    @call_type['label_2746'] = 1
  end

  private

  def get_unified_label_name(name)
    if @label_table[name]
      get_unified_label_name(@label_table[name]) # Recursively!
    else
      name
    end
  end

  def puts_(msg)
    print ' ' * @indent * 4
    puts msg
  end

  def print_(msg)
    print ' ' * @indent * 4
    print msg
  end

  def visit_program(ast)
    ast.statements.each do |stmt|
      @returned = false
      if !@top_level ||  MacroDefFuncAST === stmt ||  LabelDeclarationAST === stmt
        visit(stmt)
      end
      if @returned
        puts '}'
        @top_level = true
      end
    end
  end

  def visit_ifstatement(ast)
    if BinaryExpressionAST === ast.condition && IdentifierAST === ast.condition.rhs && (ast.condition.rhs.name == '_switch_sw' || ast.condition.rhs.name == '_switch_sw__end')
      print_ 'case '
      visit(ast.condition.lhs.rhs)
      puts ':'
      @indent += 1
      ast.true_block.statements.each do |stmt|
        visit(stmt)
      end
      @indent -= 1
      if ast.condition.rhs.name == '_switch_sw__end'
        puts_ '}'
      end
      @returned = false
      return
    end

    print_ 'if ('
    visit(ast.condition)
    print ') '
    @returned = false
    visit(ast.true_block)
    true_block_returned = @returned
    if ast.false_block
      print ' else '
      @returned = false
      visit(ast.false_block)
      false_block_returned = @returned
    else
      false_block_returned = false
    end
    puts
    @returned = true_block_returned && false_block_returned
  end

  def visit_block(ast)
    puts '{'
    @indent += 1
    ast.statements.each do |stmt|
      visit(stmt)
    end
    @indent -= 1
    print_ '}'
  end

  def visit_expressionstatement(ast)
    print_ ''
    visit(ast.expression)
    puts ';'
  end

  def visit_eventstatement(ast)
    print_ ast.event.str
    visit(ast.statement)
    @returned = false
  end

  def visit_labeldeclaration(ast)
    if @call_type[get_unified_label_name(ast.label.name)] == 1 # goto
      # :label_0000:
      print ':'
      visit(ast.label)
      puts ':'
      @top_level = false
    elsif @call_type[get_unified_label_name(ast.label.name)] == 2 # gosub
      # function label_0000()
      # {
      print 'function '
      visit(ast.label)
      puts "()\n{"
      @top_level = false
    elsif @call_type[get_unified_label_name(ast.label.name)] == 3 # goto and gosub
      # function label_00002()
      # {
      # :label_00001:
      print 'function '
      visit(ast.label)
      puts "2()\n{\n"
      print ':'
      visit(ast.label)
      puts '1:'
      @top_level = false
    else
      # function label_0000()
      # {
      print 'nevercalledfunction '
      visit(ast.label)
      puts "()\n{"
      @top_level = false
    end
  end

  def visit_label(ast)
    print get_unified_label_name(ast.name)
  end

  def visit_gotostatement(ast)
    n = ast.label.name.to_s
    print_ 'goto '
    visit(ast.label)
    if @call_type[get_unified_label_name(ast.label.name)] == 3
      print '1'
    end
    puts ';'
    @returned = true
  end

  def visit_gosubstatement(ast)
    print_ ''
    visit(ast.label)
    if @call_type[get_unified_label_name(ast.label.name)] == 3
      print '2'
    end
    puts '();'
  end

  def visit_continuestatement(ast)
    print_ 'continue'
    if ast.cnt
      print ' '
    end
    visit(ast.cnt)
    puts ';'
  end

  def visit_returnstatement(ast)
    print_ 'return'
    if ast.return_value
      print ' '
    end
    visit(ast.return_value)
    puts ';'
    @returned = true
  end

  def visit_breakstatement(ast)
    puts_ 'break;'
  end

  def visit_commandstatement(ast)
    print_ ''
    if ast.command.str == 'dim'
      print "DIM#{ast.arguments.length}"
    elsif ast.command.str == 'sdim'
      print "SDIM#{ast.arguments.length}"
    else
      print ast.command.str
    end
    print '('
    ast.arguments.each_with_index do |arg, i|
      visit(arg)
      if i != ast.arguments.length - 1
        print ', '
      end
    end
    puts ');'
  end

  def visit_repeatstatement(ast)
    if ast.times
      if ast.start
        # print_ 'for (int cnt = '
        # visit(ast.start)
        # print '; cnt < ('
        # visit(ast.start)
        # print ') + ('
        # visit(ast.times)
        # print '); ++cnt) '
        print_ 'repeat ('
        visit(ast.times)
        print ', '
        visit(ast.start)
        print ') '
      else
        # print_ 'for (int cnt = 0; cnt < ('
        # visit(ast.times)
        # print '); ++cnt) '
        print_ 'repeat ('
        visit(ast.times)
        print ') '
      end
    else
      print_ 'repeat '
    end
    visit(ast.block)
    @returned = false
    puts
  end

  def visit_functioncall(ast)
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

  def visit_binaryexpression(ast)
    print 'op__' + ast.operator.type.to_s + '('
    visit(ast.lhs)
    print ', '
    visit(ast.rhs)
    print ')'
  end

  def visit_assignmentstatement(ast)
    if IdentifierAST === ast.lhs && ast.lhs.name == '_switch_val'
      print_ 'switch ('
      visit(ast.rhs)
      puts ') {'
      return
    end
    print_ 'let '
    visit(ast.lhs)
    print ' ' + ast.operator.str + ' '
    visit(ast.rhs)
    puts ';'
  end

  def visit_unaryexpression(ast)
    print 'uop__' + ast.operator.type.to_s + '('
    visit(ast.operand)
    print ')'
  end

  def visit_macrodeffunc(ast)
    print 'function '
    visit(ast.name)
    print '('
    ast.parameters.each_with_index do |param, i|
      visit(param)
      if i != ast.parameters.length - 1
        print ', '
      end
    end
    puts ')'
    puts '{'
    @top_level = false
  end

  def visit_parameter(ast)
    visit(ast.type)
    if ast.name
      print ' '
      visit(ast.name)
    end
  end

  def visit_type(ast)
    print ast.name
  end

  def visit_identifier(ast)
    print ast.name.gsub('@', '_at_')
  end

  def visit_stringliteral(ast)
    print '"' + ast.value + '"'
  end

  def visit_integerliteral(ast)
    print ast.value
  end

  def visit_floatingliteral(ast)
    print ast.value
  end

  def visit_incrementexpression(ast)
    print '++'
    visit(ast.expression)
  end

  def visit_decrementexpression(ast)
    print '--'
    visit(ast.expression)
  end
end
