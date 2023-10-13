/*!
 * @file test/test_main.cpp
 *
 * @brief This file contains the entry point for all tests.
 */

#include "courier_test/courier_test.hpp"
#include "test_lexer.hpp"

int main()
{
    // Create the courier unit test object.
    CourierUnitTest lexer_test("lexer_test");

    // Create the first test suite.
    CourierTestSuite lexer_test_suite_1("lexer_test_suite_1");
    lexer_test_suite_1.add_test("test_lexer_empty", test_lexer_empty);
    lexer_test_suite_1.add_test("test_lexer_one_line", test_lexer_one_line);
    lexer_test_suite_1.add_test("test_lexer_multi_line", test_lexer_multi_line);

    // Add the suite to the unit test.
    lexer_test.add_suite(lexer_test_suite_1);

    // Run the tests.
    lexer_test.run_tests();

    // Return the error.
    return lexer_test.get_error();
}

/***   end of file   ***/
