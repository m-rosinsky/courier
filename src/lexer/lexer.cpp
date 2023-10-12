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

#include "lexer.hpp"

constexpr char CHAR_COMMENT = '#';

/******************************************************************************/
/*                            Static functions                                */
/******************************************************************************/

/*!
 * @brief This is a static helper function to determine alphabetic characters
 *          including '_'.
 */
static bool is_alpha(char c)
{
    return ((c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            (c == '_'));
}

/*!
 * @brief This is a static helper function to determine numeric characters.
 */
static bool is_num(char c)
{
    return (c >= '0' && c <= '9');
}

/*!
 * @brief This is a static helper function to determine alphanumeric characters.
 */
static bool is_alphanum(char c)
{
    return ((is_alpha(c)) ||
            (is_num(c)));
}

/*!
 * @brief This is a static helper function to determine statement delimiters.
 */
static bool is_delim(char c)
{
    return ((c == ';') ||
            (c == ',') ||
            (c == ':'));
}

/*!
 * @brief This is a static helper function to determine control structures.
 */
static bool is_ctrl(char c)
{
    return ((c == '{') ||
            (c == '}') ||
            (c == '(') ||
            (c == ')'));
}

/*!
 * @brief This is a static helper function to determine operator characters.
 */
static bool is_op(char c)
{
    std::string op_string = "+-*/=";
    for (char op : op_string)
    {
        if (c == op) { return true; }
    }
    return false;
}

/******************************************************************************/
/*                          Accessor functions                                */
/******************************************************************************/

/*!
 * @brief This function is a getter for the Lexer token table.
 */
const std::vector<sp_token_t>& Lexer::get_table(void) const
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

    std::string line;

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
/*                          Private functions                                 */
/******************************************************************************/

/*!
 * @brief This function tokenizes a symbol.
 *
 *          Symbols start with an alphabetic character and may
 *          contain alphabetic characters, numbers, and '_'.
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

    // Collect until non alphanumeric character.
    char c = 0;
    for (;;)
    {
        // Get current character at index.
        c = __line[_line_idx];

        // Test for non-alphanumeric character.
        if (!is_alphanum(c))
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

    // Allocate new token.
    push_token(LEXER_TOKEN_SYMBOL, token_start_idx);
}

/******************************************************************************/

/*!
 * @brief This function tokenizes a number.
 *
 * @param[in] __line The line being tokenized.
 * 
 * @return None, but set _err on error.
 */
void Lexer::tokenize_num(const std::string& __line)
{
    // Clear the current token.
    _token.clear();

    // Bookmark the start index of the token.
    uint32_t token_start_idx = _line_idx + 1; // +1 since idx is zero based.

    // Collect until non alphanumeric character.
    char c = 0;
    for (; _line_idx < __line.size(); ++_line_idx)
    {
        // Get current character at index.
        c = __line[_line_idx];

        // Alphabetic characters are considered an error.
        if (is_alpha(c))
        {
            // Assert error, but continue to collect token.
            _err._status = ERR_INVAL_NUM;
            _token.push_back(c);
            continue;
        }

        // Test for non-numeric character.
        if (!is_num(c))
        {
            break;
        }

        // Capture current character into token.
        _token.push_back(c);
    }

    // If an error was asserted, record info.
    if (!_err.is_success())
    {
        _err._line_num = _line_num;
        _err._col_num = token_start_idx;
        _err._msg = _token;
    }

    // Allocate new token.
    push_token(LEXER_TOKEN_NUM, token_start_idx);
}

/******************************************************************************/

/*!
 * @brief This function tokenizes a operator.
 *
 * @param[in] __line The line being tokenized.
 * 
 * @return None, but set _err on error.
 */
void Lexer::tokenize_op(const std::string& __line)
{
    // Clear the current token.
    _token.clear();

    // Bookmark the start index of the token.
    uint32_t token_start_idx = _line_idx + 1; // +1 since idx is zero based.

    // Capture the current character and increment index.
    char c = __line[_line_idx];
    _line_idx++;

    // Create token.
    _token.push_back(c);

    // Allocate new token.
    push_token(LEXER_TOKEN_OPERATOR, token_start_idx);
}

/******************************************************************************/

/*!
 * @brief This function tokenizes a delimiter.
 *
 * @param[in] __line The line being tokenized.
 * 
 * @return None, but set _err on error.
 */
void Lexer::tokenize_delim(const std::string& __line)
{
    // Clear the current token.
    _token.clear();

    // Bookmark the start index of the token.
    uint32_t token_start_idx = _line_idx + 1; // +1 since idx is zero based.

    // Capture the current character and increment index.
    char c = __line[_line_idx];
    _line_idx++;

    // Create token.
    _token.push_back(c);

    // Allocate new token.
    push_token(LEXER_TOKEN_DELIM, token_start_idx);
}

/******************************************************************************/

/*!
 * @brief This function tokenizes a control structure.
 *
 * @param[in] __line The line being tokenized.
 * 
 * @return None, but set _err on error.
 */
void Lexer::tokenize_ctrl(const std::string& __line)
{
    // Clear the current token.
    _token.clear();

    // Bookmark the start index of the token.
    uint32_t token_start_idx = _line_idx + 1; // +1 since idx is zero based.

    // Capture the current character and increment index.
    char c = __line[_line_idx];
    _line_idx++;

    // Create token.
    _token.push_back(c);

    // Allocate new token.
    push_token(LEXER_TOKEN_CTRL, token_start_idx);
}

/******************************************************************************/

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

        // If a comment character is encountered, we can ignore the rest
        // of the line.
        if (CHAR_COMMENT == c)
        {
            return;
        }

        // For symbols starting with letters, tokenize the word.
        if (is_alpha(c))
        {
            tokenize_symbol(__line);
            continue;
        }

        // Symbols starting with numbers, tokenize the number.
        if (is_num(c))
        {
            tokenize_num(__line);
            continue;
        }

        // Operator symbols.
        if (is_op(c))
        {
            tokenize_op(__line);
            continue;
        }

        // Delimiters (';', ',',  etc.)
        if (is_delim(c))
        {
            tokenize_delim(__line);
            continue;
        }

        // Control structures ('{', '}', '(', ')')
        if (is_ctrl(c))
        {
            tokenize_ctrl(__line);
            continue;
        }
        
        // Unrecognized character.
        _token.clear();
        _token.push_back(c);
        _err._status = ERR_UNREC_SYMB;
        _err._line_num = _line_num;
        _err._col_num = _line_idx + 1;
        _err._msg = _token;
        break;
    }
}

/******************************************************************************/

/*!
 * @brief This function allocates a new token into the Lexer's table.
 */
void Lexer::push_token(uint8_t __type, uint32_t __col_num)
{
    // Allocate. On failure to allocate, set error status.
    try
    {
        sp_token_t sp_token = std::make_shared<token_t>(
            _token, __type, _line_num, __col_num
        );
        _table.push_back(std::move(sp_token));
    }
    catch (const std::exception& exp)
    {
        _err._status = ERR_MEM_ALLOC;
        _err._line_num = _line_num;
        _err._col_num = _line_idx+1;
    }
}

/***   end of file   ***/
