/* 
可以从不同的角度来评价，
这个可以看clean code里面的：先按照记忆中的一些想一想哈：

变量：
函数：
变量和函数都有命名上的问题。--不过命名问题，更本质上来说，是语义的表达
还有函数是算法的具体实现，可以划分成层次，每一层细致地干什么活，这样，
不用一下子看一大段程序，便于理解。而且划分之后，再命名，就更清晰地解释
了算法。

所以只是单独列一下记得的评判，之后要弄成通用的，好添加不同的评判标准，
然后有不同的显示模块。

1. 全局变量数量、被外部调用的次数
2. 内聚性：静态变量和函数（这个不太好弄）调用关系，（这个是放到单个文件中来说的）
3. 函数调用的次数（按照比例来）
4. 函数被外部调用的次数

注意，统计的时候，可能涉及变量和函数两个方面的问题，比较复杂

但是统计出来，只是作为表征，怎么改还需要进一步探索。而且是不是表征好了，
可复用的性能就好了呢？
这个还是有待讨论的。
所以先就弄出可以明显改进的表征参数吧。

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

