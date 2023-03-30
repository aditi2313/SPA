#include <iostream>
#include <fstream>

namespace logging {
class OutputRedirector {
 public:
  OutputRedirector(std::ostream &out, const char *filename)
      : original_stream_(out), file(filename) {
    original_buffer_ = out.rdbuf();
    out.rdbuf(file.rdbuf());
  }

  OutputRedirector(std::ostream &out, const wchar_t *filename)
      : original_stream_(out), file(filename) {
    original_buffer_ = out.rdbuf();
    out.rdbuf(file.rdbuf());
  }

  ~OutputRedirector() {
    // Restore original stream buffer
    // File is automatically closed when the std::ofstream object is destroyed
    original_stream_.rdbuf(original_buffer_);
  }

 private:
  std::ostream &original_stream_;
  std::streambuf *original_buffer_;
  std::ofstream file;
};
}  // namespace logging
