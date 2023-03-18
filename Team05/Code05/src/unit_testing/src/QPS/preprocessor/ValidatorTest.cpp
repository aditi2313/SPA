#include <exception>
#include <catch.hpp>

#include "QPS/models/PQL.h"
#include "QPS/preprocessor/SelectClParser.h"
#include "QPS/preprocessor/Validator.h"
#include "common/exceptions/QPSExceptions.h"

using namespace qps;  // NOLINT

std::unique_ptr<Query> BuildQuery(
    std::vector<std::pair<SynonymName, EntityType>> synonyms,
    std::vector<std::string> selected_synonyms);  // Forward declaration

TEST_CASE("Test Wildcard as first argument in Clauses") {
  SelectClParser parser;
  SECTION("First argument for Modifies is not a wildcard is valid") {
    // No wildcard
    std::string query_str = "stmt s; Select s such that Modifies(s, \"var\")";
    auto query = parser.ParseQuery(query_str);

    REQUIRE_NOTHROW(Validator::Validate(query));
  }

  SECTION("First argument for Modifies is a wildcard should throw error") {
    std::string query_str = "stmt s; Select s such that Modifies(_, \"var\")";
    auto query = parser.ParseQuery(query_str);

    REQUIRE_THROWS_AS(Validator::Validate(query), PqlSemanticErrorException);
  }

  SECTION("First argument for Uses is a wildcard should throw error") {
    std::string query_str = "stmt s; Select s such that Uses(_, \"var\")";
    auto query = parser.ParseQuery(query_str);

    REQUIRE_THROWS_AS(Validator::Validate(query), PqlSemanticErrorException);
  }

  SECTION("First argument for Follows is a wildcard is valid") {
    // No wildcard
    std::string query_str = "stmt s; Select s such that Follows(_, 2)";
    auto query = parser.ParseQuery(query_str);

    REQUIRE_NOTHROW(Validator::Validate(query));
  }
}

TEST_CASE("Test that all synonyms used are declared") {
  SelectClParser parser;
  SECTION("All synonyms used are declared once") {
    // All used synonyms are declared
    std::string query_str = "stmt s; Select s";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_NOTHROW(Validator::Validate(query));
  }

  SECTION("Select BOOLEAN is valid and should not throw error") {
    // All used synonyms are declared
    std::string query_str = "stmt s; Select BOOLEAN";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_NOTHROW(Validator::Validate(query));
  }

  SECTION("Undeclared synonym used in Select") {
    std::string query_str = "stmt s; Select v";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_THROWS_AS(Validator::Validate(query), PqlSemanticErrorException);
  }

  SECTION("Undeclared synonym used in a Clause") {
    std::string query_str = "stmt s; Select s such that Modifies(v, \"var\")";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_THROWS_AS(Validator::Validate(query), PqlSemanticErrorException);
  }
}

TEST_CASE("Test that synonyms are declared exactly once") {
  SelectClParser parser;

  SECTION("Synonym declared more than once") {
    std::string query_str =
        "variable v; stmt v;"
        "Select v";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_THROWS_AS(Validator::Validate(query),
                      PqlSemanticErrorException);
  }
}

TEST_CASE("Test that selected attrRefs are semantically correct") {
  SelectClParser parser;

  SECTION("Select attrRef with correct types should pass") {
    std::string query_str =
        "stmt s;"
        "Select s.stmt#";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_NOTHROW(Validator::Validate(query));
  }

  SECTION("Select multiple attrRef with correct types should pass") {
    std::string query_str =
        "stmt s; variable v; procedure p; constant c;"
        "Select <s.stmt#, v.varName, p.procName, c.value>";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_NOTHROW(Validator::Validate(query));
  }

  SECTION("Select attrRef with incorrect types should throw error") {
    std::string query_str =
        "stmt s;"
        "Select s.value";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_THROWS_AS(Validator::Validate(query),
                      PqlSemanticErrorException);
  }

  SECTION("Select multiple attrRef with only one incorrect type "
          "should throw error") {
    // c.varName is incorrect
    std::string query_str =
        "stmt s; variable v; procedure p; constant c;"
        "Select <s.stmt#, v.varName, p.procName, c.varName>";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_THROWS_AS(Validator::Validate(query),
                      PqlSemanticErrorException);
  }
}

