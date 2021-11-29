%{
# include <stdio.h>
# include <stdlib.h>
# include "com_assign.h"
extern void yyerror(char *s, ...);
struct ast *ast_root = NULL;
%}

%union{
	struct ast *a;
	int i;
	struct symbol *s;
	int fn;
}

%token <i> NUM
%token <s> NAME
%token IF THEN ELSE AND SKIP INT EOI

%nonassoc <fn> CMP
%right '=' ASSIGN1 ASSIGN2
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%type <a> exp stmt list iniv

%start topList
%%
stmt: IF exp THEN list { $$ = newflow('I',$2,$4,NULL); }
   | IF exp THEN list ELSE list { $$ = newflow('I',$2,$4,$6); }
   | exp
   | exp AND exp { $$ = newast('a',$1,$3); }
	| stmt ';' stmt {$$ = newast(';',$1,$3); }
	| stmt ';' { $$ = newast(';',$1,NULL); }
;

list: /* 空 */ { $$ = NULL; }
	| exp
;

exp: exp CMP exp { $$ = newcmp($2,$1,$3); }
   | exp '+' exp { $$ = newast('+',$1,$3); }
   | exp '-' exp { $$ = newast('-',$1,$3); }
   | exp '*' exp { $$ = newast('*',$1,$3); }
   | exp '/' exp { $$ = newast('/',$1,$3); }
   | '(' exp ')' { $$ = $2; }
   | '{' exp '}' { $$ = $2; }
   | '-' exp %prec UMINUS { $$ = newast('M',$2,NULL); }
   | NUM { $$ = newnum($1); }
   | SKIP { $$ = newast('s',NULL,NULL); }
   | INT exp { $$ = newast('i',$2,NULL); }
   | NAME { $$ = newasgn('0',$1,0); }
   | NAME '=' exp { $$ = newasgn('=',$1,$3); }
   | NAME ASSIGN1 exp {$$ = newasgn(666,$1,$3); }
   | NAME ASSIGN2 exp {$$ = newasgn(777,$1,$3); }
;

topList:
	| topList stmt EOI {
		ast_root=$2;
		printtree(ast_root,0);
		treefree($2);
	}
;

%%