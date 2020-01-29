# Localization Interpolation Syntax

Elona foobar has a string interpolation system to localize various text. Here is a complete syntax of the interpolation.


## Syntax in EBNF

The syntax is writte in Extended Backus-Naur form (EBNF).


```
replacement  ::=  "{" exp "}"

exp          ::=  "nil"
               |  "false"
               |  "true"
               |  INT
               |  FLOAT
               |  STR
               |  IDENT "(" args ")"
               |  IDENT "." IDENT "(" args ")"

args         ::=  { exp separated by "," }

IDENT        ::=  /[A-Za-z_][A-Za-z_0-9]*/
INT          ::=  /[0-9]+/
FLOAT        ::=  /TBD/
STR          ::=  /TBD/
```
