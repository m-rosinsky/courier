/*!
 * @file src/parser/var_handler/var_handler.cpp
 *
 * @brief This file contains the variable handler class, which is
 *          a member of a parser context.
 */

#include <stdexcept>            // std::exception

#include "var_handler.hpp"

/******************************************************************************/
/*                          Accessor functions                                */
/******************************************************************************/

/*!
 * @brief This function gets the number of total variables in the table.
 */
size_t var_table_t::size(void) const noexcept
{
    return _table.size();
}

/******************************************************************************/
/*                          Modifier functions                                */
/******************************************************************************/

/*!
 * @brief This function finds a variable within the table with a given
 *          name.
 * 
 * @param[in] __name The name of the variable to find.
 * 
 * @return The shared_ptr to the object the variable references.
 *          nullptr if the variable is not found.
 */
sp_obj_t var_table_t::find(const std::string& __name) noexcept
{
    for (auto it = _table.begin(); it != _table.end(); ++it)
    {
        if (it->_name == __name)
        {
            return it->_sp_obj;
        }
    }

    return nullptr;
}

/******************************************************************************/

/*!
 * @brief This function removes all entries from a variable table.
 */
void var_table_t::clear(void) noexcept
{
    _table.clear();
}

/******************************************************************************/

/*!
 * @brief This function adds a new entry to a variable table.
 *
 * @param[in] __name The name of the variable.
 * @param[in] __scope The scope for the variable.
 * @param[in] __sp_obj A shared_ptr to the associated object.
 * 
 * @return COURIER_ERR.
 */
uint8_t var_table_t::add(const std::string& __name,
                         uint32_t __scope,
                         sp_obj_t __sp_obj) noexcept
{
    // If a variable with the same name exists at the same scope or greater,
    // this is a duplicate declaration.
    for (auto it = _table.begin(); it != _table.end(); ++it)
    {
        if ((it->_name == __name) &&
            (it->_scope >= __scope))
        {
            return ERR_VAR_DUPLICATE;
        }
    }

    // Create the variable entry.
    var_t var = { __name, __scope, __sp_obj };

    // Insert into table and catch memory errors.
    try
    {
        _table.push_back(var);
    }
    catch (const std::exception& e)
    {
        return ERR_MEM_ALLOC;
    }

    return ERR_SUCCESS;
}

/******************************************************************************/

/*!
 * @brief This function removes all variables above a given scope from
 *          a table.
 * 
 * @param[in] __scope The scope level to drop.
 * 
 * @return COURIER_ERR.
 */
uint8_t var_table_t::drop_above_scope(uint32_t __scope) noexcept
{
    for (auto it = _table.begin(); it != _table.end(); ++it)
    {
        if (it->_scope > __scope)
        {
            try
            {
                _table.erase(it);
            }
            catch (const std::exception& e)
            {
                return ERR_MEM_ALLOC;
            }
        }
    }

    return ERR_SUCCESS;
}

/***   end of file   ***/
