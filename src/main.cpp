/*!
 * @file src/main.cpp
 *
 * @brief This file contains the entry point for the program.
 */

#include <iostream>
#include <memory>
#include <vector>

#include "lexer/lexer.hpp"

int main(int argc, char *argv[])
{
    if (2 != argc)
    {
        std::cerr << "Usage: $ courier [filename]" << std::endl;
        return 1;
    }

    // Create the token table.
    std::vector<std::shared_ptr<lexer_token>> token_table;

    // Tokenize the input file.
    if (LEXER_SUCCESS != tokenize_file(argv[1], token_table))
    {
        std::cerr << "Syntax error" << std::endl;
    }

    // Dump the table.
    for (auto it = token_table.begin(); it != token_table.end(); ++it)
    {
        std::cout << "Entry:\n";
        std::cout << "\t" << it->get()->_token << "\n";
        std::cout << "\t" << it->get()->_line_num << "\n";
        std::cout << "\t" << it->get()->_col_num << "\n\n";
    }
    std::cout << std::endl;

    return 0;
}

/***   end of file   ***/
