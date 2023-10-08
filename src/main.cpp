/*!
 * @file src/main.cpp
 *
 * @brief This file contains the entry point for the program.
 */

#include <iostream>

#include "lexer/lexer.hpp"

int main(int argc, char *argv[])
{
    if (2 != argc)
    {
        std::cerr << "Usage: $ courier [filename]" << std::endl;
        return 1;
    }

    Lexer lexer(argv[1]);
    if (-1 == lexer.tokenize_file())
    {
        std::cerr << "Error: Lexer" << std::endl;
        return 1;
    }

    std::cout << lexer._fdata << std::endl;
}

/***   end of file   ***/
