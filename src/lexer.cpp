#include "./lexer.h"
#include <cctype>

std::vector<Token> Lexer::Tokenize()
{
    std::string buf = "";
    std::vector<Token> tokens;
    
    while (peak().has_value())
    {
        if (std::isalpha(peak().value()))
        {
            buf.push_back(consume());
            while (peak().has_value() && std::isalnum(peak().value()))
            {
                buf.push_back(consume());
            } // Now check for keywords
            if (buf == "exit")
            {
                tokens.push_back({.type = TokenType::TOKEN_EXIT});
                buf.clear();
                continue;
            }
            else
            {
                std::cout << "ERROR: NO KEYWORD FOUND\n";
                exit(1);
            }
        }
        else if (std::isdigit(peak().value()))
        {
            buf.push_back(consume());
            while (peak().has_value() && std::isdigit(peak().value()))
            {
                buf.push_back(consume());
            }
            tokens.push_back({.type = TokenType::TOKEN_INT, .value = buf});
            buf.clear();
            continue;
        }
        else if (peak().has_value() && peak().value() == ';')
        {
            consume();
            tokens.push_back({.type = TokenType::TOKEN_SEMI});
            buf.clear();
            continue;
        }
        else if (std::isspace(peak().value()))
        {
            consume();
            continue;
        }
        else
        {
            std::cout << "ERROR!\n";
        }
    }
    m_index = 0;
    return tokens;
}

char Lexer::consume()
{
    return m_src.at(m_index++);
}
