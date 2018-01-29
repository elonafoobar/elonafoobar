require './ast.rb'


class NullVisitor < ASTVisitor
  def initialize
  end

  def visit_functiondefinition(ast)
    ast.parameters.each(&method(:visit))
    visit(ast.block)
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
    visit(ast.return_value)
  end

  def visit_functioncall(ast)
    visit(ast.function)
    ast.arguments.each(&method(:visit))
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

  def visit_variable(ast)
  end

  def visit_stringliteral(ast)
  end

  def visit_integerliteral(ast)
  end

  def visit_floatingliteral(ast)
  end

  def visit_incrementstatement(ast)
    visit(ast.expression)
  end

  def visit_decrementstatement(ast)
    visit(ast.expression)
  end
end
