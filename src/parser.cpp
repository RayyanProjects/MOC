#include "./parser.h"
#include "lexer.h"

std::optional<NodeExpr> Parser::Parse_Expr()
{
    if (peek().has_value() && peek().value().type == TokenType::TOKEN_INT)
    {
        return NodeExpr{.var = NodeExprIntLit { .int_lit =  consume()}};
    }
    else if (peek().has_value() && peek().value().type == TokenType::TOKEM_IDENT)
    {
        return NodeExpr {.var = NodeExprIdent {.ident = consume()}};
    }
    else
    {
        return {};
    }
}

std::optional<NodeStmt> Parser::Parse_Stmt()
{
    if (peek().value().type == TokenType::TOKEN_EXIT && peek(1).has_value() && peek(1).value().type == TokenType::TOKEN_LPREN)
        {
        consume();
        consume();
        NodeStmtExit stmt_exit;
        if (auto node_expr = Parse_Expr()) // This if statement means that if parsing was successful save the result in expr_node but if not successful give an error.
        {
            stmt_exit = {.expr = node_expr.value()};
        }
        else
        {
            std::cout << "ERROR: Invalid Expression.\n";
            exit(1);
        }
        if (peek().has_value() && peek().value().type == TokenType::TOKEN_RPREN)
        {
            consume();
        }
        else
        {
            std::cout << "ERROR: Expected a ')'\n";
            exit(1);
        }
        if (peek().has_value() && peek().value().type == TokenType::TOKEN_SEMI)
        {
            consume();
        }
        else
        {
            std::cout << "ERROR: Expected ';'.\n";
            exit(1);                    
        }
        return NodeStmt{.var = stmt_exit};
    }
    else if (peek().has_value() && peek().value().type == TokenType::TOKEN_LET
            && peek(1).has_value() && peek(1).value().type == TokenType::TOKEM_IDENT
            && peek(2).has_value() && peek(2).value().type == TokenType::TOKEN_EQ)
    {
        consume(); // consuming let
        auto stmt_let = NodeStmtLet {.ident = consume()}; // consuming the identifier
        consume(); // consuming the equal sign
        if (auto expr = Parse_Expr())
        {
            stmt_let.expr = expr.value();
        }
        else
        {
            std::cout << "ERROR: Invalude expression.\n";
            exit(1);
        }
        if (peek().has_value() && peek().value().type == TokenType::TOKEN_SEMI)
        {
            consume();
        }
        else
        {
            std::cout << "ERROR: Expected ';'\n";
            exit(1);
        }
        return NodeStmt {.var = stmt_let};
    }
    else
    {
        return {};
    }
}

std::optional<NodeProg> Parser::Parse_Prog()
{
NodeProg prog;
    while (peek().has_value())
    {
        if (auto stmt = Parse_Stmt())
        {
            prog.stmts.push_back(stmt.value());
        }
        else
        {
            std::cout << "ERROR: Invalid statememnt.\n";
            exit(1);
        }
    }
    return prog;
}

Token Parser::consume()
{
    return m_tokens.at(m_index++);
}