TEST_CASE("Test synonym types for each clause are valid") {
  SelectClParser parser;

  SECTION("Valid synonym types for Modifies Clause") {
    std::string query_str = "stmt s; Select s such that Modifies(s, \"var\")";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_NOTHROW(Validator::Validate(query));
  }

  SECTION("Valid synonym types that is a sub-type for Modifies Clause") {
    std::string query_str = "assign a; Select a such that Modifies(a, \"var\")";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_NOTHROW(Validator::Validate(query));
  }

  SECTION("Valid synonym types for Follows Clause") {
    std::string query_str = "stmt s; Select s such that Follows(s, 2)";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_NOTHROW(Validator::Validate(query));
  }

  SECTION("Valid synonym types for Calls Clause") {
    std::string query_str = "procedure p1, p2; "
                            "Select p1 such that Calls(p1, p2)";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_NOTHROW(Validator::Validate(query));
  }

  SECTION("Valid synonym types for Next Clause") {
    std::string query_str = "stmt s1, s2; "
                            "Select s1 such that Next(s1, s2)";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_NOTHROW(Validator::Validate(query));
  }

  SECTION("Invalid synonym types for Modifies Clause should throw error") {
    std::string query_str = "variable v; "
                            "Select v such that Modifies(v, \"var\")";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_THROWS_AS(Validator::Validate(query),
                      PqlSemanticErrorException);
  }

  SECTION("Invalid synonym types for Follows Clause should throw error") {
    std::string query_str = "variable v; Select v such that Follows(v, 2)";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_THROWS_AS(Validator::Validate(query),
                      PqlSemanticErrorException);
  }

  SECTION("Invalid synonym types for Calls Clause should throw error") {
    std::string query_str = "procedure p1; variable p2;"
                            " Select p1 such that Calls(p1, p2)";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_THROWS_AS(Validator::Validate(query),
                      PqlSemanticErrorException);
  }

  SECTION("Invalid synonym types for Next Clause should throw error") {
    std::string query_str = "stmt s1; constant s2;"
                            "Select s1 such that Next(s1, s2)";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_THROWS_AS(Validator::Validate(query),
                      PqlSemanticErrorException);
  }

    /* ================ Validation for WITH clauses ============== */
  SECTION("Invalid synonym with attrName for With Clause should throw error") {
    std::string query_str = "stmt s;"
                            "Select s with s.value = 1";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_THROWS_AS(Validator::Validate(query),
                      PqlSemanticErrorException);
  }

  SECTION("Invalid synonym with attrName for With Clause should throw error") {
    std::string query_str = "constant c;"
                            "Select c with c.stmt# = 1";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_THROWS_AS(Validator::Validate(query),
                      PqlSemanticErrorException);
  }

  SECTION("Invalid synonym with attrName for With Clause should throw error") {
    std::string query_str = "procedure p;"
                            "Select p with p.varName = \"procedure\"";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_THROWS_AS(Validator::Validate(query),
                      PqlSemanticErrorException);
  }

  SECTION("Invalid synonym with attrName for With Clause should throw error") {
    std::string query_str = "variable v;"
                            "Select v with v.procName = \"variable\"";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_THROWS_AS(Validator::Validate(query),
                      PqlSemanticErrorException);
  }

  SECTION("Valid synonym with attrName for With Clause should pass") {
    std::string query_str = "stmt s;"
                            "Select s with s.stmt# = 1";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_NOTHROW(Validator::Validate(query));
  }

  SECTION("Valid synonym with attrName for With Clause should pass") {
    std::string query_str = "constant c;"
                            "Select c with c.value = 1";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_NOTHROW(Validator::Validate(query));
  }

  SECTION("Valid synonym with attrName for With Clause should pass") {
    std::string query_str = "procedure p;"
                            "Select p with p.procName = \"procedure\"";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_NOTHROW(Validator::Validate(query));
  }

  SECTION("Valid synonym with attrName for With Clause should pass") {
    std::string query_str = "call c;"
                            "Select c with c.procName = \"callee\"";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_NOTHROW(Validator::Validate(query));
  }

  SECTION("Valid synonym with attrName for With Clause should pass") {
    std::string query_str = "read r;"
                            "Select r with r.varName = \"var\"";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_NOTHROW(Validator::Validate(query));
  }

  SECTION("Valid synonym with attrName for With Clause should pass") {
    std::string query_str = "print p;"
                            "Select p with p.varName = \"var\"";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_NOTHROW(Validator::Validate(query));
  }

  SECTION("Valid synonym with attrName for With Clause should pass") {
    std::string query_str = "variable v;"
                            "Select v with v.varName = \"variable\"";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_NOTHROW(Validator::Validate(query));
  }

  SECTION("Exact expression for Pattern should pass") {
    std::string query_str = "assign a; variable v;"
                            "Select a pattern a(v, \"quota\")";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_NOTHROW(Validator::Validate(query));
  }

  SECTION("Invalid types between LHS and RHS for With Clause "
          "should throw error") {
    std::string query_str = "stmt s;"
                            "Select s with s.stmt# = \"ident\"";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_THROWS_AS(Validator::Validate(query),
                      PqlSemanticErrorException);
  }

  SECTION("Invalid types between LHS and RHS for With Clause "
          "should throw error") {
    std::string query_str = "constant c;"
                            "Select c with c.value = \"ident\"";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_THROWS_AS(Validator::Validate(query),
                      PqlSemanticErrorException);
  }

  SECTION("Invalid types between LHS and RHS for With Clause "
          "should throw error") {
    std::string query_str = "print p;"
                            "Select p with p.varName = 12";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_THROWS_AS(Validator::Validate(query),
                      PqlSemanticErrorException);
  }

  SECTION("Invalid types between LHS and RHS for With Clause "
          "should throw error") {
    std::string query_str = "call c;"
                            "Select c with c.procName = 12";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_THROWS_AS(Validator::Validate(query),
                      PqlSemanticErrorException);
  }
}

TEST_CASE("Overall Validation") {
  SelectClParser parser;

  SECTION("Semantically valid") {
    std::string query_str = "variable v; Select v such that Modifies(2, v)";
    QueryPtr query = parser.ParseQuery(query_str);

    REQUIRE_NOTHROW(Validator::Validate(query));
  }
}
