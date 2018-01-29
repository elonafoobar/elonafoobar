ProgramAST              = Struct.new(:statements)
MacroDefFuncAST         = Struct.new(:name, :parameters)
BlockAST                = Struct.new(:statements)
EventStatementAST       = Struct.new(:event, :statement)
IfStatementAST          = Struct.new(:condition, :true_block, :false_block)
RepeatStatementAST      = Struct.new(:times, :start, :block)
LabelDeclarationAST     = Struct.new(:label)
ExpressionStatementAST  = Struct.new(:expression)
BinaryExpressionAST     = Struct.new(:operator, :lhs, :rhs, :needs_parentheses)
CommaExpressionAST      = Struct.new(:lhs, :rhs)
AssignmentStatementAST  = Struct.new(:operator, :lhs, :rhs)
UnaryExpressionAST      = Struct.new(:operator, :operand)
IncrementExpressionAST  = Struct.new(:expression)
DecrementExpressionAST  = Struct.new(:expression)
FunctionCallAST         = Struct.new(:function, :arguments)
ParameterAST            = Struct.new(:type, :name)
IdentifierAST           = Struct.new(:name)
TypeAST                 = Struct.new(:name)
StringLiteralAST        = Struct.new(:value)
IntegerLiteralAST       = Struct.new(:value)
FloatingLiteralAST      = Struct.new(:value)
LabelAST                = Struct.new(:name)

CommandStatementAST  = Struct.new(:command, :arguments)
GotoStatementAST     = Struct.new(:label)
GosubStatementAST    = Struct.new(:label)
ContinueStatementAST = Struct.new(:cnt)
ReturnStatementAST   = Struct.new(:return_value)
BreakStatementAST    = Struct.new(:dummy)

def build_command_stmt_ast(command, args)
  case command.str
  when 'goto'
    GotoStatementAST.new(args.first)
  when 'gosub'
    GosubStatementAST.new(args.first)
  when 'continue'
    ContinueStatementAST.new(args.first)
  when 'return'
    ReturnStatementAST.new(args.first)
  when 'break'
    BreakStatementAST.new(nil)
  else
    CommandStatementAST.new(command, args)
  end
end



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
