#pragma once
#include<variant>

#include "./lexer.h"

struct NodeExprIntLit
{
    Token int_lit;
};

struct NodeExprIdent
{
    Token ident;
};

struct NodeExpr
{
    std::variant<NodeExprIntLit, NodeExprIdent> var;
};

struct NodeStmtExit
{
    NodeExpr expr;
};

struct NodeStmtLet
{
    Token ident;
    NodeExpr expr;
};

struct NodeStmt
{
    std::variant<NodeStmtExit, NodeStmtLet> var;
};

struct NodeProg
{
    std::vector<NodeStmt> stmts;
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

    std::optional<NodeStmt> Parse_Stmt();

    std::optional<NodeProg> Parse_Prog();
private:
    [[nodiscard]] inline std::optional<Token> peek(int offset = 0) const
    {
        if (m_index + offset >= m_tokens.size())
        {
            return {};
        }
        else
        {
            return m_tokens.at(m_index + offset);
        }
    }
    Token consume();

    const std::vector<Token> m_tokens;
    size_t m_index = 0;
};
