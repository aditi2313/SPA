#pragma once

#include <memory>
#include <vector>

namespace pkb {

template <class Data>
class TableReader {
 public:
  TableReader() {}
  virtual Data& read_data() = 0;
  virtual void increment() = 0;
  virtual bool reached_end() = 0;
};

}  // namespace pkb
