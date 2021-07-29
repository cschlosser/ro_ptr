#include "ro/ptr.h"

#include <iostream>

namespace {
struct foo {
    int bar() const {
        return 4;
    }
    int baz() {
        return 2;
    }
};
}

void ro_fnc(readonly::ro_ptr<int> ptr) {
    std::cout << "ro: " << *ptr << std::endl;
}

void ro_call(readonly::ro_ptr<foo> ptr) {
    std::cout << "ptr->bar(): " << ptr->bar() << std::endl;
    std::cout << "ptr->baz(): " << ptr.unsafe_get()->baz() << std::endl;
}

int main() {
#if __cplusplus >= 201103L
#if __cpp_lib_make_unique
    std::unique_ptr<int> uptr = std::make_unique<int>(5);
#else
    std::unique_ptr<int> uptr;
    uptr.reset(new int (5));
#endif
    ro_fnc(uptr);

    std::shared_ptr<int> sptr = std::move(uptr);
    *sptr = 3;
    ro_fnc(sptr);

    auto raw = sptr.get();
#else
    int *raw = new int;
#endif
    *raw = 1;
    ro_fnc(raw);

    foo *f = new foo;
    ro_call(f);
}
