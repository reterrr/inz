//
// Created by yhwach on 3/21/25.
//

#include "rules.hpp"
#include "event/event.hpp"

#include <utility>

rules::path::ValidPath::ValidPath(std::filesystem::path &&path) : path(std::move(path)) {
    validate();
}

void rules::path::ValidPath::validate() const {
    if (!exists(path)) {
        throw std::runtime_error("Error: File does not exist -> " + path.string());
    }

    if (!is_regular_file(path)) {
        throw std::runtime_error("Error: Path is not a regular file -> " + path.string());
    }

    if (is_symlink(path)) {
        throw std::runtime_error("Error: Path is a symbolic link -> " + path.string());
    }

    if (path.extension() != LANGUAGE_EXTENSION) {
        throw std::runtime_error("Invalid file type: " + path.string());
    }
}

const std::filesystem::path &rules::path::ValidPath::get() const {
    return path;
}
