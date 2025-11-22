#pragma once
#include<sstream>
#include <stdexcept>
#include <unordered_map>
#include "./parser.h"

class Generator
{
public:
    Generator(NodeProg prog)
        : m_prog(std::move(prog))
    {}

    void Gen_Expr(const NodeExpr& expr);

    void Gen_Stmt(const NodeStmt& stnt);

    [[nodiscard]] std::string Gen_Prog();
private:
    struct Var
    {
        size_t stack_loc;
    };
    
    const NodeProg m_prog;
    std::stringstream m_output;
    size_t m_stack_size = 0;
    std::unordered_map<std::string, Var> m_vars = {};

    void push(const std::string& reg)
    {
        m_output << "    push " << reg << "\n";
        m_stack_size++;
    }

    void pop(const std::string& reg)
    {
        m_output << "    pop " << reg << "\n";
        m_stack_size--;
    }
};
