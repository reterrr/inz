//
// Created by yhwach on 2/12/25.
//

#include "LogProcessor.h"

std::queue<LogMessage> &LogProcessor::getMessages() {
    return static_cast<std::queue<LogMessage> &>(messages);
}
