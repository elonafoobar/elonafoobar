require './lexer.rb'
require './ast.rb'




class Parser
  def initialize
  end

  def parse(input)
    @lexer = Lexer.new(input)
    parse_program
  end

  private

  def parse_program
    functions = []
    while @lexer.get != :eof
      functions << parse_function
    end
    @lexer.expect(:eof)
    ProgramAST.new(functions, 0)
  end

  def parse_function
    @lexer.expect(:keyword_function)
    name = parse_identifier
    @lexer.expect(:parenthesis_left)
    parameters = parse_parameter_list
    @lexer.expect(:parenthesis_right)
    block = parse_block
    FunctionDefinitionAST.new(name, parameters, block, 0)
  end

  def parse_parameter_list
    ret = []
    while @lexer.get != :parenthesis_right && @lexer.get != :eof
      type = parse_identifier
      if @lexer.get == :identifier
        name = parse_identifier
      else
        name = nil
      end
      ret << ParameterAST.new(type, name, 0)
      if @lexer.get != :parenthesis_right
        @lexer.expect(:comma)
      end
    end
    ret
  end

  def parse_block
    @lexer.expect(:brace_left)
    stmts = []
    while @lexer.get != :brace_right && @lexer.get != :eof
      stmts << parse_statement
    end
    @lexer.expect(:brace_right)
    BlockAST.new(stmts, 0)
  end

  def parse_statement
    t = @lexer.get
    case t.type
    when :keyword_if
      parse_if_statement
    when :keyword_repeat
      parse_repeat_statement
    when :keyword_onerror, :keyword_onkey, :keyword_comevent, :keyword_oncmd, :keyword_button
      parse_event_statement
    when :keyword_let
      parse_let_statement
    when :increment
      parse_increment_statement
    when :decrement
      parse_decrement_statement
    when :keyword_switch
      parse_switch_statement
    when :keyword_return
      parse_return_statement
    when :keyword_break
      parse_break_statement
    when :keyword_continue
      parse_continue_statement
    when :keyword_goto
      parse_goto_statement
    when :colon
      parse_label_declaration
    else
      parse_expression_statement
    end
  end

  def parse_repeat_statement
    @lexer.advance
    times = nil
    start = nil
    if @lexer.get == :parenthesis_left
      @lexer.advance
      times = parse_expression
      if @lexer.get == :comma
        @lexer.advance
        start = parse_expression
      end
      @lexer.expect(:parenthesis_right)
    end
    block = parse_block
    RepeatStatementAST.new(times, start, block, 0)
  end

  def parse_expression_statement
    expr = parse_expression
    @lexer.expect(:semicolon)
    ExpressionStatementAST.new(expr, 0)
  end

  def parse_switch_statement
    @lexer.advance
    @lexer.expect(:parenthesis_left)
    expr = parse_expression
    @lexer.expect(:parenthesis_right)
    @lexer.expect(:brace_left)
    cases = []
    while @lexer.get == :keyword_case
      @lexer.advance
      e = parse_expression
      @lexer.expect(:colon)
      stmts = []
      while @lexer.get != :keyword_case && @lexer.get != :brace_right && @lexer.get != :eof
        stmts << parse_statement
      end
      b = BlockAST.new(stmts, 0)
      cases << CaseAST.new(e, b, 0)
    end
    @lexer.expect(:brace_right)
    SwitchStatementAST.new(expr, cases, 0)
  end

  def parse_continue_statement
    @lexer.advance
    @lexer.expect(:semicolon)
    ContinueStatementAST.new(nil, 0)
  end

  def parse_break_statement
    @lexer.advance
    @lexer.expect(:semicolon)
    BreakStatementAST.new(nil, 0)
  end

  def parse_return_statement
    @lexer.advance
    if @lexer.get == :semicolon
      @lexer.advance
      ReturnStatementAST.new(nil, 0)
    else
      expr = parse_expression
      @lexer.expect(:semicolon)
      ReturnStatementAST.new(expr, 0)
    end
  end

  def parse_goto_statement
    @lexer.advance
    label = parse_label
    @lexer.expect(:semicolon)
    GotoStatementAST.new(label, 0)
  end

  def parse_event_statement
    event = @lexer.get
    @lexer.advance
    stmt = parse_statement
    EventStatementAST.new(event.str.to_sym, stmt, 0)
  end

  def parse_if_statement
    @lexer.advance
    @lexer.expect(:parenthesis_left)
    cond = parse_expression
    @lexer.expect(:parenthesis_right)
    true_block = parse_block
    false_block = nil
    if @lexer.get == :keyword_else
      @lexer.advance
      false_block = parse_block
    end
    IfStatementAST.new(cond, true_block, false_block, 0)
  end

  def parse_expression
    parse_postfix_expression
  end

  def parse_let_statement
    @lexer.advance
    lhs = parse_expression
    op = @lexer.get
    @lexer.advance
    rhs = parse_expression
    @lexer.expect(:semicolon)
    LetStatementAST.new(op.type, lhs, rhs, 0)
  end

  def parse_increment_statement
    @lexer.advance
    operand = parse_expression
    @lexer.expect(:semicolon)
    IncrementStatementAST.new(operand, 0)
  end

  def parse_decrement_statement
    @lexer.advance
    operand = parse_expression
    @lexer.expect(:semicolon)
    DecrementStatementAST.new(operand, 0)
  end

  def parse_postfix_expression
    lhs = parse_primary_expression
    while @lexer.get == :parenthesis_left
      @lexer.advance
      args = []
      while @lexer.get != :parenthesis_right && @lexer.get != :eof
        if @lexer.get == :comma
          @lexer.advance
          args << nil
          next
        end
        args << parse_expression
        if @lexer.get != :parenthesis_right
          @lexer.expect(:comma)
        end
      end
      @lexer.expect(:parenthesis_right)
      lhs = FunctionCallAST.new(lhs, args, 0)
    end
    lhs
  end

  def parse_primary_expression
    case @lexer.get.type
    when :identifier
      parse_variable
    when :integer_literal
      parse_integer_literal
    when :floating_literal
      parse_floating_literal
    when :string_literal
      parse_string_literal
    when :parenthesis_left
      @lexer.advance
      e = parse_expression
      @lexer.expect(:parenthesis_right)
      e
    else
      raise "expected a primary expression, but actually got #{@lexer.get}"
    end
  end

  def parse_variable
    name = parse_identifier
    VariableAST.new(REPLACED_VARIABLE_TABLE[name] || name, 0)
  end

  def parse_identifier
    t = @lexer.expect(:identifier)
    t.str.to_sym
  end

  def parse_string_literal
    t = @lexer.expect(:string_literal)
    StringLiteralAST.new(t.str, 0)
  end

  def parse_integer_literal
    t = @lexer.expect(:integer_literal)
    IntegerLiteralAST.new(t.str.to_i, 0)
  end

  def parse_floating_literal
    t = @lexer.expect(:floating_literal)
    FloatingLiteralAST.new(t.str.to_f, 0)
  end

  def parse_label_declaration
    @lexer.advance
    label = parse_label
    @lexer.expect(:colon)
    LabelDeclarationAST.new(label, 0)
  end

  def parse_label
    t = @lexer.expect(:identifier)
    LabelAST.new(t.str.to_sym, 0)
  end

  REPLACED_VARIABLE_TABLE = {
    delete: :elona_delete, # C++ keyword
    double: :elona_double, # C++ keyword
    export: :elona_export, # C++ keyword
    int: :elona_int, # C++ keyword
    str: :elona_str, # Conflicts with type.
  }
end
