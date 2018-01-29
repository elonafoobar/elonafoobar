ProgramAST             = Struct.new(:functions, :mark)
FunctionDefinitionAST  = Struct.new(:name, :parameters, :block, :mark)
BlockAST               = Struct.new(:statements, :mark)
EventStatementAST      = Struct.new(:event, :statement, :mark)
IfStatementAST         = Struct.new(:condition, :true_block, :false_block, :mark)
RepeatStatementAST     = Struct.new(:times, :start, :block, :mark)
LabelDeclarationAST    = Struct.new(:label, :mark)
ExpressionStatementAST = Struct.new(:expression, :mark)
LetStatementAST        = Struct.new(:operator, :lhs, :rhs, :mark)
IncrementStatementAST  = Struct.new(:expression, :mark)
DecrementStatementAST  = Struct.new(:expression, :mark)
FunctionCallAST        = Struct.new(:function, :arguments, :mark)
ParameterAST           = Struct.new(:type, :name, :mark)
VariableAST            = Struct.new(:name, :mark)
TypeAST                = Struct.new(:name, :mark)
StringLiteralAST       = Struct.new(:value, :mark)
IntegerLiteralAST      = Struct.new(:value, :mark)
FloatingLiteralAST     = Struct.new(:value, :mark)
LabelAST               = Struct.new(:name, :mark)
GotoStatementAST       = Struct.new(:label, :mark)
ContinueStatementAST   = Struct.new(:dummy, :mark)
ReturnStatementAST     = Struct.new(:return_value, :mark)
BreakStatementAST      = Struct.new(:dummy, :mark)
SwitchStatementAST     = Struct.new(:expression, :cases, :mark)
CaseAST                = Struct.new(:expression, :block, :mark)


class ASTVisitor
  def visit(ast)
    return nil unless ast

    if Array === ast
      ast.each do |a|
        visit(a)
      end
    else
      # e.g.) ProgramAST => visit_program
      method_name = 'visit_' + ast.class.name.downcase[0...-3]
      send(method_name, ast)
    end
  end
end
