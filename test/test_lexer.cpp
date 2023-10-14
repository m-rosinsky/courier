/*!
 * @file test/test_lexer.cpp
 *
 * @brief This file contains test functions for testing
 *          the lexer functionality with couriers built-in
 *          unit test suite.
 */

#include <cstdio>               // std::remove
#include <fstream>              // std::ifstream, std::ofstream
#include <string>               // std::string

#include "courier_test/courier_test.hpp"
#include "test_lexer.hpp"

#include "../src/lexer/lexer.hpp"
#include "../src/error/error.hpp"

/******************************************************************************/
/*                             Static globals                                 */
/******************************************************************************/

static Lexer g_lexer;

/******************************************************************************/
/*                             Static functions                               */
/******************************************************************************/

/*!
 * @brief This static function creates a text file with desired contents.
 *
 * @return 0 on success, -1 on error.
 */
static int
create_test_file(const std::string& __fname, const std::string& __contents)
{
    int status = 1;

    // Create output filestream object.
    std::ofstream out_file;

    // Open the file.
    out_file.open(__fname, std::ios::out);

    // Error check.
    if (!out_file.is_open())
    {
        goto EXIT;
    }

    // Write to file.
    out_file << __contents;

    // Error check.
    if (out_file.fail())
    {
        goto EXIT;
    }

    // Mark success.
    status = 0;

    EXIT:
        if (out_file.is_open())
        {
            out_file.close();
        }
        return status;
}

/******************************************************************************/
/*                              Test functions                                */
/******************************************************************************/

/*!
 * @brief This function tests the lexer against an empty file.
 *
 * @result The lexer should succeed in this case.
 */
void test_lexer_empty(void)
{
    // Create test file.
    std::string fname = "/tmp/lexer_empty.txt";
    std::string contents = "";

    int status = create_test_file(fname, contents);
    COURIER_ASSERT_EQUAL(status, 0);
    if (0 != status) { return; }

    // Lex test file.
    g_lexer.tokenize_file(fname);

    // Ensure no error was returned.
    COURIER_ASSERT(g_lexer.get_error().is_success());

    // The token table should be empty.
    COURIER_ASSERT_EQUAL(g_lexer.get_table().size(), 0);

    // Destroy test file.
    status = std::remove(fname.c_str());
    COURIER_ASSERT_EQUAL(status, 0);
}

/******************************************************************************/

/*!
 * @brief This function tests the lexer against a valid one-line file.
 *
 * @result The lexer should succeed in this case.
 */
void test_lexer_one_line(void)
{
    // Create test file.
    std::string fname = "/tmp/lexer_one_line.txt";
    std::string contents = "x = 14; y = 2 + 2; {3 + 3}";

    int status = create_test_file(fname, contents);
    COURIER_ASSERT_EQUAL(status, 0);
    if (0 != status) { return; }

    // Lex test file.
    g_lexer.tokenize_file(fname);

    // Ensure no error was returned.
    COURIER_ASSERT(g_lexer.get_error().is_success());

    // Ensure the correct number of tokens were returned.
    COURIER_ASSERT_EQUAL(g_lexer.get_table().size(), 15);

    // Ensure the line number for all tokens is 1.
    for (auto it = g_lexer.get_table().begin(); it != g_lexer.get_table().end(); ++it)
    {
        COURIER_ASSERT_EQUAL(it->get()->_line_num, 1);
    }

    // Destroy test file.
    status = std::remove(fname.c_str());
    COURIER_ASSERT_EQUAL(status, 0);
}

/******************************************************************************/

/*!
 * @brief This function tests the lexer against a valid multi-line file.
 *
 * @result The lexer should succeed in this case.
 */
void test_lexer_multi_line(void)
{
    // Create test file.
    std::string fname = "/tmp/lexer_multi_line.txt";
    std::string contents = "x = 14;\ny = 1;";

    int status = create_test_file(fname, contents);
    COURIER_ASSERT_EQUAL(status, 0);
    if (0 != status) { return; }

    // Lex test file.
    g_lexer.tokenize_file(fname);

    // Ensure no error was returned.
    COURIER_ASSERT(g_lexer.get_error().is_success());

    // Ensure the correct number of tokens were returned.
    COURIER_ASSERT_EQUAL(g_lexer.get_table().size(), 8);

    // Destroy test file.
    status = std::remove(fname.c_str());
    COURIER_ASSERT_EQUAL(status, 0);
}

/******************************************************************************/

/*!
 * @brief This function tests the lexer against a file with a bad numeric
 *          literal.
 *
 * @result The lexer should return an error of type ERR_INVAL_NUM.
 */
void test_lexer_bad_num(void)
{
    // Create test file.
    std::string fname = "/tmp/lexer_bad_num.txt";
    std::string contents = "x = 4a"; // Invalid number '4a'

    int status = create_test_file(fname, contents);
    COURIER_ASSERT_EQUAL(status, 0);
    if (0 != status) { return; }

    // Lex test file.
    g_lexer.tokenize_file(fname);

    // Ensure proper error was returned.
    COURIER_ASSERT_EQUAL(g_lexer.get_error()._status, ERR_INVAL_NUM);

    // Destroy test file.
    status = std::remove(fname.c_str());
    COURIER_ASSERT_EQUAL(status, 0);
}

/******************************************************************************/

/*!
 * @brief This function tests the lexer against a file with unicode characters.
 *
 * @result The lexer should return an error of type ERR_UNREC_SYMB.
 */
void test_lexer_unicode(void)
{
    // Create test file.
    std::string fname = "/tmp/lexer_unicode.txt";
    std::string contents = "😀😁😑"; // Invalid unicode.

    int status = create_test_file(fname, contents);
    COURIER_ASSERT_EQUAL(status, 0);
    if (0 != status) { return; }

    // Lex test file.
    g_lexer.tokenize_file(fname);

    // Ensure proper error was returned.
    COURIER_ASSERT_EQUAL(g_lexer.get_error()._status, ERR_UNREC_SYMB);

    // Destroy test file.
    status = std::remove(fname.c_str());
    COURIER_ASSERT_EQUAL(status, 0);
}

/***   end of file   ***/
