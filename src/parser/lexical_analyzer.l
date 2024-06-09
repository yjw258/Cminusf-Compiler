%option noyywrap
%{
/*****************声明和选项设置  begin*****************/
#include <stdio.h>
#include <stdlib.h>

#include "syntax_tree.h"
#include "syntax_analyzer.h"

int lines;
int pos_start;
int pos_end;

void pass_node(char *text){
     yylval.node = new_syntax_tree_node(text);
}

/*****************声明和选项设置  end*****************/

%}


%%
 /* to do for students */
 /* two cases for you, pass_node will send flex's token to bison */
<<<<<<< HEAD

 /* keyword */
else {pos_start = pos_end; pos_end += strlen(yytext); pass_node(yytext); return ELSE;}
if {pos_start = pos_end; pos_end += strlen(yytext); pass_node(yytext); return IF;}
int {pos_start = pos_end; pos_end += strlen(yytext); pass_node(yytext); return INT;}
return {pos_start = pos_end; pos_end += strlen(yytext); pass_node(yytext); return RET;}
void {pos_start = pos_end; pos_end += strlen(yytext); pass_node(yytext); return VOID;}
while {pos_start = pos_end; pos_end += strlen(yytext); pass_node(yytext); return WHILE;}
float {pos_start = pos_end; pos_end += strlen(yytext); pass_node(yytext); return FLOAT;}

 /* special symbols*/
"<="|">="|"<"|">"|"=="|"!=" {pos_start = pos_end; pos_end += strlen(yytext); pass_node(yytext); return RELOP;}
"=" {pos_start = pos_end; pos_end += strlen(yytext); pass_node(yytext); return ASSIGN;}
"+"|"-" {pos_start = pos_end; pos_end += 1; pass_node(yytext); return ADDOP;}
";" {pos_start = pos_end; pos_end += strlen(yytext); pass_node(yytext); return SEM;}
"," {pos_start = pos_end; pos_end += strlen(yytext); pass_node(yytext); return COMMA;}
"(" {pos_start = pos_end; pos_end += strlen(yytext); pass_node(yytext); return LPAREN;}
")" {pos_start = pos_end; pos_end += strlen(yytext); pass_node(yytext); return RPAREN;}
"[" {pos_start = pos_end; pos_end += strlen(yytext); pass_node(yytext); return LBRACK;}
"]" {pos_start = pos_end; pos_end += strlen(yytext); pass_node(yytext); return RBRACK;}
"{" {pos_start = pos_end; pos_end += strlen(yytext); pass_node(yytext); return LBRACE;}
"}" {pos_start = pos_end; pos_end += strlen(yytext); pass_node(yytext); return RBRACE;}
\/\*([^\*])*((\*)+[^\*\/]([^\*])*)*(\*)*\*\/  {pos_start = pos_end; pos_end += strlen(yytext);}
"*"|"/" {pos_start = pos_end; pos_end += 1; pass_node(yytext); return MULOP;}

 /* ID & NUM */
[a-zA-Z]+ {pos_start = pos_end; pos_end += strlen(yytext); pass_node(yytext); return ID;}
[0-9]+\.|[0-9]*\.[0-9]+ {pos_start = pos_end; pos_end += strlen(yytext); pass_node(yytext); return FLOATNUM;}
[0-9]+ {pos_start = pos_end; pos_end += strlen(yytext); pass_node(yytext); return INTEGER;}

 /* other thing */
\n {lines++; pos_start = pos_end = 0;}
" "|\t {pos_end++;}
. { pos_start = pos_end; pos_end++; return ERROR; }

 /****请在此补全所有flex的模式与动作  end******/
%%
=======
 /* special symbols*/
\+ 	{pos_start = pos_end; pos_end += 1; pass_node(yytext); return ADD;}
\-   {pos_start = pos_end; pos_end += 1; pass_node(yytext); return SUB;}
\*   {pos_start = pos_end; pos_end += 1; pass_node(yytext); return MUL;}
\/   {pos_start = pos_end; pos_end += 1; pass_node(yytext); return DIV;}
\<   {pos_start = pos_end; pos_end += 1; pass_node(yytext); return LT;}
"<=" {pos_start = pos_end; pos_end += 2; pass_node(yytext); return LTE;}
\>   {pos_start = pos_end; pos_end += 1; pass_node(yytext); return GT;}
">=" {pos_start = pos_end; pos_end += 2; pass_node(yytext); return GTE;}
"==" {pos_start = pos_end; pos_end += 2; pass_node(yytext); return EQ;}
"!=" {pos_start = pos_end; pos_end += 2; pass_node(yytext); return NEQ;}
\=   {pos_start = pos_end; pos_end += 1; pass_node(yytext); return ASSIGN;}
\;   {pos_start = pos_end; pos_end += 1; pass_node(yytext); return SEMICOLON;}
\,   {pos_start = pos_end; pos_end += 1; pass_node(yytext); return COMMA;}
\(   {pos_start = pos_end; pos_end += 1; pass_node(yytext); return LPAREN;}
\)   {pos_start = pos_end; pos_end += 1; pass_node(yytext); return RPAREN;}
\[   {pos_start = pos_end; pos_end += 1; pass_node(yytext); return LBRACKET;}
\]   {pos_start = pos_end; pos_end += 1; pass_node(yytext); return RBRACKET;}
\{   {pos_start = pos_end; pos_end += 1; pass_node(yytext); return LBRACE;}
\}   {pos_start = pos_end; pos_end += 1; pass_node(yytext); return RBRACE;}

 /* keyword */
else {pos_start = pos_end; pos_end += 4; pass_node(yytext); return ELSE;}
if   {pos_start = pos_end; pos_end += 2; pass_node(yytext); return IF;}
int  {pos_start = pos_end; pos_end += 3; pass_node(yytext); return INT;}
return    {pos_start = pos_end; pos_end += 6; pass_node(yytext); return RETURN;}
void {pos_start = pos_end; pos_end += 4; pass_node(yytext); return VOID;}
while     {pos_start = pos_end; pos_end += 5; pass_node(yytext); return WHILE;}
float     {pos_start = pos_end; pos_end += 5; pass_node(yytext); return FLOAT;}

 /* ID & NUM */
[a-zA-Z]+ {pos_start = pos_end; pos_end += strlen(yytext); pass_node(yytext); return ID;}
[0-9]+    {pos_start = pos_end; pos_end += strlen(yytext); pass_node(yytext); return INTEGER;}
[0-9]+\.|[0-9]*\.[0-9]+  {pos_start = pos_end; pos_end += strlen(yytext); pass_node(yytext); return FLOATPOINT;}

 /* comment */
"/*"([^\*]|(\*)*[^\*/])*(\*)*"*/" {
     for(int i = 0; i < strlen(yytext); i++){
          pos_start = pos_end;
          if(yytext[i] == '\n')
          {
               lines += 1;
               pos_start = 1;
               pos_end = 1;
          }
          else
          {
               pos_start = pos_end;
               pos_end += 1;
          }
     }
}

 /* other things */
\n { pos_start = 1; pos_end = 1; lines += 1; }
" "|\t  { pos_start = pos_end; pos_end += strlen(yytext); }
. { pos_start = pos_end; pos_end++; return ERROR; }

 /****请在此补全所有flex的模式与动作  end******/
%%
>>>>>>> c7f1069 (commit all)
