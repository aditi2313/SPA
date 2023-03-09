#include "StringExpr.h"

typedef long long ll;

const ll kPrime = 195262363;

namespace ast {

ll generate_pow(ll n) {
  long long accu = 1;
  if (n == 0) {
    return 1;
  }
  if (n == 1) {
    return 256;
  }
  if (n % 2 == 0) {
    ll half = (generate_pow(n / 2));
    return (half * half) % kPrime;
  }
  return (256 * generate_pow(n - 1)) % kPrime;
}

class StrSlidingWindow {
 public:
  StrSlidingWindow(const std::vector<std::string>& tokens, size_t size)
      : tokens_(tokens), max_size_(size) {
    code_ = 0;
    curr_str_index_ = 0;
    curr_v_index_ = 0;
    start_str_index_ = 0;
    start_v_index_ = 0;
    to_remove_ = generate_pow(size - 1);
    fill_window();
  }

  bool reached_end() { return curr_v_index_ == tokens_.size(); }

  void increment_end() {
    auto& curr_str = tokens_.at(curr_v_index_);
    if (curr_str.size() == 0) {
      curr_v_index_++;
      return increment_end();
    }
    char c = curr_str.at(curr_str_index_);
    code_ *= 256;
    code_ += c;
    code_ %= kPrime;
    curr_str_index_++;
    increment_ptrs(curr_str_index_, curr_v_index_);
  }

  void increment() {
    increment_start();
    increment_end();
  }

  ll get_code() { return code_; }

  bool compare_code(ll reference) { return code_ == reference; }

  bool compare_code(const StrSlidingWindow& other) const {
    return other.code_ == code_ && compare_vectors(other);
  }

 private:
  void fill_window() {
    int ctr = 0;
    while (ctr < max_size_ && !reached_end()) {
      increment_end();
      ctr++;
    }
  }
  bool compare_vectors(const StrSlidingWindow& other) const {
    if (start_str_index_ != 0) return false;
    auto other_ptr = other.tokens_.begin();
    for (int k = start_v_index_;
         k < tokens_.size() && other_ptr != other.tokens_.end(); k++) {
      if (tokens_[k] == "") {
        continue;
      }
      while (*other_ptr == "") {
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
    auto& start_str = tokens_.at(start_v_index_);
    if (start_str.size() == 0) {
      start_str_index_++;
      return increment_start();
    }
    char c = start_str.at(start_str_index_);
    ll to_remove = (c * to_remove_) % kPrime;
    code_ -= to_remove;
    code_ = (code_ + kPrime) % kPrime;
    increment_ptrs(start_str_index_, start_v_index_);
  }
  void increment_ptrs(int& str_index, int& v_index) {
    str_index++;
    auto& curr_str = tokens_.at(v_index);
    if (str_index >= curr_str.size()) {
      str_index = 0;
      v_index++;
      while (v_index != tokens_.size() && tokens_.at(v_index) == "") {
        v_index++;
      }
    }
  }
  size_t max_size_;
  ll to_remove_;
  ll code_;
  int curr_str_index_;
  int curr_v_index_;
  int start_str_index_;
  int start_v_index_;

  const std::vector<std::string>& tokens_;
};

// Implementation of a variant of Rabin Karp to work
// on a vector of strings
bool StringExpr::Contains(const StringExpr& other) const {
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