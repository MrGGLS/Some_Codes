
%option noyywrap nodefault yylineno

%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdarg.h>
	#include "com_assign.h"
	#include "com_assign.parser.h"
	void yyerror(char* s, ...);
%}

%%
"+" |
"-" |
"*" |
"/" |
"=" |
"|" |
"," |
";" |
"(" |
")" |
"{" |
"}" { return yytext[0]; }

">" { yylval.fn = 1; return CMP; }
"<" { yylval.fn = 2; return CMP; }
"<>" { yylval.fn = 3; return CMP; }
"==" { yylval.fn = 4; return CMP; }
">=" { yylval.fn = 5; return CMP; }
"<=" { yylval.fn = 6; return CMP; }
"<==" { return ASSIGN1; }
":=" { return ASSIGN2; }

"if"	{ return IF; }
"then"	{ return THEN; }
"else"	{ return ELSE; }
"and"   { return AND; }
"skip"  { return SKIP; }
"int"   { return INT; }
"#" 	{ return EOI; }

[a-zA-Z][a-zA-Z0-9]* {
	struct symbol *s = (struct symbol*)malloc(sizeof(struct symbol));
	s->name = strdup(yytext);
	s->value = 0;
	yylval.s = s;
	return NAME;
}

[0-9]+ { yylval.i = atoi(yytext); return NUM; }

\n { yylineno++; }
[ \t]+

.	{ yyerror("Mystery character %c\n", *yytext); }

%%
void yyerror(char* s, ...) {
	va_list ap;
	va_start(ap,s);

	fprintf(stderr, "%d: error: ", yylineno);
	vfprintf(stderr, s, ap);
	fprintf(stderr, "\n");
}
