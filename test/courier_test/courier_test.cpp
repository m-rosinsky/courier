/*!
 * @file test/courier_test/courier_test.cpp
 *
 * @brief This file contains the test bench framework that is used
 *          within test bench files to perform unit testing.
 */

#include <iostream>

#include "courier_test.hpp"

/******************************************************************************/
/*                       CourierUnitTest Globals                              */
/******************************************************************************/

// The global value for number of assertions and failed assertions.
static uint32_t g_num_assert = 0;
static uint32_t g_num_assert_fail = 0;

// The global value for number of tests and number of failed tests.
static uint32_t g_num_test = 0;
static uint32_t g_num_test_fail = 0;

// The global value for number of suites and number of failed suites.
static uint32_t g_num_suite = 0;
static uint32_t g_num_suite_fail = 0;

// The struct defining a failed assertion.
struct fail_t
{
    uint32_t _line;
    std::string _file;
    std::string _s_value;

    fail_t(uint32_t __line,
           const std::string& __file,
           const std::string& __s_value)
        : _line(__line), _file(__file), _s_value(__s_value) {}
};

// The global vector for holding failed assertions.
static std::vector<fail_t> g_fails;

/******************************************************************************/

/*!
 * @brief This function handles the assertion macros and adjusts the globals
 *          accordingly.
 *
 * @param[in] __b_value The value to assert true.
 * @param[in] __s_value A string representation of the assertion.
 * @param[in] __line The line number for the assertion.
 * @param[in] __file The file for the assertion.
 */
void courier_assert(const bool& __b_value,
                    const std::string& __s_value,
                    const uint32_t __line,
                    const std::string& __file)
{
    // Increment the number of assertions.
    g_num_assert++;

    // If the boolean value is false, increment a failed assertion and
    // add to fail vector.
    if (!__b_value)
    {
        g_num_assert_fail++;
        g_fails.emplace_back(__line, __file, __s_value);
    }
}

/******************************************************************************/
/*                            CourierTestSuite                                */
/******************************************************************************/

/*!
 * @brief This function adds a test function with an associated name to
 *          the test suite.
 *
 * @param[in] __name The name of the test.
 * @param[in] __test The test function.
 */
void CourierTestSuite::add_test(const std::string& __name,
                                test_f __test) noexcept
{
    // Emplace the new test object at the back.
    _tests.emplace_back(__name, __test);
}

/******************************************************************************/
/*                    CourierUnitTest Public Functions                        */
/******************************************************************************/

/*!
 * @brief This function returns the error status of the unit test bench.
 */
int CourierUnitTest::get_error(void) const
{
    return _error_status;
}

/******************************************************************************/

/*!
 * @brief This function adds a test suite to a unit test bench.
 *
 * @param[in] __name The name of the test suite.
 * @param[in] __suite The CourierTestSuite object.
 */
void CourierUnitTest::add_suite(const CourierTestSuite& __suite) noexcept
{
    // Emplace a new suite object at the back.
    _suites.push_back(__suite);
}

/******************************************************************************/

/*!
 * @brief This function commences the test bench, running all suites
 *          stored.
 * 
 *          It tracks the number of passed and failed assertions and generates
 *          a report to stdout when finished.
 */
void CourierUnitTest::run_tests(void)
{
    // Let stdout know we are running the test bench.
    std::cout << "Starting test bench ";
    if (!_name.empty()) { std::cout << "(" << _name << ")"; }
    std::cout << "..." << std::endl;

    // Set the error status.
    _error_status = 0;

    // Run each suite of tests.
    for (CourierTestSuite& suite : _suites)
    {
        run_test_suite(suite);
    }

    // Generate numerical report.
    std::cout << "\n\t\t\tRan\tFailed\n";
    std::cout << "Suites: \t\t" << g_num_suite << "\t";
    if (g_num_suite_fail > 0) { std::cout << "\033[31m"; }
    std::cout << g_num_suite_fail << "\033[0m\n";

    std::cout << "Tests:  \t\t" << g_num_test << "\t";
    if (g_num_test_fail > 0) { std::cout << "\033[31m"; }
    std::cout << g_num_test_fail << "\033[0m\n";

    std::cout << "Asserts:\t\t" << g_num_assert << "\t";
    if (g_num_assert_fail > 0) { std::cout << "\033[31m"; }
    std::cout << g_num_assert_fail << "\033[0m" << std::endl; 
}

/******************************************************************************/
/*                    CourierUnitTest Private Functions                       */
/******************************************************************************/

/*!
 * @brief This function runs a single test suite.
 */
void CourierUnitTest::run_test_suite(const CourierTestSuite& __suite)
{
    // Let stdout know we are running the test suite.
    std::cout << "Running test suite '" << __suite._name << "'..." << std::endl;

    // Increment the global number of suites run.
    g_num_suite++;

    // Bookmark number of failed tests.
    uint32_t num_test_fail = g_num_test_fail;

    // Run each test in the test suite.
    for (const CourierTest& test : __suite._tests)
    {
        run_test(test);
    }

    // If the number of failed tests increased, mark the suite as failed.
    if (g_num_test_fail > num_test_fail)
    {
        g_num_suite_fail++;
    }
}

/******************************************************************************/

/*!
 * @brief This function runs a single test.
 */
void CourierUnitTest::run_test(const CourierTest& __test)
{
    // Let stdout know we are running the test.
    std::cout << "Testing '" << __test._name << "'...\t";

    // Increment the global number of tests run.
    g_num_test++;

    // Bookmark the number of failed assertions.
    uint32_t num_assert_fail = g_num_assert_fail;

    __test._test();

    // If we received a failed assert, mark the test as failed.
    if (g_num_assert_fail > num_assert_fail)
    {
        g_num_test_fail++;

        // If any assertions fail, the entire unit test suite should
        // return 1.
        _error_status = 1;

        // Let stdout know the test failed.
        std::cout << "\033[31mfailed\033[0m" << std::endl;

        // Report the failures.
        std::cout << std::endl;
        for (auto& fail : g_fails)
        {
            std::cout << "\033[31mFailure\033[0m ";
            std::cout << "[" << fail._file << ":" << fail._line << "]:\t";
            std::cout << fail._s_value << std::endl;
        }
        std::cout << std::endl;

        // Clear the failed tests.
        g_fails.clear();
    }
    else
    {
        std::cout << "\033[32mpassed\033[0m" << std::endl;
    }
}

/***   end of file   ***/
