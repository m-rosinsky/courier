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
#define ERR_SUCCESS 0

// Syntax Errors.
#define ERR_UNREC_SYMB 1        // Unrecognized symbol.

class Error
{

public:

    uint8_t _status;
    std::string _msg;
    uint32_t _line_num;
    uint32_t _col_num;

    // Ctors.
    Error()
        : _status(ERR_SUCCESS), _msg("") {}
    Error(uint8_t __status)
        : _status(__status), _msg("") {}
    Error(const std::string& __msg)
        : _status(ERR_SUCCESS), _msg(__msg) {}
    Error(uint8_t __status, const std::string& __msg)
        : _status(__status), _msg(__msg) {}
    
    // Accessors.
    bool is_success(void) const;
    std::string report(void) const;

};

#endif // _COURIER_SRC_ERROR_ERROR_HPP

/***   end of file   ***/
