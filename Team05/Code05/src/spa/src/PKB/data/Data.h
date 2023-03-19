#pragma once

#include <cassert>

namespace pkb {
template <class T>
class Data {
 public:
    explicit Data(T line);

    virtual inline T get_index() { return line_; }

 protected:
    T line_;
};
}  // namespace pkb
