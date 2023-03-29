#pragma once

#include <cassert>
#include <variant>
#include "DataWrapper.h"

namespace pkb {
    template <class Key = std::variant<int, std::string>>
    class DataWrapper {
    public:
        explicit DataWrapper(Key line);

        inline Key get_index() { return line_; }

    protected:
        Key line_;
    };

    template<class Key>
    DataWrapper<Key>::DataWrapper(Key line)
            : line_(line) {}
}  // namespace pkb
