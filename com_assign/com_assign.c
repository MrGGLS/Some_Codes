# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <math.h>
# include "com_assign.h"
# include "com_assign.parser.h"
extern void yyerror(char* s, ...);

struct ast *
newast(int nodetype, struct ast *l, struct ast *r)
{
	struct ast *a = malloc(sizeof(struct ast));
	if(!a) {
		yyerror("out of space");
		exit(0);
	}
	a->nodetype = nodetype;
	a->l = l;
	a->r = r;
	return a;
}

struct ast *
newnum(int i)
{
	struct numval *a = malloc(sizeof(struct numval));
	if(!a) {
		yyerror("out of space");
		exit(0);
	}
	a->nodetype = 'K';
	a->number = i;
	return (struct ast *)a;
}

struct ast *
newcmp(int cmptype, struct ast *l, struct ast *r)
{
	struct ast *a = malloc(sizeof(struct ast));
	if(!a) {
		yyerror("out of space");
		exit(0);
	}
	a->nodetype = '0' + cmptype;
	a->l = l;
	a->r = r;
	return a;
}

struct ast *
newasgn(int nodetype, struct symbol *s, struct ast *v)
{
	struct symasgn *a = malloc(sizeof(struct symasgn));
	if(!a) {
		yyerror("out of space");
		exit(0);
	}
	a->nodetype = nodetype;
	a->s = s;
	a->v = v;
	return (struct ast *)a;
}

struct ast *
newflow(int nodetype, struct ast *cond, struct ast *tl, struct ast *el)
{
	struct flow *a = malloc(sizeof(struct flow));
	if(!a) {
		yyerror("out of space");
		exit(0);
	}
	a->nodetype = nodetype;
	a->cond = cond;
	a->tl = tl;
	a->el = el;
	return (struct ast *)a;
}

void
treefree(struct ast *a)
{
	if (!a) return;

	switch(a->nodetype) {
		/* 两棵子树 */
		case '+':
		case '-':
		case '*':
		case '/':
		case '1': case '2': case '3': case '4': case '5': case '6':
		case ';':
		case 'a':
		case 'L':{
		  treefree(a->r);
		}

		/* 一棵子树 */
		case 'i':
		case 'M':{
		  treefree(a->l);
		}

		/* 没有子树 */
		case 's':
		case 'K':
		case '=':
		case 666:
		case 777:
		case '0':
		  break;

		/* 最多三棵子树 */
		case 'I':
		case 'W': {
		  treefree(((struct flow *)a)->cond);
		  if(((struct flow *)a)->tl)
			  treefree(((struct flow *)a)->tl);
		  if(((struct flow *)a)->el)
			  treefree(((struct flow *)a)->el);
		  break;
		}

		default: printf("internal error: free bad node '%c'\n", a->nodetype);
	}
	free(a);  /* 总是释放节点自身 */
}

