#include <exception>
#include <catch.hpp>

#include "QPS/factories/MasterClauseFactory.h"
#include "QPS/preprocessor/SelectClParser.h"
#include "QPS/models/PQL.h"

using namespace qps; // NOLINT

// Helper method for testing
QueryPtr BuildQuery(
    std::vector<std::pair<SynonymName, EntityName>> synonyms,
    std::vector<std::string> selected_synonyms
) {
  QueryPtr query = std::make_unique<Query>();
  for (auto [syn, entity] : synonyms) {
    query->declare_synonym(syn, entity);
  }
  for (auto selected_syn : selected_synonyms) {
    query->add_selected_synonym(selected_syn);
  }

  return query;
}

// Helper method for testing
void TestNoThrows(std::string query_string) {
  SelectClParser parser;
  REQUIRE_NOTHROW(parser.ParseQuery(query_string));
}

// Helper method for testing
void TestThrows(std::string query_string) {
  SelectClParser parser;
  REQUIRE_THROWS_AS(
      parser.ParseQuery(query_string), PqlSyntaxErrorException);
}

TEST_CASE("Test SelectClParser methods") {
  SelectClParser parser;
  SECTION("Test PreprocessQueryString") {
    std::string query_string = "variable p; select p such that "
                               "Modifies(6, v) pattern a(_, _\" x + y \"_)";
    std::vector<std::string> expected_tokens{
        "variable", "p", ";", "select", "p", "such", "that",
        "Modifies", "(", "6", ",", "v", ")",
        "pattern", "a", "(", "_", ",", "_\"x+y\"_", ")"
    };
    REQUIRE(parser.PreprocessQueryString(query_string) == expected_tokens);

    // With random whitespaces and newlines
    query_string = "variable     p;\n   select    p   such  \n   "
                   "that Modifies(6, v) \n pattern a(_, _\"x+y\"_)";
    REQUIRE(parser.PreprocessQueryString(query_string) == expected_tokens);
  }
}

