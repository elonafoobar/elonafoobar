require './lexer.rb'
require './ast.rb'
require './command.rb'




class Parser
  def initialize
  end

  def parse(input)
    @lexer = Lexer.new(input)
    parse_program
  end

  private

  def parse_program
    stmts = []
    while @lexer.get != :eof
      stmts << parse_statement
      @lexer.skip_line_breaks
    end
    @lexer.expect(:eof)
    ProgramAST.new(stmts)
  end

  def parse_statement
    @lexer.skip_line_breaks
    t = @lexer.get
    case t.type
    when :macro_uselib, :macro_func, :macro_cfunc, :macro_deffunc, :macro_defcfunc
      return parse_macro
    when :keyword_if
      return parse_if_statement
    when :keyword_repeat
      return parse_repeat_statement
    when :keyword_onerror, :keyword_onkey, :keyword_comevent
      return parse_event_statement
    when :keyword_oncmd
      return parse_oncmd_event_statement
    when :keyword_button
      return parse_button_event_statement
    when :multiplication
      return parse_label_declaration
    when :identifier
      if COMMANDS.include?(t.str)
        return parse_command_statement
      end
    end
    parse_expression_statement
  end

  def parse_repeat_statement
    @lexer.advance
    times = nil
    start = nil
    if @lexer.get != :line_break
      times = parse_logical_expression
      if @lexer.get == :comma
        @lexer.advance
        start = parse_logical_expression
      end
    end
    @lexer.expect(:line_break)
    stmts = []
    while (@lexer.get != :identifier || @lexer.get.str != 'loop') && @lexer.get != :eof
      stmts << parse_statement
    end
    @lexer.expect(:identifier) # loop
    @lexer.skip_line_breaks
    block = BlockAST.new(stmts)
    RepeatStatementAST.new(times, start, block)
  end

  def parse_command_statement
    command = @lexer.get
    @lexer.advance
    args = []
    while @lexer.get != :line_break && @lexer.get != :eof
      if @lexer.get == :comma
        @lexer.advance
        args << nil
        next
      end
      args << parse_logical_expression
      if @lexer.get != :line_break
        @lexer.expect(:comma)
      end
    end
    @lexer.expect(:line_break)
    build_command_stmt_ast(command, args)
  end

  def parse_expression_statement
    expr = parse_expression
    @lexer.expect(:line_break)
    if AssignmentStatementAST === expr
      expr
    else
      ExpressionStatementAST.new(expr)
    end
  end

  # button goto "refresh", *label_1670
  def parse_button_event_statement
    button = @lexer.get
    @lexer.advance
    t = @lexer.get
    @lexer.advance
    @lexer.expect(:string_literal)
    @lexer.expect(:comma)
    label = parse_label
    @lexer.expect(:line_break)
    if t == :identifier && t.str == 'goto'
      EventStatementAST.new(button, GotoStatementAST.new(label))
    else
      EventStatementAST.new(button, GosubStatementAST.new(label))
    end
  end

  # oncmd goto *aaa, 0
  def parse_oncmd_event_statement
    oncmd = @lexer.get
    @lexer.advance
    t = @lexer.get
    @lexer.advance
    label = parse_label
    @lexer.expect(:comma)
    @lexer.expect(:integer_literal)
    @lexer.expect(:line_break)
    if t == :identifier && t.str == 'goto'
      EventStatementAST.new(oncmd, GotoStatementAST.new(label))
    else
      EventStatementAST.new(oncmd, GosubStatementAST.new(label))
    end
  end

  def parse_event_statement
    event = @lexer.get
    @lexer.advance
    stmt = parse_statement
    EventStatementAST.new(event, stmt)
  end

  def parse_if_statement
    @lexer.advance
    @lexer.expect(:parenthesis_left)
    cond = parse_logical_expression
    @lexer.expect(:parenthesis_right)
    true_block = parse_block
    @lexer.skip_line_breaks
    false_block = nil
    if @lexer.get == :keyword_else
      @lexer.advance
      false_block = parse_block
    end
    IfStatementAST.new(cond, true_block, false_block)
  end

  def parse_block
    @lexer.expect(:brace_left)
    @lexer.skip_line_breaks
    stmts = []
    while @lexer.get != :brace_right && @lexer.get != :eof
      stmts << parse_statement
    end
    @lexer.expect(:brace_right)
    @lexer.skip_line_breaks
    BlockAST.new(stmts)
  end

  def parse_expression
    parse_assignment_expression
  end

  def parse_assignment_expression
    lhs = parse_comma_expression
    op = @lexer.get
    case op.type
    when :assign, :assign_div, :assign_sub, :assign_add, :assign_mul
      @lexer.advance
      rhs = parse_assignment_expression
      AssignmentStatementAST.new(op, lhs, rhs)
    else
      lhs
    end
  end

  def parse_comma_expression
    lhs = parse_logical_expression
    while true
      op = @lexer.get
      case op.type
      when :comma
        @lexer.advance
        rhs = parse_logical_expression
        lhs = CommaExpressionAST.new(lhs, rhs)
      else
        break
      end
    end
    lhs
  end

  def parse_logical_expression
    lhs = parse_comparison_expression
    while true
      op = @lexer.get
      case op.type
      when :and, :or, :xor
        @lexer.advance
        rhs = parse_comparison_expression
        lhs = BinaryExpressionAST.new(op, lhs, rhs, false)
      else
        break
      end
    end
    lhs
  end

  def parse_comparison_expression
    lhs = parse_shift_expression
    while true
      op = @lexer.get
      case op.type
      when :equal, :not_equal, :less_than, :less_than_equal, :greater_than, :greater_than_equal
        @lexer.advance
        rhs = parse_shift_expression
        lhs = BinaryExpressionAST.new(op, lhs, rhs, false)
      else
        break
      end
    end
    lhs
  end

  def parse_shift_expression
    lhs = parse_additive_expression
    while true
      op = @lexer.get
      case op.type
      when :shift_l, :shift_r
        @lexer.advance
        rhs = parse_additive_expression
        lhs = BinaryExpressionAST.new(op, lhs, rhs, false)
      else
        break
      end
    end
    lhs
  end

  def parse_additive_expression
    lhs = parse_multiplicative_expression
    while true
      op = @lexer.get
      case op.type
      when :plus, :minus
        @lexer.advance
        rhs = parse_multiplicative_expression
        lhs = BinaryExpressionAST.new(op, lhs, rhs, false)
      else
        break
      end
    end
    lhs
  end

  def parse_multiplicative_expression
    lhs = parse_prefix_expression
    while true
      op = @lexer.get
      case op.type
      when :multiplication, :division, :modulo
        @lexer.advance
        rhs = parse_prefix_expression
        lhs = BinaryExpressionAST.new(op, lhs, rhs, false)
      else
        break
      end
    end
    lhs
  end

  def parse_prefix_expression
    op = @lexer.get
    case op.type
    when :plus, :minus
      @lexer.advance
      UnaryExpressionAST.new(op, parse_prefix_expression)
    else
      parse_postfix_expression
    end
  end

  def parse_postfix_expression
    lhs = parse_primary_expression
    while true
      case @lexer.get.type
      when :parenthesis_left
        @lexer.advance
        args = []
        while @lexer.get != :parenthesis_right && @lexer.get != :eof
          if @lexer.get == :comma
            @lexer.advance
            args << nil
            next
          end
          args << parse_logical_expression
          if @lexer.get != :parenthesis_right
            @lexer.expect(:comma)
          end
        end
        @lexer.expect(:parenthesis_right)
        lhs = FunctionCallAST.new(lhs, args)
      when :increment
        @lexer.advance
        lhs = IncrementExpressionAST.new(lhs)
      when :decrement
        @lexer.advance
        lhs = DecrementExpressionAST.new(lhs)
      else
        break
      end
    end
    lhs
  end

  def parse_primary_expression
    case @lexer.get.type
    when :identifier
      parse_identifier
    when :integer_literal
      parse_integer_literal
    when :floating_literal
      parse_floating_literal
    when :string_literal
      parse_string_literal
    when :multiplication
      parse_label
    when :parenthesis_left
      @lexer.advance
      expr = parse_logical_expression
      @lexer.expect(:parenthesis_right)
      if BinaryExpressionAST === expr
        BinaryExpressionAST.new(expr.operator, expr.lhs, expr.rhs, true)
      else
        expr
      end
    else
      raise "expected a primary expression, but actually got #{@lexer.get}"
    end
  end

  def parse_macro
    t = @lexer.get
    case t.type
    when :macro_cfunc, :macro_func, :macro_uselib
      until @lexer.get == :eof || @lexer.get == :line_break
        @lexer.advance
      end
      nil
    when :macro_deffunc, :macro_defcfunc
      parse_macro_deffunc
    else
      raise "unexpected token: #{@lexer.get}"
    end
  end

  def parse_macro_deffunc
    @lexer.advance
    name = parse_identifier
    parameters = parse_parameter_list
    @lexer.expect(:line_break)
    MacroDefFuncAST.new(name, parameters)
  end

  def parse_parameter_list
    ret = []
    while @lexer.get != :line_break && @lexer.get != :eof
      type = parse_type
      if @lexer.get == :identifier
        name = parse_identifier
      else
        name = nil
      end
      ret << ParameterAST.new(type, name)
      if @lexer.get != :line_break
        @lexer.expect(:comma)
      end
    end
    ret
  end

  def parse_type
    t = @lexer.expect(:identifier)
    TypeAST.new(t.str)
  end

  def parse_identifier
    t = @lexer.expect(:identifier)
    IdentifierAST.new(t.str)
  end

  def parse_string_literal
    t = @lexer.expect(:string_literal)
    StringLiteralAST.new(t.str)
  end

  def parse_integer_literal
    t = @lexer.expect(:integer_literal)
    IntegerLiteralAST.new(t.str.to_i)
  end

  def parse_floating_literal
    t = @lexer.expect(:floating_literal)
    FloatingLiteralAST.new(t.str.to_f)
  end

  def parse_label_declaration
    label = parse_label
    @lexer.expect(:line_break)
    LabelDeclarationAST.new(label)
  end

  def parse_label
    @lexer.expect(:multiplication)
    t = @lexer.expect(:identifier)
    LabelAST.new(t.str)
  end
end
