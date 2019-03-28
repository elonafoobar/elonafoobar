-- AST (abstract syntax tree) of command line
local ast = {}



-- xxx a b c; yyy d e f
function ast.CommandListThen(lhs, rhs)
   return {class = 'commandlistthen', lhs = lhs, rhs = rhs}
end



-- xxx a b c && yyy d e f
function ast.CommandListAnd(lhs, rhs)
   return {class = 'commandlistand', lhs = lhs, rhs = rhs}
end



-- xxx a b c || yyy d e f
function ast.CommandListOr(lhs, rhs)
   return {class = 'commandlistor', lhs = lhs, rhs = rhs}
end



-- xxx a b c | yyy d e f
function ast.Pipeline(lhs, rhs)
   return {class = 'pipeline', lhs = lhs, rhs = rhs}
end



-- xxx a b c > out
function ast.RedirectCommand(cmd, file)
   return {class = 'redirectcommand', command = cmd, file = file}
end



-- xxx a b c
function ast.SimpleCommand(cmd, args)
   return {class = 'simplecommand', command_name = cmd, arguments = args}
end



--- { xxx a b c }     subshell=false
--- ( xxx a b c )     subshell=true
function ast.CommandGroup(command, subshell)
   return {class = 'commandgroup', command = command, subshell = subshell}
end



-- abc
-- 'abc'
-- "abc"
function ast.StringLiteral(string)
   return {class = 'stringliteral', string = string}
end



-- $X
-- ${X}
-- "${X}"
function ast.Variable(name)
   return {class = 'variable', name = name}
end



-- $(xxx a b c)
-- "$(xxx a b c)"
function ast.CommandSubstitution(command)
   return {class = 'commandsubstitution', command = command}
end



-- "abc${def}$(xxx)"
-- Each segment is one of StringLiteral, Variable, or CommandSubstitution.
function ast.String(segments)
   return {class = 'string', segments = segments}
end



-- (( 1+2+3 ))     only_boolean=false
-- [[ 1+2+3 ]]     only_boolean=true
function ast.EmbeddedLuaExpression(expr, only_boolean)
   return {class = 'embeddedluaexpression', expression = expr, only_boolean = only_boolean}
end



return ast