int printtree(struct ast *a, int cnt)
{
	int lend;
	if(!a) return cnt;	// do not print null node.
	switch(a->nodetype) {
		/* 两棵子树 */
		case '+':
		case '-':
		case '*':
		case '/':
		case '1': case '2': case '3': case '4': case '5': case '6':
		case ';':
		case 'a':
		case 'L':{
		  if(a->nodetype == '1') printf("%d [label = \">\"]\n",cnt);
		  else if(a->nodetype == '2') printf("%d [label = \"<\"]\n",cnt);
		  else if(a->nodetype == '3') printf("%d [label = \"<>\"]\n",cnt);
		  else if(a->nodetype == '4') printf("%d [label = \"==\"]\n",cnt);
		  else if(a->nodetype == '5') printf("%d [label = \">=\"]\n",cnt);
		  else if(a->nodetype == '6') printf("%d [label = \"<=\"]\n",cnt);
		  else if(a->nodetype == 'a') printf("%d [label = \"and\"]\n",cnt);
		  else printf("%d [label = \"%c\"]\n",cnt, a->nodetype);	// root.
		  if (a->l)
		  	printf("%d -> %d [label = \"l\"]\n",cnt, cnt+1);
		  lend=printtree(a->l,cnt+1);				// left.
		  if (a->r)
		  	printf("%d -> %d [label = \"r\"]\n",cnt, lend);
		  lend=printtree(a->r,lend);				// right.
		  break;
		}

		/* 一棵子树 */
		case 'M':{
		  printf("%d [label = \"-\"]\n",cnt);
		  printf("%d -> %d [label = \"l\"]\n",cnt,cnt+1);
		  lend=printtree(a->l,cnt+1);
		  break;
		}
		case 'i':{
			printf("%d [label = \"int\"]\n",cnt);
		  	printf("%d -> %d [label = \"l\"]\n",cnt,cnt+1);
			lend=printtree(a->l,cnt+1);
			break;
		}

		/* 没有子树 */
		case 'K':{
		  printf("%d [label = \"%d\"]\n",cnt, ((struct numval*)a)->number);
		  lend=cnt+1;
		  break;
		}
		case 's':{
			printf("%d [label = \"skip\"]\n",cnt);
			lend=cnt+1;
			break;
		}
		case '=':{
		  printf("%d [label = \"=\"]\n",cnt);
		  printf("%d -> %d [label = \"l\"]\n",cnt, cnt+1);
		  printf("%d [label = \"%s\"]\n",cnt+1,((struct symasgn*)a)->s->name);
		  // printf("%c %s ", ((struct symasgn*)a)->nodetype, ((struct symasgn*)a)->s->name);
		  printf("%d -> %d [label = \"r\"]\n",cnt,cnt+2);
		  lend=printtree(((struct symasgn*)a)->v,cnt+2);
		  break;
		}
		case 666:{
		  printf("%d [label = \"<==\"]\n",cnt);
		  printf("%d -> %d [label = \"l\"]\n",cnt, cnt+1);
		  printf("%d [label = \"%s\"]\n",cnt+1,((struct symasgn*)a)->s->name);
		  // printf("<== %s ", ((struct symasgn*)a)->s->name);
		  printf("%d -> %d [label = \"r\"]\n",cnt,cnt+2);
		  lend=printtree(((struct symasgn*)a)->v,cnt+2);
		  break;
		}
		case 777:{
		  printf("%d [label = \":=\"]\n",cnt);
		  printf("%d -> %d [label = \"l\"]\n",cnt, cnt+1);
		  printf("%d [label = \"%s\"]\n",cnt+1,((struct symasgn*)a)->s->name);
		  // printf("<== %s ", ((struct symasgn*)a)->s->name);
		  printf("%d -> %d [label = \"r\"]\n",cnt,cnt+2);
		  lend=printtree(((struct symasgn*)a)->v,cnt+2);
		  break;
		}

		case '0':
			lend=cnt+1;
			printf("%d [label = \"%s\"]\n",cnt, ((struct symasgn*)a)->s->name);
			// printf("%s ", ((struct symasgn*)a)->s->name);
			break;

		/* 最多三棵子树 */
		case 'I':{
		  printf("%d [label = \"if\"]\n",cnt);
		  printf("%d -> ",cnt);
		  // printf("if (");			// root: I, W
		  printf("%d [label = \"l\"]\n",cnt+1);
		  printf("%d [label = \"cond\"]\n",cnt+1);
		  printf("%d -> ",cnt+1);
		  printf("%d [label = \"l\"]\n",cnt+2);
		  lend=printtree(((struct flow*)a)->cond,cnt+2);	// cond
		  // printf(") then {");
		  printf("%d -> ",cnt);
		  printf("%d [label = \"m\"]\n",lend+1);
		  printf("%d [label = \"then\"]\n",lend+1);
		  printf("%d -> ",lend+1);
		  printf("%d [label = \"l\"]\n",lend+2);
		  lend=printtree(((struct flow*)a)->tl,lend+2);	// tl
		  // printf("} else {");
		  printf("%d -> ",cnt);
		  printf("%d [label = \"r\"]\n",lend+1);
		  printf("%d [label = \"else\"]\n",lend+1);
		  printf("%d -> ",lend+1);
		  printf("%d [label = \"l\"]\n",lend+2);
		  lend=printtree(((struct flow*)a)->el,lend+2);	// el
		  // printf("}");
		  break;
		}

		default: printf("internal error: print bad node '%c'\n", a->nodetype);
	}
	return lend;
}
