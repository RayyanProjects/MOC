#pragma once
#include "./lexer.h"

struct NodeExpr
{
    Token token_int;
};

struct NodeExit
{
    NodeExpr expr;
};

class Parser
{
public:
    Parser(std::vector<Token> tokens)
        : m_tokens(std::move(tokens))
    {}

    std::optional<NodeExpr> Parse_Expr();

    std::optional<NodeExit> Parse();
private:
    [[nodiscard]] inline std::optional<Token> peak(int ahead = 1) const
    {
        if (m_index + ahead > m_tokens.size())
        {
            return {};
        }
        else
        {
            return m_tokens.at(m_index);
        }
    }
    Token consume();

    const std::vector<Token> m_tokens;
    size_t m_index = 0;
};
