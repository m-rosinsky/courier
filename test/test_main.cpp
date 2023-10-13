/*!
 * @file test/test_main.cpp
 *
 * @brief This file contains the entry point for all tests.
 */

#include "courier_test/courier_test.hpp"

void test_func_1(void)
{
    int t;
    COURIER_ASSERT_EQUAL(t, 3);
    return;
}

void test_func_2(void)
{
    int x = 3;
    COURIER_ASSERT_EQUAL(x, 3);
    return;
}

int main()
{
    // Create the courier unit test object.
    CourierUnitTest main_test("main_test");

    // Create the first test suite.
    CourierTestSuite suite_1("suite 1");
    suite_1.add_test("test_func_1", test_func_1);
    suite_1.add_test("test_func_2", test_func_2);

    // Add the suite to the unit test.
    main_test.add_suite(suite_1);

    // Run the tests.
    main_test.run_tests();

    // Return the error.
    return main_test.get_error();
}

/***   end of file   ***/
