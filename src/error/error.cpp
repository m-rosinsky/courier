/*!
 * @file src/error/error.cpp
 *
 * @brief This file contains the Error class implementation.
 */

#include <sstream>          // std::stringstream

#include "error.hpp"

/******************************************************************************/
/*                          Accessor functions                                */
/******************************************************************************/

/*!
 * @brief This function returns true only when the status is success.
 */
bool Error::is_success(void) const
{
    return _status == ERR_SUCCESS;
}

/******************************************************************************/

/*!
 * @brief This is a helper function to translate error types into messages.
 */
static std::string get_err_msg(uint8_t err_type)
{
    switch(err_type)
    {
        case ERR_SUCCESS:
            return "Success";
        break;
        case ERR_UNREC_SYMB:
            return "Unrecognized symbol";
        break;
        case ERR_INVAL_NUM:
            return "Invalid numeric literal";
        break;
        case ERR_MEM_ALLOC:
            return "Memory allocation error";
        break;
        default:
            return "";
        break;
    }
}

/******************************************************************************/

/*!
 * @brief This function generates an error string for the error.
 *
 * @return A string with the error message.
 */
std::string Error::report(void) const
{
    std::stringstream ss;
    ss << "Error [Line " << _line_num << ", Col " << _col_num << "]: ";
    ss << get_err_msg(_status);
    if (!_msg.empty())
    {
        ss << ": '" << _msg << "'";
    }
    return ss.str();
}

/******************************************************************************/
/*                          Modifier functions                                */
/******************************************************************************/

/*!
 * @brief This function clears the error, reseting to default values.
 */
void Error::clear(void)
{
    _status = ERR_SUCCESS;
    _msg.clear();
    _line_num = 0;
    _col_num = 0;
}

/***   end of file   ***/
