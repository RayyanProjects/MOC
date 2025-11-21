#include "./generation.h"
#include <sstream>

[[nodiscard]] std::string Generator::Generate() const
{
    std::stringstream output;
    output << "global _start\n_start:\n";
    output << "    mov rax, 60\n";
    output << "    mov rdi, " << m_root.expr.token_int.value.value() << "\n";
    output << "    syscall";
    return output.str();
}
