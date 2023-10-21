/*!
 * @file test/var_test.hpp
 *
 * @brief This file contains tests for the variable handler.
 */

#include <memory>

#include "courier_test/courier_test.hpp"
#include "test_var.hpp"

#include "../src/error/error.hpp"
#include "../src/object/object_signed_int.hpp"
#include "../src/parser/var_handler/var_handler.hpp"

/******************************************************************************/
/*                              Test functions                                */
/******************************************************************************/

/*!
 * @brief This function tests adding a variable to a table.
 */
void test_var_add(void)
{
    // Adding nullptr should succeed.
    VarTable var_table;
    uint8_t result = var_table.add("x", 0, nullptr);
    COURIER_ASSERT_EQUAL(ERR_SUCCESS, result);

    // Adding a valid object should also succeed.
    std::shared_ptr<ObjectSignedInt> obj = std::make_shared<ObjectSignedInt>(5, 32);
    result = var_table.add("y", 0, obj);
    COURIER_ASSERT_EQUAL(ERR_SUCCESS, result);

    // Find should successfully return the shared_ptr.
    std::shared_ptr<Object> find_result = var_table.find("y");
    COURIER_ASSERT_EQUAL(find_result->to_string(), "5");
}

/******************************************************************************/


void test_var_add_dupl(void)
{
    VarTable var_table;
    uint8_t result = var_table.add("x", 0, nullptr);
    COURIER_ASSERT_EQUAL(ERR_SUCCESS, result);

    // Add duplicate variable.
    result = var_table.add("x", 0, nullptr);
    COURIER_ASSERT_EQUAL(ERR_VAR_DUPLICATE, result);

    // A duplicate variable with a higher scope should
    // be successful.
    result = var_table.add("x", 1, nullptr);
    COURIER_ASSERT_EQUAL(ERR_SUCCESS, result);
}


/******************************************************************************/

void test_var_drop(void)
{
    VarTable var_table;
    std::shared_ptr<ObjectSignedInt> obj = std::make_shared<ObjectSignedInt>(5, 32);
    uint8_t result = var_table.add("x", 0, obj);
    COURIER_ASSERT_EQUAL(ERR_SUCCESS, result);
    result = var_table.add("y", 1, nullptr);
    COURIER_ASSERT_EQUAL(ERR_SUCCESS, result);
    result = var_table.add("z", 2, nullptr);
    COURIER_ASSERT_EQUAL(ERR_SUCCESS, result);

    COURIER_ASSERT_EQUAL(var_table.size(), 3);

    // Dropping all entries above scope 2 should not drop any entries.
    result = var_table.drop_above_scope(2);
    COURIER_ASSERT_EQUAL(ERR_SUCCESS, result);
    COURIER_ASSERT_EQUAL(var_table.size(), 3);

    // Dropping all entries above 0 should drop y and z.
    result = var_table.drop_above_scope(0);
    COURIER_ASSERT_EQUAL(ERR_SUCCESS, result);
    COURIER_ASSERT_EQUAL(var_table.size(), 1);
    std::shared_ptr<Object> find_result = var_table.find("x");
    COURIER_ASSERT_EQUAL(find_result, obj);
}

/***   end of file   ***/
