//
// Created by yhwach on 2/7/25.
//

#include <fstream>

#include "Input.h"

Input::~Input() = default;

std::string Input::read(rules::path::ValidPath &&path) const {
    const auto &file_path = path.get();
    std::ifstream file(file_path, std::ios::binary);

    free()

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + file_path.string());
    }

    return {
        std::istreambuf_iterator(file),
        std::istreambuf_iterator<char>()
    };
}