TEST_CASE("Test ParseQuery") {
  SelectClParser parser;
  MasterClauseFactory master_clause_factory;

  SECTION("Query with no declarations should not throw SyntaxError") {
    // It needs to throw SemanticError
    std::string query_string = "Select p";
    QueryPtr actual_query = parser.ParseQuery(query_string);
    QueryPtr expected_query = BuildQuery({}, {"p"});

    REQUIRE(*actual_query == *expected_query);
  }

  SECTION("Query with no clauses should parse correctly") {
    std::string query_string = "procedure p; Select p";
    QueryPtr actual_query = parser.ParseQuery(query_string);
    QueryPtr expected_query = BuildQuery(
        {{"p", PQL::kProcedureEntityName}},
        {"p"});

    REQUIRE(*actual_query == *expected_query);
  }

  SECTION("Query with one such-that clauses should parse correctly") {
    std::string query_string = "variable v; Select v such that Modifies(6, v)";
    QueryPtr actual_query = parser.ParseQuery(query_string);
    QueryPtr expected_query = BuildQuery(
        {{"v", PQL::kVariableEntityName}},
        {"v"});
    expected_query->add_clause(
        master_clause_factory.Create(PQL::kModifiesRelName,
                                     expected_query->CreateArgument("6"),
                                     expected_query->CreateArgument("v")));

    REQUIRE(*actual_query == *expected_query);
  }

  SECTION("Query with one clause and selected tuple should parse correctly") {
    std::string query_string = "variable v; stmt s; "
                               "Select <s, v> such that Modifies(s, v)";
    QueryPtr actual_query = parser.ParseQuery(query_string);
    QueryPtr expected_query = BuildQuery(
        {{"v", PQL::kVariableEntityName},
         {"s", PQL::kStmtEntityName}},
        {"s", "v"});
    expected_query->add_clause(
        master_clause_factory.Create(PQL::kModifiesRelName,
                                     expected_query->CreateArgument("s"),
                                     expected_query->CreateArgument("v")));

    REQUIRE(*actual_query == *expected_query);
  }

  SECTION("Query with one pattern clauses should parse correctly") {
    std::string query_string = "assign a; Select a pattern a(v, \"x + y\")";
    QueryPtr actual_query = parser.ParseQuery(query_string);
    QueryPtr expected_query = BuildQuery(
        {{"a", PQL::kAssignEntityName}},
        {"a"});
    expected_query->add_clause(
        master_clause_factory.Create(
            PQL::kModifiesRelName,
            expected_query->CreateArgument("a"),
            expected_query->CreateArgument("v")));
    expected_query->add_clause(
        master_clause_factory.Create(
            PQL::kPatternRelName,
            expected_query->CreateArgument("a"),
            expected_query->CreateArgument("\"x+y\"")));

    REQUIRE(*actual_query == *expected_query);
  }

  SECTION("Query with one with clause should parse correctly") {
    std::string query_string = "assign a; Select a with a.stmt# = 12";
    QueryPtr actual_query = parser.ParseQuery(query_string);
    QueryPtr expected_query = BuildQuery(
        {{"a", PQL::kAssignEntityName}},
        {"a"});

    expected_query->add_clause(
        master_clause_factory.Create(
            PQL::kWithRelName,
            expected_query->CreateArgument("a.stmt#"),
            expected_query->CreateArgument("12")));

    REQUIRE(*actual_query == *expected_query);
  }

  SECTION(
      "Query with multiple declarations, multiple synonyms "
      "and multiple such-that and pattern clauses should parse correctly") {
    std::string query_string = "variable v; procedure p; "
                               "Select v such that Modifies(6, v) "
                               "such that Modifies(3, v) "
                               "pattern a(_, \"x + y\") "
                               "pattern a(\"variable\", _\"x\"_)";
    QueryPtr actual_query = parser.ParseQuery(query_string);
    QueryPtr expected_query = BuildQuery(
        {{"v", PQL::kVariableEntityName}, {"p", PQL::kProcedureEntityName}},
        {"v"});

    expected_query->add_clause(
        master_clause_factory.Create(
            PQL::kModifiesRelName,
            expected_query->CreateArgument("6"),
            expected_query->CreateArgument("v")));
    expected_query->add_clause(
        master_clause_factory.Create(
            PQL::kModifiesRelName,
            expected_query->CreateArgument("3"),
            expected_query->CreateArgument("v")));
    expected_query->add_clause(
        master_clause_factory.Create(
            PQL::kModifiesRelName,
            expected_query->CreateArgument("a"),
            expected_query->CreateArgument("_")));
    expected_query->add_clause(
        master_clause_factory.Create(
            PQL::kPatternRelName,
            expected_query->CreateArgument("a"),
            expected_query->CreateArgument("\"x+y\"")));
    expected_query->add_clause(
        master_clause_factory.Create(
            PQL::kModifiesRelName,
            expected_query->CreateArgument("a"),
            expected_query->CreateArgument("\"variable\"")));
    expected_query->add_clause(
        master_clause_factory.Create(
            PQL::kPatternRelName,
            expected_query->CreateArgument("a"),
            expected_query->CreateArgument("_\"x\"_")));

    REQUIRE(*actual_query == *expected_query);
  }

  SECTION(
      "Query with multiple declarations, multiple synonyms "
      "and multiple such-that and pattern clauses and "
      "many random whitespaces and tabs"
      "should parse correctly") {
    std::string query_string = "variable  \t  v;    procedure    p; "
                               "Select v such  that \t  Modifies(  6, v) "
                               "  such  \t    that    Modifies(3, v) "
                               "pattern a(_, \"x + y   \t  \") "
                               "   \t pattern a(_,  \"   x  \t\")";
    QueryPtr actual_query = parser.ParseQuery(query_string);
    QueryPtr expected_query = BuildQuery(
        {{"v", PQL::kVariableEntityName}, {"p", PQL::kProcedureEntityName}},
        {"v"});
    expected_query->add_clause(
        master_clause_factory.Create(
            PQL::kModifiesRelName,
            expected_query->CreateArgument("6"),
            expected_query->CreateArgument("v")));
    expected_query->add_clause(
        master_clause_factory.Create(
            PQL::kModifiesRelName,
            expected_query->CreateArgument("3"),
            expected_query->CreateArgument("v")));
    expected_query->add_clause(
        master_clause_factory.Create(
            PQL::kModifiesRelName,
            expected_query->CreateArgument("a"),
            expected_query->CreateArgument("_")));
    expected_query->add_clause(
        master_clause_factory.Create(
            PQL::kPatternRelName,
            expected_query->CreateArgument("a"),
            expected_query->CreateArgument("\"x+y\"")));
    expected_query->add_clause(
        master_clause_factory.Create(
            PQL::kModifiesRelName,
            expected_query->CreateArgument("a"),
            expected_query->CreateArgument("_")));
    expected_query->add_clause(
        master_clause_factory.Create(
            PQL::kPatternRelName,
            expected_query->CreateArgument("a"),
            expected_query->CreateArgument("\"x\"")));

    REQUIRE(*actual_query == *expected_query);
  }

    // In the following testcases, it is too verbose to create the
    // full expected clause as the queries are much longer,
    // so will just be testing NoThrows or Throws.
    // The previous testcases cover whether the expected query has the
    // correct clauses.
  SECTION("Query with pattern before such-that should parse correctly") {
    std::string query_string = "variable v;"
                               "Select v pattern a(_, \"x + y\") "
                               "such that Modifies(6, v)";

    TestNoThrows(query_string);
  }

  SECTION("Query with interleaving clauses of different types"
          "should parse correctly") {
    std::string query_string = "variable v;"
                               "Select v pattern a(_, \"x + y\") "
                               "such that Modifies(6, v) "
                               "pattern a(v, _\"x\"_) "
                               "with 12 = \"test\" "
                               "such that Uses(6, v) "
                               "with a.stmt# = c.value "
                               "pattern a(_, _)";

    TestNoThrows(query_string);
  }

  SECTION("Query with mix of using 'and' and no 'and' "
          "should parse correctly") {
    std::string query_string = "variable v;"
                               "Select v pattern a(_, \"x + y\") "
                               "such that Modifies(6, v) "
                               "and Uses(6, v) "
                               "such that Parent(6, 7)";

    TestNoThrows(query_string);
  }

  SECTION("Query with interleaving clauses of different types"
          "and with 'and' should parse correctly") {
    std::string query_string = "variable v;"
                               "Select v pattern a(_, \"x + y\") "
                               "such that Modifies(6, v) "
                               "pattern a(v, _\"x\"_) "
                               "and pattern a(_, \"x\") "
                               "such that Uses(6, v) "
                               "and Parent(6, 7)";

    TestNoThrows(query_string);
  }

  SECTION("Query with Select attrRef should parse correctly") {
    std::string query_string = "stmt s;"
                               "Select s.stmt#";

    TestNoThrows(query_string);
  }

  SECTION("Query with Select <attrRef, attrRef> should parse correctly") {
    std::string query_string = "stmt s; procedure p;"
                               "Select <s.stmt#, p.procName>";

    TestNoThrows(query_string);
  }

    /* ============ ERROR CASES =============== */
  SECTION("Query with both 'and' and 'such-that'"
          "should throw error") {
    std::string query_string = "variable v;"
                               "Select v pattern a(_, \"x + y\") "
                               "such that Modifies(6, v) "
                               "and such that Uses(6, v)";

    TestThrows(query_string);
  }

  SECTION("Query with using 'and' to connect "
          "between such-that and pattern"
          "should throw error") {
    std::string query_string = "variable v;"
                               "Select v such that Modifies(6, v) "
                               "and pattern a(v, _\"x\"_)";

    TestThrows(query_string);
  }

  SECTION("Query with using 'and' to connect "
          "between pattern and with"
          "should throw error") {
    std::string query_string = "variable v;"
                               "Select v pattern a(_, \"x + y\") "
                               "and with a.stmt# = c.value";

    TestThrows(query_string);
  }

  SECTION("Query with using 'and' to connect "
          "between such-that and with"
          "should throw error") {
    std::string query_string = "variable v;"
                               "Select v such that Modifies(6, v) "
                               "and with a.stmt# = c.value";

    TestThrows(query_string);
  }

  SECTION("Query with Select attrRef, attrRef should throw error") {
    // Missing diamond braces
    std::string query_string = "stmt s; procedure p;"
                               "Select s.stmt#, p.procName";

    TestThrows(query_string);
  }
}
