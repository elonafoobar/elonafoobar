require './ast.rb'



class ASTOptimizer < ASTVisitor
  attr_reader :label_table, :call_type

  def initialize
    @label_table = {}
    @call_type = {}
    @constant_table = create_const_table
  end

  def visit_program(ast)
    ast.statements = translate_block(ast.statements)
    ast
  end

  def visit_repeatstatement(ast)
    ast.times = visit(ast.times)
    ast.start = visit(ast.start)
    ast.block = visit(ast.block)
    ast
  end

  def visit_ifstatement(ast)
    ast.condition = visit(ast.condition)
    if IntegerLiteralAST === ast.condition
      if ast.condition.value == 1
        # Always its true block is executed.
        ast.true_block = visit(ast.true_block)
        ast.false_block = nil
        return ast.true_block.statements
      elsif ast.condition.value == 0
        # Always its false block is executed.
        if ast.false_block
          ast.true_block = nil
          ast.false_block = visit(ast.false_block)
          return ast.false_block.statements
        else
          return nil
        end
      end
    end
    ast.true_block = visit(ast.true_block)
    ast.false_block = visit(ast.false_block)
    ast
  end

  def visit_block(ast)
    ast.statements = translate_block(ast.statements)
    ast
  end

  def visit_expressionstatement(ast)
    if IncrementExpressionAST === ast.expression && IdentifierAST === ast.expression.expression && ast.expression.expression.name == '_switch_sw'
      return nil
    end

    ast.expression = visit(ast.expression)
    ast
  end

  def visit_eventstatement(ast)
    ast.statement = visit(ast.statement)
    ast
  end

  def visit_labeldeclaration(ast)
    ast.label = visit(ast.label)
    ast
  end

  def visit_label(ast)
    ast
  end

  def visit_commandstatement(ast)
    ast.arguments.length.times do |i|
      ast.arguments[i] = visit(ast.arguments[i])
    end
    ast
  end

  def visit_gotostatement(ast)
    ast.label = visit(ast.label)
    if @call_type[ast.label.name]
      @call_type[ast.label.name] |= 1
    else
      @call_type[ast.label.name] = 1
    end
    ast
  end

  def visit_gosubstatement(ast)
    ast.label = visit(ast.label)
    if @call_type[ast.label.name]
      @call_type[ast.label.name] |= 2
    else
      @call_type[ast.label.name] = 2
    end
    ast
  end

  def visit_continuestatement(ast)
    if ast.cnt
      if IdentifierAST === ast.cnt && ast.cnt.name == 'cnt'
        # --cnt;
        # continue;
        [ExpressionStatementAST.new(DecrementExpressionAST.new(IdentifierAST.new('cnt'))), ContinueStatementAST.new()]
      else
        ast.cnt = visit(ast.cnt)
        # cnt = 3;
        # continue;
        [AssignmentStatementAST.new(Token.new(:assign, '='), IdentifierAST.new('cnt'), BinaryExpressionAST.new(Token.new(:minus, '-'), ast.cnt, IntegerLiteralAST.new(1))), ContinueStatementAST.new()]
      end
    else
      ast
    end
  end

  def visit_breakstatement(ast)
    ast
  end

  def visit_returnstatement(ast)
    ast.return_value = visit(ast.return_value)
    ast
  end

  def visit_functioncall(ast)
    ast.function = visit(ast.function)
    ast.arguments.length.times do |i|
      ast.arguments[i] = visit(ast.arguments[i])
    end
    ast
  end

  def visit_assignmentstatement(ast)
    if IdentifierAST === ast.lhs && ast.lhs.name == '_switch_sw'
      return nil
    end

    ast.lhs = visit(ast.lhs)
    ast.rhs = visit(ast.rhs)
    if Array === ast.rhs
      if IdentifierAST === ast.lhs
        # s = "", ""
        #
        # s(0) = "";
        # s(1) = "";
        ast.rhs.map.with_index do |rhs, i|
          AssignmentStatementAST.new(
            ast.operator,
            FunctionCallAST.new(
              ast.lhs,
              [IntegerLiteralAST.new(i)]),
            rhs)
        end
      elsif FunctionCallAST === ast.lhs
        # s(0, k) = "", ""
        #
        # s(0, k) = "";
        # s(1, k) = "";
        args = ast.lhs.arguments
        ast.rhs.map.with_index do |rhs, i|
          first = nil
          if IntegerLiteralAST === args.first
            first = IntegerLiteralAST.new(args.first.value + i)
          else
            first = BinaryExpressionAST.new(
              Token.new(:plus, '+'),
              args.first,
              IntegerLiteralAST.new(i))
          end
          AssignmentStatementAST.new(
            ast.operator,
            FunctionCallAST.new(
              ast.lhs.function,
              [first] + args[1..-1]),
            rhs)
        end
      else
        raise ast.lhs.class.name
      end
    else
      ast
    end
  end

  def visit_commaexpression(ast)
    # [[[a, b], c], d] => [[a, b, c], d] => [a, b, c, d]
    ast.lhs = visit(ast.lhs)
    ast.rhs = visit(ast.rhs)
    if Array === ast.lhs
      [*ast.lhs, ast.rhs]
    else
      [ast.lhs, ast.rhs]
    end
  end

  def visit_binaryexpression(ast)
    ast.lhs = visit(ast.lhs)
    ast.rhs = visit(ast.rhs)
    calculate(ast)
  end

  def visit_unaryexpression(ast)
    ast.operand = visit(ast.operand)
    ast
  end

  def visit_macrodeffunc(ast)
    ast.name = visit(ast.name)
    ast.parameters.length.times do |i|
      ast.parameters[i] = visit(ast.parameters[i])
    end
    ast
  end

  def visit_parameter(ast)
    ast.type = visit(ast.type)
    if ast.name
      ast.name = visit(ast.name)
    end
    ast
  end

  def visit_type(ast)
    ast
  end

  def visit_identifier(ast)
    @constant_table[ast.name] || ast
  end

  def visit_stringliteral(ast)
    ast
  end

  def visit_integerliteral(ast)
    ast
  end

  def visit_floatingliteral(ast)
    ast
  end

  def visit_incrementexpression(ast)
    ast.expression = visit(ast.expression)
    ast
  end

  def visit_decrementexpression(ast)
    ast.expression = visit(ast.expression)
    ast
  end

  # Constant folding.
  def calculate(ast)
    unless IntegerLiteralAST === ast.lhs && IntegerLiteralAST === ast.rhs ||
        StringLiteralAST === ast.lhs && StringLiteralAST === ast.rhs
      return ast
    end

    lhs = ast.lhs.value
    rhs = ast.rhs.value
    case ast.operator.type
    when :or
      ret = lhs || rhs
    when :xor
      ret = lhs ^ rhs
    when :modulo
      ret = lhs % rhs
    when :shift_r
      ret = lhs >> rhs
    when :greater_than_equal
      ret = lhs >= rhs
    when :greater_than
      ret = lhs > rhs
    when :equal
      ret = lhs == rhs
    when :less_than_equal
      ret = lhs <= rhs
    when :shift_l
      ret = lhs << rhs
    when :less_than
      ret = lhs < rhs
    when :division
      ret = lhs / rhs
    when :minus
      ret = lhs - rhs
    when :plus
      ret = lhs + rhs
    when :multiplication
      ret = lhs * rhs
    when :and
      ret = lhs && rhs
    when :not_equal
      ret = lhs != rhs
    else
      return ast
    end
    case ret
    when String
      StringLiteralAST.new(ret)
    when TrueClass
      IntegerLiteralAST.new(1)
    when FalseClass
      IntegerLiteralAST.new(0)
    else
      IntegerLiteralAST.new(ret)
    end
  end

  private

  ALWAYS_1 = %w[]
  ALWAYS_0 = %w[
debug
dbg_acemu
dbg_arena
dbg_autoidentify
dbg_corpse
dbg_figure
dbg_findinvalidmap
dbg_fish
dbg_freesp
dbg_freespell
dbg_freetravel
dbg_friend
dbg_hpalwaysfull
dbg_hpcounter
dbg_loop
dbg_meditfile
dbg_name
dbg_noadv
dbg_noautosave
dbg_nochat
dbg_notravel
dbg_noweight
dbg_plant
dbg_randomsite
dbg_randseed
dbg_rdtype
dbg_seeresist
dbg_showallskill
dbg_showsp
dbg_skillpointfix
dbg_skipcm
dbg_testtrap
dbg_tileset
dbg_titleinfo
dbg_toolversatile
dbg_usernpc
dbg_weaponalive
  ]

  def create_const_table
    ret = {}
    zero = IntegerLiteralAST.new(0)
    one = IntegerLiteralAST.new(1)
    ALWAYS_0.each do |n|
      ret[n] = zero
    end
    ALWAYS_1.each do |n|
      ret[n] = one
    end
    ret
  end

  def switch_statement?(s)
    IfStatementAST === s && BinaryExpressionAST === s.condition && IdentifierAST === s.condition.rhs && s.condition.rhs.name == '_switch_sw'
  end

  def translate_block(statements)
    hoge = nil
    statements.length.times do |i|
      ss = statements[i]
      ns = statements[i + 1]
      if LabelDeclarationAST === ss
        if LabelDeclarationAST === ns
          # *label_1
          # *label_2
          # All "label_1"s are replaced by "label_2", and the line "*label_1" is removed.
          @label_table[ss.label.name] = ns.label.name
          statements[i] = nil
        end
        if GotoStatementAST === ns
          # *label_1
          #     goto label_2
          # All "label_1"s are replaced by "label_2", and the line "*label_1" is removed.
          @label_table[ss.label.name] = ns.label.name
          statements[i] = nil
        end
      end
      if GotoStatementAST === ss || ReturnStatementAST === ss
        if GotoStatementAST === ns || ReturnStatementAST === ns || GosubStatementAST === ns
          # Two jump statements are meaningless. The latter one is removed.
          statements[i + 1] = nil
        end
      end
      if AssignmentStatementAST === ss && IdentifierAST === ss.lhs && ss.lhs.name == '_switch_val'
        # _switch_val = VALUE
        # if ( 0 ) {
        #   _switch_sw++
        # }
        statements[i + 1] = nil
      end
      if switch_statement?(ss) && !switch_statement?(ns)
        statements[i].condition.rhs.name = '_switch_sw__end'
      end
      statements[i] = visit(statements[i])
    end
    statements
  end
end
