
namespace pkb {
class Result {
 public:
  virtual bool isError() = 0;
  virtual Result Join(Result) = 0;
};

}  // namespace pkb
