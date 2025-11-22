#include "./generation.h"
#include "parser.h"
#include <cstdio>
#include <iterator>
#include <sstream>


void Generator::Gen_Expr(const NodeExpr& expr)
{
    struct ExprVisitor
    {
        Generator* gen;

        void operator()(const NodeExprIntLit& expr_int_lit) const
        {
            gen->m_output << "    mov rax, " << expr_int_lit.int_lit.value.value() << "\n";
            gen->push("rax");
        }
        void operator()(const NodeExprIdent& expr_ident) const
        {
            if (!gen->m_vars.contains(expr_ident.ident.value.value()))
            {
                std::cout << "ERROR: Undeclared identifier: " << expr_ident.ident.value.value() << "\n";
                exit(1);
            }
            const auto& var = gen->m_vars.at(expr_ident.ident.value.value());
            std::stringstream offset;
            offset << "QWORD [rsp + " << (gen->m_stack_size - var.stack_loc - 1) * 8 << "]";
            gen->push(offset.str());
        }
    };
    ExprVisitor visitor{.gen = this};
    std::visit(visitor, expr.var);
}



void Generator::Gen_Stmt(const NodeStmt& stmt)
{
    struct StmtVisitor
    {
        Generator* gen;
        void operator()(const NodeStmtExit& stmt_exit) const
        {
            gen ->Gen_Expr(stmt_exit.expr);
            gen->m_output << "    mov rax, 60\n";
            gen->pop("rdi");
            gen->m_output << "    syscall\n";

        }
        void operator()(const NodeStmtLet& stmt_let) const
        {
            if (gen->m_vars.contains(stmt_let.ident.value.value()))
            {
                std::cout << "ERROR: Identifier already used: " << stmt_let.ident.value.value() << "\n";
                exit(1);
            }
            gen->m_vars.insert({stmt_let.ident.value.value(), Var {.stack_loc = gen->m_stack_size}});
            gen->Gen_Expr(stmt_let.expr);
        }
    };
    StmtVisitor visitor {.gen = this};
    std::visit(visitor, stmt.var);
}


[[nodiscard]] std::string Generator::Gen_Prog()
{
    m_output << "global _start\n_start:\n";

    for (const NodeStmt& stmt : m_prog.stmts)
    {
        Gen_Stmt(stmt);
    }


    m_output << "    mov rax, 60\n";
    m_output << "    mov rdi, 0\n";
    m_output << "    syscall\n";
    return m_output.str();
}
