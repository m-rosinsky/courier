/*!
 * @file src/lexer/lexer.hpp
 *
 * @brief This file contains the class implementation for the lexer.
 * 
 *          The lexer's repsonsibility is "tokenizing" a raw source
 *              file into a distinct table of tokens that can be
 *              fed into the parser.
 */

#ifndef _COURIER_SRC_LEXER_LEXER_HPP
#define _COURIER_SRC_LEXER_LEXER_HPP

#include <cstddef>      // uint*_t
#include <memory>       // std::unique_ptr
#include <string>       // std::string
#include <vector>       // std::vector

#define LEXER_SUCCESS       0
#define LEXER_ERR_SYNTAX    1

#define LEXER_TOKEN_SYMBOL      0
#define LEXER_TOKEN_OPERATOR    1
#define LEXER_TOKEN_DELIM       2

/*!
 * @brief This struct defines an entry for a token to be stored
 *          in the token table via lexing.
 * 
 * @param _token The token string itself.
 * @param _type The token type.
 * @param _line_num The line number the token appears on.
 * @param _col_num The column number the token appears on.
 */
struct lexer_token
{
    std::string _token;
    uint8_t _type;
    uint32_t _line_num;
    uint32_t _col_num;
};

/*!
 * @brief This class defines the lexer class, which is used to tokenize
 *          input files.
 */
class Lexer
{

private:
    std::string _fname; // The current file being tokenized.
    std::string _token; // Storage for the current token.
    uint32_t _line_num; // The line number for the current line being tokenized.
    uint32_t _line_idx; // The current char index within the current line.

    uint8_t _err; // The error status of the lexer.

    std::vector<std::shared_ptr<lexer_token>> _table; // The table of tokens.

public:
    
    // Ctors.
    Lexer() = delete; // Must construct with a filename.
    Lexer(const std::string& __fname)
        : _fname(__fname),
          _token(""),
          _line_num(1), _line_idx(0),
          _err(LEXER_SUCCESS) {}

    // Accessors.
    std::vector<std::shared_ptr<lexer_token>>& get_table() const;
    uint8_t get_error() const;

    // Modifiers.
    void tokenize_file(void);
    void tokenize_line(const std::string& __line);
    void tokenize_symbol(const std::string& __line);
    void tokenize_operator(const std::string& __line);
};

#endif // _COURIER_SRC_LEXER_LEXER_HPP

/***   end of file   ***/
