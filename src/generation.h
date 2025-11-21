#pragma once
#include "./parser.h"

class Generator
{
public:
    Generator(NodeExit root)
        : m_root(std::move(root))
    {}

    [[nodiscard]] std::string Generate() const;
private:
    const NodeExit m_root;
};
