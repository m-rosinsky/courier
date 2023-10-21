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
    var_table_t var_table;
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
    var_table_t var_table;
    uint8_t result = var_table.add("x", 0, nullptr);
    COURIER_ASSERT_EQUAL(ERR_SUCCESS, result);

    // Add duplicate variable.
    result = var_table.add("x", 0, nullptr);
    COURIER_ASSERT_EQUAL(ERR_VAR_DUPLICATE, result);
}


/******************************************************************************/

/*
void test_var_drop(void);
*/

/***   end of file   ***/
