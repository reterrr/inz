#include <iostream>

struct A final {
    int a;
};

#define some do { \
} while(0)

int main() {
    std::cout << alignof(A) << std::endl;
}
