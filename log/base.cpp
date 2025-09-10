//
// Created by yhwach on 4/21/25.
//

#include "base.hpp"

#include <iostream>
#include <memory>
#include <utility>

BaseLogEvent::BaseLogEvent(int line, std::string message) : line(line), message(std::move(message)) {
}

void BaseLogListener::onEvent(const BaseLogEvent &event) {
    std::cout << event.line << ":" << event.message << std::endl;
}

Base::Base(): broker(event::EventDispatcher<>()) {
    broker.registerListener(std::make_unique<BaseLogListener>());
}

void Base::log(int line, const std::string &message) {
    broker.registerEvent(std::make_unique<BaseLogEvent>(line, message));
}
