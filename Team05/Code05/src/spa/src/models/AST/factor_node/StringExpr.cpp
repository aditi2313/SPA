#include "StringExpr.h"

#include <cstdint>
#include <vector>

typedef int64_t int64;

const int64 kPrime = 195262363;

namespace ast {

int64 generate_pow(int64 n) {
  int64 accu = 1;
  if (n == 0) {
    return 1;
  }
  if (n == 1) {
    return 256;
  }
  if (n % 2 == 0) {
    int64 half = (generate_pow(n / 2));
    return (half * half) % kPrime;
  }
  return (256 * generate_pow(n - 1)) % kPrime;
}

class StrSlidingWindow {
 public:
  StrSlidingWindow(const std::string& tokens, size_t size)
      : tokens_(tokens), max_size_(size) {
    code_ = 0;

    to_remove_ = generate_pow(size - 1);
    fill_window();
  }

  bool reached_end() { return end_index_ == tokens_.size(); }

  void increment_end() {
    increment_ptrs(end_index_);
    char c = tokens_.at(end_index_);
    code_ *= 256;
    code_ += c;
    code_ %= kPrime;
    end_index_++;
    increment_ptrs(end_index_);
  }

  void increment() {
    increment_start();
    increment_end();
  }

  int64 get_code() { return code_; }

  bool compare_code(int64 reference) { return code_ == reference; }

  bool compare_code(const StrSlidingWindow& other) const {
    return other.code_ == code_ && compare_vectors(other);
  }

 private:
  void fill_window() {
    int ctr = 0;
    while (ctr < max_size_) {
      increment_end();
      ctr++;
    }
  }
  bool compare_vectors(const StrSlidingWindow& other) const {
    auto other_ptr = other.tokens_.begin();
    for (int k = start_index_;
         k < tokens_.size() && other_ptr != other.tokens_.end(); k++) {
      if (tokens_[k] == ' ') {
        continue;
      }
      while (*other_ptr == ' ') {
        other_ptr++;
      }
      if (*other_ptr != tokens_.at(k)) {
        return false;
      }
      other_ptr++;
    }
    return true;
  }
  void increment_start() {
    increment_ptrs(start_index_);
    char c = tokens_.at(start_index_);
    int64 to_remove = (c * to_remove_) % kPrime;
    code_ -= to_remove;
    code_ = (code_ + kPrime) % kPrime;
    start_index_++;
    increment_ptrs(start_index_);
  }
  void increment_ptrs(int& index) {
    while (index != tokens_.size() && tokens_.at(index) == ' ') {
      ++index;
    }
  }
  size_t max_size_;
  int64 to_remove_;
  int64 code_;

  int start_index_ = 0;
  int end_index_ = 0;

  const std::string& tokens_;
};

// Implementation of a variant of Rabin Karp to work
// on a vector of strings
bool StringExpr::Contains(const StringExpr& other) const {
  if (other.size() > size()) return false;
  StrSlidingWindow reference_window(other.tokens_, other.size());

  // generate the initial sliding window of size other.size
  StrSlidingWindow window(tokens_, other.size());

  if (window.compare_code(reference_window)) return true;
  while (!window.reached_end()) {
    window.increment();
    if (window.compare_code(reference_window)) {
      // compare the subvector
      return true;
    }
  }
  return false;
}
}  // namespace ast
