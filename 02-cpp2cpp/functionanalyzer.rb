require './ast.rb'


# :void :int :str :double


class FunctionInfo
  attr_reader :ast, :name, :return_type

  def initialize(ast)
    @ast = ast
    @name = ast.name
    @return_type = nil
  end

  def return_type=(value)
    if return_type
      if value && return_type != value
        # Conflict!
        if return_type == :void
          @return_type = value
        elsif value != :void
          # puts "error: #{name} #{return_type} #{value}"
          @return_type = :void
        end
      end
    else
      @return_type = value
    end
  end
end



class FunctionAnalyzer < ASTVisitor
  def initialize
  end

  def visit_functiondefinition(ast)
    @context = FunctionInfo.new(ast)
    @parameters = {}
    # ast.parameters.each(&method(:visit))
    visit(ast.block)
    @context
  end

  def visit_repeatstatement(ast)
    visit(ast.times)
    visit(ast.start)
    visit(ast.block)
  end

  def visit_ifstatement(ast)
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
      @context.return_type = visit(ast.return_value)
    else
      @context.return_type = :void
    end
  end

  def visit_functioncall(ast)
    visit(ast.function)
    ast.arguments.each(&method(:visit))
    nil
  end

  def visit_letstatement(ast)
    visit(ast.lhs)
    visit(ast.rhs)
  end

  def visit_parameter(ast)
  end

  def visit_switchstatement(ast)
    visit(ast.expression)
    ast.cases.each(&method(:visit))
  end

  def visit_case(ast)
    visit(ast.expression)
    visit(ast.block)
  end

  def visit_type(ast)
  end

  def visit_variable(ast)
    @parameters[ast.name]
  end

  def visit_stringliteral(ast)
    :str
  end

  def visit_integerliteral(ast)
    :int
  end

  def visit_floatingliteral(ast)
    :double
  end

  def visit_incrementstatement(ast)
    visit(ast.expression)
  end

  def visit_decrementstatement(ast)
    visit(ast.expression)
  end
end
