#include <vector>
#include <catch.hpp>
#include "SP/SourceProcessor.h"
#include "common/exceptions/SPExceptions.h"

TEST_CASE("Calling non-existent procedure should throw error") {
  std::string program =
      "procedure procedure {"
      "  call x; "
      "}";

  // Definitely better if I manually constructed the AST
  // and call CallValidator's accept methods, then run its validate method
  // rather than depend on SP
  REQUIRE_THROWS_AS(sp::SourceProcessor::ParseProgram(program),
                    sp::CallSemanticsException);
}

TEST_CASE("Cyclic calls should throw error") {
  std::string program =
      "procedure proc1 {"
      "  call proc2; "
      "}"
      "procedure proc2 {"
      "  call proc1;"
      "}";

  REQUIRE_THROWS_AS(sp::SourceProcessor::ParseProgram(program),
                    sp::CallSemanticsException);
}
