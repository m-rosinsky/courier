/*!
 * @file test/test_object.cpp
 *
 * @brief This file contains test functions for testing
 *          the object functionality with couriers built-in
 *          unit test suite.
 */

#include <string>           // std::string

#include "courier_test/courier_test.hpp"
#include "test_object.hpp"

#include "../src/object/object_signed_int.hpp"
#include "../src/object/object_unsigned_int.hpp"

/******************************************************************************/
/*                              Test functions                                */
/******************************************************************************/

/*!
 * @brief This function tests the functionality of the signed integer
 *          object type.
 */
void test_object_signed_int(void)
{
    // Test default.
    ObjectSignedInt i1;
    COURIER_ASSERT_EQUAL(i1.get_type(), OBJECT_TYPE_SIGNED_INT);
    COURIER_ASSERT_EQUAL(i1.get_type_string(), "int");
    COURIER_ASSERT_EQUAL(i1.to_string(), "0");

    // Test assigned value and width.
    ObjectSignedInt i2(3, 32);
    COURIER_ASSERT_EQUAL(i2.get_type(), OBJECT_TYPE_SIGNED_INT);
    COURIER_ASSERT_EQUAL(i2.get_type_string(), "int");
    COURIER_ASSERT_EQUAL(i2.to_string(), "3");
}

/******************************************************************************/

/*!
 * @brief This function tests the functionality of the unsigned integer
 *          object type.
 */
void test_object_unsigned_int(void)
{
    // Test default.
    ObjectUnsignedInt u1;
    COURIER_ASSERT_EQUAL(u1.get_type(), OBJECT_TYPE_UNSIGNED_INT);
    COURIER_ASSERT_EQUAL(u1.get_type_string(), "uint");
    COURIER_ASSERT_EQUAL(u1.to_string(), "0");

    // Test assigned value and width.
    ObjectUnsignedInt u2(3, 32);
    COURIER_ASSERT_EQUAL(u2.get_type(), OBJECT_TYPE_UNSIGNED_INT);
    COURIER_ASSERT_EQUAL(u2.get_type_string(), "uint");
    COURIER_ASSERT_EQUAL(u2.to_string(), "3");
}

/***   end of file   ***/
