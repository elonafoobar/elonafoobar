require './ast.rb'
require './typetable.rb'



class SimpleTypeAnalyzer < ASTVisitor
  def initialize(type_table, invalid_return)
    @type_table = type_table
    @invalid_return = invalid_return
    @context = nil
  end

  def visit_functiondefinition(ast)
    @context = ast
    params = ast.parameters.map(&method(:visit))
    @return_type = :no_return
    visit(ast.block)
    if params.all?(&:valid?)
      if @return_type == :no_return
        @type_table.register(
          ast.name,
          FunctionType.new(BasicType::VOID, params))
      elsif @return_type&.valid?(as_return_type: true)
        @type_table.register(
          ast.name,
          FunctionType.new(@return_type, params))
      end
    end
    if ast.name == :encadd
        @type_table.register(
          ast.name,
          FunctionType.new(@return_type, params))
    end
  end

  def visit_parameter(ast)
    case ast.type
    when :int
      if ast.name
        @type_table.register(ast.name, BasicType::INT)
      end
      BasicType::INT
    when :str
      if ast.name
        @type_table.register(ast.name, BasicType::STRING)
      end
      BasicType::STRING
    when :elona_ref_type_int
      if ast.name
        @type_table.register(ast.name, RefType::INT)
      end
      RefType::INT
    when :elona_ref_type_str
      if ast.name
        @type_table.register(ast.name, RefType::STRING)
      end
      RefType::STRING
    else
      # Do nothing so far.
      BasicType::UNKNOWN
    end
  end

  def visit_repeatstatement(ast)
    if VariableAST === ast.times
      @type_table.register(ast.times.name, BasicType::INT)
    end
    if VariableAST === ast.start
      @type_table.register(ast.start.name, BasicType::INT)
    end
    visit(ast.times)
    visit(ast.start)
    visit(ast.block)
  end

  def visit_ifstatement(ast)
    if VariableAST === ast.condition
      @type_table.register(ast.condition.name, BasicType::INT)
    end
    visit(ast.condition)
    visit(ast.true_block)
    visit(ast.false_block)
  end

  def visit_block(ast)
    ast.statements.each(&method(:visit))
  end

  def visit_expressionstatement(ast)
    visit(ast.expression)
  end

  def visit_eventstatement(ast)
    visit(ast.statement)
  end

  def visit_labeldeclaration(ast)
    visit(ast.label)
  end

  def visit_label(ast)
  end

  def visit_gotostatement(ast)
    visit(ast.label)
  end

  def visit_continuestatement(ast)
  end

  def visit_breakstatement(ast)
  end

  def visit_returnstatement(ast)
    if ast.return_value
      if VariableAST === ast.return_value
        type = visit(ast.return_value)
        if ArrayType === type
          # `return s;` means `return s(0);`
          @return_type = @type_table.merge(@return_type, type.base_type)
        else
          @return_type = @type_table.merge(@return_type, type)
        end
      else
        @return_type = @type_table.merge(@return_type, visit(ast.return_value))
      end
    else
      @return_type = @type_table.merge(@return_type, BasicType::VOID)
    end
    if !@return_type&.valid?(as_return_type: true)
      if @return_type == Union.new(BasicType::INT, BasicType::VOID)
        @invalid_return << @context.name
        @return_type = BasicType::INT
      end
    end
  end

  def visit_functioncall(ast)
    visit(ast.function)
    ast.arguments.each(&method(:visit))
    case ast.function.name
    when :DIM1
      @type_table.register(ast.arguments.first.name, ArrayType.new(BasicType::INT, 1), :DIM1)
    when :DIM2
      @type_table.register(ast.arguments.first.name, ArrayType.new(BasicType::INT, 1), :DIM2)
    when :DIM3
      @type_table.register(ast.arguments.first.name, ArrayType.new(BasicType::INT, 2), :DIM3)
    when :DIM4
      @type_table.register(ast.arguments.first.name, ArrayType.new(BasicType::INT, 3), :DIM4)
    when :SDIM1
      @type_table.register(ast.arguments.first.name, ArrayType.new(BasicType::STRING, 1), :SDIM1)
    when :SDIM2
      @type_table.register(ast.arguments.first.name, ArrayType.new(BasicType::STRING, 1), :SDIM2)
    when :SDIM3
      @type_table.register(ast.arguments.first.name, ArrayType.new(BasicType::STRING, 1), :SDIM3)
    when :SDIM4
      @type_table.register(ast.arguments.first.name, ArrayType.new(BasicType::STRING, 2), :SDIM4)
    end
    func_type = @type_table[ast.function.name]
    if OperatorFunctionType === func_type
      arg_types = ast.arguments.map(&method(:visit))
      signature = func_type.get_concrete_signature(arg_types)
      ast.arguments.each_with_index do |arg, i|
        if VariableAST === arg
          type = signature[i+1]
          @type_table.register(arg.name, type, ast.function.name.to_s + ':arg' + i.to_s)
        end
      end
      signature.first
    else
      ast.arguments.each_with_index do |arg, i|
        if VariableAST === arg
          type = func_type&.parameter_type_at(i)
          @type_table.register(arg.name, type, ast.function.name.to_s + ':arg' + i.to_s)
        end
      end
      func_type&.return_type
    end
  end

  def visit_letstatement(ast)
    visit(ast.lhs)
    if ast.operator == :assign
      if VariableAST === ast.lhs
        type = visit(ast.rhs)
        if ArrayType === type
          # `let foobar = s;` means `foobar = s(0);`
          type = type.base_type
        end
        @type_table.register(ast.lhs.name, type, ast.rhs)
      else
        # cdata(1, 2) = 0
        d = ast.lhs.arguments.length
        base_type = visit(ast.rhs)
        if ArrayType === base_type
          # `let foobar = s;` means `foobar = s(0);`
          base_type = base_type.base_type
        end
        if base_type&.valid?
          @type_table.register(ast.lhs.function.name, ArrayType.new(base_type, d), ast.rhs)
        end
      end
    end
  end

  def visit_switchstatement(ast)
    visit(ast.expression)
    if VariableAST === ast.expression
      @type_table.register(ast.expression.name, BasicType::INT)
    end
    ast.cases.each(&method(:visit))
  end

  def visit_case(ast)
    visit(ast.expression)
    if VariableAST === ast.expression
      @type_table.register(ast.expression.name, BasicType::INT)
    end
    visit(ast.block)
  end

  def visit_variable(ast)
    @type_table.register(ast.name, BasicType::UNKNOWN)
    @type_table[ast.name]
  end

  def visit_stringliteral(ast)
    BasicType::STRING
  end

  def visit_integerliteral(ast)
    BasicType::INT
  end

  def visit_floatingliteral(ast)
    BasicType::INT
  end

  def visit_incrementstatement(ast)
    visit(ast.expression)
    if VariableAST === ast.expression
      @type_table.register(ast.expression.name, BasicType::INT)
    end
  end

  def visit_decrementstatement(ast)
    visit(ast.expression)
    if VariableAST === ast.expression
      @type_table.register(ast.expression.name, BasicType::INT)
    end
  end
end
