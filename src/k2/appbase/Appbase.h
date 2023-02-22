
#pragma once

// stl
#include <string>

namespace k2 {
    // This is a foundational class used to create K2 Apps.
class App {
public:  // API

};

// global access to the AppBase
extern App* ___appBase___;
inline App& AppBase() { return *___appBase___; }
} // namespace k2