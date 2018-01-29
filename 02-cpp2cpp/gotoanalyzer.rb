require './ast.rb'



class LabelInfo
  attr_reader :defined, :called

  def initialize(f)
    if Array === f
      @defined = nil
      @called = f
    else
      @defined = f
      @called = []
    end
  end

  def define(f)
    raise f.to_s + ' ' + @defined.to_s if @defined
    @defined = f
  end

  def call(f)
    unless @called.include?(f)
      @called << f
    end
  end
end


class GotoAnalyzer < ASTVisitor
  attr_reader :label_table

  def initialize
    @label_table = {}
    @current_function_name = '<anonymous>'
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
    label_define(ast.label.name, @current_function_name)
    visit(ast.label)
  end

  def visit_label(ast)
  end

  def visit_gotostatement(ast)
    label_call(ast.label.name, @current_function_name)
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

  def visit_functiondefinition(ast)
    @current_function_name = ast.name
    ast.parameters.each(&method(:visit))
    visit(ast.block)
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

  private

  def label_define(label_name, function_name)
    i = @label_table[label_name]
    if i
      i.define(function_name)
    else
      @label_table[label_name] = LabelInfo.new(function_name)
    end
  end

  def label_call(label_name, function_name)
    i = @label_table[label_name]
    if i
      i.call(function_name)
    else
      @label_table[label_name] = LabelInfo.new([function_name])
    end
  end
end
