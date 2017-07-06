/*
修改成在tree中漫游的时候，一边漫游，一边统计信息？
。。。第一遍的目的是快速完成程序，现在可以参照的就是那个
tceetree的程序，所以先看懂那个，再定夺以下的一个问题：
是边漫游边统计信息，还是已经形成树的结构，然后再在
树的基础上漫游。
先形成树吧？不过如果不这样，一边漫游，一边统计信息会不会有遗漏的？这样弄起来
编程的效率更加高些，不过也要先熟悉相关的代码。

hook 定义在树上漫游的钩子点，然后一边统计信息
*/
#include <stdlib.h>
#include <check.h>
#include "../src/counter.h"
#include "../src/dot_writer.h"

START_TEST(test_counter_create)
{
	Counter *counter;

	counter = counter_create("type", "path");
	ck_assert_str_eq(counter_path(counter), "path");
	counter_free(counter);
}
END_TEST

START_TEST(test_build_tree)// one then two or more
{
	// build the simplest one first
	char *cscope_file_name = prepare_cscope_file(project_folder);
	Calltree t = parse_cscope_file(cscope_file_name); // just parse with the default parameters, should add configuration later
	// TODO: add configure structure
	ck_assert_int_eq(tree_depth(t), 3);
	ck_assert_int_eq(tree_nodes_count(t), 3);
}
END_TEST

START_TEST(test_generate_tree_1_file)// one then two or more
{

}
END_TEST

START_TEST(test_layer_count)
{

}
END_TEST

START_TEST(test_stat_per_file)// add fixture to generate tree first// per module
{

}
END_TEST

//START_TEST(test_)
//{
//
//}
//END_TEST
/* test_dot_out
 * test_png_out
 *
 * test_find_node // node can be function, file, module, thus, the tree can represent different abstract layers.
 * test_tree_init
 * test_tree_free
 *
 * test_generate_as_module
 *
 * test_struct_flow
 * test_call_paras, - get stats about arguments--output, could be different color
 *
 * test_header_and_implementation
 *
 * test_function_line_count// need to read the file, the cscope does not do this
 *
 * test_encap_module // the underlying structure, module, file
 */
Suite * preparation_suite(void); // could put to a seperate file
Suite * fileIO_suite(void); // could put to a seperate file
Suite * dot_suite(void);// need add fixture, test file, delete file or something

Suite * preparation_suite(void)
{
	Suite *s;

	TCase *tc_builder;


	s = suite_create("Prepare");

	/* Core test case */
	tc_builder = tcase_create("build_tree");
	tcase_add_test(tc_builder, test_build_tree);

	suite_add_tcase(s, tc_builder);

	return s;
}
//	TCase *tc_generate_report; // put into relating suites!!
//	TCase *tc_prepare_database;
//	TCase *tc_analysis;	// analysis the layer structure, get the parameters
Suite * counter_suite(void)
{
	Suite *s;
	TCase *tc_core;


	s = suite_create("Counter");

	/* Core test case */
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_counter_create);

	suite_add_tcase(s, tc_core);

	return s;
}
static void add_additional_suites(SRunner *sr)
{
	srunner_add_suite (sr, preparation_suite());
//srunner_add_suite (sr, dot_suite);
}
int main(void)
{
	int number_failed;
	Suite *s;
	SRunner *sr;

	s = counter_suite();
	sr = srunner_create(s);
	add_additional_suites(sr);
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

