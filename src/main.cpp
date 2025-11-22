#include "./parser.h"
#include "./lexer.h"
#include "./generation.h"
#include <cctype>
#include <cerrno>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<optional>

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

    Parser parser(std::move(tokens));
    std::optional<NodeProg> prog = parser.Parse_Prog();

    if (!prog.has_value())
    {
        std::cout << "ERROR: Invalid program.\n";
        exit(1);
    }

    Generator generator(prog.value());

    // output asm to an assembly file
    {
        std::fstream file("out.asm", std::ios::out);
        file << generator.Gen_Prog();
    }

    system("nasm -felf64 out.asm");
    system("ld -o out out.o");
    std::cout << contents << "\n";
    return 0;
}
