//
// Created by yhwach on 3/21/25.
//

#pragma once
#include <filesystem>

namespace rules::path {
    class ValidPath {
#define LANGUAGE_EXTENSION ("kl")

    public:
        explicit ValidPath(std::filesystem::path &&path);

        void validate() const;

        [[nodiscard]] const std::filesystem::path &get() const;

    private:
        std::filesystem::path path;
    };
}
