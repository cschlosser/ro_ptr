#include "ro/ptr.h"
#include <iostream>

// This guarantees the user of the API that ptr is only used for reading but the
// state is never modified. The user also knows he doesn't have to call any additional
// methods to provide this type to the API making code more readable.
void foo(readonly::ro_ptr<int> ptr);

int main() {
    const auto ptr = std::make_unique<int>(42);
    foo(ptr);
}

void foo(readonly::ro_ptr<int> ptr) {
    std::cout << *ptr << std::endl;
}
