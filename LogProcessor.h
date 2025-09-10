#pragma once

#include <queue>

#include "LogWriter.h"

class LogProcessor {
public:
    static std::queue<LogMessage> &getMessages();

protected:
    static std::queue<LogMessage> messages;
};
