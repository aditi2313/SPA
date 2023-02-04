class InvalidPqlException : public std::exception {
 public:
  explicit InvalidPqlException(const char *msg) : message(msg) {}
  const char *what() { return message; }

 private:
  const char *message;
};
class PqlSemanticErrorException : public InvalidPqlException {
   public:
    explicit PqlSemanticErrorException(const char *msg)
        : InvalidPqlException(msg) {}
};
