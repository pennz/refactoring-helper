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

Suite * preparation_suite(void); // could put to a seperate file
Suite * dot_suite(void);

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
//srunner_add_suite (sr, preparation_suite);
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

