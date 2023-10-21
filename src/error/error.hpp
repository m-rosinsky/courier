/*!
 * @file src/error/error.hpp
 *
 * @brief This file contains the Error class implementation.
 */

#ifndef _COURIER_SRC_ERROR_ERROR_HPP
#define _COURIER_SRC_ERROR_ERROR_HPP

#include <cstddef>      // uint*_t
#include <string>       // std::string

/******************************************************************************/
/*                              Error Types                                   */
/******************************************************************************/

// Success.
enum err_type_e {
    ERR_SUCCESS = 0,    // success

    // File errors.
    ERR_FILE_OPEN,      // Error opening input file.

    // Syntax errors.
    ERR_UNREC_SYMB,     // Unrecognized symbol.
    ERR_INVAL_NUM,      // Invalid numeric literal.

    // Memory errors.
    ERR_MEM_ALLOC,      // Memory allocation operation failed.

    // Variable errors.
    ERR_VAR_DUPLICATE,  // Redeclaration of existing var.
};

class Error
{

public:

    err_type_e _status;
    std::string _msg;
    uint32_t _line_num;
    uint32_t _col_num;

    // Ctors.
    Error()
        : _status(ERR_SUCCESS), _msg("") {}
    Error(err_type_e __status)
        : _status(__status), _msg("") {}
    Error(const std::string& __msg)
        : _status(ERR_SUCCESS), _msg(__msg) {}
    Error(err_type_e __status, const std::string& __msg)
        : _status(__status), _msg(__msg) {}
    
    // Accessors.
    bool is_success(void) const;
    std::string report(void) const;

    // Modifiers.
    void clear(void);
};

#endif // _COURIER_SRC_ERROR_ERROR_HPP

/***   end of file   ***/
