#pragma once

#include <cassert>
#include "DataWrapper.h"

namespace pkb {
    template <class T>
    class Data : public DataWrapper<T> {
    public:
        explicit Data(T line);
    };

    template<class T>
    Data<T>::Data(T line)
            : DataWrapper<T>(line) {}
}  // namespace pkb
