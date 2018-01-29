require './ast.rb'


class GotoSimplifier < ASTVisitor
  def initialize(simplified_labels, internal_labels, function_table)
    @current_function_name = '<anonymous>'
    @simplified_labels = simplified_labels
    @internal_labels = internal_labels
    @function_table = function_table
  end

  def visit_repeatstatement(ast)
    ast.block = visit(ast.block)
    ast
  end

  def visit_ifstatement(ast)
    ast.true_block = visit(ast.true_block)
    ast.false_block = visit(ast.false_block)
    ast
  end

  def visit_block(ast)
    ast.statements.map!(&method(:visit)).flatten!
    ast
  end

  def visit_expressionstatement(ast)
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
    if @internal_labels.has_key?(ast.name)
      ast.name = (ast.name.to_s + '_internal').to_sym
    end
    ast
  end

  def visit_gotostatement(ast)
    name = nil
    if l = @simplified_labels[ast.label.name]
      if l.defined != @current_function_name
        name = (ast.label.name.to_s.chop + '2').to_sym
      end
    end
    if @function_table.has_key?(ast.label.name)
      name = ast.label.name
    end
    if name
      [ExpressionStatementAST.new(FunctionCallAST.new(VariableAST.new(name), [])), ReturnStatementAST.new]
    else
      ast.label = visit(ast.label)
      ast
    end
  end

  def visit_continuestatement(ast)
    ast
  end

  def visit_breakstatement(ast)
    ast
  end

  def visit_returnstatement(ast)
    ast
  end

  def visit_functioncall(ast)
    ast
  end

  def visit_letstatement(ast)
    ast
  end

  def visit_functiondefinition(ast)
    @current_function_name = ast.name
    ast.block = visit(ast.block)
    ast
  end

  def visit_parameter(ast)
  end

  def visit_switchstatement(ast)
    ast.cases.map!(&method(:visit))
    ast
  end

  def visit_case(ast)
    ast.block = visit(ast.block)
    ast
  end

  def visit_variable(ast)
  end

  def visit_stringliteral(ast)
  end

  def visit_integerliteral(ast)
  end

  def visit_floatingliteral(ast)
  end

  def visit_incrementstatement(ast)
    ast
  end

  def visit_decrementstatement(ast)
    ast
  end
end
