#include "./lexer.h"
#include <cctype>

std::vector<Token> Lexer::Tokenize()
{
    std::string buf;
    std::vector<Token> tokens;
    
    while (peek().has_value())
    {
        if (std::isalpha(peek().value()))
        {
            buf.push_back(consume());
            while (peek().has_value() && std::isalnum(peek().value()))
            {
                buf.push_back(consume());
            } // Now check for keywords
            if (buf == "exit")
            {
                tokens.push_back({.type = TokenType::TOKEN_EXIT});
                buf.clear();
                continue;
            }
            else if (buf == "let")
            {
                tokens.push_back({.type = TokenType::TOKEN_LET});
                buf.clear();
                continue;
            }
            else
            {
                tokens.push_back({.type = TokenType::TOKEM_IDENT, .value = buf});
                buf.clear();
                continue;
            }
        }
        else if (std::isdigit(peek().value()))
        {
            buf.push_back(consume());
            while (peek().has_value() && std::isdigit(peek().value()))
            {
                buf.push_back(consume());
            }
            tokens.push_back({.type = TokenType::TOKEN_INT, .value = buf});
            buf.clear();
            continue;
        }
        else if (peek().value() == '(')
        {
             consume();
             tokens.push_back({.type = TokenType::TOKEN_LPREN});
             continue;
        }
        else if (peek().value() == ')')
        {
            consume();
            tokens.push_back({.type = TokenType::TOKEN_RPREN});
            continue;
        }       
        else if (peek().has_value() && peek().value() == ';')
        {
            consume();
            tokens.push_back({.type = TokenType::TOKEN_SEMI});
            buf.clear();
            continue;
        }
        else if (peek().has_value() && peek().value() == '=')
        {
            consume();
            tokens.push_back({.type = TokenType::TOKEN_EQ});
            continue;
        }
        else if (std::isspace(peek().value()))
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
