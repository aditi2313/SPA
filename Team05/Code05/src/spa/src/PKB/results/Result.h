
namespace pkb {
	class Result {
 public:
          virtual bool isError() = 0;
          virtual Result join(Result) = 0;
        };

}