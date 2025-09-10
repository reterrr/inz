//
// Created by yhwach on 8/18/25.
//


#include <iostream>

template<typename fun>
struct S : fun {
    using fun::operator();

    explicit S(fun f)
        : fun(std::move(f)) {
    }
};

template<class F>
S(F) -> S<F>;

int main() {
    return 0;
}
