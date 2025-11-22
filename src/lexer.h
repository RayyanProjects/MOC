#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<optional>
#include<cctype>

enum class TokenType
{
    TOKEN_EXIT,
    TOKEN_INT,
    TOKEN_SEMI,
    TOKEN_LPREN,
    TOKEN_RPREN,
    TOKEM_IDENT,
    TOKEN_LET,
    TOKEN_EQ
};

struct Token
{
    TokenType type;
    std::optional<std::string> value {};
};

class Lexer
{
public:
    Lexer(std::string src)
        : m_src(std::move(src))
    {
    }
    
    std::vector<Token> Tokenize();
private:
    [[nodiscard]] std::optional<char> peek(int offset = 0) const
    {
        if (m_index + offset >= m_src.length())
        {
            return {};
        }
        else 
        {
            return m_src.at(m_index + offset);
        }
    }
    char consume();

    const std::string m_src;
    size_t m_index = 0;
};

