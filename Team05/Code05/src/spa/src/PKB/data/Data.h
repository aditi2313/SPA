#pragma once

#include <cassert>
#include "DataWrapper.h"

namespace pkb {
template <class T>
class Data : public DataWrapper {
 public:
    explicit Data(T line);

    inline T get_index() { return line_; }

    inline std::variant<int, std::string> get_key() {
        return line_;
    }

protected:
    T line_;
};

template<class T>
Data<T>::Data(T line)
    : line_(line) {}
}  // namespace pkb
