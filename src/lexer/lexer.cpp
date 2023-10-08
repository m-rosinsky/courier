/*!
 * @file src/lexer/lexer.cpp
 *
 * @brief This file contains the class implementation for the lexer.
 * 
 *          The lexer's repsonsibility is "tokenizing" a raw source
 *              file into a distinct table of tokens that can be
 *              fed into the parser.
 */

#include <cctype>           // isspace
#include <fstream>          // std::ifstream
#include <stdexcept>        // std::exception

/***DEBUG***/
#include <iostream>
/***DEBUG***/

#include "lexer.hpp"

/******************************************************************************/
/*                          Accessor functions                                */
/******************************************************************************/

/*!
 * @brief This function is a getter for the Lexer token table.
 */
const std::vector<std::shared_ptr<lexer_token>>& Lexer::get_table(void) const
{
    return _table;
}

/*!
 * @brief This function is a getter for the Lexer error status.
 */
const Error& Lexer::get_error(void) const
{
    return _err;
}

/******************************************************************************/
/*                          Modifier functions                                */
/******************************************************************************/

/*!
 * @brief This function processes an input file and generates a
 *          vector of lexer_token, representing a tokenized input file.
 * 
 * @return None, but set _err on error.
 */
void Lexer::tokenize_file (const std::string& __fname)
{
    // Set the filename.
    _fname = __fname;

    std::string line = "";

    // Open the file for reading.
    std::ifstream input_file(_fname);

    // Check for open error.
    if (!input_file.is_open())
    {
        goto EXIT;
    }

    // Tokenize the file by line.
    while (std::getline(input_file, line))
    {
        tokenize_line(line);
        if (!_err.is_success())
        {
            break;
        }
        _line_num++;
    }

    EXIT:
        // If the input file is still open, close.
        if (input_file.is_open())
        {
            input_file.close();
        }
}

/******************************************************************************/
/*                          Helper functions                                  */
/******************************************************************************/

/*!
 * @brief This function tokenizes a symbol.
 *
 * @param[in] __line The line being tokenized.
 * 
 * @return None, but set _err on error.
 */
void Lexer::tokenize_symbol (const std::string& __line)
{
    // Clear the current token.
    _token.clear();

    // Bookmark the start index of the token.
    uint32_t token_start_idx = _line_idx + 1; // +1 since idx is zero based.

    // Collect until whitespace.
    char c = 0;
    for (;;)
    {
        // Get current character at index.
        c = __line[_line_idx];

        // Test for whitespace.
        if (std::isspace(c))
        {
            break;
        }

        // Capture current character into token.
        _token.push_back(c);

        // Check for index out of range.
        _line_idx++;
        if (_line_idx >= __line.size())
        {
            break;
        }
    }

    // Token is fully formed. Add to table.
    lexer_token l_token = 
    {
        _token,                 // _token
        LEXER_TOKEN_SYMBOL,     // _type
        _line_num,              // _line_num
        token_start_idx         // _col_num
    };

    // Allocate.
    try
    {
        std::shared_ptr<lexer_token> p_token = std::make_shared<lexer_token>(l_token);
        _table.push_back(std::move(p_token));
    }
    catch (const std::exception& exp)
    {
        std::cerr << "Error: " << exp.what() << std::endl;
    }
}

/*!
 * @brief This function tokenizes a single line from the input file.
 *
 * @param[in] __line The line to tokenize.
 * 
 * @return None, but set _err on error.
 */
void Lexer::tokenize_line (const std::string& __line)
{
    // Set the index within the line string to 0.
    _line_idx = 0;

    // Iterate over the line.
    while (_line_idx < __line.size())
    {
        // Check that an error was not received in the last tokenize call.
        if (!_err.is_success())
        {
            break;
        }

        // Extract the current character.
        char c = __line[_line_idx];

        // Ignore whitespace.
        if (std::isspace(c))
        {
            _line_idx++;
            continue;
        }

        // For symbols starting with letters, tokenize the word.
        if (std::isalpha(c))
        {
            tokenize_symbol(__line);
            continue;
        }
        
        // Unrecognized character.
        // We collect the whole token for error reporting purposes.
        tokenize_symbol(__line);
        _err._status = ERR_UNREC_SYMB;
        _err._line_num = _line_num;
        _err._col_num = _table.back().get()->_col_num;
        _err._msg = _table.back().get()->_token;
        break;
    }
}

/***   end of file   ***/
