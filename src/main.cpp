/*!
 * @file src/main.cpp
 *
 * @brief This file contains the entry point for the program.
 */

#include <iostream>
#include <memory>
#include <vector>

#include "lexer/lexer.hpp"
#include "parser/parser.hpp"

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

    // Create parser object.
    Parser parser;

    // Parse token table from lexer.
    parser.parse(lexer.get_table(), 0, 0);

    // Perform error checking.
    if (!parser.get_error().is_success())
    {
        std::cerr << parser.get_error().report() << std::endl;
        return 1;
    }

    return 0;
}

/***   end of file   ***/
