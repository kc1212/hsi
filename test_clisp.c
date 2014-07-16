
#include <assert.h>

#include "mpc/mpc.h"

#include "common.h"
#include "eval.h"
#include "parser.h"

#define run_test(fn_name)\
	printf("%s", #fn_name);\
	fprintf(stderr, "%s\n", #fn_name);\
	fn_name();\
	for (size_t i = 0; i < 20 - strlen(#fn_name); i++) printf(".");\
	printf("OK\n");

int ast_size(mpc_ast_t* ast)
{
	if (!ast)
		return -1;

	int ctr = 1;
	if (ast->children_num > 0) // if child_num is 0, 1 is returned
	{
		for (int i = 0; i < ast->children_num; i++)
		{
			ctr += ast_size(ast->children[i]);
		}
	}
	return ctr;
}

void test_lval_num()
{
	lval v = lval_num(123);
	assert(LVAL_NUM == v.type);
	assert(123 == v.num);
}

void test_lval_err()
{
	lval v = lval_err(123);
	assert(LVAL_ERR == v.type);
	assert(123 == v.err);
}

void test_ast_size_5()
{
	mpc_ast_t* ast = parse("+ 1");
	assert(5 == ast_size(ast));
}


int main(void)
{
	FILE* fp = freopen(LOGFILE, "w+", stderr);
	if (NULL == fp)
	{
		log_err("freopen failed on %s", LOGFILE);
		return 1;
	}

	init_parser();
	run_test(test_lval_num);
	run_test(test_lval_err);
	run_test(test_ast_size_5);
	printf("Done\n");

	fclose(fp);
	return 0;
}


