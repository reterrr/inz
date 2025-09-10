//
// Created by yhwach on 4/21/25.
//

#pragma once

#include "event/EventBroker.h"
#include "event/EventListener.h"
#include "event/Event.h"

struct BaseLogEvent final : event::Event {
    BaseLogEvent(int line, std::string message);

    int line;
    std::string message;
};

class BaseLogListener final : public event::EventListener<BaseLogEvent> {
public:
    void onEvent(const BaseLogEvent &event) override;
};

class Base final {
public:
    Base();

    ~Base() = default;

    Base(Base &&) = default;

    Base &operator=(Base &&) = default;

    void log(int line, const std::string &message);

private:
    event::EventBroker broker;
};
