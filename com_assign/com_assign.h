/* 与词法分析器的接口 */
extern int yylineno; /* 来自于词法分析器 */
extern int yylex(void);


/* 符号表 */
struct symbol { /* 变量名 */
  char *name;
  int value;
};

/* 抽象语法树中的节点 */
/* 所有节点都有公共的初始nodetype */
struct ast {
  int nodetype;
  struct ast *l;
  struct ast *r;
};

struct flow {
  int nodetype; /* 类型I(if)或者W(while) */
  struct ast *cond; /* 条件 */
  struct ast *tl; /* then分支或者do语句 */
  struct ast *el; /* 可选的else分支 */
};

struct numval {
  int nodetype; /* 类型K 表明常量 */
  int number;
};

struct symasgn {
  int nodetype; /* 赋值类型 = := <== */
  struct symbol *s;
  struct ast *v; /* 值 */
};

/* 构造抽象语法树 */
struct ast *newast(int nodetype, struct ast *l, struct ast *r);
struct ast *newcmp(int cmptype, struct ast *l, struct ast *r);
struct ast *newasgn(int nodetype, struct symbol *s, struct ast *v);
struct ast *newnum(int i);
struct ast *newflow(int nodetype, struct ast *cond, struct ast *tl, struct ast *tr);

/* 删除和释放抽象语法树 */
void treefree(struct ast *);

/* 先序输出语法树 */
int printtree(struct ast *,int cnt);