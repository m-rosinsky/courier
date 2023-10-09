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

#include "../error/error.hpp"

#define LEXER_TOKEN_SYMBOL      0
#define LEXER_TOKEN_NUM         1
#define LEXER_TOKEN_OPERATOR    2
#define LEXER_TOKEN_DELIM       3

/*!
 * @brief This struct defines an entry for a token to be stored
 *          in the token table via lexing.
 * 
 * @param _token The token string itself.
 * @param _type The token type.
 * @param _line_num The line number the token appears on.
 * @param _col_num The column number the token appears on.
 */
struct token_t
{
    std::string _token;
    uint8_t _type;
    uint32_t _line_num;
    uint32_t _col_num;

    token_t(const std::string& __token,
            uint8_t __type,
            uint32_t __line_num,
            uint32_t __col_num)
        : _token(__token), _type(__type), _line_num(__line_num), _col_num(__col_num) {}
};

typedef std::shared_ptr<token_t> sp_token_t;

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

    Error _err;         // The error status of lexer operations.

    std::vector<sp_token_t> _table; // The table of tokens.

public:
    
    // Ctors.
    Lexer()
        : _fname(""),
          _token(""),
          _line_num(1), _line_idx(0) {}

    // Accessors.
    const std::vector<sp_token_t>& get_table(void) const;
    const Error& get_error(void) const;

    // Modifiers.
    void tokenize_file(const std::string& __fname);

private:
    // Helper functions.
    void tokenize_line(const std::string& __line);

    void tokenize_symbol(const std::string& __line);
    void tokenize_num(const std::string& __line);
    void tokenize_op(const std::string& __line);
    void tokenize_delim(const std::string& __line);

    void push_token(uint8_t __type, uint32_t __col_num);
};

#endif // _COURIER_SRC_LEXER_LEXER_HPP

/***   end of file   ***/
