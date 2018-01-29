require 'set'
require './ast.rb'


# These terms are used in incremental GC.
MARK_WHITE = 0
MARK_GRAY = 1
MARK_BLACK = 2


class FlowAnalyzer < ASTVisitor
  def initialize
    @functions = {}
    @table = []
  end

  def visit(ast)
    return nil unless ast
    return nil unless ast.mark == MARK_WHITE
    super
  end

  def visit_program(ast)
    ast.functions.each do |func|
      @functions[func.name] = func
    end

    ast.mark = MARK_GRAY
    # The first function is the entry point, i.e., 'main'.
    visit(ast.functions.first)
    ast.mark = MARK_BLACK

    until @table.empty?
      @table.each(&method(:visit))
      @table.delete_if{|i| !i || i.mark == MARK_BLACK}
    end
  end

  def visit_repeatstatement(ast)
    ast.mark = MARK_GRAY
    visit(ast.times)
    visit(ast.start)
    visit(ast.block)
    ast.mark = MARK_BLACK
  end

  def visit_ifstatement(ast)
    ast.mark = MARK_GRAY
    visit(ast.condition)
    visit(ast.true_block)
    visit(ast.false_block)
    ast.mark = MARK_BLACK
  end

  def visit_block(ast)
    ast.mark = MARK_GRAY
    ast.statements.each(&method(:visit))
    ast.mark = MARK_BLACK
  end

  def visit_expressionstatement(ast)
    ast.mark = MARK_GRAY
    visit(ast.expression)
    ast.mark = MARK_BLACK
  end

  def visit_eventstatement(ast)
    # Does not visit ast.statement
    ast.mark = MARK_BLACK
  end

  def visit_labeldeclaration(ast)
    ast.mark = MARK_GRAY
    visit(ast.label)
    ast.mark = MARK_BLACK
  end

  def visit_label(ast)
    ast.mark = MARK_BLACK
  end

  def visit_gotostatement(ast)
    ast.mark = MARK_GRAY
    visit(ast.label)
    call(ast.label.name)
    ast.mark = MARK_BLACK
  end

  def visit_continuestatement(ast)
    ast.mark = MARK_BLACK
  end

  def visit_breakstatement(ast)
    ast.mark = MARK_BLACK
  end

  def visit_returnstatement(ast)
    ast.mark = MARK_GRAY
    visit(ast.return_value)
    ast.mark = MARK_BLACK
  end

  def visit_functioncall(ast)
    ast.mark = MARK_GRAY
    visit(ast.function)
    call(ast.function.name)
    ast.arguments.each(&method(:visit))
    ast.mark = MARK_BLACK
  end

  def visit_letstatement(ast)
    ast.mark = MARK_GRAY
    visit(ast.lhs)
    visit(ast.rhs)
    ast.mark = MARK_BLACK
  end

  def visit_functiondefinition(ast)
    ast.mark = MARK_GRAY
    ast.parameters.each(&method(:visit))
    visit(ast.block)
    ast.mark = MARK_BLACK
  end

  def visit_parameter(ast)
    ast.mark = MARK_BLACK
  end

  def visit_switchstatement(ast)
    ast.mark = MARK_GRAY
    visit(ast.expression)
    ast.cases.each(&method(:visit))
    ast.mark = MARK_BLACK
  end

  def visit_case(ast)
    ast.mark = MARK_GRAY
    visit(ast.expression)
    visit(ast.block)
    ast.mark = MARK_BLACK
  end

  def visit_variable(ast)
    ast.mark = MARK_BLACK
  end

  def visit_stringliteral(ast)
    ast.mark = MARK_BLACK
  end

  def visit_integerliteral(ast)
    ast.mark = MARK_BLACK
  end

  def visit_floatingliteral(ast)
    ast.mark = MARK_BLACK
  end

  def visit_incrementstatement(ast)
    ast.mark = MARK_GRAY
    visit(ast.expression)
    ast.mark = MARK_BLACK
  end

  def visit_decrementstatement(ast)
    ast.mark = MARK_GRAY
    visit(ast.expression)
    ast.mark = MARK_BLACK
  end

  private

  DELETED_FUNCTIONS = [
    :label_1404, # uploader
    :label_1410, # browser
    :label_1669, # medit
  ].to_set

  def call(name)
    unless DELETED_FUNCTIONS.include?(name)
      @table << @functions[name]
    end
  end
end
