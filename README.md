# Readonly Pointer wrapper

`readonly::ro_ptr` is a pointer wrapper guaranteeing the user of the API that the parameter is only used for reading and can be implicitly converted
from `std::shared_ptr`, `std::unique_ptr` and raw pointers providing a homogeneous interface.

## Building

This is a header-only project, all you have to do is copy `include/ro/ptr.h` into your project under `ro/ptr.h`, tell your build system the additional include directory and you're all set.

The header is compatible from C++98 and up.

### CMake

If you're using `CMake` you can also use `find_package` after installing this project like this:

```bash
$> git clone https://github.com/cschlosser/ro_ptr.git
$> cd ro_ptr
$> mkdir build && cd build
$> cmake ..
$> make install
```

### Bazel

Add this to your `WORKSPACE` file:
```starlark
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
  name = "com_github_cschlosser_ro_ptr",
  urls = ["https://github.com/cschlosser/ro_ptr/archive/refs/tags/<version>.zip"],
  sha256 = "...",
  strip_prefix = "ro_ptr-<version>",
)
```

and in a `BUILD` file example:

```starlark
cc_binary(
    name = "example",
    srcs = ["example.cc"],
    deps = [
        "@com_github_cschlosser_ro_ptr//:ro_ptr",
    ],
)
```

finally run:

```bash
$> bazel run //:example
```

## Example

This is probably the most basic example how this wrapper can be useful.

```cpp
// foo.h
#pragma once

#include "ro/ptr.h"

// This guarantees the user of the API that ptr is only used for reading but the
// state is never modified. The user also knows he doesn't have to call any additional
// methods to provide this type to the API making code more readable.
void foo(readonly::ro_ptr<int> ptr);
```

```cpp
// foo.cc
#include "foo.h"

#include <iostream>

void foo(readonly::ro_ptr<int> ptr) {
    std::cout << *ptr << std::endl;
}
```

```cpp
// main.cc
#include "foo.h"

int main() {
    const auto ptr = std::make_unique<int>(42);
    foo(ptr);
}
```

