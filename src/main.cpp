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

    // Create the lexer object.
    Lexer lexer;

    // Tokenize input file.
    lexer.tokenize_file(argv[1]);

    // Perform error checking.
    if (!lexer.get_error().is_success())
    {
        std::cerr << lexer.get_error().report() << std::endl;
        return 1;
    }

    // Dump the table.
    auto table = lexer.get_table();
    std::cout << "Lexer token table:" << std::endl;
    for (auto it = table.begin(); it != table.end(); ++it)
    {
        std::cout << it->get()->_token << " | ";
        std::cout << static_cast<int>(it->get()->_type) << " | ";
        std::cout << it->get()->_line_num << " | " << it->get()->_col_num << std::endl;
    }
    std::cout << std::endl;

    return 0;
}

/***   end of file   ***/
