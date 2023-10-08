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

/*!
 * @brief This is a helper function to tokenize a single word from an input line.
 *
 * @param[in] __line The line being tokenized.
 * @param[in/out] __idx The index within the line.
 * @param[in] __line_num The line number for the current line.
 * @param[out] __token_table The table of lexer_token.
 * 
 * @return LEXER_STATUS.
 */
static int tokenize_word (const std::string& __line,
                          size_t& __idx,
                          uint32_t __line_num,
                          std::vector<std::shared_ptr<lexer_token>>& __token_table)
{
    int status = LEXER_ERR_SYNTAX;
    std::string token;

    // Bookmark the start index of the token.
    uint32_t token_start_idx = __idx + 1; // +1 since idx is zero based.

    // Collect until whitespace.
    char c = 0;
    for (;;)
    {
        // Get current character at index.
        c = __line[__idx];

        // Test for whitespace.
        if (std::isspace(c))
        {
            break;
        }

        // Capture current character into token.
        token.push_back(c);

        // Check for index out of range.
        __idx++;
        if (__idx >= __line.size())
        {
            break;
        }
    }

    // Token is fully formed. Add to table.
    lexer_token l_token = 
    {
        token,                  // _token
        LEXER_TOKEN_SYMBOL,     // _type
        __line_num,             // _line_num
        token_start_idx         // _col_num
    };

    // Allocate.
    try
    {
        std::shared_ptr<lexer_token> p_token = std::make_shared<lexer_token>(l_token);
        __token_table.push_back(std::move(p_token));
    }
    catch (const std::exception& exp)
    {
        std::cerr << "Error: " << exp.what() << std::endl;
        goto EXIT;
    }

    status = LEXER_SUCCESS;

    EXIT:
        return status;
}

/*!
 * @brief This is a helper function to tokenize a single line from an input file.
 *
 * @param[in] __line The line to tokenize.
 * @param[in] __line_num The line number for the current line.
 * @param[out] __token_table The table of lexer_token.
 * 
 * @return LEXER_STATUS.
 */
static int tokenize_line (const std::string& __line,
                          uint32_t __line_num,
                          std::vector<std::shared_ptr<lexer_token>>& __token_table)
{
    int status = LEXER_ERR_SYNTAX;

    // The index within the line string.
    size_t line_idx = 0;

    // Iterate over the line.
    while (line_idx < __line.size())
    {
        // Check that an error was not received in the last tokenize call.
        if (LEXER_SUCCESS != status)
        {
            goto EXIT;
        }

        // Extract the current character.
        char c = __line[line_idx];

        // Ignore whitespace.
        if (std::isspace(c))
        {
            line_idx++;
            continue;
        }

        // For symbols starting with letters, tokenize the word.
        if (std::isalpha(c))
        {
            status = tokenize_word(__line, line_idx, __line_num, __token_table);
        }
        // For operator symbols, tokenize the operators.
        if (is_operator(c))
        {
            status = tokenize_operator(__line, line_idx, __line_num, __token_table);
        }
    }

    EXIT:
        return status;
}

/*!
 * @brief This function processes an input file and generates a
 *          vector of lexer_token, representing a tokenized input file.
 * 
 * @return None, but set _err on error.
 */
void Lexer::tokenize_file (void)
{
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
        if (LEXER_SUCCESS != _err)
        {
            goto EXIT;
        }
        _line_num++;
    }

    _err = LEXER_SUCCESS;

    EXIT:
        // If the input file is still open, close.
        if (input_file.is_open())
        {
            input_file.close();
        }
}

/***   end of file   ***/
