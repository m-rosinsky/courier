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
    for (auto it = table.begin(); it != table.end(); ++it)
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
