//
// Created by yhwach on 7/27/25.
//

#ifndef GENERATOR_H
#define GENERATOR_H
#include <coroutine>
#include <exception>

template<typename T>
class generator {
    struct promise_type;
    std::coroutine_handle<promise_type> handle;

public:
    struct promise_type {
        T value_;

        generator get_return_object() {
            return std::coroutine_handle<promise_type>::from_promise(*this);
        }

        std::suspend_always initial_suspend() {
            return {};
        }

        std::suspend_always final_suspend() noexcept {
            return {};
        }

        std::suspend_always yield_value(T value) {
            value_ = value;

            return {};
        }

        void return_void() {
        }

        void unhandled_exception() {
            std::terminate();
        }
    };

    explicit generator(std::coroutine_handle<promise_type> handle)
        : handle(handle) {
    }

    generator(generator &&another) noexcept
        : handle(another.handle) {
        another.handle = nullptr;
    }

    ~generator() {
        if (handle) handle.destroy();
    }

    T next() {
        if (handle.done())
            return {};

        handle.resume();

        return handle.promise().value_;
    }
};


#endif
