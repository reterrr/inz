#include "LogWriter.h"
#include "LogProcessor.h"

LogWriter::LogWriter() : messages(LogProcessor::getMessages()) {
}


LogWriter &LogWriter::instance() {
    static LogWriter logWriter{};

    return logWriter;
}

void LogWriter::log(const std::string &message, LogLevel level) {
    LogMetadata metadata{}; //TODO: request an interpreter metadata for now its 0

    log(message, metadata, level);
}

void LogWriter::log(const std::string &message, const LogMetadata &metadata, LogLevel level) {
    std::lock_guard lock(messageMutex);
    messages.push({level, message, metadata});
}
