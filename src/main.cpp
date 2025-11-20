#include "./lexer.h"
#include <cctype>
#include <cstdlib>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<optional>

std::string tokens_to_asm(const std::vector<Token>& tokens)
{
    std::stringstream output;
    output << "global _start\n_start:\n";
    for (long unsigned i = 0; i < tokens.size(); i++)
    {
        const Token& token = tokens.at(i);
        if (token.type == TokenType::TOKEN_EXIT)
        {
            if (i + 1 < tokens.size() && tokens.at(i+1).type == TokenType::TOKEN_INT)
            {    
                if (i + 2 < tokens.size() && tokens.at(i+2).type == TokenType::TOKEN_SEMI)
                {
                    output << "    mov rax, 60\n"; // 60 for exit syscall
                    output << "    mov rdi, " << tokens.at(i+1).value.value() << "\n";
                    output << "    syscall";

                }
            }
        }
    }
    return output.str();
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "USAGE: moc <source.moc>\n";
        return 1;
    }
    
    std::fstream input(argv[1], std::ios::in); // fstream input file handler
    std::stringstream contents_stream;
    contents_stream << input.rdbuf(); // Read input file into a stringstream
                                      
    input.close(); // close file
    std::string contents = contents_stream.str(); // Have all the file contents in a string

    Lexer lexer(std::move(contents));   
    std::vector<Token> tokens = lexer.Tokenize();

    std::cout << tokens_to_asm(tokens) << '\n';
    
    // output asm to an assembly file
    {
        std::fstream file("out.asm", std::ios::out);
        file << tokens_to_asm(tokens);
    }

    system("nasm -felf64 out.asm");
    system("ld -o out out.o");
    std::cout << contents << "\n";
    return 0;
}
