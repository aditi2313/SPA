#include <iostream>
#include <fstream>

namespace logging {
class OutputRedirector {
 public:
  OutputRedirector(std::ostream &out, const char *filename)
      : originalStream(out), file(filename) {
    originalBuf = out.rdbuf();
    out.rdbuf(file.rdbuf());
  }

  ~OutputRedirector() {
    // Restore original stream buffer
    // File is automatically closed when the std::ofstream object is destroyed
    originalStream.rdbuf(originalBuf);
  }

 private:
  std::ostream &originalStream;
  std::streambuf *originalBuf;
  std::ofstream file;
};
}  // namespace logging
