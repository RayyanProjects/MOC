#include "./parser.h"

std::optional<NodeExpr> Parser::Parse_Expr()
{
    if (peak().has_value() && peak().value().type == TokenType::TOKEN_INT)
    {
        return NodeExpr{.token_int = consume()};
    }
    else
    {
        return {};
    }
}

std::optional<NodeExit> Parser::Parse()
{
    std::optional<NodeExit> exit_node;
    while(peak().has_value())
    {
        if (peak().value().type == TokenType::TOKEN_EXIT)
        {
            consume();
            if (auto node_expr = Parse_Expr()) // This if statement means that if parsing was successful save the result in expr_node but if not successful give an error.
            {
                exit_node = NodeExit{.expr = node_expr.value()};
            }
            else
            {
                std::cout << "ERROR: Invalid expression.\n";
                exit(1);
            }
            if (peak().has_value() && peak().value().type == TokenType::TOKEN_SEMI)
            {
                consume();
            }
            else
            {
                std::cout << "ERROR: Invalid expression.\n";
                exit(1);                    
            }
        }
    }
    return exit_node;
}

Token Parser::consume()
{
    return m_tokens.at(m_index++);
}
