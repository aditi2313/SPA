#pragma once

#include <cassert>

namespace pkb {
template <class T>
class Data {
 public:
    explicit Data(T line);

    inline T get_index() { return line_; }

 protected:
    T line_;
};

template<class T>
Data<T>::Data(T line) : line_(line) {}
}  // namespace pkb
