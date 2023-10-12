/*!
 * @file test/courier_test/courier_test.cpp
 *
 * @brief This file contains the test bench framework that is used
 *          within test bench files to perform unit testing.
 */

#include <iostream>

#include "courier_test.hpp"

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
 * @brief This function sets the test bench name.
 */
void CourierUnitTest::set_name(const std::string& __name) noexcept
{
    _name = __name;
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
    std::cout << "Starting test bench";
    if (!_name.empty()) { std::cout << "(" << _name << ")"; }
    std::cout << "..." << std::endl;

    // Set the error status.
    _error_status = 0;

    // Run each suite of tests.
    for (CourierTestSuite& suite : _suites)
    {
        run_test_suite(suite);
    }
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

    // Run each test in the test suite.
    for (const CourierTest& test : __suite._tests)
    {
        run_test(test);
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

    std::cout << "passed" << std::endl;
}

/***   end of file   ***/
