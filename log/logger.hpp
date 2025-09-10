//
// Created by yhwach on 4/21/25.
//

#pragma once
#include <string>

template<typename T>
concept LoggerType = requires(T logger, int line, const std::string &message)
{
    { logger.log(line, message) } -> std::same_as<void>;
};

template<LoggerType Impl>
class Logger final {
public:
    static void log(int line, const std::string &message) {
        impl.log(line, message);
    }

    static Impl impl;
};

template<LoggerType Impl>
Impl Logger<Impl>::impl;
