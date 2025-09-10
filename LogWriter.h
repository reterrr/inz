//
// Created by yhwach on 2/7/25.
//
#pragma once

#include <memory>
#include <queue>
#include <string>

enum class LogLevel {
    COMMON = 0,
    DEBUG = 1
};

struct LogMetadata {
    std::string fileName;
    int line;
    std::string function;
};

struct LogMessage {
    LogLevel level;
    std::string message;
    LogMetadata metadata;
};

class LogWriter {
public:
    static LogWriter &instance();

    void log(const std::string &message, LogLevel level);

private:
    void log(const std::string &message, const LogMetadata &metadata, LogLevel level);

    LogWriter();

    std::queue<LogMessage>&  messages;

    std::mutex messageMutex;
};
