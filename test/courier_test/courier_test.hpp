/*!
 * @file test/courier_test/courier_test.hpp
 *
 * @brief This file contains the test bench framework that is used
 *          within test bench files to perform unit testing.
 */

#ifndef _COURIER_TEST_COURIER_TEST_HPP
#define _COURIER_TEST_COURIER_TEST_HPP

#include <functional>           // std::function
#include <string>               // std::string
#include <vector>               // std::vector

/******************************************************************************/
/*                    CourierUnitTest Assert Macros                           */
/******************************************************************************/

/*!
 * @brief This macro tests a basic assertion to be true.
 */
#define COURIER_ASSERT(value) \
    { courier_assert((value), ("COURIER_ASSERT(" #value ")"), __LINE__, __FILE__); }

/*!
 * @brief This macro tests if an actual value matches its expected.
 */
#define COURIER_ASSERT_EQUAL(actual, expected) \
    { courier_assert(((actual) == (expected)), ("COURIER_ASSERT_EQUAL(" #actual "," #expected ")"), __LINE__, __FILE__); }

/******************************************************************************/
/*                  CourierUnitTest Assert Functionality                      */
/******************************************************************************/

void courier_assert(const bool& __b_value,
                    const std::string& __s_value,
                    const uint32_t __line,
                    const std::string& __file);

/******************************************************************************/
/*                        CourierUnitTest Classes                             */
/******************************************************************************/

/*!
 * @brief This typedef provides the function pointer type for
 *          all test functions to follow.
 */
typedef std::function<void(void)> test_f;

/*!
 * @brief This struct contains a single test function with its associated
 *          name.
 */
struct CourierTest
{
    std::string _name;
    test_f _test;

    // Ctor.
    CourierTest() = delete; // Delete default ctor.
    CourierTest(const std::string& __name, test_f __test)
        : _name(__name), _test(__test) {}
};

/*!
 * @brief This struct contains a single test suite, which is a list
 *          of multiple CourierTest and an associated name for the
 *          suite.
 */
struct CourierTestSuite
{
    std::string _name; // The name of the test suite.
    std::vector<CourierTest> _tests;

    // Construct with name.
    CourierTestSuite(const std::string __name)
        : _name(__name) {}

    // Modifiers.
    void add_test(const std::string& __name,
                  test_f __test) noexcept;
};

/*!
 * @brief This class contains the unit testing functionality.
 *
 *          It provides all basic mechanism for conducting
 *              full unit testing.
 */
class CourierUnitTest
{

private:
    std::string _name; // The name of the test bench.

    // This vector contains the test suites.
    std::vector<CourierTestSuite> _suites;

    int _error_status; // The return status of the tests.

public:

    // Delete default ctor.
    CourierUnitTest() = delete;
    CourierUnitTest(const std::string& __name)
        : _name(__name), _error_status(0) {}

    // Accessors.
    int get_error(void) const;

    // Modifiers
    void add_suite(const CourierTestSuite& __suite) noexcept;
    
    // Test functions.
    void run_tests(void);

private:
    // Helper functions.
    void run_test_suite(const CourierTestSuite& __suite);
    void run_test(const CourierTest& __test);

};

#endif // _COURIER_TEST_COURIER_TEST_HPP

/***   end of file   ***/
