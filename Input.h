#pragma once

#include "rules.hpp"

class Input_ {
public:
    virtual ~Input_() = default;

    [[nodiscard]] virtual std::string read(rules::path::ValidPath &&path) const = 0;
};

class Input final : public Input_ {
public:
    Input() = default;

    ~Input() override;

    [[nodiscard]] std::string read(rules::path::ValidPath &&path) const override;
};
