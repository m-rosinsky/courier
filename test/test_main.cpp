/*!
 * @file test/test_main.cpp
 *
 * @brief This file contains the entry point for all tests.
 */

#include "courier_test/courier_test.hpp"
#include "test_lexer.hpp"
#include "test_object.hpp"

int main()
{
    // Create the courier unit test object.
    CourierUnitTest courier_test("courier_test");

    // Lexer test suite.
    CourierTestSuite lexer_test_suite_1("lexer_test_suite_1");
    lexer_test_suite_1.add_test("test_lexer_empty", test_lexer_empty);
    lexer_test_suite_1.add_test("test_lexer_one_line", test_lexer_one_line);
    lexer_test_suite_1.add_test("test_lexer_multi_line", test_lexer_multi_line);
    lexer_test_suite_1.add_test("test_lexer_bad_num", test_lexer_bad_num);
    lexer_test_suite_1.add_test("test_lexer_unicode", test_lexer_unicode);
    courier_test.add_suite(lexer_test_suite_1);

    // Object test suite.
    CourierTestSuite object_test_suite_1("object_test_suite_1");
    object_test_suite_1.add_test("test_object_signed_int", test_object_signed_int);
    object_test_suite_1.add_test("test_object_unsigned_int", test_object_unsigned_int);
    courier_test.add_suite(object_test_suite_1);

    // Run the tests and return error.
    courier_test.run_tests();
    return courier_test.get_error();
}

/***   end of file   ***/
